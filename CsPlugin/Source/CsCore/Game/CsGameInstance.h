// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/GameInstance.h"
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Containers/Ticker.h"
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
public:

	virtual void Init() override;
	virtual void Shutdown() override;

#if WITH_EDITOR
	virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override;
#endif // #if WITH_EDITOR

#if WITH_EDITOR
	FGameInstancePIEParameters GameInstancePIEParametersCache;
#endif // #if WITH_EDITOR

#pragma endregion UGameInstance Interface

// Tick
#pragma region
protected:

	/** Delegate for callbacks to Tick */
	FTickerDelegate	TickDelegate;

	/** Handle to various registered delegates */
	FDelegateHandle	TickDelegateHandle;

	virtual bool Tick(float DeltaSeconds);

#pragma endregion Tick

	bool IsSimulateInEditor();

// Exit
#pragma region
public:

	void ExitGame();

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
};
