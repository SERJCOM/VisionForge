#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "VisionForge/Engine/Mesh.hpp"
#include <assimp/material.h>
#include "VisionForge/Common/Texture.hpp"

namespace Li{

enum Type{
    DIFFUSE,
    NORMALS,
    METALNESS,
    ROUGHNESS,
    AO
};

class Material{
public:
    struct sMaterials{
        std::string path;
        int type;
    };


    void AddNewMaterial(std::string path, Li::Type type, std::string name){
        sMaterials mat;
        mat.path = path;
        mat.type = type;

        _materials.insert(std::pair{name, mat});
    }

    std::vector<sMaterials> GetMaterials(std::string name){
        std::vector<sMaterials> returnMat;

        typedef std::multimap<std::string, sMaterials>::iterator MMAPIterator;
        std::pair<MMAPIterator, MMAPIterator> result = _materials.equal_range(name);

        for (MMAPIterator it = result.first; it != result.second; it++)
            returnMat.push_back(it->second);
        
        return returnMat;
    }

    // TODO:: может возникать ошибка если имя не было найдено (будет возвращаться последнее значение)
    // sMaterials GetMaterial(std::string name){
    //     return _materials[name];
    // }

    // int Count(Li::Type name){
    //     return _listMat.count(name);
    // }

    std::vector<sTexture> GetTexture(std::string meshName, std::vector<sTexture> &textures){
        std::vector<sTexture> sReturn;

        std::vector<sMaterials> vMaterial = GetMaterials(meshName);

        for(int i = 0; i < vMaterial.size(); i++){
            bool flag = false;
            for(int j = 0; j < textures.size(); j++){
                if(textures[j].path == vMaterial[i].path){
                    sReturn.push_back(textures[j]);
                    flag = true;
                    break;
                }
            }
            if(!flag){
                sTexture _texture;
                std::string _type;
                _texture.id = Texture::LoadTextureFromFile(vMaterial[i].path);
                switch (vMaterial[i].type){
                    case DIFFUSE:
                        _type = "texture_diffuse";
                        break;
                    case NORMALS:
                        _type = "texture_normal";
                        break;
                    case METALNESS:
                        _type = "texture_metalic";
                        break;
                    case ROUGHNESS:
                        _type = "texture_roughness";
                        break;
                    case AO:
                        _type = "texture_ao";
                        break;
                }
                _texture.type = _type;
                _texture.path = vMaterial[i].path;
                sReturn.push_back(_texture);
                textures.push_back(_texture);
            }
        }

        return sReturn;
    }

private:
    std::multimap<std::string, sMaterials> _materials;
};

};