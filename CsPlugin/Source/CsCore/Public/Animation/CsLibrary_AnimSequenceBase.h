// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

class UAnimSequenceBase;

namespace NCsAnimSequenceBase
{
	/**
	* Library of function related to UAnimSequenceBase
	*/
	class CSCORE_API FLibrary
	{
	};

	namespace NNotify
	{
		class CSCORE_API FLibrary final
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