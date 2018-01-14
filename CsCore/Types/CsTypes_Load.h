// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"

#include "Json.h"
#include "JsonObjectConverter.h"

#include "CsTypes_Load.generated.h"
#pragma once

#define CS_CVAR_LOAD_UNSET -1
#define CS_CVAR_LOAD_NONE 0
#define CS_CVAR_LOAD_FIRSTTOLAST 1
#define CS_CVAR_LOAD_BULK 2

// Load
#pragma region

namespace ECsLoadCachedString
{
	namespace Str
	{
		const FString _Internal = TEXT("_Internal");
		const FString _LoadFlags = TEXT("_LoadFlags");
		const FString _C = TEXT("_C");
	}
}

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsLoadCode : uint8
{
	CalculateResourceSizes		UMETA(DisplayName = "Calculate Resource Sizes"),
	SuppressLoadFlagsAllWarning	UMETA(DisplayName = "Suppress Load Flags All Warning"),
};

#define ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES 1

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
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

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

	FORCEINLINE FString ToString(const Type &EType)
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
typedef TEnumAsByte<ECsLoadFlags_Editor::Type> TCsLoadFlags_Editor;

USTRUCT()
struct FCsResourceSize
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

	FCsResourceSize& operator=(const FCsResourceSize& B)
	{
		Bytes = B.Bytes;
		Kilobytes = B.Kilobytes;
		Megabytes = B.Megabytes;
		return *this;
	}

	FCsResourceSize& operator+=(const FCsResourceSize& B)
	{
		Bytes += B.Bytes;
		Kilobytes += B.Kilobytes;
		Megabytes += B.Megabytes;
		return *this;
	}

	void Reset()
	{
		Bytes = 0;
		Kilobytes = 0.0f;
		Megabytes = 0.0f;
	}
};

USTRUCT()
struct FCsStringAssetReference
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Reference")
	FString Reference;

	UPROPERTY()
	FStringAssetReference Reference_Internal;

	UPROPERTY(VisibleDefaultsOnly, Category = "Reference")
	FCsResourceSize Size;

	FStringAssetReference* Get()
	{
		&Reference_Internal;
	}
};

USTRUCT()
struct FCsTArrayStringAssetReference
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

	void Get(TArray<FStringAssetReference>& OutReferences)
	{
		const int32 Count = References.Num();

		for (int32 I = 0; I < Count; I++)
		{
			OutReferences.Add(References[I].Reference_Internal);
		}
	}

	void CalculateSize()
	{
		Size.Reset();

		const int32 Count = References.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Size += References[I].Size;
		}
	}
};

#define CS_INVALID_LOOK_UP_CODE 255
#define CS_INVALID_LOOK_UP_CODE_MAX 65535

USTRUCT(BlueprintType)
struct FCsDataMappingEntry
{
	GENERATED_USTRUCT_BODY()

	/** Short Name - used to link with Backend */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FName ShortCode;

	UPROPERTY(VisibleDefaultsOnly, Category = "Data")
	uint16 LookUpCode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	TAssetSubclassOf<class ACsData> Data;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Data_LoadFlags;

	UPROPERTY(VisibleDefaultsOnly, Category = "Data")
	FCsTArrayStringAssetReference AssetReferences[ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX];

	FCsDataMappingEntry()
	{
		LookUpCode = CS_INVALID_LOOK_UP_CODE_MAX;

		CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
	}

	void Set(const FName &InShortCode, UObject* InData)
	{
		ShortCode = InShortCode;
		Data = InData;
	}
};

USTRUCT()
struct FCsAssetReferenceLoadedCache
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
struct FCsCategoryMemberAssociation
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Member")
	FString Category;

	UPROPERTY(VisibleDefaultsOnly, Category = "Member")
	TArray<FString> Members;
};

namespace ECsAssetType
{
	enum Type : uint8;
}

typedef ECsAssetType::Type TCsAssetType;

// AssetTypeToString
typedef FString(*TCsAssetTypeToString)(const TCsAssetType&);
// StringToAssetType
typedef TCsAssetType(*TCsStringToAssetType)(const FString&);

#define CS_DECLARE_ASSET_TYPE	TCsAssetType AssetType_MAX; \
								uint8 ASSET_TYPE_MAX; \
								TCsAssetTypeToString AssetTypeToString; \
								TCsStringToAssetType StringToAssetType;

#define CS_DEFINE_ASSET_TYPE	AssetType_MAX = ECsAssetType::ECsAssetType_MAX;\
								ASSET_TYPE_MAX = (uint8)AssetType_MAX; \
								AssetTypeToString = &ECsAssetType::ToString; \
								StringToAssetType = &ECsAssetType::ToType;

namespace ECsLoadAssetsType
{
	enum Type : uint8;
}

typedef ECsLoadAssetsType::Type TCsLoadAssetsType;

// LoadAssetsTypeToString
typedef FString(*TCsLoadAssetsTypeToString)(const TCsLoadAssetsType&);
// StringToLoadAssetsType
typedef TCsLoadAssetsType(*TCsStringToLoadAssetsType)(const FString&);

#define CS_DECLARE_LOAD_ASSETS_TYPE	TCsLoadAssetsType LoadAssetsType_MAX; \
									uint8 LOAD_ASSETS_TYPE_MAX; \
									TCsLoadAssetsTypeToString LoadAssetsTypeToString; \
									TCsStringToLoadAssetsType StringToLoadAssetsType;

#define CS_DEFINE_LOAD_ASSETS_TYPE	LoadAssetsType_MAX = ECsLoadAssetsType::ECsLoadAssetsType_MAX;\
									LOAD_ASSETS_TYPE_MAX = (uint8)LoadAssetsType_MAX; \
									LoadAssetsTypeToString = &ECsLoadAssetsType::ToString; \
									StringToLoadAssetsType = &ECsLoadAssetsType::ToType;

USTRUCT(BlueprintType)
struct FCsPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FName ShortCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	FString AssetType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Payload")
	uint8 AssetType_Script;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TEnumAsByte<ECsLoadFlags_Editor::Type> LoadFlags;

	FCsPayload& operator=(const FCsPayload& B)
	{
		ShortCode = B.ShortCode;
		AssetType = B.AssetType;
		AssetType_Script = B.AssetType_Script;
		LoadFlags = B.LoadFlags;
		return *this;
	}

	bool operator==(const FCsPayload& B) const
	{
		if (ShortCode != B.ShortCode) { return false; }
		if (AssetType != B.AssetType) { return false; }
		if (AssetType_Script != B.AssetType_Script) { return false; }
		if (LoadFlags != B.LoadFlags) { return false; }
		return true;
	}

	bool operator!=(const FCsPayload& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsTArrayPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Payload")
	TArray<FCsPayload> Payloads;

	FCsTArrayPayload& operator=(const FCsTArrayPayload& B)
	{
		Payloads.Reset();

		const int32 Count = B.Payloads.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Payloads.Add(B.Payloads[I]);
		}
		return *this;
	}

	bool operator==(const FCsTArrayPayload& B) const
	{
		const int32 CountA = Payloads.Num();
		const int32 CountB = B.Payloads.Num();

		if (CountA != CountB)
			return false;

		for (int32 I = 0; I < CountA; I++)
		{
			if (Payloads[I] != B.Payloads[I])
				return false;
		}
		return true;
	}

	bool operator!=(const FCsTArrayPayload& B) const
	{
		return !(*this == B);
	}
};

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

namespace ECsLoadAsyncOrder
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString None = TCsString(TEXT("None"), TEXT("none"), TEXT("none"));
		const TCsString FirstToLast = TCsString(TEXT("FirstToLast"), TEXT("firsttolast"), TEXT("first to last"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::None) { return Str::None.Value; }
		if (EType == Type::FirstToLast) { return Str::FirstToLast.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::None) { return Type::None; }
		if (String == Str::FirstToLast) { return Type::FirstToLast; }
		return Type::ECsLoadAsyncOrder_MAX;
	}
}

#define ECS_LOADING_ASYNC_ORDER_MAX (uint8)ECsLoadAsyncOrder::ECsLoadAsyncOrder_MAX
typedef TEnumAsByte<ECsLoadAsyncOrder::Type> TCsLoadAsyncOrder;

#pragma endregion Load

// JsonWriter
typedef bool(*TCsWriteStructToJson_Internal)(UProperty*, TSharedRef<class TJsonWriter<TCHAR>> &, void*, UScriptStruct* const &);
typedef bool(*TCsWriteObjectToJson_Internal)(UProperty*, TSharedRef<class TJsonWriter<TCHAR>> &, void*, UClass* const &);
// JsonReader
typedef bool(*TCsReadStructFromJson_Internal)(UProperty*, TSharedPtr<class FJsonObject> &, void*, UScriptStruct* const &);
typedef bool(*TCsReadObjectFromJson_Internal)(UProperty*, TSharedPtr<class FJsonObject> &, void*, UClass* const &);
// AssetReferences
typedef bool(*TCsGetAssetReferencesFromStruct_Internal)(UProperty*, void*, UScriptStruct* const &, const ECsLoadFlags&, TArray<FCsStringAssetReference>&, const int32&);
typedef bool(*TCsGetAssetReferencesFromObject_Internal)(UProperty*, void*, UClass* const &, const ECsLoadFlags&, TArray<FCsStringAssetReference>&, const int32&);
// Load TAssetPtrs
typedef bool(*TCsLoadStructWithTAssetPtrs_Internal)(UProperty*, const FString&, void*, UScriptStruct* const &, const ECsLoadFlags&);
typedef bool(*TCsLoadObjectWithTAssetPtrs_Internal)(UProperty*, const FString&, void*, UClass* const &, const ECsLoadFlags&);
// Get Members
typedef void*(*TCsGetStructMember_Internal)(UProperty*, void*, UScriptStruct* const &, const FString&);

typedef UScriptStruct*(*TCsGetScriptStructMember_Internal)(UProperty*, void*, UScriptStruct* const &, const FString &);

typedef void*(*TCsGetObjectMember_Internal)(UProperty*, void*, UClass* const &, const FString &);