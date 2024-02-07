#pragma once
#include "IWorkerAction.h"
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <mutex>

//Raytracing

using namespace cv;

//Raytracing

class IExecutionEvent;
class camera;
class hitable;


class StreamRay: public IWorkerAction
{
public:
	StreamRay(int x, int y, int row, int rays, Mat* mat, camera* cam, hitable* world, IExecutionEvent* executionEvent);
	~StreamRay();


	void onStartTask() override;

private:
	//Ray Parameters
	
	int currentRow = 0;
	int ns = 0;
	int nx = 0;
	int ny = 0;

	//World
	hitable* world = nullptr;

	//Camera
	camera* cam = nullptr;

	//Material
	Mat* mat;

	IExecutionEvent* execEvent;

	std::mutex guard;
};



