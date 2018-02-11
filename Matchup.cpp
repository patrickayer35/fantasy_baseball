//
//  Matchup.cpp
//  c++_files
//
//  Created by Patrick Ayer on 1/29/18.
//  Copyright © 2018 Patrick Ayer. All rights reserved.
//

#include "Matchup.h"

Matchup::Matchup()
{
    awayTeamPtr = &awayTeam;
    homeTeamPtr = &homeTeam;
    winnerPtr = nullptr;
    loserPtr = nullptr;
    winner = true;
    matchupDiff = 0;
    matchupStr = "";
}

Matchup::~Matchup() {}

void Matchup::setMatchupString(string s)
{
    matchupStr = s;
}

void Matchup::setWinnersAndLosers()
{
    if (awayTeamPtr->getTotalPoints() > homeTeamPtr->getTotalPoints())
    {
        winnerPtr = awayTeamPtr;
        awayTeamPtr->setWinner(true);
        loserPtr = homeTeamPtr;
        homeTeamPtr->setWinner(false);
        matchupDiff = awayTeamPtr->getTotalPoints() - homeTeamPtr->getTotalPoints();
    }
    else if (homeTeamPtr->getTotalPoints() > awayTeamPtr->getTotalPoints())
    {
        winnerPtr = homeTeamPtr;
        homeTeamPtr->setWinner(true);
        loserPtr = awayTeamPtr;
        awayTeamPtr->setWinner(false);
        matchupDiff = homeTeamPtr->getTotalPoints() - awayTeamPtr->getTotalPoints();
    }
    else
    {
        winner = false;
    }
}

Team* Matchup::getAwayTeam()
{
    return awayTeamPtr;
}

Team* Matchup::getHomeTeam()
{
    return homeTeamPtr;
}

Team* Matchup::getWinner()
{
    return winnerPtr;
}

Team* Matchup::getLoser()
{
    return loserPtr;
}

string Matchup::getMatchupString()
{
    return matchupStr;
}

bool Matchup::hasAWinner()
{
    return winner;
}
























