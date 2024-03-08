// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsSeDataRootSet.h"

class UObject;
class UGameInstance;
class UScriptStruct;

namespace NCsStatusEffect
{
	namespace NDataRootSet
	{
		/**
		*/
		class CSSE_API FLibrary
		{
		public:

			/**
			* Safely get the DataRootSet associated with this Module.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* return
			*/
			static const FCsSeDataRootSet* GetSafe(const FString& Context, const UObject* WorldContext);

			/**
			* Get the DataRootSet associated with this Module.
			*
			* @param Context		The calling context.
			* @param GameInstance	Route to Manager_Data, whose root is a GameInstance.
			* return				
			*/
			static const FCsSeDataRootSet& GetChecked(const FString& Context, const UGameInstance* GameInstance);

			/**
			* Get the DataRootSet associated with this Module.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* return				
			*/
			static const FCsSeDataRootSet& GetChecked(const FString& Context, const UObject* WorldContext);

		#define MemberType FCsSeDataRootSet::EMember

			/**
			* Safely get the DataTable associated with Member.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* @param Member			The DataTable member.
			* return				DataTable
			*/
			static UDataTable* GetSafeDataTable(const FString& Context, const UObject* WorldContext, const MemberType& Member);

			/**
			* Get the DataTable associated with Member.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* @param Member			The DataTable member.
			* return				DataTable
			*/
			static UDataTable* GetDataTableChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member);

			/**
			* Get the Soft Object pointer to the DataTable associated with Member.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* @param Member			The DataTable member.
			* return				SoftObject reference to DataTable.
			*/
			static const TSoftObjectPtr<UDataTable>& GetDataTableSoftObjectChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member);

			/**
			* Safely get the DataTable row associated with Member and row with name: RowName.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* @param Member			The DataTable member.
			* return				Pointer to Row Struct of the DataTable.
			*/
			template<typename RowStructType>
			FORCEINLINE static RowStructType* GetSafeDataTableRow(const FString& Context, const UObject* WorldContext, const MemberType& Member, const FName& RowName, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning)
			{
				if (const FCsSeDataRootSet* DataRootSet = GetSafe(Context, WorldContext))
					return DataRootSet->GetSafeDataTableRow<RowStructType>(Context, WorldContext, Member, RowName, Log);
				return nullptr;
			}

			/**
			* Get the DataTable row associated with Member and row with name: RowName.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* @param Member			The DataTable member.
			* return				Pointer to Row Struct of the DataTable.
			*/
			static uint8* GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const FName& RowName);

			/**
			* Get the DataTable row associated with Member and row with name: RowName.
			*
			* @param Context		The calling context
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* @param Member			The DataTable member.
			* @param RowStruct		ScriptStruct associated with the RowStruct
			* return				Pointer to Row Struct of the DataTable.
			*/
			static uint8* GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const UScriptStruct* RowStruct, const FName& RowName);

			/**
			* Get the DataTable row associated with Member and row with name: RowName.
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

			/**
			* Safely get the relative file path to the DataTable associated with Member.
			* NOTE: This path is trimmed (i.e. the path after '.' is removed).
			*
			* @param Context		The calling context
			* @param WorldContext	Object that has reference to a World (GetWorld() is Valid).
			* @param Member			The DataTable member.
			* @param OutPath		(out) String path to DataTable. This path is trimmed.
			* @param Log			(optional)
			* return				Whether a string path was found.
			*/
			static bool GetSafeDataTablePath(const FString& Context, const UObject* WorldContext, const MemberType& Member, FString& OutPath, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning);

		#undef MemberType
		};
	}
}