// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_StructOps.h"
// Log
#include "Utility/CsSeqLog.h"

#include "CsTypes_LevelSequence.generated.h"

// FCsLevelSequence
#pragma region

class ULevelSequence;

USTRUCT(BlueprintType)
struct CSSEQ_API FCsLevelSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsSeq|Level|Sequence")
	TSoftObjectPtr<ULevelSequence> Sequence;

	UPROPERTY(BlueprintReadOnly, Category = "CsSeq|Level|Sequence", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Sequence_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsSeq|Level|Sequence")
	ULevelSequence* Sequence_Internal;

public:

	FCsLevelSequence() :
		Sequence(nullptr),
		Sequence_LoadFlags(0),
		Sequence_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the ULevelSequence asset.
	*
	* return Level Sequence
	*/
	FORCEINLINE ULevelSequence* Get() const { return Sequence_Internal; }

	/**
	* Get the pointer to the Hard reference to the ULevelSequence asset.
	*
	* return Level Sequence
	*/
	FORCEINLINE ULevelSequence** GetPtr() { return &Sequence_Internal; }

	/**
	* Get the Hard reference to the ULevelSequence asset.
	*
	* @param Context	The calling context.
	* return			Level Sequence
	*/
	FORCEINLINE ULevelSequence* GetChecked(const FString& Context) const
	{
		checkf(Sequence.ToSoftObjectPath().IsValid(), TEXT("%s: Sequence is NULL."), *Context);
		checkf(Sequence_Internal, TEXT("%s: Sequence has NOT been loaded from Path @ %s."), *Context, *(Sequence.ToSoftObjectPath().ToString()));

		return Sequence_Internal;
	}

	/**
	* Get the Hard reference to the ULevelSequence asset.
	*
	* return Level Sequence
	*/
	FORCEINLINE ULevelSequence* GetChecked() const
	{
		checkf(Sequence.ToSoftObjectPath().IsValid(), TEXT("FCsLevelSequence::GetChecked: Sequence is NULL."));
		checkf(Sequence_Internal, TEXT("FCsLevelSequence::GetChecked: Sequence has NOT been loaded from Path @ %s."), *(Sequence.ToSoftObjectPath().ToString()));

		return Sequence_Internal;
	}

	/**
	* Safely get the Hard reference to the ULevelSequence asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Level Sequence
	*/
	ULevelSequence* GetSafe(const FString& Context, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning) const
	{
		if (!Sequence.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Sequence is NULL."), *Context));
			return nullptr;
		}

		if (!Sequence_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Sequence has NOT been loaded from Path @ %s."), *Context, *(Sequence.ToSoftObjectPath().ToString())));
		}
		return Sequence_Internal;
	}

	/**
	* Safely get the Hard reference to the ULevelSequence asset.
	*
	* return Level Sequence
	*/
	ULevelSequence* GetSafe()
	{
		if (!Sequence.ToSoftObjectPath().IsValid())
			return nullptr;
		return Sequence_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsLevelSequence)
	CS_STRUCT_OPS_IS_VALID(FCsLevelSequence)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsLevelSequence)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsLevelSequence)

	bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Sequence.ToSoftObjectPath().IsValid(), TEXT("%s: Sequence Path is NOT Valid."), *Context);
		return true;
	}

	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning) const
	{
		if (!Sequence.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Sequence Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	FORCEINLINE void Reset()
	{
		Sequence = nullptr;
		Sequence_Internal = nullptr;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsLevelSequence)

	FORCEINLINE void Unload()
	{
		Sequence.ResetWeakPtr();
		Sequence_Internal = nullptr;
	}
};

#pragma endregion FCsLevelSequence