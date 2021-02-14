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

class Visualizer
{
public:
	Visualizer();
	
	void SetupImgui();
	void Execute();

private:
	GLFWwindow* window_;
	
	void RenderGraphWindow();
};