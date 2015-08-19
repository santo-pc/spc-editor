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
	stringstream convert;

	convert << i;      

	return convert.str();
}

static bool SaveShaderToFile(std::string text, std::string fileName)
{

	cout << "Guardando Shader Strings: " << fileName << endl;
	ofstream myfile("../../Resources/Shaders/" + fileName, ios::out | ios::trunc);

	cout << "Saving File Path:" << "../../Resources/Shaders/" + fileName << endl;
	
	if (myfile.is_open())
	{
		myfile << text;		
		myfile.close();
		return true;
	}
	
	cout << "Unable to open file";
	return false;
	
}