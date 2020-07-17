// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/DigitalAgreement/CsManager_DigitalAgreement.h"
#include "CsOnline.h"

#include "Managers/DigitalAgreement/CsCVars_DigitalAgreement.h"

#include "Coroutine/CsCoroutineScheduler.h"

// Managers
#include "Managers/Time/CsManager_Time.h"
//#include "Managers/Save/CsManager_Save.h"
// DigitalAgreement
#include "Managers/DigitalAgreement/CsConsoleCommand_DigitalAgreement.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/DigitalAgreement/CsGetManagerDigitalAgreement.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"
#endif // #if WITH_EDITOR

// static initializations
UCsManager_DigitalAgreement* UCsManager_DigitalAgreement::s_Instance;
bool UCsManager_DigitalAgreement::s_bShutdown = false;

UCsManager_DigitalAgreement::UCsManager_DigitalAgreement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Cached
#pragma region

namespace NCsManagerDigitalAgreementCached
{
	namespace Str
	{
		const FString Query_Internal = TEXT("UCsManager_DigitalAgreement::Query_Internal");
	}

	namespace Name
	{
		const FName Query_Internal = FName("UCsManager_DigitalAgreement::Query_Internal");
	}
}

#pragma endregion Cached

// Singleton
#pragma region

/*static*/ UCsManager_DigitalAgreement* UCsManager_DigitalAgreement::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerDigitalAgreement(InRoot)->GetManager_DigitalAgreement();
#else
	if (s_bShutdown)
		return nullptr;

	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_DigitalAgreement::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerDigitalAgreement(InRoot)->GetManager_DigitalAgreement() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_DigitalAgreement::Init(UObject* InRoot)
{
#if WITH_EDITOR
	ICsGetManagerDigitalAgreement* GetManagerDigitalAgreement = Get_GetManagerDigitalAgreement(InRoot);

	UCsManager_DigitalAgreement* Manager_DigitalAgreement = GetManagerDigitalAgreement->GetManager_DigitalAgreement();

	if (!Manager_DigitalAgreement)
	{
		Manager_DigitalAgreement = NewObject<UCsManager_DigitalAgreement>(InRoot, UCsManager_DigitalAgreement::StaticClass(), TEXT("Manager_DigitalAgreement_Singleton"), RF_Transient | RF_Public);

		GetManagerDigitalAgreement->SetManager_DigitalAgreement(Manager_DigitalAgreement);

		Manager_DigitalAgreement->SetMyRoot(InRoot);
		Manager_DigitalAgreement->Initialize();
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_DigitalAgreement>(GetTransientPackage(), UCsManager_DigitalAgreement::StaticClass(), TEXT("Manager_DigitalAgreement_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_DigitalAgreement::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerDigitalAgreement* GetManagerDigitalAgreement = Get_GetManagerDigitalAgreement(InRoot);
	UCsManager_DigitalAgreement* Manager_DigitalAgreement	  = GetManagerDigitalAgreement->GetManager_DigitalAgreement();
	Manager_DigitalAgreement->CleanUp();

	GetManagerDigitalAgreement->SetManager_DigitalAgreement(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

void UCsManager_DigitalAgreement::SafeShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerDigitalAgreement* GetManagerDigitalAgreement = Get_GetManagerDigitalAgreement(InRoot);

	if (!GetManagerDigitalAgreement)
		return;

	UCsManager_DigitalAgreement* Manager_DigitalAgreement = GetManagerDigitalAgreement->GetManager_DigitalAgreement();

	if (!Manager_DigitalAgreement)
		return;

	Manager_DigitalAgreement->CleanUp();

	GetManagerDigitalAgreement->SetManager_DigitalAgreement(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_DigitalAgreement::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerDigitalAgreement(InRoot)->GetManager_DigitalAgreement() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerDigitalAgreement* UCsManager_DigitalAgreement::Get_GetManagerDigitalAgreement(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_DigitalAgreement::Get_GetManagerDigitalAgreement: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_DigitalAgreement::Get_GetManagerDigitalAgreement: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_DigitalAgreement::Get_GetManagerDigitalAgreement: Manager_Singleton is NULL."));

	ICsGetManagerDigitalAgreement* GetManagerDigitalAgreement = Cast<ICsGetManagerDigitalAgreement>(Manager_Singleton);

	checkf(GetManagerDigitalAgreement, TEXT("UCsManager_DigitalAgreement::Get_GetManagerDigitalAgreement: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerDigitalAgreement."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerDigitalAgreement;
}

/*static*/ ICsGetManagerDigitalAgreement* UCsManager_DigitalAgreement::GetSafe_GetManagerDigitalAgreement(UObject* Object)
{
	if (!Object)
		return nullptr;

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
		return nullptr;

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
		return nullptr;

	return Cast<ICsGetManagerDigitalAgreement>(Manager_Singleton);
}

/*static*/ UCsManager_DigitalAgreement* UCsManager_DigitalAgreement::GetSafe(UObject* Object)
{
	if (ICsGetManagerDigitalAgreement* GetManagerDigitalAgreement = GetSafe_GetManagerDigitalAgreement(Object))
		return GetManagerDigitalAgreement->GetManager_DigitalAgreement();
	return nullptr;
}

/*static*/ UCsManager_DigitalAgreement* UCsManager_DigitalAgreement::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsManager_DigitalAgreement* Manager = GetSafe(World->GetGameInstance()))
			return Manager;

		UE_LOG(LogCsOnline, Warning, TEXT("UCsManager_DigitalAgreement::GetFromWorldContextObject: Failed to Manager Save of type UCsManager_DigitalAgreement from GameInstance."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_DigitalAgreement::Initialize()
{
	ConsoleCommand = new FCsConsoleCommand_DigitalAgreement(MyRoot);

	const int32 Count = EMCsDigitalAgreement::Get().Num();

	States.Reserve(Count);
	States.AddDefaulted(Count);

	Query();
}

void UCsManager_DigitalAgreement::CleanUp()
{
	delete ConsoleCommand;
	ConsoleCommand = nullptr;
}

	// Root
#pragma region

void UCsManager_DigitalAgreement::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

bool UCsManager_DigitalAgreement::AreEnabled()
{
#if !UE_BUILD_SHIPPING
	return CsCVarDisableGameStartupDigitalAgreement->GetInt() == CS_CVAR_DISABLED;
#else
	return true;
#endif // #if !UE_BUILD_SHIPPING
}

// Query
#pragma region

void UCsManager_DigitalAgreement::Query()
{
	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(MyRoot);
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload(UpdateGroup);

	Payload->CoroutineImpl.BindUObject(this, &UCsManager_DigitalAgreement::Query_Internal);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetOwner(this);
	Payload->SetFName(NCsManagerDigitalAgreementCached::Name::Query_Internal);
	Payload->SetName(NCsManagerDigitalAgreementCached::Str::Query_Internal);

	Scheduler->Start(Payload); 
}

char UCsManager_DigitalAgreement::Query_Internal(FCsRoutine* R)
{
	//UCsManager_Save* Manager_Save = UCsManager_Save::Get<UCsManager_Save>(MyRoot);

	CS_COROUTINE_BEGIN(R);
	
	/*
	// Wait until Manager_Save is Valid
	CS_COROUTINE_WAIT_UNTIL(R, Manager_Save);

	// Wait until Save files have been enumerated
	CS_COROUTINE_WAIT_UNTIL(R, Manager_Save->HasSetSaveData(ECsPlayerProfile::Common, ERsSave::Save1));

	// Update States
	const FCsCommonSave& Save = Manager_Save->GetCommonSave(ECsSave::Save1);

	{
		// User Agreement
		if (Save.DigitalAgreements.bAcceptedUserAgreement)
			States[(uint8)ECsDigitalAgreement::UserAgreement].Accept();
		else
			States[(uint8)ECsDigitalAgreement::UserAgreement].DoNotAccept();
		// Privacy and Cookie Policy
		if (Save.DigitalAgreements.bAcceptedPrivacyAndCookiePolicy)
			States[(uint8)ECsDigitalAgreement::PrivacyAndCookiePolicy].Accept();
		else
			States[(uint8)ECsDigitalAgreement::PrivacyAndCookiePolicy].DoNotAccept();
	}
	*/
	CS_COROUTINE_END(R);
}

#pragma endregion Query

// Reset
#pragma region

void UCsManager_DigitalAgreement::Reset(const ECsDigitalAgreement& DigitalAgreement)
{
	checkf(DigitalAgreement != ECsDigitalAgreement::ECsDigitalAgreement_MAX, TEXT("UCsManager_DigitalAgreement::Reset: DigitalAgreement: ECsDigitalAgreement_MAX (MAX) is NOT Valid."));

	States[(uint8)DigitalAgreement].Reset();

	OnReset_Event.Broadcast(DigitalAgreement);
}

void UCsManager_DigitalAgreement::ResetAll()
{
	for (FCsDigitalAgreementState& State : States)
	{
		State.Reset();
	}
	OnResetAll_Event.Broadcast();
}

#pragma endregion Reset

// Accept
#pragma region

void UCsManager_DigitalAgreement::Accept(const ECsDigitalAgreement& DigitalAgreement)
{
	checkf(DigitalAgreement != ECsDigitalAgreement::ECsDigitalAgreement_MAX, TEXT("UCsManager_DigitalAgreement::Accept: DigitalAgreement: ECsDigitalAgreement_MAX (MAX) is NOT Valid."));

	States[(uint8)DigitalAgreement].Accept();

	OnAccept_Event.Broadcast(DigitalAgreement);
	OnAccept_ScriptEvent.Broadcast(DigitalAgreement);
}

bool UCsManager_DigitalAgreement::HasBeenAccepted(const ECsDigitalAgreement& DigitalAgreement)
{
	checkf(DigitalAgreement != ECsDigitalAgreement::ECsDigitalAgreement_MAX, TEXT("UCsManager_DigitalAgreement::HasBeenAccepted: DigitalAgreement: ECsDigitalAgreement_MAX (MAX) is NOT Valid."));

	return States[(uint8)DigitalAgreement].IsAccepted();
}

#pragma endregion Accept

// Do Not Accept
#pragma region

void UCsManager_DigitalAgreement::DoNotAccept(const ECsDigitalAgreement& DigitalAgreement)
{
	checkf(DigitalAgreement != ECsDigitalAgreement::ECsDigitalAgreement_MAX, TEXT("UCsManager_DigitalAgreement::DoNotAccept: DigitalAgreement: ECsDigitalAgreement_MAX (MAX) is NOT Valid."));

	States[(uint8)DigitalAgreement].DoNotAccept();

	OnDoNotAccept_Event.Broadcast(DigitalAgreement);
	OnDoNotAccept_ScriptEvent.Broadcast(DigitalAgreement);
}

#pragma endregion Do Not Accept