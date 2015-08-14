#pragma once
#include <list>
#define MANUFACTURER ShaderManufacturer::Instance()

class ShaderManufacter
{

	private:
		
		ShaderManufacter();
		~ShaderManufacter();




	public:
		static ShaderManufacter * Instance();

};

