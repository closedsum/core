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
DECLARE_DYNAMIC_DELEGATE_TwoParams(FCsLibraryManagerSave_OnRead, bool, WasSuccessful, const ECsSave&, Save);
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerSave_OnReadAll);
// Write
DECLARE_DYNAMIC_DELEGATE_TwoParams(FCsLibraryManagerSave_OnWrite, bool, WasSuccessful, const ECsSave&, Save);
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerSave_OnWriteAll);
// Delete
DECLARE_DYNAMIC_DELEGATE_TwoParams(FCsLibraryManagerSave_OnDelete, bool, WasSuccessful, const ECsSave&, Save);
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerSave_OnDeleteAll);

#pragma endregion Delegates


UCLASS()
class CSCORE_API UCsLibrary_Manager_Save : public UObject
{
	GENERATED_UCLASS_BODY()

// Enumerate
#pragma region
public:

	/**
	* Get a list of all save filenames for specified profile.
	*
	* @param ProfileType	Profile to get filenames for.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (AutoCreateRefTerm = "ProfileType"))
	static void Enumerate(const ECsPlayerProfile& ProfileType);

	/**
	* Bind to the event when the Enumerate action has completed.
	*
	* @param Event / Delegate	Event to call when Enumerate action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnEnumerate", AutoCreateRefTerm = "ProfileType"))
	static void BindToEvent_OnEnumerate(const ECsPlayerProfile& ProfileType, UPARAM(DisplayName = "Event") FCsLibraryManagerSave_OnEnumerate Delegate);

#pragma endregion Enumerate

// Read
#pragma region
public:

	/**
	* Read a save for a specified profile and Save (slot)
	* 
	* @param ProfileType	Profile to read save from.
	* @param Save			Save (slot) to read from.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (AutoCreateRefTerm = "ProfileType,Save"))
	static void Read(const ECsPlayerProfile& ProfileType, const ECsSave& Save);

	/**
	* Bind to the event when the Read action has completed.
	*
	* @param ProfileType		Profile to read save from.
	* @param Event / Delegate	Event to call when the Read action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnRead", AutoCreateRefTerm = "ProfileType"))
	static void BindToEvent_OnRead(const ECsPlayerProfile& ProfileType, UPARAM(DisplayName = "Event") FCsLibraryManagerSave_OnRead Delegate);

	/**
	* Read all saves for a specified profile.
	*
	* @param ProfileType	Profile to read all saves from.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (AutoCreateRefTerm = "ProfileType"))
	static void ReadAll(const ECsPlayerProfile& ProfileType);

	/**
	* Bind to the event when the Read All action has completed.
	*
	* @param ProfileType		Profile to read saves from.
	* @param Event / Delegate	Event to call when the Read All action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnReadAll", AutoCreateRefTerm = "ProfileType"))
	static void BindToEvent_OnReadAll(const ECsPlayerProfile& ProfileType, UPARAM(DisplayName = "Event") FCsLibraryManagerSave_OnReadAll Delegate);

#pragma endregion Read

// Write
#pragma region
public:

	/**
	* Write a save for a specified profile and Save (slot). 
	*
	* @param ProfileType	Profile to write save to.
	* @param Save			Save (slot) to write to.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (AutoCreateRefTerm = "ProfileType,Save"))
	static void Write(const ECsPlayerProfile& ProfileType, const ECsSave& Save);

	/**
	* Bind to the event when the Write action has completed.
	*
	* @param ProfileType		Profile to write save to.
	* @param Event / Delegate	Event to call when the Write action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnWrite", AutoCreateRefTerm = "ProfileType"))
	static void BindToEvent_OnWrite(const ECsPlayerProfile& ProfileType, UPARAM(DisplayName = "Event") FCsLibraryManagerSave_OnWrite Delegate);

	/**
	* Write all saves for a specified profile.
	* 
	* @param ProfileType	Profile to write all saves to.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (AutoCreateRefTerm = "ProfileType"))
	static void WriteAll(const ECsPlayerProfile& ProfileType);

	/**
	* Bind to the event when the Write All action has completed.
	*
	* @param ProfileType		Profile to write all saves to.
	* @param Event / Delegate	Event to call when the Write All action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnWriteAll", AutoCreateRefTerm = "ProfileType"))
	static void BindToEvent_OnWriteAll(const ECsPlayerProfile& ProfileType, UPARAM(DisplayName = "Event") FCsLibraryManagerSave_OnWriteAll Delegate);

#pragma endregion Write

// Delete
#pragma region
public:

	/**
	* Delete a save for a specified profile and Save (slot).
	*
	* @param ProfileType	Profile to delete save from.
	* @param Save			Save (slot) to delete.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (AutoCreateRefTerm = "ProfileType,Save"))
	static void Delete(const ECsPlayerProfile& ProfileType, const ECsSave& Save);

	/**
	* Bind to the event when the Delete action has completed.
	*
	* @param ProfileType		Profile to delete save from.
	* @param Event / Delegate	Event to call when the Delete action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnDelete", AutoCreateRefTerm = "ProfileType"))
	static void BindToEvent_OnDelete(const ECsPlayerProfile& ProfileType, UPARAM(DisplayName = "Event") FCsLibraryManagerSave_OnDelete Delegate);


	/**
	* Delete all saves for a specified profile.
	*
	* @param ProfileType	Profile to delete all saves from.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (AutoCreateRefTerm = "ProfileType"))
	static void DeleteAll(const ECsPlayerProfile& ProfileType);

	/**
	* Bind to the event when the Delete All action has completed.
	*
	* @param ProfileType		Profile to delete all saves from.
	* @param Event / Delegate	Event to call when the Delete All action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnDeleteAll", AutoCreateRefTerm = "ProfileType"))
	static void BindToEvent_OnDeleteAll(const ECsPlayerProfile& ProfileType, UPARAM(DisplayName = "Event") FCsLibraryManagerSave_OnDeleteAll Delegate);

	/**
	* Delete all saves for all profiles.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save")
	static void DeleteAllContent();

#pragma endregion Delete
};