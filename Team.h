#ifndef Team_h
#define Team_h

#include "Day.h"

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
	int		pitchersStarted;
	int		pitchingLimit;
	int		acquisitions;
	int 	acquisitionsLimit;
	bool	winner;
	bool	luigi;
	bool	overPitchingLimit;
	
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
	int		outs;		// innings pitched converted to outs
	int		yoshiEggs;	// = saves + holds
	double	templeRatio;	// = earnedRuns / (hits + walksPitchers + hitBatters)
	int		totalPoints;	// = battingPoints + pitchingPoints
	
	vector<Day*> dailyRosters;

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
	void setPitchersStarted(int p);
	void setPitchingLimit(int l);
	void setAcquisitions(int a);
	void setAcquisitionsLimit(int l);
	void setWinner(bool w);
	void setLuigi(bool l);
	void setoverPitchingLimit(bool o);
	
	void appendDay(Day* const d);
	
	void setRuns(int r);
	void setSingles(int s);
	void setDoubles(int d);
	void setTriples(int t);
	void setHomeRuns(int hr);
	void setRunsBattedIn(int rbi);
	void setWalksBatters(int w);
	void setStrikeoutsBatters(int k);
	void setHitByPitches(int hbp);
	void setStolenBases(int sb);
	void setCaughtStealing(int cs);
	void setCycles(int c);
	void setOutfieldAssists(int o);
	void setErrors(int e);
	void setBattingPoints(int p);
	
	void setInningsPitched(double ip);
	void setHits(int h);
	void setEarnedRuns(int er);
	void setWalksPitchers(int w);
	void setHitBatters(int hb);
	void setStrikeoutsPitchers(int k);
	void setQualityStarts(int qs);
	void setNoHitters(int nh);
	void setPerfectGames(int pg);
	void setSaves(int s);
	void setHolds(int h);
	void setPitchingPoints(int p);
	
	void setTotalBases();
	void setOuts();
	void setYoshiEggs();
	void setTempleRatio();
	void setTotalPoints();
	
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
	
	vector<Day*> getDayData();
	
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
	int 	getOuts();
	int 	getYoshiEggs();
	double 	getTempleRatio();
	int		getTotalPoints();
	
};

#endif /* Team_h */










