#include "AdjMatrix.h"

void AdjMatrix::addEdge(Streamer s1, Streamer s2)
{
    matrix[s1.getChannelID()][s2.getChannelID()] = s1.getScore(s2);
    matrix[s2.getChannelID()][s1.getChannelID()] = s2.getScore(s1);
}

void AdjMatrix::recommendStreamers(int id)
{
    // Print Recommended Streamer Info
    Streamer s1 = legend[id];
    cout << "[Preferred Streamer]" << endl << endl;
    s1.print();
    cout << "[Recommended Streamers]" << endl << endl;

    //Copy the weights into a vector that we treat as a Max Heap and pull the top 5 streamers from
    //This is not the same as the AdjList as it retains the empty slots
    vector<pair<int, int>> edges;
    for (int i = 0; i < 100000; i++)
    {
        edges.push_back(make_pair(i, matrix[id][i]));
    }

    // Build a heap in place
    for (int i = edges.size() / 2; i >= 0; i--)
    {
        heapifyDown(i, edges);
    }
    for (int i = 0; i < 5; i++)
    {
        if (i < edges.size())
        {
            Streamer recStreamer = legend[edges[0].first];
            recStreamer.print();
            edges[0] = edges[edges.size() - 1];
            edges.pop_back();
            heapifyDown(0, edges);
        }
    }
}

void AdjMatrix::addStreamer(Streamer s)
{
    legend.emplace(s.getChannelID(), s);
    for (auto iter = legend.begin(); iter != legend.end(); iter++)
    {
        //we don't want any self-pointing edges
        if(s.getChannelID() != iter->first)
        {
            //every time we have a new streamer, we need to go back through and check how they connect with the
            //streamers that we have already taken in as data.
            addEdge(iter->second, s);
        }
    }
}

void AdjMatrix::heapifyDown(int index, vector<pair<int, int>>& edges) {
    int leftInd = 2 * index + 1;
    int rightInd = 2 * index + 2;
    int biggest = index;
    if (leftInd < edges.size()) {
        if (rightInd < edges.size()) {
            if (edges[leftInd].second > edges[rightInd].second) {
                biggest = leftInd;
            }
            else {
                biggest = rightInd;
            }
        }
        else {
            biggest = leftInd;
        }
        if (edges[biggest].second > edges[index].second) {
            pair<int, int> currInd = edges[index];
            edges[index] = edges[biggest];
            edges[biggest] = currInd;
            heapifyDown(biggest, edges);
        }
    }
}