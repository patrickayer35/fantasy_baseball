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
void setTeamInfo(Matchup* m, bool away, string teamId, int week);

int main()
{
    int week = getWeek();
    Scoreboard scoreboard; Scoreboard* scoreboardPtr = &scoreboard;
    scoreboardPtr->setWeek(week);
    fillScoreboard(scoreboardPtr, week);
    cout << "70.2: " << convertInningsToOuts(70.2) << endl;
    cout << "341: " << convertOutsToInnings(341) << endl;
    
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
                throw 0;
            verifiedInput = true;
        }
        catch (string message)
        {
            cout << message << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
        catch (int)
        {
            cout << "ERROR: input a valid week.\n";
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
        
        setTeamInfo(matchup, true, teams[i], week);
        setTeamInfo(matchup, false, teams[i + 1], week);
        
        matchup->getAwayTeam()->printTeamInfo();
        matchup->getHomeTeam()->printTeamInfo();
        cout << "------\n";
        s->appendMatchup(matchup);
        
    }
    return;
}

void setTeamInfo(Matchup* m, bool away, string teamId, int week)
{
    Team* teamPtr;
    if (away)
    {
        teamPtr = m->getAwayTeam();
    }
    else
    {
        teamPtr = m->getHomeTeam();
    }
    
    ifstream teamFile("/Users/patrickayer/Desktop/fantasy/baseball/Week" +
                      to_string(week) + m->getMatchupString() + "/team_" + teamId + ".txt");
    
    string strData;
    int    intData;
    
    getline(teamFile, strData); teamPtr->setTeamName(strData);
    teamFile >> intData;        teamPtr->setTeamId(intData);
    teamFile.ignore();
    getline(teamFile, strData); teamPtr->setOwnerName(strData);
    teamFile >> intData;        teamPtr->setWins(intData);
    teamFile >> intData;        teamPtr->setLosses(intData);
    teamFile >> intData;        teamPtr->setTies(intData);
    teamFile >> strData;        teamPtr->setStreak(strData);
    teamFile >> strData;        teamPtr->setStanding(strData);
    teamFile >> intData;        teamPtr->setGamesBack(intData);
    teamFile >> intData;        teamPtr->setPitchersStarted(intData);
    teamFile >> intData;        teamPtr->setPitchingLimit(intData);
    teamFile >> intData;        teamPtr->setAcquisitions(intData);
    teamFile >> intData;        teamPtr->setPitchingLimit(intData);
    
    teamFile.close();
    
    return;
}
























