#pragma once
#include<vector>
#include "sackcomposition.h"
#include "resourceManagerBB.h"


class Node
{
public:
	int getCurrentValue() { return currentValue; };
	int getBound() { return bound; };
	int getDepth() { return depth; };
	std::unordered_map<int, int> getMaxRatioItemIndexByTask() { return maxRatioItemIndexByTask; };
	std::unordered_set<int> getSetsAlreadyPresent() { return setsAlreadyPresent; };
	SackComposition getSackcomposition() { return sackComposition; };
	Node(int b, int c, SackComposition sack, unordered_map<int, int> maxRatioItemIndexByTask, std::unordered_set<int> setsAlreadyPresent);
	Node(){};

private:
	int bound;
	int currentValue;
	int depth;
	SackComposition sackComposition;
	std::unordered_set<int> setsAlreadyPresent;
	std::unordered_map<int, int> maxRatioItemIndexByTask;
	friend class ResourceManagerBB;
};
