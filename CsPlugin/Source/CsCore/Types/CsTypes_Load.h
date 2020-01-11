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
#define CS_CVAR_LOAD_FIRSTTOLAST 1
#define CS_CVAR_LOAD_BULK 2

namespace ECsLoadCached
{
	namespace Str
	{
		extern CSCORE_API const FString _Internal;// = TEXT("_Internal");
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
	CalculateResourceSizes		UMETA(DisplayName = "Calculate Resource Sizes"),
	SuppressLoadFlagsAllWarning	UMETA(DisplayName = "Suppress Load Flags All Warning"),
};

#define ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES 1

#pragma endregion LoadCode

// LoadFlags
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsLoadFlags : uint8
{
	Game		UMETA(DisplayName = "Game"),
	Game1P		UMETA(DisplayName = "Game First Person"),
	Game3P		UMETA(DisplayName = "Game Third Person"),
	Game3PLow	UMETA(DisplayName = "Game Third Person Low"),
	GameVR		UMETA(DisplayName = "Game VR"),
	UI			UMETA(DisplayName = "UI"),
	All			UMETA(DisplayName = "All"),
};

struct CSCORE_API EMCsLoadFlags : public TCsEnumFlagMap<ECsLoadFlags>
{
protected:
	EMCsLoadFlags() {}
	EMCsLoadFlags(const EMCsLoadFlags &) = delete;
	EMCsLoadFlags(EMCsLoadFlags &&) = delete;
public:
	~EMCsLoadFlags() {}
private:
	static EMCsLoadFlags* Instance;

public:
	static EMCsLoadFlags& Get();
};

namespace NCsLoadFlags
{
	namespace Ref
	{
		typedef ECsLoadFlags Type;

		extern CSCORE_API const Type Game;
		extern CSCORE_API const Type Game1P;
		extern CSCORE_API const Type Game3P;
		extern CSCORE_API const Type Game3PLow;
		extern CSCORE_API const Type GameVR;
		extern CSCORE_API const Type UI;
		extern CSCORE_API const Type All;
	}
}

#define CS_LOAD_FLAGS_NONE 0

#pragma endregion // LoadFlags

// LoadFlags_Editor
#pragma region

UENUM(BlueprintType)
namespace ECsLoadFlags_Editor
{
	enum Type
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
}

typedef ECsLoadFlags_Editor::Type TCsLoadFlags_Editor;

struct CSCORE_API EMCsLoadFlags_Editor : public TCsEnumMap<ECsLoadFlags_Editor::Type>
{
protected:
	EMCsLoadFlags_Editor() {}
	EMCsLoadFlags_Editor(const EMCsLoadFlags_Editor &) = delete;
	EMCsLoadFlags_Editor(EMCsLoadFlags_Editor &&) = delete;
public:
	~EMCsLoadFlags_Editor() {}
private:
	static EMCsLoadFlags_Editor* Instance;

public:
	static EMCsLoadFlags_Editor& Get();
};

namespace ECsLoadFlags_Editor
{
	namespace Ref
	{
		typedef ECsLoadFlags_Editor::Type Type;

		extern CSCORE_API const Type Game;
		extern CSCORE_API const Type Game1P;
		extern CSCORE_API const Type Game3P;
		extern CSCORE_API const Type Game3PLow;
		extern CSCORE_API const Type GameVR;
		extern CSCORE_API const Type UI;
		extern CSCORE_API const Type All;
		extern CSCORE_API const Type ECsLoadFlags_Editor_MAX;
	}

	FORCEINLINE const ECsLoadFlags& ToBaseType(const Type &EType)
	{
		if (EType == Type::Game) { return NCsLoadFlags::Ref::Game; }
		if (EType == Type::Game1P) { return NCsLoadFlags::Ref::Game1P; }
		if (EType == Type::Game3P) { return NCsLoadFlags::Ref::Game3P; }
		if (EType == Type::Game3PLow) { return NCsLoadFlags::Ref::Game3PLow; }
		if (EType == Type::GameVR) { return NCsLoadFlags::Ref::GameVR; }
		if (EType == Type::UI) { return NCsLoadFlags::Ref::UI; }
		if (EType == Type::All) { return NCsLoadFlags::Ref::All; }
		return NCsLoadFlags::Ref::All;
	}
}

#define ECS_LOAD_FLAGS_EDITOR_MAX (uint8)ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX

#pragma endregion // LoadFlags_Editor

// FCsResourceSize
#pragma region

USTRUCT(BlueprintType)
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
		Bytes = 0;
		Kilobytes = 0.0f;
		Megabytes = 0.0f;
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

	FString ToString()
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

	UPROPERTY(VisibleDefaultsOnly, Category = "Path")
	FSoftObjectPath Path;

	UPROPERTY(VisibleDefaultsOnly, Category = "Path")
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
};

#pragma endregion FCsSoftObjectPath

// FCsSoftObjectPath_Test
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSoftObjectPath_Test
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Path")
	FString Path;

	UPROPERTY(VisibleDefaultsOnly, Category = "Path")
	FCsResourceSize Size;

	FCsSoftObjectPath_Test() :
		Path(),
		Size()
	{
	}
};

#pragma endregion FCsSoftObjectPath_Test

// FCsTArraySoftObjectPath
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsTArraySoftObjectPath
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Reference")
	TArray<FCsSoftObjectPath> Paths;

	UPROPERTY(BlueprintReadOnly, Category = "Reference")
	TArray<FSoftObjectPath> Paths_Internal;

	UPROPERTY(VisibleDefaultsOnly, Category = "Reference")
	FCsResourceSize Size;

	FCsTArraySoftObjectPath() :
		Paths(),
		Paths_Internal(),
		Size()
	{
	}

	void Reset()
	{
		Paths.Reset();
		Paths_Internal.Reset();
		Size.Reset();
	}

	FORCEINLINE void CalculateSize()
	{
		Size.Reset();

		for (const FCsSoftObjectPath& Path : Paths)
		{
			Size += Path.Size;
		}
	}

	void Add(const FCsSoftObjectPath& Path)
	{
		Paths.Add(Path);
		Paths_Internal.Add(Path.Path);
		Size += Path.Size;
	}

	void AppendUnique(const FCsTArraySoftObjectPath& InPaths)
	{
		for (const FCsSoftObjectPath& Path : InPaths.Paths)
		{
			Paths.AddUnique(Path);
		}

		Paths_Internal.Reset(Paths.Num());

		for (const FCsSoftObjectPath& Path : Paths)
		{
			Paths_Internal.Add(Path.Path);
		}
		CalculateSize();
	}
};

#pragma endregion FCsTArraySoftObjectPath

// FCsTArraySoftObjectPath_Test
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsTArraySoftObjectPath_Test
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Reference")
	TArray<FCsSoftObjectPath_Test> Paths;

	UPROPERTY(VisibleDefaultsOnly, Category = "Reference")
	FCsResourceSize Size;

	FCsTArraySoftObjectPath_Test() :
		Paths(),
		Size()
	{
	}

	void Reset()
	{
		Paths.Reset();
		Size.Reset();
	}

	FORCEINLINE void CalculateSize()
	{
		Size.Reset();

		for (const FCsSoftObjectPath_Test& Path : Paths)
		{
			Size += Path.Size;
		}
	}
};

#pragma endregion FCsTArraySoftObjectPath_Test

// FCsStringAssetReference
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

#pragma endregion FCsStringAssetReference

// FCsTArrayStringAssetReference
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

#pragma endregion FCsTArrayStringAssetReference

// FCsDataMappingEntry
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataMappingEntry
{
	GENERATED_USTRUCT_BODY()

	/** Short Name - used to link with Backend */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FName ShortCode;

	UPROPERTY(VisibleDefaultsOnly, Category = "Data")
	uint16 LookUpCode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data", meta = (MustImplement = "CsData"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

	UPROPERTY(VisibleDefaultsOnly, Category = "Data")
	FCsTArrayStringAssetReference AssetReferences[ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX];

	FCsDataMappingEntry() :
		ShortCode(NAME_None),
		Data_LoadFlags(0)
	{
		LookUpCode = CS_INVALID_LOOK_UP_CODE_MAX;

		CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
	}

	FORCEINLINE void Set(const FName &InShortCode, UObject* InData)
	{
		ShortCode = InShortCode;
		Data = InData;
	}
};

#pragma endregion FCsDataMappingEntry

// FCsObjectPathLoadedInfo
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

#pragma endregion FCsObjectPathLoadedInfo

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
	CS_ENUM_STRUCT_MAP_BODY(EMCsDataType, FECsDataType, uint8)
};

namespace NCsDataType
{
	typedef FECsDataType Type;
}

#pragma endregion AssetType

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

namespace NCsDataCollectionType
{
	typedef FECsDataCollectionType Type;
}

#pragma endregion DataCollectionType

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
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsAssetType)
};

namespace ECsAssetType
{
}

// GetAssetTypeStaticClass
typedef UClass*(*TCsGetAssetTypeStaticClass)(const FECsAssetType&);

#pragma endregion AssetType

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
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsLoadAssetsType)
};

#pragma endregion LoadAssetsType

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayloadOld
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FName ShortCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FECsDataType DataType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TEnumAsByte<ECsLoadFlags_Editor::Type> LoadFlags;

	FORCEINLINE FCsPayloadOld& operator=(const FCsPayloadOld& B)
	{
		ShortCode = B.ShortCode;
		DataType = B.DataType;
		LoadFlags = B.LoadFlags;
		return *this;
	}

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
	CS_ENUM_MAP_BODY(EMCsLoadAsyncOrder, ECsLoadAsyncOrder)
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<UObject> Data;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FName ShortCode;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//ECsLoadFlags_Editor Load_Flags;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FCsTArraySoftObjectPath Paths;

	FCsPayload_Data() :
		Data(),
		ShortCode(NAME_None),
		Paths()
	{
	}

	void Populate();
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> DataTable;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FName ShortCode;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//ECsLoadFlags_Editor Load_Flags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bAllRows;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> Rows;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FCsTArraySoftObjectPath Paths;

	FCsPayload_DataTable() :
		DataTable(),
		ShortCode(NAME_None),
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
		DataTable.Reset();
		ShortCode = NAME_None;
		bAllRows = false;
		Rows.Reset();
		Paths.Reset();
	}

	void Populate();
};

#pragma endregion FCsPayload_DataTable

	// FCsPayload
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FCsPayload_Data> Datas;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FCsPayload_DataTable> DataTables;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FCsTArraySoftObjectPath Paths;

	FCsPayload() :
		Datas(),
		DataTables(),
		Paths()
	{
	}

	void Reset()
	{
		Datas.Reset();
		DataTables.Reset();
		Paths.Reset();
	}

	void Populate()
	{
		Paths.Reset();

		for (FCsPayload_Data& Data : Datas)
		{
			Data.Populate();

			Paths.AppendUnique(Data.Paths);
		}

		for (FCsPayload_DataTable& DataTable : DataTables)
		{
			DataTable.Populate();

			Paths.AppendUnique(DataTable.Paths);
		}
	}
};

#pragma endregion FCsPayload

		// Test
#pragma region

			// FCsPayload_Test_Data
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload_Test_Data
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the Data asset. This should be unique. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName Data;

	/** Short unique name for Data. By default this will be the same
	    name as the Data asset. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FName ShortCode;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//ECsLoadFlags_Editor Load_Flags;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FCsSoftObjectPath_Test Path;

	FCsPayload_Test_Data() :
		Data(NAME_None),
		ShortCode(NAME_None),
		Path()
	{
	}

	void Populate()
	{

	}
};

#pragma endregion FCsPayload_Data

			// FCsPayload_Test_DataTable
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload_Test_DataTable
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the DataTable. This should be unique. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName DataTable;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//ECsLoadFlags_Editor Load_Flags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bAllRows;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> Rows;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FCsTArraySoftObjectPath_Test Paths;

	FCsPayload_Test_DataTable() :
		DataTable(),
		bAllRows(false),
		Rows(),
		Paths()
	{
	}

	void Populate()
	{

	}
};

#pragma endregion FCsPayload_Test_DataTable

			// FCsPayload_Test
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload_Test : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FCsPayload_Test_Data> Datas;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FCsPayload_Test_DataTable> DataTables;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FCsTArraySoftObjectPath_Test Paths;

	FCsPayload_Test() :
		Datas(),
		DataTables(),
		Paths()
	{
	}

	void Populate()
	{

	}
};

#pragma endregion FCsPayload_Test

#pragma endregion Test

#pragma endregion Payload

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