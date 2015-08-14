#pragma once
#include <string> 
#include "Utils.h"
//#include "Shader.cpp"


#define STRINGDEFINES StringsAndDefines::Instance()

class StringsAndDefines
{
	private:
		StringsAndDefines();
		~StringsAndDefines();

	public:
		static StringsAndDefines * Instance();
		//std::string SampleFragmet(){ return ""; };

		std::string SampleFragmet()
		{
			return LoadShader("../../Resources/Shaders/blueShaderTest.fs");
		}

};

