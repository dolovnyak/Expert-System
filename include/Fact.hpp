#pragma once

#include "INode.hpp"

class Fact final : public INode {
public:
	explicit Fact(char name)
			: name_(name) {}

	void UpdateState([[maybe_unused]] std::shared_ptr<INode> sender) override {}

	void UpdateState(State state, [[maybe_unused]] std::shared_ptr<INode> sender) override {
		state_ = state;
		UpdateParents(SharedFromThis());
	}

	[[nodiscard]] char GetName() const {
		return name_;
	}

private:
	char name_;
};