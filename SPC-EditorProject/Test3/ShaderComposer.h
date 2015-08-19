#pragma once
#include <string>
#include "StringsAndDefines.h"
#include "qneblock.h"
#include <map>
#include <assert.h>
#include <vector>

#define SHADER_COMPOSER ShaderComposer::Instance()

class ShaderComposer
{

	private:
		int membersCounter[TOTAL_TYPES_NODES];

		std::map<int, std::string> listNodeMemberNamesString;
		std::map<int, std::string> listNodeCodeFunction;
		std::map<int, std::string> listNodeCodeConst;
		std::map<int, std::string> listNodeCodeTexture;

		void GuardarEnLista(int nodeId, std::string memberString);
		
		ShaderComposer();
		~ShaderComposer();

	public:
		static ShaderComposer * Instance();
		std::string RegistrarMiembro(QNEBlock * node);
		bool AppendCodeFunction(QNEBlock * node, std::string code);
		bool AppendCodeConst(QNEBlock * node, std::string code);
		bool AppendCodeTexture(QNEBlock * node, std::string code);
		string Compose();
		void ClearAll();



private :
	std::string GetHeaderStandard();
};

