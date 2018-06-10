#pragma once
#include <iostream>
#include <vector>
#include <atomic>
#include <memory>
using namespace std;

struct Node
{
	int data;
	vector<shared_ptr<Node>> next;
	bool deleted = false;
	Node(int, int);
	//Node(const Node&);
};

class SkipList
{
public:
	SkipList(double, int);
	SkipList(const SkipList&);
	/*SkipList(const SkipList&) = delete;

	SkipList& operator=(const SkipList&) = delete;*/


	bool insert(int);
	bool remove(int);
	void print();
	Node *find(int);
	bool findAndFill(int, vector<shared_ptr<Node>>&, vector<shared_ptr<Node>>&);

	bool add(int);

//	bool find(int, vector<atomic<Node*>> &, vector<atomic<Node*>> &);

	int randomLevel();
private:
	shared_ptr<Node> head;
	shared_ptr<Node> NIL;
	double probability;
	int maxLevel;
};