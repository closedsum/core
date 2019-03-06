// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeTypes.h"
#include "Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType.h"

#include "CsTypes_BehaviorTree.generated.h"
#pragma once

// BlackboardKeyType

USTRUCT(BlueprintType)
struct CSCORE_API FECsBlackboardKeyType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsBlackboardKeyType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsBlackboardKeyType)

struct CSCORE_API EMCsBlackboardKeyType : public TCsEnumStructMap<FECsBlackboardKeyType, uint8>
{
protected:
	EMCsBlackboardKeyType() {}
	EMCsBlackboardKeyType(const EMCsBlackboardKeyType &) = delete;
	EMCsBlackboardKeyType(EMCsBlackboardKeyType &&) = delete;
public:
	~EMCsBlackboardKeyType() {}
private:
	static EMCsBlackboardKeyType* Instance;

public:
	static EMCsBlackboardKeyType& Get();
};

namespace ECsBlackboardKeyType
{
	extern CSCORE_API const FECsBlackboardKeyType Bool;
	extern CSCORE_API const FECsBlackboardKeyType Enum;
	extern CSCORE_API const FECsBlackboardKeyType Int;
	extern CSCORE_API const FECsBlackboardKeyType Float;
	extern CSCORE_API const FECsBlackboardKeyType Name;
	extern CSCORE_API const FECsBlackboardKeyType String;
	extern CSCORE_API const FECsBlackboardKeyType Vector;
	extern CSCORE_API const FECsBlackboardKeyType Rotator;
	extern CSCORE_API const FECsBlackboardKeyType Object;
	extern CSCORE_API const FECsBlackboardKeyType Class;
}

struct CSCORE_API FCsBlackboardKeyTypeHelper
{
	static const FECsBlackboardKeyType& GetType(const struct FBlackboardKeySelector &Key);
};

// BTTaskLogicalOperator

UENUM()
namespace ECsBTTask_LogicalOperator
{
	enum Type
	{
		And								UMETA(DisplayName = "And"),
		Or								UMETA(DisplayName = "Or"),
		ECsBTTask_LogicalOperator_MAX	UMETA(Hidden),
	};
}

typedef ECsBTTask_LogicalOperator::Type TCsBTTaskLogicalOperator;

struct CSCORE_API EMCsBTTask_LogicalOperator : public TCsEnumMap<ECsBTTask_LogicalOperator::Type>
{
protected:
	EMCsBTTask_LogicalOperator() {}
	EMCsBTTask_LogicalOperator(const EMCsBTTask_LogicalOperator &) = delete;
	EMCsBTTask_LogicalOperator(EMCsBTTask_LogicalOperator &&) = delete;
public:
	~EMCsBTTask_LogicalOperator() {}
private:
	static EMCsBTTask_LogicalOperator* Instance;

public:
	static EMCsBTTask_LogicalOperator& Get();
};

namespace ECsBTTask_LogicalOperator
{
	namespace Ref
	{
		extern CSCORE_API const Type And;
		extern CSCORE_API const Type Or;
		extern CSCORE_API const Type ECsBTTask_LogicalOperator_MAX;
	}

	namespace Sym
	{
		extern CSCORE_API const FString And; // = TEXT("&");
		extern CSCORE_API const FString Or; // = TEXT("|");
	}

	FORCEINLINE const FString& ToSymbol(const Type &EType)
	{
		if (EType == Type::And) { return Sym::And; }
		if (EType == Type::Or) { return Sym::Or; }
		return ECsCached::Str::Empty;
	}
}

UENUM()
namespace ECsBTTask_BasicSetOperation
{
	enum Type
	{
		Set								UMETA(DisplayName = "Set"),
		Clear							UMETA(DisplayName = "Clear"),
		ECsBTTask_BasicSetOperation_MAX	UMETA(Hidden),
	};
}

typedef ECsBTTask_BasicSetOperation::Type TCsBTTask_BasicSetOperation;

struct CSCORE_API EMCsBTTask_BasicSetOperation : public TCsEnumMap<ECsBTTask_BasicSetOperation::Type>
{
protected:
	EMCsBTTask_BasicSetOperation() {}
	EMCsBTTask_BasicSetOperation(const EMCsBTTask_BasicSetOperation &) = delete;
	EMCsBTTask_BasicSetOperation(EMCsBTTask_BasicSetOperation &&) = delete;
public:
	~EMCsBTTask_BasicSetOperation() {}
private:
	static EMCsBTTask_BasicSetOperation* Instance;

public:
	static EMCsBTTask_BasicSetOperation& Get();
};

namespace ECsBTTask_BasicSetOperation
{
	namespace Ref
	{
		extern CSCORE_API const Type Set;
		extern CSCORE_API const Type Clear;
		extern CSCORE_API const Type ECsBTTask_BasicSetOperation_MAX;
	}
}

namespace EBasicKeyOperation
{
	namespace Sym
	{
		extern CSCORE_API const FString Set; //= TEXT("true");
		extern CSCORE_API const FString NotSet; //= TEXT("false");
	}

	FORCEINLINE const FString& ToSymbol(const Type &EType)
	{
		if (EType == Type::Set) { return Sym::Set; }
		if (EType == Type::NotSet) { return Sym::NotSet; }
		return ECsCached::Str::Empty;
	}
}

namespace EArithmeticKeyOperation
{
	namespace Sym
	{
		extern CSCORE_API const FString Equal; //= TEXT("=");
		extern CSCORE_API const FString NotEqual; // = TEXT("!=");
		extern CSCORE_API const FString Less; // =TEXT("<");
		extern CSCORE_API const FString LessOrEqual; // = TEXT("<=");
		extern CSCORE_API const FString Greater; // = TEXT(">");
		extern CSCORE_API const FString GreaterOrEqual; // = TEXT(">=");
	}

	FORCEINLINE const FString& ToSymbol(const Type &EType)
	{
		if (EType == Type::Equal) { return Sym::Equal; }
		if (EType == Type::NotEqual) { return Sym::NotEqual; }
		if (EType == Type::Less) { return Sym::Less; }
		if (EType == Type::LessOrEqual) { return Sym::LessOrEqual; }
		if (EType == Type::Greater) { return Sym::Greater; }
		if (EType == Type::GreaterOrEqual) { return Sym::GreaterOrEqual; }
		return ECsCached::Str::Empty;
	}
}

namespace ETextKeyOperation
{
	namespace Sym
	{
		extern CSCORE_API const FString Equal; // = TEXT("=");
		extern CSCORE_API const FString NotEqual; // = TEXT("!=");
		extern CSCORE_API const FString Contain; // = TEXT("contains");
		extern CSCORE_API const FString NotContain; // = TEXT("not contains");
	}

	FORCEINLINE const FString& ToSymbol(const Type &EType)
	{
		if (EType == Type::Equal) { return Sym::Equal; }
		if (EType == Type::NotEqual) { return Sym::NotEqual; }
		if (EType == Type::Contain) { return Sym::Contain; }
		if (EType == Type::NotContain) { return Sym::NotContain; }
		return ECsCached::Str::Empty;
	}
}

USTRUCT()
struct CSCORE_API FCsBTTask_KeyValue_Compare
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector Key;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	TEnumAsByte<EBasicKeyOperation::Type> BasicOperation;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	TEnumAsByte<EArithmeticKeyOperation::Type> ArithmeticOperation;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	TEnumAsByte<ETextKeyOperation::Type> TextOperation;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	TEnumAsByte<ESearchCase::Type> SearchCase;

	FECsBlackboardKeyType Type;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	int32 Value_Int;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	float Value_Float;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FName Value_Name;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FString Value_String;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FVector Value_Vector;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FRotator Value_Rotator;

	bool Last_Evaluation;

	FCsBTTask_KeyValue_Compare() :
		Key(),
		BasicOperation(EBasicKeyOperation::NotSet),
		ArithmeticOperation(EArithmeticKeyOperation::Equal),
		TextOperation(ETextKeyOperation::Contain),
		Value_Int(0),
		Value_Float(0.0f),
		Value_Name(NAME_None),
		Value_Vector(0.0f),
		Value_Rotator(0.0f)
	{
		SearchCase	= ESearchCase::IgnoreCase;
		Type		= EMCsBlackboardKeyType::Get().GetMAX();
		Last_Evaluation = false;
	}
	~FCsBTTask_KeyValue_Compare(){}

public:
	void Init(const FString& FunctionName);
	bool IsValid();
	bool Evaluate(const class UBlackboardComponent* Blackboard);
protected:
	bool Evaluate_Internal(const class UBlackboardComponent* Blackboard);
public:
	FString GetRuntimeDescription(const class UBlackboardComponent* Blackboard) const;
	FString GetStaticDescription() const;
};