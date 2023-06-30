#include "stdafx.h"
#include "Globals.h"
#include "Offsets.h"

namespace Exile {
	HWND Globals::MainWindow;
	HMODULE Globals::MainModule;
	HMODULE Globals::D3D9Module;

	void Globals::Initialize() {
		MainModule = GetModuleHandle(nullptr);
		D3D9Module = GetModuleHandle("d3d9.dll");
		MainWindow = *(HWND*)DEFINE_RVA(Offsets::RiotWindow::Instance);
	}
}