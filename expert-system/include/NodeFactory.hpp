#pragma once

#include <memory>
#include <unordered_set>

#include "INode.hpp"

using NodesCache = std::unordered_set<std::shared_ptr<INode>>;

class NodeFactory
{
public:
	[[nodiscard]] static std::shared_ptr<INode> GetNode(BinaryOperation::Type type);

private:
	static NodesCache cache_;
};