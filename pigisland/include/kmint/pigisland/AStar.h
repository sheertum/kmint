#include <list>
#include <functional>
#include <map>

#include "kmint/map/map.hpp"

#define Node kmint::graph::basic_node<kmint::map::map_node_info>
#define Cost float

class AStar {
	using calculateHeuristic = std::function<Cost(const Node& node, const Node& end)>;
	//typedef kmint::graph::basic_node<map_node_info> Node;
public:
	static Cost h(const Node& node, const Node& end);
	static std::list<Node*> getPath(Node& start, Node& end, bool& found);

private:
	static std::list<Node*> constructPath(std::map<Node*, Node*>& from, Node& current);
};

