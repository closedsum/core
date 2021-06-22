// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Data/CsLibrary_Manager_Data.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Data/CsManager_Data.h"

#if WITH_EDITOR
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
#endif // #if WITH_EDITOR

namespace NCsData
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsData::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsData::NManager::FLibrary, GetSafe);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsData::NManager::FLibrary, GetSafeDataTable);
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString& Context) /*=&FCsLog::Warning*/)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			using namespace NCsData::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Data* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot		  = GetContextRootChecked(Context, ContextObject);
			UCsManager_Data* Manager_Data = UCsManager_Data::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Data)
			return Manager_Data;
		}

		UCsManager_Data* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &NCsPlayback::FLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Data* Manager_Data = UCsManager_Data::Get(ContextRoot);

			if (!Manager_Data)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Data."), *Context));
			}
			return Manager_Data;
		}

		UCsManager_Data* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsData::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		// Add
		#pragma region

			// Data
		#pragma region

		bool FLibrary::SafeAddDataObject_Loaded(const FString& Context, const UObject* ContextObject, const FName& EntryName, UObject* Data, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject, Log);

			if (!Manager_Data)
				return false;

			return Manager_Data->SafeAddDataObject_Loaded(Context, EntryName, Data, Log);
		}

		void FLibrary::AddDataCompositionObject_Loaded_Checked(const FString& Context, const UObject* ContextObject, UObject* Data)
		{
			GetChecked(Context, ContextObject)->AddDataCompositionObject_Loaded(Data);
		}

		#pragma endregion Data

		#pragma endregion Add

		// DataTabe
		#pragma region
		
		UDataTable* FLibrary::GetSafeDataTable(const FString& Context, const UObject* ContextObject, const FName& EntryName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject, Log);

			if (!Manager_Data)
				return nullptr;

			CS_IS_NAME_NONE_RET_NULL(EntryName)

			return Manager_Data->GetDataTable(EntryName);
		}

		UDataTable* FLibrary::GetDataTableChecked(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path)
		{
			return GetChecked(Context, ContextObject)->GetDataTableChecked(Context, Path);
		}

		UDataTable* FLibrary::GetSafeDataTable(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject, Log);

			if (!Manager_Data)
				return nullptr;

			CS_IS_SOFT_OBJECT_PATH_VALID_RET_NULL(Path)

			return Manager_Data->GetDataTable(Path);
		}

		UDataTable* FLibrary::GetSafeDataTable(const UObject* ContextObject, const FSoftObjectPath& Path)
		{
			using namespace NCsData::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeDataTable;

			return GetSafeDataTable(Context, ContextObject, Path, nullptr);
		}

		UDataTable* FLibrary::GetDataTableChecked(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject)
		{
			return GetChecked(Context, ContextObject)->GetDataTableChecked(Context, SoftObject);
		}

		UDataTable* FLibrary::GetSafeDataTable(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject, Log);

			if (!Manager_Data)
				return nullptr;

			const FSoftObjectPath& Path = SoftObject.ToSoftObjectPath();

			if (!Path.IsValid())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: SoftObject is NOT Valid."), *Context));
				return nullptr;
			}
		
			return Manager_Data->GetDataTable(SoftObject);
		}

		UDataTable* FLibrary::GetSafeDataTable(const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject)
		{
			using namespace NCsData::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeDataTable;

			return GetSafeDataTable(Context, ContextObject, SoftObject, nullptr);
		}

		#pragma endregion DataTable
	}
}