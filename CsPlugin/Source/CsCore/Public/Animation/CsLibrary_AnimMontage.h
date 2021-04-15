// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Log
#include "Utility/CsLog.h"
#pragma once

class UObject;
class UAnimMontage;

namespace NCsAnimMontage
{
	/**
	* Library of function related to UAnimMontage
	*/
	class CSCORE_API FLibrary
	{
	// Load
	#pragma region
	public:

		/**
		* Load the AnimMontage at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the AnimMontage to load.
		* @param Log
		* return			AnimMontage.
		*/
		static UAnimMontage* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Load a AnimMontage at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the AnimMontage to load.
		* @param Log
		* return			AnimMontage.
		*/
		static UAnimMontage* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Load
	};
}