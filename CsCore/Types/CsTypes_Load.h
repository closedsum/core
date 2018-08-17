// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
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

#define CS_LOAD_FLAGS_NONE 0

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

namespace ECsLoadFlags_Editor
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Game = TCsString(TEXT("Game"), TEXT("game"), TEXT("game"));
		const TCsString Game1P = TCsString(TEXT("Game1P"), TEXT("game1p"), TEXT("game 1p"));
		const TCsString Game3P = TCsString(TEXT("Game3P"), TEXT("game3p"), TEXT("game 3p"));
		const TCsString Game3PLow = TCsString(TEXT("Game3PLow"), TEXT("game3plow"), TEXT("game 3p low"));
		const TCsString GameVR = TCsString(TEXT("GameVR"), TEXT("gamevr"), TEXT("game vr"));
		const TCsString UI = TCsString(TEXT("UI"), TEXT("ui"), TEXT("ui"));
		const TCsString All = TCsString(TEXT("All"), TEXT("all"), TEXT("all"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Game) { return Str::Game.Value; }
		if (EType == Type::Game1P) { return Str::Game1P.Value; }
		if (EType == Type::Game3P) { return Str::Game3P.Value; }
		if (EType == Type::Game3PLow) { return Str::Game3PLow.Value; }
		if (EType == Type::GameVR) { return Str::GameVR.Value; }
		if (EType == Type::UI) { return Str::UI.Value; }
		if (EType == Type::All) { return Str::All.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Game) { return Type::Game; }
		if (String == Str::Game1P) { return Type::Game1P; }
		if (String == Str::Game3P) { return Type::Game3P; }
		if (String == Str::Game3PLow) { return Type::Game3PLow; }
		if (String == Str::GameVR) { return Type::GameVR; }
		if (String == Str::UI) { return Type::UI; }
		if (String == Str::All) { return Type::All; }
		return Type::ECsLoadFlags_Editor_MAX;
	}

	FORCEINLINE ECsLoadFlags ToBaseType(const Type &EType)
	{
		if (EType == Type::Game) { return ECsLoadFlags::Game; }
		if (EType == Type::Game1P) { return ECsLoadFlags::Game1P; }
		if (EType == Type::Game3P) { return ECsLoadFlags::Game3P; }
		if (EType == Type::Game3PLow) { return ECsLoadFlags::Game3PLow; }
		if (EType == Type::GameVR) { return ECsLoadFlags::GameVR; }
		if (EType == Type::UI) { return ECsLoadFlags::UI; }
		if (EType == Type::All) { return ECsLoadFlags::All; }
		return ECsLoadFlags::All;
	}

	FORCEINLINE ECsLoadFlags ToFlag(const FString &String)
	{
		if (String == Str::Game) { return ECsLoadFlags::Game; }
		if (String == Str::Game1P) { return ECsLoadFlags::Game1P; }
		if (String == Str::Game3P) { return ECsLoadFlags::Game3P; }
		if (String == Str::Game3PLow) { return ECsLoadFlags::Game3PLow; }
		if (String == Str::GameVR) { return ECsLoadFlags::GameVR; }
		if (String == Str::UI) { return ECsLoadFlags::UI; }
		if (String == Str::All) { return ECsLoadFlags::All; }
		return ECsLoadFlags::All;;
	}
}

#define ECS_LOAD_FLAGS_EDITOR_MAX (uint8)ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX
typedef ECsLoadFlags_Editor::Type TCsLoadFlags_Editor;

#pragma endregion // LoadFlags

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

	FCsDataMappingEntry()
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

USTRUCT()
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

USTRUCT()
struct CSCORE_API FCsCategoryMemberAssociation
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Member")
	FString Category;

	UPROPERTY(VisibleDefaultsOnly, Category = "Member")
	TArray<FString> Members;
};

// AssetType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsAssetType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsAssetType() {}
	FECsAssetType(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsAssetType(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsAssetType() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsAssetType& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsAssetType : public TCsEnumStructMap<FECsAssetType, uint8>
{
protected:
	EMCsAssetType() {}
	EMCsAssetType(const EMCsAssetType &) = delete;
	EMCsAssetType(EMCsAssetType &&) = delete;
public:
	~EMCsAssetType() {}
private:
	static EMCsAssetType* Instance;

public:
	static EMCsAssetType& Get();
};

namespace ECsAssetType
{
}

// GetAssetTypeStaticClass
typedef UClass*(*TCsGetAssetTypeStaticClass)(const FECsAssetType&);

#pragma endregion // AssetType

// LoadAssetsType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsLoadAssetsType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsLoadAssetsType() {}
	FECsLoadAssetsType(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsLoadAssetsType(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsLoadAssetsType() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsLoadAssetsType& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsLoadAssetsType : public TCsEnumStructMap<FECsLoadAssetsType, uint8>
{
protected:
	EMCsLoadAssetsType() {}
	EMCsLoadAssetsType(const EMCsLoadAssetsType &) = delete;
	EMCsLoadAssetsType(EMCsLoadAssetsType &&) = delete;
public:
	~EMCsLoadAssetsType() {}
private:
	static EMCsLoadAssetsType* Instance;

public:
	static EMCsLoadAssetsType& Get();
};

#pragma endregion // LoadAssetsType

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FName ShortCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FECsAssetType AssetType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TEnumAsByte<ECsLoadFlags_Editor::Type> LoadFlags;

	FORCEINLINE FCsPayload& operator=(const FCsPayload& B)
	{
		ShortCode = B.ShortCode;
		AssetType = B.AssetType;
		LoadFlags = B.LoadFlags;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsPayload& B) const
	{
		if (ShortCode != B.ShortCode) { return false; }
		if (AssetType != B.AssetType) { return false; }
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
protected:
	EMCsLoadAsyncOrder() {}
	EMCsLoadAsyncOrder(const EMCsLoadAsyncOrder &) = delete;
	EMCsLoadAsyncOrder(EMCsLoadAsyncOrder &&) = delete;
public:
	~EMCsLoadAsyncOrder() {}
private:
	static EMCsLoadAsyncOrder* Instance;

public:
	static EMCsLoadAsyncOrder& Get();
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

USTRUCT(BlueprintType)
struct CSCORE_API FCsData_ShortCode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data_ShortCode")
	FECsAssetType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data_ShortCode")
	FName ShortCode;

public:
	FCsData_ShortCode() {}
	~FCsData_ShortCode() {}
};

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