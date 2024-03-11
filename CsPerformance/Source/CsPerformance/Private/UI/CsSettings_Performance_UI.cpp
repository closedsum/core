// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "UI/CsSettings_Performance_UI.h"

// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsPerformanceSettings.h"
// UI
#include "UI/CsPerformanceUI.h"
#include "Blueprint/UserWidget.h"

// FCsSettings_Performance_UI
#pragma region

/*static*/ const FCsSettings_Performance_UI& FCsSettings_Performance_UI::Get()
{
	return GetMutableDefault<UCsPerformanceSettings>()->UI;
}

bool FCsSettings_Performance_UI::IsValidChecked(const FString& Context) const
{
	CS_IS_SOFT_CLASS_PTR_VALID_CHECKED(Class, UUserWidget)
	return true;
}

UClass* FCsSettings_Performance_UI::LoadClassChecked(const FString& Context) const
{
	check(IsValidChecked(Context));

	UClass* C = Class.LoadSynchronous();

	checkf(C, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Class.ToString()));
	checkf(C->ImplementsInterface(UCsPerformanceUI::StaticClass()), TEXT("%s: Class: %s does NOT implement the interface: ICsPerformanceUI."), *Context, *(C->GetName()));
	return C;
}

#pragma endregion FCsSettings_Performance_UI