// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"
#include "Types/Enum/CsEnumFlagMap.h"
// Log
#include "Utility/CsLog.h"
// Json
#include "Json.h"
#include "JsonObjectConverter.h"
// DataTable
#include "Engine/DataTable.h"

#include "CsTypes_Load.generated.h"

#define CS_CVAR_LOAD_UNSET -1
#define CS_CVAR_LOAD_NONE 0
#define CS_CVAR_LOAD_FICSTTOLAST 1
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
	RecursiveUnloadDataTable	UMETA(DisplayName = "Recursive Unload DataTable", )		// 1
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

// ObjectPathDependencyGroup
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsObjectPathDependencyGroup : uint8
{
	// Texture | Render Target | Font
	Texture								UMETA(DisplayName = "Texture"),
	// Material | Material Instance
	Material							UMETA(DisplayName = "Material"),
	StaticMesh							UMETA(DisplayName = "Static Mesh"),
	// Skeletal Mesh | Physics Asset | Skeleton
	Skeletal							UMETA(DisplayName = "Skeletal"),
	// TODO: Need a way to capture other sound plugins (i.e. Wise)
	Sound								UMETA(DisplayName = "Sound"),
	// Particle System | TODO: Niagara (need to be careful what Niagara references)
	FX									UMETA(DisplayName = "FX"),
	// Anim Sequence | Blend Space
	AnimationAsset						UMETA(DisplayName = "Animation Asset"),
	// Anim Montage | Anim Composite
	AnimComposite						UMETA(DisplayName = "Anim Composite"),
	// General umbrella of blueprints: Anim Blueprint, ... etc
	Blueprint							UMETA(DisplayName = "Blueprint"),
	// IMovieScenePlayer (UMovieSceneSequencePlayer) | IMovieScenePlaybackClient | IMovieSceneBindingOwnerInterface | UMovieSceneSignedObject
	Sequencer							UMETA(DisplayName = "Sequencer"),
	DataTable							UMETA(DisplayName = "DataTable"),
	// Catch all for anything not categorized
	Other								UMETA(DisplayName = "Other"),
	ECsObjectPathDependencyGroup_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsObjectPathDependencyGroup : public TCsEnumMap<ECsObjectPathDependencyGroup>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsObjectPathDependencyGroup, ECsObjectPathDependencyGroup)
};

namespace NCsObjectPathDependencyGroup
{
	typedef ECsObjectPathDependencyGroup Type;

	namespace Ref
	{
		extern CSCORE_API const Type Texture;
		extern CSCORE_API const Type Material;
		extern CSCORE_API const Type StaticMesh;
		extern CSCORE_API const Type Skeletal;
		extern CSCORE_API const Type Sound;
		extern CSCORE_API const Type FX;
		extern CSCORE_API const Type AnimationAsset;
		extern CSCORE_API const Type AnimComposite;
		extern CSCORE_API const Type Blueprint;
		extern CSCORE_API const Type Sequencer;
		extern CSCORE_API const Type DataTable;
		extern CSCORE_API const Type Other;
		extern CSCORE_API const Type ECsObjectPathDependencyGroup_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion ObjectPathDependencyGroup

// FCsResourceSize
#pragma region

USTRUCT()
struct CSCORE_API FCsResourceSize
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	int32 Bytes;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	float Kilobytes;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
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

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	FSoftObjectPath Path;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	FCsResourceSize Size;

	FCsSoftObjectPath() :
		Path(),
		Size()
	{
	}

	FORCEINLINE bool operator==(const FCsSoftObjectPath& B) const
	{
		return Path.GetAssetPathName() == B.Path.GetAssetPathName() && Path.GetSubPathString() == B.Path.GetSubPathString();
	}

	FORCEINLINE bool operator!=(const FCsSoftObjectPath& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE FString ToString() const
	{
		return FString::Printf(TEXT("[%s] @ %s"), *(Size.ToString()), *(Path.ToString()));
	}

	FORCEINLINE friend uint32 GetTypeHash(FCsSoftObjectPath const& This)
	{
		return GetTypeHash(This.Path);
	}
};

#pragma endregion FCsSoftObjectPath

// FCsTArraySoftObjectPath
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsTArraySoftObjectPath
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	TArray<FCsSoftObjectPath> Paths;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	TSet<FCsSoftObjectPath> Set;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	TArray<FSoftObjectPath> Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	TSet<FSoftObjectPath> InternalSet;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	FCsResourceSize Size;

	FCsTArraySoftObjectPath() :
		Paths(),
		Set(),
		Internal(),
		InternalSet(),
		Size()
	{
	}

	void Reset()
	{
		Paths.Reset(Paths.Max());
		Set.Reset();
		Internal.Reset(Internal.Max());
		InternalSet.Reset();
		Size.Reset();
	}

	void BuildFromPaths()
	{
		for (const FCsSoftObjectPath& Path : Paths)
		{
			Set.Add(Path);
			InternalSet.Add(Path.Path);
		}
		
		// Reset Paths since there could be duplicates
		Paths.Reset(Paths.Max());
		Internal.Reset(Paths.Max());

		for (const FCsSoftObjectPath& Path : Set)
		{
			Paths.Add(Path);
			Internal.Add(Path.Path);
		}
		CalculateSize();
	}

#if WITH_EDITOR
	
	void BuildFromSet()
	{
		const int32 Count = Set.Num();

		Paths.Reset(Count);
		Internal.Reset(Count);
		InternalSet.Reset();

		for (const FCsSoftObjectPath& Path : Set)
		{
			Paths.Add(Path);
			Internal.Add(Path.Path);
			InternalSet.Add(Path.Path);
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
		Set.Append(InPaths.Set);

		BuildFromSet();
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

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	FString Reference;

	UPROPERTY()
	FStringAssetReference Reference_Internal;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
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

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	TArray<FCsStringAssetReference> References;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	FName ShortCode;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	uint16 LookUpCode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load", meta = (MustImplement = "CsDataInterface"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(EditAnywhere, Category = "CsCore|Load", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	FCsTArrayStringAssetReference AssetReferences[(uint8)ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX];

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

// FCsLoadHandle
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsLoadHandle
{
	GENERATED_USTRUCT_BODY()

public:

	static const FCsLoadHandle Invalid;

public:

	UPROPERTY()
	int32 Index;

	UPROPERTY()
	FGuid Handle;

	FCsLoadHandle() :
		Index(INDEX_NONE),
		Handle()
	{
	}

	FORCEINLINE bool operator==(const FCsLoadHandle& B) const
	{
		return Index == B.Index && Handle == B.Handle;
	}

	FORCEINLINE bool operator!=(const FCsLoadHandle& B) const
	{
		return !(*this == B);
	}

	friend uint32 GetTypeHash(const FCsLoadHandle& InHandle)
	{
		return static_cast<uint32>(InHandle.Index) ^ GetTypeHash(InHandle.Handle);
	}

	FORCEINLINE bool IsValid() const
	{
		return Index > INDEX_NONE && Handle.IsValid();
	}

	FORCEINLINE void New()
	{
		Handle = Handle.NewGuid();
	}

	FORCEINLINE void Reset()
	{
		Handle.Invalidate();
	}
};

#pragma endregion FCsLoadHandle

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	FName Name;

	/** Object that implements the interface: ICsData. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load", meta = (MustImplement = "CsData"))
	TSoftClassPtr<UObject> Data;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//ECsLoadFlags_Editor Data_LoadFlags;

	/** All ObjectPaths and Resource Sizes (Memory Size) for Data. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	TSoftObjectPtr<UDataTable> DataTable;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//ECsLoadFlags_Editor DataTable_LoadFlags;

	/** Whether to store all rows or use specific row names of 
	    the DataTable to store ObjectPaths for in Paths. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	bool bAllRows;

	/** Specific row names of the DataTable to store ObjectPaths 
		for in Paths. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	TSet<FName> Rows;

	/** All ObjectPaths and Resource Sizes (Memory Size) for DataTable. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	FCsTArraySoftObjectPath Paths;

	/** */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	TMap<FName, FCsTArraySoftObjectPath> PathsByRowMap;

	FCsPayload_DataTable() :
		Name(NAME_None),
		DataTable(),
		bAllRows(false),
		Rows(),
		Paths(),
		PathsByRowMap()
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
		PathsByRowMap.Reset();
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

	UPROPERTY()
	int32 Index;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	bool bUpdateDataRootSetOnSave;

	/** List of all Payload information related to objects that
	    implement the interface: ICsData. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (TitleProperty = "Name"))
	TArray<FCsPayload_Data> Datas;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	TMap<FName, FCsPayload_Data> DataMap;

	/** List of all Payload information related to DataTables. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (TitleProperty = "Name"))
	TArray<FCsPayload_DataTable> DataTables;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	TMap<FName, FCsPayload_DataTable> DataTableMap;

	/** All ObjectPaths and Resource Sizes (Memory Size) for Datas and DataTables. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	FCsTArraySoftObjectPath Paths;

	FCsPayload() :
		Index(INDEX_NONE),
		bUpdateDataRootSetOnSave(true),
		Datas(),
		DataMap(),
		DataTables(),
		DataTableMap(),
		Paths()
	{
	}

	FORCEINLINE FCsPayload& operator=(const FCsPayload& B)
	{
		bUpdateDataRootSetOnSave = B.bUpdateDataRootSetOnSave;
		Datas = B.Datas;
		DataMap = B.DataMap;
		DataTables = B.DataTables;
		DataTableMap = B.DataTableMap;
		Paths = B.Paths;
		return *this;
	}

	FORCEINLINE void SetIndex(const int32& InIndex)
	{
		Index = InIndex;
	}

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
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

	UPROPERTY()
	int32 Index;

	UPROPERTY(BlueprintReadOnly, Category = DataTable)
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	bool bPopulateOnSave;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (MustImplement = "CsData"))
	TSoftClassPtr<UObject> Data;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//int32 Data_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	UClass* Data_Class;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	FCsTArraySoftObjectPath Paths;

	FCsDataEntry_Data() :
		Index(INDEX_NONE),
		Name(NAME_None),
		bPopulateOnSave(false),
		Data(),
		Data_Internal(nullptr),
		Data_Class(nullptr),
		Paths()
	{
	}

	FORCEINLINE FCsDataEntry_Data& operator=(const FCsDataEntry_Data& B)
	{
		Name = B.Name;
		bPopulateOnSave = B.bPopulateOnSave;
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		Data_Class = B.Data_Class;
		Paths = B.Paths;
		return *this;
	}

	FORCEINLINE void SetIndex(const int32& InIndex)
	{
		Index = InIndex;
	}

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
	}

	void Reset()
	{
		Data = nullptr;
		Data_Internal = nullptr;
		Data_Class = nullptr;
		Paths.Reset();
	}

	FORCEINLINE UObject* Get() { return Data_Internal; }

	template<typename T>
	FORCEINLINE T* Get(){ return Cast<T>(Get()); }

	FORCEINLINE UObject* GetChecked(const FString& Context)
	{
		checkf(Data_Internal, TEXT("%s: Failed to load Data with Entry: %s @ Path: %s."), *Context, *(Name.ToString()), *(Data.ToSoftObjectPath().ToString()));

		return Data_Internal;
	}

	template<typename T>
	FORCEINLINE T* GetChecked(const FString& Context)
	{
		checkf(Cast<T>(GetChecked(Context)), TEXT("%s: Failed to cast Object: %s with Class: %s to type: T."), *Context, *(Data_Internal->GetName()), *(Data_Class->GetName()));

		return Cast<T>(GetChecked(Context));
	}

	template<typename InterfaceType>
	FORCEINLINE InterfaceType* GetInterfaceChecked(const FString& Context)
	{
		static_assert(std::is_abstract<InterfaceType>(), "FCsDataEntry_Data::GetInterfaceChecked: InterfaceType must be Abstract.");

		checkf(Cast<InterfaceType>(GetChecked(Context)), TEXT("%s: Object: %s with Class: %s does NOT implement interface: InterfaceType."), *Context, *(Data_Internal->GetName()), *(Data_Class->GetName()));

		return Cast<InterfaceType>(GetChecked(Context));
	}

	FORCEINLINE UClass* GetClass() { return Data_Class; }

	void BuildFromPaths()
	{
		Paths.BuildFromPaths();
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

	// FCsDataEntry_DataTable
#pragma region

class UDataTable;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataEntry_DataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
	int32 Index;

	UPROPERTY(BlueprintReadOnly, Category = DataTable)
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	bool bPopulateOnSave;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	TSoftObjectPtr<UDataTable> DataTable;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//int32 DataTable_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	UDataTable* DataTable_Internal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	bool bAllRows;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	TSet<FName> Rows;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	FCsTArraySoftObjectPath Paths;

	/** */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DataTable)
	TMap<FName, FCsTArraySoftObjectPath> PathsByRowMap;

	FCsDataEntry_DataTable() :
		Index(INDEX_NONE),
		Name(NAME_None),
		bPopulateOnSave(false),
		DataTable(),
		DataTable_Internal(nullptr),
		bAllRows(false),
		Rows(),
		Paths(),
		PathsByRowMap()
	{
	}

	FORCEINLINE FCsDataEntry_DataTable& operator=(const FCsDataEntry_DataTable& B)
	{
		Name = B.Name;
		bPopulateOnSave = B.bPopulateOnSave;
		DataTable = B.DataTable;
		DataTable_Internal = B.DataTable_Internal;
		bAllRows = B.bAllRows;
		Rows = B.Rows;
		Paths = B.Paths;
		PathsByRowMap = B.PathsByRowMap;
		return *this;
	}

	FORCEINLINE bool IsValid() const
	{
		return DataTable.IsValid();
	}

	FORCEINLINE void SetIndex(const int32& InIndex)
	{
		Index = InIndex;
	}

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
	}

	void Reset()
	{
		DataTable = nullptr;
		DataTable_Internal = nullptr;
		bAllRows = false;
		Rows.Reset();
		Paths.Reset();
		PathsByRowMap.Reset();
	}

	FORCEINLINE UDataTable* Get() { return DataTable_Internal; }

	FORCEINLINE UDataTable* GetChecked(const FString& Context)
	{
		checkf(DataTable_Internal, TEXT("%s: Failed to load DataTable with Entry: %s @ Path: %s."), *Context, *(Name.ToString()), *(DataTable.ToSoftObjectPath().ToString()));

		return DataTable_Internal;
	}

	void BuildFromPaths()
	{
		Paths.BuildFromPaths();

		for (TPair<FName, FCsTArraySoftObjectPath>& Pair : PathsByRowMap)
		{
			Pair.Value.BuildFromPaths();
		}
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

#pragma endregion DataEntry

// FCsDataRootSetContainer
#pragma region

class UObject;
class UClass;
class ICsGetDataRootSet;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataRootSetContainer
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Load", EditAnywhere, meta = (MustImplement = "CsGetDataRootSet"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	UClass* Data_Class;

	ICsGetDataRootSet* Interface;

	FCsDataRootSetContainer() :
		Data(nullptr),
		Data_Internal(nullptr),
		Data_Class(nullptr),
		Interface(nullptr)
	{
	}

	FORCEINLINE UObject* GetObject() const { return Data_Internal;}

	template<typename T>
	FORCEINLINE T* GetObject() const
	{
		return Cast<T>(GetObject());
	}

	FORCEINLINE UClass* GetClass() const { return Data_Class; }

	FORCEINLINE ICsGetDataRootSet* Get() const { return Interface; }

	template<typename T>
	FORCEINLINE T* GetChecked(const FString& Context) const
	{
		T* Slice = Cast<T>(Data_Internal);

		checkf(Slice, TEXT("%s: Failed to cast Data_Internal to type: T."), *Context);

		return Slice;
	}
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Load")
	TSoftObjectPtr<UDataTable> Data;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Load")
	int32 Data_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	UDataTable* Data_Internal;

	FCsDataTable() :
		Data(nullptr),
		Data_LoadFlags(0),
		Data_Internal(nullptr)
	{
	}

	FORCEINLINE bool operator==(const FCsDataTable& B) const
	{
		return Data == B.Data && Data_LoadFlags == B.Data_LoadFlags && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsDataTable& B) const
	{
		return !(*this == B);
	}

	/**
	* Get the Hard reference to the UDataTable asset.
	*
	* return DataTable
	*/
	FORCEINLINE UDataTable* Get() const { return Data_Internal; }

	/**
	* Get the pointer to the Hard reference to the UDataTable asset.
	*
	* return DataTable
	*/
	FORCEINLINE UDataTable** GetPtr() { return &Data_Internal; }

	/**
	* Get the Hard reference to the UDataTable asset.
	*
	* @param Context	The calling context.
	* return			DataTable
	*/
	FORCEINLINE UDataTable* GetChecked(const FString& Context) const
	{
		checkf(Data.ToSoftObjectPath().IsValid(), TEXT("%s: Data is NULL."), *Context);

		checkf(Data_Internal, TEXT("%s: Data has NOT been loaded from Path @ %s."), *Context, *(Data.ToSoftObjectPath().ToString()));

		return Data_Internal;
	}

	/**
	* Get the Hard reference to the UDataTable asset.
	*
	* return DataTable
	*/
	FORCEINLINE UDataTable* GetChecked() const
	{
		checkf(Data.ToSoftObjectPath().IsValid(), TEXT("FCsDataTable::GetChecked: Data is NULL."));

		checkf(Data_Internal, TEXT("FCsDataTable::GetChecked: Data has NOT been loaded from Path @ %s."), *(Data.ToSoftObjectPath().ToString()));

		return Data_Internal;
	}

	UDataTable* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Data.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data is NULL."), *Context));
			return nullptr;
		}

		if (!Data_Internal)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data has NOT been loaded from Path @ %s."), *Context, *(Data.ToSoftObjectPath().ToString())));
		}
		return Data_Internal;
	}

	UDataTable* GetSafe()
	{
		if (!Data.ToSoftObjectPath().IsValid())
			return nullptr;
		return Data_Internal;
	}

	bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}
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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CsCore|Load")
	TSoftClassPtr<AActor> Actor;

	UPROPERTY()
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	AActor* Actor_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	UClass* Actor_Class;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
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

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayloadOld
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Load")
	FName ShortCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Load")
	FECsDataType DataType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Load")
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Load")
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

class FProperty;

// JsonWriter
typedef bool(*TCsWriteStructToJson_Internal)(FProperty*, TSharedRef<class TJsonWriter<TCHAR>> &, void*, UScriptStruct* const &);
typedef bool(*TCsWriteObjectToJson_Internal)(FProperty*, TSharedRef<class TJsonWriter<TCHAR>> &, void*, UClass* const &);
// JsonReader
typedef bool(*TCsReadStructFromJson_Internal)(FProperty*, TSharedPtr<class FJsonObject> &, void*, UScriptStruct* const &);
typedef bool(*TCsReadObjectFromJson_Internal)(FProperty*, TSharedPtr<class FJsonObject> &, void*, UClass* const &);
// AssetReferences
typedef bool(*TCsGetAssetReferencesFromStruct_Internal)(FProperty*, void*, UScriptStruct* const &, const ECsLoadFlags&, TArray<FCsStringAssetReference>&, const int32&);
typedef bool(*TCsGetAssetReferencesFromObject_Internal)(FProperty*, void*, UClass* const &, const ECsLoadFlags&, TArray<FCsStringAssetReference>&, const int32&);
// Load TSoftObjectPtrs
typedef bool(*TCsLoadStructWithTSoftObjectPtrs_Internal)(FProperty*, const FString&, void*, UScriptStruct* const &, const ECsLoadFlags&);
typedef bool(*TCsLoadObjectWithTSoftObjectPtrs_Internal)(FProperty*, const FString&, void*, UClass* const &, const ECsLoadFlags&);
// Get Members
typedef void*(*TCsGetStructMember_Internal)(FProperty*, void*, UScriptStruct* const &, const FString&);

typedef UScriptStruct*(*TCsGetScriptStructMember_Internal)(FProperty*, void*, UScriptStruct* const &, const FString &);

typedef void*(*TCsGetObjectMember_Internal)(FProperty*, void*, UClass* const &, const FString &);
// Enums
typedef bool(*TCsCheckStructWithEnum_Internal)(FProperty*, const FString&, void*, UScriptStruct* const &);
typedef bool(*TCsCheckObjectWithEnum_Internal)(FProperty*, const FString&, void*, UClass* const &);