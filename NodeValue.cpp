#include "NodeValue.h"

NodeValue::NodeValue(int b, int c, SackComposition sack, unordered_map<int, int> maxRatioItemIndexByTask) {
	this->bound = b;
	this->count = c;
	this->sackComposition = sack;
	for (auto item : this->sackComposition.getItemList()) {
		tasksAlreadyPresent.insert(item.getTask());
	}
	this->maxRatioItemIndexByTask = maxRatioItemIndexByTask;
}

NodeValue::NodeValue() {
}
