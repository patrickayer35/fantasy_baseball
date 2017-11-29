from bs4 import BeautifulSoup
import os
import re
import urllib2

def main():
    
    week = get_week()
    boxscore_urls = get_full_boxscore_urls(week)
    for b in boxscore_urls:
        process_main_scoreboard(b)

def get_week():
    
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

def get_full_boxscore_urls(week):
    
    url = "http://games.espn.com/flb/scoreboard?leagueId=75894&matchupPeriodId=" + str(week)
    raw_html = urllib2.urlopen(url).read()
    boxscore_link_divs = BeautifulSoup(raw_html).find_all("div", {"class":"boxscoreLinks"})
    
    boxscore_urls = []
    for b in boxscore_link_divs:
        rel_boxscore_url = b.find("a").get("href")
        boxscore_urls.append("http://games.espn.com" + rel_boxscore_url)
    
    return boxscore_urls

def process_main_scoreboard(url):
    
    raw_html = urllib2.urlopen(url).read()
    
    team_info_div = BeautifulSoup(raw_html).find("div", {"id":"teamInfos"})
    away_block = team_info_div.find("div", {"style":"float:left;"})
    home_block = team_info_div.find("div", {"style":"float:right;"})
    
    away_data = parse_team_data(away_block)
    home_data = parse_team_data(home_block)
    
    for a in away_data:
        print(a)
    for h in home_data:
        print(h)

def parse_team_data(team_block):
    
    data = []
    data.append(team_block.find("div", {"style":"font-size:18px; margin-bottom:14px; font-family:Helvetica,sans-serif;"}).get_text())
    data.append("http://games.espn.com" + team_block.find("a").get("href"))
    #data.append("http://games.espn.com" + \
    #           team_block.find("div", {"stlye":"float:left; border-right:1px solid #dddddd; line-height:0px;"}).find("a").get("href"))
    data.append(team_block.find("div", {"class":"teamInfoOwnerData"}).get_text())
    
    text = team_block.get_text()
    record = parse_record(text)
    for r in record:
        data.append(r)
    data.append(re.findall("Streak: ([W|L|T][\d]{1,})", text))
    
    #print(len(text))
    #print(type(text))
    
    return data

def parse_record(text):
    
    record = []
    record_raw = re.findall("Record: ([\d]{1,}-[\d]{1,}-[\d]{1,})", text)
    
    record.append(re.findall("^[\d]{1,}", record_raw[0]))
    record.append(re.findall("-([\d]{1,})-", record_raw[0]))
    record.append(re.findall("-([\d]{1,})$", record_raw[0]))
    
    return record

main()


#BeautifulSoup(raw_html).find("div", {"style":"float:left;width:440px;margin-top:0px;"})
#BeautifulSoup(raw_html).find("div", {"style":"float:left;width:440px;margin-left:44px;margin-top:0px;"})











