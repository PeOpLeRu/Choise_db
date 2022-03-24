#pragma once

#include <set>
#include <string>

using namespace std;

class Node
{

public:

	Node(const string& aname)
	{
		this->name = aname;
	}

	Node(const char* aname)
	{
		this->name = string(aname);
	}

	Node(const Node& node)
	{
		this->name = node.name;
	}

	bool is_end() const
	{
		return this->yes == nullptr && this->no == nullptr;
	}

	const string getName() const
	{
		return this->name;
	}

	std::set<Node*>::const_iterator neighbours_begin() const
	{
		return this->neighbours.begin();
	}

	std::set<Node*>::const_iterator neighbours_end() const
	{
		return this->neighbours.end();
	}

	~Node()
	{
		neighbours.clear();
	}

	Node* yes;
	Node* no;
private:

	std::set<Node*> neighbours;
	std::string name;

	void addNeigbours(Node* neighbour)
	{
		if (!neighbour)
			return;

		this->neighbours.insert(neighbour);

		return;
	}

	void removeNeigbours(Node* neighbour)
	{
		if (!neighbour)
			return;

		this->neighbours.erase(neighbour);

		return;
	}

	friend class Graph;
};