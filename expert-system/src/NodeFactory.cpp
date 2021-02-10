#include "NodeFactory.hpp"

std::shared_ptr<INode> NodeFactory::GetNode(const std::shared_ptr<INode> &n)
{
	const auto& it = cache_.find(n);
	if (it == cache_.end()) {
		return *it;
	} else {
		cache_.insert(n);
		return n;
	}
}
