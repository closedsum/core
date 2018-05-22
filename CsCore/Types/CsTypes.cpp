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

#pragma endregion Transform