#pragma once
#include "model.h"
#include "collection.hpp"

class ModelManager: public Collection{
public:
    ModelManager() = default;

    Model* AddLight(std::string path){
        Model _model(path);
        return static_cast<Model*>(this->AddComponent(_model));
    }

    Model* AddLight(Model _model){
        return static_cast<Model*>(this->AddComponent(_model));
    }

    Model* AddLight(){
        return static_cast<Model*>(this->AddComponent());
    }

    virtual void Update() override const{
        for(const auto& model : _components){
            static_cast<Model*>(model.get())->Draw();
        }
    }
};
