/*
 * Copyright (c) 2015-2022 Morwenn
 * SPDX-License-Identifier: MIT
 */
#ifndef CPPSORT_DETAIL_LOW_COMPARISONS_SORT5_H_
#define CPPSORT_DETAIL_LOW_COMPARISONS_SORT5_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "../rotate_right.h"

namespace cppsort::detail
{
    template<>
    struct low_comparisons_sorter_impl<5u>
    {
        template<
            typename RandomAccessIterator,
            typename Compare = std::less<>,
            typename Projection = std::identity,
            typename = detail::enable_if_t<is_projection_iterator_v<
                Projection, RandomAccessIterator, Compare
            >>
        >
        auto operator()(RandomAccessIterator first, RandomAccessIterator,
                        Compare compare={}, Projection projection={}) const
            -> void
        {
            using utility::iter_swap;
            auto&& comp = utility::as_function(compare);
            auto&& proj = utility::as_function(projection);

            // Order elements pair-wise

            iter_swap_if(first, first + 1u, compare, projection);
            iter_swap_if(first + 2u, first + 3u, compare, projection);

            // Order pairs of elements by max value

            if (comp(proj(first[3u]), proj(first[1u]))) {
                iter_swap(first, first + 2u);
                iter_swap(first + 1u, first + 3u);
            }

            // Merge-insert minimal elements

            if (comp(proj(first[4u]), proj(first[1u]))) {
                // Insert last element in [0, 1, 3]
                if (comp(proj(first[4u]), proj(first[0u]))) {
                    rotate_right<5u>(first);
                } else {
                    rotate_right<4u>(first + 1u);
                }
            } else {
                if (comp(proj(first[4u]), proj(first[3u]))) {
                    rotate_right<3u>(first + 2u);
                } else {
                    // Insert 2 in [0, 1, 3]
                    if (comp(proj(first[2u]), proj(first[0u]))) {
                        rotate_right<3u>(first);
                    } else {
                        iter_swap_if(first + 1u, first + 2u,
                                     std::move(compare), std::move(projection));
                    }
                    return;
                }
            }

            // Insert 3 in [0, 1, 2]
            if (comp(proj(first[3u]), proj(first[1u]))) {
                if (comp(proj(first[3u]), proj(first[0u]))) {
                    rotate_right<4u>(first);
                } else {
                    rotate_right<3u>(first + 1u);
                }
            } else {
                iter_swap_if(first + 2u, first + 3u,
                             std::move(compare), std::move(projection));
            }
        }
    };
}

#endif // CPPSORT_DETAIL_LOW_COMPARISONS_SORT5_H_
