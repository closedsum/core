// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsPIE_Delegates.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsPIE_Delegates)

namespace NCsPIE
{
	FDelegates::FOnBegin FDelegates::OnBegin_Event;
	FDelegates::FOnEnd FDelegates::OnEnd_Event;
	FDelegates::FOnEnd_Last FDelegates::OnEnd_Last_Event;
	FDelegates::FOnEnd_NextFrame FDelegates::OnEnd_NextFrame_Event;
	FDelegates::FOnEndPlayMap FDelegates::OnEndPlayMap_Event;
}