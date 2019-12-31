// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "Json.h"
#include "JsonObjectConverter.h"

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

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsLoadCode : uint8
{
	CalculateResourceSizes		UMETA(DisplayName = "Calculate Resource Sizes"),
	SuppressLoadFlagsAllWarning	UMETA(DisplayName = "Suppress Load Flags All Warning"),
};

#define ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES 1

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

	FORCEINLINE void Reset()
	{
		Bytes = 0;
		Kilobytes = 0.0f;
		Megabytes = 0.0f;
	}
};

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

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataMappingEntry
{
	GENERATED_USTRUCT_BODY()

	/** Short Name - used to link with Backend */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FName ShortCode;

	UPROPERTY(VisibleDefaultsOnly, Category = "Data")
	uint16 LookUpCode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	TSoftClassPtr<class ACsData> Data;

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

USTRUCT(BlueprintType)
struct CSCORE_API FCsAssetReferenceLoadedCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FStringAssetReference Reference;

	UPROPERTY()
	int32 Count;

	UPROPERTY()
	FCsResourceSize Size;

	UPROPERTY()
	float Time;
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsCategoryMemberAssociation
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Member")
	FString Category;

	UPROPERTY(VisibleDefaultsOnly, Category = "Member")
	TArray<FString> Members;
};

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

// DataCollection
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

#pragma endregion DataCollection

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
struct CSCORE_API FCsPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FName ShortCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FECsDataType DataType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TEnumAsByte<ECsLoadFlags_Editor::Type> LoadFlags;

	FORCEINLINE FCsPayload& operator=(const FCsPayload& B)
	{
		ShortCode = B.ShortCode;
		DataType = B.DataType;
		LoadFlags = B.LoadFlags;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsPayload& B) const
	{
		if (ShortCode != B.ShortCode) { return false; }
		if (DataType != B.DataType) { return false; }
		if (LoadFlags != B.LoadFlags) { return false; }
		return true;
	}

	FORCEINLINE bool operator!=(const FCsPayload& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsTArrayPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TArray<FCsPayload> Payloads;

	FORCEINLINE FCsTArrayPayload& operator=(const FCsTArrayPayload& B)
	{
		Payloads.Reset();

		for (const FCsPayload& Payload : B.Payloads)
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

// LoadAsyncOrder

UENUM(BlueprintType)
namespace ECsLoadAsyncOrder
{
	enum Type
	{
		// Default to Bulk
		None					UMETA(DisplayName = "None"),
		// Process Assets IN ORDER 1 by 1
		FirstToLast				UMETA(DisplayName = "First to Last"),
		// Group Assets, only get notification once ENTIRE Group is Finished
		Bulk					UMETA(DisplayName = "Bulk"),
		ECsLoadAsyncOrder_MAX	UMETA(Hidden),
	};
}

typedef ECsLoadAsyncOrder::Type TCsLoadAsyncOrder;

struct CSCORE_API EMCsLoadAsyncOrder : public TCsEnumMap<ECsLoadAsyncOrder::Type>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsLoadAsyncOrder)
};

namespace ECsLoadAsyncOrder
{
	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type FirstToLast;
		extern CSCORE_API const Type Bulk;
		extern CSCORE_API const Type ECsLoadAsyncOrder_MAX;
	}
}

#pragma endregion // LoadAsyncOrder

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