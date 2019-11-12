// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Save/CsManager_Save.h"
#include "CsCore.h"
#include "CsCVars.h"

// Player
#include "Engine/LocalPlayer.h"
// Online
#include "Interfaces/OnlineIdentityInterface.h"

UCsManager_Save::UCsManager_Save(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SaveFileNameExt = TEXT(".json");

	// SaveFileInfos
	{
		const int32& Count = EMCsSave::Get().Num();

		SaveFileInfos.Reserve(Count);
		SaveFileInfosAll.Reserve(Count);

		for (const ECsSave& Save : EMCsSave::Get())
		{
			const FString& Name = EMCsSave::Get().ToString(Save);

			SaveFileInfos.AddDefaulted();

			FCsSaveFileInfo& Info = SaveFileInfos.Last();

			Info.FileName		 = Name;
			Info.FileNameWithExt = Name + SaveFileNameExt;
			Info.bValid			 = true;
		}
	}
}

// UObject Interface
#pragma region

void UCsManager_Save::BeginDestroy()
{
	Super::BeginDestroy();
}

#pragma endregion UObject Interface

void UCsManager_Save::Init()
{
	// Set the FileNames again. This could change depending on the Profile.
	for (const ECsSave& Save : EMCsSave::Get())
	{
		const FString& Name = EMCsSave::Get().ToString(Save);

		FCsSaveFileInfo& Info = SaveFileInfos[(uint8)Save];

		Info.FileName		 = Name;
		Info.FileNameWithExt = Name + SaveFileNameExt;
	}

	for (FCsSaveFileInfo& Info : SaveFileInfos)
	{
		const uint8 Index = (uint8)ECsPlayerProfile::Profile1;

		Info.FileName		 = ProfileFileNamePrefixWithUndECscore + Info.FileName;
		Info.FileNameWithExt = ProfileFileNamePrefixWithUndECscore + Info.FileNameWithExt;
	}

	// 
	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
		// Online
	if (IUserCloud.IsValid())
	{
		IUserCloud->OnEnumerateUserFilesCompleteDelegates.AddUObject(this, &UCsManager_Save::OnEnumerateUserFilesComplete);
		IUserCloud->OnWriteUserFileCompleteDelegates.AddUObject(this, &UCsManager_Save::OnWriteUserFileComplete);
		IUserCloud->OnReadUserFileCompleteDelegates.AddUObject(this, &UCsManager_Save::OnReadUserFileComplete);
		IUserCloud->OnDeleteUserFileCompleteDelegates.AddUObject(this, &UCsManager_Save::OnDeleteUserFileComplete);

		for (FCsSaveFileInfo& Info : SaveFileInfos)
		{
			Info.bValid = false;
		}
	}

	ReadAll();
}

// Player
#pragma region

void UCsManager_Save::SetLocalPlayer(ULocalPlayer* Player)
{
	LocalPlayer = Player;
}

TSharedPtr<const FUniqueNetId> UCsManager_Save::GetLocalPlayerId()
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();
	return Identity->GetUniquePlayerId(LocalPlayer->GetControllerId());
}

const FUniqueNetId& UCsManager_Save::GetLocalPlayerIdRef()
{
	return *GetLocalPlayerId();
}

#pragma endregion Player

// Profile
#pragma region

void UCsManager_Save::SetProfileType(const ECsPlayerProfile& InProfileType)
{
	ProfileType = InProfileType;
}

void UCsManager_Save::SetProfileName(const FString& Name)
{
	ProfileName = Name;
}

#pragma endregion Profile

void UCsManager_Save::OnTick(const float& DeltaSeconds)
{
	TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* Current = Manager_MemoryResource.GetAllocatedHead();
	TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* Next    = Current;

	while (Next)
	{
		Current											= Next;
		FCsMemoryResource_SaveActionInfo* InfoContainer = **Current;
		Next											= Current->GetNextLink();

		FCsSaveActionInfo* Info = InfoContainer->Get();
		
		const ECsSave Save			= (ECsSave)Info->FileIndex;
		const ECsSaveAction& Action = Info->Action;

		// If In Progress, wait for Complete
		if (Info->InProgress())
			break;
		// If Complete, handle completion (fire any events) and move onto next Action
		if (Info->IsComplete())
		{
			const bool WasSuccessful = Info->WasSuccessful();

			// Enumerate
			if (Action == ECsSaveAction::Enumerate)
			{
				OnEnumerate_Event.Broadcast(WasSuccessful);
				OnEnumerate_ScriptEvent.Broadcast(WasSuccessful);
			}
			// Read
			else
			if (Action == ECsSaveAction::Read)
			{
				OnRead_Event.Broadcast(WasSuccessful, Save);
				OnRead_ScriptEvent.Broadcast(WasSuccessful, Save);
			}
			// Read All
			else
			if (Action == ECsSaveAction::ReadAll)
			{
				OnReadAll_Event.Broadcast();
				OnReadAll_ScriptEvent.Broadcast();
			}
			// Write
			else
			if (Action == ECsSaveAction::Write)
			{
				OnWrite_Event.Broadcast(WasSuccessful, Save);
				OnWrite_ScriptEvent.Broadcast(WasSuccessful, Save);
			}
			// Write All
			else
			if (Action == ECsSaveAction::WriteAll)
			{
				OnWriteAll_Event.Broadcast();
				OnWriteAll_ScriptEvent.Broadcast();
			}
			// Delete
			else
			if (Action == ECsSaveAction::Delete)
			{
				OnDelete_Event.Broadcast(WasSuccessful, Save);
				OnDelete_ScriptEvent.Broadcast(WasSuccessful, Save);
			}
			// Delete All
			else
			if (Action == ECsSaveAction::DeleteAll)
			{
				OnDeleteAll_Event.Broadcast();
				OnDeleteAll_ScriptEvent.Broadcast();
			}
			Manager_MemoryResource.Deallocate(InfoContainer);
			continue;
		}
		// If Ready to Process, Start
		if (Info->IsReadyToProcess())
		{
			// Enumerate
			if (Action == ECsSaveAction::Enumerate)
			{
				Info->StartProgress();
				Enumerate_Internal();
				break;
			}
			// Read
			else
			if (Action == ECsSaveAction::Read)
			{
				Info->StartProgress();
				Read_Internal(Info);
				break;
			}
			// Read All
			else
			if (Action == ECsSaveAction::ReadAll)
			{
				ReadAll_Internal(Info);

				// Update Next since Current's Next could have changed
				Next = Current->GetNextLink();

				Manager_MemoryResource.Deallocate(InfoContainer);
			}
			// Write
			else
			if (Action == ECsSaveAction::Write)
			{
				Info->StartProgress();
				Write_Internal(Info);
				break;
			}
			// Write All
			else
			if (Action == ECsSaveAction::WriteAll)
			{
				WriteAll_Internal(Info);

				// Update Next since Current's Next could have changed
				Next = Current->GetNextLink();

				Manager_MemoryResource.Deallocate(InfoContainer);
			}
			// Delete
			else
			if (Action == ECsSaveAction::Delete)
			{
				Info->StartProgress();
				Delete_Internal(Info);
				break;
			}
			// Delete All
			else
			if (Action == ECsSaveAction::DeleteAll)
			{
				DeleteAll_Internal(Info);

				// Update Next since Current's Next could have changed
				Next = Current->GetNextLink();

				Manager_MemoryResource.Deallocate(InfoContainer);
			}
		}
	}
}

// FileName
#pragma region

void UCsManager_Save::SetProfileFileNamePrefix(const FString& Prefix)
{
	ProfileFileNamePrefix				= Prefix;
	ProfileFileNamePrefixWithUndECscore = Prefix + TEXT("_");
}

void UCsManager_Save::SetSaveFileNameExt(const FString& Ext)
{
	SaveFileNameExt = Ext;
}

void UCsManager_Save::SetSaveFileName(const ECsSave& Save, const FString& FileName)
{
	// TODO: Need to Delete file if it already exists and then Write new file.
	FCsSaveFileInfo& Info = SaveFileInfos[(uint8)Save];

	Info.FileName = FileName;
	Info.FileNameWithExt = FileName + SaveFileNameExt;
}

const FString& UCsManager_Save::GetSaveFileName(const ECsSave& Save)
{
	return SaveFileInfos[(uint8)Save].FileName;
}

const FCsSaveFileInfo& UCsManager_Save::GetSaveFileInfo(const ECsSave& Save)
{
	return SaveFileInfos[(uint8)Save];
}

#pragma endregion FileName

// Data
#pragma region

void UCsManager_Save::SetSaveDataTest(const ECsSave& Save, const FString& InData)
{

}

void UCsManager_Save::SetSaveData(const ECsSave& Save)
{

}

void UCsManager_Save::GetSaveData(const ECsSave& Save, FString& OutData)
{
	GetSaveData((int32)Save, OutData);
}

void UCsManager_Save::GetSaveData(const int32& Index, FString& OutData)
{
}

#pragma endregion Data

// Action
#pragma region

void UCsManager_Save::QueueAction(const ECsSaveAction& Action, const ECsSave& Save)
{
	QueueAction(Action, (int32)Save);
}

void UCsManager_Save::QueueAction(const ECsSaveAction& Action, const int32& Index)
{
	checkf(Index < SaveFileInfos.Num(), TEXT(""));

	// Allocate SaveActionInfo from a pool
	FCsMemoryResource_SaveActionInfo* InfoContainer = Manager_MemoryResource.Allocate();
	FCsSaveActionInfo* Info							= InfoContainer->Get();

	Info->Reset();

	Info->Action    = Action;
	Info->FileIndex = Index;
	Info->Profile   = ProfileType;
}

void UCsManager_Save::QueueAction(const ECsSaveAction& Action)
{
	QueueAction(Action, INDEX_NONE);
}

void UCsManager_Save::QueueActionAsHead(const ECsSaveAction& Action, const int32& Index)
{
	FCsMemoryResource_SaveActionInfo* InfoContainer = Manager_MemoryResource.AllocateBeforeHead();
	FCsSaveActionInfo* Info							= InfoContainer->Get();

	Info->Reset();

	Info->Action	  = Action;
	Info->FileIndex = Index;
	Info->Profile = ProfileType;
}

void UCsManager_Save::QueueActionAsHead(const ECsSaveAction& Action)
{
	QueueActionAsHead(Action, INDEX_NONE);
}

void UCsManager_Save::QueueActionAfterHead(const ECsSaveAction& Action, const int32& Index)
{
	FCsMemoryResource_SaveActionInfo* InfoContainer = Manager_MemoryResource.AllocateAfterHead();
	FCsSaveActionInfo* Info							= InfoContainer->Get();

	Info->Reset();

	Info->Action    = Action;
	Info->FileIndex = Index;
	Info->Profile	= ProfileType;
}

void UCsManager_Save::QueueActionAfterHead(const ECsSaveAction& Action)
{
	QueueActionAfterHead(Action, INDEX_NONE);
}

#pragma endregion Action

// Enumerate
#pragma region

void UCsManager_Save::Enumerate()
{
	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!EnumerateUserFilesState.IsQueued())
		{
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Enumerate: Queueing Enumerate for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			QueueAction(ECsSaveAction::Enumerate);
		}
	}
	else
	{

	}
}

void UCsManager_Save::Enumerate_Internal()
{
	EnumerateUserFilesState.Reset();

	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		EnumerateUserFilesState.Queue();

		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Enumerate_Internal: Starting Enumerate for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		IUserCloud->EnumerateUserFiles(UserId);
	}
	else
	{

	}
}

#pragma endregion Enumerate

// Read
#pragma region

void UCsManager_Save::Read(const ECsSave& Save)
{
	Read((int32)Save);
}

void UCsManager_Save::Read(const int32& Index)
{
	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Check to Queue Enumerate
		if (!EnumerateUserFilesState.IsComplete() &&
			!EnumerateUserFilesState.IsQueued())
		{
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Read: Queueing Enumerate for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			EnumerateUserFilesState.Queue();
			QueueAction(ECsSaveAction::Enumerate);
		}

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Read: Queueing Read for File: %s for Profile: %s for Player: %s at %s."), *(SaveFileInfos[Index].FileNameWithExt), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(ECsSaveAction::Read, Index);
	}
}

void UCsManager_Save::Read_Internal(FCsSaveActionInfo* ActionInfo)
{
	FCsSaveFileInfo& FileInfo = SaveFileInfos[ActionInfo->FileIndex];
	FileInfo.bRead			  = false;

	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (EnumerateUserFilesState.bSuccess &&
			FileInfo.bValid)
		{
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Read_Internal: Starting Read for File: %s for Profile: %s for Player: %s at %s."), *(FileInfo.FileNameWithExt), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			IUserCloud->ReadUserFile(UserId, FileInfo.FileNameWithExt);
		}
		else
		{
			// Enumeration failed
			if (!EnumerateUserFilesState.bSuccess)
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Read_Internal: File: %s has NOT been enumerated properly for Player: %s."), *(FileInfo.FileNameWithExt), *(UserId.ToString()));
			}
			// Not Valid
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Read_Internal: File: %s is NOT Valid (does NOT exist in the Cloud) for Player: %s."), *(FileInfo.FileNameWithExt), *(UserId.ToString()));
			}
			ActionInfo->Complete();
		}
	}
	// Local
	else
	{

	}
}

void UCsManager_Save::ReadAll()
{
	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!EnumerateUserFilesState.IsComplete() &&
			!EnumerateUserFilesState.IsQueued())
		{
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::ReadAll: Queueing Enumerate for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			EnumerateUserFilesState.Queue();
			QueueAction(ECsSaveAction::Enumerate);
		}

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::ReadAll: Queueing ReadAll for Profile: %s for Player: %s at %s."), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(ECsSaveAction::ReadAll);
	}
	// Local
	else
	{

	}
}

void UCsManager_Save::ReadAll_Internal(FCsSaveActionInfo* ActionInfo)
{
	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::ReadAll_Internal: Starting ReadAll for Profile: %s for Player: %s at %s."), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* Current = Manager_MemoryResource.GetAllocatedHead();
		FCsMemoryResource_SaveActionInfo* InfoContainer					= **Current;
		FCsSaveActionInfo* ReadAllActionInfo							= InfoContainer->Get();

		// Queue Read for all Files
		if (EnumerateUserFilesState.bSuccess)
		{
			const int32 Count = SaveFileInfos.Num();

			for (int32 I = 0; I < Count; ++I) 
			{
				FCsSaveFileInfo& FileInfo = SaveFileInfos[I];

				if (FileInfo.bValid)
				{
					FileInfo.bRead = false;

					FCsMemoryResource_SaveActionInfo* ReadInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
					FCsSaveActionInfo* ReadInfo						    = ReadInfoContainer->Get();

					ReadInfo->Reset();

					ReadInfo->Action    = ECsSaveAction::Read;
					ReadInfo->FileIndex = I;

					// Update InfoContainer so actions get queued in order
					InfoContainer = ReadInfoContainer;

	#if !UE_BUILD_SHIPPING
					if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
					{
						UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::ReadAll_Internal: Queueing Read for File: %s for Profile: %s for Player: %s at %s."), *(FileInfo.FileNameWithExt), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
					}
	#endif // #if !UE_BUILD_SHIPPING
				}
			}

			// Queue Read All event at end
			FCsMemoryResource_SaveActionInfo* ReadAllInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
			FCsSaveActionInfo* ReadAllInfo						   = ReadAllInfoContainer->Get();

			ReadAllInfo->Reset();

			ReadAllInfo->Action = ECsSaveAction::ReadAll;
			ReadAllInfo->Complete();
		}
		// Abort / Complete
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::ReadAll_Internal: Files have NOT been enumerated properly for Player: %s."), *(UserId.ToString()));

			ReadAllActionInfo->Complete();
		}
	}
	// Local
	else
	{

	}
}

#pragma endregion Read

// Write
#pragma region

void UCsManager_Save::Write(const ECsSave& Save)
{
	Write((int32)Save);
}

void UCsManager_Save::Write(const int32& Index)
{
	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Write: Queueing Write for File: %s for Profile: %s for Player: %s at %s."), *(SaveFileInfos[Index].FileNameWithExt), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(ECsSaveAction::Write, Index);
	}
	// Local
	else
	{

	}
}

void UCsManager_Save::Write_Internal(FCsSaveActionInfo* ActionInfo)
{
	const int32& FileIndex	  = ActionInfo->FileIndex;
	FCsSaveFileInfo& FileInfo = SaveFileInfos[FileIndex];
	FileInfo.bWrite			  = false;

	GetSaveData(FileIndex, FileInfo.WriteContents);

	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Write then Enumerate

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Write_Internal: Starting Write for File: %s for Profile: %s for Player: %s at %s."), *(FileInfo.FileNameWithExt), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));

			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Write_Internal: Contents:"));

			UE_LOG(LogCs, Warning, TEXT("%s"), *(FileInfo.WriteContents));

			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Write_Internal: Queueing Enumerate after Write for Profile: %s for Player: %s at %s."), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueActionAfterHead(ECsSaveAction::Enumerate);

		int32 Size = FileInfo.WriteContents.Len();
		TArray<uint8> FileContents;
		FileContents.AddUninitialized(Size);

		// Assume UFT8
		StringToBytes(FileInfo.WriteContents, FileContents.GetData(), Size);

		IUserCloud->WriteUserFile(UserId, FileInfo.FileNameWithExt, FileContents);
	}
	// Local
	else
	{

	}
}

void UCsManager_Save::WriteAll()
{
	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::WriteAll: Queueing WriteAll for Profile: %s for Player: %s at %s."), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(ECsSaveAction::WriteAll);
	}
	// Local
	else
	{

	}
}

void UCsManager_Save::WriteAll_Internal(FCsSaveActionInfo* ActionInfo)
{
	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Queue Write for all Files

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::WriteAll_Internal: Starting WriteAll for Profile: %s for Player: %s at %s."), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* Current = Manager_MemoryResource.GetAllocatedHead();
		FCsMemoryResource_SaveActionInfo* InfoContainer					= **Current;

		const int32 Count = SaveFileInfos.Num();

		for (int32 I = 0; I < Count; ++I) 
		{
			FCsSaveFileInfo& FileInfo = SaveFileInfos[I];

			FCsMemoryResource_SaveActionInfo* WriteInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
			FCsSaveActionInfo* WriteInfo						 = WriteInfoContainer->Get();

			WriteInfo->Reset();

			WriteInfo->Action      = ECsSaveAction::Write;
			WriteInfo->FileIndex   = I;

			// Update InfoContainer so actions get queued in order
			InfoContainer = WriteInfoContainer;

#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::WriteAll_Internal: Queueing Write for File: %s for Profile: %s for Player: %s at %s."), *(FileInfo.FileNameWithExt), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING
		}

		// Queue Write All event at end
		FCsMemoryResource_SaveActionInfo* WriteAllInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
		FCsSaveActionInfo* WriteAllInfo							= WriteAllInfoContainer->Get();

		WriteAllInfo->Reset();

		WriteAllInfo->Action = ECsSaveAction::WriteAll;
		WriteAllInfo->Complete();

		InfoContainer = WriteAllInfoContainer;

		// Queue Enumerate
		FCsMemoryResource_SaveActionInfo* EnumerateInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
		FCsSaveActionInfo* EnumerateInfo						 = EnumerateInfoContainer->Get();

		EnumerateInfo->Reset();

		EnumerateInfo->Action = ECsSaveAction::Enumerate;

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::WriteAll_Internal: Queueing Enumerate for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING
	}
	// Local
	else
	{

	}
}

#pragma endregion Write

// Delete
#pragma region

void UCsManager_Save::Delete(const ECsSave& Save)
{
	Delete((int32)Save);
}

void UCsManager_Save::Delete(const int32& Index)
{
	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Check to Queue Enumerate
		if (!EnumerateUserFilesState.IsComplete() &&
			!EnumerateUserFilesState.IsQueued())
		{
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Delete: Queueing Enumerate for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			EnumerateUserFilesState.Queue();
			QueueAction(ECsSaveAction::Enumerate);
		}

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Delete: Queueing Delete for File: %s for Player: %s at %s."), *(SaveFileInfos[Index].FileNameWithExt), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(ECsSaveAction::Delete, Index);
	}
	// Local
	else
	{

	}
}

void UCsManager_Save::Delete_Internal(FCsSaveActionInfo* ActionInfo)
{
	const int32& Index		  = ActionInfo->FileIndex;
	FCsSaveFileInfo& FileInfo = ActionInfo->IsAllProfiles() ? SaveFileInfosAll[Index] : SaveFileInfos[Index];
	FileInfo.bDelete		  = false;

	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();
		// Files have been Enumerated
		if (EnumerateUserFilesState.bSuccess)
		{
			// File has been Enumerated
			if (FileInfo.bValid)
			{
				// Delete, Enumerate, then ReadAll

				TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* AllocatedHead = Manager_MemoryResource.GetAllocatedHead();
				FCsMemoryResource_SaveActionInfo* InfoContainer						  = **AllocatedHead;

				// Enumerate
				{
					FCsMemoryResource_SaveActionInfo* EnumerateInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
					FCsSaveActionInfo* EnumerateInfo						 = EnumerateInfoContainer->Get();

					EnumerateInfo->Reset();

					EnumerateInfo->Action = ECsSaveAction::Enumerate;

					InfoContainer = EnumerateInfoContainer;
				}
				// ReadAll
				{
					FCsMemoryResource_SaveActionInfo* ReadAllInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
					FCsSaveActionInfo* ReadAllInfo						   = ReadAllInfoContainer->Get();

					ReadAllInfo->Reset();

					ReadAllInfo->Action = ECsSaveAction::ReadAll;
				}

#if !UE_BUILD_SHIPPING
				if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
				{
					UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Delete_Internal: Starting Delete for File: %s for Player: %s at %s."), *(FileInfo.FileNameWithExt), *(UserId.ToString()), *(FDateTime::Now().ToString()));

					UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Delete_Internal: Queueing Enumerate after Delete for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));

					UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Delete_Internal: Queueing ReadAll after Enumerate for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
				}
#endif // #if !UE_BUILD_SHIPPING

				IUserCloud->DeleteUserFile(UserId, FileInfo.FileNameWithExt, true, true);
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Delete_Internal: File: %s is NOT Valid (does NOT exist in the Cloud) for Player: %s."), *(FileInfo.FileNameWithExt), *(UserId.ToString()));

				ActionInfo->Complete();
			}
		}
		// Abort / Complete
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Delete_Internal: Files have NOT been enumerated properly for Player: %s."), *(UserId.ToString()));

			ActionInfo->Complete();

			/*
			// Push Enumerate to Top (Head)
			QueueActionAsHead(ECsSaveAction::Enumerate);
			// Push Read after Enumerate (Head)
			QueueActionAfterHead(ECsSaveAction::Read, Index);

			// Reset Delete Action
			int32 FileIndex = Index;
			ActionInfo->Reset();
			ActionInfo->Action = ECsSaveAction::Delete;
			ActionInfo->FileIndex = FileIndex;

#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Delete_Internal: Queueing Enumerate for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));

				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Delete_Internal: Queueing ReadAll after Enumerate for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));

				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Delete_Internal: Queueing Delete after Enumerate for File: %s for Player: %s at %s."), *(FileInfo.FileNameWithExt), *(UserId.ToString()), *(FDateTime::Now().ToString()));

			}
#endif // #if !UE_BUILD_SHIPPING
*/
		}
	}
	// Local
	else
	{

	}
}

void UCsManager_Save::DeleteAll()
{
	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Check to Queue Enumerate
		if (!EnumerateUserFilesState.IsComplete() &&
			!EnumerateUserFilesState.IsQueued())
		{
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::DeleteAll: Queueing Enumerate for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			EnumerateUserFilesState.Queue();
			QueueAction(ECsSaveAction::Enumerate);
		}

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::DeleteAll: Queueing DeleteAll for Profile: %s for Player: %s at %s."), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(ECsSaveAction::DeleteAll);
	}
	// Local
	else
	{

	}
}

void UCsManager_Save::DeleteAllContent()
{
	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Check to Queue Enumerate
		if (!EnumerateUserFilesState.IsComplete() &&
			!EnumerateUserFilesState.IsQueued())
		{
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::DeleteAllContent: Queueing Enumerate for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			EnumerateUserFilesState.Queue();
			QueueAction(ECsSaveAction::Enumerate);
		}

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::DeleteAllContent: Queueing DeleteAll for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		// Allocate SaveActionInfo from a pool
		FCsMemoryResource_SaveActionInfo* InfoContainer = Manager_MemoryResource.Allocate();
		FCsSaveActionInfo* Info							= InfoContainer->Get();

		Info->Reset();

		Info->Action  = ECsSaveAction::DeleteAll;
		Info->Profile = ECsPlayerProfile::ECsPlayerProfile_MAX;
	}
	// Local
	else
	{

	}
}

void UCsManager_Save::DeleteAll_Internal(FCsSaveActionInfo* ActionInfo)
{
	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Queue Delete for all Files

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			if (ActionInfo->IsAllProfiles())
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::DeleteAll_Internal: Starting DeleteAll for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::DeleteAll_Internal: Starting DeleteAll for ProfileName: %s for Player: %s at %s."), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
		}
#endif // #if !UE_BUILD_SHIPPING

		TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* Current = Manager_MemoryResource.GetAllocatedHead();
		FCsMemoryResource_SaveActionInfo* InfoContainer					= **Current;

		const int32 Count = ActionInfo->IsAllProfiles() ? SaveFileInfosAll.Num() : SaveFileInfos.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			FCsSaveFileInfo& FileInfo = ActionInfo->IsAllProfiles() ? SaveFileInfosAll[I] : SaveFileInfos[I];

			if (FileInfo.bValid)
			{
				FileInfo.bRead = false;

				FCsMemoryResource_SaveActionInfo* DeleteInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
				FCsSaveActionInfo* DeleteInfo						  = DeleteInfoContainer->Get();

				DeleteInfo->Reset();

				DeleteInfo->Action      = ECsSaveAction::Delete;
				DeleteInfo->Profile		= ActionInfo->Profile;
				DeleteInfo->FileIndex   = I;

				// Update InfoContainer so actions get queued in order
				InfoContainer = DeleteInfoContainer;

#if !UE_BUILD_SHIPPING
				if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
				{
					if (ActionInfo->IsAllProfiles())
					{
						UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::DeleteAll_Internal: Queueing Delete for File: %s for Player: %s at %s."), *(FileInfo.FileNameWithExt), *(UserId.ToString()), *(FDateTime::Now().ToString()));
					}
					else
					{
						UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::DeleteAll_Internal: Queueing Delete for File: %s for Profile: %s for Player: %s at %s."), *(FileInfo.FileNameWithExt), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
					}
				}
#endif // #if !UE_BUILD_SHIPPING
			}
		}

		// Queue Delete All at end
		FCsMemoryResource_SaveActionInfo* DeleteAllInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
		FCsSaveActionInfo* DeleteAllInfo						 = DeleteAllInfoContainer->Get();

		DeleteAllInfo->Reset();

		DeleteAllInfo->Action = ECsSaveAction::DeleteAll;
		DeleteAllInfo->Complete();
	}
	// Local
	else
	{

	}
}

#pragma endregion Delete

// IOnlineUserCloud
#pragma region

IOnlineUserCloudPtr UCsManager_Save::GetUserCloudInterface()
{
	if (LocalPlayer && LocalPlayer->GetControllerId() != -1)
	{
		int32 ControllerId = LocalPlayer->GetControllerId();

		if (IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get())
		{
			IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();
			if (Identity.IsValid())
			{
				TSharedPtr<const FUniqueNetId> UserId = Identity->GetUniquePlayerId(LocalPlayer->GetControllerId());

				if (UserId.IsValid())
				{
					IOnlineUserCloudPtr OnlineUserCloud = OnlineSub->GetUserCloudInterface();

					if (OnlineUserCloud.IsValid())
					{
						return OnlineUserCloud;
					}
					UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::GetUserCloudInterface (%d): No Online User Cloud Interface found."), ControllerId);
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::GetUserCloudInterface (%d): No UniquePlayerId set for Local Player: %d."), ControllerId, ControllerId);
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::GetUserCloudInterface (%d): No Online Identity found."), ControllerId);
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::GetUserCloudInterface (%d): No Online Subsystem found."), ControllerId);
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::GetUserCloudInterface: No Local Player set."));
	}
	return nullptr;
}

void UCsManager_Save::OnEnumerateUserFilesComplete(bool WasSuccessful, const FUniqueNetId& UserId)
{
	EnumerateUserFilesState.bSuccess = WasSuccessful;
	EnumerateUserFilesState.Complete();

	TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* AllocatedHead = Manager_MemoryResource.GetAllocatedHead();
	
	checkf(AllocatedHead, TEXT("UCsManager_Save::OnEnumerateUserFilesComplete: No Read Action was queued."));

	FCsMemoryResource_SaveActionInfo* InfoContainer	= **AllocatedHead;
	FCsSaveActionInfo* ActionInfo					= InfoContainer->Get();

	checkf(ActionInfo->Action == ECsSaveAction::Enumerate, TEXT("UCsManager_Save::OnEnumerateUserFilesComplete: Current Action: %s is NOT Enumerate."), *(EMCsSaveAction::Get().ToChar(ActionInfo->Action)));

	if (WasSuccessful)
	{
		ActionInfo->Success();

		IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();

		TArray<FCloudFileHeader> UserFiles;
		IUserCloud->GetUserFileList(UserId, UserFiles);

		const int32 Count	  = UserFiles.Num();
		const int32 InfoCount = SaveFileInfosAll.Num();

		for (FCsSaveFileInfo& Info : SaveFileInfos)
		{
			Info.bValid = false;
		}

		for (int32 I = InfoCount; I < Count; ++I)
		{
			SaveFileInfosAll.AddDefaulted();
		}

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnEnumerateUserFilesComplete: Finished Enumerate for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));

			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnEnumerateUserFilesComplete: Enumerating %d Files."), Count);
		}
#endif // #if !UE_BUILD_SHIPPING

		for (int32 I = 0; I < Count; ++I)
		{
			const FCloudFileHeader& Header = UserFiles[I];

			FString DLName = Header.DLName;

			// Get just the FileName + Extension

			// TODO: Path separator may be different on different platforms (i.e. '/' or '\')
			//		 For now, assume '/' (Backslash)

			int32 BackslashIndex = INDEX_NONE;
			DLName.FindLastChar('/', BackslashIndex);

			if (BackslashIndex != INDEX_NONE)
				DLName = DLName.Right(DLName.Len() - (BackslashIndex + 1));

			const FString FileNameWithExt = DLName;

			DLName.RemoveFromEnd(SaveFileNameExt);

			const FString FileName = DLName;

			// Check Prefix (for the Profile the save is associated with)
			bool bMatchesPrefix = DLName.StartsWith(ProfileFileNamePrefix);

			// This Profile
			if (bMatchesPrefix)
			{
				// Determine the Save
				FString SaveAsString = FileName;
				
				SaveAsString.RemoveFromStart(ProfileFileNamePrefixWithUndECscore);

				const FName SaveAsName = FName(*SaveAsString);
				
				if (EMCsSave::Get().IsValidEnum(SaveAsName))
				{
					const ECsSave& Save = EMCsSave::Get().GetEnum(SaveAsName);
					const int32 Index   = (int32)Save;

					FCsSaveFileInfo& Info = SaveFileInfos[Index];

					Info.FileNameWithExt = FileNameWithExt;
					Info.FileName		 = FileName;
					Info.bValid			 = true;

#if !UE_BUILD_SHIPPING
					if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
					{
						UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnEnumerateUserFilesComplete: %d. Profile: %s. Save: %s. %s."), Index, *ProfileName, *SaveAsString, *(Header.DLName));
					}
#endif // #if !UE_BUILD_SHIPPING
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnEnumerateUserFilesComplete: Save Type: %s is NOT Valid for %s."), *SaveAsString, *(Header.DLName));
				}
			}

			// All Profiles
			
			FCsSaveFileInfo& AllInfo = SaveFileInfosAll[I];

			AllInfo.FileNameWithExt = FileNameWithExt;
			AllInfo.FileName		= FileName;
			AllInfo.bValid			= true;

#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnEnumerateUserFilesComplete: %d. %s."), I, *(Header.DLName));
			}
#endif // #if !UE_BUILD_SHIPPING
		}

		ActionInfo->Complete();
		OnEnumerate_AsyncEvent.Broadcast(WasSuccessful);
		OnEnumerate_AsyncScriptEvent.Broadcast(WasSuccessful);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnEnumerateUserFilesComplete: Failed for Player: %s"), *(UserId.ToString()));

		ActionInfo->Complete();
	}
}

void UCsManager_Save::OnReadUserFileComplete(bool WasSuccessful, const FUniqueNetId& UserId, const FString& FileName)
{
	TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* AllocatedHead = Manager_MemoryResource.GetAllocatedHead();

	checkf(AllocatedHead, TEXT("UCsManager_Save::OnReadUserFileComplete: No Read Action was queued."));

	FCsMemoryResource_SaveActionInfo* InfoContainer = **AllocatedHead;
	FCsSaveActionInfo* ActionInfo					= InfoContainer->Get();

	checkf(ActionInfo->Action == ECsSaveAction::Read, TEXT("UCsManager_Save::OnReadUserFileComplete: Current Action: %s is NOT Read."), *(EMCsSaveAction::Get().ToChar(ActionInfo->Action)));

	if (WasSuccessful)
	{
		ActionInfo->Success();

		// Read Contents
		IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();

		TArray<uint8> FileContents;
		IUserCloud->GetFileContents(UserId, FileName, FileContents);

		FString Contents = BytesToString(FileContents.GetData(), FileContents.Num());

		// Do checks for SaveActionInfo
		checkf(ActionInfo->FileIndex >= 0 && ActionInfo->FileIndex < SaveFileInfos.Num(), TEXT("UCsManager_Save::OnReadUserFileComplete: Invalid FileIndex: %d for SaveFileInfo."), ActionInfo->FileIndex);

		FCsSaveFileInfo& FileInfo = SaveFileInfos[ActionInfo->FileIndex];

		checkf(FileInfo.FileNameWithExt == FileName, TEXT("UCsManager_Save::OnReadUserFileComplete: Mistach between FileNameWithExt: %s and FileName: %s."), *(FileInfo.FileNameWithExt), *FileName);

		FileInfo.bRead		  = true;
		FileInfo.ReadContents = Contents;
		FileInfo.ReadTime     = FDateTime::Now();

		if (Contents.IsEmpty())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnReadUserFileComplete: Failed to read File: %s for Profile: %s for Player: %s at %s."), *FileName, *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnReadUserFileComplete: Finished Read for File: %s for Profile: %s for Player: %s at %s."), *FileName, *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));

			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnReadUserFileComplete: Contents:"));

			UE_LOG(LogCs, Warning, TEXT("%s"), *(FileInfo.ReadContents));
		}
#endif // #if !UE_BUILD_SHIPPING

		ActionInfo->Complete();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnReadUserFileComplete: Failed to read File: %s for Profile: %s for Player: %s at %s."), *FileName, *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		
		ActionInfo->Complete();
	}

	const ECsSave Save = (ECsSave)ActionInfo->FileIndex;

	OnRead_AsyncEvent.Broadcast(WasSuccessful, Save);
	OnRead_AsyncScriptEvent.Broadcast(WasSuccessful, Save);
}

void UCsManager_Save::OnWriteUserFileComplete(bool WasSuccessful, const FUniqueNetId& UserId, const FString& FileName)
{
	TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* AllocatedHead = Manager_MemoryResource.GetAllocatedHead();

	checkf(AllocatedHead, TEXT("UCsManager_Save::OnWriteUserFileComplete: No Write Action was queued."));

	FCsMemoryResource_SaveActionInfo* InfoContainer = **AllocatedHead;
	FCsSaveActionInfo* ActionInfo					= InfoContainer->Get();

	checkf(ActionInfo->Action == ECsSaveAction::Write, TEXT("UCsManager_Save::OnWriteUserFileComplete: Current Action: %s is NOT Write."), *(EMCsSaveAction::Get().ToChar(ActionInfo->Action)));

	if (WasSuccessful)
	{
		ActionInfo->Success();

		// Do checks for SaveActionInfo
		checkf(ActionInfo->FileIndex >= CS_EMPTY && ActionInfo->FileIndex < SaveFileInfos.Num(), TEXT("UCsManager_Save::OnWriteUserFileComplete: Invalid FileIndex: %d for SaveFileInfo."), ActionInfo->FileIndex);

		FCsSaveFileInfo& FileInfo = SaveFileInfos[ActionInfo->FileIndex];

		checkf(FileInfo.FileNameWithExt == FileName, TEXT("UCsManager_Save::OnWriteUserFileComplete: Mistach between FileNameWithExt: %s and FileName: %s."), *(FileInfo.FileNameWithExt), *FileName);

		FileInfo.bWrite	   = true;
		FileInfo.WriteTime = FDateTime::Now();

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnWriteUserFileComplete: Finished Write for File: %s for Profile: %s for Player: %s at %s."), *FileName, *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		ActionInfo->Complete();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnWriteUserFileComplete: Failed to write File: %s for Profile: %s for Player: %s"), *FileName, *ProfileName, *(UserId.ToString()));

		ActionInfo->Complete();
	}

	const ECsSave Save = (ECsSave)ActionInfo->FileIndex;

	OnWrite_AsyncEvent.Broadcast(WasSuccessful, Save);
	OnWrite_AsyncScriptEvent.Broadcast(WasSuccessful, Save);
}

void UCsManager_Save::OnDeleteUserFileComplete(bool WasSuccessful, const FUniqueNetId& UserId, const FString& FileName)
{
	TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* AllocatedHead = Manager_MemoryResource.GetAllocatedHead();

	checkf(AllocatedHead, TEXT("UCsManager_Save::OnDeleteUserFileComplete: No Delete Action was queued."));

	FCsMemoryResource_SaveActionInfo* InfoContainer = **AllocatedHead;
	FCsSaveActionInfo* ActionInfo					= InfoContainer->Get();

	checkf(ActionInfo->Action == ECsSaveAction::Delete, TEXT("UCsManager_Save::OnDeleteUserFileComplete: Current Action: %s is NOT Delete."), *(EMCsSaveAction::Get().ToChar(ActionInfo->Action)));

	if (WasSuccessful)
	{
		ActionInfo->Success();

		// Do checks for SaveActionInfo
		TArray<FCsSaveFileInfo>& FileInfos = ActionInfo->IsAllProfiles() ? SaveFileInfosAll : SaveFileInfos;

		checkf(ActionInfo->FileIndex >= CS_EMPTY && ActionInfo->FileIndex < FileInfos.Num(), TEXT("UCsManager_Save::OnDeleteUserFileComplete: Invalid FileIndex: %d for SaveFileInfo."), ActionInfo->FileIndex);

		FCsSaveFileInfo& FileInfo = FileInfos[ActionInfo->FileIndex];

		checkf(FileInfo.FileNameWithExt == FileName, TEXT("UCsManager_Save::OnDeleteUserFileComplete: Mistach between FileNameWithExt: %s and FileName: %s."), *(FileInfo.FileNameWithExt), *FileName);

		FileInfo.bDelete	= true;
		FileInfo.DeleteTime = FDateTime::Now();
		FileInfo.bValid		= false;

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			if (ActionInfo->IsAllProfiles())
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnDeleteUserFileComplete: Finished Delete for File: %s for Player: %s at %s."), *FileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnDeleteUserFileComplete: Finished Delete for File: %s for Profile: %s for Player: %s at %s."), *FileName, *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
		}
#endif // #if !UE_BUILD_SHIPPING

		ActionInfo->Complete();
	}
	else
	{
		if (ActionInfo->IsAllProfiles())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnDeleteUserFileComplete: Failed to delete File: %s for Player: %s"), *FileName, *(UserId.ToString()));
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnDeleteUserFileComplete: Failed to delete File: %s for Profile: %s for Player: %s"), *FileName, *ProfileName, *(UserId.ToString()));
		}

		ActionInfo->Complete();
	}

	const ECsSave Save = (ECsSave)ActionInfo->FileIndex;

	OnDelete_AsyncEvent.Broadcast(WasSuccessful, Save);
	OnDelete_AsyncScriptEvent.Broadcast(WasSuccessful, Save);
}

#pragma endregion IOnlineUserCloud