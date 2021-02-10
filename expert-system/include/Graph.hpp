#pragma once

#include <memory>
#include <map>

#include "Node.hpp"

#include "Fact.hpp"
#include "UnaryOperation.hpp"
#include "BinaryOperation.hpp"

class Graph
{
public:
	[[nodiscard]] static std::shared_ptr<INode> FindNode(const std::string &str) {
		return cache_.contains(str) ? cache_.at(str) : nullptr;
	}

	static void AddNode(const std::string &str, std::shared_ptr<INode> &node) {
		cache_.insert(std::pair(str, node));
	}

private:
	static std::map<std::string, std::shared_ptr<INode>> cache_;
};