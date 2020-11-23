#include "../../../modules/task_3/zoreev_m_moore_algorithm/moore_algorithm.h"

size_t* mooreAlgorithm(size_t vertices_count, size_t edges_count, int64_t *edges, size_t root) {
    if (vertices_count < 2) {
        throw std::runtime_error("WRONG SIZE");
    }
    int64_t *distance = new int64_t[vertices_count];
    size_t *predecessor = new size_t[vertices_count];
    for (size_t i = 0; i < vertices_count; i++) {
        distance[i] = INT64_MAX;
        predecessor[i] = SIZE_MAX;
    }
    distance[root] = 0;

    for (size_t i = 0; i < vertices_count - 1; i++) {
        for (size_t j = 0; j < edges_count; j += 3) {
            if (distance[edges[j + 1]] > distance[edges[j]] + edges[j + 2]) {
                distance[edges[j + 1]] = distance[edges[j]] + edges[j + 2];
                predecessor[edges[j + 1]] = edges[j];
            }
        }
    }
    delete[] distance;

    return predecessor;
}