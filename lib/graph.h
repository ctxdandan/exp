#ifndef TOL_GRAPH_H
#define TOL_GRAPH_H

#include <vector>

template<typename Vertex, typename Weight>
struct DiEdge {
    Vertex to;
    Weight weight;

    DiEdge(Vertex to_, Weight weight_) : to(to_), weight(weight_) {}
};

template<typename Vertex, typename Weight>
using DiEdges = std::vector<DiEdge<Vertex, Weight>>;
template<typename Vertex, typename Weight>
using DiGraph = std::vector<DiEdges<Vertex, Weight>>;

#endif // TOL_GRAPH_H
