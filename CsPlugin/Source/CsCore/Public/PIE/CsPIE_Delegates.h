// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsPIE_Delegates.generated.h"

USTRUCT()
struct CSCORE_API FCsPIE_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsPIE_Delegates_STUB()
	{
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsPIE_OnBegin, bool, IsSimulating);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsPIE_OnEnd, bool, IsSimulating);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsPIE_OnEnd_Last, bool, IsSimulating);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsPIE_OnEnd_NextFrame, bool, IsSimulating);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsPIE_OnEndPlayMap, bool, IsSimulating);

namespace NCsPIE
{
	struct CSCORE_API FDelegates
	{
	public:

		DECLARE_MULTICAST_DELEGATE_OneParam(FOnBegin, bool /*IsSimulating*/);

		static FOnBegin OnBegin_Event;

		DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnd, bool /*IsSimulating*/);

		static FOnEnd OnEnd_Event;

		DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnd_Last, bool /*IsSimulating*/);

		static FOnEnd_Last OnEnd_Last_Event;

		DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnd_NextFrame, bool /*IsSimulating*/);

		static FOnEnd_NextFrame OnEnd_NextFrame_Event;

		DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndPlayMap, bool /*IsSimulating*/);

		static FOnEndPlayMap OnEndPlayMap_Event;
	};
}