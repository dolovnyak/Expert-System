#include "Graph.hpp"

std::shared_ptr<INode> Graph::FindNode(const std::string &str) {
	return cache_.contains(str) ? cache_.at(str) : nullptr;
}

void Graph::AddNode(const std::string &str, std::shared_ptr<INode> &node) {
	cache_[str] = node;
}
