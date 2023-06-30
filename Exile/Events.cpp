#include "stdafx.h"
#include "Events.h"
#include "MenuSettings.h"
#include "EventManager.h"
#include "Instances.h"
#include "Menu.h"
#include "HealthPrediction.h"
#include "TargetSelector.h"
#include "Orbwalker.h"
#include "Plugins.h"

#include "GameClient.h"
#include "ClockFacade.h"
#include "ManagerTemplate.h"
#include "ObjectManager.h"

namespace Exile {
	namespace SDK {
		void Events::Initialize() {
			GameStart::Initialize();
		}

		namespace Events {
			namespace GameStart {

				void Initialize() {
					EventManager::AddEventHandler(LeagueEvents::OnPresent, OnGameUpdate);
				}

				void OnGameUpdate() {
					if (GameClient::Instance->GameState == GameState::GameLoop && *(DWORD*)DEFINE_RVA(Offsets::ObjectManager::Player)) {
						Instances::Initialize();

						Objects::Initialize();
						SpellCast::Initialize();
						NewPath::Initialize();

						Menu::Initialize();
						HealthPrediction::Initialize();
						TargetSelector::Initialize();
						Orbwalker::Initialize();
						//Plugins::Initialize();

						EventManager::RemoveEventHandler(LeagueEvents::OnPresent, OnGameUpdate);
					}
				}
			}

			namespace Objects {
				GameObject* CachedGameObjects[10000];

				void Initialize() {
					for (auto i = 0; i < 10000; i++) {
						auto gameObject = ObjectManager::Instance->ObjectsArray[i];
						CachedGameObjects[i] = gameObject;
						if (gameObject) {
							EventManager::Trigger(LeagueEvents::OnCreateObject, gameObject);
						}
					}

					EventManager::AddEventHandler(LeagueEvents::OnPresent, OnGameUpdate);
				}

				void OnGameUpdate() {
					for (auto i = 0; i < ObjectManager::Instance->MaxObjects; i++) {
						auto gameObject = ObjectManager::Instance->ObjectsArray[i];
						auto& cachedGameObject = CachedGameObjects[i];

						if (!cachedGameObject && gameObject) {
							cachedGameObject = gameObject;
							EventManager::Trigger(LeagueEvents::OnCreateObject, gameObject);
						}
						else if (cachedGameObject && gameObject != cachedGameObject) {
							EventManager::Trigger(LeagueEvents::OnDeleteObject, cachedGameObject);
							cachedGameObject = gameObject;
							if (gameObject) {
								EventManager::Trigger(LeagueEvents::OnCreateObject, gameObject);
							}
						}
					}
				}
			}

			namespace SpellCast {
				SpellInstanceClient* CachedSpells[10000];
				float CachedSpellCastEndTime[10000];
				kSpellState CachedSpellStates[SpellSlot_Trinket];

				void Initialize() {
					for (auto slot = SpellSlot_Q; slot < SpellSlot_Item6; slot = (kSpellSlot)(slot + 1)) {
						CachedSpellStates[slot] = ObjectManager::Player->GetSpellState(slot);
					}
					EventManager::AddEventHandler(LeagueEvents::OnPresent, OnGameUpdate);
				}

				void OnGameUpdate() {
					for (auto slot = SpellSlot_Q; slot < SpellSlot_Item6; slot = (kSpellSlot)(slot + 1)) {
						auto& cachedSpellState = CachedSpellStates[slot];
						auto spellState = ObjectManager::Player->GetSpellState(slot);

						if (cachedSpellState != spellState) {
							if (!(cachedSpellState & SpellState_Supressed) && !(cachedSpellState & SpellState_Cooldown)) {
								if (spellState & SpellState_Supressed || spellState & SpellState_Cooldown) {
									EventManager::Trigger(LeagueEvents::OnSpellCast, slot);
								}
							}
							cachedSpellState = spellState;
						}
					}

					for (auto unit : *ManagerTemplate::AIBases) {
						auto activeSpell = unit->Spellbook.ActiveSpellInstance;
						auto& cachedSpell = CachedSpells[unit->Id];
						auto& cachedSpellCastEndTime = CachedSpellCastEndTime[unit->Id];

						if (activeSpell) {
							auto castInfo = activeSpell->GetCastInfo();
							if (cachedSpell == nullptr || cachedSpell != activeSpell) {
								cachedSpell = activeSpell;
								cachedSpellCastEndTime = castInfo->CastEndTime;
								EventManager::Trigger(LeagueEvents::OnProcessSpell, unit, castInfo);
							}
							else if (cachedSpellCastEndTime != 0.0f && activeSpell->GetCastInfo()->IsStopped) {
								cachedSpellCastEndTime = 0.0f;
								EventManager::Trigger(LeagueEvents::OnStopCast, unit, cachedSpellCastEndTime);
							}
						}
						else if (cachedSpell) {
							if (ClockFacade::Instance->GetGameTime() <= cachedSpellCastEndTime) {
								EventManager::Trigger(LeagueEvents::OnStopCast, unit, cachedSpellCastEndTime);
							}
							cachedSpellCastEndTime = 0.0f;
							cachedSpell = nullptr;
						}
					}
				}
			}

			namespace NewPath {
				Vector3 CachedEndPositions[10000];

				void Initialize() {
					for (auto hero : *ManagerTemplate::Heroes) {
						CachedEndPositions[hero->Id] = hero->GetPathController()->GetNavigationPath()->EndPosition;
					}
					EventManager::AddEventHandler(LeagueEvents::OnPresent, OnGameUpdate);
				}

				void OnGameUpdate() {
					for (auto hero : *ManagerTemplate::Heroes) {
						auto navigationPath = hero->GetPathController()->GetNavigationPath();
						auto endPosition = navigationPath->EndPosition;
						auto& cachedEndPosition = CachedEndPositions[hero->Id];
						if (endPosition != cachedEndPosition) {
							cachedEndPosition = endPosition;
							EventManager::Trigger(LeagueEvents::OnNewPath, hero, navigationPath);
						}
					}
				}
			}
		}
	}
}