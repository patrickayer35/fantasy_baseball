//
//  main.cpp
//  c++_files
//
//  Created by Patrick Ayer on 1/26/18.
//  Copyright © 2018 Patrick Ayer. All rights reserved.
//

#include "inningsConversions.h"
#include "Scoreboard.h"
#include <fstream>
#include <iostream>

using namespace std;

int  getWeek();
void fillScoreboard(Scoreboard* s, int week);
void setTeamInfo(Team* teamPtr, int week, string matchupStr, string teamId, string days[], int numOfDays);
void setBatters(Roster* rosterPtr, string fileLoc);
void setPitchers(Roster* rosterPtr, string fileLoc);
void setBench(Roster* rosterPtr, string fileLoc);
void writeAwardToFile(Team* t, int week, string award);
void displayAwards(Scoreboard* s);
int  returnInteger(string data);

void bowserPower(Scoreboard* s);
void falconPawnch(Scoreboard* s);
void gimp(Scoreboard*s);
void homeRunBat(Scoreboard* s);
void littleMacComeback(Scoreboard* s);
void plankingLuigi(Scoreboard* s);
void squeakyHammer(Scoreboard* s);
void superSonic(Scoreboard* s);
void targetSmasher(Scoreboard* s);
void templeBasementSurvivor(Scoreboard* s);
void womboCombo(Scoreboard* s);
void yoshiEgg(Scoreboard* s);
void youreTooSlow(Scoreboard* s);
void daybreak(Scoreboard* s);
void dragoon(Scoreboard* s);

int main()
{
    int week = getWeek();
    Scoreboard scoreboard; Scoreboard* scoreboardPtr = &scoreboard;
    scoreboardPtr->setWeek(week);
    fillScoreboard(scoreboardPtr, week);
    displayAwards(scoreboardPtr);
    
    return 0;
}

int getWeek()
{
    int week;
    string str1 = "ERROR: input an integer.";
    string str2 = "ERROR: input a valid week.";
    bool verifiedInput = false;
    do
    {
        try
        {
            cout << "Week: "; cin >> week;
            if (!cin)
            {
                throw str1;
            }
            if (week < 1 || week > 19)
            {
                throw str2;
            }
            verifiedInput = true;
        }
        catch (string message)
        {
            cout << message << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
    }
    while (!verifiedInput);
    
    return week;
}

void fillScoreboard(Scoreboard* s, int week)
{
    //string matchups[6] = { "Matchup4vs10", "Matchup5vs3", "Matchup6vs2", "Matchup8vs1", "Matchup11vs7", "Matchup12vs9" };
    string teams[12] = { "4", "10", "5", "3", "6", "2", "8", "1", "11", "7", "12", "9" };
    string days[8]   = { "Apr 2", "Apr 3", "Apr 4", "Apr 5", "Apr 6", "Apr 7", "Apr 8", "Apr 9" };
    //string away_id, home_id;
    //ifstream scoreboardFile("/Users/patrickayer/Desktop/fantasy/baseball/Week" +
                            //to_string(week) + "/matchups.txt");
    /*
    while (scoreboardFile >> away_id)
    {
        scoreboardFile >> home_id;
        string matchupStr = "/Matchup" + away_id + "vs" + home_id;
    }
     */
    for (int i = 0; i < 12; i += 2)
    {
        Matchup* matchup = new Matchup;
        matchup->setMatchupString("/Matchup" + teams[i] + "vs" + teams[i + 1]);
        //string matchupStr = "/Matchup" + to_string(teams[i]) + "vs" + to_string(teams[i + 1]);
        
        setTeamInfo(matchup->getAwayTeam(),
                    week,
                    matchup->getMatchupString(),
                    teams[i],
                    days,
                    (sizeof(days) / sizeof(*days)));
        setTeamInfo(matchup->getHomeTeam(),
                    week,
                    matchup->getMatchupString(),
                    teams[i + 1],
                    days,
                    (sizeof(days) / sizeof(*days)));
        
        //matchup->getAwayTeam()->printTeamInfo();
        //matchup->getHomeTeam()->printTeamInfo();
        matchup->setWinnersAndLosers();
        matchup->setLargestPointDiff();
        //cout << matchup->getAwayTeam()->isWinner() << endl;
        //cout << matchup->getHomeTeam()->isWinner() << endl;
        //cout << matchup->getAwayTeam()->getTeamId() << endl;
        //cout << matchup->getAwayTeam()->getPitchingLimit() << endl;
        //cout << matchup->getAwayTeam()->getPitchersStarted() << endl;
        /*
        if (matchup->getAwayTeam()->isOverPitchingLimit())
        {
            matchup->getAwayTeam()->pitchingLimitAdjustments();
        }
         */
        //cout << "------\n";
        //cout << matchup->getHomeTeam()->getTeamId() << endl;
        //cout << matchup->getHomeTeam()->getPitchingLimit() << endl;
        //cout << matchup->getHomeTeam()->getPitchersStarted() << endl;
        /*
        if (matchup->getHomeTeam()->isOverPitchingLimit())
        {
            matchup->getHomeTeam()->pitchingLimitAdjustments();
        }
         */
        //cout << "------\n";
        s->appendMatchup(matchup);
    }
    s->setTeams();
}

//void setTeamInfo(Team* teamPtr, string fileLoc, string days[], int numOfDays)
void setTeamInfo(Team* teamPtr, int week, string matchupStr, string teamId, string days[], int numOfDays)
{
    string fileLoc = "/Users/patrickayer/Desktop/fantasy/baseball/Week" + to_string(week) + matchupStr + "/team_" + teamId + ".txt";
    ifstream teamFile(fileLoc);
    string strData;
    int    intData;
    double fltData;
    
    getline(teamFile, strData); teamPtr->setTeamName(strData);
    teamFile >> intData;        teamPtr->setTeamId(intData);
    teamFile.ignore();
    getline(teamFile, strData); teamPtr->setOwnerName();
    teamFile >> intData;        teamPtr->setWins(intData);
    teamFile >> intData;        teamPtr->setLosses(intData);
    teamFile >> intData;        teamPtr->setTies(intData);
    teamFile >> strData;        teamPtr->setStreak(strData);
    teamFile >> strData;        teamPtr->setStanding(strData);
    teamFile >> fltData;        teamPtr->setGamesBack(fltData);
    teamFile >> intData;        teamPtr->setPitchersStarted(intData);
    teamFile >> intData;        teamPtr->setPitchingLimit(intData);
    teamFile >> intData;        teamPtr->setAcquisitions(intData);
    teamFile >> intData;        teamPtr->setPitchingLimit(intData);
    
    teamFile.close();
    
    for (int i = 0; i < numOfDays; i++)
    {
        Roster* roster = new Roster;
        roster->setDate(days[i]);
        
        string batterLoc = "/Users/patrickayer/Desktop/fantasy/baseball/Week" + to_string(week)
                           + matchupStr + "/" + days[i] + "/team_" + teamId + "_batters.txt";
        setBatters(roster, batterLoc);
        string pitcherLoc = "/Users/patrickayer/Desktop/fantasy/baseball/Week" + to_string(week)
                            + matchupStr + "/" + days[i] + "/team_" + teamId + "_pitchers.txt";
        setPitchers(roster, pitcherLoc);
        string benchLoc = "/Users/patrickayer/Desktop/fantasy/baseball/Week" + to_string(week)
                          + matchupStr + "/" + days[i] + "/team_" + teamId + "_bench.txt";
        setBench(roster, benchLoc);
        
        roster->setRosterCount();
        roster->setTotalPoints();
        teamPtr->appendRoster(roster);
    }
    
    teamPtr->setBattingStats();
    teamPtr->setPitchingStats();
    teamPtr->setOverPitchingLimit();
    teamPtr->setPitchingQualification();
    if (teamPtr->isOverPitchingLimit())
    {
        teamPtr->pitchingLimitAdjustments();
    }
    teamPtr->setTotalBases();
    teamPtr->setInningsPitched();
    teamPtr->setYoshiEggs();
    teamPtr->setTempleRatio();
    teamPtr->setTotalPoints();
    teamPtr->setLuigi();
    
}

void setBatters(Roster* rosterPtr, string fileLoc)
{
    ifstream batterFile(fileLoc);
    string strData;
    
    while (batterFile >> strData)
    {
        Batter* batter = new Batter;
        batter->slot = strData;
        batterFile.ignore();
        getline(batterFile, strData);   batter->playerName = strData;
        batterFile >> strData;          batter->teamName = strData;
        batterFile >> strData;          // temporarily for the batter's health
        for (int i = 0; i < 15; i++)
        {
            batterFile >> strData;      batter->stats[i] = returnInteger(strData);
        }
        rosterPtr->appendBatter(batter);
    }
}

void setPitchers(Roster* rosterPtr, string fileLoc)
{
    ifstream pitcherFile(fileLoc);
    string strData;
    
    while (pitcherFile >> strData)
    {
        Pitcher* pitcher = new Pitcher;
        pitcher->slot = strData;
        pitcherFile.ignore();
        getline(pitcherFile, strData);  pitcher->playerName = strData;
        pitcherFile >> strData;         pitcher->teamName = strData;
        pitcherFile >> strData;         // temporarily for the pitcher's health
        for (int i = 0; i < 12; i++)
        {
            pitcherFile >> strData;
            if (i == 0)
            {
                double inningsPitched = atof(strData.c_str());
                pitcher->stats[i] = convertInningsToOuts(inningsPitched);
            }
            else
            {
                pitcher->stats[i] = returnInteger(strData);
            }
        }
        rosterPtr->appendPitcher(pitcher);
    }
}

void setBench(Roster* rosterPtr, string fileLoc)
{
    ifstream benchFile(fileLoc);
    string strData;
    
    while (benchFile >> strData)
    {
        BenchPlayer* benchPlayer = new BenchPlayer;
        benchPlayer->slot = strData;
        benchFile.ignore();
        getline(benchFile, strData);    benchPlayer->playerName = strData;
        benchFile >> strData;           benchPlayer->teamName = strData;
        benchFile >> strData;           // temporarily for the bench player's health
        rosterPtr->appendBenchPlayer(benchPlayer);
    }
}

void writeAwardToFile(Team* t, int week, string award)
{
    ofstream outFile;
    outFile.open("/Users/patrickayer/Desktop/fantasy/baseball/Week" +
                 to_string(week) + "/awards_team" + to_string(t->getTeamId()) + ".txt", ios::app);
    outFile << award << "\n";
    outFile.close();
}

void displayAwards(Scoreboard* s)
{
    for (int i = 0; i < s->getTeamCount(); i++)
    {
        ofstream outFile;
        outFile.open("/Users/patrickayer/Desktop/fantasy/baseball/Week" +
                     to_string(s->getWeek()) + "/awards_team" + to_string(s->getTeams()[i]->getTeamId()) + ".txt", ios::out);
        outFile.close();
    }
    cout << "Awards for week " << s->getWeek() << endl;
    bowserPower(s);
    falconPawnch(s);
    gimp(s);
    homeRunBat(s);
    littleMacComeback(s);
    plankingLuigi(s);
    squeakyHammer(s);
    superSonic(s);
    targetSmasher(s);
    templeBasementSurvivor(s);
    womboCombo(s);
    yoshiEgg(s);
    youreTooSlow(s);
    
    s->setRunsBattedInLeaders();
    s->setEarnedRunsLeaders();
    s->setQualityStartsLeaders();
    
    daybreak(s);
    dragoon(s);
    
    //s->displayLeaders();
}

int returnInteger(string data)
{
    try
    {
        return stoi(data);
    }
    catch (invalid_argument)
    {
        return 0;
    }
}

void bowserPower(Scoreboard* s)
{
    vector<Team*> winners = s->getBowserPowerAwardWinners();
    if (winners.size() == 0)
    {
        cout << "Bowser Power Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "Bowser Power Award, " << winners[0]->getOwnerName() << " (" << winners[0]->getTotalBases() << " bases).\n";
        string award = "Bowser Power Award (" + to_string(winners[0]->getTotalBases()) + " bases)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "Bowser Power Award, no winners, " << winners.size() << "-way tie.\n";
    }
}

void falconPawnch(Scoreboard* s)
{
    vector<Team*> winners = s->getFalconPawnchAwardWinners();
    if (winners.size() == 0)
    {
        cout << "Falcon PAWNCH Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "Falcon PAWNCH Award, " << winners[0]->getOwnerName() << " (" << winners[0]->getTotalPoints() << " points).\n";
        string award = "Falcon PAWNCH Award (" + to_string(winners[0]->getTotalPoints()) + " points)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "Falcon PAWNCH Award, no winners, " << winners.size() << "-way tie.\n";
    }
}

void gimp(Scoreboard*s)
{
    vector<Team*> winners = s->getGimpAwardWinners();
    if (winners.size() == 0)
    {
        cout << "Gimp Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "Gimp Award, " << winners[0]->getOwnerName() << " (" << s->getGimpAmount() << " points).\n";
        string award = "Gimp Award (" + to_string(s->getGimpAmount()) + " points)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "Gimp Award, no winners.\n";
    }
}

void homeRunBat(Scoreboard* s)
{
    vector<Team*> winners = s->getHomeRunBatAwardWinners();
    if (winners.size() == 0)
    {
        cout << "Home Run Bat Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "Home Run Bat Award, " << winners[0]->getOwnerName() << " (" << winners[0]->getHomeRuns() << " home runs).\n";
        string award = "Home Run Bat Award (" + to_string(winners[0]->getHomeRuns()) + " home runs)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "Home Run Bat Award, no winners, " << winners.size() << "-way tie.\n";
    }
}

void imReallyFeelingIt(Scoreboard* s)
{
    vector<Team*> winners = s->getImReallyFeelingItAwardWinners();
    if (winners.size() == 0)
    {
        cout << "I'm Really Feeling It Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "I'm Really Feeling It Award, " << winners[0]->getOwnerName() << " (" << winners[0]->getHitByPitches() << " hit by pitches).\n";
        string award = "I'm Really Feeling It Award (" + to_string(winners[0]->getHitByPitches()) + " hit by pitches)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
}

void littleMacComeback(Scoreboard* s)
{
    vector<Team*> winners = s->getLittleMacComebackAwardWinners();
    if (winners.size() == 0)
    {
        cout << "Little Mac Comeback Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "Little Mac Comeback Award, " << winners[0]->getOwnerName() << " (overcoming " << s->getLittleMacComebackAmount() << "-point deficit).\n";
        string award = "Little Mac Comeback Award (overcoming " + to_string(s->getLittleMacComebackAmount()) + "-point deficit)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "Little Mac Comeback Award, no winners, " << winners.size() << "-way tie.\n";
    }
}

void plankingLuigi(Scoreboard* s)
{
    vector<Team*> winners = s->getPlankingLuigiAwardWinners();
    if (winners.size() == 0)
    {
        cout << "Planking Luigi Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "Planking Luigi Award, " << winners[0]->getOwnerName() << " (" << winners[0]->getTotalPoints() << " points).\n";
        string award = "Planking Luigi Award (" + to_string(winners[0]->getTotalPoints()) + " points)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "Planking Luigi Award, no winners, " << winners.size() << "-way tie.\n";
    }
}

void squeakyHammer(Scoreboard* s)
{
    vector<Team*> winners = s->getSqueakyHammerAwardWinners();
    if (winners.size() == 0)
    {
        cout << "Squeaky Hammer Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "Squeaky Hammer Award, " << winners[0]->getOwnerName() << " (" << winners[0]->getTotalPoints() << " points).\n";
        string award = "Squeaky Hammer Award (" + to_string(winners[0]->getTotalPoints()) + " points)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "Squeaky Hammer Award, no winners, " << winners.size() << "-way tie.\n";
    }
}

void superSonic(Scoreboard* s)
{
    vector<Team*> winners = s->getSuperSonicAwardWinners();
    if (winners.size() == 0)
    {
        cout << "Super Sonic Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "Super Sonic Award, " << winners[0]->getOwnerName() << " (" << winners[0]->getStolenBases() << " stolen bases).\n";
        string award = "Super Sonic Award (" + to_string(winners[0]->getStolenBases()) + " stolen bases)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "Super Sonic Award, no winners, " << winners.size() << "-way tie.\n";
    }
}

void targetSmasher(Scoreboard* s)
{
    vector<Team*> winners = s->getTargetSmasherAwardWinners();
    if (winners.size() == 0)
    {
        cout << "Target Smasher Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "Target Smasher Award, " << winners[0]->getOwnerName() << " (" << winners[0]->getStrikeoutsPitchers() << " strikeouts).\n";
        string award = "Target Smasher Award (" + to_string(winners[0]->getStrikeoutsPitchers()) + " strikeouts)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "Target Smasher Award, no winners, " << winners.size() << "-way tie.\n";
    }
}

void templeBasementSurvivor(Scoreboard* s)
{
    vector<Team*> winners = s->getTempleBasementSurvivorAwardWinners();
    if (winners.size() == 0)
    {
        cout << "Temple Basement Survivor Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "Temple Basement Survivor Award, " << winners[0]->getOwnerName() << " (" << winners[0]->getTempleRatio() << ", ratio of earned runs allowed to baserunners allowed).\n";
        string award = "Temple Basement Survivor Award (" + to_string(winners[0]->getStrikeoutsPitchers()) + ", ratio of earned runs allowed to baserunners allowed)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "Temple Basement Survivor Award, no winners, " << winners.size() << "-way tie.\n";
    }
}

void womboCombo(Scoreboard* s)
{
    vector<Team*> winners = s->getWomboComboAwardWinners();
    if (winners.size() == 0)
    {
        cout << "Wombo Combo Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "Wombo Combo Award, " << winners[0]->getOwnerName() << " (" << s->getWomboComboAmount() << " points).\n";
        string award = "Wombo Combo Award (" + to_string(s->getWomboComboAmount()) + " points)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "Wombo Combo Award, no winners, " << winners.size() << "-way tie.\n";
    }
}

void yoshiEgg(Scoreboard* s)
{
    vector<Team*> winners = s->getYoshiEggAwardWinners();
    if (winners.size() == 0)
    {
        cout << "Yoshi Egg Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "Yoshi Egg Award, " << winners[0]->getOwnerName() << " (" << winners[0]->getYoshiEggs() << " saves + holds).\n";
        string award = "Yoshi Egg Award (" + to_string(winners[0]->getYoshiEggs()) + " saves + holds)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "Yoshi Egg Award, no winners, " << winners.size() << "-way tie.\n";
    }
}

void youreTooSlow(Scoreboard* s)
{
    vector<Team*> winners = s->getYoureTooSlowAwardWinners();
    if (winners.size() == 0)
    {
        cout << "You're Too Slow Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "You're Too Slow Award, " << winners[0]->getOwnerName() << " (" << winners[0]->getStrikeoutsBatters() << " strikeouts).\n";
        string award = "You're Too Slow Award (" + to_string(winners[0]->getStrikeoutsBatters()) + " strikeouts)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "You're Too Slow Award, no winners, " << winners.size() << "-way tie.\n";
    }
}

void daybreak(Scoreboard* s)
{
    vector<Team*> winners = s->getDaybreakAwardWinners();
    if (winners.size() == 0)
    {
        cout << "Daybreak Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "Daybreak Award, " << winners[0]->getOwnerName()
        << " (" << winners[0]->getEarnedRuns() << " earned runs, "
        << winners[0]->getQualityStarts() << " quality starts, "
        << winners[0]->getStrikeoutsPitchers() << " strikeouts).\n";
        
        string award = "Daybreak Award (" + to_string(winners[0]->getEarnedRuns()) + " earned runs, "
        + to_string(winners[0]->getQualityStarts()) + " quality starts, "
        + to_string(winners[0]->getStrikeoutsPitchers()) + " strikeouts)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "Daybreak Award, no winners, " << winners.size() << "-way tie.\n";
    }
}

void dragoon(Scoreboard* s)
{
    vector<Team*> winners = s->getDragoonAwardWinners();
    if (winners.size() == 0)
    {
        cout << "Dragoon Award, no winners.\n";
        return;
    }
    if (winners.size() == 1)
    {
        cout << "Dragoon Award, " << winners[0]->getOwnerName()
             << " (" << winners[0]->getTotalBases() << " total bases, "
             << winners[0]->getHomeRuns() << " home runs, "
             << winners[0]->getRunsBattedIn() << " runs batted in).\n";
        
        string award = "Dragoon Award (" + to_string(winners[0]->getTotalBases()) + " total bases, "
                     + to_string(winners[0]->getHomeRuns()) + " home runs, "
                     + to_string(winners[0]->getRunsBattedIn()) + " runs batted in)\n";
        writeAwardToFile(winners[0], s->getWeek(), award);
        return;
    }
    if (winners.size() > 1)
    {
        cout << "Dragoon Award, no winners, " << winners.size() << "-way tie.\n";
    }
}


















