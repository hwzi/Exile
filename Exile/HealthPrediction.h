#pragma once

#include "GameObject.h"

namespace Exile {
	namespace SDK {
		class IncomingAttack {
		public:
			GameObject* Source;
			GameObject* Target;
			Vector3 SourcePosition;
			float CastDelay;
			float Delay;
			float MissileSpeed;
			float StartTime;
			float Damage;
			bool IsActiveAttack;
			bool IsRangedAttack;

			IncomingAttack(GameObject* source, GameObject* target, Vector3 sourcePosition, float attackCastDelay, float attackDelay, float missileSpeed, float startTime, float damage);
			float GetDamage(float time);
		};

		namespace HealthPrediction {
			extern std::vector<IncomingAttack> IncomingAttacks;

			void Initialize();
			void OnGameUpdate();
			void OnDeleteObject(GameObject* unit);
			void OnProcessSpell(GameObject* unit, SpellCastInfo* castInfo);
			void OnStopCast(GameObject* unit, float lastCastEndTime);

			float GetHealthPrediction(GameObject* unit, float time);
		}
	}
}