#pragma once

#include <queue>
#include <map>
#include <functional>

template<class Key, class Value>
class PriorityMap {
public:
	using pair = struct { Key key; Value value; };
	using compare = std::function<bool(const pair&, const pair&)>;

	PriorityMap(compare cmp = defaultCompare) : _queue{ cmp } {};

	static bool defaultCompare(const pair& left, const pair& right);

	bool exists(Key) const;

	void push(Key key, const Value& value);

	//pair top() const;
	void pop();

	pair top() {
		return _queue.top();
	}

	bool empty() const;

private:
	std::priority_queue<pair, std::vector<pair>, compare> _queue;
	std::map<Key, Value> _map;
};

template<class Key, class Value>
inline bool PriorityMap<Key, Value>::defaultCompare(const pair& left, const pair& right)
{
	return left.value > right.value;
}

template<class Key, class Value>
inline bool PriorityMap<Key, Value>::exists(Key key) const
{
	return _map.find(key) != _map.end();
}

template<class Key, class Value>
void PriorityMap<Key, Value>::push(Key key, const Value& value)
{
	_map[key] = value;
	_queue.push(pair{ key,value });
}

//template<class Key, class Value>
//inline Value PriorityMap<Key, Value>::top() const
//{
//	return _queue.top();
//}

template<class Key, class Value>
inline void PriorityMap<Key, Value>::pop()
{
	_map.erase(_queue.top().key);
	_queue.pop();
}


template<class Key, class Value>
inline bool PriorityMap<Key, Value>::empty() const
{
	return _queue.empty();
}
