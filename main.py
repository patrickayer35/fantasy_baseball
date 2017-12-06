from bs4 import BeautifulSoup
import os
import re
import urllib2

def main():
    
    week = get_week()
    file_loc = "/Users/patrickayer/Desktop/fantasy/baseball/Week" + str(week)
    if not os.path.exists(file_loc):
        os.mkdir(file_loc)
    
    print("Extracting scoreboard matchups from week " + str(week) + "..."),
    boxscore_urls = get_full_boxscore_urls(week)
    print("Done.")
    for b in boxscore_urls:
        print("Processing data from " + b + "..."),
        away_data, home_data = scrape_team_data(b)
        matchup_str = "/Matchup" + away_data[1] + "vs" + home_data[1]
        write_team_data(away_data, file_loc + matchup_str)
        write_team_data(home_data, file_loc + matchup_str)
        print("Done.")

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
        rel_boxscore_url = b.find("a").get("href")
        boxscore_urls.append("http://games.espn.com" + rel_boxscore_url)
    
    return boxscore_urls

def scrape_team_data(url):
    
    raw_html = urllib2.urlopen(url).read()
    
    team_info_soup = BeautifulSoup(raw_html).find("div", {"id":"teamInfos"})    # this html block contains both team's information
    away_soup = team_info_soup.find("div", {"style":"float:left;"})             # this html block contains only the away team's info
    home_soup = team_info_soup.find("div", {"style":"float:right;"})            # this html block contains only the home team's info
    
    away_data_basics = parse_team_data_basics(away_soup)
    home_data_basics = parse_team_data_basics(home_soup)
    
    # find html blocks containing pitching and acquisition limits for both teams
    away_limits = BeautifulSoup(raw_html).find_all("div", {"style":"float:left;width:440px;margin-top:0px;"})
    home_limits = BeautifulSoup(raw_html).find_all("div", {"style":"float:left;width:440px;margin-left:44px;margin-top:0px;"})
    
    away_pitching_limits = parse_pitching_limits(away_limits[0])
    home_pitching_limits = parse_pitching_limits(home_limits[0])
    
    away_acq_limits = parse_acquisition_limits(away_limits[1])
    home_acq_limits = parse_acquisition_limits(home_limits[1])
    
    return away_data_basics + away_pitching_limits + away_acq_limits, home_data_basics + home_pitching_limits + home_acq_limits

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
    
    # get remaining text from team html block to extract record, standing, and streak
    text = team_soup.get_text()
    
    record = parse_record(text)
    for r in record:
        data.append(r)
    data.append(parse_streak(text))
    standing = parse_standing(text)
    for s in standing:
        data.append(s)
    
    return data

def parse_record(text):
    
    record = []
    record_raw = re.findall("Record: ([\d]{1,}-[\d]{1,}-[\d]{1,})", text)   # extract only the last matching expression to safeguard against
    last = len(record_raw) - 1                                              # friends naming their teams something that also matches
    
    wins = re.findall("^[\d]{1,}", record_raw[last])
    losses = re.findall("-([\d]{1,})-", record_raw[last])
    ties = re.findall("-([\d]{1,})$", record_raw[last])
    
    record.append(wins[0].encode("utf-8"))
    record.append(losses[0].encode("utf-8"))
    record.append(ties[0].encode("utf-8"))
    
    return record

def parse_streak(text):
    
    streak = re.findall("Streak: ([W|L|T][\d]{1,})", text)
    last = len(streak) - 1
    
    return streak[last].encode("utf-8")

def parse_standing(text):
    
    standing = re.findall("Standing:\s(.*)\n", text)
    last = len(standing) - 1
    
    place = re.findall("(T-[\d]{1,}st|T-[\d]{1,}th|T-[\d]{1,}nd|T-[\d]{1,}rd)|([\d]{1,}st|[\d]{1,}th|[\d]{1,}nd|[\d]{1,}rd)", standing[last])
    games_back = re.findall("\(([\d.]{1,})\sGB\)", standing[last])
    if len(games_back) == 0:
        games_back.append("0")
    if place[0][0] == "":
        return place[0][1].encode("utf-8"), games_back[0].encode("utf-8")
    else:
        return place[0][0].encode("utf-8"), games_back[0].encode("utf-8")

def parse_pitching_limits(soup):
    
    text = re.findall("P:\s([\d]{1,}\/[\d]{1,})", soup.get_text())
    limits = text[0].encode("utf-8").split("/")
    
    return limits

def parse_acquisition_limits(soup):
    
    text = re.findall("\(Used\/Max\)\s:\s\s([\d]{1,}\s\/\s[\d]{1,})", soup.get_text())
    limits = text[0].encode("utf-8").split(" / ")
    
    return limits

def write_team_data(team_data, file_loc):
    
    # create the file location if it doesn't exist
    if not os.path.exists(file_loc):
        os.mkdir(file_loc)
    # team data will be stored in files that are identified by their team ids
    file_name = os.path.join(file_loc, ("team_" + team_data[1] + ".txt"))
    out_file = open(file_name, "w")
    for d in team_data:
        out_file.write(d + "\n")
    out_file.close()
    
    return

main()











