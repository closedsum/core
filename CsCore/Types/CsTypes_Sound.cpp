// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Sound.h"
#include "CsCore.h"

// SoundType
EMCsSoundType* EMCsSoundType::Instance;

EMCsSoundType& EMCsSoundType::Get()
{
	if (!Instance)
		Instance = new EMCsSoundType();
	return *Instance;
}

// SoundPriority
EMCsSoundPriority* EMCsSoundPriority::Instance;

EMCsSoundPriority& EMCsSoundPriority::Get()
{
	if (!Instance)
		Instance = new EMCsSoundPriority();
	return *Instance;
}

namespace ECsSoundPriority
{
	namespace Ref
	{
		CSCORE_API const Type VeryLow = EMCsSoundPriority::Get().Add(Type::VeryLow, TEXT("VeryLow"), TEXT("Very Low"));
		CSCORE_API const Type Low = EMCsSoundPriority::Get().Add(Type::Low, TEXT("Low"));
		CSCORE_API const Type Medium = EMCsSoundPriority::Get().Add(Type::Medium, TEXT("Medium"));
		CSCORE_API const Type High = EMCsSoundPriority::Get().Add(Type::High, TEXT("High"));
		CSCORE_API const Type VeryHigh = EMCsSoundPriority::Get().Add(Type::VeryHigh, TEXT("VeryHigh"), TEXT("Very High"));
		CSCORE_API const Type ECsSoundPriority_MAX = EMCsSoundPriority::Get().Add(Type::ECsSoundPriority_MAX, TEXT("ECsSoundPriority_MAX"), TEXT("MAX"));
	}
}