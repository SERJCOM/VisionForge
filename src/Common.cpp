#include "VisionForge/Common/Common.hpp"

namespace vision{
std::ostream& operator << (std::ostream& out, glm::vec3 vec){
    out << "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z;
    return out;
}

}