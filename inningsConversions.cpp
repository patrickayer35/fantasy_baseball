//
//  inningsConversions.cpp
//  c++_files
//
//  Created by Patrick Ayer on 1/26/18.
//  Copyright © 2018 Patrick Ayer. All rights reserved.
//

#include "inningsConversions.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int convertInningsToOuts(double ips)
{
    ostringstream strs;
    strs << ips; string ipsString = strs.str();
    string delimiter = ".";
    int delimLoc = ipsString.find(delimiter);
    if (delimLoc == -1)
    {
        return 3*ips;
    }
    else
    {
        string fullInnings = ipsString.substr(0, delimLoc);
        string outs = ipsString.substr(delimLoc + 1, 1);
        return 3*atoi(fullInnings.c_str()) + atoi(outs.c_str());
    }
}

double convertOutsToInnings(int totalOuts)
{
    int fullInnings = totalOuts / 3;
    int outs = totalOuts % 3;
    string innings = to_string(fullInnings) + "." + to_string(outs);
    
    return atof(innings.c_str());
}
