#pragma once
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <thread>

//Threading
#include "IExecutionEvent.h"

class hitable;
class ThreadPool;
class camera;

using namespace cv;

static bool isRunning = false;
static int count = 0;

class BaseRaytracing: public IExecutionEvent
{
public:

	static int const LENGTH = 1080;
	static int const WIDTH = 1080;
	static int const RAYS = 400;


	BaseRaytracing();
	void run();

	//thread related
	void onFinishedExecution();
private:
	
	
	void FinishedRayTracing();
	void PrintOutput();

	hitable* generate_random_scenes();

	int nx;
	int ny;
	int ns;

	

	camera* cam;
	hitable* world;
	
	Mat *mat;
	std::vector<int> compression_params;

	//Multithreading
	ThreadPool* threadPool;

};


