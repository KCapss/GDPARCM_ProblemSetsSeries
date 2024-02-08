#include "BaseRaytracing.h"
#include "StreamRay.h"
#include "Component.h"
#include "ThreadPool.h"



BaseRaytracing::BaseRaytracing()
{
	srand48(time(NULL));
	
	//Define Parameters
	nx = LENGTH;
	ny = WIDTH;
	ns = RAYS;
	
	//Camera Parameters
	vec3 lookfrom(18, 2, -12.5);
	vec3 lookat(-3, 1, 0);

	float dist_to_focus = (lookfrom - lookat).length();
	//Test Case 2: Changing camera aperture to achieve bookeh effect

	float aperture = 1.0f;

	this->cam = new camera (lookfrom, lookat, vec3(0, 1, 0), 20.0f, float(nx) / float(ny), aperture, dist_to_focus);

	//Constructing Png Format
	mat = new Mat(ny, nx, CV_8UC4);
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);
}

void BaseRaytracing::run()
{
	//Intitialize ThreadPool;
	const auto processor_count = std::thread::hardware_concurrency();
	std::cout << "Raytracing by Capalar, K.C" << std::endl;
	std::cout << "Thread Count: " << processor_count << std::endl;
	this->threadPool = new ThreadPool("Worker Pixel", processor_count); //Dependent on physical threads exist on the system
	threadPool->startScheduler();
	isRunning = true;

	//World Geration
	this->world = this->generate_random_scenes();

	//Load Task
	for (int j = ny - 1; j >= 0; j--) {
		StreamRay* sampleRay = new StreamRay(nx, ny, j, ns, mat, cam, world, this);
		this->threadPool->scheduleTask(sampleRay);
	}


	while (isRunning) {

		//Track until all task are done
		if (count == ny) {
			isRunning = false;
			std::cout << "Pended work done" << std::endl;
		}
		//std::cout << "Pended work" << std::endl;
	}

	this->PrintOutput();
}

//IExecutionEvent attached
void BaseRaytracing::onFinishedExecution()
{
	count++;
	if (count == ny) {
		FinishedRayTracing();
	}

	if(count % 10 == 0)
		std::cout << "Lines Remaining: " << ny - count << std::endl;
}

void BaseRaytracing::FinishedRayTracing()
{
	isRunning = false;
}

void BaseRaytracing::PrintOutput()
{
	imwrite("PngOutputRayTrace.png", *mat, compression_params);
}

hitable* BaseRaytracing::generate_random_scenes()
{
	int n = 1000;
	hitable** list = new hitable * [n + 2];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = drand48();
			vec3 center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) { //difuse
					list[i++] = new sphere(center, 0.2, new lambertian(vec3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));

				}
				else if (choose_mat < 0.95f) {//metal
					list[i++] = new sphere(center, 0.2,
						new metal(vec3(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * (1 + drand48())));
				}

				else { //glass
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}
	//Test Case Requirment # 1 - 3 deafult big balls + 1 reflective ball. 


	//Transparent Glass
	list[i++] = new sphere(vec3(-2, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-2, 1, 0), -0.8, new dielectric(1.5));

	//Matte Sphere - Green
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.1, 0.8, 0.2)));

	//Metal Sphere - low gloss
	list[i++] = new sphere(vec3(-0.5, 1, 1), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.2));

	//Mirror Metal - Test case 1 ball
	list[i++] = new sphere(vec3(-6, 1, -1), 1.0, new metal(vec3(1, 1, 1), 0.0));


	return new hitable_list(list, i);
}


