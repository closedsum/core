// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/CsManager_Javascript.h"
#include "CsJs.h"

// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/CsLibrary_Manager_Javascript.h"
#include "Managers/Input/CsLibrary_Manager_Input.h"
	// Common
#include "Object/CsLibrary_Object.h"
#include "Library/CsJsLibrary_Common.h"
#include "Library/CsLibrary_Valid.h"
// Coroutine
#include "Coroutine/CsRoutine.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Coordinators
#include "Coordinators/GameEvent/CsCoordinator_GameEvent.h"
// Settings
#include "Managers/CsSettings_Manager_Javascript.h"
// Game
#include "Engine/GameInstance.h"
#include "GameFramework/GameStateBase.h"
// Player
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Pawn.h"
// Settings
#include "Settings/CsJsSettings.h"
// Javascript
#include "JavascriptInstance.h"
// Engine
#include "Engine/World.h"
#include "Engine/Engine.h"

#if WITH_EDITOR
// Singleton
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Managers/CsGetManagerJavascript.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_Javascript)

// Cache
#pragma region

namespace NCsManagerJavascript
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, GetSafe_GetManagerJavascript);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, GetSafe);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, GetFromWorldContextObject);
			// Entry Point
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, CreateEntryPoint);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, CreateEntryPoint_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, SetupEntryPoint);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, SetupEntryPoint_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, SetupAndRunEntryPoint);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, SetupAndRunEntryPoint_Internal);
			// Scripts
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, CreateScriptObjects);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, CreateScriptObjects_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, SetupScriptObjects);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, SetupScriptObjects_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, SetupAndRunScripts);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, SetupAndRunScripts_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, ReloadScript);
			// Events
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript, SetupCallbacks);
		}

		namespace Name
		{
			// Entry Point
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Javascript, CreateEntryPoint_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Javascript, SetupEntryPoint_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Javascript, SetupAndRunEntryPoint_Internal);
			// Scripts
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Javascript, CreateScriptObjects_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Javascript, SetupScriptObjects_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Javascript, SetupAndRunScripts_Internal);
		}
	}

	namespace NEditorScriptImpl
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript::FEditorScriptImpl, Init);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript::FEditorScriptImpl, Init_Internal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript::FEditorScriptImpl, CreateAndRun);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Javascript::FEditorScriptImpl, Reload);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsManager_Javascript::FEditorScriptImpl, Init_Internal);
			}
		}
	}
}

#pragma endregion Cache

// static initializations
UCsManager_Javascript* UCsManager_Javascript::s_Instance;
bool UCsManager_Javascript::s_bShutdown = false;

UCsManager_Javascript::UCsManager_Javascript(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// GetJavascriptInstance
	JavascriptInstanceInfo(),
	JavascriptInstance(nullptr),
	// Scripts
	ScriptObjects(),
	ScriptInfo(),
	bSetupScriptObjectsComplete(false),
	OnSetupAndRunScriptsComplete_ScriptEvent(),
	OnRunScriptsComplete_ScriptEvent(),
	OnPreReloadScript_ScriptEvent(),
	CurrentScriptIndex(INDEX_NONE),
	bScriptReload(false),
	// Editor Scripts
	EditorScriptImpl(),
	CurrentEditorScriptIndex(INDEX_NONE),
	CurrentEditorScriptId(),
	EditorScript_OnShutdown_ScriptEvent()
{
}

#define USING_NS_CACHED using namespace NCsManagerJavascript::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsManagerJavascript::NCached; \
	const FString& Context = Str::__FunctionName

// ICsGetJavascriptIsolate
#pragma region

TSharedPtr<FJavascriptIsolate> UCsManager_Javascript::GetSharedJavascriptIsolate()
{
	return JavascriptInstance->GetSharedIsolate();
}

#pragma endregion ICsGetJavascriptIsolate

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_Javascript* UCsManager_Javascript::Get(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerJavascript(InRoot)->GetManager_Javascript();
}

/*static*/ bool UCsManager_Javascript::IsValid(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerJavascript(InRoot)->GetManager_Javascript() != nullptr;
}

#endif // #if WITH_EDITOR

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

/*static*/ ICsGetManagerJavascript* UCsManager_Javascript::GetSafe_GetManagerJavascript(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
{
	if (!Object)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object is NULL."), *Context));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *Context, *(Object->GetName())));
		return nullptr;
	}
	
	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get object of type: UCsManager_Singleton from Object: %s."), *Context, *(Object->GetName())));
		return nullptr;
	}

	return Cast<ICsGetManagerJavascript>(Manager_Singleton);
}

/*static*/ ICsGetManagerJavascript* UCsManager_Javascript::GetSafe_GetManagerJavascript(UObject* Object)
{
	SET_CONTEXT(GetSafe_GetManagerJavascript);

	return GetSafe_GetManagerJavascript(Context, Object, nullptr);
}

/*static*/ UCsManager_Javascript* UCsManager_Javascript::GetSafe(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
{
	if (ICsGetManagerJavascript* GetManagerJavascript = GetSafe_GetManagerJavascript(Context, Object, Log))
		return GetManagerJavascript->GetManager_Javascript();
	return nullptr;
}

/*static*/ UCsManager_Javascript* UCsManager_Javascript::GetSafe(UObject* Object)
{
	SET_CONTEXT(GetSafe);

	return GetSafe(Context, Object, nullptr);
}

/*static*/ UCsManager_Javascript* UCsManager_Javascript::GetFromWorldContextObject(const FString& Context, const UObject* WorldContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
{
	if (UObject* ContextRoot = CsJavascriptManagerLibrary::GetSafe(Context, WorldContextObject))
	{
		if (UCsManager_Javascript* Manager = GetSafe(ContextRoot))
			return Manager;

		UE_LOG(LogCsJs, Warning, TEXT("%s: Failed to Manager Javascript of type UCsManager_Javascript from ContextRoot: %s."), *Context, *(ContextRoot->GetName()));
	}
	return nullptr;
}

/*static*/ UCsManager_Javascript* UCsManager_Javascript::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	SET_CONTEXT(GetFromWorldContextObject);

	return GetFromWorldContextObject(Context, WorldContextObject, nullptr);
}

#endif // #if WITH_EDITOR

void UCsManager_Javascript::Initialize()
{
	CsJavascriptCommonLibrary::AsyncCreateInstance(this);
	/*
	if (Cast<UGameInstance>(MyRoot))
	{
	}
	*/
	EditorScriptImpl.Outer = this;
}

void UCsManager_Javascript::CleanUp()
{
	EntryPoint.Shutdown();
	ShutdownScripts();
	EditorScriptImpl.Shutdown();
}

	// Root
#pragma region

void UCsManager_Javascript::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Entry Point
#pragma region

void UCsManager_Javascript::CreateEntryPoint()
{
	SET_CONTEXT(CreateEntryPoint);

	const FECsUpdateGroup& Group = MyRoot == GEngine ? NCsUpdateGroup::EditorEngine : NCsUpdateGroup::GameInstance;

	CS_COROUTINE_SETUP_UOBJECT(UCsManager_Javascript, CreateEntryPoint_Internal, Group, this, MyRoot);

	CS_COROUTINE_START(MyRoot);
}

char UCsManager_Javascript::CreateEntryPoint_Internal(FCsRoutine* R)
{
	SET_CONTEXT(CreateEntryPoint_Internal);

	CS_COROUTINE_BEGIN(R);

	// NOTE: Currently using a SHARED Isolate from the JavascriptInstance
	CS_COROUTINE_WAIT_UNTIL(R, JavascriptInstanceInfo.CreateInfo.IsComplete());

	checkf(JavascriptInstanceInfo.CreateInfo.IsSuccessful(), TEXT("%s: Failed to Create JavascriptInstance."), *Context);

	// Setup Isolate and Context
	CsJavascriptCommonLibrary::SetupIsolateAndContext(this, EntryPoint.Isolate, EntryPoint.Context, false);

	CS_COROUTINE_END(R);
}

void UCsManager_Javascript::SetupEntryPoint(UGameInstance* InGameInstance /*=nullptr*/)
{
	SET_CONTEXT(SetupEntryPoint);

	CS_IS_VALID_CHECKED(EntryPoint);

	CS_COROUTINE_SETUP_UOBJECT(UCsManager_Javascript, SetupEntryPoint_Internal, NCsUpdateGroup::GameInstance, this, MyRoot);

	GameInstance = InGameInstance;

	if (!GameInstance)
		GameInstance = Cast<UGameInstance>(MyRoot);

	bSetupEntryPointComplete = false;

	CS_COROUTINE_START(MyRoot);
}

char UCsManager_Javascript::SetupEntryPoint_Internal(FCsRoutine* R)
{
	SET_CONTEXT(SetupEntryPoint_Internal);

	UWorld* World						= GameInstance->GetWorld();
	AGameStateBase* GameState			= World ? World->GetGameState() : nullptr;
	APlayerController* PlayerController = World ? GEngine->GetFirstLocalPlayerController(World) : nullptr;
	APlayerState* PlayerState			= PlayerController ? PlayerController->PlayerState : nullptr;
	APawn* PlayerPawn					= PlayerController ? PlayerController->GetPawn() : nullptr;

	CS_COROUTINE_BEGIN(R);

	// NOTE: Currently using a SHARED Isolate from the JavascriptInstance
	CS_COROUTINE_WAIT_UNTIL(R, JavascriptInstanceInfo.CreateInfo.IsComplete());

	checkf(JavascriptInstanceInfo.CreateInfo.IsSuccessful(), TEXT("%s: Failed to Create JavascriptInstance."), *Context);

	EntryPoint.ExposedObjectNames.Add(TEXT("Root"));

	// Engine
	CsJavascriptCommonLibrary::ExposeObject(EntryPoint.Context, TEXT("GEngine"), GEngine);
	EntryPoint.ExposedObjectNames.Add(TEXT("GEngine"));
	 
	// GameInstance
	CsJavascriptCommonLibrary::ExposeObject(EntryPoint.Context, TEXT("GameInstance"), GameInstance);
	EntryPoint.ExposedObjectNames.Add(TEXT("GameInstance"));

	// Manager_Time
	CsJavascriptCommonLibrary::ExposeObject(EntryPoint.Context, TEXT("Manager_Time"), UCsManager_Time::Get(GameInstance));
	EntryPoint.ExposedObjectNames.Add(TEXT("Manager_Time"));

	// Coordinator_GameEvent
	CsJavascriptCommonLibrary::ExposeObject(EntryPoint.Context, TEXT("Coordinator_GameEvent"), UCsCoordinator_GameEvent::Get(GameInstance));
	EntryPoint.ExposedObjectNames.Add(TEXT("Coordinator_GameEvent"));

	// World
	CS_COROUTINE_WAIT_UNTIL(R, World);

	CsJavascriptCommonLibrary::ExposeObject(EntryPoint.Context, TEXT("World"), World);
	EntryPoint.ExposedObjectNames.Add(TEXT("World"));
	EntryPoint.ExposedObjectNames.Add(TEXT("GWorld"));

	// Game State
	CS_COROUTINE_WAIT_UNTIL(R, GameState);

	CsJavascriptCommonLibrary::ExposeObject(EntryPoint.Context, TEXT("GameState"), GameState);
	EntryPoint.ExposedObjectNames.Add(TEXT("GameState"));

	// Player Controller
	CS_COROUTINE_WAIT_UNTIL(R, PlayerController);

	CsJavascriptCommonLibrary::ExposeObject(EntryPoint.Context, TEXT("PlayerController"), PlayerController);
	EntryPoint.ExposedObjectNames.Add(TEXT("PlayerController"));

	// Player State
	CS_COROUTINE_WAIT_UNTIL(R, PlayerState);

	CsJavascriptCommonLibrary::ExposeObject(EntryPoint.Context, TEXT("PlayerState"), PlayerState);
	EntryPoint.ExposedObjectNames.Add(TEXT("PlayerState"));

	// Player Pawn
	CS_COROUTINE_WAIT_UNTIL(R, PlayerPawn);

	CsJavascriptCommonLibrary::ExposeObject(EntryPoint.Context, TEXT("PlayerPawn"), PlayerPawn);
	EntryPoint.ExposedObjectNames.Add(TEXT("PlayerPawn"));

	// Additional Setup
	if (AdditionalSetupEntryPoint_Impl.IsBound())
	{
		checkf(IsAdditionalSetupEntryPointComplete_Impl.IsBound(), TEXT("%s: AdditionalSetupEntryPoint_Impl is Bound but IsAdditionalSetupEntryPointComplete_Impl is NOT Bound."), *Context);

		AdditionalSetupEntryPoint_Impl.Execute();

		CS_COROUTINE_WAIT_UNTIL(R, IsAdditionalSetupEntryPointComplete_Impl.Execute());
	}

	bSetupEntryPointComplete = true;

	CS_COROUTINE_END(R);
}

void UCsManager_Javascript::SetupAndRunEntryPoint(UGameInstance* InGameInstance /*=nullptr*/)
{
	SET_CONTEXT(SetupAndRunEntryPoint);

	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameInstance;
	PayloadType* Payload			   = CsCoroutineSchedulerLibrary::AllocatePayloadChecked(Context, MyRoot, UpdateGroup);

	typedef UCsManager_Javascript ClassType;
	#define COROUTINE SetupAndRunEntryPoint_Internal

	Payload->Init<ClassType>(Context, this, &ClassType::COROUTINE, MyRoot, UpdateGroup, Str::COROUTINE, Name::COROUTINE);

	#undef COROUTINE

	GameInstance = InGameInstance;

	if (!GameInstance)
		GameInstance = Cast<UGameInstance>(MyRoot);

	CsCoroutineSchedulerLibrary::StartChecked(Context, MyRoot, Payload);
}

char UCsManager_Javascript::SetupAndRunEntryPoint_Internal(FCsRoutine* R)
{
	CS_COROUTINE_READ_OBJECT_START

	CS_COROUTINE_BEGIN(R);

	// Setup Isolate and Context
	CreateEntryPoint();
	// Expose Objects
	SetupEntryPoint(GameInstance);

	// Wait until SetupEntryPoint is complete.
	CS_COROUTINE_WAIT_UNTIL(R, bSetupEntryPointComplete);

	// Run Javascript
	RunEntryPoint();

	CS_COROUTINE_END(R);
}

void UCsManager_Javascript::RunEntryPoint()
{
	checkf(EntryPoint.Context, TEXT("UCsManager_Javascript::RunEntryPoint: Context is NULL."));

	const FString& FileName = EntryPointInfo.File;

	checkf(!FileName.IsEmpty(), TEXT("UCsManager_Javascript::RunEntryPoint: FileName is Empty."));

	CsJavascriptCommonLibrary::RunFile(EntryPoint.Context, FileName);
}

void UCsManager_Javascript::ShutdownEntryPoint()
{
	EntryPoint.Shutdown();
}

#pragma endregion Entry Point

// Scripts
#pragma region

void UCsManager_Javascript::CreateScriptObjects()
{
	SET_CONTEXT(CreateScriptObjects);

	const FECsUpdateGroup& Group = MyRoot == GEngine ? NCsUpdateGroup::EditorEngine : NCsUpdateGroup::GameInstance;

	CS_COROUTINE_SETUP_UOBJECT(UCsManager_Javascript, CreateScriptObjects_Internal, Group, this, MyRoot);

	CS_COROUTINE_START(MyRoot);
}

char UCsManager_Javascript::CreateScriptObjects_Internal(FCsRoutine* R)
{
	SET_CONTEXT(CreateScriptObjects_Internal);

	CS_COROUTINE_BEGIN(R);

	// NOTE: Currently using a SHARED Isolate from the JavascriptInstance
	CS_COROUTINE_WAIT_UNTIL(R, JavascriptInstanceInfo.CreateInfo.IsComplete());

	checkf(JavascriptInstanceInfo.CreateInfo.IsSuccessful(), TEXT("%s: Failed to Create JavascriptInstance."), *Context);

	{
		const FCsSettings_Manager_Javascript& Settings = FCsSettings_Manager_Javascript::Get();

		const int32 Count = Settings.PoolSize;

		ScriptObjects.Reset(Count);

		// Setup Isolates and Contexts

		for (int32 I = 0; I < Count; ++I)
		{
			FCsJavascriptFileObjects& ScriptObject = ScriptObjects.AddDefaulted_GetRef();

			ScriptObject.Index = I;
			ScriptObject.Init(this);
		}
	}

	CS_COROUTINE_END(R);
}

void UCsManager_Javascript::ConditionalCreateScriptObjects()
{
	if (ScriptObjects.Num() == CS_EMPTY)
		CreateScriptObjects();
}

void UCsManager_Javascript::SetupScriptObjects(UGameInstance* InGameInstance /*=nullptr*/)
{
	SET_CONTEXT(SetupScriptObjects);

	CS_IS_VALID_CHECKED(ScriptInfo);

	const FCsSettings_Manager_Javascript& Settings = FCsSettings_Manager_Javascript::Get();

	checkf(Settings.PoolSize >= ScriptInfo.FileInfos.Num(), TEXT("%s: Pool Size (%d) of Script Objects is not large to support the number of requested files (%d) to run."), *Context, Settings.PoolSize, ScriptInfo.FileInfos.Num());

	CS_COROUTINE_SETUP_UOBJECT(UCsManager_Javascript, SetupScriptObjects_Internal, NCsUpdateGroup::GameInstance, this, MyRoot);

	GameInstance = InGameInstance;

	bSetupScriptObjectsComplete = false;

	CS_COROUTINE_START(MyRoot);
}

char UCsManager_Javascript::SetupScriptObjects_Internal(FCsRoutine* R)
{
	SET_CONTEXT(SetupScriptObjects_Internal);

	CS_COROUTINE_READ_OBJECT_START

	if (!GameInstance)
		GameInstance = Cast<UGameInstance>(MyRoot);

	UWorld* World						= GameInstance->GetWorld();
	AGameStateBase* GameState			= World ? World->GetGameState() : nullptr;
	APlayerController* PlayerController = World ? GEngine->GetFirstLocalPlayerController(World) : nullptr;
	APlayerState* PlayerState			= PlayerController ? PlayerController->PlayerState : nullptr;
	APawn* PlayerPawn					= PlayerController ? PlayerController->GetPawn() : nullptr;

	CS_COROUTINE_BEGIN(R);

	// NOTE: Currently using a SHARED Isolate from the JavascriptInstance
	CS_COROUTINE_WAIT_UNTIL(R, JavascriptInstanceInfo.CreateInfo.IsComplete());

	checkf(JavascriptInstanceInfo.CreateInfo.IsSuccessful(), TEXT("%s: Failed to Create JavascriptInstance."), *Context);

	// World
	CS_COROUTINE_WAIT_UNTIL(R, World);
	// Game State
	CS_COROUTINE_WAIT_UNTIL(R, GameState);
	// Player Controller
	CS_COROUTINE_WAIT_UNTIL(R, PlayerController);
	// Player State
	CS_COROUTINE_WAIT_UNTIL(R, PlayerState);
	// Player Pawn
	//CS_COROUTINE_WAIT_UNTIL(R, PlayerPawn);

	{
		const int32 MaxScripts = ScriptObjects.Num();

		for (int32 I = 0; I < MaxScripts; ++I)
		{
			if (ScriptInfo.HasFileInfo(I))
			{
				FCsJavascriptFileObjects& ScriptObject = ScriptObjects[I];

				ScriptObject.ExposedObjectNames.Add(TEXT("Root"));

				// Engine
				CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("GEngine"), GEngine);
				ScriptObject.ExposedObjectNames.Add(TEXT("GEngine"));
	 
				// GameInstance
				CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("GameInstance"), GameInstance);
				ScriptObject.ExposedObjectNames.Add(TEXT("GameInstance"));

				// Manager_Time
				CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("Manager_Time"), UCsManager_Time::Get(GameInstance));
				ScriptObject.ExposedObjectNames.Add(TEXT("Manager_Time"));

				// Coordinator_GameEvent
				CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("Coordinator_GameEvent"), UCsCoordinator_GameEvent::Get(GameInstance));
				ScriptObject.ExposedObjectNames.Add(TEXT("Coordinator_GameEvent"));

				// World
				CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("World"), World);
				ScriptObject.ExposedObjectNames.Add(TEXT("World"));
				ScriptObject.ExposedObjectNames.Add(TEXT("GWorld"));

				// Game State
				CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("GameState"), GameState);
				ScriptObject.ExposedObjectNames.Add(TEXT("GameState"));

				// Manager_Javascript
				CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("Manager_Javascript"), this);
				ScriptObject.ExposedObjectNames.Add(TEXT("Manager_Javascript"));

				// Player Controller
				CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("PlayerController"), PlayerController);
				ScriptObject.ExposedObjectNames.Add(TEXT("PlayerController"));

				// Player State
				CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("PlayerState"), PlayerState);
				ScriptObject.ExposedObjectNames.Add(TEXT("PlayerState"));

				// Player Pawn
				//CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("PlayerPawn"), PlayerPawn);
				//ScriptObject.ExposedObjectNames.Add(TEXT("PlayerPawn"));

				// Additional Setup
				if (AdditionalSetupScriptObjects_Impl.IsBound())
					AdditionalSetupScriptObjects_Impl.Execute(I);
			}
		}
	}

	if (IsAdditionalSetupScriptObjectsComplete_Impl.IsBound())
		IsAdditionalSetupScriptObjectsComplete_Impl.Execute();

	bSetupScriptObjectsComplete = true;

	CS_COROUTINE_END(R);
}

void UCsManager_Javascript::SetupAndRunScripts(UGameInstance* InGameInstance /*=nullptr*/)
{
	SET_CONTEXT(SetupAndRunScripts);

	CS_COROUTINE_SETUP_UOBJECT(UCsManager_Javascript, SetupAndRunScripts_Internal, NCsUpdateGroup::GameInstance, this, MyRoot);

	GameInstance = InGameInstance;

	CS_COROUTINE_START(MyRoot);
}

char UCsManager_Javascript::SetupAndRunScripts_Internal(FCsRoutine* R)
{
	CS_COROUTINE_READ_OBJECT_START

	if (!GameInstance)
		GameInstance = Cast<UGameInstance>(MyRoot);

	CS_COROUTINE_BEGIN(R);

	// Setup Isolate and Context
	CreateScriptObjects();
	// Expose Objects
	SetupScriptObjects(GameInstance);

	// Wait until SetupSriptObjects is complete.
	CS_COROUTINE_WAIT_UNTIL(R, bSetupScriptObjectsComplete);

	// Run Javascript
	RunScripts();

	OnSetupAndRunScriptsComplete_ScriptEvent.Broadcast();

	CS_COROUTINE_END(R);
}

void UCsManager_Javascript::RunScripts()
{
	const FCsSettings_Manager_Javascript& Settings = FCsSettings_Manager_Javascript::Get();

	const int32 MaxScripts = ScriptObjects.Num();

	CurrentScriptIndex = 0;
	bScriptReload = false;

	for (int32 I = 0; I < MaxScripts; ++I)
	{
		if (ScriptInfo.HasFileInfo(I))
		{
			FCsScript_FileInfo& FileInfo		   = ScriptInfo.FileInfos[I];
			FCsJavascriptFileObjects& ScriptObject = ScriptObjects[I];

			checkf(ScriptObject.Context, TEXT("UCsManager_Javascript::RunScripts: Context is NULL."));

			const FString& FileName = FileInfo.Entry;

			checkf(!FileName.IsEmpty(), TEXT("UCsManager_Javascript::RunScripts: FileName is Empty."));

			ScriptObject.Path = FileName;

			CsJavascriptCommonLibrary::RunFile(ScriptObject.Context, FileName);
		}
		++CurrentScriptIndex;
	}
	OnRunScriptsComplete_ScriptEvent.Broadcast();
}

void UCsManager_Javascript::ReloadScript(const int32& Index)
{
	SET_CONTEXT(ReloadScript);

	if (Index < 0)
	{
		UE_LOG(LogCsJs, Warning, TEXT("%s: Index: %d is NOT Valid. Index: %d MUST be > 0."), *Context, Index, Index);
		return;
	}

	if (Index > ScriptObjects.Num())
	{
		UE_LOG(LogCsJs, Warning, TEXT("%s: No Script associated with Index: %d."), *Context, Index);
		return;
	}

	const FCsScript_FileInfo& FileInfo = ScriptInfo.FileInfos[Index];

	if (!FileInfo.bEnable)
	{
		UE_LOG(LogCsJs, Warning, TEXT("%s: Script: %s associated with index: %d is NOT Enabled."), *Context, *(FileInfo.Entry), Index);
		return;
	}

	if (!FileInfo.IsValid(Context))
		return;

	FCsJavascriptFileObjects& ScriptObject = ScriptObjects[Index];

	ScriptObject.Deactivate(this);

	UWorld* World						= GameInstance->GetWorld();
	AGameStateBase* GameState			= World ? World->GetGameState() : nullptr;
	APlayerController* PlayerController = World ? GEngine->GetFirstLocalPlayerController(World) : nullptr;
	APlayerState* PlayerState			= PlayerController ? PlayerController->PlayerState : nullptr;
	APawn* PlayerPawn					= PlayerController ? PlayerController->GetPawn() : nullptr;

	ScriptObject.ExposedObjectNames.Add(TEXT("Root"));

	// Engine
	CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("GEngine"), GEngine);
	ScriptObject.ExposedObjectNames.Add(TEXT("GEngine"));
	 
	// GameInstance
	CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("GameInstance"), GameInstance);
	ScriptObject.ExposedObjectNames.Add(TEXT("GameInstance"));

	// Manager_Time
	CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("Manager_Time"), UCsManager_Time::Get(GameInstance));
	ScriptObject.ExposedObjectNames.Add(TEXT("Manager_Time"));

	// Coordinator_GameEvent
	CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("Coordinator_GameEvent"), UCsCoordinator_GameEvent::Get(GameInstance));
	ScriptObject.ExposedObjectNames.Add(TEXT("Coordinator_GameEvent"));

	// World
	CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("World"), World);
	ScriptObject.ExposedObjectNames.Add(TEXT("World"));
	ScriptObject.ExposedObjectNames.Add(TEXT("GWorld"));

	// Game State
	CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("GameState"), GameState);
	ScriptObject.ExposedObjectNames.Add(TEXT("GameState"));

	// Manager_Javascript
	CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("Manager_Javascript"), this);
	ScriptObject.ExposedObjectNames.Add(TEXT("Manager_Javascript"));

	// Player Controller
	CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("PlayerController"), PlayerController);
	ScriptObject.ExposedObjectNames.Add(TEXT("PlayerController"));

	// Player State
	CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("PlayerState"), PlayerState);
	ScriptObject.ExposedObjectNames.Add(TEXT("PlayerState"));

	// Player Pawn
	//JavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("PlayerPawn"), PlayerPawn);
	//ScriptObject.ExposedObjectNames.Add(TEXT("PlayerPawn"));

	// Additional Setup
	if (AdditionalSetupScriptObjects_Impl.IsBound())
		AdditionalSetupScriptObjects_Impl.Execute(Index);

	const FString& FileName	= FileInfo.Entry;

	CsJavascriptCommonLibrary::RunFile(ScriptObject.Context, FileName);
}

void UCsManager_Javascript::DeactivateScripts(const bool& bForce /*=false*/)
{
	OnShutdownScripts_Start_ScriptEvent.Broadcast();

	const FCsSettings_Manager_Javascript& Settings = FCsSettings_Manager_Javascript::Get();

	const int32 Count = ScriptObjects.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (bForce)
		{
			ScriptObjects[I].Deactivate(this);
		}
		else
		if (ScriptInfo.HasFileInfo(I))
		{
			FCsJavascriptFileObjects& ScriptObject = ScriptObjects[I];
			const FCsScript_FileInfo& FileInfo = ScriptInfo.FileInfos[I];
			const FString& FileName			   = FileInfo.Entry;

			if (ScriptObject.Path != Settings.EmptyPath)
				ScriptObject.Deactivate(this);
		}
	}
}

void UCsManager_Javascript::ShutdownScripts()
{
	OnShutdownScripts_Start_ScriptEvent.Broadcast();

	for (FCsJavascriptFileObjects& ScriptObject : ScriptObjects)
	{
		ScriptObject.Shutdown();
	}
	ScriptObjects.Reset(ScriptObjects.Max());
}

#pragma endregion Scripts

// Editor Scripts
#pragma region

#define USING_NS_CACHED2 using namespace NCsManagerJavascript::NEditorScriptImpl::NCached;
#define SET_CONTEXT2(__FunctionName) using namespace NCsManagerJavascript::NEditorScriptImpl::NCached; \
	const FString& Context = Str::__FunctionName

void UCsManager_Javascript::FEditorScriptImpl::Init()
{
	SET_CONTEXT2(Init);

	CS_COROUTINE_SETUP_RAW(UCsManager_Javascript::FEditorScriptImpl, Init_Internal, NCsUpdateGroup::EditorEngine, this, Outer, Outer->GetMyRoot());

	CS_COROUTINE_START(Outer->GetMyRoot());
}

char UCsManager_Javascript::FEditorScriptImpl::Init_Internal(FCsRoutine* R)
{
	SET_CONTEXT2(Init_Internal);

	CS_COROUTINE_BEGIN(R);

	// NOTE: Currently using a SHARED Isolate from the JavascriptInstance
	CS_COROUTINE_WAIT_UNTIL(R, Outer->GetJavascriptInstanceInfo().CreateInfo.IsComplete());

	checkf(Outer->GetJavascriptInstanceInfo().CreateInfo.IsSuccessful(), TEXT("%s: Failed to Create JavascriptInstance."), *Context);

	{
		const FCsSettings_Manager_Javascript& Settings = FCsSettings_Manager_Javascript::Get();

		CS_IS_VALID_CHECKED(Settings);

		const int32 Count = Settings.PoolSize;

		TArray<FCsJavascriptFileObjects>& Objects = GetObjects();

		Objects.Reset(Count);
		Manager_Objects.CreatePool(Count);

		for (int32 I = 0; I < Count; ++I)
		{
			FCsJavascriptFileObjects& ScriptObject = Objects.AddDefaulted_GetRef();

			ScriptObject.Index = I;
			ScriptObject.Init(Outer);

			Manager_Objects.Add(&ScriptObject);
		}
	}

	CS_COROUTINE_END(R);
}

void UCsManager_Javascript::FEditorScriptImpl::Validate()
{
	TArray<FCsJavascriptFileObjects>& Objects = GetObjects();

	// Check other Script Objects are still Valid.
	TArray<int32> IdsToRemove;

	for (TPair<int32, UObject*>& Pair : OwnerByOwnerIdMap)
	{
		const int32& Id = Pair.Key;
		UObject* Owner	= Pair.Value;

		if (!CsObjectLibrary::IsValidObject(Owner))
			IdsToRemove.Add(Id);
	}

	// Remove any Script Objects associated with Invalid Owners.
	const int32 Count = IdsToRemove.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const int32& OwnerId_Remove = IdsToRemove[I];

		OwnerByOwnerIdMap.Remove(OwnerId_Remove);

		// Remove the Invalid Index from the list
		const int32& Index_Remove   = IndexByOwnerIdMap[OwnerId_Remove];
		const FGuid ScriptId_Remove	= Objects[Index_Remove].Id;

		Objects[Index_Remove].Deactivate(Outer);
		Manager_Objects.DeallocateAt(Objects[Index_Remove].Index);

		// Remove from remaining lists
		IndexByOwnerIdMap.Remove(OwnerId_Remove);
		IdByOwnerIdMap.Remove(OwnerId_Remove);
		OwnerIdByIdMap.Remove(ScriptId_Remove);
	}
}

FGuid UCsManager_Javascript::FEditorScriptImpl::CreateAndRun(UObject* Owner, const FString& Path)
{
	SET_CONTEXT2(CreateAndRun);

	FGuid ScriptId;

	ScriptId.Invalidate();

	CS_IS_PENDING_KILL_CHECKED(Owner)
	CS_IS_STRING_EMPTY_CHECKED(Path)

	Validate();

	FCsJavascriptFileObjects& ScriptObject = Manager_Objects.AllocateResourceRef();

	// Setup Isolates and Contexts
	{
		ScriptObject.Id = FGuid::NewGuid();

		// Update Maps
		const int32 OwnerId		= Owner->GetClass()->GetDefaultObject()->GetUniqueID();
		ScriptId			    = ScriptObject.Id;
		const int32 ScriptIndex = GetObjects().Num() - 1;

		OwnerByOwnerIdMap.Add(OwnerId, Owner);
		IndexByOwnerIdMap.Add(OwnerId, ScriptIndex);
		IdByOwnerIdMap.Add(OwnerId, ScriptId);
		OwnerIdByIdMap.Add(ScriptId, OwnerId);
	}
	
	// Expose Objects
	{
		ScriptObject.ExposedObjectNames.Add(TEXT("Root"));

		// Script Outer | Owner
		CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("ScriptOuter"), Owner);
		ScriptObject.ExposedObjectNames.Add(TEXT("ScriptOuter"));

		// Engine
		CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("GEngine"), GEngine);
		ScriptObject.ExposedObjectNames.Add(TEXT("GEngine"));

		// Manager_Time
		CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("Manager_Time"), UCsManager_Time::Get(GEngine));
		ScriptObject.ExposedObjectNames.Add(TEXT("Manager_Time"));

		// World
		CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("World"), Owner->GetWorld());
		ScriptObject.ExposedObjectNames.Add(TEXT("World"));
		ScriptObject.ExposedObjectNames.Add(TEXT("GWorld"));

		// Manager_Javascript
		CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("Manager_Javascript"), Outer);
		ScriptObject.ExposedObjectNames.Add(TEXT("Manager_Javascript"));
	}

	Outer->CurrentEditorScriptIndex = GetObjects().Num() - 1;
	Outer->CurrentEditorScriptId    = ScriptObject.Id;

	CsJavascriptCommonLibrary::RunFile(ScriptObject.Context, Path);

	return ScriptId;
}

void UCsManager_Javascript::FEditorScriptImpl::Reload(const FGuid& Id, const FString& Path)
{
	SET_CONTEXT2(Reload);

	if (!OwnerIdByIdMap.Contains(Id))
	{
		UE_LOG(LogCsJs, Warning, TEXT("%s: No Script associated with Id: %s."), *Context, *(Id.ToString()));
		return;
	}

	const int32& OwnerId = OwnerIdByIdMap[Id];
	const int32& Index   = IndexByOwnerIdMap[OwnerId];
	UObject* Owner		 = OwnerByOwnerIdMap[OwnerId];

	FCsJavascriptFileObjects& ScriptObject = GetObjects()[Index];

	ScriptObject.Deactivate(Outer);

	ScriptObject.ExposedObjectNames.Add(TEXT("Root"));

	// Script Outer | Owner
	CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("ScriptOuter"), Owner);
	ScriptObject.ExposedObjectNames.Add(TEXT("ScriptOuter"));

	// Engine
	CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("GEngine"), GEngine);
	ScriptObject.ExposedObjectNames.Add(TEXT("GEngine"));

	// Manager_Time
	CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("Manager_Time"), UCsManager_Time::Get(GEngine));
	ScriptObject.ExposedObjectNames.Add(TEXT("Manager_Time"));

	// World
	CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("World"), Owner->GetWorld());
	ScriptObject.ExposedObjectNames.Add(TEXT("World"));
	ScriptObject.ExposedObjectNames.Add(TEXT("GWorld"));

	// Manager_Javascript
	CsJavascriptCommonLibrary::ExposeObject(ScriptObject.Context, TEXT("Manager_Javascript"), Outer);
	ScriptObject.ExposedObjectNames.Add(TEXT("Manager_Javascript"));

	CsJavascriptCommonLibrary::RunFile(ScriptObject.Context, Path);
}

bool UCsManager_Javascript::FEditorScriptImpl::Shutdown(UObject* Owner)
{
	const int32 OwnerId_Remove = Owner->GetClass()->GetDefaultObject()->GetUniqueID();

	if (!OwnerByOwnerIdMap.Contains(OwnerId_Remove))
		return false;

	OwnerByOwnerIdMap.Remove(OwnerId_Remove);

	TArray<FCsJavascriptFileObjects>& Objects = GetObjects();

	// Remove the Invalid Index from the list
	const int32& Index_Remove	 = IndexByOwnerIdMap[OwnerId_Remove];
	const FGuid ScriptId_Remove	 = Objects[Index_Remove].Id;

	Outer->EditorScript_OnShutdown_ScriptEvent.Broadcast(ScriptId_Remove);

	Objects[Index_Remove].Deactivate(Outer);
	Manager_Objects.DeallocateAt(Objects[Index_Remove].Index);

	// Remove from remaining lists
	IndexByOwnerIdMap.Remove(OwnerId_Remove);
	IdByOwnerIdMap.Remove(OwnerId_Remove);
	OwnerIdByIdMap.Remove(ScriptId_Remove);
	return true;
}

void UCsManager_Javascript::FEditorScriptImpl::Shutdown()
{
	TArray<FCsJavascriptFileObjects>& Objects = GetObjects();

	for (FCsJavascriptFileObjects& ScriptObject : Objects)
	{
		ScriptObject.Shutdown();
	}

	Manager_Objects.Shutdown();
	Objects.Reset();
	OwnerByOwnerIdMap.Reset();
	IndexByOwnerIdMap.Reset();
	IdByOwnerIdMap.Reset();
	OwnerIdByIdMap.Reset();
}

#undef USING_NS_CACHED2
#undef SET_CONTEXT2

bool UCsManager_Javascript::EditorScript_Shutdown_ByOwner(const FString& Context, UObject* Owner)
{
	void(*Log)(const FString&) = &NCsJs::FLog::Warning;

	CS_IS_PENDING_KILL(Owner)

	return EditorScriptImpl.Shutdown(Owner);
}

#pragma endregion Editor Scripts

// Events
#pragma region
 
void UCsManager_Javascript::SetupCallbacks()
{
	SET_CONTEXT(SetupCallbacks);

	CS_IS_PENDING_KILL_CHECKED(WorldContext)

	// TODO: Need OnAnyKey_Pressed for InputManagerWithGameplayTag
	/*
	typedef NCsInput::NManager::NFirst::FLibrary InputManagerLibrary;

	InputManagerLibrary::GetOnAnyKey_Pressed_EventChecked(Context, WorldContext).RemoveAll(this);
	InputManagerLibrary::GetOnAnyKey_Pressed_EventChecked(Context, WorldContext).AddUObject(this, &UCsManager_Javascript::OnAnyKey_Pressed);
	*/
}

void UCsManager_Javascript::OnAnyKey_Pressed(const FKey& Key)
{
	const FCsSettings_Manager_Javascript& Settings = FCsSettings_Manager_Javascript::Get();

	if (const FCsArray_int32* ArrayPtr = Settings.ReloadScriptsByKeyMap.Find(Key))
	{
		TArray<int32> Indices = ArrayPtr->Array;

		Indices.Sort([](const int32& a, const int32& b) {
			return  a < b;
		});

		const int32 Count = Indices.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			CurrentScriptIndex = I;
			bScriptReload	   = true;

			OnPreReloadScript_ScriptEvent.Broadcast(I);

			ReloadScript(I);
		}

		CurrentScriptIndex = INDEX_NONE;
		bScriptReload	   = false;
	}
}

#pragma endregion Events

#undef USING_NS_CACHED
#undef SET_CONTEXT