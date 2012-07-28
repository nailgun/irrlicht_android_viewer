#ifndef _PACKT_EVENTLOOP_HPP_
#define _PACKT_EVENTLOOP_HPP_

#include "ActivityHandler.hpp"
#include "Types.hpp"

#include <android_native_app_glue.h>

namespace packt {
    class EventLoop {
    public:
        EventLoop(android_app* pApplication);
        void run(ActivityHandler* pActivityHandler);

    protected:
        void activate();
        void deactivate();

        void processAppEvent(int32_t pCommand);

    private:
        // Private callbacks handling events occuring in the thread loop.
        static void callback_event(android_app* pApplication,
            int32_t pCommand);

    private:
        // Saves application state when application is active/paused.
        bool mEnabled;
        // Indicates if the event handler wants to exit.
        bool mQuit;
        // Application details provided by Android.
        android_app* mApplication;
        // Activity event observer.
        ActivityHandler* mActivityHandler;
    };
}
#endif
