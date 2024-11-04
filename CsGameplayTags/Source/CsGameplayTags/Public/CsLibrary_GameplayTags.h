// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
#include "GameplayTagContainer.h"
// Log
#include "Utility/CsGameplayTagsLog.h"

namespace NCsGameplayTags
{
	struct CSGAMEPLAYTAGS_API FLibrary final
	{
	private:

		CS_DECLARE_STATIC_LOG_LEVEL

	public:
		
		/**
		* Get the GameplayTag associated with Name.
		* 
		* @param Context	The calling context
		* @param Name		The Name of the GameplayTag
		* return			GameplayTag associated with Name.
		*/
		static FGameplayTag GetChecked(const FString& Context, const FName& Name);

		/**
		* Get the GameplayTag associated with Name.
		* 
		* @param Context	The calling context
		* @param Name		The Name of the GameplayTag
		* return			GameplayTag associated with Name.
		*/
		static FGameplayTag GetChecked(const FString& Context, const FString& Name);

		/**
		* Safely get the GameplayTag associated with Name.
		* 
		* @param Context	The calling context
		* @param Name		The Name of the GameplayTag
		* @param OutSuccess	(out)
		* @param Log		(optional)
		* return			GameplayTag associated with Name.
		*/
		static FGameplayTag GetSafe(const FString& Context, const FName& Name, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		FORCEINLINE static FGameplayTag GetSafe(const FString& Context, const FName& Name, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			bool OutSuccess = false;
			return GetSafe(Context, Name, OutSuccess, Log);
		}

		/**
		* Safely get the GameplayTag associated with Name.
		* 
		* @param Context	The calling context
		* @param Name		The Name of the GameplayTag
		* @param OutSuccess	(out)
		* @param Log		(optional)
		* return			GameplayTag associated with Name.
		*/
		static FGameplayTag GetSafe(const FString& Context, const FString& Name, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		FORCEINLINE static FGameplayTag GetSafe(const FString& Context, const FString& Name, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
		{
			bool OutSuccess = false;
			return GetSafe(Context, Name, OutSuccess, Log);
		}

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
	};
}

using CsGameplayTagsLibrary = NCsGameplayTags::FLibrary;