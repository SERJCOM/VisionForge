#pragma once 
#include <iostream>
#include <GL/glew.h>
#include <memory>
#include <cassert>

namespace vision{

class IFrameBuffer{
public:

    IFrameBuffer() = default;
    virtual ~IFrameBuffer() = default;

    virtual void ClearBuffer() = 0;

    virtual void UseFrameBuffer() = 0;

    virtual int GetTexture() {
        std::cerr << "This method is not supported" << std::endl;
        assert(false);
    }

};


std::unique_ptr<IFrameBuffer> CreateCommonFrameBuffer();
std::unique_ptr<IFrameBuffer> CreateTextureWrittingFrameBuffer();

}