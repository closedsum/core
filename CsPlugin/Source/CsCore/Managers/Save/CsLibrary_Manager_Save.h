// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/CoreUObject/Public/UObject/Object.h"
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"
#include "Managers/Save/CsTypes_Save.h"
#include "CsLibrary_Manager_Save.generated.h"

// Delegates
#pragma region

// Enumerate
DECLARE_DYNAMIC_DELEGATE_OneParam(FCsLibraryManagerSave_OnEnumerate, bool, WasSuccessful);
// Read
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCsLibraryManagerSave_OnRead, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerSave_OnReadAll);
// Write
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCsLibraryManagerSave_OnWrite, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerSave_OnWriteAll);
// Delete
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCsLibraryManagerSave_OnDelete, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerSave_OnDeleteAll);

#pragma endregion Delegates


UCLASS()
class CSCORE_API UCsLibrary_Manager_Save : public UObject
{
	GENERATED_UCLASS_BODY()

// FileName
#pragma region
public:

	/**
	* Set the current save (slot).
	*
	* @param WorldContextObject
	* @param Save					Save (slot) to set as the current save.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Save"))
	static void SetCurrentSave(const UObject* WorldContextObject, const ECsSave& Save);

#pragma endregion FileName

// Enumerate
#pragma region
public:

	/**
	* Get a list of all save filenames for specified profile.
	*
	* @param WorldContextObject
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject"))
	static void Enumerate(const UObject* WorldContextObject);

	/**
	* Bind to the event when the Enumerate action has completed.
	*		
	* @param Event / Delegate	Event to call when Enumerate action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnEnumerate", WorldContext = "WorldContextObject"))
	static void BindToEvent_OnEnumerate(const UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsLibraryManagerSave_OnEnumerate Delegate);

#pragma endregion Enumerate

// Read
#pragma region
public:

	/**
	* Read a save for a specified profile and Save (slot)
	* 
	* @param WorldContextObject
	* @param Profile				Profile to read save from.
	* @param Save					Save (slot) to read from.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Profile,Save"))
	static void Read(const UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save);

	/**
	* Bind to the event when the Read action has completed.
	*
	* @param WorldContextObject
	* @param Profile				Profile to read save from.
	* @param Event / Delegate		Event to call when the Read action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnRead", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Profile"))
	static void BindToEvent_OnRead(const UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsLibraryManagerSave_OnRead Delegate);

	/**
	* Read all saves for a specified profile.
	*
	* @param WorldContextObject
	* @param Profile				Profile to read all saves from.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Profile"))
	static void ReadAll(const UObject* WorldContextObject, const ECsPlayerProfile& Profile);

	/**
	* Bind to the event when the Read All action has completed.
	*
	* @param WorldContextObject
	* @param Event / Delegate		Event to call when the Read All action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnReadAll", WorldContext = "WorldContextObject"))
	static void BindToEvent_OnReadAll(const UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsLibraryManagerSave_OnReadAll Delegate);

#pragma endregion Read

// Write
#pragma region
public:

	/**
	* Write a save for a specified profile and Save (slot). 
	*
	* @param WorldContextObject
	* @param Profile				Profile to write save to.
	* @param Save					Save (slot) to write to.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Profile,Save"))
	static void Write(const UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save);

	/**
	* Bind to the event when the Write action has completed.
	*
	* @param WorldContextObject
	* @param Event / Delegate		Event to call when the Write action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnWrite", WorldContext = "WorldContextObject"))
	static void BindToEvent_OnWrite(const UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsLibraryManagerSave_OnWrite Delegate);

	/**
	* Write all saves for a specified profile.
	* 
	* @param WorldContextObject
	* @param Profile				Profile to write all saves to.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Profile"))
	static void WriteAll(const UObject* WorldContextObject, const ECsPlayerProfile& Profile);

	/**
	* Bind to the event when the Write All action has completed.
	*
	* @param WorldContextObject
	* @param Event / Delegate		Event to call when the Write All action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnWriteAll", WorldContext = "WorldContextObject"))
	static void BindToEvent_OnWriteAll(const UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsLibraryManagerSave_OnWriteAll Delegate);

#pragma endregion Write

// Delete
#pragma region
public:

	/**
	* Delete a save for a specified profile and Save (slot).
	*
	* @param WorldContextObject
	* @param Profile				Profile to delete save from.
	* @param Save					Save (slot) to delete.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Profile,Save"))
	static void Delete(const UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save);

	/**
	* Bind to the event when the Delete action has completed.
	*
	* @param WorldContextObject
	* @param Event / Delegate		Event to call when the Delete action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnDelete", WorldContext = "WorldContextObject"))
	static void BindToEvent_OnDelete(const UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsLibraryManagerSave_OnDelete Delegate);


	/**
	* Delete all saves for a specified profile.
	*
	* @param WorldContextObject
	* @param Profile				Profile to delete all saves from.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Profile"))
	static void DeleteAll(const UObject* WorldContextObject, const ECsPlayerProfile& Profile);

	/**
	* Bind to the event when the Delete All action has completed.
	*
	* @param WorldContextObject
	* @param Event / Delegate		Event to call when the Delete All action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnDeleteAll", WorldContext = "WorldContextObject"))
	static void BindToEvent_OnDeleteAll(const UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsLibraryManagerSave_OnDeleteAll Delegate);

	/**
	* Delete all saves for all profiles.
	*
	* * @param WorldContextObject
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject"))
	static void DeleteAllContent(const UObject* WorldContextObject);

#pragma endregion Delete
};