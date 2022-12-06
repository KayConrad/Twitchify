#include "AdjList.h"

void AdjList::addEdge(Streamer s1, Streamer s2) {
	// Find the similiarity score of the two streamers (it would be the same either way it's called)
	int score1pref = s1.getScore(s2);
	int score2pref = s2.getScore(s1);

	// Make sure entries exist in the map for both streamers
	if (graph.count(s1.getChannelID()) == 0) {
		vector<pair<int, int>> v;
		graph.insert(pair<int, vector<pair<int, int>>>(s1.getChannelID(), v));
	}
	if (graph.count(s2.getChannelID()) == 0) {
		vector<pair<int, int>> v;
		graph.insert(pair<int, vector<pair<int, int>>>(s2.getChannelID(), v));
	}

	// Append each streamer to the other streamer's list
	if (score1pref != 0) {
		graph[s1.getChannelID()].push_back(pair<int, int>(s2.getChannelID(), score1pref));
		
	}
	if (score2pref != 0) {
		graph[s2.getChannelID()].push_back(pair<int, int>(s1.getChannelID(), score2pref));
	}
}

void AdjList::recommendStreamers(Streamer s1) {
	// Print Recommended Streamer Info
	cout << "[Preferred Streamer]" << endl;
	s1.print();
	cout << endl;
	cout << "[Recommended Streamers]" << endl;

	// Goal: get the 5 most similiar streamers through a heap sort
	vector<pair<int, int>> edges = graph[s1.getChannelID()];

	// Build a heap in place
	for (int i = edges.size() / 2; i >= 0; i--) {
		heapifyDown(i, edges);
	}
	for (int i = 0; i < 5; i++) {
		if (i < edges.size()) {
			Streamer recStreamer = legend[edges[i].first];
			recStreamer.print();
			edges[0] = edges[edges.size() - 1];
			edges.pop_back();
			heapifyDown(0, edges);
		}
	}
}

void AdjList::heapifyDown(int index, vector<pair<int, int>>& edges) {
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

void AdjList::addStreamer(Streamer s) {
	legend.insert(pair<int, Streamer>(s.getChannelID(), s));
	for (auto iter = legend.begin(); iter != legend.end(); iter++) {
		if (s.getChannelID() != iter->first) {
			addEdge(iter->second, s);
		}
	}
}