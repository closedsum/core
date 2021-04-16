// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Level/CsManager_Level.h"
#include "CsCore.h"

// CVar
//#include "CsCVars_Manager_Data.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
// Library
#include "Level/CsLibrary_Level.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"
// Level
#include "Level/CsLevelScriptActor.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Level/CsGetManagerLevel.h"

#include "Library/CsLibrary_Common.h"

#include "Engine/Engine.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerLevel
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, Check_FinishedLoadingPersistentLevel_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, ChangeMap_Internal);
		}

		namespace Name
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Level, Check_FinishedLoadingPersistentLevel_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Level, ChangeMap_Internal);
		}
	}
}

#pragma endregion Cached

// static initializations
UCsManager_Level* UCsManager_Level::s_Instance;
bool UCsManager_Level::s_bShutdown = false;

UCsManager_Level::UCsManager_Level(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

#if WITH_EDITOR
/*static*/ UCsManager_Level* UCsManager_Level::Get(UObject* InRoot /*= nullptr*/)
{
	return Get_GetManagerLevel(InRoot)->GetManager_Level();
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

/*static*/ void UCsManager_Level::Shutdown(UObject* InRoot /*=nullptr*/)
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

/*static*/ ICsGetManagerLevel* UCsManager_Level::Get_GetManagerLevel(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Level::Get_GetManagerLevel: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Level::Get_GetManagerLevel: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Level::Get_GetManagerLevel: Manager_Singleton is NULL."));

	ICsGetManagerLevel* GetManagerLevel = Cast<ICsGetManagerLevel>(Manager_Singleton);

	checkf(GetManagerLevel, TEXT("UCsManager_Level::Get_GetManagerLevel: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerLevel."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerLevel;
}

/*static*/ ICsGetManagerLevel* UCsManager_Level::GetSafe_GetManagerLevel(UObject* Object)
{
	if (!Object)
		return nullptr;

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
		return nullptr;

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
		return nullptr;

	return Cast<ICsGetManagerLevel>(Manager_Singleton);
}

/*static*/ UCsManager_Level* UCsManager_Level::GetSafe(UObject* Object)
{
	if (ICsGetManagerLevel* GetManagerLevel = GetSafe_GetManagerLevel(Object))
		return GetManagerLevel->GetManager_Level();
	return nullptr;
}

/*static*/ UCsManager_Level* UCsManager_Level::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsManager_Level* Manager = GetSafe(World->GetGameInstance()))
			return Manager;

		UE_LOG(LogCs, Warning, TEXT("UCsManager_Level::GetFromWorldContextObject: Failed to Manager Data of type UCsManager_Level from GameInstance."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_Level::Initialize()
{
}

void UCsManager_Level::CleanUp()
{
}

	// Root
#pragma region

void UCsManager_Level::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Persistent Level
#pragma region

void UCsManager_Level::Check_FinishedLoadingPersistentLevel()
{
	using namespace NCsManagerLevel::NCached;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(MyRoot);

	typedef NCsCoroutine::NPayload::FImpl PayloadImplType;

	PayloadImplType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	Payload->CoroutineImpl.BindUObject(this, &UCsManager_Level::Check_FinishedLoadingPersistentLevel_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetOwner(this);
	Payload->SetName(Str::Check_FinishedLoadingPersistentLevel_Internal);
	Payload->SetFName(Name::Check_FinishedLoadingPersistentLevel_Internal);

	bFinishedLoadingPersistentlLevel = false;

	Payload->SetValue_Flag(CS_FIRST, false);

	Scheduler->Start(Payload);
}

void UCsManager_Level::Check_FinishedLoadingPersistentLevel(const FString& MapPackageName)
{
	using namespace NCsManagerLevel::NCached;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(MyRoot);

	typedef NCsCoroutine::NPayload::FImpl PayloadImplType;

	PayloadImplType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	Payload->CoroutineImpl.BindUObject(this, &UCsManager_Level::Check_FinishedLoadingPersistentLevel_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetOwner(this);
	Payload->SetName(Str::Check_FinishedLoadingPersistentLevel_Internal);
	Payload->SetFName(Name::Check_FinishedLoadingPersistentLevel_Internal);

	bFinishedLoadingPersistentlLevel = false;

	Payload->SetValue_Flag(CS_FIRST, MapPackageName.IsEmpty() ? false : true);
	Payload->SetValue_String(CS_FIRST, MapPackageName);

	Scheduler->Start(Payload);
}

char UCsManager_Level::Check_FinishedLoadingPersistentLevel_Internal(FCsRoutine* R)
{
	const bool& CheckMapName	  = R->GetValue_Flag(CS_FIRST);
	const FString& MapPackageName = R->GetValue_String(CS_FIRST);

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
						bFinishedLoadingPersistentlLevel = true;
						break;
					}
				}
				else
				{
					bFinishedLoadingPersistentlLevel = true;
					break;
				}
			}
		}
	}

	CS_COROUTINE_BEGIN(R);

	// Wait until Persistent level is loaded
	CS_COROUTINE_WAIT_UNTIL(R, bFinishedLoadingPersistentlLevel);

	CS_COROUTINE_END(R);
}

#pragma endregion Persistent Level

// TODO: Add ChangeMap Params

void UCsManager_Level::ChangeMap(const FChangeMapParams& Params)
{
	using namespace NCsManagerLevel::NCached;

	checkf(!Params.Map.IsEmpty(), TEXT("UCsManager_Level::ChangeMap: Params.Map is Empty."));

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(MyRoot);

	typedef NCsCoroutine::NPayload::FImpl PayloadImplType;

	PayloadImplType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	Payload->CoroutineImpl.BindUObject(this, &UCsManager_Level::ChangeMap_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::ChangeMap_Internal);
	Payload->SetFName(Name::ChangeMap_Internal);

	static const int32 MAP_INDEX = 0;
	Payload->SetValue_String(MAP_INDEX, Params.Map);

	static const int32 TRANSITION_MAP_INDEX = 1;
	Payload->SetValue_String(TRANSITION_MAP_INDEX, Params.TransitionMap);

	typedef NCsLevel::NPersistent::FLibrary LevelLibrary;

	CurrentMap = LevelLibrary::GetSafeName(MyRoot);

	bChangeMapCompleted = false;

	Scheduler->Start(Payload);
}

char UCsManager_Level::ChangeMap_Internal(FCsRoutine* R)
{
	static const int32 MAP_INDEX = 0;
	const FString& NewMap = R->GetValue_String(MAP_INDEX);

	static const int32 TRANSITION_MAP_INDEX = 1;
	const FString& TransitionMap = R->GetValue_String(TRANSITION_MAP_INDEX);

	CS_COROUTINE_BEGIN(R);

	// Transition to New Map
	{
		// TODO: Add setting Transition Map
		if (!TransitionMap.IsEmpty())
		{

		}
		/*
#if !UE_BUILD_SHIPPING
		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogGameStartup))
		{
			UE_LOG(LogCs, Warning, TEXT("%s: Transition to Shell: %s."), *Context, *URL);
		}
#endif // #if !UE_BUILD_SHIPPING
		*/
		MyRoot->GetWorld()->ServerTravel(NewMap);
		Check_FinishedLoadingPersistentLevel(NewMap);
	}

	// Wait until the New Map is loaded
	CS_COROUTINE_WAIT_UNTIL(R, HasFinishedLoadingPersistentLevel());

	bChangeMapCompleted = true;

	OnChangeMapComplete_Event.Broadcast(CurrentMap, NewMap);

	CurrentMap = NewMap;

	CS_COROUTINE_END(R);
}