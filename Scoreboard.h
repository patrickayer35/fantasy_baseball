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
    int gimpAmount;
    int littleMacComebackAmount;
    int womboComboAmount;
    vector<Matchup*> matchups;
    vector<Team*> teams;
    
public:
    
    Scoreboard();
    ~Scoreboard();
    
    void setWeek(int w);
    void appendMatchup(Matchup* const m);
    void setTeams();
    
    int getWeek();
    vector<Matchup*> getMatchups();
    vector<Team*> getTeams();
    int getMatchupCount();
    int getTeamCount();
    int getGimpAmount();
    int getLittleMacComebackAmount();
    int getWomboComboAmount();
    
    vector<Team*> getBowserPowerAwardWinners();         // team with the most total bases, no award if 2 or more teams tie
    
    vector<Team*> getFalconPawnchAwardWinners();        // team with most total points, no award if 2 or more teams tie
    
    vector<Team*> getGimpAwardWinners();                // winning team of matchup with smallest point differential
                                                        // tie goes to team with most total points, if still a tie, no award
    
    vector<Team*> getHomeRunBatAwardWinners();          // team with most home runs, no award if 2 or more teams tie
    
    vector<Team*> getImReallyFeelingItAwardWinners();   // team with most hit batters, no award if 2 or more teams tie
    
    vector<Team*> getLittleMacComebackAwardWinners();   // team with largest comeback, compare point differentials throughout the week
                                                        // winning team with largest defecit overcome wins award
    
    vector<Team*> getPlankingLuigiAwardWinners();       // team with 0 roster moves/changes and still wins, tie breaker goes to team
                                                        // with most points
    
    vector<Team*> getSqueakyHammerAwardWinners();       // team with fewest points scored, tie breaker goes to team with the most batting
                                                        // strikeouts
    
    vector<Team*> getSuperSonicAwardWinners();          // team with most stolen bases, no award if 2 or more teams tie
    
    vector<Team*> getTargetSmasherAwardWinners();       // team with most strikeouts by pitcher, no award if 2 ore more teams tie
    
    vector<Team*> getTempleBasementSurvivorAwardWinners();  // team with best ratio of ERA to baserunners allowed, no award if 2 or more
                                                            // teams tie
    
    vector<Team*> getWomboComboAwardWinners();          // winning team that won by the greatest point differential, tie breaker goes
                                                        // to team with most points
    
    vector<Team*> getYoshiEggAwardWinners();            // team with most saves + holds, no award if 2 or more teams tie
    
    vector<Team*> getYoureTooSlowAwardWinners();        // team with most strikeouts by batter, no award if 2 or more teams tie
    
    vector<Team*> getDaybreakWinners();                 // team with the most pitching strikeouts, most quality starts, and least earned runs
                                                        // no award if 2 or more teams tie (in all three categories), a team can still win if they're tied in one or two of the categories, however
    vector<Team*> getTieBreaker(vector<Team*>& qualifiers);
    
};


#endif /* Scoreboard_h */
