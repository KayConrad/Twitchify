#include <fstream>
#include <sstream>
#include <chrono>
#include "AdjList.h"
#include "AdjMatrix.h"

Streamer newStreamer(vector<string> info) {

	// Prep Variables for Streamer Object
	int c = stoi(info[0]);
	int a = stoi(info[1]);
	int mo = stoi(info[2]);
	bool p = ((info[3]).compare("TRUE") == 0) ? true : false;
	bool ma = ((info[4]).compare("TRUE") == 0) ? true : false;
	string gamesRaw = info[5];
	string tagsRaw = info[6];
	string l = info[7];
	vector<string> g;
	vector<string> t;

	// Translate gamesRaw to g

	string tokenG;
	stringstream strG(gamesRaw);
	while (getline(strG, tokenG, '.')) {
		g.push_back(tokenG);
	}

	// Translate tagsRaw to t

	string tokenT;
	stringstream strT(tagsRaw);
	while (getline(strT, tokenT, '.')) {
		t.push_back(tokenT);
	}

	// Instantiate New Streamer Object
	Streamer currentStreamer(c, a, mo, p, ma, g, t, l);

	return currentStreamer;

}

int main() {

	// Read the CSV and Store Content in a vector of vector of strings

	string fileName = "RandomStreamerData.csv";

	vector<vector<string>> content;
	vector<string> row;
	string line, word;

	fstream file(fileName, ios::in);
	if (file.is_open()) {
		while (getline(file, line)) {
			row.clear();
			stringstream str(line);
			while (getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else {
		std::cout << "Could not open the file" << endl;
	}



	// Ask User for Preferred Data Structure

	std::cout << "Data Structure:" << endl;
	std::cout << "1. Adjacency Matrix" << endl;
	std::cout << "2. Adjacency List" << endl;
	std::cout << "(enter 1 or 2): ";
	int dataStructure;
	cin >> dataStructure;
	std::cout << endl;



	// Instantiate an Empty Adjacency Matrix Object
	AdjMatrix myMatrix;

	// Instantiate an Empty Adjacency List Object
	AdjList myList;

	

	// Start the Timer for the Data Structure
	auto startA = chrono::steady_clock::now();
	auto endAM = startA;
	double elapsedTimeAM = 0;



	// Preferred Streamer ID
	int preferredStreamerID;


	
	// Start the Implementation

	switch (dataStructure) {

	case 1: // Adjacency Matrix

		// Loop through content and prep Streamer Object
		// Start at i = 1 to ignore the title row
		for (int i = 1; i < 1001; i++) {

			Streamer myStreamer = newStreamer(content[i]);

			// Add Streamer Object to the Matrix w/ a Similarity Score to Existing Streamer Objects in the Matrix
			myMatrix.addStreamer(myStreamer);

			if (i % 10 == 0) std::cout << (i / 10) << "%" << endl;

		}

		std::cout << endl;

		// Data Structure Time End
		endAM = chrono::steady_clock::now();
		elapsedTimeAM = double(chrono::duration_cast <chrono::nanoseconds> (endAM - startA).count());
		std::cout << "Adjacency List Import Runtime (s) = " << elapsedTimeAM / 1e9 << endl << endl << endl << endl;

		do {

			// Ask User for Preferred Streamer

			std::cout << "Preferred Streamer (enter 0-99999): ";
			cin >> preferredStreamerID;
			std::cout << endl;

			if (preferredStreamerID == -1) break;

			// Give streamer recommendations based on a given threshold w/ Timer

			auto startAM = chrono::steady_clock::now();

			myMatrix.recommendStreamers(preferredStreamerID);

			endAM = chrono::steady_clock::now();
			elapsedTimeAM = double(chrono::duration_cast <chrono::nanoseconds> (endAM - startAM).count());
			std::cout << "Search Runtime (s) = " << elapsedTimeAM / 1e9 << endl << endl << endl << endl;

		} while (preferredStreamerID != -1);

		break;

	case 2: // Adjacency List

		// Loop through content and prep Streamer Object
		// Start at i = 1 to ignore the title row
		for (int i = 1; i < 1001; i++) {

			Streamer myStreamer = newStreamer(content[i]);

			// Add Streamer Object to the List w/ a Similarity Score to Existing Streamer Objects in the Matrix
			myList.addStreamer(myStreamer);

			if (i % 10 == 0) std::cout << (i / 10) << "%" << endl;

		}

		std::cout << endl;

		// Data Structure Time End
		auto endAL = chrono::steady_clock::now();
		double elapsedTimeAL = double(chrono::duration_cast <chrono::nanoseconds> (endAL - startA).count());
		std::cout << "Adjacency List Import Runtime (s) = " << elapsedTimeAL / 1e9 << endl << endl << endl << endl;

		do {

			// Ask User for Preferred Streamer

			std::cout << "Preferred Streamer (enter 0-99999): ";
			cin >> preferredStreamerID;
			std::cout << endl;

			if (preferredStreamerID == -1) break;

			// Give streamer recommendations based on a given threshold w/ Timer

			auto startAL = chrono::steady_clock::now();
			
			myList.recommendStreamers(preferredStreamerID);

			endAL = chrono::steady_clock::now();
			elapsedTimeAL = double(chrono::duration_cast <chrono::nanoseconds> (endAL - startAL).count());
			std::cout << "Search Runtime (s) = " << elapsedTimeAL / 1e9 << endl << endl << endl << endl;

		} while (preferredStreamerID != -1);

		break;

	}

	std::system("pause");

	return 0;

}