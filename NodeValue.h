#pragma once
#include <atomic> //std::atomic_uint32_t
#include <unordered_set>
#include <unordered_map>
#include "sackcomposition.h"
//#include "Node.h"

class NodeValue
{
public:
	int getCount() { return count; };
	int getBound() { return bound; };
	std::unordered_map<int, int> getLastItemIndexConsideredPerTask() { return lastItemIndexConsidered; };
	std::unordered_set<int> getTasksAlreadyPresent() { return tasksAlreadyPresent; };
	SackComposition sackComposition;
	NodeValue(int b, int c, SackComposition sack, unordered_map<int, int> maxRatioItemIndexByTask);
	NodeValue();

private:
	std::unordered_set<int> tasksAlreadyPresent;
	int bound;
	int count;
	std::unordered_map<int, int> lastItemIndexConsidered;
	unordered_map<int, int> maxRatioItemIndexByTask;
	//friend class Node;
};
