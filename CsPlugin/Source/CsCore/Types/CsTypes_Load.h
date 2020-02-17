// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

// Json
#include "Json.h"
#include "JsonObjectConverter.h"
// DataTable
#include "Engine/DataTable.h"

#include "CsTypes_Load.generated.h"
#pragma once

#define CS_CVAR_LOAD_UNSET -1
#define CS_CVAR_LOAD_NONE 0
#define CS_CVAR_LOAD_FICSTTOLAST 1
#define CS_CVAR_LOAD_BULK 2

namespace ECsLoadCached
{
	namespace Str
	{
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
	RecursiveLoadDataTable		UMETA(DisplayName = "Recursive Load DataTable",)		// 3
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

class UObject;

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

// FCsResourceSize
#pragma region

USTRUCT()
struct CSCORE_API FCsResourceSize
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Size")
	int32 Bytes;

	UPROPERTY(VisibleDefaultsOnly, Category = "Size")
	float Kilobytes;

	UPROPERTY(VisibleDefaultsOnly, Category = "Size")
	float Megabytes;

	FCsResourceSize()
	{
		Reset();
	}

	FORCEINLINE FCsResourceSize& operator=(const FCsResourceSize& B)
	{
		Bytes = B.Bytes;
		Kilobytes = B.Kilobytes;
		Megabytes = B.Megabytes;
		return *this;
	}

	FORCEINLINE FCsResourceSize& operator+=(const FCsResourceSize& B)
	{
		Bytes += B.Bytes;
		Kilobytes += B.Kilobytes;
		Megabytes += B.Megabytes;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsResourceSize& B) const
	{
		return Bytes == B.Bytes && Kilobytes == B.Kilobytes && Megabytes == B.Megabytes;
	}

	FORCEINLINE void Reset()
	{
		Bytes = 0;
		Kilobytes = 0.0f;
		Megabytes = 0.0f;
	}

	void SetBytes(const int32& InBytes)
	{
		Bytes	  = InBytes;
		Kilobytes = Bytes * FMath::Pow(10, -3);
		Megabytes = Bytes * FMath::Pow(10, -6);
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("%f mb, %f kb, %d b"), Megabytes, Kilobytes, Bytes);
	}
};

#pragma endregion FCsResourceSize

// FCsSoftObjectPath
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSoftObjectPath
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly)
	FSoftObjectPath Path;

	UPROPERTY(VisibleDefaultsOnly)
	FCsResourceSize Size;

	FCsSoftObjectPath() :
		Path(),
		Size()
	{
	}

	FORCEINLINE bool operator==(const FCsSoftObjectPath& B) const
	{
		return Path.GetAssetPathName() == B.Path.GetAssetPathName() && Path.GetSubPathString() == B.Path.GetSubPathString() && Size == B.Size;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("[%s] @ %s"), *(Size.ToString()), *(Path.ToString()));
	}
};

#pragma endregion FCsSoftObjectPath

// FCsTArraySoftObjectPath
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsTArraySoftObjectPath
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TArray<FCsSoftObjectPath> Paths;

	UPROPERTY(Transient, BlueprintReadOnly)
	TMap<FName, FCsSoftObjectPath> Map;

	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<FSoftObjectPath> Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	TMap<FName, FSoftObjectPath> InternalMap;

	UPROPERTY(VisibleDefaultsOnly)
	FCsResourceSize Size;

	FCsTArraySoftObjectPath() :
		Paths(),
		Map(),
		Internal(),
		InternalMap(),
		Size()
	{
	}

	void Reset()
	{
		Paths.Reset();
		Map.Reset();
		Internal.Reset();
		InternalMap.Reset();
		Size.Reset();
	}

	void BuildFromPaths()
	{
		for (const FCsSoftObjectPath& Path : Paths)
		{
			const FName Name = Path.Path.GetAssetPathName();

			// Map
			{
				FCsSoftObjectPath& Value = Map.FindOrAdd(Name);
				Value = Path;
			}
			// InternalMap
			{
				FSoftObjectPath& Value = InternalMap.FindOrAdd(Name);
				Value = Path.Path;
			}
		}
		
		// Reset Paths since there could be duplicates
		Paths.Reset(Paths.Max());
		Internal.Reset(Paths.Max());

		for (const TPair<FName, FCsSoftObjectPath>& Pair : Map)
		{
			const FCsSoftObjectPath& Path = Pair.Value;

			Paths.Add(Path);
			Internal.Add(Path.Path);
		}
		CalculateSize();
	}

#if WITH_EDITOR
	
	void BuildFromMap()
	{
		TArray<FName> Keys;
		const int32 Count = Map.GetKeys(Keys);

		Paths.Reset(Count);
		Internal.Reset(Count);
		InternalMap.Reset();

		for (const TPair<FName, FCsSoftObjectPath>& Pair : Map)
		{
			const FCsSoftObjectPath& Path = Pair.Value;

			Paths.Add(Path);
			Internal.Add(Path.Path);
			InternalMap.Add(Pair.Key, Path.Path);
		}
		CalculateSize();
	}

#endif // #if WITH_EDITOR

	FORCEINLINE void CalculateSize()
	{
		Size.Reset();

		for (const FCsSoftObjectPath& Path : Paths)
		{
			Size += Path.Size;
		}
	}

#if WITH_EDITOR

	void Append(const FCsTArraySoftObjectPath& InPaths)
	{
		Map.Append(InPaths.Map);

		BuildFromMap();
	}

#endif // #if WITH_EDITOR
};

#pragma endregion FCsTArraySoftObjectPath

// StringAssetReference
#pragma region

USTRUCT()
struct CSCORE_API FCsStringAssetReference
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Reference")
	FString Reference;

	UPROPERTY()
	FStringAssetReference Reference_Internal;

	UPROPERTY(VisibleDefaultsOnly, Category = "Reference")
	FCsResourceSize Size;

	FORCEINLINE FStringAssetReference* Get()
	{
		return &Reference_Internal;
	}
};

#pragma endregion StringAssetReference

// TArrayStringAssetReference
#pragma region

USTRUCT()
struct CSCORE_API FCsTArrayStringAssetReference
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Reference")
	TArray<FCsStringAssetReference> References;

	UPROPERTY(VisibleDefaultsOnly, Category = "Reference")
	FCsResourceSize Size;

	void Reset()
	{
		References.Reset();
		Size.Reset();
	}

	FORCEINLINE void Get(TArray<FStringAssetReference>& OutReferences)
	{
		for (const FCsStringAssetReference& Reference : References)
		{
			OutReferences.Add(Reference.Reference_Internal);
		}
	}

	FORCEINLINE void CalculateSize()
	{
		Size.Reset();

		for (const FCsStringAssetReference& Reference : References)
		{
			Size += Reference.Size;
		}
	}
};

#pragma endregion TArrayStringAssetReference

// DataMappingEntry
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataMappingEntry
{
	GENERATED_USTRUCT_BODY()

	/** Short Name - used to link with Backend */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FName ShortCode;

	UPROPERTY(VisibleDefaultsOnly, Category = "Data")
	uint16 LookUpCode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data", meta = (MustImplement = "CsDataInterface"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

	UPROPERTY(VisibleDefaultsOnly, Category = "Data")
	FCsTArrayStringAssetReference AssetReferences[ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX];

	FCsDataMappingEntry() :
		ShortCode(NAME_None),
		Data_LoadFlags(0)
	{
		LookUpCode = UINT16_MAX;

		CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE void Set(const FName &InShortCode, UObject* InData)
	{
		ShortCode = InShortCode;
		Data = InData;
	}
};

#pragma endregion DataMappingEntry

// ObjectPathLoadedInfo
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsObjectPathLoadedInfo
{
public:

	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FSoftObjectPath Path;

	UPROPERTY()
	int32 Count;

	UPROPERTY()
	FCsResourceSize Size;

	UPROPERTY()
	float Time;

	FCsObjectPathLoadedInfo() :
		Path(),
		Count(0),
		Size(),
		Time(0.0f)
	{
	}

	void Reset()
	{
		Path.Reset();
		Count = 0;
		Size.Reset();
		Time = 0.0f;
	}
};

#pragma endregion ObjectPathLoadedInfo

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

// Payload
#pragma region

	// FCsPayload_Data
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload_Data
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the Data Object. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FName Name;

	/** Object that implements the interface: ICsData. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (MustImplement = "CsData"))
	TSoftClassPtr<UObject> Data;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//ECsLoadFlags_Editor Data_LoadFlags;

	/** All ObjectPaths and Resource Sizes (Memory Size) for Data. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FCsTArraySoftObjectPath Paths;

	FCsPayload_Data() :
		Name(NAME_None),
		Data(),
		Paths()
	{
	}

	FORCEINLINE bool IsValid() const
	{
		return Data.IsValid();
	}

	FORCEINLINE bool IsPopulated() const
	{
		return IsValid() && Name != NAME_None;
	}

	void Reset()
	{
		Name = NAME_None;
		Data.Reset();
		Paths.Reset();
	}

#if WITH_EDITOR

	/**
	* Get all ObjectPaths and Resource Sizes (Memory Size) from Data and 
	*  store that in Paths.
	*/
	void Populate();

#endif // #if WITH_EDITOR
};

#pragma endregion FCsPayload_Data

	// FCsPayload_DataTable
#pragma region

class UDataTable;

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload_DataTable
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the DataTable */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> DataTable;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//ECsLoadFlags_Editor DataTable_LoadFlags;

	/** Whether to store all rows or use specific row names of 
	    the DataTable to store ObjectPaths for in Paths. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bAllRows;

	/** Specific row names of the DataTable to store ObjectPaths 
		for in Paths. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> Rows;

	/** All ObjectPaths and Resource Sizes (Memory Size) for DataTable. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FCsTArraySoftObjectPath Paths;

	FCsPayload_DataTable() :
		Name(NAME_None),
		DataTable(),
		bAllRows(false),
		Rows(),
		Paths()
	{
	}

	FORCEINLINE bool IsValid() const
	{
		return DataTable.IsValid();
	}

	FORCEINLINE bool IsPopulated() const
	{
		return IsValid() && Name != NAME_None;
	}

	void Reset()
	{
		Name = NAME_None;
		DataTable.Reset();
		bAllRows = false;
		Rows.Reset();
		Paths.Reset();
	}

#if WITH_EDITOR

	/**
	* Get all ObjectPaths and Resource Sizes (Memory Size) from DataTable and
	*  store that in Paths.
	*/
	void Populate();

#endif // #if WITH_EDITOR
};

#pragma endregion FCsPayload_DataTable

	// FCsPayload
#pragma region

class UDataTable;

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	/** List of all Payload information related to objects that
	    implement the interface: ICsData. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "Name"))
	TArray<FCsPayload_Data> Datas;

	UPROPERTY(Transient, BlueprintReadOnly)
	TMap<FName, FCsPayload_Data> DataMap;

	/** List of all Payload information related to DataTables. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "Name"))
	TArray<FCsPayload_DataTable> DataTables;

	UPROPERTY(Transient, BlueprintReadOnly)
	TMap<FName, FCsPayload_DataTable> DataTableMap;

	/** All ObjectPaths and Resource Sizes (Memory Size) for Datas and DataTables. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FCsTArraySoftObjectPath Paths;

	FCsPayload() :
		Datas(),
		DataMap(),
		DataTables(),
		DataTableMap(),
		Paths()
	{
	}

	void Reset()
	{
		Datas.Reset();
		DataMap.Reset();
		DataTables.Reset();
		DataTableMap.Reset();
		Paths.Reset();
	}

#if WITH_EDITOR

	/**
	*
	*/
	void BuildMaps()
	{
		// Datas
		DataMap.Reset();

		for (FCsPayload_Data& Data : Datas)
		{
			if (Data.IsPopulated())
				DataMap.Add(Data.Name, Data);
		}
		// DataTables
		DataTableMap.Reset();

		for (FCsPayload_DataTable& DataTable : DataTables)
		{
			if (DataTable.IsPopulated())
				DataTableMap.Add(DataTable.Name, DataTable);
		}
	}

	/**
	*
	*/
	void BuildFromMaps()
	{
		// Datas
		Datas.Reset(DataMap.Num());

		for (TPair<FName, FCsPayload_Data>& Pair : DataMap)
		{
			Datas.Add(Pair.Value);
		}
		// DataTables
		DataTables.Reset(DataTableMap.Num());

		for (TPair<FName, FCsPayload_DataTable>& Pair : DataTableMap)
		{
			DataTables.Add(Pair.Value);
		}
	}

	/**
	* Get all ObjectPaths and Resource Sizes (Memory Size) from Datas and
	*  DataTables and store that in Paths. This also calls Populate on each
	*  Data and DataTable.
	*/
	void Populate()
	{
		Paths.Reset();

		for (TPair<FName, FCsPayload_Data>& Pair : DataMap)
		{
			FCsPayload_Data& Data = Pair.Value;

			Data.Populate();

			Paths.Append(Data.Paths);
		}

		for (TPair<FName, FCsPayload_DataTable>& Pair : DataTableMap)
		{
			FCsPayload_DataTable& DataTable = Pair.Value;

			DataTable.Populate();

			Paths.Append(DataTable.Paths);
		}
	}

	/**
	*
	*
	* @param DataTableMap
	* @param AllRows
	*/
	void Append(TMap<FName, UDataTable*>& InDataTableMap, const bool& AllRows = false);

	/**
	* 
	*
	* @param Payload
	*/
	void Append(const FCsPayload& Payload);

	/**
	*
	*
	* @param PayloadMap
	*/
	void Append(const TMap<FName, FCsPayload>& PayloadMap);

#endif // #if WITH_EDITOR
};

#pragma endregion FCsPayload

#pragma endregion Payload

// DataEntry
#pragma region

	// FCsDataEntry_Data
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataEntry_Data : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<UObject> Data;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//int32 Data_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Data_Class;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FCsTArraySoftObjectPath Paths;

	FCsDataEntry_Data() :
		Name(NAME_None),
		Data(),
		Data_Internal(nullptr),
		Data_Class(nullptr),
		Paths()
	{
	}

	void Reset()
	{
		Name = NAME_None;
		Data.Reset();
		Data_Internal = nullptr;
		Data_Class = nullptr;
		Paths.Reset();
	}

	FORCEINLINE UObject* Get() { return Data_Internal; }

	FORCEINLINE UClass* GetClass() { return Data_Class; }
};

#pragma endregion FCsPayload_Data

	// FCsDataEntry_DataTable
#pragma region

class UDataTable;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataEntry_DataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool bPopulateOnSave;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> DataTable;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//int32 DataTable_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UDataTable* DataTable_Internal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bAllRows;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> Rows;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FCsTArraySoftObjectPath Paths;

	FCsDataEntry_DataTable() :
		bPopulateOnSave(false),
		Name(NAME_None),
		DataTable(),
		DataTable_Internal(nullptr),
		bAllRows(false),
		Rows(),
		Paths()
	{
	}

	FORCEINLINE bool IsValid() const
	{
		return DataTable.IsValid();
	}

	void Reset()
	{
		Name = NAME_None;
		DataTable.Reset();
		DataTable_Internal = nullptr;
		bAllRows = false;
		Rows.Reset();
		Paths.Reset();
	}

	FORCEINLINE UDataTable* Get() { return DataTable_Internal; }

#if WITH_EDITOR

	/**
	* Get all ObjectPaths and Resource Sizes (Memory Size) from DataTable and
	*  store that in Paths.
	*/
	void Populate();

#endif // #if WITH_EDITOR
};

#pragma endregion FCsPayload_DataTable

#pragma endregion DataEntry

// FCsDataRootSetContainer
#pragma region

class UCsDataRootSet;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataRootSetContainer
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftClassPtr<UCsDataRootSet> Data;

	UPROPERTY(Transient, BlueprintReadOnly)
	UCsDataRootSet* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Data_Class;

	FCsDataRootSetContainer() :
		Data(nullptr),
		Data_Internal(nullptr),
		Data_Class(nullptr)
	{
	}

	FORCEINLINE UCsDataRootSet* Get() const { return Data_Internal; }

	template<typename T>
	FORCEINLINE T* Get() const { return Cast<T>(Get()); }

	FORCEINLINE UClass* GetClass() const { return Data_Class; }
};

#pragma endregion FCsDataRootSetContainer

// FCsDataTable
#pragma region

class UDataTable;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataTable
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UDataTable* Data_Internal;

	FCsDataTable() :
		Data(nullptr),
		Load_Flags(0),
		Data_Internal(nullptr)
	{
	}

	FORCEINLINE UDataTable* Get() const { return Data_Internal; }
};

#pragma endregion FCsDataTable

// FCsActor
#pragma region

class AActor;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsActor
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftClassPtr<AActor> Actor;

	UPROPERTY()
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly)
	AActor* Actor_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Actor_Class;

	UPROPERTY(Transient, BlueprintReadOnly)
	TSubclassOf<AActor> Actor_SubclassOf;

	FCsActor() :
		Actor(nullptr),
		Load_Flags(0),
		Actor_Internal(nullptr),
		Actor_Class(nullptr),
		Actor_SubclassOf(nullptr)
	{
	}

	FORCEINLINE AActor* Get() const { return Actor_Internal; }
	
	template<typename T>
	FORCEINLINE T* Get() const { return Cast<T>(Get()); }

	FORCEINLINE UClass* GetClass() const { return Actor_Class; }

	template<typename T>
	FORCEINLINE T* GetClass() const { return Cast<T>(GetClass()); }

	FORCEINLINE TSubclassOf<AActor> GetSubclassOf() const { return Actor_SubclassOf; }
};

#pragma endregion FCsActor

// FCsTexture
#pragma region

class UTexture;

USTRUCT(BlueprintType)
struct CSCORE_API FCsTexture
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftObjectPtr<UTexture> Texture;

	UPROPERTY()
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UTexture* Texture_Internal;

	FCsTexture() :
		Texture(nullptr),
		Load_Flags(0),
		Texture_Internal(nullptr)
	{
	}

	FORCEINLINE UTexture* Get() const { return Texture_Internal; }
};

#pragma endregion FCsTexture

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

	UPROPERTY(VisibleDefaultsOnly, Category = "Member")
	FString Category;

	UPROPERTY(VisibleDefaultsOnly, Category = "Member")
	TArray<FString> Members;
};

#pragma endregion FCsCategoryMemberAssociation

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayloadOld
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FName ShortCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FECsDataType DataType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	ECsLoadFlags_Editor LoadFlags;

	FORCEINLINE bool operator==(const FCsPayloadOld& B) const
	{
		if (ShortCode != B.ShortCode) { return false; }
		if (DataType != B.DataType) { return false; }
		if (LoadFlags != B.LoadFlags) { return false; }
		return true;
	}

	FORCEINLINE bool operator!=(const FCsPayloadOld& B) const
	{
		return !(*this == B);
	}
};

// FCsTArrayPayload
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsTArrayPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TArray<FCsPayloadOld> Payloads;

	FORCEINLINE FCsTArrayPayload& operator=(const FCsTArrayPayload& B)
	{
		Payloads.Reset();

		for (const FCsPayloadOld& Payload : B.Payloads)
		{
			Payloads.Add(Payload);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const FCsTArrayPayload& B) const
	{
		const int32 CountA = Payloads.Num();
		const int32 CountB = B.Payloads.Num();

		if (CountA != CountB)
			return false;

		for (int32 I = 0; I < CountA; ++I)
		{
			if (Payloads[I] != B.Payloads[I])
				return false;
		}
		return true;
	}

	FORCEINLINE bool operator!=(const FCsTArrayPayload& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion FCsTArrayPayload

// JsonWriter
typedef bool(*TCsWriteStructToJson_Internal)(UProperty*, TSharedRef<class TJsonWriter<TCHAR>> &, void*, UScriptStruct* const &);
typedef bool(*TCsWriteObjectToJson_Internal)(UProperty*, TSharedRef<class TJsonWriter<TCHAR>> &, void*, UClass* const &);
// JsonReader
typedef bool(*TCsReadStructFromJson_Internal)(UProperty*, TSharedPtr<class FJsonObject> &, void*, UScriptStruct* const &);
typedef bool(*TCsReadObjectFromJson_Internal)(UProperty*, TSharedPtr<class FJsonObject> &, void*, UClass* const &);
// AssetReferences
typedef bool(*TCsGetAssetReferencesFromStruct_Internal)(UProperty*, void*, UScriptStruct* const &, const ECsLoadFlags&, TArray<FCsStringAssetReference>&, const int32&);
typedef bool(*TCsGetAssetReferencesFromObject_Internal)(UProperty*, void*, UClass* const &, const ECsLoadFlags&, TArray<FCsStringAssetReference>&, const int32&);
// Load TSoftObjectPtrs
typedef bool(*TCsLoadStructWithTSoftObjectPtrs_Internal)(UProperty*, const FString&, void*, UScriptStruct* const &, const ECsLoadFlags&);
typedef bool(*TCsLoadObjectWithTSoftObjectPtrs_Internal)(UProperty*, const FString&, void*, UClass* const &, const ECsLoadFlags&);
// Get Members
typedef void*(*TCsGetStructMember_Internal)(UProperty*, void*, UScriptStruct* const &, const FString&);

typedef UScriptStruct*(*TCsGetScriptStructMember_Internal)(UProperty*, void*, UScriptStruct* const &, const FString &);

typedef void*(*TCsGetObjectMember_Internal)(UProperty*, void*, UClass* const &, const FString &);
// Enums
typedef bool(*TCsCheckStructWithEnum_Internal)(UProperty*, const FString&, void*, UScriptStruct* const &);
typedef bool(*TCsCheckObjectWithEnum_Internal)(UProperty*, const FString&, void*, UClass* const &);