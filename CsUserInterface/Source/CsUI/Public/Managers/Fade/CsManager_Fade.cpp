// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Fade/CsManager_Fade.h"
#include "CsUI.h"

// CVar
#include "Managers/Fade/CsCVars_Manager_Fade.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Data/CsUILibrary_DataRootSet.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// UI
#include "Managers/Fade/CsUserWidget_Fade.h"
#include "Components/Image.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Fade/CsGetManagerFade.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerFade
{
	namespace NCached
	{
		namespace Str
		{
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
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

#if WITH_EDITOR
/*static*/ UCsManager_Fade* UCsManager_Fade::Get(const UObject* InRoot /*= nullptr*/)
{
	return Get_GetManagerFade(InRoot)->GetManager_Fade();
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

/*static*/ UCsManager_Fade* UCsManager_Fade::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerFade* GetManagerFade = GetSafe_GetManagerFade(Context, InRoot, Log))
		return GetManagerFade->GetManager_Fade();
	return nullptr;
}

#endif // #if WITH_EDITOR

void UCsManager_Fade::Initialize()
{
}

void UCsManager_Fade::CleanUp()
{
	if (FadeWidget &&
		!FadeWidget->IsPendingKill())
	{
		FadeWidget->MarkPendingKill();
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
	using namespace NCsManagerFade::NCached;

	const FString& Context = Str::CreateFadeWidget;

	if (FadeWidget &&
		!FadeWidget->IsPendingKill())
	{
		FadeWidget->SetVisibility(ESlateVisibility::Collapsed);
		FadeWidget->MarkPendingKill();
		FadeWidget = nullptr;

#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
		{
			UE_LOG(LogCsUI, Warning, TEXT("%s: Marking FadeWidget to be destroyed."), *Context);
		}
#endif // #if !UE_BUILD_SHIPPING
	}

	typedef NCsUIDataRootSet::FLibrary DataRootSetLibrary;

	UObject* ContextRoot				= DataRootSetLibrary::GetContextRootChecked(Context, MyRoot);
	const FCsUIDataRootSet& DataRootSet = DataRootSetLibrary::GetChecked(Context, ContextRoot);

	UClass* Class = DataRootSet.FadeWidget.Get();

	checkf(Class, TEXT("%s: FCsUIDataRootSet.FadeWidget is NULL."), *Context);

	FadeWidget = CreateWidget<UCsUserWidget_Fade>(Cast<UGameInstance>(MyRoot), Class);

	static const int32 ZOrder = 1000;
	FadeWidget->AddToViewport(ZOrder);
	FadeWidget->SetVisibility(ESlateVisibility::Collapsed);

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
	{
		UE_LOG(LogCsUI, Warning, TEXT("%s: Creating FadeWidget and adding to viewport."), *Context);
	}
#endif // #if !UE_BUILD_SHIPPING
}

#define ParamsType NCsFade::FParams
void UCsManager_Fade::Fade(const ParamsType& Params)
{
#undef ParamsType

	using namespace NCsManagerFade::NCached;

	const FString& Context = Str::Fade;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	UObject* ContextRoot = CoroutineSchedulerLibrary::GetContextRootChecked(Context, MyRoot);

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(MyRoot);

	Scheduler->End(UpdateGroup, FadeHandle);

	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE Fade_Internal

	Payload->CoroutineImpl.BindUObject(this, &UCsManager_Fade::COROUTINE);
	Payload->StartTime = UCsManager_Time::Get(ContextRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	// From
	static const int32 FROM = 0;
	Payload->SetValue_Color(FROM, Params.From);
	// To
	static const int32 TO = 1;
	Payload->SetValue_Color(TO, Params.To);
	// Time
	static const int32 TIME = 0;
	Payload->SetValue_Float(TIME, Params.Time);
	// bCollapseOnEnd
	static const int32 COLLAPSE = 0;
	Payload->SetValue_Flag(COLLAPSE, Params.bCollapseOnEnd);

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
	{
		UE_LOG(LogCsUI, Warning, TEXT("%s: Starting Fade"), *Context);
		UE_LOG(LogCsUI, Warning, TEXT(" From: %s"), *(Params.From.ToString()));
		UE_LOG(LogCsUI, Warning, TEXT(" To: %s"), *(Params.To.ToString()));
		UE_LOG(LogCsUI, Warning, TEXT(" Time: %f"), Params.Time);
		UE_LOG(LogCsUI, Warning, TEXT(" bCollapseOnEnd: %s"), Params.bCollapseOnEnd ? TEXT("True") : TEXT("False"));
	}
#endif // #if !UE_BUILD_SHIPPING

	FadeHandle = Scheduler->Start(Payload);
}

char UCsManager_Fade::Fade_Internal(FCsRoutine* R)
{
	using namespace NCsManagerFade::NCached;

	const FString& Context = Str::Fade_Internal;

	// From
	static const int32 FROM = 0;
	const FLinearColor& From = R->GetValue_Color(FROM);
	// To
	static const int32 TO = 1;
	const FLinearColor& To = R->GetValue_Color(TO);
	// Time
	static const int32 TIME = 0;
	const float& Time = R->GetValue_Float(TIME);
	// bCollapseOnEnd
	static const int32 COLLAPSE = 0;
	const bool& bCollapseOnEnd = R->GetValue_Flag(COLLAPSE);

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
				UE_LOG(LogCsUI, Warning, TEXT("%s: Performing Fade"), *Context);
				UE_LOG(LogCsUI, Warning, TEXT(" From: %s"), *(From.ToString()));
				UE_LOG(LogCsUI, Warning, TEXT(" To: %s"), *(To.ToString()));
				UE_LOG(LogCsUI, Warning, TEXT(" Percent: %f"), Percent);
				UE_LOG(LogCsUI, Warning, TEXT(" ElapsedTime: %f"), R->ElapsedTime.Time);
			}
#endif // #if !UE_BUILD_SHIPPING

			CS_COROUTINE_YIELD(R);
		}
	} while (R->ElapsedTime.Time < Time);

	FadeWidget->SetColorAndOpacity(To);

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
	{
		UE_LOG(LogCsUI, Warning, TEXT("%s: Ending Fade"), *Context);
		UE_LOG(LogCsUI, Warning, TEXT(" To: %s"), *(To.ToString()));
	}
#endif // #if !UE_BUILD_SHIPPING

	if (bCollapseOnEnd)
	{
		FadeWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	CS_COROUTINE_END(R);
}

#define ParamsType NCsFade::FParams
void UCsManager_Fade::SafeFade(const ParamsType& Params)
{
#undef ParamsType

	using namespace NCsManagerFade::NCached;

	const FString& Context = Str::SafeFade;

	if (!FadeWidget ||
		FadeWidget->IsPendingKill())
	{
#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
		{
			UE_LOG(LogCsUI, Warning, TEXT("%s: CreateFadeWidget."), *Context);
		}
#endif // #if !UE_BUILD_SHIPPING

		CreateFadeWidget();
	}

	if (!FadeWidget->IsInViewport())
	{
#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
		{
			UE_LOG(LogCsUI, Warning, TEXT("%s: FadeWidget is NOT in the viewport. Adding to viewport."), *Context);
		}
#endif // #if !UE_BUILD_SHIPPING

		static const int32 ZOrder = 1000;
		FadeWidget->AddToViewport(ZOrder);
	}

	Fade(Params);
}

void UCsManager_Fade::StopFade()
{
	using namespace NCsManagerFade::NCached;

	const FString& Context = Str::StopFade;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	UObject* ContextRoot = CoroutineSchedulerLibrary::GetContextRootChecked(Context, MyRoot);

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(ContextRoot);

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerFade))
	{
		UE_LOG(LogCsUI, Warning, TEXT("%s: Stopping Fade"), *Context);
	}
#endif // #if !UE_BUILD_SHIPPING

	Scheduler->End(UpdateGroup, FadeHandle);
}

void UCsManager_Fade::ClearFade()
{
	StopFade();
	FadeWidget->SetVisibility(ESlateVisibility::Collapsed);
}