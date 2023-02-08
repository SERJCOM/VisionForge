#pragma once
#include <memory>
#include <vector>
#include "component.hpp"


class Collection{
public:

    Collection() = default;

    virtual IComponent* AddComponent(const IComponent& component){
        IComponent* _component = new IComponent(component);
        _components.push_back(std::shared_ptr<IComponent>(_component));
        return _component;
    }

    virtual IComponent* AddComponent(){
        IComponent* _component = new IComponent();
        _components.push_back(std::shared_ptr<IComponent>(_component));
        return _component;
    }

    virtual IComponent* GetComponent(int index) const {
        return _components.at(index).get();
    }

protected:
    std::vector<std::shared_ptr<IComponent>> _components;
};