//
//  Matchup.cpp
//  c++_files
//
//  Created by Patrick Ayer on 1/29/18.
//  Copyright © 2018 Patrick Ayer. All rights reserved.
//

#include "Matchup.h"
#include <iostream>

Matchup::Matchup()
{
    awayTeamPtr = &awayTeam;
    homeTeamPtr = &homeTeam;
    winnerPtr = nullptr;
    loserPtr = nullptr;
    winner = true;
    largestPointDiff = 0;
    matchupPointDiff = 0;
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
        matchupPointDiff = awayTeamPtr->getTotalPoints() - homeTeamPtr->getTotalPoints();
    }
    else if (homeTeamPtr->getTotalPoints() > awayTeamPtr->getTotalPoints())
    {
        winnerPtr = homeTeamPtr;
        homeTeamPtr->setWinner(true);
        loserPtr = awayTeamPtr;
        awayTeamPtr->setWinner(false);
        matchupPointDiff = homeTeamPtr->getTotalPoints() - awayTeamPtr->getTotalPoints();
    }
    else
    {
        winner = false;
    }
}

void Matchup::setLargestPointDiff()
{
    int diff = 0;
    int days = awayTeamPtr->getRosterCount();
    if (winner)
    {
        int winnerTotal = 0, loserTotal = 0;
        for (int i = 0; i < days; i++)
        {
            winnerTotal += winnerPtr->getRosterData()[i]->getTotalPoints();
            loserTotal  += loserPtr->getRosterData()[i]->getTotalPoints();
            diff = loserTotal - winnerTotal;
            if (diff > largestPointDiff)
            {
                largestPointDiff = diff;
            }
        }
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

int Matchup::getLargestPointDiff()
{
    return largestPointDiff;
}

int Matchup::getMatchupPointDiff()
{
    return matchupPointDiff;
}

void Matchup::displayPointDifferentials()
{
    int days = winnerPtr->getRosterData().size();
    int winnerTotal = 0, loserTotal = 0;
    for (int i = 0; i < days; i++)
    {
        winnerTotal += winnerPtr->getRosterData()[i]->getTotalPoints();
        loserTotal  += loserPtr->getRosterData()[i]->getTotalPoints();
        cout << "\n" << winnerPtr->getTeamName() << ", " << loserPtr->getTeamName() << endl;
        cout << winnerPtr->getRosterData()[i]->getDate();
        cout << ", " << winnerTotal;
        cout << ", " << loserTotal;
        cout << ", " << winnerTotal - loserTotal << endl;
    }
}





















