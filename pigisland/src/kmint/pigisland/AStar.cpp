#include "kmint/pigisland/AStar.h"

#include <map>
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

template<class Queue, class Node, class Cost>
std::list<Node> AStar<Queue, Node, Cost>::getPath(const Node& start, const Node& end, bool& found, calculateHeuristic const& h)
{
	found = false;
	std::set<std::pair<Node, Cost>, comp> open;
	std::list<Node> from;
	open.insert(start);

	std::map<Node, Cost> gScore;
	std::map<Node, Cost> fScore;

	gScore[start] = 0;
	fScore[start] = h(start, end);

	while (!open.empty()) {
		Node current = open.front();

		if (current == end) {
			found = true;
			return constructPath(from, current);
		}

		open.pop_front();

		for (size_t i = 0; i < current.num_edges(); i++)
		{
			Node neighbour = current[i].to();
			scoreToNeighbour = gScore[current] + current[i].to().weight();

			Cost scoreNeighbour = (gScore.find(neighbour) != gScore.end()) ? gScore[neighbour] : std::numeric_limits<Cost>::infinity();
			if (scoreToNeighbour < scoreNeighbour) {
				from[neighbour] = current;
				gScore[neighbour] = scoreToNeighbour;
				fScore[neighbour] = scoreToNeighbour + h(neighbour, end);
				if (open.find(neighbour) == open.end()) {
					open.insert(neighbour);
				}
			}
		}
	}

	return std::list<Node>{start};
}

template<class Queue, class Node, class Cost>
Cost AStar<Queue, Node, >::defaultCalculateHearistic(const Node& node, const Node& end)
{
	Cost x = std::abs(node.location().x() - end.location().x());
	Cost y = std::abs(node.location().y() - end.location().y());

	return x + y;
}

template<class Queue, class Node, class Cost>
std::list<Node> AStar<Queue, Node, Cost>::constructPath(const std::list<Node>& from, const Node& current)
{
	std::list<Node> path;
	path.push_back(current);
	current.
	while (from.find(current) != from.end()) {
		current = from[current];
		path.push_back(current);
	}

	return path;
}
