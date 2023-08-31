// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

// NOTE: Should only be included in .h files

class UObject;
class UDataTable;

/**
* Utility class to help populate a EnumStructMap. Called internally by the 
* namespace associated with the appropriate EnumStruct.
*/
struct CSCORE_API FCsPopulateEnumMapFromSettings final
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

	static UDataTable* GetDataTable(const FString& Context, const UObject* ContextRoot, const TSoftObjectPtr<UDataTable>& DT_SoftObject);

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

#define PayloadType FCsPopulateEnumMapFromSettings::FFromDataTable::FPayload
	static void FromDataTable(const FString& Context, PayloadType& Payload);
#undef PayloadType

	/**
	* Populate EnumMap with values corresponding to the rows of the DataTable.
	*  Assume the struct used as the entry of the DataTable has the properties:
	*   Name: type is FString
	*   DisplayName: type is FString
	*  These properties are used to generate the Name, DisplayName, and Value added to the EnumMap.
	* 
	* @param Context		The calling context.
	* @param ContextRoot	Context (Root) to route to the UCsManager_Data. This is 
	*						usually a reference to the GameInstance.
	*						TODO: Eventually change to WorldContext.
	* @param DataTable
	* @param EnumName
	* @param Log
	*/
	template<typename EnumMap>
	static void FromDataTable(const FString& Context, const UObject* ContextRoot, UDataTable* DataTable, const FString& EnumName, void(*Log)(const FString&))
	{
		const UScriptStruct* RowStruct	  = DataTable->GetRowStruct();
		const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();
		{
			// Set if the Row Struct has the properties Name and DisplayName

			FStrProperty* NameProperty		  = CastField<FStrProperty>(RowStruct->FindPropertyByName(NamePropertyName));
			NameProperty					  = NameProperty ? NameProperty : CastField<FStrProperty>(RowStruct->CustomFindProperty(NamePropertyName));
			FStrProperty* DisplayNameProperty = CastField<FStrProperty>(RowStruct->FindPropertyByName(DisplayNamePropertyName));
			DisplayNameProperty				  = DisplayNameProperty ? DisplayNameProperty : CastField<FStrProperty>(RowStruct->CustomFindProperty(DisplayNamePropertyName));

			if (NameProperty &&
				DisplayNameProperty)
			{
				if (RowMap.Num() == CS_EMPTY)
				{
					CS_NON_SHIPPING_EXPR(Log(FString::Printf(TEXT("%s: No entries found for %s."), *Context, *(DataTable->GetName()))));
				}

				const FName Name_NewRow = FName("NewRow");

				for (const TPair<FName, uint8*>& Pair : RowMap)
				{
					const FName& RowName = Pair.Key;
					const uint8* RowPtr  = Pair.Value;

					const FString& Name		   = NameProperty->GetPropertyValue_InContainer(RowPtr);
					const FString& DisplayName = DisplayNameProperty->GetPropertyValue_InContainer(RowPtr);

					// If Making a New Row, skip
					if (RowName == Name_NewRow &&
						Name.IsEmpty() &&
						DisplayName.IsEmpty())
					{
						continue;
					}

					checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != %s Name (%s != %s)."), *Context, *EnumName, *(RowName.ToString()), *Name);

					checkf(!EnumMap::Get().IsValidEnum(Name), TEXT("%s: %s (Name): %s already exists (declared in native)."), *Context, *EnumName, *Name);

					if (!DisplayName.IsEmpty())
					{
						checkf(!EnumMap::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: %s (DisplayName): %s already exists (declared in native)."), *Context, *EnumName, *DisplayName);

						EnumMap::Get().Create(Name, DisplayName, true);
					}
					else
					{
						EnumMap::Get().Create(Name, true);
					}
				}
			}
			else
			{
				CS_NON_SHIPPING_EXPR(Log(FString::Printf(TEXT("%s: Failed to find properties with name: Name and Display for struct: %s."), *Context, *(RowStruct->GetName()))));
			}
		}
	}

	/**
	* 
	* 
	* @param Context		The calling context.
	* @param ContextRoot	Context (Root) to route to the UCsManager_Data. This is
	*						usually a reference to the GameInstance.
	*						TODO: Eventually change to WorldContext.
	* @param DT_SoftObject
	* @param EnumName
	* @param Log
	*/
	template<typename EnumMap>
	static void FromDataTable(const FString& Context, const UObject* ContextRoot, const TSoftObjectPtr<UDataTable>& DT_SoftObject, const FString& EnumName, void(*Log)(const FString&))
	{
		if (UDataTable* DT = GetDataTable(Context, ContextRoot, DT_SoftObject))
		{
			FromDataTable<EnumMap>(Context, ContextRoot, DT, EnumName, Log);
		}
		else
		{
			CS_NON_SHIPPING_EXPR(Log(FString::Printf(TEXT("%s: Failed to Load DataTable @ %s."), *Context, *(DT_SoftObject.ToSoftObjectPath().ToString()))));
		}
	}

	/**
	* Populate EnumMap with values corresponding to the rows of the DataTable.
	*  The row name is used to generate the Name, DisplayName and Value added to the EnumMap.
	*
	* @param Context		The calling context.
	* @param ContextRoot	Context (Root) to route to the UCsManager_Data. This is
	*						usually a reference to the GameInstance.
	*						TODO: Eventually change to WorldContext.
	* @param DataTable
	* @param EnumName
	* @param Log
	*/
#define PayloadType FCsPopulateEnumMapFromSettings::FFromDataTable::FPayload
	static void FromDataTable_RowAsName(const FString& Context, PayloadType Payload);
#undef PayloadType

	/**
	* Populate EnumMap with values corresponding to the rows of the DataTable.
	*  The row name is used to generate the Name, DisplayName and Value added to the EnumMap.
	* 
	* @param Context		The calling context.
	* @param ContextRoot	Context (Root) to route to the UCsManager_Data. This is 
	*						usually a reference to the GameInstance.
	*						TODO: Eventually change to WorldContext.
	* @param DataTable
	* @param EnumName
	* @param Log
	*/
	template<typename EnumMap>
	static void FromDataTable_RowAsName(const FString& Context, UObject* ContextRoot, UDataTable* DataTable, const FString& EnumName, void(*Log)(const FString&))
	{
		const UScriptStruct* RowStruct	  = DataTable->GetRowStruct();
		const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();
		{
			if (RowMap.Num() == CS_EMPTY)
			{
				CS_NON_SHIPPING_EXPR(Log(FString::Printf(TEXT("%s: No entries found for %s."), *Context, *(DataTable->GetName()))));
			}

			const FName Name_NewRow = FName("NewRow");
			FString Name;
			FString DisplayName;

			for (const TPair<FName, uint8*>& Pair : RowMap)
			{
				const FName& RowName = Pair.Key;
				const uint8* RowPtr  = Pair.Value;

				Name		= RowName.ToString();
				DisplayName = Name;

				// If Making a New Row, skip
				if (RowName == Name_NewRow &&
					Name.IsEmpty() &&
					DisplayName.IsEmpty())
				{
					continue;
				}

				checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != %s Name (%s != %s)."), *Context, *EnumName, *(RowName.ToString()), *Name);

				checkf(!EnumMap::Get().IsValidEnum(Name), TEXT("%s: %s (Name): %s already exists (declared in native)."), *Context, *EnumName, *Name);

				if (!DisplayName.IsEmpty())
				{
					checkf(!EnumMap::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: %s (DisplayName): %s already exists (declared in native)."), *Context, *EnumName, *DisplayName);

					EnumMap::Get().Create(Name, DisplayName, true);
				}
				else
				{
					EnumMap::Get().Create(Name, true);
				}
			}
		}
	}
};