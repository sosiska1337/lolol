#include <vector>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <windows.h>
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_internal.h"

#include "custom.h"
#include "arialbd.hpp"
#include "arialbd.hpp"
#include "arialblk.hpp"

using namespace ImGui;
static int tabs = 1;

ImFont* icons;
ImFont* tolstiy;
ImFont* ne_takoi_tolstiy;
ImFont* ne_takoi_tolstiy2;
c_gui* gui = new c_gui;

class dot
{
public:
	dot(SourceEngine::Vector p, SourceEngine::Vector v) {
		m_vel = v;
		m_pos = p;
	}

	void update();
	void draw();

	SourceEngine::Vector m_pos, m_vel;
};
std::vector<dot*> dots = { };

void dot::update() {
	auto opacity = 240 / 255.0f;

	m_pos += m_vel * (opacity);
}
void dot::draw() {
	int opacity = 55.0f * (240 / 255.0f);

	ImGui::GetWindowDrawList()->AddRectFilled({ m_pos.x - 2, m_pos.y - 2 }, { m_pos.x + 2, m_pos.y + 2 }, ImColor(9, 169, 232, 195));

	auto t = std::find(dots.begin(), dots.end(), this);
	if (t == dots.end()) {
		return;
	}

	for (auto i = t; i != dots.end(); i++) {
		if ((*i) == this) continue;

		auto dist = (m_pos - (*i)->m_pos).Length2D();

		if (dist < 128) {
			int alpha = opacity * (dist / 128);
			ImGui::GetWindowDrawList()->AddLine({ m_pos.x - 1, m_pos.y - 2 }, { (*i)->m_pos.x - 2, (*i)->m_pos.y - 1 }, ImColor(9, 169, 232, 195));
		}
	}
}

void dot_draw() {
	struct screen_size {
		int x, y;
	}; screen_size sc;

	sc.x = 1920, sc.y = 1080;

	int s = rand() % 9;

	if (s == 0) {
		dots.push_back(new dot(SourceEngine::Vector(rand() % (int)sc.x, -16, 0), SourceEngine::Vector((rand() % 7) - 3, rand() % 3 + 1, 0)));
	}
	else if (s == 1) {
		dots.push_back(new dot(SourceEngine::Vector(rand() % (int)sc.x, (int)sc.y + 16, 0), SourceEngine::Vector((rand() % 7) - 3, -1 * (rand() % 3 + 1), 0)));
	}
	else if (s == 2) {
		dots.push_back(new dot(SourceEngine::Vector(-16, rand() % (int)sc.y, 0), SourceEngine::Vector(rand() % 3 + 1, (rand() % 7) - 3, 0)));
	}
	else if (s == 3) {
		dots.push_back(new dot(SourceEngine::Vector((int)sc.x + 16, rand() % (int)sc.y, 0), SourceEngine::Vector(-1 * (rand() % 3 + 1), (rand() % 7) - 3, 0)));
	}

	auto alph = 135.0f * (240 / 255.0f);
	auto a_int = (int)(alph);

	ImGui::GetWindowDrawList()->AddRectFilled({ 0, 0 }, { (float)sc.x, (float)sc.y }, ImColor(a_int, 0, 0, 0));

	for (auto i = dots.begin(); i < dots.end();) {
		if ((*i)->m_pos.y < -20 || (*i)->m_pos.y > sc.y + 20 || (*i)->m_pos.x < -20 || (*i)->m_pos.x > sc.x + 20) {
			delete (*i);
			i = dots.erase(i);
		}
		else {
			(*i)->update();
			i++;
		}
	}

	for (auto i = dots.begin(); i < dots.end(); i++) {
		(*i)->draw();
	}
}

VOID ImGUI_Style()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
	colors[ImGuiCol_ChildBg] = ImColor(13, 11, 16);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.0f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImColor(32, 32, 30);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
	colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
	colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
	colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}
#include <mutex>
void Menu() {
	ImGUI_Style();
	ImGui::Begin("$gangboyz$", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
	{
		auto pos = ImGui::GetWindowPos();
		auto draw = ImGui::GetWindowDrawList();
		static int tabs = 0;
		ImGui::SetWindowSize(ImVec2(810, 675));

		// background
		draw->AddRectFilled(ImVec2(pos.x + 190, pos.y + 0), ImVec2(pos.x + 807, pos.y + 657), ImColor(8, 8, 8), 8.f, 10);

		//tabs_child
		draw->AddRectFilled(ImVec2(pos.x + 0, pos.y + 0), ImVec2(pos.x + 197, pos.y + 657), ImColor(8, 8, 8, 230), 10.f, 5);

		//пизда какая то
		draw->AddLine(ImVec2(pos.x + 190, pos.y + 70), ImVec2(pos.x + 807, pos.y + 71), ImColor(32, 32, 30));

		//cheat_name
		draw->AddText(tolstiy, 35.f, ImVec2(pos.x + 16, pos.y + 26), ImColor(65, 186, 217), "HUYNA");
		draw->AddText(tolstiy, 35.f, ImVec2(pos.x + 17, pos.y + 26), ImColor(255, 255, 255), "HUYNA");
		draw->AddText(tolstiy, 35.f, ImVec2(pos.x + 210, pos.y + 20), ImColor(65, 186, 217), "HUYNA");
		draw->AddText(tolstiy, 35.f, ImVec2(pos.x + 210, pos.y + 20), ImColor(255, 255, 255), "HUYNA");

		ImGui::SetCursorPos(ImVec2(12, 94));
		ImGui::BeginGroup();
		{
			ImGui::TextColored(ImVec4(55 / 255.f, 55 / 255.f, 55 / 255.f, 1.f), "Aimbot");
			if (gui->tabs("0", "Ragebot", tabs == 0, ImVec2(172, 31)))
				tabs = 0;
			if (gui->tabs("1", "Anti Aim", tabs == 1, ImVec2(172, 31)))
				tabs = 1;
			ImGui::TextColored(ImVec4(55 / 255.f, 55 / 255.f, 55 / 255.f, 1.f), "Visuals");
			if (gui->tabs("2", "Players", tabs == 2, ImVec2(172, 31)))
				tabs = 2;
			if (gui->tabs("4", "World", tabs == 4, ImVec2(172, 31)))
				tabs = 4;
			ImGui::TextColored(ImVec4(55 / 255.f, 55 / 255.f, 55 / 255.f, 1.f), "Miscellaneous");
			if (gui->tabs("3", "Weapon", tabs == 3, ImVec2(172, 31)))
				tabs = 3;
			if (gui->tabs("5", "Main", tabs == 5, ImVec2(172, 31)))
				tabs = 5;
		}
		ImGui::EndGroup();


		ImGui::SetCursorPos(ImVec2(210, 90));
		ImGui::BeginGroup();
		{
			switch (tabs) {
			case 0:
				gui->begin_child("Rage", ImVec2(575, 550));
				{
				}
				gui->end_child();
				break;
				ImGui::EndGroup();
			}
			ImGui::End();
		}
	}
}


