// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CoreUObject/Public/UObject/Object.h"
#include "Managers/Save/CsTypes_Save.h"
#include "OnlineSubsystem.h"
#include "OnlineStats.h"
#include "Interfaces/OnlineUserCloudInterface.h"
#include "Managers/MemoryResource/CsManager_MemoryResource.h"
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"
#include "CsManager_Save.generated.h"

// Structs
#pragma region

	// Memory Resource
#pragma region

struct CSCORE_API FCsMemoryResource_SaveActionInfo : public TCsMemoryResource<FCsSaveActionInfo>
{
};

struct CSCORE_API FCsManager_MemoryResource_SaveActionInfo : public TCsManager_MemoryResource<FCsSaveActionInfo, FCsMemoryResource_SaveActionInfo, 64>
{
};

#pragma endregion Memory Resource

#pragma endregion Structs

// Delegates
#pragma region
	
	// Enumerate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagECsave_OnEnumerate, bool, WasSuccessful);
	// Read
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagECsave_OnRead, bool, WasSuccessful, const ECsSave&, Save);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagECsave_OnReadAll);
	// Write
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagECsave_OnWrite, bool, WasSuccessful, const ECsSave&, Save);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagECsave_OnWriteAll);
	// Delete
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagECsave_OnDelete, bool, WasSuccessful, const ECsSave&, Save);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagECsave_OnDeleteAll);

#pragma endregion Delegates

class ULocalPlayer;

UCLASS(transient)
class CSCORE_API UCsManager_Save : public UObject
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

public:

	virtual void Init();

// Player
#pragma region
protected:

	/** Local player to retrieve FUniqueNetId. */
	ULocalPlayer* LocalPlayer;

public:

	/**
	* Set the current local player.
	*
	* @param Player		Local Player
	*/
	void SetLocalPlayer(ULocalPlayer* Player);

	/**
	* Get the UniqueNetId for the LocalPlayer. This assumes the OnlineSubsystem and OnlineIdentity exist.
	*
	* return	Id for Local Player.
	*/
	TSharedPtr<const FUniqueNetId> GetLocalPlayerId();

	/**
	* Get the UniqueNetId for the LocalPlayer. This assumes the OnlineSubsystem and OnlineIdentity exist.
	*
	* return	Id for Local Player.
	*/
	const FUniqueNetId& GetLocalPlayerIdRef();

#pragma endregion Player

// Profile
#pragma region
protected:

	/** Player Profile associated with this manager. */
	ECsPlayerProfile ProfileType;

public:

	/**
	* Set the player profile associated with this manager.
	*
	* @param InProfileType	New player profile for this manager.
	*/
	void SetProfileType(const ECsPlayerProfile& InProfileType);

protected:

	/** Name of the profile associated with this manager. */
	FString ProfileName;

public:

	/**
	* Set the name of the profile associated with this manager.
	*
	* @param Name	Name of the profile.
	*/
	void SetProfileName(const FString& Name);

#pragma endregion Profile

public:

	virtual void OnTick(const float& DeltaSeconds);

// FileName
#pragma region
protected:

	/** Name to be appended in from the save filename (i.e. Profile1 to make Profile1_Save1). */
	FString ProfileFileNamePrefix;

	/** Name to be appended in from the save filename (i.e. Profile1_ to make Profile1_Save1). */
	FString ProfileFileNamePrefixWithUndECscore;

public:

	/**
	* Set the name of the prefix to append to the save filename.
	*
	* @ param Prefix	Name of the prefix to append to the save filename.
	*/
	void SetProfileFileNamePrefix(const FString& Prefix);

protected:

	/** File extension for Save Files (i.e. .json, ... etc). */
	FString SaveFileNameExt;

public:

	/**
	* Set the File extension for Save Files.
	* @param Ext	Name of the extension (i.e. .json, ... etc).
	*/
	void SetSaveFileNameExt(const FString& Ext);

	/**
	*
	*
	* @param Save
	* @param FileName
	*/
	void SetSaveFileName(const ECsSave& Save, const FString& FileName);

	/**
	*
	*
	* @param Save
	* return FileName
	*/
	const FString& GetSaveFileName(const ECsSave& Save);

protected:

	/** */
	TArray<FCsSaveFileInfo> SaveFileInfos;

	/** */
	TArray<FCsSaveFileInfo> SaveFileInfosAll;

public:

	/**
	*
	*
	* @param Save
	* return SaveFileInfo associated with Save.
	*/
	const FCsSaveFileInfo& GetSaveFileInfo(const ECsSave& Save);

#pragma endregion FileName

// Data
#pragma region
public:

	void SetSaveDataTest(const ECsSave& Save, const FString& InData);

protected:

	virtual void SetSaveData(const ECsSave& Save);

	virtual void GetSaveData(const ECsSave& Save, FString& OutData);
	virtual void GetSaveData(const int32& Index, FString& OutData);

#pragma endregion Data

// Action
#pragma region
protected:

	/** Manager to handle a resource pool of FCsSaveActionInfo. */
	FCsManager_MemoryResource_SaveActionInfo Manager_MemoryResource;

public:

	/**
	* @param Action		Type of action to queue (Enumerate, Read, Write, or Delete).
	* @param Save		The Save (slot) to perform the action on.
	*/
	void QueueAction(const ECsSaveAction& Action, const ECsSave& Save);

protected:

	/**
	* Queue action. The action gets enqueued into the list of actions being processed.
	*
	* @param Action		Type of action to queue (Enumerate, Read, Write, or Delete).
	* @param Index		The File Index to perform the action on.
	*/
	void QueueAction(const ECsSaveAction& Action, const int32& Index);

	/**
	* Queue action. The action gets enqueued into the list of actions being processed.
	*
	* @param Action		Type of action to queue (Enumerate, Read, Write, or Delete).
	*/
	void QueueAction(const ECsSaveAction& Action);

protected:

	void QueueActionAsHead(const ECsSaveAction& Action, const int32& Index);

	/**
	* Queue action as the first action (Head) to be processed.
	*
	* @param Action		Type of action to queue (Enumerate, Read, Write, or Delete).
	*/
	void QueueActionAsHead(const ECsSaveAction& Action);

	void QueueActionAfterHead(const ECsSaveAction& Action, const int32& Index);

	void QueueActionAfterHead(const ECsSaveAction& Action);

#pragma endregion Action

// Enumerate
#pragma region
public:

	/**
	* Get a list of all save filenames.
	*/
	void Enumerate();

protected:

	void Enumerate_Internal();

public:

	/** Delegate type when save files have been enumerated / file names recorded.
	*
	* @param WasSuccessful
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnumerate, bool /*WasSuccessful*/);

	/** Event for when save files have been enumerated / file names recorded.
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnEnumerate OnEnumerate_Event;
	/** Script Event for when save files have been enumerated / file names recorded.
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagECsave_OnEnumerate OnEnumerate_ScriptEvent;

	/** Event for when save files have been enumerated / file names recorded.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnEnumerate OnEnumerate_AsyncEvent;
	/** Script Event for when save files have been enumerated / file names recorded.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagECsave_OnEnumerate OnEnumerate_AsyncScriptEvent;

#pragma endregion Enumerate

// Read
#pragma region
public:

	/**
	* Read a save from a defined Save (slot)
	* 
	* @param Save		Save (slot) to read from.
	*/
	void Read(const ECsSave& Save);

protected:

	/**
	* Read a save at Index.
	* 
	* @param Index		Index of the save to read from.
	*/
	void Read(const int32& Index);
	void Read_Internal(FCsSaveActionInfo* ActionInfo);

public:

	/** Delegate type when successfully finished reading a Save. 
	*
	* @param WasSuccessful
	* @param Save
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRead, bool /*WasSuccessful*/, const ECsSave& /*Save*/);

	/** Event for when successfully finished reading a Save.
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnRead OnRead_Event;
	/** Script Event for when successfully finished reading a Save.
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagECsave_OnRead OnRead_ScriptEvent;

	/** Event for when successfully finished reading a Save.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnRead OnRead_AsyncEvent;
	/** Script Event for when successfully finished reading a Save.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagECsave_OnRead OnRead_AsyncScriptEvent;

public:

	/**
	* Read all saves for a Profile.
	* 
	* @param Profile
	*/
	void ReadAll();

protected:

	void ReadAll_Internal(FCsSaveActionInfo* ActionInfo);

public:

	/** Delegate type when successfully finished reading a all saves.
	*
	*/
	DECLARE_MULTICAST_DELEGATE(FOnReadAll);

	/** Event for when successfully finished reading all saves. */
	FOnReadAll OnReadAll_Event;

	/** Script Event for when successfully finished reading all saves. */
	FCsManagECsave_OnReadAll OnReadAll_ScriptEvent;

#pragma endregion Read

// Write
#pragma region
public:

	/**
	* Write save at defined Save (slot).
	* 
	* @param Save	Save (slot) to write to.
	*/
	void Write(const ECsSave& Save);

protected:

	/**
	* Write save at Index.
	*
	* @param Index	Index of the save to write to.
	*/
	void Write(const int32& Index);
	void Write_Internal(FCsSaveActionInfo* ActionInfo);

public:

	/** Delegate type when successfully finished writing a Save.
	* 
	* @param WasSuccessful
	* @param Save
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWrite, bool /*WasSuccessful*/, const ECsSave& /*Save*/);

	/** Event for when successfully finished writing a Save.
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnWrite OnWrite_Event;
	/** Script Event for when successfully finished writing a Save.
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagECsave_OnWrite OnWrite_ScriptEvent;

	/** Event for when successfully finished writing a Save.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnWrite OnWrite_AsyncEvent;
	/** Script Event for when successfully finished writing a Save.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagECsave_OnWrite OnWrite_AsyncScriptEvent;

public:

	/**
	* Write all saves for a Profile.
	*/
	void WriteAll();

protected:

	void WriteAll_Internal(FCsSaveActionInfo* ActionInfo);

public:

	/** Delegate type when successfully finished writing a all saves.
	*
	*/
	DECLARE_MULTICAST_DELEGATE(FOnWriteAll);

	/** Event for when successfully finished writing all saves. */
	FOnWriteAll OnWriteAll_Event;

	/** Script Event for when successfully finished writing all saves. */
	FCsManagECsave_OnWriteAll OnWriteAll_ScriptEvent;

#pragma endregion Write

// Delete
#pragma region
public:

	/**
	* Delete save a defined Save (slot).
	*
	* @param Save	Save (slot) to delete.
	*/
	void Delete(const ECsSave& Save);

protected:

	/**
	* Delete save at Index.
	*
	* @param Index	Index of the save to delete to.
	*/
	void Delete(const int32& Index);
	void Delete_Internal(FCsSaveActionInfo* ActionInfo);

public:

	/** Delegate type when successfully finished deleting a Save. 
	*
	* @param WasSuccessful
	* @param Save
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDelete, bool /*WasSuccessful*/, const ECsSave& /*Save*/);

	/** Event for when successfully finished deleting a Save.
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnDelete OnDelete_Event;
	/** Script Event for when successfully finished deleting a Save.
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagECsave_OnDelete OnDelete_ScriptEvent;

	/** Event for when successfully finished deleting a Save.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnDelete OnDelete_AsyncEvent;
	/** Script Event for when successfully finished deleting a Save.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagECsave_OnDelete OnDelete_AsyncScriptEvent;

public:

	/**
	* Delete all saves for a Profile.
	*/
	void DeleteAll();
	void DeleteAllContent();

protected:

	void DeleteAll_Internal(FCsSaveActionInfo* ActionInfo);

public:

	/** Delegate type when successfully finished deleting a all saves.
	*
	*/
	DECLARE_MULTICAST_DELEGATE(FOnDeleteAll);

	/** Event for when successfully finished deleting all saves. */
	FOnDeleteAll OnDeleteAll_Event;

	/** Script Event for when successfully finished deleting all saves. */
	FCsManagECsave_OnDeleteAll OnDeleteAll_ScriptEvent;

#pragma endregion Delete

// NOTE: If saving special charactECs, need to look convECsion to and from UTF-16

// IOnlineUserCloud
#pragma region
protected:

	IOnlineUserCloudPtr GetUserCloudInterface();

	FCsSaveEnumerateUserFilesState EnumerateUserFilesState;

	void OnEnumerateUserFilesComplete(bool WasSuccessful, const FUniqueNetId& UserId);

	void OnReadUserFileComplete(bool WasSuccessful, const FUniqueNetId& UserId, const FString& FileName);

	void OnWriteUserFileComplete(bool WasSuccessful, const FUniqueNetId& UserId, const FString& FileName);

	void OnDeleteUserFileComplete(bool WasSuccessful, const FUniqueNetId& UserId, const FString& FileName);

#pragma endregion IOnlineUserCloud
};