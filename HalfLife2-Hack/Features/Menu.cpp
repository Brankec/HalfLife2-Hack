#include "Menu.h"

void InitImGui(LPDIRECT3DDEVICE9* pDevice, HWND* window);

void Hack::Menu::Draw(HWND* window, LPDIRECT3DDEVICE9* pDevice)
{
	static bool init = false;
	static bool showStatsMenu = false;
	static bool showMovementMenu = false;
	static bool showGameControlsMenu = false;
	static bool showWallhackMenu = false;

	if (!init)
	{
		InitImGui(pDevice, window);

		init = true;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::BeginMainMenuBar();
	if (ImGui::Button("Player Stats"))
		showStatsMenu = !showStatsMenu;
	if (ImGui::Button("Player Movement"))
		showMovementMenu = !showMovementMenu;
	if (ImGui::Button("Wallhack"))
		showWallhackMenu = !showWallhackMenu;
	if (ImGui::Button("Game Controls"))
		showGameControlsMenu = !showGameControlsMenu;
	ImGui::EndMainMenuBar();

	if (showStatsMenu)
	{
		ImGui::Begin("Player Stats Window", &showStatsMenu);
		ImGui::Text("Infinite");
		ImGui::Checkbox("Health", &Data::bHealthFreeze);
		ImGui::Checkbox("Armor", &Data::bArmorFreeze);
		ImGui::Checkbox("Aux Power", &Data::bAuxPowerFreeze);
		ImGui::End();
	}

	if (showMovementMenu)
	{
		ImGui::Begin("Player Movement Window", &showMovementMenu);
		ImGui::Text("Flight");
		ImGui::Checkbox("Activate", &Data::bFlyMode);
		ImGui::SliderFloat("Speed", &Data::flightSpeed, 0.0f, 20.0f);
		ImGui::NewLine();
		ImGui::Text("Gravity");
		ImGui::PushItemWidth(80.f);
		ImGui::InputFloat("Input", (float*)Hack::Data::gravity);
		ImGui::PopItemWidth();
		ImGui::SliderFloat("Slider", (float*)Hack::Data::gravity, -2000.0f, 2000.0f);
		ImGui::End();
	}

	if (showGameControlsMenu)
	{
		ImGui::Begin("Game Controls Window", &showGameControlsMenu);
		ImGui::SliderInt("FOV", (int*)Hack::Data::fov, 0, 100);
		ImGui::SliderFloat("Time Scale", (float*)Hack::Data::timeScale, 0.f, 10.f);
		ImGui::End();
	}

	if (showWallhackMenu)
	{
		ImGui::Begin("Wallhack Window", &showWallhackMenu);
		ImGui::Checkbox("Activate", &Data::bWallhack);
		ImGui::SliderFloat("Distance", &Data::WallhackDistance, 100.f, 10000.f);
		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void InitImGui(LPDIRECT3DDEVICE9* pDevice, HWND* window)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(*window);
	ImGui_ImplDX9_Init(*pDevice);

	ImGuiStyle& style = ImGui::GetStyle();
	style.FrameRounding = 0.f;
	style.WindowRounding = 0.f;
	style.TabRounding = 0.f;

	ImVec4* colors = style.Colors;
	colors[ImGuiCol_Text] = COLOR_ORANGE_TXT;
	colors[ImGuiCol_WindowBg] = COLOR_GRAY_BROWN;
	colors[ImGuiCol_TitleBg] = COLOR_DARK_GRAY;
	colors[ImGuiCol_TitleBgActive] = COLOR_DARK_GRAY;
	colors[ImGuiCol_Tab] = COLOR_DARK_GRAY;
	colors[ImGuiCol_TabHovered] = COLOR_GRAY;
	colors[ImGuiCol_TabActive] = COLOR_DARK_GRAY_2;
	colors[ImGuiCol_CheckMark] = COLOR_ORANGE;
	colors[ImGuiCol_FrameBg] = COLOR_DARK_GRAY;
	colors[ImGuiCol_FrameBgHovered] = COLOR_DARK_GRAY;
	colors[ImGuiCol_FrameBgActive] = COLOR_GRAY;
	colors[ImGuiCol_SliderGrab] = COLOR_ORANGE;
	colors[ImGuiCol_SliderGrabActive] = COLOR_LIGHT_ORANGE;
	colors[ImGuiCol_Button] = COLOR_DARK_GRAY;
	colors[ImGuiCol_ButtonHovered] = COLOR_DARK_GRAY_2;
	colors[ImGuiCol_ButtonActive] = COLOR_GRAY;
	colors[ImGuiCol_TabHovered] = COLOR_DARK_GRAY;
	colors[ImGuiCol_Header] = COLOR_DARK_GRAY_2;
	colors[ImGuiCol_HeaderHovered] = COLOR_GRAY;
	colors[ImGuiCol_HeaderActive] = COLOR_GRAY_3;
	colors[ImGuiCol_MenuBarBg] = COLOR_GRAY_BROWN;
	colors[ImGuiCol_Border] = COLOR_ORANGE;
	colors[ImGuiCol_ResizeGrip] = COLOR_DARK_ORANGE;
	colors[ImGuiCol_ResizeGripHovered] = COLOR_ORANGE;
	colors[ImGuiCol_ResizeGripActive] = COLOR_LIGHT_ORANGE;
}