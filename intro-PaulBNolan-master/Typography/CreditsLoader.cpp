/// <summary>
/// @Author: Paul Nolan
/// @Version 2.0
/// </summary>

#include "CreditsLoader.h"


//These three operators are used to load in the names and titles
void operator >> (const YAML::Node& nameNode, NameData& name)
{
	name.m_name = nameNode["Name"].as<std::string>();
}

void operator >> (const YAML::Node& titleNode, TitleData& title)
{
	title.m_title = titleNode["Title"].as<std::string>();
}

void operator >> (const YAML::Node& textNode, TextData& Text)
{
	const YAML::Node& NameNode = textNode["Names"].as<YAML::Node>();

	for (unsigned i = 0; i < NameNode.size(); ++i)
	{
		NameData name;
		NameNode[i] >> name;
		Text.m_name.push_back(name);
	}

	const YAML::Node& TitleNode = textNode["Titles"].as<YAML::Node>();

	for (unsigned i = 0; i <TitleNode.size(); ++i)
	{
		TitleData title;
		TitleNode[i] >> title;
		Text.m_title.push_back(title);
	}
}
bool CreditsLoader::load(TextData& Text)
{
	std::stringstream ss;
	ss << "Credits.yaml";
	YAML::Node baseNode = YAML::LoadFile("ASSETS/Credits/" + ss.str());
	try
	{
		if (baseNode.IsNull())
		{
			std::string message("file:Credits not found");
			throw std::exception(message.c_str());
		}

		baseNode >> Text;
	}
	catch (YAML::ParserException& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	return true;
}
