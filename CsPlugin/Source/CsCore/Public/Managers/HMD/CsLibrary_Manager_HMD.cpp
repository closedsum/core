// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/HMD/CsLibrary_Manager_HMD.h"
#include "CsCore.h"

#include "Managers/HMD/CsManager_HMD.h"

UCsLibrary_Manager_HMD::UCsLibrary_Manager_HMD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsLibrary_Manager_HMD::BindToEvent_HMDTrackingInitializingAndNeedsHMDToBeTracked(FCsLibraryManagerHMD_HMDTrackingInitializingAndNeedsHMDToBeTracked Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDTrackingInitializingAndNeedsHMDToBeTracked_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDTrackingInitializingAndNeedsHMDToBeTracked: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDTrackingInitializingAndNeedsHMDToBeTracked: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_HMDTrackingInitializingAndNeedsHMDToBeTracked(FCsLibraryManagerHMD_HMDTrackingInitializingAndNeedsHMDToBeTracked Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDTrackingInitializingAndNeedsHMDToBeTracked_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_HMDTrackingInitializingAndNeedsHMDToBeTracked: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_HMDTrackingInitializingAndNeedsHMDToBeTracked: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::BindToEvent_HMDTrackingInitialized(FCsLibraryManagerHMD_HMDTrackingInitialized Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDTrackingInitialized_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDTrackingInitialized: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDTrackingInitialized: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_HMDTrackingInitialized(FCsLibraryManagerHMD_HMDTrackingInitialized Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDTrackingInitialized_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_HMDTrackingInitialized: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_HMDTrackingInitialized: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::BindToEvent_HMDRecenter(FCsLibraryManagerHMD_HMDRecenter Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDRecenter_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDRecenter: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDRecenter: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_HMDRecenter(FCsLibraryManagerHMD_HMDRecenter Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDRecenter_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_HMDRecenter: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_HMDRecenter: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::BindToEvent_HMDLost(FCsLibraryManagerHMD_HMDLost Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDLost_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDLost: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDLost: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_HMDLost(FCsLibraryManagerHMD_HMDLost Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDLost_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_HMDLost: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_HMDLost: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::BindToEvent_HMDReconnected(FCsLibraryManagerHMD_HMDReconnected Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDReconnected_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDReconnected: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDReconnected: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_HMDReconnected(FCsLibraryManagerHMD_HMDReconnected Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDReconnected_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindToEvent_HMDReconnected: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindToEvent_HMDReconnected: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::BindToEvent_HMDConnectCanceled(FCsLibraryManagerHMD_HMDConnectCanceled Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDConnectCanceled_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDConnectCanceled: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDConnectCanceled: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_HMDConnectCanceled(FCsLibraryManagerHMD_HMDConnectCanceled Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDConnectCanceled_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_HMDConnectCanceled: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_HMDConnectCanceled: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::BindToEvent_HMDPutOnHead(FCsLibraryManagerHMD_HMDPutOnHead Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDPutOnHead_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDPutOnHead: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDPutOnHead: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_HMDPutOnHead(FCsLibraryManagerHMD_HMDPutOnHead Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDPutOnHead_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_HMDPutOnHead: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_HMDPutOnHead: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::BindToEvent_HMDRemovedFromHead(FCsLibraryManagerHMD_HMDRemovedFromHead Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDRemovedFromHead_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDRemovedFromHead: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_HMDRemovedFromHead: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_HMDRemovedFromHead(FCsLibraryManagerHMD_HMDRemovedFromHead Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnHMDRemovedFromHead_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_HMDRemovedFromHead: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_HMDRemovedFromHead: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::BindToEvent_VRControllerRecentered(FCsLibraryManagerHMD_VRControllerRecentered Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnVRControllerRecentered_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_VRControllerRecentered: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_VRControllerRecentered: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}

void UCsLibrary_Manager_HMD::UnbindFromEvent_VRControllerRecentered(FCsLibraryManagerHMD_VRControllerRecentered Delegate)
{
	if (UCsManager_HMD* Manager = UCsManager_HMD::Get())
	{
		if (Delegate.IsBound())
		{
			Manager->OnVRControllerRecentered_Event.Add(Delegate);
		}
#if WITH_EDITOR
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_VRControllerRecentered: No Delegate Bound."));
		}
#endif // #if WITH_EDITOR
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_HMD::UnbindFromEvent_VRControllerRecentered: No Manager HMD of type: UCsManager_HMD was created."));
	}
#endif // #if WITH_EDITOR
}