#include "Model.hpp"
#include "Log.hpp"

namespace dbs {
    Model::Model(packt::Context* pContext, const char* mesh, const char* texture) :
      mGraphicsService(pContext->mGraphicsService) {
        mMesh = pContext->mGraphicsService->registerObject(
            texture, mesh, &mLocation);
    }

    void Model::spawn() {
        mLocation.setPosition(mGraphicsService->getWidth()  * 1 / 2,
                mGraphicsService->getHeight() * 1 / 2);
    }

    void Model::update() {
    }
}
