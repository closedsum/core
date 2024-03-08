// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Save/CsManager_Save_Delegates.h"

#include "CsScriptLibrary_Manager_Save.generated.h"

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
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Save"))
	static bool SetCurrentSave(const FString& Context, UObject* WorldContextObject, const ECsSave& Save);

	/**
	* Set the current save (slot).
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Save					Save (slot) to set as the current save.
	* @param OutSuccess				(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (DisplayName = "Set Current Save (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Save"))
	static void SetCurrentSaveChecked(const FString& Context, UObject* WorldContextObject, const ECsSave& Save, bool& OutSuccess);

#pragma endregion FileName

// Enumerate
#pragma region
public:

	/**
	* Get a list of all save filenames for specified profile.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static bool Enumerate(const FString& Context, UObject* WorldContextObject);

	/**
	* Get a list of all save filenames for specified profile.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess				(out)
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (DisplayName = "Enumerate (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static void EnumerateChecked(const FString& Context, UObject* WorldContextObject, bool& OutSuccess);

	/**
	* Bind to the event when the Enumerate action has completed.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event / Delegate	Event to call when Enumerate action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnEnumerate", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static void BindToEvent_OnEnumerate(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsManagerSave_ScriptPassable_OnEnumerate Delegate);

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
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Profile,Save"))
	static bool Read(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save);

	/**
	* Read a save for a specified profile and Save (slot)
	* 
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to read save from.
	* @param Save					Save (slot) to read from.
	* @param OutSuccess				(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Profile,Save"))
	static void ReadChecked(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, bool& OutSuccess);


	/**
	* Bind to the event when the Read action has completed.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to read save from.
	* @param Event / Delegate		Event to call when the Read action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnRead", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Profile"))
	static void BindToEvent_OnRead(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsManagerSave_ScriptPassable_OnRead Delegate);

	/**
	* Read all saves for a specified profile.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to read all saves from.
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Profile"))
	static bool ReadAll(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile);

	/**
	* Read all saves for a specified profile.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to read all saves from.
	* @param OutSuccess				(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (DisplayName = "Read All (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Profile"))
	static void ReadAllChecked(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, bool& OutSuccess);

	/**
	* Bind to the event when the Read All action has completed.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event / Delegate		Event to call when the Read All action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnReadAll", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static void BindToEvent_OnReadAll(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsManagerSave_ScriptPassable_OnReadAll Delegate);

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
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Profile,Save"))
	static bool Write(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save);

	/**
	* Write a save for a specified profile and Save (slot). 
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to write save to.
	* @param Save					Save (slot) to write to.
	* @param OutSuccess				(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (DisplayName = "Write (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Profile,Save"))
	static void WriteChecked(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, bool& OutSuccess);

	/**
	* Bind to the event when the Write action has completed.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event / Delegate		Event to call when the Write action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnWrite", CallableWithoutWorldContext, WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void BindToEvent_OnWrite(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsManagerSave_ScriptPassable_OnWrite Delegate);

	/**
	* Write all saves for a specified profile.
	* 
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to write all saves to.
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Profile"))
	static bool WriteAll(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile);

	/**
	* Write all saves for a specified profile.
	* 
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to write all saves to.
	* @param OutSuccess				(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (DisplayName = "Write All (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Profile"))
	static void WriteAllChecked(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, bool& OutSuccess);

	/**
	* Bind to the event when the Write All action has completed.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event / Delegate		Event to call when the Write All action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnWriteAll", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static void BindToEvent_OnWriteAll(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsManagerSave_ScriptPassable_OnWriteAll Delegate);

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
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Profile,Save"))
	static bool Delete(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save);

	/**
	* Delete a save for a specified profile and Save (slot).
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to delete save from.
	* @param Save					Save (slot) to delete.
	* @param OutSuccess				(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (DisplayName = "Delete (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Profile,Save"))
	static void DeleteChecked(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, bool& OutSuccess);

	/**
	* Bind to the event when the Delete action has completed.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event / Delegate		Event to call when the Delete action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnDelete", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static void BindToEvent_OnDelete(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsManagerSave_ScriptPassable_OnDelete Delegate);


	/**
	* Delete all saves for a specified profile.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to delete all saves from.
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Profile"))
	static bool DeleteAll(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile);

	/**
	* Delete all saves for a specified profile.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Profile				Profile to delete all saves from.
	* @param OutSuccess				(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (DisplayName = "Delete All (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Profile"))
	static void DeleteAllChecked(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& Profile, bool& OutSuccess);

	/**
	* Bind to the event when the Delete All action has completed.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event / Delegate		Event to call when the Delete All action has completed.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnDeleteAll", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static void BindToEvent_OnDeleteAll(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsManagerSave_ScriptPassable_OnDeleteAll Delegate);

	/**
	* Delete all saves for all profiles.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static bool DeleteAllContent(const FString& Context, UObject* WorldContextObject);

	/**
	* Delete all saves for all profiles.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess				(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Save", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static void DeleteAllContentChecked(const FString& Context, UObject* WorldContextObject, bool& OutSuccess);

#pragma endregion Delete
};