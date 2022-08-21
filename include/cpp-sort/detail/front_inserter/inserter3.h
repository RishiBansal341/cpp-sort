/*
 * Copyright (c) 2015-2022 Morwenn
 * SPDX-License-Identifier: MIT
 */
#ifndef CPPSORT_DETAIL_FRONT_INSERTER3_H_
#define CPPSORT_DETAIL_FRONT_INSERTER3_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cpp-sort/utility/as_function.h>
#include "../rotate_left.h"

namespace cppsort::detail
{
    template<>
    struct front_inserter_n<3u>
    {
        template<
            typename RandomAccessIterator,
            typename Compare,
            typename Projection
        >
        auto operator()(RandomAccessIterator first, Compare compare, Projection projection) const
            -> void
        {
            auto&& comp = utility::as_function(compare);
            auto&& proj = utility::as_function(projection);
            auto&& proj0 = proj(first[0u]);

            if (comp(proj(first[1u]), proj0)) {
                if (comp(proj(first[2u]), proj0)) {
                    rotate_left<3u>(first);
                } else {
                    rotate_left<2u>(first);
                }
            }
        }
    };
}

#endif // CPPSORT_DETAIL_FRONT_INSERTER3_H_
