// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Physics.h"

// PhysicsImpulseType
#pragma region

namespace NCsPhysicsImpulseType
{
	namespace Ref
	{
		typedef EMCsPhysicsImpulseType EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(AddForce, "Add Force");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(AddForceAtPosition, "Add Force at Position");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(AddTorque, "Add Torque");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(AddAngularImpulse, "Add Angular Impulse");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(AddImpulse, "Add Impulse");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(AddImpulseAtPosition, "Add Impulse at Position");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPhysicsImpulseType_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsPhysicsImpulseType_MAX;
}

#pragma endregion PhysicsImpulseType