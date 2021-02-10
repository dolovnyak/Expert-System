#pragma once

#include "Node.hpp"

class UnaryOperation final : public INode {
public:
	enum Type {
		Not
	};

	explicit UnaryOperation(Type type, std::shared_ptr<INode> child)
			: type_(type) {
		if (child == nullptr) {
			throw std::logic_error("Child is null.");
		}

		child_ = std::move(child);
	}

	State EvaluateState() override {
		State s = child_->EvaluateState();
		if (s == Undetermined) {
			return Undetermined;
		}

		switch (type_) {
			case Not:
				return (s == False) ? True : False;
			default:
				throw std::logic_error("Unknown binary operation type.");
		}
	}

	[[nodiscard]] Type GetType() const {
		return type_;
	}

	[[nodiscard]] const std::shared_ptr<INode> &GetChild() const {
		return child_;
	}

private:
	Type type_;
	std::shared_ptr<INode> child_;
};