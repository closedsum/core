// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes.h"

// Level
#pragma region

namespace ECsLevelState
{
	namespace Str
	{
		const TCsString None = TCsString(TEXT("None"), TEXT("none"));
		const TCsString Loaded = TCsString(TEXT("Loaded"), TEXT("loaded"));
		const TCsString BeginTransition = TCsString(TEXT("BeginTransition"), TEXT("begintransition"));
		const TCsString InTransition = TCsString(TEXT("InTransition"), TEXT("intransition"));
	}

	namespace Ref
	{
		const Type None = Type::None;
		const Type Loaded = Type::Loaded;
		const Type BeginTransition = Type::BeginTransition;
		const Type InTransition = Type::InTransition;
		const Type ECsLevelState_MAX = Type::ECsLevelState_MAX;
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
		const TCsString X = TCsString(TEXT("X"), TEXT("x"), TEXT("roll"));
		const TCsString Y = TCsString(TEXT("Y"), TEXT("y"), TEXT("pitch"));
		const TCsString Z = TCsString(TEXT("Z"), TEXT("z"), TEXT("yaw"));
	}

	namespace Ref
	{
		const Type X = Type::X;
		const Type Y = Type::Y;
		const Type Z = Type::Z;
		const Type ECsAxes_Editor_MAX = Type::ECsAxes_Editor_MAX;
	}
}

namespace ECsTransformMember
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Location = TCsString(TEXT("Location"), TEXT("location"));
		const TCsString Rotation = TCsString(TEXT("Rotation"), TEXT("rotation"));
		const TCsString Scale = TCsString(TEXT("Scale"), TEXT("scale"));
	}

	namespace Ref
	{
		const Type Location = Type::Location;
		const Type Rotation = Type::Rotation;
		const Type Scale = Type::Scale;
		const Type ECsTransformMember_MAX = Type::ECsTransformMember_MAX;
	}
}

#pragma endregion Transform

// Physics
#pragma region

namespace ECsPhysicsImpulseType
{
	namespace Str
	{
		const TCsString AddForce = TCsString(TEXT("AddForce"), TEXT("addforce"));
		const TCsString AddForceAtPosition = TCsString(TEXT("AddForceAtPosition"), TEXT("addforceatposition"));
		const TCsString AddTorque = TCsString(TEXT("AddTorque"), TEXT("addtorque"));
		const TCsString AddAngularImpulse = TCsString(TEXT("AddAngularImpulse"), TEXT("addangularimpulse"));
		const TCsString AddImpulse = TCsString(TEXT("AddImpulse"), TEXT("addimpulse"));
		const TCsString AddImpulseAtPosition = TCsString(TEXT("AddImpulseAtPosition"), TEXT("addimpulseatposition"));
	}

	namespace Ref
	{
		const Type AddForce = Type::AddForce;
		const Type AddForceAtPosition = Type::AddForceAtPosition;
		const Type AddTorque = Type::AddTorque;
		const Type AddAngularImpulse = Type::AddAngularImpulse;
		const Type AddImpulse = Type::AddImpulse;
		const Type AddImpulseAtPosition = Type::AddImpulseAtPosition;
		const Type ECsPhysicsImpulseType_MAX = Type::ECsPhysicsImpulseType_MAX;
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
		const TCsString DT_OculusRift = TCsString(TEXT("DT_OculusRift"), TEXT("dt_oculusrift"), TEXT("oculus rift"));
		const TCsString DT_Morpheus = TCsString(TEXT("DT_Morpheus"), TEXT("dt_morpheus"), TEXT("psvr"));
		const TCsString DT_ES2GenericStereoMesh = TCsString(TEXT("DT_ES2GenericStereoMesh"), TEXT("dt_es2genericstereomesh"), TEXT("es2 generic"));
		const TCsString DT_SteamVR = TCsString(TEXT("DT_SteamVR"), TEXT("dt_steamvr"), TEXT("vive"));
		const TCsString DT_GearVR = TCsString(TEXT("DT_GearVR"), TEXT("dt_gearvr"), TEXT("gearvr"));
		const TCsString DT_GoogleVR = TCsString(TEXT("DT_GoogleVR"), TEXT("dt_googlevr"), TEXT("goolgevr"));
	}

	namespace Ref
	{
		const Type DT_OculusRift = Type::DT_OculusRift;
		const Type DT_Morpheus = Type::DT_Morpheus;
		const Type DT_ES2GenericStereoMesh = Type::DT_ES2GenericStereoMesh;
		const Type DT_SteamVR = Type::DT_SteamVR;
		const Type DT_GearVR = Type::DT_GearVR;
		const Type DT_GoogleVR = Type::DT_GoogleVR;
		const Type ECsHMDDeviceType_MAX = Type::ECsHMDDeviceType_MAX;
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
		const TCsString Mouse = TCsString(TEXT("Mouse"), TEXT("mouse"), TEXT("mouse"));
		const TCsString MotionController = TCsString(TEXT("MotionController"), TEXT("motioncontroller"), TEXT("motion controller"));
	}

	namespace Ref
	{
		const Type Mouse = Type::Mouse;
		const Type MotionController = Type::MotionController;
		const Type ECsGestureDevice_MAX = Type::ECsGestureDevice_MAX;
	}
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