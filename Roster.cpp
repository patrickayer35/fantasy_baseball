#inclde "Roster.h"
#include <iostream>

Roster::Roster()
{
	date = "";
	batterCount = 0;
	pitcherCount = 0;
	benchCount = 0;
	rosterCount = 0;
}

Roster::~Roster()
{
	for (int i = 0; i < batterCount; i++)
	{
		delete batters[i];
	}
	for (int i = 0; i < pitcherCount; i++)
	{
		delete pitchers[i];
	}
	for (int i = 0; i < benchCount; i++)
	{
		delete bench[i];
	}
}

void Roster::setDate(string d)
{
	date = d;
}

void Roster::appendBatter(Batter* const b)
{
	batters.push_back(b);
	batterCount += 1;
}

void Roster::appendPitcher(Pitcher* const p)
{
	pitchers.push_back(p);
	pitcherCount += 1;
}

void Roster::appendBenchPlayer(BenchPlayer* const p)
{
	bench.push_back(p);
	benchCount += 1;
}

void Roster::setRosterCount()
{
	rosterCount = (batterCount + pitcherCount + benchCount);
}

string Roster::getDate()
{
	return date;
}

vector<Batter*> Roster::getBatters()
{
	return batters;
}

vector<Pitcher*> Roster::getPitchers()
{
	return pitchers;
}

vector<BenchPlayer*> Roster::getBench()
{
	return bench;
}

int Roster::getBatterCount()
{
	return batterCount;
}

int Roster::getPitcherCount()
{
	return pitcherCount;
}

int Roster::getBenchCount()
{
	return benchCount;
}

int Roster::getRosterCount()
{
	return rosterCount;
}

bool Roster::isSameRoster(Roster* const r)
{
	if (rosterCount != r->getRosterCount())
	{
		return false;
	}
	if (batterCount != r->getBatterCount())
	{
		return false;
	}
	if (pitcherCount != r->getPitcherCount())
	{
		return false;
	}
	if (benchCount != r->getBenchCount())
	{
		return false;
	}
	for (int i = 0; i < batterCount; i++)
	{
		vector<Batter*> otherBatters = r->getBatters();
		for (int i = 0; i < batterCount; i++)
		{
			if (batters[i]->playerName != otherBatters[i]->playerName)
			{
				return false;
			}
		}
	}
	for (int i = 0; i < pitcherCount; i++)
	{
		vector<Pitcher*> otherPitchers = r->getPitchers();
		for (int i = 0; i < pitcherCount; i++)
		{
			if (pitchers[i]->playerName != otherPitchers[i]->playerName)
			{
				return false;
			}
		}
	}
	for (int i = 0; i < benchCount; i++)
	{
		vector<BenchPlayer*> otherBench = r->getBench();
		for (int i = 0; i < benchCount; i++)
		{
			if (bench[i]->playerName != otherBench[i]->playerName)
			{
				return false;
			}
		}
	}
	return true;
}















