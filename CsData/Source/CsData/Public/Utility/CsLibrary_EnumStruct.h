// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"
#include "UObject/SoftObjectPtr.h"

// NOTE: Should only be included in .h files

class UObject;
class UDataTable;
class UStruct;
struct FCsDataRootSet;

namespace NCsEnum
{
	namespace NStruct
	{
		namespace NPopulate
		{
			/**
			* Utility class to help populate a EnumStructMap. Called internally by the 
			* namespace associated with the appropriate EnumStruct.
			*/
			struct CSDATA_API FLibrary final
			{
			private:

				static const FName NamePropertyName;
				static const FName DisplayNamePropertyName;

			public:

				static UObject* GetDataRootSetImpl(const FString& Context, UObject* ContextRoot);

				/**
				*
				*
				* @param Context		The calling context.
				* @param ContextRoot	Context (Root) to route to the UCsManager_Data. This is
				*						usually a reference to the GameInstance.
				*						TODO: Eventually change to WorldContext.
				* return
				*/
				template<typename DataRootSetType, typename GetDataRootSetType, const DataRootSetType&(GetDataRootSetType::*GetDataRootSetFn)() const>
				static const DataRootSetType* GetDataRootSet(const FString& Context, UObject* ContextRoot)
				{
					// Get DataRootSet
					UObject* DataRootSetImpl = GetDataRootSetImpl(Context, ContextRoot);

					if (!DataRootSetImpl)
						return nullptr;

					GetDataRootSetType* GetDataRootSet = Cast<GetDataRootSetType>(DataRootSetImpl);

					if (!GetDataRootSet)
						return nullptr;

					const DataRootSetType& DataRootSet = (GetDataRootSet->*GetDataRootSetFn)();

					return &DataRootSet;
				}

				/**
				*
				*
				* @param Context		The calling context.
				* @param ContextRoot	Context (Root) to route to the UCsManager_Data. This is
				*						usually a reference to the GameInstance.
				*						TODO: Eventually change to WorldContext.
				* return
				*/
				template<typename DataRootSetType, typename GetDataRootSetType, const DataRootSetType& (GetDataRootSetType::* GetDataRootSetFn)() const>
				static const DataRootSetType* GetDataRootSet(const FString& Context, UObject* ContextRoot, UObject*& OutDataRootSetImpl)
				{
					// Get DataRootSet
					OutDataRootSetImpl = GetDataRootSetImpl(Context, ContextRoot);

					if (!OutDataRootSetImpl)
						return nullptr;

					GetDataRootSetType* GetDataRootSet = Cast<GetDataRootSetType>(OutDataRootSetImpl);

					if (!GetDataRootSet)
						return nullptr;

					const DataRootSetType& DataRootSet = (GetDataRootSet->*GetDataRootSetFn)();

					return &DataRootSet;
				}

				static const FCsDataRootSet* GetDataRootSet(const FString& Context, UObject* ContextRoot);

				static UDataTable* GetDataTable(const FString& Context, const UObject* ContextRoot, const TSoftObjectPtr<UDataTable>& DT_SoftObject);
				static UDataTable* GetDataTable(const FString& Context, const FName& DataTableName);

				struct FFromDataTable
				{
				public:

					struct FPayload
					{
					public:
			
						UObject* ContextRoot;

						UDataTable* DataTable;

						TSoftObjectPtr<UDataTable> DataTableSoftObject;

						FString EnumName;

						void(*Create)(const FString& /*Name*/, const bool& /*UserDefinedEnum*/);
						void(*CreateCustom)(const FString& /*Name*/, const FString& /*DisplayName*/, const bool& /*UserDefinedEnum*/);
						bool(*IsValidEnum)(const FString& /*Name*/);
						bool(*IsValidEnumByDisplayName)(const FString& /*DisplayName*/);

						void(*Log)(const FString&);

						FPayload() :
							ContextRoot(nullptr),
							DataTable(nullptr),
							DataTableSoftObject(),
							EnumName(),
							Create(nullptr),
							CreateCustom(nullptr),
							IsValidEnum(nullptr),
							IsValidEnumByDisplayName(nullptr),
							Log(nullptr)
						{
						}
					};
				};

			#define PayloadType NCsEnum::NStruct::NPopulate::FLibrary::FFromDataTable::FPayload

				/**
				* Populate EnumMap with values corresponding to the rows of the DataTable.
				*  Assume the struct used as the entry of the DataTable has the properties:
				*   Name: type is FString
				*   DisplayName: type is FString
				*  These properties are used to generate the Name, DisplayName, and Value added to the EnumMap.
				*
				* @param Context		The calling context.
				* @param Payload
				*/
			
				static void FromDataTable(const FString& Context, PayloadType& Payload);

				/**
				* Populate EnumMap with values corresponding to the rows of the DataTable.
				*  The row name is used to generate the Name, DisplayName and Value added to the EnumMap.
				*
				* @param Context		The calling context.
				* @param Payload
				*/
				static void FromDataTable_RowAsName(const FString& Context, PayloadType Payload);

			#undef PayloadType
			};
		}
	}
}

using CsEnumStructPopulateLibrary = NCsEnum::NStruct::NPopulate::FLibrary;

namespace NCsEnum
{
	namespace NStruct
	{
		namespace NLayout
		{
			struct CSDATA_API FLibrary final
			{	
			public:

				static void(*ConditionalAddLayout)(const FName& /*EnumName*/, const TArray<FName>& /*Names*/, UDataTable* /*DataTable*/);

				static void(*AddPropertyChange)(const FName& /*EnumName*/, UStruct* /*EnumStruct*/);

				static void CheckChange();
			};
		}
	}
}

using CsEnumStructLayoutLibrary = NCsEnum::NStruct::NLayout::FLibrary;