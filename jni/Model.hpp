#ifndef _DBS_MODEL_HPP_
#define _DBS_MODEL_HPP_

#include "Context.hpp"
#include "GraphicsService.hpp"
#include "GraphicsObject.hpp"
#include "Types.hpp"

namespace dbs {
    class Model {
    public:
        Model(packt::Context* pContext, const char* mesh, const char* texture);

        void spawn();
        void update();

    private:
        packt::GraphicsService* mGraphicsService;
        packt::GraphicsObject::ptr mMesh;
        packt::Location mLocation;
    };
}
#endif
