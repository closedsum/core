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
namespace ECgBlockchainContractFunctionArgumentType
{
	enum Type
	{
		Int32											UMETA(DisplayName = "Int32"),
		Float											UMETA(DisplayName = "Float"),
		String											UMETA(DisplayName = "String"),
		ECgBlockchainContractFunctionArgumentType_MAX	UMETA(Hidden),
	};
}

#define ECS_BLOCKCHAIN_CONTRACT_FUNCTION_ARGUMENT_TYPE_MAX (uint8)ECgBlockchainContractFunctionArgumentType::ECgBlockchainContractFunctionArgumentType_MAX
typedef ECgBlockchainContractFunctionArgumentType::Type TCgBlockchainContractFunctionArgumentType;

namespace ECgBlockchainContractFunctionArgumentType
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
		const Type ECgBlockchainContractFunctionArgumentType_MAX = Type::ECgBlockchainContractFunctionArgumentType_MAX;
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
		return Ref::ECgBlockchainContractFunctionArgumentType_MAX;
	}
}

USTRUCT(BlueprintType)
struct FCsBlockchainContractFunctionArgument
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	TEnumAsByte<ECgBlockchainContractFunctionArgumentType::Type> ValueType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	int32 Value_int32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	float Value_float;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Value_FString;

	FCsBlockchainContractFunctionArgument() {}
	FCsBlockchainContractFunctionArgument(const TCgBlockchainContractFunctionArgumentType &InValueType, const int32 &Value)
	{
		ValueType = InValueType;
		Value_int32 = Value;
	}

	FCsBlockchainContractFunctionArgument(const TCgBlockchainContractFunctionArgumentType &InValueType, const float &Value)
	{
		ValueType = InValueType;
		Value_float = Value;
	}

	FCsBlockchainContractFunctionArgument(const TCgBlockchainContractFunctionArgumentType &InValueType, const FString &Value)
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
		if (ValueType == ECgBlockchainContractFunctionArgumentType::Int32)
			return FString::FromInt(Value_int32);
		// Float
		if (ValueType == ECgBlockchainContractFunctionArgumentType::Float)
			return FString::SanitizeFloat(Value_float);
		// String
		if (ValueType == ECgBlockchainContractFunctionArgumentType::String)
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

class ICsBlockchainContract
{
public:

	ICsBlockchainContract();
	virtual ~ICsBlockchainContract();

	virtual const FString& GetName() = 0;

	virtual bool IsValid() = 0;
	virtual FString ToString() = 0;
	virtual void Parse(const FString &Str) = 0;
	virtual void ParseFromFilePath(const FString &Path) = 0;
};