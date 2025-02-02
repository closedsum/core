// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Settings_Enum.generated.h"

// FCsSettings_Enum
#pragma region

USTRUCT(BlueprintType)
struct CSTYPES_API FCsSettings_Enum
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings")
	FString DisplayName;

	FCsSettings_Enum() :
		Name(),
		DisplayName()
	{
	}
};

namespace NCsEnum
{
	namespace NSettings
	{
		struct CSTYPES_API FLibrary
		{
		public:

			static void PopulateArrayFromString(TArray<FCsSettings_Enum>& Enums, const FString& Str, const FString& EnumTypeName);

			struct FPopulate
			{
			public:

				struct FPayload
				{
				public:

					TArray<FCsSettings_Enum> Enums;
					
					FString EnumSettingsPath;

					FString EnumName;

					void(*Create)(const FString& /*Name*/, const bool& /*UserDefinedEnum*/);
					void(*CreateCustom)(const FString& /*Name*/, const FString& /*DisplayName*/, const bool& /*UserDefinedEnum*/ );
					bool(*IsValidEnum)(const FString& /*Name*/ );
					bool(*IsValidEnumByDisplayName)(const FString& /*DisplayName*/);

					void(*Log)(const FString&);

					FPayload() : 
						Enums(),
						EnumSettingsPath(),
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

			using PayloadType = NCsEnum::NSettings::FLibrary::FPopulate::FPayload;

			static void Populate(const FString& Context, PayloadType& Payload);
		};
	}
}

using CsEnumSettingsLibrary = NCsEnum::NSettings::FLibrary;

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

struct CSTYPES_API EMCsPopulateEnumMapMethod : public TCsEnumMap<ECsPopulateEnumMapMethod>
{
	CS_ENUM_MAP_BODY(EMCsPopulateEnumMapMethod, ECsPopulateEnumMapMethod)
};

namespace NCsPopulateEnumMapMethod
{
	typedef ECsPopulateEnumMapMethod Type;

	namespace Ref
	{
		extern CSTYPES_API const Type Native;
		extern CSTYPES_API const Type EnumSettings;
		extern CSTYPES_API const Type DataTable;
		extern CSTYPES_API const Type ECsPopulateEnumMapMethod_MAX;
	}

	extern CSTYPES_API const uint8 MAX;
}

#define ECS_POPULATE_ENUM_MAP_METHOD_MAX (uint8)ECsPopulateEnumMapMethod::ECsPopulateEnumMapMethod_MAX

#pragma endregion PopulateEnumMapMethod