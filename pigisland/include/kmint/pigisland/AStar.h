#include <list>
#include <functional>


template<class Queue, class Node, class Cost>
class AStar {
	using calculateHeuristic = std::function<Cost(const Node& node, const Node& end)>;
	
public:
	static Cost defaultCalculateHearistic(const Node& node, const Node& end);
	static std::list<Node> getPath(const Node& start, const Node& end, bool& found, calculateHeuristic const& h = defaultCalculateHearistic);

private:
	static std::list<Node> constructPath(const std::list<Node>& from, const Node& current);
};

