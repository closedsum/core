// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/GameInstance.h"
// Interface
#include "Singleton/CsGetManagerSingleton.h"
#include "Game/Transition/Event/CsGameInstance_Transition_Event.h"
// Types
#include "Managers/Time/CsTypes_Time.h"
#include "Game/Transition/CsGameInstance_Transition_Delegates.h"
#include "Game/Shutdown/CsGameInstance_Shutdown_Delegates.h"
// Containers
#include "Containers/Ticker.h"
// Play
#include "Play/Mode/CsPlayMode.h"

#include "CsGameInstance.generated.h"

class UCsManager_Singleton;
struct FCsRoutine;
class ULevel;
class ACsLevelScriptActor;

UCLASS(config = Game)
class CSCORE_API UCsGameInstance : public UGameInstance, 
								   public ICsGetManagerSingleton,
								   public ICsGameInstance_Transition_Event
{
	GENERATED_UCLASS_BODY()

private:

	typedef NCsGameInstance::NTransition::FOut_OnStart OnStartTransitionOutEventType;
	typedef NCsGameInstance::NTransition::FOnFinish OnFinishedTransitionEventType;

// UGameInstance Interface
#pragma region
public:

	virtual void Init() override;
	virtual void Shutdown() override;

#if WITH_EDITOR
	virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override;
#endif // #if WITH_EDITOR

#if WITH_EDITOR
	FGameInstancePIEParameters GameInstancePIEParametersCache;
#endif // #if WITH_EDITOR

protected:

	virtual void OnStart() override;

#pragma endregion UGameInstance Interface

// ICsGameInstance_Transition_Event
#pragma region
public:

	FORCEINLINE OnStartTransitionOutEventType& GetTransitionOut_OnStart_Event() { return TransitionOut_OnStart_Event; }
	FORCEINLINE OnFinishedTransitionEventType& GetTransition_OnFinish_Event() { return Transition_OnFinish_Event; }

#pragma endregion ICsGameInstance_Transition_Event

// GameInstance_Transition_Event
#pragma region
protected:

	OnStartTransitionOutEventType TransitionOut_OnStart_Event;

public:

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Game Instance")
	FCsGameInstance_TransitionOut_OnStart TransitionOut_OnStart_ScriptEvent;

protected:

	OnFinishedTransitionEventType Transition_OnFinish_Event;

public:

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Game Instance")
	FCsGameInstance_Transition_OnFinish Transition_OnFinish_ScriptEvent;

#pragma endregion GameInstance_Transition_Event

// Shutdown
#pragma region

#define OnPreShutdownEventType NCsGameInstance::FOnPreShutdown

protected:

	OnPreShutdownEventType OnPreShutdown_Event;

public:

	FORCEINLINE OnPreShutdownEventType& GetOnPreShutdown_Event() { return OnPreShutdown_Event; }

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Game Instance")
	FCsGameInstance_OnPreShutdown OnPreShutdown_ScriptEvent;

#undef OnPreShutdownEventType

#pragma endregion Shutdown

// FExec Interface
#pragma region

	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out = *GLog) override;

#pragma endregion FExec Interface

// Tick
#pragma region
protected:

	/** Delegate for callbacks to Tick */
	FTickerDelegate	TickDelegate;

	/** Handle to various registered delegates */
	FTSTicker::FDelegateHandle	TickDelegateHandle;

	virtual bool Tick(float DeltaSeconds);

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdate, const FCsDeltaTime& DeltaTime);

	FOnUpdate OnUpdate_Event;

#pragma endregion Tick

	bool IsSimulateInEditor();

// Start
#pragma region
protected:

	bool bHasStartedFromEntry;

public:

	FORCEINLINE bool HasStartedFromEntry() const { return bHasStartedFromEntry; }

#pragma endregion Start

// Exit
#pragma region
protected:

	virtual bool CanExitGame();

public:

	virtual void QueueExitGame();

#define OnQueueExitGameEventType NCsGameInstance::FOnQueueExitGame

protected:

	OnQueueExitGameEventType OnQueueExitGame_Event;

public:

	FORCEINLINE OnQueueExitGameEventType& GetOnQueueExitGame_Event() { return OnQueueExitGame_Event; }

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Game Instance")
	FCsGameInstance_OnQueueExitGame OnQueueExitGame_ScriptEvent;

#undef OnQueueExitGameEventType

private:

	void ExitGame();

protected:

	virtual char ExitGame_Internal(FCsRoutine* R);

#pragma endregion Exit

// Managers
#pragma region
protected:

	UPROPERTY()
	UCsManager_Singleton* Manager_Singleton;

	virtual void ConstructManagerSingleton();

#pragma endregion Managers

// ICsGetManagerSingleton
#pragma region
public:

	FORCEINLINE UCsManager_Singleton* GetManager_Singleton() const
	{
		return Manager_Singleton;
	}

#pragma endregion ICsGetManagerSingleton

// Editor
#pragma region
private:

	ECsPlayMode PlayMode;

	bool bPIE;
	bool bStandaloneFromEditor;
	bool bStandaloneMobileFromEditor;
	bool bOnStart;

public:

	FORCEINLINE bool IsPIE() const { return bPIE; }
	FORCEINLINE bool IsMobilePIE() const { return NCsPlayMode::IsMobilePIE(PlayMode); }
	FORCEINLINE bool IsStandaloneFromEditor() const { return bStandaloneFromEditor; }
	FORCEINLINE bool IsStandaloneMobileFromEditor() const { return bStandaloneMobileFromEditor; }
	FORCEINLINE bool IsMobilePreviewEditor() const { return NCsPlayMode::IsMobilePreviewEditor(PlayMode); }
	FORCEINLINE bool HasOnStart() const { return bOnStart; }

#pragma endregion Editor

// Transition
#pragma region
protected:

	bool bFinishedTransition;

public:

	FORCEINLINE bool HasFinishedTransition() const { return bFinishedTransition; }

#pragma endregion Transition
};
