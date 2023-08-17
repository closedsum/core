// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/Time/CsUpdateGroup.h"

#include "CsManager_Time.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerTime_OnUpdate, const FECsUpdateGroup&, Group, const FCsDeltaTime&, DeltaTime);

class ICsGetManagerTime;

// NCsTime::NManager::FConsoleCommand
CS_FWD_DECLARE_CLASS_NAMESPACE_2(NCsTime, NManager, FConsoleCommand)

UCLASS()
class CSCORE_API UCsManager_Time : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Time* Get(UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_Time* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR
	static UCsManager_Time* GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsManager_Time* GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot);
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerTime* Get_GetManagerTime(UObject* InRoot);
	static ICsGetManagerTime* GetSafe_GetManagerTime(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Time* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
private:

	UObject* MyRoot;

public:

	FORCEINLINE void SetMyRoot(UObject* InRoot)
	{
		MyRoot = InRoot;
	}

	FORCEINLINE const UObject* GetMyRoot() const
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

// Console Commnad
#pragma region
private:

#define ConsoleCommandManagerType NCsTime::NManager::FConsoleCommand
	ConsoleCommandManagerType* Manager_ConsoleCommand;
#undef ConsoleCommandManagerType

#pragma endregion Console Command

protected:

	TArray<FCsUpdateGroup> UpdateGroups;

public:

	/**
	*
	*
	* @param Group
	*/
	void Start(const FECsUpdateGroup& Group);

	// Pause
#pragma region
public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPause, const FECsUpdateGroup& /*Group*/, bool /*bPaused*/);

private:

	TArray<FOnPause> OnPause_Events;

public:

	FORCEINLINE FOnPause& GetOnPause_Event(const FECsUpdateGroup& Group)
	{
		return OnPause_Events[Group.GetValue()];
	}

#define OnPauseDelegateType FOnPause::FDelegate

	FORCEINLINE FDelegateHandle AddOnPause(const FECsUpdateGroup& Group, OnPauseDelegateType& OnPause)
	{
		return OnPause_Events[Group.GetValue()].Add(OnPause);
	}

#undef OnPauseDelegateType

	FORCEINLINE void RemoveOnPause(const FECsUpdateGroup& Group, const FDelegateHandle& Handle)
	{
		OnPause_Events[Group.GetValue()].Remove(Handle);
	}

	/**
	* Pause updates for the specified Group
	*
	* @param Group
	*/
	FORCEINLINE void Pause(const FECsUpdateGroup& Group)
	{
		checkf(!IsPaused(Group), TEXT("UCsManager_Time::Pause: UpdateGroup: %s is ALREADY Paused."), Group.ToChar());

		UpdateGroups[Group.GetValue()].Pause();
		OnPause_Events[Group.GetValue()].Broadcast(Group, true);
	}

	/**
	* Unpause updates for the specified Group
	*
	* @param Group
	*/
	FORCEINLINE void Unpause(const FECsUpdateGroup& Group)
	{
		checkf(IsPaused(Group), TEXT("UCsManager_Time::Pause: UpdateGroup: %s is ALREADY Unpaused."), Group.ToChar());

		UpdateGroups[Group.GetValue()].Unpause();
		OnPause_Events[Group.GetValue()].Broadcast(Group, false);
	}

	/**
	* Check if updates are paused for the specified Group
	*
	* @param Group
	* return		Whether updating is paused or not.
	*/
	FORCEINLINE bool IsPaused(const FECsUpdateGroup& Group)
	{
		return UpdateGroups[Group.GetValue()].IsPaused();
	}

#pragma endregion Pause

	// Update
#pragma region
public:

	/**
	*
	*
	* @param Group
	* @param DeltaTime
	*/
	void Update(const FECsUpdateGroup& Group, const float& DeltaTime);

	/**
	*
	*
	* @param Group
	* @param DeltaTime
	* @param Time
	* @param RealTime
	*/
	void Update(const FECsUpdateGroup& Group, const float& DeltaTime, const float& Time, const float& RealTime);

#define OnUpdateType FCsUpdateGroup::FOnUpdate
#define OnUpdateDelegateType FCsUpdateGroup::FOnUpdate::FDelegate

	FORCEINLINE OnUpdateType& GetOnUpdate_Event(const FECsUpdateGroup& Group)
	{
		return UpdateGroups[Group.GetValue()].GetOnUpdate_Event();
	}

	FORCEINLINE FDelegateHandle AddOnUpdate(const FECsUpdateGroup& Group, OnUpdateDelegateType& OnUpdate)
	{
		return UpdateGroups[Group.GetValue()].AddOnUpdate(OnUpdate);
	}

	FORCEINLINE void RemoveOnUpdate(const FECsUpdateGroup& Group, const FDelegateHandle& Handle)
	{
		UpdateGroups[Group.GetValue()].RemoveOnUpdate(Handle);
	}

	UPROPERTY(BlueprintAssignable)
	FCsManagerTime_OnUpdate OnUpdate_ScriptEvent;

#undef OnUpdateType
#undef OnUpdateDelegateType

	FORCEINLINE void SetCustom(const FECsUpdateGroup& Group, const bool& ClearOnUpdate)
	{
		UpdateGroups[Group.GetValue()].SetCustom(ClearOnUpdate);
	}

	FORCEINLINE void ClearCustom(const FECsUpdateGroup& Group)
	{
		UpdateGroups[Group.GetValue()].ClearCustom();
	}

	FORCEINLINE bool IsCustom(const FECsUpdateGroup& Group) const
	{
		return UpdateGroups[Group.GetValue()].IsCustom();
	}

	FORCEINLINE void SetCustomDeltaTime(const FECsUpdateGroup& Group, const FCsDeltaTime& DeltaTime)
	{
		UpdateGroups[Group.GetValue()].SetCustomDeltaTime(DeltaTime);
	}

#pragma endregion Update

public:

	/**
	*
	*
	* @param Group
	* return 
	*/
	FORCEINLINE const FCsTime& GetTime(const FECsUpdateGroup& Group) const
	{
		return UpdateGroups[Group.GetValue()].GetTime();
	}

	/**
	*
	*
	* @param Group
	* return
	*/
	FCsTime GetTimeNow(const FECsUpdateGroup& Group);

	/**
	*
	*
	* @param Group
	* return
	*/
	FORCEINLINE const FCsDeltaTime& GetTimeSinceStart(const FECsUpdateGroup& Group) const
	{
		return UpdateGroups[Group.GetValue()].GetTimeSinceStart();
	}

	/**
	*
	*
	* @param Group
	* return
	*/
	FORCEINLINE const FCsDeltaTime& GetScaledDeltaTime(const FECsUpdateGroup& Group) const
	{
		return UpdateGroups[Group.GetValue()].GetScaledDeltaTime();
	}

	/**
	*
	*
	* @param Group
	* @param ScaleName
	* return
	*/
	FORCEINLINE const FCsDeltaTime& GetScaledDeltaTime(const FECsUpdateGroup& Group, const FName& ScaleName) const
	{
		return UpdateGroups[Group.GetValue()].GetScaledDeltaTime(ScaleName);
	}

	/**
	*
	* 
	* @param Group
	* @param Scale
	*/
	FORCEINLINE void SetScaledDeltaTime(const FECsUpdateGroup& Group, const float& Scale)
	{
		UpdateGroups[Group.GetValue()].SetScale(Scale);
	}

	/**
	* Resets the Scale (to 1.0f) applied to the delta time for the specified Group.
	*
	* @param Group
	*/
	FORCEINLINE void ResetScaledDeltaTime(const FECsUpdateGroup& Group)
	{
		UpdateGroups[Group.GetValue()].ResetScale();
	}

	void SetupInputListener();

	void OnAnyKey_Pressed(const FKey& Key);
	void OnAnyKey_Released(const FKey& Key);
};