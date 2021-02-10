#pragma once

#include <memory>
#include <unordered_set>

#include "Node.hpp"
#include "NodeComparator.hpp"
#include "NodeHashComparator.hpp"

#include "Fact.hpp"
#include "UnaryOperation.hpp"
#include "BinaryOperation.hpp"

using NodesCache = std::unordered_set<std::shared_ptr<INode>, NodeHashComparator, NodeComparator>;

class NodeFactory
{
public:
	[[nodiscard]] static std::shared_ptr<INode> GetNode(const std::shared_ptr<INode>& n);

private:
	static NodesCache cache_;
};