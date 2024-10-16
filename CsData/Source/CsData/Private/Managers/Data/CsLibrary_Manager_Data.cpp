// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Data/CsLibrary_Manager_Data.h"

// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Data/CsManager_Data.h"

#if WITH_EDITOR
// Types
#include "CsMacro_Misc.h"
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

			#define USING_NS_CACHED using namespace NCsData::NManager::NLibrary::NCached;
			#define SET_CONTEXT(__FunctionName) using namespace NCsData::NManager::NLibrary::NCached; \
				const FString& Context = Str::__FunctionName
			#define LogLevel void(*Log)(const FString&) /*=&NCsData::FLog::Warning*/

			// ContextRoot
			#pragma region

			#if WITH_EDITOR

			UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
			{
				return CsGameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
			}

			UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, LogLevel)
			{
				return CsGameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
			}

			UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
			{
				SET_CONTEXT(GetSafeContextRoot);

				return GetSafeContextRoot(Context, ContextObject, nullptr);
			}

			#endif // #if WITH_EDITOR

			#pragma endregion ContextRoot

			// Root Set
			#pragma region

			UObject* FLibrary::GetDataRootSetImplChecked(const FString& Context, const UObject* ContextObject)
			{
				return GetChecked(Context, ContextObject)->GetDataRootSetImplChecked(Context);
			}

			UObject* FLibrary::GetSafeDataRootSetImpl(const FString& Context, const UObject* ContextObject, LogLevel)
			{
				if (UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject, Log))
					return Manager_Data->GetSafeDataRootSetImpl(Context, Log);
				return nullptr;
			}

			#pragma endregion Root Set

			// Get
			#pragma region

			UCsManager_Data* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
			{
			#if !UE_BUILD_SHIPPING
				UObject* ContextRoot		  = GetContextRootChecked(Context, ContextObject);
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(ContextRoot);

				CS_IS_PENDING_KILL_CHECKED(Manager_Data)
				return Manager_Data;
			#else
				return UCsManager_Data::Get();
			#endif // #if !UE_BUILD_SHIPPING
			}

			UCsManager_Data* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &NCsPlayback::FLog::Warning*/)
			{
				UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

			#if WITH_EDITOR
				if (!ContextRoot)
					return nullptr;
			#endif // #if WITH_EDITOR

				UCsManager_Data* Manager_Data = UCsManager_Data::Get(ContextRoot);

				if (!CsObjectLibrary::IsValidObject(Manager_Data))
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Data."), *Context));
				}
				return Manager_Data;
			}

			UCsManager_Data* FLibrary::GetSafe(const UObject* ContextObject)
			{
				SET_CONTEXT(GetSafe);

				return GetSafe(Context, ContextObject, nullptr);
			}

				// Data
			#pragma region

			ICsData* FLibrary::GetDataChecked(const FString& Context, const UObject* ContextObject, const FName& EntryName)
			{
				return GetChecked(Context, ContextObject)->GetDataChecked(Context, EntryName);
			}

			ICsData* FLibrary::GetSafeData(const FString& Context, const UObject* ContextObject, const FName& EntryName, LogLevel)
			{
				if (UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject))
				{
					return Manager_Data->GetSafeData(Context, EntryName, Log);
				}
				return nullptr;
			}

			ICsData* FLibrary::GetDataChecked(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path)
			{
				return GetChecked(Context, ContextObject)->GetDataChecked(Context, Path);
			}

			ICsData* FLibrary::GetSafeData(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, LogLevel)
			{
				if (UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject))
				{
					return Manager_Data->GetSafeData(Context, Path, Log);
				}
				return nullptr;
			}

			UObject* FLibrary::GetDataObjectChecked(const FString& Context, const UObject* ContextObject, const FName& EntryName)
			{
				return GetChecked(Context, ContextObject)->GetDataObjectChecked(Context, EntryName);
			}

			UObject* FLibrary::GetSafeDataObject(const FString& Context, const UObject* ContextObject, const FName& EntryName, LogLevel)
			{
				if (UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject))
				{
					return Manager_Data->GetSafeDataObject(Context, EntryName, Log);
				}
				return nullptr;
			}

			UObject* FLibrary::GetDataObjectChecked(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path)
			{
				return GetChecked(Context, ContextObject)->GetDataObjectChecked(Context, Path);
			}

			UObject* FLibrary::GetSafeDataObject(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, LogLevel)
			{
				if (UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject))
				{
					return Manager_Data->GetSafeDataObject(Context, Path, Log);
				}
				return nullptr;
			}

			#pragma endregion Data

				// ScriptData
			#pragma region

			UObject* FLibrary::GetScriptDataObjectChecked(const FString& Context, const UObject* ContextObject, const FName& EntryName)
			{
				return GetChecked(Context, ContextObject)->GetScriptDataObjectChecked(Context, EntryName);
			}

			UObject* FLibrary::GetSafeScriptDataObject(const FString& Context, const UObject* ContextObject, const FName& EntryName, LogLevel)
			{
				if (UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject))
				{
					return Manager_Data->GetSafeScriptDataObject(Context, EntryName, Log);
				}
				return nullptr;
			}

			UObject* FLibrary::GetScriptDataObjectChecked(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path)
			{
				return GetChecked(Context, ContextObject)->GetScriptDataObjectChecked(Context, Path);
			}

			UObject* FLibrary::GetSafeScriptDataObject(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, LogLevel)
			{
				if (UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject))
				{
					return Manager_Data->GetSafeScriptDataObject(Context, Path, Log);
				}
				return nullptr;
			}

			#pragma endregion ScriptData

				// DataTabe
			#pragma region
		
			UDataTable* FLibrary::GetSafeDataTable(const FString& Context, const UObject* ContextObject, const FName& EntryName, LogLevel)
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

			UDataTable* FLibrary::GetSafeDataTable(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, LogLevel)
			{
				UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject, Log);

				if (!Manager_Data)
					return nullptr;

				CS_IS_SOFT_OBJECT_PATH_VALID_RET_NULL(Path)

				return Manager_Data->GetDataTable(Path);
			}

			UDataTable* FLibrary::GetSafeDataTable(const UObject* ContextObject, const FSoftObjectPath& Path)
			{
				SET_CONTEXT(GetSafeDataTable);

				return GetSafeDataTable(Context, ContextObject, Path, nullptr);
			}

			UDataTable* FLibrary::GetDataTableChecked(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject)
			{
				return GetChecked(Context, ContextObject)->GetDataTableChecked(Context, SoftObject);
			}

			UDataTable* FLibrary::GetSafeDataTable(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject, LogLevel)
			{
				UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject, Log);

				if (!Manager_Data)
					return nullptr;

				CS_IS_SOFT_OBJECT_PTR_VALID_RET_NULL(SoftObject, UDataTable)

				return Manager_Data->GetDataTable(SoftObject);
			}

			UDataTable* FLibrary::GetSafeDataTable(const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject)
			{
				SET_CONTEXT(GetSafeDataTable);

				return GetSafeDataTable(Context, ContextObject, SoftObject, nullptr);
			}

			uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, const FName& RowName)
			{
				return GetChecked(Context, ContextObject)->GetDataTableRowChecked(Context, Path, RowName);
			}

			uint8* FLibrary::GetSafeDataTableRow(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, const FName& RowName, LogLevel)
			{
				UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject, Log);

				if (!Manager_Data)
					return nullptr;

				return Manager_Data->GetSafeDataTableRow(Context, Path, RowName, Log);
			}

			uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject, const FName& RowName)
			{
				return GetChecked(Context, ContextObject)->GetDataTableRowChecked(Context, SoftObject, RowName);
			}

			uint8* FLibrary::GetSafeDataTableRow(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject, const FName& RowName, LogLevel)
			{
				UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject, Log);

				if (!Manager_Data)
					return nullptr;

				return Manager_Data->GetSafeDataTableRow(Context, SoftObject, RowName, Log);
			}

			uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject, const UScriptStruct* RowStruct, const FName& RowName)
			{
				return GetChecked(Context, ContextObject)->GetDataTableRowChecked(Context, SoftObject, RowStruct, RowName);
			}

			FName FLibrary::DataTable_GetEntryNameChecked(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject)
			{
				return GetChecked(Context, ContextObject)->DataTable_GetEntryNameChecked(Context, SoftObject);
			}

			#pragma endregion DataTable

			#pragma endregion Get

			// Maps
			#pragma region
		
				// Payload
			#pragma region

			bool FLibrary::DoesPayloadContainChecked(const FString& Context, const UObject* ContextObject, const FName& PayloadName, const TSoftObjectPtr<UDataTable>& DataTable)
			{
				return GetChecked(Context, ContextObject)->DoesPayloadContain(PayloadName, DataTable);
			}
		
			#pragma endregion Payload

			#pragma endregion Maps

			// Add
			#pragma region

				// Data
			#pragma region

			bool FLibrary::SafeAddDataObject_Loaded(const FString& Context, const UObject* ContextObject, const FName& EntryName, UObject* Data, LogLevel)
			{
				UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject, Log);

				if (!Manager_Data)
					return false;

				return Manager_Data->SafeAddDataObject_Loaded(Context, EntryName, Data, Log);
			}

			void FLibrary::AddDataCompositionObject_Loaded_Checked(const FString& Context, const UObject* ContextObject, const FName& DataName, UObject* Data, const FName& SliceName)
			{
				GetChecked(Context, ContextObject)->AddDataCompositionObject_Loaded(DataName, Data, SliceName);
			}

			bool FLibrary::SafeRemoveDataCompositionObject_Loaded(const FString& Context, const UObject* ContextObject, const FName& DataName, LogLevel)
			{
				UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject, Log);

				if (!Manager_Data)
					return false;

				return Manager_Data->SafeRemoveDataCompositionObject_Loaded(Context, DataName, Log);
			}

			#pragma endregion Data

				// Payload
			#pragma region
		
			void FLibrary::AddPayloadChecked(const FString& Context, const UObject* ContextRoot, const FName& PayloadName, const FCsPayload* Payload)
			{
				CS_IS_PTR_NULL_CHECKED(Payload)

				GetChecked(Context, ContextRoot)->AddPayload(PayloadName, *Payload);
			}

			#pragma endregion Payload

			#pragma endregion Add

			// Load
			#pragma region
		
				// Payload
			#pragma region

			OnAsyncLoadPayloadCompletePersistentType& FLibrary::GetOnAsyncLoadPayloadComplete_Persistent_EventChecked(const FString& Context, const UObject* ContextObject)
			{
				return GetChecked(Context, ContextObject)->GetOnAsyncLoadPayloadCompleted_Persistent_Event();
			}

			void FLibrary::AsyncLoadPayloadChecked(const FString& Context, const UObject* ContextObject, const FName& PayloadName, OnAsyncLoadPayloadCompleteOnceType Delegate)
			{
				GetChecked(Context, ContextObject)->AsyncLoadPayload(PayloadName, Delegate);
			}

			void FLibrary::AsyncAddAndLoadPayloadChecked(const FString& Context, const UObject* ContextObject, const FName& PayloadName, const FCsPayload* Payload, OnAsyncLoadPayloadCompleteOnceType Delegate)
			{
				CS_IS_PTR_NULL_CHECKED(Payload)

				GetChecked(Context, ContextObject)->AddPayload(PayloadName, *Payload);
				GetChecked(Context, ContextObject)->AsyncLoadPayload(PayloadName, Delegate);
			}

			void FLibrary::AsyncLoadStartupPayloadChecked(const FString& Context, const UObject* ContextObject, OnAsyncLoadPayloadCompleteOnceType Delegate)
			{
				GetChecked(Context, ContextObject)->AsyncLoadStartupPayload(Delegate);
			}

			bool FLibrary::SafeAsyncLoadStartupPayload(const FString& Context, const UObject* ContextObject, OnAsyncLoadPayloadCompleteOnceType Delegate, LogLevel)
			{
				if (UCsManager_Data* Manager_Data = GetSafe(Context, ContextObject, Log))
					return Manager_Data->SafeAsyncLoadStartupPaylod(Context, Delegate, Log);
				return false;
			}

			void FLibrary::AsyncLoadPayloadsChecked(const FString& Context, const UObject* ContextObject, const TArray<FName>& PayloadNames, OnAsyncLoadPayloadsCompleteOnceType Delegate)
			{
				GetChecked(Context, ContextObject)->AsyncLoadPayloads(PayloadNames, Delegate);
			}

			void FLibrary::UnloadPayloadChecked(const FString& Context, const UObject* ContextObject, const FName& PayloadName)
			{
				GetChecked(Context, ContextObject)->UnloadPayload(PayloadName);
			}

			#pragma endregion Payload
			
			#pragma endregion Load

			#undef USING_NS_CACHED
			#undef SET_CONTEXT
			#undef LogLevel
		}
	}
}