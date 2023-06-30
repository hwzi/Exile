#include "stdafx.h"
#include "ObjectManager.h"

namespace Exile
{
	ObjectManager* ObjectManager::Instance;
	GameObject* ObjectManager::Player;

	GameObject* ObjectManager::Get(unsigned short id) {
		if (id >= this->MaxObjects) {
			return nullptr;
		}

		return this->ObjectsArray[id];
	}
}