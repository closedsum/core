// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "PIE/CsPIE_Delegates.h"

namespace NCsPIE
{
	FDelegates::FOnBegin FDelegates::OnBegin_Event;
	FDelegates::FOnEnd FDelegates::OnEnd_Event;
	FDelegates::FOnEnd_Last FDelegates::OnEnd_Last_Event;
	FDelegates::FOnEnd_NextFrame FDelegates::OnEnd_NextFrame_Event;
	FDelegates::FOnEndPlayMap FDelegates::OnEndPlayMap_Event;
}