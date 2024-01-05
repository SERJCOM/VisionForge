#include "VisionForge/Engine/ShadowManager.hpp"

class ShadowFrameBuffer: public vision::FrameBuffer{
public:

    ShadowFrameBuffer(){
    }

    void Init() override{
        UseBuffer();

    }


private:




};

// void vision::ShadowManager::Start(){

// }

vision::ShadowManager::ShadowManager()
{
}

void vision::ShadowManager::PrepareShadows()
{
}

void vision::ShadowManager::UseShadows()
{
}
