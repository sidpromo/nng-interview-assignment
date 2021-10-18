// NNG_interview_assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>  // for std::find
#include <iostream>   // for std::cout
#include <string>
#include <vector>

#include<tuple>

#include "file_loader.h"

void findOverlappingAdresses(std::vector<MapInfo>& map_info) {
	if (map_info.size() < 2)
	{
		return;
	}

	std::sort(map_info.begin(), map_info.end(), [](const MapInfo& lhs, const MapInfo& rhs)
		{
			return std::tie(lhs.order8_name, lhs.order9_name, lhs.street_name, lhs.street_type, lhs.from) <
				std::tie(lhs.order8_name, rhs.order9_name, rhs.street_name, rhs.street_type, rhs.from);
		});

	int interval[2] = { 0,0 };

	for (auto i = 0; i < map_info.size() - 1; ++i)
	{
		if (!map_info[i].isSameStreet(map_info[i + 1]))
		{
			if (interval[0] != 0)
			{
				std::cout << map_info[i].street_name << " " << map_info[i].street_type << " " << map_info[i].scheme << " " << interval[0] << "-" << interval[1] << std::endl;
				interval[0] = 0;
				interval[1] = 0;
			}
			continue;
		}

		if (map_info[i].to >= map_info[i + 1].from)
		{

			int overlap_start = map_info[i + 1].from;
			int overlap_end = std::min(map_info[i].to, map_info[i + 1].to);

			if (interval[0] == 0)
			{
				interval[0] = overlap_start;
				interval[1] = overlap_end;
			}
			else if (overlap_start <= interval[1])
			{
				interval[0] = std::min(interval[0], overlap_start);
				interval[1] = std::max(interval[1], overlap_end);
			}
		}
	}
}

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