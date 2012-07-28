#ifndef _PACKT_CONTEXT_HPP_
#define _PACKT_CONTEXT_HPP_

#include "Types.hpp"

namespace packt {
    class GraphicsService;

    struct Context {
        GraphicsService* mGraphicsService;
    };
}
#endif
