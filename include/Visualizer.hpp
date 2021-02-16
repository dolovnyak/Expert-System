#pragma once

#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <utility>
#include <vector>
#include <map>

#include "Expressions/Expression.hpp"
#include "ExpertSystem.hpp"

#define GRAPH_WINDOW_WIDTH 800
#define GRAPH_WINDOW_HEIGHT 600
#define INPUT_WINDOW_WIDTH 400
#define INPUT_WINDOW_HEIGHT 300
#define PADDING_X 10
#define PADDING_Y 10

static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

struct Node
{
	int			ID;
	std::string	Name;
	Expression::State State;
	ImVec2		Pos, Size;
	int			InputsCount, OutputsCount;

	Node(int id,
	  std::string name,
	  const ImVec2& pos,
	  int inputs_count,
	  int outputs_count)
	  : ID(id), Name(std::move(name)), State(Expression::State::False), Pos(pos), InputsCount(inputs_count), OutputsCount(outputs_count) { }

	[[nodiscard]] ImVec2 GetInputSlotPos(int slot_no) const {
		return ImVec2(Pos.x, Pos.y + Size.y * ((float)slot_no + 1) / ((float)InputsCount + 1));
	}
	[[nodiscard]] ImVec2 GetOutputSlotPos(int slot_no) const {
		return ImVec2(Pos.x + Size.x, Pos.y + Size.y * ((float)slot_no + 1) / ((float)OutputsCount + 1));
	}
};
struct NodeLink
{
	int     InputIdx, InputSlot, OutputIdx, OutputSlot;
	NodeLink(int input_idx, int input_slot, int output_idx, int output_slot) { InputIdx = input_idx; InputSlot = input_slot; OutputIdx = output_idx; OutputSlot = output_slot; }
};

class Visualizer
{
public:
	explicit Visualizer(const ExpertSystem &owner)
		: owner_(const_cast<ExpertSystem &>(owner)) {}

	void SetupImGui();
	void Show();

private:
	ExpertSystem &owner_;

	GLFWwindow* window_ = nullptr;

	std::vector<std::shared_ptr<Node>> nodes;
	std::vector<std::shared_ptr<NodeLink>> links;
	// TODO optimize
	std::map<std::string, std::shared_ptr<Node>> expressions_;

	ImVec2 scrolling = ImVec2(0.0f, 0.0f);
	int node_selected = -1;

	static const int BUF_SIZE = 1024;
	char buf[BUF_SIZE] = {0};
	void CopyExpressionListToBuf();

	bool should_execute_ = false;

	std::unique_ptr<std::string> error = nullptr;

	void ProcessNode(const std::shared_ptr<Node>& parent, const Expression *current, const ImVec2 &pos);
	void UpdateNodesAndLinks();

	void DrawGraphWindow();

	void DrawInputWindow();
};