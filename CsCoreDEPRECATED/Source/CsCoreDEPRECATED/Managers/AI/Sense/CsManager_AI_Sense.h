// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Components/ActorComponent.h"
#include "Types/CsTypes_Sound.h"
#include "CsManager_AI_Sense.generated.h"

class AActor;

UCLASS()
class CSCOREDEPRECATED_API UCsManager_AI_Sense : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:

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

	static UCsManager_AI_Sense* Get();
	static void Init(UCsManager_AI_Sense* Manager);
	static void Shutdown();

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_AI_Sense* s_Instance;
	static bool s_bShutdown;

#pragma endregion Singleton

public:

	virtual void OnTick(const float& DeltaSeconds);

	// Noise
#pragma region
public:

	virtual void ReportNoiseEvent(const FECsNoiseEvent& EventType, const FVector& Location, const float& Loudness = 1.0f, AActor* Instigator = nullptr, const float& MaxRange = 0.0f, const FName& Tag = NAME_None);

#pragma endregion Noise
};