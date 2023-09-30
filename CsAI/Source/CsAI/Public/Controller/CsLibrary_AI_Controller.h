// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsAILog.h"

class UObject;
class AAIController;
class UBlackboardComponent;

namespace NCsAI
{
	namespace NController
	{
		/**
		* Library of functions related to AIController
		*/
		struct CSAI_API FLibrary final
		{
			/**
			* Get the Blackboard associated with Controller.
			* 
			* @param Context	The calling context.
			* @param Controller
			* return			Blackboard
			*/
			static UBlackboardComponent* GetBlackboardChecked(const FString& Context, const AAIController* Controller);

			/**
			* Safely get the Blackboard associated with Controller.
			*
			* @param Context	The calling context.
			* @param Controller
			* @param Log		(optional)
			* return			Blackboard
			*/
			static UBlackboardComponent* GetSafeBlackboard(const FString& Context, const AAIController* Controller, void(*Log)(const FString&) = &NCsAI::FLog::Warning);
		};
	}
}