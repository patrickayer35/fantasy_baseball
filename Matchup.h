//
//  Matchup.h
//  c++_files
//
//  Created by Patrick Ayer on 1/28/18.
//  Copyright © 2018 Patrick Ayer. All rights reserved.
//

#ifndef Matchup_h
#define Matchup_h
#include "Team.h"

class Matchup
{
    
private:
    
    Team awayTeam;      Team* awayTeamPtr;
    Team homeTeam;      Team* homeTeamPtr;
    Team winningTeam;   Team* winnerPtr;
    Team losingTeam;    Team* loserPtr;
    bool    winner;
    int     matchupDiff;
    string  matchupStr;
    
public:
    
    Matchup();
    ~Matchup();
    
    void setWinnersAndLosers();
    void setMatchupString(string s);
    
    Team* getAwayTeam();
    Team* getHomeTeam();
    Team* getWinner();
    Team* getLoser();
    string getMatchupString();
    bool hasAWinner();
    
};


#endif /* Matchup_h */
