//
// Created by Tony Gupta on 12/5/22.
// Abstract Base Class for the Adjacency Matrix and Adjacency List classes
//

#pragma once
#include "Streamer.h"


class Graph
{
public:
    virtual void addEdge(Streamer s1, Streamer s2) = 0;
    virtual void recommendStreamers(Streamer s1) = 0;
};