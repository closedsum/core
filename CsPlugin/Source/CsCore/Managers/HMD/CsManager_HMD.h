// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "../CoreUObject/Public/UObject/Object.h"
#include "CsManager_HMD.generated.h"

UCLASS(transient)
class CSCORE_API UCsManager_HMD : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsManager_HMD* Get();
	static void Init();
	static void Shutdown();

protected:

	void Initialize();
	void CleanUp();

private:
	// Singleton data
	static UCsManager_HMD* s_Instance;
	static bool s_bShutdown;

#pragma endregion Singleton

// Tick
#pragma region
public:

	/** Delegate for callbacks to Tick */
	FTickerDelegate	TickDelegate;

	/** Handle to various registered delegates */
	FDelegateHandle	TickDelegateHandle;

	bool Tick(float DeltaSeconds);

#pragma endregion Tick
};