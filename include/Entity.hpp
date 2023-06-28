#pragma once 


namespace lthm{

class Entity{

public:

    Entity() = default;

    virtual void Update(){}
    virtual void Start(){}

    ~Entity() = default;

private:



};

}