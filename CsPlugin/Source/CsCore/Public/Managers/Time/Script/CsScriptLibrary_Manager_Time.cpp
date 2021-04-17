// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/Script/CsScriptLibrary_Manager_Time.h"
#include "CsCore.h"

// Library
#include "Managers/Time/CsLibrary_Manager_Time.h"
// Managers
#include "Managers/Time/CsManager_Time.h"

UCsScriptLibrary_Manager_Time::UCsScriptLibrary_Manager_Time(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Update
#pragma region

void UCsScriptLibrary_Manager_Time::BindToEvent_OnUpdate(UObject* WorldContextObject, FCsScriptLibraryManagerTime_OnUpdate Delegate)
{
	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	UObject* ContextRoot = TimeManagerLibrary::GetSafeContextRoot(WorldContextObject);

	if (UCsManager_Time* Manager = UCsManager_Time::Get(ContextRoot))
	{
		if (Delegate.IsBound())
		{
			if (!Manager->OnUpdate_ScriptEvent.Contains(Delegate))
			{
				Manager->OnUpdate_ScriptEvent.Add(Delegate);
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsScriptLibrary_Manager_Time::BindToEvent_OnUpdate: Delegate is already bound."));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsScriptLibrary_Manager_Time::BindToEvent_OnUpdate: No Delegate Bound."));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsScriptLibrary_Manager_Time::BindToEvent_OnUpdate: No Manager Time of type UCsManager_Time was created."));
	}
}

#pragma endregion Update