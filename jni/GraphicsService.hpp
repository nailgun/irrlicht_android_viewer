#ifndef _PACKT_GRAPHICSSERVICE_HPP_
#define _PACKT_GRAPHICSSERVICE_HPP_

#include "GraphicsObject.hpp"
#include "Types.hpp"

#include <android_native_app_glue.h>
#include <irrlicht.h>
#include <EGL/egl.h>

namespace packt {
    class GraphicsService {
    public:
        GraphicsService(android_app* pApplication);

        const int32_t& getHeight();
        const int32_t& getWidth();

        status start();
        void stop();
        status update();

        GraphicsObject::ptr registerObject(const char* pTexture,
            const char* pMesh, Location* pLocation);

    protected:
        void setup();

    private:
        android_app* mApplication;

        // Display properties.
        int32_t mWidth, mHeight;
        EGLDisplay mDisplay;
        EGLSurface mSurface;
        EGLContext mContext;

        // Graphics resources.
        irr::IrrlichtDevice* mDevice;
        irr::video::IVideoDriver* mDriver;
        irr::scene::ISceneManager* mSceneManager;

        GraphicsObject::vec mObjects;
    };
}
#endif
