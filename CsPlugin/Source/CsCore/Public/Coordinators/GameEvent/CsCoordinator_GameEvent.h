// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Input/CsTypes_Input.h"
#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"

#include "CsCoordinator_GameEvent.generated.h"

class ICsGetCoordinatorGameEvent;

// NCsGameEvent::NCoordinator::FConsoleCommand
CS_FWD_DECLARE_CLASS_NAMESPACE_2(NCsGameEvent, NCoordinator, FConsoleCommand)

UCLASS()
class CSCORE_API UCsCoordinator_GameEvent : public UObject
{
	GENERATED_UCLASS_BODY()

#define ConsoleCommandManagerType NCsGameEvent::NCoordinator::FConsoleCommand

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsCoordinator_GameEvent* Get(UObject* InRoot = nullptr);
#else
	static UCsCoordinator_GameEvent* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR
	
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

// Console Command
#pragma region
private:

	ConsoleCommandManagerType* Manager_ConsoleCommand;

#pragma endregion Console Command

public:

	void OnGameEventInfo_ManagerInput0(const FCsGameEventInfo& Info);
	void OnGameEventInfo_ManagerInput1(const FCsGameEventInfo& Info);

	void ProcessGameEventInfo(const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info);

	/**
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnProcessGameEventInfo, const FECsGameEventCoordinatorGroup& /*Group*/, const FCsGameEventInfo& /*Info*/);

private:

	TArray<FOnProcessGameEventInfo> OnProcessGameEventInfo_Events;

public:

	FORCEINLINE FOnProcessGameEventInfo& GetOnProcessGameEventInfo_Event(const FECsGameEventCoordinatorGroup& Group) 
	{
		return OnProcessGameEventInfo_Events[Group.GetValue()];
	}

private:

	TMap<FECsGameEventCoordinatorGroup, TArray<FCsGameEventInfo>> QueuedGameEventInfosByGroupMap;

public:

	void QueueGameEventInfo(const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info);

	void OnPostProcessInput_ManagerInput0(const float& DeltaTime, const bool bGamePaused);
	void OnPostProcessInput_ManagerInput1(const float& DeltaTime, const bool bGamePaused);

	void ProcessQueuedGameEventInfos(const FECsGameEventCoordinatorGroup& Group);

#undef ConsoleCommandManagerType
};