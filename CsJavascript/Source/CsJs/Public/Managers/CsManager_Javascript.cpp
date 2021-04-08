// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsManager_Javascript.h"
#include "CsJs.h"

// Library
#include "Library/CsJsLibrary_Common.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
#include "Coroutine/CsRoutine.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Game
#include "Engine/GameInstance.h"
#include "GameFramework/GameStateBase.h"
// Player
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Pawn.h"
// Settings
#include "Settings/CsJsSettings.h"

#include "Engine/World.h"
#include "Engine/Engine.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/CsGetManagerJavascript.h"

#include "Library/CsLibrary_Common.h"

#endif // #if WITH_EDITOR

// Cache
#pragma region

namespace NCsManagerJavascript
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, SetupAndRunGameInstanceEntryPoint_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, SetupGameStateEntryPoint);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, SetupGameStateEntryPoint_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, SetupAndRunGameStateEntryPoint_Internal);
		}

		namespace Name
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Javascript, SetupAndRunGameInstanceEntryPoint_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Javascript, SetupGameStateEntryPoint_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Javascript, SetupAndRunGameStateEntryPoint_Internal);
		}
	}
}

#pragma endregion Cache

// static initializations
UCsManager_Javascript* UCsManager_Javascript::s_Instance;
bool UCsManager_Javascript::s_bShutdown = false;

UCsManager_Javascript::UCsManager_Javascript(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer)
{
	//EditorFile = TEXT("Cs/EntryPoint_Game.js");
}

// Singleton
#pragma region

/*static*/ UCsManager_Javascript* UCsManager_Javascript::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerJavascript(InRoot)->GetManager_Javascript();
#else
	if (s_bShutdown)
		return nullptr;

	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Javascript::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerJavascript(InRoot)->GetManager_Javascript() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Javascript::Init(UObject* InRoot)
{
#if WITH_EDITOR
	ICsGetManagerJavascript* GetManagerJavascript = Get_GetManagerJavascript(InRoot);

	UCsManager_Javascript* Manager_Javascript = GetManagerJavascript->GetManager_Javascript();

	if (!Manager_Javascript)
	{
		Manager_Javascript = NewObject<UCsManager_Javascript>(InRoot, UCsManager_Javascript::StaticClass(), TEXT("Manager_Javascript_Singleton"), RF_Transient | RF_Public);

		GetManagerJavascript->SetManager_Javascript(Manager_Javascript);

		Manager_Javascript->SetMyRoot(InRoot);
		Manager_Javascript->Initialize();
	}
	else
	{
		UE_LOG(LogCsJs, Warning, TEXT("UCsManager_Javascript::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Javascript>(GetTransientPackage(), UCsManager_Javascript::StaticClass(), TEXT("Manager_Creep_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCsJs, Warning, TEXT("UCsManager_Javascript::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Javascript::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerJavascript* GetManagerJavascript = Get_GetManagerJavascript(InRoot);
	UCsManager_Javascript* Manager_Javascript	  = GetManagerJavascript->GetManager_Javascript();

	Manager_Javascript->OnShutdown_ScriptEvent.Broadcast();
	Manager_Javascript->CleanUp();

	GetManagerJavascript->SetManager_Javascript(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsJs, Warning, TEXT("UCsManager_Javascript::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->OnShutdown_ScriptEvent.Broadcast();
	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Javascript::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerJavascript(InRoot)->GetManager_Javascript() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerJavascript* UCsManager_Javascript::Get_GetManagerJavascript(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Javascript::Get_GetManagerJavascript: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Javascript::Get_GetManagerJavascript: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Javascript::Get_GetManagerJavascript: Manager_Singleton is NULL."));

	ICsGetManagerJavascript* GetManagerJavascript = Cast<ICsGetManagerJavascript>(Manager_Singleton);

	checkf(GetManagerJavascript, TEXT("UCsManager_Javascript::Get_GetManagerJavascript: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerJavascript."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerJavascript;
}

/*static*/ ICsGetManagerJavascript* UCsManager_Javascript::GetSafe_GetManagerJavascript(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCsJs, Warning, TEXT("UCsManager_Javascript::GetSafe_GetManagerJavascript: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCsJs, Warning, TEXT("UCsManager_Javascript::GetSafe_GetManagerJavascript: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}
	
	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCsJs, Warning, TEXT("UCsManager_Javascript::GetSafe_GetManagerJavascript: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerJavascript>(Manager_Singleton);
}

/*static*/ UCsManager_Javascript* UCsManager_Javascript::GetSafe(UObject* Object)
{
	if (ICsGetManagerJavascript* GetManagerJavascript = GetSafe_GetManagerJavascript(Object))
		return GetManagerJavascript->GetManager_Javascript();
	return nullptr;
}

/*static*/ UCsManager_Javascript* UCsManager_Javascript::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsManager_Javascript* Manager = GetSafe(World->GetGameInstance()))
			return Manager;

		UE_LOG(LogCsJs, Warning, TEXT("UCsManager_Javascript::GetFromWorldContextObject: Failed to Manager Item of type UCsManager_Javascript from GameInstance."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_Javascript::Initialize()
{
/*
	if (Cast<UGameInstance>(MyRoot))
	{
		SetupAndRunGameInstanceEntryPoint();
		SetupAndRunGameStateEntryPoint();
	}
*/
}

void UCsManager_Javascript::CleanUp()
{
	GameInstanceEntryPoint.Shutdown();
	GameStateEntryPoint.Shutdown();
}

	// Root
#pragma region

void UCsManager_Javascript::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

void UCsManager_Javascript::SetupAndRunGameInstanceEntryPoint()
{
	using namespace NCsManagerJavascript::NCached;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(MyRoot);

	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE SetupAndRunGameInstanceEntryPoint_Internal

	Payload->CoroutineImpl.BindUObject(this, &UCsManager_Javascript::COROUTINE);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	Scheduler->Start(Payload);
}

char UCsManager_Javascript::SetupAndRunGameInstanceEntryPoint_Internal(FCsRoutine* R)
{
	UGameInstance* GameInstance = Cast<UGameInstance>(MyRoot);

	CS_COROUTINE_BEGIN(R);

	typedef NCsJs::NCommon::FLibrary JavascriptCommonLibrary;

	// Setup Isolate and Context
	JavascriptCommonLibrary::SetupIsolateAndContext(this, GameInstanceEntryPoint.Isolate, GameInstanceEntryPoint.Context, false);

	// GameInstance
	JavascriptCommonLibrary::ExposeObject(GameInstanceEntryPoint.Context, TEXT("GameInstance"), GameInstance);

	// Run Javascript
	{
		UCsJsSettings* Settings = GetMutableDefault<UCsJsSettings>();

		checkf(Settings, TEXT("UCsManager_Javascript::SetupAndRunGameInstanceEntryPoint_Internal: Failed to find Settings of type: UCsJsSettings."));

		const FString& FileName = Settings->GameInstanceEntryPointFileName;

		checkf(!FileName.IsEmpty(), TEXT("UCsManager_Javascript::SetupAndRunGameInstanceEntryPoint_Internal: FileName is Empty."));

		JavascriptCommonLibrary::RunFile(GameInstanceEntryPoint.Context, FileName);
	}

	CS_COROUTINE_END(R);
}

void UCsManager_Javascript::RunGameInstanceEntryPoint()
{
	checkf(GameInstanceEntryPoint.Context, TEXT("UCsManager_Javascript::RunGameInstanceEntryPoint: Context is NULL."));

	UCsJsSettings* Settings = GetMutableDefault<UCsJsSettings>();

	checkf(Settings, TEXT("UCsManager_Javascript::RunGameInstanceEntryPoint: Failed to find Settings of type: UCsJsSettings."));

	const FString& FileName = Settings->GameInstanceEntryPointFileName;

	checkf(!FileName.IsEmpty(), TEXT("UCsManager_Javascript::RunGameInstanceEntryPoint: FileName is Empty."));

	typedef NCsJs::NCommon::FLibrary JavascriptCommonLibrary;

	JavascriptCommonLibrary::RunFile(GameInstanceEntryPoint.Context, FileName);
}

void UCsManager_Javascript::CreateGameStateEntryPoint()
{
	typedef NCsJs::NCommon::FLibrary JavascriptCommonLibrary;

	// Setup Isolate and Context
	JavascriptCommonLibrary::SetupIsolateAndContext(this, GameStateEntryPoint.Isolate, GameStateEntryPoint.Context, false);
}

void UCsManager_Javascript::SetupGameStateEntryPoint(UGameInstance* GameInstance /*=nullptr*/)
{
	using namespace NCsManagerJavascript::NCached;

	const FString& Context = Str::SetupGameStateEntryPoint;

	check(GameStateEntryPoint.IsValidChecked(Context));

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(MyRoot);

	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE SetupGameStateEntryPoint_Internal

	Payload->CoroutineImpl.BindUObject(this, &UCsManager_Javascript::COROUTINE);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	static const int32 GAME_INSTANCE = 0;
	Payload->SetValue_Void(GAME_INSTANCE, GameInstance);

	bSetupGameStateEntryPointComplete = false;

	Scheduler->Start(Payload);
}

char UCsManager_Javascript::SetupGameStateEntryPoint_Internal(FCsRoutine* R)
{
	static const int32 GAME_INSTANCE = 0;
	UGameInstance* GameInstance	= R->GetValue_Void<UGameInstance>(GAME_INSTANCE);

	if (!GameInstance)
		GameInstance = Cast<UGameInstance>(MyRoot);

	UWorld* World						= GameInstance->GetWorld();
	AGameStateBase* GameState			= World ? World->GetGameState() : nullptr;
	APlayerController* PlayerController = World ? GEngine->GetFirstLocalPlayerController(World) : nullptr;
	APlayerState* PlayerState			= PlayerController ? PlayerController->PlayerState : nullptr;
	APawn* PlayerPawn					= PlayerController ? PlayerController->GetPawn() : nullptr;

	CS_COROUTINE_BEGIN(R);

	typedef NCsJs::NCommon::FLibrary JavascriptCommonLibrary;

	// GameInstance
	JavascriptCommonLibrary::ExposeObject(GameStateEntryPoint.Context, TEXT("GameInstance"), GameInstance);

	// World
	CS_COROUTINE_WAIT_UNTIL(R, World);

	JavascriptCommonLibrary::ExposeObject(GameStateEntryPoint.Context, TEXT("World"), World);

	// Game State
	CS_COROUTINE_WAIT_UNTIL(R, GameState);

	JavascriptCommonLibrary::ExposeObject(GameStateEntryPoint.Context, TEXT("GameState"), GameState);

	// Player Controller
	CS_COROUTINE_WAIT_UNTIL(R, PlayerController);

	JavascriptCommonLibrary::ExposeObject(GameStateEntryPoint.Context, TEXT("PlayerController"), PlayerController);

	// Player State
	CS_COROUTINE_WAIT_UNTIL(R, PlayerState);

	JavascriptCommonLibrary::ExposeObject(GameStateEntryPoint.Context, TEXT("PlayerState"), PlayerState);

	// Player Pawn
	CS_COROUTINE_WAIT_UNTIL(R, PlayerPawn);

	JavascriptCommonLibrary::ExposeObject(GameStateEntryPoint.Context, TEXT("PlayerPawn"), PlayerPawn);

	bSetupGameStateEntryPointComplete = true;

	CS_COROUTINE_END(R);
}

void UCsManager_Javascript::SetupAndRunGameStateEntryPoint(UGameInstance* GameInstance /*=nullptr*/)
{
	using namespace NCsManagerJavascript::NCached;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(MyRoot);

	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE SetupAndRunGameStateEntryPoint_Internal

	Payload->CoroutineImpl.BindUObject(this, &UCsManager_Javascript::COROUTINE);
	Payload->StartTime = UCsManager_Time::Get(MyRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	static const int32 GAME_INSTANCE = 0;
	Payload->SetValue_Void(GAME_INSTANCE, GameInstance);

	Scheduler->Start(Payload);
}

char UCsManager_Javascript::SetupAndRunGameStateEntryPoint_Internal(FCsRoutine* R)
{
	static const int32 GAME_INSTANCE = 0;
	UGameInstance* GameInstance	= R->GetValue_Void<UGameInstance>(GAME_INSTANCE);

	if (!GameInstance)
		GameInstance = Cast<UGameInstance>(MyRoot);

	CS_COROUTINE_BEGIN(R);

	typedef NCsJs::NCommon::FLibrary JavascriptCommonLibrary;

	// Setup Isolate and Context
	CreateGameStateEntryPoint();
	// Expose Objects
	SetupGameStateEntryPoint(GameInstance);

	// Wait until SetupGameStateEntryPoint is complete.
	CS_COROUTINE_WAIT_UNTIL(R, bSetupGameStateEntryPointComplete);

	// Run Javascript
	RunGameStateEntryPoint();

	CS_COROUTINE_END(R);
}

void UCsManager_Javascript::RunGameStateEntryPoint()
{
	checkf(GameStateEntryPoint.Context, TEXT("UCsManager_Javascript::RunGameStateEntryPoint: Context is NULL."));

	UCsJsSettings* Settings = GetMutableDefault<UCsJsSettings>();

	checkf(Settings, TEXT("UCsManager_Javascript::RunGameStateEntryPoint: Failed to find Settings of type: UCsJsSettings."));

	const FString& FileName = Settings->GameStateEntryPointFileName;

	checkf(!FileName.IsEmpty(), TEXT("UCsManager_Javascript::RunGameStateEntryPoint: FileName is Empty."));

	typedef NCsJs::NCommon::FLibrary JavascriptCommonLibrary;

	JavascriptCommonLibrary::RunFile(GameStateEntryPoint.Context, FileName);
}

void UCsManager_Javascript::ShutdownGameStateEntryPoint()
{
	GameStateEntryPoint.Shutdown();
}