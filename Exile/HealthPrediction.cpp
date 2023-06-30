#include "stdafx.h"
#include "HealthPrediction.h"
#include "EventManager.h"
#include "ClockFacade.h"
#include "ObjectManager.h"
#include "Damage.h"
#include "NetClient.h"

namespace Exile {
	namespace SDK {
		std::vector<IncomingAttack> HealthPrediction::IncomingAttacks;

		IncomingAttack::IncomingAttack(GameObject* source, GameObject* target, Vector3 sourcePosition, float castDelay, float delay, float missileSpeed, float startTime, float damage) {
			this->Source = source;
			this->Target = target;
			this->SourcePosition = sourcePosition;
			this->CastDelay = castDelay;
			this->Delay = delay;
			this->MissileSpeed = missileSpeed;
			this->StartTime = startTime;
			this->Damage = damage;
			this->IsActiveAttack = true;
			this->IsRangedAttack = source->IsRanged();
		}

		float IncomingAttack::GetDamage(float time) {
			time += NetClient::Instance->GetPing() * 0.0005f;
			auto damage = 0.0f;
			
			auto timeTillHit = this->StartTime + this->CastDelay - ClockFacade::Instance->GetGameTime();
			if (this->IsRangedAttack) {
				timeTillHit += std::max(0.0f, this->Target->GetPathController()->ServerPosition.Distance(this->SourcePosition) - this->Source->GetBoundingRadius()) / this->MissileSpeed;
			}

			if (this->IsActiveAttack) {
				while (timeTillHit < time) {
					if (timeTillHit > 0.0f) {
						damage += this->Damage;
					}
					timeTillHit += this->Delay;
				}
			}
			else if (timeTillHit < time && timeTillHit > 0.0f && this->IsRangedAttack) {
				damage += Damage;
			}

			return damage;
		}

		void HealthPrediction::Initialize() {
			EventManager::AddEventHandler(LeagueEvents::OnPresent, OnGameUpdate);
			EventManager::AddEventHandler(LeagueEvents::OnDeleteObject, OnDeleteObject);
			EventManager::AddEventHandler(LeagueEvents::OnProcessSpell, OnProcessSpell);
			EventManager::AddEventHandler(LeagueEvents::OnStopCast, OnStopCast);
		}

		void HealthPrediction::OnGameUpdate() {
			auto time = ClockFacade::Instance->GetGameTime();
			for (auto it = IncomingAttacks.begin(); it != IncomingAttacks.end();) {
				if (it->Target->IsDead() || (it->Source->IsDead() && it->StartTime + it->CastDelay > time)) {
					IncomingAttacks.erase(it);
				}
				else {
					auto timeTillHit = it->StartTime + it->CastDelay - time;
					if (it->IsRangedAttack) {
						timeTillHit += std::max(0.0f, it->Target->GetPathController()->ServerPosition.Distance(it->SourcePosition) - it->Source->GetBoundingRadius()) / it->MissileSpeed;
					}

					if (timeTillHit <= 0.0f) {
						IncomingAttacks.erase(it);
					}
					else {
						it++;
					}
				}
			}
		}

		void HealthPrediction::OnDeleteObject(GameObject* unit) {
			for (auto it = IncomingAttacks.begin(); it != IncomingAttacks.end();) {
				if (unit == it->Source || unit == it->Target) {
					IncomingAttacks.erase(it);
				}
				else {
					it++;
				}
			}
		}

		void HealthPrediction::OnProcessSpell(GameObject* unit, SpellCastInfo* castInfo) {
			if (unit != ObjectManager::Player && unit->IsAlly() && castInfo->IsAutoAttack() && ObjectManager::Player->Position.IsInRange(unit->Position, 2000.0f)) {
				for (auto it = IncomingAttacks.begin(); it != IncomingAttacks.end(); it++) {
					if (unit == it->Source) {
						it->IsActiveAttack = false;
					}
				}

				auto target = ObjectManager::Instance->ObjectsArray[castInfo->TargetId];
				if (target && target->Flags() & GameObjectFlags_AIMinionClient) {
					IncomingAttacks.push_back(IncomingAttack(unit, target, castInfo->StartPosition, castInfo->CastDelay, castInfo->Delay, castInfo->SpellData->Resource->MissileSpeed, castInfo->StartTime, Damage::CalculateAutoAttackDamage(unit, target)));
				}
			}
		}

		void HealthPrediction::OnStopCast(GameObject* unit, float lastCastEndTime) {
			if (unit->IsMelee()) {
				for (auto it = IncomingAttacks.begin(); it != IncomingAttacks.end();) {
					if (it->Source == unit) {
						IncomingAttacks.erase(it);
					}
					else {
						it++;
					}
				}
			}
			else {
				for (auto it = IncomingAttacks.rbegin(); it != IncomingAttacks.rend(); it++) {
					if (it->Source == unit) {
						IncomingAttacks.erase(it.base() - 1);
						break;
					}
				}
			}
		}

		float HealthPrediction::GetHealthPrediction(GameObject* unit, float time) {
			float predictedHealth = unit->Health;

			for (auto attack : IncomingAttacks) {
				if (unit == attack.Target) {
					predictedHealth -= attack.GetDamage(time);
				}
			}

			return predictedHealth;
		}
	}
}