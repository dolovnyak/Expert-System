#pragma once

#include <memory>
#include <utility>
#include <vector>

class INode : public std::enable_shared_from_this<INode> {
public:
	enum State {
		False,
		Undetermined,
		True,
	};

	/// Executed by parent
	virtual void UpdateState(State, std::shared_ptr<INode>) = 0;

	/// Executed by child
	virtual void UpdateState(std::shared_ptr<INode>) = 0;

	[[nodiscard]] State GetState() const {
		return state_;
	}

	[[nodiscard]] const std::vector<std::weak_ptr<INode>> &GetParents() const {
		return parents_;
	}

protected:
	State state_{False};
	std::vector<std::weak_ptr<INode>> parents_;

	void UpdateParents(const std::shared_ptr<INode>& sender) {
		for (const auto &weak_parent : parents_) {
			std::shared_ptr<INode> shared_parent = weak_parent.lock();
			if (shared_parent != sender) {
				shared_parent->UpdateState(sender);
			}
		}
	}

	[[nodiscard]] std::shared_ptr<INode> SharedFromThis() {
		return shared_from_this();
	}
};