// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"

class UAnimSequenceBase;

namespace NCsAnimSequenceBase
{
	/**
	* Library of function related to UAnimSequenceBase
	*/
	class CSCORELIBRARY_API FLibrary
	{
	};

	namespace NNotify
	{
		class CSCORELIBRARY_API FLibrary final
		{
		public:

			static float GetTimeChecked(const FString& Context, const UAnimSequenceBase* Anim, const FName& NotifyName);

			static float GetRemainingTimeAfterChecked(const FString& Context, UAnimSequenceBase* Anim, const FName& NotifyName);

			static void GetNamesChecked(const FString& Context, UAnimSequenceBase* Anim, const float& Time, TArray<FName>& OutNames);

			static void GetNamesChecked(const FString& Context, UAnimSequenceBase* Anim, const float& Time, TArray<FName, TFixedAllocator<8>>& OutNames);

			static void GetNamesChecked(const FString& Context, UAnimSequenceBase* Anim, const float& MinTime, const float& MaxTime, TArray<FName>& OutNames);

			static void GetNamesChecked(const FString& Context, UAnimSequenceBase* Anim, const float& MinTime, const float& MaxTime, TArray<FName, TFixedAllocator<8>>& OutNames);
		};
	}
}