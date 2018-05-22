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