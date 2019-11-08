// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CoreUObject/Public/UObject/Object.h"
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"
#include "CsManager_PlayerProfile.generated.h"

class UCsPlayerProfile;
class UCsManager_Achievement;

UCLASS(transient)
class CSCORE_API UCsManager_PlayerProfile : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsManager_PlayerProfile* Get();
	static bool IsValid();
	static void Init();
	static void Shutdown();
	static bool HasShutdown();

protected:

	void Initialize();
	void CleanUp();

private:
	// Singleton data
	static UCsManager_PlayerProfile* s_Instance;
	static bool s_bShutdown;

#pragma endregion Singleton

public:

	virtual void OnTick(const float& DeltaSeconds);

protected:

	UPROPERTY()
	TArray<UCsPlayerProfile*> Profiles;

	TMap<ECsPlayerProfile, UCsPlayerProfile*> ProfileMap;

public:

	virtual UCsPlayerProfile* CreateProfile(const ECsPlayerProfile& ProfileType);

	UCsPlayerProfile* GetProfile(const ECsPlayerProfile& ProfileType);
};