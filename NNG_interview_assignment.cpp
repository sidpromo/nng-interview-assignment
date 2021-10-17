// NNG_interview_assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>  // for std::find
#include <iostream>   // for std::cout
#include <string>
#include <vector>

#include<tuple>

#include "file_loader.h"

static void findOverlappingAdresses(std::vector<MapInfo>& mapData) {
	std::vector<std::tuple<std::string, int, int>> ret;
	if (mapData.size() < 2)
	{
		return;
	}

	std::sort(mapData.begin(), mapData.end(), [](const MapInfo& lhs, const MapInfo& rhs)
		{
			return std::tie(lhs.order9Name, lhs.street_Name, lhs.street_Type, lhs.from) <
				std::tie(rhs.order9Name, rhs.street_Name, rhs.street_Type, rhs.from);
		});

	int interval[2] = { 0,0 };

	for (size_t i = 0; i < mapData.size() - 1; i++)
	{
		if (!mapData[i].isSameStreet(mapData[i + 1]))
		{
			if (interval[0] != 0)
			{
				std::cout << mapData[i].street_Name << " " << mapData[i].street_Type << " " << mapData[i].scheme << " " << interval[0] << "-" << interval[1] << std::endl;
				interval[0] = 0;
				interval[1] = 0;
			}
			continue;
		}

		if (mapData[i].to >= mapData[i + 1].from)
		{

			int overlapStart = mapData[i + 1].from;
			int overlapEnd = std::min(mapData[i].to, mapData[i + 1].to);

			if (interval[0] == 0)
			{
				interval[0] = overlapStart;
				interval[1] = overlapEnd;
			}
			else if (overlapStart <= interval[1])
			{
				interval[0] = std::min(interval[0], overlapStart);
				interval[1] = std::max(interval[1], overlapEnd);
			}
		}
	}
}

int main(int argc, char* argv[])
{
	char const* filePath = argv[argc - 1];
	std::vector<MapInfo> oddNos;
	std::vector<MapInfo> evenNos;
	std::vector<MapInfo> mixedNos;

	loadFile(filePath, oddNos, evenNos, mixedNos);

	findOverlappingAdresses(oddNos);
	findOverlappingAdresses(evenNos);
	findOverlappingAdresses(mixedNos);
}