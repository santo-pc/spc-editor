#include "ShaderManufacter.h"

ShaderManufacter * ShaderManufacter::Instance()
{
	static ShaderManufacter instance;

	return &instance;
}

ShaderManufacter::ShaderManufacter()
{
}


ShaderManufacter::~ShaderManufacter()
{
}
