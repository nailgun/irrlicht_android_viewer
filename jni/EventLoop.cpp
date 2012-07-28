#include "EventLoop.hpp"
#include "Log.hpp"

namespace packt {
    EventLoop::EventLoop(android_app* pApplication) :
        mEnabled(false), mQuit(false),
        mApplication(pApplication),
        mActivityHandler(NULL) {

        mApplication->userData = this;
        mApplication->onAppCmd = callback_event;
    }

    void EventLoop::run(ActivityHandler* pActivityHandler) {
        int32_t lResult;
        int32_t lEvents;
        android_poll_source* lSource;

        // Makes sure native glue is not stripped by the linker.
        app_dummy();
        mActivityHandler = pActivityHandler;

        // Global step loop.
        packt::Log::info("Starting event loop");
        while (true) {
            // Event processing loop.
            while ((lResult = ALooper_pollAll(mEnabled ? 0 : -1,
                         NULL, &lEvents, (void**) &lSource)) >= 0) {
                // An event has to be processed.
                if (lSource != NULL) {
                    lSource->process(mApplication, lSource);
                }
                // Application is getting destroyed.
                if (mApplication->destroyRequested) {
                    packt::Log::info("Exiting event loop");
                    return;
                }
            }

            // Steps the application.
            if ((mEnabled) && (!mQuit)) {
                if (mActivityHandler->onStep() != STATUS_OK) {
                    mQuit = true;
                    ANativeActivity_finish(mApplication->activity);
                }
            }
        }
    }

    void EventLoop::activate() {
        // Enables activity only if a window is available.
        if ((!mEnabled) && (mApplication->window != NULL)) {
            mQuit = false; mEnabled = true;
            if (mActivityHandler->onActivate() != STATUS_OK) {
                goto ERROR;
            }
        }
        return;

    ERROR:
        mQuit = true;
        deactivate();
        ANativeActivity_finish(mApplication->activity);
    }

    void EventLoop::deactivate() {
        if (mEnabled) {
            mActivityHandler->onDeactivate();
            mEnabled = false;
        }
    }

    void EventLoop::processAppEvent(int32_t pCommand) {
        switch (pCommand) {
        case APP_CMD_CONFIG_CHANGED:
            mActivityHandler->onConfigurationChanged();
            break;
        case APP_CMD_INIT_WINDOW:
            mActivityHandler->onCreateWindow();
            break;
        case APP_CMD_DESTROY:
            mActivityHandler->onDestroy();
            break;
        case APP_CMD_GAINED_FOCUS:
            activate();
            mActivityHandler->onGainFocus();
            break;
        case APP_CMD_LOST_FOCUS:
            mActivityHandler->onLostFocus();
            deactivate();
            break;
        case APP_CMD_LOW_MEMORY:
            mActivityHandler->onLowMemory();
            break;
        case APP_CMD_PAUSE:
            mActivityHandler->onPause();
            deactivate();
            break;
        case APP_CMD_RESUME:
            mActivityHandler->onResume();
            break;
        case APP_CMD_SAVE_STATE:
            mActivityHandler->onSaveState(&mApplication->savedState,
                &mApplication->savedStateSize);
            break;
        case APP_CMD_START:
            mActivityHandler->onStart();
            break;
        case APP_CMD_STOP:
            mActivityHandler->onStop();
            break;
        case APP_CMD_TERM_WINDOW:
            mActivityHandler->onDestroyWindow();
            deactivate();
            break;
        default:
            break;
        }
    }

    void EventLoop::callback_event(android_app* pApplication,
        int32_t pCommand) {
        EventLoop& lEventLoop = *(EventLoop*) pApplication->userData;
        lEventLoop.processAppEvent(pCommand);
    }
}
