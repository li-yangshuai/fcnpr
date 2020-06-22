//
// Created by fpeng on 2020/6/22.
//

#ifndef ROPPER_TYPES_H
#define ROPPER_TYPES_H

#include <utility>
#include <vector>
#include <set>

namespace fcnpr {
    using Id         = uint64_t;
    using Coordinate = uint64_t;
    using Position   = std::pair<Coordinate, Coordinate>;
    using Region     = std::set<Position>;
    using Placement  = std::pair<Id, Position>;
    using Route      = std::vector<Position>;
    using TimeZone   = uint8_t;
}

#endif //ROPPER_TYPES_H
