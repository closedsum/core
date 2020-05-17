// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"

#include "CsEdTypes_DataTable.generated.h"
#pragma once

// DataTableFileType
#pragma region

UENUM(BlueprintType)
enum class ECsDataTableFileType : uint8
{
	json						UMETA(DisplayName = "json"),
	csv							UMETA(DisplayName = "csv"),
	ECsDataTableFileType_MAX	UMETA(Hidden),
};

struct CSEDDATATABLE_API EMCsDataTableFileType final : public TCsEnumMap<ECsDataTableFileType>
{
	CS_ENUM_MAP_BODY(EMCsDataTableFileType, ECsDataTableFileType)
};

namespace NCsDataTableFileType
{
	typedef ECsDataTableFileType Type;

	namespace Ref
	{
		extern CSEDDATATABLE_API const Type json;
		extern CSEDDATATABLE_API const Type csv;
		extern CSEDDATATABLE_API const Type ECsDataTableFileType_MAX;
	}

	extern CSEDDATATABLE_API const uint8 MAX;
}

#define ECS_DATA_TABLE_FILE_TYPE_MAX NCsDataTableFileTypev::MAX

#pragma endregion DataTableFileType

// FCsDataTableImportExportInfo
#pragma region

class UDataTable;

USTRUCT(BlueprintType)
struct CSEDDATATABLE_API FCsDataTableImportExportInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> DataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsDataTableFileType FileType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString FileName;

	FCsDataTableImportExportInfo() :
		DataTable(nullptr),
		FileType(ECsDataTableFileType::json),
		FileName()
	{
	}

	FORCEINLINE bool operator==(const FCsDataTableImportExportInfo& B) const
	{
		return DataTable == B.DataTable && FileType == B.FileType && FileName == B.FileName;
	}

	FORCEINLINE friend uint32 GetTypeHash(FCsDataTableImportExportInfo const& This)
	{
		return GetTypeHash(This.DataTable);
	}
};

#pragma endregion FCsDataTableImportExportInfo