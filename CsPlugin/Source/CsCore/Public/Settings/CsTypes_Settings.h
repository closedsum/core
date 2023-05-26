// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Settings.generated.h"

// FCsSettings_Enum
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Enum
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
		struct CSCORE_API FLibrary
		{
		public:

			static void PopulateArrayFromString(TArray<FCsSettings_Enum>& Enums, const FString& Str, const FString& EnumTypeName);
		};
	}
}

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

// FCsSettings_PIE
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_PIE
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings")
	bool bSwapViewportDimensions;

	/** The width of the new view port window in pixels (0 = use the desktop's screen resolution). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings", meta = (ClampMin = 0))
	int32 NewWindowWidth;

	/** The height of the new view port window in pixels (0 = use the desktop's screen resolution). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings", meta = (ClampMin = 0))
	int32 NewWindowHeight;

	FCsSettings_PIE() :
		bSwapViewportDimensions(false),
		NewWindowWidth(1280),
		NewWindowHeight(720)
	{
	}

	void SwapViewportDimensions()
	{
		int32 Temp	    = NewWindowWidth;
		NewWindowWidth  = NewWindowHeight;
		NewWindowHeight = Temp;

		bSwapViewportDimensions = false;
	}
};

#pragma endregion FCsSettings_PIE

// FCsSettings_Entry
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Entry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float CompanyLogoDisplayTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float GameSplashDisplayTime;

	FCsSettings_Entry() :
		CompanyLogoDisplayTime(0.0f),
		GameSplashDisplayTime(0.0f)
	{
	}
};

#pragma endregion FCsSettings_Entry