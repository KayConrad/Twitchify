//
// Created by Tony Gupta on 12/5/22.
// Abstract Base Class for the Adjacency Matrix and Adjacency List classes
//

#pragma once
#include <unordered_map>
#include "Streamer.h"


class Graph
{
protected:
    unordered_map<int, Streamer> legend;
public:
    virtual void addEdge(Streamer s1, Streamer s2) = 0;
    virtual void recommendStreamers(int id) = 0;
    virtual void addStreamer(Streamer s) = 0;
};
