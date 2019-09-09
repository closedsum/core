// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/HMD/CsLibrary_Manager_HMD.h"
#include "CsCore.h"

#include "Managers/HMD/CsManager_HMD.h"

UCsLibrary_Manager_HMD::UCsLibrary_Manager_HMD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Worn State
#pragma region

void UCsLibrary_Manager_HMD::BindToEvent_OnChange_WornState(FCsLibraryManagerHMD_OnChange_WornState Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnChange_WornState_ScriptEvent.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_OnChange_WornState: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_OnChange_WornState: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_OnChange_WornState(FCsLibraryManagerHMD_OnChange_WornState Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnChange_WornState_ScriptEvent.Remove(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_OnChange_WornState: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_OnChange_WornState: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::BindToEvent_OnWornState_FirstWorn(FCsLibraryManagerHMD_OnWornState_FirstWorn Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnWornState_FirstWorn_ScriptEvent.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_OnWornState_FirstWorn: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_OnWornState_FirstWorn: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_OnWornState_FirstWorn(FCsLibraryManagerHMD_OnWornState_FirstWorn Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnWornState_FirstWorn_ScriptEvent.Remove(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_OnWornState_FirstWorn: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_OnWornState_FirstWorn: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::BindToEvent_OnWornState_FirstNotWorn(FCsLibraryManagerHMD_OnWornState_FirstNotWorn Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnWornState_FirstNotWorn_ScriptEvent.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_OnWornState_FirstNotWorn: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_OnWornState_FirstNotWorn: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_OnWornState_FirstNotWorn(FCsLibraryManagerHMD_OnWornState_FirstNotWorn Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnWornState_FirstNotWorn_ScriptEvent.Remove(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_OnWornState_FirstNotWorn: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_OnWornState_FirstNotWorn: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

#pragma endregion Worn State