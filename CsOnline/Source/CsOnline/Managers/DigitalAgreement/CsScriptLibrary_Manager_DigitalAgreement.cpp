// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/DigitalAgreement/CsScriptLibrary_Manager_DigitalAgreement.h"
#include "CsOnline.h"

// Managers
#include "Managers/DigitalAgreement/CsManager_DigitalAgreement.h"
// Engine
#include "Engine/World.h"
#include "Engine/Engine.h"

// Cached
#pragma region

namespace NCsScriptLibraryManagerDigitalAgreement
{
	namespace Str
	{
		const FString Accept = TEXT("UCsScriptLibrary_Manager_DigitalAgreement::Accept");
		const FString BindToEvent_OnAccept = TEXT("UCsScriptLibrary_Manager_DigitalAgreement::BindToEvent_OnAccept");
		const FString DoNotAccept = TEXT("UCsScriptLibrary_Manager_DigitalAgreement::DoNotAccept");
		const FString BindToEvent_OnDoNotAccept = TEXT("UCsScriptLibrary_Manager_DigitalAgreement::BindToEvent_OnDoNotAccept");
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_DigitalAgreement::UCsScriptLibrary_Manager_DigitalAgreement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_Manager_DigitalAgreement::AreEnabled(const UObject* WorldContextObject)
{
#if WITH_EDITOR
	if (UCsManager_DigitalAgreement* Manager = UCsManager_DigitalAgreement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_DigitalAgreement* Manager = UCsManager_DigitalAgreement::Get())
#endif // #if WITH_EDITOR
	{
		return Manager->AreEnabled();
	}
	else
	{
		UE_LOG(LogCsOnline, Warning, TEXT("UCsScriptLibrary_Manager_DigitalAgreement::AreEnabled: No Manager DigitalAgreement of type UCsManager_DigitalAgreement was created."));
	}
	return false;
}

void UCsScriptLibrary_Manager_DigitalAgreement::ResetAll(const UObject* WorldContextObject)
{
#if WITH_EDITOR
	if (UCsManager_DigitalAgreement* Manager = UCsManager_DigitalAgreement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_DigitalAgreement* Manager = UCsManager_DigitalAgreement::Get())
#endif // #if WITH_EDITOR
	{
		Manager->ResetAll();
	}
	else
	{
		UE_LOG(LogCsOnline, Warning, TEXT("UCsScriptLibrary_Manager_DigitalAgreement::ResetAll: No Manager DigitalAgreement of type UCsManager_DigitalAgreement was created."));
	}
}

// Accept
#pragma region

void UCsScriptLibrary_Manager_DigitalAgreement::Accept(const UObject* WorldContextObject, const ECsDigitalAgreement& DigitalAgreement)
{
	Accept_Internal(NCsScriptLibraryManagerDigitalAgreement::Str::Accept, WorldContextObject, DigitalAgreement);
}

void UCsScriptLibrary_Manager_DigitalAgreement::Accept_Internal(const FString& Context, const UObject* WorldContextObject, const ECsDigitalAgreement& DigitalAgreement)
{
	if (DigitalAgreement == ECsDigitalAgreement::ECsDigitalAgreement_MAX)
	{
		UE_LOG(LogCsOnline, Warning, TEXT("%s: DigitalAgreement: ECsDigitalAgreement_MAX (MAX) is NOT Valid."), *Context);
		return;
	}

#if WITH_EDITOR
	if (UCsManager_DigitalAgreement* Manager = UCsManager_DigitalAgreement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_DigitalAgreement* Manager = UCsManager_DigitalAgreement::Get())
#endif // #if WITH_EDITOR
	{
		Manager->Accept(DigitalAgreement);
	}
	else
	{
		UE_LOG(LogCsOnline, Warning, TEXT("%s: No Manager DigitalAgreement of type UCsManager_DigitalAgreement was created."), *Context);
	}
}

void UCsScriptLibrary_Manager_DigitalAgreement::BindToEvent_OnAccept(const UObject* WorldContextObject, FCsScriptLibraryManagerDigitalAgreement_OnAccept Delegate)
{
	BindToEvent_OnAccept_Internal(NCsScriptLibraryManagerDigitalAgreement::Str::BindToEvent_OnAccept, WorldContextObject, Delegate);
}

void UCsScriptLibrary_Manager_DigitalAgreement::BindToEvent_OnAccept_Internal(const FString& Context, const UObject* WorldContextObject, const FCsScriptLibraryManagerDigitalAgreement_OnAccept& Delegate)
{
#if WITH_EDITOR
	if (UCsManager_DigitalAgreement* Manager = UCsManager_DigitalAgreement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_DigitalAgreement* Manager = UCsManager_DigitalAgreement::Get())
#endif // #if WITH_EDITOR
	{

		if (Delegate.IsBound())
		{
			if (!Manager->OnAccept_ScriptEvent.Contains(Delegate))
			{
				Manager->OnAccept_ScriptEvent.Add(Delegate);
			}
			else
			{
				UE_LOG(LogCsOnline, Warning, TEXT("%s: Delegate is already bound."), *Context);
			}
		}
		else
		{
			UE_LOG(LogCsOnline, Warning, TEXT("%s: No Delegate Bound."), *Context);
		}
	}
	else
	{
		UE_LOG(LogCsOnline, Warning, TEXT("%s: No Manager DigitalAgreement of type UCsManager_DigitalAgreement was created."), *Context);
	}
}

bool UCsScriptLibrary_Manager_DigitalAgreement::HasBeenAccepted(const UObject* WorldContextObject, const ECsDigitalAgreement& DigitalAgreement)
{
	if (DigitalAgreement == ECsDigitalAgreement::ECsDigitalAgreement_MAX)
	{
		UE_LOG(LogCsOnline, Warning, TEXT("UCsScriptLibrary_Manager_DigitalAgreement::HasBeenAccepted: DigitalAgreement: ECsDigitalAgreement_MAX (MAX) is NOT Valid."));
		return false;
	}

#if WITH_EDITOR
	if (UCsManager_DigitalAgreement* Manager = UCsManager_DigitalAgreement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_DigitalAgreement* Manager = UCsManager_DigitalAgreement::Get())
#endif // #if WITH_EDITOR
	{
		return Manager->HasBeenAccepted(DigitalAgreement);
	}
	else
	{
		UE_LOG(LogCsOnline, Warning, TEXT("UCsScriptLibrary_Manager_DigitalAgreement::HasBeenAccepted: No Manager DigitalAgreement of type UCsManager_DigitalAgreement was created."));
	}
	return false;
}

#pragma endregion Accept

// Do Not Accept
#pragma region

void UCsScriptLibrary_Manager_DigitalAgreement::DoNotAccept(const UObject* WorldContextObject, const ECsDigitalAgreement& DigitalAgreement)
{
	DoNotAccept_Internal(NCsScriptLibraryManagerDigitalAgreement::Str::DoNotAccept, WorldContextObject, DigitalAgreement);
}

void UCsScriptLibrary_Manager_DigitalAgreement::DoNotAccept_Internal(const FString& Context, const UObject* WorldContextObject, const ECsDigitalAgreement& DigitalAgreement)
{
	if (DigitalAgreement == ECsDigitalAgreement::ECsDigitalAgreement_MAX)
	{
		UE_LOG(LogCsOnline, Warning, TEXT("%s: DigitalAgreement: ECsDigitalAgreement_MAX (MAX) is NOT Valid."), *Context);
		return;
	}

#if WITH_EDITOR
	if (UCsManager_DigitalAgreement* Manager = UCsManager_DigitalAgreement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_DigitalAgreement* Manager = UCsManager_DigitalAgreement::Get())
#endif // #if WITH_EDITOR
	{
		Manager->DoNotAccept(DigitalAgreement);
	}
	else
	{
		UE_LOG(LogCsOnline, Warning, TEXT("%s: No Manager DigitalAgreement of type UCsManager_DigitalAgreement was created."), *Context);
	}
}

void UCsScriptLibrary_Manager_DigitalAgreement::BindToEvent_OnDoNotAccept(const UObject* WorldContextObject, FCsScriptLibraryManagerDigitalAgreement_OnDoNotAccept Delegate)
{
	BindToEvent_OnDoNotAccept_Internal(NCsScriptLibraryManagerDigitalAgreement::Str::BindToEvent_OnDoNotAccept, WorldContextObject, Delegate);
}

void UCsScriptLibrary_Manager_DigitalAgreement::BindToEvent_OnDoNotAccept_Internal(const FString& Context, const UObject* WorldContextObject, const FCsScriptLibraryManagerDigitalAgreement_OnDoNotAccept& Delegate)
{
#if WITH_EDITOR
	if (UCsManager_DigitalAgreement* Manager = UCsManager_DigitalAgreement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_DigitalAgreement* Manager = UCsManager_DigitalAgreement::Get())
#endif // #if WITH_EDITOR
	{
		if (Delegate.IsBound())
		{
			if (!Manager->OnDoNotAccept_ScriptEvent.Contains(Delegate))
			{
				Manager->OnDoNotAccept_ScriptEvent.Add(Delegate);
			}
			else
			{
				UE_LOG(LogCsOnline, Warning, TEXT("%s: Delegate is already bound."), *Context);
			}
		}
		else
		{
			UE_LOG(LogCsOnline, Warning, TEXT("%s: No Delegate Bound."), *Context);
		}
	}
	else
	{
		UE_LOG(LogCsOnline, Warning, TEXT("%s: No Manager DigitalAgreement of type UCsManager_DigitalAgreement was created."), *Context);
	}
}

#pragma endregion Do Not Accept