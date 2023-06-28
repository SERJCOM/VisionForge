#pragma once


#include <iostream>
#include "window.h"
#include "Engine.h"
#include "CameraEntity.h"
#include "model.h"
#include <math.h>
#include "Texture.h"
#include "Shader.h"
#include <string>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "lightManager.hpp"
#include "mesh.hpp"
#include <vector>
#include <GL/glew.h>
#include "shape.hpp"
#include "framebuffer.hpp"
#include "scene_manager.h"
#include "shadow.hpp"
#include "material.hpp"

PhysicsCommon physicsCommon;
PhysicsWorld* world = physicsCommon.createPhysicsWorld();


using	std::cout;
using	std::endl;

