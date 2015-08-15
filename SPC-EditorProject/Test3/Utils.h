#pragma once


#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <locale>
#include <sstream>


using namespace std;

static std::string LoadShader(const std::string& fileName)
{
	cout << "Cargando Shader Strings from: " << fileName << endl;
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

static std::string ConvertIntToString(int i)
{
	stringstream convert;   // stream used for the conversion

	convert << i;      // insert the textual representation of 'Number' in the characters in the stream

	return convert.str();
}