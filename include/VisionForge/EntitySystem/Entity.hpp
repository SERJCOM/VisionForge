#pragma once 
#include <vector>
#include "Component.hpp"

namespace lthm{

class IEntity{

public:

    IEntity() = default;

    virtual void Update() = 0;
    virtual void Start() = 0;
    virtual std::vector<std::shared_ptr<lthm::IComponent>> GetComponents() const = 0;

    ~IEntity() = default;

private:



};

}