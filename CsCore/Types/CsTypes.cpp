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