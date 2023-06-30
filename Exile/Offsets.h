#pragma once

#include "Globals.h"

#define RIOT_BUILD

#if defined(CHINA_BUILD)
#define LOL_VERSION "9.7.269.2391"
#include "OffsetsChina.h"

#elif defined(GARENA_BUILD)
#define LOL_VERSION "9.7.269.2391"
#include "OffsetsGarena.h"

#elif defined(RIOT_BUILD)
#define LOL_VERSION "9.7.269.2391"
#include "OffsetsRiot.h"

#endif

#define DEFINE_RVA(address) ((DWORD)Globals::MainModule + (DWORD)address)
#define DEFINE_RVA_STUB(address) ((DWORD)Globals::StubModule + (DWORD)address)

#define STR_MERGE_IMPL(x, y)				x##y
#define STR_MERGE(x,y)						STR_MERGE_IMPL(x,y)
#define MAKE_PAD(size)						BYTE STR_MERGE(pad_, __COUNTER__) [ size ]
#define DEFINE_MEMBER_0(x)					x;
#define DEFINE_MEMBER_N(x,offset)			struct { MAKE_PAD((DWORD)offset); x; };
#define DEFINE_CHARACTER_INTERMEDIATE(name) DEFINE_MEMBER_N(float name, (DWORD)Offsets::GameObject::CharacterIntermediate + (DWORD)Offsets::CharacterIntermediate::name)
#define DEFINE_EXPERIENCE(type, name) DEFINE_MEMBER_N(type name, (DWORD)Offsets::GameObject::Experience + (DWORD)Offsets::Experience::name)

#define DEFINE_MEMBER_ENCRYPTED(type, name, offset)											\
type name() {																				\
	auto _this = (DWORD)this;																\
	auto _offset = (DWORD)offset;															\
	type result = *(type*)(_this + 4 * *(BYTE*)(_this + _offset + 0x1) + _offset + 0x4);	\
																							\
	auto large_size = *(BYTE*)(_this + _offset + 0x14);										\
	if (large_size) {																		\
		auto key_it = (DWORD*)(_this + _offset + 0x10);										\
		auto i = 0;																			\
		do 																					\
		{																					\
			auto key_dir = *key_it;															\
			key_it++;																		\
			*((DWORD*)&result + i) ^= ~(key_dir ^ 0xB291667B);								\
			i++;																			\
		}																					\
		while (i < large_size);																\
	}																						\
																							\
	auto small_size = *(BYTE*)(_this + _offset + 0x15);										\
	if (small_size) {																		\
		for (BYTE i = 4 - small_size; i < 4; i++) {											\
			*((BYTE*)&result + i) ^= *(BYTE*)(_this + i + _offset + 0x10) ^ 0x7B;			\
		}																					\
	}																						\
																							\
	return result;																			\
}

#define DEFINE_MEMBER_ENCRYPTED_BOOLEAN(name, offset)									\
bool name() {																			\
	auto _this = (DWORD)this;															\
	auto _offset = (DWORD)offset;														\
	BYTE result = *(BYTE*)(_this + *(BYTE*)(_this + _offset + 0x1) + _offset + 0x2);	\
																						\
	auto large_size = *(BYTE*)(_this + _offset + 0x6);									\
	if (large_size) {																	\
		auto key_it = (DWORD*)(_this + _offset + 0x5);									\
		auto i = 0;																		\
		do 																				\
		{																				\
			auto key_dir = *key_it;														\
			key_it++;																	\
			*((DWORD*)&result + i) ^= ~(key_dir ^ 0xB291667B);							\
			i++;																		\
		}																				\
		while (i < large_size);															\
	}																					\
																						\
	auto small_size = *(BYTE*)(_this + _offset + 0x7);									\
	if (!small_size)																	\
		return result;																	\
																						\
	auto i = 1 - small_size;															\
	if (i >= 1)																			\
		return result;																	\
																						\
	do 																					\
	{																					\
		*(&result + i) ^= *(BYTE*)(_this + i + _offset + 0x5) ^ 0x7B;					\
		i++;																			\
	}																					\
	while(i < 1);																		\
																						\
	return result;																		\
}