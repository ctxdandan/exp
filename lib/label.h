#ifndef TOL_LABEL_H
#define TOL_LABEL_H

#include <algorithm>
#include <iterator>
#include <set>
#include <vector>

template<typename Vertex> using Label = std::set<Vertex>;
template<typename Vertex> using Labels = std::vector<Label<Vertex>>;

template<typename Vertex>
Label<Vertex> operator|(const Label<Vertex>& s, const Label<Vertex>& t) {
    using std::begin;
    using std::end;

    Label<Vertex> result;

    std::set_union(begin(s), end(s), begin(t), end(t), std::inserter(result, end(result)));

    return result;
}

template<typename Vertex>
Label<Vertex> operator&(const Label<Vertex>& s, const Label<Vertex>& t) {
    using std::begin;
    using std::end;

    Label<Vertex> result;

    std::set_intersection(begin(s), end(s), begin(t), end(t), std::inserter(result, begin(result)));

    return result;
}

#endif // TOL_LABEL_H
