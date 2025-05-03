// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "CsMacro_Cached.h"
#include "Managers/Time/CsTypes_Time.h"
#include "Coordinators/GameplayTag/CsCoordinator_GameplayTag_Delegates.h"
#include "Templates/SubclassOf.h"
// Container
#include "Containers/CsGameplayTagCountContainer.h"

#include "CsCoordinator_GameplayTag.generated.h"

class ICsGetCoordinatorGameplayTag;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME(CsCoordinator_GameplayTag)

UCLASS(BlueprintType, Blueprintable, Meta = (ShowWorldContextPin))
class CSGAMEPLAYTAGS_API UCsCoordinator_GameplayTag : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	using CountContainerType = NCsGameplayTag::NCount::FContainer;
	using OnProcessGameplayTagEventEventType = NCsGameplayTag::NCoordinator::FOnProcessGameplayTagEvent;

	CS_USING_CACHED_FUNCTION_NAME(CsCoordinator_GameplayTag);

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsCoordinator_GameplayTag* Get(UObject* InRoot = nullptr);
#else
	static UCsCoordinator_GameplayTag* Get(UObject* InRoot = nullptr)
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

	static void Init(UObject* InRoot, TSubclassOf<UCsCoordinator_GameplayTag> CoordinatorClass);
	static void Init(UObject* InRoot);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetCoordinatorGameplayTag* Get_GetCoordinatorGameplayTag(UObject* InRoot);
	static ICsGetCoordinatorGameplayTag* GetSafe_GetCoordinatorGameplayTag(UObject* Object);

	static UCsCoordinator_GameplayTag* GetSafe(UObject* Object);

public:

	static UCsCoordinator_GameplayTag* GetFromWorldContextObject(UObject* WorldContextObject);

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
	static UCsCoordinator_GameplayTag* s_Instance;
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

// StartPlay
#pragma region
public:

	void StartPlay();

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "CsGameplayTags|Coordinators|GameplayTag|Start Play", meta = (DisplayName = "Start Play"))
	void ReceiveStartPlay();

#pragma endregion StartPlay

// Update
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "CsGameplayTags|Coordinators|GameplayTag|Update", meta = (DisplayName = "Update"))
	void ReceiveUpdate(const FCsDeltaTime& DeltaTime);

#pragma endregion Update

public:

	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Coordinators|Game Event")
	UObject* GetWorldContext() const;

// Tag
#pragma region
private:

	CountContainerType CountContainer;

public:

	FORCEINLINE bool HasMatchingTag(const FGameplayTag& TagToCheck) const { return CountContainer.HasMatchingTag(TagToCheck); }
	FORCEINLINE bool HasAllMatchingTags(const FGameplayTagContainer& TagContainer) const { return CountContainer.HasAllMatchingTags(TagContainer); }
	FORCEINLINE bool HasAnyMatchingTags(const FGameplayTagContainer& TagContainer) const { return CountContainer.HasAnyMatchingTags(TagContainer); }

	void GetOwnedTags(FGameplayTagContainer& OutTagContainer) const;

	[[nodiscard]] FORCEINLINE const FGameplayTagContainer& GetOwnedTags() const { return CountContainer.GetExplicitTags(); }

	/** Checks whether the query matches the owned GameplayTags */
	/*FORCEINLINE bool MatchesGameplayTagQuery(const FGameplayTagQuery& TagQuery) const
	{
		return TagQuery.Matches(GameplayTagCountContainer.GetExplicitGameplayTags());
	}*/

	/** Returns the number of instances of a given tag */
	FORCEINLINE int32 GetTagCount(const FGameplayTag& TagToCheck) const { return CountContainer.GetTagCount(TagToCheck); }
	/** Forcibly sets the number of instances of a given tag */
	FORCEINLINE void SetTagMapCount(const FGameplayTag& Tag, const int32& NewCount) { CountContainer.SetTagCount(Tag, NewCount); }

	/** Update the number of instances of a given tag and calls callback */
	FORCEINLINE void UpdateTagMap(const FGameplayTag& BaseTag, int32 CountDelta)
	{
		if (CountContainer.UpdateTagCount(BaseTag, CountDelta))
			OnTagUpdated(BaseTag, CountDelta > 0);
	}

	/** Update the number of instances of a given tag and calls callback */
	FORCEINLINE void UpdateTagMap(const FGameplayTagContainer& Container, int32 CountDelta)
	{
		if (!Container.IsEmpty())
			UpdateTagMap_Internal(Container, CountDelta);
	}

private:

	void UpdateTagMap_Internal(const FGameplayTagContainer& Container, const int32& CountDelta);

	void OnTagUpdated(const FGameplayTag& Tag, const bool& TagExists);

public:

	FORCEINLINE void AddTag(const FGameplayTag& GameplayTag, const int32& Count = 1)				{ UpdateTagMap(GameplayTag, Count); }
	FORCEINLINE void AddTags(const FGameplayTagContainer& GameplayTags, const int32& Count = 1)		{ UpdateTagMap(GameplayTags, Count); }
	FORCEINLINE void RemoveTag(const FGameplayTag& GameplayTag, const int32& Count = 1)				{ UpdateTagMap(GameplayTag, -Count); }
	FORCEINLINE void RemoveTags(const FGameplayTagContainer& GameplayTags, const int32& Count = 1)	{ UpdateTagMap(GameplayTags, -Count); }
	FORCEINLINE void SetTagCount(const FGameplayTag& GameplayTag, const int32& NewCount)			{ SetTagMapCount(GameplayTag, NewCount); }

#pragma endregion Tag

// Events
#pragma region
public:

	void OnTagEvent_ManagerInput0(const FCsGameplayTagEvent& Event);
	void OnTagEvent_ManagerInput1(const FCsGameplayTagEvent& Event);

	void ProcessGameplayTagEvent(const FECsGameplayTagCoordinatorGroup& Group, const FCsGameplayTagEvent& Info);

private:

	TArray<OnProcessGameplayTagEventEventType> OnProcessGameplayTagEvent_Events;

public:

	FORCEINLINE OnProcessGameplayTagEventEventType& GetOnProcessGameplayTagEvent_Event(const FECsGameplayTagCoordinatorGroup& Group) 
	{
		return OnProcessGameplayTagEvent_Events[Group.GetValue()];
	}

	UPROPERTY(BlueprintAssignable, Category = "CsGameplayTags|Coordinators|GameplayTag")
	FCsCoordinatorGameplayTag_OnProcessGameplayTagEvent OnProcessGameplayTagEvent_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "CsGameplayTags|Coordinators|GameplayTag")
	FCsCoordinatorGameplayTag_OnProcessGameplayTagEvent2 OnProcessGameplayTagEvent2_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "CsGameplayTags|Coordinators|GameplayTag")
	FCsCoordinatorGameplayTag_OnProcessGameplayTagEvent OnProcessGameplayTagEvent_ManagerInput0_ScriptEvent;

private:

	TMap<FECsGameplayTagCoordinatorGroup, TArray<FCsGameplayTagEvent>> QueuedGameplayTagEventsByGroupMap;

public:

	void QueueGameplayTagEvent(const FECsGameplayTagCoordinatorGroup& Group, const FCsGameplayTagEvent& Event);

	/**
	* Handle queued events for Group (FECsGameplayTagCoordinatorGroup): ManagerInput0.
	* 
	* @param DeltaTime
	* @param bGamePaused
	*/
	void OnPostProcessInput_ManagerInput0(const float& DeltaTime, const bool bGamePaused);

	/**
	* Handle queued events for Group (FECsGameplayTagCoordinatorGroup): ManagerInput1.
	*
	* @param DeltaTime
	* @param bGamePaused
	*/
	void OnPostProcessInput_ManagerInput1(const float& DeltaTime, const bool bGamePaused);

	void ProcessQueuedGameplayTagEvents(const FECsGameplayTagCoordinatorGroup& Group);

#pragma endregion Events
};