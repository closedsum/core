// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetDataTable);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetDataTableByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetDataTableBySoftObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, SafeAddDataObject_Loaded);
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

	// DataTable
#pragma region

UDataTable* UCsScriptLibrary_Manager_Data::GetDataTable(const FString& Context, const UObject* WorldContextObject, const FName& TableName)
{
	using namespace NCsScriptLibraryManagerData::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDataTable : Context;

	typedef NCsData::NManager::FLibrary DataManagerLibrary;

	return DataManagerLibrary::GetSafeDataTable(Ctxt, WorldContextObject, TableName);
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

bool UCsScriptLibrary_Manager_Data::SafeAddDataObject_Loaded(const FString& Context, const UObject* WorldContextObject, const FName& EntryName, UObject* Data)
{
	using namespace NCsScriptLibraryManagerData::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SafeAddDataObject_Loaded : Context;

	typedef NCsData::NManager::FLibrary DataManagerLibrary;

	return DataManagerLibrary::SafeAddDataObject_Loaded(Ctxt, WorldContextObject, EntryName, Data);
}

#pragma endregion Data

#pragma endregion Add