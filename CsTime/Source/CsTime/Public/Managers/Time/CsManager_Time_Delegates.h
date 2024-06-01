// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/Time/CsTypes_Update.h"

#include "CsManager_Time_Delegates.generated.h"

USTRUCT()
struct CSTIME_API FCsManager_Time_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsManager_Time_Delegates_STUB()
	{
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerTime_OnUpdate, const FECsUpdateGroup&, Group, const FCsDeltaTime&, DeltaTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerTime_OnSetScaledDeltaTime, const FECsUpdateGroup&, Group, const float&, Scale);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerTime_OnResetScaledDeltaTime, const FECsUpdateGroup&, Group);

namespace NCsTime
{
	namespace NManager
	{
		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPause, const FECsUpdateGroup& /*Group*/, bool /*bPaused*/);
		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdate, const FECsUpdateGroup& /*Group*/, const FCsDeltaTime& /*DeltaTime*/);
		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSetScaledDeltaTime, const FECsUpdateGroup& /*Group*/, const float& /*Scale*/);
		DECLARE_MULTICAST_DELEGATE_OneParam(FOnResetScaledDeltaTime, const FECsUpdateGroup& /*Group*/);
	}
}