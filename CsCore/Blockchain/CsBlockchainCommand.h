// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Types/CsTypes_Primitive.h"
#include "CsBlockchainCommand.generated.h"

USTRUCT(BlueprintType)
struct FECsBlockchainCommand : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsBlockchainCommand() {}
	FECsBlockchainCommand(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsBlockchainCommand(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsBlockchainCommand() {}
};

FORCEINLINE uint32 GetTypeHash(const FECsBlockchainCommand& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsBlockchainCommand : public TCsEnumMap<FECsBlockchainCommand, uint8>
{
protected:
	EMCsBlockchainCommand() {}
	EMCsBlockchainCommand(const EMCsBlockchainCommand &) = delete;
	EMCsBlockchainCommand(EMCsBlockchainCommand &&) = delete;
public:
	~EMCsBlockchainCommand() {}
private:
	static EMCsBlockchainCommand* Instance;

public:
	static EMCsBlockchainCommand& Get();
};

UENUM(BlueprintType)
namespace ECsBlockchainCommandArgumentType
{
	enum Type
	{
		Int32									UMETA(DisplayName = "Int32"),
		Float									UMETA(DisplayName = "Float"),
		String									UMETA(DisplayName = "Local"),
		StringString							UMETA(DisplayName = "Server"),
		ECsBlockchainCommandArgumentType_MAX	UMETA(Hidden),
	};
}

#define ECS_BLOCKCHAIN_COMMAND_ARGUMENT_TYPE_MAX (uint8)ECsBlockchainCommandArgumentType::ECsBlockchainCommandArgumentType_MAX
typedef ECsBlockchainCommandArgumentType::Type TCsBlockchainCommandArgumentType;

namespace ECsBlockchainCommandArgumentType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Int32 = TCsString(TEXT("Int32"), TEXT("int32"));
		const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
		const TCsString String = TCsString(TEXT("String"), TEXT("string"));
		const TCsString StringString = TCsString(TEXT("StringString"), TEXT("stringstring"));
	}

	namespace Ref
	{
		const Type Int32 = Type::Int32;
		const Type Float = Type::Float;
		const Type String = Type::String;
		const Type StringString = Type::StringString;
		const Type ECsBlockchainCommandArgumentType_MAX = Type::ECsBlockchainCommandArgumentType_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Int32) { return Str::Int32.Value; }
		if (EType == Type::Float) { return Str::Float.Value; }
		if (EType == Type::String) { return Str::String.Value; }
		if (EType == Type::StringString) { return Str::StringString.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::Int32) { return Ref::Int32; }
		if (String == Str::Float) { return Ref::Float; }
		if (String == Str::String) { return Ref::String; }
		if (String == Str::StringString) { return Ref::StringString; }
		return Ref::ECsBlockchainCommandArgumentType_MAX;
	}
}

USTRUCT(BlueprintType)
struct FCsBlockchainCommandArgument
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	TEnumAsByte<ECsBlockchainCommandArgumentType::Type> ValueType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	int32 Value_int32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	float Value_float;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Value_FString;

	FCsBlockchainCommandArgument(){}
	FCsBlockchainCommandArgument(const TCsBlockchainCommandArgumentType &valueType, const int32& value)
	{
		ValueType = valueType;
		Value_int32 = value;
	}

	FCsBlockchainCommandArgument(const TCsBlockchainCommandArgumentType &valueType, const float& value)
	{
		ValueType = valueType;
		Value_float = value;
	}

	FCsBlockchainCommandArgument(const TCsBlockchainCommandArgumentType &valueType, const FString& value)
	{
		ValueType = valueType;
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

	bool operator==(const FCsBlockchainCommandArgument& B) const
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

	bool operator!=(const FCsBlockchainCommandArgument& B) const
	{
		return !(*this == B);
	}

	void Set(const TCsBlockchainCommandArgumentType &valueType, const int32& value)
	{
		ValueType = valueType;
		Value_int32 = value;
	}

	void Set(const TCsBlockchainCommandArgumentType &valueType, const float& value)
	{
		ValueType = valueType;
		Value_float = value;
	}

	void Set(const TCsBlockchainCommandArgumentType &valueType, const FString& value)
	{
		ValueType = valueType;
		Value_FString = value;
	}

	FString ToString()
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
		return ECsCached::Str::Empty;
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

	FCsBlockchainCommandOutput(){}
	~FCsBlockchainCommandOutput(){}

	FCsBlockchainCommandOutput& operator=(const FCsBlockchainCommandOutput& B)
	{
		Value_bool = B.Value_bool;
		Value_int32 = B.Value_int32;
		Value_float = B.Value_float;
		Value_FString = B.Value_FString;
		Value_ptr = B.Value_ptr;
		return *this;
	}

	bool operator==(const FCsBlockchainCommandOutput& B) const
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

	bool operator!=(const FCsBlockchainCommandOutput& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		Value_bool = false;
		Value_int32 = 0;
		Value_float = 0.0f;
		Value_FString = ECsCached::Str::Empty;
		Value_ptr = nullptr;
	}
};