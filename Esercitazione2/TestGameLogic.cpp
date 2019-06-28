#include "TestGameLogic.h"
#include "Triangle.h"
#include <iostream>
#include "Sphere.h"
#include "Rectangle.h"
#include "Sun.h"
#include "Bucket.h"

TestGameLogic::TestGameLogic()
{

}

std::vector<BaseObject*> TestGameLogic::objectToSpawn(){
	
	MyRectangle* sky = new MyRectangle(0, 0, 0, 640, 160);
	sky->setColor(0.274, 0.905, 0.894);
	
	MyRectangle* grass = new MyRectangle(0, 160, 0, 640, 160);
	grass->setColor(0.082, 0.415, 0.188);
	
	Sun* sun = new Sun(50, 50, 20);
	sun->setMainColor(1.0, 1.0, 0.0);
	sun->setRayColor(0.949, 0.737, 0.388);
	
	Bucket* bucket = new Bucket(100, 100, 0, 40, 40);
	bucket->setColor(1.0, 0.0, 0.0);

	std::vector<BaseObject*> objects;
	//objects.push_back(sky);
	//objects.push_back(grass);
	objects.push_back(sun);
	objects.push_back(bucket);
	return objects;
}
