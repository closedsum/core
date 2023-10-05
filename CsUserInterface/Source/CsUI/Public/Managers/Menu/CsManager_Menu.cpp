// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Menu/CsManager_Menu.h"
#include "CsUI.h"

// Managers
#include "Managers/Time/CsManager_Time.h"
// Settings
#include "Managers/Menu/CsSettings_Manager_Menu.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_Valid.h"
// Singleton
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Menu/CsGetManagerMenu.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerMenu
{
	namespace NCached
	{
		namespace Str
		{
			// Singleton
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Menu, Init);
		}
	}
}

#pragma endregion Cached

// static initializations
UCsManager_Menu* UCsManager_Menu::s_Instance;
bool UCsManager_Menu::s_bShutdown = false;

UCsManager_Menu::UCsManager_Menu(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_Menu* UCsManager_Menu::Get(UObject* InRoot /*= nullptr*/)
{
	return Get_GetManagerMenu(InRoot)->GetManager_Menu();
}

/*static*/ UCsManager_Menu* UCsManager_Menu::GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerMenu* GetManagerMenu = GetSafe_GetManagerMenu(Context, InRoot, Log))
		return GetManagerMenu->GetManager_Menu();
	return nullptr;
}

#endif // #if WITH_EDITOR

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

/*static*/ void UCsManager_Menu::Init(UObject* InRoot, UObject* InOuter /*= nullptr*/)
{
	using namespace NCsManagerMenu::NCached;

	const FString& Context = Str::Init;

	const FCsSettings_Manager_Menu& Settings = FCsSettings_Manager_Menu::Get();

	Init(InRoot, Settings.LoadClassChecked(Context), InOuter);
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

/*static*/ ICsGetManagerMenu* UCsManager_Menu::GetSafe_GetManagerMenu(const FString& Context, UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	CS_IS_PTR_NULL_RET_NULL(InRoot)

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

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
	return Cast<ICsGetManagerMenu>(Manager_Singleton);
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

void UCsManager_Menu::Update(const float& DeltaSeconds)
{
	// Update Time
	UCsManager_Time* Manager_Time = UCsManager_Time::Get(GetOuter());

	const FECsUpdateGroup& Group = NCsUpdateGroup::Menu;

	Manager_Time->Update(Group, DeltaSeconds);
}