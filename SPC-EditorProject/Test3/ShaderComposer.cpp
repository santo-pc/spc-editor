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
	std::map<int, std::string>::const_iterator it = listNodeMemberNamesString.find(node->GetId());
	assert((it != listNodeMemberString.end()) && "<Node::NodeFromId>: invalid ID");
	
	// Existe devuelvo su nombre
	if ((it != listNodeMemberNamesString.end()))
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

		if (node->GetType() == ID_TYPE_SPTextureNode)
			listNodeMemberNamesStringTextures.insert(std::pair<int, std::string>(node->GetId(), resultName));

		// Actualizar el contador por tipo
		membersCounter[node->GetType()]++;

		return resultName;

	}


}


void ShaderComposer::GuardarEnLista(int nodeId, std::string memberString)
{
	listNodeMemberNamesString.insert(std::pair<int, std::string>(nodeId, memberString));



}




bool ShaderComposer::AppendCodeFunction(QNEBlock * node, std::string code)
{
	bool existe = false;
	for (std::vector<CodeStringData>::const_iterator it = vectorNodeCodeFunction.begin(); 
		 it != vectorNodeCodeFunction.end();
		++it)
	{
		if (node->GetId() == (*it).IdNode)
		{
			existe = true;
			break;
		}
	}

	
	if (!existe)
	{
		vectorNodeCodeFunction.push_back(CodeStringData(node->GetId(), code));
		return true;
	}

	return false;
}


bool ShaderComposer::AppendCodeConst(QNEBlock * node, std::string code)
{
	bool existe = false;
	for (std::vector<CodeStringData>::const_iterator it = vectorNodeCodeConst.begin();
		it != vectorNodeCodeConst.end();
		++it)
	{
		if (node->GetId() == (*it).IdNode)
		{
			existe = true;
			break;
		}
	}


	if (!existe)
	{
		vectorNodeCodeConst.push_back(CodeStringData(node->GetId(), code));
		return true;
	}

	return false;

}

bool ShaderComposer::AppendCodeTexture(QNEBlock * node, std::string code)
{
	bool existe = false;
	for (std::vector<CodeStringData>::const_iterator it = vectorNodeCodeTexture.begin();
		it != vectorNodeCodeTexture.end();
		++it)
	{
		if (node->GetId() == (*it).IdNode)
		{
			existe = true;
			break;
		}
	}


	if (!existe)
	{
		vectorNodeCodeTexture.push_back(CodeStringData(node->GetId(), code));
		return true;
	}

	return false;
}


string ShaderComposer::Compose(string mainString)
{
	string result = GetHeaderStandard();


	
	result += "\n// Const Section\n";
	for (std::vector<CodeStringData>::const_iterator it = vectorNodeCodeConst.begin(); it != vectorNodeCodeConst.end(); ++it)
	{
		result += (*it).Code+ "\n";
	}

	result += "\n// Textures Section\n";

	for (std::vector<CodeStringData>::const_iterator it = vectorNodeCodeTexture.begin(); it != vectorNodeCodeTexture.end(); ++it)
	{
		result += (*it).Code + "\n";
	}

	result += "\n// Functions Section\n";

	for (std::vector<CodeStringData>::const_iterator it = vectorNodeCodeFunction.begin(); it != vectorNodeCodeFunction.end(); ++it)
	{
		result += (*it).Code + "\n";
	}

	result += GetBlinnPhongStandard();
	result += mainString;

	cout << result;

	return result;

}


void ShaderComposer::ClearAll()
{
	// Reiniciar la cuenta
	for (int i = 0; i < TOTAL_TYPES_NODES; i++)
		membersCounter[i] = 0;



	// Limpiar las listas
	listNodeMemberNamesString.clear();
	listNodeMemberNamesStringTextures.clear();
	/*listNodeCodeConst.clear();
	listNodeCodeTexture.clear();
	listNodeCodeFunction.clear();*/
	vectorNodeCodeConst.clear();
	vectorNodeCodeTexture.clear();
	vectorNodeCodeFunction.clear();
	

	
}
string ShaderComposer::GetHeaderStandard()
{
	return "#version 400\n"
		"\n"
		"in vec3 VexterPosEye;\n"
		"in vec2 TexCoord;\n"
		"in vec3 ViewDir;\n"
		"in vec3 LightDirStaticTan;\n"		
		"\nuniform vec3 LightColor;"
		"\nuniform float LightDiffuseIntensity;"
		"\nuniform float LightAmbientIntensity;"
		"\n"
		"layout(location = 0) out vec4 FragColor;\n";

}

string ShaderComposer::GetBlinnPhongStandard()
{
	return "\nvec3 BlinnPhong(vec3 diffR, vec3 norm, vec3 specularLvl, float Shininess)\n"
	"{\n"	
	"\n"
	"	// this is blinn phong\n"
	"	vec3 h = normalize(LightDirStaticTan + ViewDir);\n"
	"\n"
	"	vec3 ambient = (LightAmbientIntensity *  LightColor);\n"
	"\n"
	"	float sDotN = max(dot(LightDirStaticTan, norm), 0.0);\n"
	"\n"
	"	vec3 diffuse = (LightDiffuseIntensity *  LightColor) * diffR * sDotN;\n"
	"\n"
	"	vec3 spec = vec3(0.0);\n"
	"\n"
	"	if (sDotN > 0.0)\n"
	"		spec = LightColor * specularLvl * pow(max(dot(h, norm), 0.0), Shininess);\n"
	"\n"
	"	return ambient + diffuse + spec;\n"
	"}\n";

}