#include "skipList.h"
#include <iostream>
#include <atomic>
#include <ctime>
using namespace std;


Node::Node(int data, int level)
{
	this->data = data;
	next.resize(level);
}

//Node::Node(const Node& origin)
//{
//	data = origin.data;
//	next = origin.next;
//}

SkipList::SkipList(double prob, int maxLev)
{
	probability = prob;
	maxLevel = maxLev;

	head = make_shared<Node>(numeric_limits<int>::min(), maxLevel);
	NIL = make_shared<Node>(numeric_limits<int>::max(), maxLevel);
	
	for (int i = 0; i < head->next.size(); i++)
	{
		head->next[i] = NIL;
	}
}

//SkipList::SkipList(const SkipList& origin)
//{
//	head = origin.head.load(memory_order_relaxed);
//	NIL = origin.NIL.load(memory_order_relaxed);
//}
//
//Node *SkipList::find(int search)
//{
//	Node *node = head;
//	for (int i = maxLevel - 1; i >= 0; i--)
//	{
//		while (node->next[i].load(memory_order_relaxed) != nullptr && node->next[i].load(memory_order_relaxed)->data < search)
//		{
//			node = node->next[i];
//		}
//	}
//
//	node = node->next[0];
//
//	if (node->data == search)
//	{
//		return node;
//	}
//	return NULL;
//}
//

int SkipList::randomLevel()
{
	
	int level = 1;
	while (((double)rand() / RAND_MAX) < probability && level < maxLevel)
	{
		level++;
	}
	return level;
}

bool SkipList::findAndFill(int fnd, vector<shared_ptr<Node>> &preds, vector<shared_ptr<Node>> &succs)
{
	shared_ptr<Node> pred;
	shared_ptr<Node> curr;
	shared_ptr<Node> succ;
	bool flag;
	preds.resize(maxLevel);
	succs.resize(maxLevel);
	while (true)
	{
		flag = true;
		pred = head;
		for (int i = maxLevel - 1; i >= 0 && flag; i--)
		{
	
			curr = pred->next[i];
			while (curr != nullptr &&curr->deleted)
			{
				curr = curr->next[i];
			}

			if (curr == NIL)
			{
				preds[i] = pred;
				succs[i] = curr;
				continue;
			}
			while (flag)
			{
				succ = curr->next[i]; 
				while (succ != nullptr && succ->deleted)
				{
					succ = succ->next[i];
				}
				//flag =pred.load(memory_order_relaxed)->next[i].load(memory_order_relaxed);
				flag = atomic_compare_exchange_weak_explicit(&pred->next[i], &curr, pred->next[i], memory_order_release, memory_order_relaxed);
				if (!flag)
				{
					continue;
				}
				curr = pred->next[i];
				while (curr != nullptr && curr->deleted)
				{
					curr = curr->next[i];
				}
				succ = curr->next[i];
				while (succ != nullptr && succ->deleted)
				{
					succ = succ->next[i];
				}
				if (curr->data < fnd)
				{
					pred = curr;
					curr = succ;
				}
				else
				{
					break;
				}
			}
			if (flag)
			{
				preds[i] = pred;
				succs[i] = curr;
			}
		}
		if (flag)
		{
			return (curr->data == fnd) && !curr->deleted;
		}
	}
}



bool SkipList::insert(int ins)
{
	/*atomic<Node *> node = find(ins);

	if (node.load(memory_order_relaxed))
	{
		cout << "Element is already exists" << endl;
		return ;
	}*/
	vector<shared_ptr<Node>> preds;
	vector<shared_ptr<Node>> succs;
	bool isExists;
	while (true)
	{
		isExists = findAndFill(ins, preds, succs);
		if (isExists)
		{
			return false;
		}
		else
		{
			int rndLevel = randomLevel();
			auto newNode = make_shared<Node>(ins, rndLevel);

			shared_ptr<Node>succ;
			shared_ptr<Node>pred;
			for (int i = 0; i < rndLevel; i++)
			{
				succ = succs[i];
				newNode->next[i] = succ;
			}
			succ = succs[0];
			pred = preds[0];
			if (!atomic_compare_exchange_weak_explicit(&pred->next[0], &succ, newNode, memory_order_release, memory_order_relaxed))
			{
				continue;
			}
			for (int i = 1; i < rndLevel; i++)
			{
				while (true)
				{
					pred = preds[i];
					succ = succs[i];
					if (atomic_compare_exchange_weak_explicit(&pred->next[i], &succ, newNode, memory_order_release, memory_order_relaxed))
					{
						break;
					}
					findAndFill(ins, preds, succs);
				}
			}
			return true;

			//update = head.load(memory_order_relaxed)->next;
			//node = head.load(memory_order_relaxed);
			//for (int i = maxLevel - 1; i >= 0; i--)
			//{
			//	while (node.load(memory_order_relaxed)->next[i].load(memory_order_relaxed) != NULL
			//		&& node.load(memory_order_relaxed)->next[i].load(memory_order_relaxed)->data < ins
			//		/*&& !atomic_compare_exchange_weak_explicit(&node, &(node.load(memory_order_relaxed)->next[i]), head,  memory_order_release, memory_order_relaxed)
			//		*/)
			//	{
			//		node = node.load(memory_order_relaxed)->next[i].load(memory_order_relaxed);
			//	}
			//	update[i] = node.load(memory_order_relaxed);
			//}

			//node = node.load(memory_order_relaxed)->next[0].load(memory_order_relaxed);


			//int rndLvl = randomLevel();
			///*if (node.load(memory_order_relaxed)->data != ins)
			//{

			//}*/
			//node = new Node(ins, rndLvl);
			//for (int i = 0; i < rndLvl; i++)
			//{
			//	node.load(memory_order_relaxed)->next[i] = update[i].load(memory_order_relaxed)->next[i].load(memory_order_relaxed);
			//}

			//update[i]->next[i] = node.load(memory_order_relaxed);
		}
	}
}


//bool SkipList::find(int fnd, vector<atomic<Node*>> &predc, vector<atomic<Node*>> &succs)
//{
//	compare
//	atomic<Node*> curr, pred, succ;
//	while (true)
//	{
//		pred = head;
//
//	}
//}



bool SkipList::remove(int rmv)
{
	vector<shared_ptr<Node>> preds;
	vector<shared_ptr<Node>> succs;
	shared_ptr<Node> succ;
	shared_ptr<Node> pred;
	bool isExists;
	while (true)
	{

		isExists = findAndFill(rmv, preds, succs);
		if (!isExists)
		{
			return false;
		}
		else
		{
			shared_ptr<Node> nodeToRemove = succs[0];
			nodeToRemove->deleted = true;
			
			succ = nodeToRemove->next[0];
			for (int i = nodeToRemove->next.size() - 1; i >= 0; i--)
			{
				while (true)
				{
					pred = preds[i];
					succ = nodeToRemove->next[i];
					if (atomic_compare_exchange_weak_explicit(&pred->next[i], &nodeToRemove, succ, memory_order_release, memory_order_relaxed))
					{
						break;
					}
					findAndFill(rmv, preds, succs);
				}
			}
			//delete nodeToRemove.get();
			return true;
		}
	}
}





void SkipList::print()
{
	shared_ptr<Node> node = head;
	node = node->next[0];
	cout << "---------head---------" << endl;
	while (node != NIL)
	{
			for (int i = 0; i < node->next.size(); i++)
			{
				cout << "v ";
			}
			for (int i = node->next.size(); i < maxLevel; i++)
			{
				cout << "| ";
			}
			cout << endl;
		for (int i = 0; i < node->next.size(); i++)
		{
			cout << node->data << " ";
		}
		for (int i = node->next.size(); i < maxLevel; i++)
		{
			cout << "| ";
		}
		cout << endl;
		
		node = node->next[0];
	}
	for (int i = 0; i < maxLevel; i++)
	{
		cout << "v ";
	}
	cout << "\n---------NIL---------" << endl;
}