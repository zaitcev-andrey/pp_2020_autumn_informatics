#include "../../../modules/task_3/zoreev_m_moore_algorithm/moore_algorithm.h"

void randomCompleteGraph(size_t size, int64_t *graph) {
    std::mt19937 generator;
    generator.seed(static_cast<unsigned int>(time(0)));
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            graph[i * size + j] = generator() % size * 5 + 1;
        }
    }
    for (size_t i = 0; i < size; i++) {
        graph[i * size + i] = INT64_MIN;
    }
}

void printGraph(size_t size, int64_t *graph) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < i; j++) {
            std::cout << std::setw(2) << graph[i * size + j] << ' ';
        }
        std::cout << std::setw(2) << 'x' << ' ';
        for (size_t j = i + 1; j < size; j++)
        {
            std::cout << std::setw(2) << graph[i * size + j] << ' ';
        }
        std::cout << std::endl;
    }
}

void printPredecessor(size_t size, size_t *predecessor) {
    for (size_t i = 0; i < size; i++) {
        std::cout << std::setw(2) << predecessor[i] << ' ';
    }
    std::cout << std::endl;
}

size_t *mooreAlgorithm(size_t size, int64_t *graph, size_t root) {
    if (size < 2) {
        throw std::runtime_error("WRONG SIZE");
    }
    int64_t *distance = new int64_t[size];
    size_t *predecessor = new size_t[size];
    for (size_t i = 0; i < size; i++) {
        distance[i] = INT64_MAX;
        predecessor[i] = SIZE_MAX;
    }
    distance[root] = 0;
    predecessor[root] = root;

    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size; j++) {
            for (size_t k = 0; k < j; k++) {
                if (distance[k] > distance[j] + graph[j * size + k]) {
                    distance[k] = distance[j] + graph[j * size + k];
                    predecessor[k] = j;
                }
            }
            for (size_t k = j + 1; k < size; k++) {
                if (distance[k] > distance[j] + graph[j * size + k]) {
                    distance[k] = distance[j] + graph[j * size + k];
                    predecessor[k] = j;
                }
            }
        }
    }
    delete[] distance;

    return predecessor;
}