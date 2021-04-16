// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "CsTypes_ScriptEntryPointInfo.generated.h"
#pragma once

USTRUCT(BlueprintType)
struct FCsScriptEntryPointInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString File;

	/** Whether to recompile all scripts when exiting PIE. 
		If this is NOT set, then only File will get recompiled. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRecompileAllOnPIEExit;

	FCsScriptEntryPointInfo() :
		bEnable(false),
		File(),
		bRecompileAllOnPIEExit(false)
	{
	}
};