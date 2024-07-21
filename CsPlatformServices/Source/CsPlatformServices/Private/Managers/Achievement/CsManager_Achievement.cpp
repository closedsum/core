// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Achievement/CsManager_Achievement.h"
#include "CsPlatformServices.h"

// CVars
#include "Managers/Achievement/CsCVars_Manager_Achievement.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_String.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsPlatformServicesSettings.h"
// Player
#include "Engine/LocalPlayer.h"
// Online
#include "Interfaces/OnlineIdentityInterface.h"
// Package
#include "UObject/Package.h"

#if WITH_EDITOR
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Managers/Achievement/CsGetManagerAchievement.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_Achievement)

// Cached
#pragma region

namespace NCsManagerAchievement
{
	namespace NCached
	{
		namespace Str
		{
			// Singleton
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, Init);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, Initialize);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, Start);
			// Query
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, QueryIds);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, QueryIds_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, QueryDescriptions);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, QueryDescriptions_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, CheckAndQueueQuery);
			// Descriptions
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, UpdateDescriptions);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, UpdateDescriptions_Internal);
			// Settings
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, UpdateBySettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, UpdateByDataTable);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, UpdateOrAddEntry);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, GetEntry);
			// Create
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, Create);
			// Modify
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, ModifyAchievement);
			// Remove
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, Remove);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, RemoveAll);
			// Write
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, Write);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, Write_Internal);
			// Complete
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, Complete);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, Complete_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, SafeComplete);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, IsCompleted);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, IsSafeCompleted);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, CompleteAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, CompleteAll_Internal);
			// Reset
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, Reset);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, SafeReset);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, Reset_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, ResetAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, ResetAll_Internal);
			// Progress
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, SetProgress);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, SetSafeProgress);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, GetProgress);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, GetSafeProgress);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, GetProgressAsPercent);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, GetSafeProgressAsPercent);
			// Count
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, Increment);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, SafeIncrement);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, SetCount);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, SetSafeCount);
			// Bitfield
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, SetBit);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Achievement, SetSafeBit);
		}
	}
}

#pragma endregion Cached

// static initializations
UCsManager_Achievement* UCsManager_Achievement::s_Instance;
bool UCsManager_Achievement::s_bShutdown = false;

UCsManager_Achievement::UCsManager_Achievement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Remove
	bRemoveBlocksQueuedActions = true;
	bRemoveAllBlocksQueuedActions = true;
	// Write
	WriteObject = nullptr;
	// Reset
	bResetAsResetAll = false;
	// Progress
	bOnlyForwardProgress = true;
	// Count
	bCountAsAdd = false;
	// Bitfield
	bBitfieldIndexStartsAtZero = true;
	bBitfieldAsOr = true;
	// IOnlineAchievements
	typedef NCsAchievement::NQuery::EOrder QueryOrderType;

	QueryOrder = QueryOrderType::IdsFirst;
}

#define USING_NS_CACHED using namespace NCsManagerAchievement::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsManagerAchievement::NCached; \
	const FString& Context = Str::__FunctionName
#define QueryOrderType NCsAchievement::NQuery::EOrder
#define ProgressMapType NCsAchievement::EMProgress
#define ProgressType NCsAchievement::EProgress

// Singleton
#pragma region

#if WITH_EDITOR
/*static*/ UCsManager_Achievement* UCsManager_Achievement::Get(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerAchievement(InRoot)->GetManager_Achievement();
}
#endif // #if WITH_EDITOR

/*static*/ bool UCsManager_Achievement::IsValid()
{
	return s_Instance != nullptr;
}

/*static*/ void UCsManager_Achievement::Init(UObject* InRoot, TSubclassOf<UCsManager_Achievement> ManagerAchievementClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerAchievement* GetManagerAchievement = Get_GetManagerAchievement(InRoot);
	UCsManager_Achievement* Manager_Achievement		= GetManagerAchievement->GetManager_Achievement();

	if (!Manager_Achievement)
	{
		Manager_Achievement = NewObject<UCsManager_Achievement>(InOuter ? InOuter : InRoot, ManagerAchievementClass, TEXT("Manager_Achievement_Singleton"), RF_Transient | RF_Public);

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

/*static*/ void UCsManager_Achievement::Init(UObject* InRoot, UObject* InOuter /*=nullptr*/)
{
	SET_CONTEXT(Init);

	const FCsSettings_Manager_Achievement& Settings = FCsSettings_Manager_Achievement::Get();

	Init(InRoot, Settings.LoadClassChecked(Context), InOuter);
}

/*static*/ void UCsManager_Achievement::Shutdown(const UObject* InRoot /*=nullptr*/)
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

/*static*/ ICsGetManagerAchievement* UCsManager_Achievement::Get_GetManagerAchievement(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Achievement::Get_GetManagerAchievement: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Achievement::Get_GetManagerAchievement: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Achievement::Get_GetManagerAchievement: Manager_Singleton is NULL."));

	ICsGetManagerAchievement* GetManagerAchievement = Cast<ICsGetManagerAchievement>(Manager_Singleton);

	checkf(GetManagerAchievement, TEXT("UCsManager_Achievement::Get_GetManagerAchievement: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerAchievement."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerAchievement;
}

/*static*/ ICsGetManagerAchievement* UCsManager_Achievement::GetSafe_GetManagerAchievement(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	CS_IS_PTR_NULL_RET_NULL(InRoot)

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	if (!GetManagerSingleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Singleton from InRoot: %s with Class: %s."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}
	return Cast<ICsGetManagerAchievement>(Manager_Singleton);
}

/*static*/ UCsManager_Achievement* UCsManager_Achievement::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerAchievement* GetManagerAchievement = GetSafe_GetManagerAchievement(Context, InRoot, Log))
		return GetManagerAchievement->GetManager_Achievement();
	return nullptr;
}

#endif // #if WITH_EDITOR

void UCsManager_Achievement::Initialize()
{
	SET_CONTEXT(Initialize);

	NCsAchievement::PopulateEnumMapFromSettings(Context);

	const int32& Count = EMCsAchievement::Get().Num();

	Achievements.Reserve(Count);

	for (const FECsAchievement& Enum : EMCsAchievement::Get())
	{
		Achievements.Add(ConstructAchievement());
		ICsAchievement* A = Achievements.Last();
		SetId(A, Enum.GetName());
		SetType(A, Enum);
		SetProgressType(A, ProgressType::Standard);
	}

	for (const FECsAchievement& Enum : EMCsAchievement::Get())
	{
		AchievementMap.Add(Enum.GetName(), Achievements[Enum.GetValue()]);
	}

	AchievementEntries.Reserve(Count);
	AchievementEntries.AddDefaulted(Count);

	for (const FECsAchievement& Enum : EMCsAchievement::Get())
	{
		FCsAchievementEntry& Entry = AchievementEntries[Enum.GetValue()];

		Entry.Name		  = Enum.GetName();
		Entry.DisplayName = Enum.GetDisplayName();

		AchievementEntryMap.Add(Enum.GetName(), Entry);
	}

	Local_OutAchievements.Reserve(Count);

	Construct_Local_OnlineAchievementDesc();

	//ConsoleCommand = new FRsConsoleCommand_Manager_Achievement(MyRoot);
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
	SET_CONTEXT(Start);

	if (!IsEnabled(Context))
		return;

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
		if (QueryOrder == QueryOrderType::IdsFirst)
		{
			QueryIds();
			QueryDescriptions();
		}
		// Descriptions First
		else
		if (QueryOrder == QueryOrderType::DescriptionsFirst)
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

ICsAchievement* UCsManager_Achievement::GetAchievement(const FECsAchievement& Achievement)
{
	return Achievements[Achievement.GetValue()];
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

FString UCsManager_Achievement::GetLocalPlayerNickname()
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();
	return Identity->GetPlayerNickname(LocalPlayer->GetControllerId());
}

#pragma endregion Player

void UCsManager_Achievement::Update(const float& DeltaSeconds)
{
	typedef NCsAchievement::NAction::NInfo::FResource InfoContainerType;
	typedef NCsAchievement::NAction::NInfo::FInfo InfoType;

	typedef NCsAchievement::EAction ActionType;

	TCsDoubleLinkedList<InfoContainerType*>* Current = Manager_Resource.GetAllocatedHead();
	TCsDoubleLinkedList<InfoContainerType*>* Next    = Current;

	while (Next)
	{
		Current							 = Next;
		InfoContainerType* InfoContainer = **Current;
		Next							 = Current->GetNextLink();

		InfoType* Info = InfoContainer->Get();
		
		const FECsAchievement& Achievement = Info->Achievement;
		const FString& Name				   = Info->Name;
		const ActionType& Action		   = Info->Action;
		const float& Percent			   = Info->Value.Percent;
		const FCsAchievementEntry& Entry   = Info->Entry;


		// If In Progress, wait for Complete
		if (Info->InProgress())
			break;
		// If Complete, handle completion (fire any events) and move onto next Action
		if (Info->IsComplete())
		{
			const bool WasSuccessful = Info->WasSuccessful();

			ICsAchievement* IA = Achievement != EMCsAchievement::Get().GetMAX() ? Achievements[Achievement.GetValue()] : nullptr;

			const float Progress = IA ? IA->CalculateProgress(Percent) : 0.0f;

			// Query Ids
			if (Action == ActionType::QueryIds)
			{
				OnQueryIds_Event.Broadcast(WasSuccessful);
				OnQueryIds_ScriptEvent.Broadcast(WasSuccessful);
			}
			// Query Descriptions
			else
			if (Action == ActionType::QueryDescriptions)
			{
				OnQueryDescriptions_Event.Broadcast(WasSuccessful);
				OnQueryDescriptions_ScriptEvent.Broadcast(WasSuccessful);
			}
			// Create
			else
			if (Action == ActionType::Create)
			{
				OnCreate_Event.Broadcast(WasSuccessful, IA);
				OnCreate_ScriptEvent.Broadcast(WasSuccessful, Achievement);
			}
			// Modify
			else
			if (Action == ActionType::Modify)
			{
				OnModify_Event.Broadcast(WasSuccessful, IA);
				OnModify_ScriptEvent.Broadcast(WasSuccessful, Achievement);
			}
			// Remove
			else
			if (Action == ActionType::Remove)
			{
				OnRemove_Event.Broadcast(WasSuccessful, Name);
				OnRemove_ScriptEvent.Broadcast(WasSuccessful, Name);
			}
			// Remove All
			else
			if (Action == ActionType::RemoveAll)
			{
				OnRemoveAll_Event.Broadcast(WasSuccessful);
				OnRemoveAll_ScriptEvent.Broadcast(WasSuccessful);
			}
			// Write
			else
			if (Action == ActionType::Write)
			{
				OnProgress_Event.Broadcast(WasSuccessful, IA, Progress);
				OnProgress_ScriptEvent.Broadcast(WasSuccessful, Achievement, Progress);
			}
			// Complete
			else
			if (Action == ActionType::Complete)
			{
				OnComplete_Event.Broadcast(WasSuccessful, IA);
				OnComplete_ScriptEvent.Broadcast(WasSuccessful, Achievement);
			}
			// Complete All
			else
			if (Action == ActionType::CompleteAll)
			{
				OnCompleteAll_Event.Broadcast();
				OnCompleteAll_ScriptEvent.Broadcast();
			}
			// Reset
			else
			if (Action == ActionType::Reset)
			{
				OnReset_Event.Broadcast(WasSuccessful, IA, Progress);
				OnReset_ScriptEvent.Broadcast(WasSuccessful, Achievement, Progress);
			}
			// Reset All
			else
			if (Action == ActionType::ResetAll)
			{
				OnResetAll_Event.Broadcast(WasSuccessful);
				OnResetAll_ScriptEvent.Broadcast(WasSuccessful);
			}
			Manager_Resource.Deallocate(InfoContainer);
			continue;
		}
		// If Ready to Process, Start
		if (Info->IsReadyToProcess())
		{
			Info->StartProgress();

			// Query Ids
			if (Action == ActionType::QueryIds)
			{
				QueryIds_Internal();
			}
			// Query Descriptions
			else
			if (Action == ActionType::QueryDescriptions)
			{
				QueryDescriptions_Internal();
			}
			// Update Descriptions
			else
			if (Action == ActionType::UpdateDescriptions)
			{
				UpdateDescriptions_Internal(Info);
			}
			// Create
			else
			if (Action == ActionType::Create)
			{
				Create_Internal(Info);
			}
			// Modify
			else
			if (Action == ActionType::Modify)
			{
				ModifyAchievement_Internal(Info);
			}
			// Remove
			else
			if (Action == ActionType::Remove)
			{
				Remove_Internal(Info);
			}
			// Remove All
			else
			if (Action == ActionType::RemoveAll)
			{
				RemoveAll_Internal(Info);
			}
			// Write
			else
			if (Action == ActionType::Write)
			{
				Write_Internal(Info);
			}
			// Complete
			else
			if (Action == ActionType::Complete)
			{
				Complete_Internal(Info);
			}
			// Complete All
			else
			if (Action == ActionType::CompleteAll)
			{
				CompleteAll_Internal(Info);
			}
			// Reset
			else
			if (Action == ActionType::Reset)
			{
				Reset_Internal(Info);
			}
			// Reset All
			else
			if (Action == ActionType::ResetAll)
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

#define ActionType NCsAchievement::EAction
#define ActionInfoContainerType NCsAchievement::NAction::NInfo::FResource
#define ActionInfoType NCsAchievement::NAction::NInfo::FInfo
#define ActionAllocationType NCsAchievement::NAction::EAllocation

void UCsManager_Achievement::QueueAction(const ActionType& Action, const FECsAchievement& Achievement, const float& Percent)
{
	ActionInfoType* Info = QueueAction_Internal(ActionAllocationType::AfterTail, Action, Achievement);

	Info->Value.SetPercent(Percent);
}

void UCsManager_Achievement::QueueAction(const ActionType& Action, const FECsAchievement& Achievement, const uint64& Count)
{
	ActionInfoType* Info = QueueAction_Internal(ActionAllocationType::AfterTail, Action, Achievement);

	Info->Value.SetCount(Count);
}

void UCsManager_Achievement::QueueAction(const ActionType& Action, const FECsAchievement& Achievement, const FString& Bitfield)
{
	ActionInfoType* Info = QueueAction_Internal(ActionAllocationType::AfterTail, Action, Achievement);

	Info->Value.SetBitfield(Bitfield);
}

void UCsManager_Achievement::QueueAction(const ActionType& Action, const FCsAchievementEntry& Entry)
{
	QueueAction_Internal(ActionAllocationType::AfterTail, Action, Entry);
}

void UCsManager_Achievement::QueueAction(const ActionType& Action, const FECsAchievement& Achievement, const FCsAchievementEntry& Entry)
{
	QueueAction_Internal(ActionAllocationType::AfterTail, Action, Achievement, Entry);
}

void UCsManager_Achievement::QueueAction(const ActionType& Action, const FECsAchievement& Achievement)
{
	QueueAction_Internal(ActionAllocationType::AfterTail, Action, Achievement);
}

void UCsManager_Achievement::QueueAction(const ActionType& Action)
{
	QueueAction_Internal(ActionAllocationType::AfterTail, Action);
}

ActionInfoType* UCsManager_Achievement::QueueAction_Internal(const ActionAllocationType& Allocation, const ActionType& Action)
{
	// Allocate AchievementActionInfo from a pool
	ActionInfoContainerType* InfoContainer = nullptr;

	// After Tail
	if (Allocation == ActionAllocationType::AfterTail)
		InfoContainer = Manager_Resource.Allocate();
	// As Head
	else
	if (Allocation == ActionAllocationType::AsHead)
		InfoContainer = Manager_Resource.AllocateBeforeHead();
	// After Head
	else
	if (Allocation == ActionAllocationType::AfterHead)
		InfoContainer = Manager_Resource.AllocateBeforeHead();

	ActionInfoType* Info	= InfoContainer->Get();

	Info->Reset();

	Info->Action = Action;

	return Info;
}

ActionInfoType* UCsManager_Achievement::QueueAction_Internal(const ActionAllocationType& Allocation, const ActionType& Action, const FECsAchievement& Achievement)
{
	ActionInfoType* Info = QueueAction_Internal(Allocation, Action);

	Info->Achievement = Achievement;

	return Info;
}

ActionInfoType* UCsManager_Achievement::QueueAction_Internal(const ActionAllocationType& Allocation, const ActionType& Action, const FCsAchievementEntry& Entry)
{
	ActionInfoType* Info = QueueAction_Internal(Allocation, Action);

	Info->Entry = Entry;

	return Info;
}

ActionInfoType* UCsManager_Achievement::QueueAction_Internal(const ActionAllocationType& Allocation, const ActionType& Action, const FECsAchievement& Achievement, const FCsAchievementEntry& Entry)
{
	ActionInfoType* Info = QueueAction_Internal(Allocation, Action, Achievement);

	Info->Entry = Entry;

	return Info;
}

void UCsManager_Achievement::QueueActionAsHead(const ActionType& Action, const FECsAchievement& Achievement, const float& Percent)
{
	ActionInfoType* Info = QueueAction_Internal(ActionAllocationType::AsHead, Action, Achievement);

	Info->Value.SetPercent(Percent);
}

void UCsManager_Achievement::QueueActionAsHead(const ActionType& Action)
{
	QueueAction_Internal(ActionAllocationType::AsHead, Action);
}

void UCsManager_Achievement::QueueActionAfterHead(const ActionType& Action, const FECsAchievement& Achievement, const float& Percent)
{
	ActionInfoType* Info = QueueAction_Internal(ActionAllocationType::AfterHead, Action, Achievement);

	Info->Value.SetPercent(Percent);
}

void UCsManager_Achievement::QueueActionAfterHead(const ActionType& Action)
{
	QueueAction_Internal(ActionAllocationType::AfterHead, Action);
}

#undef ActionType
#undef ActionInfoContainerType
#undef ActionInfoType
#undef ActionAllocationType

#pragma endregion Action

// Query
#pragma region

#define ActionType NCsAchievement::EAction

void UCsManager_Achievement::QueryIds()
{
	SET_CONTEXT(QueryIds);

	if (!IsEnabled(Context))
		return;

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Query Ids for Player: %s at %s."), *Context, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		QueryState.Ids.Reset();
		QueryState.Ids.Queue();

		QueueAction(ActionType::QueryIds);
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::QueryIds_Internal()
{
	SET_CONTEXT(QueryIds_Internal);

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		TSharedPtr<const FUniqueNetId> UserId = GetLocalPlayerId();

	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Start Querying Achievements Ids for Player: %s at %s."), *Context, *(UserId->ToString()), *(FDateTime::Now().ToString()));
		}
	#endif // !UE_BUILD_SHIPPING

		QueryState.Ids.Reset();
		QueryState.Ids.StartProcessing();

		QueryAchievementIds(*UserId, FOnQueryAchievementsCompleteDelegate::CreateUObject(this, &UCsManager_Achievement::OnQueryAchievementsComplete));
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::QueryAchievementIds(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate)
{
	GetAchievementsInterface()->QueryAchievements(PlayerId, Delegate);
}

void UCsManager_Achievement::QueryDescriptions()
{
	SET_CONTEXT(QueryDescriptions);

	if (!IsEnabled(Context))
		return;

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Query Descriptions for Player: %s at %s."), *Context, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		QueryState.Descriptions.Reset();
		QueryState.Descriptions.Queue();

		QueueAction(ActionType::QueryDescriptions);
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::QueryDescriptions_Internal()
{
	SET_CONTEXT(QueryDescriptions_Internal);

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		TSharedPtr<const FUniqueNetId> UserId = GetLocalPlayerId();

	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Start Querying Achievement Descriptions for Player: %s at %s."), *Context, *(UserId->ToString()), *(FDateTime::Now().ToString()));
		}
	#endif // !UE_BUILD_SHIPPING

		QueryState.Descriptions.Reset();
		QueryState.Descriptions.StartProcessing();

		QueryAchievementDescriptions(*UserId, FOnQueryAchievementsCompleteDelegate::CreateUObject(this, &UCsManager_Achievement::OnQueryAchievementDescriptionsComplete));
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::QueryAchievementDescriptions(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate)
{
	GetAchievementsInterface()->QueryAchievementDescriptions(PlayerId, Delegate);
}

bool UCsManager_Achievement::CheckAndQueueQuery()
{
	SET_CONTEXT(CheckAndQueueQuery);

	if (!IsEnabled(Context))
		return false;

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Check to Queue Query Ids and Descriptions
		if (QueryState.IsComplete() &&
			!QueryState.IsSuccessful())
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed for Player: %s at %s."), *Context, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			return false;
		}

		// Check Query Ids
		if (!QueryState.Ids.IsComplete() &&
			!QueryState.Ids.IsQueued() &&
			!QueryState.Ids.IsProcessing())
		{
		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Query Ids for Player: %s at %s."), *Context, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
		#endif // #if !UE_BUILD_SHIPPING

			QueryState.Ids.Queue();
			QueueAction(ActionType::QueryIds);
		}

		// Check Query Description
		bool DescriptionsQueued = false;

		if (!QueryState.Ids.IsComplete() &&
			!QueryState.Ids.IsQueued() &&
			!QueryState.Ids.IsProcessing())
		{
		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Query Descriptions for Player: %s at %s."), *Context, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			}
		#endif // #if !UE_BUILD_SHIPPING

			QueryState.Descriptions.Queue();
			QueueAction(ActionType::QueryDescriptions);
		}

		// Update Descriptions if Query Description has been Queued
		if (DescriptionsQueued)
		{
		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Update Descriptions for Player: %s - %s."), *Context, *GetLocalPlayerNickname(), *(UserId.ToString()));
			}
		#endif // #if !UE_BUILD_SHIPPING
			QueueAction(ActionType::UpdateDescriptions);
		}
	}
	// Local
	else
	{

	}
	return true;
}

#undef ActionType

#pragma endregion Query

// Descriptions
#pragma region

#define ActionType NCsAchievement::EAction
#define ActionInfoType NCsAchievement::NAction::NInfo::FInfo

void UCsManager_Achievement::UpdateInfoAndDescription(ICsAchievement* Achievement, const FOnlineAchievement* Info, const FOnlineAchievementDesc* Description)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);

	A->Title			 = Description->Title;
	A->Description		 = Description->LockedDesc;
	A->UnlockDescription = Description->UnlockedDesc;
	A->bHidden			 = Description->bIsHidden;
	A->UnlockTime		 = Description->UnlockTime;

	A->SetValid();
}

void UCsManager_Achievement::UpdateDescriptions()
{
	SET_CONTEXT(UpdateDescriptions);

	if (!IsEnabled(Context))
		return;

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting UpdateDescriptions for Player: %s at %s."), *Context, *(UserId.ToString()), *(FDateTime::Now().ToString()));
			return;
		}

		// Queue UpdateDescriptions
	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing UpdateDescriptions for Player: %s at %s."), *Context, *(UserId.ToString()), *(FDateTime::Now().ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		QueueAction(ActionType::UpdateDescriptions);
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::Construct_Local_OnlineAchievementDesc()
{
	Local_OnlineAchievementDesc = new FOnlineAchievementDesc();
}

void UCsManager_Achievement::Reset_Local_OnlineAchievementDesc()
{
	Local_OnlineAchievementDesc->Title = FText::FromString(TEXT(""));
	Local_OnlineAchievementDesc->LockedDesc = FText::FromString(TEXT(""));
	Local_OnlineAchievementDesc->UnlockedDesc = FText::FromString(TEXT(""));
	Local_OnlineAchievementDesc->bIsHidden = false;
	Local_OnlineAchievementDesc->UnlockTime = FDateTime::Now();
}

void UCsManager_Achievement::UpdateDescriptions_Internal(ActionInfoType* ActionInfo)
{
	SET_CONTEXT(UpdateDescriptions_Internal);

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
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: No Achievements found for Player: %s at %s."), *Context, *(PlayerId.ToString()), *(FDateTime::Now().ToString()));
			
			ActionInfo->Complete();
			return;
		}
	#endif // #if !UE_BUILD_SHIPPING

		for (FOnlineAchievement& OnlineAchievement : Local_OutAchievements)
		{
			const FString& Id = OnlineAchievement.Id;

			Reset_Local_OnlineAchievementDesc();

			FOnlineAchievementDesc* Desc = Local_OnlineAchievementDesc;

			Result = GetCachedAchievementDescription(Id, Desc);
			
			if (Result == EOnlineCachedResult::NotFound)
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Failed to find a description for Achievement: %s at %s."), *Context, *Id, *(FDateTime::Now().ToString()));
				continue;
			}

			ICsAchievement** AchievementPtr = AchievementMap.Find(Id);
			ICsAchievement* Achievement		= nullptr;

			if (!AchievementPtr)
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Failed to find internally Achievement with Id: %s at %s."), *Context, *Id, *(FDateTime::Now().ToString()));
				
				FECsAchievement Enum = EMCsAchievement::Get().Create(Id);

				checkf(Enum.GetValue() == Achievements.Num(), TEXT("%s: Achievement: %s Value: %d does NOT match array position in Achievements."), *Context, *(Enum.GetName()), Enum.GetValue());

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
			
			UpdateInfoAndDescription(Achievement, &OnlineAchievement, Desc);
			UpdateOrAddEntry(Achievement);

		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				PrintDescription(Achievement);
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

EOnlineCachedResult::Type UCsManager_Achievement::GetCachedAchievementDescription(const FString& AchievementId, FOnlineAchievementDesc* OutAchievementDesc)
{
	return GetAchievementsInterface()->GetCachedAchievementDescription(AchievementId, *OutAchievementDesc);
}

void UCsManager_Achievement::PrintDescription(ICsAchievement* Achievement)
{
	UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::PrintDescription: Achievement: %s with Id: %s."), Achievement->GetType().DisplayNameToChar(), *Achievement->GetId());
	UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::PrintDescription: - Progress: %f."), (float)Achievement->GetProgress());
	UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::PrintDescription: - Title: %s."), *(Achievement->GetTitle().ToString()));
	UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::PrintDescription: - Description: %s."), *(Achievement->GetDescription().ToString()));
	UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::PrintDescription: - Unlocked Description: %s."), *(Achievement->GetUnlockedDescription().ToString()));
	UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::PrintDescription: - IsHIdden: %s."), Achievement->IsHidden() ? TEXT("True") : TEXT("False"));
	UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::PrintDescription: - Unlock Time: %s."), *(Achievement->GetUnlockTime().ToString()));

	const ProgressType& Type = Achievement->GetProgressType();

	UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::PrintDescription: - ProgressType: %s."), ProgressMapType::Get().ToChar(Type));

	// Bitfield
	if (Type == ProgressType::Bitfield)
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::PrintDescription: - Unlock Bitfield Length: %d."), Achievement->GetUnlockBitfieldLength());
	}
	// Count
	else
	if (Type == ProgressType::Count)
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::PrintDescription: - Max Count: %d."), Achievement->GetMaxCount());
	}
}

#undef ActionType
#undef ActionInfoType

#pragma endregion Descriptions

// Settings
#pragma region

void UCsManager_Achievement::UpdateBySettings()
{
	SET_CONTEXT(UpdateBySettings);

	if (!IsEnabled(Context))
		return;

	UCsPlatformServicesSettings* Settings = GetMutableDefault<UCsPlatformServicesSettings>();

	if (!Settings)
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Failed to get settings of type: UCsPlatformServicesSettings."), *Context);
		return;
	}

	TSoftObjectPtr<UDataTable> AchievementsDataTable = Settings->Achievements;
	UDataTable* DataTable							 = AchievementsDataTable.LoadSynchronous();

	if (!DataTable)
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Failed to get Achievements DataTable from Settings: UCsPlatformServicesSettings."), *Context);
		return;
	}

	UpdateByDataTable(DataTable);
}

void UCsManager_Achievement::UpdateByDataTable(UDataTable* DataTable)
{
	SET_CONTEXT(UpdateByDataTable);

	if (!IsEnabled(Context))
		return;

	CS_IS_PENDING_KILL_CHECKED(DataTable)

	checkf(DataTable->GetRowStruct() == FCsAchievementEntry::StaticStruct(), TEXT("%s: DataTable: %s RowStruct: %s != FCsAchievementEntry."), *Context, *(DataTable->GetName()), *(DataTable->GetRowStruct()->GetName()));

	// Check Enum entries have been added
	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

#if !UE_BUILD_SHIPPING
	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& Name				 = Pair.Key;
		const FCsAchievementEntry* Entry = (const FCsAchievementEntry*)Pair.Value;

		checkf(Entry->Name.Compare(Name.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != Achievement Name (%s != %s)."), *Context, *(Entry->Name), *(Name.ToString()));

		checkf(EMCsAchievement::Get().IsValidEnum(Entry->Name), TEXT("%s: Achievement (Name): %s has not been added to the Enum Map: EMCsAchievement."), *Context, *(Entry->Name));

		if (!Entry->DisplayName.IsEmpty())
		{
			checkf(EMCsAchievement::Get().IsValidEnumByDisplayName(Entry->DisplayName), TEXT("%s: Achievement (DisplayName): %s has not been added to the Enum Map: EMCsAchievement."), *Context, *(Entry->DisplayName));
		}
	}
#endif // #if !UE_BUILD_SHIPPING

	// Check for a change in Achievements, If so, remove the difference
	bool Change = false;

	TArray<ICsAchievement*> AchievementsToRemove;
	AchievementsToRemove.Reserve(AchievementMap.Num());

	TArray<FCsAchievementEntry*> AchievementsToAdd;
	AchievementsToAdd.Reserve(RowMap.Num());

	TArray<FCsAchievementEntry*> AchievementsToModify;
	AchievementsToModify.Reserve(FMath::Max(RowMap.Num(), AchievementMap.Num()));

	// Find Achievements to Remove
	for (const TPair<FString, ICsAchievement*>& Pair : AchievementMap)
	{
		const FString& Id = Pair.Key;
		const FName Name  = FName(*Id);

		// Find Achievements to Modify
		if (const uint8* const* RowPtr = RowMap.Find(Name))
		{
			const FCsAchievementEntry* Row   = (const FCsAchievementEntry*)(*RowPtr);
			const FCsAchievementEntry& Entry = AchievementEntryMap[Row->Name];

			if (*Row != Entry)
			{
				AchievementsToModify.Add(const_cast<FCsAchievementEntry*>(Row));
				Change = true;
			}
		}
		else
		{
			AchievementsToRemove.Add(Pair.Value);
			Change = true;
		}
	}
	// Find Achievements to Add
	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FCsAchievementEntry* Entry = (const FCsAchievementEntry*)Pair.Value;

		if (!AchievementMap.Find(Entry->Name))
		{
			AchievementsToAdd.Add(const_cast<FCsAchievementEntry*>(Entry));
			Change = true;
		}
	}

	if (Change)
	{
		// Queue Remove
		if (AchievementsToRemove.Num() > CS_EMPTY)
		{
			for (ICsAchievement* IA : AchievementsToRemove)
			{
				Remove(IA->GetType());
			}
		}

		// Queue Create
		if (AchievementsToAdd.Num() > CS_EMPTY)
		{
			for (FCsAchievementEntry* Entry : AchievementsToAdd)
			{
				Create(*Entry);
			}
		}

		// Queue Modify
		if (AchievementsToModify.Num() > CS_EMPTY)
		{
			for (FCsAchievementEntry* Entry : AchievementsToModify)
			{
				ModifyAchievement(*Entry);
			}
		}
	}
}

void UCsManager_Achievement::UpdateOrAddEntry(ICsAchievement* Achievement)
{
	SET_CONTEXT(UpdateOrAddEntry);

	const FECsAchievement& Type	  = Achievement->GetType();
	FCsAchievementEntry* EntryPtr = AchievementEntryMap.Find(Type.GetName());

	if (!EntryPtr)
	{	
		EntryPtr = &(AchievementEntryMap.Add(Type.GetName()));

		checkf(Type.GetValue() == AchievementEntries.Num(), TEXT("%s: Achievement: %s Value: %d does not match array position in AchievementEntries."), *Context, *(Type.GetName()), Type.GetValue());

		AchievementEntries.AddDefaulted();
	}

	FCsAchievementEntry& Entry = AchievementEntries[Type.GetValue()];

	Entry.Name			= Type.GetName();
	Entry.DisplayName	= Type.GetDisplayName();
	Entry.bValid		= Achievement->IsValid();
	Entry.SetProgressType((ECsAchievementProgress)Achievement->GetProgressType());
	Entry.Count			= Achievement->GetCount();
	Entry.BitfieldLength = Achievement->GetBitfieldLength();

	// TODO: Some platforms (Oculus) doesn't seem to report this back properly
	//		 So, don't update this for now.

	//Entry.Title = Achievement->GetTitle();
	//Entry.Description = Achievement->GetDescription();
	//Entry.UnlockedDescription = Achievement->GetUnlockedDescription();

	Entry.bHidden = Achievement->IsHidden();

	*EntryPtr = Entry;
}

void UCsManager_Achievement::UpdateFromEntry(ICsAchievement* Achievement)
{
	const FECsAchievement& Type		 = Achievement->GetType();
	const FCsAchievementEntry& Entry = GetEntry(Type);

	if (Entry.bValid)
		Achievement->SetValid();
	else
		Achievement->SetInvalid();

	SetProgressType(Achievement, (ProgressType)Entry.GetProgressType());
	
	// Count
	if (Entry.GetProgressType() == ECsAchievementProgress::Count)
	{
		SetCount(Achievement, Entry.Count);
	}
	// Bitfield
	else
	if (Entry.GetProgressType() == ECsAchievementProgress::Bitfield)
	{
		typedef NCsString::FLibrary StringLibrary;

		FString Bitfield;
		StringLibrary::CreateUnsetBitfield(Bitfield, Entry.BitfieldLength);

		SetBitfield(Achievement, Bitfield);
		SetUnlockBitfieldLength(Achievement, Entry.Count);
	}
}

const FCsAchievementEntry& UCsManager_Achievement::GetEntry(const FECsAchievement& Achievement)
{
	SET_CONTEXT(GetEntry);
	
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsAchievement, Achievement)

	checkf(Achievement.GetValue() < AchievementEntries.Num(), TEXT("%s: No Entry has been created for Achievement: %s."), *Context, Achievement.ToChar());

	return AchievementEntries[Achievement.GetValue()];
}

bool UCsManager_Achievement::HasEntry(const FString& Name)
{
	return AchievementEntryMap.Find(Name) != nullptr;
}

#pragma endregion Settings

// Create
#pragma region

void UCsManager_Achievement::Create(const FCsAchievementEntry& Entry)
{
	SET_CONTEXT(Create);

	if (!IsEnabled(Context))
		return;

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting Create for Achievement: %s for Player: %s - %s."), *Context, *(Entry.Name), *GetLocalPlayerNickname(), *(UserId.ToString()));
			return;
		}

#if !UE_BUILD_SHIPPING
		if (EMCsAchievement::Get().IsValidEnum(FName(*(Entry.Name))))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement (Name): %s already exists."), *Context, *(Entry.Name));
			return;
		}

		if (!Entry.DisplayName.IsEmpty() &&
			EMCsAchievement::Get().IsValidEnumByDisplayName(Entry.DisplayName))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement (DisplayName): %s already exists."), *Context, *(Entry.DisplayName));
			return;
		}
	#endif // #if !UE_BUILD_SHIPPING

	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Create for Achievement: %s for Player: %s - %s."), *Context, *(Entry.Name), *GetLocalPlayerNickname(), *(UserId.ToString()));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- Name: %s."), *(Entry.Name));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- DisplayName: %s."), *(Entry.DisplayName));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- bValid: %s."), Entry.bValid ? TEXT("True") : TEXT("False"));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- WritePolicy: %s."), EMCsAchievementWritePolicy::Get().ToChar(Entry.WritePolicy));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- ProgressType: %s."), EMCsAchievementProgress::Get().ToChar(Entry.GetProgressType()));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- Count: %d."), Entry.Count);
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- BitfieldLength: %d."), Entry.BitfieldLength);
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- Title: %s."), *(Entry.Title));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- Description: %s."), *(Entry.Description));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- UnlockedDescription: %s."), *(Entry.UnlockedDescription));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- bHidden: %s."), Entry.bHidden ? TEXT("True") : TEXT("False"));
		}
	#endif // #if !UE_BUILD_SHIPPING

		typedef NCsAchievement::EAction ActionType;

		QueueAction(ActionType::Create, Entry);
	}
	// Local
	else
	{

	}
}

#define ActionInfoType NCsAchievement::NAction::NInfo::FInfo
void UCsManager_Achievement::Create_Internal(ActionInfoType* ActionInfo)
{
	UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::Create_Internal: This must be implemented in the derived class."));
	ActionInfo->Complete();
}
#undef ActionInfoType

#pragma endregion Create

// Modify
#pragma region

void UCsManager_Achievement::ModifyAchievement(const FCsAchievementEntry& Entry)
{
	SET_CONTEXT(ModifyAchievement);

	if (!IsEnabled(Context))
		return;

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting Create for Achievement: %s for Player: %s - %s."), *Context, *(Entry.Name), *GetLocalPlayerNickname(), *(UserId.ToString()));
			return;
		}

	#if !UE_BUILD_SHIPPING
		if (!EMCsAchievement::Get().IsValidEnum(FName(*(Entry.Name))))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement (Name): %s has not been added to the Enum Map: EMCsAchievement."), *Context, *(Entry.Name));
			return;
		}

		if (!Entry.DisplayName.IsEmpty() &&
			!EMCsAchievement::Get().IsValidEnumByDisplayName(Entry.DisplayName))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement (DisplayName): %s has not been added to the Enum Map: EMCsAchievement."), *Context, *(Entry.DisplayName));
			return;
		}
	#endif // #if !UE_BUILD_SHIPPING

		const FECsAchievement& Achievement = EMCsAchievement::Get().GetEnum(Entry.Name);

		check(IsValidChecked(Context, Achievement));

	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Modify for Achievement: %s for Player: %s - %s."), *Context, *(Entry.Name), *GetLocalPlayerNickname(), *(UserId.ToString()));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- Name: %s."), *(Entry.Name));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- DisplayName: %s."), *(Entry.DisplayName));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- bValid: %s."), Entry.bValid ? TEXT("True") : TEXT("False"));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- WritePolicy: %s."), EMCsAchievementWritePolicy::Get().ToChar(Entry.WritePolicy));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- ProgressType: %s."), EMCsAchievementProgress::Get().ToChar(Entry.GetProgressType()));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- Count: %d."), Entry.Count);
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- BitfieldLength: %d."), Entry.BitfieldLength);
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- Title: %s."), *(Entry.Title));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- Description: %s."), *(Entry.Description));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- UnlockedDescription: %s."), *(Entry.UnlockedDescription));
			UE_LOG(LogCsPlatformServices, Warning, TEXT("- bHidden: %s."), Entry.bHidden ? TEXT("True") : TEXT("False"));
		}
	#endif // #if !UE_BUILD_SHIPPING

		typedef NCsAchievement::EAction ActionType;

		QueueAction(ActionType::Modify, Achievement, Entry);
	}
	// Local
	else
	{

	}
}

#define ActionInfoType NCsAchievement::NAction::NInfo::FInfo
void UCsManager_Achievement::ModifyAchievement_Internal(ActionInfoType* ActionInfo)
{
	UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::ModifyAchievement_Internal: This must be implemented in the derived class."));
	ActionInfo->Complete();
}
#undef ActionInfoType

#pragma endregion Modify

// Remove
#pragma region

#define ActionType NCsAchievement::EAction
#define ActionInfoType NCsAchievement::NAction::NInfo::FInfo

void UCsManager_Achievement::Remove(const FECsAchievement& Achievement)
{
	SET_CONTEXT(Remove);

	if (!IsEnabled(Context))
		return;

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsAchievement, Achievement)

	checkf(Achievement.GetValue() < Achievements.Num(), TEXT("%s: Achievement: %s of type: ICsAchievement has not been constructed."), *Context, Achievement.ToChar());
	checkf(Achievements[Achievement.GetValue()], TEXT("%s: Achievement: %s of type: ICsAchievement has not been constructed."), *Context, Achievement.ToChar());

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting CompleteAll for Player: %s - %s."), *Context, *GetLocalPlayerNickname(), *(UserId.ToString()));
			return;
		}

		// Queue Remove
	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Remove for Achievement: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		QueueAction(ActionType::Remove, Achievement);
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::Remove_Internal(ActionInfoType* ActionInfo)
{
	UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::Remove_Internal: This must be implemented in the derived class."));
	ActionInfo->Complete();
}

void UCsManager_Achievement::RemoveAll()
{
	SET_CONTEXT(RemoveAll);

	if (!IsEnabled(Context))
		return;
}

void UCsManager_Achievement::RemoveAll_Internal(ActionInfoType* ActionInfo)
{
}

bool UCsManager_Achievement::IsCurrentActionRemoveOrRemoveAll()
{
	ActionInfoType* Head = Manager_Resource.GetAllocatedResourceHead();

	return Head ? (Head->Action == ActionType::Remove || Head->Action == ActionType::RemoveAll) : false;
}

#undef ActionType
#undef ActionInfoType

#pragma endregion Remove

// Write
#pragma region

#define ValueType NCsAchievement::FValue

void UCsManager_Achievement::Write(const FECsAchievement& Achievement, const float& Percent)
{
	ValueType Value;
	Value.SetPercent(Percent);

	Write(Achievement, Value);
}

void UCsManager_Achievement::Write(const FECsAchievement& Achievement, const uint64& Count)
{
	ValueType Value;
	Value.SetCount(Count);

	Write(Achievement, Value);
}

void UCsManager_Achievement::Write(const FECsAchievement& Achievement, const FString& Bitfield)
{
	ValueType Value;
	Value.SetBitfield(Bitfield);

	Write(Achievement, Value);
}

#undef ValueType

#define ValueType NCsAchievement::FValue
void UCsManager_Achievement::Write(const FECsAchievement& Achievement, const ValueType& Value)
{
#undef ValueType

	SET_CONTEXT(Write);

	if (!IsEnabled(Context))
		return;

	check(IsValidChecked(Context, Achievement));

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting Write for Achievement: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *GetLocalPlayerNickname(), *(UserId.ToString()));
			return;
		}

		ICsAchievement* IA = Achievements[Achievement.GetValue()];

		const ProgressType& ProgType = IA->GetProgressType();

		// Queue Write
		typedef NCsAchievement::EValue ValueType;
		typedef NCsAchievement::EAction ActionType;

		const ValueType& ValType = Value.ValueType;

		// Normalized | Standard | Binary
		if (ProgType == ProgressType::Normalized ||
			ProgType == ProgressType::Standard ||
			ProgType == ProgressType::Binary)
		{
			// Float
			if (ValType == ValueType::Float)
			{
				const float Percent = FMath::Clamp(Value.Percent, 0.0f, 1.0f);

			#if !UE_BUILD_SHIPPING
				if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
				{
					UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Reset for Achievement: %s to Percent: %f for Player: %s - %s."), *Context, Achievement.ToChar(), Percent, *GetLocalPlayerNickname(), *(UserId.ToString()));
				}
			#endif // #if !UE_BUILD_SHIPPING

				QueueAction(ActionType::Write, Achievement, Percent);
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s has ProgressType: %s and the ValueType must be Float."), *Context, Achievement.ToChar(), ProgressMapType::Get().ToChar(ProgType));
				return;
			}
		}
		// Count
		else
		if (ProgType == ProgressType::Count)
		{
			if (ValType == ValueType::String)
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s has ProgressType: Count and the ValueType must be Float or Integer."), *Context, Achievement.ToChar());
				return;
			}

			uint64 Count = 0ull;

			// Float
			if (ValType == ValueType::Float)
			{
				const float Percent = FMath::Clamp(Value.Percent, 0.0f, 1.0f);
				Count				= (uint64)FMath::FloorToInt(Percent * IA->GetMaxCount());
			}
			// Integer
			else
			if (ValType == ValueType::Integer)
			{
				Count = CalculateCount(IA, Value.Count);
			}

		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Reset for Achievement: %s to Count: %d for Player: %s - %s."), *Context, Achievement.ToChar(), Count, *GetLocalPlayerNickname(), *(UserId.ToString()));
			}
		#endif // #if !UE_BUILD_SHIPPING

			QueueAction(ActionType::Write, Achievement, Count);
		}
		// Bitfield
		else
		if (ProgType == ProgressType::Bitfield)
		{
			if (ValType == ValueType::Integer)
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s has ProgressType: Bitfield and the ValueType must be Float or String."), *Context, Achievement.ToChar());
				return;
			}

			FString NewBitfield;

			// Float
			if (ValType == ValueType::Float)
			{
				const float Percent = FMath::Clamp(Value.Percent, 0.0f, 1.0f);

				const uint32& BitfieldLength  = IA->GetBitfieldLength();
				const uint32& NumBitsToUnlock = IA->GetUnlockBitfieldLength();

				const uint32 Count		 = (uint64)FMath::FloorToInt(Percent * NumBitsToUnlock);
				const uint32& NumBitsSet = IA->GetNumBitsSet();
				uint32 Delta			 = NumBitsSet >= Count ? NumBitsSet - Count : 0;
			
				const FString& Bitfield = IA->GetBitfield();

				checkf(Bitfield.Len() == BitfieldLength, TEXT("%s: Mismatch between Bitfield.Len() and BitfieldLength (%d != %d)."), *Context, Bitfield.Len(), BitfieldLength);

				NewBitfield.Reset(BitfieldLength);

				for (uint32 I = 0; I < BitfieldLength; ++I)
				{
					NewBitfield += '0';

					if (Delta > 0)
					{
						NewBitfield[I] = '1';
						--Delta;
					}
				}
			}
			// String
			else
			if (ValType == ValueType::Integer)
			{
				NewBitfield = Value.Bitfield;
			}

			if (IsValidBitfield(IA, NewBitfield))
			{
			#if !UE_BUILD_SHIPPING
				if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
				{
					UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Write for Achievement: %s to Bitfield: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *NewBitfield, *GetLocalPlayerNickname(), *(UserId.ToString()));
				}
			#endif // #if !UE_BUILD_SHIPPING

				QueueAction(ActionType::Write, Achievement, NewBitfield);
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Bitfield: %s is NOT a Valid Bitfield for Achievement: %s."), *Context, *NewBitfield, Achievement.ToChar());
				return;
			}
		}

	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Query Descriptions for Player: %s - %s."), *Context, *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		QueryState.Descriptions.Queue();
		QueueAction(ActionType::QueryDescriptions);
	}
	// Local
	else
	{

	}
}

#define ActionInfoType NCsAchievement::NAction::NInfo::FInfo
void UCsManager_Achievement::Write_Internal(ActionInfoType* ActionInfo)
{
#undef ActionInfoType

	SET_CONTEXT(Write_Internal);

	const FECsAchievement& Achievement = ActionInfo->Achievement;
	ICsAchievement* IA				   = Achievements[Achievement.GetValue()];

	bool HasValueChanged = false;

	const ProgressType& ProgType = IA->GetProgressType();

	FString NoChangeSnippet;
	FString ChangeSnippet;

	// Normalized | Standard | Binary
	const float& Percent		= ActionInfo->Value.Percent;
	const float CurrentProgress = IA->GetProgress();
	const float NewProgress		= IA->CalculateProgress(Percent);
	// Count
	const uint64& CurrentCount = IA->GetCount();
	const uint64& CountToWrite = ActionInfo->Value.Count;
	// Bitfield
	const FString& Bitfield = IA->GetBitfield();
	FString& NewBitfield	= ActionInfo->Value.Bitfield;

	// Online
	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();

	typedef NCsAchievement::EAction ActionType;

	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Normalized | Standard | Binary
		if (ProgType == ProgressType::Normalized ||
			ProgType == ProgressType::Standard ||
			ProgType == ProgressType::Binary)
		{
			HasValueChanged = CurrentProgress != NewProgress;

			// No value change
			if (!HasValueChanged)
			{
				NoChangeSnippet = FString::Printf(TEXT("Progress: %f"), Percent);
			}
			else
			{
				ChangeSnippet = FString::Printf(TEXT("Progress from %f to %f"), CurrentProgress, NewProgress);
			}
		}
		// Count
		else
		if (ProgType == ProgressType::Count)
		{
			const uint64 NewCount = bCountAsAdd ? CurrentCount + CountToWrite : CountToWrite;
			HasValueChanged		  = CurrentCount != NewCount;

			// No value change
			if (!HasValueChanged)
			{
				NoChangeSnippet = FString::Printf(TEXT("Count: %d"), NewCount);
			}
			else
			{
				ChangeSnippet = FString::Printf(TEXT("Count from %d to %d (%d)"), CurrentCount, NewCount, CsMathLibrary::GetAbsDelta(NewCount, CurrentCount));
			}
		}
		// Bitfield
		else
		if (ProgType == ProgressType::Bitfield)
		{
			const uint32& BitfieldLength = IA->GetBitfieldLength();

			checkf(Bitfield.Len() == BitfieldLength, TEXT("%s: Mismatch between Bitfield.Len() and BitfieldLength (%d != %d)."), *Context, Bitfield.Len(), BitfieldLength);
			checkf(NewBitfield.Len() == BitfieldLength, TEXT("%s: Mismatch between NewBitfield.Len() and BitfieldLength (%d != %d)."), *Context, NewBitfield.Len(), BitfieldLength);

			FString BitMask;
			FString BitfieldOrBitMask;

			BitMask.Reset(BitfieldLength);
			BitfieldOrBitMask.Reset(BitfieldLength);

			uint32 AdditionalBitsSet = 0;

			for (uint32 I = 0; I < BitfieldLength; ++I)
			{
				BitMask			  += Bitfield[I] == '0' && NewBitfield[I] == '1' ? '1' : '0';
				BitfieldOrBitMask += Bitfield[I] == '1' || NewBitfield[I] == '1' ? '1' : '0';

				if (BitMask[I] == '1')
					++AdditionalBitsSet;

				HasValueChanged |= BitMask[I] == '1';
			}

			NewBitfield = bBitfieldAsOr ? BitMask : BitfieldOrBitMask;

			// No value change
			if (!HasValueChanged)
			{
				NoChangeSnippet = FString::Printf(TEXT("Bitfield: %s"), *Bitfield);
			}
			else
			{
				ChangeSnippet = FString::Printf(TEXT("Bitfield from %s to %s (%s - %d bits set)"), *Bitfield, *BitfieldOrBitMask, *BitMask, AdditionalBitsSet);
			}
		}

		// No value change
		if (!HasValueChanged)
		{
		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s already set %s."), *Context, Achievement.ToChar(), *NoChangeSnippet);
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
					UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s is NOT Valid. Make sure both QueryAchievements and QueryAchievementDescriptions have been called."), *Context, Achievement.ToChar());

					ActionInfo->Complete();
				}
				else
				{
					CurrentAchievementWritten = Achievement;

					WriteObject = MakeShareable(new FOnlineAchievementsWrite());

					// Normalized | Standard | Binary
					if (ProgType == ProgressType::Normalized ||
						ProgType == ProgressType::Standard ||
						ProgType == ProgressType::Binary)
					{
						WriteObject->SetFloatStat(Achievement.GetFName(), NewProgress);
					}
					// Count
					else
					if (ProgType == ProgressType::Count)
					{
						WriteObject->SetIntStat(Achievement.GetFName(), CountToWrite);
					}
					// Bitfield
					else
					if (ProgType == ProgressType::Bitfield)
					{
						FVariantData& Data = WriteObject->Properties.Add(Achievement.GetFName());
						Data.SetValue(NewBitfield);
					}

					FOnlineAchievementsWriteRef WriteObjectRef = WriteObject.ToSharedRef();

				#if !UE_BUILD_SHIPPING
					if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
					{
						UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Starting Update Achievement: %s %s."), *Context, Achievement.ToChar(), *ChangeSnippet);
					}
				#endif // #if !UE_BUILD_SHIPPING

					IAchievements->WriteAchievements(UserId, WriteObjectRef, FOnAchievementsWrittenDelegate::CreateUObject(this, &UCsManager_Achievement::OnAchievementsWritten));
				}
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting Write for Achievement: %s %s for Player: %s - %s."), *Context, Achievement.ToChar(), *ChangeSnippet, *GetLocalPlayerNickname(), *(UserId.ToString()));
			}
		}
		// Queue Write
		else
		{
		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Update Achievement: %s %s."), *Context, Achievement.ToChar(), *ChangeSnippet);
			}
		#endif // #if !UE_BUILD_SHIPPING

			// Normalized | Standard | Binary
			if (ProgType == ProgressType::Normalized ||
				ProgType == ProgressType::Standard ||
				ProgType == ProgressType::Binary)
			{
				QueueAction(ActionType::Write, Achievement, Percent);
			}
			// Count
			else
			if (ProgType == ProgressType::Count)
			{
				QueueAction(ActionType::Write, Achievement, CountToWrite);
			}
			// Bitfield
			else
			if (ProgType == ProgressType::Bitfield)
			{
				QueueAction(ActionType::Write, Achievement, NewBitfield);
			}
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
			SetProgress(IA, NewProgress / MaxProgress);

			CalculateTotalProgress();

		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Updated Achievement: %s Progress from %f to %f."), *Context, Achievement.ToChar(), CurrentProgress, NewProgress);
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
			
			CalculateTotalProgress();

		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Completed Achievement: %s."), *Context, Achievement.ToChar());
			}
		#endif // #if !UE_BUILD_SHIPPING

			OnComplete_Event.Broadcast(true, IA);
			OnComplete_ScriptEvent.Broadcast(true, Achievement);
		}
	}
}

#undef ValueType

#pragma endregion Write

// Complete
#pragma region

void UCsManager_Achievement::Complete(const FECsAchievement& Achievement)
{
	SET_CONTEXT(Complete);

	if (!IsEnabled(Context))
		return;

	check(IsValidChecked(Context, Achievement));

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting Complete for Achievement: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *GetLocalPlayerNickname(), *(UserId.ToString()));
			return;
		}

		// Queue Complete
	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Complete for Achievement: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		ICsAchievement* IA = Achievements[Achievement.GetValue()];

		const ProgressType& ProgType = IA->GetProgressType();

		typedef NCsAchievement::EAction ActionType;

		// Normalized | Standard | Binary
		if (ProgType == ProgressType::Normalized ||
			ProgType == ProgressType::Standard ||
			ProgType == ProgressType::Binary)
		{
			QueueAction(ActionType::Complete, Achievement, 1.0f);
		}
		// Count
		else
		if (ProgType == ProgressType::Count)
		{
			QueueAction(ActionType::Complete, Achievement, IA->GetMaxCount());
		}
		// Bitfield
		else
		if (ProgType == ProgressType::Bitfield)
		{
			QueueAction(ActionType::Complete, Achievement, IA->GetBitMaskComplete());
		}

		// Queue Query Descriptions
	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Query Descriptions for Player: %s - %s."), *Context, *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		QueryState.Descriptions.Queue();
		QueueAction(ActionType::QueryDescriptions);
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::SafeComplete(const FECsAchievement& Achievement)
{
	SET_CONTEXT(SafeComplete);

	if (IsValid(Context, Achievement) &&
		!IsCompleted(Achievement))
	{
		Complete(Achievement);
	}
}

#define ActionInfoType NCsAchievement::NAction::NInfo::FInfo
void UCsManager_Achievement::Complete_Internal(ActionInfoType* ActionInfo)
{
#undef ActionInfoType
	SET_CONTEXT(Complete_Internal);

	const FECsAchievement& Achievement = ActionInfo->Achievement;
	ICsAchievement* IA				   = Achievements[Achievement.GetValue()];

	bool HasValueChanged = false;

	const ProgressType& ProgType = IA->GetProgressType();

	// Normalized | Standard | Binary
	if (ProgType == ProgressType::Normalized ||
		ProgType == ProgressType::Standard ||
		ProgType == ProgressType::Binary)
	{
		const float& Percent		= ActionInfo->Value.Percent;
		const float CurrentProgress = IA->GetProgress();
		const float NewProgress		= IA->CalculateProgress(Percent);

		HasValueChanged = CurrentProgress != NewProgress;
	}
	// Count
	else
	if (ProgType == ProgressType::Count)
	{
		const uint64& CurrentCount = IA->GetCount();
		const uint64& CountToWrite = ActionInfo->Value.Count;
		const uint64 NewCount	   = bCountAsAdd ? CurrentCount + CountToWrite : CountToWrite;

		HasValueChanged = CurrentCount != NewCount;
	}
	// Bitfield
	else
	if (ProgType == ProgressType::Bitfield)
	{
		const FString& Bitfield	= IA->GetBitfield();
		FString& NewBitfield	= ActionInfo->Value.Bitfield;

		FString BitMask;
		FString BitfieldOrBitMask;

		const int32 Len = Bitfield.Len();			

		BitMask.Reset(Len);

		for (int32 I = 0; I < Len; ++I)
		{
			BitMask			  += Bitfield[I] == '0' && NewBitfield[I] == '1' ? '1' : '0';
			BitfieldOrBitMask += Bitfield[I] == '1' || NewBitfield[I] == '1' ? '1' : '0';

			HasValueChanged |= BitMask[I] == '1';
		}

		NewBitfield = BitfieldOrBitMask;
	}

	// No value change
	if (!HasValueChanged)
	{
		// Online
		IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();

		if (IAchievements.IsValid())
		{
			const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s already Complete for Player: %s - %s."), *Context, Achievement.ToChar(), *GetLocalPlayerNickname(), *(UserId.ToString()));
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
			if (!IA->IsValid())
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s is NOT Valid. Make sure both QueryAchievements and QueryAchievementDescriptions have been called."), *Context, Achievement.ToChar());

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

				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting Reset for Achievement: %s for Player: %s."), *Context, Achievement.ToChar(), *(UserId.ToString()));
			}

			ActionInfo->Complete();
		}
	}
}

bool UCsManager_Achievement::IsCompleted(const FECsAchievement& Achievement)
{
	SET_CONTEXT(IsCompleted);

	check(IsValidChecked(Context, Achievement));

	typedef NCsAchievement::EState StateType;

	return Achievements[Achievement.GetValue()]->GetState() == StateType::Completed;
}

bool UCsManager_Achievement::IsSafeCompleted(const FECsAchievement& Achievement)
{
	SET_CONTEXT(IsSafeCompleted);

	if (IsValid(Context, Achievement))
	{
		return IsCompleted(Achievement);
	}
	return false;
}

const int32& UCsManager_Achievement::GetNumCompleted()
{
	return NumCompleted;
}

void UCsManager_Achievement::CompleteAll()
{
	SET_CONTEXT(CompleteAll);

	if (!IsEnabled(Context))
		return;

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting CompleteAll for Player: %s - %s."), *Context, *GetLocalPlayerNickname(), *(UserId.ToString()));
			return;
		}

		// Queue Complete All
	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing CompleteAll for Player: %s - %s."), *Context, *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		typedef NCsAchievement::EAction ActionType;

		QueueAction(ActionType::CompleteAll);
	}
	// Local
	else
	{

	}
}

#define ActionInfoType NCsAchievement::NAction::NInfo::FInfo
void UCsManager_Achievement::CompleteAll_Internal(ActionInfoType* ActionInfo)
{
	SET_CONTEXT(CompleteAll_Internal);

	typedef NCsAchievement::NAction::NInfo::FResource ActionInfoContainerType;

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Queue Complete for Achievements

	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Starting CompleteAll for Player: %s - %s."), *Context, *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		TCsDoubleLinkedList<ActionInfoContainerType*>* Current = Manager_Resource.GetAllocatedHead();
		ActionInfoContainerType* InfoContainer				   = **Current;

		for (ICsAchievement* IA : Achievements)
		{
			if (!IA->IsValid())
				continue;

			ActionInfoContainerType* CompleteInfoContainer = Manager_Resource.AllocateAfter(InfoContainer);
			ActionInfoType* CompleteInfo				   = CompleteInfoContainer->Get();

			CompleteInfo->Reset();

			const FECsAchievement& Achievement = IA->GetType();

			CompleteInfo->Achievement = Achievement;

			typedef NCsAchievement::EAction ActionType;

			CompleteInfo->Action = ActionType::Complete;

			const ProgressType& ProgType = IA->GetProgressType();

			// Normalized | Standard | Binary
			if (ProgType == ProgressType::Normalized ||
				ProgType == ProgressType::Standard ||
				ProgType == ProgressType::Binary)
			{
				CompleteInfo->Value.SetPercent(1.0f);
			}
			// Count
			else
			if (ProgType == ProgressType::Count)
			{
				CompleteInfo->Value.SetCount(IA->GetMaxCount());
			}
			// Bitfield
			else
			if (ProgType == ProgressType::Bitfield)
			{
				const uint32& Length = IA->GetBitfieldLength();
				FString Bitfield	 = TEXT("");

				for (uint32 I = 0; I < Length; ++I)
				{
					Bitfield += '1';
				}
				CompleteInfo->Value.SetBitfield(Bitfield);
			}
			
			// Update InfoContainer so actions get queued in order
			InfoContainer = CompleteInfoContainer;

		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Complete for Achievement: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *GetLocalPlayerNickname(), *(UserId.ToString()));
			}
		#endif // #if !UE_BUILD_SHIPPING
		}

		// Queue Complete All event at end
		ActionInfoContainerType* CompleteAllInfoContainer = Manager_Resource.AllocateAfter(InfoContainer);
		ActionInfoType* CompleteAllInfo					  = CompleteAllInfoContainer->Get();

		CompleteAllInfo->Reset();

		typedef NCsAchievement::EAction ActionType;

		CompleteAllInfo->Action = ActionType::CompleteAll;
		CompleteAllInfo->Complete();

		InfoContainer = CompleteAllInfoContainer;

		// Queue Query Descriptions
		ActionInfoContainerType* QueryDescriptionsInfoContainer = Manager_Resource.AllocateAfter(InfoContainer);
		ActionInfoType* QueryDescriptionsInfo					= QueryDescriptionsInfoContainer->Get();

		QueryDescriptionsInfo->Reset();

		QueryDescriptionsInfo->Action = ActionType::QueryDescriptions;

	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing QueryDescriptions for Player: %s - %s."), *Context, *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING
	}
	// Local
	else
	{

	}
}
#undef ActionInfoType

#pragma endregion Complete

// Reset
#pragma region

#define ValueType NCsAchievement::FValue

void UCsManager_Achievement::Reset(const FECsAchievement& Achievement, const float& Percent)
{
	ICsAchievement* IA = Achievements[Achievement.GetValue()];

	const ProgressType& ProgType = IA->GetProgressType();

	ValueType Value;
	Value.SetPercent(Percent);
	Reset(Achievement, Value);
}

void UCsManager_Achievement::Reset(const FECsAchievement& Achievement, const uint64& Count)
{
	ValueType Value;
	Value.SetCount(Count);

	Reset(Achievement, Value);
}

void UCsManager_Achievement::Reset(const FECsAchievement& Achievement, const FString& Bitfield)
{
	ValueType Value;
	Value.SetBitfield(Bitfield);

	Reset(Achievement, Value);
}

#undef ValueType

#define ValueType NCsAchievement::FValue
void UCsManager_Achievement::Reset(const FECsAchievement& Achievement, const ValueType& Value)
{
#undef ValueType
	SET_CONTEXT(Reset);

	if (!IsEnabled(Context))
		return;

	check(IsValidChecked(Context, Achievement));

	typedef NCsAchievement::EAction ActionType;

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting Reset for Achievement: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *GetLocalPlayerNickname(), *(UserId.ToString()));
			return;
		}

		ICsAchievement* IA = Achievements[Achievement.GetValue()];

		const ProgressType& ProgType = IA->GetProgressType();

		// Queue Reset
		typedef NCsAchievement::EValue ValueType;

		const ValueType& ValType = Value.ValueType;

		// Normalized | Standard | Binary
		if (ProgType == ProgressType::Normalized ||
			ProgType == ProgressType::Standard ||
			ProgType == ProgressType::Binary)
		{
			// Float
			if (ValType == ValueType::Float)
			{
				const float Percent = FMath::Clamp(Value.Percent, 0.0f, 1.0f);

			#if !UE_BUILD_SHIPPING
				if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
				{
					UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Reset for Achievement: %s to Percent: %f for Player: %s - %s."), *Context, Achievement.ToChar(), Percent, *GetLocalPlayerNickname(), *(UserId.ToString()));
				}
			#endif // #if !UE_BUILD_SHIPPING

				QueueAction(bResetAsResetAll ? ActionType::ResetAll : ActionType::Reset, Achievement, Percent);
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s has ProgressType: %s and the ValueType must be Float."), *Context, Achievement.ToChar(), ProgressMapType::Get().ToChar(ProgType));
				return;
			}
		}
		// Count
		else
		if (ProgType == ProgressType::Count)
		{
			if (ValType == ValueType::String)
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s has ProgressType: Count and the ValueType must be Float or Integer."), *Context, Achievement.ToChar());
				return;
			}

			uint64 Count = 0ull;

			// Float
			if (ValType == ValueType::Float)
			{
				const float Percent = FMath::Clamp(Value.Percent, 0.0f, 1.0f);
				Count				= (uint64)FMath::FloorToInt(Percent * IA->GetMaxCount());
			}
			// Integer
			else
			if (ValType == ValueType::Integer)
			{
				Count = CalculateCount(IA, Value.Count);
			}

		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Reset for Achievement: %s to Count: %d for Player: %s - %s."), *Context, Achievement.ToChar(), Count, *GetLocalPlayerNickname(), *(UserId.ToString()));
			}
		#endif // #if !UE_BUILD_SHIPPING

			QueueAction(bResetAsResetAll ? ActionType::ResetAll : ActionType::Reset, Achievement, Count);
		}
		// Bitfield
		else
		if (ProgType == ProgressType::Bitfield)
		{
			if (ValType == ValueType::Integer)
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s has ProgressType: Bitfield and the ValueType must be Float or String."), *Context, Achievement.ToChar());
				return;
			}

			FString NewBitfield;

			// Float
			if (ValType == ValueType::Float)
			{
				const float Percent = FMath::Clamp(Value.Percent, 0.0f, 1.0f);

				const uint32& BitfieldLength  = IA->GetBitfieldLength();
				const uint32& NumBitsToUnlock = IA->GetUnlockBitfieldLength();

				uint32 NewNumBitsSet = (uint64)FMath::FloorToInt(Percent * NumBitsToUnlock);
			
				const FString& Bitfield = IA->GetBitfield();

				checkf(Bitfield.Len() == BitfieldLength, TEXT("%s: Mismatch between Bitfield.Len() and BitfieldLength (%d != %d)."), *Context, Bitfield.Len(), BitfieldLength);

				NewBitfield.Reset(BitfieldLength);

				for (uint32 I = 0; I < BitfieldLength; ++I)
				{
					NewBitfield += '0';

					if (NewNumBitsSet > 0)
					{
						NewBitfield[I] = '1';
						--NewNumBitsSet;
					}
				}
			}
			// String
			else
			if (ValType == ValueType::Integer)
			{
				NewBitfield = Value.Bitfield;
			}

			if (IsValidBitfield(IA, NewBitfield))
			{
			#if !UE_BUILD_SHIPPING
				if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
				{
					UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Reset for Achievement: %s to Bitfield: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *NewBitfield, *GetLocalPlayerNickname(), *(UserId.ToString()));
				}
			#endif // #if !UE_BUILD_SHIPPING

				QueueAction(bResetAsResetAll ? ActionType::ResetAll : ActionType::Reset, Achievement, NewBitfield);
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Bitfield: %s is NOT a Valid Bitfield for Achievement: %s."), *Context, *NewBitfield, Achievement.ToChar());
				return;
			}
		}

		if (!bResetAsResetAll)
		{
		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Query Descriptions for Player: %s - %s."), *Context, *GetLocalPlayerNickname(), *(UserId.ToString()));
			}
		#endif // #if !UE_BUILD_SHIPPING

			QueryState.Descriptions.Queue();
			QueueAction(ActionType::QueryDescriptions);
		}
	}
	// Local
	else
	{

	}
}

#define ValueType NCsAchievement::FValue
void UCsManager_Achievement::SafeReset(const FECsAchievement& Achievement, const ValueType& Value)
{
#undef ValueType
	SET_CONTEXT(SafeReset);

	if (IsValid(Context, Achievement))
	{
		ICsAchievement* IA = Achievements[Achievement.GetValue()];

		bool Pass = false;

		typedef NCsAchievement::EValue ValueType;

		// Percent
		if (Value.ValueType == ValueType::Float)
		{
			Pass = IA->GetProgressAsPercent() != Value.Percent;
		}
		// Count
		else
		if (Value.ValueType == ValueType::Integer)
		{
			if (SupportsSafeCount(Context, Achievement))
			{
				Pass = IA->GetCount() != Value.Count;
			}
		}
		// Bitfield
		else
		if (Value.ValueType == ValueType::String)
		{
			if (SupportsSafeBitfield(Context, Achievement))
			{
				Pass = IA->GetBitfield() != Value.Bitfield;
			}
		}

		if (Pass)
		{
			Reset(Achievement, Value);
		}
	}
}

#define ActionInfoType NCsAchievement::NAction::NInfo::FInfo
void UCsManager_Achievement::Reset_Internal(ActionInfoType* ActionInfo)
{
#undef ActionInfoType
	SET_CONTEXT(Reset_Internal);

	const FECsAchievement& Achievement = ActionInfo->Achievement;
	ICsAchievement* IA				   = Achievements[Achievement.GetValue()];

	bool HasValueChanged = false;

	const ProgressType& ProgType = IA->GetProgressType();

	FString Snippet;

	// Normalized | Standard | Binary
	if (ProgType == ProgressType::Normalized ||
		ProgType == ProgressType::Standard ||
		ProgType == ProgressType::Binary)
	{
		const float& Percent		= ActionInfo->Value.Percent;
		const float CurrentProgress = IA->GetProgress();
		const float NewProgress		= IA->CalculateProgress(Percent);

		HasValueChanged = CurrentProgress != NewProgress;

		Snippet = FString::Printf(TEXT("Progress: %f"), NewProgress);
	}
	// Count
	else
	if (ProgType == ProgressType::Count)
	{
		const uint64& CurrentCount  = IA->GetCount();
		const uint64& CountToWrite  = ActionInfo->Value.Count;
		// bCountAsAdd == true DOES NOT work, so set the value to 0.
		const uint64 NewCount		= bCountAsAdd ? 0 : CountToWrite;

		HasValueChanged = CurrentCount != NewCount;

		Snippet = FString::Printf(TEXT("Count: %d"), NewCount);
	}
	// Bitfield
	else
	if (ProgType == ProgressType::Bitfield)
	{
		const FString& Bitfield	= IA->GetBitfield();
		FString& NewBitfield	= ActionInfo->Value.Bitfield;

		const uint32& BitfieldLength = IA->GetBitfieldLength();

		checkf(Bitfield.Len() == BitfieldLength, TEXT("%s: Mismatch between Bitfield.Len() and BitfieldLength (%d != %d)."), *Context, Bitfield.Len(), BitfieldLength);
		checkf(NewBitfield.Len() == BitfieldLength, TEXT("%s: Mismatch between NewBitfield.Len() and BitfieldLength (%d != %d)."), *Context, NewBitfield.Len(), BitfieldLength);

		FString BitMask;
		FString BitfieldOrBitMask;

		BitMask.Reset(BitfieldLength);
		BitfieldOrBitMask.Reset(BitfieldLength);

		uint32 AdditionalBitsSet = 0;

		for (uint32 I = 0; I < BitfieldLength; ++I)
		{
			BitMask			  += Bitfield[I] == '0' && NewBitfield[I] == '1' ? '1' : '0';
			BitfieldOrBitMask += Bitfield[I] == '1' || NewBitfield[I] == '1' ? '1' : '0';

			if (BitMask[I] == '1')
				++AdditionalBitsSet;

			HasValueChanged |= BitMask[I] == '1';
		}

		NewBitfield = bBitfieldAsOr ? BitMask : BitfieldOrBitMask;

		Snippet = FString::Printf(TEXT("Bitfield from %s to %s (%s - %d bits set)"), *Bitfield, *BitfieldOrBitMask, *BitMask, AdditionalBitsSet);
	}

	if (!HasValueChanged)
	{
		// Online
		IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();

		if (IAchievements.IsValid())
		{
			const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s already set to %s for Player: %s - %s."), *Context, Achievement.ToChar(), *Snippet, *GetLocalPlayerNickname(), *(UserId.ToString()));
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
			if (!IA->IsValid())
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s is NOT Valid. Make sure both QueryAchievements and QueryAchievementDescriptions have been called."), *Context, Achievement.ToChar());

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

				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting Reset for Achievement: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *GetLocalPlayerNickname(), *(UserId.ToString()));
			}

			ActionInfo->Complete();
		}
	}
}

void UCsManager_Achievement::ResetAll()
{
	SET_CONTEXT(ResetAll);

	if (!IsEnabled(Context))
		return;

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting ResetAll for Player: %s - %s."), *Context, *GetLocalPlayerNickname(), *(UserId.ToString()));
			return;
		}

		// Queue Reset All
	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing ResetAll for Player: %s - %s."), *Context, *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		typedef NCsAchievement::EAction ActionType;

		QueueAction(ActionType::ResetAll);
	}
	// Local
	else
	{

	}
}

#define ActionInfoType NCsAchievement::NAction::NInfo::FInfo
void UCsManager_Achievement::ResetAll_Internal(ActionInfoType* ActionInfo)
{
	SET_CONTEXT(ResetAll_Internal);

	typedef NCsAchievement::NAction::NInfo::FResource ActionInfoContainerType;

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		// Queue Reset All for Achievements

	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Starting ResetAll for Player: %s - %s."), *Context, *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		TCsDoubleLinkedList<ActionInfoContainerType*>* Current = Manager_Resource.GetAllocatedHead();
		ActionInfoContainerType* InfoContainer				   = **Current;

		for (ICsAchievement* IA : Achievements)
		{
			if (!IA->IsValid())
				continue;

			ActionInfoContainerType* ResetInfoContainer = Manager_Resource.AllocateAfter(InfoContainer);
			ActionInfoType* ResetInfo					= ResetInfoContainer->Get();

			ResetInfo->Reset();

			const FECsAchievement& Achievement = IA->GetType();

			ResetInfo->Achievement = Achievement;

			typedef NCsAchievement::EAction ActionType;

			ResetInfo->Action = ActionType::Reset;

			const ProgressType& ProgType = IA->GetProgressType();

			// Normalized | Standard | Binary
			if (ProgType == ProgressType::Normalized ||
				ProgType == ProgressType::Standard ||
				ProgType == ProgressType::Binary)
			{
				ResetInfo->Value.SetPercent(0.0f);
			}
			// Count
			else
			if (ProgType == ProgressType::Count)
			{
				ResetInfo->Value.SetCount(0ull);
			}
			// Bitfield
			else
			if (ProgType == ProgressType::Bitfield)
			{
				ResetInfo->Value.SetBitfield(IA->GetBitMaskNone());
			}

			// Update InfoContainer so actions get queued in order
			InfoContainer = ResetInfoContainer;

		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Reset for Achievement: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *GetLocalPlayerNickname(), *(UserId.ToString()));
			}
		#endif // #if !UE_BUILD_SHIPPING
		}

		// Queue Reset All event at end
		ActionInfoContainerType* ResetAllInfoContainer = Manager_Resource.AllocateAfter(InfoContainer);
		ActionInfoType* ResetAllInfo				   = ResetAllInfoContainer->Get();

		ResetAllInfo->Reset();

		typedef NCsAchievement::EAction ActionType;

		ResetAllInfo->Action = ActionType::ResetAll;
		ResetAllInfo->Complete();

		InfoContainer = ResetAllInfoContainer;

		// Queue Query Descriptions
		ActionInfoContainerType* QueryDescriptionsInfoContainer = Manager_Resource.AllocateAfter(InfoContainer);
		ActionInfoType* QueryDescriptionsInfo					= QueryDescriptionsInfoContainer->Get();

		QueryDescriptionsInfo->Reset();

		QueryDescriptionsInfo->Action = ActionType::QueryDescriptions;

	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing QueryDescriptions for Player: %s - %s."), *Context, *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		ActionInfo->Complete();
	}
	// Local
	else
	{

	}
}
#undef ActionInfoType

#pragma endregion Reset

// Progress
#pragma region

void UCsManager_Achievement::SetProgress(const FECsAchievement& Achievement, const float& Percent)
{
	SET_CONTEXT(SetProgress);

	if (!IsEnabled(Context))
		return;

	check(IsValidChecked(Context, Achievement));

	checkf(Percent >= 0.0f && Percent <= 1.0f, TEXT("%s: Percent: %f must be a value between [0, 1] inclusive."), *Context, Percent);

	ICsAchievement* IA = Achievements[Achievement.GetValue()];

	const ProgressType& ProgType = IA->GetProgressType();

	const float CurrentProgress = IA->GetProgress();
	const float NewProgress		= IA->CalculateProgress(Percent);

	typedef NCsAchievement::EAction ActionType;

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting Reset for Achievement: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *GetLocalPlayerNickname(), *(UserId.ToString()));
			return;
		}

		bool QueueReset = bOnlyForwardProgress && NewProgress < CurrentProgress;

		FString Snippet;

		// Normalized | Standard | Binary
		if (ProgType == ProgressType::Normalized ||
			ProgType == ProgressType::Standard ||
			ProgType == ProgressType::Binary)
		{
			// Queue Reset
			if (QueueReset)
				QueueAction(ActionType::Reset, Achievement, 0.0f);
			// Queue Write
			Snippet = FString::Printf(TEXT("Percent: %f"), Percent);

			QueueAction(ActionType::Write, Achievement, Percent);
		}
		// Count
		else
		if (ProgType == ProgressType::Count)
		{
			// Queue Reset
			if (QueueReset)
				QueueAction(ActionType::Reset, Achievement, 0ull);
			// Queue Write
			const uint64 NewCount = (uint64)FMath::FloorToInt(Percent * IA->GetMaxCount());
			Snippet				  = FString::Printf(TEXT("Count: %d"), NewCount);

			QueueAction(ActionType::Write, Achievement, NewCount);
		}
		// Bitfield
		else
		if (ProgType == ProgressType::Bitfield)
		{
			// Queue Reset
			if (QueueReset)
				QueueAction(ActionType::Reset, Achievement, IA->GetBitMaskNone());
			// Queue Write
			const uint32& BitfieldLength  = IA->GetBitfieldLength();
			const uint32& NumBitsToUnlock = IA->GetUnlockBitfieldLength();

			uint32 NewNumBitsSet = (uint64)FMath::FloorToInt(Percent * NumBitsToUnlock);
			uint32 NumBitsSet	 = IA->GetNumBitsSet();
			
			const FString& Bitfield = IA->GetBitfield();

			checkf(Bitfield.Len() == BitfieldLength, TEXT("%s: Mismatch between Bitfield.Len() and BitfieldLength (%d != %d)."), *Context, Bitfield.Len(), BitfieldLength);

			FString NewBitfield;

			NewBitfield.Reset(BitfieldLength);

			for (uint32 I = 0; I < BitfieldLength; ++I)
			{
				NewBitfield += '0';

				if (NewNumBitsSet > 0)
				{
					if (NumBitsSet > 0)
					{
						if (Bitfield[I] == '1')
						{
							NewBitfield[I] = '1';

							--NumBitsSet;
							--NewNumBitsSet;
						}
					}
					else
					{
						NewBitfield[I] = '1';
						--NewNumBitsSet;
					}
				}
			}

			Snippet = FString::Printf(TEXT("Bitfield: %s"), *NewBitfield);

			QueueAction(ActionType::Write, Achievement, NewBitfield);
		}

	#if !UE_BUILD_SHIPPING
		// Queue Reset
		if (QueueReset &&
			CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Reset for Achievement: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *GetLocalPlayerNickname(), *(UserId.ToString()));
		}

		// Queue Write
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Write for Achievement: %s to %s for Player: %s - %s."), *Context, Achievement.ToChar(), *Snippet, *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		// Queue Query Descriptions
	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Query Descriptions for Player: %s - %s."), *Context, *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		QueryState.Descriptions.Queue();
		QueueAction(ActionType::QueryDescriptions);
	}
	// Local
	else
	{

	}
}

void UCsManager_Achievement::SetSafeProgress(const FECsAchievement& Achievement, const float& Percent)
{
	SET_CONTEXT(SetSafeProgress);

	if (Percent < 0.0f || Percent > 1.0f)
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Percent: %f must be a value between [0, 1] inclusive."), *Context, Percent);
		return;
	}

	if (IsValid(Context, Achievement))
	{
		ICsAchievement* IA = Achievements[Achievement.GetValue()];

		if (IA->GetProgressAsPercent() != Percent)
		{
			SetProgress(Achievement, Percent);
		}
	}
}

float UCsManager_Achievement::GetProgress(const FECsAchievement& Achievement)
{
	SET_CONTEXT(GetProgress);

	check(IsValidChecked(Context, Achievement));

	return Achievements[Achievement.GetValue()]->GetProgress();
}

float UCsManager_Achievement::GetSafeProgress(const FECsAchievement& Achievement)
{
	SET_CONTEXT(GetSafeProgress);

	if (IsValid(Context, Achievement))
	{
		return GetProgress(Achievement);
	}
	return 0.0f;
}

float UCsManager_Achievement::GetProgressAsPercent(const FECsAchievement& Achievement)
{
	SET_CONTEXT(GetProgressAsPercent);

	check(IsValidChecked(Context, Achievement));

	return Achievements[Achievement.GetValue()]->GetProgressAsPercent();
}

float UCsManager_Achievement::GetSafeProgressAsPercent(const FECsAchievement& Achievement)
{
	SET_CONTEXT(GetSafeProgressAsPercent);

	if (IsValid(Context, Achievement))
	{
		return GetProgressAsPercent(Achievement);
	}
	return 0.0f;
}

void UCsManager_Achievement::CalculateTotalProgress()
{
	int32 Count = 0;
	NumCompleted = 0;

	typedef NCsAchievement::EState StateType;

	for (const FECsAchievement& Achievement : EMCsAchievement::Get())
	{
		ICsAchievement* IA = Achievements[Achievement.GetValue()];

		if (!IA->IsValid())
			continue;

		++Count;

		if (IA->GetState() != StateType::Completed)
			continue;

		++NumCompleted;
	}

	TotalProgress = Count > 0 ? (float)NumCompleted / (float)Count : 0.0f;
}

const float& UCsManager_Achievement::GetTotalProgress()
{
	return TotalProgress;
}

#pragma endregion Progress

// Count
#pragma region

void UCsManager_Achievement::Increment(const FECsAchievement& Achievement, const uint64& Count /*=1*/)
{
	SET_CONTEXT(Increment);

	if (!IsEnabled(Context))
		return;

	if (!IsValidChecked(Context, Achievement))
		return;

	ICsAchievement* IA = Achievements[Achievement.GetValue()];

	const ProgressType& ProgType = IA->GetProgressType();

	checkf(SupportsCount(Achievement), TEXT("%s: Achievement: %s ProgressType: %s does NOT support Count."), *Context, Achievement.ToChar(), ProgressMapType::Get().ToChar(ProgType));

	if (Count == 0)
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Count is 0."), *Context);
		return;
	}

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting Reset for Achievement: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *GetLocalPlayerNickname(), *(UserId.ToString()));
			return;
		}

		if (ProgType != ProgressType::Count)
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s is NOT ProgressType: Count (currently = %s)."), *Context, Achievement.ToChar(), ProgressMapType::Get().ToChar(ProgType));
			return;
		}

		// Queue Write
		const int32& CurrentCount = IA->GetCount();
		const uint64 NewCount	  = CalculateCount(IA, CurrentCount + Count);
		const uint64 CountToWrite = bCountAsAdd ? NewCount - CurrentCount : NewCount;

	#if !UE_BUILD_SHIPPING
		// Queue Write
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			FString Snippet = bCountAsAdd ? FString::Printf(TEXT("Count: %d (as add)"), CountToWrite): FString::Printf(TEXT("Count: %d"), CountToWrite);

			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Write for Achievement: %s to %s for Player: %s - %s."), *Context, Achievement.ToChar(), *Snippet, *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		typedef NCsAchievement::EAction ActionType;

		QueueAction(ActionType::Write, Achievement, CountToWrite);
	}
}

void UCsManager_Achievement::SafeIncrement(const FECsAchievement& Achievement, const uint64& Count /*=1*/)
{
	SET_CONTEXT(SafeIncrement);

	if (IsValid(Context, Achievement) &&
		SupportsSafeCount(Context, Achievement) &&
		!IsCompleted(Achievement))
	{
		Increment(Achievement, Count);
	}
}

void UCsManager_Achievement::SetCount(const FECsAchievement& Achievement, const uint64& Count)
{
	SET_CONTEXT(SetCount);

	if (!IsEnabled(Context))
		return;

	ICsAchievement* IA = Achievements[Achievement.GetValue()];

	const ProgressType& ProgType = IA->GetProgressType();
	
	checkf(SupportsCount(Achievement), TEXT("%s: Achievement: %s ProgressType: %s does NOT support Count."), *Context, Achievement.ToChar(), ProgressMapType::Get().ToChar(ProgType));

	typedef NCsAchievement::EAction ActionType;

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting Reset for Achievement: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *GetLocalPlayerNickname(), *(UserId.ToString()));
			return;
		}

		if (ProgType != ProgressType::Count)
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s is NOT ProgressType: Count (currently = %s)."), *Context, Achievement.ToChar(), ProgressMapType::Get().ToChar(ProgType));
			return;
		}

		const int32 CurrentCount = IA->GetCount();
		
		bool QueueReset = (bOnlyForwardProgress || bCountAsAdd) && Count < CurrentCount;

		// Queue Reset
		if (QueueReset)
			QueueAction(ActionType::Reset, Achievement, 0ull);
		// Queue Write
		uint64 NewCount		= 0ull;
		uint64 CountToWrite	= 0ull;
		
		if (QueueReset)
		{
			NewCount	 = Count;
			CountToWrite = Count;
		}
		else
		{
			NewCount	 = CalculateCount(IA, Count);
			CountToWrite = bCountAsAdd ? NewCount - CurrentCount : NewCount;
		}
		
		QueueAction(ActionType::Write, Achievement, CountToWrite);

	#if !UE_BUILD_SHIPPING
		// Queue Write
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			FString Snippet;

			if (QueueReset)
			{
				Snippet = FString::Printf(TEXT("Count: %d"), CountToWrite);
			}
			else
			{
				Snippet = bCountAsAdd ? FString::Printf(TEXT("Count: %d (as add)"), CountToWrite) : FString::Printf(TEXT("Count: %d"), CountToWrite);
			}

			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Write for Achievement: %s to %s for Player: %s - %s."), *Context, Achievement.ToChar(), *Snippet, *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING
	}
}

void UCsManager_Achievement::SetSafeCount(const FECsAchievement& Achievement, const uint64& Count)
{
	SET_CONTEXT(SetSafeCount);

	if (IsValid(Context, Achievement) &&
		!IsCompleted(Achievement))
	{
		SetCount(Achievement, Count);
	}
}

bool UCsManager_Achievement::SupportsCount(const FECsAchievement& Achievement)
{
	return Achievements[Achievement.GetValue()]->GetProgressType() == ProgressType::Count;
}

bool UCsManager_Achievement::SupportsSafeCount(const FString& Context, const FECsAchievement& Achievement)
{
	if (Achievements[Achievement.GetValue()]->GetProgressType() != ProgressType::Count)
	{
		const ProgressType& Type = Achievements[Achievement.GetValue()]->GetProgressType();
		const TCHAR* Str		 = ProgressMapType::Get().ToChar(Type);

		UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s ProgressType: %s does NOT support Count."), *Context, Achievement.ToChar(), Str);
		return false;
	}
	return true;
}

#pragma endregion Count

// Bitfield
#pragma region

void UCsManager_Achievement::SetBit(const FECsAchievement& Achievement, const uint32& Index)
{
	SET_CONTEXT(SetBit);

	if (!IsEnabled(Context))
		return;

	if (!IsValidChecked(Context, Achievement))
		return;

	ICsAchievement* IA = Achievements[Achievement.GetValue()];

	const ProgressType& ProgType = IA->GetProgressType();

	checkf(SupportsBitfield(Achievement), TEXT("%s: Achievement: %s ProgressType: %s does NOT support Bitfield."), *Context, Achievement.ToChar(), ProgressMapType::Get().ToChar(ProgType));

	if (!bBitfieldIndexStartsAtZero && Index == 0)
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: bBitfieldIndexStartsAtZero is false and Index is 0."), *Context);
		return;
	}

	IOnlineAchievementsPtr IAchievements = GetAchievementsInterface();
	// Online
	if (IAchievements.IsValid())
	{
		const FUniqueNetId& UserId = GetLocalPlayerIdRef();

		if (!CheckAndQueueQuery())
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Query Ids and/or Query Descriptions Failed. Aborting Reset for Achievement: %s for Player: %s - %s."), *Context, Achievement.ToChar(), *GetLocalPlayerNickname(), *(UserId.ToString()));
			return;
		}

		if (ProgType != ProgressType::Bitfield)
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s is NOT ProgressType: Bitfield (currently = %s)."), *Context, Achievement.ToChar(), ProgressMapType::Get().ToChar(ProgType));
			return;
		}

		const uint32& BitfieldLength = IA->GetBitfieldLength();

		if (bBitfieldIndexStartsAtZero && Index >= BitfieldLength)
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: bBitfieldIndexStartsAtZero is true and Index is GREATER THAN OR EQUAL TO %d."), *Context, BitfieldLength);
			return;
		}

		if (!bBitfieldIndexStartsAtZero && Index > BitfieldLength)
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: bBitfieldIndexStartsAtZero is false and Index is GREATER THAN %d."), *Context, BitfieldLength);
			return;
		}

		// Queue Write
		const FString& Bitfield = IA->GetBitfield();
		const FString& BitMask  = IA->GetBitMask(Index);

		checkf(Bitfield.Len() == BitfieldLength, TEXT("%s: Mismatch between Bitfield.Len() and BitfieldLength (%d != %d)."), *Context, Bitfield.Len(), BitfieldLength);
		checkf(BitMask.Len() == BitfieldLength, TEXT("%s: Mismatch between BitMask.Len() and BitfieldLength (%d != %d)."), *Context, BitMask.Len(), BitfieldLength);

		FString NewBitfield;

		NewBitfield.Reset(BitfieldLength);

		if (bBitfieldAsOr)
		{
			NewBitfield = BitMask;
		}
		else
		{
			for (uint32 I = 0; I < BitfieldLength; ++I)
			{
				NewBitfield += Bitfield[I] == '1' || BitMask[I] == '1' ? '1' : '0';
			}
		}
		
	#if !UE_BUILD_SHIPPING
		// Queue Write
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			FString Snippet = bBitfieldAsOr ? FString::Printf(TEXT("Bitfield: %s (as or)"), *NewBitfield) : FString::Printf(TEXT("Bitfield: %s"), *NewBitfield);

			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Queueing Write for Achievement: %s to %s for Player: %s - %s."), *Context, Achievement.ToChar(), *Snippet, *GetLocalPlayerNickname(), *(UserId.ToString()));
		}
	#endif // #if !UE_BUILD_SHIPPING

		typedef NCsAchievement::EAction ActionType;

		QueueAction(ActionType::Write, Achievement, NewBitfield);
	}
}

void UCsManager_Achievement::SetSafeBit(const FECsAchievement& Achievement, const uint32& Index)
{
	SET_CONTEXT(SetSafeBit);

	if (IsValid(Context, Achievement) &&
		SupportsSafeBitfield(Context, Achievement) &&
		!IsCompleted(Achievement))
	{
		SetBit(Achievement, Index);
	}
}

bool UCsManager_Achievement::SupportsBitfield(const FECsAchievement& Achievement)
{
	return Achievements[Achievement.GetValue()]->GetProgressType() == ProgressType::Bitfield;
}

bool UCsManager_Achievement::SupportsSafeBitfield(const FString& Context, const FECsAchievement& Achievement)
{
	if (Achievements[Achievement.GetValue()]->GetProgressType() != ProgressType::Bitfield)
	{
		const ProgressType& Type = Achievements[Achievement.GetValue()]->GetProgressType();
		const TCHAR* Str		 = ProgressMapType::Get().ToChar(Type);

		UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s ProgressType: %s does NOT support Count."), *Context, Achievement.ToChar(), Str);
		return false;
	}
	return true;
}

#pragma endregion Bitfield

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
					UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::GetAchievementsInterface (%d): No Online Achievements Interface found."), ControllerId);
				}
				else
				{
					UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::GetAchievementsInterface (%d): No UniquePlayerId set for Local Player: %d."), ControllerId, ControllerId);
				}
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::GetAchievementsInterface (%d): No Online Identity found."), ControllerId);
			}
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::GetAchievementsInterface (%d): No Online Subsystem found."), ControllerId);
		}
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::GetAchievementsInterface: No Local Player set."));
	}
	return nullptr;
}

void UCsManager_Achievement::OnQueryAchievementsComplete(const FUniqueNetId& PlayerId, const bool Success)
{
	typedef NCsAchievement::NAction::NInfo::FResource ActionInfoContainerType;
	typedef NCsAchievement::NAction::NInfo::FInfo ActionInfoType;

	TCsDoubleLinkedList<ActionInfoContainerType*>* AllocatedHead = Manager_Resource.GetAllocatedHead();

	checkf(AllocatedHead, TEXT("UCsManager_Achievement::OnQueryAchievementsComplete: No Action was queued."));

	ActionInfoContainerType* InfoContainer = **AllocatedHead;
	ActionInfoType* ActionInfo		       = InfoContainer->Get();

	typedef NCsAchievement::EMAction ActionMapType;
	typedef NCsAchievement::EAction ActionType;

	checkf(ActionInfo->Action == ActionType::QueryIds, TEXT("UCsManager_Achievement::OnQueryAchievementsComplete: Current Action: %s is NOT QueryIds."), ActionMapType::Get().ToChar(ActionInfo->Action));

	if (!Success)
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::OnQueryAchievementsComplete: Failed to Query Achievements for Player: %s - %s."), *GetLocalPlayerNickname(), *(PlayerId.ToString()));
		
		QueryState.Ids.Complete();
		ActionInfo->Complete();
		return;
	}

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::OnQueryAchievementsComplete: Completed Query Achievement Ids for Player: %s - %s."), *GetLocalPlayerNickname(), *(PlayerId.ToString()));
	}
#endif // #if !UE_BUILD_SHIPPING

	QueryState.Ids.Success();
	QueryState.Ids.Complete();

	ActionInfo->Success();
	ActionInfo->Complete();
}

void UCsManager_Achievement::OnQueryAchievementDescriptionsComplete(const FUniqueNetId& PlayerId, const bool Success)
{
	typedef NCsAchievement::NAction::NInfo::FResource ActionInfoContainerType;
	typedef NCsAchievement::NAction::NInfo::FInfo ActionInfoType;

	TCsDoubleLinkedList<ActionInfoContainerType*>* AllocatedHead = Manager_Resource.GetAllocatedHead();

	checkf(AllocatedHead, TEXT("UCsManager_Achievement::OnQueryAchievementDescriptionsComplete: No Action was queued."));

	ActionInfoContainerType* InfoContainer = **AllocatedHead;
	ActionInfoType* ActionInfo		       = InfoContainer->Get();

	typedef NCsAchievement::EMAction ActionMapType;
	typedef NCsAchievement::EAction ActionType;

	checkf(ActionInfo->Action == ActionType::QueryDescriptions, TEXT("UCsManager_Achievement::OnQueryAchievementDescriptionsComplete: Current Action: %s is NOT QueryDescriptions."), ActionMapType::Get().ToChar(ActionInfo->Action));

	if (!Success)
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::OnQueryAchievementDescriptionsComplete: Failed to Query Achievement Descriptions for Player: %s - %s."), *GetLocalPlayerNickname(), *(PlayerId.ToString()));
		
		QueryState.Descriptions.Complete();
		ActionInfo->Complete();
		return;
	}

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::OnQueryAchievementDescriptionsComplete: Completed Query Achievement Descriptions for Player: %s - %s."), *GetLocalPlayerNickname(), *(PlayerId.ToString()));
	}
#endif // #if !UE_BUILD_SHIPPING

	QueryState.Descriptions.Success();
	QueryState.Descriptions.Complete();

	ActionInfo->Success();
	ActionInfo->Complete();
}

void UCsManager_Achievement::OnAchievementsWritten(const FUniqueNetId& PlayerId, bool Success)
{
	typedef NCsAchievement::NAction::NInfo::FResource ActionInfoContainerType;
	typedef NCsAchievement::NAction::NInfo::FInfo ActionInfoType;

	TCsDoubleLinkedList<ActionInfoContainerType*>* AllocatedHead = Manager_Resource.GetAllocatedHead();

	checkf(AllocatedHead, TEXT("UCsManager_Achievement::OnAchievementsWritten: No Action was queued."));

	ActionInfoContainerType* InfoContainer = **AllocatedHead;
	ActionInfoType* ActionInfo		       = InfoContainer->Get();

	const FECsAchievement& Achievement = ActionInfo->Achievement;

	typedef NCsAchievement::EAction ActinoType;

	const ActinoType& Action = ActionInfo->Action;

	ICsAchievement* IA = Achievements[Achievement.GetValue()];

	const float CurrentProgress = IA->GetProgress();

	if (!Success)
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::OnAchievementsWritten: Achievement: %s not written for Player: %s - %s."), Achievement.ToChar(), *GetLocalPlayerNickname(), *(PlayerId.ToString()));
		
		// Write
		if (Action == ActinoType::Write)
		{
			OnProgress_AsyncEvent.Broadcast(Success, IA, CurrentProgress);
			OnProgress_AsyncScriptEvent.Broadcast(Success, Achievement, CurrentProgress);
		}
		// Complete
		else
		if (Action == ActinoType::Complete)
		{
			OnComplete_AsyncEvent.Broadcast(Success, IA);
			OnComplete_AsyncScriptEvent.Broadcast(Success, Achievement);
		}
		// Reset
		else
		if (Action == ActinoType::Reset)
		{
			OnReset_AsyncEvent.Broadcast(Success, IA, CurrentProgress);
			OnReset_AsyncScriptEvent.Broadcast(Success, Achievement, CurrentProgress);
		}
		ActionInfo->Complete();
		return;
	}

	// Determine the result

	FVariantData* Data = WriteObject->FindStatByName(Achievement.Name_Internal);

	const ProgressType& ProgType = IA->GetProgressType();
	float Progress				 = 0.0f;

	// Standard | Binary
	if (ProgType == ProgressType::Standard ||
		ProgType == ProgressType::Binary)
	{
		GetWriteAchievementValue(Data, Progress);
	}
	// Count
	else
	if (ProgType == ProgressType::Count)
	{
		uint64 Count = 0ull;

		GetWriteAchievementCountValue(Data, Count);

		if (bCountAsAdd)
			IncrementCountBy(IA, Count);
		else
			SetCount(IA, Count);

		Progress = IA->GetProgress();
	}
	// Bitfield
	else
	if (ProgType == ProgressType::Bitfield)
	{
		FString Bitfield;

		GetWriteAchievementBitfieldValue(Data, Bitfield, IA->GetBitfieldLength());

		const uint32& BitfieldLength = IA->GetBitfieldLength();

		checkf(Bitfield.Len() == BitfieldLength, TEXT("UCsManager_Achievement::OnAchievementsWritten: Mismatch between Bitfield.Len() and BitfieldLength (%d != %d)."), Bitfield.Len(), BitfieldLength);

		if (bBitfieldAsOr)
			OrBitfield(IA, Bitfield);
		else
			SetBitfield(IA, Bitfield);
		
		Progress = IA->GetProgress();
	}

	// Reset / None or InProgress
	const float MaxProgress = IA->CalculateProgress(1.0f);

	if (Progress < MaxProgress)
	{
		if (ProgType != ProgressType::Bitfield)
			SetProgress(IA, Progress / MaxProgress);

#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::OnAchievementsWritten: Updated Achievement: %s Progress from %f to %f."), Achievement.ToChar(), CurrentProgress, Progress);
		}
#endif // #if !UE_BUILD_SHIPPING

		typedef NCsAchievement::EAction ActionType;

		// Write
		if (Action == ActionType::Write)
		{
			OnProgress_AsyncEvent.Broadcast(Success, IA, Progress);
			OnProgress_AsyncScriptEvent.Broadcast(Success, Achievement, Progress);
		}
		// Reset
		if (Action == ActionType::Reset)
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

#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerAchievementTransactions))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::OnAchievementsWritten: Completed Achievement: %s for Player: %s - %s."), Achievement.ToChar(), *GetLocalPlayerNickname(), *(PlayerId.ToString()));
		}
#endif // #if !UE_BUILD_SHIPPING

		OnComplete_AsyncEvent.Broadcast(Success, IA);
		OnComplete_AsyncScriptEvent.Broadcast(Success, Achievement);
	}
	ActionInfo->Success();
	ActionInfo->Complete();
}

void UCsManager_Achievement::GetWriteAchievementValue(FVariantData* VariantData, float& OutData) const
{
	switch (VariantData->GetType())
	{
		case EOnlineKeyValuePairDataType::Float:
		{
			VariantData->GetValue(OutData);
			break;
		}
		default:
		{
			checkf(false, TEXT("UCsManager_Achievement::GetWriteAchievementValue: Could not %s convert to float."), VariantData->GetTypeString());

			OutData = 0.0f;
			break;
		}
	}
}

void UCsManager_Achievement::GetWriteAchievementCountValue(FVariantData* VariantData, uint64& OutData) const
{
	switch (VariantData->GetType())
	{
		case EOnlineKeyValuePairDataType::Int32:
		{
			int32 Value;
			VariantData->GetValue(Value);
			OutData = static_cast<uint64>(Value);
			break;
		}
		case EOnlineKeyValuePairDataType::Int64:
		{
			int64 Value;
			VariantData->GetValue(Value);
			OutData = static_cast<uint64>(Value);
			break;
		}
		case EOnlineKeyValuePairDataType::UInt32:
		{
			uint32 Value;
			VariantData->GetValue(Value);
			OutData = static_cast<uint64>(Value);
			break;
		}
		case EOnlineKeyValuePairDataType::UInt64:
		{
			VariantData->GetValue(OutData);
			break;
		}
		default:
		{
			checkf(false, TEXT("UCsManager_Achievement::GetWriteAchievementCountValue: Could not %s convert to uint64."), VariantData->GetTypeString());

			OutData = 0;
			break;
		}
	}
}

void UCsManager_Achievement::GetWriteAchievementBitfieldValue(FVariantData* VariantData, FString& OutData, const uint32& BitfieldLength) const
{
	switch (VariantData->GetType())
	{
		case EOnlineKeyValuePairDataType::Int32:
		{
			int32 Value;
			VariantData->GetValue(Value);

			auto UnpaddedBitfield = FString::FromInt(Value);
			auto PaddingLength	  = BitfieldLength - UnpaddedBitfield.Len();

			OutData = TEXT("");
			
			for (uint32 i = 0; i < PaddingLength; ++i)
			{
				OutData.AppendChar('0');
			}
			OutData.Append(UnpaddedBitfield);
			break;
		}
		case EOnlineKeyValuePairDataType::String:
		{
			VariantData->GetValue(OutData);
			break;
		}
		default:
		{
			checkf(false, TEXT("UCsManager_Achievement::GetWriteAchievementBitfieldValue: Could not %s convert to string."), VariantData->GetTypeString());
			break;
		}
	}
}

#pragma endregion IOnlineAchievements

// Internals
#pragma region

bool UCsManager_Achievement::IsEnabled(const FString& Context)
{
#if !UE_BUILD_SHIPPING
	if (FCsCVarToggleMap::Get().IsDisabled(NCsCVarToggle::EnableManagerAchievement))
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievements are disabled. enable.manager.achievement = 0."), *Context);
		return false;
	}
#endif // #if !UE_BUILD_SHIPPING
	return true;
}

bool UCsManager_Achievement::IsValidChecked(const FString& Context, const FECsAchievement& Achievement)
{
	checkf(EMCsAchievement::Get().IsValidEnum(Achievement), TEXT("%s: Achievement: %s is NOT Valid."), *Context, Achievement.ToChar());

	checkf(Achievement.GetValue() < Achievements.Num(), TEXT("%s: Achievement: %s of type: ICsAchievement has not been constructed."), *Context, Achievement.ToChar());

	checkf(Achievements[Achievement.GetValue()], TEXT("%s: Achievement: %s of type: ICsAchievement has not been constructed."), *Context, Achievement.ToChar());

	return Achievements[Achievement.GetValue()]->IsValid();
}

bool UCsManager_Achievement::IsValid(const FString& Context, const FECsAchievement& Achievement, void(*Log)(const FString&) /*=&NCsPlatformServices::FLog::Warning*/)
{
	if (!EMCsAchievement::Get().IsValidEnum(Achievement))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Achievement: %s is NOT Valid."), *Context, Achievement.ToChar()));
		return false;
	}

	if (Achievement.GetValue() >= Achievements.Num())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Achievement: %s is NOT Valid."), *Context, Achievement.ToChar()));
		return false;
	}

	if (!Achievements[Achievement.GetValue()])
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Achievement: %s of type: ICsAchievement has not been constructed.."), *Context, Achievement.ToChar()));
		return false;
	}
	return Achievements[Achievement.GetValue()]->IsValid();
}

void UCsManager_Achievement::SetId(ICsAchievement* Achievement, const FString& Id)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
	A->Id = Id;
}

void UCsManager_Achievement::SetType(ICsAchievement* Achievement, const FECsAchievement& AchievementType)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
	A->Type = AchievementType;
}

void UCsManager_Achievement::SetProgressType(ICsAchievement* Achievement, const ProgressType& Type)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
	A->SetProgressType(Type);
}

void UCsManager_Achievement::SetProgress(ICsAchievement* Achievement, const float& Percent)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);

	const ProgressType& Type = A->GetProgressType();
	
	// Bitfield
	if (Type == ProgressType::Bitfield)
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsManager_Achievement::SetProgress: Achievement: %s has ProgressType:: Bitfield and does NOT support SetProgress."), *(Achievement->GetId()));
		return;
	}

	A->SetProgress(Percent);

	// Count
	if (Type == ProgressType::Count)
	{
		A->SetCount(A->GetProgressAsPercent() * A->GetMaxCount());
	}
}

void UCsManager_Achievement::SetCount(ICsAchievement* Achievement, const uint64& Count)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
	A->SetCount(Count);
}

void UCsManager_Achievement::SetMaxCount(ICsAchievement* Achievement, const uint64& Count)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
	A->SetMaxCount(Count);
}

void UCsManager_Achievement::IncrementCount(ICsAchievement* Achievement)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
	A->IncrementCount();
}

void UCsManager_Achievement::IncrementCountBy(ICsAchievement* Achievement, const uint64& Count)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
	A->IncrementCountBy(Count);
}

uint64 UCsManager_Achievement::CalculateCount(ICsAchievement* Achievement, const uint64& Count)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
	return A->CalculateCount(Count);
}

void UCsManager_Achievement::SetBitfield(ICsAchievement* Achievement, const FString& Bitfield)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
	A->SetBitfield(Bitfield);
}

void UCsManager_Achievement::OrBitfield(ICsAchievement* Achievement, const FString& Bitfield)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
	A->OrBitfield(Bitfield);
}

void UCsManager_Achievement::SetUnlockBitfieldLength(ICsAchievement* Achievement, const uint32& Length)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
	A->SetUnlockBitfieldLength(Length);
}

bool UCsManager_Achievement::IsValidBitfield(ICsAchievement* Achievement, const FString& Bitfield)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
	return A->IsValidBitfield(Bitfield);
}

void UCsManager_Achievement::SetTitle(ICsAchievement* Achievement, const FString& Title)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
}

void UCsManager_Achievement::SetDescription(ICsAchievement* Achievement, const FString& Description)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
}

void UCsManager_Achievement::SetUnlockedDescription(ICsAchievement* Achievement, const FString& UnlockedDescription)
{
	FCsAchievement* A = static_cast<FCsAchievement*>(Achievement);
}

#pragma endregion Internals

#undef USING_NS_CACHED
#undef SET_CONTEXT
#undef QueryOrderType
#undef ProgressMapType
#undef ProgressType