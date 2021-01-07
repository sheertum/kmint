#include "kmint/pigisland/AStar.h"
#include "kmint/pigisland/PriorityMap.hpp"

#include <vector>
#include<queue>
#include <set>

struct comp
{
	template<typename T>
	bool operator()(const T& l, const T& r) const
	{
		if (l.second != r.second)
			return l.second < r.second;

		return l.first < r.first;
	}
};

std::list<Node*> AStar::getPath(Node& start, Node& end, bool& found)
{
	found = false;

	PriorityMap<Node*,Cost> open;

	std::map<Node*, Node*> from;
	open.push(&start, 0);

	std::map<Node*, Cost> gScore;
	std::map<Node*, Cost> fScore;

	gScore[&start] = 0;
	fScore[&start] = h(start, end);

	while (!open.empty()) {
		Node& current = *open.top().key;
		current.tag(kmint::graph::node_tag::path);
		if (&current == &end) {
			found = true;
			return constructPath(from, current);
		}

		open.pop();

		for (size_t i = 0; i < current.num_edges(); i++)
		{
			Node& neighbour = current[i].to();
			Cost scoreToNeighbour = gScore[&current] + current[i].weight();

			Cost scoreNeighbour = (gScore.find(&neighbour) != gScore.end()) ? gScore[&neighbour] : std::numeric_limits<Cost>::infinity();
			if (scoreToNeighbour < scoreNeighbour) {
				from[&neighbour] = &current;
				gScore[&neighbour] = scoreToNeighbour;
				fScore[&neighbour] = scoreToNeighbour + h(neighbour, end);
				if (!open.exists(&neighbour)) {
					open.push(&neighbour, fScore[&neighbour]);
				}
			}
		}
	}

	return std::list<Node*>{&start};
}

Cost AStar::h(const Node& node, const Node& end)
{
	Cost x = std::abs(node.location().x() - end.location().x());
	Cost y = std::abs(node.location().y() - end.location().y());

	return x + y;
}

std::list<Node*> AStar::constructPath(std::map<Node*,Node*>& from, Node& current)
{
	Node* temp = &current;
	std::list<Node*> path;
	path.push_back(temp);
	
	while (from.find(temp) != from.end()) {
		temp = from[temp];
		path.push_back(temp);
	}

	return path;
}
