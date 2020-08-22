// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Input/CsTypes_Input.h"

#include "CsCoordinator_GameEvent.generated.h"

class ICsGetCoordinatorGameEvent;

UCLASS()
class CSCORE_API UCsCoordinator_GameEvent : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsCoordinator_GameEvent* Get(UObject* InRoot = nullptr);
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetCoordinatorGameEvent* Get_GetCoordinatorGameEvent(UObject* InRoot);
	static ICsGetCoordinatorGameEvent* GetSafe_GetCoordinatorGameEvent(UObject* Object);

	static UCsCoordinator_GameEvent* GetSafe(UObject* Object);

public:

	static UCsCoordinator_GameEvent* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	bool bInitialized;

	virtual void Initialize();

public:

	static bool HasInitialized(UObject* InRoot);

protected:

	virtual void CleanUp();

private:
	// Singleton data
	static UCsCoordinator_GameEvent* s_Instance;
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

	void OnGameEventInfo(const FCsGameEventInfo& Info);

	void ProcessGameEventInfo(const FCsGameEventInfo& Info);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnProcessGameEventInfo, const FCsGameEventInfo& /*Info*/);

	FOnProcessGameEventInfo OnProcessGameEventInfo_Event;
};