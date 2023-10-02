#pragma once

namespace lthm{

class IComponent{
public:
    IComponent() = default;

    ~IComponent() = default;

    virtual void Update() = 0;

    virtual void Start() = 0;
};

}