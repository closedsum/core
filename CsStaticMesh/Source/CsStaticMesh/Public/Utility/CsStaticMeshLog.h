// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/UnrealString.h"

namespace NCsStaticMesh
{
	struct CSSTATICMESH_API FLog final
	{
	public:

		static void Warning(const FString& Str);

		static void Error(const FString& Str);
	};
}