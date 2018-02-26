//
//  Scoreboard.cpp
//  c++_files
//
//  Created by Patrick Ayer on 1/30/18.
//  Copyright © 2018 Patrick Ayer. All rights reserved.
//

#include "Scoreboard.h"
#include <iostream>

Scoreboard::Scoreboard()
{
    week = 0;
    matchupCount = 0;
    teamCount = 0;
}

Scoreboard::~Scoreboard()
{
    for (int i = 0; i < matchupCount; i++)
    {
        delete matchups[i];
    }
}

void Scoreboard::setWeek(int w)
{
    week = w;
}

void Scoreboard::appendMatchup(Matchup* const m)
{
    matchups.push_back(m);
    matchupCount += 1;
}

void Scoreboard::setTeams()
{
    for (int i = 0; i < matchupCount; i++)
    {
        teams.push_back(matchups[i]->getAwayTeam());
        teams.push_back(matchups[i]->getHomeTeam());
        teamCount += 2;
    }
}

int Scoreboard::getWeek()
{
    return week;
}

vector<Matchup*> Scoreboard::getMatchups()
{
    return matchups;
}

vector<Team*> Scoreboard::getTeams()
{
    return teams;
}

int Scoreboard::getMatchupCount()
{
    return matchupCount;
}

int Scoreboard::getTeamCount()
{
    return teamCount;
}

vector<Team*> Scoreboard::getBowserPowerAwardWinners()
{
    vector<Team*> winners;
    int target = 0;
    for (int i = 0; i < teamCount; i++)
    {
        int bases = teams[i]->getTotalBases();
        if (bases > target)
        {
            target = bases;
        }
    }
    for (int i = 0; i < teamCount; i++)
    {
        int bases = teams[i]->getTotalBases();
        if (bases == target)
        {
            winners.push_back(teams[i]);
        }
    }
    return winners;
}

vector<Team*> Scoreboard::getFalconPawnchAwardWinners()
{
    vector<Team*> winners;
    int target = 0;
    for (int i = 0; i < teamCount; i++)
    {
        int points = teams[i]->getTotalPoints();
        if (points > target)
        {
            target = points;
        }
    }
    for (int i = 0; i < teamCount; i++)
    {
        int points = teams[i]->getTotalPoints();
        if (points == target)
        {
            winners.push_back(teams[i]);
        }
    }
    return winners;
}

vector<Team*> Scoreboard::getGimpAwardWinners()
{
    vector<Team*> qualifiers;
    int target = 1000;
    for (int i = 0; i < matchupCount; i++)
    {
        if (matchups[i]->hasAWinner())
        {
            int diff = matchups[i]->getLargestPointDiff();
            if (diff < target)
            {
                target = diff;
            }
        }
    }
    for (int i = 0; i < matchupCount; i++)
    {
        if (matchups[i]->hasAWinner())
        {
            int diff = matchups[i]->getLargestPointDiff();
            if (diff == target)
            {
                qualifiers.push_back(matchups[i]->getWinner());
            }
        }
    }
    // if tie breaker, winner is determined by most points
    if (qualifiers.size() > 1)
    {
        vector<Team*> winners;
        int target = 0;
        for (int i = 0; i < qualifiers.size(); i++)
        {
            int points = qualifiers[i]->getTotalPoints();
            if (points > target)
            {
                target = points;
            }
        }
        for (int i = 0; i < qualifiers.size(); i++)
        {
            int points = qualifiers[i]->getTotalPoints();
            if (points == target)
            {
                winners.push_back(teams[i]);
            }
        }
        return winners;
    }
    else
    {
        return qualifiers;
    }
}

vector<Team*> Scoreboard::getHomeRunBatAwardWinners()
{
    vector<Team*> winners;
    int target = 0;
    for (int i = 0; i < teamCount; i++)
    {
        int hrs = teams[i]->getHomeRuns();
        if (hrs > target)
        {
            target = hrs;
        }
    }
    for (int i = 0; i < teamCount; i++)
    {
        int hrs = teams[i]->getHomeRuns();
        if (hrs == target)
        {
            winners.push_back(teams[i]);
        }
    }
    return winners;
}

vector<Team*> Scoreboard::getImReallyFeelingItAwardWinners()
{
    vector<Team*> winners;
    int target = 0;
    for (int i = 0; i < teamCount; i++)
    {
        int hbs = teams[i]->getHitBatters();
        if (hbs > target)
        {
            target = hbs;
        }
    }
    for (int i = 0; i < teamCount; i++)
    {
        int hbs = teams[i]->getHitBatters();
        if (hbs == target)
        {
            winners.push_back(teams[i]);
        }
    }
    return winners;
}

vector<Team*> Scoreboard::getTargetSmasherWinners()
{
    vector<Team*> winners;
    int target = 0;
    for (int i = 0; i < teamCount; i++)
    {
        int ks = teams[i]->getStrikeoutsPitchers();
        if (ks > target)
        {
            target = ks;
        }
    }
    for (int i = 0; i < teamCount; i++)
    {
        int ks = teams[i]->getStrikeoutsPitchers();
        if (ks == target)
        {
            winners.push_back(teams[i]);
        }
    }
    return winners;
}

vector<Team*> Scoreboard::getLittleMacComebackAwardWinners()
{
    vector<Team*> qualifiers;
    int target = 0;
    for (int i = 0; i < matchupCount; i++)
    {
        if (matchups[i]->hasAWinner())
        {
            int diff = matchups[i]->getLargestPointDiff();
            //cout << matchups[i]->getWinner()->getTeamName() << ", " << matchups[i]->getLoser()->getTeamName() << ", " << diff << endl;
            if (diff > target)
            {
                target = diff;
            }
        }
    }
    for (int i = 0; i < matchupCount; i++)
    {
        if (matchups[i]->hasAWinner())
        {
            int diff = matchups[i]->getLargestPointDiff();
            if (diff == target)
            {
                qualifiers.push_back(matchups[i]->getWinner());
            }
        }
    }
    /*
    for (int i = 0; i < qualifiers.size(); i++)
    {
        cout << qualifiers[i]->getTeamName() << endl;
    }
     */
    if (qualifiers.size() > 1)
    {
        vector<Team*> winners;
        int target = 0;
        for (int i = 0; i < qualifiers.size(); i++)
        {
            int points = qualifiers[i]->getTotalPoints();
            if (points > target)
            {
                target = points;
            }
        }
        for (int i = 0; i < qualifiers.size(); i++)
        {
            int points = qualifiers[i]->getTotalPoints();
            if (points == target)
            {
                winners.push_back(teams[i]);
            }
        }
        return winners;
    }
    else
    {
        return qualifiers;
    }
}



















