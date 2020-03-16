// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsTypes_Enum.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeTypes.h"
#include "Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType.h"

#include "CsTypes_BehaviorTree.generated.h"
#pragma once

// BlackboardKeyType
#pragma region
USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsBlackboardKeyType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsBlackboardKeyType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsBlackboardKeyType)

struct CSCOREDEPRECATED_API EMCsBlackboardKeyType : public TCsEnumStructMap<FECsBlackboardKeyType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsBlackboardKeyType, FECsBlackboardKeyType, uint8)
};

namespace NCsBlackboardKeyType
{
	typedef FECsBlackboardKeyType Type;

	extern CSCOREDEPRECATED_API const Type Bool;
	extern CSCOREDEPRECATED_API const Type Enum;
	extern CSCOREDEPRECATED_API const Type Int;
	extern CSCOREDEPRECATED_API const Type Float;
	extern CSCOREDEPRECATED_API const Type Name;
	extern CSCOREDEPRECATED_API const Type String;
	extern CSCOREDEPRECATED_API const Type Vector;
	extern CSCOREDEPRECATED_API const Type Rotator;
	extern CSCOREDEPRECATED_API const Type Object;
	extern CSCOREDEPRECATED_API const Type Class;
}

struct CSCOREDEPRECATED_API FCsBlackboardKeyTypeHelper
{
	static const FECsBlackboardKeyType& GetType(const struct FBlackboardKeySelector& Key);
};

#pragma endregion BlackboardKeyType

// BTTaskLogicalOperator
#pragma region

UENUM(BlueprintType)
enum class ECsBTTask_LogicalOperator : uint8
{
	And								UMETA(DisplayName = "And"),
	Or								UMETA(DisplayName = "Or"),
	ECsBTTask_LogicalOperator_MAX	UMETA(Hidden),
};

struct CSCOREDEPRECATED_API EMCsBTTask_LogicalOperator : public TCsEnumMap<ECsBTTask_LogicalOperator>
{
	CS_ENUM_MAP_BODY(EMCsBTTask_LogicalOperator, ECsBTTask_LogicalOperator)
};

namespace NCsBTTask_LogicalOperator
{
	typedef ECsBTTask_LogicalOperator Type;

	namespace Ref
	{
		extern CSCOREDEPRECATED_API const Type And;
		extern CSCOREDEPRECATED_API const Type Or;
		extern CSCOREDEPRECATED_API const Type ECsBTTask_LogicalOperator_MAX;
	}

	namespace Sym
	{
		extern CSCOREDEPRECATED_API const FString And; // = TEXT("&");
		extern CSCOREDEPRECATED_API const FString Or; // = TEXT("|");
	}

	FORCEINLINE const FString& ToSymbol(const Type& EType)
	{
		if (EType == Type::And) { return Sym::And; }
		if (EType == Type::Or) { return Sym::Or; }
		return NCsCached::Str::Empty;
	}
}

#pragma endregion BTTaskLogicalOperator

// BTTask_BasicSetOperation
#pragma region

UENUM(BlueprintType)
enum class ECsBTTask_BasicSetOperation : uint8
{
	Set								UMETA(DisplayName = "Set"),
	Clear							UMETA(DisplayName = "Clear"),
	ECsBTTask_BasicSetOperation_MAX	UMETA(Hidden),
};

struct CSCOREDEPRECATED_API EMCsBTTask_BasicSetOperation : public TCsEnumMap<ECsBTTask_BasicSetOperation>
{
	CS_ENUM_MAP_BODY(EMCsBTTask_BasicSetOperation, ECsBTTask_BasicSetOperation)
};

namespace NCsBTTask_BasicSetOperation
{
	typedef ECsBTTask_BasicSetOperation Type;

	namespace Ref
	{
		extern CSCOREDEPRECATED_API const Type Set;
		extern CSCOREDEPRECATED_API const Type Clear;
		extern CSCOREDEPRECATED_API const Type ECsBTTask_BasicSetOperation_MAX;
	}
}

#pragma endregion BTTask_BasicSetOperation

// BasicKeyOperation
#pragma region

namespace EBasicKeyOperation
{
	namespace Sym
	{
		extern CSCOREDEPRECATED_API const FString Set; //= TEXT("true");
		extern CSCOREDEPRECATED_API const FString NotSet; //= TEXT("false");
	}

	FORCEINLINE const FString& ToSymbol(const Type& EType)
	{
		if (EType == Type::Set) { return Sym::Set; }
		if (EType == Type::NotSet) { return Sym::NotSet; }
		return NCsCached::Str::Empty;
	}
}

#pragma endregion BasicKeyOperation

// ArithmeticKeyOperation
#pragma region

namespace EArithmeticKeyOperation
{
	namespace Sym
	{
		extern CSCOREDEPRECATED_API const FString Equal; //= TEXT("=");
		extern CSCOREDEPRECATED_API const FString NotEqual; // = TEXT("!=");
		extern CSCOREDEPRECATED_API const FString Less; // =TEXT("<");
		extern CSCOREDEPRECATED_API const FString LessOrEqual; // = TEXT("<=");
		extern CSCOREDEPRECATED_API const FString Greater; // = TEXT(">");
		extern CSCOREDEPRECATED_API const FString GreaterOrEqual; // = TEXT(">=");
	}

	FORCEINLINE const FString& ToSymbol(const Type& EType)
	{
		if (EType == Type::Equal) { return Sym::Equal; }
		if (EType == Type::NotEqual) { return Sym::NotEqual; }
		if (EType == Type::Less) { return Sym::Less; }
		if (EType == Type::LessOrEqual) { return Sym::LessOrEqual; }
		if (EType == Type::Greater) { return Sym::Greater; }
		if (EType == Type::GreaterOrEqual) { return Sym::GreaterOrEqual; }
		return NCsCached::Str::Empty;
	}
}

#pragma endregion ArithmeticKeyOperation

// TextKeyOperation
#pragma region

namespace ETextKeyOperation
{
	namespace Sym
	{
		extern CSCOREDEPRECATED_API const FString Equal; // = TEXT("=");
		extern CSCOREDEPRECATED_API const FString NotEqual; // = TEXT("!=");
		extern CSCOREDEPRECATED_API const FString Contain; // = TEXT("contains");
		extern CSCOREDEPRECATED_API const FString NotContain; // = TEXT("not contains");
	}

	FORCEINLINE const FString& ToSymbol(const Type& EType)
	{
		if (EType == Type::Equal) { return Sym::Equal; }
		if (EType == Type::NotEqual) { return Sym::NotEqual; }
		if (EType == Type::Contain) { return Sym::Contain; }
		if (EType == Type::NotContain) { return Sym::NotContain; }
		return NCsCached::Str::Empty;
	}
}

#pragma endregion TextKeyOperation

// FCsBTTask_KeyValue_Compare
#pragma region

USTRUCT()
struct CSCOREDEPRECATED_API FCsBTTask_KeyValue_Compare
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

#pragma endregion FCsBTTask_KeyValue_Compare