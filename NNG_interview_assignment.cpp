// NNG_interview_assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>  // for std::find
#include <iostream>   // for std::cout
#include <string>
#include <vector>

#include<tuple>

#include "file_loader.h"

static void findOverlappingAdresses(std::vector<MapInfo>& map_infos) {
	if (map_infos.size() < 2)
	{
		return;
	}

	std::sort(map_infos.begin(), map_infos.end(), [](const MapInfo& lhs, const MapInfo& rhs)
		{
			return std::tie(lhs.order9Name, lhs.street_Name, lhs.street_Type, lhs.from) <
				std::tie(rhs.order9Name, rhs.street_Name, rhs.street_Type, rhs.from);
		});

	int interval[2] = { 0,0 };

	for (size_t i = 0; i < map_infos.size() - 1; i++)
	{
		if (!map_infos[i].isSameStreet(map_infos[i + 1]))
		{
			if (interval[0] != 0)
			{
				std::cout << map_infos[i].street_Name << " " << map_infos[i].street_Type << " " << map_infos[i].scheme << " " << interval[0] << "-" << interval[1] << std::endl;
				interval[0] = 0;
				interval[1] = 0;
			}
			continue;
		}

		if (map_infos[i].to >= map_infos[i + 1].from)
		{

			int overlap_start = map_infos[i + 1].from;
			int overlap_end = std::min(map_infos[i].to, map_infos[i + 1].to);

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