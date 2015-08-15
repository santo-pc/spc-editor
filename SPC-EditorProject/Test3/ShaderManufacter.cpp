#include "ShaderManufacter.h"
#include "Utils.h"
ShaderManufacter * ShaderManufacter::Instance()
{
	static ShaderManufacter instance;

	return &instance;
}

ShaderManufacter::ShaderManufacter()
{
	for (int i = 0; i < TOTAL_TYPES_NODES; i++)
		membersCounter[i] = 0;
}


ShaderManufacter::~ShaderManufacter()
{
}


std::string ShaderManufacter::RegistrarMiembro(QNEBlock * node, std::string memberString)
{
	std::map<int, std::string>::const_iterator it = listNodeMemberString.find(node->GetId());
	assert((it != listNodeMemberString.end()) && "<Node::NodeFromId>: invalid ID");
	
	// Existe devuelvo su nombre
	if ((it != listNodeMemberString.end()))
	{
		return (*it).second;
	}
	else
	{
		// Buscar por id de grupo la ultima aparicion segun su tipo
		int nameIndex = membersCounter[node->GetType()];
		


		std::string resultName = node->titulo + ConvertIntToString(nameIndex) + "()";
		
		// Guardar en la lista
		GuardarEnLista(node->GetId(), resultName);


		// Actualizar el contador por tipo
		membersCounter[node->GetType()]++;

		return resultName;

	}


}


void ShaderManufacter::GuardarEnLista(int nodeId, std::string memberString)
{
	listNodeMemberString.insert(std::pair<int, std::string>(nodeId, memberString));
}


bool ShaderManufacter::AppendCodeFunction(QNEBlock * node, std::string code)
{
	return true;
}


bool ShaderManufacter::AppendCodeConst(QNEBlock * node, std::string code)
{
	return true;

}

bool ShaderManufacter::AppendCodeTexture(QNEBlock * node, std::string code)
{
	return true;
}


