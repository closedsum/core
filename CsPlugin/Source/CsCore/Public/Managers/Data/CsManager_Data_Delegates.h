// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsManager_Data_Delegates.generated.h"

USTRUCT()
struct CSCORE_API FCsManager_Data_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsManager_Data_Delegates_STUB()
	{
	}
};

// System

class UObject;

namespace NCsData
{
	namespace NManager
	{
		namespace NOnce
		{
			/**
			* Delegate type for the event when a Payload loaded asynchronously completes.
			*  This is a synchronous event (fired on the Game Thread).
			*
			* @param WasSuccessful
			* @param PayloadName
			*/
			DECLARE_DELEGATE_TwoParams(FOnAsyncLoadPayloadComplete, bool /*WasSuccessful*/, const FName& /*PayloadName*/);

			/**
			* Delegate type for the event when a list Payloads loaded asynchronously completes.
			*  This is a synchronous event (fired on the Game Thread).
			*
			* @param WasSuccessful
			* @param PayloadNames
			*/
			DECLARE_DELEGATE_TwoParams(FOnAsyncLoadPayloadsComplete, bool /*WasSuccessful*/, const TArray<FName>& /*PayloadNames*/);
		}

		namespace NPersistent
		{
			/**
			* Delegate type for the event when a Payload loaded asynchronously completes.
			*  This is a synchronous event (fired on the Game Thread).
			*
			* @param WasSuccessful
			* @param PayloadName
			*/
			DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAsyncLoadPayloadComplete, bool /*WasSuccessful*/, const FName& /*PayloadName*/);
		}
	}
}