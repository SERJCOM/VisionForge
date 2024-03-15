#pragma once

#include <glm/glm.hpp>
// #include "VisionForge/EntitySystem/VisualComponent.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/ModelComponent.hpp"

namespace vision
{
    // class ModelComponent;
    class PostProcessingManager;

    namespace post
    {
        class Sun : public vision::ModelComponent
        {
        public:
            Sun() = default;

            void Start() override;


        private:

            friend class PostProcessingManager;

        };

    }

} // namespace vision

