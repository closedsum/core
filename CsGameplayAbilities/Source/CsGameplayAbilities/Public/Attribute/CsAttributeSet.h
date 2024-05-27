// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_StructOps.h"
// Log
#include "Utility/CsGameplayAbilitiesLog.h"

#include "CsAttributeSet.generated.h"

// FCsAttributeSet
#pragma region

class UAttributeSet;
class UClass;

USTRUCT(BlueprintType)
struct CSGAMEPLAYABILITIES_API FCsAttributeSet
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsGameplayAbilities")
	TSoftClassPtr<UAttributeSet> Set;

	UPROPERTY()
	int32 Set_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsGameplayAbilities")
	UAttributeSet* Set_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsGameplayAbilities")
	UClass* Set_Class;

	FCsAttributeSet() :
		Set(nullptr),
		Set_LoadFlags(0),
		Set_Internal(nullptr),
		Set_Class(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UAttributeSet asset.
	*
	* return Set
	*/
	FORCEINLINE UAttributeSet* Get() const { return Set_Internal; }

	/**
	* Get the pointer to the Hard reference to the UAttributeSet asset.
	*
	* return Set
	*/
	FORCEINLINE UAttributeSet** GetPtr() { return &Set_Internal; }

	/**
	* Get the Hard reference to the UAttributeSet asset.
	*
	* @param Context	The calling context.
	* return			Set
	*/
	FORCEINLINE UAttributeSet* GetChecked(const FString& Context) const
	{
		checkf(Set.ToSoftObjectPath().IsValid(), TEXT("%s: Set's Path is NOT Valid."), *Context);
		checkf(Set_Internal, TEXT("%s: Set has NOT been loaded from Path @ %s."), *Context, *(Set.ToSoftObjectPath().ToString()));

		return Set_Internal;
	}

	/**
	* Get the Hard reference to the UAttributeSet asset.
	*
	* return Set
	*/
	FORCEINLINE UAttributeSet* GetChecked() const
	{
		checkf(Set.ToSoftObjectPath().IsValid(), TEXT("FCsSet::GetChecked: Set's Path is NOT Valid."));
		checkf(Set_Internal, TEXT("FCsSet::GetChecked: Set has NOT been loaded from Path @ %s."), *(Set.ToSoftObjectPath().ToString()));

		return Set_Internal;
	}

	/**
	* Safely get the Hard reference to the UAttributeSet asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Static Mesh
	*/
	UAttributeSet* GetSafe(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning) const
	{
		if (!Set.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Set's Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (!Set_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Set has NOT been loaded from Path @ %s."), *Context, *(Set.ToSoftObjectPath().ToString())));
		}
		return Set_Internal;
	}

	/**
	* Safely get the Hard reference to the UAttributeSet asset.
	*
	* return Static Mesh
	*/
	UAttributeSet* GetSafe()
	{
		if (!Set.ToSoftObjectPath().IsValid())
			return nullptr;
		return Set_Internal;
	}

	UAttributeSet* SafeLoad(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning);
	UAttributeSet* SafeLoad();

	UObject* SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning);

	FORCEINLINE UClass* GetClass() const { return Set_Class; }

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsAttributeSet)
	CS_STRUCT_OPS_IS_VALID(FCsAttributeSet)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsAttributeSet)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsAttributeSet)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Set.ToSoftObjectPath().IsValid(), TEXT("%s: Set's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning) const
	{
		if (!Set.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Set's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsAttributeSet)

	FORCEINLINE void Unload()
	{
		Set.ResetWeakPtr();
		Set_Internal = nullptr;
	}
};

#pragma endregion FCsAttributeSet