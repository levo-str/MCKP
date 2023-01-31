#include "Node.h"

Node::Node(float b, SackComposition sack, std::unordered_set<int> setsAlreadyPresent) {
	this->bound = b;
	this->sackComposition = sack;
	this->currentValue = sack.calculateTotalProfit();
	this->setsAlreadyPresent = setsAlreadyPresent;
	for (auto item : this->sackComposition.getItemList()) {
		setsAlreadyPresent.insert(item.getTask());
	}
}
