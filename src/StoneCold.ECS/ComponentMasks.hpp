
#ifndef STONECOLD_ECS_COMPONENTMASKS_H
#define STONECOLD_ECS_COMPONENTMASKS_H

#include <unordered_map>
#include "Types.hpp"
#include "Components.hpp"

namespace StoneCold::ECS {

using namespace StoneCold::Core;

//
// Component (Bit-)Masks
//
static auto ComponentMasks = std::unordered_map<scHash, const scBitMask64>({
	{ GetTypeHash<CInput>(),			0x0000000000000001 },
	{ GetTypeHash<CTransform>(),		0x0000000000000002 },
	{ GetTypeHash<CStaticPosition>(),	0x0000000000000004 },
	{ GetTypeHash<CSprite>(),			0x0000000000000008 },
	{ GetTypeHash<CAnimation>(),		0x0000000000000010 },
	{ GetTypeHash<CCollision>(),		0x0000000000000020 },
	{ GetTypeHash<CScore>(),			0x0000000000000040 },
	// { GetTypeHash<ScreenPositionComponent>(),		0x0000000000000080 },
	// { GetTypeHash<ScreenPositionLayeredComponent>(),	0x0000000000000100 },
	// { GetTypeHash<EnemyStateComponent>(),			0x0000000000000200 }
});

template<typename T>
inline scBitMask64 GetComponentMask() { return ComponentMasks[GetTypeHash<T>()]; }

}

#endif
