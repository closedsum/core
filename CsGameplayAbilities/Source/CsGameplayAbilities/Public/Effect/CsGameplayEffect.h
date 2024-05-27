// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_StructOps.h"
// Log
#include "Utility/CsGameplayAbilitiesLog.h"

#include "CsGameplayEffect.generated.h"

// FCsGameplayEffect
#pragma region

class UGameplayEffect;
class UClass;

USTRUCT(BlueprintType)
struct CSGAMEPLAYABILITIES_API FCsGameplayEffect
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsGameplayAbilities")
	TSoftClassPtr<UGameplayEffect> Effect;

	UPROPERTY()
	int32 Effect_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsGameplayAbilities")
	UGameplayEffect* Effect_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsGameplayAbilities")
	UClass* Effect_Class;

	FCsGameplayEffect() :
		Effect(nullptr),
		Effect_LoadFlags(0),
		Effect_Internal(nullptr),
		Effect_Class(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UGameplayEffect asset.
	*
	* return Effect
	*/
	FORCEINLINE UGameplayEffect* Get() const { return Effect_Internal; }

	/**
	* Get the pointer to the Hard reference to the UGameplayEffect asset.
	*
	* return Effect
	*/
	FORCEINLINE UGameplayEffect** GetPtr() { return &Effect_Internal; }

	/**
	* Get the Hard reference to the UGameplayEffect asset.
	*
	* @param Context	The calling context.
	* return			Effect
	*/
	FORCEINLINE UGameplayEffect* GetChecked(const FString& Context) const
	{
		checkf(Effect.ToSoftObjectPath().IsValid(), TEXT("%s: Effect's Path is NOT Valid."), *Context);
		checkf(Effect_Internal, TEXT("%s: Effect has NOT been loaded from Path @ %s."), *Context, *(Effect.ToSoftObjectPath().ToString()));

		return Effect_Internal;
	}

	/**
	* Get the Hard reference to the UGameplayEffect asset.
	*
	* return Effect
	*/
	FORCEINLINE UGameplayEffect* GetChecked() const
	{
		checkf(Effect.ToSoftObjectPath().IsValid(), TEXT("FCsEffect::GetChecked: Effect's Path is NOT Valid."));
		checkf(Effect_Internal, TEXT("FCsEffect::GetChecked: Effect has NOT been loaded from Path @ %s."), *(Effect.ToSoftObjectPath().ToString()));

		return Effect_Internal;
	}

	/**
	* Safely get the Hard reference to the UGameplayEffect asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Static Mesh
	*/
	UGameplayEffect* GetSafe(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning) const
	{
		if (!Effect.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Effect's Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (!Effect_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Effect has NOT been loaded from Path @ %s."), *Context, *(Effect.ToSoftObjectPath().ToString())));
		}
		return Effect_Internal;
	}

	/**
	* Safely get the Hard reference to the UGameplayEffect asset.
	*
	* return Static Mesh
	*/
	UGameplayEffect* GetSafe()
	{
		if (!Effect.ToSoftObjectPath().IsValid())
			return nullptr;
		return Effect_Internal;
	}

	UGameplayEffect* SafeLoad(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning);
	UGameplayEffect* SafeLoad();

	UObject* SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning);

	FORCEINLINE UClass* GetClass() const { return Effect_Class; }

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsGameplayEffect)
	CS_STRUCT_OPS_IS_VALID(FCsGameplayEffect)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsGameplayEffect)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsGameplayEffect)

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
		checkf(Effect.ToSoftObjectPath().IsValid(), TEXT("%s: Effect's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning) const
	{
		if (!Effect.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Effect's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsGameplayEffect)

	FORCEINLINE void Unload()
	{
		Effect.ResetWeakPtr();
		Effect_Internal = nullptr;
	}
};

#pragma endregion FCsGameplayEffect

// FCsGameplayEffectInfo
#pragma region

USTRUCT(BlueprintType)
struct CSGAMEPLAYABILITIES_API FCsGameplayEffectInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsGameplayAbilities")
	FCsGameplayEffect Effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsGameplayAbilities", meta = (UIMin = "0", ClampMin = "0"))
	int32 Level;

	FCsGameplayEffectInfo() :
		Effect(),
		Level(0)
	{
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsGameplayEffectInfo)
	CS_STRUCT_OPS_IS_VALID(FCsGameplayEffectInfo)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsGameplayEffectInfo)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsGameplayEffectInfo)

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning) const;
	bool IsTopValidChecked(const FString& Context) const;
	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning) const;

	CS_STRUCT_OPS_DATA_UNLOAD(FCsGameplayEffectInfo)

	FORCEINLINE void Unload()
	{
		Effect.Unload();
	}
};

#pragma endregion FCsGameplayEffectInfo