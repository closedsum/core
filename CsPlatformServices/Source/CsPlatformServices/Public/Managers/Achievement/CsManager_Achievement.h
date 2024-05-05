// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Achievement/CsManager_Achievement_Delegates.h"
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Log
#include "Utility/CsPlatformServicesLog.h"
// Online
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

namespace NCsAchievement
{
	namespace NAction
	{
		namespace NInfo
		{
		#define InfoType NCsAchievement::NAction::NInfo::FInfo

			/**
			* Container for holding a reference to the object InfoType (NCsAchievement::NAction::NInfo::FInfo).
			* This serves as an easy way for a Manager Resource to keep track of the resource.
			*/
			struct CSPLATFORMSERVICES_API FResource : public TCsResourceContainer<InfoType>
			{
				~FResource(){}
			};

			/**
			* A manager handling allocating and deallocating the object InfoType (NCsAchievement::NAction::NInfo::FInfo) and
			* are wrapped in the container: NCsAchievement::NAction::NInfo::FResource.
			*/
			struct CSPLATFORMSERVICES_API FManager : public NCsResource::NManager::NValue::TFixed<InfoType, FResource, 256>
			{
				~FManager(){}
			};

		#undef InfoType
		}
	}
}

#pragma endregion Structs

UCLASS(transient)
class CSPLATFORMSERVICES_API UCsManager_Achievement : public UObject
{
	GENERATED_UCLASS_BODY()

#define ActionType NCsAchievement::EAction
#define ActionInfoManagerType NCsAchievement::NAction::NInfo::FManager
#define ActionInfoType NCsAchievement::NAction::NInfo::FInfo
#define ActionAllocationType NCsAchievement::NAction::EAllocation
#define ValueType NCsAchievement::FValue

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Achievement* Get(const UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_Achievement* Get(const UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	template<typename T>
	FORCEINLINE static T* Get(const UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid();
	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Achievement> ManagerAchievementClass, UObject* InOuter = nullptr);
	static void Init(UObject* InRoot, UObject* InOuter = nullptr);
	static void Shutdown(const UObject* InRoot = nullptr);
	static bool HasShutdown();

#if WITH_EDITOR
protected:

	static ICsGetManagerAchievement* Get_GetManagerAchievement(const UObject* InRoot);
	static ICsGetManagerAchievement* GetSafe_GetManagerAchievement(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

	static UCsManager_Achievement* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

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
	TArray<FCsAchievementEntry> AchievementEntries;
	TMap<FString, FCsAchievementEntry> AchievementEntryMap;

public:

	ICsAchievement* GetAchievement(const FECsAchievement& Achievement);

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

	/**
	* Get the Local Player's Nickname. This is retrieved from the Online Identity.
	*
	* return Local Player's Nickname
	*/
	FString GetLocalPlayerNickname();

#pragma endregion Player

	virtual void Update(const float& DeltaSeconds);

// Action
#pragma region
protected:

	/** Manager to handle a resource pool of InfoType (NCsAchievement::NAction::FInfo). */
	ActionInfoManagerType Manager_Resource;

	/**
	* Queue an action (Write, Complete, or Reset) to perform on an achievement.
	* The action gets enqueued into the list of actions being processed.
	*
	* @param Action			Type of action to queue (Write, Complete, or Reset).
	* @param Achievement	The Achievement to perform the action on.
	* @param Percent		The progress as a percent [0.0, 1.0] inclusive.
	*/
	void QueueAction(const ActionType& Action, const FECsAchievement& Achievement, const float& Percent);

	/**
	* Queue an action (Write, Complete, or Reset) to perform on an achievement.
	* The action gets enqueued into the list of actions being processed.
	*
	* @param Action			Type of action to queue (Write, Complete, or Reset).
	* @param Achievement	The Achievement to perform the action on.
	* @param Count			Count.
	*/
	void QueueAction(const ActionType& Action, const FECsAchievement& Achievement, const uint64& Count);

	/**
	* Queue an action (Write, Complete, or Reset) to perform on an achievement.
	* The action gets enqueued into the list of actions being processed.
	*
	* @param Action			Type of action to queue (Write, Complete, or Reset).
	* @param Achievement	The Achievement to perform the action on.
	* @param Bitfield		String of 0s and 1s.
	*/
	void QueueAction(const ActionType& Action, const FECsAchievement& Achievement, const FString& Bitfield);

	/**
	* Queue an action (Create or Modify) to perform on an achievement.
	* The action gets enqueued into the list of actions being processed.
	*
	* @param Action			Type of action to queue (Create or Modify).
	* @param Entry			The data for the achievement.
	*/
	void QueueAction(const ActionType& Action, const FCsAchievementEntry& Entry);

	/**
	* Queue an action (Remove) to perform on an achievement.
	* The action gets enqueued into the list of actions being processed.
	*
	* @param Action			Type of action to queue (Remove).
	* @param Achievement	The Achievement to perform the action on.
	* @param Entry			The data for the achievement.
	*/
	void QueueAction(const ActionType& Action, const FECsAchievement& Achievement, const FCsAchievementEntry& Entry);

	/**
	* Queue an action (Remove) to perform on an achievement.
	* The action gets enqueued into the list of actions being processed.
	*
	* @param Action			Type of action to queue (Remove).
	* @param Achievement	The Achievement to perform the action on.
	*/
	void QueueAction(const ActionType& Action, const FECsAchievement& Achievement);

	/**
	* Queue an action (QueryIds, QueryDescriptions, Remove All, Complete All, or Reset All) to preform. 
	* The action gets enqueued into the list of actions being processed.
	*
	* @param Action		Type of action to queue (QueryIds, QueryDescriptions, Remove All, Complete All, or Reset All).
	*/
	void QueueAction(const ActionType& Action);

	ActionInfoType* QueueAction_Internal(const ActionAllocationType& Allocation, const ActionType& Action);
	ActionInfoType* QueueAction_Internal(const ActionAllocationType& Allocation, const ActionType& Action, const FECsAchievement& Achievement);
	ActionInfoType* QueueAction_Internal(const ActionAllocationType& Allocation, const ActionType& Action, const FCsAchievementEntry& Entry);
	ActionInfoType* QueueAction_Internal(const ActionAllocationType& Allocation, const ActionType& Action, const FECsAchievement& Achievement, const FCsAchievementEntry& Entry);

	/**
	* Queue an action (QueryIds, QueryDescriptions, Complete All, or Reset All) as the first action (Head) to be processed.
	*
	* @param Action			Type of action to queue (Write, Complete, or Reset).
	* @param Achievement	The Achievement to perform the action on.
	* @param Percent		if Action == Write, the progress as a percent [0.0, 1.0] inclusive.
	*/
	void QueueActionAsHead(const ActionType& Action, const FECsAchievement& Achievement, const float& Percent = 0.0f);

	/**
	* Queue an action (QueryIds, QueryDescriptions, Complete All, or Reset All) as the first action (Head) to be processed.
	*
	* @param Action		Type of action to queue (QueryIds, QueryDescriptions, Complete All, or Reset All).
	*/
	void QueueActionAsHead(const ActionType& Action);

	/**
	* Queue an action (QueryIds, QueryDescriptions, Complete All, or Reset All) 
	* after the first action (Head) to be processed.
	*
	* @param Action			Type of action to queue (Write, Complete, or Reset).
	* @param Achievement	The Achievement to perform the action on.
	* @param Percent		if Action == Write, the progress as a percent [0.0, 1.0] inclusive.
	*/
	void QueueActionAfterHead(const ActionType& Action, const FECsAchievement& Achievement, const float& Percent = 0.0f);

	/**
	* Queue an action (QueryIds, QueryDescriptions, Complete All, or Reset All)
	* after the first action (Head) to be processed.
	*
	* @param Action		Type of action to queue (Write, Complete, or Reset).
	*/
	void QueueActionAfterHead(const ActionType& Action);

#pragma endregion Action

// Query
#pragma region
protected:

#define QueryStateType NCsAchievement::NQuery::FState

	QueryStateType QueryState;

#undef QueryStateType

	// Ids
#pragma region
public:

	/**
	*
	*/
	void QueryIds();

protected:

	void QueryIds_Internal();

	virtual void QueryAchievementIds(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate);

public:

#define OnQueryIdsEventType NCsAchievement::NManager::FOnQueryIds

	/** Event for when Querying Achievement Ids has completed.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	OnQueryIdsEventType OnQueryIds_Event;
	
	FORCEINLINE OnQueryIdsEventType& GeOnQueryIds_Event() { return OnQueryIds_Event; }

	/** Script Event for when Querying Achievement Ids has completed.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnQueryIds OnQueryIds_ScriptEvent;

	FORCEINLINE FCsManagerAchievement_OnQueryIds& GetOnQueryIds_ScriptEvent() { return OnQueryIds_ScriptEvent; }

	/** Event for when Querying Achievement Ids has completed.
	Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	OnQueryIdsEventType OnQueryIds_AsyncEvent;
	
	FORCEINLINE OnQueryIdsEventType& GeOnQueryIds_AsyncEvent() { return OnQueryIds_AsyncEvent; }

	/** Script Event for when Querying Achievement Ids has completed.
	Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnQueryIds OnQueryIds_AsyncScriptEvent;

	FORCEINLINE FCsManagerAchievement_OnQueryIds& GetOnQueryIds_AsyncScriptEvent() { return OnQueryIds_AsyncScriptEvent; }

#undef OnQueryIdsEventType

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

	virtual void QueryAchievementDescriptions(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate);

public:

#define OnQueryDescriptionsEventType NCsAchievement::NManager::FOnQueryDescriptions

	/** Event for when Querying Achievement Descriptions has completed.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	OnQueryDescriptionsEventType OnQueryDescriptions_Event;

	/** Script Event for when Querying Achievement Descriptions has completed.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnQueryDescriptions OnQueryDescriptions_ScriptEvent;

	/** Event for when Querying Achievement Descriptions has completed.
	Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	OnQueryDescriptionsEventType OnQueryDescriptions_AsyncEvent;

	/** Script Event for when Querying Achievement Descriptions has completed.
	Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnQueryDescriptions OnQueryDescriptions_AsyncScriptEvent;

#undef OnQueryDescriptionsEventType

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
	virtual void UpdateInfoAndDescription(ICsAchievement* Achievement, const FOnlineAchievement* Info, const FOnlineAchievementDesc* Description);

	/**
	*
	*/
	void UpdateDescriptions();

protected:

	FOnlineAchievementDesc* Local_OnlineAchievementDesc;

	virtual void Construct_Local_OnlineAchievementDesc();
	virtual void Reset_Local_OnlineAchievementDesc();

	void UpdateDescriptions_Internal(ActionInfoType* ActionInfo);

	virtual EOnlineCachedResult::Type GetCachedAchievementDescription(const FString& AchievementId, FOnlineAchievementDesc* OutAchievementDesc);

	void PrintDescription(ICsAchievement* Achievement);

#pragma endregion Descriptions

// Settings
#pragma region
public:

	void UpdateBySettings();

	void UpdateByDataTable(UDataTable* DataTable);

protected:

	void UpdateOrAddEntry(ICsAchievement* Achievement);
	void UpdateFromEntry(ICsAchievement* Achievement);

public:

	const FCsAchievementEntry& GetEntry(const FECsAchievement& Achievement);

	bool HasEntry(const FString& Name);

#pragma endregion Settings

// Create
#pragma region
public:

	void Create(const FCsAchievementEntry& Entry);

protected:

	virtual void Create_Internal(ActionInfoType* ActionInfo);

public:

#define OnCreateEventType NCsAchievement::NManager::FOnCreate

	/** Event for when .
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	OnCreateEventType OnCreate_Event;

	FORCEINLINE OnCreateEventType& GetOnCreate_Event() { return OnCreate_Event; }

	/** Script Event for when .
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnCreate OnCreate_ScriptEvent;

	FORCEINLINE FCsManagerAchievement_OnCreate& GetOnCreate_ScriptEvent() { return OnCreate_ScriptEvent; }

#undef OnCreateEventType

#pragma endregion Create

// Modify
#pragma region
public:

	void ModifyAchievement(const FCsAchievementEntry& Entry);

protected:

	virtual void ModifyAchievement_Internal(ActionInfoType* ActionInfo);

public:

#define OnModifyEventType NCsAchievement::NManager::FOnModify

	/** Event for when .
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	OnModifyEventType OnModify_Event;

	FORCEINLINE OnModifyEventType& GetOnModify_Event() { return OnModify_Event; }

	/** Script Event for when .
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnModify OnModify_ScriptEvent;

	FORCEINLINE FCsManagerAchievement_OnModify& GetOnModify_ScriptEvent() { return OnModify_ScriptEvent; }

#undef OnModifyEventType

#pragma endregion Modify

// Remove
#pragma region
public:

	/** Whether the Remove action blocks other actions (outside of Remove or RemoveAll or Create). */
	bool bRemoveBlocksQueuedActions;
	/** Whether the RemoveAll action blocks other actions (outside of Remove or RemoveAll or Create). */
	bool bRemoveAllBlocksQueuedActions;

	void Remove(const FECsAchievement& Achievement);

protected:

	virtual void Remove_Internal(ActionInfoType* ActionInfo);

public:

#define OnRemoveEventType NCsAchievement::NManager::FOnRemove

	/** Event for when .
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	OnRemoveEventType OnRemove_Event;

	FORCEINLINE OnRemoveEventType& GetOnRemove_Event() { return OnRemove_Event; }

	/** Script Event for when .
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnRemove OnRemove_ScriptEvent;

	FORCEINLINE FCsManagerAchievement_OnRemove& GetOnRemove_ScriptEvent() { return OnRemove_ScriptEvent; }

#undef OnRemoveEventType

	void RemoveAll();

protected:

	void RemoveAll_Internal(ActionInfoType* ActionInfo);

public:

#define OnRemoveAllEventType NCsAchievement::NManager::FOnRemoveAll

	/** Event for when .
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	OnRemoveAllEventType OnRemoveAll_Event;

	FORCEINLINE OnRemoveAllEventType& GetOnRemoveAll_Event() { return OnRemoveAll_Event; }

	/** Script Event for when .
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnRemoveAll OnRemoveAll_ScriptEvent;

	FORCEINLINE FCsManagerAchievement_OnRemoveAll& GetOnRemoveAll_ScriptEvent() { return OnRemoveAll_ScriptEvent; }

#undef OnRemoveAllEventType

protected:

	bool IsCurrentActionRemoveOrRemoveAll();

#pragma endregion Remove

// Write
#pragma region
protected:

	/** Current Achievement that has been written.
		This is only relevant when an OnlineSubsystem with OnlineAchievements is valid. */
	FECsAchievement CurrentAchievementWritten;

	/**
	* Set the progress as a percent [0.0, 1.0] inclusive of an achievement.
	*
	* @param Achievement	Achievement to update.
	* @param Percent		Value between [0, 1]. This will get adjusted by GetProgressValue.
	*/
	void Write(const FECsAchievement& Achievement, const float& Percent);

	/**
	* Set the count [0, Max Count] inclusive for an achievement.
	*
	* @param Achievement	Achievement to update.
	* @param Count			Value between [0, Max Count]. Max Count is defined by the achievement.
	*/
	void Write(const FECsAchievement& Achievement, const uint64& Count);

	/**
	*
	* @param Achievement
	* @param Bitfield
	*
	*/
	void Write(const FECsAchievement& Achievement, const FString& Bitfield);

	/**
	* Set the value (Float, Integer, String, ... etc) for an achievement.
	*
	* @param Achievement	Achievement to update.
	* @param Value			Value.
	*/
	void Write(const FECsAchievement& Achievement, const ValueType& Value);

	void Write_Internal(ActionInfoType* ActionInfo);

#pragma endregion Write

// Complete
#pragma region
public:

	/**
	* Start the process of marking an achievement as complete.
	*
	* @param Achievement		Achievement to complete.
	*/
	void Complete(const FECsAchievement& Achievement);

	/**
	* Safely start the process of marking an achievement as complete.
	* Checks if the Achievement is Valid and has already been completed.
	*
	* @param Achievement		Achievement to complete.
	*/
	void SafeComplete(const FECsAchievement& Achievement);

protected:

	void Complete_Internal(ActionInfoType* ActionInfo);

public:

#define OnCompleteEventType NCsAchievement::NManager::FOnComplete

	/** Event for when an Achievement has completed. 
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	OnCompleteEventType OnComplete_Event;

	FORCEINLINE OnCompleteEventType& GetOnComplete_Event() { return OnComplete_Event; }

	/** Script Event for when an Achievement has completed. 
	    Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnComplete OnComplete_ScriptEvent;

	FORCEINLINE FCsManagerAchievement_OnComplete& GetOnComplete_ScriptEvent() { return OnComplete_ScriptEvent; }

	/** Event for when an Achievement has completed. 
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	OnCompleteEventType OnComplete_AsyncEvent;

	FORCEINLINE OnCompleteEventType& GetOnComplete_AsyncEvent() { return OnComplete_AsyncEvent; }

	/** Script Event for when an Achievement has completed. 
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnComplete OnComplete_AsyncScriptEvent;

	FORCEINLINE FCsManagerAchievement_OnComplete& GetOnComplete_AsyncScriptEvent() { return OnComplete_AsyncScriptEvent; }

#undef OnCompleteEventType

public:

	/**
	* Check if an Achievement has been completed.
	*
	* @param Achievement	Achievement to check.
	* return				Whether the Achievement is Completed.
	*/
	bool IsCompleted(const FECsAchievement& Achievement);

	/**
	* Safely check if an Achievement has been completed.
	* Checks if the Achievement is Valid
	*
	* @param Achievement	Achievement to check.
	* return				Whether the Achievement is Completed.
	*/
	bool IsSafeCompleted(const FECsAchievement& Achievement);

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

	void CompleteAll_Internal(ActionInfoType* ActionInfo);

public:

#define OnCompleteAllEventType NCsAchievement::NManager::FOnCompleteAll

	/** Event for when all achievements have been completed.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	OnCompleteAllEventType OnCompleteAll_Event;

	FORCEINLINE OnCompleteAllEventType& GetOnCompleteAll_Event() { return OnCompleteAll_Event; }

	/** Script Event for when all achievements have been completed.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnCompleteAll OnCompleteAll_ScriptEvent;

	FORCEINLINE FCsManagerAchievement_OnCompleteAll& GetOnCompleteAll_ScriptEvent() { return OnCompleteAll_ScriptEvent; }

#undef OnCompleteAllEventType

#pragma endregion Complete

// Reset
#pragma region
protected:

	/** */
	bool bResetAsResetAll;

public:

	/**
	* Reset the progress an Achievement to Percent. This sets the Achievement State to None
	*  or not completed.
	*
	* @param Achievement	Achievement to reset.
	* @param Percent		Percent to reset the Achievement to. Defaults to 0.
	*/
	virtual void Reset(const FECsAchievement& Achievement, const float& Percent);

	/**
	*
	*
	* @param Achievement
	* @param Count
	*/
	virtual void Reset(const FECsAchievement& Achievement, const uint64& Count);

	/**
	*
	*
	* @param Achievement
	* @param Count
	*/
	virtual void Reset(const FECsAchievement& Achievement, const FString& Bitfield);

	/**
	* Reset the value an Achievement. This sets the Achievement State to None
	*  or not completed.
	*
	* @param Achievement	Achievement to reset.
	* @param Value			Value.
	*/
	virtual void Reset(const FECsAchievement& Achievement, const ValueType& Value);

	/**
	* Safely reset the value an Achievement. This sets the Achievement State to None
	*  or not completed.
	* Checks if the Achievement is Valid
	*
	* @param Achievement	Achievement to reset.
	* @param Value			Value.
	*/
	void SafeReset(const FECsAchievement& Achievement, const ValueType& Value);

protected:

	void Reset_Internal(ActionInfoType* ActionInfo);

public:

#define OnResetEventType NCsAchievement::NManager::FOnReset

	/** Event for when the progress of an Achievement has reset to a value (default is 0).
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	OnResetEventType OnReset_Event;

	FORCEINLINE OnResetEventType& GetOnReset_Event() { return OnReset_Event; }

	/** Script Event for when the progress of an Achievement has reset to a value (default is 0).
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnReset OnReset_ScriptEvent;

	FORCEINLINE FCsManagerAchievement_OnReset& GetOnReset_ScriptEvent() { return OnReset_ScriptEvent; }

	/** Event for when the progress of an Achievement has reset to a value (default is 0).
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	OnResetEventType OnReset_AsyncEvent;

	FORCEINLINE OnResetEventType& GetOnReset_AsyncEvent() { return OnReset_AsyncEvent; }

	/** Script Event for when the progress of an Achievement has reset to a value (default is 0).
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnReset OnReset_AsyncScriptEvent;

	FORCEINLINE FCsManagerAchievement_OnReset& GetOnReset_AsyncScriptEvent() { return OnReset_AsyncScriptEvent; }

#undef OnResetEventType

	/**
	*
	*/
	void ResetAll();

protected:

	virtual void ResetAll_Internal(ActionInfoType* ActionInfo);

public:

#define OnResetAllEventType NCsAchievement::NManager::FOnResetAll

	/** Event for when all achievements have been reset.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	OnResetAllEventType OnResetAll_Event;

	FORCEINLINE OnResetAllEventType& GetResetAll_Event() { return OnResetAll_Event; }

	/** Script Event for when all achievements have been reset.
	Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnResetAll OnResetAll_ScriptEvent;

	FORCEINLINE FCsManagerAchievement_OnResetAll& GetResetAll_ScriptEvent() { return OnResetAll_ScriptEvent; }

#undef OnResetAllEventType

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
	*
	* @param Achievement	Achievement to update.
	* @param Percent		Value between [0, 1]. This will get adjusted by GetProgressValue.
 	*/
	void SetProgress(const FECsAchievement& Achievement, const float& Percent);

	/**
	* Safely set the progress of an Achievement.
	* Checks if the Achievement is Valid and if the progress is already at Percent.
	*
	* @param Achievement	Achievement to update.
	* @param Percent		Value between [0, 1]. This will get adjusted by GetProgressValue.
	*/
	void SetSafeProgress(const FECsAchievement& Achievement, const float& Percent);

#define OnProgressEventType NCsAchievement::NManager::FOnProgress

	/** Event for when the progress of an Achievement has updated. 
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	OnProgressEventType OnProgress_Event;

	FORCEINLINE OnProgressEventType& GetOnProgress_Event() { return OnProgress_Event; }

	/** Script Event for when the progress of an Achievement has updated. 
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnProgress OnProgress_ScriptEvent;

	FORCEINLINE FCsManagerAchievement_OnProgress& GetOnProgress_ScriptEvent() { return OnProgress_ScriptEvent; }

	/** Event for when the progress of an Achievement has updated. 
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	OnProgressEventType OnProgress_AsyncEvent;

	FORCEINLINE OnProgressEventType& GetOnProgress_AsyncEvent() { return OnProgress_AsyncEvent; }

	/** Script Event for when the progress of an Achievement has updated. 
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	UPROPERTY(BlueprintAssignable, Category = "CsPlatformServices|Managers|Achievement")
	FCsManagerAchievement_OnProgress OnProgress_AsyncScriptEvent;

	FORCEINLINE FCsManagerAchievement_OnProgress& GetOnProgress_AsyncScriptEvent() { return OnProgress_AsyncScriptEvent; }

#undef OnProgressEventType

public:

	/**
	* Get the current Progress of an Achievement
	*
	* @param Achievement	Achievement to get progress for.
	* return Progress		Value range dictated by ProgressType.
	* 						 Normalized: [0.0, 1.0] Inclusive.
	*						 Standard: [0.0, 100.0] Inclusive.
	*						 Binary: [0.0, 100.0] Inclusive. Internally only values supported are 0.0 = Lock and 100.0 = Unlock.
	*						 Count: [0.0, 100.0] Inclusive. Internally [0, N] Inclusive. X out of N.
	*						 Bitfield: [0.0, 100.0] Inclusive. Internally check against bits set for a mask (i.e. 010010, ... etc).
	*/
	float GetProgress(const FECsAchievement& Achievement);

	/**
	* Safely get the current Progress of an Achievement
	* Checks if the Achievement is Valid
	*
	* @param Achievement	Achievement to get progress for.
	* return Progress		Value range dictated by ProgressType.
	* 						 Normalized: [0.0, 1.0] Inclusive.
	*						 Standard: [0.0, 100.0] Inclusive.
	*						 Binary: [0.0, 100.0] Inclusive. Internally only values supported are 0.0 = Lock and 100.0 = Unlock.
	*						 Count: [0.0, 100.0] Inclusive. Internally [0, N] Inclusive. X out of N.
	*						 Bitfield: [0.0, 100.0] Inclusive. Internally check against bits set for a mask (i.e. 010010, ... etc).
	*/
	float GetSafeProgress(const FECsAchievement& Achievement);

	/**
	* Get the current progress of an Achievement as a percent.
	*
	* @param Achievement	Achievement to get progress for.
	* return Percent		Value between [0, 1] inclusive.
	*/
	float GetProgressAsPercent(const FECsAchievement& Achievement);

	/**
	* Safely get the current progress of an Achievement as a percent.
	* Checks if the Achievement is Valid
	*
	* @param Achievement	Achievement to get progress for.
	* return Percent		Value between [0, 1] inclusive.
	*/
	float GetSafeProgressAsPercent(const FECsAchievement& Achievement);

protected:

	void CalculateTotalProgress();

protected:

	float TotalProgress;

public:

	const float& GetTotalProgress();

#pragma endregion Progress

// Count
#pragma region
protected:

	bool bCountAsAdd;

public:

	/**
	* Increment the current count of the Achievement by Count. 
	*
	* @param Achievement
	* @param Count
	*/
	void Increment(const FECsAchievement& Achievement, const uint64& Count = 1);

	/**
	* Safely increment the current count of the Achievement by Count.
	* Checks if the Achievement is Valid and has already been completed.
	*
	* @param Achievement
	* @param Count
	*/
	void SafeIncrement(const FECsAchievement& Achievement, const uint64& Count = 1);

	/**
	* Set the current count of the Achievement by Count.
	*
	* @param Achievement
	* @param Count
	*/
	void SetCount(const FECsAchievement& Achievement, const uint64& Count);

	/**
	* Safely set the current count of the Achievement by Count.
	* Checks if the Achievement is Valid and has already been completed.
	*
	* @param Achievement
	* @param Count
	*/
	void SetSafeCount(const FECsAchievement& Achievement, const uint64& Count);

protected:

	/**
	* Check whether the Achievement uses the ProgressType: Count.
	*
	* @param Achievement	Achievement to check.
	* return				Whether the achievement DOES or does NOT use ProgressType: Count
	*/
	bool SupportsCount(const FECsAchievement& Achievement);

	/**
	* Check whether the Achievement uses the ProgressType: Count.
	*
	* @param Context		Calling context / function.
	* @param Achievement	Achievement to check.
	* return				Whether the achievement DOES or does NOT use ProgressType: Count
	*/
	bool SupportsSafeCount(const FString& Context, const FECsAchievement& Achievement);

#pragma endregion Count

// Bitfield
#pragma region
protected:

	bool bBitfieldIndexStartsAtZero;
	bool bBitfieldAsOr;

public:

	/**
	* Set the bit at Index of the Bitfield for Achievement.
	*
	* @param Achievement	The Achievement to set bit for.
	*						The Achievement must have a progress type: NCsAchievement::EProgress::Bitfield.
	* @param Index			Bit position in the Bitfield for the Achievement to set.
	*/
	void SetBit(const FECsAchievement& Achievement, const uint32& Index);

	/**
	* Safely set the bit at Index of the Bitfield for Achievement.
	* Checks if the Achievement is Valid and has already been completed.
	*
	* @param Achievement
	* @param Index
	*/
	void SetSafeBit(const FECsAchievement& Achievement, const uint32& Index);

protected:

	/**
	* Check whether the Achievement uses the ProgressType: Bitfield.
	*
	* @param Achievement	Achievement to check.
	* return				Whether the achievement DOES or does NOT use ProgressType: Bitfield
	*/
	bool SupportsBitfield(const FECsAchievement& Achievement);

	/**
	* Check whether the Achievement uses the ProgressType: Bitfield.
	*
	* @param Context		Calling context / function.
	* @param Achievement	Achievement to check.
	* return				Whether the achievement DOES or does NOT use ProgressType: Bitfield
	*/
	bool SupportsSafeBitfield(const FString& Context, const FECsAchievement& Achievement);

#pragma endregion Bitfield

public:

	bool bOnline;

	// IOnlineAchievements
#pragma region
public:

	IOnlineAchievementsPtr GetAchievementsInterface();

protected:

#define QueryOrderType NCsAchievement::NQuery::EOrder
	QueryOrderType QueryOrder;
#undef QueryOrderType

	void OnQueryAchievementsComplete(const FUniqueNetId& PlayerId, const bool Success);

	void OnQueryAchievementDescriptionsComplete(const FUniqueNetId& PlayerId, const bool Success);

	TArray<FOnlineAchievement> Local_OutAchievements;

	/** Achievements write object */
	FOnlineAchievementsWritePtr WriteObject;

	void OnAchievementsWritten(const FUniqueNetId& PlayerId, bool Success);

	void GetWriteAchievementValue(FVariantData* VariantData, float& OutData) const;
	void GetWriteAchievementCountValue(FVariantData* VariantData, uint64& OutData) const;
	void GetWriteAchievementBitfieldValue(FVariantData* VariantData, FString& OutData, const uint32& BitfieldLength) const;

#pragma endregion IOnlineAchievements

	// Internals
#pragma region
protected:

	bool IsEnabled(const FString& Context);

public:

	bool IsValidChecked(const FString& Context, const FECsAchievement& Achievement);

	bool IsValid(const FString& Context, const FECsAchievement& Achievement, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);

protected:

	virtual void SetId(ICsAchievement* Achievement, const FString& Id);

	virtual void SetType(ICsAchievement* Achievement, const FECsAchievement& AchievementType);

#define ProgressType NCsAchievement::EProgress
	virtual void SetProgressType(ICsAchievement* Achievement, const ProgressType& Type);
#undef ProgressType

	virtual void SetProgress(ICsAchievement* Achievement, const float& Percent);

	virtual void SetCount(ICsAchievement* Achievement, const uint64& Count);

	virtual void SetMaxCount(ICsAchievement* Achievement, const uint64& Count);

	virtual void IncrementCount(ICsAchievement* Achievement);

	virtual void IncrementCountBy(ICsAchievement* Achievement, const uint64& Count);

	virtual uint64 CalculateCount(ICsAchievement* Achievement, const uint64& Count);

	virtual void SetBitfield(ICsAchievement* Achievement, const FString& Bitfield);

	virtual void OrBitfield(ICsAchievement* Achievement, const FString& Bitfield);

	virtual void SetUnlockBitfieldLength(ICsAchievement* Achievement, const uint32& Length);

	virtual bool IsValidBitfield(ICsAchievement* Achievement, const FString& Bitfield);

	virtual void SetTitle(ICsAchievement* Achievement, const FString& Title);

	virtual void SetDescription(ICsAchievement* Achievement, const FString& Description);

	virtual void SetUnlockedDescription(ICsAchievement* Achievement, const FString& UnlockedDescription);

#pragma endregion Internals

#undef ActionType
#undef ActionInfoManagerType
#undef ActionInfoType
#undef ActionAllocationType
#undef ValueType
};