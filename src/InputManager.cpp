#include "VisionForge/Common/InputManager.hpp"

#include <unordered_map>
// #include <SFML/Window/Keyboard.hpp>
#include <iostream>

// #include "VisionForge/Common/Common.hpp"
#include "VisionForge/System/System.hpp"


using namespace vision;
using namespace std;
using namespace input;

struct DeviceHash{
    size_t operator()(const DeviceParametrs& device) const {
        size_t hash = 0;

        hash += std::hash<int>{}(device.GetKeyIndex()) * 37 ^ 4;
        hash += std::hash<int>{}(static_cast<int>(device.GetDeviceType())) * 37 ^ 2;

        return hash;

    }
};

class BasicInputManager : public input::IInputManager{
public:

    BasicInputManager(){}

    void CreateNewInput(DeviceParametrs device, std::string_view name) override{
        device_names_[device].push_back(string(name));
    }

    void AddInputEvent(std::string_view name, std::function<void(int activation, float value)>&& func) override{
        name_func_[string(name)] = move(func);
    }

    void Start(){

    }

    void Update(){
        input::DeviceType device;
        int activation = 0;

        for(auto&[device, names] : device_names_){
            if(device.GetDeviceType() == DeviceType::KEYBOARD){
                int state = glfwGetKey(System::GetInstance()->GetGLFWWindow(), device.GetKeyIndex());
                if(state == GLFW_PRESS){
                // if(sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(device.GetKeyIndex()))){
                    for(const auto& name : names){
                        if(name_func_.count(name) == 0){
                            std::cerr << name + " is not located in name_func_" << std::endl;
                            assert(false);
                        }

                        name_func_.at(name)(1, 1);
                    }
                }
            }
        }
        
    }

    std::vector<std::string> GetInputNames() const override{
        // return;
    }

private:
    std::unordered_map<std::string, std::function<void(int activation, float value)>> name_func_;
    std::unordered_map<input::DeviceParametrs, std::vector<std::string>, DeviceHash> device_names_;
    
};

std::unique_ptr<input::IInputManager> vision::input::CreateBasicInputManager(){
    return std::make_unique<BasicInputManager>();
}