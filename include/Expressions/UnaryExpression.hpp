#pragma once

#include "Expressions/Expression.hpp"

enum UnaryOperator
{
	NOT = 0
};

class UnaryExpression : public Expression
{
public:
	UnaryExpression(UnaryOperator unaryOperator, Expression* expression);
	
	Expression* Find(Expression* expression) override;
	std::string ToString() const override;
	ExpressionType GetType() const override;
	bool operator==(const Expression& expression) const override;
	bool operator!=(const Expression& expression) const override;

	[[nodiscard]] Expression *GetChild() const { return expression_; }
	
private:
	Expression *expression_;
	UnaryOperator unary_operator_;
	
	std::string UnaryOperatorToString(UnaryOperator unaryOperator) const;
};

//class UnaryOperation final : public INode {
//public:
//	enum Type {
//		Not
//	};
//
//	explicit UnaryOperation(Type type, std::shared_ptr<INode> child)
//			: type_(type) {
//		if (child == nullptr) {
//			throw std::logic_error("Child is null.");
//		}
//
//		child_ = std::move(child);
//	}
//
//	void UpdateState(std::shared_ptr<INode> sender) override {
//		State new_state;
//		switch (type_) {
//			case Not:
//				new_state = ApplyNotOperation(child_->GetState());
//		}
//
//		if (static_cast<int>(new_state) > static_cast<int>(state_)) {
//			state_ = new_state;
//			UpdateParents(sender);
//		}
//	}
//
//	void UpdateState(State state, std::shared_ptr<INode> sender) override {
//		state_ = state;
//
//		State new_child_state;
//		switch (type_) {
//			case Not:
//				new_child_state = ApplyNotOperation(state_);
//		}
//
//		if (static_cast<int>(new_child_state) > static_cast<int>(child_->GetState())) {
//			child_->UpdateState(new_child_state, SharedFromThis());
//		}
//
//		UpdateParents(sender);
//	}
//
//	[[nodiscard]] Type GetType() const {
//		return type_;
//	}
//
//	[[nodiscard]] const std::shared_ptr<INode> &GetChild() const {
//		return child_;
//	}
//
//private:
//	Type type_;
//	std::shared_ptr<INode> child_;
//
//	static State ApplyNotOperation(State state) {
//		switch (state) {
//			case False:
//				return True;
//			case Undetermined:
//				return Undetermined;
//			case True:
//				return False;
//		}
//	}
//};
