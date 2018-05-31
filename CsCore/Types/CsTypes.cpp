// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes.h"

// Level
#pragma region

namespace ECsLevelState
{
	namespace Str
	{
		CSCORE_API const TCsString None = TCsString(TEXT("None"), TEXT("none"));
		CSCORE_API const TCsString Loaded = TCsString(TEXT("Loaded"), TEXT("loaded"));
		CSCORE_API const TCsString BeginTransition = TCsString(TEXT("BeginTransition"), TEXT("begintransition"));
		CSCORE_API const TCsString InTransition = TCsString(TEXT("InTransition"), TEXT("intransition"));
	}

	namespace Ref
	{
		CSCORE_API const Type None = Type::None;
		CSCORE_API const Type Loaded = Type::Loaded;
		CSCORE_API const Type BeginTransition = Type::BeginTransition;
		CSCORE_API const Type InTransition = Type::InTransition;
		CSCORE_API const Type ECsLevelState_MAX = Type::ECsLevelState_MAX;
	}
}

#pragma endregion Level

// Transform
#pragma region

namespace ECsAxes_Editor
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		CSCORE_API const TCsString X = TCsString(TEXT("X"), TEXT("x"), TEXT("roll"));
		CSCORE_API const TCsString Y = TCsString(TEXT("Y"), TEXT("y"), TEXT("pitch"));
		CSCORE_API const TCsString Z = TCsString(TEXT("Z"), TEXT("z"), TEXT("yaw"));
	}

	namespace Ref
	{
		CSCORE_API const Type X = Type::X;
		CSCORE_API const Type Y = Type::Y;
		CSCORE_API const Type Z = Type::Z;
		CSCORE_API const Type ECsAxes_Editor_MAX = Type::ECsAxes_Editor_MAX;
	}
}

namespace ECsTransformMember
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		CSCORE_API const TCsString Location = TCsString(TEXT("Location"), TEXT("location"));
		CSCORE_API const TCsString Rotation = TCsString(TEXT("Rotation"), TEXT("rotation"));
		CSCORE_API const TCsString Scale = TCsString(TEXT("Scale"), TEXT("scale"));
	}

	namespace Ref
	{
		CSCORE_API const Type Location = Type::Location;
		CSCORE_API const Type Rotation = Type::Rotation;
		CSCORE_API const Type Scale = Type::Scale;
		CSCORE_API const Type ECsTransformMember_MAX = Type::ECsTransformMember_MAX;
	}
}

#pragma endregion Transform

// Surface
#pragma region

EMCsSurfaceType* EMCsSurfaceType::Instance;

EMCsSurfaceType& EMCsSurfaceType::Get()
{
	if (!Instance)
		Instance = new EMCsSurfaceType();
	return *Instance;
}

#pragma endregion Surface

// Physics
#pragma region

namespace ECsPhysicsImpulseType
{
	namespace Str
	{
		CSCORE_API const TCsString AddForce = TCsString(TEXT("AddForce"), TEXT("addforce"));
		CSCORE_API const TCsString AddForceAtPosition = TCsString(TEXT("AddForceAtPosition"), TEXT("addforceatposition"));
		CSCORE_API const TCsString AddTorque = TCsString(TEXT("AddTorque"), TEXT("addtorque"));
		CSCORE_API const TCsString AddAngularImpulse = TCsString(TEXT("AddAngularImpulse"), TEXT("addangularimpulse"));
		CSCORE_API const TCsString AddImpulse = TCsString(TEXT("AddImpulse"), TEXT("addimpulse"));
		CSCORE_API const TCsString AddImpulseAtPosition = TCsString(TEXT("AddImpulseAtPosition"), TEXT("addimpulseatposition"));
	}

	namespace Ref
	{
		CSCORE_API const Type AddForce = Type::AddForce;
		CSCORE_API const Type AddForceAtPosition = Type::AddForceAtPosition;
		CSCORE_API const Type AddTorque = Type::AddTorque;
		CSCORE_API const Type AddAngularImpulse = Type::AddAngularImpulse;
		CSCORE_API const Type AddImpulse = Type::AddImpulse;
		CSCORE_API const Type AddImpulseAtPosition = Type::AddImpulseAtPosition;
		CSCORE_API const Type ECsPhysicsImpulseType_MAX = Type::ECsPhysicsImpulseType_MAX;
	}
}

#pragma endregion Physics

// VR
#pragma region

namespace ECsHMDDeviceType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		CSCORE_API const TCsString DT_OculusRift = TCsString(TEXT("DT_OculusRift"), TEXT("dt_oculusrift"), TEXT("oculus rift"));
		CSCORE_API const TCsString DT_Morpheus = TCsString(TEXT("DT_Morpheus"), TEXT("dt_morpheus"), TEXT("psvr"));
		CSCORE_API const TCsString DT_ES2GenericStereoMesh = TCsString(TEXT("DT_ES2GenericStereoMesh"), TEXT("dt_es2genericstereomesh"), TEXT("es2 generic"));
		CSCORE_API const TCsString DT_SteamVR = TCsString(TEXT("DT_SteamVR"), TEXT("dt_steamvr"), TEXT("vive"));
		CSCORE_API const TCsString DT_GearVR = TCsString(TEXT("DT_GearVR"), TEXT("dt_gearvr"), TEXT("gearvr"));
		CSCORE_API const TCsString DT_GoogleVR = TCsString(TEXT("DT_GoogleVR"), TEXT("dt_googlevr"), TEXT("goolgevr"));
	}

	namespace Ref
	{
		CSCORE_API const Type DT_OculusRift = Type::DT_OculusRift;
		CSCORE_API const Type DT_Morpheus = Type::DT_Morpheus;
		CSCORE_API const Type DT_ES2GenericStereoMesh = Type::DT_ES2GenericStereoMesh;
		CSCORE_API const Type DT_SteamVR = Type::DT_SteamVR;
		CSCORE_API const Type DT_GearVR = Type::DT_GearVR;
		CSCORE_API const Type DT_GoogleVR = Type::DT_GoogleVR;
		CSCORE_API const Type ECsHMDDeviceType_MAX = Type::ECsHMDDeviceType_MAX;
	}
}

#pragma endregion VR

// Gestures
#pragma region

namespace ECsGestureDevice
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		CSCORE_API const TCsString Mouse = TCsString(TEXT("Mouse"), TEXT("mouse"), TEXT("mouse"));
		CSCORE_API const TCsString MotionController = TCsString(TEXT("MotionController"), TEXT("motioncontroller"), TEXT("motion controller"));
	}

	namespace Ref
	{
		CSCORE_API const Type Mouse = Type::Mouse;
		CSCORE_API const Type MotionController = Type::MotionController;
		CSCORE_API const Type ECsGestureDevice_MAX = Type::ECsGestureDevice_MAX;
	}
}

EMCsGestureType* EMCsGestureType::Instance;

EMCsGestureType& EMCsGestureType::Get()
{
	if (!Instance)
		Instance = new EMCsGestureType();
	return *Instance;
}

#pragma endregion Gestures

// Motion Controller
#pragma region

namespace ECsControllerHand
{
	namespace Str
	{
		const TCsString Left = TCsString(TEXT("Left"), TEXT("left"));
		const TCsString Right = TCsString(TEXT("Right"), TEXT("right"));
	}

	namespace Ref
	{
		const Type Left = Type::Left;
		const Type Right = Type::Right;
	}
}

#pragma endregion Motion Controller

// Collision
#pragma region

namespace ECollisionEnabled
{
	namespace Str
	{
		const TCsString NoCollision = TCsString(TEXT("NoCollision"), TEXT("nocollision"), TEXT("no collision"));
		const TCsString QueryOnly = TCsString(TEXT("QueryOnly"), TEXT("queryonly"), TEXT("query only"));
		const TCsString PhysicsOnly = TCsString(TEXT("PhysicsOnly"), TEXT("physicsonly"), TEXT("physics only"));
		const TCsString QueryAndPhysics = TCsString(TEXT("QueryAndPhysics"), TEXT("queryandphysics"), TEXT("query and physics"));
	}

	namespace Ref
	{
		const Type NoCollision = Type::NoCollision;
		const Type QueryOnly = Type::QueryOnly;
		const Type PhysicsOnly = Type::PhysicsOnly;
		const Type QueryAndPhysics = Type::QueryAndPhysics;
	}
}

#pragma endregion Collision