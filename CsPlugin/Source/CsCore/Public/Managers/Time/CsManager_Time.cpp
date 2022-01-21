// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsManager_Time.h"
#include "CsCore.h"

// Library
#include "Managers/Input/CsLibrary_Manager_Input.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Managers
#include "Managers/Input/CsManager_Input.h"
// Console Command
#include "Managers/Time/CsConsoleCommand_Manager_Time.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Time/CsGetManagerTime.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
#endif // #if WITH_EDITOR

// static initializations
UCsManager_Time* UCsManager_Time::s_Instance;
bool UCsManager_Time::s_bShutdown = false;

// Cached
#pragma region

namespace NCsManagerTime
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Time, SetupInputListener);
		}
	}
}

#pragma endregion Cached

UCsManager_Time::UCsManager_Time(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_Time* UCsManager_Time::Get(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerTime(InRoot)->GetManager_Time();
}

/*static*/ UCsManager_Time* UCsManager_Time::GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerTime* GetManagerTime = GetSafe_GetManagerTime(Context, InRoot, Log))
		return GetManagerTime->GetManager_Time();
	return nullptr;
}

#endif // #if WITH_EDITOR

/*static*/ void UCsManager_Time::Init(UObject* InRoot)
{
#if WITH_EDITOR
	ICsGetManagerTime* GetManagerTime = Get_GetManagerTime(InRoot);

	UCsManager_Time* Manager_Time = NewObject<UCsManager_Time>(InRoot, UCsManager_Time::StaticClass(), TEXT("Manager_Time_Singleton"), RF_Transient | RF_Public);

	GetManagerTime->SetManager_Time(Manager_Time);

	Manager_Time->SetMyRoot(InRoot);
	Manager_Time->Initialize();
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Time>(GetTransientPackage(), UCsManager_Time::StaticClass(), TEXT("Manager_Time_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Time::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerTime* GetManagerTime = Get_GetManagerTime(InRoot);
	UCsManager_Time* Manager_Time	  = GetManagerTime->GetManager_Time();
	Manager_Time->CleanUp();

	GetManagerTime->SetManager_Time(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerTime* UCsManager_Time::Get_GetManagerTime(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Time::Get: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Time::Get: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Time::Get: Manager_Singleton is NULL."));

	ICsGetManagerTime* GetManagerTime = Cast<ICsGetManagerTime>(Manager_Singleton);

	checkf(GetManagerTime, TEXT("UCsManager_Time::Get: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerTime."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerTime;
}

/*static*/ ICsGetManagerTime* UCsManager_Time::GetSafe_GetManagerTime(const FString& Context, UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
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
	return Cast<ICsGetManagerTime>(Manager_Singleton);
}

#endif // #if WITH_EDITOR

void UCsManager_Time::Initialize()
{
	// Time Groups
	{
		const int32& Count = EMCsUpdateGroup::Get().Num();

		UpdateGroups.Reset(Count);

		for (const FECsUpdateGroup& Group : EMCsUpdateGroup::Get())
		{
			UpdateGroups.AddDefaulted();
		}
	}
	// Pause
	{
		const int32& Count = EMCsUpdateGroup::Get().Num();

		OnPause_Events.Reset(Count);
		OnPause_Events.AddDefaulted(Count);
	}

#if WITH_EDITOR
	typedef NCsGameInstance::FLibrary GameInstanceLibrary;

	if (!GameInstanceLibrary::IsSafe(MyRoot))
		return;
#endif // #if WITH_EDITOR

	typedef NCsTime::NManager::FConsoleCommand ConsoleCommandManagerType;

	Manager_ConsoleCommand = new ConsoleCommandManagerType(MyRoot);
}

void UCsManager_Time::CleanUp()
{
	delete Manager_ConsoleCommand;
	Manager_ConsoleCommand = nullptr;
}

#pragma endregion Singleton

void UCsManager_Time::Start(const FECsUpdateGroup& Group)
{
	UpdateGroups[Group.GetValue()].Start();
}


// Update
#pragma region

void UCsManager_Time::Update(const FECsUpdateGroup& Group, const float& DeltaTime)
{
	UpdateGroups[Group.GetValue()].Update(DeltaTime);

	OnUpdate_ScriptEvent.Broadcast(Group, GetScaledDeltaTime(Group));
}

void UCsManager_Time::Update(const FECsUpdateGroup& Group, const float& DeltaTime, const float& Time, const float& RealTime)
{
	UpdateGroups[Group.GetValue()].Update(DeltaTime, Time, RealTime);

	OnUpdate_ScriptEvent.Broadcast(Group, GetScaledDeltaTime(Group));
}

#pragma endregion Update

FCsTime UCsManager_Time::GetTimeNow(const FECsUpdateGroup& Group)
{
	FCsTime Time = GetTime(Group);

	Time.DateTime = FDateTime::Now();

	return Time;
}

void UCsManager_Time::SetupInputListener()
{
	using namespace NCsManagerTime::NCached;

	const FString& Context = Str::SetupInputListener;

	typedef NCsInput::NManager::FLibrary InputManagerLibrary;

	UCsManager_Input* Manager_Input = InputManagerLibrary::GetFirstChecked(Context, MyRoot);

	Manager_Input->OnAnyKey_Pressed_Event.AddUObject(this, &UCsManager_Time::OnAnyKey_Pressed);
	Manager_Input->OnAnyKey_Released_Event.AddUObject(this, &UCsManager_Time::OnAnyKey_Released);
}

void UCsManager_Time::OnAnyKey_Pressed(const FKey& Key)
{
	UCsDeveloperSettings* Settings				 = GetMutableDefault<UCsDeveloperSettings>();
	const FCsSettings_Manager_Time& TimeSettings = Settings->Manager_Time;

	// Check for Pause
	for (const TPair<FECsUpdateGroup, FCsSet_Key>& Pair : TimeSettings.TogglePauseGroupByKeysMap)
	{
		const FECsUpdateGroup& Group = Pair.Key;
		const TSet<FKey>& Keys		 = Pair.Value.Set;

		if (Keys.Contains(Key))
		{
			if (IsPaused(Group))
				Unpause(Group);
			else
				Pause(Group);
		}
	}
	// Check for Custom Update
	for (const TPair<FECsUpdateGroup, FCsSettings_Manager_Time_CustomUpdate>& Pair : TimeSettings.CustomUpdateMap)
	{
		const FECsUpdateGroup& Group									  = Pair.Key;
		const FCsSettings_Manager_Time_CustomUpdate& CustomUpdateSettings = Pair.Value;

		const TSet<FKey>& Keys = CustomUpdateSettings.Keys;

		if (Keys.Contains(Key))
		{
			// NOTE: For now this will only call SetCustom for the Group if the Group is Paused
			if (IsPaused(Group))
			{
				SetCustom(Group, !CustomUpdateSettings.bAllowSustained);
				SetCustomDeltaTime(Group, FCsDeltaTime(CustomUpdateSettings.DeltaTime));
			}
		}
	}
}

void UCsManager_Time::OnAnyKey_Released(const FKey& Key)
{
	UCsDeveloperSettings* Settings				 = GetMutableDefault<UCsDeveloperSettings>();
	const FCsSettings_Manager_Time& TimeSettings = Settings->Manager_Time;

	// Check for Custom Update
	for (const TPair<FECsUpdateGroup, FCsSettings_Manager_Time_CustomUpdate>& Pair : TimeSettings.CustomUpdateMap)
	{
		const FECsUpdateGroup& Group									  = Pair.Key;
		const FCsSettings_Manager_Time_CustomUpdate& CustomUpdateSettings = Pair.Value;

		const TSet<FKey>& Keys = CustomUpdateSettings.Keys;

		if (Keys.Contains(Key))
		{
			ClearCustom(Group);
		}
	}
}