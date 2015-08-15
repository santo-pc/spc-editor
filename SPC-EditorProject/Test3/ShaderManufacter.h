#pragma once
#include <string>
#include "StringsAndDefines.h"
#include "qneblock.h"
#include <map>
#include <assert.h>
#include <vector>

#define MANUFACTURER ShaderManufacturer::Instance()

class ShaderManufacter
{

	private:
		int membersCounter[TOTAL_TYPES_NODES];

		std::map<int, std::string> listNodeMemberString;
		void GuardarEnLista(int nodeId, std::string memberString);
		
		ShaderManufacter();
		~ShaderManufacter();

	public:
		static ShaderManufacter * Instance();
		std::string RegistrarMiembro(QNEBlock * node, std::string memberString);
		bool AppendCodeFunction(QNEBlock * node, std::string code);
		bool AppendCodeConst(QNEBlock * node, std::string code);
		bool AppendCodeTexture(QNEBlock * node, std::string code);

};

