// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsSkeletalMeshLog.h"
#include "CsSKeletalMesh.h"

namespace NCsSkeletalMesh
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsSkeletalMesh, Warning, TEXT("%s"), *Str);
	}

	void FLog::Error(const FString& Str)
	{
		UE_LOG(LogCsSkeletalMesh, Error, TEXT("%s"), *Str);
	}
}