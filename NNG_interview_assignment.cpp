// NNG_interview_assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>  
#include <iostream>   
#include <string>
#include <vector>

#include<tuple>

#include "file_loader.h"

void writeToOutputAndResetInterval(const MapInfo& map_info, int interval[2]) {
	if (map_info.street_name.empty())
	{
		return;
	}
	std::cout << map_info.street_name << " " << map_info.street_type << ": " << map_info.scheme << " " << interval[0] << "-" << interval[1] << std::endl;
	interval[0] = 0;
	interval[1] = 0;
}

/// <summary>
/// Compare newly found overlap with the previously found overlap
/// </summary>
/// <param name="current_max_to">Current interval upper limit</param>
/// <param name="next_map_info">MapInfo object which contains the next interval</param>
/// <param name="interval">Previously found overlap</param>
void processOverlap(const int current_upper_limit, const MapInfo& next_map_info, int interval[2]) {
	int overlap_start = next_map_info.from;
	int overlap_end = std::min(current_upper_limit, next_map_info.to);

	if (interval[0] == 0)
	{
		interval[0] = overlap_start;
		interval[1] = overlap_end;
	}
	//can extend the previous interval
	else if (overlap_start <= interval[1])
	{
		interval[0] = std::min(interval[0], overlap_start);
		interval[1] = std::max(interval[1], overlap_end);
	}
	//can't extend the previous interval anymore
	else
	{
		writeToOutputAndResetInterval(next_map_info, interval);
		interval[0] = overlap_start;
		interval[1] = overlap_end;
	}
}

void findOverlappingAdresses(std::vector<MapInfo>& map_info) {
	if (map_info.size() < 2)
	{
		return;
	}

	std::sort(map_info.begin(), map_info.end(), [](const MapInfo& lhs, const MapInfo& rhs)
		{
			return std::tie(lhs.order8_name, lhs.order9_name, lhs.street_name, lhs.street_type, lhs.from, lhs.to) <
				std::tie(lhs.order8_name, rhs.order9_name, rhs.street_name, rhs.street_type, rhs.from, rhs.to);
		});

	int interval[2] = { 0,0 };
	int max_interval_to = 0;
	
	for (auto i = 0; i < map_info.size() - 1; ++i)
	{
		if (!map_info[i].isSameStreet(map_info[i + 1]))
		{
			//overlap with any previous
			if (max_interval_to > map_info[i].from)
			{
				interval[0] = map_info[i].from;
				interval[1] = std::min(map_info[i].to, max_interval_to);
			}

			if (interval[0] != 0)
			{
				writeToOutputAndResetInterval(map_info[i], interval);
			}
			max_interval_to = 0;
			continue;
		}

		//Has overlap with next
		if (map_info[i].to >= map_info[i + 1].from)
		{
			processOverlap(map_info[i].to, map_info[i + 1], interval);
		}
		//no overlap with next
		else
		{
			//overlap with any previous
			if (max_interval_to >= map_info[i + 1].from)
			{
				processOverlap(max_interval_to, map_info[i + 1], interval);
			}
			else if (interval[0] != 0)
			{
				writeToOutputAndResetInterval(map_info[i], interval);
			}
		}

		max_interval_to = std::max(map_info[i].to, max_interval_to);
	}

	if (interval[0] != 0)
	{
		writeToOutputAndResetInterval(map_info.back(), interval);
	}
}

// Input file path must be given as a command line argument
int main(int argc, char* argv[])
{
	char const* file_path = argv[argc - 1];
	std::vector<MapInfo> odd_nos;
	std::vector<MapInfo> even_nos;
	std::vector<MapInfo> mixed_nos;

	loadFile(file_path, odd_nos, even_nos, mixed_nos);

	findOverlappingAdresses(odd_nos);
	findOverlappingAdresses(even_nos);
	findOverlappingAdresses(mixed_nos);
}