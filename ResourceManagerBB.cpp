#include "ResourceManagerBB.h"
#include "Node.h"
#include <limits>
#include <queue>

float calculateRatio(JobConfiguration jobConfiguration) {
	return jobConfiguration.getProfit() / jobConfiguration.getResources();
}

bool compareByRatio(JobConfiguration a, JobConfiguration b) {
	return calculateRatio(a) < calculateRatio(b);
}

std::unordered_map<int, int> initializeMaxRatioItemIndexPerSet(std::vector<JobConfiguration> itemsSortedByRatio) {
	std::unordered_map<int, int> initialMaxRatioItemIndexPerSet;
	for (int i = 0; i < itemsSortedByRatio.size(); i++) {
		int consideredItemSet = itemsSortedByRatio[i].getTask();
		if (initialMaxRatioItemIndexPerSet.count(consideredItemSet) == 0) {
			initialMaxRatioItemIndexPerSet[consideredItemSet] = i;
		}
	}
	return initialMaxRatioItemIndexPerSet;
}

/**
* Default builder for ResourceManagerBB
*/
ResourceManagerBB::ResourceManagerBB() : ResourceManager() {
}

ResourceManagerBB::~ResourceManagerBB(){
}

/**
* ResourceManager builder
*/
ResourceManagerBB::ResourceManagerBB(int numberOfResources, std::unordered_map<int, JobConfiguration> mapItems) : ResourceManager(numberOfResources, mapItems) {
	this->numberItems = mapItems.size();
	for (auto item : mapItems) {
		itemsSortedByRatio.push_back(item.second);
	}
	sort(itemsSortedByRatio.begin(), itemsSortedByRatio.end(), compareByRatio);
	//std::cout << "Initialisation complete" << endl;
}

int ResourceManagerBB::calculateBound(std::vector<JobConfiguration> currentComposition, std::unordered_map<int, int> maxRatioItemIndexByTask, std::unordered_set<int> setsAlreadyPresent) {
	SackComposition currentSackComposition = SackComposition(currentComposition);
	int bound = currentSackComposition.calculateTotalProfit();
	int remainingWeightInKnapSack = this->numberResources - currentSackComposition.calculateTotalWeight();
	std::vector<JobConfiguration> bestItemPerSetOrderedByRatio;
	for (auto [setNumber, index] : maxRatioItemIndexByTask) {
		if (setsAlreadyPresent.count(setNumber) == 0) {
			bestItemPerSetOrderedByRatio.push_back(itemsSortedByRatio[index]);
		}
	}
	sort(bestItemPerSetOrderedByRatio.begin(), bestItemPerSetOrderedByRatio.end(), compareByRatio);
	for (JobConfiguration item : bestItemPerSetOrderedByRatio) {
		if (item.getResources() <= remainingWeightInKnapSack) {
			bound += item.getProfit();
			remainingWeightInKnapSack -= item.getResources();
		}
		else {
			bound += remainingWeightInKnapSack * calculateRatio(item);
			remainingWeightInKnapSack = 0;
		}
	}
	return bound;
	
}

int ResourceManagerBB::calculateProfit(Node node) {
	int totalProfit = 0;
	for (auto item : node.sackComposition.getItemList()) {
		totalProfit += item.getProfit();
	}
	return totalProfit;
}

SackComposition ResourceManagerBB::solveMckp() {
	std::queue<Node> nodesToExpand;
	std::unordered_map<int, int > initialIndexMap = initializeMaxRatioItemIndexPerSet(itemsSortedByRatio);
	
	Node rootNode = Node(calculateBound(std::vector<JobConfiguration>(), initialIndexMap, std::unordered_set<int>()), 0, SackComposition(std::vector<JobConfiguration>()), initialIndexMap, std::unordered_set<int>());
	rootNode.depth = -1;
	nodesToExpand.push(rootNode);
	int bestValue = -std::numeric_limits<int>::max();
	SackComposition bestComposition = SackComposition(std::vector<JobConfiguration>());
	
	while (!nodesToExpand.empty()) {

		Node nodeConsidered = nodesToExpand.front();
		nodesToExpand.pop();
		
		//if it's a leaf node
		if (nodeConsidered.depth == itemsSortedByRatio.size() - 1) {
			if (nodeConsidered.getCurrentValue() > bestValue) {
				bestValue = nodeConsidered.getCurrentValue();
				bestComposition = nodeConsidered.sackComposition;
			}
		}

		//else it's not worth studying
		if (nodeConsidered.getBound() >= bestValue) {
			
			if (nodeConsidered.getCurrentValue() > bestValue) {
				bestValue = nodeConsidered.getCurrentValue();
				bestComposition = nodeConsidered.sackComposition;
			}

			JobConfiguration itemConsidered = itemsSortedByRatio[nodeConsidered.getDepth() + 1];
			std::unordered_map<int, int> newMaxRatioItemIndexByTask = nodeConsidered.getLastItemIndexConsideredPerSet();
			newMaxRatioItemIndexByTask[itemConsidered.getTask()] ++;

			// include itemConsidered ?
			if (nodeConsidered.getSetsAlreadyPresent().count(itemConsidered.getTask()) == 0 && nodeConsidered.getSackcomposition().getTotalWeight() + itemConsidered.getResources() <= numberResources) {
				std::vector<JobConfiguration> leftChildItemList = nodeConsidered.getSackcomposition().getItemList();
				leftChildItemList.push_back(itemsSortedByRatio[nodeConsidered.getDepth()]);
				std::unordered_set<int> newSetsAlreadyPresent = nodeConsidered.getSetsAlreadyPresent();
				newSetsAlreadyPresent.insert(itemConsidered.getTask());
				Node leftChildNode = Node(calculateBound(leftChildItemList, newMaxRatioItemIndexByTask, newSetsAlreadyPresent), nodeConsidered.getCurrentValue() + itemsSortedByRatio[nodeConsidered.getDepth() + 1].getProfit(), SackComposition(leftChildItemList), newMaxRatioItemIndexByTask, newSetsAlreadyPresent);
				leftChildNode.depth = nodeConsidered.depth + 1;
				if (leftChildNode.getBound() >= bestValue) {
					nodesToExpand.push(leftChildNode);
				}
			}
			//without including item considered
			Node rightChildNode = Node(calculateBound(nodeConsidered.getSackcomposition().getItemList(), newMaxRatioItemIndexByTask, nodeConsidered.getSetsAlreadyPresent()), nodeConsidered.getCurrentValue() + itemsSortedByRatio[nodeConsidered.getDepth() + 1].getProfit(), SackComposition(nodeConsidered.getSackcomposition().getItemList()), newMaxRatioItemIndexByTask, nodeConsidered.getSetsAlreadyPresent());
			rightChildNode.depth = nodeConsidered.depth + 1;
			if (rightChildNode.getBound() >= bestValue) {
				nodesToExpand.push(rightChildNode);
			}
			
		}
	}
	return bestComposition;
}

SackComposition ResourceManagerBB::solveMckpConcurrently() {
	return SackComposition(vector<JobConfiguration>());
}
