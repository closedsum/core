// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Level/CsManager_Level.h"
#include "CsCore.h"

// CVar
//#include "CsCVars_Manager_Data.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Level/CsGetManagerLevel.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"
#endif // #if WITH_EDITOR

// static initializations
UCsManager_Level* UCsManager_Level::s_Instance;
bool UCsManager_Level::s_bShutdown = false;

UCsManager_Level::UCsManager_Level(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_Level* UCsManager_Level::Get(UObject* InRoot /*= nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerLevel(InRoot)->GetManager_Level();
#else
	if (s_bShutdown)
		return nullptr;

	return s_Instance;
#endif // #if WITH_EDITOR
}

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