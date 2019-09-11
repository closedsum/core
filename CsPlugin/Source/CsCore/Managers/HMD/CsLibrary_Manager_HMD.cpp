// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/HMD/CsLibrary_Manager_HMD.h"
#include "CsCore.h"

#include "Managers/HMD/CsManager_HMD.h"

UCsLibrary_Manager_HMD::UCsLibrary_Manager_HMD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsLibrary_Manager_HMD::BindToEvent_VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked(FCsLibraryManagerHMD_VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->HMDTrackingInitializingAndNeedsHMDToBeTrackedDelegate.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked(FCsLibraryManagerHMD_VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->HMDTrackingInitializingAndNeedsHMDToBeTrackedDelegate.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::BindToEvent_VRHeadsetTrackingInitialized(FCsLibraryManagerHMD_VRHeadsetTrackingInitialized Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->HMDTrackingInitializedDelegate.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_VRHeadsetTrackingInitialized: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_VRHeadsetTrackingInitialized: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_VRHeadsetTrackingInitialized(FCsLibraryManagerHMD_VRHeadsetTrackingInitialized Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->HMDTrackingInitializedDelegate.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_VRHeadsetTrackingInitialized: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_VRHeadsetTrackingInitialized: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::BindToEvent_VRHeadsetRecenter(FCsLibraryManagerHMD_VRHeadsetRecenter Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->HMDRecenteredDelegate.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_VRHeadsetRecenter: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_VRHeadsetRecenter: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_VRHeadsetRecenter(FCsLibraryManagerHMD_VRHeadsetRecenter Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->HMDRecenteredDelegate.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_VRHeadsetRecenter: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_VRHeadsetRecenter: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::BindToEvent_VRHeadsetLost(FCsLibraryManagerHMD_VRHeadsetLost Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->HMDLostDelegate.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_VRHeadsetLost: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_VRHeadsetLost: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_VRHeadsetLost(FCsLibraryManagerHMD_VRHeadsetLost Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->HMDLostDelegate.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_VRHeadsetLost: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_VRHeadsetLost: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}