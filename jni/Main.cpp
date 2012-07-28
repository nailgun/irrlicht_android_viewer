#include "Context.hpp"
#include "ModelViewer.hpp"
#include "EventLoop.hpp"
#include "GraphicsService.hpp"
#include "Log.hpp"

void android_main(android_app* pApplication) {
    packt::EventLoop lEventLoop(pApplication);

    // Creates services.
    packt::GraphicsService lGraphicsService(pApplication);

    // Fills the context.
    packt::Context lContext = { &lGraphicsService };

    // Starts the game loop.
    dbs::ModelViewer lModelViewer(&lContext);
    lEventLoop.run(&lModelViewer);
}
