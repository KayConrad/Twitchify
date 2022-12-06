#include <fstream>
#include <sstream>
#include "Streamer.h"

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



	// Ask User for Data Structure Preference

	cout << "Data Structure:" << endl;
	cout << "1. Adjacency Matrix" << endl;
	cout << "2. Adjacency List" << endl;
	cout << "(enter 1 or 2): ";
	int dataStructure;
	cin >> dataStructure;
	cout << endl;



	switch (dataStructure) {

	case 1: // Adjacency Matrix

		// Instantiate an Adjacency Matrix Object
		// INSERT CODE HERE

		// Loop through content and prep Streamer Object
		// Start at i = 1 to ignore the title row
		for (int i = 1; i < content.size(); i++) {

			Streamer myStreamer = newStreamer(content[i]);
			myStreamer.print(); // DELETE

			// Add Streamer Object to the Matrix w/ a Similarity Score to Existing Streamer Objects in the Matrix
			// INSERT CODE HERE

		}

		// Ask for which streamer they like and spit out the streamers recommended based on a given threshold
		// INSERT CODE HERE

		break;

	case 2: // Adjacency List

		// Instantiate an Adjacency List Object
		// INSERT CODE HERE

		// Loop through content and prep Streamer Object
		// Start at i = 1 to ignore the title row
		for (int i = 1; i < content.size(); i++) {

			Streamer myStreamer = newStreamer(content[i]);
			myStreamer.print(); // DELETE

			// Add Streamer Object to the List w/ a Similarity Score to Existing Streamer Objects in the Matrix
			// INSERT CODE HERE

		}

		// Ask for which streamer they like and spit out the streamers recommended based on a given threshold
		// INSERT CODE HERE

		break;

	}

	return 0;

}