#pragma once

#include "Node.hpp"

struct NodeHashComparator {
public:
	size_t operator()(const std::shared_ptr<INode> &node) const {
		return node->GetHash();
	}
};