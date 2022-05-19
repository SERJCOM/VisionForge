#pragma once
#include "init.h"

class Physics {
public:
	Transform& transformGet;
	Vector3& positionGet;


	void CreateWorld(PhysicsCommon physicsCommon, PhysicsWorld* world) {
		
		//world = physicsCommon.createPhysicsWorld();
	}

	void SetVectorPosition(glm::vec3 pos) {
		position = Vector3(pos.x, pos.y, pos.z);
	}

	void CreateOrientation() {
		orientation = Quaternion::identity();
	}

	void CreateTransform() {
		transform = Transform(position, orientation);
	}

	void CreateRigidBody() {
		body = world->createRigidBody(transform);
	}

	void UpdatePosition() {
		transform = body->getTransform();
		position = transform.getPosition();
	}

	void UpdateWorld() {
		world->update(timeStep);
	}

	void SetTimeStep(decimal time) { timeStep = time; }
private:
	PhysicsCommon physicsCommon;
	PhysicsWorld* world;
	Vector3 position;
	Quaternion orientation;
	Transform transform;
	RigidBody* body;
	decimal timeStep;
	
};