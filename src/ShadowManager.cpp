#include "VisionForge/Engine/ShadowManager.hpp"

class ShadowFrameBuffer: public vision::FrameBuffer{
public:

    ShadowFrameBuffer(){
    }

    void Init() override{
        UseBuffer();

        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);  

        this->DontUseBuffer();
    }


private:




};

void vision::ShadowManager::Start(){
    framebuffer_->Init();

    for(auto& i : shadows_){
        i->Start();
    }


}

vision::ShadowManager::ShadowManager()
{
    framebuffer_ = std::make_unique<ShadowFrameBuffer>();
}

void vision::ShadowManager::PrepareShadows()
{
    for(auto& i : shadows_){
        i->Start();
    }
}

void vision::ShadowManager::UseShadows()
{
}
