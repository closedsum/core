// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "GameplayTagContainer.h"
// Log
//#include "Utility/CsGameplayAbilitiesLog.h"

namespace NCsGameplayTags
{
	struct CSGAMEPLAYTAGS_API FLibrary final
	{
	//#define LogLevel void(*Log)(const FString&) = &NCsGameplayAbilities::FLog::Warning

	public:
		
		FORCEINLINE static TArray<FGameplayTag>& GetGameplayTags(FGameplayTagContainer& Container)
		{
			// Get pointer to start of struct (TArray<FGameplayTag> GameplayTags)
			TArray<FGameplayTag>* GameplayTags = ((TArray<FGameplayTag>*)(&Container));
			return *GameplayTags;
		}
		
		FORCEINLINE static const TArray<FGameplayTag>& GetGameplayTags(const FGameplayTagContainer& Container)
		{
			// Get pointer to start of struct (TArray<FGameplayTag> GameplayTags)
			const TArray<FGameplayTag>* GameplayTags = ((TArray<FGameplayTag>*)(&Container));
			return *GameplayTags;
		}

		FORCEINLINE static TArray<FGameplayTag>& GetParentTags(FGameplayTagContainer& Container)
		{
			// Get pointer to start of struct (TArray<FGameplayTag> GameplayTags)
			TArray<FGameplayTag>* GameplayTags = ((TArray<FGameplayTag>*)(&Container));
			char* Base						   = (char*)GameplayTags;

			// Offset by GameplayTags
			size_t Offset					 = sizeof(TArray<FGameplayTag>);
			TArray<FGameplayTag>* ParentTags = (TArray<FGameplayTag>*)(Base + Offset);
			return *ParentTags;
		}

		FORCEINLINE static const TArray<FGameplayTag>& GetParentTags(const FGameplayTagContainer& Container)
		{
			// Get pointer to start of struct (TArray<FGameplayTag> GameplayTags)
			const TArray<FGameplayTag>* GameplayTags = ((TArray<FGameplayTag>*)(&Container));
			char* Base								 = (char*)GameplayTags;

			// Offset by GameplayTags
			size_t Offset						   = sizeof(TArray<FGameplayTag>);
			const TArray<FGameplayTag>* ParentTags = (TArray<FGameplayTag>*)(Base + Offset);
			return *ParentTags;
		}

		FORCEINLINE static void Equal(FGameplayTagContainer& Left, const FGameplayTagContainer& Right)
		{
			TArray<FGameplayTag>& Left_GameplayTags		   = GetGameplayTags(Left);
			TArray<FGameplayTag>& Left_ParentTags		   = GetParentTags(Left);
			const TArray<FGameplayTag>& Right_GameplayTags = GetGameplayTags(Right);
			const TArray<FGameplayTag>& Right_ParentTags   = GetParentTags(Right);

			Left_GameplayTags.Reset(FMath::Max(Left_GameplayTags.Max(), Right_GameplayTags.Num()));
			Left_GameplayTags.Append(Right_GameplayTags);
			Left_ParentTags.Reset(FMath::Max(Left_ParentTags.Max(), Right_ParentTags.Num()));
			Left_ParentTags.Append(Right_ParentTags);
		}

		FORCEINLINE static void Copy(const FGameplayTagContainer& From, FGameplayTagContainer& To)
		{
			Equal(To, From);
		}

		FORCEINLINE static void Reset(FGameplayTagContainer& Container)
		{
			TArray<FGameplayTag>& GameplayTags = GetGameplayTags(Container);
			TArray<FGameplayTag>& ParentTags   = GetParentTags(Container);

			GameplayTags.Reset(GameplayTags.Max());
			ParentTags.Reset(ParentTags.Max());
		}

	//#undef LogLevel
	};
}