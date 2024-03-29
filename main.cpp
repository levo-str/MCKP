#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <chrono>
#include <random>

#include "Jobconfiguration.h"
#include "SackComposition.h"
#include "ResourceManagerDP.h"
#include "ResourceManagerBB.h"

auto get_time() {
	return std::chrono::high_resolution_clock::now();
}

bool hasProblem(SackComposition sackComposition) {
	std::unordered_set<int> hasId;
	for (JobConfiguration item : sackComposition.getItemList()) {
		if (hasId.count(item.getId()) == 0) {
			hasId.insert(item.getId());
		}
		else {
			return true;
		}
	}
	return false;
}

int main() {

	/*
	// TODO put this part in test file
	Item testItem = Item(1, 1, 1);
	Item secondTestItem = Item(1, 1, 1);
	cout << "Testing if ID auto-incrementation works and if object creation is possible" << endl;
	cout << testItem.getId() << endl;
	cout << secondTestItem.getId();
	*/

	// Creating the tables to solve the multiple choice knapsack problem :
	// first one classic knapsack problem
	// second one composition of the knapsack in each case
	// third one (optional) just the list ordered by increasing id of the Items
	// apply normal dynamic knapsack resolution algorithm but also test out for configurations and test out where there is already an 
	// item on the same task 

	// first sketch without creating class or anything
		//int numberItems, numberResources;
		//unordered_map<int, JobConfiguration> mapItems;
		//cout << "number of Items = number of Job configurations = ";
		//cin >> numberItems;
		//cout << endl << "number of resources we have = ";
		//cin >> numberResources;
		//cout << endl;
		//int** profitArray = new int* [numberItems + 1];

		//int r, p, t;

		//for (int i = 0; i < numberItems+1; i++) {
		//	if (i != numberItems) {
		//		cout << "Item number  " << i + 1 << " please" << endl;
		//		cout << "resources = ";
		//		cin >> r;
		//		cout << endl;
		//		//p = pow(r,i+1);
		//		cout << "profit = ";
		//		cin >> p;
		//		cout << endl;
		//		//cout << "task number = ";
		//		//cin >> t;
		//		t = 0;
		//		cout << endl;

		//		JobConfiguration item = JobConfiguration(r, p, t);
		//		cout << "item number : " << item.getId() << endl;
		//		mapItems[item.getId()] = item;
		//	}
		//	profitArray[i] = new int[numberResources + 1];
		//}

	
	std::vector<int> v(3);
	int maxCapacity = 1000;
	int maxNumberOfItems = 1025;
	
	// Set up our random number generator
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<int> dist1(maxCapacity / 3, maxCapacity);
	std::uniform_int_distribution<int> dist3(1, 3);
	//specify the number of nodes
	//specify the number of jobs running
	//calculate memory consumption
	//calculate speedup of the algorithm
	//look into other parallelization methods
	
	std::vector<long long> timesSerialDP;
	std::vector<long long> timesparallelDP;
	std::vector<long long> timesSerialBB;
	vector<int> xAxis;

	for (int numberOfitems = 5; numberOfitems < maxNumberOfItems; numberOfitems = numberOfitems*1.2) {
		std::cout << "generating values for number of items = " << numberOfitems << endl;
		long long totalTimeForSerialResolution = 0;
		long long totalTimeForParallelResolution = 0;
		long long totalTimeForBBResolution = 0;
		
		for (int testNumber = 0; testNumber < 100; testNumber++) {
			int numberOfSet = dist3(rng);
			int capacity = dist1(rng);
			std::uniform_int_distribution<int> dist2(1, capacity);
			unordered_map<int, JobConfiguration> mapItems;

			for (int itemNumber = 0; itemNumber < numberOfitems; itemNumber++) {
				std::generate(begin(v), end(v), [&]() { return dist2(rng); });
				JobConfiguration newJobConfig = JobConfiguration(v[0], v[1], v[2] % numberOfSet);
				mapItems[newJobConfig.getId()] = newJobConfig;
			}
			auto start = get_time();
			ResourceManagerDP problemSolver = ResourceManagerDP(capacity, mapItems);
			SackComposition solution = problemSolver.solveMckp();
			auto finish = get_time();
			auto duration =
				std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);
			totalTimeForSerialResolution += duration.count();


			auto parallelStart = get_time();

			ResourceManagerDP parallelProblemSolver = ResourceManagerDP(capacity, mapItems);
			SackComposition parallelSolution = parallelProblemSolver.solveMckpConcurrently();

			auto parallelFinish = get_time();

			auto parallelDuration =
				std::chrono::duration_cast<std::chrono::nanoseconds>(parallelFinish - parallelStart);
			totalTimeForParallelResolution += parallelDuration.count();
			
			auto bBstart = get_time();
			ResourceManagerBB problemSolverBB = ResourceManagerBB(capacity, mapItems);
			SackComposition solutionBB = problemSolverBB.solveMckp();

			auto bBFinish = get_time();

			auto bBDuration =
				std::chrono::duration_cast<std::chrono::nanoseconds>(bBFinish - bBstart);
			totalTimeForBBResolution += bBDuration.count();
			
			if (solutionBB.calculateTotalProfit() != solution.calculateTotalProfit()) {
				std::cout << "There is a problem" << std::endl;
				
				std::cout << solution.calculateTotalProfit() << endl;
				std::cout << solutionBB.calculateTotalProfit() << endl;
				std::cout << "knapsack :" << capacity << endl;
				std::cout << "mapItems :" << endl;
				for (auto [key, item] : mapItems) {
					std::cout << "mapItems[" << item.getId() << "] = " << "JobConfiguration(" << item.getResources() << ", " << item.getProfit() << ", " << item.getTask() << ");" << endl;
				}
				/*
				std::cout << "DP Solution : " << endl;
				for (JobConfiguration item : solution.getItemList()) {
					std::cout << item.getId() << "," << item.getResources() << "," << item.getProfit() << "," << item.getTask() << endl;
				}
				std::cout << endl;
				std::cout << "BB Solution : " << endl;
				for (JobConfiguration item : solutionBB.getItemList()) {
					std::cout << item.getId() << "," << item.getResources() << "," << item.getProfit() << "," << item.getTask() << endl;
				}
				std::cout << "mapItems" << endl;
				for (auto [key, item] : mapItems) {
					std::cout << item.getId() << "," << item.getResources() << "," << item.getProfit() << "," << item.getTask() << endl;
				}
				std::cout << endl;
				std::cout << "profitArray :" << endl;
				problemSolver.printProfitArray();
				std::cout << endl;
				*/
			}
		}
		xAxis.push_back(numberOfitems);
		timesSerialDP.push_back(totalTimeForSerialResolution);
		timesparallelDP.push_back(totalTimeForParallelResolution);
		timesSerialBB.push_back(totalTimeForBBResolution);
		
		//std::cout << "for serial execution : " << totalTimeForSerialResolution << "ms" << endl;
		//std::cout << "for parallel execution : " << totalTimeForParallelResolution << "ms" << endl;
		//std::cout << "for branch and bound execution : " << totalTimeForBBResolution << "ms" << endl;
		
	}
	for (auto value : xAxis) {
		std::cout<< value <<endl;
	}
	std::cout << endl;
	for (auto value : timesSerialDP) {
		std::cout << value << endl;
	}
	std::cout << endl;
	for (auto value : timesparallelDP) {
		std::cout << value << endl;
	}
	std::cout << endl;
	for (auto value : timesSerialBB) {
		std::cout << value << endl;
	}
	std::cout << endl;

	/*
	unordered_map<int, JobConfiguration> mapItems;
	mapItems[1] = JobConfiguration(4, 4, 1);
	mapItems[2] = JobConfiguration(5, 3, 1);
	mapItems[3] = JobConfiguration(7, 4, 1);
	mapItems[4] = JobConfiguration(3, 9, 1);
	mapItems[5] = JobConfiguration(3, 9, 2);
	mapItems[6] = JobConfiguration(7, 12, 2);
	mapItems[7] = JobConfiguration(6, 8, 3);
	mapItems[8] = JobConfiguration(8, 4, 3);
	mapItems[9] = JobConfiguration(3, 3, 4);
	mapItems[10] = JobConfiguration(8, 4, 4);
	mapItems[11] = JobConfiguration(6, 8, 4);
	mapItems[12] = JobConfiguration(10, 12, 4);
	*/
	
	/*
	std::unordered_map<int, JobConfiguration> mapItems;
	mapItems[1] = JobConfiguration(3, 3, 0);
	mapItems[2] = JobConfiguration(4, 5, 0);
	mapItems[3] = JobConfiguration(1, 4, 1);
	mapItems[4] = JobConfiguration(3, 5, 1);
	mapItems[5] = JobConfiguration(3, 4, 2);

	auto start = get_time();
	ResourceManagerDP problemSolver = ResourceManagerDP(7, mapItems);
	ResourceManagerBB problemSolverBB = ResourceManagerBB(7, mapItems);
	SackComposition solution = problemSolver.solveMckp();
	SackComposition solutionBB = problemSolverBB.solveMckp();
	int** profitArray = problemSolver.getProfitArray();
	auto finish = get_time();
	std::cout << endl << "Sack composition is : " << endl;
	for (auto item : solution.getItemList()) {
		std::cout << item.getId() << ",";
	}
	problemSolver.printProfitArray();
	auto duration =
		std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
	std::cout << "Elapsed time = " << duration.count() << " ms\n";
	*/

	/*
	for (int i = 0; i < 1; i++) {
		unordered_map<int, JobConfiguration> mapItems;
		mapItems[1] = JobConfiguration(5, 4, 0);
		mapItems[2] = JobConfiguration(8, 5, 0);
		mapItems[3] = JobConfiguration(7, 1, 2);
		mapItems[4] = JobConfiguration(10, 10, 1);
		mapItems[5] = JobConfiguration(6, 7, 1);
		mapItems[6] = JobConfiguration(3, 7, 1);
		mapItems[7] = JobConfiguration(3, 2, 0);
		mapItems[8] = JobConfiguration(10, 1, 0);
		mapItems[9] = JobConfiguration(9, 2, 0);
		mapItems[10] = JobConfiguration(5, 2, 1);

		auto start = get_time();
		ResourceManagerDP problemSolver = ResourceManagerDP(20, mapItems);
		ResourceManagerBB problemSolverBB = ResourceManagerBB(20, mapItems);
		SackComposition solution = problemSolver.solveMckp();
		SackComposition solutionBB = problemSolverBB.solveMckp();
		if (solutionBB.getTotalProfit() != solution.getTotalProfit()) {
			cout << "there is a problem" << endl;
		}
	}
	*/
	/*
	unordered_map<int, JobConfiguration> mapItems;
	mapItems[1] = JobConfiguration(10, 9, 0);
	mapItems[2] = JobConfiguration(8, 8, 0);
	mapItems[3] = JobConfiguration(5, 8, 1);
	mapItems[4] = JobConfiguration(9, 1, 2);
	mapItems[5] = JobConfiguration(6, 6, 0);

	auto start = get_time();
	ResourceManagerDP problemSolver = ResourceManagerDP(10, mapItems);
	ResourceManagerBB problemSolverBB = ResourceManagerBB(10, mapItems);
	SackComposition solution = problemSolver.solveMckp();
	SackComposition solutionBB = problemSolverBB.solveMckp();
	int** profitArray = problemSolver.getProfitArray();
	auto finish = get_time();
	cout << endl << "Sack composition is : " << endl;
	for (auto item : solution.getItemList()) {
		cout << item.getId() << ",";
	}
	cout << endl << "BB Sack composition is : " << endl;
	for (auto item : solutionBB.getItemList()) {
		cout << item.getId() << ",";
	}
	auto duration =
	std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
	std::cout << "Elapsed time = " << duration.count() << " ms\n";
 
	return 0;
	*/
}
