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
    bool winner;
    int  matchupDiff;
    
public:
    
    Matchup();
    ~Matchup();
    
    void setWinnersAndLosers();
    
    Team* getAwayTeam();
    Team* getHomeTeam();
    Team* getWinner();
    Team* getLoser();
    bool hasAWinner();
    
};


#endif /* Matchup_h */
