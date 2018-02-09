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
    int teams[12] = { 4, 10, 5, 3, 6, 2, 8, 1, 11, 7, 12, 9 };
    string days[8]     = { "Apr 2", "Apr 3", "Apr 4", "Apr 5", "Apr 6", "Apr 7", "Apr 8", "Apr 9" };
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
        string matchupStr = "/Matchup" + to_string(teams[i]) + "vs" + to_string(teams[i + 1]);
        string teamName, owner, streak, standing;
        int teamId, wins, losses, ties, gamesBack, ps, pl, acq, acql;
        
        ifstream awayTeamFile("/Users/patrickayer/Desktop/fantasy/baseball/Week" +
                              to_string(week) + matchupStr + "/team_" + to_string(teams[i]) + ".txt");
        //cout << "/Users/patrickayer/Desktop/fantasy/baseball/Week" << to_string(week) << matchupStr << "/team_" << to_string(teams[i]) << ".txt\n";
        
        //awayTeamFile.ignore();
        getline(awayTeamFile, teamName);
        cout << teamName << "\n";
        awayTeamFile >> teamId; awayTeamFile.ignore(); getline(awayTeamFile, owner);
        //awayTeamFile >> owner;
        awayTeamFile >> wins >> losses >> ties >> streak >> standing >> gamesBack >> ps >> pl >> acq >> acql;
        
        matchup->getAwayTeam()->setTeamName(teamName);
        matchup->getAwayTeam()->setTeamId(teamId);
        matchup->getAwayTeam()->setOwnerName(owner);
        matchup->getAwayTeam()->setWins(wins);
        matchup->getAwayTeam()->setLosses(losses);
        matchup->getAwayTeam()->setTies(ties);
        matchup->getAwayTeam()->setStreak(streak);
        matchup->getAwayTeam()->setStanding(standing);
        matchup->getAwayTeam()->setGamesBack(gamesBack);
        matchup->getAwayTeam()->setPitchersStarted(ps);
        matchup->getAwayTeam()->setPitchingLimit(pl);
        matchup->getAwayTeam()->setAcquisitions(acq);
        matchup->getAwayTeam()->setPitchingLimit(acql);
        
        awayTeamFile.close();
        
        ifstream homeTeamFile("/Users/patrickayer/Desktop/fantasy/baseball/Week" +
                              to_string(week) + matchupStr + "/team_" + to_string(teams[i + 1]) + ".txt");
        
        //homeTeamFile.ignore();
        getline(homeTeamFile, teamName);
        homeTeamFile >> teamId; homeTeamFile.ignore(); getline(homeTeamFile, owner);
        homeTeamFile >> wins >> losses >> ties >> streak >> standing >> gamesBack >> ps >> pl >> acq >> acql;
        
        matchup->getHomeTeam()->setTeamName(teamName);
        matchup->getHomeTeam()->setTeamId(teamId);
        matchup->getHomeTeam()->setOwnerName(owner);
        matchup->getHomeTeam()->setWins(wins);
        matchup->getHomeTeam()->setLosses(losses);
        matchup->getHomeTeam()->setTies(ties);
        matchup->getHomeTeam()->setStreak(streak);
        matchup->getHomeTeam()->setStanding(standing);
        matchup->getHomeTeam()->setGamesBack(gamesBack);
        matchup->getHomeTeam()->setPitchersStarted(ps);
        matchup->getHomeTeam()->setPitchingLimit(pl);
        matchup->getHomeTeam()->setAcquisitions(acq);
        matchup->getHomeTeam()->setPitchingLimit(acql);
        
        homeTeamFile.close();
        
        matchup->getAwayTeam()->printTeamInfo();
        matchup->getHomeTeam()->printTeamInfo();
        cout << "------\n";
        s->appendMatchup(matchup);
        
    }
}

void setTeamInfo(Matchup* m, int teamType)
{
    Team* teamPtr;
    if (teamType == 1)
    {
        teamPtr = m->getAwayTeam();
    }
    else
    {
        teamPtr = m->getHomeTeam();
    }
}
























