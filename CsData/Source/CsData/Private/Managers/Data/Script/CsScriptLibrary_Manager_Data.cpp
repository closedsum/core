// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Data/Script/CsScriptLibrary_Manager_Data.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Data/CsLibrary_Manager_Data.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_Data)

// Cached
#pragma region

namespace NCsScriptLibraryManagerData
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetDataObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetDataObjectByPath);
				// Script
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetScriptDataObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetScriptDataObjectChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetScriptDataObjectByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetScriptDataObjectByPathChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetDataTable);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetDataTableByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Data, GetDataTableBySoftObject);
			// Add
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

#define USING_NS_CACHED using namespace NCsScriptLibraryManagerData::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerData::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// Get
#pragma region

	// Data
#pragma region

UObject* UCsScriptLibrary_Manager_Data::GetDataObject(const FString& Context, const UObject* WorldContextObject, const FName& EntryName)
{
	CONDITIONAL_SET_CTXT(GetDataObject);

	return CsDataManagerLibrary::GetSafeDataObject(Ctxt, WorldContextObject, EntryName);
}

UObject* UCsScriptLibrary_Manager_Data::GetDataObjectByPath(const FString& Context, const UObject* WorldContextObject, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(GetDataObjectByPath);

	return CsDataManagerLibrary::GetSafeDataObject(Ctxt, WorldContextObject, Path);
}

#pragma endregion Data

	// ScriptData
#pragma region

UObject* UCsScriptLibrary_Manager_Data::GetScriptDataObject(const FString& Context, const UObject* WorldContextObject, const FName& EntryName)
{
	CONDITIONAL_SET_CTXT(GetScriptDataObject);

	return CsDataManagerLibrary::GetSafeScriptDataObject(Ctxt, WorldContextObject, EntryName);
}

UObject* UCsScriptLibrary_Manager_Data::GetScriptDataObjectChecked(const FString& Context, const UObject* WorldContextObject, const FName& EntryName, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetScriptDataObjectChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsDataManagerLibrary::GetScriptDataObjectChecked(Ctxt, WorldContextObject, EntryName), CsDataManagerLibrary::GetSafeScriptDataObject(Ctxt, WorldContextObject, EntryName, OutSuccess));
}

UObject* UCsScriptLibrary_Manager_Data::GetScriptDataObjectByPath(const FString& Context, const UObject* WorldContextObject, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(GetScriptDataObjectByPath);

	return CsDataManagerLibrary::GetSafeScriptDataObject(Ctxt, WorldContextObject, Path);
}

UObject* UCsScriptLibrary_Manager_Data::GetScriptDataObjectByPathChecked(const FString& Context, const UObject* WorldContextObject, const FSoftObjectPath& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetScriptDataObjectByPathChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsDataManagerLibrary::GetScriptDataObjectChecked(Ctxt, WorldContextObject, Path), CsDataManagerLibrary::GetSafeScriptDataObject(Ctxt, WorldContextObject, Path, OutSuccess));
}

#pragma endregion ScriptData

	// DataTable
#pragma region

UDataTable* UCsScriptLibrary_Manager_Data::GetDataTable(const FString& Context, const UObject* WorldContextObject, const FName& EntryName)
{
	CONDITIONAL_SET_CTXT(GetDataTable);

	return CsDataManagerLibrary::GetSafeDataTable(Ctxt, WorldContextObject, EntryName);
}

UDataTable* UCsScriptLibrary_Manager_Data::GetDataTableByPath(const FString& Context, const UObject* WorldContextObject, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(GetDataTableByPath);

	return CsDataManagerLibrary::GetSafeDataTable(Ctxt, WorldContextObject, Path);
}

UDataTable* UCsScriptLibrary_Manager_Data::GetDataTableBySoftObject(const FString& Context, const UObject* WorldContextObject, TSoftObjectPtr<UDataTable> SoftObject)
{
	CONDITIONAL_SET_CTXT(GetDataTableBySoftObject);

	return CsDataManagerLibrary::GetSafeDataTable(Ctxt, WorldContextObject, SoftObject);
}

#pragma endregion DataTable

#pragma endregion Get

// Add
#pragma region

	// Data
#pragma region

bool UCsScriptLibrary_Manager_Data::AddDataObject_Loaded(const FString& Context, const UObject* WorldContextObject, const FName& EntryName, UObject* Data)
{
	CONDITIONAL_SET_CTXT(AddDataObject_Loaded);

	return CsDataManagerLibrary::SafeAddDataObject_Loaded(Ctxt, WorldContextObject, EntryName, Data);
}

bool UCsScriptLibrary_Manager_Data::RemoveDataCompositionObject_Loaded(const FString& Context, const UObject* WorldContextObject, const FName& DataName)
{
	CONDITIONAL_SET_CTXT(RemoveDataCompositionObject_Loaded);;

	return CsDataManagerLibrary::SafeRemoveDataCompositionObject_Loaded(Ctxt, WorldContextObject, DataName);
}

#pragma endregion Data

#pragma endregion Add

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT