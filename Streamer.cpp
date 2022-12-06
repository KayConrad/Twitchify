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

Streamer::Streamer(int c, int a, int mo, bool p, bool ma, vector<string> g, vector<string> t, string l, Streamer* n) : channelID(c), averageViewers(a), monthlyStreamTime(mo), partnered(p), mature(ma), games(g), tags(t), language(l) {}

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

int Streamer::getScore(Streamer secondStreamer) {

	int score = 0;
	int startSize, endSize; // For Repeated Use
	
	// Get Score from Same Games
	int gameWeight = 10; // Each Similar Game Adds 10 Points
	set<string> sameGames;
	for (int i = 0; i < (this->games).size(); i++) {
		sameGames.insert((this->games)[i]);
	}
	startSize = sameGames.size();
	endSize = startSize;
	for (int i = 0; i < (secondStreamer.getGames()).size(); i++) {
		sameGames.insert((secondStreamer.getGames())[i]);
	}
	score += ((endSize - startSize)*gameWeight);

	// Get Score from Same Tags
	int tagWeight = 5; // Each Similar Tag Adds 5 Points
	set<string> sameTags;
	for (int i = 0; i < (this->tags).size(); i++) {
		sameTags.insert((this->tags)[i]);
	}
	startSize = sameTags.size();
	endSize = startSize;
	for (int i = 0; i < (secondStreamer.getTags()).size(); i++) {
		sameTags.insert((secondStreamer.getTags())[i]);
	}
	score += ((endSize - startSize) * tagWeight);

	// If Preferred Streamer is Immature, Recommend Only Immature
	if (!(this->mature) && secondStreamer.getMature()) score = 0;

	// If Language Does Not Match, Score is 0
	if ((this->language).compare(secondStreamer.getLanguage()) != 0) score = 0;

	return score;

}