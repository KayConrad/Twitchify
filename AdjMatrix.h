//
// Adjacency Matrix Graph Implementation using 2D Array
//

#pragma once
#include <vector>
include "Graph.h"

class AdjMatrix : public Graph
{
    int[100000][100000] matrix;
    void heapifyDown(int index, vector<pair<int, int>>& edges);
public:
    void addEdge(Streamer s1, Streamer s2);
    void recommendStreamers(int id);
    void addStreamer(Streamer s);
};