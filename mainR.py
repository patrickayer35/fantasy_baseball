from bs4 import BeautifulSoup
import csv
import re
import urllib2

def main():
    
    week = get_week()
    
    filename = "Week" + str(week) + "_data.csv"
    with open(filename, "w") as f:
        csv_writer = csv.writer(f)
        csv_writer.writerow(["playerSlot", "playerName", "playerTeam", "runs", "singles", "doubles", "triples", "homeRuns", "runsBattedIn", "walksBatters",\
                             "strikeoutsBatters", "hitByPitches", "stolenBases", "caughtStealing", "cycles", "outfieldAssists", "errors", "battingPoints",\
                             "inningsPitched", "hits", "earnedRuns", "walksPitchers", "hitBatters", "strikeoutsPitchers", "qualityStarts",\
                             "noHitters", "perfectGames", "saves", "holds", "pitchingPoints", "teamName", "teamId", "teamOwner", "pitchingStarts",\
                             "pitchingLimit", "acquisitions", "acquisitionLimit", "teamNameOpp", "teamIdOpp", "teamOwnerOpp", "week", "date"])
    f.close()
    
    boxscore_urls = get_full_boxscore_urls(week)
    
    for b in boxscore_urls:
        
        print(b)
        away_basic, home_basic, days = get_team_data(b)
        away_basic.append(str(week))
        home_basic.append(str(week))
        
        #print(away_data)
        #print(home_data)
        
        for d in days:
            
            #away_basic.append(d["Day"])
            #home_basic.append(d["Day"])
            
            raw_html = urllib2.urlopen(d["Url"]).read()
            roster_soup = BeautifulSoup(raw_html).find_all("div", {"style":"width: 100%; margin-bottom: 40px; clear: both;"})
            
            away_batters, away_pitchers, away_bench = get_full_roster(roster_soup[0])
            home_batters, home_pitchers, home_bench = get_full_roster(roster_soup[1])
            
            away_data = merge_data(away_basic, [d["Day"]], away_batters, away_pitchers, away_bench)
            home_data = merge_data(home_basic, [d["Day"]], home_batters, home_pitchers, home_bench)
            
            write_table(filename, away_data)
            write_table(filename, home_data)
            
        #print(days)
    
    return

def get_week():     # get the matchup's week number
    
    flag = True
    while (flag):
        temp_week = raw_input("Week: ")
        try:
            week = int(temp_week)
        except ValueError:
            print("ERROR: input an integer.")
        else:
            if ((week < 1) or (week > 19)):
                print("ERROR: input a valid week.")
            else:
                flag = False;
    
    return week

def get_full_boxscore_urls(week):       # get the boxscore urls for each matchup
    
    url = "http://games.espn.com/flb/scoreboard?leagueId=75894&matchupPeriodId=" + str(week)
    raw_html = urllib2.urlopen(url).read()
    boxscore_link_divs = BeautifulSoup(raw_html).find_all("div", {"class":"boxscoreLinks"})
    
    boxscore_urls = []
    for b in boxscore_link_divs:
        href = b.find("a").get("href")
        boxscore_urls.append("http://games.espn.com" + href)
    
    return boxscore_urls

def get_team_data(url):
    
    raw_html = urllib2.urlopen(url).read()
    
    team_info_soup = BeautifulSoup(raw_html).find("div", {"id":"teamInfos"})    # this html block contains both team's information
    away_soup = team_info_soup.find("div", {"style":"float:left;"})             # this html block contains only the away team's info
    home_soup = team_info_soup.find("div", {"style":"float:right;"})            # this html block contains only the home team's info
    
    away_data_basics = parse_team_data_basics(away_soup)
    home_data_basics = parse_team_data_basics(home_soup)
    
    away_limits = BeautifulSoup(raw_html).find_all("div", {"style":"float:left;width:440px;margin-top:0px;"})
    home_limits = BeautifulSoup(raw_html).find_all("div", {"style":"float:left;width:440px;margin-left:44px;margin-top:0px;"})
    
    away_pitching_limits = parse_pitching_limits(away_limits[0])
    home_pitching_limits = parse_pitching_limits(home_limits[0])
    
    try:
        away_acq_limits = parse_acquisition_limits(away_limits[1])
        home_acq_limits = parse_acquisition_limits(home_limits[1])
    except IndexError:
        away_acq_limits = [0, "7"]
        home_acq_limits = [0, "7"]
    
    away_team_data = away_data_basics + away_pitching_limits + away_acq_limits + home_data_basics
    home_team_data = home_data_basics + home_pitching_limits + home_acq_limits + away_data_basics
    
    days_soup = BeautifulSoup(raw_html).find("div", {"style":"margin:10px 0px 10px 2px;"})
    days = get_days(days_soup)
    
    return away_team_data, home_team_data, days
    
    return

def get_days(soup):
    
    day_tags = soup("a")
    days = []
    for day in day_tags:
        days.append({"Day":day.get_text().encode("utf-8"), "Url":day.get("href").encode("utf-8")})
    
    return days

def parse_team_data_basics(team_soup):
    
    data = []
    
    # get the team's name
    team_name = team_soup.find("div", {"style":"font-size:18px; margin-bottom:14px; font-family:Helvetica,sans-serif;"}).get_text()
    # get the team's id by first locating the team's clubhouse url and extracting the id from the end
    team_id = re.findall("http:\/\/games\.espn\.com\/flb\/clubhouse\?leagueId=75894&teamId=([\d]{1,})", "http://games.espn.com" + team_soup.find("a").get("href"))
    # get the team owner's name
    owner = team_soup.find("div", {"class":"teamInfoOwnerData"}).get_text()
    
    # team_name, team_id, and owner data items are returned as unicode objects
    # convert each item from unicode to string via the encode("utf-8") method
    data.append(team_name.encode("utf-8"))
    data.append(team_id[0].encode("utf-8"))
    data.append(owner.encode("utf-8"))
    
    return data

def parse_pitching_limits(soup):
    
    text = re.findall("P:\s([\d]{1,}\/[\d]{1,})", soup.get_text())
    limits = text[0].encode("utf-8").split("/")
    
    return limits

def parse_acquisition_limits(soup):
    
    text = re.findall("\(Used\/Max\)\s:\s\s([\d]{1,}\s\/\s[\d]{1,})", soup.get_text())
    limits = text[0].encode("utf-8").split(" / ")
    
    return limits

def get_full_roster(soup):
    
    batters = []
    pitchers = []
    bench = []
    #roster = []
    player_tables = soup.find_all("table", {"class":"playerTableTable tableBody"})
    #roster += get_players(player_tables[0])
    #roster += get_players(player_tables[1])
    batters = get_players(player_tables[0])
    pitchers = get_players(player_tables[1])
    
    hideables = soup.find_all("table", {"class":"playerTableTable tableBody hideableGroup"})
    for h in hideables:
        bench += get_players(h)
    
    return batters, pitchers, bench

def get_players(soup):
    
    p_0 = soup.find_all("tr", {"class":"pncPlayerRow playerTableBgRow0"})
    p_1 = soup.find_all("tr", {"class":"pncPlayerRow playerTableBgRow1"})
    p_2 = soup.find_all("tr", {"class":"pncPlayerRow irRow playerTableBgRow0"})
    p_3 = soup.find_all("tr", {"class":"pncPlayerRow irRow playerTableBgRow1"})
    raw_players = p_0 + p_1 + p_2 + p_3
    
    clean_players = []
    for p in raw_players:
        clean_players.append(get_player_data(p))
    
    return clean_players

def get_player_data(soup):
    
    l = []  # empty list to hold all player's data
    batting_filler = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    pitching_filler = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    l.append(soup.find("td", {"style":"font-weight: bold;"}).get_text().encode("utf-8"))    # append player's fantasy slot
    
    # try catch block for when a roster slot is empty
    try:
        l.append(soup.find("a").get_text().encode("utf-8"))
        text = soup.find("td", {"class":"playertablePlayerName"}).get_text()
        text = text.replace(u'\xa0', u' ')
        print(text)
        l.append(re.findall("^[\w\d\s.\-\*\']+,\s([\w]+)", text)[0].encode("utf-8"))
    except AttributeError:
        l.append("NA")
        l.append("NA")
        l += (batting_filler + pitching_filler)
        return l
    
    if l[1] == "Shohei Ohtani":
        if l[0] == "UTIL" or l[0] == "OF":
            l += get_player_statistics(soup)
            l += pitching_filler
        elif l[0] == "SP" or l[0] == "RP":
            l += batting_filler
            l += get_player_statistics(soup)
        else:
            l += (batting_filler + pitching_filler)
    else:
        pos = re.findall(",.*(\sSP|\sRP)", text)
        if not pos:
            #print(text)
            l += get_player_statistics(soup)
            l += pitching_filler
        else:
            l += batting_filler
            l += get_player_statistics(soup)
    
    #fuckers = text.split("u00A0")
    #print("fuckers: " + fuckers[len(fuckers) - 1])
    
    return l

def get_player_statistics(soup):
    
    l = []
    stats = soup.find_all("td", {"class":"playertableStat "})
    for s in stats:
        l.append(convert_na_data(s.get_text().encode("utf-8")))
    # try catch block for appending a player's totals. If the player was not playing, the total is embedded in a different tag
    try:
        raw_data = soup.find("td", {"class":"playertableStat appliedPoints appliedPointsProGameFinal"}).get_text().encode("utf-8")
        l.append(convert_na_data(raw_data))
    except AttributeError:
        raw_data = soup.find("td", {"class":"playertableStat appliedPoints"}).get_text().encode("utf-8")
        l.append(convert_na_data(raw_data))
    
    return l

def convert_na_data(x):
    
    if (x == "--"):
        return 0
    else:
        return x

def merge_data(basic_info, day, batters, pitchers, bench):
    
    full_table = []
    for b in batters:
        full_table.append(b + basic_info + day)
    for p in pitchers:
        full_table.append(p + basic_info + day)
    for b in bench:
        full_table.append(b + basic_info + day)
    
    return full_table

def write_table(filename, data):
    
    with open(filename, "a") as f:
        csv_writer = csv.writer(f)
        for d in data:
            csv_writer.writerow(d)
    
    f.close()

def TEST_roster_acquisition():
    
    url = "http://games.espn.com/flb/boxscorefull?leagueId=75894&teamId=4&scoringPeriodId=5&seasonId=2018&view=scoringperiod&version=full"
    raw_html = urllib2.urlopen(url).read()
    roster_soup = BeautifulSoup(raw_html).find_all("div", {"style":"width: 100%; margin-bottom: 40px; clear: both;"})
    away_batters, away_pitchers, away_bench = get_full_roster(roster_soup[0])
    
    print("batters")
    for b in away_batters:
        print(b)
    print("\npitchers")
    for p in away_pitchers:
        print(p)
    print("\nbench")
    for b in away_bench:
        print(b)

def TEST_regex():
    
    text1 = "Yoenis Cespedes, NYM OF".encode("utf-8")
    text2 = "Joe Musgrove*, Pit SP, RP DL10".encode("utf-8")
    print(type(re.findall(",.*(SP|RP)", text1)))
    #print(re.findall(",.*(SP|RP)", text1)[0].encode("utf-8"))
    print(re.findall(",.*(SP|RP)", text2)[0].encode("utf-8"))
    
    return
    
main()
#TEST_roster_acquisition()
#TEST_regex()
    
    















