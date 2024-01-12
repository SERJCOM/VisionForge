#pragma once
#include <filesystem>
#include <memory>

// этот класс нужен для управления движком через конфигурационный файл, вывода дебаг информации и тд

namespace vision{

class Engine;

class IConfig{
public:

    virtual void SetConfigFile(std::filesystem::path path) = 0;

    virtual void EnableDebugInformationOnScreen(bool flag) = 0;

private:

    Engine* engine = nullptr;
};

std::unique_ptr<IConfig> CreateDefaultConfigClass();

}