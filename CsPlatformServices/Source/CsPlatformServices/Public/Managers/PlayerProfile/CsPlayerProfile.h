// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "CoreUObject/Public/UObject/Object.h"
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"
#include "CsPlayerProfile.generated.h"

class UWorld;
class ULocalPlayer;

UCLASS(transient)
class CSPLATFORMSERVICES_API UCsPlayerProfile : public UObject
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

	virtual void Update(const float& DeltaSeconds);
};