#pragma once 
#include <vector>
#include "Component.hpp"
#include <memory>

namespace vision{

class Environment;

class IEntity{
public:

    IEntity() = default;

    virtual void Update() = 0;
    virtual void Start() = 0;
    virtual std::vector<std::shared_ptr<vision::IComponent>> GetComponents() const = 0;

    ~IEntity() = default;

protected:
    Environment* gEnv = nullptr;


};

}