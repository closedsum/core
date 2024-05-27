// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_StructOps.h"
#include "Types/Enum/CsEnumMap.h"
#include "GameplayTagContainer.h"
// Log
#include "Utility/CsGameplayAbilitiesLog.h"

#include "CsTypes_GameplayAbility.generated.h"

// GameplayAbilityInstance
#pragma region

/**
* Describes what type "Instance" the Gameplay Ability is.
*/
UENUM(BlueprintType)
enum class ECsGameplayAbilityInstance : uint8
{
	DefaultObject					UMETA(DisplayName = "Default Object"),
	Instance						UMETA(DisplayName = "Instance"),
	Replicated						UMETA(DisplayName = "Replicated"),
	ECsGameplayAbilityInstance_MAX	UMETA(Hidden),
};

struct CSGAMEPLAYABILITIES_API EMCsGameplayAbilityInstance : public TCsEnumMap<ECsGameplayAbilityInstance>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsGameplayAbilityInstance, ECsGameplayAbilityInstance)
};

namespace NCsGameplayAbilityInstance
{
	typedef ECsGameplayAbilityInstance Type;

	namespace Ref
	{
		extern CSGAMEPLAYABILITIES_API const Type DefaultObject;
		extern CSGAMEPLAYABILITIES_API const Type Instance;
		extern CSGAMEPLAYABILITIES_API const Type Replicated;
		extern CSGAMEPLAYABILITIES_API const Type ECsGameplayAbilityInstance_MAX;
	}
}

namespace NCsGameplayAbility
{
	/**
	* Describes what type "Instance" the Gameplay Ability is.
	*/
	enum class EInstance : uint8 
	{
		DefaultObject,
		Instance,
		Replicated,
		EInstance_MAX
	};

	struct CSGAMEPLAYABILITIES_API EMInstance : public TCsEnumMap<EInstance>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMInstance, EInstance)
	};

	namespace NInstance
	{
		namespace Ref
		{
			typedef EInstance Type;

			extern CSGAMEPLAYABILITIES_API const Type DefaultObject;
			extern CSGAMEPLAYABILITIES_API const Type Instance;
			extern CSGAMEPLAYABILITIES_API const Type Replicated;
			extern CSGAMEPLAYABILITIES_API const Type EInstance_MAX;
		}
	}
}
#pragma endregion GameplayAbilityInstance

// GameplayAbilityInstanceQuery

// FCsGameplayAbility
#pragma region

class UGameplayAbility;
class UClass;

USTRUCT(BlueprintType)
struct CSGAMEPLAYABILITIES_API FCsGameplayAbility
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsGameplayAbilities")
	TSoftClassPtr<UGameplayAbility> Ability;

	UPROPERTY()
	int32 Ability_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsGameplayAbilities")
	UGameplayAbility* Ability_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsGameplayAbilities")
	UClass* Ability_Class;

	FCsGameplayAbility() :
		Ability(nullptr),
		Ability_LoadFlags(0),
		Ability_Internal(nullptr),
		Ability_Class(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UGameplayAbility asset.
	*
	* return Ability
	*/
	FORCEINLINE UGameplayAbility* Get() const { return Ability_Internal; }

	/**
	* Get the pointer to the Hard reference to the UGameplayAbility asset.
	*
	* return Ability
	*/
	FORCEINLINE UGameplayAbility** GetPtr() { return &Ability_Internal; }

	/**
	* Get the Hard reference to the UGameplayAbility asset.
	*
	* @param Context	The calling context.
	* return			Ability
	*/
	FORCEINLINE UGameplayAbility* GetChecked(const FString& Context) const
	{
		checkf(Ability.ToSoftObjectPath().IsValid(), TEXT("%s: Ability's Path is NOT Valid."), *Context);
		checkf(Ability_Internal, TEXT("%s: Ability has NOT been loaded from Path @ %s."), *Context, *(Ability.ToSoftObjectPath().ToString()));

		return Ability_Internal;
	}

	/**
	* Get the Hard reference to the UGameplayAbility asset.
	*
	* return Ability
	*/
	FORCEINLINE UGameplayAbility* GetChecked() const
	{
		checkf(Ability.ToSoftObjectPath().IsValid(), TEXT("FCsAbility::GetChecked: Ability's Path is NOT Valid."));
		checkf(Ability_Internal, TEXT("FCsAbility::GetChecked: Ability has NOT been loaded from Path @ %s."), *(Ability.ToSoftObjectPath().ToString()));

		return Ability_Internal;
	}

	/**
	* Safely get the Hard reference to the UGameplayAbility asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Ability
	*/
	UGameplayAbility* GetSafe(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning) const
	{
		if (!Ability.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Ability's Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (!Ability_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Ability has NOT been loaded from Path @ %s."), *Context, *(Ability.ToSoftObjectPath().ToString())));
		}
		return Ability_Internal;
	}

	/**
	* Safely get the Hard reference to the UGameplayAbility asset.
	*
	* return Ability
	*/
	UGameplayAbility* GetSafe()
	{
		if (!Ability.ToSoftObjectPath().IsValid())
			return nullptr;
		return Ability_Internal;
	}

	UGameplayAbility* SafeLoad(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning);
	UGameplayAbility* SafeLoad();

	UObject* SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning);

	FORCEINLINE UClass* GetClass() const { return Ability_Class; }

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsGameplayAbility)
	CS_STRUCT_OPS_IS_VALID(FCsGameplayAbility)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsGameplayAbility)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsGameplayAbility)

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
		checkf(Ability.ToSoftObjectPath().IsValid(), TEXT("%s: Ability's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning) const
	{
		if (!Ability.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Ability's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsGameplayAbility)

	FORCEINLINE void Unload()
	{
		Ability.ResetWeakPtr();
		Ability_Internal = nullptr;
	}
};

#pragma endregion FCsGameplayAbility


// FCsGameplayAbilityInfo
#pragma region

USTRUCT(BlueprintType)
struct CSGAMEPLAYABILITIES_API FCsGameplayAbilityInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsGameplayAbilities")
	FCsGameplayAbility Ability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsGameplayAbilities", meta = (UIMin = "0", ClampMin = "0"))
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsGameplayAbilities")
	FGameplayTagContainer ExecutionRequiredTags;

	FCsGameplayAbilityInfo() :
		Ability(),
		Level(0),
		ExecutionRequiredTags()
	{
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsGameplayAbilityInfo)
	CS_STRUCT_OPS_IS_VALID(FCsGameplayAbilityInfo)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsGameplayAbilityInfo)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsGameplayAbilityInfo)

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning) const;
	bool IsTopValidChecked(const FString& Context) const;
	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning) const;

	CS_STRUCT_OPS_DATA_UNLOAD(FCsGameplayAbilityInfo)

	FORCEINLINE void Unload()
	{
		Ability.Unload();
	}
};

#pragma endregion FCsGameplayAbilityInfo