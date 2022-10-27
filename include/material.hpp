#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Li{

enum Type{
    DIFFUSE,
    NORMALS,
    METALNESS
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

private:
    std::multimap<std::string, sMaterials> _materials;
};

};