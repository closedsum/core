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
		* Get the UObject implementation of the DataRootSet.
		* 
		* @param Context		The calling context.
		* @param GameInstance	Route to Manager_Data, whose root is a GameInstance.
		* return				UObject for the DataRootSet
		*/
		static UObject* GetImplChecked(const FString& Context, UGameInstance* GameInstance);

		/**
		* Get the UObject implementation of the DataRootSet.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
		* return				UObject for the DataRootSet
		*/
		static UObject* GetImplChecked(const FString& Context, UObject* WorldContext);

		/**
		*/
		static const FCsDataRootSet& GetChecked(const FString& Context, UGameInstance* GameInstance);

		/**
		*/
		static const FCsDataRootSet& GetChecked(const FString& Context, UObject* WorldContext);

		/**
		*/
		template<typename DataRootSetType, typename GetDataRootSetType, const DataRootSetType& (GetDataRootSetType::* GetDataRootSetFn)() const>
		static const DataRootSetType& GetChecked(const FString& Context, UGameInstance* GameInstance)
		{
			// Get DataRootSetImpl
			UObject* DataRootSetImpl = GetImplChecked(Context, GameInstance);

			// Get DataRootSet for this Module
			GetDataRootSetType* GetDataRootSet = Cast<GetDataRootSetType>(DataRootSetImpl);

			checkf(GetDataRootSet, TEXT("%s: DataRootSet: %s with Class: %s does NOT implement interface: GetDataRootSetType."), *Context, *(DataRootSetImpl->GetName()), *(DataRootSetImpl->GetClass()->GetName()));

			return (GetDataRootSet->*GetDataRootSetFn)();
		}

		/**
		*/
		template<typename DataRootSetType, typename GetDataRootSetType, const DataRootSetType&(GetDataRootSetType::*GetDataRootSetFn)() const>
		static const DataRootSetType& GetChecked(const FString& Context, UObject* WorldContext)
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
		* @param Context			The calling context.
		* @param WorldContext		Object that has reference to a World (GetWorld() is Valid).
		* @param InterfaceGetName
		* @param DataTableSoftPath
		* @param DataTableName
		* return
		*/
		static UDataTable* GetSafeDataTable(const FString& Context, UObject* WorldContext, const FString& InterfaceGetName, TSoftObjectPtr<UDataTable> DataTableSoftPath, const FString& DataTableName);

		/**
		* 
		* 
		* @param Context			The calling context.
		* @param WorldContext		Object that has reference to a World (GetWorld() is Valid).
		* @param DataTableSoftPath
		* return
		*/
		static UDataTable* GetDataTableChecked(const FString& Context, UObject* WorldContext, const TSoftObjectPtr<UDataTable>& DataTableSoftPath);

		/**
		* 
		* 
		* @param Context			The calling context.
		* @param WorldContext		Object that has reference to a World (GetWorld() is Valid).
		* @param DataTableSoftPath
		* @param RowName
		*/
		static uint8* GetDataTableRowChecked(const FString& Context, UObject* WorldContext, const TSoftObjectPtr<UDataTable>& DataTableSoftPath, const FName& RowName);
	};
}