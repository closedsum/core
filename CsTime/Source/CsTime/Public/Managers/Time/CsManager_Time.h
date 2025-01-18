// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "Managers/Time/CsUpdateGroup.h"
#include "Managers/Time/CsManager_Time_Delegates.h"
#include "Templates/SubclassOf.h"

#include "CsManager_Time.generated.h"

class ICsGetManagerTime;

// NCsTime::NManager::FConsoleCommand
CS_FWD_DECLARE_CLASS_NAMESPACE_2(NCsTime, NManager, FConsoleCommand)

UCLASS()
class CSTIME_API UCsManager_Time : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	using ConsoleCommandManagerType = NCsTime::NManager::FConsoleCommand;
	using OnPauseEventType = NCsTime::NManager::FOnPause;
	using OnPauseDelegateType = OnPauseEventType::FDelegate;
	using OnSetScaledDeltaTimeEventType = NCsTime::NManager::FOnSetScaledDeltaTime;
	using OnResetScaledDeltaTimeEventType = NCsTime::NManager::FOnResetScaledDeltaTime;
	using OnUpdateType = FCsUpdateGroup::FOnUpdate;
	using OnUpdateDelegateType = FCsUpdateGroup::FOnUpdate::FDelegate;
	using OnUpdateEventType = NCsTime::NManager::FOnUpdate;

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Time* Get(const UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_Time* Get(const UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	template<typename T>
	FORCEINLINE static T* Get(const UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static UCsManager_Time* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsManager_Time* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Time> ManagerTimeClass, UObject* InOuter = nullptr);
	static void Init(UObject* InRoot, UObject* InOuter = nullptr);
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerTime* Get_GetManagerTime(const UObject* InRoot);
	static ICsGetManagerTime* GetSafe_GetManagerTime(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

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
protected:

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

	ConsoleCommandManagerType* Manager_ConsoleCommand;

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
private:

	TArray<OnPauseEventType> OnPause_Events;

public:

	FORCEINLINE OnPauseEventType& GetOnPause_Event(const FECsUpdateGroup& Group)
	{
		return OnPause_Events[Group.GetValue()];
	}

	FORCEINLINE FDelegateHandle AddOnPause(const FECsUpdateGroup& Group, OnPauseDelegateType& OnPause)
	{
		return OnPause_Events[Group.GetValue()].Add(OnPause);
	}

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

	OnUpdateEventType OnUpdate_Event;
	FORCEINLINE OnUpdateEventType& GetOnUpdate_Event() { return OnUpdate_Event; }

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Mangager|Time")
	FCsManagerTime_OnUpdate OnUpdate_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Mangager|Time")
	FCsManagerTime_OnUpdate2 OnUpdate2_ScriptEvent;

	FORCEINLINE FCsManagerTime_OnUpdate& GetOnUpdate_ScriptEvent() { return OnUpdate_ScriptEvent; }
	
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

		OnSetScaledDeltaTime_Event.Broadcast(Group, Scale);
		OnSetScaledDeltaTime_ScriptEvent.Broadcast(Group, Scale);
	}

	OnSetScaledDeltaTimeEventType OnSetScaledDeltaTime_Event;
	FORCEINLINE OnSetScaledDeltaTimeEventType& GetOnSetScaledDeltaTime_Event() { return OnSetScaledDeltaTime_Event; }

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Mangager|Time")
	FCsManagerTime_OnSetScaledDeltaTime OnSetScaledDeltaTime_ScriptEvent;

	/**
	* Resets the Scale (to 1.0f) applied to the delta time for the specified Group.
	*
	* @param Group
	*/
	FORCEINLINE void ResetScaledDeltaTime(const FECsUpdateGroup& Group)
	{
		UpdateGroups[Group.GetValue()].ResetScale();

		OnResetScaledDeltaTime_Event.Broadcast(Group);
		OnResetScaledDeltaTime_ScriptEvent.Broadcast(Group);
	}

	OnResetScaledDeltaTimeEventType OnResetScaledDeltaTime_Event;
	FORCEINLINE OnResetScaledDeltaTimeEventType& GetOnResetScaledDeltaTime_Event() { return OnResetScaledDeltaTime_Event; }

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Mangager|Time")
	FCsManagerTime_OnResetScaledDeltaTime OnResetScaledDeltaTime_ScriptEvent;
};