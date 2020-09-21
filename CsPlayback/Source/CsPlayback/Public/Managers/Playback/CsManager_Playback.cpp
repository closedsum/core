// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Playback/CsManager_Playback.h"
#include "CsPlayback.h"

// Settings
//#include "Settings/CsDeveloperSettings.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Playback/CsGetManagerPlayback.h"

#include "Library/CsLibrary_Common.h"

#include "Engine/World.h"
#include "Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// static initializations
UCsManager_Playback* UCsManager_Playback::s_Instance;
bool UCsManager_Playback::s_bShutdown = false;

UCsManager_Playback::UCsManager_Playback(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_Playback* UCsManager_Playback::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerPlayback(InRoot)->GetManager_Playback();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::Get: Manager has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Playback::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerPlayback(InRoot)->GetManager_Playback() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Playback::Init(UObject* InRoot)
{
#if WITH_EDITOR
	ICsGetManagerPlayback* GetManagerPlayback = Get_GetManagerPlayback(InRoot);

	UCsManager_Playback* Manager_Playback = GetManagerPlayback->GetManager_Playback();

	if (!Manager_Playback)
	{
		Manager_Playback = NewObject<UCsManager_Playback>(InRoot, UCsManager_Playback::StaticClass(), TEXT("Manager_Playback_Singleton"), RF_Transient | RF_Public);

		GetManagerPlayback->SetManager_Playback(Manager_Playback);

		Manager_Playback->SetMyRoot(InRoot);
		Manager_Playback->Initialize();
	}
	else
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Playback>(GetTransientPackage(), UCsManager_Playback::StaticClass(), TEXT("Manager_Playback_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Playback::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerPlayback* GetManagerPlayback = Get_GetManagerPlayback(InRoot);
	UCsManager_Playback* Manager_Playback	  = GetManagerPlayback->GetManager_Playback();
	Manager_Playback->CleanUp();

	GetManagerPlayback->SetManager_Playback(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Playback::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerPlayback(InRoot)->GetManager_Playback() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerPlayback* UCsManager_Playback::Get_GetManagerPlayback(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Playback::Get_GetManagerPlayback: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Playback::Get_GetManagerPlayback: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Playback::Get_GetManagerPlayback: Manager_Singleton is NULL."));

	ICsGetManagerPlayback* GetManagerPlayback = Cast<ICsGetManagerPlayback>(Manager_Singleton);

	checkf(GetManagerPlayback, TEXT("UCsManager_Playback::Get_GetManagerPlayback: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerPlayback."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerPlayback;
}

/*static*/ ICsGetManagerPlayback* UCsManager_Playback::GetSafe_GetManagerPlayback(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::GetSafe_GetManagerPlayback: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::GetSafe_GetManagerPlayback: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::GetSafe_GetManagerPlayback: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerPlayback>(Manager_Singleton);
}

/*static*/ UCsManager_Playback* UCsManager_Playback::GetSafe(UObject* Object)
{
	if (ICsGetManagerPlayback* GetManagerPlayback = GetSafe_GetManagerPlayback(Object))
		return GetManagerPlayback->GetManager_Playback();
	return nullptr;
}

/*static*/ UCsManager_Playback* UCsManager_Playback::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsManager_Playback* Manager = GetSafe(World->GetGameInstance()))
			return Manager;

		UE_LOG(LogCsPlayback, Warning, TEXT("UCsManager_Playback::GetFromWorldContextObject: Failed to Manager Item of type UCsManager_Playback from GameInstance."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_Playback::Initialize()
{
	bInitialized = true;
}

/*static*/ bool UCsManager_Playback::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Playback::CleanUp()
{
	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_Playback::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

void UCsManager_Playback::Update(const FCsDeltaTime& DeltaTime)
{
}