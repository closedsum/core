// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Types/CsTypes_Primitive.h"
#include "CsBlockchainContract.generated.h"

USTRUCT(BlueprintType)
struct FECsBlockchainContract : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsBlockchainContract() {}
	FECsBlockchainContract(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsBlockchainContract() {}
};

FORCEINLINE uint32 GetTypeHash(const FECsBlockchainContract& b)
{
	return FCrc::MemCrc_DEPRECATED(&b, sizeof(FECsBlockchainContract));
}

struct EMCsBlockchainContract : public TCsEnumMap<FECsBlockchainContract, uint8>
{
protected:
	EMCsBlockchainContract() {}
	EMCsBlockchainContract(const EMCsBlockchainContract &) = delete;
	EMCsBlockchainContract(EMCsBlockchainContract &&) = delete;
public:
	~EMCsBlockchainContract() {}

	static EMCsBlockchainContract& Get()
	{
		static EMCsBlockchainContract Instance;
		return Instance;
	}
};

// Argument
#pragma region

UENUM(BlueprintType)
namespace ECsBlockchainContractArgumentType
{
	enum Type
	{
		Bool									UMETA(DisplayName = "Bool"),
		Int32									UMETA(DisplayName = "Int32"),
		Float									UMETA(DisplayName = "Float"),
		String									UMETA(DisplayName = "String"),
		StringString							UMETA(DisplayName = "StringString"),
		ECsBlockchainContractArgumentType_MAX	UMETA(Hidden),
	};
}

#define ECS_BLOCKCHAIN_CONTRACT_ARGUMENT_TYPE_MAX (uint8)ECsBlockchainContractArgumentType::ECsBlockchainContractArgumentType_MAX
typedef ECsBlockchainContractArgumentType::Type TCsBlockchainContractArgumentType;

namespace ECsBlockchainContractArgumentType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Bool = TCsString(TEXT("Bool"), TEXT("bool"));
		const TCsString Int32 = TCsString(TEXT("Int32"), TEXT("int32"));
		const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
		const TCsString String = TCsString(TEXT("String"), TEXT("string"));
	}

	namespace Ref
	{
		const Type Bool = Type::Bool;
		const Type Int32 = Type::Int32;
		const Type Float = Type::Float;
		const Type String = Type::String;
		const Type ECsBlockchainContractArgumentType_MAX = Type::ECsBlockchainContractArgumentType_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Bool) { return Str::Bool.Value; }
		if (EType == Type::Int32) { return Str::Int32.Value; }
		if (EType == Type::Float) { return Str::Float.Value; }
		if (EType == Type::String) { return Str::String.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &InString)
	{
		if (InString == Str::Bool) { return Ref::Bool; }
		if (InString == Str::Int32) { return Ref::Int32; }
		if (InString == Str::Float) { return Ref::Float; }
		if (InString == Str::String) { return Ref::String; }
		return Ref::ECsBlockchainContractArgumentType_MAX;
	}
}

USTRUCT(BlueprintType)
struct FCsBlockchainContractArgument
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	TEnumAsByte<ECsBlockchainContractArgumentType::Type> ValueType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	bool Value_bool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	int32 Value_int32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	float Value_float;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Value_FString;

	FCsBlockchainContractArgument(){}
	FCsBlockchainContractArgument(const FString &InName, const TCsBlockchainContractArgumentType &InValueType)
	{
		// HACKY: For now add ',' to distinguish between the same input arguments in the ABI
		Name	  = InName + TEXT(",");
		ValueType = InValueType;
	}

	FCsBlockchainContractArgument(const FString &InName, const TCsBlockchainContractArgumentType &InValueType, const bool &Value)
	{
		FCsBlockchainContractArgument(InName, InValueType);
		Value_bool = Value;
	}

	FCsBlockchainContractArgument(const FString &InName, const TCsBlockchainContractArgumentType &InValueType, const int32 &Value)
	{
		FCsBlockchainContractArgument(InName, InValueType);
		Value_int32 = Value;
	}

	FCsBlockchainContractArgument(const FString &InName, const TCsBlockchainContractArgumentType &InValueType, const float &Value)
	{
		FCsBlockchainContractArgument(InName, InValueType);
		Value_float = Value;
	}

	FCsBlockchainContractArgument(const FString &InName, const TCsBlockchainContractArgumentType &InValueType, const FString &Value)
	{
		FCsBlockchainContractArgument(InName, InValueType);
		Value_FString = Value;
	}

	~FCsBlockchainContractArgument(){}

	void Set(const FString &InName, const TCsBlockchainContractArgumentType &InValueType)
	{
		// HACKY: For now add ',' to distinguish between the same input arguments in the ABI
		Name = InName + TEXT(",");
		ValueType = InValueType;
	}

	void Set(const FString &InName, const TCsBlockchainContractArgumentType &InValueType, const bool &Value)
	{
		Set(InName, InValueType);
		Value_bool = Value;
	}

	void Set(const FString &InName, const TCsBlockchainContractArgumentType &InValueType, const int32 &Value)
	{
		Set(InName, InValueType);
		Value_int32 = Value;
	}

	void Set(const FString &InName, const TCsBlockchainContractArgumentType &InValueType, const float &Value)
	{
		Set(InName, InValueType);
		Value_float = Value;
	}

	void Set(const FString &InName, const TCsBlockchainContractArgumentType &InValueType, const FString &Value)
	{
		Set(InName, InValueType);
		Value_FString = Value;
	}

	FString ToString() const
	{
		// HACKY: For now add ',' to distinguish between the same input arguments in the ABI

		// Bool
		if (ValueType == ECsBlockchainContractArgumentType::Bool)
			return Value_bool ? TEXT("true,") : TEXT("false,");
		// Int32
		if (ValueType == ECsBlockchainContractArgumentType::Int32)
			return FString::FromInt(Value_int32) + (",");
		// Float
		if (ValueType == ECsBlockchainContractArgumentType::Float)
			return FString::SanitizeFloat(Value_float) + (",");
		// String
		if (ValueType == ECsBlockchainContractArgumentType::String)
			return Value_FString + TEXT(",");
		// StringString
		if (ValueType == ECsBlockchainContractArgumentType::StringString)
			return TEXT("'") + Value_FString + TEXT("',");
		return ECsCachedString::Str::Empty;
	}

	void Reset()
	{
		Name = ECsCachedString::Str::Empty;
		ValueType = ECsBlockchainContractArgumentType::ECsBlockchainContractArgumentType_MAX;
		Value_bool = false;
		Value_int32 = 0;
		Value_float  = 0.0f;
		Value_FString = ECsCachedString::Str::Empty;
	}
};

#pragma endregion Argument

// Function
#pragma region

USTRUCT(BlueprintType)
struct FECsBlockchainContractFunction : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsBlockchainContractFunction() {}
	FECsBlockchainContractFunction(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsBlockchainContractFunction() {}
};

FORCEINLINE uint32 GetTypeHash(const FECsBlockchainContractFunction& b)
{
	return FCrc::MemCrc_DEPRECATED(&b, sizeof(FECsBlockchainContractFunction));
}

struct EMCsBlockchainContractFunction : public TCsEnumMap<FECsBlockchainContractFunction, uint8>
{
protected:
	EMCsBlockchainContractFunction() {}
	EMCsBlockchainContractFunction(const EMCsBlockchainContractFunction &) = delete;
	EMCsBlockchainContractFunction(EMCsBlockchainContractFunction &&) = delete;
public:
	~EMCsBlockchainContractFunction() {}

	static EMCsBlockchainContractFunction& Get()
	{
		static EMCsBlockchainContractFunction Instance;
		return Instance;
	}
};

UENUM(BlueprintType)
namespace ECsBlockchainContractFunctionArgumentType
{
	enum Type
	{
		Int32											UMETA(DisplayName = "Int32"),
		Float											UMETA(DisplayName = "Float"),
		String											UMETA(DisplayName = "String"),
		ECsBlockchainContractFunctionArgumentType_MAX	UMETA(Hidden),
	};
}

#define ECS_BLOCKCHAIN_CONTRACT_FUNCTION_ARGUMENT_TYPE_MAX (uint8)ECsBlockchainContractFunctionArgumentType::ECsBlockchainContractFunctionArgumentType_MAX
typedef ECsBlockchainContractFunctionArgumentType::Type TCsBlockchainContractFunctionArgumentType;

namespace ECsBlockchainContractFunctionArgumentType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Int32 = TCsString(TEXT("Int32"), TEXT("int32"));
		const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
		const TCsString String = TCsString(TEXT("String"), TEXT("string"));
	}

	namespace Ref
	{
		const Type Int32 = Type::Int32;
		const Type Float = Type::Float;
		const Type String = Type::String;
		const Type ECsBlockchainContractFunctionArgumentType_MAX = Type::ECsBlockchainContractFunctionArgumentType_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Int32) { return Str::Int32.Value; }
		if (EType == Type::Float) { return Str::Float.Value; }
		if (EType == Type::String) { return Str::String.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &InString)
	{
		if (InString == Str::Int32) { return Ref::Int32; }
		if (InString == Str::Float) { return Ref::Float; }
		if (InString == Str::String) { return Ref::String; }
		return Ref::ECsBlockchainContractFunctionArgumentType_MAX;
	}
}

USTRUCT(BlueprintType)
struct FCsBlockchainContractFunctionArgument
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	TEnumAsByte<ECsBlockchainContractFunctionArgumentType::Type> ValueType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	int32 Value_int32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	float Value_float;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Value_FString;

	FCsBlockchainContractFunctionArgument() {}
	FCsBlockchainContractFunctionArgument(const TCsBlockchainContractFunctionArgumentType &InValueType, const int32 &Value)
	{
		ValueType = InValueType;
		Value_int32 = Value;
	}

	FCsBlockchainContractFunctionArgument(const TCsBlockchainContractFunctionArgumentType &InValueType, const float &Value)
	{
		ValueType = InValueType;
		Value_float = Value;
	}

	FCsBlockchainContractFunctionArgument(const TCsBlockchainContractFunctionArgumentType &InValueType, const FString &Value)
	{
		ValueType = InValueType;
		Value_FString = Value;
	}
	~FCsBlockchainContractFunctionArgument(){}

	FCsBlockchainContractFunctionArgument& operator=(const FCsBlockchainContractFunctionArgument& B)
	{
		ValueType = B.ValueType;
		Value_int32 = B.Value_int32;
		Value_float = B.Value_float;
		Value_FString = B.Value_FString;
		return *this;
	}

	bool operator==(const FCsBlockchainContractFunctionArgument& B) const
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

	bool operator!=(const FCsBlockchainContractFunctionArgument& B) const
	{
		return !(*this == B);
	}

	FString ToString()
	{
		// Int32
		if (ValueType == ECsBlockchainContractFunctionArgumentType::Int32)
			return FString::FromInt(Value_int32);
		// Float
		if (ValueType == ECsBlockchainContractFunctionArgumentType::Float)
			return FString::SanitizeFloat(Value_float);
		// String
		if (ValueType == ECsBlockchainContractFunctionArgumentType::String)
			return TEXT("'") + Value_FString + TEXT("'");
		return ECsCachedString::Str::Empty;
	}

	void Clear()
	{
		Value_int32 = 0;
		Value_float = 0.0f;
		Value_FString = ECsCachedString::Str::Empty;
	}
};

UENUM(BlueprintType)
namespace ECsBlockchainContractFunctionReturnType
{
	enum Type
	{
		Int32										UMETA(DisplayName = "Int32"),
		Float										UMETA(DisplayName = "Float"),
		String										UMETA(DisplayName = "STring"),
		ECsBlockchainContractFunctionReturnType_MAX	UMETA(Hidden),
	};
}

#define ECS_BLOCKCHAIN_CONTRACT_FUNCTION_RETURN_TYPE_MAX (uint8)ECsBlockchainContractFunctionReturnType::ECsBlockchainContractFunctionReturnType_MAX
typedef ECsBlockchainContractFunctionReturnType::Type TCsBlockchainContractFunctionReturnType;

namespace ECsBlockchainContractFunctionReturnType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Int32 = TCsString(TEXT("Int32"), TEXT("int32"));
		const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
		const TCsString String = TCsString(TEXT("String"), TEXT("string"));
	}

	namespace Ref
	{
		const Type Int32 = Type::Int32;
		const Type Float = Type::Float;
		const Type String = Type::String;
		const Type ECsBlockchainContractFunctionReturnType_MAX = Type::ECsBlockchainContractFunctionReturnType_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Int32) { return Str::Int32.Value; }
		if (EType == Type::Float) { return Str::Float.Value; }
		if (EType == Type::String) { return Str::String.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &InString)
	{
		if (InString == Str::Int32) { return Ref::Int32; }
		if (InString == Str::Float) { return Ref::Float; }
		if (InString == Str::String) { return Ref::String; }
		return Ref::ECsBlockchainContractFunctionReturnType_MAX;
	}
}

USTRUCT(BlueprintType)
struct FCsBlockchainContractFunctionReturn
{
	GENERATED_USTRUCT_BODY()

	//public static readonly CgBlockchainContractFunctionReturn Void = new CgBlockchainContractFunctionReturn(ECgBlockchainContractFunctionReturnType.MAX, null);
	//public static readonly CgBlockchainContractFunctionReturn Number = new CgBlockchainContractFunctionReturn(ECgBlockchainContractFunctionReturnType.Number, 0);
	//public static readonly CgBlockchainContractFunctionReturn String = new CgBlockchainContractFunctionReturn(ECgBlockchainContractFunctionReturnType.String, "");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	TEnumAsByte<ECsBlockchainContractFunctionReturnType::Type> ValueType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	int32 Value_int32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	float Value_float;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Value_FString;

	FCsBlockchainContractFunctionReturn() {}
	FCsBlockchainContractFunctionReturn(const TCsBlockchainContractFunctionReturnType &InValueType, const int32 &Value)
	{
		ValueType = InValueType;
		Value_int32 = Value;
	}

	FCsBlockchainContractFunctionReturn(const TCsBlockchainContractFunctionReturnType &InValueType, const float &Value)
	{
		ValueType = InValueType;
		Value_float = Value;
	}

	FCsBlockchainContractFunctionReturn(const TCsBlockchainContractFunctionReturnType &InValueType, const FString &Value)
	{
		ValueType = InValueType;
		Value_FString = Value;
	}

	~FCsBlockchainContractFunctionReturn(){}

	FCsBlockchainContractFunctionReturn& operator=(const FCsBlockchainContractFunctionReturn& B)
	{
		ValueType = B.ValueType;
		Value_int32 = B.Value_int32;
		Value_float = B.Value_float;
		Value_FString = B.Value_FString;
		return *this;
	}

	bool operator==(const FCsBlockchainContractFunctionReturn& B) const
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

	bool operator!=(const FCsBlockchainContractFunctionReturn& B) const
	{
		return !(*this == B);
	}

	FString ToString()
	{
		// Int32
		if (ValueType == ECsBlockchainContractFunctionReturnType::Int32)
			return FString::FromInt(Value_int32);
		// Float
		if (ValueType == ECsBlockchainContractFunctionReturnType::Float)
			return FString::FromInt(Value_float);
		// String
		if (ValueType == ECsBlockchainContractFunctionReturnType::String)
			return FString::SanitizeFloat(Value_float);
		return ECsCachedString::Str::Empty;
	}

	void Clear()
	{
		Value_int32 = 0;
		Value_float = 0.0f;
		Value_FString = ECsCachedString::Str::Empty;
	}
};

USTRUCT(BlueprintType)
struct FCsBlockchainContractFunction
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Signature;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	TArray<FCsBlockchainContractFunctionArgument> Arguments;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FCsBlockchainContractFunctionReturn Return;

	FCsBlockchainContractFunction(){}
	FCsBlockchainContractFunction(const FString &InSignature, const TArray<FCsBlockchainContractFunctionArgument> &Args, const FCsBlockchainContractFunctionReturn &Ret)
	{
		Signature = InSignature;

		Arguments.Reset();

		const int32 Count = Args.Num();
		
		for (int32 I = 0; I < Count; ++I)
		{
			Arguments.Add(Args[I]);
		}

		Return = Ret;
	}

	~FCsBlockchainContractFunction() {}

	FCsBlockchainContractFunction& operator=(const FCsBlockchainContractFunction& B)
	{
		Signature = B.Signature;

		Arguments.Reset();

		const int32 Count = B.Arguments.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Arguments.Add(Arguments[I]);
		}

		Return = B.Return;
		return *this;
	}

	bool operator==(const FCsBlockchainContractFunction& B) const
	{
		if (Signature != B.Signature)
			return false;

		if (Arguments.Num() != B.Arguments.Num())
			return false;

		const int32 Count = Arguments.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Arguments[I] != B.Arguments[I])
				return false;
		}

		if (Return != B.Return)
			return false;
		return true;
	}

	bool operator!=(const FCsBlockchainContractFunction& B) const
	{
		return !(*this == B);
	}

	void SetArgument(const int32 &Index, const int32 &Value)
	{
		Arguments[Index].Value_int32 = Value;
	}

	void SetArguments(const TArray<FCsBlockchainContractFunctionArgument> &Args)
	{
		Arguments.Reset();

		const int32 Count = Args.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Arguments.Add(Args[I]);
		}
	}

	FString BuildConstantFunction()
	{
		FString Output = Signature + TEXT("(");

		if (Arguments.Num() > CS_EMPTY)
		{
			const int32 Count = Arguments.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				Output += Arguments[I].ToString();

				if (I < Count - 1)
					Output += TEXT(",");
			}
		}

		Output += TEXT(");");

		return Output;
	}

	FString BuildEstimateFunction(const FString &Address)
	{
		FString Output = Signature;

		Output += TEXT(".estimateGas(");

		if (Arguments.Num() > CS_EMPTY)
		{
			const int32 Count = Arguments.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				Output += Arguments[I].ToString();
				Output += TEXT(",");
			}
		}

		Output += TEXT(" { from: ") + Address + TEXT(" });");

		return Output;
	}

	FString BuildStateChangeFunction(const FString &Address, const int32 &Gas)
	{
		FString Output = Signature;

		Output += TEXT("(");

		if (Arguments.Num() > CS_EMPTY)
		{
			const int32 Count = Arguments.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				Output += Arguments[I].ToString();
				Output += TEXT(",");
			}
		}

		Output += TEXT(" { from: ") + Address + TEXT(", gas: ") + FString::FromInt(Gas) + TEXT(" });");

		return Output;
	}

	void Clear()
	{
		const int32 Count = Arguments.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Arguments[I].Clear();
		}
		Return.Clear();
	}
};

USTRUCT(BlueprintType)
struct FCsBlockchainContractFunctionPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FECsBlockchainContract Contract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FECsBlockchainContractFunction Function;

	//void* Payload;

	FCsBlockchainContractFunctionPayload(){}
	FCsBlockchainContractFunctionPayload(const FECsBlockchainContract &EContract, const FECsBlockchainContractFunction &EFn)
	{
		Contract = EContract;
		Function = EFn;
		//Payload = payload;
	}

	~FCsBlockchainContractFunctionPayload(){}

	FCsBlockchainContractFunctionPayload& operator=(const FCsBlockchainContractFunctionPayload& B)
	{
		Contract = B.Contract;
		Function = B.Function;
		return *this;
	}

	bool operator==(const FCsBlockchainContractFunctionPayload& B) const
	{
		return Contract == B.Contract && Function == B.Function;
	}

	bool operator!=(const FCsBlockchainContractFunctionPayload& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion Function

class CSCORE_API ICsBlockchainContract
{
public:

	ICsBlockchainContract();
	ICsBlockchainContract(const FString &InName);
	virtual ~ICsBlockchainContract();

	virtual const FString& GetName() = 0;

	virtual bool IsValid() = 0;
	virtual FString ToString() = 0;
	virtual void Parse(const FString &Str) = 0;
	virtual void ParseFromFilePath(const FString &Path) = 0;
};