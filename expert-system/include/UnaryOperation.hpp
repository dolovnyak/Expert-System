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

public:
	size_t GetHash() override {
		return static_cast<int>(type_) * child_->GetHash();
	}

	bool Equals(const std::shared_ptr<INode> &n) override {
		std::shared_ptr<UnaryOperation> ruo = std::dynamic_pointer_cast<UnaryOperation>(n);
		return ruo != nullptr
			&& GetType() == ruo->GetType()
			&& GetChild()->Equals(ruo->GetChild());
	}

private:
	Type type_;
	std::shared_ptr<INode> child_;
};