#pragma once

#ifndef GRATH_MATRIXGRAPH_H
#define GRATH_MATRIXGRAPH_H

#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

class CMatrixGraph {
public:
    CMatrixGraph(int n) : matrix_size(n) {
        CreateMatrix(n);
    }

    CMatrixGraph(const CMatrixGraph& graph) : matrix_size(graph.VerticesCount()) {
        CreateMatrix(matrix_size);
        for (int i = 0; i < matrix_size; i++) {
            vector<int> verts_list = graph.GetNextVertices(i);
            for (int j : verts_list) {
                adjacuncy_matrix[i][j] = true;
            }
        }
    }

    ~CMatrixGraph() {
        for (int i = 0; i < matrix_size; i++) {
            delete[] adjacuncy_matrix[i];
        }
    }

    void AddEdge(int from, int to) {
        assert(from >= 0 && from < matrix_size);
        assert(to >= 0 && to < matrix_size);
        adjacuncy_matrix[from][to] = 1;
    }

    int VerticesCount() const {
        return matrix_size;
    }

    vector<int> GetNextVertices(int vertex) const {
        assert(vertex >= 0 && vertex < matrix_size);
        vector<int> next_verts;
        for (int j = 0; j < matrix_size; j++) {
            if (adjacuncy_matrix[vertex][j] < matrix_size) next_verts.push_back(j);
        }
        return next_verts;
    }

    vector<int>GetPrevVertices(int vertex) const {
        assert(vertex >= 0 && vertex < matrix_size);
        vector<int> prev_verts;
        for (int i = 0; i < matrix_size; i++) {
            if (adjacuncy_matrix[i][vertex] < matrix_size) prev_verts.push_back(i);
        }
        return prev_verts;
    }

    // јлгоритм поиска в ширину: находит минимальные
    // рассто€ние от заданной вершины до всех остальных
    int* BFS(const int& vertex) const {
        int* dist = new int(matrix_size);
        for (int i = 0; i < matrix_size; i++) {
            dist[i] = matrix_size;
        }
        dist[vertex] = 0;
        queue<int> qu;
        qu.push(vertex);

        while (!qu.empty()) {
            int v = qu.front();
            qu.pop();
            vector<int> children = GetNextVertices(v);
            for (auto& child : children) {
                if (dist[child] > dist[v] + 1) {
                    dist[child] = dist[v] + 1;
                    qu.push(child);
                }
            }
        }
        return dist;
    }

    // ‘ункци€ дл€ нахождени€ матрицы минимальных рассто€ний
    int** getShortestDistanceMatrix() {
        int** distance_matrix;
        distance_matrix = new int* [matrix_size];
        for (int i = 0; i < matrix_size; i++) {
            distance_matrix[i] = BFS(i);
        }
        return distance_matrix;
    }

    void printMatrix() {
        for (int i = 0; i < matrix_size; i++) {
            for (int j = 0; j < matrix_size; j++) {
                cout << adjacuncy_matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

private:
    int matrix_size;
    int** adjacuncy_matrix{};

    void CreateMatrix(int n) {
        adjacuncy_matrix = new int* [n];
        for (int i = 0; i < n; i++) {
            adjacuncy_matrix[i] = new int[n];
            for (int j = 0; j < n; j++) {
                if (j == i) adjacuncy_matrix[i][j] = 0;
                else adjacuncy_matrix[i][j] = matrix_size;
            }
        }
    }
};

#endif //GRATH_MATRIXGRAPH_H
