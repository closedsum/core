// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Engine/GameInstance.h"
// Types
#include "Managers/Time/CsTypes_Time.h"
// Singleton
#include "Managers/Singleton/CsGetManagerSingleton.h"
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
class CSCORE_API UCsGameInstance : public UGameInstance, public ICsGetManagerSingleton
{
	GENERATED_UCLASS_BODY()

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
	FDelegateHandle	TickDelegateHandle;

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

	void QueueExitGame();

	DECLARE_MULTICAST_DELEGATE(OnQueueExitGame)

	OnQueueExitGame OnQueueExitGame_Event;

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
