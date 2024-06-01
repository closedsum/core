// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Fade/CsManager_Fade.h"
#include "CsFade.h"

// CVar
#include "Managers/Fade/CsCVars_Manager_Fade.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Data/CsFadeLibrary_DataRootSet.h"
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Settings
#include "Managers/Fade/CsSettings_Manager_Fade.h"
// UI
#include "Managers/Fade/CsUserWidget_Fade.h"
#include "Components/Image.h"
// Game
#include "Engine/GameInstance.h"

#if WITH_EDITOR
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Managers/Fade/CsGetManagerFade.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_Fade)

// Cached
#pragma region

namespace NCsManagerFade
{
	namespace NCached
	{
		namespace Str
		{
			// Singleton
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Fade, Init);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Fade, CreateFadeWidget);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Fade, Fade);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Fade, Fade_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Fade, SafeFade);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Fade, StopFade);
		}

		namespace Name
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Fade, Fade_Internal);
		}
	}
}

#pragma endregion Cached

// static initializations
UCsManager_Fade* UCsManager_Fade::s_Instance;
bool UCsManager_Fade::s_bShutdown = false;

UCsManager_Fade::UCsManager_Fade(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	FadeWidget(nullptr),
	FadeHandle(),
	OnFadeComplete_Event(),
	OnFadeComplete_ScriptEvent(),
	bFadeComplete(false)
{
}

#define USING_NS_CACHED using namespace NCsManagerFade::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsManagerFade::NCached; \
	const FString& Context = Str::__FunctionName
#define CoroutineSchedulerLibrary NCsCoroutine::NScheduler::FLibrary

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_Fade* UCsManager_Fade::Get(const UObject* InRoot /*= nullptr*/)
{
	return Get_GetManagerFade(InRoot)->GetManager_Fade();
}

/*static*/ UCsManager_Fade* UCsManager_Fade::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerFade* GetManagerFade = GetSafe_GetManagerFade(Context, InRoot, Log))
		return GetManagerFade->GetManager_Fade();
	return nullptr;
}

#endif // #if WITH_EDITOR

/*static*/ void UCsManager_Fade::Init(UObject* InRoot, TSubclassOf<UCsManager_Fade> ManagerFadeClass, UObject* InOuter /*= nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerFade* GetManagerFade = Get_GetManagerFade(InRoot);

	UCsManager_Fade* Manager_Fade = GetManagerFade->GetManager_Fade();

	if (!Manager_Fade)
	{
		Manager_Fade = NewObject<UCsManager_Fade>(InOuter ? InOuter : InRoot, ManagerFadeClass, TEXT("Manager_Fade_Singleton"), RF_Transient | RF_Public);

		GetManagerFade->SetManager_Fade(Manager_Fade);

		Manager_Fade->SetMyRoot(InRoot);
		Manager_Fade->Initialize();
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Fade>(GetTransientPackage(), ManagerFadeClass, TEXT("Manager_Fade_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Fade::Init(UObject* InRoot, UObject* InOuter /*= nullptr*/)
{
	using namespace NCsManagerFade::NCached;

	const FString& Context = Str::Init;

	const FCsSettings_Manager_Fade& Settings = FCsSettings_Manager_Fade::Get();

	Init(InRoot, Settings.LoadClassChecked(Context), InOuter);
}

/*static*/ void UCsManager_Fade::Shutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerFade* GetManagerFade = Get_GetManagerFade(InRoot);
	UCsManager_Fade* Manager_Fade     = GetManagerFade->GetManager_Fade();
	Manager_Fade->CleanUp();
	Manager_Fade->SetMyRoot(nullptr);

	GetManagerFade->SetManager_Fade(nullptr);
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

/*static*/ ICsGetManagerFade* UCsManager_Fade::Get_GetManagerFade(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Fade::Get_GetManagerFade: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Fade::Get_GetManagerFade: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Fade::Get_GetManagerFade: Manager_Singleton is NULL."));

	ICsGetManagerFade* GetManagerFade = Cast<ICsGetManagerFade>(Manager_Singleton);

	checkf(GetManagerFade, TEXT("UCsManager_Fade::Get_GetManagerFade: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerFade."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerFade;
}

/*static*/ ICsGetManagerFade* UCsManager_Fade::GetSafe_GetManagerFade(const FString & Context, const UObject * InRoot, void(*Log)(const FString&) /*=nullptr*/)
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
	return Cast<ICsGetManagerFade>(Manager_Singleton);
}

#endif // #if WITH_EDITOR

void UCsManager_Fade::Initialize()
{
}

void UCsManager_Fade::CleanUp()
{
	if (IsValid(FadeWidget))
	{
		//FadeWidget->MarkAsGarbage();

		FadeWidget->SetVisibility(ESlateVisibility::Collapsed);

		if (FadeWidget->GetParent())
			FadeWidget->RemoveFromParent();
		FadeWidget = nullptr;
	}
}

	// Root
#pragma region

void UCsManager_Fade::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

void UCsManager_Fade::CreateFadeWidget()
{
	SET_CONTEXT(CreateFadeWidget);

	if (IsValid(FadeWidget))
	{
		FadeWidget->SetVisibility(ESlateVisibility::Collapsed);

		if (FadeWidget->GetParent())
			FadeWidget->RemoveFromParent();
		FadeWidget = nullptr;

#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
		{
			UE_LOG(LogCsFade, Warning, TEXT("%s: Marking FadeWidget to be destroyed."), *Context);
		}
#endif // #if !UE_BUILD_SHIPPING
	}

	typedef NCsFade::NDataRootSet::FLibrary DataRootSetLibrary;

	UClass* Class = DataRootSetLibrary::GetFadeWidgetClassChecked(Context, MyRoot);
	FadeWidget	  = CreateWidget<UCsUserWidget_Fade>(Cast<UGameInstance>(MyRoot), Class);

	static const int32 ZOrder = 1000;
	FadeWidget->AddToViewport(ZOrder);
	FadeWidget->SetVisibility(ESlateVisibility::Collapsed);

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
	{
		UE_LOG(LogCsFade, Warning, TEXT("%s: Creating FadeWidget and adding to viewport."), *Context);
	}
#endif // #if !UE_BUILD_SHIPPING
}

#define ParamsType NCsFade::FParams
void UCsManager_Fade::Fade(const ParamsType& Params)
{
#undef ParamsType
	SET_CONTEXT(Fade);

	CS_IS_VALID_CHECKED(Params);

	bFadeComplete = false;

	if (Params.GetTime() == 0.0f)
	{
	#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
		{
			UE_LOG(LogCsFade, Warning, TEXT("%s: Start, Perform, and End Fade"), *Context);
			UE_LOG(LogCsFade, Warning, TEXT(" From: %s"), *(Params.GetFrom().ToString()));
			UE_LOG(LogCsFade, Warning, TEXT(" To: %s"), *(Params.GetTo().ToString()));
			UE_LOG(LogCsFade, Warning, TEXT(" Percent: %f"), 1.0f);
			UE_LOG(LogCsFade, Warning, TEXT(" ElapsedTime: %f"), 0.0f);
		}
	#endif // #if !UE_BUILD_SHIPPING

		FadeWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		FadeWidget->SetColorAndOpacity(Params.GetTo());

		if (Params.GetbCollapseOnEnd())
		{
			FadeWidget->SetVisibility(ESlateVisibility::Collapsed);
		}

		bFadeComplete = true;

		OnFadeComplete_Event.Broadcast();
		OnFadeComplete_ScriptEvent.Broadcast();
		return;
	}

	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;

	CoroutineSchedulerLibrary::EndAndInvalidateChecked(Context, MyRoot, UpdateGroup, FadeHandle);

	PayloadType* Payload = CoroutineSchedulerLibrary::AllocatePayloadChecked(Context, MyRoot, UpdateGroup);

	typedef UCsManager_Fade ClassType;
	#define COROUTINE Fade_Internal

	Payload->Init<ClassType>(Context, this, &ClassType::COROUTINE, MyRoot, UpdateGroup, Str::COROUTINE, Name::COROUTINE);

	#undef COROUTINE

	CS_COROUTINE_PAYLOAD_PASS_FLAG_START
	CS_COROUTINE_PAYLOAD_PASS_FLOAT_START
	CS_COROUTINE_PAYLOAD_PASS_COLOR_START

	// From
	CS_COROUTINE_PAYLOAD_PASS_COLOR(Payload, Params.GetFrom());
	// To
	CS_COROUTINE_PAYLOAD_PASS_COLOR(Payload, Params.GetTo());
	// Time
	CS_COROUTINE_PAYLOAD_PASS_FLOAT(Payload, Params.GetTime());
	// bCollapseOnEnd
	CS_COROUTINE_PAYLOAD_PASS_FLAG(Payload, Params.GetbCollapseOnEnd());

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
	{
		UE_LOG(LogCsFade, Warning, TEXT("%s: Starting Fade"), *Context);
		UE_LOG(LogCsFade, Warning, TEXT(" From: %s"), *(Params.GetFrom().ToString()));
		UE_LOG(LogCsFade, Warning, TEXT(" To: %s"), *(Params.GetTo().ToString()));
		UE_LOG(LogCsFade, Warning, TEXT(" Time: %f"), Params.GetTime());
		UE_LOG(LogCsFade, Warning, TEXT(" bCollapseOnEnd: %s"), Params.GetbCollapseOnEnd() ? TEXT("True") : TEXT("False"));
	}
#endif // #if !UE_BUILD_SHIPPING

	FadeHandle = CoroutineSchedulerLibrary::StartChecked(Context, MyRoot, Payload);
}

char UCsManager_Fade::Fade_Internal(FCsRoutine* R)
{
	SET_CONTEXT(Fade_Internal);

	CS_COROUTINE_READ_FLAG_START
	CS_COROUTINE_READ_FLOAT_START
	CS_COROUTINE_READ_COLOR_START

	// From
	CS_COROUTINE_READ_COLOR_CONST_REF(R, From);
	// To
	CS_COROUTINE_READ_COLOR_CONST_REF(R, To);
	// Time
	CS_COROUTINE_READ_FLOAT_CONST_REF(R, Time);
	// bCollapseOnEnd
	CS_COROUTINE_READ_FLAG_CONST_REF(R, bCollapseOnEnd);

	const float Percent = Time > 0.0f ? R->ElapsedTime.Time / Time : 0.0f;

	CS_COROUTINE_BEGIN(R);

	FadeWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	FadeWidget->SetColorAndOpacity(From);

	do
	{
		{
			FadeWidget->SetColorAndOpacity(FLinearColor::LerpUsingHSV(From, To, Percent));

		#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
			{
				UE_LOG(LogCsFade, Warning, TEXT("%s: Performing Fade"), *Context);
				UE_LOG(LogCsFade, Warning, TEXT(" From: %s"), *(From.ToString()));
				UE_LOG(LogCsFade, Warning, TEXT(" To: %s"), *(To.ToString()));
				UE_LOG(LogCsFade, Warning, TEXT(" Percent: %f"), Percent);
				UE_LOG(LogCsFade, Warning, TEXT(" ElapsedTime: %f"), R->ElapsedTime.Time);
			}
		#endif // #if !UE_BUILD_SHIPPING

			CS_COROUTINE_YIELD(R);
		}
	} while (R->ElapsedTime.Time < Time);

	FadeWidget->SetColorAndOpacity(To);

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
	{
		UE_LOG(LogCsFade, Warning, TEXT("%s: Ending Fade"), *Context);
		UE_LOG(LogCsFade, Warning, TEXT(" To: %s"), *(To.ToString()));
	}
#endif // #if !UE_BUILD_SHIPPING

	if (bCollapseOnEnd)
	{
		FadeWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	bFadeComplete = true;

	OnFadeComplete_Event.Broadcast();
	OnFadeComplete_ScriptEvent.Broadcast();

	CS_COROUTINE_END(R);
}

#define ParamsType NCsFade::FParams
void UCsManager_Fade::SafeFade(const ParamsType& Params)
{
#undef ParamsType
	SET_CONTEXT(SafeFade);

	void(*Log)(const FString&) = &NCsFade::FLog::Warning;

	CS_IS_VALID_EXIT(Params)

	if (!IsValid(FadeWidget))
	{
#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
		{
			UE_LOG(LogCsFade, Warning, TEXT("%s: CreateFadeWidget."), *Context);
		}
#endif // #if !UE_BUILD_SHIPPING

		CreateFadeWidget();
	}

	if (!FadeWidget->IsInViewport())
	{
#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
		{
			UE_LOG(LogCsFade, Warning, TEXT("%s: FadeWidget is NOT in the viewport. Adding to viewport."), *Context);
		}
#endif // #if !UE_BUILD_SHIPPING

		static const int32 ZOrder = 1000;
		FadeWidget->AddToViewport(ZOrder);
	}

	Fade(Params);
}

void UCsManager_Fade::StopFade()
{
	SET_CONTEXT(StopFade);

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
	{
		UE_LOG(LogCsFade, Warning, TEXT("%s: Stopping Fade"), *Context);
	}
#endif // #if !UE_BUILD_SHIPPING

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;

	CoroutineSchedulerLibrary::EndAndInvalidateChecked(Context, MyRoot, UpdateGroup, FadeHandle);

	bFadeComplete = false;
}

void UCsManager_Fade::ClearFade()
{
	StopFade();
	FadeWidget->SetVisibility(ESlateVisibility::Collapsed);
}

#undef USING_NS_CACHED
#undef SET_CONTEXT
#undef CoroutineSchedulerLibrary