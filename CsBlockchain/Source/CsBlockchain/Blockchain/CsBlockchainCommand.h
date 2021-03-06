// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"
#include "CsBlockchainCommand.generated.h"

USTRUCT(BlueprintType)
struct CSBLOCKCHAIN_API FECsBlockchainCommand : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsBlockchainCommand)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsBlockchainCommand)

struct CSBLOCKCHAIN_API EMCsBlockchainCommand : public TCsEnumStructMap<FECsBlockchainCommand, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsBlockchainCommand, FECsBlockchainCommand, uint8)
};

UENUM(BlueprintType)
enum class ECsBlockchainCommandArgumentType : uint8
{
	Int32									UMETA(DisplayName = "Int32"),
	Float									UMETA(DisplayName = "Float"),
	String									UMETA(DisplayName = "Local"),
	StringString							UMETA(DisplayName = "Server"),
	ECsBlockchainCommandArgumentType_MAX	UMETA(Hidden),
};

#define ECS_BLOCKCHAIN_COMMAND_ARGUMENT_TYPE_MAX (uint8)ECsBlockchainCommandArgumentType::ECsBlockchainCommandArgumentType_MAX

struct CSBLOCKCHAIN_API EMCsBlockchainCommandArgumentType : public TCsEnumMap<ECsBlockchainCommandArgumentType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsBlockchainCommandArgumentType, ECsBlockchainCommandArgumentType)
};

namespace NCsBlockchainCommandArgumentType
{
	typedef ECsBlockchainCommandArgumentType Type;

	namespace Ref
	{
		extern CSBLOCKCHAIN_API const Type Int32;
		extern CSBLOCKCHAIN_API const Type Float;
		extern CSBLOCKCHAIN_API const Type String;
		extern CSBLOCKCHAIN_API const Type StringString;
		extern CSBLOCKCHAIN_API const Type ECsBlockchainCommandArgumentType_MAX;
	}
}

USTRUCT(BlueprintType)
struct FCsBlockchainCommandArgument
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	ECsBlockchainCommandArgumentType ValueType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	int32 Value_int32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	float Value_float;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Value_FString;

	FCsBlockchainCommandArgument() :
		ValueType(ECsBlockchainCommandArgumentType::ECsBlockchainCommandArgumentType_MAX),
		Value_int32(0),
		Value_float(0.0f),
		Value_FString()
	{
	}

	FCsBlockchainCommandArgument(const ECsBlockchainCommandArgumentType &valueType, const int32& value)
	{
		ValueType = valueType;
		Value_int32 = value;
		Value_float = 0.0f;
	}

	FCsBlockchainCommandArgument(const ECsBlockchainCommandArgumentType &valueType, const float& value)
	{
		ValueType = valueType;
		Value_int32 = 0;
		Value_float = value;
	}

	FCsBlockchainCommandArgument(const ECsBlockchainCommandArgumentType &valueType, const FString& value)
	{
		ValueType = valueType;
		Value_int32 = 0;
		Value_float = 0.0f;
		Value_FString = value;
	}

	~FCsBlockchainCommandArgument(){}

	FCsBlockchainCommandArgument& operator=(const FCsBlockchainCommandArgument& B)
	{
		ValueType = B.ValueType;
		Value_int32 = B.Value_int32;
		Value_float = B.Value_float;
		Value_FString = B.Value_FString;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsBlockchainCommandArgument& B) const
	{
		if (ValueType != B.ValueType)
			return false;
		if (Value_int32 != B.Value_int32)
			return false;
		if (Value_float != B.Value_float)
			return false;
		if (Value_FString != B.Value_FString)
			return false;
		return true;
	}

	FORCEINLINE bool operator!=(const FCsBlockchainCommandArgument& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const ECsBlockchainCommandArgumentType &valueType, const int32& value)
	{
		ValueType = valueType;
		Value_int32 = value;
		Value_float = 0.0f;
	}

	FORCEINLINE void Set(const ECsBlockchainCommandArgumentType &valueType, const float& value)
	{
		ValueType = valueType;
		Value_int32 = 0;
		Value_float = value;
	}

	FORCEINLINE void Set(const ECsBlockchainCommandArgumentType &valueType, const FString& value)
	{
		ValueType = valueType;
		Value_int32 = 0;
		Value_float = 0.0f;
		Value_FString = value;
	}

	FORCEINLINE FString ToString()
	{
		// Int32
		if (ValueType == ECsBlockchainCommandArgumentType::Int32)
			return FString::FromInt(Value_int32);
		// Float
		if (ValueType == ECsBlockchainCommandArgumentType::Float)
			return FString::SanitizeFloat(Value_float);
		// String
		if (ValueType == ECsBlockchainCommandArgumentType::String)
			return Value_FString;
		// StringString
		if (ValueType == ECsBlockchainCommandArgumentType::StringString)
			return TEXT("\"") + Value_FString + TEXT("\"");
		return NCsCached::Str::Empty;
	}
};

USTRUCT(BlueprintType)
struct FCsBlockchainCommandOutput
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	bool Value_bool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	int32 Value_int32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	float Value_float;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Value_FString;

	void* Value_ptr;

	FCsBlockchainCommandOutput() :
		Value_bool(false),
		Value_int32(0),
		Value_float(0.0f),
		Value_FString(),
		Value_ptr(nullptr)
	{}

	~FCsBlockchainCommandOutput(){}

	FORCEINLINE FCsBlockchainCommandOutput& operator=(const FCsBlockchainCommandOutput& B)
	{
		Value_bool = B.Value_bool;
		Value_int32 = B.Value_int32;
		Value_float = B.Value_float;
		Value_FString = B.Value_FString;
		Value_ptr = B.Value_ptr;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsBlockchainCommandOutput& B) const
	{
		if (Value_bool != B.Value_bool)
			return false;
		if (Value_int32 != B.Value_int32)
			return false;
		if (Value_float != B.Value_float)
			return false;
		if (Value_FString != B.Value_FString)
			return false;
		if (Value_ptr != B.Value_ptr)
			return false;
		return true;
	}

	FORCEINLINE bool operator!=(const FCsBlockchainCommandOutput& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		Value_bool = false;
		Value_int32 = 0;
		Value_float = 0.0f;
		Value_FString = NCsCached::Str::Empty;
		Value_ptr = nullptr;
	}
};