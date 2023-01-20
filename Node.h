#pragma once
#include<vector>
#include"NodeValue.h"
//#include"resourceManagerBB.h"

class Node
{
public:
	Node* left;
	Node* right;
	int level;
	bool isLeaf;

	Node(NodeValue v) : id(current_id++) {
		val = v;
		left = nullptr;
		right = nullptr;
		isLeaf = false;
	};
	Node(const Node& t) {
	}
	Node& operator=(const Node& t)
	{
		return *this;
	}
	Node() {};
	int getNodeId() { return id; };

private:
	NodeValue val;
	uint32_t id;
	static atomic_uint32_t current_id; // added
	//friend class ResourceManagerBB;

};
