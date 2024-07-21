// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "GameplayTagContainer.h"
// Log
#include "Utility/CsGameplayTagsLog.h"

#include "CsTypes_Coordinator_GameplayTag.generated.h"

// GameplayTagCoordinatorGroup
#pragma region

USTRUCT(BlueprintType)
struct CSGAMEPLAYTAGS_API FECsGameplayTagCoordinatorGroup : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsGameplayTagCoordinatorGroup)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsGameplayTagCoordinatorGroup)

struct CSGAMEPLAYTAGS_API EMCsGameplayTagCoordinatorGroup : public TCsEnumStructMap<FECsGameplayTagCoordinatorGroup, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsGameplayTagCoordinatorGroup, FECsGameplayTagCoordinatorGroup, uint8)
};

namespace NCsGameplayTagCoordinatorGroup
{
	typedef FECsGameplayTagCoordinatorGroup Type;
	typedef EMCsGameplayTagCoordinatorGroup EnumMapType;

	/** Broadcast GameEvents Immediately */
	extern CSGAMEPLAYTAGS_API const Type None;
	/** Broadcast GameEvents during GameInstance->Tick() */
	extern CSGAMEPLAYTAGS_API const Type GameInstance;
	/** Broadcast GameEvents during GameState->Update() */
	extern CSGAMEPLAYTAGS_API const Type GameState;
	/** Broadcast GameEvents during ControllerId 0's ManagerInput->PostProcessInput. */
	extern CSGAMEPLAYTAGS_API const Type ManagerInput0;
	/** Broadcast GameEvents during ControllerId 1's ManagerInput->PostProcessInput. */
	extern CSGAMEPLAYTAGS_API const Type ManagerInput1;

	FORCEINLINE static bool IsManagerInput(const Type& Group)
	{
		return Group == ManagerInput0 || ManagerInput1;
	}

	FORCEINLINE static int32 GetManagerInputIndex(const Type& Group)
	{
		check(IsManagerInput(Group));

		return Group == ManagerInput0 ? 0 : 1;
	}
}

#pragma endregion GameplayTagCoordinatorGroup

// FCsGameplayTagEvent

USTRUCT(BlueprintType)
struct CSGAMEPLAYTAGS_API FCsGameplayTagEvent
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsGameplayTags|Event")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsGameplayTags|Event")
	bool bFlag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsGameplayTags|Event")
	FVector Value;

	FCsGameplayTagEvent() :
		Tag(),
		bFlag(false),
		Value()
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsGameplayTags::FLog::Warning) const;
};