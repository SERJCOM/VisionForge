#pragma once

#include <iostream>
#include <reactphysics3d/reactphysics3d.h> 
#include <reactphysics3d/utils/DebugRenderer.h>
#include <reactphysics3d/containers/Array.h>

using namespace reactphysics3d;

class PhysDebug {
public:
	void LoadLines(Array <DebugRenderer::DebugLine> array);
	
private:
	
};