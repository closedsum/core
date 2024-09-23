// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsTypesLog.h"

#include "CsTypes_ScriptInfo.generated.h"

USTRUCT(BlueprintType)
struct CSTYPES_API FCsScript_FileInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Script")
	bool bEnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Script")
	FString Entry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Script")
	FString Target;

	FCsScript_FileInfo() :
		bEnable(false),
		Entry(),
		Target()
	{
	}

	bool IsValidChecked(const FString& Context) const
	{
		if (bEnable)
		{
			checkf(!Entry.IsEmpty(), TEXT("%s: Entry is Empty"), *Context);
		}
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (bEnable)
		{
			if (Entry.IsEmpty())
			{
				if (Log)
				{
					Log(FString::Printf(TEXT("%s: Entry is EMPTY."), *Context));
				}
				return false;
			}
		}
		return true;
	}
};

USTRUCT(BlueprintType)
struct CSTYPES_API FCsScriptInfo
{
	GENERATED_USTRUCT_BODY()

	/** Whether to recompile all scripts when exiting PIE. 
		If this is NOT set, then only File will get recompiled. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Script")
	bool bRecompileAllOnPIEExit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Script")
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

	bool IsValidChecked(const FString& Context) const 
	{
		for (const FCsScript_FileInfo& FileInfo : FileInfos)
		{
			check(FileInfo.IsValidChecked(Context));
		}
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		for (const FCsScript_FileInfo& FileInfo : FileInfos)
		{
			if (!FileInfo.IsValid(Context, Log))
				return false;
		}
		return true;
	}

	FORCEINLINE bool HasFileInfo(const int32& Index) const
	{
		return FileInfos.Num() > Index && FileInfos[Index].bEnable;
	}
};