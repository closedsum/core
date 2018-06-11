// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_FX.h"

// FxPriority
EMCsFxPriority* EMCsFxPriority::Instance;

EMCsFxPriority& EMCsFxPriority::Get()
{
	if (!Instance)
		Instance = new EMCsFxPriority();
	return *Instance;
}

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