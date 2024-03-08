// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"
#include "Types/Enum/CsEnumFlagMap.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_Load.generated.h"

#define CS_CVAR_LOAD_UNSET -1
#define CS_CVAR_LOAD_NONE 0
#define CS_CVAR_LOAD_FIRSTTOLAST 1
#define CS_CVAR_LOAD_BULK 2

namespace ECsLoadCached
{
	namespace Str
	{
		extern CSCORE_API const FString _Path;// = TEXT("_Path");
		extern CSCORE_API const FString _Internal;// = TEXT("_Internal");
		extern CSCORE_API const FString _Class;// = TEXT("_Class");
		extern CSCORE_API const FString _SubclassOf;// = TEXT("_Class");
		extern CSCORE_API const FString _LoadFlags;//= TEXT("_LoadFlags");
		extern CSCORE_API const FString _1P_LoadFlags;// = TEXT("1P_LoadFlags");
		extern CSCORE_API const FString _3P_LoadFlags;// = TEXT("3P_LoadFlags");
		extern CSCORE_API const FString _3P_Low_LoadFlags;// = TEXT("3P_Low_LoadFlags");
		extern CSCORE_API const FString VR_LoadFlags;// = TEXT("VR_LoadFlags");
		extern CSCORE_API const FString _C;// = TEXT("_C");
	}
}

// LoadCode
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsLoadCode : uint8
{
	CalculateResourceSizes		UMETA(DisplayName = "Calculate Resource Sizes"),		// 0
	SuppressLoadFlagsAllWarning	UMETA(DisplayName = "Suppress Load Flags All Warning"),	// 1
	/** Data implements the interface: ICsData. */
	RecursiveLoadData			UMETA(DisplayName = "Recursive Load Data"),				// 2
	RecursiveLoadDataTable		UMETA(DisplayName = "Recursive Load DataTable"),		// 3
};

#define ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES 1

namespace NCsLoadCodes
{
	typedef ECsLoadCode Type;

	/*
	namespace Ref
	{
		extern CSCORE_API const Type CalculateResourceSizes;
		extern CSCORE_API const Type SuppressLoadFlagsAllWarning;
		extern CSCORE_API const Type RecursiveLoadData;
		extern CSCORE_API const Type RecursiveLoadDataTable;
	}
	*/

	extern CSCORE_API const int32 None;
	extern CSCORE_API const int32 All;
}

#pragma endregion LoadCode

// LoadFlags
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsLoadFlags : uint8
{
	Game		UMETA(DisplayName = "Game"),					// 0
	Game1P		UMETA(DisplayName = "Game First Person"),		// 1
	Game3P		UMETA(DisplayName = "Game Third Person"),		// 2
	Game3PLow	UMETA(DisplayName = "Game Third Person Low"),	// 3
	GameVR		UMETA(DisplayName = "Game VR"),					// 4
	UI			UMETA(DisplayName = "UI"),						// 5
	//All			UMETA(DisplayName = "All"),						// 6
};

struct CSCORE_API EMCsLoadFlags : public TCsEnumFlagMap<ECsLoadFlags>
{
	CS_ENUM_FLAG_MAP_BODY(EMCsLoadFlags, ECsLoadFlags)
};

namespace NCsLoadFlags
{
	typedef ECsLoadFlags Type;

	namespace Ref
	{
		extern CSCORE_API const Type Game;
		extern CSCORE_API const Type Game1P;
		extern CSCORE_API const Type Game3P;
		extern CSCORE_API const Type Game3PLow;
		extern CSCORE_API const Type GameVR;
		extern CSCORE_API const Type UI;
		//extern CSCORE_API const Type All;
	}

	extern CSCORE_API const int32 None;
	extern CSCORE_API const int32 All;
}

#define CS_LOAD_FLAGS_NONE 0

#pragma endregion LoadFlags

// LoadFlags_Editor
#pragma region

UENUM(BlueprintType)
enum class ECsLoadFlags_Editor : uint8
{
	Game					UMETA(DisplayName = "Game"),
	Game1P					UMETA(DisplayName = "Game First Person"),
	Game3P					UMETA(DisplayName = "Game Third Person"),
	Game3PLow				UMETA(DisplayName = "Game Third Person Low"),
	GameVR					UMETA(DisplayName = "Game VR"),
	UI						UMETA(DisplayName = "UI"),
	All						UMETA(DisplayName = "All"),
	ECsLoadFlags_Editor_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsLoadFlags_Editor : public TCsEnumMap<ECsLoadFlags_Editor>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsLoadFlags_Editor, ECsLoadFlags_Editor)
};

namespace NCsLoadFlags_Editor
{
	typedef ECsLoadFlags_Editor Type;

	namespace Ref
	{
		extern CSCORE_API const Type Game;
		extern CSCORE_API const Type Game1P;
		extern CSCORE_API const Type Game3P;
		extern CSCORE_API const Type Game3PLow;
		extern CSCORE_API const Type GameVR;
		extern CSCORE_API const Type UI;
		extern CSCORE_API const Type All;
		extern CSCORE_API const Type ECsLoadFlags_Editor_MAX;
	}

	extern CSCORE_API const uint8 MAX;
	
	FORCEINLINE const ECsLoadFlags& ToBaseType(const Type &EType)
	{
		if (EType == Type::Game) { return NCsLoadFlags::Ref::Game; }
		if (EType == Type::Game1P) { return NCsLoadFlags::Ref::Game1P; }
		if (EType == Type::Game3P) { return NCsLoadFlags::Ref::Game3P; }
		if (EType == Type::Game3PLow) { return NCsLoadFlags::Ref::Game3PLow; }
		if (EType == Type::GameVR) { return NCsLoadFlags::Ref::GameVR; }
		if (EType == Type::UI) { return NCsLoadFlags::Ref::UI; }
		//if (EType == Type::All) { return NCsLoadFlags::Ref::All; }
		return NCsLoadFlags::Ref::Game;
	}
}

#pragma endregion LoadFlags_Editor

// UnloadCode
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsUnloadCode : uint8
{
	/** Data implements the interface: ICsData. */
	RecursiveUnloadData			UMETA(DisplayName = "Recursive Unload Data"),			// 0
	RecursiveUnloadDataTable	UMETA(DisplayName = "Recursive Unload DataTable")		// 1
};

namespace NCsUnloadCodes
{
	typedef ECsUnloadCode Type;

	/*
	namespace Ref
	{
		extern CSCORE_API const Type RecursiveUnloadData;
		extern CSCORE_API const Type RecursiveUnloadDataTable;
	}
	*/

	extern CSCORE_API const int32 None;
	extern CSCORE_API const int32 All;
}

#pragma endregion UnloadCode

// DataType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsDataType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsDataType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsDataType)

struct CSCORE_API EMCsDataType : public TCsEnumStructMap<FECsDataType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY_WITH_EXPLICIT_MAX(EMCsDataType, FECsDataType, uint8)
};

namespace NCsDataType
{
	typedef FECsDataType Type;
}

#pragma endregion DataType

// DataCollectionType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsDataCollectionType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsDataCollectionType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsDataCollectionType)

struct CSCORE_API EMCsDataCollectionType : public TCsEnumStructMap<FECsDataCollectionType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsDataCollectionType, FECsDataCollectionType, uint8)
};

#pragma endregion DataCollectionType

// LoadAsyncOrder
#pragma region

UENUM(BlueprintType)
enum class ECsLoadAsyncOrder : uint8
{
	// Default to Bulk
	None					UMETA(DisplayName = "None"),
	// Process Assets IN ORDER 1 by 1
	FirstToLast				UMETA(DisplayName = "First to Last"),
	// Group Assets, only get notification once ENTIRE Group is Finished
	Bulk					UMETA(DisplayName = "Bulk"),
	ECsLoadAsyncOrder_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsLoadAsyncOrder : public TCsEnumMap<ECsLoadAsyncOrder>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsLoadAsyncOrder, ECsLoadAsyncOrder)
};

namespace NCsLoadAsyncOrder
{
	typedef ECsLoadAsyncOrder Type;

	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type FirstToLast;
		extern CSCORE_API const Type Bulk;
		extern CSCORE_API const Type ECsLoadAsyncOrder_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion LoadAsyncOrder

// AssetType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsAssetType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsAssetType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsAssetType)

struct CSCORE_API EMCsAssetType : public TCsEnumStructMap<FECsAssetType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAssetType, FECsAssetType, uint8)
};

namespace NCsAssetType
{
	typedef FECsAssetType Type;
}

#pragma endregion DataType

// LoadAssetsType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsLoadAssetsType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsLoadAssetsType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsLoadAssetsType)

struct CSCORE_API EMCsLoadAssetsType : public TCsEnumStructMap<FECsLoadAssetsType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsLoadAssetsType, FECsLoadAssetsType, uint8)
};

#pragma endregion LoadAssetsType

// FCsCategoryMemberAssociation
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsCategoryMemberAssociation
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	FString Category;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	TArray<FString> Members;
};

#pragma endregion FCsCategoryMemberAssociation