/// <summary>
/// @Author: Paul Nolan
/// @Version 2.0
/// </summary>

#ifndef CREDITS_LOADER
#define CREDITS_LOADER


#include <SFML/System/Vector2.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"
//The below three structs are used to load in the names and job titles for the credits

struct NameData
{
	std::string m_name;
};

struct TitleData
{
	std::string m_title;
};

struct TextData
{
	std::vector<NameData> m_name;
	std::vector<TitleData> m_title;
};


class CreditsLoader
{
public:
	CreditsLoader() = default;
	
	static bool load(TextData& Text);
};

#endif