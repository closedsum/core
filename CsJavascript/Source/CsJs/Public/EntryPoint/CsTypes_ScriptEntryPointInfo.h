// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsTypes_ScriptEntryPointInfo.generated.h"

USTRUCT(BlueprintType)
struct CSJS_API FCsScriptEntryPointInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Entry Point")
	bool bEnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Entry Point")
	FString File;

	/** Whether to recompile all scripts when exiting PIE. 
		If this is NOT set, then only File will get recompiled. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Entry Point")
	bool bRecompileAllOnPIEExit;

	FCsScriptEntryPointInfo() :
		bEnable(false),
		File(),
		bRecompileAllOnPIEExit(false)
	{
	}
};