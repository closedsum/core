// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/UnrealString.h"

namespace NCsProjectile
{
	struct CSPRJ_API FLog final
	{
	public:

		static void Warning(const FString& Str);
	};
}