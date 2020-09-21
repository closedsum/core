// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Time/CsTypes_Time.h"

#include "CsManager_Playback.generated.h"

class ICsGetManagerPlayback;

UCLASS(transient)
class CSPLAYBACK_API UCsManager_Playback : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsManager_Playback* Get(UObject* InRoot = nullptr);

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot);

	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

	static void Shutdown();

#if WITH_EDITOR
protected:

	static ICsGetManagerPlayback* Get_GetManagerPlayback(UObject* InRoot);
	static ICsGetManagerPlayback* GetSafe_GetManagerPlayback(UObject* Object);

	static UCsManager_Playback* GetSafe(UObject* Object);

public:

	static UCsManager_Playback* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	bool bInitialized;

	virtual void Initialize();

public:

	static bool HasInitialized(UObject* InRoot);

protected:

	void CleanUp();

private:
	// Singleton data
	static UCsManager_Playback* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

public:

	void Update(const FCsDeltaTime& DeltaTime);
};