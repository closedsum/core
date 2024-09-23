// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/GameEvent/CsSettings_Coordinator_GameEvent.h"

// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Coordinators/GameEvent/CsCoordinator_GameEvent.h"
// Settings
#include "Settings/CsInputSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Coordinator_GameEvent)

// FCsSettings_Coordinator_GameEvent
#pragma region

FCsSettings_Coordinator_GameEvent::FCsSettings_Coordinator_GameEvent() :
	Class(UCsCoordinator_GameEvent::StaticClass())
{
}

/*static*/ const FCsSettings_Coordinator_GameEvent& FCsSettings_Coordinator_GameEvent::Get()
{
	return GetMutableDefault<UCsInputSettings>()->Coordinator_GameEvent;
}

bool FCsSettings_Coordinator_GameEvent::IsValidChecked(const FString& Context) const
{
	const FSoftObjectPath& SoftPath = Class.ToSoftObjectPath();

	checkf(SoftPath.IsValid(), TEXT("%s: Class is NULL or does NOT point to a Valid Path."), *Context);
	return true;
}

UClass* FCsSettings_Coordinator_GameEvent::LoadClassChecked(const FString& Context) const
{
	check(IsValidChecked(Context));

	UClass* C = Class.LoadSynchronous();

	checkf(C, TEXT("%s: Failed to load Class at Path: %s."), *Context, *(Class.ToString()));
	return C;
}

#pragma endregion FCsSettings_Coordinator_GameEvent