#include "ShaderComposer.h"
#include "Utils.h"
ShaderComposer * ShaderComposer::Instance()
{
	static ShaderComposer instance;

	return &instance;
}

ShaderComposer::ShaderComposer()
{
	for (int i = 0; i < TOTAL_TYPES_NODES; i++)
		membersCounter[i] = 0;
}


ShaderComposer::~ShaderComposer()
{
}


std::string ShaderComposer::RegistrarMiembro(QNEBlock * node)
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
		


		std::string resultName = node->titulo + ConvertIntToString(nameIndex);
		
		// Guardar en la lista
		GuardarEnLista(node->GetId(), resultName);


		// Actualizar el contador por tipo
		membersCounter[node->GetType()]++;

		return resultName;

	}


}


void ShaderComposer::GuardarEnLista(int nodeId, std::string memberString)
{
	listNodeMemberString.insert(std::pair<int, std::string>(nodeId, memberString));
}


bool ShaderComposer::AppendCodeFunction(QNEBlock * node, std::string code)
{
	std::map<int, std::string>::const_iterator it = listNodeCodeFunction.find(node->GetId());
	assert((it != listNodeCodeFunction.end()) && "<Node::NodeFromId>: invalid ID");

	// Existe devuelvo su nombre
	if ((it != listNodeCodeFunction.end()))
	{
		listNodeCodeFunction.insert(std::pair<int, std::string>(node->GetId(), code));
		return true;
	}

	return false;
}


bool ShaderComposer::AppendCodeConst(QNEBlock * node, std::string code)
{
	std::map<int, std::string>::const_iterator it = listNodeCodeConst.find(node->GetId());
	assert((it != listNodeCodeConst.end()) && "<Node::NodeFromId>: invalid ID");

	// Existe devuelvo su nombre
	if ((it == listNodeCodeConst.end()))
	{
		listNodeCodeConst.insert(std::pair<int, std::string>(node->GetId(), code));
		return true;
	}

	return false;

}

bool ShaderComposer::AppendCodeTexture(QNEBlock * node, std::string code)
{
	std::map<int, std::string>::const_iterator it = listNodeCodeTexture.find(node->GetId());
	assert((it != listNodeCodeTexture.end()) && "<Node::NodeFromId>: invalid ID");

	// Existe devuelvo su nombre
	if ((it != listNodeCodeTexture.end()))
	{
		listNodeCodeTexture.insert(std::pair<int, std::string>(node->GetId(), code));
		return true;
	}

	return false;
}


string ShaderComposer::Compose()
{
	string result = "#version 400 \n\n";


	result += "\n// CONSTS SECTION\n";
	for (std::map<int, std::string>::const_iterator it = listNodeCodeConst.begin(); it != listNodeCodeConst.end(); ++it)
	{
		result += (*it).second + "\n";
	}

	result += "\n// TEXTURE SECTION\n";

	for (std::map<int, std::string>::const_iterator it = listNodeCodeTexture.begin(); it != listNodeCodeTexture.end(); ++it)
	{
		result += (*it).second + "\n";
	}

	result += "\n// FUNCTIONS SECTION\n";

	for (std::map<int, std::string>::const_iterator it = listNodeCodeFunction.begin(); it != listNodeCodeFunction.end(); ++it)
	{
		result += (*it).second + "\n";
	}


	result +=	"void main()\n"
				"{\n"
				"	// THIS IS THE MAIN\n"
				"}\n"
				;

	cout << result;

	return result;

}

