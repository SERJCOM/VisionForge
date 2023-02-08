#pragma once
#include <memory>
#include <vector>

template<class T>
class Component{
public:

    Component() = default;

    T* AddComponent(const T& component){
        T* _component = new T(component);
        _components.push_back(std::shared_ptr<T>(_component));
        return _component;
    }

    T* AddComponent(){
        T* _component = new T();
        _components.push_back(std::shared_ptr<T>(_component));
        return _component;
    }

    T* GetComponent(int index) const {
        return _components.at(index).get();
    }

protected:
    std::vector<std::shared_ptr<T>> _components;
};