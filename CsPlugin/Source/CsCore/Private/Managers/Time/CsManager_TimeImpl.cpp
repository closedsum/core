// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Time/CsManager_TimeImpl.h"
#include "CsCore.h"

// Library
#include "Managers/Input/CsLibrary_Manager_Input.h"
// Settings
#include "Settings/CsTimeSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_TimeImpl)

// Cached
#pragma region

namespace NCsManagerTimeImpl
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_TimeImpl, SetupInputListener);
		}
	}
}

#pragma endregion Cached

UCsManager_TimeImpl::UCsManager_TimeImpl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsManager_TimeImpl::SetupInputListener()
{
	using namespace NCsManagerTimeImpl::NCached;

	const FString& Context = Str::SetupInputListener;

	typedef NCsInput::NManager::NFirst::FLibrary InputManagerLibrary;

	InputManagerLibrary::GetOnAnyKey_Pressed_EventChecked(Context, MyRoot).AddUObject(this, &UCsManager_TimeImpl::OnAnyKey_Pressed);
	InputManagerLibrary::GetOnAnyKey_Released_EventChecked(Context, MyRoot).AddUObject(this, &UCsManager_TimeImpl::OnAnyKey_Released);
}

void UCsManager_TimeImpl::OnAnyKey_Pressed(const FKey& Key)
{
	UCsTimeSettings* Settings				     = GetMutableDefault<UCsTimeSettings>();
	const FCsSettings_Manager_Time& TimeSettings = Settings->Manager_Time;

	// Check for Pause
	for (const TPair<FECsUpdateGroup, FCsSettings_Manager_Time_Set_Key>& Pair : TimeSettings.TogglePauseGroupByKeysMap)
	{
		const FECsUpdateGroup& Group = Pair.Key;
		const TSet<FKey>& Keys		 = Pair.Value.Set;

		if (Keys.Contains(Key))
		{
			if (IsPaused(Group))
				Unpause(Group);
			else
				Pause(Group);
		}
	}
	// Check for Custom Update
	for (const TPair<FECsUpdateGroup, FCsSettings_Manager_Time_CustomUpdate>& Pair : TimeSettings.CustomUpdateMap)
	{
		const FECsUpdateGroup& Group									  = Pair.Key;
		const FCsSettings_Manager_Time_CustomUpdate& CustomUpdateSettings = Pair.Value;

		const TSet<FKey>& Keys = CustomUpdateSettings.Keys;

		if (Keys.Contains(Key))
		{
			// NOTE: For now this will only call SetCustom for the Group if the Group is Paused
			if (IsPaused(Group))
			{
				SetCustom(Group, !CustomUpdateSettings.bAllowSustained);
				SetCustomDeltaTime(Group, FCsDeltaTime(CustomUpdateSettings.DeltaTime));
			}
		}
	}
}

void UCsManager_TimeImpl::OnAnyKey_Released(const FKey& Key)
{
	UCsTimeSettings* Settings					 = GetMutableDefault<UCsTimeSettings>();
	const FCsSettings_Manager_Time& TimeSettings = Settings->Manager_Time;

	// Check for Custom Update
	for (const TPair<FECsUpdateGroup, FCsSettings_Manager_Time_CustomUpdate>& Pair : TimeSettings.CustomUpdateMap)
	{
		const FECsUpdateGroup& Group									  = Pair.Key;
		const FCsSettings_Manager_Time_CustomUpdate& CustomUpdateSettings = Pair.Value;

		const TSet<FKey>& Keys = CustomUpdateSettings.Keys;

		if (Keys.Contains(Key))
		{
			ClearCustom(Group);
		}
	}
}