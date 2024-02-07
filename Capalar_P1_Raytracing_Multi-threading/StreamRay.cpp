#include "StreamRay.h"
#include "Component.h"

//threading
#include "IExecutionEvent.h"




vec3 color(const ray& r, hitable* world, int depth) {
	hit_record rec;

	if (world->hit(r, 0.00001f, 340282346638528859811704183484516925400.0f, rec)) {
		ray scattered;
		vec3 attenutation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenutation, scattered)) {
			return attenutation * color(scattered, world, depth + 1);
		}
		else {
			return vec3(0, 0, 0);
		}
	}

	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}

}
//Threading

StreamRay::StreamRay(int x, int y, int row, int rays, Mat* mat, camera* cam, hitable* world, IExecutionEvent* executionEvent)
{
	currentRow = row;
    ns = rays;
	this->nx = x;
	this->ny = y;


	this->world = world;
	this->cam = cam;
	this->mat = mat;

	this->execEvent = executionEvent;
}

StreamRay::~StreamRay()
{

}

void StreamRay::onStartTask()
{
	for (int i = 0; i < nx; i++) {
		vec3 col(0, 0, 0);
		for (int s = 0; s < ns; s++) {
			float u = float(i + drand48()) / float(nx);
			float v = float(currentRow + drand48()) / float(ny);
			ray r = cam->get_ray(u, v);
			vec3 p = r.point_at_perimeter(2.0);
			col += color(r, world, 0);
		}

		col /= float(ns);
		col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

		int ir = int(255.99f * col[0]);
		int ig = int(255.99f * col[1]);
		int ib = int(255.99f * col[2]);

		//Resolving Inverted Png
		guard.lock();
		Vec4b& bgra = mat->at<Vec4b>(ny - currentRow - 1, nx - i - 1);
		bgra[0] = saturate_cast<uchar>(ib); // Blue
		bgra[1] = saturate_cast<uchar>(ig); // Green
		bgra[2] = saturate_cast<uchar>(ir); // Red
		bgra[3] = UCHAR_MAX; // ALPHA

		guard.unlock();


	}

	execEvent->onFinishedExecution();
	delete this;
}




