#include "NodesManager.h"
#include "qneblock.h"
#include <iostream>
using namespace std;

NodesManager * NodesManager::Instance()
{
	static NodesManager manager;
	return &manager;
}

NodesManager::NodesManager()
{
	nextIndexFree = 0;
}


NodesManager::~NodesManager()
{
}

void NodesManager::RegisterNode(QNEBlock * node)
{
	if (!node)return;

	node->SetId(nextIndexFree);
	map.insert(std::pair<int, QNEBlock *>(nextIndexFree, node));
	cout << "Node registered ID: " << nextIndexFree << endl;
	nextIndexFree++;

}

int NodesManager::CreateNewId()
{
	int devolver = nextIndexFree;
	nextIndexFree++;
	return devolver;
}

QNEBlock* NodesManager::GetActorFromID(int id)const
{

	// Get a QNEBlock
	/*cout << id << endl;*/
	NodesMap::const_iterator it = map.find(id);
	assert((it != map.end()) && "<QNEBlock::NodeID>: invalid ID");
	QNEBlock * aux = it->second;

	return aux;
}

void NodesManager::RemoveActor(QNEBlock * node)
{
	map.erase(map.find(node->GetId()));
}

void NodesManager::DeleteAll()
{
	map.clear();
}

//std::vector<QNEBlock * > NodesManager::GetActorsFromGroup(int group)
//{
//	vector<QNEBlock * > vector;
//	NodesMap::const_iterator it;
//	for (it = map.begin(); it != map.end(); ++it)
//	{
//		QNEBlock * actor = (*it).second;
//		if (actor->GetGroup() == group)
//			vector.push_back(actor);
//	}
//	return vector;
//}

