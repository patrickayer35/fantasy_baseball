//
//  Roster.h
//  c++_files
//
//  Created by Patrick Ayer on 1/26/18.
//  Copyright © 2018 Patrick Ayer. All rights reserved.
//

#ifndef Roster_h
#define Roster_h

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

class Roster
{
    
private:
    
    string date;
    vector<Batter*> batters;
    vector<Pitcher*> pitchers;
    vector<BenchPlayer*> bench;
    int batterCount;
    int pitcherCount;
    int benchCount;
    int rosterCount;
    
public:
    
    Roster();
    ~Roster();
    
    void setDate(string d);
    void appendBatter(Batter* const b);
    void appendPitcher(Pitcher* const p);
    void appendBenchPlayer(BenchPlayer* const p);
    void setRosterCount();
    
    string getDate();
    vector<Batter*> getBatters();
    vector<Pitcher*> getPitchers();
    vector<BenchPlayer*> getBench();
    int getBatterCount();
    int getPitcherCount();
    int getBenchCount();
    int getRosterCount();
    
    bool isSameRoster(Roster* const d);
    bool hadPitching();
    void printRoster();
    
};

#endif /* Roster_h */
