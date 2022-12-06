#pragma once
#include "Graph.h"
#include <vector>
using namespace std;

class AdjList :
    public Graph
{
    unordered_map<int, vector<pair<int, int>>> graph;
    void heapifyDown(int index, vector<pair<int, int>>& edges);
public:
    void addEdge(Streamer s1, Streamer s2);
    void recommendStreamers(int id);
    void addStreamer(Streamer s);
};

