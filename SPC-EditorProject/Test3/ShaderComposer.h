#pragma once
#include <string>
#include "StringsAndDefines.h"
#include "qneblock.h"
#include <map>
#include <assert.h>
#include <vector>

#define SHADER_COMPOSER ShaderComposer::Instance()
class CodeStringData
{
	
	public:
		int IdNode;
		string Code;
		CodeStringData(int idNode, string code)
		{
			IdNode = idNode;
			Code = code;
		};

};

class ShaderComposer
{

	private:
		int membersCounter[TOTAL_TYPES_NODES];

		std::map<int, std::string> listNodeMemberNamesString;
		
		//std::map<int, std::string> listNodeCodeFunction;
		//std::map<int, std::string> listNodeCodeConst;
		//std::map<int, std::string> listNodeCodeTexture;
		std::vector<CodeStringData> vectorNodeCodeFunction;
		std::vector<CodeStringData> vectorNodeCodeConst;
		std::vector<CodeStringData> vectorNodeCodeTexture;


		
		
		ShaderComposer();
		~ShaderComposer();

	public:
		static ShaderComposer * Instance();
		std::string RegistrarMiembro(QNEBlock * node);
		bool AppendCodeFunction(QNEBlock * node, std::string code);
		bool AppendCodeConst(QNEBlock * node, std::string code);
		bool AppendCodeTexture(QNEBlock * node, std::string code);
		string Compose(string mainString);
		void ClearAll();
		void GuardarEnLista(int nodeId, std::string memberString);
		std::map<int, std::string> listNodeMemberNamesStringTextures;


private :
	std::string GetHeaderStandard();
	std::string GetBlinnPhongStandard();
};

