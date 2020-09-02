// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Physics.h"

// PhysicsImpulseType
#pragma region

namespace NCsPhysicsImpulseType
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPhysicsImpulseType, AddForce, "Add Force");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPhysicsImpulseType, AddForceAtPosition, "Add Force at Position");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPhysicsImpulseType, AddTorque, "Add Torque");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPhysicsImpulseType, AddAngularImpulse, "Add Angular Impulse");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPhysicsImpulseType, AddImpulse, "Add Impulse");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPhysicsImpulseType, AddImpulseAtPosition, "Add Impulse at Position");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPhysicsImpulseType, ECsPhysicsImpulseType_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsPhysicsImpulseType_MAX;
}

#pragma endregion PhysicsImpulseType