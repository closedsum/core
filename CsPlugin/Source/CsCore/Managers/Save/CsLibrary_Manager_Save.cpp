// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Save/CsLibrary_Manager_Save.h"
#include "CsCore.h"

// Managers
#include "Managers/PlayerProfile/CsManager_PlayerProfile.h"
#include "Managers/Save/CsManager_Save.h"

#include "Managers/PlayerProfile/CsPlayerProfile.h"

UCsLibrary_Manager_Save::UCsLibrary_Manager_Save(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Enumerate
#pragma region

void UCsLibrary_Manager_Save::Enumerate(const ECsPlayerProfile& ProfileType)
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ProfileType))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				Manager_Save->Enumerate();
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::Enumerate: No Manager Save of type UCsManager_Save was created for Profile Type: %s."), EMCsPlayerProfile::Get().ToChar(ProfileType));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::Enumerate: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::Enumerate: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

void UCsLibrary_Manager_Save::BindToEvent_OnEnumerate(const ECsPlayerProfile& ProfileType, FCsLibraryManagerSave_OnEnumerate Delegate)
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ProfileType))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				if (Delegate.IsBound())
				{
					if (!Manager_Save->OnEnumerate_ScriptEvent.Contains(Delegate))
					{
						Manager_Save->OnEnumerate_ScriptEvent.Add(Delegate);
					}
					else
					{
						UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnEnumerate: Delegate is already bound."));
					}
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnEnumerate: No Delegate Bound."));
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnEnumerate: No Manager Save of type UCsManager_Save was created for Profile Type: %s."), EMCsPlayerProfile::Get().ToChar(ProfileType));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnEnumerate: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnEnumerate: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

#pragma endregion Enumerate

// Read
#pragma region

void UCsLibrary_Manager_Save::Read(const ECsPlayerProfile& ProfileType, const ECsSave& Save)
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ProfileType))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				Manager_Save->Read(Save);
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::Read: No Manager Save of type UCsManager_Save was created for Profile Type: %s."), EMCsPlayerProfile::Get().ToChar(ProfileType));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::Read: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::Read: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

void UCsLibrary_Manager_Save::BindToEvent_OnRead(const ECsPlayerProfile& ProfileType, FCsLibraryManagerSave_OnRead Delegate)
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ProfileType))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				if (Delegate.IsBound())
				{
					if (!Manager_Save->OnRead_ScriptEvent.Contains(Delegate))
					{
						Manager_Save->OnRead_ScriptEvent.Add(Delegate);
					}
					else
					{
						UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnRead: Delegate is already bound."));
					}
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnRead: No Delegate Bound."));
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnRead: No Manager Save of type UCsManager_Save was created for Profile Type: %s."), EMCsPlayerProfile::Get().ToChar(ProfileType));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnRead: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnRead: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

void UCsLibrary_Manager_Save::ReadAll(const ECsPlayerProfile& ProfileType)
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ProfileType))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				Manager_Save->ReadAll();
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::ReadAll: No Manager Save of type UCsManager_Save was created for Profile Type: %s."), EMCsPlayerProfile::Get().ToChar(ProfileType));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::ReadAll: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::ReadAll: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

void UCsLibrary_Manager_Save::BindToEvent_OnReadAll(const ECsPlayerProfile& ProfileType, FCsLibraryManagerSave_OnReadAll Delegate)
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ProfileType))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				if (Delegate.IsBound())
				{
					if (!Manager_Save->OnReadAll_ScriptEvent.Contains(Delegate))
					{
						Manager_Save->OnReadAll_ScriptEvent.Add(Delegate);
					}
					else
					{
						UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnReadAll: Delegate is already bound."));
					}
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnReadAll: No Delegate Bound."));
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnReadAll: No Manager Save of type UCsManager_Save was created for Profile Type: %s."), EMCsPlayerProfile::Get().ToChar(ProfileType));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnReadAll: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnReadAll: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

#pragma endregion Read

// Write
#pragma region

void UCsLibrary_Manager_Save::Write(const ECsPlayerProfile& ProfileType, const ECsSave& Save)
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ProfileType))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				Manager_Save->Write(Save);
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::Complete: No Manager Save of type UCsManager_Save was created for Profile Type: %s."), EMCsPlayerProfile::Get().ToChar(ProfileType));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::Complete: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::Complete: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

void UCsLibrary_Manager_Save::BindToEvent_OnWrite(const ECsPlayerProfile& ProfileType, FCsLibraryManagerSave_OnWrite Delegate)
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ProfileType))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				if (Delegate.IsBound())
				{
					if (!Manager_Save->OnWrite_ScriptEvent.Contains(Delegate))
					{
						Manager_Save->OnWrite_ScriptEvent.Add(Delegate);
					}
					else
					{
						UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWrite: Delegate is already bound."));
					}
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWrite: No Delegate Bound."));
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWrite: No Manager Achievement of type UCsManager_Save was created for Profile Type: %s."), EMCsPlayerProfile::Get().ToChar(ProfileType));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWrite: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWrite: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

void UCsLibrary_Manager_Save::WriteAll(const ECsPlayerProfile& ProfileType)
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ProfileType))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				Manager_Save->WriteAll();
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::WriteAll: No Manager Save of type UCsManager_Save was created for Profile Type: %s."), EMCsPlayerProfile::Get().ToChar(ProfileType));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::WriteAll: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::WriteAll: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

void UCsLibrary_Manager_Save::BindToEvent_OnWriteAll(const ECsPlayerProfile& ProfileType, FCsLibraryManagerSave_OnWriteAll Delegate)
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ProfileType))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				if (Delegate.IsBound())
				{
					if (!Manager_Save->OnWriteAll_ScriptEvent.Contains(Delegate))
					{
						Manager_Save->OnWriteAll_ScriptEvent.Add(Delegate);
					}
					else
					{
						UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWriteAll: Delegate is already bound."));
					}
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWriteAll: No Delegate Bound."));
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWriteAll: No Manager Save of type UCsManager_Save was created for Profile Type: %s."), EMCsPlayerProfile::Get().ToChar(ProfileType));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWriteAll: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnWriteAll: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

#pragma endregion Write

// Delete
#pragma region

void UCsLibrary_Manager_Save::Delete(const ECsPlayerProfile& ProfileType, const ECsSave& Save)
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ProfileType))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				Manager_Save->Delete(Save);
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::Delete: No Manager Save of type UCsManager_Save was created for Profile Type: %s."), EMCsPlayerProfile::Get().ToChar(ProfileType));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::Delete: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::Delete: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

void UCsLibrary_Manager_Save::BindToEvent_OnDelete(const ECsPlayerProfile& ProfileType, FCsLibraryManagerSave_OnDelete Delegate)
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ProfileType))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				if (Delegate.IsBound())
				{
					if (!Manager_Save->OnDelete_ScriptEvent.Contains(Delegate))
					{
						Manager_Save->OnDelete_ScriptEvent.Add(Delegate);
					}
					else
					{
						UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDelete: Delegate is already bound."));
					}
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDelete: No Delegate Bound."));
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDelete: No Manager Achievement of type UCsManager_Save was created for Profile Type: %s."), EMCsPlayerProfile::Get().ToChar(ProfileType));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDelete: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDelete: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

void UCsLibrary_Manager_Save::DeleteAll(const ECsPlayerProfile& ProfileType)
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ProfileType))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				Manager_Save->DeleteAll();
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::DeleteAll: No Manager Save of type UCsManager_Save was created for Profile Type: %s."), EMCsPlayerProfile::Get().ToChar(ProfileType));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::DeleteAll: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::DeleteAll: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

void UCsLibrary_Manager_Save::BindToEvent_OnDeleteAll(const ECsPlayerProfile& ProfileType, FCsLibraryManagerSave_OnDeleteAll Delegate)
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ProfileType))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				if (Delegate.IsBound())
				{
					if (!Manager_Save->OnDeleteAll_ScriptEvent.Contains(Delegate))
					{
						Manager_Save->OnDeleteAll_ScriptEvent.Add(Delegate);
					}
					else
					{
						UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDeleteAll: Delegate is already bound."));
					}
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDeleteAll: No Delegate Bound."));
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDeleteAll: No Manager Save of type UCsManager_Save was created for Profile Type: %s."), EMCsPlayerProfile::Get().ToChar(ProfileType));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDeleteAll: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::BindToEvent_OnDeleteAll: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

void UCsLibrary_Manager_Save::DeleteAllContent()
{
	if (UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get())
	{
		if (UCsPlayerProfile* Profile = Manager_PlayerProfile->GetProfile(ECsPlayerProfile::Profile1))
		{
			if (UCsManager_Save* Manager_Save = Profile->Manager_Save)
			{
				Manager_Save->DeleteAllContent();
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::DeleteAllContent: No Manager Save of type UCsManager_Save was created."));
			}
		}
		else
		{
			//UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::DeleteAllContent: Profile Type: %s does NOT exist."), EMCsPlayerProfile::Get().ToChar(ProfileType));
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Save::DeleteAllContent: No Manager PlayerProfile of type UCsManager_PlayerProfile was created."));
	}
}

#pragma endregion Delete