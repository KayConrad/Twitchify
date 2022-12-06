#pragma once
#include "Graph.h"
#include <unordered_map>
#include <vector>
using namespace std;

class AdjList :
    public Graph
{
    unordered_map<int, vector<pair<int, int>>> graph;
    unordered_map<int, Streamer> legend;
    void heapifyDown(int index, vector<pair<int, int>>& edges);
public:
    void addEdge(Streamer s1, Streamer s2);
    void recommendStreamers(Streamer s1);
    void addStreamer(Streamer s);
};

