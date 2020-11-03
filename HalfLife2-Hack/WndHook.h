#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "mainhack.h"
#include "minhook/include/MinHook.h"

namespace WndHook
{
	void Hook(PVOID base);
}

