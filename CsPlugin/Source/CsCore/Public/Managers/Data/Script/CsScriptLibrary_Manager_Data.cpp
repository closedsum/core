// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Data/Script/CsScriptLibrary_Manager_Data.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Managers/Data/CsLibrary_Manager_Data.h"

// Cached
#pragma region

namespace NCsScriptLibraryManagerData
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetDataObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetDataObjectByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetDataTable);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetDataTableByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetDataTableBySoftObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, AddDataObject_Loaded);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, RemoveDataCompositionObject_Loaded);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Data::UCsScriptLibrary_Manager_Data(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Get
#pragma region

	// Data
#pragma region

UObject* UCsScriptLibrary_Manager_Data::GetDataObject(const FString& Context, const UObject* WorldContextObject, const FName& EntryName)
{
	using namespace NCsScriptLibraryManagerData::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDataObject : Context;

	typedef NCsData::NManager::FLibrary DataManagerLibrary;

	return DataManagerLibrary::GetSafeDataObject(Ctxt, WorldContextObject, EntryName);
}

UObject* UCsScriptLibrary_Manager_Data::GetDataObjectByPath(const FString& Context, const UObject* WorldContextObject, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryManagerData::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDataObjectByPath : Context;

	typedef NCsData::NManager::FLibrary DataManagerLibrary;

	return DataManagerLibrary::GetSafeDataObject(Ctxt, WorldContextObject, Path);
}

#pragma endregion Data

	// DataTable
#pragma region

UDataTable* UCsScriptLibrary_Manager_Data::GetDataTable(const FString& Context, const UObject* WorldContextObject, const FName& EntryName)
{
	using namespace NCsScriptLibraryManagerData::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDataTable : Context;

	typedef NCsData::NManager::FLibrary DataManagerLibrary;

	return DataManagerLibrary::GetSafeDataTable(Ctxt, WorldContextObject, EntryName);
}

UDataTable* UCsScriptLibrary_Manager_Data::GetDataTableByPath(const FString& Context, const UObject* WorldContextObject, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryManagerData::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDataTableByPath : Context;

	typedef NCsData::NManager::FLibrary DataManagerLibrary;

	return DataManagerLibrary::GetSafeDataTable(Ctxt, WorldContextObject, Path);
}

UDataTable* UCsScriptLibrary_Manager_Data::GetDataTableBySoftObject(const FString& Context, const UObject* WorldContextObject, TSoftObjectPtr<UDataTable> SoftObject)
{
	using namespace NCsScriptLibraryManagerData::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDataTableBySoftObject : Context;

	typedef NCsData::NManager::FLibrary DataManagerLibrary;

	return DataManagerLibrary::GetSafeDataTable(Ctxt, WorldContextObject, SoftObject);
}

#pragma endregion DataTable

#pragma endregion Get

// Add
#pragma region

	// Data
#pragma region

bool UCsScriptLibrary_Manager_Data::AddDataObject_Loaded(const FString& Context, const UObject* WorldContextObject, const FName& EntryName, UObject* Data)
{
	using namespace NCsScriptLibraryManagerData::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddDataObject_Loaded : Context;

	typedef NCsData::NManager::FLibrary DataManagerLibrary;

	return DataManagerLibrary::SafeAddDataObject_Loaded(Ctxt, WorldContextObject, EntryName, Data);
}

bool UCsScriptLibrary_Manager_Data::RemoveDataCompositionObject_Loaded(const FString& Context, const UObject* WorldContextObject, const FName& DataName)
{
	using namespace NCsScriptLibraryManagerData::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::RemoveDataCompositionObject_Loaded : Context;

	typedef NCsData::NManager::FLibrary DataManagerLibrary;

	return DataManagerLibrary::SafeRemoveDataCompositionObject_Loaded(Ctxt, WorldContextObject, DataName);
}

#pragma endregion Data

#pragma endregion Add