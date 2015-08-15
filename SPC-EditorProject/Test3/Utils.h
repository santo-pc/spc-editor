#pragma once


#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string.h>


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