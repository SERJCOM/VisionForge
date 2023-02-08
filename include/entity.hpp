#pragma once 


class Entity{

public:

    Entity() = default;

    virtual void Update(){}
    virtual void Start(){}

private:

~Entity(){

}

};