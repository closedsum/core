// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/UnrealString.h"
#include "UObject/NameTypes.h"

class UObject;

struct FCsWpDataRootSet;

/**
* Utility class to help populate a EnumStructMap. Called internally by the 
* namespace associated with the appropriate EnumStruct.
*/
struct CSWP_API FCsWpPopulateEnumMapFromSettings final
{
public:

	static const FCsWpDataRootSet* GetDataRootSet(const FString& Context, UObject* ContextRoot);

	struct FFromDataTable
	{
	public:

		struct FPayload
		{
		public:

			UObject* ContextRoot;

			FName DataTableName;

			FString EnumName;

			void(*Create)(const FString& /*Name*/, const bool& /*UserDefinedEnum*/);
			void(*CreateCustom)(const FString& /*Name*/, const FString& /*DisplayName*/, const bool& /*UserDefinedEnum*/);
			bool(*IsValidEnum)(const FString& /*Name*/);
			bool(*IsValidEnumByDisplayName)(const FString& /*DisplayName*/);

			void(*Log)(const FString&);

			FPayload() :
				ContextRoot(nullptr),
				DataTableName(NAME_None),
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
	using PayloadType = FCsWpPopulateEnumMapFromSettings::FFromDataTable::FPayload;

	static void FromDataTable(const FString& Context, PayloadType& Payload);
};