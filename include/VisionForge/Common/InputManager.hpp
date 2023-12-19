#pragma once

#include <memory>
#include "VisionForge/EntitySystem/Component.hpp"
#include <string>
#include <functional>
#include <vector>

/*
Отвечает за центрилизованное управление вводом. Например ввод клавиатурой, геймпадом и тд
*/

namespace vision{

namespace input{

    enum class DeviceType{
        KEYBOARD,
        GAMEPAD,
        MOUSE
    };

    class DeviceParametrs{
        public:
            DeviceParametrs() = default;
            
            void SetDeviceType(DeviceType type){
                type_ = type;
            }

            void SetKeyIndex(int key){
                key_ = key;
            }

            void SetAxis(int axis){
                axis_ = axis;
            }

            DeviceType GetDeviceType() const{
                return type_;
            }

            int GetKeyIndex() const {
                return key_;
            }

            int GetAxis() const {
                return axis_;
            }

            bool operator==(const DeviceParametrs& device) const{
                return device.GetDeviceType() == type_ && key_ == device.GetKeyIndex();
            }

        private:
            DeviceType  type_;
            int key_;
            int axis_;
            
    };


    class IInputManager : public IComponent{
    public:

        IInputManager() = default;

        virtual ~IInputManager() = default;

        virtual void AddInputEvent(std::string_view name, std::function<void(int activation, float value)>&& func) = 0;

        virtual void CreateNewInput(DeviceParametrs device, std::string_view name) = 0;

        virtual std::vector<std::string> GetInputNames() const = 0;
    };

    std::unique_ptr<IInputManager> CreateBasicInputManager();

}

}