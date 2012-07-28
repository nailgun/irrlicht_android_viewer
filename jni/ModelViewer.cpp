#include "ModelViewer.hpp"
#include "Log.hpp"

namespace dbs {
    ModelViewer::ModelViewer(packt::Context* pContext) :
        mGraphicsService(pContext->mGraphicsService),
        mModel(pContext, "dwarf.x", "metal.png") {

        packt::Log::info("Creating ModelViewer");
    }

    packt::status ModelViewer::onActivate() {
        packt::Log::info("Activating ModelViewer");

        // Starts services.
        if (mGraphicsService->start() != packt::STATUS_OK) {
            return packt::STATUS_KO;
        }

        // Initializes game objects.
        mModel.spawn();

        return packt::STATUS_OK;
    }

    void ModelViewer::onDeactivate() {
        packt::Log::info("Deactivating ModelViewer");
        mGraphicsService->stop();
    }

    packt::status ModelViewer::onStep() {
        // Updates entities.
        mModel.update();

        // Updates services.
        if (mGraphicsService->update() != packt::STATUS_OK) {
            return packt::STATUS_KO;
        }
        return packt::STATUS_OK;
    }

    void ModelViewer::onStart() {
        packt::Log::info("onStart");
    }

    void ModelViewer::onResume() {
        packt::Log::info("onResume");
    }

    void ModelViewer::onPause() {
        packt::Log::info("onPause");
    }

    void ModelViewer::onStop() {
        packt::Log::info("onStop");
    }

    void ModelViewer::onDestroy() {
        packt::Log::info("onDestroy");
    }

    void ModelViewer::onSaveState(void** pData, size_t* pSize) {
        packt::Log::info("onSaveInstanceState");
    }

    void ModelViewer::onConfigurationChanged() {
        packt::Log::info("onConfigurationChanged");
    }

    void ModelViewer::onLowMemory() {
        packt::Log::info("onLowMemory");
    }

    void ModelViewer::onCreateWindow() {
        packt::Log::info("onCreateWindow");
    }

    void ModelViewer::onDestroyWindow() {
        packt::Log::info("onDestroyWindow");
    }

    void ModelViewer::onGainFocus() {
        packt::Log::info("onGainFocus");
    }

    void ModelViewer::onLostFocus() {
        packt::Log::info("onLostFocus");
    }
}
