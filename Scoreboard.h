//
//  Scoreboard.h
//  c++_files
//
//  Created by Patrick Ayer on 1/30/18.
//  Copyright © 2018 Patrick Ayer. All rights reserved.
//

#ifndef Scoreboard_h
#define Scoreboard_h

#include "Matchup.h"

class Scoreboard
{
    
private:
    
    int week;
    int matchupCount;
    int teamCount;
    vector<Matchup*> matchups;
    vector<Team*> teams;
    
public:
    
    Scoreboard();
    ~Scoreboard();
    
    void setWeek(int w);
    void appendMatchup(Matchup* const m);
    void appendTeam(Team* const t);
    
    int getWeek();
    vector<Matchup*> getMatchups();
    vector<Team*> getTeams();
    int getMatchupCount();
    int getTeamCount();
    
};


#endif /* Scoreboard_h */
