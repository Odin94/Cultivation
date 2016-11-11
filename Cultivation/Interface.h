#pragma once
#include "Camera.h"

class Interface
{
public:
	Interface();
	~Interface();

	Camera camera;


	void draw();
};

