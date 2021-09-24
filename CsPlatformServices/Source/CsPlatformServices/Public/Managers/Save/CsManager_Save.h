// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/Save/CsTypes_Save.h"
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Online
#include "OnlineSubsystem.h"
#include "OnlineStats.h"
#include "Interfaces/OnlineUserCloudInterface.h"

#include "CsManager_Save.generated.h"

// Structs
#pragma region

	// Memory Resource
#pragma region

namespace NCsSave
{
	namespace NAction
	{
		namespace NInfo
		{
		#define InfoType NCsSave::NAction::NInfo::FInfo

			struct CSPLATFORMSERVICES_API FResource : public TCsResourceContainer<InfoType>
			{
			};

			struct CSPLATFORMSERVICES_API FManager : public TCsManager_ResourceValueType_Fixed<InfoType, FResource, 64>
			{
			};

		#undef InfoType
		}
	}
}

#pragma endregion Memory Resource

#pragma endregion Structs

// Delegates
#pragma region
	
/**
* OnStart
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerSave_OnStart);
/**
* OnEnumerate
*
* @param WasSuccessful
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerSave_OnEnumerate, bool, WasSuccessful);
/**
* OnRead
*
* @param WasSuccessful
* @param Profile
* @param Save
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsManagerSave_OnRead, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
/**
* OnReadAll
*
* @param Profile
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerSave_OnReadAll, const ECsPlayerProfile&, Profile);
/**
* OnWrite
*
* @param WasSuccessful
* @param Profile
* @param Save
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsManagerSave_OnWrite, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
/**
* OnWriteAll
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerSave_OnWriteAll);
/**
* OnDelete
*
* @param WasSuccessful
* @param Profile
* @param Save
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsManagerSave_OnDelete, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
/**
* OnDeleteAll
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerSave_OnDeleteAll);

#pragma endregion Delegates

class UClass;
class ULocalPlayer;
class ICsGetManagerSave;

/**
* 
*/
UCLASS(transient)
class CSPLATFORMSERVICES_API UCsManager_Save : public UObject
{
	GENERATED_UCLASS_BODY()

#define FileInfoType NCsSave::NFile::FInfo
#define ActionType NCsSave::EAction
#define ActionInfoType NCsSave::NAction::NInfo::FInfo

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Save* Get(UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_Save* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid();
	static void Init(UObject* InRoot, UClass* ManagerSaveClass);
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown();

#if WITH_EDITOR
protected:

	static ICsGetManagerSave* Get_GetManagerSave(UObject* InRoot);
	static ICsGetManagerSave* GetSafe_GetManagerSave(UObject* Object);

	static UCsManager_Save* GetSafe(UObject* Object);

public:

	static UCsManager_Save* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Save* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject * MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

// Start
#pragma region
public:

	void Start();

	/**
	*
	*/
	DECLARE_MULTICAST_DELEGATE(FOnStart);

	/** */
	FOnStart OnStart_Event;
	/** */
	FCsManagerSave_OnStart OnStart_ScriptEvent;

protected:

	bool bHasStarted;

public:

	FORCEINLINE bool HasStarted() { return bHasStarted; }

#pragma endregion Start

// Storage
#pragma region
protected:

	ECsSaveStorage CurrentStorage;

public:

	void SetCurrentStorage(const ECsSaveStorage& Storage);

protected:

	FString SaveFolder;

public:

	void SetSaveFolder(const FString& Folder);

	const FString& GetSaveFolder() const;

protected:

	FString SaveDir;
	FString SaveDirAbsolute;

public:

	/**
	*
	*
	* return
	*/
	const FString& GetSaveDir() const;

	/**
	*
	*
	* return
	*/
	const FString& GetSaveDirAbsolute() const;

#pragma endregion Storage

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

	/**
	*
	*
	* return
	*/
	FString GetLocalPlayerNickname();

#pragma endregion Player

// Profile
#pragma region
protected:

	/** Name of the profile associated with this manager. */
	TArray<FString> ProfileNames;

public:

	/**
	* Set the name of the profile for particular profile type.
	*
	* @param Profile	Type of profile.
	* @param Name		Name of the profile.
	*/
	void SetProfileName(const ECsPlayerProfile& Profile, const FString& Name);

#pragma endregion Profile

public:

	virtual void Update(const FCsDeltaTime& DeltaTime);

// FileName
#pragma region
protected:

	/** Name to be appended in front of the save filename (i.e. Profile1 to make Profile1_Save1). */
	TArray<FString> ProfileFileNamePrefixes;

	/** Name to be appended in front of the save filename (i.e. Profile1_ to make Profile1_Save1). */
	TArray<FString> ProfileFileNamePrefixesWithUnderscore;

public:

	/**
	* Set the name of the prefix to append to the save filename.
	*
	* @param Profile
	* @param Prefix		Name of the prefix to append to the save filename.
	*/
	void SetProfileFileNamePrefix(const ECsPlayerProfile& Profile, const FString& Prefix);

protected:

	/** File extension for Save Files (i.e. .json, ... etc). */
	FString SaveFileNameExt;

public:

	/**
	* Set the File extension for Save Files.
	*
	* @param Ext	Name of the extension (i.e. .json, ... etc).
	*/
	void SetSaveFileNameExt(const FString& Ext);

	/**
	*
	*
	* @param Profile
	* @param Save
	* @param FileName
	*/
	void SetSaveFileName(const ECsPlayerProfile& Profile, const ECsSave& Save, const FString& FileName);

	/**
	*
	*
	* @param Profile
	* @param Save
	* return FileName
	*/
	const FString& GetSaveFileName(const ECsPlayerProfile& Profile, const ECsSave& Save);

protected:

	/** */
	TArray<TArray<FileInfoType>> SaveFileInfos;

	/** */
	TArray<FileInfoType> SaveFileInfosAll;

public:

	/**
	*
	*
	* @param Profile
	* @param Save
	* return SaveFileInfo associated with Save.
	*/
	const FileInfoType& GetSaveFileInfo(const ECsPlayerProfile& Profile, const ECsSave& Save);

protected:

	/** */
	int32 CurrentSaveIndex;

public:

	/**
	*
	*
	* @param Index
	*/
	void SetCurrentSaveIndex(const int32& Index);

protected:

	/** */
	ECsSave CurrentSave;

public:

	/**
	*
	*
	* @param Index
	*/
	void SetCurrentSave(const ECsSave& Save);

#pragma endregion FileName

// Data
#pragma region
public:

	void SetSaveDataTest(const ECsPlayerProfile& Profile, const ECsSave& Save, const FString& InData);

protected:
	
	/**
	* Called on action: Read or Read All. After Read or for each Read in Read All, update the data for the appropriate Profile
	* and Save (slot). The details of how this is implemented is left for the child class as 
	* the structure and / or layout of the data could vary from project to project.
	* Example: 
	*  Data stored as a struct vs class.
	*  De-serializing the raw data, typically a string, to the appropriate data structure (i.e. .json string to struct) 
	* 
	* @param Profile	Profile to set data for.
	* @param Save		Save (slot) to set data for.
	*/
	virtual void SetSaveData(const ECsPlayerProfile& Profile, const ECsSave& Save);

	/**
	* Called on action: Read or Read All. After Read or for each Read in Read All, update the data for the appropriate Profile
	* and Save (index). The details of how this is implemented is left for the child class as
	* the structure and / or layout of the data could vary from project to project.
	* Example:
	*  Data stored as a struct vs class.
	*  De-serializing the raw data, typically a string, to the appropriate data structure (i.e. .json to struct)
	*
	* @param Profile	Profile to set data for.
	* @param Index		Index of the save set data for.
	*/
	virtual void SetSaveData(const ECsPlayerProfile& Profile, const int32& Index);

	/**
	*
	*/
	void SetAllSaveData(const ECsPlayerProfile& Profile);

	/**
	* Called on action: Write or Write All. For Write or for each Write in Write All, get the data for the appropriate Profile
	* and Save (slot) as a string. The details of how this is implemented is left for the child class as
	* the structure and / or layout of the data could vary from project to project.
	* Example:
	*  Data stored as a struct vs class.
	*  Serializing the data to a string (i.e. struct to .json string).
	*
	* @param Profile	Profile to get data for.
	* @param Save		Save (slot) to get data for.
	* @param OutData	Data serialized as a string.
	*/
	virtual void GetSaveData(const ECsPlayerProfile& Profile, const ECsSave& Save, FString& OutData);

	/**
	* Called on action: Write or Write All. For Write or for each Write in Write All, get the data for the appropriate Profile
	* and Save (index) as a string. The details of how this is implemented is left for the child class as
	* the structure and / or layout of the data could vary from project to project.
	* Example:
	*  Data stored as a struct vs class.
	*  Serializing the data to a string (i.e. struct to .json string).
	*
	* @param Profile	Profile to get data for.
	* @param Index		Index of the save to get data for.
	* @param OutData	Data serialized as a string.
	*/
	virtual void GetSaveData(const ECsPlayerProfile& Profile, const int32& Index, FString& OutData);

	/**
	* Called on action: Delete or Delete All. For Delete or for each Delete in Delete All, clear the data for the appropriate Profile
	* and Save (slot). The details of how this is implemented is left for the child class as
	* the structure and / or layout of the data could vary from project to project.
	* Example:
	*  Data stored as a struct or class.
	*  Empty the contents of the data (i.e. reset the struct to a default state).
	*
	* @param Profile	Profile to reset data for.
	* @param Save		Save (slot) to reset the data for.
	*/
	virtual void ClearSaveData(const ECsPlayerProfile& Profile, const ECsSave& Save);

	/**
	* Called on action: Delete or Delete All. For Delete or for each Delete in Delete All, clear the data for the appropriate Profile
	* and Save (index). The details of how this is implemented is left for the child class as
	* the structure and / or layout of the data could vary from project to project.
	* Example:
	*  Data stored as a struct or class.
	*  Empty the contents of the data (i.e. reset the struct to a default state).
	*
	* @param Profile	Profile to reset data for.
	* @param Index		Index of the save to reset data for.
	*/
	virtual void ClearSaveData(const ECsPlayerProfile& Profile, const int32& Index);

#define DataInfoType NCsSave::NData::FInfo
	TArray<TArray<DataInfoType>> SaveDataInfos;
#undef DataInfoType

public:

	bool HasSetSaveData(const ECsPlayerProfile& Profile, const ECsSave& Save);

protected:

	bool HasSetSaveData(const ECsPlayerProfile& Profile, const int32& Index);

#pragma endregion Data

// Action
#pragma region
protected:

#define ActionInfoManagerType NCsSave::NAction::NInfo::FManager

	/** Manager to handle a resource pool of ActionInfoType (NCsSave::NAction::NInfo::FInfo). */
	ActionInfoManagerType Manager_Resource;

#undef ActionInfoManagerType

public:

	/**
	*
	*
	* @param Profile
	* @param Action		Type of action to queue (Enumerate, Read, Write, or Delete).
	* @param Save		The Save (slot) to perform the action on.
	* @param Data		Data for the action.
	*/
	void QueueAction(const ECsPlayerProfile& Profile, const ActionType& Action, const ECsSave& Save, const FString& Data = NCsCached::Str::Empty);

protected:

	/**
	* Queue action. The action gets enqueued into the list of actions being processed.
	*
	* @param Profile
	* @param Action		Type of action to queue (Enumerate, Read, Write, or Delete).
	* @param Index		The File Index to perform the action on.
	* @param Data		Data for the action.
	*/
	void QueueAction(const ECsPlayerProfile& Profile, const ActionType& Action, const int32& Index, const FString& Data = NCsCached::Str::Empty);

	/**
	* Queue action. The action gets enqueued into the list of actions being processed.
	*
	* @param Profile
	* @param Action		Type of action to queue (Enumerate, Read, Write, or Delete).
	*/
	void QueueAction(const ECsPlayerProfile& Profile, const ActionType& Action);

protected:

	void QueueActionAsHead(const ECsPlayerProfile& Profile, const ActionType& Action, const int32& Index);

	/**
	* Queue action as the first action (Head) to be processed.
	*
	* @param Profile
	* @param Action		Type of action to queue (Enumerate, Read, Write, or Delete).
	*/
	void QueueActionAsHead(const ECsPlayerProfile& Profile, const ActionType& Action);

	void QueueActionAfterHead(const ECsPlayerProfile& Profile, const ActionType& Action, const int32& Index);

	void QueueActionAfterHead(const ECsPlayerProfile& Profile, const ActionType& Action);

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
	FCsManagerSave_OnEnumerate OnEnumerate_ScriptEvent;

	/** Event for when save files have been enumerated / file names recorded.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnEnumerate OnEnumerate_AsyncEvent;
	/** Script Event for when save files have been enumerated / file names recorded.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerSave_OnEnumerate OnEnumerate_AsyncScriptEvent;

	/**
	*
	*
	* return
	*/
	FORCEINLINE bool IsEnumerateComplete() const
	{
		return EnumerateUserFilesState.IsComplete();
	}

	/**
	*
	*
	* return
	*/
	FORCEINLINE bool IsEnumerateCompleteAndNotProcessing() const
	{
		return EnumerateUserFilesState.IsCompleteAndNotProcessing();
	}

#pragma endregion Enumerate

// Read
#pragma region
public:

	/**
	* Read a save from a defined Save (slot)
	* 
	* @param Profile	Profile to read from.
	* @param Save		Save (slot) to read from.
	*/
	void Read(const ECsPlayerProfile& Profile, const ECsSave& Save);

protected:

	/**
	* Read a save at Index.
	* 
	* @param Profile	Profile to read from.
	* @param Index		Index of the save to read from.
	*/
	void Read(const ECsPlayerProfile& Profile, const int32& Index);
	void Read_Internal(ActionInfoType* ActionInfo);

public:

	/** Delegate type when successfully finished reading a Save. 
	*
	* @param WasSuccessful		If the save was successful or not.
	* @param Profile			Profile the save was read from.
	* @param Save				Save (slot) that was read from.
	*/
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnRead, bool /*WasSuccessful*/, const ECsPlayerProfile& /*Profile*/, const ECsSave& /*Save*/);

	/** Event for when successfully finished reading a Save.
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnRead OnRead_Event;
	/** Script Event for when successfully finished reading a Save.
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerSave_OnRead OnRead_ScriptEvent;

	/** Event for when successfully finished reading a Save.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnRead OnRead_AsyncEvent;
	/** Script Event for when successfully finished reading a Save.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerSave_OnRead OnRead_AsyncScriptEvent;

	/**
	* Check whether the Read action has been performed at least once
	* for the CurrentSaveIndex.
	*
	* @param Profile	Profile to check.
	*/
	bool HasPerformedRead(const ECsPlayerProfile& Profile) const;

	/**
	* Check whether the Read action has been performed at least once.
	*
	* @param Profile	Profile to check.
	* @param Save		Save (slot) to check.
	*/
	bool HasPerformedRead(const ECsPlayerProfile& Profile, const ECsSave& Save) const;

protected:

	/**
	* Check whether the Read action has been performed at least once.
	*
	* @param Profile	Profile to check.
	* @param Save		Index of the save to check.
	*/
	bool HasPerformedRead(const ECsPlayerProfile& Profile, const int32& Index) const;

public:

	/**
	* Read all saves.
	* 
	* @param Profile
	*/
	void ReadAll(const ECsPlayerProfile& Profile);

protected:

	void ReadAll_Internal(ActionInfoType* ActionInfo);

public:

	/**
	* Delegate type when successfully finished reading a all saves.
	*
	* @param Profile
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnReadAll, const ECsPlayerProfile& /*Profile*/);

	/** Event for when successfully finished reading all saves. */
	FOnReadAll OnReadAll_Event;

	/** Script Event for when successfully finished reading all saves. */
	FCsManagerSave_OnReadAll OnReadAll_ScriptEvent;

	/**
	* Check whether the Read All action has been performed at least once.
	*
	* @param Profile	Profile to check.
	*/
	bool HasPerformedReadAll(const ECsPlayerProfile& Profile) const;

	/**
	* Check whether the Read All action has been performed at least once.
	*/
	bool HasPerformedReadAll() const;

#pragma endregion Read

// Write
#pragma region
public:

	/**
	* Write a save to a defined Save (slot).
	* 
	* @param Profile	Profile to write to.
	* @param Save		Save (slot) to write to.
	*/
	void Write(const ECsPlayerProfile& Profile, const ECsSave& Save);

protected:

	/**
	* Write save at Index.
	*
	* @param Profile	Profile to write to.
	* @param Index		Index of the save to write to.
	*/
	void Write(const ECsPlayerProfile& Profile, const int32& Index);
	void Write_Internal(ActionInfoType* ActionInfo);

public:

	/** Delegate type when successfully finished writing a Save.
	* 
	* @param WasSuccessful		If the write was successful or not.
	* @param Profile			Profile the save was written to.
	* @param Save				Save (slot) that was written to.
	*/
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnWrite, bool /*WasSuccessful*/, const ECsPlayerProfile& /*Profile*/, const ECsSave& /*Save*/);

	/** Event for when successfully finished writing a Save.
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnWrite OnWrite_Event;
	/** Script Event for when successfully finished writing a Save.
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerSave_OnWrite OnWrite_ScriptEvent;

	/** Event for when successfully finished writing a Save.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnWrite OnWrite_AsyncEvent;
	/** Script Event for when successfully finished writing a Save.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerSave_OnWrite OnWrite_AsyncScriptEvent;

	/**
	* Check whether the Write action has been performed at least once.
	*
	* @param Profile	Profile to check.
	* @param Save		Save (slot) to check.
	*/
	bool HasPerformedWrite(const ECsPlayerProfile& Profile, const ECsSave& Save) const;

protected:

	/**
	* Check whether the Write action has been performed at least once.
	*
	* @param Profile	Profile to check.
	* @param Save		Index of the save to check.
	*/
	bool HasPerformedWrite(const ECsPlayerProfile& Profile, const int32& Index) const;

public:

	/**
	* Write all saves for a Profile.
	*
	* @param Profile
	*/
	void WriteAll(const ECsPlayerProfile& Profile);

protected:

	void WriteAll_Internal(ActionInfoType* ActionInfo);

public:

	/** Delegate type when successfully finished writing a all saves.
	*
	*/
	DECLARE_MULTICAST_DELEGATE(FOnWriteAll);

	/** Event for when successfully finished writing all saves. */
	FOnWriteAll OnWriteAll_Event;

	/** Script Event for when successfully finished writing all saves. */
	FCsManagerSave_OnWriteAll OnWriteAll_ScriptEvent;

#pragma endregion Write

// Delete
#pragma region
public:

	/**
	* Delete a save at a defined Save (slot).
	*
	* @param Profile	Profile to delete save from.
	* @param Save		Save (slot) to delete.
	*/
	void Delete(const ECsPlayerProfile& Profile, const ECsSave& Save);

protected:

	/**
	* Delete a save at Index.
	*
	* @param Profile	Profile to delete save from.
	* @param Index		Index of the save to delete to.
	*/
	void Delete(const ECsPlayerProfile& Profile, const int32& Index);
	void Delete_Internal(ActionInfoType* ActionInfo);

public:

	/** Delegate type when successfully finished deleting a Save. 
	*
	* @param WasSuccessful		If the delete was successful or not.
	* @param Profile			Profile the save was deleted from.
	* @param Save				Save (slot) that has been deleted.
	*/
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnDelete, bool /*WasSuccessful*/, const ECsPlayerProfile& /*Profile*/, const ECsSave& /*Save*/);

	/** Event for when successfully finished deleting a Save.
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnDelete OnDelete_Event;
	/** Script Event for when successfully finished deleting a Save.
		Latent and Synchronous (Game Thread) when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerSave_OnDelete OnDelete_ScriptEvent;

	/** Event for when successfully finished deleting a Save.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FOnDelete OnDelete_AsyncEvent;
	/** Script Event for when successfully finished deleting a Save.
		Latent and Asynchronous. Only called when an OnlineSubsystem with OnlineAchievements is valid. */
	FCsManagerSave_OnDelete OnDelete_AsyncScriptEvent;

	/**
	* Check whether the Delete action has been performed at least once.
	*
	* @param Profile	Profile to check.
	* @param Save		Save (slot) to check.
	*/
	bool HasPerformedDelete(const ECsPlayerProfile& Profile, const ECsSave& Save) const;

protected:

	/**
	* Check whether the Delete action has been performed at least once.
	*
	* @param Profile	Profile to check.
	* @param Save		Index of the save to check.
	*/
	bool HasPerformedDelete(const ECsPlayerProfile& Profile, const int32& Index) const;

public:

	/**
	* Delete all saves.
	*
	* @param Profile
	*/
	void DeleteAll(const ECsPlayerProfile& Profile);

	/**
	* Delete all saves for all profiles.
	*/
	void DeleteAllContent();

protected:

	void DeleteAll_Internal(ActionInfoType* ActionInfo);

public:

	/** Delegate type when successfully finished deleting a all saves.
	*
	*/
	DECLARE_MULTICAST_DELEGATE(FOnDeleteAll);

	/** Event for when successfully finished deleting all saves. */
	FOnDeleteAll OnDeleteAll_Event;

	/** Script Event for when successfully finished deleting all saves. */
	FCsManagerSave_OnDeleteAll OnDeleteAll_ScriptEvent;

#pragma endregion Delete

// NOTE: If saving special characters, need to look conversion to and from UTF-16

// IOnlineUserCloud
#pragma region
protected:

	IOnlineUserCloudPtr GetUserCloudInterface();

	NCsSave::FEnumerateUserFilesState EnumerateUserFilesState;

	void OnEnumerateUserFilesComplete(bool WasSuccessful, const FUniqueNetId& UserId);

	void OnReadUserFileComplete(bool WasSuccessful, const FUniqueNetId& UserId, const FString& FileName);

	void OnWriteUserFileComplete(bool WasSuccessful, const FUniqueNetId& UserId, const FString& FileName);

	void OnDeleteUserFileComplete(bool WasSuccessful, const FUniqueNetId& UserId, const FString& FileName);

#pragma endregion IOnlineUserCloud

#undef FileInfoType
#undef ActionType
#undef ActionInfoType
};