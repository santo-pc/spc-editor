#pragma once

#include <map>
#include <assert.h>
#include <vector>

#define MANAGER NodesManager::Instance()

class QNEBlock;
class NodesManager
{
	private:
		NodesManager();
		~NodesManager();
	

	public:
		static NodesManager * Instance();
		typedef std::map<int, QNEBlock*> NodesMap;
		int nextIndexFree;
		NodesMap map;


		void RegisterNode(QNEBlock * nodo);
		int CreateNewId();
		QNEBlock * GetNodeFromID(int id)const;
		void RemoveNode(QNEBlock * actor);
		std::vector<QNEBlock * > GetNodeFromGroup(int group);		
		void DeleteAll();
	
};

