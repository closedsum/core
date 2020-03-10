// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CoreUObject/Public/UObject/Object.h"
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"
#include "CsManager_PlayerProfile.generated.h"

class UCsPlayerProfile;
class ICsGetManagerPlayerProfile;

UCLASS(transient)
class CSPLATFORMSERVICES_API UCsManager_PlayerProfile : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsManager_PlayerProfile* Get(UObject* InRoot = nullptr);
	static bool IsValid();
	static void Init(UObject* InRoot);
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown();

#if WITH_EDITOR
protected:

	static ICsGetManagerPlayerProfile* Get_GetManagerPlayerProfile(UObject* InRoot);
	static ICsGetManagerPlayerProfile* GetSafe_GetManagerPlayerProfile(UObject* InRoot);

	static UCsManager_PlayerProfile* GetSafe(UObject* InRoot);

public:

	static UCsManager_PlayerProfile* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	void Initialize();
	void CleanUp();

private:
	// Singleton data
	static UCsManager_PlayerProfile* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot() const
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

public:

	virtual void Update(const float& DeltaSeconds);

protected:

	UPROPERTY()
	TArray<UCsPlayerProfile*> Profiles;

	TMap<ECsPlayerProfile, UCsPlayerProfile*> ProfileMap;

public:

	virtual UCsPlayerProfile* CreateProfile(const ECsPlayerProfile& ProfileType);

	UCsPlayerProfile* GetProfile(const ECsPlayerProfile& ProfileType);

protected:

	UCsPlayerProfile* CurrentActiveProfile;

	ECsPlayerProfile CurrentActiveProfileType;

public:

	void SetCurrentActiveProfile(const ECsPlayerProfile& ProfileType);

	const UCsPlayerProfile* GetCurrentActiveProfile();

	const ECsPlayerProfile& GetCurrentActiveProfileType();
};