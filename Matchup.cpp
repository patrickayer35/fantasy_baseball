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
    matchupDiff = 0;
    winner = true;
}

Matchup::~Matchup() {}

void Matchup::setWinnersAndLosers()
{
    if (awayTeamPtr->getTotalPoints() > homeTeamPtr->getTotalPoints())
    {
        winnerPtr = awayTeamPtr;
        loserPtr = homeTeamPtr;
        matchupDiff = awayTeamPtr->getTotalPoints() - homeTeamPtr->getTotalPoints();
    }
    else if (homeTeamPtr->getTotalPoints() > awayTeamPtr->getTotalPoints())
    {
        winnerPtr = homeTeamPtr;
        loserPtr = awayTeamPtr;
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

bool Matchup::hasAWinner()
{
    return winner;
}
























