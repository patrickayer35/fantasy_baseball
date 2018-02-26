//
//  Team.h
//  c++_files
//
//  Created by Patrick Ayer on 1/26/18.
//  Copyright © 2018 Patrick Ayer. All rights reserved.
//

#ifndef Team_h
#define Team_h

#include "Roster.h"

class Team
{
    
private:
    
    string 	teamName;
    string 	ownerName;
    int		teamId;
    int		wins;
    int		losses;
    int		ties;
    string	streak;
    string  standing;
    double  gamesBack;
    int		pitchersStarted;
    int		pitchingLimit;
    int		acquisitions;
    int 	acquisitionsLimit;
    bool	winner;				// true if team won their matchup
    bool	luigi;				// true if team is a Luigi (0 roster changes during matchup)
    bool	overPitchingLimit;	// true if pitchersStarted > pitchingLimit
    bool    pitchingQualify;    // true if pitchersStarted >= pitchingLimit (team will then be eligible for pitching awards)
    
    vector<Roster*> rosters;
    int rosterCount;
    
    int 	runs;
    int		singles;
    int		doubles;
    int		triples;
    int		homeRuns;
    int		runsBattedIn;
    int		walksBatters;
    int		strikeoutsBatters;
    int		hitByPitches;
    int		stolenBases;
    int		caughtStealing;
    int		cycles;
    int		outfieldAssists;
    int		errors;
    int		battingPoints;
    
    double	inningsPitched;
    int		outs;		// innings pitched converted to outs
    int		hits;
    int		earnedRuns;
    int		walksPitchers;
    int		hitBatters;
    int		strikeoutsPitchers;
    int		qualityStarts;
    int		noHitters;
    int		perfectGames;
    int		saves;
    int		holds;
    int		pitchingPoints;
    
    int		totalBases;	// = singles + 2*doubles + 3*triples + 4*homeRuns + walksBatters + hitByPitches + stolenBases
    int		yoshiEggs;	// = saves + holds
    double	templeRatio;	// = earnedRuns / (hits + walksPitchers + hitBatters)
    int		totalPoints;	// = battingPoints + pitchingPoints
    
public:
    
    Team();
    ~Team();
    
    void setTeamName(string n);
    void setOwnerName(string o);
    void setTeamId(int i);
    void setWins(int w);
    void setLosses(int l);
    void setTies(int t);
    void setStreak(string s);
    void setStanding(string s);
    void setGamesBack(double g);
    void setPitchersStarted(int p);
    void setPitchingLimit(int l);
    void setAcquisitions(int a);
    void setAcquisitionsLimit(int l);
    void setWinner(bool w);
    
    void appendRoster(Roster* const r);
    
    void setBattingStats();
    void setPitchingStats();
    
    void setTotalBases();
    void setInningsPitched();
    void setYoshiEggs();
    void setTempleRatio();
    void setTotalPoints();
    void setLuigi();
    void setOverPitchingLimit();
    void setPitchingQualification();
    
    string	getTeamName();
    string 	getOwnerName();
    int		getTeamId();
    int		getWins();
    int		getLosses();
    int		getTies();
    string	getStreak();
    int		getPitchersStarted();
    int		getPitchingLimit();
    int		getAcquisitions();
    int		getAcquisitionsLimit();
    bool	isWinner();
    bool	isLuigi();
    bool	isOverPitchingLimit();
    bool    qualifiesForPitchingAwards();
    
    vector<Roster*> getRosterData();
    int getRosterCount();
    
    int getRuns();
    int getSingles();
    int getDoubles();
    int getTriples();
    int getHomeRuns();
    int getRunsBattedIn();
    int getWalksBatters();
    int getStrikeoutsBatters();
    int getHitByPitches();
    int getStolenBases();
    int getCaughtStealing();
    int getCycles();
    int getOutfieldAssists();
    int getErrors();
    int getBattingPoints();
    
    double	getInningsPitched();
    int 	getOuts();
    int		getHits();
    int		getEarnedRuns();
    int		getWalksPitchers();
    int		getHitBatters();
    int		getStrikeoutsPitchers();
    int		getQualityStarts();
    int		getNoHitters();
    int		getPerfectGames();
    int		getSaves();
    int		getHolds();
    int		getPitchingPoints();
    
    int 	getTotalBases();
    int 	getYoshiEggs();
    double 	getTempleRatio();
    int		getTotalPoints();
    
    void   pitchingLimitAdjustments();
    int    getPitcher(int c);
    string deductPitcherTotals(Pitcher* const p, Roster* r);
    void   printTeamInfo();
    void   printCalculatatedStats();
    
};

#endif /* Team_h */
