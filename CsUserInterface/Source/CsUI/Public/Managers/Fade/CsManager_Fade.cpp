// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Fade/CsManager_Fade.h"
#include "CsUI.h"

// CVar

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Data/CsUILibrary_DataRootSet.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"
// UI
#include "Managers/Fade/CsUserWidget_Fade.h"
#include "Components/Image.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Fade/CsGetManagerFade.h"

#include "Library/CsLibrary_Common.h"

#include "Engine/Engine.h"
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
/*static*/ UCsManager_Fade* UCsManager_Fade::Get(UObject* InRoot /*= nullptr*/)
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

/*static*/ void UCsManager_Fade::Shutdown(UObject* InRoot /*=nullptr*/)
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

/*static*/ ICsGetManagerFade* UCsManager_Fade::Get_GetManagerFade(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Fade::Get_GetManagerFade: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Fade::Get_GetManagerFade: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Fade::Get_GetManagerFade: Manager_Singleton is NULL."));

	ICsGetManagerFade* GetManagerFade = Cast<ICsGetManagerFade>(Manager_Singleton);

	checkf(GetManagerFade, TEXT("UCsManager_Fade::Get_GetManagerFade: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerFade."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerFade;
}

/*static*/ ICsGetManagerFade* UCsManager_Fade::GetSafe_GetManagerFade(UObject* Object)
{
	if (!Object)
		return nullptr;

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
		return nullptr;

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
		return nullptr;

	return Cast<ICsGetManagerFade>(Manager_Singleton);
}

/*static*/ UCsManager_Fade* UCsManager_Fade::GetSafe(UObject* Object)
{
	if (ICsGetManagerFade* GetManagerFade = GetSafe_GetManagerFade(Object))
		return GetManagerFade->GetManager_Fade();
	return nullptr;
}

/*static*/ UCsManager_Fade* UCsManager_Fade::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsManager_Fade* Manager = GetSafe(World->GetGameInstance()))
			return Manager;

		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_Fade::GetFromWorldContextObject: Failed to Manager Data of type UCsManager_Fade from GameInstance."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
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
		FadeWidget->MarkPendingKill();
		FadeWidget = nullptr;
	}

	typedef NCsUIDataRootSet::FLibrary DataRootSetLibrary;

	UObject* ContextRoot				= DataRootSetLibrary::GetContextRootChecked(Context, MyRoot);
	const FCsUIDataRootSet& DataRootSet = DataRootSetLibrary::GetChecked(Context, ContextRoot);

	UClass* Class = DataRootSet.FadeWidget.Get();

	checkf(Class, TEXT("%s: FCsUIDataRootSet.FadeWidget is NULL."), *Context);

	FadeWidget = CreateWidget<UCsUserWidget_Fade>(Cast<UGameInstance>(ContextRoot), Class);

	static const int32 ZOrder = 1000;
	FadeWidget->AddToViewport(ZOrder);
	FadeWidget->SetVisibility(ESlateVisibility::Collapsed);
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

	FadeHandle = Scheduler->Start(Payload);
}

char UCsManager_Fade::Fade_Internal(FCsRoutine* R)
{
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

			CS_COROUTINE_YIELD(R);
		}
	} while (R->ElapsedTime.Time < Time);

	FadeWidget->SetColorAndOpacity(To);

	if (bCollapseOnEnd)
	{
		FadeWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	CS_COROUTINE_END(R);
}

void UCsManager_Fade::StopFade()
{
	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(this);

	Scheduler->End(UpdateGroup, FadeHandle);
}

void UCsManager_Fade::ClearFade()
{
	StopFade();
	FadeWidget->SetVisibility(ESlateVisibility::Collapsed);
}