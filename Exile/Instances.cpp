#include "stdafx.h"
#include "Instances.h"
#include "Offsets.h"
#include "ClockFacade.h"
#include "HudManager.h"
#include "ManagerTemplate.h"
#include "NetClient.h"
#include "ObjectManager.h"

namespace Exile {
	void Instances::Initialize() {
		ClockFacade::Instance = *(ClockFacade**)DEFINE_RVA(Offsets::ClockFacade::Instance);
		HudManager::Instance = *(HudManager**)DEFINE_RVA(Offsets::HudManager::Instance);
		ManagerTemplate::AIBases = (std::vector<GameObject*>*)DEFINE_RVA(Offsets::ManagerTemplate::AIBases);
		ManagerTemplate::Turrets = (std::vector<GameObject*>*)DEFINE_RVA(Offsets::ManagerTemplate::Turrets);
		ManagerTemplate::Minions = (std::vector<GameObject*>*)DEFINE_RVA(Offsets::ManagerTemplate::Minions);
		ManagerTemplate::Heroes = (std::vector<GameObject*>*)DEFINE_RVA(Offsets::ManagerTemplate::Heroes);
		NetClient::Instance = *(NetClient**)DEFINE_RVA(Offsets::NetClient::Instance);
		ObjectManager::Instance = (ObjectManager*)DEFINE_RVA(Offsets::ObjectManager::Instance);
		ObjectManager::Player = *(GameObject**)DEFINE_RVA(Offsets::ObjectManager::Player);
	}
}