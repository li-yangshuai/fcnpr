//
// Created by fpeng on 2020/6/22.
//

#include "Solution.h"
#include <algorithm>

namespace fcnpr {

    Solution::Solution(ChessBoard &chb, const Network &ntk) : chess_board(chb), network(ntk)
    {}

    std::optional<Position> Solution::find_position(Id) const noexcept {
        auto ret = std::nullopt;

        for(auto it=std::crbegin(placements), it!=std::crend(placements),++it) {
            auto pos = it->position(Id);
            if(pos) {
                ret = pos;
                break;
            }
        }
        return ret;
    }

}