#pragma once

#include <ExpertSystem.hpp>

#include "Expression.hpp"

enum BinaryOperator {
	AND = 0,
	OR,
	XOR,
	IMPLIES,
	MUTUAL_IMPLIES
};

class BinaryExpression : public Expression {
public:
	BinaryExpression(Expression *left, BinaryOperator binaryOperator, Expression *right);

	Expression *Find(Expression *expression) override;

	[[nodiscard]] std::string ToString() const override;

	[[nodiscard]] ExpressionType GetType() const override;
	
	bool operator==(const Expression &expression) const override;

	bool operator!=(const Expression &expression) const override;

	[[nodiscard]] const std::shared_ptr<Expression> &GetLeftChild() const { return left_child_; }
	
	[[nodiscard]] BinaryOperator GetBinaryOperator() const;

	[[nodiscard]] const std::shared_ptr<Expression> &GetRightChild() const { return right_child_; }

	void Calculate(ExpertSystemData &expert_system_data) override;

protected:
	void UpdateState(State state) override;

private:
    std::shared_ptr<Expression> left_child_;
    std::shared_ptr<Expression> right_child_;
	BinaryOperator binary_operator_;
	
	[[nodiscard]] static std::string GetString(BinaryOperator binaryOperator) ;
};

















//class BinaryOperation final : public INode {
//public:
//	enum Type {
//		And,
//		Or,
//		Xor,
//		Implication,
//		Equivalence
//	};
//
//	BinaryOperation(Type type, std::shared_ptr<INode> left_child, std::shared_ptr<INode> right_child)
//			: type_(type) {
//		if (left_child == nullptr) {
//			throw std::logic_error("Left child is null.");
//		} else if (right_child == nullptr) {
//			throw std::logic_error("Right child is null.");
//		}
//
//		left_child_ = std::move(left_child);
//		right_child_ = std::move(right_child);
//	}
//
//	void UpdateState(std::shared_ptr<INode> sender) override {
//		std::shared_ptr<INode> child_to_update = sender == left_child_ ? right_child_ : left_child_;
//
//		State new_state;
////		State new_child_state;
//		switch (type_) {
//			case And:
//				new_state = ApplyAndOperation(left_child_->GetState(), right_child_->GetState());
////				new_child_state = new_state
//				break;
//			case Or:
//				new_state = ApplyOrOperation(left_child_->GetState(), right_child_->GetState());
//				break;
//			case Xor:
//				new_state = ApplyXorOperation(left_child_->GetState(), right_child_->GetState());
//				break;
//			case Implication:
//				new_state = ApplyImplicationOperation(left_child_->GetState(), right_child_->GetState());
//				break;
//			case Equivalence:
//				new_state = ApplyEquivalenceOperation(left_child_->GetState(), right_child_->GetState());
//				break;
//		}
//
//		if (static_cast<int>(new_state) > static_cast<int>(state_)) {
//			state_ = new_state;
//			UpdateParents(sender);
//		}
//	}
//
//	void UpdateState(State state, std::shared_ptr<INode> sender) override {
//		std::shared_ptr<INode> child_to_update = sender == left_child_ ? right_child_ : left_child_;
//
//		state_ = state;
//		State new_state;
////		State new_child_state;
//		switch (type_) {
//			case And:
//				new_state = ApplyAndOperation(left_child_->GetState(), right_child_->GetState());
////				new_child_state = new_state
//				break;
//			case Or:
//				new_state = ApplyOrOperation(left_child_->GetState(), right_child_->GetState());
//				break;
//			case Xor:
//				new_state = ApplyXorOperation(left_child_->GetState(), right_child_->GetState());
//				break;
//			case Implication:
//				new_state = ApplyImplicationOperation(left_child_->GetState(), right_child_->GetState());
//				break;
//			case Equivalence:
//				new_state = ApplyEquivalenceOperation(left_child_->GetState(), right_child_->GetState());
//				break;
//		}
//
//		if (static_cast<int>(new_state) > static_cast<int>(state_)) {
//			state_ = new_state;
//			UpdateParents(sender);
//		}
//	}
//
//	[[nodiscard]] Type GetType() const {
//		return type_;
//	}
//
//	[[nodiscard]] const std::shared_ptr<INode> &GetLeftChild() const {
//		return left_child_;
//	}
//
//	[[nodiscard]] const std::shared_ptr<INode> &GetRightChild() const {
//		return right_child_;
//	}
//
//private:
//	Type type_;
//	std::shared_ptr<INode> left_child_;
//	std::shared_ptr<INode> right_child_;
//
//	State ApplyAndOperation(State lhs, State rhs) {
//		if (lhs == True && rhs == True) {
//			return True;
//		} else if (lhs == False && rhs == False) {
//			return False;
//		}
//		return Undetermined;
//	}
//
//	State ApplyOrOperation(State lhs, State rhs) {
//		if (lhs == True || rhs == True) {
//			return True;
//		} else if (lhs == Undetermined || rhs == Undetermined) {
//			return Undetermined;
//		}
//		return False;
//	}
//
//	State ApplyXorOperation(State lhs, State rhs) {
//		if ((lhs == True && rhs == False) || (lhs == False && rhs == True)) {
//			return True;
//		} else if ((lhs == True && rhs == True) || (lhs == False && rhs == False)) {
//			return False;
//		}
//		return Undetermined;
//	}
//
//	State ApplyImplicationOperation(State lhs, State rhs) {
//		if (rhs == True) {
//			return True;
//		} else if (lhs == True && rhs == False) {
//			return False;
//		}
//		return Undetermined;
//	}
//
//	State ApplyEquivalenceOperation(State lhs, State rhs) {
//		if ((lhs == True && rhs == True) || (lhs == False && rhs == False)) {
//			return True;
//		} else if ((lhs == True && rhs == False) || (lhs == False && rhs == True)) {
//			return False;
//		}
//		return Undetermined;
//	}
//};
