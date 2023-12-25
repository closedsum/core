// Copyright Studio Sai. All Rights Reserved.
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
		/**
		* Delegate type for the event when a Payload loaded asynchronously completes.
		*  This is a synchronous event (fired on the Game Thread).
		*
		* @param WasSuccessful
		* @param PayloadName
		*/
		DECLARE_DELEGATE_TwoParams(FOnAsyncLoadPayloadComplete, bool /*WasSuccessful*/, const FName& /*PayloadName*/);
	}
}