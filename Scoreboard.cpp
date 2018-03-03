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
    littleMacComebackAmount = 0;
    womboComboAmount = 0;
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

int Scoreboard::getGimpAmount()
{
    return gimpAmount;
}

int Scoreboard::getLittleMacComebackAmount()
{
    return littleMacComebackAmount;
}

int Scoreboard::getWomboComboAmount()
{
    return womboComboAmount;
}

vector<Team*> Scoreboard::getBowserPowerAwardWinners()
{
    vector<Team*> winners;
    int target = 0, bases;
    for (int i = 0; i < teamCount; i++)
    {
        bases = teams[i]->getTotalBases();
        if (bases > target)
        {
            target = bases;
        }
    }
    for (int i = 0; i < teamCount; i++)
    {
        bases = teams[i]->getTotalBases();
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
    int target = 0, points;
    for (int i = 0; i < teamCount; i++)
    {
        points = teams[i]->getTotalPoints();
        if (points > target)
        {
            target = points;
        }
    }
    for (int i = 0; i < teamCount; i++)
    {
        points = teams[i]->getTotalPoints();
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
    int target = 1000, diff;
    for (int i = 0; i < matchupCount; i++)
    {
        if (matchups[i]->hasAWinner())
        {
            diff = matchups[i]->getMatchupPointDiff();
            if (diff < target)
            {
                target = diff;
            }
        }
    }
    gimpAmount = target;
    for (int i = 0; i < matchupCount; i++)
    {
        if (matchups[i]->hasAWinner())
        {
            diff = matchups[i]->getMatchupPointDiff();
            if (diff == target)
            {
                qualifiers.push_back(matchups[i]->getWinner());
            }
        }
    }
    // if tie breaker, winner is determined by most points
    if (qualifiers.size() > 1)
    {
        return getTieBreaker(qualifiers);
    }
    else
    {
        return qualifiers;
    }
}

vector<Team*> Scoreboard::getHomeRunBatAwardWinners()
{
    vector<Team*> winners;
    int target = 0, hrs;
    for (int i = 0; i < teamCount; i++)
    {
        hrs = teams[i]->getHomeRuns();
        if (hrs > target)
        {
            target = hrs;
        }
    }
    for (int i = 0; i < teamCount; i++)
    {
        hrs = teams[i]->getHomeRuns();
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
    int target = 0, hbs;
    for (int i = 0; i < teamCount; i++)
    {
        hbs = teams[i]->getHitBatters();
        if (hbs > target)
        {
            target = hbs;
        }
    }
    for (int i = 0; i < teamCount; i++)
    {
        hbs = teams[i]->getHitBatters();
        if (hbs == target)
        {
            winners.push_back(teams[i]);
        }
    }
    return winners;
}

vector<Team*> Scoreboard::getLittleMacComebackAwardWinners()
{
    vector<Team*> qualifiers;
    int target = 0, diff;
    for (int i = 0; i < matchupCount; i++)
    {
        if (matchups[i]->hasAWinner())
        {
            diff = matchups[i]->getLargestPointDiff();
            //matchups[i]->displayPointDifferentials();
            if (diff > target)
            {
                target = diff;
            }
        }
    }
    littleMacComebackAmount = target;
    for (int i = 0; i < matchupCount; i++)
    {
        if (matchups[i]->hasAWinner())
        {
            diff = matchups[i]->getLargestPointDiff();
            if (diff == target)
            {
                qualifiers.push_back(matchups[i]->getWinner());
            }
        }
    }
    if (qualifiers.size() > 1)
    {
        return getTieBreaker(qualifiers);
    }
    else
    {
        return qualifiers;
    }
}

vector<Team*> Scoreboard::getPlankingLuigiAwardWinners()
{
    vector<Team*> qualifiers;
    for (int i = 0; i < matchupCount; i++)
    {
        if (matchups[i]->hasAWinner())
        {
            if (matchups[i]->getWinner()->isLuigi())
            {
                //cout << matchups[i]->getWinner()->getOwnerName() << endl;
                qualifiers.push_back(matchups[i]->getWinner());
            }
        }
    }
    if (qualifiers.size() > 1)
    {
        return getTieBreaker(qualifiers);
    }
    else
    {
        return qualifiers;
    }
}

vector<Team*> Scoreboard::getSqueakyHammerAwardWinners()
{
    vector<Team*> qualifiers;
    int target = 1000, points;
    for (int i = 0; i < teamCount; i++)
    {
        points = teams[i]->getTotalPoints();
        if (points < target)
        {
            target = points;
        }
    }
    for (int i = 0; i < teamCount; i++)
    {
        points = teams[i]->getTotalPoints();
        if (points == target)
        {
            qualifiers.push_back(teams[i]);
        }
    }
    if (qualifiers.size() > 1)
    {
        vector<Team*> winners;
        target = 0;
        int ks;
        for (int i = 0; i < qualifiers.size(); i++)
        {
            ks = qualifiers[i]->getStrikeoutsBatters();
            if (ks > target)
            {
                target = ks;
            }
        }
        for (int i = 0; i < qualifiers.size(); i++)
        {
            ks = qualifiers[i]->getStrikeoutsBatters();
            if (ks == target)
            {
                winners.push_back(qualifiers[i]);
            }
        }
        return winners;
    }
    else
    {
        return qualifiers;
    }
}

vector<Team*> Scoreboard::getSuperSonicAwardWinners()
{
    vector<Team*> winners;
    int target = 0, sbs;
    for (int i = 0; i < teamCount; i++)
    {
        sbs = teams[i]->getStolenBases();
        if (sbs > target)
        {
            target = sbs;
        }
    }
    for (int i = 0; i < teamCount; i++)
    {
        sbs = teams[i]->getStolenBases();
        if (sbs == target)
        {
            winners.push_back(teams[i]);
        }
    }
    return winners;
}

vector<Team*> Scoreboard::getTargetSmasherAwardWinners()
{
    vector<Team*> qualifiers;
    vector<Team*> winners;
    int target = 0, ks;
    for (int i = 0; i < teamCount; i++)
    {
        if (teams[i]->qualifiesForPitchingAwards())
        {
            qualifiers.push_back(teams[i]);
            ks = teams[i]->getStrikeoutsPitchers();
            if (ks > target)
            {
                target = ks;
            }
        }
    }
    for (int i = 0; i < qualifiers.size(); i++)
    {
        ks = qualifiers[i]->getStrikeoutsPitchers();
        if (ks == target)
        {
            winners.push_back(teams[i]);
        }
    }
    return winners;
}

vector<Team*> Scoreboard::getTempleBasementSurvivorAwardWinners()
{
    vector<Team*> qualifiers;
    vector<Team*> winners;
    double target = 1000.00, tr;
    for (int i = 0; i < teamCount; i++)
    {
        if (teams[i]->qualifiesForPitchingAwards())
        {
            qualifiers.push_back(teams[i]);
            tr = teams[i]->getTempleRatio();
            //cout << teams[i]->getOwnerName() << ", " << tr << endl;
            if (tr < target)
            {
                target = tr;
            }
        }
    }
    //cout << "Target: " << target << endl;
    for (int i = 0; i < qualifiers.size(); i++)
    {
        tr = qualifiers[i]->getTempleRatio();
        if (tr == target)
        {
            winners.push_back(qualifiers[i]);
        }
    }
    return winners;
}

vector<Team*> Scoreboard::getWomboComboAwardWinners()
{
    vector<Team*> qualifiers;
    int target = 0, diff;
    for (int i = 0; i < matchupCount; i++)
    {
        if (matchups[i]->hasAWinner())
        {
            diff = matchups[i]->getMatchupPointDiff();
            if (diff > target)
            {
                target = diff;
            }
        }
    }
    womboComboAmount = target;
    for (int i = 0; i < matchupCount; i++)
    {
        if (matchups[i]->hasAWinner())
        {
            diff = matchups[i]->getMatchupPointDiff();
            if (diff == target)
            {
                qualifiers.push_back(matchups[i]->getWinner());
            }
        }
    }
    if (qualifiers.size() > 1)
    {
        return getTieBreaker(qualifiers);
    }
    else
    {
        return qualifiers;
    }
}

vector<Team*> Scoreboard::getYoshiEggAwardWinners()
{
    vector<Team*> qualifiers;
    vector<Team*> winners;
    int target = 0, ye;
    for (int i = 0; i < teamCount; i++)
    {
        if (teams[i]->qualifiesForPitchingAwards())
        {
            qualifiers.push_back(teams[i]);
            ye = teams[i]->getYoshiEggs();
            //cout << teams[i]->getOwnerName() << ", " << ye << endl;
            if (ye > target)
            {
                target = ye;
            }
        }
    }
    for (int i = 0; i < qualifiers.size(); i++)
    {
        ye = qualifiers[i]->getYoshiEggs();
        if (ye == target)
        {
            winners.push_back(qualifiers[i]);
        }
    }
    return winners;
}

vector<Team*> Scoreboard::getYoureTooSlowAwardWinners()
{
    vector<Team*> winners;
    int target = 0, ks;
    for (int i = 0; i < teamCount; i++)
    {
        ks = teams[i]->getStrikeoutsBatters();
        if (ks > target)
        {
            target = ks;
        }
    }
    for (int i = 0; i < teamCount; i++)
    {
        ks = teams[i]->getStrikeoutsBatters();
        if (ks == target)
        {
            winners.push_back(teams[i]);
        }
    }
    return winners;
}

vector<Team*> Scoreboard::getTieBreaker(vector<Team*>& qualifiers)
{
    vector<Team*> winners;
    int target = 0, points;
    for (int i = 0; i < qualifiers.size(); i++)
    {
        //cout << qualifiers[i]->getOwnerName() << endl;
        points = qualifiers[i]->getTotalPoints();
        if (points > target)
        {
            target = points;
        }
    }
    for (int i = 0; i < qualifiers.size(); i++)
    {
        points = qualifiers[i]->getTotalPoints();
        if (points == target)
        {
            winners.push_back(qualifiers[i]);
        }
    }
    return winners;
}



















