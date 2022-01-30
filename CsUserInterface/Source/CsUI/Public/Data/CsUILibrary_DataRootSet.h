// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsUIDataRootSet.h"

class UObject;

namespace NCsUI
{
	namespace NDataRootSet
	{
		/**
		*/
		class CSUI_API FLibrary final
		{
		public:

			/**
			*
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* return
			*/
			static const FCsUIDataRootSet* GetSafe(const FString& Context, const UObject* WorldContext);

			/**
			*
			*
			* @param Context		The calling context.
			* @param GameInstance	Route to Manager_Data, whose root is a GameInstance.
			* return				
			*/
			static const FCsUIDataRootSet& GetChecked(const FString& Context, const UGameInstance* GameInstance);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* return				
			*/
			static const FCsUIDataRootSet& GetChecked(const FString& Context, const UObject* WorldContext);

		#define MemberType FCsUIDataRootSet::EMember

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* @param Member			The DataTable member.
			* return				DataTable
			*/
			static UDataTable* GetSafeDataTable(const FString& Context, const UObject* WorldContext, const MemberType& Member);

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* @param Member			The DataTable member.
			* return				DataTable
			*/
			static UDataTable* GetDataTableChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* @param Member			The DataTable member.
			* return				SoftObject reference to DataTable.
			*/
			static const TSoftObjectPtr<UDataTable>& GetDataTableSoftObjectChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member);

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* @param Member			The DataTable member.
			* return				Pointer to Row Struct of the DataTable.
			*/
			template<typename RowStructType>
			FORCEINLINE static RowStructType* GetSafeDataTableRow(const FString& Context, const UObject* WorldContext, const MemberType& Member, const FName& RowName, void(*Log)(const FString&))
			{
				if (const FCsUIDataRootSet* DataRootSet = GetSafe(Context, WorldContext))
					return DataRootSet->GetSafeDataTableRow<RowStructType>(Context, WorldContext, Member, RowName, Log);
				return nullptr;
			}

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* @param Member			The DataTable member.
			* return				Pointer to Row Struct of the DataTable.
			*/
			static uint8* GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const FName& RowName);

			/**
			*
			*
			* @param Context		The calling context
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* @param Member			The DataTable member.
			* @param RowStruct		ScriptStruct associated with the RowStruct
			* return				Pointer to Row Struct of the DataTable.
			*/
			static uint8* GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const UScriptStruct* RowStruct, const FName& RowName);

			/**
			*
			*
			* @param Context		The calling context
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* @param Member			The DataTable member.
			* return				Pointer to Row Struct of the DataTable.
			*/
			template<typename RowStructType>
			FORCEINLINE static RowStructType* GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const FName& RowName)
			{
				RowStructType* Row = reinterpret_cast<RowStructType*>(GetDataTableRowChecked(Context, WorldContext, Member, RowStructType::StaticStruct(), RowName));

				checkf(Row, TEXT("%s: Failed in casting Row Pointer to RowStructType."), *Context);

				return Row;
			}

		#undef MemberType
		};
	}
}