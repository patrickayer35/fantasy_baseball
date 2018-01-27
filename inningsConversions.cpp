//
//  inningsConversions.cpp
//  c++_files
//
//  Created by Patrick Ayer on 1/26/18.
//  Copyright © 2018 Patrick Ayer. All rights reserved.
//

#include "inningsConversions.h"
#include <sstream>
#include <string>

using namespace std;

int convertInningsToOuts(double ips)
{
    ostringstream strs;
    strs << ips; string ipsString = strs.str();
    string delimiter = ".";
    string fullInnings = ipsString.substr(0, ipsString.find(delimiter));
    string outs = ipsString.substr(ipsString.find(delimiter) + 1, 1);
    
    return 3*atoi(fullInnings.c_str()) + atoi(outs.c_str());
}

double convertOutsToInnings(int totalOuts)
{
    int fullInnings = totalOuts / 3;
    int outs = totalOuts % 3;
    string innings = to_string(fullInnings) + "." + to_string(outs);
    
    return atof(innings.c_str());
}
