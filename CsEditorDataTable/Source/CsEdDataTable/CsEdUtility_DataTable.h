// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UDataTable;

class CSEDDATATABLE_API FCsEdUtility_DataTable
{
// Delegates
#pragma region
public:
	
	static void BindDelegates();

	// Editor Delegates
#pragma region
public:

	static void OnBeginPIE(bool IsSimulating);
	static void OnEndPIE(bool IsSimulating);

	static void OnAssetsPreDelete(const TArray<UObject*>& Objects);

protected:

	static bool bPIE;

#pragma endregion Editor Delegates

	// Asset Registry Delegates
#pragma region
public:

	static void OnAssetRenamed(const FAssetData& AssetData, const FString& OldObjectPath);
	static void OnAssetRemoved(const FAssetData& AssetData);

#pragma endregion Asset Registry Delegates

	// Asset Editor Manager
#pragma region
public:

	static void OnAssetEditorOpened(UObject* Object);

#pragma endregion Asset Editor Manager

	// Core Delegates
#pragma region

public:

	static void OnObjectSaved(UObject* Object);

	static void OnAssetLoaded(UObject* Object);

#pragma endregion Core Delegates

#pragma endregion Delegates

public:

	/**
	*
	*
	* @param DataTable
	* return
	*/
	static bool ExportToTextFile(UDataTable* DataTable);
	
	/**
	*
	*
	* @param ObjectPath
	* @param OldObjectPath
	*/
	static void OnRenamed(const FName& ObjectPath, const FString& OldObjectPath);

	/**
	*
	*
	* @param ObjectPath
	*/
	static void OnDelete(const FName& ObjectPath);

	/**
	*
	*
	* @param DataTable
	*/
	static void OnOpened(UDataTable* DataTable);

	/**
	*
	*
	* @param DataTable
	*/
	static void OnLoaded(UDataTable* DataTable);

private:

	static void LoadFromTextFile(const FString& Context, UDataTable* DataTable);

	/**
	*
	*
	* @param A
	* @param B
	* return
	*/
	static bool AreContentsEqual(UDataTable* A, UDataTable* B);
};