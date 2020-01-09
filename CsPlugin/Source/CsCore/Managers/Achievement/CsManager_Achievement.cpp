// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Achievement/CsManager_Achievement.h"
#include "CsCore.h"
#include "CsCVars.h"

// Player
#include "Engine/LocalPlayer.h"
// Online
#include "Interfaces/OnlineIdentityInterface.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Achievement/CsGetManagerAchievement.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"
#endif // #if WITH_EDITOR

// static initializations
UCsManager_Achievement* UCsManager_Achievement::s_Instance;
bool UCsManager_Achievement::s_bShutdown = false;

UCsManager_Achievement::UCsManager_Achievement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Write
	WriteObject = nullptr;
	// Progress
	bOnlyForwardProgress = true;
	// IOnlineAchievements
	AchievementQueryOrder = ECsAchievementQueryOrder::IdsFirst;
}

// Singleton
#pragma region

/*static*/ UCsManager_Achievement* UCsManager_Achievement::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerAchievement(InRoot)->GetManager_Achievement();
#else
	if (s_bShutdown)
		return nullptr;

	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Achievement::IsValid()
{
	return s_Instance != nullptr;
}

/*static*/ void UCsManager_Achievement::Init(UObject* InRoot, UClass* ManagerAchievementClass)
{
#if WITH_EDITOR
	ICsGetManagerAchievement* GetManagerAchievement = Get_GetManagerAchievement(InRoot);

	UCsManager_Achievement* Manager_Achievement = GetManagerAchievement->GetManager_Achievement();

	if (!Manager_Achievement)
	{
		Manager_Achievement = NewObject<UCsManager_Achievement>(InRoot, ManagerAchievementClass, TEXT("Manager_Achievement_Singleton"), RF_Transient | RF_Public);

		GetManagerAchievement->SetManager_Achievement(Manager_Achievement);

		Manager_Achievement->SetMyRoot(InRoot);
		Manager_Achievement->Initialize();
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Achievement>(GetTransientPackage(), ManagerAchievementClass, TEXT("Manager_Achievement_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Achievement::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerAchievement* GetManagerAchievement = Get_GetManagerAchievement(InRoot);
	UCsManager_Achievement* Manager_Achievement		= GetManagerAchievement->GetManager_Achievement();
	Manager_Achievement->CleanUp();

	GetManagerAchievement->SetManager_Achievement(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Achievement::HasShutdown()
{
	return s_bShutdown;
}

#if WITH_EDITOR

/*static*/ ICsGetManagerAchievement* UCsManager_Achievement::Get_GetManagerAchievement(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Achievement::Get_GetManagerAchievement: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Achievement::Get_GetManagerAchievement: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Achievement::Get_GetManagerAchievement: Manager_Singleton is NULL."));

	ICsGetManagerAchievement* GetManagerAchievement = Cast<ICsGetManagerAchievement>(Manager_Singleton);

	checkf(GetManagerAchievement, TEXT("UCsManager_Achievement::Get_GetManagerAchievement: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerAchievement."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerAchievement;
}

/*static*/ ICsGetManagerAchievement* UCsManager_Achievement::GetSafe_GetManagerAchievement(UObject* Object)
{
	if (!Object)
		return nullptr;

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
		return nullptr;

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
		return nullptr;

	return Cast<ICsGetManagerAchievement>(Manager_Singleton);
}

/*static*/ UCsManager_Achievement* UCsManager_Achievement::GetSafe(UObject* Object)
{
	if (ICsGetManagerAchievement* GetManagerAchievement = GetSafe_GetManagerAchievement(Object))
		return GetManagerAchievement->GetManager_Achievement();
	return nullptr;
}

/*static*/ UCsManager_Achievement* UCsManager_Achievement::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsManager_Achievement* Manager = GetSafe(World->GetGameInstance()))
			return Manager;
		// Game State
		if (UCsManager_Achievement* Manager = GetSafe(World->GetGameState()))
			return Manager;

		// Player Controller
		TArray<APlayerController*> Controllers;

		//UCsLibrary_Common::GetAllLocalPlayerControllers(World, Controllers);

		if (Controllers.Num() == CS_EMPTY)
			return nullptr;

		for (APlayerController* Controller : Controllers)
		{
			if (UCsManager_Achievement* Manager = GetSafe(Controller))
				return Manager;
		}

		UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::GetFromWorldContextObject: Failed to Manager Achievement of type UCsManager_Achievement from GameInstance, GameState, or PlayerController."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_Achievement::Initialize()
{
	const int32& Count = EMCsAchievement::Get().Num();

	Achievements.Reserve(Count);

	for (const FECsAchievement& Enum : EMCsAchievement::Get())
	{
		Achievements.Add(ConstructAchievement());
		ICsAchievement* A = Achievements.Last();
		SetId(A, Enum.Name);
		SetType(A, Enum);
		A->SetProgressType(ECsAchievementProgress::Standard);
	}

	for (const FECsAchievement& Enum : EMCsAchievement::Get())
	{
		AchievementMap.Add(Enum.Name, Achievements[Enum.Value]);
	}

	AchievementsToWrite.Reserve(Count);

	Local_OutAchievements.Reserve(Count);
}

void UCsManager_Achievement::CleanUp()
{
	const int32& Count = Achievements.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		ICsAchievement* A = Achievements[I];
		delete A;
		Achievements[I] = nullptr;
	}
	Achievements.Reset();
}

	// Root
#pragma region

void UCsManager_Achievement::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

void UCsManager_Achievement::Start()
{
	// Read Achievements
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
		// Online
	if (IAchievements.IsValid())
	{
		// Set Achievements as NOT Valid until the Achievements have been queried
		for (ICsAchievement* A : Achievements)
		{
			A->SetInvalid();
		}

		// Ids First
		if (AchievementQueryOrder == ECsAchievementQueryOrder::IdsFirst)
		{
			QueryIds();
			QueryDescriptions();
		}
		// Descriptions First
		else
		if (AchievementQueryOrder == ECsAchievementQueryOrder::DescriptionsFirst)
		{
			QueryDescriptions();
			QueryIds();
		}
		UpdateDescriptions();
	}
		// Local
	else
	{

	}
}

ICsAchievement* UCsManager_Achievement::ConstructAchievement()
{
	return new FCsAchievement();
}

// Player
#pragma region

void UCsManager_Achievement::SetLocalPlayer(ULocalPlayer* Player)
{
	LocalPlayer = Player;
}

TSharedPtr<const FUniqueNetId> UCsManager_Achievement::GetLocalPlayerId()
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();
	return Identity->GetUniquePlayerId(LocalPlayer->GetControllerId());
}

const FUniqueNetId& UCsManager_Achievement::GetLocalPlayerIdRef()
{
	return *GetLocalPlayerId();
}

#pragma endregion Player

void UCsManager_Achievement::Update(const float& DeltaSeconds)
{
	TCsDoubleLinkedList<FCsResourceContainer_AchievementActionInfo*>* Current = Manager_Resource.GetAllocatedHead();
	TCsDoubleLinkedList<FCsResourceContainer_AchievementActionInfo*>* Next    = Current;

	while (Next)
	{
		Current													  = Next;
		FCsResourceContainer_AchievementActionInfo* InfoContainer = **Current;
		Next													  = Current->GetNextLink();

		FCsAchievementActionInfo* Info = InfoContainer->Get();
		
		const FECsAchievement& Achievement = Info->Achievement;
		const ECsAchievementAction& Action = Info->Action;
		const float& Percent			   = Info->Percent;


		// If In Progress, wait for Complete
		if (Info->InProgress())
			break;
		// If Complete, handle completion (fire any events) and move onto next Action
		if (Info->IsComplete())
		{
			const bool WasSuccessful = Info->WasSuccessful();

			ICsAchievement* IA = Achievement != EMCsAchievement::Get().GetMAX() ? Achievements[Achievement.Value] : nullptr;

			const float Progress = IA ? IA->CalculateProgress(Percent) : 0.0f;

			// Query Ids
			if (Action == ECsAchievementAction::QueryIds)
			{
				OnQueryIds_Event.Broadcast(WasSuccessful);
				OnQueryIds_ScriptEvent.Broadcast(WasSuccessful);
			}
			// Query Descriptions
			else
			if (Action == ECsAchievementAction::QueryDescriptions)
			{
				OnQueryDescriptions_Event.Broadcast(WasSuccessful);
				OnQueryDescriptions_ScriptEvent.Broadcast(WasSuccessful);
			}
			// Write
			else
			if (Action == ECsAchievementAction::Write)
			{
				OnProgress_Event.Broadcast(WasSuccessful, IA, Progress);
				OnProgress_ScriptEvent.Broadcast(WasSuccessful, Achievement, Progress);
			}
			// Complete
			else
			if (Action == ECsAchievementAction::Complete)
			{
				OnComplete_Event.Broadcast(WasSuccessful, IA);
				OnComplete_ScriptEvent.Broadcast(WasSuccessful, Achievement);
			}
			// Complete All
			else
			if (Action == ECsAchievementAction::CompleteAll)
			{
				OnCompleteAll_Event.Broadcast();
				OnCompleteAll_ScriptEvent.Broadcast();
			}
			// Reset
			else
			if (Action == ECsAchievementAction::Reset)
			{
				OnReset_Event.Broadcast(WasSuccessful, IA, Progress);
				OnReset_ScriptEvent.Broadcast(WasSuccessful, Achievement, Progress);
			}
			// Reset All
			else
			if (Action == ECsAchievementAction::ResetAll)
			{
				OnResetAll_Event.Broadcast();
				OnResetAll_ScriptEvent.Broadcast();
			}
			Manager_Resource.Deallocate(InfoContainer);
			continue;
		}
		// If Ready to Process, Start
		if (Info->IsReadyToProcess())
		{
			Info->StartProgress();

			// Query Ids
			if (Action == ECsAchievementAction::QueryIds)
			{
				QueryIds_Internal();
			}
			// Query Descriptions
			else
			if (Action == ECsAchievementAction::QueryDescriptions)
			{
				QueryDescriptions_Internal();
			}
			// Update Descriptions
			else
			if (Action == ECsAchievementAction::UpdateDescriptions)
			{
				UpdateDescriptions_Internal(Info);
			}
			// Write
			else
			if (Action == ECsAchievementAction::Write)
			{
				Write_Internal(Info);
			}
			// Complete
			else
			if (Action == ECsAchievementAction::Complete)
			{
				Complete_Internal(Info);
			}
			// Complete All
			else
			if (Action == ECsAchievementAction::CompleteAll)
			{
				CompleteAll_Internal(Info);
			}
			// Reset
			else
			if (Action == ECsAchievementAction::Reset)
			{
				Reset_Internal(Info);
			}
			// Reset All
			else
			if (Action == ECsAchievementAction::ResetAll)
			{
				ResetAll_Internal(Info);
			}

			if (Info->IsComplete())
			{
				// Update Next since Current's Next could have changed
				Next = Current->GetNextLink();

				Manager_Resource.Deallocate(InfoContainer);
			}
			else
			{
				break;
			}
		}
	}
}

// Action
#pragma region

void UCsManager_Achievement::QueueAction(const ECsAchievementAction& Action, const FECsAchievement& Achievement, const float& Percent /*=0.0f*/)
{
	// Allocate AchievementActionInfo from a pool
	FCsResourceContainer_AchievementActionInfo* InfoContainer = Manager_Resource.Allocate();
	FCsAchievementActionInfo* Info							  = InfoContainer->Get();

	Info->Reset();

	Info->Achievement = Achievement;
	Info->Action	  = Action;
	Info->Percent	  = Percent;
}

void UCsManager_Achievement::QueueAction(const ECsAchievementAction& Action)
{
	QueueAction(Action, EMCsAchievement::Get().GetMAX());
}

void UCsManager_Achievement::QueueActionAsHead(const ECsAchievementAction& Action, const FECsAchievement& Achievement, const float& Percent /*=0.0f*/)
{
	// Allocate AchievementActionInfo from a pool
	FCsResourceContainer_AchievementActionInfo* InfoContainer = Manager_Resource.AllocateBeforeHead();
	FCsAchievementActionInfo* Info							  = InfoContainer->Get();

	Info->Reset();

	Info->Achievement = Achievement;
	Info->Action	  = Action;
	Info->Percent	  = Percent;
}

void UCsManager_Achievement::QueueActionAsHead(const ECsAchievementAction& Action)
{
	QueueActionAsHead(Action, EMCsAchievement::Get().GetMAX());
}

void UCsManager_Achievement::QueueActionAfterHead(const ECsAchievementAction& Action, const FECsAchievement& Achievement, const float& Percent /*=0.0f*/)
{
	// Allocate AchievementActionInfo from a pool
	FCsResourceContainer_AchievementActionInfo* InfoContainer = Manager_Resource.AllocateAfterHead();
	FCsAchievementActionInfo* Info							  = InfoContainer->Get();

	Info->Reset();

	Info->Achievement = Achievement;
	Info->Action	  = Action;
	Info->Percent	  = Percent;
}

void UCsManager_Achievement::QueueActionAfterHead(const ECsAchievementAction& Action)
{
	QueueActionAfterHead(Action, EMCsAchievement::Get().GetMAX());
}

#pragma endregion Action

// Query
#pragma region

void UCsManager_Achievement::QueryIds()
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::QueryIds: Queueing Query Ids for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueryState.Ids.Reset();
		QueryState.Ids.Queue();
		QueueAction(ECsAchievementAction::QueryIds);
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::QueryIds_Internal()
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		TSharedPtr<const FUniqueNetId> UserId = GetLocalPlayerId();

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::QueryIds_Internal: Start Querying Achievements Ids for Player: %s at %s."), *(UserId->ToString()), *(FDateTime::Now().ToString()));
		}
#endif // !UE_BUILD_SHIPPING

		QueryState.Ids.Reset();
		QueryState.Ids.StartProcessing();

		IAchievements->QueryAchievements(*UserId, FOnQueryAchievementsCompleteDelegate::CreateUObject(this, &UCsManager_Achievement::OnQueryAchievementsComplete));
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::QueryDescriptions()
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::QueryDescriptions: Queueing Query Descriptions for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueryState.Descriptions.Reset();
		QueryState.Descriptions.Queue();
		QueueAction(ECsAchievementAction::QueryDescriptions);
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::QueryDescriptions_Internal()
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		TSharedPtr<const FUniqueNetId> UserId = GetLocalPlayerId();

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::QueryAchievementDescriptions: Start Querying Achievement Descriptions for Player: %s at %s."), *(UserId->ToString()), *(FDateTime::Now().ToString()));
		}
#endif // !UE_BUILD_SHIPPING

		QueryState.Descriptions.Reset();
		QueryState.Descriptions.StartProcessing();

		IAchievements->QueryAchievementDescriptions(*UserId, FOnQueryAchievementsCompleteDelegate::CreateUObject(this, &UCsManager_Achievement::OnQueryAchievementDescriptionsComplete));
	}
	// Local
	else
	{

	}
}

bool UCsManager_Achievement::CheckAndQueueQuery()
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Check to Queue Query Ids and Descriptions
		if (QueryState.IsComplete() &&
			!QueryState.IsSuccessful())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::CheckAndQueueQuery: Query Ids and/or Query Descriptions Failed for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			return false;
		}

		// Check Query Ids
		if (!QueryState.Ids.IsComplete() &&
			!QueryState.Ids.IsQueued() &&
			!QueryState.Ids.IsProcessing())
		{
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::CheckAndQueueQuery: Queueing Query Ids for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			QueryState.Ids.Queue();
			QueueAction(ECsAchievementAction::QueryIds);
		}

		// Check Query Description
		if (!QueryState.Ids.IsComplete() &&
			!QueryState.Ids.IsQueued() &&
			!QueryState.Ids.IsProcessing())
		{
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::CheckAndQueueQuery: Queueing Query Descriptions for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			QueryState.Descriptions.Queue();
			QueueAction(ECsAchievementAction::QueryDescriptions);
		}
	}
	// Local
	else
	{

	}
	return true;
}

#pragma endregion Query

// Descriptions
#pragma region

void UCsManager_Achievement::UpdateDescription(ICsAchievement* Achievement, const FOnlineAchievementDesc& Description)
{
	FCsAchievement* A = (FCsAchievement*)Achievement;

	A->Title			 = Description.Title;
	A->LockedDescription = Description.LockedDesc;
	A->UnlockDescription = Description.UnlockedDesc;
	A->bHidden			 = Description.bIsHidden;
	A->UnlockTime		 = Description.UnlockTime;

	A->SetValid();
}

void UCsManager_Achievement::UpdateDescriptions()
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::UpdateDescriptions: Query Ids and/or Query Descriptions Failed. Aborting UpdateDescriptions for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			return;
		}

		// Queue UpdateDescriptions
#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::UpdateDescriptions: Queueing UpdateDescriptions for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(ECsAchievementAction::UpdateDescriptions);
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::UpdateDescriptions_Internal(FCsAchievementActionInfo* ActionInfo)
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		// Get a list of all Achievements
		Local_OutAchievements.Reset(Local_OutAchievements.Max());
		const FUniqueNetId& PlayerId = GetLocalPlayerIdRef();

		EOnlineCachedResult::Type Result = IAchievements->GetCachedAchievements(PlayerId, Local_OutAchievements);

#if !UE_BUILD_SHIPPING
		if (Result == EOnlineCachedResult::NotFound)
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::UpdateDescriptions_Internal: No Achievements found for Player: %s at %s."), *(PlayerId.ToString()), *(FDateTime::Now().ToString()));
			
			ActionInfo->Complete();
			return;
		}
#endif // #if !UE_BUILD_SHIPPING

		for (FOnlineAchievement& OnlineAchievement : Local_OutAchievements)
		{
			const FString& Id = OnlineAchievement.Id;
			FOnlineAchievementDesc Desc;

			Result = IAchievements->GetCachedAchievementDescription(Id, Desc);
			
			if (Result == EOnlineCachedResult::NotFound)
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::UpdateDescriptions_Internal: Failed to find a description for Achievement: %s at %s."), *Id, *(FDateTime::Now().ToString()));
				continue;
			}

			ICsAchievement** AchievementPtr = AchievementMap.Find(Id);
			ICsAchievement* Achievement		= nullptr;

			if (!AchievementPtr)
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::UpdateDescriptions_Internal: Failed to find internally Achievement with Id: %s at %s."), *Id, *(FDateTime::Now().ToString()));
				
				FECsAchievement Enum = EMCsAchievement::Get().Create(Id);

				Achievements.Add(ConstructAchievement());
				Achievement = Achievements.Last();
				SetId(Achievement, Id);
				SetType(Achievement, Enum);

				AchievementMap.Add(Id, Achievement);
			}
			else
			{
				Achievement = *AchievementPtr;
			}
			
			const float MaxProgress = Achievement->CalculateProgress(1.0f);

			Achievement->SetProgress((float)(OnlineAchievement.Progress / MaxProgress));
			UpdateDescription(Achievement, Desc);

#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::UpdateDescriptions_Internal: Achievement: %s description updated at %s."), *Id, *(FDateTime::Now().ToString()));
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::UpdateDescriptions_Internal: - Progress: %f."), (float)OnlineAchievement.Progress);
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::UpdateDescriptions_Internal: - Title: %s."), *(Desc.Title.ToString()));
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::UpdateDescriptions_Internal: - Locked Description: %s."), *(Desc.LockedDesc.ToString()));
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::UpdateDescriptions_Internal: - Unlocked Description: %s."), *(Desc.UnlockedDesc.ToString()));
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::UpdateDescriptions_Internal: - IsHIdden: %s."), *(Desc.bIsHidden ? NCsCached::Str::True : NCsCached::Str::False));
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::UpdateDescriptions_Internal: - Unlock Time: %s."), *(Desc.UnlockTime.ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			ActionInfo->Complete();
		}
	}
	// Local
	else
	{

	}
}

#pragma endregion Descriptions

// Write
#pragma region

void UCsManager_Achievement::Write(const FECsAchievement& Achievement, const float& Percent)
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Write: Query Ids and/or Query Descriptions Failed. Aborting Write for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			return;
		}

		// Queue Write
#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Write: Queueing Write for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(ECsAchievementAction::Write, Achievement, Percent);

		// Queue Query Descriptions
#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Write: Queueing Query Descriptions for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueryState.Descriptions.Queue();
		QueueAction(ECsAchievementAction::QueryDescriptions);
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::Write_Internal(FCsAchievementActionInfo* ActionInfo)
{
	const FECsAchievement& Achievement = ActionInfo->Achievement;
	const float& Percent			   = ActionInfo->Percent;

	ICsAchievement* IA = Achievements[Achievement.Value];

	const float CurrentProgress = IA->GetProgress();
	const float NewProgress		= IA->CalculateProgress(Percent);

	// Online
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();

	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// No value change
		if (CurrentProgress == NewProgress)
		{
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Write_Internal: Achievement: %s already set to Progress: %f at %s."), *(Achievement.Name), CurrentProgress, *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING
			ActionInfo->Complete();
		}
		// Try to perform Write
		else
		if (!WriteObject.IsValid() ||
			 WriteObject->WriteState != EOnlineAsyncTaskState::InProgress)
		{
			if (QueryState.IsComplete() &&
				QueryState.IsSuccessful())
			{
				if (!IA->IsValid())
				{
					UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Write_Internal: Achievement: %s is NOT Valid. Make sure both QueryAchievements and QueryAchievementDescriptions have been called."), *(Achievement.Name));

					ActionInfo->Complete();
				}
				else
				{
					WriteState.Lock();

					CurrentAchievementWritten = Achievement;

					WriteObject = MakeShareable(new FOnlineAchievementsWrite());
					WriteObject->SetFloatStat(Achievement.Name_Internal, NewProgress);

					FOnlineAchievementsWriteRef WriteObjectRef = WriteObject.ToSharedRef();

#if !UE_BUILD_SHIPPING
					if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
					{
						UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Write_Internal: Starting Update Achievement: %s Progress from %f to %f at %s."), *(Achievement.Name), CurrentProgress, NewProgress, *(FDateTime::Now().ToString()));
					}
#endif // #if !UE_BUILD_SHIPPING

					IAchievements->WriteAchievements(UserId, WriteObjectRef, FOnAchievementsWrittenDelegate::CreateUObject(this, &UCsManager_Achievement::OnAchievementsWritten));
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Write_Internal: Query Ids and/or Query Descriptions Failed. Aborting Write for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
		}
		// Queue Write
		else
		{
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Write_Internal: Queueing Update Achievement: %s Progress from %f to %f at %s."), *(Achievement.Name), CurrentProgress, NewProgress, *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			QueueAction(ECsAchievementAction::Write, Achievement, Percent);
		}
	}
	// Local
	else
	{
		// TODO: Add Write to Disk

		// Reset / None or InProgress
		const float MaxProgress = IA->CalculateProgress(1.0f);

		if (NewProgress < MaxProgress)
		{
			IA->SetProgress(NewProgress);

#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::WriteAchievement: Updated Achievement: %s Progress from %f to %f at %s."), *(Achievement.Name), CurrentProgress, NewProgress, *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			OnProgress_Event.Broadcast(true, IA, NewProgress);
			OnProgress_ScriptEvent.Broadcast(true, Achievement, NewProgress);
		}
		// Completed
		else
		{
			// Update Achievement and progress
			IA->Complete();
			++NumCompleted;

			TotalProgress = NumCompleted / EMCsAchievement::Get().Num();

	#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::WriteAchievement: Completed Achievement: %s at %s."), *(Achievement.Name), *(FDateTime::Now().ToString()));
			}
	#endif // #if !UE_BUILD_SHIPPING

			OnComplete_Event.Broadcast(true, IA);
			OnComplete_ScriptEvent.Broadcast(true, Achievement);
		}
	}
}

#pragma endregion Write

// Complete
#pragma region

void UCsManager_Achievement::Complete(const FECsAchievement& Achievement)
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Complete: Query Ids and/or Query Descriptions Failed. Aborting Complete for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			return;
		}

		// Queue Complete
#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Complete: Queueing Complete for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(ECsAchievementAction::Complete, Achievement, 1.0f);

		// Queue Query Descriptions
#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Complete: Queueing Query Descriptions for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueryState.Descriptions.Queue();
		QueueAction(ECsAchievementAction::QueryDescriptions);
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::Complete_Internal(FCsAchievementActionInfo* ActionInfo)
{
	const FECsAchievement& Achievement = ActionInfo->Achievement;
	const float& Percent			   = ActionInfo->Percent;

	ICsAchievement* IA = Achievements[Achievement.Value];

	const float CurrentProgress = IA->GetProgress();
	const float NewProgress		= IA->CalculateProgress(Percent);

	// No value change
	if (CurrentProgress == NewProgress)
	{
		// Online
		IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();

		if (IAchievements.IsValid())
		{
			const FUniqueNetId& UserId = GetLocalPlayerIdRef();

#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Complete_Internal: Achievement: %s already Complete for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING
		}

		ActionInfo->Complete();
	}
	else
	{
		if (QueryState.IsComplete() &&
			QueryState.IsSuccessful())
		{
			if (!Achievements[Achievement.Value]->IsValid())
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Complete_Internal: Achievement: %s is NOT Valid. Make sure both QueryAchievements and QueryAchievementDescriptions have been called."), *(Achievement.Name));

				ActionInfo->Complete();
			}
			else
			{
				Write_Internal(ActionInfo);
			}
		}
		else
		{
			// Online
			IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();

			if (IAchievements.IsValid())
			{
				const FUniqueNetId& UserId = GetLocalPlayerIdRef();

				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Complete_Internal: Query Ids and/or Query Descriptions Failed. Aborting Reset for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}

			ActionInfo->Complete();
		}
	}
}

bool UCsManager_Achievement::IsCompleted(const FECsAchievement& Achievement)
{
	return Achievements[Achievement.Value]->GetState() == ECsAchievementState::Completed;
}

const int32& UCsManager_Achievement::GetNumCompleted()
{
	return NumCompleted;
}

void UCsManager_Achievement::CompleteAll()
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::CompleteAll: Query Ids and/or Query Descriptions Failed. Aborting CompleteAll for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			return;
		}

		// Queue Complete All
#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::CompleteAll: Queueing CompleteAll for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(ECsAchievementAction::CompleteAll);
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::CompleteAll_Internal(FCsAchievementActionInfo* ActionInfo)
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Queue Complete for Achievements

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::CompleteAll_Internal: Starting CompleteAll for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		TCsDoubleLinkedList<FCsResourceContainer_AchievementActionInfo*>* Current = Manager_Resource.GetAllocatedHead();
		FCsResourceContainer_AchievementActionInfo* InfoContainer				  = **Current;

		for (ICsAchievement* IA : Achievements)
		{
			if (!IA->IsValid())
				continue;

			FCsResourceContainer_AchievementActionInfo* CompleteInfoContainer = Manager_Resource.AllocateAfter(InfoContainer);
			FCsAchievementActionInfo* CompleteInfo							  = CompleteInfoContainer->Get();

			CompleteInfo->Reset();

			const FECsAchievement& Achievement = IA->GetType();

			CompleteInfo->Achievement = Achievement;
			CompleteInfo->Action	  = ECsAchievementAction::Complete;
			CompleteInfo->Percent	  = 1.0f;

			// Update InfoContainer so actions get queued in order
			InfoContainer = CompleteInfoContainer;

#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::CompleteAll_Internal: Queueing Complete for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING
		}

		// Queue Complete All event at end
		FCsResourceContainer_AchievementActionInfo* CompleteAllInfoContainer = Manager_Resource.AllocateAfter(InfoContainer);
		FCsAchievementActionInfo* CompleteAllInfo							 = CompleteAllInfoContainer->Get();

		CompleteAllInfo->Reset();

		CompleteAllInfo->Action = ECsAchievementAction::CompleteAll;
		CompleteAllInfo->Complete();

		InfoContainer = CompleteAllInfoContainer;

		// Queue Query Descriptions
		FCsResourceContainer_AchievementActionInfo* QueryDescriptionsInfoContainer = Manager_Resource.AllocateAfter(InfoContainer);
		FCsAchievementActionInfo* QueryDescriptionsInfo							   = QueryDescriptionsInfoContainer->Get();

		QueryDescriptionsInfo->Reset();

		QueryDescriptionsInfo->Action = ECsAchievementAction::QueryDescriptions;

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::CompleteAll_Internal: Queueing QueryDescriptions for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING
	}
	// Local
	else
	{

	}
}

#pragma endregion Complete

// Reset
#pragma region

void UCsManager_Achievement::Reset(const FECsAchievement& Achievement, const float& Percent /*= 0*/)
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Reset: Query Ids and/or Query Descriptions Failed. Aborting Reset for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			return;
		}

		// Queue Reset
#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Reset: Queueing Reset for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(ECsAchievementAction::Reset, Achievement, Percent);

		// Queue Query Descriptions
#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Reset: Queueing Query Descriptions for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueryState.Descriptions.Queue();
		QueueAction(ECsAchievementAction::QueryDescriptions);
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::Reset_Internal(FCsAchievementActionInfo* ActionInfo)
{
	const FECsAchievement& Achievement = ActionInfo->Achievement;
	const float& Percent			   = ActionInfo->Percent;

	ICsAchievement* IA = Achievements[Achievement.Value];

	const float CurrentProgress = IA->GetProgress();
	const float NewProgress		= IA->CalculateProgress(Percent);

	// No value change
	if (CurrentProgress == NewProgress)
	{
		// Online
		IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();

		if (IAchievements.IsValid())
		{
			const FUniqueNetId& UserId = GetLocalPlayerIdRef();

#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Reset_Internal: Achievement: %s already set to Progress: %f for Player: %s at %s."), *(Achievement.Name), CurrentProgress, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING
		}

		ActionInfo->Complete();
	}
	else
	{
		if (QueryState.IsComplete() &&
			QueryState.IsSuccessful())
		{
			if (!Achievements[Achievement.Value]->IsValid())
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Reset: Achievement: %s is NOT Valid. Make sure both QueryAchievements and QueryAchievementDescriptions have been called."), *(Achievement.Name));
				
				ActionInfo->Complete();
			}
			else
			{
				Write_Internal(ActionInfo);
			}
		}
		else
		{
			// Online
			IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();

			if (IAchievements.IsValid())
			{
				const FUniqueNetId& UserId = GetLocalPlayerIdRef();

				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::Reset: Query Ids and/or Query Descriptions Failed. Aborting Reset for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}

			ActionInfo->Complete();
		}
	}
}

void UCsManager_Achievement::ResetAll()
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::ResetAll: Query Ids and/or Query Descriptions Failed. Aborting ResetAll for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			return;
		}

		// Queue Reset All
#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::ResetAll: Queueing ResetAll for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueueAction(ECsAchievementAction::ResetAll);
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::ResetAll_Internal(FCsAchievementActionInfo* ActionInfo)
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Queue Reset All for Achievements

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::ResetAll_Internal: Starting ResetAll for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		TCsDoubleLinkedList<FCsResourceContainer_AchievementActionInfo*>* Current = Manager_Resource.GetAllocatedHead();
		FCsResourceContainer_AchievementActionInfo* InfoContainer				  = **Current;

		for (ICsAchievement* IA : Achievements)
		{
			if (!IA->IsValid())
				continue;

			FCsResourceContainer_AchievementActionInfo* ResetInfoContainer = Manager_Resource.AllocateAfter(InfoContainer);
			FCsAchievementActionInfo* ResetInfo							   = ResetInfoContainer->Get();

			ResetInfo->Reset();

			const FECsAchievement& Achievement = IA->GetType();

			ResetInfo->Achievement = Achievement;
			ResetInfo->Action	   = ECsAchievementAction::Reset;
			ResetInfo->Percent	   = 0.0f;

			// Update InfoContainer so actions get queued in order
			InfoContainer = ResetInfoContainer;

#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::ResetAll_Internal: Queueing Reset for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING
		}

		// Queue Reset All event at end
		FCsResourceContainer_AchievementActionInfo* ResetAllInfoContainer = Manager_Resource.AllocateAfter(InfoContainer);
		FCsAchievementActionInfo* ResetAllInfo							  = ResetAllInfoContainer->Get();

		ResetAllInfo->Reset();

		ResetAllInfo->Action = ECsAchievementAction::ResetAll;
		ResetAllInfo->Complete();

		InfoContainer = ResetAllInfoContainer;

		// Queue Query Descriptions
		FCsResourceContainer_AchievementActionInfo* QueryDescriptionsInfoContainer = Manager_Resource.AllocateAfter(InfoContainer);
		FCsAchievementActionInfo* QueryDescriptionsInfo							   = QueryDescriptionsInfoContainer->Get();

		QueryDescriptionsInfo->Reset();

		QueryDescriptionsInfo->Action = ECsAchievementAction::QueryDescriptions;

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::ResetAll_Internal: Queueing QueryDescriptions for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		ActionInfo->Complete();
	}
	// Local
	else
	{

	}
}

#pragma endregion Reset

// Progress
#pragma region

void UCsManager_Achievement::SetProgress(const FECsAchievement& Achievement, const float& Percent)
{
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::SetProgress: Query Ids and/or Query Descriptions Failed. Aborting Reset for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			return;
		}

		// Reset then Write
		if (bOnlyForwardProgress)
		{
			// Queue Reset
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::SetProgress: Queueing Reset for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			QueueAction(ECsAchievementAction::Reset, Achievement, 0.0f);

			// Queue Write
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::SetProgress: Queueing Write for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			QueueAction(ECsAchievementAction::Write, Achievement, Percent);
		}
		// Write
		else
		{
			// Queue Write
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::SetProgress: Queueing Write for Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
#endif // #if !UE_BUILD_SHIPPING

			QueueAction(ECsAchievementAction::Write, Achievement, Percent);
		}

		// Queue Query Descriptions
#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::SetProgress: Queueing Query Descriptions for Player: %s at %s."), *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		QueryState.Descriptions.Queue();
		QueueAction(ECsAchievementAction::QueryDescriptions);
	}
	// Local
	else
	{

	}
}

float UCsManager_Achievement::GetProgress(const FECsAchievement& Achievement)
{
	return Achievements[Achievement.Value]->GetProgress();
}

const float& UCsManager_Achievement::GetTotalProgress()
{
	return TotalProgress;
}

#pragma endregion Progress

// IOnlineAchievements
#pragma region

IOnlineAchievementsPtr UCsManager_Achievement::GetAchievementsInterface()
{
	//if (!bOnline)
	//	return nullptr;

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
					IOnlineAchievementsPtr OnlineAchievements = OnlineSub->GetAchievementsInterface();

					if (OnlineAchievements.IsValid())
					{
						return OnlineAchievements;
					}
					UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::GetAchievementsInterface (%d): No Online Achievements Interface found."), ControllerId);
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::GetAchievementsInterface (%d): No UniquePlayerId set for Local Player: %d."), ControllerId, ControllerId);
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::GetAchievementsInterface (%d): No Online Identity found."), ControllerId);
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::GetAchievementsInterface (%d): No Online Subsystem found."), ControllerId);
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::GetAchievementsInterface: No Local Player set."));
	}
	return nullptr;
}

void UCsManager_Achievement::OnQueryAchievementsComplete(const FUniqueNetId& PlayerId, const bool Success)
{
	TCsDoubleLinkedList<FCsResourceContainer_AchievementActionInfo*>* AllocatedHead = Manager_Resource.GetAllocatedHead();

	checkf(AllocatedHead, TEXT("UCsManager_Achievement::OnQueryAchievementsComplete: No Action was queued."));

	FCsResourceContainer_AchievementActionInfo* InfoContainer = **AllocatedHead;
	FCsAchievementActionInfo* ActionInfo				      = InfoContainer->Get();

	checkf(ActionInfo->Action == ECsAchievementAction::QueryIds, TEXT("UCsManager_Achievement::OnQueryAchievementsComplete: Current Action: %s is NOT QueryIds."), *(EMCsAchievementAction::Get().ToChar(ActionInfo->Action)));

	if (!Success)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::OnQueryAchievementsComplete: Failed to Query Achievements for Player: %s at %s."), *(PlayerId.ToString()), *(FDateTime::Now().ToString()));
		
		QueryState.Ids.Complete();
		ActionInfo->Complete();
		return;
	}

#if !UE_BUILD_SHIPPING
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::OnQueryAchievementsComplete: Completed Query Achievement Ids for Player: %s at %s."), *(PlayerId.ToString()), *(FDateTime::Now().ToString()));
	}
#endif // #if !UE_BUILD_SHIPPING

	QueryState.Ids.Success();
	QueryState.Ids.Complete();

	ActionInfo->Success();
	ActionInfo->Complete();
}

void UCsManager_Achievement::OnQueryAchievementDescriptionsComplete(const FUniqueNetId& PlayerId, const bool Success)
{
	TCsDoubleLinkedList<FCsResourceContainer_AchievementActionInfo*>* AllocatedHead = Manager_Resource.GetAllocatedHead();

	checkf(AllocatedHead, TEXT("UCsManager_Achievement::OnQueryAchievementDescriptionsComplete: No Action was queued."));

	FCsResourceContainer_AchievementActionInfo* InfoContainer = **AllocatedHead;
	FCsAchievementActionInfo* ActionInfo				      = InfoContainer->Get();

	checkf(ActionInfo->Action == ECsAchievementAction::QueryDescriptions, TEXT("UCsManager_Achievement::OnQueryAchievementDescriptionsComplete: Current Action: %s is NOT QueryDescriptions."), *(EMCsAchievementAction::Get().ToChar(ActionInfo->Action)));

	if (!Success)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::OnQueryAchievementDescriptionsComplete: Failed to Query Achievement Descriptions for Player: %s at %s."), *(PlayerId.ToString()), *(FDateTime::Now().ToString()));
		
		QueryState.Descriptions.Complete();
		ActionInfo->Complete();
		return;
	}

#if !UE_BUILD_SHIPPING
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::OnQueryAchievementDescriptionsComplete: Completed Query Achievement Descriptions for Player: %s at %s."), *(PlayerId.ToString()), *(FDateTime::Now().ToString()));
	}
#endif // #if !UE_BUILD_SHIPPING

	QueryState.Descriptions.Success();
	QueryState.Descriptions.Complete();

	ActionInfo->Success();
	ActionInfo->Complete();
}

void UCsManager_Achievement::OnAchievementsWritten(const FUniqueNetId& PlayerId, bool Success)
{
	TCsDoubleLinkedList<FCsResourceContainer_AchievementActionInfo*>* AllocatedHead = Manager_Resource.GetAllocatedHead();

	checkf(AllocatedHead, TEXT("UCsManager_Achievement::OnAchievementsWritten: No Action was queued."));

	FCsResourceContainer_AchievementActionInfo* InfoContainer = **AllocatedHead;
	FCsAchievementActionInfo* ActionInfo					  = InfoContainer->Get();

	const FECsAchievement& Achievement = ActionInfo->Achievement;
	const ECsAchievementAction& Action = ActionInfo->Action;

	ICsAchievement* IA = Achievements[Achievement.Value];

	const float CurrentProgress = IA->GetProgress();

	if (!Success)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::OnAchievementsWritten: Achievement: %s not written for Player: %s at %s."), *(Achievement.Name), *(PlayerId.ToString()), *(FDateTime::Now().ToString()));
		
		// Write
		if (Action == ECsAchievementAction::Write)
		{
			OnProgress_AsyncEvent.Broadcast(Success, IA, CurrentProgress);
			OnProgress_AsyncScriptEvent.Broadcast(Success, Achievement, CurrentProgress);
		}
		// Complete
		else
		if (Action == ECsAchievementAction::Complete)
		{
			OnComplete_AsyncEvent.Broadcast(Success, IA);
			OnComplete_AsyncScriptEvent.Broadcast(Success, Achievement);
		}
		// Reset
		else
		if (Action == ECsAchievementAction::Reset)
		{
			OnReset_AsyncEvent.Broadcast(Success, IA, CurrentProgress);
			OnReset_AsyncScriptEvent.Broadcast(Success, Achievement, CurrentProgress);
		}
		ActionInfo->Complete();
		return;
	}

	// Determine the result

	FVariantData* Data = WriteObject->FindStatByName(Achievement.Name_Internal);

	const EOnlineKeyValuePairDataType::Type DataType = Data->GetType();

	// TODO: Type may be different based on how Achievement is recorded.
	//		 Count -> uint64
	//		 Bitfield -> String

	const ECsAchievementProgress& ProgressType = IA->GetProgressType();
	float Progress = 0.0f;

	// Standard
	if (ProgressType == ECsAchievementProgress::Standard)
	{
		checkf(DataType == EOnlineKeyValuePairDataType::Float, TEXT("UCsManager_Achievement::OnAchievementsWritten: DataType for Achievement: %s with ProgressType: %s should be a Float at %s."), *(Achievement.Name), *(EMCsAchievementProgress::Get().ToString(ProgressType)), *(FDateTime::Now().ToString()));

		Data->GetValue(Progress);
	}
	// Count
	else
	if (ProgressType == ECsAchievementProgress::Count)
	{

	}
	// Bitfield
	else
	if (ProgressType == ECsAchievementProgress::Bitfield)
	{
	}

	// Reset / None or InProgress
	const float MaxProgress = IA->CalculateProgress(1.0f);

	if (Progress < MaxProgress)
	{
		IA->SetProgress(Progress / MaxProgress);

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::OnAchievementsWritten: Updated Achievement: %s Progress from %f to %f at %s."), *(Achievement.Name), CurrentProgress, Progress, *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		// Write
		if (Action == ECsAchievementAction::Write)
		{
			OnProgress_AsyncEvent.Broadcast(Success, IA, Progress);
			OnProgress_AsyncScriptEvent.Broadcast(Success, Achievement, Progress);
		}
		// Reset
		if (Action == ECsAchievementAction::Reset)
		{
			OnReset_AsyncEvent.Broadcast(Success, IA, Progress);
			OnReset_AsyncScriptEvent.Broadcast(Success, Achievement, Progress);
		}
	}
	// Completed
	else
	{
		// Update Achievement and progress
		IA->Complete();
		++NumCompleted;

		TotalProgress = NumCompleted / EMCsAchievement::Get().Num();

#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerAchievementTransactions))
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Achievement::OnAchievementsWritten: Completed Achievement: %s for Player: %s at %s."), *(Achievement.Name), *(PlayerId.ToString()), *(FDateTime::Now().ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		OnComplete_AsyncEvent.Broadcast(Success, IA);
		OnComplete_AsyncScriptEvent.Broadcast(Success, Achievement);
	}
	ActionInfo->Success();
	ActionInfo->Complete();
}

#pragma endregion IOnlineAchievements

// Internals
#pragma region

bool UCsManager_Achievement::IsValid(const FECsAchievement& Achievement)
{
	return Achievements[Achievement.Value]->IsValid();
}

void UCsManager_Achievement::SetId(ICsAchievement* Achievement, const FString& Id)
{
	FCsAchievement* A = (FCsAchievement*)Achievement;
	A->Id = Id;
}

void UCsManager_Achievement::SetType(ICsAchievement* Achievement, const FECsAchievement& AchievementType)
{
	FCsAchievement* A = (FCsAchievement*)Achievement;
	A->Type = AchievementType;
}

#pragma endregion Internals