#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "window.h"
#include "engine.h"
#include "camera.h"
#include "object.h"
#include <math.h>
#include "texture.h"
#include "shader.h"
#include <string>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "light.h"
#include "mesh.h"
#include <vector>
#include <GL/glew.h>
#include "scene_manager.h""


using	std::cout;
using	std::endl;


PhysicsCommon physicsCommon;
PhysicsWorld* world = physicsCommon.createPhysicsWorld();