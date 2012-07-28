#ifndef _PACKT_MODELVIEWER_HPP_
#define _PACKT_MODELVIEWER_HPP_

#include "ActivityHandler.hpp"
#include "Context.hpp"
#include "GraphicsService.hpp"
#include "Model.hpp"
#include "Types.hpp"

namespace dbs {
    class ModelViewer : public packt::ActivityHandler {
    public:
        ModelViewer(packt::Context* pContext);

    protected:
        packt::status onActivate();
        void onDeactivate();
        packt::status onStep();

        void onStart();
        void onResume();
        void onPause();
        void onStop();
        void onDestroy();

        void onSaveState(void** pData, size_t* pSize);
        void onConfigurationChanged();
        void onLowMemory();

        void onCreateWindow();
        void onDestroyWindow();
        void onGainFocus();
        void onLostFocus();

    private:
        packt::GraphicsService* mGraphicsService;
        Model mModel;
    };
}
#endif
