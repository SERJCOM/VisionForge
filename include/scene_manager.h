#pragma once
#include <iostream>
#include <json/json.h>
#include <fstream>
#include <string>
#include "model.h"
#include <vector>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Scene {
public:
	Scene(std::string path) {
		std::ifstream in(path.c_str());
		bool parsingSuccessful = reader.parse(in, root);
		in.close();
	}

	void LoadPhysics(PhysicsWorld* physworld, PhysicsCommon& physicsCommon) {
		this->physworld = physworld;
		this->physicsCommon = &physicsCommon;
	}

	void LoadScene() {
		for (unsigned int i = 0; i < root["objects"].size();i++) {
			const char* path = root["objects"][i]["url"].asCString();
			glm::vec3 scale_object(root["objects"][i]["scale"][0].asFloat(), root["objects"][i]["scale"][1].asFloat(), root["objects"][i]["scale"][2].asFloat());
			glm::vec3 rotate_object(root["objects"][i]["rotate"][0].asInt(), root["objects"][i]["rotate"][1].asInt(), root["objects"][i]["rotate"][2].asInt());
			glm::vec3 position_object(root["objects"][i]["position"][0].asFloat(), root["objects"][i]["position"][1].asFloat(), root["objects"][i]["position"][2].asFloat());
			
			Model Model(path, physworld, physicsCommon);
			Model.ScaleObject(scale_object);
			Model.RotateObject(rotate_object);
			Model.SetObjectPosition(position_object.x, position_object.y, position_object.z);
			objects.push_back(Model);
		}
	}

	void DrawScene(Shader& shader) {
		for (int i = 0; i < objects.size(); i++) {
			objects[i].Draw(shader);
		}
	}


private:
	Json::Value root;
	Json::Reader reader;
	std::vector <Model> objects;
	PhysicsWorld* physworld;
	PhysicsCommon* physicsCommon;
};