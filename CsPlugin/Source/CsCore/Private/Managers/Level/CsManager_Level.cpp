// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Level/CsManager_Level.h"
#include "CsCore.h"

// CVar
#include "Managers/Level/CsCVars_Manager_Level.h"
// Coroutine
#include "Coroutine/CsRoutine.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "World/CsWorld_Delegates.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
	// Common
#include "Game/CsLibrary_GameInstanceImpl.h"
#include "Level/CsLibrary_Level.h"
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Managers/Level/CsSettings_Manager_Level.h"
// World
#include "Engine/World.h"
// Level
#include "Level/CsLevelScriptActor.h"
#include "Engine/Level.h"
#include "Engine/LevelStreaming.h"
#include "Managers/Level/Event/CsLevel_Streaming_EventHandler.h"
// Package
#include "UObject/Package.h"

#if WITH_EDITOR
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Managers/Level/CsGetManagerLevel.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_Level)

// Cached
#pragma region

namespace NCsManagerLevel
{
	namespace NCached
	{
		namespace Str
		{
			// Singleton
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, Init);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, Initialize);
			// Persistent Level
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, Check_FinishedLoadingPersistentLevel);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, Check_FinishedLoadingPersistentLevel_Internal);
			// Change Map
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, ChangeMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, ChangeMap_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, ChangeMap_TransitionAsDestination);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, ChangeMap_TransitionAsDestination_Internal);
			// Transition
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, GameInstance_Transition_OnFinish);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, DestroyOtherPIEWorld);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, DestroyOtherPIEWorld_Internal);
			// Streaming
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, Level_Streaming_OnAdded);
		}

		namespace Name
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Level, Check_FinishedLoadingPersistentLevel_Internal);
			// Change Map
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Level, ChangeMap_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Level, ChangeMap_TransitionAsDestination_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Level, DestroyOtherPIEWorld_Internal);
		}
	}
}

#pragma endregion Cached

// static initializations
UCsManager_Level* UCsManager_Level::s_Instance;
bool UCsManager_Level::s_bShutdown = false;

UCsManager_Level::UCsManager_Level(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// Change Map
	CurrentMap(),
	ChangeMapInfo(),
	ChangeMap_OnStart_Event(),
	ChangeMap_OnStart_ScriptEvent(),
	ChangeMap_OnComplete_Event(),
	ChangeMap_OnComplete_ScriptEvent(),
	// Streaming
	StreamingEventsByIdMap(),
	Level_Streaming_OnLoaded_Event(),
	Level_Streaming_OnLoaded_ScriptEvent(),
	Level_Streaming_OnUnloaded_Event(),
	Level_Streaming_OnUnloaded_ScriptEvent(),
	Level_Streaming_OnShown_Event(),
	Level_Streaming_OnShown_ScriptEvent(),
	Level_Streaming_OnHidden_Event(),
	Level_Streaming_OnHidden_ScriptEvent()
{
}

#define USING_NS_CACHED using namespace NCsManagerLevel::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsManagerLevel::NCached; \
	const FString& Context = Str::__FunctionName

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_Level* UCsManager_Level::Get(const UObject* InRoot /*= nullptr*/)
{
	return Get_GetManagerLevel(InRoot)->GetManager_Level();
}

/*static*/ UCsManager_Level* UCsManager_Level::GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerLevel* GetManagerLevel = GetSafe_GetManagerLevel(Context, InRoot, Log))
		return GetManagerLevel->GetManager_Level();
	return nullptr;
}

#endif // #if WITH_EDITOR

/*static*/ void UCsManager_Level::Init(UObject* InRoot, TSubclassOf<UCsManager_Level> ManageLevelClass, UObject* InOuter /*= nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerLevel* GetManagerLevel = Get_GetManagerLevel(InRoot);

	UCsManager_Level* Manager_Menu = GetManagerLevel->GetManager_Level();

	if (!Manager_Menu)
	{
		Manager_Menu = NewObject<UCsManager_Level>(InOuter ? InOuter : InRoot, ManageLevelClass, TEXT("Manager_Level_Singleton"), RF_Transient | RF_Public);

		GetManagerLevel->SetManager_Level(Manager_Menu);

		Manager_Menu->SetMyRoot(InRoot);
		Manager_Menu->Initialize();
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Level>(GetTransientPackage(), ManageLevelClass, TEXT("Manager_Level_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Level::Init(UObject* InRoot, UObject* InOuter /*= nullptr*/)
{
	using namespace NCsManagerLevel::NCached;

	const FString& Context = Str::Init;

	const FCsSettings_Manager_Level& Settings = FCsSettings_Manager_Level::Get();

	Init(InRoot, Settings.LoadClassChecked(Context), InOuter);
}

/*static*/ void UCsManager_Level::Shutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerLevel* GetManagerLevel = Get_GetManagerLevel(InRoot);
	UCsManager_Level* Manager_Menu     = GetManagerLevel->GetManager_Level();
	Manager_Menu->CleanUp();
	Manager_Menu->SetMyRoot(nullptr);

	GetManagerLevel->SetManager_Level(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->SetMyRoot(nullptr);
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerLevel* UCsManager_Level::Get_GetManagerLevel(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Level::Get_GetManagerLevel: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Level::Get_GetManagerLevel: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Level::Get_GetManagerLevel: Manager_Singleton is NULL."));

	ICsGetManagerLevel* GetManagerLevel = Cast<ICsGetManagerLevel>(Manager_Singleton);

	checkf(GetManagerLevel, TEXT("UCsManager_Level::Get_GetManagerLevel: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerLevel."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerLevel;
}

/*static*/ ICsGetManagerLevel* UCsManager_Level::GetSafe_GetManagerLevel(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
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
	return Cast<ICsGetManagerLevel>(Manager_Singleton);
}

#endif // #if WITH_EDITOR

void UCsManager_Level::Initialize()
{
	SET_CONTEXT(Initialize);

	// Bind to Delegates

	NCsWorld::FDelegates::OnPostWorldInitialization_Simple_Event.AddUObject(this, &UCsManager_Level::OnPostWorldInitialization);
	CsGameInstanceImplLibrary::GetTransition_OnFinish_EventChecked(Context, MyRoot).AddUObject(this, &UCsManager_Level::GameInstance_Transition_OnFinish);
	NCsLevel::NStreaming::NDynamic::FDelegates::OnAdded_Event.AddUObject(this, &UCsManager_Level::Level_Streaming_OnAdded);
}

void UCsManager_Level::CleanUp()
{
	ReceiveCleanUp();
}

	// Root
#pragma region

void UCsManager_Level::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

UObject* UCsManager_Level::GetWorldContext() const
{
	return CsWorldLibrary::GetSafe(MyRoot);
}

// Persistent Level
#pragma region

void UCsManager_Level::Check_FinishedLoadingPersistentLevel()
{
	SET_CONTEXT(Check_FinishedLoadingPersistentLevel);

	FinishedLoadingPersistentLevelInfo.bCompleted = false;

	if (UWorld* World = MyRoot->GetWorld())
	{
		const TArray<ULevel*>& Levels = World->GetLevels();

		for (ULevel* Level : Levels)
		{
			if (Level->IsPersistentLevel() &&
				Level->bIsVisible)
			{
				FinishedLoadingPersistentLevelInfo.bCompleted = true;
				break;
			}
		}
	}

	if (FinishedLoadingPersistentLevelInfo.bCompleted)
	{
		FinishedLoadingPersistentLevelInfo.bActive = false;
		return;
	}

	CS_COROUTINE_SETUP_UOBJECT(UCsManager_Level, Check_FinishedLoadingPersistentLevel_Internal, NCsUpdateGroup::GameInstance, this, MyRoot);

	CS_COROUTINE_PAYLOAD_PASS_FLAG_START

	CS_COROUTINE_PAYLOAD_PASS_FLAG(false);

	FinishedLoadingPersistentLevelInfo.bActive = true;

	CS_COROUTINE_START(MyRoot);
}

void UCsManager_Level::Check_FinishedLoadingPersistentLevel(const FString& MapPackageName)
{
	SET_CONTEXT(Check_FinishedLoadingPersistentLevel);

	if (MapPackageName.IsEmpty())
	{
		Check_FinishedLoadingPersistentLevel();
		return;
	}

	FinishedLoadingPersistentLevelInfo.bCompleted = false;

	if (UWorld* World = MyRoot->GetWorld())
	{
		const TArray<ULevel*>& Levels = World->GetLevels();

		for (ULevel* Level : Levels)
		{
			if (Level->IsPersistentLevel() &&
				Level->bIsVisible)
			{
				const FString PersistentLevelPackageName = UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);

				if (PersistentLevelPackageName == MapPackageName)
				{
					FinishedLoadingPersistentLevelInfo.bCompleted = true;
					break;
				}
			}
		}
	}

	if (FinishedLoadingPersistentLevelInfo.bCompleted)
	{
		FinishedLoadingPersistentLevelInfo.bActive = false;
		return;
	}

	FinishedLoadingPersistentLevelInfo.MapPackageName = MapPackageName;
	FinishedLoadingPersistentLevelInfo.bActive		  = true;
}

char UCsManager_Level::Check_FinishedLoadingPersistentLevel_Internal(FCsRoutine* R)
{
	CS_COROUTINE_READ_FLAG_START
	CS_COROUTINE_READ_STRING_START

	CS_COROUTINE_READ_FLAG_CONST_REF(R, CheckMapName);
	CS_COROUTINE_READ_STRING_CONST_REF(R, MapPackageName);

	if (UWorld* World = MyRoot->GetWorld())
	{
		const TArray<ULevel*>& Levels = World->GetLevels();

		for (ULevel* Level : Levels)
		{
			if (Level->IsPersistentLevel() &&
				Level->bIsVisible)
			{
				if (CheckMapName)
				{
					const FString PersistentLevelPackageName = UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);

					if (PersistentLevelPackageName == MapPackageName)
					{
						FinishedLoadingPersistentLevelInfo.bCompleted = true;
						break;
					}
				}
				else
				{
					FinishedLoadingPersistentLevelInfo.bCompleted = true;
					break;
				}
			}
		}
	}

	CS_COROUTINE_BEGIN(R);

	// Wait until Persistent level is loaded
	CS_COROUTINE_WAIT_UNTIL(R, FinishedLoadingPersistentLevelInfo.IsCompleted());

	FinishedLoadingPersistentLevelInfo.bActive = false;

	CS_COROUTINE_END(R);
}

#pragma endregion Persistent Level

// Change Map
#pragma region

#define ChangeMapParamsType NCsLevel::NManager::NChangeMap::FParams

void UCsManager_Level::ChangeMap(const ChangeMapParamsType& Params)
{
	SET_CONTEXT(ChangeMap);

	CS_IS_VALID_CHECKED(Params);

	if (Params.IsTransitionDestination())
	{
		ChangeMap_TransitionAsDestination(Params);
	}
	else
	{
		CS_COROUTINE_SETUP_UOBJECT(UCsManager_Level, ChangeMap_Internal, NCsUpdateGroup::GameInstance, this, this);

		CS_COROUTINE_PAYLOAD_PASS_STRING_START

		CS_COROUTINE_PAYLOAD_PASS_STRING(Params.Map);
		CS_COROUTINE_PAYLOAD_PASS_STRING(Params.TransitionMap);

		CurrentMap = CsPersistentLevelLibrary::GetSafeName(MyRoot);

		ChangeMapInfo.bActive = true;
		ChangeMapInfo.bCompleted = false;
		ChangeMapInfo.DestinationMap = Params.Map;

		CS_COROUTINE_START(MyRoot);
	}
}

char UCsManager_Level::ChangeMap_Internal(FCsRoutine* R)
{
	CS_COROUTINE_READ_STRING_START

	CS_COROUTINE_READ_STRING_CONST_REF(R, NewMap);
	CS_COROUTINE_READ_STRING_CONST_REF(R, TransitionMap);

	CS_COROUTINE_BEGIN(R);

	ChangeMap_OnStart_Event.Broadcast(CurrentMap, NewMap);
	ChangeMap_OnStart_ScriptEvent.Broadcast(CurrentMap, NewMap);

	// Transition to New Map
	{
		// TODO: Add setting Transition Map
		if (!TransitionMap.IsEmpty())
		{

		}
		/*
#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogGameStartup))
		{
			UE_LOG(LogCs, Warning, TEXT("%s: Transition to Shell: %s."), *Context, *URL);
		}
#endif // #if !UE_BUILD_SHIPPING
		*/
		MyRoot->GetWorld()->ServerTravel(NewMap);
		Check_FinishedLoadingPersistentLevel(NewMap);
	}

	// Wait until the New Map is loaded
	CS_COROUTINE_WAIT_UNTIL(R, ChangeMapInfo.IsCompleted());

	ChangeMapInfo.bActive = false;

	ChangeMap_OnComplete_Event.Broadcast(CurrentMap, NewMap);
	ChangeMap_OnComplete_ScriptEvent.Broadcast(CurrentMap, NewMap);

	CurrentMap = NewMap;

	CS_COROUTINE_END(R);
}

void UCsManager_Level::ChangeMap_TransitionAsDestination(const ChangeMapParamsType& Params)
{
	SET_CONTEXT(ChangeMap_TransitionAsDestination);

	CS_IS_VALID_CHECKED(Params);

	CS_COROUTINE_SETUP_UOBJECT(UCsManager_Level, ChangeMap_TransitionAsDestination_Internal, NCsUpdateGroup::GameInstance, this, this);

	CS_COROUTINE_PAYLOAD_PASS_STRING_START

	CS_COROUTINE_PAYLOAD_PASS_STRING(Params.Map);
	CS_COROUTINE_PAYLOAD_PASS_STRING(Params.TransitionMap);

	CurrentMap = CsPersistentLevelLibrary::GetSafeName(MyRoot);

	ChangeMapInfo.bActive = true;
	ChangeMapInfo.bCompleted = false;
	ChangeMapInfo.DestinationMap = Params.TransitionMap;

	CS_COROUTINE_START(MyRoot);
}

char UCsManager_Level::ChangeMap_TransitionAsDestination_Internal(FCsRoutine* R)
{
	SET_CONTEXT(ChangeMap_TransitionAsDestination_Internal);

	CS_COROUTINE_READ_STRING_START

	CS_COROUTINE_READ_STRING_CONST_REF(R, NewMap);
	CS_COROUTINE_READ_STRING_CONST_REF(R, TransitionMap);

	CS_COROUTINE_BEGIN(R);

	ChangeMap_OnStart_Event.Broadcast(CurrentMap, TransitionMap);
	ChangeMap_OnStart_ScriptEvent.Broadcast(CurrentMap, TransitionMap);

	// Transition to "New Map" (TransitionMap)
	MyRoot->GetWorld()->ServerTravel(NewMap);
	MyRoot->GetWorld()->SetSeamlessTravelMidpointPause(true);

	// Wait until the New Map is loaded
	CS_COROUTINE_WAIT_UNTIL(R, ChangeMapInfo.IsCompleted());

	ChangeMapInfo.bActive = false;

	ChangeMap_OnComplete_Event.Broadcast(CurrentMap, TransitionMap);
	ChangeMap_OnComplete_ScriptEvent.Broadcast(CurrentMap, TransitionMap);

	CurrentMap = TransitionMap;

	CS_COROUTINE_END(R);
}

#undef ChangeMapParamsType

#pragma endregion Change Map

// Transition
#pragma region

void UCsManager_Level::GameInstance_Transition_OnFinish()
{
	SET_CONTEXT(GameInstance_Transition_OnFinish);

	StreamingEventsByIdMap.Reset();

	// TODO: FUTURE: Handle Dynamic loading of levels not in the streaming list

	UWorld* World = CsWorldLibrary::GetChecked(Context, MyRoot);

	// Populate Map
	for (ULevelStreaming* LevelStreaming : World->GetStreamingLevels())
	{
		if (IsValid(LevelStreaming))
		{
			const uint32 Id					   = LevelStreaming->GetUniqueID();
			ACsLevel_Streaming_EventHandler* A = World->SpawnActor<ACsLevel_Streaming_EventHandler>();

			StreamingEventsByIdMap.Add(Id, A);
		}
	}

	for (ULevelStreaming* LevelStreaming : World->GetStreamingLevels())
	{
		if (IsValid(LevelStreaming))
		{
			const uint32 Id								  = LevelStreaming->GetUniqueID();
			ACsLevel_Streaming_EventHandler* EventHandler = StreamingEventsByIdMap[Id];

			EventHandler->Level = LevelStreaming;

			LevelStreaming->OnLevelLoaded.AddDynamic(EventHandler, &ACsLevel_Streaming_EventHandler::OnLevelLoaded);
			LevelStreaming->OnLevelUnloaded.AddDynamic(EventHandler, &ACsLevel_Streaming_EventHandler::OnLevelUnloaded);
			LevelStreaming->OnLevelShown.AddDynamic(EventHandler, &ACsLevel_Streaming_EventHandler::OnLevelShown);
			LevelStreaming->OnLevelHidden.AddDynamic(EventHandler, &ACsLevel_Streaming_EventHandler::OnLevelHidden);
		}	
	}
}

#pragma endregion Transition

// Streaming
#pragma region

void UCsManager_Level::Level_Streaming_OnAdded(UWorld* World, ULevelStreaming* LevelStreaming)
{
	SET_CONTEXT(Level_Streaming_OnAdded);

	if (World == CsWorldLibrary::GetChecked(Context, GetWorldContext()))
	{
		const uint32 Id					   = LevelStreaming->GetUniqueID();
		ACsLevel_Streaming_EventHandler* A = World->SpawnActor<ACsLevel_Streaming_EventHandler>();

		StreamingEventsByIdMap.Add(Id, A);

		A->Level = LevelStreaming;

		LevelStreaming->OnLevelLoaded.AddDynamic(A, &ACsLevel_Streaming_EventHandler::OnLevelLoaded);
		LevelStreaming->OnLevelUnloaded.AddDynamic(A, &ACsLevel_Streaming_EventHandler::OnLevelUnloaded);
		LevelStreaming->OnLevelShown.AddDynamic(A, &ACsLevel_Streaming_EventHandler::OnLevelShown);
		LevelStreaming->OnLevelHidden.AddDynamic(A, &ACsLevel_Streaming_EventHandler::OnLevelHidden);
	}
}

void UCsManager_Level::Broadcast_Level_Streaming_OnLoaded(ULevelStreaming* Level) 
{
#if WITH_EDITOR
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerLevelStreaming))
	{
		UE_LOG(LogCs, Warning, TEXT("Level Streaming: OnLoaded: %s"), *(Level->GetWorldAssetPackageName()));
	}
#endif // #if WITH_EDITOR

	Level_Streaming_OnLoaded_Event.Broadcast(Level);
	Level_Streaming_OnLoaded_ScriptEvent.Broadcast(Level);
}

void UCsManager_Level::Broadcast_Level_Streaming_OnUnloaded(ULevelStreaming* Level)
{
#if WITH_EDITOR
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerLevelStreaming))
	{
		UE_LOG(LogCs, Warning, TEXT("Level Streaming: OnUnloaded: %s"), *(Level->GetWorldAssetPackageName()));
	}
#endif // #if WITH_EDITOR

	Level_Streaming_OnUnloaded_Event.Broadcast(Level);
	Level_Streaming_OnUnloaded_ScriptEvent.Broadcast(Level);
}

void UCsManager_Level::Broadcast_Level_Streaming_OnShown(ULevelStreaming* Level)
{
#if WITH_EDITOR
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerLevelStreaming))
	{
		UE_LOG(LogCs, Warning, TEXT("Level Streaming: OnShown: %s"), *(Level->GetWorldAssetPackageName()));
	}
#endif // #if WITH_EDITOR

	Level_Streaming_OnShown_Event.Broadcast(Level);
	Level_Streaming_OnShown_ScriptEvent.Broadcast(Level);
}

void UCsManager_Level::Broadcast_Level_Streaming_OnHidden(ULevelStreaming* Level)
{
#if WITH_EDITOR
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerLevelStreaming))
	{
		UE_LOG(LogCs, Warning, TEXT("Level Streaming: OnHidden: %s"), *(Level->GetWorldAssetPackageName()));
	}
#endif // #if WITH_EDITOR

	Level_Streaming_OnHidden_Event.Broadcast(Level);
	Level_Streaming_OnHidden_ScriptEvent.Broadcast(Level);
}

#pragma endregion Streaming

// Events
#pragma region

void UCsManager_Level::OnPostWorldInitialization(UWorld* World)
{
	// Finished Loading Persistent Level
	if (FinishedLoadingPersistentLevelInfo.IsActive() &&
		!FinishedLoadingPersistentLevelInfo.IsCompleted())
	{
		const FString PersistentLevelPackageName = UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);

		if (PersistentLevelPackageName == FinishedLoadingPersistentLevelInfo.MapPackageName)
			FinishedLoadingPersistentLevelInfo.MarkCompleted();
	}
	// Change Map
	if (ChangeMapInfo.IsActive() &&
		!ChangeMapInfo.IsCompleted())
	{
		const FString PersistentLevelPackageName = UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);

		if (PersistentLevelPackageName == ChangeMapInfo.DestinationMap)
			ChangeMapInfo.MarkCompleted();
	}
}
	
#pragma endregion Events

#if WITH_EDITOR

void UCsManager_Level::DestroyOtherPIEWorld(const FString& URL)
{
	SET_CONTEXT(DestroyOtherPIEWorld);

	// TODO: Check URL is not Current World

	CS_IS_STRING_EMPTY_CHECKED(URL);

	CS_COROUTINE_SETUP_UOBJECT(UCsManager_Level, DestroyOtherPIEWorld_Internal, NCsUpdateGroup::GameInstance, this, this);

	const FString URL_PIE = UWorld::ConvertToPIEPackageName(URL, 0);

	UPackage* WorldPackage = Cast<UPackage>(StaticFindObject(nullptr, nullptr, *URL_PIE, true));
	UWorld* OtherWorld	   = WorldPackage ? UWorld::FindWorldInPackage(WorldPackage) : nullptr;

	if (IsValid(OtherWorld))
	{
		CS_COROUTINE_PAYLOAD_PASS_STRING_START

		CS_COROUTINE_PAYLOAD_PASS_STRING(URL_PIE);

		bFinishedDestroyingOtherPIEWorld = false;

		CS_COROUTINE_START(MyRoot);
	}
	else
	{
		bFinishedDestroyingOtherPIEWorld = true;
	}
}

char UCsManager_Level::DestroyOtherPIEWorld_Internal(FCsRoutine* R)
{
	CS_COROUTINE_READ_STRING_START

	CS_COROUTINE_READ_STRING_CONST_REF(R, URL_PIE);

	UPackage* WorldPackage = Cast<UPackage>(StaticFindObject(nullptr, nullptr, *URL_PIE, true));
	UWorld* OtherWorld	   = WorldPackage ? UWorld::FindWorldInPackage(WorldPackage) : nullptr;

	CS_COROUTINE_BEGIN(R);

	OtherWorld->DestroyWorld(true);

	CS_COROUTINE_WAIT_UNTIL(R, !IsValid(OtherWorld))

	bFinishedDestroyingOtherPIEWorld = true;

	CS_COROUTINE_END(R);
}

#endif // #if WITH_EDITOR

#undef USING_NS_CACHED
#undef SET_CONTEXT