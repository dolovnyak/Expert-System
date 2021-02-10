#include "NodeCache.hpp"

std::shared_ptr<INode> NodeCache::FindNode(const std::string &str) {
	return cache_.contains(str) ? cache_.at(str) : nullptr;
}

void NodeCache::AddNode(const std::string &str, std::shared_ptr<INode> &node) {
	cache_[str] = node;
}
