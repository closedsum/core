// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Types/CsTypes_Primitive.h"
#include "CsBlockchainContract.generated.h"

USTRUCT(BlueprintType)
struct FECsBlockchainCommand : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsBlockchainCommand() {}
	FECsBlockchainCommand(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsBlockchainCommand() {}
};

FORCEINLINE uint32 GetTypeHash(const FECsBlockchainCommand& b)
{
	return FCrc::MemCrc_DEPRECATED(&b, sizeof(FECsBlockchainCommand));
}

struct EMCsBlockchainCommand : public TCsEnumMap<FECsBlockchainCommand, uint8>
{
protected:
	EMCsBlockchainCommand() {}
	EMCsBlockchainCommand(const EMCsBlockchainCommand &) = delete;
	EMCsBlockchainCommand(EMCsBlockchainCommand &&) = delete;
public:
	~EMCsBlockchainCommand() {}

	static EMCsBlockchainContract& Get()
	{
		static EMCsBlockchainCommand Instance;
		return Instance;
	}
};

UENUM(BlueprintType)
namespace ECgBlockchainCommandArgumentType
{
	enum Type
	{
		Int32									UMETA(DisplayName = "Int32"),
		Float									UMETA(DisplayName = "Float"),
		String									UMETA(DisplayName = "Local"),
		StringString							UMETA(DisplayName = "Server"),
		ECgBlockchainCommandArgumentType_MAX	UMETA(Hidden),
	};
}

#define ECS_BLOCKCHAIN_COMMAND_ARGUMENT_TYPE_MAX (uint8)ECgBlockchainCommandArgumentType::ECgBlockchainCommandArgumentType_MAX
typedef ECgBlockchainCommandArgumentType::Type TCgBlockchainCommandArgumentType;

namespace ECgBlockchainCommandArgumentType
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
		const Type ECgBlockchainCommandArgumentType_MAX = Type::ECgBlockchainCommandArgumentType_MAX;
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
		return Ref::ECgBlockchainCommandArgumentType_MAX;
	}
}

USTRUCT(BlueprintType)
struct FCgBlockchainCommandArgument
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	TEnumAsByte<ECgBlockchainCommandArgumentType::Type> ValueType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	int32 Value_int32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	float Value_float;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Value_FString;

	FCgBlockchainCommandArgument(){}
	FCgBlockchainCommandArgument(const TCgBlockchainCommandArgumentType &valueType, const int32& value)
	{
		ValueType = valueType;
		Value_int32 = value;
	}

	~FCgBlockchainCommandArgument(){}

	FString ToString()
	{
		// Int32
		if (ValueType == ECgBlockchainCommandArgumentType::Int32)
			return FString::FromInt(Value_int32);
		// Float
		if (ValueType == ECgBlockchainCommandArgumentType::Float)
			return FString::SanitizeFloat(Value_float);
		// String
		if (ValueType == ECgBlockchainCommandArgumentType::String)
			return Value_FString;
		// StringString
		if (ValueType == ECgBlockchainCommandArgumentType::StringString)
			return TEXT("\"") + Value_FString + TEXT("\"");
		return ECsCachedString::Str::Empty;
	}
}

USTRUCT(BlueprintType)
struct CgBlockchainCommandInfo
{
	GENERATED_USTRUCT_BODY()

	public ECgBlockchainCommand Command;
	public CgBlockchainCommandArgument[] Arguments;
	public object Payload;

	public CgBlockchainCommandInfo(ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null, object payload = null)
	{
		Command = command;
		Arguments = args;
		Payload = payload;
	}

	public void Set(ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null, object payload = null)
	{
		Command = command;
		Arguments = args;
		Payload = payload;
	}
}