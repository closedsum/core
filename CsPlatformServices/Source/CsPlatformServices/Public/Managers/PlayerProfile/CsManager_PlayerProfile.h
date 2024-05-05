// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
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

#if WITH_EDITOR
	static UCsManager_PlayerProfile* Get(const UObject* InRoot = nullptr);
#else
FORCEINLINE static UCsManager_PlayerProfile* Get(const UObject* InRoot = nullptr)
{
	return s_bShutdown ? nullptr : s_Instance;
}
#endif // #if WITH_EDITOR

	static bool IsValid();
	static void Init(UObject* InRoot, TSubclassOf<UCsManager_PlayerProfile> ManagerPlayerProfileClass, UObject* InOuter = nullptr);
	static void Init(UObject* InRoot, UObject* InOuter = nullptr);
	static void Shutdown(const UObject* InRoot = nullptr);
	static bool HasShutdown();

#if WITH_EDITOR
protected:

	static ICsGetManagerPlayerProfile* Get_GetManagerPlayerProfile(const UObject* InRoot);
	static ICsGetManagerPlayerProfile* GetSafe_GetManagerPlayerProfile(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

	static UCsManager_PlayerProfile* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

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

	FORCEINLINE const UCsPlayerProfile* GetCurrentActiveProfile()
	{
		return CurrentActiveProfile;
	}

	FORCEINLINE const ECsPlayerProfile& GetCurrentActiveProfileType()
	{
		return CurrentActiveProfileType;
	}
};