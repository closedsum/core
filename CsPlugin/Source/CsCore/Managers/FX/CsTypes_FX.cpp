// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsTypes_FX.h"

// FX
#pragma region

namespace NCsFX
{
}

#pragma endregion FX

// FxPriority
#pragma region

namespace ECsFxPriority
{
	namespace Ref
	{
		CSCORE_API const Type Low = EMCsFxPriority::Get().Add(Type::Low, TEXT("Low"));
		CSCORE_API const Type Medium = EMCsFxPriority::Get().Add(Type::Medium, TEXT("Medium"));
		CSCORE_API const Type High = EMCsFxPriority::Get().Add(Type::High, TEXT("High"));
		CSCORE_API const Type ECsFxPriority_MAX = EMCsFxPriority::Get().Add(Type::ECsFxPriority_MAX, TEXT("ECsFxPriority_MAX"), TEXT("MAX"));
	}
}

#pragma endregion FxPriority