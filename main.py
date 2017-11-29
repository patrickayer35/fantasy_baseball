from bs4 import BeautifulSoup
import os
import re
import urllib2

def main():
    
    week = get_week()
    boxscore_urls = get_full_boxscore_urls(week)

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

main()















