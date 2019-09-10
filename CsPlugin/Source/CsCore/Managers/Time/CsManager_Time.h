// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Engine/Classes/Components/ActorComponent.h"
#include "CsManager_Time.generated.h"


UCLASS()
class CSCORE_API UCsManager_Time : public UActorComponent
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region
protected:

	virtual void OnRegister() override;

#pragma endregion UActorComponent Interface

// Singleton
#pragma region

public:

	static UCsManager_Time* Get();
	static void Init(UCsManager_Time* Manager);
	static void Shutdown();

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Time* s_Instance;
	static bool s_bShutdown;

#pragma endregion Singleton
};