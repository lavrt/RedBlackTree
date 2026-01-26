#pragma once

#include <set>

#include "tree.hpp"

namespace RangeQuery {

template <typename KeyT>
int range_query(const Trees::RBTree<KeyT>& s, KeyT fst, KeyT snd) {
    return (fst > snd) ? 0 : s.Distance(s.LowerBound(fst), s.UpperBound(snd));
}

template <typename KeyT>
int range_query(const std::set<KeyT>& s, KeyT fst, KeyT snd) {
    return (fst > snd) ? 0 : std::distance(s.lower_bound(fst), s.upper_bound(snd));
}

} // namespace RangeQuery
