// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"
#include "Managers/Save/CsTypes_Save.h"

#include "CsScriptLibrary_Manager_Save.generated.h"

// Delegates
#pragma region

// Enumerate
DECLARE_DYNAMIC_DELEGATE_OneParam(FCsScriptLibraryManagerSave_OnEnumerate, bool, WasSuccessful);
// Read
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCsScriptLibraryManagerSave_OnRead, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
DECLARE_DYNAMIC_DELEGATE(FCsScriptLibraryManagerSave_OnReadAll);
// Write
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCsScriptLibraryManagerSave_OnWrite, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
DECLARE_DYNAMIC_DELEGATE(FCsScriptLibraryManagerSave_OnWriteAll);
// Delete
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCsScriptLibraryManagerSave_OnDelete, bool, WasSuccessful, const ECsPlayerProfile&, Profile, const ECsSave&, Save);
DECLARE_DYNAMIC_DELEGATE(FCsScriptLibraryManagerSave_OnDeleteAll);

#pragma endregion Delegates


UCLASS()
class CSPLATFORMSERVICES_API UCsScriptLibrary_Manager_Save : public UObject
{
	GENERATED_UCLASS_BODY()

// FileName
#pragma region
public:

	/**
	* Set the current save (slot).
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Save					Save (slot) to set as the current save.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Save"))
	static void SetCurrentSave(const FString& Context, UObject* WorldContextObject, const ECsSave& Save);

#pragma endregion FileName

// Enumerate
#pragma region
public:

	/**
	* Get a list of all save filenames for specified profile.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void Enumerate(const FString& Context, UObject* WorldContextObject);

	/**
	* Bind to the event when the Enumerate action has completed.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event / Delegate	Event to call when Enumerate action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnEnumerate", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void BindToEvent_OnEnumerate(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsScriptLibraryManagerSave_OnEnumerate Delegate);

#pragma endregion Enumerate

// Read
#pragma region
public:

	/**
	* Read a save for a specified profile and Save (slot)
	* 
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to read save from.
	* @param Save					Save (slot) to read from.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Profile,Save"))
	static void Read(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save);

	/**
	* Bind to the event when the Read action has completed.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to read save from.
	* @param Event / Delegate		Event to call when the Read action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnRead", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Profile"))
	static void BindToEvent_OnRead(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsScriptLibraryManagerSave_OnRead Delegate);

	/**
	* Read all saves for a specified profile.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to read all saves from.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Profile"))
	static void ReadAll(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile);

	/**
	* Bind to the event when the Read All action has completed.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event / Delegate		Event to call when the Read All action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnReadAll", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void BindToEvent_OnReadAll(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsScriptLibraryManagerSave_OnReadAll Delegate);

#pragma endregion Read

// Write
#pragma region
public:

	/**
	* Write a save for a specified profile and Save (slot). 
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to write save to.
	* @param Save					Save (slot) to write to.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Profile,Save"))
	static void Write(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save);

	/**
	* Bind to the event when the Write action has completed.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event / Delegate		Event to call when the Write action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnWrite", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void BindToEvent_OnWrite(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsScriptLibraryManagerSave_OnWrite Delegate);

	/**
	* Write all saves for a specified profile.
	* 
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to write all saves to.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Profile"))
	static void WriteAll(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile);

	/**
	* Bind to the event when the Write All action has completed.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event / Delegate		Event to call when the Write All action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnWriteAll", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void BindToEvent_OnWriteAll(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsScriptLibraryManagerSave_OnWriteAll Delegate);

#pragma endregion Write

// Delete
#pragma region
public:

	/**
	* Delete a save for a specified profile and Save (slot).
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to delete save from.
	* @param Save					Save (slot) to delete.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Profile,Save"))
	static void Delete(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save);

	/**
	* Bind to the event when the Delete action has completed.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event / Delegate		Event to call when the Delete action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnDelete", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void BindToEvent_OnDelete(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsScriptLibraryManagerSave_OnDelete Delegate);


	/**
	* Delete all saves for a specified profile.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to delete all saves from.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Profile"))
	static void DeleteAll(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile);

	/**
	* Bind to the event when the Delete All action has completed.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event / Delegate		Event to call when the Delete All action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnDeleteAll", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void BindToEvent_OnDeleteAll(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsScriptLibraryManagerSave_OnDeleteAll Delegate);

	/**
	* Delete all saves for all profiles.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void DeleteAllContent(const FString& Context, UObject* WorldContextObject);

#pragma endregion Delete
};