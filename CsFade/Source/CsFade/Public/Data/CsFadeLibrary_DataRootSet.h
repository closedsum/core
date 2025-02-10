// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Data/CsFadeDataRootSet.h"

class UObject;
class UClass;
class UGameInstance;

namespace NCsFade
{
	namespace NDataRootSet
	{
		/**
		*/
		class CSFADE_API FLibrary final
		{
		public:

			/**
			*
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* return
			*/
			static const FCsFadeDataRootSet* GetSafe(const FString& Context, const UObject* WorldContext);

			/**
			*
			*
			* @param Context		The calling context.
			* @param GameInstance	Route to Manager_Data, whose root is a GameInstance.
			* return				
			*/
			static const FCsFadeDataRootSet& GetChecked(const FString& Context, const UGameInstance* GameInstance);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* return				
			*/
			static const FCsFadeDataRootSet& GetChecked(const FString& Context, const UObject* WorldContext);

			static UClass* GetFadeWidgetClassChecked(const FString& Context, const UObject* WorldContext);
		};
	}
}

using CsFadeDataRootSetLibrary = NCsFade::NDataRootSet::FLibrary;