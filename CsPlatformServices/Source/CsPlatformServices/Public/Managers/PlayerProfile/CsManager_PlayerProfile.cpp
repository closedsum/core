// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/PlayerProfile/CsManager_PlayerProfile.h"
#include "CsPlatformServices.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/PlayerProfile/CsPlayerProfile.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/PlayerProfile/CsGetManagerPlayerProfile.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerPlayerProfile
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_PlayerProfile, SetCurrentActiveProfile);
		}
	}
}

#pragma endregion Cached

// static initializations
UCsManager_PlayerProfile* UCsManager_PlayerProfile::s_Instance;
bool UCsManager_PlayerProfile::s_bShutdown = false;

UCsManager_PlayerProfile::UCsManager_PlayerProfile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentActiveProfileType = ECsPlayerProfile::Profile1;
}

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_PlayerProfile* UCsManager_PlayerProfile::Get(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerPlayerProfile(InRoot)->GetManager_PlayerProfile();
}

#endif // #if WITH_EDITOR

/*static*/ bool UCsManager_PlayerProfile::IsValid()
{
	return s_Instance != nullptr;
}

/*static*/ void UCsManager_PlayerProfile::Init(UObject* InRoot)
{
#if WITH_EDITOR
	ICsGetManagerPlayerProfile* GetManagerPlayerProfile = Get_GetManagerPlayerProfile(InRoot);

	UCsManager_PlayerProfile* Manager_PlayerProfile = NewObject<UCsManager_PlayerProfile>(InRoot, UCsManager_PlayerProfile::StaticClass(), TEXT("Manager_PlayerProfile_Singleton"), RF_Transient | RF_Public);

	GetManagerPlayerProfile->SetManager_PlayerProfile(Manager_PlayerProfile);

	Manager_PlayerProfile->SetMyRoot(InRoot);
	Manager_PlayerProfile->Initialize();
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_PlayerProfile>(GetTransientPackage(), UCsManager_PlayerProfile::StaticClass(), TEXT("Manager_PlayerProfile_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}

#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_PlayerProfile::Shutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerPlayerProfile* GetManagerPlayerProfile = Get_GetManagerPlayerProfile(InRoot);
	UCsManager_PlayerProfile* Manager_PlayerProfile		= GetManagerPlayerProfile->GetManager_PlayerProfile();
	Manager_PlayerProfile->CleanUp();

	GetManagerPlayerProfile->SetManager_PlayerProfile(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_PlayerProfile::HasShutdown()
{
	return s_bShutdown;
}

#if WITH_EDITOR

/*static*/ ICsGetManagerPlayerProfile* UCsManager_PlayerProfile::Get_GetManagerPlayerProfile(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_PlayerProfile::Get_GetManagerPlayerProfile: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_PlayerProfile::Get_GetManagerPlayerProfile: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_PlayerProfile::Get_GetManagerPlayerProfile: Manager_Singleton is NULL."));

	ICsGetManagerPlayerProfile* GetManagerPlayerProfile = Cast<ICsGetManagerPlayerProfile>(Manager_Singleton);

	checkf(GetManagerPlayerProfile, TEXT("UCsManager_PlayerProfile::Get_GetManagerPlayerProfile: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerPlayerProfile."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerPlayerProfile;
}

/*static*/ ICsGetManagerPlayerProfile* UCsManager_PlayerProfile::GetSafe_GetManagerPlayerProfile(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
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
	return Cast<ICsGetManagerPlayerProfile>(Manager_Singleton);
}

/*static*/ UCsManager_PlayerProfile* UCsManager_PlayerProfile::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerPlayerProfile* GetManagerPlayerProfiles = GetSafe_GetManagerPlayerProfile(Context, InRoot, Log))
		return GetManagerPlayerProfiles->GetManager_PlayerProfile();
	return nullptr;
}

#endif // #if WITH_EDITOR

void UCsManager_PlayerProfile::Initialize()
{
}

void UCsManager_PlayerProfile::CleanUp()
{
	/*
	for (TPair<ECsPlayerProfile, UCsPlayerProfile*>& Pair : Profiles)
	{
		UCsPlayerProfile* P = Pair.Value;

		if (P && !P->IsPendingKill())
		{
			P->BeginDestroy();
		}
		Pair.Value = nullptr;
	}
	*/
	Profiles.Reset();
}

	// Root
#pragma region

void UCsManager_PlayerProfile::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

void UCsManager_PlayerProfile::Update(const float& DeltaSeconds)
{
	for (TPair<ECsPlayerProfile, UCsPlayerProfile*>& Pair : ProfileMap)
	{
		Pair.Value->Update(DeltaSeconds);
	}
}

UCsPlayerProfile* UCsManager_PlayerProfile::CreateProfile(const ECsPlayerProfile& ProfileType)
{
	// TODO: May need to tie Profile to ULocalPlayer

	if (UCsPlayerProfile** ProfilePtr = ProfileMap.Find(ProfileType))
	{
		// LOG
		return *ProfilePtr;
	}

	UCsPlayerProfile* P = NewObject<UCsPlayerProfile>(this, UCsPlayerProfile::StaticClass());

	P->SetProfileType(ProfileType);

	Profiles.Add(P);
	ProfileMap.Add(ProfileType, P);

	return P;
}

UCsPlayerProfile* UCsManager_PlayerProfile::GetProfile(const ECsPlayerProfile& ProfileType)
{
	if (UCsPlayerProfile** ProfilePtr = ProfileMap.Find(ProfileType))
	{
		return *ProfilePtr;
	}
	return nullptr;
}

void UCsManager_PlayerProfile::SetCurrentActiveProfile(const ECsPlayerProfile& ProfileType)
{
	using namespace NCsManagerPlayerProfile::NCached;

	const FString& Context = Str::SetCurrentActiveProfile;

	check(EMCsPlayerProfile::Get().IsValidEnumChecked(Context, ProfileType));

	CurrentActiveProfile	 = ProfileMap[ProfileType];
	CurrentActiveProfileType = ProfileType;
}