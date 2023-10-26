#pragma once

#include <glm/glm.hpp>

namespace vision
{
    class Environment;
    class Engine;

    class Object
    {
    public:
        Object() = default;

        virtual ~Object() = default;

        virtual void SetObjectPosition(glm::vec3 pos);
        virtual void MoveObject(glm::vec3 pos);
        glm::vec3 GetObjectPosition() const;

        virtual void SetObjectSize(glm::vec3 size);
        virtual void ScaleObject(glm::vec3 size);
        glm::vec3 GetObjectSize() const;

        virtual void SetObjectRotation(glm::vec3 rotate);
        virtual void RotateObject(glm::vec3 rotate);
        glm::vec3 GetObjectRotation() const;

        void SetEnginePtr(Engine *sys);

        void SetEnvironmentPtr(Environment *env);

    protected:
        Environment *gEnv ;
        Engine *gEngine ;

        glm::vec3 pos_ = glm::vec3(0, 0, 0);
        glm::vec3 size_ = glm::vec3(1, 1, 1);
        glm::vec3 rotate_ = glm::vec3(0, 0, 0);
    };

}