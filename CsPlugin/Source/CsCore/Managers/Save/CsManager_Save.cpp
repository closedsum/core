// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Save/CsManager_Save.h"
#include "CsCore.h"
#include "CsCVars.h"

// Player
#include "Engine/LocalPlayer.h"
// Online
#include "Interfaces/OnlineIdentityInterface.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Save/CsGetManagerSave.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"
#endif // #if WITH_EDITOR

// static initializations
UCsManager_Save* UCsManager_Save::s_Instance;
bool UCsManager_Save::s_bShutdown = false;

UCsManager_Save::UCsManager_Save(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentSaveIndex = 0;
	CurrentSave = ECsSave::Save1;

	// Profile
	{
		const int32& Count = EMCsPlayerProfile::Get().Num();

		ProfileNames.Reserve(Count);

		for (const ECsPlayerProfile& Profile : EMCsPlayerProfile::Get())
		{
			ProfileNames.AddDefaulted();

			FString& Name = ProfileNames.Last();
			Name		  = EMCsPlayerProfile::Get().ToString(Profile);
		}
	}

	// FileName
	{
		const int32& ProfileCount = EMCsPlayerProfile::Get().Num();

		ProfileFileNamePrefixes.Reserve(ProfileCount);
		ProfileFileNamePrefixesWithUnderscore.Reserve(ProfileCount);

		for (const ECsPlayerProfile& Profile : EMCsPlayerProfile::Get())
		{
			ProfileFileNamePrefixes.AddDefaulted();

			FString& Name = ProfileFileNamePrefixes.Last();
			Name		  = EMCsPlayerProfile::Get().ToString(Profile);

			ProfileFileNamePrefixesWithUnderscore.AddDefaulted();

			FString& NameWithUnderscore = ProfileFileNamePrefixesWithUnderscore.Last();
			NameWithUnderscore			= Name + TEXT("_");
		}

		SaveFileNameExt = TEXT(".json");

		// SaveFileInfos
		{
			SaveFileInfos.Reserve(ProfileCount);

			const int32& SaveCount = EMCsSave::Get().Num();

			for (const ECsPlayerProfile& Profile : EMCsPlayerProfile::Get())
			{
				SaveFileInfos.AddDefaulted();

				TArray<FCsSaveFileInfo>& Infos = SaveFileInfos.Last();

				Infos.Reserve(SaveCount);

				for (const ECsSave& Save : EMCsSave::Get())
				{
					const FString& Name = EMCsSave::Get().ToString(Save);

					Infos.AddDefaulted();

					FCsSaveFileInfo& Info = Infos.Last();

					Info.FileName		 = ProfileFileNamePrefixesWithUnderscore[(uint8)Profile] + Name;
					Info.FileNameWithExt = ProfileFileNamePrefixesWithUnderscore[(uint8)Profile] + Name + SaveFileNameExt;
					Info.bValid			 = true;
				}
			}
			SaveFileInfosAll.Reserve(ProfileCount * SaveCount);
		}
	}
}

// Singleton
#pragma region

/*static*/ UCsManager_Save* UCsManager_Save::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerSave(InRoot)->GetManager_Save();
#else
	if (s_bShutdown)
		return nullptr;

	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Save::IsValid()
{
	return s_Instance != nullptr;
}

/*static*/ void UCsManager_Save::Init(UObject* InRoot, UClass* ManagerSaveClass)
{
#if WITH_EDITOR
	ICsGetManagerSave* GetManagerSave = Get_GetManagerSave(InRoot);

	UCsManager_Save* Manager_Save = GetManagerSave->GetManager_Save();

	if (!Manager_Save)
	{
		Manager_Save = NewObject<UCsManager_Save>(InRoot, ManagerSaveClass, TEXT("Manager_Save_Singleton"), RF_Transient | RF_Public);

		GetManagerSave->SetManager_Save(Manager_Save);

		Manager_Save->SetMyRoot(InRoot);
		Manager_Save->Initialize();
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Save>(GetTransientPackage(), ManagerSaveClass, TEXT("Manager_Save_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Save::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerSave* GetManagerSave = Get_GetManagerSave(InRoot);
	UCsManager_Save* Manager_Save	  = GetManagerSave->GetManager_Save();
	Manager_Save->CleanUp();

	GetManagerSave->SetManager_Save(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Save::HasShutdown()
{
	return s_bShutdown;
}

#if WITH_EDITOR

/*static*/ ICsGetManagerSave* UCsManager_Save::Get_GetManagerSave(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Save::Get_GetManagerSave: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Save::Get_GetManagerSave: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Save::Get_GetManagerSave: Manager_Singleton is NULL."));

	ICsGetManagerSave* GetManagerSave = Cast<ICsGetManagerSave>(Manager_Singleton);

	checkf(GetManagerSave, TEXT("UCsManager_Save::Get_GetManagerSave: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerSave."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerSave;
}

/*static*/ ICsGetManagerSave* UCsManager_Save::GetSafe_GetManagerSave(UObject* Object)
{
	if (!Object)
		return nullptr;

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
		return nullptr;

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
		return nullptr;

	return Cast<ICsGetManagerSave>(Manager_Singleton);
}

/*static*/ UCsManager_Save* UCsManager_Save::GetSafe(UObject* Object)
{
	if (ICsGetManagerSave* GetManagerSave = GetSafe_GetManagerSave(Object))
		return GetManagerSave->GetManager_Save();
	return nullptr;
}

/*static*/ UCsManager_Save* UCsManager_Save::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsManager_Save* Manager = GetSafe(World->GetGameInstance()))
			return Manager;
		// Game State
		if (UCsManager_Save* Manager = GetSafe(World->GetGameState()))
			return Manager;

		// Player Controller
		TArray<APlayerController*> Controllers;

		UCsLibrary_Common::GetAllLocalPlayerControllers(World, Controllers);

		if (Controllers.Num() == CS_EMPTY)
			return nullptr;

		for (APlayerController* Controller : Controllers)
		{
			if (UCsManager_Save* Manager = GetSafe(Controller))
				return Manager;
		}

		UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::GetFromWorldContextObject: Failed to Manager Save of type UCsManager_Save from GameInstance, GameState, or PlayerController."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_Save::Initialize()
{
}

void UCsManager_Save::CleanUp()
{
}

	// Root
#pragma region

void UCsManager_Save::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

void UCsManager_Save::Start()
{
	// Set the FileNames again. This could change depending on the Profile.
	for (const ECsPlayerProfile& Profile : EMCsPlayerProfile::Get())
	{
		for (const ECsSave& Save : EMCsSave::Get())
		{
			const FString& Name = EMCsSave::Get().ToString(Save);

			FCsSaveFileInfo& Info = SaveFileInfos[(uint8)Profile][(uint8)Save];

			Info.FileName		 = ProfileFileNamePrefixesWithUnderscore[(uint8)Profile] + Name;
			Info.FileNameWithExt = ProfileFileNamePrefixesWithUnderscore[(uint8)Profile] + Name + SaveFileNameExt;
		}
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

		for (TArray<FCsSaveFileInfo>& Infos : SaveFileInfos)
		{
			for (FCsSaveFileInfo& Info : Infos)
			{
				Info.bValid = false;
			}
		}
	}

	Enumerate();

	for (const ECsPlayerProfile& Profile : EMCsPlayerProfile::Get())
	{
		ReadAll(Profile);
	}
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

void UCsManager_Save::SetProfileName(const ECsPlayerProfile& Profile, const FString& Name)
{
	ProfileNames[(uint8)Profile] = Name;
}

#pragma endregion Profile

void UCsManager_Save::Update(const float& DeltaSeconds)
{
	TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* Current = Manager_MemoryResource.GetAllocatedHead();
	TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* Next    = Current;

	while (Next)
	{
		Current											= Next;
		FCsMemoryResource_SaveActionInfo* InfoContainer = **Current;
		Next											= Current->GetNextLink();

		FCsSaveActionInfo* Info = InfoContainer->Get();
		
		const ECsPlayerProfile& Profile = Info->Profile;
		const ECsSave Save				= (ECsSave)Info->FileIndex;
		const ECsSaveAction& Action		= Info->Action;

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
				SetSaveData(Profile, Save);

				OnRead_Event.Broadcast(WasSuccessful, Profile, Save);
				OnRead_ScriptEvent.Broadcast(WasSuccessful, Profile, Save);
			}
			// Read All
			else
			if (Action == ECsSaveAction::ReadAll)
			{
#if !UE_BUILD_SHIPPING
				if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
				{
					const FString& ProfileName = ProfileNames[(uint8)Profile];

					UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Update: Completed ReadAll for Profile: %s at %s."), *ProfileName, *(FDateTime::Now().ToString()));
				}
#endif // #if !UE_BUILD_SHIPPING

				OnReadAll_Event.Broadcast();
				OnReadAll_ScriptEvent.Broadcast();
			}
			// Write
			else
			if (Action == ECsSaveAction::Write)
			{
				OnWrite_Event.Broadcast(WasSuccessful, Profile, Save);
				OnWrite_ScriptEvent.Broadcast(WasSuccessful, Profile, Save);
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
				ClearSaveData(Profile, Info->FileIndex);

				OnDelete_Event.Broadcast(WasSuccessful, Profile, Save);
				OnDelete_ScriptEvent.Broadcast(WasSuccessful, Profile, Save);
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

void UCsManager_Save::SetProfileFileNamePrefix(const ECsPlayerProfile& Profile, const FString& Prefix)
{
	ProfileFileNamePrefixes[(uint8)Profile]				  = Prefix;
	ProfileFileNamePrefixesWithUnderscore[(uint8)Profile] = Prefix + TEXT("_");
}

void UCsManager_Save::SetSaveFileNameExt(const FString& Ext)
{
	SaveFileNameExt = Ext;
}

void UCsManager_Save::SetSaveFileName(const ECsPlayerProfile& Profile, const ECsSave& Save, const FString& FileName)
{
	// TODO: Need to Delete file if it already exists and then Write new file.
	FCsSaveFileInfo& Info = SaveFileInfos[(uint8)Profile][(uint8)Save];

	Info.FileName		 = FileName;
	Info.FileNameWithExt = FileName + SaveFileNameExt;
}

const FString& UCsManager_Save::GetSaveFileName(const ECsPlayerProfile& Profile, const ECsSave& Save)
{
	return SaveFileInfos[(uint8)Profile][(uint8)Save].FileName;
}

const FCsSaveFileInfo& UCsManager_Save::GetSaveFileInfo(const ECsPlayerProfile& Profile, const ECsSave& Save)
{
	return SaveFileInfos[(uint8)Profile][(uint8)Save];
}

void UCsManager_Save::SetCurrentSaveIndex(const int32& Index)
{
	CurrentSaveIndex = Index;
}

void UCsManager_Save::SetCurrentSave(const ECsSave& Save)
{
	CurrentSave = Save;
}

#pragma endregion FileName

// Data
#pragma region

void UCsManager_Save::SetSaveDataTest(const ECsPlayerProfile& Profile, const ECsSave& Save, const FString& InData)
{

}

void UCsManager_Save::SetSaveData(const ECsPlayerProfile& Profile, const ECsSave& Save)
{
	SetSaveData(Profile, (int32)Save);
}

void UCsManager_Save::SetSaveData(const ECsPlayerProfile& Profile, const int32& Index)
{

}

void UCsManager_Save::GetSaveData(const ECsPlayerProfile& Profile, const ECsSave& Save, FString& OutData)
{
	GetSaveData(Profile, (int32)Save, OutData);
}

void UCsManager_Save::GetSaveData(const ECsPlayerProfile& Profile, const int32& Index, FString& OutData)
{
}

void UCsManager_Save::ClearSaveData(const ECsPlayerProfile& Profile, const ECsSave& Save)
{
	ClearSaveData(Profile, (int32)Save);
}

void UCsManager_Save::ClearSaveData(const ECsPlayerProfile& Profile, const int32& Index)
{

}

#pragma endregion Data

// Action
#pragma region

void UCsManager_Save::QueueAction(const ECsPlayerProfile& Profile, const ECsSaveAction& Action, const ECsSave& Save, const FString& Data /*= NCsCached::Str::Empty*/)
{
	QueueAction(Profile, Action, (int32)Save, Data);
}

void UCsManager_Save::QueueAction(const ECsPlayerProfile& Profile, const ECsSaveAction& Action, const int32& Index, const FString& Data /*= NCsCached::Str::Empty*/)
{
	// Allocate SaveActionInfo from a pool
	FCsMemoryResource_SaveActionInfo* InfoContainer = Manager_MemoryResource.Allocate();
	FCsSaveActionInfo* Info							= InfoContainer->Get();

	Info->Reset();

	Info->Action    = Action;
	Info->FileIndex = Index;
	Info->Profile   = Profile;
	Info->Data		= Data;
}

void UCsManager_Save::QueueAction(const ECsPlayerProfile& Profile, const ECsSaveAction& Action)
{
	QueueAction(Profile, Action, INDEX_NONE);
}

void UCsManager_Save::QueueActionAsHead(const ECsPlayerProfile& Profile, const ECsSaveAction& Action, const int32& Index)
{
	FCsMemoryResource_SaveActionInfo* InfoContainer = Manager_MemoryResource.AllocateBeforeHead();
	FCsSaveActionInfo* Info							= InfoContainer->Get();

	Info->Reset();

	Info->Action	= Action;
	Info->FileIndex = Index;
	Info->Profile   = Profile;
}

void UCsManager_Save::QueueActionAsHead(const ECsPlayerProfile& Profile, const ECsSaveAction& Action)
{
	QueueActionAsHead(Profile, Action, INDEX_NONE);
}

void UCsManager_Save::QueueActionAfterHead(const ECsPlayerProfile& Profile, const ECsSaveAction& Action, const int32& Index)
{
	FCsMemoryResource_SaveActionInfo* InfoContainer = Manager_MemoryResource.AllocateAfterHead();
	FCsSaveActionInfo* Info							= InfoContainer->Get();

	Info->Reset();

	Info->Action    = Action;
	Info->FileIndex = Index;
	Info->Profile	= Profile;
}

void UCsManager_Save::QueueActionAfterHead(const ECsPlayerProfile& Profile, const ECsSaveAction& Action)
{
	QueueActionAfterHead(Profile, Action, INDEX_NONE);
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

			EnumerateUserFilesState.Queue();
			QueueAction(NCsPlayerProfile::AllProfiles, ECsSaveAction::Enumerate);
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

void UCsManager_Save::Read(const ECsPlayerProfile& Profile, const ECsSave& Save)
{
	Read(Profile, (int32)Save);
}

void UCsManager_Save::Read(const ECsPlayerProfile& Profile, const int32& Index)
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
			QueueAction(NCsPlayerProfile::AllProfiles, ECsSaveAction::Enumerate);
		}

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			const FString& FileNameWithExt = SaveFileInfos[(uint8)Profile][Index].FileNameWithExt;
			const FString& ProfileName	   = ProfileNames[(uint8)Profile];

			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Read: Queueing Read for File: %s for Profile: %s for Player: %s at %s."), *FileNameWithExt, *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(Profile, ECsSaveAction::Read, Index);
	}
}

void UCsManager_Save::Read_Internal(FCsSaveActionInfo* ActionInfo)
{
	ECsPlayerProfile& Profile = ActionInfo->Profile;
	FCsSaveFileInfo& FileInfo = SaveFileInfos[(uint8)Profile][ActionInfo->FileIndex];
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
				const FString& ProfileName = ProfileNames[(uint8)Profile];

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

void UCsManager_Save::ReadAll(const ECsPlayerProfile& Profile)
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
			QueueAction(NCsPlayerProfile::AllProfiles, ECsSaveAction::Enumerate);
		}

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			// All Profiles
			if (Profile == NCsPlayerProfile::AllProfiles)
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::ReadAll: Queueing ReadAll for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
			else
			{
				const FString& ProfileName = ProfileNames[(uint8)Profile];

				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::ReadAll: Queueing ReadAll for Profile: %s for Player: %s at %s."), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(Profile, ECsSaveAction::ReadAll);
	}
	// Local
	else
	{

	}
}

void UCsManager_Save::ReadAll_Internal(FCsSaveActionInfo* ActionInfo)
{
	const ECsPlayerProfile& Profile = ActionInfo->Profile;

	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			if (Profile == NCsPlayerProfile::AllProfiles)
			{
			}
			else
			{
				const FString& ProfileName = ProfileNames[(uint8)Profile];

				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::ReadAll_Internal: Starting ReadAll for Profile: %s for Player: %s at %s."), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
		}
#endif // #if !UE_BUILD_SHIPPING

		TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* Current = Manager_MemoryResource.GetAllocatedHead();
		FCsMemoryResource_SaveActionInfo* InfoContainer					= **Current;
		FCsSaveActionInfo* ReadAllActionInfo							= InfoContainer->Get();

		// Queue Read for all Files
		if (EnumerateUserFilesState.bSuccess)
		{
			for (const ECsPlayerProfile& PlayerProfile : EMCsPlayerProfile::Get())
			{
				if (Profile != NCsPlayerProfile::AllProfiles &&
					Profile != PlayerProfile)
				{
					continue;
				}

				TArray<FCsSaveFileInfo>& Infos = SaveFileInfos[(uint8)PlayerProfile];

				const int32 Count = Infos.Num();

				for (int32 I = 0; I < Count; ++I) 
				{
					FCsSaveFileInfo& FileInfo = Infos[I];

					if (FileInfo.bValid)
					{
						FileInfo.bRead = false;

						FCsMemoryResource_SaveActionInfo* ReadInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
						FCsSaveActionInfo* ReadInfo						    = ReadInfoContainer->Get();

						ReadInfo->Reset();

						ReadInfo->Profile   = PlayerProfile;
						ReadInfo->Action    = ECsSaveAction::Read;
						ReadInfo->FileIndex = I;

						// Update InfoContainer so actions get queued in order
						InfoContainer = ReadInfoContainer;

		#if !UE_BUILD_SHIPPING
						if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
						{
							const FString& ProfileName = ProfileNames[(uint8)PlayerProfile];

							UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::ReadAll_Internal: Queueing Read for File: %s for Profile: %s for Player: %s at %s."), *(FileInfo.FileNameWithExt), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
						}
		#endif // #if !UE_BUILD_SHIPPING
					}
				}
			}

			// Queue Read All event at end
			FCsMemoryResource_SaveActionInfo* ReadAllInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
			FCsSaveActionInfo* ReadAllInfo						   = ReadAllInfoContainer->Get();

			ReadAllInfo->Reset();

			ReadAllInfo->Profile = Profile;
			ReadAllInfo->Action  = ECsSaveAction::ReadAll;
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

void UCsManager_Save::Write(const ECsPlayerProfile& Profile, const ECsSave& Save)
{
	Write(Profile, (int32)Save);
}

void UCsManager_Save::Write(const ECsPlayerProfile& Profile, const int32& Index)
{
	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			const FString& FileNameWithExt = SaveFileInfos[(uint8)Profile][Index].FileNameWithExt;
			const FString& ProfileName	   = ProfileNames[(uint8)Profile];

			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Write: Queueing Write for File: %s for Profile: %s for Player: %s at %s."), *FileNameWithExt, *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		FString Data;
		GetSaveData(Profile, Index, Data);

		QueueAction(Profile, ECsSaveAction::Write, Index, Data);
	}
	// Local
	else
	{

	}
}

void UCsManager_Save::Write_Internal(FCsSaveActionInfo* ActionInfo)
{
	const ECsPlayerProfile& Profile = ActionInfo->Profile;
	const int32& FileIndex			= ActionInfo->FileIndex;
	FCsSaveFileInfo& FileInfo		= SaveFileInfos[(uint8)Profile][FileIndex];
	FileInfo.bWrite					= false;
	FileInfo.WriteContents			= ActionInfo->Data;

	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Write then Enumerate

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			const FString& ProfileName = ProfileNames[(uint8)Profile];

			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Write_Internal: Starting Write for File: %s for Profile: %s for Player: %s at %s."), *(FileInfo.FileNameWithExt), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));

			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Write_Internal: Contents:"));

			UE_LOG(LogCs, Warning, TEXT("%s"), *(FileInfo.WriteContents));

			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Write_Internal: Queueing Enumerate after Write for Profile: %s for Player: %s at %s."), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueActionAfterHead(NCsPlayerProfile::AllProfiles, ECsSaveAction::Enumerate);

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

void UCsManager_Save::WriteAll(const ECsPlayerProfile& Profile)
{
	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			// All Profiles
			if (Profile == NCsPlayerProfile::AllProfiles)
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::WriteAll: Queueing WriteAll for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
			else
			{
				const FString& ProfileName = ProfileNames[(uint8)Profile];

				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::WriteAll: Queueing WriteAll for Profile: %s for Player: %s at %s."), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(Profile, ECsSaveAction::WriteAll);
	}
	// Local
	else
	{

	}
}

void UCsManager_Save::WriteAll_Internal(FCsSaveActionInfo* ActionInfo)
{
	const ECsPlayerProfile& Profile = ActionInfo->Profile;

	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Queue Write for all Files

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			// All Profiles
			if (Profile == NCsPlayerProfile::AllProfiles)
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::WriteAll_Internal: Starting WriteAll for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
			else
			{
				const FString& ProfileName = ProfileNames[(uint8)Profile];

				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::WriteAll_Internal: Starting WriteAll for Profile: %s for Player: %s at %s."), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
		}
#endif // #if !UE_BUILD_SHIPPING

		TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* Current = Manager_MemoryResource.GetAllocatedHead();
		FCsMemoryResource_SaveActionInfo* InfoContainer					= **Current;

		for (const ECsPlayerProfile& PlayerProfile : EMCsPlayerProfile::Get())
		{
			if (Profile != NCsPlayerProfile::AllProfiles &&
				Profile != PlayerProfile)
			{
				continue;
			}

			const int32 Count = SaveFileInfos.Num();

			for (int32 I = 0; I < Count; ++I) 
			{
				FCsSaveFileInfo& FileInfo = SaveFileInfos[(uint8)PlayerProfile][I];

				FCsMemoryResource_SaveActionInfo* WriteInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
				FCsSaveActionInfo* WriteInfo						 = WriteInfoContainer->Get();

				WriteInfo->Reset();

				WriteInfo->Profile	   = PlayerProfile;
				WriteInfo->Action      = ECsSaveAction::Write;
				WriteInfo->FileIndex   = I;

				// Update InfoContainer so actions get queued in order
				InfoContainer = WriteInfoContainer;

	#if !UE_BUILD_SHIPPING
				if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
				{
					const FString& ProfileName = ProfileNames[(uint8)PlayerProfile];

					UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::WriteAll_Internal: Queueing Write for File: %s for Profile: %s for Player: %s at %s."), *(FileInfo.FileNameWithExt), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
				}
	#endif // #if !UE_BUILD_SHIPPING
			}
		}

		// Queue Write All event at end
		FCsMemoryResource_SaveActionInfo* WriteAllInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
		FCsSaveActionInfo* WriteAllInfo							= WriteAllInfoContainer->Get();

		WriteAllInfo->Reset();

		WriteAllInfo->Profile = Profile;
		WriteAllInfo->Action  = ECsSaveAction::WriteAll;
		WriteAllInfo->Complete();

		InfoContainer = WriteAllInfoContainer;

		// Queue Enumerate
		FCsMemoryResource_SaveActionInfo* EnumerateInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
		FCsSaveActionInfo* EnumerateInfo						 = EnumerateInfoContainer->Get();

		EnumerateInfo->Reset();

		EnumerateInfo->Profile = NCsPlayerProfile::AllProfiles;
		EnumerateInfo->Action  = ECsSaveAction::Enumerate;

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

void UCsManager_Save::Delete(const ECsPlayerProfile& Profile, const ECsSave& Save)
{
	Delete(Profile, (int32)Save);
}

void UCsManager_Save::Delete(const ECsPlayerProfile& Profile, const int32& Index)
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
			QueueAction(NCsPlayerProfile::AllProfiles, ECsSaveAction::Enumerate);
		}

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			// All Profiles
			if (Profile == NCsPlayerProfile::AllProfiles)
			{
				const FString& FileNameWithExt = SaveFileInfosAll[Index].FileNameWithExt;

				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Delete: Queueing Delete for File: %s for Player: %s at %s."), *FileNameWithExt, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
			else
			{
				const FString& FileNameWithExt = SaveFileInfos[(uint8)Profile][Index].FileNameWithExt;
				const FString& ProfileName	   = ProfileNames[(uint8)Profile];

				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::Delete: Queueing Delete for File: %s for Profile: %s for Player: %s at %s."), *FileNameWithExt, *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(Profile, ECsSaveAction::Delete, Index);
	}
	// Local
	else
	{

	}
}

void UCsManager_Save::Delete_Internal(FCsSaveActionInfo* ActionInfo)
{
	const ECsPlayerProfile& Profile = ActionInfo->Profile;
	const int32& Index				= ActionInfo->FileIndex;
	FCsSaveFileInfo& FileInfo		= ActionInfo->IsAllProfiles() ? SaveFileInfosAll[Index] : SaveFileInfos[(uint8)Profile][Index];
	FileInfo.bDelete				= false;

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

					EnumerateInfo->Profile = NCsPlayerProfile::AllProfiles;
					EnumerateInfo->Action  = ECsSaveAction::Enumerate;

					InfoContainer = EnumerateInfoContainer;
				}
				// ReadAll
				{
					FCsMemoryResource_SaveActionInfo* ReadAllInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
					FCsSaveActionInfo* ReadAllInfo						   = ReadAllInfoContainer->Get();

					ReadAllInfo->Reset();

					ReadAllInfo->Profile = Profile;
					ReadAllInfo->Action  = ECsSaveAction::ReadAll;
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

void UCsManager_Save::DeleteAll(const ECsPlayerProfile& Profile)
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
			QueueAction(NCsPlayerProfile::AllProfiles, ECsSaveAction::Enumerate);
		}

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			// All Profiles
			if (Profile == NCsPlayerProfile::AllProfiles)
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::DeleteAll: Queueing DeleteAll for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
			else
			{
				const FString& ProfileName = ProfileNames[(uint8)Profile];

				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::DeleteAll: Queueing DeleteAll for Profile: %s for Player: %s at %s."), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(Profile, ECsSaveAction::DeleteAll);
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
			QueueAction(NCsPlayerProfile::AllProfiles, ECsSaveAction::Enumerate);
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
	const ECsPlayerProfile& Profile = ActionInfo->Profile;

	IOnlineUserCloudPtr IUserCloud = GetUserCloudInterface();
	// Online
	if (IUserCloud.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Queue Delete for all Files

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
		{
			// All Profiles
			if (ActionInfo->IsAllProfiles())
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::DeleteAll_Internal: Starting DeleteAll for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
			else
			{
				const FString& ProfileName = ProfileNames[(uint8)Profile];

				UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::DeleteAll_Internal: Starting DeleteAll for ProfileName: %s for Player: %s at %s."), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
		}
#endif // #if !UE_BUILD_SHIPPING

		TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* Current = Manager_MemoryResource.GetAllocatedHead();
		FCsMemoryResource_SaveActionInfo* InfoContainer					= **Current;

		// All Content
		if (ActionInfo->IsAllProfiles())
		{
			const int32 Count = SaveFileInfosAll.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				FCsSaveFileInfo& FileInfo = SaveFileInfosAll[I];

				if (FileInfo.bValid)
				{
					FileInfo.bRead = false;

					FCsMemoryResource_SaveActionInfo* DeleteInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
					FCsSaveActionInfo* DeleteInfo						  = DeleteInfoContainer->Get();

					DeleteInfo->Reset();

					DeleteInfo->Profile		= Profile;
					DeleteInfo->Action      = ECsSaveAction::Delete;
					DeleteInfo->FileIndex   = I;

					// Update InfoContainer so actions get queued in order
					InfoContainer = DeleteInfoContainer;

	#if !UE_BUILD_SHIPPING
					if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
					{
						UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::DeleteAll_Internal: Queueing Delete for File: %s for Player: %s at %s."), *(FileInfo.FileNameWithExt), *(UserId.ToString()), *(FDateTime::Now().ToString()));
					}
	#endif // #if !UE_BUILD_SHIPPING
				}
			}
		}
		else
		{
			TArray<FCsSaveFileInfo>& Infos = SaveFileInfos[(uint8)Profile];

			const int32 Count = Infos.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				FCsSaveFileInfo& FileInfo = Infos[I];

				if (FileInfo.bValid)
				{
					FileInfo.bRead = false;

					FCsMemoryResource_SaveActionInfo* DeleteInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
					FCsSaveActionInfo* DeleteInfo						  = DeleteInfoContainer->Get();

					DeleteInfo->Reset();

					DeleteInfo->Profile   = Profile;
					DeleteInfo->Action    = ECsSaveAction::Delete;
					DeleteInfo->FileIndex = I;

					// Update InfoContainer so actions get queued in order
					InfoContainer = DeleteInfoContainer;

#if !UE_BUILD_SHIPPING
					if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
					{
						const FString& ProfileName = ProfileNames[(uint8)Profile];

						UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::DeleteAll_Internal: Queueing Delete for File: %s for Profile: %s for Player: %s at %s."), *(FileInfo.FileNameWithExt), *ProfileName, *(UserId.ToString()), *(FDateTime::Now().ToString()));
					}
#endif // #if !UE_BUILD_SHIPPING
				}
			}
		}
		
		// Queue Delete All at end
		FCsMemoryResource_SaveActionInfo* DeleteAllInfoContainer = Manager_MemoryResource.AllocateAfter(InfoContainer);
		FCsSaveActionInfo* DeleteAllInfo						 = DeleteAllInfoContainer->Get();

		DeleteAllInfo->Reset();

		DeleteAllInfo->Profile = Profile;
		DeleteAllInfo->Action  = ECsSaveAction::DeleteAll;
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

		for (TArray<FCsSaveFileInfo>& Infos : SaveFileInfos)
		{
			for (FCsSaveFileInfo& Info : Infos)
			{
				Info.bValid = false;
			}
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

			// Check all Profiles
			for (const ECsPlayerProfile& Profile : EMCsPlayerProfile::Get())
			{
				// Check Prefix (for the Profile the save is associated with)
				bool bMatchesPrefix = DLName.StartsWith(ProfileFileNamePrefixes[(uint8)Profile]);

				// This Profile
				if (bMatchesPrefix)
				{
					// Determine the Save
					FString SaveAsString = FileName;
				
					SaveAsString.RemoveFromStart(ProfileFileNamePrefixesWithUnderscore[(uint8)Profile]);

					const FName SaveAsName = FName(*SaveAsString);
				
					if (EMCsSave::Get().IsValidEnum(SaveAsName))
					{
						const ECsSave& Save = EMCsSave::Get().GetEnum(SaveAsName);
						const int32 Index   = (int32)Save;

						FCsSaveFileInfo& Info = SaveFileInfos[(uint8)Profile][Index];

						Info.FileNameWithExt = FileNameWithExt;
						Info.FileName		 = FileName;
						Info.bValid			 = true;

	#if !UE_BUILD_SHIPPING
						if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerSaveTransactions))
						{
							const FString& ProfileName = ProfileNames[(uint8)Profile];

							UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnEnumerateUserFilesComplete: %d. Profile: %s. Save: %s. %s."), Index, *ProfileName, *SaveAsString, *(Header.DLName));
						}
	#endif // #if !UE_BUILD_SHIPPING
					}
					else
					{
						UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnEnumerateUserFilesComplete: Save Type: %s is NOT Valid for %s."), *SaveAsString, *(Header.DLName));
					}
					continue;
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
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnEnumerateUserFilesComplete: Failed for Player: %s"), *(UserId.ToString()));

		ActionInfo->Complete();
	}

	EnumerateUserFilesState.bSuccess = WasSuccessful;
	EnumerateUserFilesState.Complete();

	OnEnumerate_AsyncEvent.Broadcast(WasSuccessful);
	OnEnumerate_AsyncScriptEvent.Broadcast(WasSuccessful);
}

void UCsManager_Save::OnReadUserFileComplete(bool WasSuccessful, const FUniqueNetId& UserId, const FString& FileName)
{
	TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* AllocatedHead = Manager_MemoryResource.GetAllocatedHead();

	checkf(AllocatedHead, TEXT("UCsManager_Save::OnReadUserFileComplete: No Read Action was queued."));

	FCsMemoryResource_SaveActionInfo* InfoContainer = **AllocatedHead;
	FCsSaveActionInfo* ActionInfo					= InfoContainer->Get();

	checkf(ActionInfo->Action == ECsSaveAction::Read, TEXT("UCsManager_Save::OnReadUserFileComplete: Current Action: %s is NOT Read."), *(EMCsSaveAction::Get().ToChar(ActionInfo->Action)));

	const ECsPlayerProfile& Profile = ActionInfo->Profile;
	const FString& ProfileName		= ProfileNames[(uint8)Profile];

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

		FCsSaveFileInfo& FileInfo = SaveFileInfos[(uint8)Profile][ActionInfo->FileIndex];

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

	OnRead_AsyncEvent.Broadcast(WasSuccessful, Profile, Save);
	OnRead_AsyncScriptEvent.Broadcast(WasSuccessful, Profile, Save);
}

void UCsManager_Save::OnWriteUserFileComplete(bool WasSuccessful, const FUniqueNetId& UserId, const FString& FileName)
{
	TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* AllocatedHead = Manager_MemoryResource.GetAllocatedHead();

	checkf(AllocatedHead, TEXT("UCsManager_Save::OnWriteUserFileComplete: No Write Action was queued."));

	FCsMemoryResource_SaveActionInfo* InfoContainer = **AllocatedHead;
	FCsSaveActionInfo* ActionInfo					= InfoContainer->Get();

	checkf(ActionInfo->Action == ECsSaveAction::Write, TEXT("UCsManager_Save::OnWriteUserFileComplete: Current Action: %s is NOT Write."), *(EMCsSaveAction::Get().ToChar(ActionInfo->Action)));

	const ECsPlayerProfile& Profile = ActionInfo->Profile;
	const FString& ProfileName		= ProfileNames[(uint8)Profile];

	if (WasSuccessful)
	{
		ActionInfo->Success();

		// Do checks for SaveActionInfo
		checkf(ActionInfo->FileIndex >= CS_EMPTY && ActionInfo->FileIndex < SaveFileInfos.Num(), TEXT("UCsManager_Save::OnWriteUserFileComplete: Invalid FileIndex: %d for SaveFileInfo."), ActionInfo->FileIndex);

		FCsSaveFileInfo& FileInfo = SaveFileInfos[(uint8)Profile][ActionInfo->FileIndex];

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

	OnWrite_AsyncEvent.Broadcast(WasSuccessful, Profile, Save);
	OnWrite_AsyncScriptEvent.Broadcast(WasSuccessful, Profile, Save);
}

void UCsManager_Save::OnDeleteUserFileComplete(bool WasSuccessful, const FUniqueNetId& UserId, const FString& FileName)
{
	TCsDoubleLinkedList<FCsMemoryResource_SaveActionInfo*>* AllocatedHead = Manager_MemoryResource.GetAllocatedHead();

	checkf(AllocatedHead, TEXT("UCsManager_Save::OnDeleteUserFileComplete: No Delete Action was queued."));

	FCsMemoryResource_SaveActionInfo* InfoContainer = **AllocatedHead;
	FCsSaveActionInfo* ActionInfo					= InfoContainer->Get();

	checkf(ActionInfo->Action == ECsSaveAction::Delete, TEXT("UCsManager_Save::OnDeleteUserFileComplete: Current Action: %s is NOT Delete."), *(EMCsSaveAction::Get().ToChar(ActionInfo->Action)));

	const ECsPlayerProfile& Profile = ActionInfo->Profile;

	if (WasSuccessful)
	{
		ActionInfo->Success();

		// Do checks for SaveActionInfo
		TArray<FCsSaveFileInfo>& FileInfos = ActionInfo->IsAllProfiles() ? SaveFileInfosAll : SaveFileInfos[(uint8)Profile];

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
				const FString& ProfileName = ProfileNames[(uint8)Profile];

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
			const FString& ProfileName = ProfileNames[(uint8)Profile];

			UE_LOG(LogCs, Warning, TEXT("UCsManager_Save::OnDeleteUserFileComplete: Failed to delete File: %s for Profile: %s for Player: %s"), *FileName, *ProfileName, *(UserId.ToString()));
		}

		ActionInfo->Complete();
	}

	const ECsSave Save = (ECsSave)ActionInfo->FileIndex;

	OnDelete_AsyncEvent.Broadcast(WasSuccessful, Profile, Save);
	OnDelete_AsyncScriptEvent.Broadcast(WasSuccessful, Profile, Save);
}

#pragma endregion IOnlineUserCloud