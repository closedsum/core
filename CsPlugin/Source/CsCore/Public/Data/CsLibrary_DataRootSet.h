// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Data
#include "Data/CsDataRootSet.h"

// NOTE: Should only be included in .h files

class UObject;
class UGameInstance;

namespace NCsDataRootSet
{
	/**
	*/
	class CSCORE_API FLibrary
	{
	public:

		/**
		* Safely get the UObject implementation of the DataRootSet.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
		* return				UObject for the DataRootSet
		*/
		static UObject* GetSafeImpl(const FString& Context, const UObject* WorldContext);
		
		/**
		* Get the UObject implementation of the DataRootSet.
		* 
		* @param Context		The calling context.
		* @param GameInstance	Route to Manager_Data, whose root is a GameInstance.
		* return				UObject for the DataRootSet
		*/
		static UObject* GetImplChecked(const FString& Context, const UGameInstance* GameInstance);

		/**
		* Get the UObject implementation of the DataRootSet.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
		* return				UObject for the DataRootSet
		*/
		static UObject* GetImplChecked(const FString& Context, const UObject* WorldContext);

		/**
		* 
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
		* return
		*/
		static const FCsDataRootSet* GetSafe(const FString& Context, const UObject* WorldContext);

		/**
		* 
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
		* @param Log
		* return
		*/
		template<typename DataRootSetType, typename GetDataRootSetType, const DataRootSetType& (GetDataRootSetType::* GetDataRootSetFn)() const>
		static const DataRootSetType* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&))
		{
			// Get DataRootSetImpl
			UObject* DataRootSetImpl = GetSafeImpl(Context, WorldContext);

			if (!DataRootSetImpl)
				return nullptr;

			// Get DataRootSet for this Module
			GetDataRootSetType* GetDataRootSet = Cast<GetDataRootSetType>(DataRootSetImpl);

			if (!GetDataRootSet)
			{
				Log(FString::Printf(TEXT("%s: DataRootSet: %s with Class: %s does NOT implement interface: GetDataRootSetType."), *Context, *(DataRootSetImpl->GetName()), *(DataRootSetImpl->GetClass()->GetName())));
				return nullptr;
			}
			return &(GetDataRootSet->*GetDataRootSetFn)();
		}

		/**
		* 
		* 
		* @param Context		The calling context.
		* @param GameInstance	Root for UCsManager_Data.
		* return
		*/
		static const FCsDataRootSet& GetChecked(const FString& Context, const UGameInstance* GameInstance);

		/**
		* 
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
		*/
		static const FCsDataRootSet& GetChecked(const FString& Context, const UObject* WorldContext);

		/**
		* 
		* 
		* @param Context		The calling context.
		* @param GameInstance	Root for UCsManager_Data.
		* return
		*/
		template<typename DataRootSetType, typename GetDataRootSetType, const DataRootSetType& (GetDataRootSetType::* GetDataRootSetFn)() const>
		static const DataRootSetType& GetChecked(const FString& Context, const UGameInstance* GameInstance)
		{
			// Get DataRootSetImpl
			UObject* DataRootSetImpl = GetImplChecked(Context, GameInstance);

			// Get DataRootSet for this Module
			GetDataRootSetType* GetDataRootSet = Cast<GetDataRootSetType>(DataRootSetImpl);

			checkf(GetDataRootSet, TEXT("%s: DataRootSet: %s with Class: %s does NOT implement interface: GetDataRootSetType."), *Context, *(DataRootSetImpl->GetName()), *(DataRootSetImpl->GetClass()->GetName()));

			return (GetDataRootSet->*GetDataRootSetFn)();
		}

		/**
		* 
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
		* return
		*/
		template<typename DataRootSetType, typename GetDataRootSetType, const DataRootSetType&(GetDataRootSetType::*GetDataRootSetFn)() const>
		static const DataRootSetType& GetChecked(const FString& Context, const UObject* WorldContext)
		{
			// Get DataRootSetImpl
			UObject* DataRootSetImpl = GetImplChecked(Context, WorldContext);

			// Get DataRootSet for this Module
			GetDataRootSetType* GetDataRootSet = Cast<GetDataRootSetType>(DataRootSetImpl);

			checkf(GetDataRootSet, TEXT("%s: DataRootSet: %s with Class: %s does NOT implement interface: GetDataRootSetType."), *Context, *(DataRootSetImpl->GetName()), *(DataRootSetImpl->GetClass()->GetName()));

			return (GetDataRootSet->*GetDataRootSetFn)();
		}

		/**
		* 
		* 
		* @param Context				The calling context.
		* @param WorldContext			Object that has reference to a World (GetWorld() is Valid).
		* @param InterfaceGetName
		* @param DataTableSoftObject	FSoftObjectPtr to a DataTable.
		* @param DataTableName			Name of the DataTable.
		* return						DataTable
		*/
		static UDataTable* GetSafeDataTable(const FString& Context, const UObject* WorldContext, const FString& InterfaceGetName, TSoftObjectPtr<UDataTable> DataTableSoftObject, const FString& DataTableName);

		/**
		* 
		* 
		* @param Context				The calling context.
		* @param WorldContext			Object that has reference to a World (GetWorld() is Valid).
		* @param DataTableSoftObject	FSoftObjectPtr to a DataTable.
		* return						DataTable
		*/
		static UDataTable* GetDataTableChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UDataTable>& DataTableSoftObject);

		/**
		* 
		* 
		* @param Context				The calling context.
		* @param WorldContext			Object that has reference to a World (GetWorld() is Valid).
		* @param DataTableSoftObject	FSoftObjectPtr to a DataTable.
		* @param RowName				Name of the row in the DataTable.
		* return						Pointer to row.
		*/
		static uint8* GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UDataTable>& DataTableSoftObject, const FName& RowName);

		/**
		*
		*
		* @param Context				The calling context.
		* @param WorldContext			Object that has reference to a World (GetWorld() is Valid).
		* @param DataTableSoftObject	FSoftObjectPtr to a DataTable.
		* @param RowStruct				ScriptStruct associated with the row.
		* @param RowName				Name of the row in the DataTable.
		* return						Pointer to row.
		*/
		static uint8* GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UDataTable>& DataTableSoftObject, const UScriptStruct* RowStruct, const FName& RowName);
	};
}