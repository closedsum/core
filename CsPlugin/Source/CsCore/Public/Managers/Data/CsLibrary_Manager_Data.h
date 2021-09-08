// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
// Log
#include "Utility/CsLog.h"

#pragma once

class UObject;
class UCsManager_Data;
class ICsData;
class UDataTable;

namespace NCsData
{
	namespace NManager
	{
		struct CSCORE_API FLibrary final
		{
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
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString& Context) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString& Context) = &FCsLog::Warning) { return nullptr; }
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
			static UCsManager_Data* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static ICsData* GetSafeData(const FString& Context, const UObject* ContextObject, const FName& EntryName, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static ICsData* GetSafeData(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static UObject* GetSafeDataObject(const FString& Context, const UObject* ContextObject, const FName& EntryName, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static UObject* GetSafeDataObject(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		#pragma endregion Data

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
			static UDataTable* GetSafeDataTable(const FString& Context, const UObject* ContextObject, const FName& EntryName, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static UDataTable* GetSafeDataTable(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static UDataTable* GetSafeDataTable(const FString& Context, const UObject* ContextObject, const TSoftObjectPtr<UDataTable>& SoftObject, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get a DataTable by SoftObjectPtr.
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

		#pragma endregion DataTable

		#pragma endregion Get

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
		static bool SafeAddDataObject_Loaded(const FString& Context, const UObject* ContextObject, const FName& EntryName, UObject* Data, void(*Log)(const FString&) = &FCsLog::Warning);
		
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

		#pragma endregion Data

		#pragma endregion Add
		};
	}
}