#inclde "Day.h"
#include <iostream>

Day::Day()
{
	date = "";
	batterCount = 0;
	pitcherCount = 0;
	benchCount = 0;
	rosterCount = 0;
}

Day::~Day()
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

void Day::setDate(string d)
{
	date = d;
}

void Day::appendBatter(Batter* const b)
{
	batters.push_back(b);
	batterCount += 1;
}

void Day::appendPitcher(Pitcher* const p)
{
	pitchers.push_back(p);
	pitcherCount += 1;
}

void Day::appendBenchPlayer(BenchPlayer* const p)
{
	bench.push_back(p);
	benchCount += 1;
}

void Day::setRosterCount()
{
	rosterCount = (batterCount + pitcherCount + benchCount);
}

string Day::getDate()
{
	return date;
}

vector<Batter*> Day::getBatters()
{
	return batters;
}

vector<Pitcher*> Day::getPitchers()
{
	return pitchers;
}

vector<BenchPlayer*> Day::getBench()
{
	return bench;
}

int Day::getBatterCount()
{
	return batterCount;
}

int Day::getPitcherCount()
{
	return pitcherCount;
}

int Day::getBenchCount()
{
	return benchCount;
}

int Day::getRosterCount()
{
	return rosterCount;
}

bool Day::isSameRoster(Day* const d)
{
	if (rosterCount != d->getRosterCount())
	{
		return false;
	}
	if (batterCount != d->getBatterCount())
	{
		return false;
	}
	if (pitcherCount != d->getPitcherCount())
	{
		return false;
	}
	if (benchCount != d->getBenchCount())
	{
		return false;
	}
	for (int i = 0; i < batterCount; i++)
	{
		vector<Batter*> otherBatters = d->getBatters();
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
		vector<Pitcher*> otherPitchers = d->getPitchers();
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
		vector<BenchPlayer*> otherBench = d->getBench();
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















