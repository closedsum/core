// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CoreUObject/Public/UObject/Object.h"
#include "Managers/Achievement/CsTypes_Achievement.h"
#include "Managers/MemoryResource/CsManager_MemoryResource_Fixed.h"
#include "OnlineSubsystem.h"
#include "OnlineStats.h"
#include "Interfaces/OnlineAchievementsInterface.h"
#include "CsManager_Achievement.generated.h"

struct ICsAchievement;
class UWorld;
class ULocalPlayer;
class ICsGetManagerAchievement;

// Structs
#pragma region

	// Memory Resource
#pragma region

struct CSCORE_API FCsMemoryResource_AchievementActionInfo : public TCsMemoryResource<FCsAchievementActionInfo>
{
};

struct CSCORE_API FCsManager_MemoryResource_AchievementActionInfo : public TCsManager_MemoryResource_Fixed<FCsAchievementActionInfo, FCsMemoryResource_AchievementActionInfo, 256>
{
};

#pragma endregion Memory Resource

#pragma endregion Structs

// Delegates
#pragma region

// QueryIds
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerAchievement_OnQueryIds, bool, WasSuccessful);
// QueryDescriptions
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerAchievement_OnQueryDescriptions, bool, WasSuccessful);
// Complete
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerAchievement_OnComplete, bool, WasSuccessful, const FECsAchievement&, Achievement);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerAchievement_OnCompleteAll);
// Progress
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsManagerAchievement_OnProgress, bool, WasSuccessful, const FECsAchievement&, Achievement, const float&, Progress);
// Reset
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsManagerAchievement_OnReset, bool, WasSuccessful, const FECsAchievement&, Achievement, const float&, Progress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerAchievement_OnResetAll);

#pragma endregion Delegates

UCLASS(transient)
class CSCORE_API UCsManager_Achievement : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsManager_Achievement* Get(UObject* InRoot = nullptr);

	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid();
	static void Init(UObject* InRoot, UClass* ManagerAchievementClass);
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown();

#if WITH_EDITOR
protected:

	static ICsGetManagerAchievement* Get_GetManagerAchievement(UObject* InRoot);
	static ICsGetManagerAchievement* GetSafe_GetManagerAchievement(UObject* Object);

	static UCsManager_Achievement* GetSafe(UObject* Object);

public:

	static UCsManager_Achievement* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Achievement* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject * MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot() const
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

public:

	virtual void Start();

	/** Construct an Achievement object. */
	virtual ICsAchievement* ConstructAchievement();

protected:

	TArray<ICsAchievement*> Achievements;
	TMap<FString, ICsAchievement*> AchievementMap;

// Player
#pragma region
protected:

	ULocalPlayer* LocalPlayer;

public:

	void SetLocalPlayer(ULocalPlayer* Player);

	/**
	* Get the UniqueNetId for the LocalPlayer. This assumes the OnlineSubsystem and OnlineIdentity exist.
	* return	Id for Local Player.
	*/
	TSharedPtr<const FUniqueNetId> GetLocalPlayerId();

	/**
	* Get the UniqueNetId for the LocalPlayer. This assumes the OnlineSubsystem and OnlineIdentity exist.
	* return	Id for Local Player.
	*/
	const FUniqueNetId& GetLocalPlayerIdRef();

#pragma endregion Player

	virtual void Update(const float& DeltaSeconds);

// Action
#pragma region
protected:

	/** Manager to handle a resource pool of FCsAchievementActionInfo. */
	FCsManager_MemoryResource_AchievementActionInfo Manager_MemoryResource;

	/**
	* Queue an action (Write, Complete, or Reset) to perform on an achievement.
	* The action gets enqueued into the list of actions being processed.
	*
	* @param Action			Type of action to queue (Write, Complete, or Reset).
	* @param Achievement	The Achievement to perform the action on.
	* @param Percent		if Action == Write, the progress as a percent [0.0, 1.0] inclusive.
	*/
	void QueueAction(const ECsAchievementAction& Action, const FECsAchievement& Achievement, const float& Percent = 0.0f);

	/**
	* Queue an action (QueryIds, QueryDescriptions, Complete All, or Reset All) to preform. 
	* The action gets enqueued into the list of actions being processed.
	*
	* @param Action		Type of action to queue (QueryIds, QueryDescriptions, Complete All, or Reset All).
	*/
	void QueueAction(const ECsAchievementAction& Action);

	/**
	* Queue an action (QueryIds, QueryDescriptions, Complete All, or Reset All) as the first action (Head) to be processed.
	*
	* @param Action			Type of action to queue (Write, Complete, or Reset).
	* @param Achievement	The Achievement to perform the action on.
	* @param Percent		if Action == Write, the progress as a percent [0.0, 1.0] inclusive.
	*/
	void QueueActionAsHead(const ECsAchievementAction& Action, const FECsAchievement& Achievement, const float& Percent = 0.0f);

	/**
	* Queue an action (QueryIds, QueryDescriptions, Complete All, or Reset All) as the first action (Head) to be processed.
	*
	* @param Action		Type of action to queue (QueryIds, QueryDescriptions, Complete All, or Reset All).
	*/
	void QueueActionAsHead(const ECsAchievementAction& Action);

	/**
	* Queue an action (QueryIds, QueryDescriptions, Complete All, or Reset All) 
	* after the first action (Head) to be processed.
	*
	* @param Action			Type of action to queue (Write, Complete, or Reset).
	* @param Achievement	The Achievement to perform the action on.
	* @param Percent		if Action == Write, the progress as a percent [0.0, 1.0] inclusive.
	*/
	void QueueActionAfterHead(const ECsAchievementAction& Action, const FECsAchievement& Achievement, const float& Percent = 0.0f);

	/**
	* Queue an action (QueryIds, QueryDescriptions, Complete All, or Reset All)
	* after the first action (Head) to be processed.
	*
	* @param Action		Type of action to queue (Write, Complete, or Reset).
	*/
	void QueueActionAfterHead(const ECsAchievementAction& Action);

#pragma endregion Action

// Query
#pragma region
protected:

	FCsAchievementQueryState QueryState;

	// Ids
#pragma region
public:

	/**
	*
	*/
	void QueryIds();

protected:

	void QueryIds_Internal();

public:

	/** Delegate type when finished Querying Achievement Ids. */
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnQueryIds, bool);

	/** Event for when Querying Achievement Ids has completed.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnQueryIds OnQueryIds_Event;
	/** Script Event for when Querying Achievement Ids has completed.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerAchievement_OnQueryIds OnQueryIds_ScriptEvent;

	/** Event for when Querying Achievement Ids has completed.
	Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnQueryIds OnQueryIds_AsyncEvent;
	/** Script Event for when Querying Achievement Ids has completed.
	Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerAchievement_OnQueryIds OnQueryIds_AsyncScriptEvent;

#pragma endregion Ids

	// Descriptions
#pragma region
public:

	/**
	*
	*/
	void QueryDescriptions();

protected:

	void QueryDescriptions_Internal();

public:

	/** Delegate type when finished Querying Achievement Descriptions. */
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnQueryDescriptions, bool);

	/** Event for when Querying Achievement Descriptions has completed.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnQueryDescriptions OnQueryDescriptions_Event;
	/** Script Event for when Querying Achievement Descriptions has completed.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerAchievement_OnQueryDescriptions OnQueryDescriptions_ScriptEvent;

	/** Event for when Querying Achievement Descriptions has completed.
	Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnQueryDescriptions OnQueryDescriptions_AsyncEvent;
	/** Script Event for when Querying Achievement Descriptions has completed.
	Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerAchievement_OnQueryDescriptions OnQueryDescriptions_AsyncScriptEvent;

#pragma endregion Descriptions

protected:

	/**
	*
	*
	* return
	*/
	bool CheckAndQueueQuery();

#pragma endregion Query

// Descriptions
#pragma region
public:

	/**
	*
	*/
	virtual void UpdateDescription(ICsAchievement* Achievement, const FOnlineAchievementDesc& Description);

	/**
	*
	*/
	void UpdateDescriptions();

protected:

	void UpdateDescriptions_Internal(FCsAchievementActionInfo* ActionInfo);

#pragma endregion Descriptions

// Write
#pragma region
protected:

	/** The state (Completed and or Success) when an Achievement has been written. 
		This is only relevant when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsAchievementWriteState WriteState;

	/** Current Achievement that has been written. 
		This is only relevant when an OnlineSubsystem with OnlineAchievements is valid. */
	FECsAchievement CurrentAchievementWritten;

	// TODO: Change to a Queue

	/** Achievements queued to write. 
		When an OnlineSubsystem with OnlineAchievements is valid, achievements are written one at a time. */
	TArray<FCsAchievementToWrite> AchievementsToWrite;

	/**
	* Set the progress as a percent [0.0, 1.0] inclusive of an achievement. 
	*
	* @param Achievement	Achievement to update.
	* @param Percent		Value between [0, 1]. This will get adjusted by GetProgressValue.
	*/
	void Write(const FECsAchievement& Achievement, const float& Percent);
	void Write_Internal(FCsAchievementActionInfo* ActionInfo);

#pragma endregion Write

// Complete
#pragma region
public:

	/**
	* Start the process of marking an achievement as complete.
	* @param Achievement		Achievement to complete.
	*/
	void Complete(const FECsAchievement& Achievement);

protected:

	void Complete_Internal(FCsAchievementActionInfo* ActionInfo);

public:

	/** Delegate type when completing an Achievement */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnComplete, bool /*WasSuccessful*/, const ICsAchievement* /*Achievement*/);

	/** Event for when an Achievement has completed. 
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnComplete OnComplete_Event;
	/** Script Event for when an Achievement has completed. 
	    Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerAchievement_OnComplete OnComplete_ScriptEvent;

	/** Event for when an Achievement has completed. 
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnComplete OnComplete_AsyncEvent;
	/** Script Event for when an Achievement has completed. 
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerAchievement_OnComplete OnComplete_AsyncScriptEvent;

public:

	/**
	* Check if an Achievement has been completed.
	* @param Achievement	Achievement to check.
	* return				Whether the Achievement is Completed.
	*/
	bool IsCompleted(const FECsAchievement& Achievement);

protected:

	int32 NumCompleted;

public:

	/**
	* Get the number of completed achievements.
	* return	Number of Achievements completed.
	*/
	const int32& GetNumCompleted();


	/**
	*
	*/
	void CompleteAll();

protected:

	void CompleteAll_Internal(FCsAchievementActionInfo* ActionInfo);

public:

	/** Delegate type when completing all achievement */
	DECLARE_MULTICAST_DELEGATE(FOnCompleteAll);

	/** Event for when all achievements have been completed.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnCompleteAll OnCompleteAll_Event;
	/** Script Event for when all achievements have been completed.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerAchievement_OnCompleteAll OnCompleteAll_ScriptEvent;

#pragma endregion Complete

// Reset
#pragma region
public:

	/**
	* Reset the progress an Achievement to Percent. This sets the Achievement State to None
	*  or not completed.
	*
	* @param Achievement	Achievement to reset.
	* @param Percent		Percent to reset the Achievement to. Defaults to 0.
	*/
	virtual void Reset(const FECsAchievement& Achievement, const float& Percent = 0);

protected:

	void Reset_Internal(FCsAchievementActionInfo* ActionInfo);

public:

	/** Delegate type when the progress of an Achievement has been reset to a value (default is 0). */
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnReset, bool /*WasSuccessful*/, const ICsAchievement* /*Achievement*/, const float& /*Progress*/);

	/** Event for when the progress of an Achievement has reset to a value (default is 0).
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnReset OnReset_Event;
	/** Script Event for when the progress of an Achievement has reset to a value (default is 0).
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerAchievement_OnReset OnReset_ScriptEvent;

	/** Event for when the progress of an Achievement has reset to a value (default is 0).
	Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnReset OnReset_AsyncEvent;
	/** Script Event for when the progress of an Achievement has reset to a value (default is 0).
	Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerAchievement_OnReset OnReset_AsyncScriptEvent;

	/**
	*
	*/
	void ResetAll();

protected:

	virtual void ResetAll_Internal(FCsAchievementActionInfo* ActionInfo);

public:

	/** Delegate type when resetting all achievement */
	DECLARE_MULTICAST_DELEGATE(FOnResetAll);

	/** Event for when all achievements have been reset.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnResetAll OnResetAll_Event;
	/** Script Event for when all achievements have been reset.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerAchievement_OnResetAll OnResetAll_ScriptEvent;

#pragma endregion Reset

// Progress
#pragma region
protected:

	/** Whether the progress of achievements can only be set in one direction.
	    Default is true. For example, if the progress is 50 / 100 and you set the 
		progress to 25. First Reset will be called and then the progress will be 
		set to 25. */
	bool bOnlyForwardProgress;

public:

	/**
	* Set the progress of an Achievement.
	* @param Achievement	Achievement to update.
	* @param Percent		Value between [0, 1]. This will get adjusted by GetProgressValue.
 	*/
	void SetProgress(const FECsAchievement& Achievement, const float& Percent);

	/** Delegate type when the progress of an Achievement has been updated. */
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnProgress, bool /*WasSuccessful*/, const ICsAchievement* /*Achievement*/, const float& /*Progress*/);

	/** Event for when the progress of an Achievement has updated. 
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnProgress OnProgress_Event;
	/** Script Event for when the progress of an Achievement has updated. 
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerAchievement_OnProgress OnProgress_ScriptEvent;

	/** Event for when the progress of an Achievement has updated. 
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnProgress OnProgress_AsyncEvent;
	/** Script Event for when the progress of an Achievement has updated. 
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerAchievement_OnProgress OnProgress_AsyncScriptEvent;

public:

	/**
	* 
	* @param Achievement	Achievement to get progress for.
	* return Progress		Value range dictated by ProgressType.
	*/
	float GetProgress(const FECsAchievement& Achievement);

protected:

	float TotalProgress;

public:

	const float& GetTotalProgress();

#pragma endregion Progress

public:

	bool bOnline;

// IOnlineAchievements
#pragma region
public:

	IOnlineAchievementsPtr GetAchievementsInterface();

protected:

	ECsAchievementQueryOrder AchievementQueryOrder;

	void OnQueryAchievementsComplete(const FUniqueNetId& PlayerId, const bool Success);

	void OnQueryAchievementDescriptionsComplete(const FUniqueNetId& PlayerId, const bool Success);

	TArray<FOnlineAchievement> Local_OutAchievements;

	/** Achievements write object */
	FOnlineAchievementsWritePtr WriteObject;

	void OnAchievementsWritten(const FUniqueNetId& PlayerId, bool Success);

#pragma endregion IOnlineAchievements

// Internals
#pragma region
public:

	bool IsValid(const FECsAchievement& Achievement);

protected:

	virtual void SetId(ICsAchievement* Achievement, const FString& Id);

	virtual void SetType(ICsAchievement* Achievement, const FECsAchievement& AchievementType);

#pragma endregion Internals
};