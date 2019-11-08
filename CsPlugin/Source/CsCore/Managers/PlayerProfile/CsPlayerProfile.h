// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "CoreUObject/Public/UObject/Object.h"
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"
#include "CsPlayerProfile.generated.h"

class UWorld;
class ULocalPlayer;
class UCsManager_Save;
class UCsManager_Achievement;

UCLASS(transient)
class CSCORE_API UCsPlayerProfile : public UObject
{
	GENERATED_UCLASS_BODY()

protected:

	ECsPlayerProfile ProfileType;

public:

	void SetProfileType(const ECsPlayerProfile& InProfileType);

// World
#pragma region
protected:
	
	TWeakObjectPtr<UWorld> CurrentWorld;

public:

	void SetCurrentWorld(UWorld* World);

	UWorld* GetCurrentWorld();

#pragma endregion World

// Player
#pragma region
protected:

	ULocalPlayer* LocalPlayer;

public:

	void SetLocalPlayer(ULocalPlayer* Player);

#pragma endregion Player

public:

	virtual void Init();

// Managers
#pragma region
public:

	// Save

	TSubclassOf<UCsManager_Save> Manager_Save_Class;

	UPROPERTY()
	UCsManager_Save* Manager_Save;

	// Achievement

	TSubclassOf<UCsManager_Achievement> Manager_Achievement_Class;

	UPROPERTY()
	UCsManager_Achievement* Manager_Achievement;

#pragma endregion Managers

	virtual void OnTick(const float& DeltaSeconds);
};