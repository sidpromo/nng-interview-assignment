#pragma once

#include<iosfwd>
#include <fstream>

#include <string>
#include <vector>

#include<filesystem>

enum DataField { StreetName = 16, StreetType, RoadName, SchemeLeft = 20, FromLeft, ToLeft, SchemeRight, FromRight, ToRight, LOrder8, ROrder8, LOrder9, ROrder9, LPostalCode = 32, RPostalCode };

struct MapInfo {
	std::string street_Name;
	std::string street_Type;
	std::string road_Name;
	char scheme;
	int from;
	int to;
	std::string order8Name;
	std::string order9Name;
	int postalCode;

	MapInfo(std::string streetName, std::string sType, std::string rName,
		char scheme, int from, int to,
		std::string order8Name, std::string order9Name, int postalCode)
		:street_Name(streetName), street_Type(sType), road_Name(rName),
		scheme(scheme), from(from), to(to),
		order8Name(order8Name), order9Name(order9Name), postalCode(postalCode)
	{}

	bool isSameStreet(MapInfo& rhs) {
		return street_Name == rhs.street_Name && street_Type == rhs.street_Type && order8Name == rhs.order8Name;
	};
};

void createMapInfo(std::string streetName, std::string sType, std::string rName,
	char scheme, int from, int to,
	std::string order8Name, std::string order9Name, int postalCode,
	std::vector<MapInfo>& odds, std::vector<MapInfo>& evens, std::vector<MapInfo>& mixes) {
	switch (scheme)
	{
	case 'O':odds.emplace_back(streetName, sType, rName, scheme, from, to, order8Name, order9Name, postalCode); break;
	case 'E':evens.emplace_back(streetName, sType, rName, scheme, from, to, order8Name, order9Name, postalCode); break;
	case 'M':mixes.emplace_back(streetName, sType, rName, scheme, from, to, order8Name, order9Name, postalCode); break;
	default:
		break;
	}
}

static void createMapInfo(std::string line, std::vector<MapInfo>& odds, std::vector<MapInfo>& evens, std::vector<MapInfo>& mixes) {
	size_t pos = 0;
	std::string token;
	std::string delimiter = ",";
	int i = 0;

	std::string street_Name;
	std::string street_Type;
	std::string road_Name;

	char scheme_Left = '\0';
	int from_Left = 0;
	int to_Left = 0;
	char scheme_Right = '\0';
	int from_Right = 0;
	int to_Right = 0;

	std::string l_Order8;
	std::string r_Order8;
	std::string l_Order9;
	std::string r_Order9;

	int l_Postal_code = 0;
	int r_Postal_code = 0;

	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());

		token.erase(remove(token.begin(), token.end(), '\"'), token.end());

		if (!token.empty())
			switch (i) {
			case StreetName: street_Name = token; break;
			case StreetType: street_Type = token; break;
			case RoadName: road_Name = token; break;
			case SchemeLeft: scheme_Left = token.front(); break;
			case FromLeft: from_Left = atoi(token.c_str()); break;
			case ToLeft: to_Left = atoi(token.c_str()); break;
			case SchemeRight: scheme_Right = token.front(); break;
			case FromRight: from_Right = atoi(token.c_str()); break;
			case ToRight: to_Right = atoi(token.c_str()); break;
			case LOrder8: l_Order8 = token; break;
			case ROrder8: r_Order8 = token; break;
			case LOrder9: l_Order9 = token; break;
			case ROrder9: r_Order9 = token; break;
			case LPostalCode: l_Postal_code = atoi(token.c_str()); break;
			}
		i++;
	}
	r_Postal_code = atoi(token.c_str());

	if (from_Left != 0)
	{
		createMapInfo(street_Name, street_Type, road_Name, scheme_Left, from_Left, to_Left, l_Order8, l_Order9, l_Postal_code, odds, evens, mixes);
	}
	if (from_Right != 0)
	{
		createMapInfo(street_Name, street_Type, road_Name, scheme_Right, from_Right, to_Right, r_Order8, r_Order9, r_Postal_code, odds, evens, mixes);
	}
}

static void loadFile(char const* path, std::vector<MapInfo>& odds, std::vector<MapInfo>& evens, std::vector<MapInfo>& mixes) {
	if (!std::filesystem::exists(path))
	{
		odds = {};
		evens = {};
		mixes = {};
		return;
	}
	std::ifstream file(path);
	std::string str;

	while (std::getline(file, str))
	{
		createMapInfo(str, odds, evens, mixes);
	}
}
