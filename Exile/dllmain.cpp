#include "stdafx.h"
#include "Globals.h"
#include "Functions.h"
#include "DeviceHandler.h"
#include "GameClient.h"
#include "RenderLayer.h"
#include "Instances.h"
#include "Renderer.h"
#include "Hooks.h"
#include "Events.h"
#include "Plugins.h"
#include "Menu.h"

using namespace Exile;
using namespace Exile::SDK;

__declspec(dllexport, naked) void __stdcall unpackman() {
	__asm pushfd
	__asm pushad
	__asm push 0
	__asm push 1
	__asm push unpackman
	__asm call unpackman
	__asm popad
	__asm popfd
	__asm ret
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID) {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(module);
		Globals::Initialize();
		Functions::Initialize();
		DeviceHandler::Instance = *(DeviceHandler**)DEFINE_RVA(Offsets::DeviceHandler::Instance);
		GameClient::Instance = *(GameClient**)DEFINE_RVA(Offsets::GameClient::Instance);
		RenderLayer::Instance = *(RenderLayer**)DEFINE_RVA(Offsets::RenderLayer::Instance);
		Renderer::Initialize();
		Hooks::Initialize();
		Events::Initialize();
		break;
	case DLL_PROCESS_DETACH:
		Plugins::Dispose();
		Menu::Dispose();
		Hooks::Dispose();
		Renderer::Dispose();
		break;
	}

	return TRUE;
}