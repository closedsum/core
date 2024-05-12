// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsFadeDataRootSet.h"

// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Fade
#include "Managers/Fade/CsUserWidget_Fade.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsFadeDataRootSet)

UClass* FCsFadeDataRootSet::GetFadeWidgetClassChecked(const FString& Context) const
{
	CS_IS_SUBCLASS_OF_NULL_CHECKED(FadeWidget, UCsUserWidget_Fade)

	return FadeWidget.Get();
}