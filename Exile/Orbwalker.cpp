#include "stdafx.h"
#include "Orbwalker.h"
#include "Menu.h"
#include "EventManager.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "ManagerTemplate.h"
#include "ClockFacade.h"
#include "HudManager.h"
#include "NetClient.h"
#include "TargetSelector.h"
#include "HealthPrediction.h"

namespace Exile {
	namespace SDK {
		GameObject* Orbwalker::LastHitMinion = nullptr;
		GameObject* Orbwalker::AlmostLastHitMinion = nullptr;
		GameObject* Orbwalker::LaneClearMinion = nullptr;
		GameObjectOrder Orbwalker::LastOrder = GameObjectOrder::None;
		float Orbwalker::LastAttackOrder = 0.0f;
		float Orbwalker::LastMoveOrder = 0.0f;
		float Orbwalker::LastShouldWait = 0.0f;
		GameObject* Orbwalker::LastTarget = nullptr;
		Vector3 Orbwalker::LastMovePosition = Vector3::Zero;
		float Orbwalker::LastAttack = 0.0f;
		float Orbwalker::LastAttackCastEndTime = 0.0f;
		unsigned int Orbwalker::ActiveMode = OrbwalkerMode_None;
		bool Orbwalker::IsAzir = false;
		std::vector<GameObject*> Orbwalker::AzirSoldiers;
		bool Orbwalker::IsAshe = false;
		bool Orbwalker::IsGraves = false;
		bool Orbwalker::IsRengar = false;
		bool Orbwalker::AttackUsesAmmo = false;
		kSpellSlot Orbwalker::AttackResetSlot = SpellSlot_Unknown;
		unsigned int Orbwalker::AttackResetHash = 0;
		bool Orbwalker::IsDashAttackReset = false;
		GameObject* Orbwalker::ForcedTarget = nullptr;
		Vector3 Orbwalker::ForcedPosition = Vector3::Zero;

		namespace Orbwalker {
			namespace Config {
				namespace Hotkeys {
					KeyBind* Combo;
					KeyBind* Harass;
					KeyBind* LaneClear;
					KeyBind* JungleClear;
					KeyBind* LastHit;
					KeyBind* Flee;
				}

				namespace Configuration {
					CheckBox* LaneClearHeroes;
					CheckBox* SupportMode;
					Slider* HoldRadius;
					Slider* MovementDelay;
					Slider* ExtraWindUpTime;
				}

				namespace Farming {
					CheckBox* LastHitPriority;
					CheckBox* PushPriority;
					Slider* ExtraFarmDelay;
				}

				namespace Melee {
					CheckBox* StickToTarget;
				}

				namespace Drawings {
					CheckBox* AttackRange;
					CheckBox* AzirSoldierAttackRange;
					CheckBox* EnemyAttackRange;
					CheckBox* HoldRadius;
					CheckBox* LasthittableMinions;
				}
			}
		}

		void Orbwalker::Initialize() {
			switch (ObjectManager::Player->BaseCharacterData->SkinHash) {
			case Character::Ashe:
				IsAshe = true;
				break;
			case Character::Azir:
				IsAzir = true;
				break;
			case Character::Blitzcrank:
				AttackResetSlot = SpellSlot_E;
				break;
			case Character::Camille:
				AttackResetSlot = SpellSlot_Q;
				break;
			case Character::Chogath:
				AttackResetSlot = SpellSlot_E;
				break;
			case Character::Darius:
				AttackResetSlot = SpellSlot_W;
				break;
			case Character::DrMundo:
				AttackResetSlot = SpellSlot_E;
				break;
			case Character::Elise:
				AttackResetSlot = SpellSlot_W;
				AttackResetHash = 0x211D8403; // "EliseSpiderW"
				break;
			case Character::Fiora:
				AttackResetSlot = SpellSlot_E;
				break;
			case Character::Fizz:
				AttackResetSlot = SpellSlot_W;
				break;
			case Character::Garen:
				AttackResetSlot = SpellSlot_Q;
				break;
			case Character::Graves:
				IsGraves = true;
				AttackUsesAmmo = true;
				AttackResetSlot = SpellSlot_E;
				IsDashAttackReset = true;
				break;
			case Character::Kassadin:
				AttackResetSlot = SpellSlot_W;
				break;
			case Character::Illaoi:
				AttackResetSlot = SpellSlot_W;
				break;
			case Character::Jax:
				AttackResetSlot = SpellSlot_W;
				break;
			case Character::Jayce:
				AttackResetSlot = SpellSlot_W;
				AttackResetHash = 0xE95D0E7; // "JayceHyperCharge"
				break;
			case Character::Jhin:
				AttackUsesAmmo = true;
				break;
			case Character::Leona:
				AttackResetSlot = SpellSlot_Q;
				break;
			case Character::Lucian:
				AttackResetSlot = SpellSlot_E;
				IsDashAttackReset = true;
				break;
			case Character::MasterYi:
				AttackResetSlot = SpellSlot_W;
				break;
			case Character::Mordekaiser:
				AttackResetSlot = SpellSlot_Q;
				break;
			case Character::Nasus:
				AttackResetSlot = SpellSlot_Q;
				break;
			case Character::Nautilus:
				AttackResetSlot = SpellSlot_W;
				break;
			case Character::Nidalee:
				AttackResetSlot = SpellSlot_Q;
				AttackResetHash = 0xCCD4C05E; // "Takedown"
				break;
			case Character::RekSai:
				AttackResetSlot = SpellSlot_Q;
				break;
			case Character::Rengar:
				IsRengar = true;
				AttackResetSlot = SpellSlot_Q;
				break;
			case Character::Renekton:
				AttackResetSlot = SpellSlot_W;
				break;
			case Character::Riven:
				AttackResetSlot = SpellSlot_Q;
				IsDashAttackReset = true;
				break;
			case Character::Shyvana:
				AttackResetSlot = SpellSlot_Q;
				break;
			case Character::Sivir:
				AttackResetSlot = SpellSlot_W;
			case Character::Talon:
				AttackResetSlot = SpellSlot_Q;
				break;
			case Character::Trundle:
				AttackResetSlot = SpellSlot_Q;
				break;
			case Character::Vayne:
				AttackResetSlot = SpellSlot_Q;
				IsDashAttackReset = true;
				break;
			case Character::Vi:
				AttackResetSlot = SpellSlot_E;
				break;
			case Character::Volibear:
				AttackResetSlot = SpellSlot_Q;
				break;
			case Character::MonkeyKing:
				AttackResetSlot = SpellSlot_Q;
				break;
			case Character::XinZhao:
				AttackResetSlot = SpellSlot_Q;
				break;
			case Character::Yorick:
				AttackResetSlot = SpellSlot_Q;
				break;
			}

			auto menu = Menu::CreateMenu("Orbwalker", "Orbwalker");

			auto hoykeysMenu = menu->AddMenu("Hotkeys", "Hotkeys");
			Config::Hotkeys::Combo = hoykeysMenu->AddKeyBind("Combo", "Combo", VK_SPACE, false, false, [](KeyBind * self, bool newValue) {
				if (newValue) {
					ActiveMode |= OrbwalkerMode_Combo;
				}
				else {
					ActiveMode &= ~OrbwalkerMode_Combo;
				}
				});
			Config::Hotkeys::Harass = hoykeysMenu->AddKeyBind("Harass", "Harass", 'C', false, false, [](KeyBind * self, bool newValue) {
				if (newValue) {
					ActiveMode |= OrbwalkerMode_Harass;
				}
				else {
					ActiveMode &= ~OrbwalkerMode_Harass;
				}
				});
			Config::Hotkeys::LaneClear = hoykeysMenu->AddKeyBind("LaneClear", "LaneClear", 'V', false, false, [](KeyBind * self, bool newValue) {
				if (newValue) {
					ActiveMode |= OrbwalkerMode_LaneClear;
				}
				else {
					ActiveMode &= ~OrbwalkerMode_LaneClear;
				}
				});
			Config::Hotkeys::JungleClear = hoykeysMenu->AddKeyBind("JungleClear", "JungleClear", 'V', false, false, [](KeyBind * self, bool newValue) {
				if (newValue) {
					ActiveMode |= OrbwalkerMode_JungleClear;
				}
				else {
					ActiveMode &= ~OrbwalkerMode_JungleClear;
				}
				});
			Config::Hotkeys::LastHit = hoykeysMenu->AddKeyBind("LastHit", "LastHit", 'X', false, false, [](KeyBind * self, bool newValue) {
				if (newValue) {
					ActiveMode |= OrbwalkerMode_LastHit;
				}
				else {
					ActiveMode &= ~OrbwalkerMode_LastHit;
				}
				});
			Config::Hotkeys::Flee = hoykeysMenu->AddKeyBind("Flee", "Flee", 'T', false, false, [](KeyBind * self, bool newValue) {
				if (newValue) {
					ActiveMode |= OrbwalkerMode_Flee;
				}
				else {
					ActiveMode &= ~OrbwalkerMode_Flee;
				}
				});

			auto configurationMenu = menu->AddMenu("Configuration", "Configuration");
			Config::Configuration::LaneClearHeroes = configurationMenu->AddCheckBox("LaneClearHeroes", "Attack heroes in laneclear", true);
			Config::Configuration::LaneClearHeroes->AddTooltip("It will attack heroes when lane clearing");
			Config::Configuration::SupportMode = configurationMenu->AddCheckBox(("SupportMode" + ObjectManager::Player->SkinName).c_str(), "Support mode");
			Config::Configuration::HoldRadius = configurationMenu->AddSlider("HoldRadius", "Hold radius", 100, 0, 100);
			Config::Configuration::MovementDelay = configurationMenu->AddSlider("MovementDelay", "Movement delay", 100, 0, 500, 10);
			Config::Configuration::ExtraWindUpTime = configurationMenu->AddSlider("ExtraWindUpTime", "Extra windup time", 0, 0, 200, 10);

			auto farmingMenu = menu->AddMenu("Farming", "Farming");
			Config::Farming::LastHitPriority = farmingMenu->AddCheckBox("LastHitPriority", "Prioritize lasthit over harass", true);
			Config::Farming::PushPriority = farmingMenu->AddCheckBox("PushPriority", "Prioritize push over freeze", true);
			Config::Farming::ExtraFarmDelay = farmingMenu->AddSlider("ExtraFarmDelay", "Extra farm delay", 0, -80, 80, 10);

			auto meleeMenu = menu->AddMenu("Melee", "Melee");
			Config::Melee::StickToTarget = meleeMenu->AddCheckBox("StickToTarget", "Stick to target", false);

			auto drawingsMenu = menu->AddMenu("Drawings", "Drawings");
			Config::Drawings::AttackRange = drawingsMenu->AddCheckBox("AttackRange", "Attack range", true);
			if (IsAzir) {
				Config::Drawings::AzirSoldierAttackRange = drawingsMenu->AddCheckBox("AzirSoldierAttackRange", "Azir soldier attack range", true);
			}
			Config::Drawings::EnemyAttackRange = drawingsMenu->AddCheckBox("EnemyAttackRange", "Enemy attack range", true);
			Config::Drawings::HoldRadius = drawingsMenu->AddCheckBox("HoldRadius", "Hold radius", true);
			Config::Drawings::LasthittableMinions = drawingsMenu->AddCheckBox("LasthittableMinions", "Lasthittable minions", true);

			EventManager::AddEventHandler(LeagueEvents::OnIssueOrder, OnIssueOrder);
			EventManager::AddEventHandler(LeagueEvents::OnSpellCast, OnSpellCast);
			EventManager::AddEventHandler(LeagueEvents::OnProcessSpell, OnProcessSpell);
			EventManager::AddEventHandler(LeagueEvents::OnStopCast, OnStopCast);
			EventManager::AddEventHandler(LeagueEvents::OnNewPath, OnNewPath);
			EventManager::AddEventHandler(LeagueEvents::OnCreateObject, OnCreateObject);
			EventManager::AddEventHandler(LeagueEvents::OnDeleteObject, OnDeleteObject);
			EventManager::AddEventHandler(LeagueEvents::OnPresent, OnGameUpdate);
			EventManager::AddEventHandler(LeagueEvents::OnPresent, OnDraw);
		}

		void Orbwalker::Dispose() {
			EventManager::RemoveEventHandler(LeagueEvents::OnIssueOrder, OnIssueOrder);
			EventManager::RemoveEventHandler(LeagueEvents::OnSpellCast, OnSpellCast);
			EventManager::RemoveEventHandler(LeagueEvents::OnProcessSpell, OnProcessSpell);
			EventManager::RemoveEventHandler(LeagueEvents::OnStopCast, OnStopCast);
			EventManager::RemoveEventHandler(LeagueEvents::OnNewPath, OnNewPath);
			EventManager::RemoveEventHandler(LeagueEvents::OnCreateObject, OnCreateObject);
			EventManager::RemoveEventHandler(LeagueEvents::OnDeleteObject, OnDeleteObject);
			EventManager::RemoveEventHandler(LeagueEvents::OnPresent, OnGameUpdate);
			EventManager::RemoveEventHandler(LeagueEvents::OnPresent, OnDraw);
		}

		bool Orbwalker::OnIssueOrder(GameObject* unit, GameObjectOrder order, Vector3 position, GameObject* target) {
			if (unit == ObjectManager::Player) {
				switch (order) {
				case GameObjectOrder::MoveTo:
					LastOrder = GameObjectOrder::MoveTo;
					LastMoveOrder = ClockFacade::Instance->GetGameTime();
					LastMovePosition = position;
					LastTarget = nullptr;
					break;
				case GameObjectOrder::AttackUnit:
					LastOrder = GameObjectOrder::AttackUnit;
					LastAttackOrder = ClockFacade::Instance->GetGameTime();
					LastTarget = target;
					break;
				case GameObjectOrder::Stop:
					LastOrder = GameObjectOrder::Stop;
					LastTarget = nullptr;
					break;
				}
			}

			return true;
		}

		void Orbwalker::OnSpellCast(kSpellSlot slot) {
			if (slot == AttackResetSlot && !IsDashAttackReset) {
				if (IsAshe) {
					LastAttack -= ObjectManager::Player->GetAttackDelay() * 0.4f;
					LastAttackOrder = 0.0f;
				}
				else if (IsRengar) {
					auto pathController = ObjectManager::Player->GetPathController();
					if (!pathController->HasNavigationPath || !pathController->GetNavigationPath()->IsDashing) {
						ResetAutoAttack();
					}
				}
				else if (!AttackResetHash || ObjectManager::Player->GetSpell(slot)->SpellData->Script->Hash == AttackResetHash) {
					ResetAutoAttack();
				}
			}
			else if (slot >= SpellSlot_Item1 && slot <= SpellSlot_Item6) {
				auto inventorySlot = ObjectManager::Player->HeroInventory.Slots[slot - SpellSlot_Item1];
				auto itemInfo = inventorySlot->ItemInfo;
				if (itemInfo && itemInfo->ItemData->ItemId == Item::Titanic_Hydra) {
					ResetAutoAttack();
				}
			}
		}

		void Orbwalker::OnProcessSpell(GameObject * unit, SpellCastInfo * castInfo) {
			if (unit == ObjectManager::Player) {
				LastOrder = GameObjectOrder::None;
				LastMovePosition = Vector3::Zero;

				if (castInfo->IsAutoAttack()) {
					LastAttack = castInfo->StartTime;
					LastAttackCastEndTime = castInfo->CastEndTime;
					auto targetId = castInfo->TargetId;
					if (targetId) {
						LastTarget = ObjectManager::Instance->ObjectsArray[targetId];
					}
				}
			}
		}

		void Orbwalker::OnStopCast(GameObject * unit, float castEndTime) {
			if (unit == ObjectManager::Player && castEndTime == LastAttackCastEndTime) {
				ResetAutoAttack();
			}
		}

		void Orbwalker::OnNewPath(GameObject* unit, NavigationPath* navigationPath) {
			if (unit == ObjectManager::Player) {
				if (IsRengar && LastTarget && navigationPath->DashSpeed == 1450.0f) {
					LastAttack = ClockFacade::Instance->GetGameTime() - ObjectManager::Player->GetAttackCastDelay() - NetClient::Instance->GetPing() * 0.001f;
				}
			}
		}

		void Orbwalker::OnCreateObject(GameObject* unit) {
			if (IsAzir && unit->Flags() & GameObjectFlags_AIMinionClient && unit->BaseCharacterData->SkinHash == Character::AzirSoldier) {
				AzirSoldiers.push_back(unit);
			}
		}

		void Orbwalker::OnDeleteObject(GameObject* unit) {
			if (IsAzir) {
				for (auto it = AzirSoldiers.begin(); it != AzirSoldiers.end(); it++) {
					if (unit == *it) {
						AzirSoldiers.erase(it);
						break;
					}
				}
			}
			if (unit == LastTarget) {
				LastTarget = nullptr;
			}
			if (unit == ForcedTarget) {
				ForcedTarget = nullptr;
			}
		}

		void Orbwalker::OnGameUpdate() {
			if (LastTarget && !LastTarget->IsValidTarget()) {
				LastTarget = nullptr;
			}

			LastHitMinion = nullptr;
			AlmostLastHitMinion = nullptr;
			LaneClearMinion = nullptr;

			if (ActiveMode != OrbwalkerMode_None || Config::Drawings::LasthittableMinions->Value) {
				for (auto minion : *ManagerTemplate::Minions) {
					if (minion->Team != GameObjectTeam_Neutral - ObjectManager::Player->Team || !ObjectManager::Player->IsInAutoAttackRange(minion) || !minion->IsValidTarget()) {
						continue;
					}

					auto attackCastDelay = GetAttackCastDelay(minion);
					auto attackMissileSpeed = GetAttackMissileSpeed();
					auto lastHitHealth = minion->Health;
					auto laneClearHealth = lastHitHealth;

					auto LastHitMinion_lastHitHealth = FLT_MAX;
					auto AlmostLastHitMinion_laneClearHealth = FLT_MAX;
					auto LaneClearMinion_laneClearHealth = 0;

					for (auto attack : HealthPrediction::IncomingAttacks) {
						if (attack.Target == minion) {
							lastHitHealth -= attack.GetDamage(attackCastDelay + (attackMissileSpeed != FLT_MAX ? std::max(0.0f, minion->GetPathController()->ServerPosition.Distance(ObjectManager::Player->GetPathController()->ServerPosition) - ObjectManager::Player->GetBoundingRadius()) / attackMissileSpeed : 0.0f) + std::max(0.0f, LastAttack + GetAttackDelay(minion) - ClockFacade::Instance->GetGameTime()) + Config::Farming::ExtraFarmDelay->Value * 0.001f);
							laneClearHealth -= attack.GetDamage(attackCastDelay + GetAttackDelay(minion) + (attackMissileSpeed != FLT_MAX ? ObjectManager::Player->GetAutoAttackRange(minion) / attackMissileSpeed : 0.0f) + Config::Farming::ExtraFarmDelay->Value * 0.001f);
						}
					}

					auto health = laneClearHealth; // lastHitHealth if turret is targetting
					auto attackDamage = Damage::CalculateAutoAttackDamage(ObjectManager::Player, minion);

					if (lastHitHealth > 0 && lastHitHealth < attackDamage) {
						if (!LastHitMinion || (minion->MaxHealth == LastHitMinion->MaxHealth ? lastHitHealth < LastHitMinion_lastHitHealth : minion->MaxHealth > LastHitMinion->MaxHealth)) {
							LastHitMinion = minion;
							LastHitMinion_lastHitHealth = lastHitHealth;
						}
					}
					else if (health <= (minion->IsSiegeMinion() ? 1.5f : 1.0f) * attackDamage && health < minion->Health) {
						if (!AlmostLastHitMinion || (minion->MaxHealth == AlmostLastHitMinion->MaxHealth ? laneClearHealth < AlmostLastHitMinion_laneClearHealth : minion->MaxHealth > AlmostLastHitMinion->MaxHealth)) {
							AlmostLastHitMinion = minion;
							AlmostLastHitMinion_laneClearHealth = laneClearHealth;
							LastShouldWait = ClockFacade::Instance->GetGameTime();
						}
					}
					else if (ActiveMode & OrbwalkerMode_LaneClear) {
						bool isLaneClearMinion = true;
						for (auto turret : *ManagerTemplate::Turrets) {
							if (turret->IsAlly() && turret->IsInAutoAttackRange(minion)) {
								if (laneClearHealth == minion->Health) {
									auto turretDamage = Damage::CalculateAutoAttackDamage(turret, minion);
									for (auto minionHealth = minion->Health; minionHealth > 0.0f && turretDamage > 0.0f; minionHealth -= turretDamage) {
										if (minionHealth <= attackDamage) {
											isLaneClearMinion = false;
											break;
										}
									}
									if (!LaneClearMinion || (Config::Farming::PushPriority->Value ? laneClearHealth < LaneClearMinion_laneClearHealth : laneClearHealth > LaneClearMinion_laneClearHealth)) {
										LaneClearMinion = minion;
										LaneClearMinion_laneClearHealth = laneClearHealth;
									}
								}
								isLaneClearMinion = false;
								break;
							}
						}

						if (!isLaneClearMinion) {
							continue;
						}

						if (laneClearHealth > 2.0f * attackDamage || laneClearHealth == minion->Health) {
							if (!LaneClearMinion || (Config::Farming::PushPriority->Value ? laneClearHealth < LaneClearMinion_laneClearHealth : laneClearHealth > LaneClearMinion_laneClearHealth)) {
								LaneClearMinion = minion;
								LaneClearMinion_laneClearHealth = laneClearHealth;
							}
						}
					}
				}
			}

			if (ActiveMode != OrbwalkerMode_None) {
				OrbwalkTo(GetOrbwalkPosition());
			}
		}

		void Orbwalker::OnDraw() {
			if (Config::Drawings::AttackRange->Value) {
				Renderer::AddCircle(ObjectManager::Player->Position, ObjectManager::Player->GetAutoAttackRange(), 2.0f, IM_COL32(144, 238, 144, 255));
			}

			if (Config::Drawings::HoldRadius->Value) {
				Renderer::AddCircle(ObjectManager::Player->Position, Config::Configuration::HoldRadius->Value, 2.0f, IM_COL32(144, 238, 144, 255));
			}

			if (Config::Drawings::EnemyAttackRange->Value) {
				for (auto hero : *ManagerTemplate::Heroes) {
					if (hero->IsEnemy() && hero->IsValidTarget()) {
						auto range = hero->GetAutoAttackRange(ObjectManager::Player);
						Renderer::AddCircle(hero->Position, range, 2.0f, hero->ServerPosition().IsInRange(ObjectManager::Player->GetPathController()->ServerPosition, range) ? IM_COL32(255, 69, 0, 255) : IM_COL32(144, 238, 144, 255));
					}
				}
			}

			if (Config::Drawings::LasthittableMinions->Value) {
				if (LastHitMinion) {
					Renderer::AddCircle(LastHitMinion->Position, LastHitMinion->GetBoundingRadius(), 2.0f, IM_COL32(255, 255, 255, 255));
				}
				if (AlmostLastHitMinion && AlmostLastHitMinion != LastHitMinion) {
					Renderer::AddCircle(AlmostLastHitMinion->Position, AlmostLastHitMinion->GetBoundingRadius(), 2.0f, IM_COL32(255, 69, 0, 255));
				}
			}

			if (IsAzir && Config::Drawings::AzirSoldierAttackRange->Value) {
				for (auto soldier : AzirSoldiers) {
					if (!soldier->IsDead() && ObjectManager::Player->GetPathController()->ServerPosition.IsInRange(soldier->Position, 790.0f)) {
						auto pathController = soldier->GetPathController();
						if ((!pathController->HasNavigationPath || !pathController->GetNavigationPath()->IsDashing)) {
							Renderer::AddCircle(soldier->Position, soldier->GetAutoAttackRange(), 2.0f, IM_COL32(144, 238, 144, 255));
						}
					}
				}
			}
		}

		void Orbwalker::ResetAutoAttack() {
			LastAttack = 0.0f;
			LastAttackOrder = 0.0f;
			LastMoveOrder = 0.0f;
			LastAttackCastEndTime = 0.0f;
		}

		Vector3 Orbwalker::GetOrbwalkPosition() {
			if (ForcedPosition.IsValid()) {
				return ForcedPosition;
			}
			else if (ObjectManager::Player->IsMelee() && Config::Melee::StickToTarget->Value && !(ActiveMode & OrbwalkerMode_Flee) && LastTarget) {
				auto pathController = LastTarget->GetPathController();
				if ((LastTarget->IsMonster() || LastTarget->IsHero()) && pathController->HasNavigationPath && ObjectManager::Player->ServerPosition().IsInRange(pathController->ServerPosition, ObjectManager::Player->GetAutoAttackRange(LastTarget) + 150.0f)) {
					return pathController->GetNavigationPath()->EndPosition;
				}
			}

			return HudManager::Instance->CursorTargetLogic->CursorPosition;
		}

		GameObject* Orbwalker::GetTarget() {
			if (ForcedTarget && ForcedTarget->IsValidTarget()) {
				return ObjectManager::Player->IsInAutoAttackRange(ForcedTarget) ? ForcedTarget : nullptr;
			}

			if (ActiveMode & OrbwalkerMode_Combo) {
				auto hero = GetTargetByType(OrbwalkerTargetType::Hero);
				if (hero) {
					return hero;
				}
			}

			if (ActiveMode & OrbwalkerMode_Harass) {
				auto structure = GetTargetByType(OrbwalkerTargetType::Structure);

				if (structure) {
					if (!Config::Farming::LastHitPriority->Value) {
						return structure;
					}
					auto minion = GetTargetByType(OrbwalkerTargetType::Minion);
					if (minion) {
						return minion;
					}
					if (!ShouldWait()) {
						return structure;
					}
				}
				else {
					auto hero = GetTargetByType(OrbwalkerTargetType::Hero);
					if (hero && !Config::Farming::LastHitPriority->Value) {
						return hero;
					}
					auto minion = GetTargetByType(OrbwalkerTargetType::Minion);
					if (minion) {
						return minion;
					}
					if (hero && !ShouldWait()) {
						return hero;
					}
				}
			}

			if (ActiveMode & OrbwalkerMode_LastHit) {
				auto minion = GetTargetByType(OrbwalkerTargetType::Minion);
				if (minion) {
					return minion;
				}
			}

			if (ActiveMode & OrbwalkerMode_LaneClear) {
				auto structure = GetTargetByType(OrbwalkerTargetType::Structure);

				if (structure) {
					if (!Config::Farming::LastHitPriority->Value) {
						return structure;
					}
					auto minion = GetTargetByType(OrbwalkerTargetType::Minion);
					if (minion && minion == LastHitMinion) {
						return minion;
					}
					if (!ShouldWait()) {
						return structure;
					}
				}
				else {
					auto hero = GetTargetByType(OrbwalkerTargetType::Hero);
					if (hero && Config::Configuration::LaneClearHeroes->Value && !Config::Farming::LastHitPriority->Value) {
						return hero;
					}
					auto minion = GetTargetByType(OrbwalkerTargetType::Minion);
					if (minion && minion == LastHitMinion) {
						return minion;
					}
					if (hero && Config::Configuration::LaneClearHeroes->Value && !ShouldWait()) {
						return hero;
					}
					if (minion) {
						return minion;
					}
				}
			}

			if (ActiveMode & OrbwalkerMode_JungleClear) {
				return GetTargetByType(OrbwalkerTargetType::Monster);
			}

			return nullptr;
		}

		GameObject* Orbwalker::GetTargetByType(OrbwalkerTargetType targetType) {
			switch (targetType) {
			case OrbwalkerTargetType::Hero: {
				if (IsAzir) {
					std::vector<GameObject*> soldierTargets;
					for (auto hero : *ManagerTemplate::Heroes) {
						if (hero && hero->IsEnemy() && hero->IsValidTarget()) {
							for (auto soldier : AzirSoldiers) {
								if (!soldier->IsDead() && soldier->IsInAutoAttackRange(hero) && ObjectManager::Player->GetPathController()->ServerPosition.IsInRange(soldier->Position, 790.0f)) {
									auto pathController = soldier->GetPathController();
									if ((!pathController->HasNavigationPath || !pathController->GetNavigationPath()->IsDashing)) {
										soldierTargets.push_back(hero);
										break;
									}
								}
							}
						}
					}
					auto target = TargetSelector::GetTarget(soldierTargets, DamageType_Magical);
					if (target && ObjectManager::Player->IsInAutoAttackRange(target)) {
						return target;
					}
				}

				std::vector<GameObject*> heroes;
				for (auto hero : *ManagerTemplate::Heroes) {
					if (hero->IsEnemy() && hero->IsValidTarget() && ObjectManager::Player->IsInAutoAttackRange(hero)) {
						heroes.push_back(hero);
					}
				}

				return TargetSelector::GetTarget(heroes, DamageType_Physical);
			}
			case OrbwalkerTargetType::Monster: {
				GameObject* monster = nullptr;
				float highestMaxHealth = 0.0f;
				for (auto minion : *ManagerTemplate::Minions) {
					if (minion && minion->IsMonster() && minion->IsValidTarget() && ObjectManager::Player->IsInAutoAttackRange(minion)) {
						if (minion->MaxHealth > highestMaxHealth) {
							monster = minion;
							highestMaxHealth = minion->MaxHealth;
						}
					}
				}
				return monster;
			}
			case OrbwalkerTargetType::Minion: {
				auto supportMode = false;
				if (Config::Configuration::SupportMode->Value) {
					for (auto hero : *ManagerTemplate::Heroes) {
						if (hero != ObjectManager::Player && hero->IsAlly() && hero->IsValidTarget(1050.0f)) {
							supportMode = true;
							break;
						}
					}
				}

				if (!supportMode || ObjectManager::Player->FindBuff(0xC406EAE0)) { // "TalentReaper"
					if (LastHitMinion) {
						if (AlmostLastHitMinion && AlmostLastHitMinion != LastHitMinion && AlmostLastHitMinion->IsSiegeMinion()) {
							return nullptr;
						}
						return LastHitMinion;
					}
					if (supportMode || ShouldWait()) {
						return nullptr;
					}
					if (ActiveMode & OrbwalkerMode_LaneClear) {
						return LaneClearMinion;
					}
				}
				break;
			}
			case OrbwalkerTargetType::Structure: {
				for (auto unit : *ManagerTemplate::AIBases) {
					if (unit->IsEnemy() && !unit->IsDead() && unit->IsTargetable && unit->IsStructure() && ObjectManager::Player->GetPathController()->ServerPosition.IsInRange(unit->Position, ObjectManager::Player->GetAutoAttackRange(unit))) {
						return unit;
					}
				}
				break;
			}
			}

			return nullptr;
		}

		bool Orbwalker::ShouldWait() {
			return ClockFacade::Instance->GetGameTime() - LastShouldWait <= 0.4f || AlmostLastHitMinion;
		}

		void Orbwalker::OrbwalkTo(Vector3 position) {
			if (ClockFacade::Instance->GetGameTime() - LastAttackOrder < 0.07f + NetClient::Instance->GetPing() * 0.001f) {
				return;
			}

			if (CanAttack()) {
				auto target = GetTarget();
				if (target) {
					ObjectManager::Player->IssueOrder(GameObjectOrder::AttackUnit, target);
					return;
				}
			}

			MoveTo(position);
		}

		void Orbwalker::MoveTo(Vector3 position) {
			if (!CanMove() || ClockFacade::Instance->GetGameTime() - LastMoveOrder < Config::Configuration::MovementDelay->Value * 0.001f) {
				return;
			}

			auto playerPosition = ObjectManager::Player->Position;
			auto movePosition = playerPosition.DistanceSquared(position) < 10000.0f ? playerPosition.Extended(position, 100.0f) : position;
			auto order = GameObjectOrder::MoveTo;

			auto holdRadius = Config::Configuration::HoldRadius->Value;
			if (holdRadius > 0) {
				if (playerPosition.DistanceSquared(position) <= holdRadius * holdRadius) {
					movePosition = playerPosition;
					order = GameObjectOrder::Stop;
				}
			}

			if (order == LastOrder) {
				switch (LastOrder) {
				case GameObjectOrder::Stop:
					return;
				case GameObjectOrder::MoveTo:
					if (movePosition == LastMovePosition && ObjectManager::Player->GetPathController()->HasNavigationPath) {
						return;
					}
					break;
				}
			}

			ObjectManager::Player->IssueOrder(order, movePosition);
		}

		float Orbwalker::GetAttackCastDelay(GameObject* target) {
			if (IsAzir && target) {
				for (auto soldier : AzirSoldiers) {
					if (soldier->IsInAutoAttackRange(target)) {
						return soldier->GetAttackCastDelay();
					}
				}
			}

			return ObjectManager::Player->GetAttackCastDelay();
		}

		float Orbwalker::GetAttackDelay(GameObject* target) {
			if (IsAzir && target) {
				for (auto soldier : AzirSoldiers) {
					if (soldier->IsInAutoAttackRange(target)) {
						return soldier->GetAttackDelay();
					}
				}
			}

			return ObjectManager::Player->GetAttackDelay();
		}

		float Orbwalker::GetAttackMissileSpeed() {
			switch (ObjectManager::Player->BaseCharacterData->SkinHash) {
			case Character::Thresh:
			case Character::Azir:
			case Character::Velkoz:
			case Character::Rakan:
				return FLT_MAX;
			case Character::Viktor:
				if (ObjectManager::Player->FindBuff("ViktorPowerTransferReturn")) {
					return FLT_MAX;
				}
				break;
			case Character::Jinx:
				if (ObjectManager::Player->FindBuff("JinxQ")) {
					return 2000.0f;
				}
				break;
			case Character::Poppy:
				if (ObjectManager::Player->FindBuff("poppypassivebuff")) {
					return 1600.0f;
				}
				break;
			case Character::Ivern:
				if (ObjectManager::Player->FindBuff("ivernwpassive")) {
					return 1600.0f;
				}
				break;
			case Character::Caitlyn:
				if (ObjectManager::Player->FindBuff("caitlynheadshot")) {
					return 3000.0f;
				}
				break;
			case Character::Twitch:
				if (ObjectManager::Player->FindBuff("TwitchFullAutomatic")) {
					return 4000.0f;
				}
				break;
			case Character::Jayce:
				if (ObjectManager::Player->FindBuff("jaycestancegun")) {
					return 2000.0f;
				}
				return FLT_MAX;
			}

			return ObjectManager::Player->IsMelee() ? FLT_MAX : ObjectManager::Player->GetBasicAttack()->Resource->MissileSpeed;
		}

		bool Orbwalker::CanAttack() {
			if (!(ObjectManager::Player->ActionState & GameObjectActionState_CanAttack)) {
				return false;
			}

			auto activeSpell = ObjectManager::Player->Spellbook.ActiveSpellInstance;
			if (activeSpell) {
				auto castInfo = activeSpell->GetCastInfo();
				if (castInfo->SpellData->Resource->ChannelIsInterruptedByAttacking && (!castInfo->IsInstantCast || !castInfo->SpellWasCast)) {
					return false;
				}
			}

			auto time = ClockFacade::Instance->GetGameTime();
			auto ping = NetClient::Instance->GetPing() * 0.0005f;

			if (AttackUsesAmmo && time + ping <= ObjectManager::Player->PassiveCooldownEndTime) {
				return false;
			}

			return time + ping > LastAttack + GetAttackDelay();
		}

		bool Orbwalker::CanMove() {
			if (!(ObjectManager::Player->ActionState & GameObjectActionState_CanMove)) {
				return false;
			}

			auto activeSpell = ObjectManager::Player->Spellbook.ActiveSpellInstance;
			if (activeSpell) {
				auto castInfo = activeSpell->GetCastInfo();
				if (!castInfo->SpellData->Resource->CanMoveWhileChanneling && (!castInfo->IsInstantCast || !castInfo->SpellWasCast)) {
					return false;
				}
			}

			return ClockFacade::Instance->GetGameTime() + NetClient::Instance->GetPing() * 0.0005f > LastAttackCastEndTime + Config::Configuration::ExtraWindUpTime->Value * 0.001f;
		}
	}
}