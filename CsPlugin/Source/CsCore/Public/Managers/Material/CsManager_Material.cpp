// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Material/CsManager_Material.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Material/CsGetManagerMaterial.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerMaterial
{
	namespace NCached
	{
		namespace Str
		{
		}
	}
}

#pragma endregion Cached

// static initializations
UCsManager_Material* UCsManager_Material::s_Instance;
bool UCsManager_Material::s_bShutdown = false;

UCsManager_Material::UCsManager_Material(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_Material* UCsManager_Material::Get(const UObject* InRoot /*= nullptr*/)
{
	return Get_GetManagerMaterial(InRoot)->GetManager_Material();
}

/*static*/ UCsManager_Material* UCsManager_Material::GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerMaterial* GetManagerMaterial = GetSafe_GetManagerMaterial(Context, InRoot, Log))
		return GetManagerMaterial->GetManager_Material();
	return nullptr;
}

#endif // #if WITH_EDITOR

/*static*/ void UCsManager_Material::Init(UObject* InRoot, TSubclassOf<UCsManager_Material> ManagerMaterialClass, UObject* InOuter /*= nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerMaterial* GetManagerMaterial = Get_GetManagerMaterial(InRoot);

	UCsManager_Material* Manager_Menu = GetManagerMaterial->GetManager_Material();

	if (!Manager_Menu)
	{
		Manager_Menu = NewObject<UCsManager_Material>(InOuter ? InOuter : InRoot, ManagerMaterialClass, TEXT("Manager_Material_Singleton"), RF_Transient | RF_Public);

		GetManagerMaterial->SetManager_Material(Manager_Menu);

		Manager_Menu->SetMyRoot(InRoot);
		Manager_Menu->Initialize();
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Material>(GetTransientPackage(), ManagerMaterialClass, TEXT("Manager_Material_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Material::Shutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerMaterial* GetManagerMaterial = Get_GetManagerMaterial(InRoot);
	UCsManager_Material* Manager_Menu     = GetManagerMaterial->GetManager_Material();
	Manager_Menu->CleanUp();
	Manager_Menu->SetMyRoot(nullptr);

	GetManagerMaterial->SetManager_Material(nullptr);
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

/*static*/ ICsGetManagerMaterial* UCsManager_Material::Get_GetManagerMaterial(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Material::Get_GetManagerMaterial: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Material::Get_GetManagerMaterial: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Material::Get_GetManagerMaterial: Manager_Singleton is NULL."));

	ICsGetManagerMaterial* GetManagerMaterial = Cast<ICsGetManagerMaterial>(Manager_Singleton);

	checkf(GetManagerMaterial, TEXT("UCsManager_Material::Get_GetManagerMaterial: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerMaterial."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerMaterial;
}

/*static*/ ICsGetManagerMaterial* UCsManager_Material::GetSafe_GetManagerMaterial(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
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
	return Cast<ICsGetManagerMaterial>(Manager_Singleton);
}

#endif // #if WITH_EDITOR

void UCsManager_Material::Initialize()
{
}

void UCsManager_Material::CleanUp()
{
}

	// Root
#pragma region

void UCsManager_Material::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton