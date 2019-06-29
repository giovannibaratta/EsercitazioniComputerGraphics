#include "glm/glm.hpp"
#include "BaseObject.h"

using namespace glm;

#pragma once
class Movable : public BaseObject
{
	public:
		Movable(vec4 position);

		virtual void move(vec4 position);
};
