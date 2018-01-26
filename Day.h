#ifndef Day_h
#define Day_h

#include <string>
#include <vector>

using namespace std;

struct Batter
{
	string playerName;
	string slot;
	string teamName;
	int stats[15];
};

struct Pitcher
{
	string playerName;
	string slot;
	string teamName;
	double innings;
	int stats[12];	// stats[0] will hold innings pitched converted to outs
};

struct BenchPlayer
{
	string playerName;
	string slot;
	string teamName;
};

class Day
{
	
private:
	
	string date;
	vector<Batter*> batters;
	vector<Pitcher*> pitchers;
	vector<BenchPlayer*> bench;
	
public:
	
	Day();
	~Day();
	
	void setDate(string d);
    void appendBatter(Batter* const b);
	void appendPitcher(Pitcher* const p);
	void appendBenchPlayer(BenchPlayer* const p);
	
	string getDate();
	vector<Batter*> getBatters();
	vector<Pitcher*> getPitchers();
	vector<BenchPlayer*> getBench();
	
	bool isSame(Day* const d);
	
};

#endif /* Day_h */









