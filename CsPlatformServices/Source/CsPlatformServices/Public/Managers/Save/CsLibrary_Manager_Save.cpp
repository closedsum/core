// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Save/CsLibrary_Manager_Save.h"
#include "CsPlatformServices.h"

// Managers
#include "Managers/PlayerProfile/CsManager_PlayerProfile.h"
#include "Managers/Save/CsManager_Save.h"

#include "Managers/PlayerProfile/CsPlayerProfile.h"

UCsLibrary_Manager_Save::UCsLibrary_Manager_Save(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


// FileName
#pragma region

void UCsLibrary_Manager_Save::SetCurrentSave(const UObject* WorldContextObject, const ECsSave& Save)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		Manager->SetCurrentSave(Save);
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::Enumerate: No Manager Save of type UCsManager_Save was created."));
	}
}

#pragma endregion FileName

// Enumerate
#pragma region

void UCsLibrary_Manager_Save::Enumerate(const UObject* WorldContextObject)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		Manager->Enumerate();
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::Enumerate: No Manager Save of type UCsManager_Save was created."));
	}
}

void UCsLibrary_Manager_Save::BindToEvent_OnEnumerate(const UObject* WorldContextObject, FCsLibraryManagerSave_OnEnumerate Delegate)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		if (Delegate.IsBound())
		{
			if (!Manager->OnEnumerate_ScriptEvent.Contains(Delegate))
			{
				Manager->OnEnumerate_ScriptEvent.Add(Delegate);
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnEnumerate: Delegate is already bound."));
			}
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnEnumerate: No Delegate Bound."));
		}
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnEnumerate: No Manager Save of type UCsManager_Save was created."));
	}
}

#pragma endregion Enumerate

// Read
#pragma region

void UCsLibrary_Manager_Save::Read(const UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		Manager->Read(Profile, Save);
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::Read: No Manager Save of type UCsManager_Save was created."));
	}
}

void UCsLibrary_Manager_Save::BindToEvent_OnRead(const UObject* WorldContextObject, FCsLibraryManagerSave_OnRead Delegate)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		if (Delegate.IsBound())
		{
			if (!Manager->OnRead_ScriptEvent.Contains(Delegate))
			{
				Manager->OnRead_ScriptEvent.Add(Delegate);
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnRead: Delegate is already bound."));
			}
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnRead: No Delegate Bound."));
		}
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnRead: No Manager Save of type UCsManager_Save was created."));
	}
}

void UCsLibrary_Manager_Save::ReadAll(const UObject* WorldContextObject, const ECsPlayerProfile& Profile)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		Manager->ReadAll(Profile);
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::ReadAll: No Manager Save of type UCsManager_Save was created."));
	}
}

void UCsLibrary_Manager_Save::BindToEvent_OnReadAll(const UObject* WorldContextObject, FCsLibraryManagerSave_OnReadAll Delegate)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		if (Delegate.IsBound())
		{
			if (!Manager->OnReadAll_ScriptEvent.Contains(Delegate))
			{
				Manager->OnReadAll_ScriptEvent.Add(Delegate);
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnReadAll: Delegate is already bound."));
			}
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnReadAll: No Delegate Bound."));
		}
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnReadAll: No Manager Save of type UCsManager_Save was created."));
	}
}

#pragma endregion Read

// Write
#pragma region

void UCsLibrary_Manager_Save::Write(const UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		Manager->Write(Profile, Save);
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::Complete: No Manager Save of type UCsManager_Save was created."));
	}
}

void UCsLibrary_Manager_Save::BindToEvent_OnWrite(const UObject* WorldContextObject, FCsLibraryManagerSave_OnWrite Delegate)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		if (Delegate.IsBound())
		{
			if (!Manager->OnWrite_ScriptEvent.Contains(Delegate))
			{
				Manager->OnWrite_ScriptEvent.Add(Delegate);
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWrite: Delegate is already bound."));
			}
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWrite: No Delegate Bound."));
		}
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWrite: No Manager Achievement of type UCsManager_Save was created."));
	}
}

void UCsLibrary_Manager_Save::WriteAll(const UObject* WorldContextObject, const ECsPlayerProfile& Profile)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		Manager->WriteAll(Profile);
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::WriteAll: No Manager Save of type UCsManager_Save was created."));
	}
}

void UCsLibrary_Manager_Save::BindToEvent_OnWriteAll(const UObject* WorldContextObject, FCsLibraryManagerSave_OnWriteAll Delegate)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		if (Delegate.IsBound())
		{
			if (!Manager->OnWriteAll_ScriptEvent.Contains(Delegate))
			{
				Manager->OnWriteAll_ScriptEvent.Add(Delegate);
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWriteAll: Delegate is already bound."));
			}
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWriteAll: No Delegate Bound."));
		}
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWriteAll: No Manager Save of type UCsManager_Save was created."));
	}
}

#pragma endregion Write

// Delete
#pragma region

void UCsLibrary_Manager_Save::Delete(const UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		Manager->Delete(Profile, Save);
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::Delete: No Manager Save of type UCsManager_Save was created."));
	}
}

void UCsLibrary_Manager_Save::BindToEvent_OnDelete(const UObject* WorldContextObject, FCsLibraryManagerSave_OnDelete Delegate)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		if (Delegate.IsBound())
		{
			if (!Manager->OnDelete_ScriptEvent.Contains(Delegate))
			{
				Manager->OnDelete_ScriptEvent.Add(Delegate);
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDelete: Delegate is already bound."));
			}
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDelete: No Delegate Bound."));
		}
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDelete: No Manager Achievement of type UCsManager_Save was created."));
	}
}

void UCsLibrary_Manager_Save::DeleteAll(const UObject* WorldContextObject, const ECsPlayerProfile& Profile)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		Manager->DeleteAll(Profile);
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::DeleteAll: No Manager Save of type UCsManager_Save was created."));
	}
}

void UCsLibrary_Manager_Save::BindToEvent_OnDeleteAll(const UObject* WorldContextObject, FCsLibraryManagerSave_OnDeleteAll Delegate)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		if (Delegate.IsBound())
		{
			if (!Manager->OnDeleteAll_ScriptEvent.Contains(Delegate))
			{
				Manager->OnDeleteAll_ScriptEvent.Add(Delegate);
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDeleteAll: Delegate is already bound."));
			}
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDeleteAll: No Delegate Bound."));
		}
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDeleteAll: No Manager Save of type UCsManager_Save was created."));
	}
}

void UCsLibrary_Manager_Save::DeleteAllContent(const UObject* WorldContextObject)
{
#if WITH_EDITOR
	if (UCsManager_Save* Manager = UCsManager_Save::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Save* Manager = UCsManager_Save::Get())
#endif // #if WITH_EDITOR
	{
		Manager->DeleteAll(NCsPlayerProfile::AllProfiles);
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Save::DeleteAllContent: No Manager Save of type UCsManager_Save was created."));
	}
}

#pragma endregion Delete