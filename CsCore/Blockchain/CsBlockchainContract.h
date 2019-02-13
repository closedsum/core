// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Types/CsTypes_Primitive.h"
#include "CsBlockchainContract.generated.h"

USTRUCT(BlueprintType)
struct CSCORE_API FECsBlockchainContract : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsBlockchainContract() {}
	FECsBlockchainContract(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsBlockchainContract(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsBlockchainContract() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsBlockchainContract& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsBlockchainContract : public TCsEnumStructMap<FECsBlockchainContract, uint8>
{
protected:
	EMCsBlockchainContract() {}
	EMCsBlockchainContract(const EMCsBlockchainContract &) = delete;
	EMCsBlockchainContract(EMCsBlockchainContract &&) = delete;
public:
	~EMCsBlockchainContract() {}
private:
	static EMCsBlockchainContract* Instance;

public:
	static EMCsBlockchainContract& Get();
};

// Argument
#pragma region

	// BlockchainContractArgumentType
#pragma region

UENUM(BlueprintType)
enum class ECsBlockchainContractArgumentType : uint8
{
	Bool									UMETA(DisplayName = "Bool"),
	Int32									UMETA(DisplayName = "Int32"),
	Float									UMETA(DisplayName = "Float"),
	String									UMETA(DisplayName = "String"),
	StringString							UMETA(DisplayName = "StringString"),
	ECsBlockchainContractArgumentType_MAX	UMETA(Hidden),
};

#define ECS_BLOCKCHAIN_CONTRACT_ARGUMENT_TYPE_MAX (uint8)ECsBlockchainContractArgumentType::ECsBlockchainContractArgumentType_MAX

struct CSCORE_API EMCsBlockchainContractArgumentType : public TCsEnumMap<ECsBlockchainContractArgumentType>
{
protected:
	EMCsBlockchainContractArgumentType() {}
	EMCsBlockchainContractArgumentType(const EMCsBlockchainContractArgumentType &) = delete;
	EMCsBlockchainContractArgumentType(EMCsBlockchainContractArgumentType &&) = delete;
public:
	~EMCsBlockchainContractArgumentType() {}
private:
	static EMCsBlockchainContractArgumentType* Instance;

public:
	static EMCsBlockchainContractArgumentType& Get();
};

namespace NCsBlockchainContractArgumentType
{
	namespace Ref
	{
		typedef ECsBlockchainContractArgumentType Type;

		extern CSCORE_API const Type Bool;
		extern CSCORE_API const Type Int32;
		extern CSCORE_API const Type Float;
		extern CSCORE_API const Type String;
		extern CSCORE_API const Type StringString;
		extern CSCORE_API const Type ECsBlockchainContractArgumentType_MAX;
	}
}

#pragma endregion BlockchainContractArgumentType

USTRUCT(BlueprintType)
struct FCsBlockchainContractArgument
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	ECsBlockchainContractArgumentType ValueType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	bool Value_bool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	int32 Value_int32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	float Value_float;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Value_FString;

	FCsBlockchainContractArgument()
	{
		Reset();
	}

	FCsBlockchainContractArgument(const FString &InName, const ECsBlockchainContractArgumentType &InValueType)
	{
		// HACKY: For now add ',' to distinguish between the same input arguments in the ABI
		Name	  = InName + TEXT(",");
		ValueType = InValueType;
		Value_bool = false;
		Value_int32 = 0;
		Value_float = 0.0f;
	}

	FCsBlockchainContractArgument(const FString &InName, const ECsBlockchainContractArgumentType &InValueType, const bool &Value)
	{
		FCsBlockchainContractArgument(InName, InValueType);
		Value_bool = Value;
	}

	FCsBlockchainContractArgument(const FString &InName, const ECsBlockchainContractArgumentType &InValueType, const int32 &Value)
	{
		FCsBlockchainContractArgument(InName, InValueType);
		Value_int32 = Value;
	}

	FCsBlockchainContractArgument(const FString &InName, const ECsBlockchainContractArgumentType &InValueType, const float &Value)
	{
		FCsBlockchainContractArgument(InName, InValueType);
		Value_float = Value;
	}

	FCsBlockchainContractArgument(const FString &InName, const ECsBlockchainContractArgumentType &InValueType, const FString &Value)
	{
		FCsBlockchainContractArgument(InName, InValueType);
		Value_FString = Value;
	}

	~FCsBlockchainContractArgument(){}

	FORCEINLINE FCsBlockchainContractArgument& operator=(const FCsBlockchainContractArgument& B)
	{
		Name = B.Name;
		ValueType = B.ValueType;
		Value_bool = B.Value_bool;
		Value_int32 = B.Value_int32;
		Value_float = B.Value_float;
		Value_FString = B.Value_FString;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsBlockchainContractArgument& B) const
	{
		if (Name != B.Name) { return false; }
		if (ValueType != B.ValueType) { return false; }
		if (Value_bool != B.Value_bool) { return false; }
		if (Value_int32 != B.Value_int32) { return false; }
		if (Value_float != B.Value_float) { return false; }
		if (Value_FString != B.Value_FString) { return false; }
		return true;
	}

	FORCEINLINE bool operator!=(const FCsBlockchainContractArgument& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const FString &InName, const ECsBlockchainContractArgumentType &InValueType)
	{
		// HACKY: For now add ',' to distinguish between the same input arguments in the ABI
		Name = InName + TEXT(",");
		ValueType = InValueType;
	}

	FORCEINLINE void Set(const FString &InName, const ECsBlockchainContractArgumentType &InValueType, const bool &Value)
	{
		Set(InName, InValueType);
		Value_bool = Value;
	}

	FORCEINLINE void Set(const FString &InName, const ECsBlockchainContractArgumentType &InValueType, const int32 &Value)
	{
		Set(InName, InValueType);
		Value_int32 = Value;
	}

	FORCEINLINE void Set(const FString &InName, const ECsBlockchainContractArgumentType &InValueType, const float &Value)
	{
		Set(InName, InValueType);
		Value_float = Value;
	}

	FORCEINLINE void Set(const FString &InName, const ECsBlockchainContractArgumentType &InValueType, const FString &Value)
	{
		Set(InName, InValueType);
		Value_FString = Value;
	}

	FORCEINLINE FString ToString() const
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
		return ECsCached::Str::Empty;
	}

	FORCEINLINE void Reset()
	{
		Name = ECsCached::Str::Empty;
		ValueType = ECsBlockchainContractArgumentType::ECsBlockchainContractArgumentType_MAX;
		Value_bool = false;
		Value_int32 = 0;
		Value_float  = 0.0f;
		Value_FString = ECsCached::Str::Empty;
	}
};

#pragma endregion Argument

// Function
#pragma region

	// BlockchainContractFunction
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsBlockchainContractFunction : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsBlockchainContractFunction() {}
	FECsBlockchainContractFunction(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsBlockchainContractFunction(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsBlockchainContractFunction() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsBlockchainContractFunction& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsBlockchainContractFunction : public TCsEnumStructMap<FECsBlockchainContractFunction, uint8>
{
protected:
	EMCsBlockchainContractFunction() {}
	EMCsBlockchainContractFunction(const EMCsBlockchainContractFunction &) = delete;
	EMCsBlockchainContractFunction(EMCsBlockchainContractFunction &&) = delete;
public:
	~EMCsBlockchainContractFunction() {}
private:
	static EMCsBlockchainContractFunction* Instance;

public:
	static EMCsBlockchainContractFunction& Get();
};

#pragma endregion BlockchainContractFunction

	// BlockchainContractFunctionArgumentType
#pragma region

UENUM(BlueprintType)
enum class ECsBlockchainContractFunctionArgumentType : uint8
{
	Int32											UMETA(DisplayName = "Int32"),
	Float											UMETA(DisplayName = "Float"),
	String											UMETA(DisplayName = "String"),
	ECsBlockchainContractFunctionArgumentType_MAX	UMETA(Hidden),
};

#define ECS_BLOCKCHAIN_CONTRACT_FUNCTION_ARGUMENT_TYPE_MAX (uint8)ECsBlockchainContractFunctionArgumentType::ECsBlockchainContractFunctionArgumentType_MAX

struct CSCORE_API EMCsBlockchainContractFunctionArgumentType : public TCsEnumMap<ECsBlockchainContractFunctionArgumentType>
{
protected:
	EMCsBlockchainContractFunctionArgumentType() {}
	EMCsBlockchainContractFunctionArgumentType(const EMCsBlockchainContractFunctionArgumentType &) = delete;
	EMCsBlockchainContractFunctionArgumentType(EMCsBlockchainContractFunctionArgumentType &&) = delete;
public:
	~EMCsBlockchainContractFunctionArgumentType() {}
private:
	static EMCsBlockchainContractFunctionArgumentType* Instance;

public:
	static EMCsBlockchainContractFunctionArgumentType& Get();
};

namespace NCsBlockchainContractFunctionArgumentType
{
	namespace Ref
	{
		typedef ECsBlockchainContractFunctionArgumentType Type;

		extern CSCORE_API const Type Int32;
		extern CSCORE_API const Type Float;
		extern CSCORE_API const Type String;
		extern CSCORE_API const Type ECsBlockchainContractFunctionArgumentType_MAX;
	}
}

#pragma endregion BlockchainContractFunctionArgumentType

USTRUCT(BlueprintType)
struct FCsBlockchainContractFunctionArgument
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	ECsBlockchainContractFunctionArgumentType ValueType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	int32 Value_int32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	float Value_float;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Value_FString;

	FCsBlockchainContractFunctionArgument() :
		ValueType(ECsBlockchainContractFunctionArgumentType::ECsBlockchainContractFunctionArgumentType_MAX),
		Value_int32(0),
		Value_float(0.0f),
		Value_FString()
	{
	}

	FCsBlockchainContractFunctionArgument(const ECsBlockchainContractFunctionArgumentType &InValueType, const int32 &Value)
	{
		ValueType = InValueType;
		Value_int32 = Value;
	}

	FCsBlockchainContractFunctionArgument(const ECsBlockchainContractFunctionArgumentType &InValueType, const float &Value)
	{
		ValueType = InValueType;
		Value_float = Value;
	}

	FCsBlockchainContractFunctionArgument(const ECsBlockchainContractFunctionArgumentType &InValueType, const FString &Value)
	{
		ValueType = InValueType;
		Value_FString = Value;
	}
	~FCsBlockchainContractFunctionArgument(){}

	FORCEINLINE FCsBlockchainContractFunctionArgument& operator=(const FCsBlockchainContractFunctionArgument& B)
	{
		ValueType = B.ValueType;
		Value_int32 = B.Value_int32;
		Value_float = B.Value_float;
		Value_FString = B.Value_FString;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsBlockchainContractFunctionArgument& B) const
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

	FORCEINLINE bool operator!=(const FCsBlockchainContractFunctionArgument& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE FString ToString()
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
		return ECsCached::Str::Empty;
	}

	FORCEINLINE void Clear()
	{
		Value_int32 = 0;
		Value_float = 0.0f;
		Value_FString = ECsCached::Str::Empty;
	}
};

	// BlockchainContractFunctionReturnType
#pragma region

UENUM(BlueprintType)
enum class ECsBlockchainContractFunctionReturnType : uint8
{
	Int32										UMETA(DisplayName = "Int32"),
	Float										UMETA(DisplayName = "Float"),
	String										UMETA(DisplayName = "STring"),
	ECsBlockchainContractFunctionReturnType_MAX	UMETA(Hidden),
};

#define ECS_BLOCKCHAIN_CONTRACT_FUNCTION_RETURN_TYPE_MAX (uint8)ECsBlockchainContractFunctionReturnType::ECsBlockchainContractFunctionReturnType_MAX

struct CSCORE_API EMCsBlockchainContractFunctionReturnType : public TCsEnumMap<ECsBlockchainContractFunctionReturnType>
{
protected:
	EMCsBlockchainContractFunctionReturnType() {}
	EMCsBlockchainContractFunctionReturnType(const EMCsBlockchainContractFunctionReturnType &) = delete;
	EMCsBlockchainContractFunctionReturnType(EMCsBlockchainContractFunctionReturnType &&) = delete;
public:
	~EMCsBlockchainContractFunctionReturnType() {}
private:
	static EMCsBlockchainContractFunctionReturnType* Instance;

public:
	static EMCsBlockchainContractFunctionReturnType& Get();
};

namespace NCsBlockchainContractFunctionReturnType
{
	namespace Ref
	{
		typedef ECsBlockchainContractFunctionReturnType Type;

		extern CSCORE_API const Type Int32;
		extern CSCORE_API const Type Float;
		extern CSCORE_API const Type String;
		extern CSCORE_API const Type ECsBlockchainContractFunctionReturnType_MAX;
	}
}

#pragma endregion BlockchainContractFunctionReturnType

USTRUCT(BlueprintType)
struct FCsBlockchainContractFunctionReturn
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	ECsBlockchainContractFunctionReturnType ValueType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	int32 Value_int32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	float Value_float;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Value_FString;

	FCsBlockchainContractFunctionReturn() :
		ValueType(ECsBlockchainContractFunctionReturnType::ECsBlockchainContractFunctionReturnType_MAX),
		Value_int32(0),
		Value_float(0.0f),
		Value_FString()
	{
	}

	FCsBlockchainContractFunctionReturn(const ECsBlockchainContractFunctionReturnType &InValueType, const int32 &Value)
	{
		ValueType = InValueType;
		Value_int32 = Value;
	}

	FCsBlockchainContractFunctionReturn(const ECsBlockchainContractFunctionReturnType &InValueType, const float &Value)
	{
		ValueType = InValueType;
		Value_float = Value;
	}

	FCsBlockchainContractFunctionReturn(const ECsBlockchainContractFunctionReturnType &InValueType, const FString &Value)
	{
		ValueType = InValueType;
		Value_FString = Value;
	}

	~FCsBlockchainContractFunctionReturn(){}

	FORCEINLINE FCsBlockchainContractFunctionReturn& operator=(const FCsBlockchainContractFunctionReturn& B)
	{
		ValueType = B.ValueType;
		Value_int32 = B.Value_int32;
		Value_float = B.Value_float;
		Value_FString = B.Value_FString;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsBlockchainContractFunctionReturn& B) const
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

	FORCEINLINE bool operator!=(const FCsBlockchainContractFunctionReturn& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE FString ToString()
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
		return ECsCached::Str::Empty;
	}

	FORCEINLINE void Clear()
	{
		Value_int32 = 0;
		Value_float = 0.0f;
		Value_FString = ECsCached::Str::Empty;
	}
	
	FORCEINLINE void Reset()
	{
		ValueType = ECsBlockchainContractFunctionReturnType::ECsBlockchainContractFunctionReturnType_MAX;
		Clear();
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

		for (const FCsBlockchainContractFunctionArgument& Arg : Args)
		{
			Arguments.Add(Arg);
		}
		Return = Ret;
	}

	~FCsBlockchainContractFunction() {}

	FORCEINLINE FCsBlockchainContractFunction& operator=(const FCsBlockchainContractFunction& B)
	{
		Signature = B.Signature;

		Arguments.Reset();

		for (const FCsBlockchainContractFunctionArgument& Arg : B.Arguments)
		{
			Arguments.Add(Arg);
		}

		Return = B.Return;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsBlockchainContractFunction& B) const
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

	FORCEINLINE bool operator!=(const FCsBlockchainContractFunction& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const FString &InSignature, const TArray<FCsBlockchainContractFunctionArgument> &Args, const FCsBlockchainContractFunctionReturn &Ret)
	{
		Signature = InSignature;

		Arguments.Reset();

		for (const FCsBlockchainContractFunctionArgument& Arg : Args)
		{
			Arguments.Add(Arg);
		}
		Return = Ret;
	}

	FORCEINLINE void SetArgument(const int32 &Index, const int32 &Value)
	{
		Arguments[Index].Value_int32 = Value;
	}

	FORCEINLINE void SetArguments(const TArray<FCsBlockchainContractFunctionArgument> &Args)
	{
		Arguments.Reset();

		for (const FCsBlockchainContractFunctionArgument& Arg : Args)
		{
			Arguments.Add(Arg);
		}
	}

	FORCEINLINE FString BuildConstantFunction()
	{
		FString Output = Signature + TEXT("(");

		const int32 Count = Arguments.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Output += Arguments[I].ToString();

			if (I < Count - 1)
				Output += TEXT(",");
		}

		Output += TEXT(");");

		return Output;
	}

	FORCEINLINE FString BuildEstimateFunction(const FString &Address)
	{
		FString Output = Signature;

		Output += TEXT(".estimateGas(");

		for (FCsBlockchainContractFunctionArgument& Arg : Arguments)
		{
			Output += Arg.ToString();
			Output += TEXT(",");
		}

		Output += TEXT(" { from: ") + Address + TEXT(" });");

		return Output;
	}

	FORCEINLINE FString BuildStateChangeFunction(const FString &Address, const int32 &Gas)
	{
		FString Output = Signature;

		Output += TEXT("(");

		for (FCsBlockchainContractFunctionArgument& Arg : Arguments)
		{
			Output += Arg.ToString();
			Output += TEXT(",");
		}

		Output += TEXT(" { from: ") + Address + TEXT(", gas: ") + FString::FromInt(Gas) + TEXT(" });");

		return Output;
	}

	FORCEINLINE void Clear()
	{
		for (FCsBlockchainContractFunctionArgument& Arg : Arguments)
		{
			Arg.Clear();
		}
		Return.Clear();
	}

	FORCEINLINE void Reset()
	{
		Signature = ECsCached::Str::Empty;
		Arguments.Reset();
		Return.Reset();
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

	FCsBlockchainContractFunctionPayload() :
		Contract(EMCsBlockchainContract::Get().GetMAX()),
		Function(EMCsBlockchainContractFunction::Get().GetMAX())
	{
	}

	FCsBlockchainContractFunctionPayload(const FECsBlockchainContract &EContract, const FECsBlockchainContractFunction &EFn)
	{
		Contract = EContract;
		Function = EFn;
		//Payload = payload;
	}

	~FCsBlockchainContractFunctionPayload(){}

	FORCEINLINE FCsBlockchainContractFunctionPayload& operator=(const FCsBlockchainContractFunctionPayload& B)
	{
		Contract = B.Contract;
		Function = B.Function;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsBlockchainContractFunctionPayload& B) const
	{
		return Contract == B.Contract && Function == B.Function;
	}

	FORCEINLINE bool operator!=(const FCsBlockchainContractFunctionPayload& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const FECsBlockchainContract &EContract, const FECsBlockchainContractFunction &EFn)
	{
		Contract = EContract;
		Function = EFn;
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