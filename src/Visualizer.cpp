#include "Visualizer.hpp"
#include "MainExpressionsList.hpp"

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
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	ImGui_ImplGlfw_InitForOpenGL(window_, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);
}

void Visualizer::Show()
{
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	UpdateNodesAndLinks();

	while (!glfwWindowShouldClose(window_))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		DrawGraphWindow();
		DrawInputWindow();

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
				FILE *content = fmemopen(buf, BUF_SIZE, "r");
				owner_.Execute(content);
			} catch (const std::exception &exception) {
				std::shared_ptr<std::string> error_local(new std::string(exception.what()));
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

static inline int GetOutputsCount(const Expression *expression) {
	return static_cast<int>(expression->GetType());
}

void Visualizer::ProcessNode(const Node *parent, const Expression *current, const ImVec2 &pos) {
	std::string str = current->ToString();
	if (expressions_.find(str) != expressions_.end()) {
		if (parent != nullptr) {
			const auto node = expressions_.at(str);
			links.push_back(NodeLink(parent->ID, 0, node.ID, 0));
		}
		return;
	}

	nodes.push_back(Node(local_id++, current->ToString(), pos, 1, GetOutputsCount(current)));
	const Node &current_node = nodes.back();
	expressions_.insert({str, current_node});

	if (parent != nullptr) {
		links.push_back(NodeLink(parent->ID, 0, current_node.ID, 0));
	}

	// TODO ugly construction
	const auto *ue = dynamic_cast<const UnaryExpression *>(current);
	if (ue != nullptr) {
		ProcessNode(&current_node, ue->GetChild(), pos + ImVec2(100, 0));
	}

	const auto *be = dynamic_cast<const BinaryExpression *>(current);
	if (be != nullptr) {
		ProcessNode(&current_node, be->GetLeftChild(), pos + ImVec2(150, -25));
		ProcessNode(&current_node, be->GetRightChild(), pos + ImVec2(150, 25));
	}
}

void Visualizer::UpdateNodesAndLinks() {
	local_id = 0;
	nodes.clear();
	links.clear();

	ImVec2 pos(50, 50);
	for (const auto expression : MainExpressionsList::Instance().main_expressions_list_) {
		ProcessNode(nullptr, expression, pos);
		pos = pos + ImVec2(0, 100);
	}
}

void Visualizer::DrawGraphWindow() {
	ImGui::SetNextWindowPos(ImVec2(PADDING_X, PADDING_Y));
	ImGui::SetNextWindowSize(ImVec2(GRAPH_WINDOW_WIDTH, GRAPH_WINDOW_HEIGHT));

	ImGui::Begin("Graph");
	ImGuiIO& io = ImGui::GetIO();
	ImGui::BeginGroup();
	const float NODE_SLOT_RADIUS = 4.0f;
	const ImVec2 NODE_WINDOW_PADDING(8.0f, 8.0f);
	// Create our child canvas
//	ImGui::Text("Hold middle mouse button to scroll (%.2f,%.2f)", scrolling.x, scrolling.y);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(60, 60, 70, 200));
	ImGui::BeginChild("scrolling_region", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
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
	for (int link_idx = 0; link_idx < links.Size; link_idx++)
	{
		NodeLink* link = &links[link_idx];
		Node* node_inp = &nodes[link->InputIdx];
		Node* node_out = &nodes[link->OutputIdx];
		ImVec2 p1 = offset + node_inp->GetOutputSlotPos(link->InputSlot);
		ImVec2 p2 = offset + node_out->GetInputSlotPos(link->OutputSlot);
		draw_list->AddBezierCurve(p1, p1 + ImVec2(+50, 0), p2 + ImVec2(-50, 0), p2, IM_COL32(200, 200, 100, 255), 3.0f);
	}

	// Display nodes
	for (int node_idx = 0; node_idx < nodes.Size; node_idx++)
	{
		Node* node = &nodes[node_idx];
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
		ImVec4 color;
		switch (node->State) {
			case Expression::False:
				color = { 1, 0, 0, 1 };
				break;
			case Expression::Undetermined:
				color = { 0.66f, 0.66f, 0.66f, 1 };
				break;
			case Expression::True:
				color = { 0, 0, 1, 1 };
				break;
		}
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
//		if (ImGui::IsItemHovered())
//		{
//			node_hovered_in_scene = node->ID;
//			open_context_menu |= ImGui::IsMouseClicked(1);
//		}
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
	ImGui::SetNextWindowPos(ImVec2(GRAPH_WINDOW_WIDTH + 2 * PADDING_X, PADDING_Y));
	ImGui::SetNextWindowSize(ImVec2(INPUT_WINDOW_WIDTH, INPUT_WINDOW_HEIGHT));
	ImGui::Begin("Input");

	ImGui::InputTextMultiline("", buf, IM_ARRAYSIZE(buf));
	if (ImGui::Button("Build")) {
		should_execute_ = true;
	}
	if (error != nullptr) {
		ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", error->c_str());
	}

	ImGui::End();
}


