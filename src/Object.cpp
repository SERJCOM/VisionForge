#include "VisionForge/Engine/Object.hpp"
#include "VisionForge/Engine/Engine.hpp"
#include "VisionForge/System/System.hpp"

void vision::Object::SetObjectPosition(glm::vec3 pos)
{
    pos_ = pos;
}

void vision::Object::MoveObject(glm::vec3 pos)
{
    pos_ += pos;
}

void vision::Object::SetObjectSize(glm::vec3 size)
{
    size_ = size;
}

void vision::Object::ScaleObject(glm::vec3 size)
{
    size_ += size;
}

glm::vec3 vision::Object::GetObjectSize() const
{
    return size_;
}

void vision::Object::RotateObject(glm::vec3 rotate)
{
    rotate_ += rotate;
}

glm::vec3 vision::Object::GetObjectRotation() const
{
    return rotate_;
}

void vision::Object::SetEnginePtr(Engine *sys)
{
    gEngine = sys;
}

void vision::Object::SetEnvironmentPtr(Environment *env)
{
    gEnv = env;
}

void vision::Object::SetObjectRotation(glm::vec3 rotate)
{
    rotate_ = rotate;
}

glm::vec3 vision::Object::GetObjectPosition() const
{
    return pos_;
}
