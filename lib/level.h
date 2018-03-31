#ifndef TOL_LEVEL_H
#define TOL_LEVEL_H

#include <unordered_map>
#include <utility>
#include <vector>

template<typename Vertex>
struct Levels {
    Levels(size_t n) {lvs.resize(n);}
    void add(Vertex v, size_t lv) {
        if (lvs.size() <= lv) lvs.resize(lv + 1);

        lvs[lv] = v;
        data.insert(std::make_pair(v, lv));
    }

    size_t& operator[](Vertex v) { return data[v]; }

    using iterator = typename std::vector<Vertex>::iterator;

    iterator begin() { return lvs.begin(); }
    iterator end() { return lvs.end(); }

private:
    std::vector<Vertex> lvs;
    std::unordered_map<Vertex, size_t> data;
};

#endif // TOL_LEVEL_H
