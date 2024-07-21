// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/UnrealString.h"

namespace NCsGameplayTags
{
	struct CSGAMEPLAYTAGS_API FLog final
	{
	public:

		static void Warning(const FString& Str);
	
		static void Error(const FString& Str);
	};
}