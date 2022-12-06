#include "Streamer.h"

// Constructors

Streamer::Streamer() {

	channelID = -1;
	averageViewers = -1;
	monthlyStreamTime = -1;
	partnered = false;
	mature = false;
	games = {};
	tags = {};
	language = "";

}

Streamer::Streamer(int c, int a, int mo, bool p, bool ma, vector<string> g, vector<string> t, string l) : channelID(c), averageViewers(a), monthlyStreamTime(mo), partnered(p), mature(ma), games(g), tags(t), language(l) {}

// Accessors

int Streamer::getChannelID() { return channelID; }
int Streamer::getAverageViewers() { return averageViewers; }
int Streamer::getMonthlyStreamTime() { return monthlyStreamTime; }
bool Streamer::getPartnered() { return partnered; }
bool Streamer::getMature() { return mature; }
vector<string> Streamer::getGames() { return games; }
vector<string> Streamer::getTags() { return tags; }
string Streamer::getLanguage() { return language; }

// Streamer Comparison

int Streamer::getScore(Streamer s2) {

	int score = 0;
	int startSize, endSize; // For Repeated Use
	
	// Get Score from Same Games
	int gameWeight = 10; // Each Similar Game Adds 10 Points
	set<string> sameGames;
	for (int i = 0; i < (this->games).size(); i++) {
		sameGames.insert((this->games)[i]);
	}
	startSize = sameGames.size();
	for (int i = 0; i < (s2.getGames()).size(); i++) {
		sameGames.insert((s2.getGames())[i]);
	}
	endSize = sameGames.size();
	score += ((endSize - startSize)*gameWeight);

	// Get Score from Same Tags
	int tagWeight = 5; // Each Similar Tag Adds 5 Points
	set<string> sameTags;
	for (int i = 0; i < (this->tags).size(); i++) {
		sameTags.insert((this->tags)[i]);
	}
	startSize = sameTags.size();
	for (int i = 0; i < (s2.getTags()).size(); i++) {
		sameTags.insert((s2.getTags())[i]);
	}
	endSize = sameTags.size();
	score += ((endSize - startSize) * tagWeight);

	// If Preferred Streamer is Immature, Recommend Only Immature
	if (!(this->mature) && s2.getMature()) score = 0;

	// If Language Does Not Match, Score is 0
	if ((this->language).compare(s2.getLanguage()) != 0) score = 0;

	return score;

}

// Print Streamer Info

void Streamer::print() {

	string pPrint, mPrint;
	cout << "Channel ID: " << this->channelID << endl;
	cout << "Average Viewers: " << this->averageViewers << endl;
	cout << "Monthly Stream Time (hours): " << this->monthlyStreamTime << endl;
	pPrint = (this->partnered) ? "TRUE" : "FALSE";
	cout << "Partnered: " << pPrint << endl;
	mPrint = (this->mature) ? "TRUE" : "FALSE";
	cout << "Mature: " << mPrint << endl;
	cout << "Games: ";
	for (int i = 0; i < (this->games).size(); i++) {
		cout << (this->games)[i];
		if (i < (this->games).size() - 1) cout << ", ";
	}
	cout << endl;
	cout << "Tags: ";
	for (int i = 0; i < (this->tags).size(); i++) {
		cout << (this->tags)[i];
		if (i < (this->tags).size() - 1) cout << ", ";
	}
	cout << endl;
	cout << "Language: " << this->language << endl << endl;

}