// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Performance/CsManager_Performance.h"
#include "CsPerformance.h"

// CVar
#include "Managers/Performance/CsCVars_Manager_Performance.h"
#include "CsCVars_Performance.h"
// Types
#include "CsMacro_Misc.h"
// Library
	// Common
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsPerformanceSettings.h"
// UI
#include "UI/CsPerformanceUI.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

#if WITH_EDITOR
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Managers/Performance/CsGetManagerPerformance.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_Performance)

// Cached
#pragma region

namespace NCsManagerPerformance
{
	namespace NCached
	{
		namespace Str
		{
			// Singleton
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Performance, Init);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Performance, CreatePerformanceWidget);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Performance, ConditionalCreatePerformanceWidget);
		}
	}
}

#pragma endregion Cached

// static initializations
UCsManager_Performance* UCsManager_Performance::s_Instance;
bool UCsManager_Performance::s_bShutdown = false;

UCsManager_Performance::UCsManager_Performance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	PerformanceWidget(nullptr),
	PerformanceWidgetInterface(nullptr)
{

}

#define USING_NS_CACHED using namespace NCsManagerPerformance::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsManagerPerformance::NCached; \
	const FString& Context = Str::__FunctionName

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_Performance* UCsManager_Performance::Get(const UObject* InRoot /*= nullptr*/)
{
	return Get_GetManagerPerformance(InRoot)->GetManager_Performance();
}

/*static*/ UCsManager_Performance* UCsManager_Performance::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerPerformance* GetManagerPerformance = GetSafe_GetManagerPerformance(Context, InRoot, Log))
		return GetManagerPerformance->GetManager_Performance();
	return nullptr;
}

#endif // #if WITH_EDITOR

/*static*/ void UCsManager_Performance::Init(UObject* InRoot, TSubclassOf<UCsManager_Performance> ManagerPerformanceClass, UObject* InOuter /*= nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerPerformance* GetManagerPerformance = Get_GetManagerPerformance(InRoot);

	UCsManager_Performance* Manager_Performance = GetManagerPerformance->GetManager_Performance();

	if (!Manager_Performance)
	{
		Manager_Performance = NewObject<UCsManager_Performance>(InOuter ? InOuter : InRoot, ManagerPerformanceClass, TEXT("Manager_Performance_Singleton"), RF_Transient | RF_Public);

		GetManagerPerformance->SetManager_Performance(Manager_Performance);

		Manager_Performance->SetMyRoot(InRoot);
		Manager_Performance->Initialize();
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Performance>(GetTransientPackage(), ManagerPerformanceClass, TEXT("Manager_Performance_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Performance::Init(UObject* InRoot, UObject* InOuter /*= nullptr*/)
{
	using namespace NCsManagerPerformance::NCached;

	const FString& Context = Str::Init;

	const FCsSettings_Manager_Performance& Settings = FCsSettings_Manager_Performance::Get();

	Init(InRoot, Settings.LoadClassChecked(Context), InOuter);
}

/*static*/ void UCsManager_Performance::Shutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerPerformance* GetManagerPerformance = Get_GetManagerPerformance(InRoot);
	UCsManager_Performance* Manager_Performance     = GetManagerPerformance->GetManager_Performance();
	Manager_Performance->CleanUp();
	Manager_Performance->SetMyRoot(nullptr);

	GetManagerPerformance->SetManager_Performance(nullptr);
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

/*static*/ ICsGetManagerPerformance* UCsManager_Performance::Get_GetManagerPerformance(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Performance::Get_GetManagerPerformance: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Performance::Get_GetManagerPerformance: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Performance::Get_GetManagerPerformance: Manager_Singleton is NULL."));

	ICsGetManagerPerformance* GetManagerPerformance = Cast<ICsGetManagerPerformance>(Manager_Singleton);

	checkf(GetManagerPerformance, TEXT("UCsManager_Performance::Get_GetManagerPerformance: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerPerformance."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerPerformance;
}

/*static*/ ICsGetManagerPerformance* UCsManager_Performance::GetSafe_GetManagerPerformance(const FString & Context, const UObject * InRoot, void(*Log)(const FString&) /*=nullptr*/)
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
	return Cast<ICsGetManagerPerformance>(Manager_Singleton);
}

#endif // #if WITH_EDITOR

void UCsManager_Performance::Initialize()
{
	UCsPerformanceSettings* Settings = GetMutableDefault<UCsPerformanceSettings>();

	// FPS
	{
		bool Toggle = CsCVarShowPerformanceFPS->GetBool();

		CsCVarShowPerformanceFPS->Set(Toggle | Settings->bShowFPS, ECVF_SetByConsole);
	}
}

void UCsManager_Performance::CleanUp()
{
	if (IsValid(PerformanceWidget))
	{
		//PerformanceWidget->MarkAsGarbage();

		PerformanceWidget->SetVisibility(ESlateVisibility::Collapsed);

		if (PerformanceWidget->GetParent())
			PerformanceWidget->RemoveFromParent();
		PerformanceWidget = nullptr;
	}
}

	// Root
#pragma region

void UCsManager_Performance::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

void UCsManager_Performance::CreatePerformanceWidget()
{
	SET_CONTEXT(CreatePerformanceWidget);

	if (IsValid(PerformanceWidget))
	{
		PerformanceWidget->SetVisibility(ESlateVisibility::Collapsed);

		if (PerformanceWidget->GetParent())
			PerformanceWidget->RemoveFromParent();
		PerformanceWidget = nullptr;
		PerformanceWidgetInterface = nullptr;

#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerPerformance))
		{
			UE_LOG(LogCsPerformance, Warning, TEXT("%s: Marking PerformanceWidget to be destroyed."), *Context);
		}
#endif // #if !UE_BUILD_SHIPPING
	}

	const FCsSettings_Performance_UI& Settings = FCsSettings_Performance_UI::Get();

	UClass* Class			   = Settings.LoadClassChecked(Context);
	PerformanceWidget		   = CreateWidget<UUserWidget>(Cast<UGameInstance>(MyRoot), Class);
	PerformanceWidgetInterface = CS_INTERFACE_CAST_CHECKED(PerformanceWidget, UUserWidget, ICsPerformanceUI);

	static const int32 ZOrder = 10000;
	PerformanceWidget->AddToViewport(ZOrder);
	PerformanceWidgetInterface->Init(this);

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerPerformance))
	{
		UE_LOG(LogCsPerformance, Warning, TEXT("%s: Creating PerformanceWidget and adding to viewport."), *Context);
	}
#endif // #if !UE_BUILD_SHIPPING
}

void UCsManager_Performance::ConditionalCreatePerformanceWidget()
{
	SET_CONTEXT(ConditionalCreatePerformanceWidget);

	if (!IsValid(PerformanceWidget))
	{
#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerPerformance))
		{
			UE_LOG(LogCsPerformance, Warning, TEXT("%s: CreatePerformanceWidget."), *Context);
		}
#endif // #if !UE_BUILD_SHIPPING

		CreatePerformanceWidget();
	}

	if (!PerformanceWidget->IsInViewport())
	{
#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerPerformance))
		{
			UE_LOG(LogCsPerformance, Warning, TEXT("%s: PerformanceWidget is NOT in the viewport. Adding to viewport."), *Context);
		}
#endif // #if !UE_BUILD_SHIPPING

		static const int32 ZOrder = 10000;
		PerformanceWidget->AddToViewport(ZOrder);
	}
}

#undef USING_NS_CACHED
#undef SET_CONTEXT