// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

#include "CsTypes_ScriptInfo.generated.h"

USTRUCT(BlueprintType)
struct FCsScript_FileInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Script")
	bool bEnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Script")
	FString File;

	FCsScript_FileInfo() :
		bEnable(false),
		File()
	{
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (bEnable)
		{
			if (File.IsEmpty())
			{
				if (Log)
				{
					Log(FString::Printf(TEXT("%s: File is EMPTY."), *Context));
				}
				return false;
			}
		}
		return true;
	}
};

USTRUCT(BlueprintType)
struct FCsScriptInfo
{
	GENERATED_USTRUCT_BODY()

	/** Whether to recompile all scripts when exiting PIE. 
		If this is NOT set, then only File will get recompiled. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Script")
	bool bRecompileAllOnPIEExit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Script")
	TArray<FCsScript_FileInfo> FileInfos;

	FCsScriptInfo() :
		bRecompileAllOnPIEExit(false),
		FileInfos()
	{
	}

	bool AnyEnabled() const 
	{
		for (const FCsScript_FileInfo& FileInfo : FileInfos)
		{
			if (FileInfo.bEnable)
				return true;
		}
		return false;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		for (const FCsScript_FileInfo& FileInfo : FileInfos)
		{
			if (!FileInfo.IsValid(Context, Log))
				return false;
		}
		return true;
	}
};