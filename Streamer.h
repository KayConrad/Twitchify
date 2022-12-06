#pragma once
#include <vector>
#include <string>
#include <set>
#include <iostream>
using namespace std;

class Streamer
{

	int channelID;
	int averageViewers;
	int monthlyStreamTime;
	bool partnered;
	bool mature;
	vector<string> games;
	vector<string> tags;
	string language;

public:

	// Constructor
	Streamer();
	Streamer(int c, int a, int mo, bool p, bool ma, vector<string> g, vector<string> t, string l);

	// Accessors
	int getChannelID();
	int getAverageViewers();
	int getMonthlyStreamTime();
	bool getPartnered();
	bool getMature();
	vector<string> getGames();
	vector<string> getTags();
	string getLanguage();

	// Streamer Comparison
	int getScore(Streamer s2);

	// Print Streamer Info
	void print();

};