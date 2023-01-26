#include "Node.h"

Node::Node(int b, int c, SackComposition sack, unordered_map<int, int> maxRatioItemIndexByTask, std::unordered_set<int> setsAlreadyPresent) {
	this->bound = b;
	this->currentValue = c;
	this->sackComposition = sack;
	this->setsAlreadyPresent = setsAlreadyPresent;
	for (auto item : this->sackComposition.getItemList()) {
		setsAlreadyPresent.insert(item.getTask());
	}
	this->maxRatioItemIndexByTask = maxRatioItemIndexByTask;
}
