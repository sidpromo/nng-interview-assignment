#pragma once

#include<iosfwd>
#include <fstream>

#include <string>
#include <vector>

#include<filesystem>

enum DataField { StreetName = 16, StreetType, RoadName, SchemeLeft = 20, FromLeft, ToLeft, SchemeRight, FromRight, ToRight, LOrder8, ROrder8, LOrder9, ROrder9 };

struct MapInfo {
	std::string street_name;
	std::string street_type;
	std::string road_name;
	char scheme;
	int from;
	int to;
	std::string order8_name;
	std::string order9_name;

	MapInfo(std::string streetName, std::string sType, std::string rName,
		char scheme, int from, int to,
		std::string order8_name, std::string order9_name)
		:street_name(streetName), street_type(sType), road_name(rName),
		scheme(scheme), from(from), to(to),
		order8_name(order8_name), order9_name(order9_name)
	{}

	bool isSameStreet(const MapInfo& rhs) {
		return street_name == rhs.street_name && street_type == rhs.street_type && order8_name == rhs.order8_name;
	};
};

void createMapInfo(std::string streetName, std::string sType, std::string rName,
	char scheme, int from, int to,
	std::string order8_name, std::string order9_name,
	std::vector<MapInfo>& odds, std::vector<MapInfo>& evens, std::vector<MapInfo>& mixes) {
	switch (scheme)
	{
	case 'O':odds.emplace_back(streetName, sType, rName, scheme, from, to, order8_name, order9_name); break;
	case 'E':evens.emplace_back(streetName, sType, rName, scheme, from, to, order8_name, order9_name); break;
	case 'M':mixes.emplace_back(streetName, sType, rName, scheme, from, to, order8_name, order9_name); break;
	default:
		break;
	}
}

void assortAddressesByParity(std::string line, std::vector<MapInfo>& odds, std::vector<MapInfo>& evens, std::vector<MapInfo>& mixes) {
	size_t pos = 0;
	std::string token;
	const std::string delimiter = ",";
	int i = 0;

	std::string street_name;
	std::string street_type;
	std::string road_name;

	char scheme_left = '\0';
	int from_left = 0;
	int to_left = 0;
	char scheme_right = '\0';
	int from_right = 0;
	int to_right = 0;

	std::string l_order8;
	std::string r_order8;
	std::string l_order9;
	std::string r_order9;

	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());

		token.erase(remove(token.begin(), token.end(), '"'), token.end());

		if (!token.empty())
			switch (i) {
			case StreetName: street_name = token; break;
			case StreetType: street_type = token; break;
			case RoadName: road_name = token; break;
			case SchemeLeft: scheme_left = token.front(); break;
			case FromLeft: from_left = std::stoi(token); break;
			case ToLeft: to_left = std::stoi(token); break;
			case SchemeRight: scheme_right = token.front(); break;
			case FromRight: from_right = std::stoi(token); break;
			case ToRight: to_right = std::stoi(token); break;
			case LOrder8: l_order8 = token; break;
			case ROrder8: r_order8 = token; break;
			case LOrder9: l_order9 = token; break;
			case ROrder9: r_order9 = token; break;
			}
		++i;
	}

	if (from_left != 0)
	{
		createMapInfo(street_name, street_type, road_name, scheme_left, from_left, to_left, l_order8, l_order9, odds, evens, mixes);
	}
	if (from_right != 0)
	{
		createMapInfo(street_name, street_type, road_name, scheme_right, from_right, to_right, r_order8, r_order9, odds, evens, mixes);
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
		assortAddressesByParity(str, odds, evens, mixes);
	}
}
