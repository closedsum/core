// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Enhanced/Data/CsEnhancedInputWithGameplayTagDataRootSet.h"

class UObject;
class UGameInstance;
class UCsData_EnhancedInput_WithGameplayTag;

namespace NCsInput
{
	namespace NEnhanced
	{
		namespace NWithGameplayTag
		{
			namespace NDataRootSet
			{
				/**
				*/
				class CSINPUTWITHGAMEPLAYTAG_API FLibrary final
				{
				public:

					/**
					*
					* 
					* @param Context		The calling context.
					* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
					* return
					*/
					static const FCsEnhancedInputWithGameplayTagDataRootSet* GetSafe(const FString& Context, const UObject* WorldContext);

					/**
					*
					*
					* @param Context		The calling context.
					* @param GameInstance	Route to Manager_Data, whose root is a GameInstance.
					* return				
					*/
					static const FCsEnhancedInputWithGameplayTagDataRootSet& GetChecked(const FString& Context, const UGameInstance* GameInstance);

					/**
					* 
					* 
					* @param Context		The calling context.
					* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
					* return				
					*/
					static const FCsEnhancedInputWithGameplayTagDataRootSet& GetChecked(const FString& Context, const UObject* WorldContext);

					static UCsData_EnhancedInput_WithGameplayTag* GetDataChecked(const FString& Context, const UObject* WorldContext);
				};
			}
		}
	}
}