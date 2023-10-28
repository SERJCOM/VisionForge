#pragma once

#include <glm/glm.hpp>
#include <iostream>

namespace vision{


std::ostream& operator << (std::ostream& out, glm::vec3 vec){
    out << "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z;
    return out;
}

}