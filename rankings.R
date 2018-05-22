update_rankings <- function(filename, week, update)
{
	library(dplyr)
	data_raw <- read.csv(filename, colClasses = "character")
	data_clean <- clean_data(data_raw)
	
	batting_data <- select(data_clean, playerName, playerSlot, hardcodedTeamOwner, date, week, battingPoints)
	pitching_data <- select(data_clean, playerName, playerSlot, hardcodedTeamOwner, date, week, pitchingPoints)
	
	if (!update)
	{
		b <- get_batters_daily_std(batting_data)
		p <- get_pitchers_daily_std(pitching_data)
		
		write.csv(head(data.frame(b[[1]]), n = 200), "top_200_batters_daily.csv", row.names = FALSE)
		write.csv(head(data.frame(b[[2]]), n = 100), "worst_100_batters_daily.csv", row.names = FALSE)
		write.csv(head(data.frame(p[[1]]), n = 200), "top_200_pitchers_daily.csv", row.names = FALSE)
		write.csv(head(data.frame(p[[2]]), n = 100), "worst_100_pitchers_daily.csv", row.names = FALSE)
		
		write.csv(head(find_top_batters_bench(batting_data), n = 50), "top_50_batters_bench.csv", row.names = FALSE)
		write.csv(head(find_top_pitchers_bench(pitching_data), n = 50), "top_50_pitchers_bench.csv", row.names = FALSE)
		write.csv(head(find_top_batters_wo_hr(data_clean), n = 50), "top_50_batters_wo_hr.csv", row.names = FALSE)
		write.csv(head(find_worst_quality_starts(data_clean), n = 50), "worst_50_quality_starts.csv", row.names = FALSE)
		
		bw <- find_batters_weekly(batting_data, week)
		pw <- find_pitchers_weekly(pitching_data, week)
		
		write.csv(head(data.frame(bw[[1]]), n = 200), "top_200_batters_byAvg.csv", row.names = FALSE)
		write.csv(head(data.frame(bw[[2]]), n = 200), "top_200_batters_byPts.csv", row.names = FALSE)
		write.csv(head(data.frame(bw[[3]]), n = 100), "worst_100_batters_byAvg.csv", row.names = FALSE)
		write.csv(head(data.frame(bw[[4]]), n = 100), "worst_100_batters_byPts.csv", row.names = FALSE)
		
		write.csv(head(data.frame(pw[[1]]), n = 200), "top_200_pitchers_byAvg.csv", row.names = FALSE)
		write.csv(head(data.frame(pw[[2]]), n = 200), "top_200_pitchers_byPts.csv", row.names = FALSE)
		write.csv(head(data.frame(pw[[3]]), n = 100), "worst_100_pitchers_byAvg.csv", row.names = FALSE)
		write.csv(head(data.frame(pw[[4]]), n = 100), "worst_100_pitchers_byPts.csv", row.names = FALSE)
	}
	else
	{
		b <- update_batters_daily(batting_data)
		p <- update_pitchers_daily(pitching_data)
		
		write.csv(head(data.frame(b[[1]]), n = 200), "top_200_batters_daily.csv", row.names = FALSE)
		write.csv(head(data.frame(b[[2]]), n = 100), "worst_100_batters_daily.csv", row.names = FALSE)
		write.csv(head(data.frame(p[[1]]), n = 200), "top_200_pitchers_daily.csv", row.names = FALSE)
		write.csv(head(data.frame(p[[2]]), n = 100), "worst_100_pitchers_daily.csv", row.names = FALSE)
		
		write.csv(head(update_top_batters_bench(batting_data), n = 50), "top_50_batters_bench.csv", row.names = FALSE)
		write.csv(head(update_top_pitchers_bench(pitching_data), n = 50), "top_50_pitchers_bench.csv", row.names = FALSE)
		write.csv(head(update_top_batters_wo_hr(data_clean), n = 50), "top_50_batters_wo_hr.csv", row.names = FALSE)
		write.csv(head(update_worst_quality_starts(data_clean), n = 50), "worst_50_quality_starts.csv", row.names = FALSE)
		
		bw <- update_batters_weekly(batting_data, week)
		pw <- update_pitchers_weekly(pitching_data, week)
		
		write.csv(head(data.frame(bw[[1]]), n = 200), "top_200_batters_byAvg.csv", row.names = FALSE)
		write.csv(head(data.frame(bw[[2]]), n = 200), "top_200_batters_byPts.csv", row.names = FALSE)
		write.csv(head(data.frame(bw[[3]]), n = 100), "worst_100_batters_byAvg.csv", row.names = FALSE)
		write.csv(head(data.frame(bw[[4]]), n = 100), "worst_100_batters_byPts.csv", row.names = FALSE)
		
		write.csv(head(data.frame(pw[[1]]), n = 200), "top_200_pitchers_byAvg.csv", row.names = FALSE)
		write.csv(head(data.frame(pw[[2]]), n = 200), "top_200_pitchers_byPts.csv", row.names = FALSE)
		write.csv(head(data.frame(pw[[3]]), n = 100), "worst_100_pitchers_byAvg.csv", row.names = FALSE)
		write.csv(head(data.frame(pw[[4]]), n = 100), "worst_100_pitchers_byPts.csv", row.names = FALSE)
	}
}

clean_data <- function(data)
{
	tidy_data <- tbl_df(data)
	tidy_data[, 4:30] <- apply(tidy_data[, 4:30], 2, as.double)
	tidy_data$hardcodedTeamOwner <- convert_owner_names(tidy_data$teamId, tidy_data$teamOwner)
	
	return(tidy_data)
}

convert_owner_names <- function(team_ids, owner_names_raw)
{
	for (i in 1:length(team_ids))
	{
		if (team_ids[i] == 1)
		{
			owner_names_raw[i] <- "Patrick Ayer"
		}
		else if (team_ids[i] == 2)
		{
			owner_names_raw[i] <- "Craig Wise"
		}
		else if (team_ids[i] == 3)
		{
			owner_names_raw[i] <- "Ryan Daley"
		}
		else if (team_ids[i] == 4)
		{
			owner_names_raw[i] <- "Nic Hay"
		}
		else if (team_ids[i] == 5)
		{
			owner_names_raw[i] <- "Rory Lynch"
		}
		else if (team_ids[i] == 6)
		{
			owner_names_raw[i] <- "Megan Seagren"
		}
		else if (team_ids[i] == 7)
		{
			owner_names_raw[i] <- "Eric Wang"
		}
		else if (team_ids[i] == 8)
		{
			owner_names_raw[i] <- "Ben Chance"
		}
		else if (team_ids[i] == 9)
		{
			owner_names_raw[i] <- "Will Smith"
		}
		else if (team_ids[i] == 10)
		{
			owner_names_raw[i] <- "Will Cherry"
		}
		else if (team_ids[i] == 11)
		{
			owner_names_raw[i] <- "Sean Phillips"
		}
		else
		{
			owner_names_raw[i] <- "Sandy Kishida"
		}
	}
	return(owner_names_raw)
}

get_old_data_daily <- function(filename)
{
	data <- read.csv(filename, colClasses = "character")
	tidy_data <- tbl_df(data)
	tidy_data[, 6] <- as.double(unlist(tidy_data[, 6]))
	
	return(tidy_data)
}

get_old_data_weekly <- function(filename)
{
	data <- read.csv(filename, colClasses = "character")
	tidy_data <- tbl_df(data)
	tidy_data[, 4:5] <- as.double(unlist(tidy_data[, 4:5]))
	
	return(tidy_data)
}

get_batters_daily_std <- function(data)
{
	ext_d <- data %>%
		filter(playerSlot != "Bench" & playerSlot != "DL")
	
	return(list(arrange(ext_d, desc(battingPoints)), arrange(ext_d, battingPoints)))
}

update_batters_daily <- function(data)
{
	t_old <- get_old_data_daily("top_200_batters_daily.csv")
	w_old <- get_old_data_daily("worst_100_batters_daily.csv")
	
	c_data <- rbind(t_old, w_old, data)
	return(get_batters_daily_std(c_data))
}

get_pitchers_daily_std <- function(data)
{
	ext_d <- data %>%
		filter(playerSlot != "Bench" & playerSlot != "DL")
	
	return(list(arrange(ext_d, desc(pitchingPoints)), arrange(ext_d, pitchingPoints)))
}

update_pitchers_daily <- function(data)
{
	t_old <- get_old_data_daily("top_200_pitchers_daily.csv")
	w_old <- get_old_data_daily("worst_100_pitchers_daily.csv")
	
	c_data <- rbind(t_old, w_old, data)
	return(get_pitchers_daily_std(c_data))
}

find_top_batters_bench <- function(data)
{
	ext_d <- data %>%
		filter(playerSlot == "Bench" | playerSlot == "DL") %>%
		arrange(desc(battingPoints))
	
	return(ext_d)
}

update_top_batters_bench <- function(data)
{
	od <- get_old_data_daily("top_50_batters_bench.csv")
	nd <- rbind(od, data)
	
	return(find_top_batters_bench(nd))
}

find_top_pitchers_bench <- function(data)
{
	ext_d <- data %>%
		filter(playerSlot == "Bench" | playerSlot == "DL") %>%
		arrange(desc(pitchingPoints))
	
	return(ext_d)
}

update_top_pitchers_bench <- function(data)
{
	od <- get_old_data_daily("top_50_pitchers_bench.csv")
	nd <- rbind(od, data)
	
	return(find_top_pitchers_bench(nd))
}

find_top_batters_wo_hr <- function(data)
{
	ext_d <- data %>%
		filter(playerSlot != "Bench" & playerSlot != "DL" & homeRuns == 0) %>%
		arrange(desc(battingPoints)) %>%
		select(playerName, playerSlot, hardcodedTeamOwner, date, week, battingPoints)
	
	return(ext_d)
}

update_top_batters_wo_hr <- function(data)
{
	od <- get_old_data_daily("top_50_batters_wo_hr.csv")
	nd <- find_top_batters_wo_hr(data)
	cd <- rbind(od, nd)
	
	return(arrange(cd, desc(battingPoints)))
}

find_worst_quality_starts <- function(data)
{
	ext_d <- data %>%
		filter(playerSlot != "Bench" & playerSlot != "DL" & qualityStarts == 1) %>%
		arrange(pitchingPoints) %>%
		select(playerName, playerSlot, hardcodedTeamOwner, date, week, pitchingPoints)
		
	return(ext_d)
}

update_worst_quality_starts <- function(data)
{
	od <- get_old_data_daily("worst_50_quality_starts.csv")
	nd <- find_worst_quality_starts(data)
	cd <- rbind(od, nd)
	
	return(arrange(cd, pitchingPoints))
}

find_batters_weekly <- function(data, week)
{
	owners <- levels(as.factor(data$hardcodedTeamOwner))
	ext_d <- data.frame(matrix(ncol = 5, nrow = 0))
	for (o in 1:length(owners))
	{
		ext_d <- rbind(ext_d, per_team(filter(data, hardcodedTeamOwner == owners[o]), owners[o], week, TRUE))
	}
	colnames(ext_d) <- c("playerName", "hardcodedTeamOwner", "week", "battingPoints", "avgBattingPoints")
	ext_d$battingPoints <- as.double(ext_d$battingPoints)
	ext_d$avgBattingPoints <- as.double(ext_d$avgBattingPoints)
	return(list(arrange(ext_d, desc(avgBattingPoints)),
				arrange(ext_d, desc(battingPoints)),
				arrange(ext_d, avgBattingPoints),
				arrange(ext_d, battingPoints)))
}

update_batters_weekly <- function(data, week)
{
	odta <- get_old_data_weekly("top_200_batters_byAvg.csv")
	odtp <- get_old_data_weekly("top_200_batters_byPts.csv")
	odwa <- get_old_data_weekly("worst_100_batters_byAvg.csv")
	odwp <- get_old_data_weekly("worst_100_batters_byPts.csv")
	nd <- find_batters_weekly(data, week)
	
	cdta <- rbind(odta, data.frame(nd[[1]]))
	cdtp <- rbind(odtp, data.frame(nd[[2]]))
	cdwa <- rbind(odwa, data.frame(nd[[3]]))
	cdtp <- rbind(odtp, data.frame(nd[[4]]))
	
	return(list(arrange(cdta, desc(avgBattingPoints)),
				arrange(cdtp, desc(battingPoints)),
				arrange(cdwa, avgBattingPoints),
				arrange(cdtp, battingPoints)))
}

find_pitchers_weekly <- function(data, week)
{
	owners <- levels(as.factor(data$hardcodedTeamOwner))
	ext_d <- data.frame(matrix(ncol = 5, nrow = 0))
	for (o in 1:length(owners))
	{
		ext_d <- rbind(ext_d, per_team(filter(data, hardcodedTeamOwner == owners[o]), owners[o], week, FALSE))
	}
	colnames(ext_d) <- c("playerName", "hardcodedTeamOwner", "week", "pitchingPoints", "avgPitchingPoints")
	#extracted_data$pitchingPoints <- as.double(extracted_data$pitchingPoints)
	ext_d$pitchingPoints <- as.double(ext_d$pitchingPoints)
	ext_d$avgPitchingPoints <- as.double(ext_d$avgPitchingPoints)
	return(list(arrange(ext_d, desc(avgPitchingPoints)),
				arrange(ext_d, desc(pitchingPoints)),
				arrange(ext_d, avgPitchingPoints),
				arrange(ext_d, pitchingPoints)))
}

update_pitchers_weekly <- function(data, week)
{
	odta <- get_old_data_weekly("top_200_pitchers_byAvg.csv")
	odtp <- get_old_data_weekly("top_200_pitchers_byPts.csv")
	odwa <- get_old_data_weekly("worst_100_pitchers_byAvg.csv")
	odwp <- get_old_data_weekly("worst_100_pitchers_byPts.csv")
	nd <- find_pitchers_weekly(data, week)
	
	cdta <- rbind(odta, data.frame(nd[[1]]))
	cdtp <- rbind(odtp, data.frame(nd[[2]]))
	cdwa <- rbind(odwa, data.frame(nd[[3]]))
	cdtp <- rbind(odtp, data.frame(nd[[4]]))
	
	return(list(arrange(cdta, desc(avgPitchingPoints)),
				arrange(cdtp, desc(pitchingPoints)),
				arrange(cdwa, avgPitchingPoints),
				arrange(cdtp, pitchingPoints)))
}

per_team <- function(data, owner, week, batting)
{
	totals <- data.frame(matrix(ncol = 5, nrow = 0))
	players <- levels(as.factor(data$playerName))
	day_count <- length(levels(as.factor(data$date)))
	for (p in 1:length(players))
	{
		player_data <- filter(data, playerName == players[p] & playerSlot != "DL" & playerSlot != "Bench")
		if (batting)
		{
			r <- c(players[p], owner, week, sum(player_data$battingPoints), sum(player_data$battingPoints) / day_count)
		}
		else
		{
			r <- c(players[p], owner, week, sum(player_data$pitchingPoints), sum(player_data$pitchingPoints) / day_count)
		}
		totals[nrow(totals) + 1, ] <- r
	}
	return(totals)
}
















