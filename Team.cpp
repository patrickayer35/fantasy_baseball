//
//  Team.cpp
//  c++_files
//
//  Created by Patrick Ayer on 1/26/18.
//  Copyright © 2018 Patrick Ayer. All rights reserved.
//

#include "inningsConversions.h"
#include "Team.h"
#include <cmath>
#include <iomanip>
#include <iostream>

Team::Team()
{
    teamName = "";
    ownerName = "";
    teamId = 0;
    wins = 0;
    losses = 0;
    ties = 0;
    streak = "";
    standing = "";
    gamesBack = 0;
    pitchersStarted = 0;
    pitchingLimit = 0;
    acquisitions = 0;
    acquisitionsLimit = 0;
    winner = false;
    luigi = false;
    overPitchingLimit = false;
    pitchingQualify = false;
    runs = 0;
    singles = 0;
    doubles = 0;
    triples = 0;
    homeRuns = 0;
    runsBattedIn = 0;
    walksBatters = 0;
    strikeoutsBatters = 0;
    hitByPitches = 0;
    stolenBases = 0;
    caughtStealing = 0;
    cycles = 0;
    outfieldAssists = 0;
    errors = 0;
    battingPoints = 0;
    inningsPitched = 0.0;
    outs = 0;
    hits = 0;
    earnedRuns = 0;
    walksPitchers = 0;
    hitBatters = 0;
    strikeoutsPitchers = 0;
    qualityStarts = 0;
    noHitters = 0;
    perfectGames = 0;
    saves = 0;
    holds = 0;
    pitchingPoints = 0;
    totalBases = 0;
    yoshiEggs = 0;
    templeRatio = 0.0;
    totalPoints = 0;
    rosterCount = 0;
}

Team::~Team()
{
    for (int i = 0; i < rosterCount; i++)
    {
        delete rosters[i];
    }
}

void Team::setTeamName(string n)
{
    teamName = n;
}

void Team::setOwnerName()
{
    switch(teamId)
    {
        case 1: ownerName = "Patrick Ayer";
            break;
        case 2: ownerName = "Craig Wise";
            break;
        case 3: ownerName = "Ryan Daley";
            break;
        case 4: ownerName = "Nic Hay";
            break;
        case 5: ownerName = "Rory Lynch";
            break;
        case 6: ownerName = "Ricardo Martinez";
            break;
        case 7: ownerName = "Eric Wang";
            break;
        case 8: ownerName = "Ben Chance";
            break;
        case 9: ownerName = "Will Smith";
            break;
        case 10: ownerName = "Will Cherry";
            break;
        case 11: ownerName = "Sean Phillips";
            break;
        case 12: ownerName = "Sandy Kishida";
            break;
    }
}

void Team::setTeamId(int i)
{
    teamId = i;
}

void Team::setWins(int w)
{
    wins = w;
}

void Team::setLosses(int l)
{
    losses = l;
}

void Team::setTies(int t)
{
    ties = t;
}

void Team::setStreak(string s)
{
    streak = s;
}

void Team::setStanding(string s)
{
    standing = s;
}

void Team::setGamesBack(double g)
{
    gamesBack = g;
}

void Team::setPitchersStarted(int p)
{
    pitchersStarted = p;
}

void Team::setPitchingLimit(int l)
{
    pitchingLimit = l;
}

void Team::setAcquisitions(int a)
{
    acquisitions = a;
}

void Team::setAcquisitionsLimit(int l)
{
    acquisitionsLimit = l;
}

void Team::setWinner(bool w)
{
    winner = w;
}

void Team::appendRoster(Roster* const r)
{
    rosters.push_back(r);
    rosterCount += 1;
}

void Team::setBattingStats()
{
    for (int i = 0; i < rosterCount; i++)
    {
        int batterCount = rosters[i]->getBatterCount();
        for (int j = 0; j < batterCount; j++)
        {
            Batter* batter = rosters[i]->getBatters()[j];
            
            runs += batter->stats[0];
            singles += batter->stats[1];
            doubles += batter->stats[2];
            triples += batter->stats[3];
            homeRuns += batter->stats[4];
            runsBattedIn += batter->stats[5];
            walksBatters += batter->stats[6];
            strikeoutsBatters += batter->stats[7];
            hitByPitches += batter->stats[8];
            stolenBases += batter->stats[9];
            caughtStealing += batter->stats[10];
            cycles += batter->stats[11];
            outfieldAssists += batter->stats[12];
            errors += batter->stats[13];
            battingPoints += batter->stats[14];
        }
    }
}

void Team::setPitchingStats()
{
    for (int i = 0; i < rosterCount; i++)
    {
        int pitcherCount = rosters[i]->getPitcherCount();
        for (int j = 0; j < pitcherCount; j++)
        {
            Pitcher* pitcher = rosters[i]->getPitchers()[j];
            
            outs += pitcher->stats[0];
            hits += pitcher->stats[1];
            earnedRuns += pitcher->stats[2];
            walksPitchers += pitcher->stats[3];
            hitBatters += pitcher->stats[4];
            strikeoutsPitchers += pitcher->stats[5];
            qualityStarts += pitcher->stats[6];
            noHitters += pitcher->stats[7];
            perfectGames += pitcher->stats[8];
            saves += pitcher->stats[9];
            holds += pitcher->stats[10];
            pitchingPoints += pitcher->stats[11];
        }
    }
}

void Team::setTotalBases()
{
    totalBases = singles + 2*doubles + 3*triples + 4*homeRuns + walksBatters + hitByPitches + stolenBases;
}

void Team::setInningsPitched()
{
    inningsPitched = convertOutsToInnings(outs);
}

void Team::setYoshiEggs()
{
    yoshiEggs = saves + holds;
}

void Team::setTempleRatio()
{
    double val = (double) earnedRuns / (hits + walksPitchers + hitBatters);
    templeRatio = round(val * 1000.0) / 1000.0;
}

void Team::setTotalPoints()
{
    totalPoints = battingPoints + pitchingPoints;
}

void Team::setLuigi()
{
    for (int i = 0; i < rosterCount - 1; i++)
    {
        if (!rosters[i]->isSameRoster(rosters[i + 1]))
        {
            luigi = false;
            return;
        }
    }
    if (acquisitions > 0)
    {
        luigi = false;
    }
    else
    {
        luigi = true;
    }
}

void Team::setOverPitchingLimit()
{
    if (pitchersStarted > pitchingLimit)
    {
        overPitchingLimit = true;
    }
    else
    {
        overPitchingLimit = false;
    }
}

void Team::setPitchingQualification()
{
    if (pitchersStarted >= pitchingLimit)
    {
        pitchingQualify = true;
    }
    else
    {
        pitchingQualify = false;
    }
}

string Team::getTeamName()
{
    return teamName;
}

string Team::getOwnerName()
{
    return ownerName;
}

int Team::getTeamId()
{
    return teamId;
}

int Team::getWins()
{
    return wins;
}

int Team::getLosses()
{
    return losses;
}

int Team::getTies()
{
    return ties;
}

string Team::getStreak()
{
    return streak;
}

int Team::getPitchersStarted()
{
    return pitchersStarted;
}

int Team::getPitchingLimit()
{
    return pitchingLimit;
}

int Team::getAcquisitions()
{
    return acquisitions;
}

int Team::getAcquisitionsLimit()
{
    return acquisitionsLimit;
}

bool Team::isWinner()
{
    return winner;
}

bool Team::isLuigi()
{
    return luigi;
}

bool Team::isOverPitchingLimit()
{
    return overPitchingLimit;
}

bool Team::qualifiesForPitchingAwards()
{
    return pitchingQualify;
}

vector<Roster*> Team::getRosterData()
{
    return rosters;
}

int Team::getRosterCount()
{
    return rosterCount;
}

int Team::getRuns()
{
    return runs;
}

int Team::getSingles()
{
    return singles;
}

int Team::getDoubles()
{
    return doubles;
}

int Team::getTriples()
{
    return triples;
}

int Team::getHomeRuns()
{
    return homeRuns;
}

int Team::getRunsBattedIn()
{
    return runsBattedIn;
}

int Team::getWalksBatters()
{
    return walksBatters;
}

int Team::getStrikeoutsBatters()
{
    return strikeoutsBatters;
}

int Team::getHitByPitches()
{
    return hitByPitches;
}

int Team::getStolenBases()
{
    return stolenBases;
}

int Team::getCaughtStealing()
{
    return caughtStealing;
}

int Team::getCycles()
{
    return cycles;
}

int Team::getOutfieldAssists()
{
    return outfieldAssists;
}

int Team::getErrors()
{
    return errors;
}

int Team::getBattingPoints()
{
    return battingPoints;
}

double Team::getInningsPitched()
{
    return inningsPitched;
}

int Team::getOuts()
{
    return outs;
}

int Team::getHits()
{
    return hits;
}

int Team::getEarnedRuns()
{
    return earnedRuns;
}

int Team::getWalksPitchers()
{
    return walksPitchers;
}

int Team::getHitBatters()
{
    return hitBatters;
}

int Team::getStrikeoutsPitchers()
{
    return strikeoutsPitchers;
}

int Team::getQualityStarts()
{
    return qualityStarts;
}

int Team::getNoHitters()
{
    return noHitters;
}

int Team::getPerfectGames()
{
    return perfectGames;
}

int Team::getSaves()
{
    return saves;
}

int Team::getHolds()
{
    return holds;
}

int Team::getPitchingPoints()
{
    return pitchingPoints;
}

int Team::getTotalBases()
{
    return totalBases;
}

int Team::getYoshiEggs()
{
    return yoshiEggs;
}

double Team::getTempleRatio()
{
    return templeRatio;
}

int Team::getTotalPoints()
{
    return totalPoints;
}

// the pitchingLimitAdjustments() method solves the ESPN loophole with pitchers
// loophole allows teams to start up to 13 pitchers a week, when the limit is set to 7 (one per day)
// this loophole allows teams to rack up points from starting pitchers
// the pitchingLimitAdjustment() method allows for the user to subtract points from teams who went over
void Team::pitchingLimitAdjustments()
{
    
    string deductStr = "\n" + ownerName + ", pitchers deducted:\n";
    cout << ownerName << ", " << teamName << endl;
    for (int i = rosterCount - 1; i >= 0; i--)
    {
        if (rosters[i]->hadPitching())
        {
            cout << rosters[i]->getDate() << endl;
            cout << "Pitchers started / pitching limit: " << pitchersStarted << " / " << pitchingLimit << endl;
            vector<Pitcher*> pitchers = rosters[i]->getPitchers();
            int count = rosters[i]->getPitcherCount();
            cout << left << setw(4) << "#";
            cout << left << setw(20) << "Name";
            cout << left << setw(7) << "Outs";
            cout << left << setw(7) << "QS";
            cout << left << setw(7) << "Saves";
            cout << left << setw(7) << "Holds";
            cout << left << setw(7) << "Points"; cout << "\n";
            cout << "-----------------------------------------------------------------------\n";
            // display list of pitchers
            for (int j = 0; j < count; j++)
            {
                cout << (j + 1) << left << setw(3) << ".";
                cout << left << setw(20) << pitchers[j]->playerName;;
                cout << left << setw(7) << pitchers[j]->stats[0];
                cout << left << setw(7) << pitchers[j]->stats[6];
                cout << left << setw(7) << pitchers[j]->stats[9];
                cout << left << setw(7) << pitchers[j]->stats[10];
                cout << left << setw(7) << pitchers[j]->stats[11] << "\n";
            }
            
            bool stillDeducting = true;
            while (stillDeducting)
            {
                int p = getPitcher(count);      // get pitcher to be deducted
                if (p == -1)
                {
                    stillDeducting = false;
                }
                else
                {
                    deductStr += deductPitcherTotals(pitchers[p - 1], rosters[i]);      // deduct points and return string
                    deductStr += rosters[i]->getDate() + "\n";
                    pitchersStarted -= 1;                                   // adjust pitcherStarted member
                    setOverPitchingLimit();
                    if (!overPitchingLimit)         // if team is no longer over the limit, exit method
                    {
                        cout << deductStr << endl;
                        return;
                    }
                }
            }
            if (!overPitchingLimit)
            {
                cout << deductStr << endl;
                return;
            }
        }
    }
}

int Team::getPitcher(int c)
{
    int p;
    string str1 = "ERROR: input an integer.";
    string str2 = "ERROR: input a valid pitcher.";
    bool verifiedInput = false;
    do
    {
        try
        {
            cout << "Subtract pitcher (-1 to exit): "; cin >> p;
            if (!cin)
            {
                throw str1;
            }
            if (p < 1 || p > c)
            {
                if (p == -1)
                {
                    return p;
                }
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
    
    return p;
}

string Team::deductPitcherTotals(Pitcher* const p, Roster* r)
{
    outs -= p->stats[0];
    hits -= p->stats[1];
    earnedRuns -= p->stats[2];
    walksPitchers -= p->stats[3];
    hitBatters -= p->stats[4];
    strikeoutsPitchers -= p->stats[5];
    qualityStarts -= p->stats[6];
    noHitters -= p->stats[7];
    perfectGames -= p->stats[8];
    saves -= p->stats[9];
    holds -= p->stats[10];
    pitchingPoints -= p->stats[11];
    
    r->editTotalPoints(p->stats[11]);
    
    cout << p->playerName + " points deducted.\n";
    
    return p->playerName + ", " + to_string(p->stats[11]) + " points, ";
}

void Team::printTeamInfo()
{
    cout << "Team info for " << teamId << ":\n";
    cout << "Name: " << teamName << "\n";
    cout << "Owner: " << ownerName << "\n";
    cout << "Wins: " << wins << "\n";
    cout << "Losses: " << losses << "\n";
    cout << "Ties: " << ties << "\n";
    cout << "Standing: " << standing << "\n";
    cout << "Games back: " << gamesBack << "\n";
    for (int i = 0; i < rosterCount; i++)
    {
        rosters[i]->printRoster();
    }
}

void Team::printCalculatatedStats()
{
    cout << "Name: " << teamName << "\n";
    cout << "Owner: " << ownerName << "\n";
    cout << "Total bases: " << totalBases << "\n";
    cout << "Innings pitched: " << inningsPitched << "\n";
    cout << "Yoshi eggs: " << yoshiEggs << "\n";
    cout << "Temple ratio: " << fixed << showpoint << setprecision(2) << templeRatio << "\n";
    cout << "Total points: " << totalPoints << "\n";
    if (luigi)
    {
        cout << "Is a luigi.\n";
    }
    else
    {
        cout << "Is not a luigi.\n";
    }
}































