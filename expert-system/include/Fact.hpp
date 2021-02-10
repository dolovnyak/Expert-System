#pragma once

#include "Node.hpp"

class Fact final : public INode {
public:
	explicit Fact(char name)
			: state_(Undetermined),
			  name_(name) {}

	State EvaluateState() override {
		return state_;
	}

	[[nodiscard]] char GetName() const {
		return name_;
	}

public:
	size_t GetHash() override {
		return static_cast<size_t>(name_);
	}

	bool Equals(const std::shared_ptr<INode> &n) override {
		std::shared_ptr<Fact> rf = std::dynamic_pointer_cast<Fact>(n);
		return rf != nullptr
			   && GetName() == rf->GetName();
	}

private:
	INode::State state_;
	char name_;
};