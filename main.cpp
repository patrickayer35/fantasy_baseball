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

int getWeek();
void fillScoreboard(Scoreboard* s, int week);
//void setTeamInfo(Matchup* m, bool away, string teamId, int week);
//void setTeamInfo(Team* teamPtr, string fileLoc, string days[], int numOfDays);
void setTeamInfo(Team* teamPtr, int week, string matchupStr, string teamId, string days[], int numOfDays);
void setBatters(Roster* rosterPtr, string fileLoc);
void setPitchers(Roster* rosterPtr, string fileLoc);
void setBench(Roster* rosterPtr, string fileLoc);
int returnInteger(string data);

int main()
{
    int week = getWeek();
    Scoreboard scoreboard; Scoreboard* scoreboardPtr = &scoreboard;
    scoreboardPtr->setWeek(week);
    fillScoreboard(scoreboardPtr, week);
    //cout << returnInteger("34.2");
    //cout << "70.2: " << convertInningsToOuts(70.2) << endl;
    //cout << "341: " << convertOutsToInnings(341) << endl;
    //cout << returnInteger("--") << "\n";
    //cout << returnInteger("5") << "\n";
    
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
                throw str1;
            if (week < 1 || week > 19)
                throw str2;
            verifiedInput = true;
        }
        catch (string message)
        {
            cout << message << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
        /*
        catch (int)
        {
            cout << "ERROR: input a valid week.\n";
        }
         */
    }
    while (!verifiedInput);
    
    return week;
}

void fillScoreboard(Scoreboard* s, int week)
{
    //string matchups[6] = { "Matchup4vs10", "Matchup5vs3", "Matchup6vs2", "Matchup8vs1", "Matchup11vs7", "Matchup12vs9" };
    string teams[12] = { "4", "10", "5", "3", "6", "2", "8", "1", "11", "7", "12", "9" };
    string days[8]   = { "/Apr 2", "/Apr 3", "/Apr 4", "/Apr 5", "/Apr 6", "/Apr 7", "/Apr 8", "/Apr 9" };
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
        //cout << matchup->getAwayTeam()->isWinner() << endl;
        //cout << matchup->getHomeTeam()->isWinner() << endl;
        cout << matchup->getAwayTeam()->getTeamId() << endl;
        cout << matchup->getAwayTeam()->getPitchingLimit() << endl;
        cout << matchup->getAwayTeam()->getPitchersStarted() << endl;
        matchup->getAwayTeam()->subtractPitchers();
        cout << "------\n";
        cout << matchup->getHomeTeam()->getTeamId() << endl;
        cout << matchup->getHomeTeam()->getPitchingLimit() << endl;
        cout << matchup->getHomeTeam()->getPitchersStarted() << endl;
        matchup->getHomeTeam()->subtractPitchers();
        cout << "------\n";
        s->appendMatchup(matchup);
    }
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
    getline(teamFile, strData); teamPtr->setOwnerName(strData);
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
                           + matchupStr + days[i] + "/team_" + teamId + "_batters.txt";
        setBatters(roster, batterLoc);
        string pitcherLoc = "/Users/patrickayer/Desktop/fantasy/baseball/Week" + to_string(week)
                            + matchupStr + days[i] + "/team_" + teamId + "_pitchers.txt";
        setPitchers(roster, pitcherLoc);
        string benchLoc = "/Users/patrickayer/Desktop/fantasy/baseball/Week" + to_string(week)
                          + matchupStr + days[i] + "/team_" + teamId + "_bench.txt";
        setBench(roster, benchLoc);
        
        roster->setRosterCount();
        teamPtr->appendRoster(roster);
    }
    
    teamPtr->setBattingStats();
    teamPtr->setPitchingStats();
    teamPtr->setOverPitchingLimit();
    teamPtr->setPitchingQualification();
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




















