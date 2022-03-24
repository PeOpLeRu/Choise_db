#pragma once

#include <set>
#include <fstream>

using namespace std;

#include "Node.h"

class Graph
{
public:

	Graph()
	{

	}

	void addNode(Node* node)
	{
		nodes.insert(node);

		return;
	}

	void addNode(Node node)
	{
		Node* node_ptr = new Node(node);

		nodes.insert(node_ptr);

		return;
	}

	void addNode(string& name)
	{
		Node* node = new Node(name);

		nodes.insert(node);

		return;
	}

	void addNode(const char* name)
	{
		Node* node = new Node(string(name));

		nodes.insert(node);

		return;
	}

	void removeNode(Node* node)
	{
		nodes.erase(node);

		for (auto it = nodes.begin(); it != nodes.end(); ++it)
		{
			(*it)->removeNeigbours(node);
		}

		return;
	}

	void addEdge(Node* begin, Node* end)
	{
		if (nodes.find(begin) == nodes.end())
			return;

		if (nodes.find(end) == nodes.end())
			return;

		begin->addNeigbours(end);
		end->addNeigbours(begin);

		return;
	}

	void removeEdge(Node* begin, Node* end)
	{
		if (nodes.find(begin) == nodes.end())
			return;

		if (nodes.find(end) == nodes.end())
			return;

		begin->removeNeigbours(end);
		end->removeNeigbours(begin);

		return;
	}

	~Graph()
	{
		for (auto it = nodes.begin(); it != nodes.end(); ++it)
		{
			(*it)->~Node();
		}

		nodes.clear();
	}

	void full_clear()
	{

	}

	bool in(const string& name) const
	{
		for (auto i = nodes.begin(); i != nodes.end(); ++i)
		{
			if ((*i)->name == name)
				return true;
		}

		return false;
	}

	Node* find(string& name)
	{
		for (auto i = nodes.begin(); i != nodes.end(); ++i)
		{
			if ((*i)->name == name)
				return *i;
		}

		return nullptr;
	}

	bool empty()
	{
		if (nodes.size())
			return false;
		else
			return true;
	}

	string split(const string& source, const char separator, short part)
	{
		int index(0);

		for (int i = 0; i < source.length(); i++)
		{
			if (source[i] == separator)
			{
				index = i;
				break;
			}
		}

		return part == 1 ? string(source.begin(), source.begin() + index) : string(source.begin() + index + 1, source.end());
	}

	friend ifstream& operator>>(ifstream& in, Graph& graph)
	{
		string row, temp_name_1, temp_name_2;

		while (!in.eof())
		{
			std::getline(in, row);
			temp_name_1 = graph.split(row, '|', 1);
			temp_name_2 = graph.split(row, '|', 2);

			if (!graph.in(temp_name_1))
				graph.addNode(temp_name_1);

			if (!graph.in(temp_name_2))
				graph.addNode(temp_name_2);

			graph.find(temp_name_1)->yes == nullptr ? graph.find(temp_name_1)->yes = graph.find(temp_name_2) : graph.find(temp_name_1)->no = graph.find(temp_name_2);
			graph.addEdge(graph.find(temp_name_1), graph.find(temp_name_2));
		}

		return in;
	}

	friend ofstream& operator<<(ofstream& out, Graph& graph)
	{
		while (!graph.empty())
		{
			auto it = graph.begin();
			for (auto i = (*it)->neighbours_begin(); i != (*it)->neighbours_end(); ++i)
			{
				out << (*it)->getName() << "|" << (*i)->getName() << endl;
			}
			graph.removeNode(*it);
		}

		return out;
	}

	std::set<Node*>::const_iterator begin()
	{
		return nodes.begin();
	}

	std::set<Node*>::const_iterator end()
	{
		return nodes.end();
	}

private:

	std::set<Node*> nodes;
};