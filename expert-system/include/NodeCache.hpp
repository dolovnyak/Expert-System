#pragma once

#include <memory>
#include <map>

#include "Node.hpp"

#include "Fact.hpp"
#include "UnaryOperation.hpp"
#include "BinaryOperation.hpp"

class NodeCache
{
public:
	[[nodiscard]] static std::shared_ptr<INode> FindNode(const std::string &str);
	static void AddNode(const std::string &str, std::shared_ptr<INode> &node);

private:
	static std::map<std::string, std::shared_ptr<INode>> cache_;
};