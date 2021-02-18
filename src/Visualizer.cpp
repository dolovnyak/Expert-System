// TODO remove
#include <iostream>

#include <memory>
//#include <imgui_internal.h>

#include "Visualizer.hpp"
#include "ExpertSystemData.hpp"
#include "Expressions/FactExpression.hpp"
#include "Expressions/UnaryExpression.hpp"
#include "Expressions/BinaryExpression.hpp"
#include <imgui_internal.h>

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void Visualizer::SetupImGui()
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		throw std::runtime_error("glfw init error");

	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac

	window_ = glfwCreateWindow(1280, 720, "Expert-System", NULL, NULL);
	if (window_ == NULL)
		throw std::runtime_error("glfw init error");
	glfwMakeContextCurrent(window_);
	glfwSwapInterval(1);

	bool err = glewInit() != GLEW_OK;
	if (err)
		throw std::runtime_error("glew init error");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window_, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

//	io.Fonts->AddFontDefault();
//	io.Fonts->AddFontFromFileTTF("libs/imgui/imgui-github/misc/fonts/Roboto-Medium.ttf", 15.0f);
//	io.Fonts->AddFontFromFileTTF("libs/imgui/imgui-github/misc/fonts/Cousine-Regular.ttf", 15.0f);
	io.Fonts->AddFontFromFileTTF("libs/imgui/imgui-github/misc/fonts/DroidSans.ttf", 15.0f);
//	io.Fonts->AddFontFromFileTTF("libs/imgui/imgui-github/misc/fonts/ProggyTiny.ttf", 16.0f);
}

void Visualizer::Show(const ExpertSystemData &expert_system_data)
{
	ExpertSystemData data = expert_system_data;

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	CopyExpressionListToBuf(expert_system_data.GetMainExpressions());
	UpdateNodesAndLinks(expert_system_data);

	while (!glfwWindowShouldClose(window_))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		DrawGraphWindow();
		DrawInputWindow();
		DrawFactsWindow(data);

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window_, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window_);

		if (should_execute_) {
			error = nullptr;
			try {
				data = ExpertSystem::Parse(buf);
				ExpertSystem::Solve(data);
				
				UpdateNodesAndLinks(data);
			} catch (const std::exception &exception) {
				std::unique_ptr<std::string> error_local(new std::string(exception.what()));
				error = std::move(error_local);
			}
			should_execute_ = false;
		}
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window_);
	glfwTerminate();
}

static int local_id = 0;

void Visualizer::ProcessNode(const std::shared_ptr<Node> &parent, const Expression *current, const ImVec2 &pos) {
	std::string str = current->ToString();
	if (expressions_.find(str) != expressions_.end()) {
		if (parent != nullptr) {
			links.push_back(std::make_shared<NodeLink>(parent->ID, 0, expressions_.at(str)->ID, 0));
		}
		return;
	}

	std::shared_ptr<Node> current_node = std::make_shared<Node>(local_id++, current->ToString(), current->GetState(), pos, 1, 1);
	nodes.push_back(current_node);
	expressions_.insert({str, current_node});

	if (parent != nullptr) {
		links.push_back(std::make_shared<NodeLink>(parent->ID, 0, current_node->ID, 0));
	}

	// TODO ugly construction
	const auto *ue = dynamic_cast<const UnaryExpression *>(current);
	if (ue != nullptr) {
		ProcessNode(current_node, ue->GetChild().get(), pos + ImVec2(150, 0));
	}

	const auto *be = dynamic_cast<const BinaryExpression *>(current);
	if (be != nullptr) {
		ProcessNode(current_node, be->GetLeftChild().get(), pos + ImVec2(150, -30));
		ProcessNode(current_node, be->GetRightChild().get(), pos + ImVec2(150, 30));
	}
}

void Visualizer::UpdateNodesAndLinks(const ExpertSystemData &expert_system_data) {
	local_id = 0;
	nodes.clear();
	links.clear();
	expressions_.clear();

	ImVec2 pos(50, 100);
	for (const auto &expression : expert_system_data.GetMainExpressions()) {
		ProcessNode(nullptr, expression.get(), pos);
		pos = pos + ImVec2(0, 130);
	}
}

static inline ImVec4 GetColor(Expression::State state) {
	switch (state) {
		case Expression::False:
			return { 1, 0, 0, 1 };
		case Expression::Undetermined:
			return { 0.66f, 0.66f, 0.66f, 1 };
		case Expression::True:
			return { 0, 1, 0, 1 };
	}
}

void Visualizer::DrawGraphWindow() {
	ImGui::SetNextWindowPos(ImVec2(PADDING_X, PADDING_Y), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(GRAPH_WINDOW_WIDTH, GRAPH_WINDOW_HEIGHT), ImGuiCond_FirstUseEver);

	ImGui::Begin("Graph");
	ImGuiIO& io = ImGui::GetIO();
	ImGui::BeginGroup();
	
	//display canvas
	const float NODE_SLOT_RADIUS = 4.0f;
	const ImVec2 NODE_WINDOW_PADDING(8.0f, 8.0f);
	ImGui::Text("Hold middle mouse button to move");
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(60, 60, 70, 200));
	ImGui::BeginChild("scrolling_region", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
	ImGui::PopStyleVar(); // WindowPadding
	ImGui::PushItemWidth(120.0f);
	
	const ImVec2 offset = ImGui::GetCursorScreenPos() + scrolling;
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	
	// Display grid
	ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);
	float GRID_SZ = 64.0f;
	ImVec2 win_pos = ImGui::GetCursorScreenPos();
	ImVec2 canvas_sz = ImGui::GetWindowSize();
	for (float x = fmodf(scrolling.x, GRID_SZ); x < canvas_sz.x; x += GRID_SZ)
		draw_list->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, canvas_sz.y) + win_pos, GRID_COLOR);
	for (float y = fmodf(scrolling.y, GRID_SZ); y < canvas_sz.y; y += GRID_SZ)
		draw_list->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(canvas_sz.x, y) + win_pos, GRID_COLOR);

	// Display links
	draw_list->ChannelsSplit(2);
	draw_list->ChannelsSetCurrent(0); // Background
	for (const auto &link : links)
	{
		ImVec2 p1 = offset + nodes[link->InputIdx]->GetOutputSlotPos(link->InputSlot);
		ImVec2 p2 = offset + nodes[link->OutputIdx]->GetInputSlotPos(link->OutputSlot);
		draw_list->AddBezierCurve(p1, p1 + ImVec2(+50, 0), p2 + ImVec2(-50, 0), p2, IM_COL32(200, 200, 100, 255), 3.0f);
	}

	// Display nodes
	for (const auto &node : nodes)
	{
		ImGui::PushID(node->ID);
		ImVec2 node_rect_min = offset + node->Pos;

		// Display node contents first
		draw_list->ChannelsSetCurrent(1); // Foreground
		bool old_any_active = ImGui::IsAnyItemActive();
		ImGui::SetCursorScreenPos(node_rect_min + NODE_WINDOW_PADDING);
		ImGui::BeginGroup(); // Lock horizontal position
		ImGui::Text("%s", node->Name.c_str());
		ImGui::Text("State:");
		ImGui::SameLine();
		ImVec4 color = GetColor(node->State);
		ImGui::TextColored(color, "%s", Expression::GetStateName(node->State).c_str());
		ImGui::EndGroup();

		// Save the size of what we have emitted and whether any of the widgets are being used
		bool node_widgets_active = (!old_any_active && ImGui::IsAnyItemActive());
		node->Size = ImGui::GetItemRectSize() + NODE_WINDOW_PADDING + NODE_WINDOW_PADDING;
		ImVec2 node_rect_max = node_rect_min + node->Size;

		// Display node box
		draw_list->ChannelsSetCurrent(0); // Background
		ImGui::SetCursorScreenPos(node_rect_min);
		ImGui::InvisibleButton("node", node->Size);
		
		bool node_moving_active = ImGui::IsItemActive();
		if (node_widgets_active || node_moving_active)
			node_selected = node->ID;
		if (node_moving_active && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
			node->Pos = node->Pos + io.MouseDelta;

		ImU32 node_bg_color = (node_selected == node->ID) ? IM_COL32(75, 75, 75, 255) : IM_COL32(60, 60, 60, 255);
		draw_list->AddRectFilled(node_rect_min, node_rect_max, node_bg_color, 4.0f);
		draw_list->AddRect(node_rect_min, node_rect_max, IM_COL32(100, 100, 100, 255), 4.0f);
		for (int slot_idx = 0; slot_idx < node->InputsCount; slot_idx++)
			draw_list->AddCircleFilled(offset + node->GetInputSlotPos(slot_idx), NODE_SLOT_RADIUS, IM_COL32(150, 150, 150, 150));
		for (int slot_idx = 0; slot_idx < node->OutputsCount; slot_idx++)
			draw_list->AddCircleFilled(offset + node->GetOutputSlotPos(slot_idx), NODE_SLOT_RADIUS, IM_COL32(150, 150, 150, 150));

		ImGui::PopID();
	}
	draw_list->ChannelsMerge();

	// Scrolling
	if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f))
		scrolling = scrolling + io.MouseDelta;
	
	ImGui::PopItemWidth();
	ImGui::EndChild();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::EndGroup();

	ImGui::End();
}

void Visualizer::DrawInputWindow() {
	ImGui::SetNextWindowPos(ImVec2(GRAPH_WINDOW_WIDTH + 2 * PADDING_X, PADDING_Y), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(INPUT_WINDOW_WIDTH, INPUT_WINDOW_HEIGHT), ImGuiCond_FirstUseEver);
	
	ImGui::Begin("Input");
	ImGui::InputTextMultiline("", buf, IM_ARRAYSIZE(buf), ImVec2(INPUT_WINDOW_WIDTH - 30, INPUT_WINDOW_HEIGHT * 0.8));
	bool is_executable = strlen(buf) != 0;
	
	if (!is_executable)
	{
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
	}
	if (ImGui::ButtonEx("Execute", ImVec2(0, 0))) {
		should_execute_ = true;
	}
	if (!is_executable)
	{
		ImGui::PopItemFlag();
		ImGui::PopStyleVar();
	}
	if (error != nullptr) {
		ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", error->c_str());
	}

	ImGui::End();
}

void Visualizer::CopyExpressionListToBuf(const std::vector<std::shared_ptr<Expression>> &expressions) {
	bzero(buf, IM_ARRAYSIZE(buf));
	size_t i = 0;
	for (const auto exp : expressions) {
		std::string exp_str = exp->ToString();
		size_t len = exp_str.size();
		if (i + len + 1 >= IM_ARRAYSIZE(buf)) {
			break;
		}
		strcpy(buf + i, exp_str.c_str());
		i += len + 1;
		buf[i - 1] = '\n';
	}
}

void Visualizer::DrawFactsWindow(const ExpertSystemData &data) {
	ImGui::SetNextWindowPos(ImVec2(GRAPH_WINDOW_WIDTH + 2 * PADDING_X, INPUT_WINDOW_HEIGHT + 2 * PADDING_Y), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(FACTS_WINDOW_WIDTH, FACTS_WINDOW_HEIGHT), ImGuiCond_FirstUseEver);

	ImGui::Begin("Facts");
	for (char f = 'A'; f <= 'Z'; ++f) {
		auto it = std::find_if(data.GetFacts().begin(), data.GetFacts().end(), [f](const std::shared_ptr<Expression> &e) {
			auto fe = dynamic_cast<FactExpression *>(e.get());
			return fe != nullptr && fe->GetFact() == f;
		});
		ImGui::Text("%c", f);
		ImGui::SameLine();
		if (it != data.GetFacts().end()) {
			ImGui::TextColored(GetColor((*it)->GetState()), "%s", Expression::GetStateName((*it)->GetState()).c_str());
		} else {
			ImGui::Text("-");
		}
	}
	ImGui::End();
}


