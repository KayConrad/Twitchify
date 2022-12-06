#include <fstream>
#include <sstream>
#include <chrono>
#include "AdjList.h"

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
		cout << "Could not open the file" << endl;
	}



	// Ask User for Preferred Streamer

	cout << "Preferred Streamer (enter 0-99999): ";
	int preferredStreamerID;
	cin >> preferredStreamerID;
	cout << endl;

	// Ask User for Preferred Data Structure

	cout << "Data Structure:" << endl;
	cout << "1. Adjacency Matrix" << endl;
	cout << "2. Adjacency List" << endl;
	cout << "(enter 1 or 2): ";
	int dataStructure;
	cin >> dataStructure;
	cout << endl;



	// Instantiate an Empty Adjacency Matrix Object
	// INSERT CODE HERE
	// AdjMatrix myMatrix;

	// Instantiate an Empty Adjacency List Object
	AdjList myList;

	// Preferred Streamer
	Streamer preferredStreamer;

	

	// Start the Timer
	auto start = chrono::steady_clock::now();


	
	// Start the Implementation

	switch (dataStructure) {

	case 1: // Adjacency Matrix

		// Loop through content and prep Streamer Object
		// Start at i = 1 to ignore the title row
		for (int i = 1; i < content.size(); i++) {

			Streamer myStreamer = newStreamer(content[i]);

			// If myStreamer is the preferred streamer, save it to preferredStreamer
			if (myStreamer.getChannelID() == preferredStreamerID) preferredStreamer = myStreamer;

			// Add Streamer Object to the Matrix w/ a Similarity Score to Existing Streamer Objects in the Matrix
			// INSERT CODE HERE
			// myMatrix.addStreamer(myStreamer);

		}

		// Give streamer recommendations based on a given threshold
		// INSERT CODE HERE
		// myMatrix.recommendStreamers(preferredStreamer);

		break;

	case 2: // Adjacency List

		// Loop through content and prep Streamer Object
		// Start at i = 1 to ignore the title row
		for (int i = 1; i < content.size()+1; i++) { // DELETE

			Streamer myStreamer = newStreamer(content[i]);

			// If myStreamer is the preferred streamer, save it to preferredStreamer
			// Print Preferred Streamer
			if (myStreamer.getChannelID() == preferredStreamerID) { preferredStreamer = myStreamer; }

			// Add Streamer Object to the List w/ a Similarity Score to Existing Streamer Objects in the Matrix
			myList.addStreamer(myStreamer);

			if(i % 1000 == 0) cout << (i/1000) << "%" << endl; // DELETE - Progress Bar

		}

		cout << endl << endl; // DELETE

		// Give streamer recommendations based on a given threshold
		myList.recommendStreamers(preferredStreamer);

		break;

	}

	// Get End Time
	auto end = chrono::steady_clock::now();
	double elapsedTime = double(chrono::duration_cast <chrono::nanoseconds> (end - start).count());
	cout << "Total Runtime (s) = " << elapsedTime / 1e9 << endl;

	system("pause");

	return 0;

}