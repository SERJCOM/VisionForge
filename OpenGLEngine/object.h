#pragma once
#include <iostream>

class Object {
public:
	int size;
	struct map_color {
		float x, y, z;
	};
	map_color* map;
	Object(int size):size(size){
		map = new map_color[size];
	}
	~Object() {
		delete[] map;
	}
	map_color* change_length(map_color* map, int size) {
		map_color* map_t = new map_color[this->size + size];
		for (int i = 0; i < this->size;i++) {
			map_t[i] = map[i];
		}
		this->size += size;
		delete[] map;
		return map_t;
	}
};