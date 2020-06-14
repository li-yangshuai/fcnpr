//
// Created by fpeng on 2020/6/14.
//

#include <cassert>
#include "Cell.h"

namespace fcnpr {
    bool Cell::place_node(Id node) noexcept {
        if( node || (current_weight+NODE_WEIGHT)>MAX_CELL_WEIGHT )
            return false;

        this->node = node;
        current_weight += NODE_WEIGHT;
        return true;
    }

    void Cell::unplace_node() noexcept {
        assert(current_weight >= NODE_WEIGHT);

        if(node) {
            node.reset();
            current_weight -= NODE_WEIGHT;
        }
    }

    bool Cell::place_wire() noexcept {
        if(current_weight + WIRE_WEIGHT > MAX_CELL_WEIGHT)
            return false;

        current_weight += WIRE_WEIGHT;
        wire_count += 1;
        return true;
    }

    void Cell::unplace_wire() noexcept {
        assert(wire_count > 0);

        wire_count -= 1;
        current_weight -= WIRE_WEIGHT;
    }
}
