//
//  Scoreboard.cpp
//  c++_files
//
//  Created by Patrick Ayer on 1/30/18.
//  Copyright © 2018 Patrick Ayer. All rights reserved.
//

#include "Scoreboard.h"

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

void Scoreboard::appendTeam(Team* const t)
{
    teams.push_back(t);
    teamCount += 1;
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





















