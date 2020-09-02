// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Menu/CsManager_Menu.h"
#include "CsUI.h"

// CVar
//#include "CsCVars_Manager_Data.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Menu/CsGetManagerMenu.h"

#include "Library/CsLibrary_Common.h"

#include "Engine/World.h"
#include "Engine/Engine.h"
#endif // #if WITH_EDITOR

// static initializations
UCsManager_Menu* UCsManager_Menu::s_Instance;
bool UCsManager_Menu::s_bShutdown = false;

UCsManager_Menu::UCsManager_Menu(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_Menu* UCsManager_Menu::Get(UObject* InRoot /*= nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerMenu(InRoot)->GetManager_Menu();
#else
	if (s_bShutdown)
		return nullptr;

	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Menu::Init(UObject* InRoot, TSubclassOf<UCsManager_Menu> ManagerMenuClass, UObject* InOuter /*= nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerMenu* GetManagerMenu = Get_GetManagerMenu(InRoot);

	UCsManager_Menu* Manager_Menu = GetManagerMenu->GetManager_Menu();

	if (!Manager_Menu)
	{
		Manager_Menu = NewObject<UCsManager_Menu>(InOuter ? InOuter : InRoot, ManagerMenuClass, TEXT("Manager_Menu_Singleton"), RF_Transient | RF_Public);

		GetManagerMenu->SetManager_Menu(Manager_Menu);

		Manager_Menu->SetMyRoot(InRoot);
		Manager_Menu->Initialize();
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Menu>(GetTransientPackage(), ManagerMenuClass, TEXT("Manager_Menu_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Menu::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerMenu* GetManagerMenu = Get_GetManagerMenu(InRoot);
	UCsManager_Menu* Manager_Menu     = GetManagerMenu->GetManager_Menu();
	Manager_Menu->CleanUp();
	Manager_Menu->SetMyRoot(nullptr);

	GetManagerMenu->SetManager_Menu(nullptr);
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

/*static*/ ICsGetManagerMenu* UCsManager_Menu::Get_GetManagerMenu(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Menu::Get_GetManagerMenu: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Menu::Get_GetManagerMenu: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Menu::Get_GetManagerMenu: Manager_Singleton is NULL."));

	ICsGetManagerMenu* GetManagerMenu = Cast<ICsGetManagerMenu>(Manager_Singleton);

	checkf(GetManagerMenu, TEXT("UCsManager_Menu::Get_GetManagerMenu: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerMenu."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerMenu;
}

/*static*/ ICsGetManagerMenu* UCsManager_Menu::GetSafe_GetManagerMenu(UObject* Object)
{
	if (!Object)
		return nullptr;

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
		return nullptr;

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
		return nullptr;

	return Cast<ICsGetManagerMenu>(Manager_Singleton);
}

/*static*/ UCsManager_Menu* UCsManager_Menu::GetSafe(UObject* Object)
{
	if (ICsGetManagerMenu* GetManagerMenu = GetSafe_GetManagerMenu(Object))
		return GetManagerMenu->GetManager_Menu();
	return nullptr;
}

/*static*/ UCsManager_Menu* UCsManager_Menu::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsManager_Menu* Manager = GetSafe(World->GetGameInstance()))
			return Manager;

		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_Menu::GetFromWorldContextObject: Failed to Manager Data of type UCsManager_Menu from GameInstance."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_Menu::Initialize()
{
}

void UCsManager_Menu::CleanUp()
{
}

	// Root
#pragma region

void UCsManager_Menu::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton