// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Data/CsManager_Data_Delegates.h"
// Log
#include "Utility/CsDataLog.h"

class UObject;
class UCsManager_Data;
class ICsData;
class UDataTable;
class UScriptStruct;
struct FCsPayload;

namespace NCsData
{
	namespace NManager
	{
		namespace NLibrary
		{
			using OnAsyncLoadPayloadCompleteOnceType = NCsData::NManager::NOnce::FOnAsyncLoadPayloadComplete;
			using OnAsyncLoadPayloadsCompleteOnceType = NCsData::NManager::NOnce::FOnAsyncLoadPayloadsComplete;
			using OnAsyncLoadPayloadCompletePersistentType = NCsData::NManager::NPersistent::FOnAsyncLoadPayloadComplete;

			struct CSDATA_API FLibrary final
			{
			#define LogLevel void(*Log)(const FString&) = &NCsData::FLog::Warning

			// ContextRoot
			#pragma region

			public:

			#if WITH_EDITOR
				/**
				* Get the Context (Root) for UCsManager_Data from a WorldContext.
				*
				* @param Context		The calling context.
				* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
				*						or
				*						A reference to the GameInstance.
				* return				Context for UCsManager_Data
				*/
				static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject);
			#else
				FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject) { return nullptr; }
			#endif // #if WITH_EDITOR

			#if WITH_EDITOR
				/**
				* Safely get the Context (Root) for UCsManager_Data from a WorldContext.
				*
				* @param Context		The calling context.
				* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
				*						or
				*						A reference to the GameInstance.
				* @param Log
				* return				Context for UCsManager_Data
				*/
				static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, LogLevel);
			#else
				FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, LogLevel) { return nullptr; }
			#endif // #if WITH_EDITOR

			#if WITH_EDITOR
				/**
				* Get the Context (Root) for UCsManager_Data from a WorldContext.
				*
				* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
				*						or
				*						A reference to the GameInstance.
				* return				Context for UCsManager_Data
				*/
				static UObject* GetSafeContextRoot(const UObject* ContextObject);
			#else
				FORCEINLINE static UObject* GetSafeContextRoot(const UObject* ContextObject) { return nullptr; }
			#endif // #if WITH_EDITOR

			#pragma endregion ContextRoot

			// Root Set
			#pragma region
			public:

				static UObject* GetDataRootSetImplChecked(const FString& Context, const UObject* ContextObject);

				static UObject* GetSafeDataRootSetImpl(const FString& Context, const UObject* ContextObject, LogLevel);

			#pragma endregion Root Set

			// Get
			#pragma region
			public:

				/**
				* Get the reference to UCsManager_Data from a ContextObject.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* return				UCsManager_Time.
				*/
				static UCsManager_Data* GetChecked(const FString& Context, const UObject* ContextObject);

				/**
				* Safely get the reference to UCsManager_Data from a ContextObject.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Log			(optional)
				* return				UCsManager_Data.
				*/
				static UCsManager_Data* GetSafe(const FString& Context, const UObject* ContextObject, LogLevel);

				/**
				* Safely get the reference to UCsManager_Data from a ContextObject.
				*
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* return				UCsManager_Data.
				*/
				static UCsManager_Data* GetSafe(const UObject* ContextObject);

				// Data
			#pragma region
			public:

				/**
				* Get Data by the Data's Entry Name
				* (Row Name in the master Data list).
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param EntryName		Row Name in the master Data list.
				* return				Data
				*/
				static ICsData* GetDataChecked(const FString& Context, const UObject* ContextObject, const FName& EntryName);
			
				/**
				* Safely get Data by the Data's Entry Name
				* (Row Name in the master Data list).
				*
				* @param EntryName		Row Name in the master Data list.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Log			(optional)
				* return				Data
				*/
				static ICsData* GetSafeData(const FString& Context, const UObject* ContextObject, const FName& EntryName, LogLevel);

				/**
				* Get a Data by SoftObjectPath.
				* Check against the current loaded datas.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Path			Soft path to a data.
				* return				Data
				*/
				static ICsData* GetDataChecked(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path);

				/**
				* Safely get a Data by SoftObjectPath.
				* Check against the current loaded datas.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Path			Soft path to a data.
				* @param Log			(optional)
				* return				Data
				*/
				static ICsData* GetSafeData(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, LogLevel);

				/**
				* Get a Data by the Data's Entry Name.
				* Check against the current loaded datas.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param EntryName		Row Name in the master Data list.
				* return				Data as UObject.
				*/
				static UObject* GetDataObjectChecked(const FString& Context, const UObject* ContextObject, const FName& EntryName);

				/**
				* Safely get a Data by SoftObjectPath.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param EntryName		Row Name in the master Data list.
				* @param Log			(optional)
				* return				Data as UObject.
				*/
				static UObject* GetSafeDataObject(const FString& Context, const UObject* ContextObject, const FName& EntryName, LogLevel);

				/**
				* Get a Data by SoftObjectPath.
				* Check against the current loaded datas.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Path			Soft path to a data.
				* return
				*/
				static UObject* GetDataObjectChecked(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path);

				/**
				* Get a Data by SoftObjectPath.
				* Check against the current loaded datas.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Path			Soft path to a data.
				* @param Log			(optional)
				* return
				*/
				static UObject* GetSafeDataObject(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, LogLevel);

			#pragma endregion Data

				// ScriptData
			#pragma region
			public:

				/**
				* Get a Script Data by the Data's Entry Name.
				* Check against the current loaded datas.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param EntryName		Row Name in the master Script Data list.
				* return				Script Data as UObject.
				*/
				static UObject* GetScriptDataObjectChecked(const FString& Context, const UObject* ContextObject, const FName& EntryName);

				/**
				* Safely get a Script Data by SoftObjectPath.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param EntryName		Row Name in the master Script Data list.
				* @param Log			(optional)
				* return				Script Data as UObject.
				*/
				static UObject* GetSafeScriptDataObject(const FString& Context, const UObject* ContextObject, const FName& EntryName, LogLevel);
				FORCEINLINE static UObject* GetSafeScriptDataObject(const FString& Context, const UObject* ContextObject, const FName& EntryName, bool& OutSuccess, LogLevel)
				{
					UObject* Object = GetSafeScriptDataObject(Context, ContextObject, EntryName, Log);
					OutSuccess		= Object != nullptr;
					return Object;
				}

				/**
				* Get a Script Data by SoftObjectPath.
				* Check against the current loaded datas.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Path			Soft path to a Script Data.
				* return
				*/
				static UObject* GetScriptDataObjectChecked(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path);

				/**
				* Get a Script Data by SoftObjectPath.
				* Check against the current loaded datas.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Path			Soft path to a Script Data.
				* @param Log			(optional)
				* return
				*/
				static UObject* GetSafeScriptDataObject(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, LogLevel);
				FORCEINLINE static UObject* GetSafeScriptDataObject(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, bool& OutSuccess, LogLevel)
				{
					UObject* Object = GetSafeScriptDataObject(Context, ContextObject, Path, Log);
					OutSuccess		= Object != nullptr;
					return Object;
				}

			#pragma endregion ScriptData

				// DataTabe
			#pragma region
			public:

				/**
				* Safely get a DataTable by EntryName.
				* Check against the current loaded data tables.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param EntryName		Row Name in the master DataTable list.
				* @param Log			(optional)
				* return				DataTable
				*/
				static UDataTable* GetSafeDataTable(const FString& Context, const UObject* ContextObject, const FName& EntryName, LogLevel);

				/**
				* Get a DataTable by SoftObjectPath.
				* Check against the current loaded data tables.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Path			Soft path to a data table.
				* return				DataTable
				*/
				static UDataTable* GetDataTableChecked(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path);

				/**
				* Safely get a DataTable by SoftObjectPath.
				* Check against the current loaded data tables.
				*
				* @param Context	The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Path		Soft path to a data table.
				* @param Log		(optional)
				* return			DataTable
				*/
				static UDataTable* GetSafeDataTable(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, LogLevel);

				/**
				* Safely get a DataTable by SoftObjectPath.
				* Check against the current loaded data tables.
				*
				* @param Context	The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Path		Soft path to a data table.
				* @param Log			(optional)
				* return				DataTable
				*/
				static UDataTable* GetSafeDataTable(const UObject* ContextObject, const FSoftObjectPath& Path);

				/**
				* Get a DataTable by SoftObjectPtr.
				* Check against the current loaded data tables.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param SoftObject		Soft reference to a data table.
				* return				DataTable
				*/
				static UDataTable* GetDataTableChecked(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject);

				/**
				* Safely get a DataTable by SoftObjectPtr.
				* Check against the current loaded data tables.
				*
				* @param Context	The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param SoftObject		Soft reference to a data table.
				* @param Log			(optional)
				* return				DataTable
				*/
				static UDataTable* GetSafeDataTable(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject, LogLevel);

				/**
				* Safely get a DataTable associated with the SoftObject.
				* Check against the current loaded data tables.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param SoftObject		Soft reference to a data table.
				* @param Log			(optional)
				* return				DataTable
				*/
				static UDataTable* GetSafeDataTable(const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject);

				/**
				* Get a pointer to the Row with name: Row Name in a DataTable associated with Path.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Path			Soft Path to the DataTable.
				* @param RowName		Row Name in the retrieved DataTable.
				* return				Pointer to the Row.
				*/
				static uint8* GetDataTableRowChecked(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, const FName& RowName);

				/**
				* Safely get a pointer to the Row with name: Row Name in a DataTable associated with Path.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Path			Soft Path to the DataTable.
				* @param RowName		Row Name in the retrieved DataTable.
				* @param Log			(optional)
				* return				Pointer to the Row.
				*/
				static uint8* GetSafeDataTableRow(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, const FName& RowName, LogLevel);

				/**
				* Get a pointer to the Row with name: Row Name in a DataTable associated with SoftObject.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param SoftObject		Soft reference to the DataTable.
				* @param RowName		Row Name in the retrieved DataTable.
				* return				Pointer to the Row.
				*/
				static uint8* GetDataTableRowChecked(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject, const FName& RowName);

				/**
				* Safely get a pointer to the Row with name: Row Name in a DataTable associated with SoftObject.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param SoftObject		Soft reference to the DataTable.
				* @param RowName		Row Name in the retrieved DataTable.
				* @param Log			(optional)
				* return				Pointer to the Row.
				*/
				static uint8* GetSafeDataTableRow(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject, const FName& RowName, LogLevel);

				/**
				* Get a pointer to the Row with name: Row Name in a DataTable associated with SoftObject.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param SoftObject		Soft reference to the DataTable.
				* @param RowStruct
				* @param RowName		Row Name in the retrieved DataTable.
				* return				Pointer to the Row.
				*/
				static uint8* GetDataTableRowChecked(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject, const UScriptStruct* RowStruct, const FName& RowName);

				static FName DataTable_GetEntryNameChecked(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject);

			#pragma endregion DataTable

			#pragma endregion Get

			// Active
			#pragma region
			public:

				FORCEINLINE static bool IsActiveChecked(const FString& Context, const UObject* ContextObject)
				{
				#if !UE_BUILD_SHIPPING
					return GetChecked(Context, ContextObject) != nullptr;
				#else
					return true;
				#endif // #if !UE_BUILD_SHIPPING
				}

				FORCEINLINE static bool SafeIsActive(const FString& Context, const UObject* ContextObject, LogLevel)
				{
					return GetSafe(Context, ContextObject, Log) != nullptr;
				}

			#pragma endregion Active

			// Maps
			#pragma region
		
				// Payload
			#pragma region
			public:

				static bool DoesPayloadContainChecked(const FString& Context, const UObject* ContextObject, const FName& PayloadName, const TSoftObjectPtr<UDataTable>& DataTable);
		
			#pragma endregion Payload

			#pragma endregion Maps

			// Add
			#pragma region
			public:

				// Data
			#pragma region
			public:

			/**
			* Add a Data UObject to an internal list in Manager_Data.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param EntryName
			* @param Data			Object that implements the interface: ICsData and
			*						Data->_getIData() returns an object that implements the interface: NCsData::IData
			* @param Log			(optional)
			* return				Whether Data was successful added to an internal list in Manager_Data.
			*/
			static bool SafeAddDataObject_Loaded(const FString& Context, const UObject* ContextObject, const FName& EntryName, UObject* Data, LogLevel);
		
			/**
			* Add a Data UObject to an internal list in Manager_Data.
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param DataName
			* @param Data			Object that serves as the UObject acting as a composition of multiple interfaces. The 
			*						composition is built from this UObject and the UObject holds all the "hard" references in the 
			*						case of garbage collection.
			* @param SliceName
			*/
			static void AddDataCompositionObject_Loaded_Checked(const FString& Context, const UObject* ContextObject, const FName& DataName, UObject* Data, const FName& SliceName);

			/**
			* Remove a Data with name: DataName from an internal list in Manager_Data.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @parma Log			(optional)
			* return				Whether Data with name: DataName was successfully removed.
			*/
			static bool SafeRemoveDataCompositionObject_Loaded(const FString& Context, const UObject* ContextObject, const FName& DataName, LogLevel);

			#pragma endregion Data

				// Payload
			#pragma region
			public:

				/**
				* 
				* 
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param PayloadName
				*/
				static void AddPayloadChecked(const FString& Context, const UObject* ContextRoot, const FName& PayloadName, const FCsPayload* Payload);

			#pragma endregion Payload

			#pragma endregion Add

			// Load
			#pragma region
		
				// Payload
			#pragma region
			public:
	
				static OnAsyncLoadPayloadCompletePersistentType& GetOnAsyncLoadPayloadComplete_Persistent_EventChecked(const FString& Context, const UObject* ContextObject);

				/**
				* Asynchronous load a Payload by Payload Name.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param PayloadName	Name of the Payload to async load.
				* @param Delegate		Delegate called synchronously (on the Game Thread) 
				*						when the async load completes.
				*/
				static void AsyncLoadPayloadChecked(const FString& Context, const UObject* ContextObject, const FName& PayloadName, OnAsyncLoadPayloadCompleteOnceType Delegate);

				/**
				* Asynchronous load a Payload by Payload Name.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param PayloadName	Name of the Payload to async load.
				* @param Delegate		Delegate called synchronously (on the Game Thread) 
				*						when the async load completes.
				*/
				static void AsyncAddAndLoadPayloadChecked(const FString& Context, const UObject* ContextObject, const FName& PayloadName, const FCsPayload* Payload, OnAsyncLoadPayloadCompleteOnceType Delegate);

				/**
				* Asynchronous load the Startup Payload (This is set in the current DataRootSet. See UCsDeveloperSettings).
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Delegate		Delegate called synchronously (on the Game Thread) 
				*						when the async load completes.
				*/
				static void AsyncLoadStartupPayloadChecked(const FString& Context, const UObject* ContextObject, OnAsyncLoadPayloadCompleteOnceType Delegate);

				/**
				* Safely Asynchronous load the Startup Payload (This is set in the current DataRootSet. See UCsDeveloperSettings).
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param Delegate		Delegate called synchronously (on the Game Thread) 
				*						when the async load completes.
				* return
				*/
				static bool SafeAsyncLoadStartupPayload(const FString& Context, const UObject* ContextObject, OnAsyncLoadPayloadCompleteOnceType Delegate, LogLevel);

				/**
				* Asynchronous load a list of Payloads by Name.
				*
				* @param Context		The calling context.
				* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
				*						or
				*						A reference to the GameInstance.
				* @param PayloadNames	Names of the Payload to async load.
				* @param Delegate		Delegate called synchronously (on the Game Thread) 
				*						when the async load completes.
				*/
				static void AsyncLoadPayloadsChecked(const FString& Context, const UObject* ContextObject, const TArray<FName>& PayloadNames, OnAsyncLoadPayloadsCompleteOnceType Delegate);

				static void UnloadPayloadChecked(const FString& Context, const UObject* ContextObject, const FName& PayloadName);

			#pragma endregion Payload
			
			#pragma endregion Load

			#undef LogLevel
			};
		}
	}
}

using CsDataManagerLibrary = NCsData::NManager::NLibrary::FLibrary;