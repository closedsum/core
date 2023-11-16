// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Level/CsManager_Level.h"
#include "CsCore.h"

// CVar
//#include "CsCVars_Manager_Data.h"
// Coroutine
#include "Coroutine/CsRoutine.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
	// Common
#include "Level/CsLibrary_Level.h"
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Managers/Level/CsSettings_Manager_Level.h"
// World
#include "Engine/World.h"
// Level
#include "Level/CsLevelScriptActor.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Level/CsGetManagerLevel.h"
#endif // #if WITH_EDITOR

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
			// Persistent Level
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, Check_FinishedLoadingPersistentLevel);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, Check_FinishedLoadingPersistentLevel_Internal);
			// Change Map
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, ChangeMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, ChangeMap_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, DestroyOtherPIEWorld);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Level, DestroyOtherPIEWorld_Internal);
		}

		namespace Name
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Level, Check_FinishedLoadingPersistentLevel_Internal);
			// Change Map
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Level, ChangeMap_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Level, DestroyOtherPIEWorld_Internal);
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
	typedef NCsWorld::FLibrary WorldLibrary;

	return WorldLibrary::GetSafe(MyRoot);
}

// Persistent Level
#pragma region

void UCsManager_Level::Check_FinishedLoadingPersistentLevel()
{
	using namespace NCsManagerLevel::NCached;

	const FString& Context = Str::Check_FinishedLoadingPersistentLevel;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;
	typedef NCsCoroutine::NPayload::FImpl PayloadImplType;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	PayloadImplType* Payload		   = CoroutineSchedulerLibrary::AllocatePayloadChecked(Context, MyRoot, UpdateGroup);

	typedef UCsManager_Level ClassType;
	#define COROUTINE Check_FinishedLoadingPersistentLevel_Internal

	Payload->Init<ClassType>(Context, this, &ClassType::COROUTINE, MyRoot, UpdateGroup, Str::COROUTINE, Name::COROUTINE);

	#undef COROUTINE

	bFinishedLoadingPersistentlLevel = false;

	CS_COROUTINE_PAYLOAD_PASS_FLAG_START

	CS_COROUTINE_PAYLOAD_PASS_FLAG(Payload, false);

	CoroutineSchedulerLibrary::StartChecked(Context, MyRoot, Payload);
}

void UCsManager_Level::Check_FinishedLoadingPersistentLevel(const FString& MapPackageName)
{
	using namespace NCsManagerLevel::NCached;

	const FString& Context = Str::Check_FinishedLoadingPersistentLevel;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;
	typedef NCsCoroutine::NPayload::FImpl PayloadImplType;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	PayloadImplType* Payload		   = CoroutineSchedulerLibrary::AllocatePayloadChecked(Context, MyRoot, UpdateGroup);

	typedef UCsManager_Level ClassType;
	#define COROUTINE Check_FinishedLoadingPersistentLevel_Internal

	Payload->Init<ClassType>(Context, this, &ClassType::COROUTINE, MyRoot, UpdateGroup, Str::COROUTINE, Name::COROUTINE);

	#undef COROUTINE

	bFinishedLoadingPersistentlLevel = false;

	CS_COROUTINE_PAYLOAD_PASS_FLAG_START
	CS_COROUTINE_PAYLOAD_PASS_STRING_START

	CS_COROUTINE_PAYLOAD_PASS_FLAG(Payload, MapPackageName.IsEmpty() ? false : true);
	CS_COROUTINE_PAYLOAD_PASS_STRING(Payload, MapPackageName);

	CoroutineSchedulerLibrary::StartChecked(Context, MyRoot, Payload);
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

// Change Map
#pragma region

#define ChangeMapParamsType NCsLevel::NManager::NChangeMap::FParams
void UCsManager_Level::ChangeMap(const ChangeMapParamsType& Params)
{
#undef ChangeMapParamsType
	using namespace NCsManagerLevel::NCached;

	const FString& Context = Str::ChangeMap;

	CS_IS_VALID_CHECKED(Params);

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineScheculerLibrary;
	typedef NCsCoroutine::NPayload::FImpl PayloadImplType;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	PayloadImplType* Payload		   = CoroutineScheculerLibrary::AllocatePayloadChecked(Context, MyRoot, UpdateGroup);

	typedef UCsManager_Level ClassType;
	#define COROUTINE ChangeMap_Internal

	Payload->Init<ClassType>(Context, this, &ClassType::COROUTINE, this, UpdateGroup, Str::COROUTINE, Name::COROUTINE);

	#undef COROUTINE

	CS_COROUTINE_PAYLOAD_PASS_STRING_START

	CS_COROUTINE_PAYLOAD_PASS_STRING(Payload, Params.Map);
	CS_COROUTINE_PAYLOAD_PASS_STRING(Payload, Params.TransitionMap);

	typedef NCsLevel::NPersistent::FLibrary LevelLibrary;

	CurrentMap = LevelLibrary::GetSafeName(MyRoot);

	bChangeMapCompleted = false;

	CoroutineScheculerLibrary::StartChecked(Context, MyRoot, Payload);
}

char UCsManager_Level::ChangeMap_Internal(FCsRoutine* R)
{
	CS_COROUTINE_READ_STRING_START

	CS_COROUTINE_READ_STRING_CONST_REF(R, NewMap);
	CS_COROUTINE_READ_STRING_CONST_REF(R, TransitionMap);

	CS_COROUTINE_BEGIN(R);

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
	CS_COROUTINE_WAIT_UNTIL(R, HasFinishedLoadingPersistentLevel());

	bChangeMapCompleted = true;

	OnChangeMapComplete_Event.Broadcast(CurrentMap, NewMap);

	CurrentMap = NewMap;

	CS_COROUTINE_END(R);
}

#pragma endregion Change Map

#if WITH_EDITOR

void UCsManager_Level::DestroyOtherPIEWorld(const FString& URL)
{
	using namespace NCsManagerLevel::NCached;

	const FString& Context = Str::DestroyOtherPIEWorld;

	// TODO: Check URL is not Current World

	CS_IS_STRING_EMPTY_CHECKED(URL);

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineScheculerLibrary;
	typedef NCsCoroutine::NPayload::FImpl PayloadImplType;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	PayloadImplType* Payload		   = CoroutineScheculerLibrary::AllocatePayloadChecked(Context, MyRoot, UpdateGroup);

	typedef UCsManager_Level ClassType;
	#define COROUTINE DestroyOtherPIEWorld_Internal

	Payload->Init<ClassType>(Context, this, &ClassType::COROUTINE, this, UpdateGroup, Str::COROUTINE, Name::COROUTINE);

	#undef COROUTINE

	const FString URL_PIE = UWorld::ConvertToPIEPackageName(URL, 0);

	UPackage* WorldPackage = Cast<UPackage>(StaticFindObject(nullptr, nullptr, *URL_PIE, true));
	UWorld* OtherWorld	   = WorldPackage ? UWorld::FindWorldInPackage(WorldPackage) : nullptr;

	if (IsValid(OtherWorld))
	{
		CS_COROUTINE_PAYLOAD_PASS_STRING_START

		CS_COROUTINE_PAYLOAD_PASS_STRING(Payload, URL_PIE);

		bFinishedDestroyingOtherPIEWorld = false;

		CoroutineScheculerLibrary::StartChecked(Context, MyRoot, Payload);
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