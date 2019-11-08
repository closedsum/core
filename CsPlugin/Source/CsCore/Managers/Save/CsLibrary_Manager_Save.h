// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/CoreUObject/Public/UObject/Object.h"
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"
#include "Managers/Save/CsTypes_Save.h"
#include "CsLibrary_Manager_Save.generated.h"

// Delegates
#pragma region

// Enumerate
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagECsave_OnEnumerate);
// Read
DECLARE_DYNAMIC_DELEGATE_OneParam(FCsLibraryManagECsave_OnRead, const ECsSave&, Save);
// Write
DECLARE_DYNAMIC_DELEGATE_OneParam(FCsLibraryManagECsave_OnWrite, const ECsSave&, Save);
// Progress
//DECLARE_DYNAMIC_DELEGATE_TwoParams(FCsLibraryManagerAchievement_OnProgress, const FECsAchievement&, Achievement, const float&, Progress);

#pragma endregion Delegates


UCLASS()
class CSCORE_API UCsLibrary_Manager_Save : public UObject
{
	GENERATED_UCLASS_BODY()

// Enumerate
#pragma region
public:

	/**
	*
	* @param ProfileType
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (AutoCreateRefTerm = "ProfileType"))
	static void Enumerate(const ECsPlayerProfile& ProfileType);

#pragma endregion Enumerate

// Read
#pragma region
public:

	/**
	*
	* @param ProfileType
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (AutoCreateRefTerm = "ProfileType,Save"))
	static void Read(const ECsPlayerProfile& ProfileType, const ECsSave& Save);

	/**
	*
	* @param ProfileType
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (AutoCreateRefTerm = "ProfileType"))
	static void ReadAll(const ECsPlayerProfile& ProfileType);

#pragma endregion Read

// Write
#pragma region
public:

	/**
	* 
	* @param ProfileType
	* @param Save
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (AutoCreateRefTerm = "ProfileType,Save"))
	static void Write(const ECsPlayerProfile& ProfileType, const ECsSave& Save);

	/**
	*
	* @param Event / Delegate
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (DisplayName = "BindToEvent: OnWriteComplete", AutoCreateRefTerm = "ProfileType,Save"))
	static void BindToEvent_OnWrite(const ECsPlayerProfile& ProfileType, const ECsSave& Save, UPARAM(DisplayName = "Event") FCsLibraryManagECsave_OnWrite Delegate);

	/**
	*
	* @param ProfileType
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (AutoCreateRefTerm = "ProfileType"))
	static void WriteAll(const ECsPlayerProfile& ProfileType);

#pragma endregion Write

// Delete
#pragma region
public:

	/**
	*
	* @param ProfileType
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (AutoCreateRefTerm = "ProfileType,Save"))
	static void Delete(const ECsPlayerProfile& ProfileType, const ECsSave& Save);

	/**
	*
	* @param ProfileType
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save", meta = (AutoCreateRefTerm = "ProfileType"))
	static void DeleteAll(const ECsPlayerProfile& ProfileType);

	/**
	*
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Save")
	static void DeleteAllContent();

#pragma endregion Delete
};