#pragma once

#include "NodeComparator.hpp"

struct NodeComparator {
public:
	size_t operator()(const std::shared_ptr<INode> &firstNode, const std::shared_ptr<INode> &secondNode) const {
		return firstNode->Equals(secondNode);
	}
};