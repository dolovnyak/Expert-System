#include <iostream>

#include "Node.hpp"
#include "Graph.hpp"

#include "imgui.h"

int main([[maybe_unused]] int ac, [[maybe_unused]] char **av) {
	ImGui::Text("Hello, world %d", 123);
	char buf[10];
	if (ImGui::Button("Save"))
		;
	ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
	float f;
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
	std::cout << "Hello world!" << std::endl;
	return 0;
}