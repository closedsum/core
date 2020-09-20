// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Settings.generated.h"

// FCsSettings_Enum
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Enum
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	FCsSettings_Enum() :
		Name(),
		DisplayName()
	{
	}
};

#pragma endregion FCsSettings_Enum

// PopulateEnumMapMethod
#pragma region

UENUM(BlueprintType)
enum class ECsPopulateEnumMapMethod : uint8
{
	Native							UMETA(DisplayName = "Native"),
	EnumSettings					UMETA(DisplayName = "Enum Settings"),
	DataTable						UMETA(DisplayName = "DataTable"),
	ECsPopulateEnumMapMethod_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsPopulateEnumMapMethod : public TCsEnumMap<ECsPopulateEnumMapMethod>
{
	CS_ENUM_MAP_BODY(EMCsPopulateEnumMapMethod, ECsPopulateEnumMapMethod)
};

namespace NCsPopulateEnumMapMethod
{
	typedef ECsPopulateEnumMapMethod Type;

	namespace Ref
	{
		extern CSCORE_API const Type Native;
		extern CSCORE_API const Type EnumSettings;
		extern CSCORE_API const Type DataTable;
		extern CSCORE_API const Type ECsPopulateEnumMapMethod_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#define ECS_POPULATE_ENUM_MAP_METHOD_MAX (uint8)ECsPopulateEnumMapMethod::ECsPopulateEnumMapMethod_MAX

#pragma endregion PopulateEnumMapMethod