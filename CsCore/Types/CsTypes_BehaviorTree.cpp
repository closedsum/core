// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_BehaviorTree.h"
#include "CsCore.h"

#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

// BlackboardKeyType
EMCsBlackboardKeyType* EMCsBlackboardKeyType::Instance;

EMCsBlackboardKeyType& EMCsBlackboardKeyType::Get()
{
	if (!Instance)
		Instance = new EMCsBlackboardKeyType();
	return *Instance;
}

namespace ECsBlackboardKeyType
{
	CSCORE_API const FECsBlackboardKeyType Bool = EMCsBlackboardKeyType::Get().Create(TEXT("Bool"));
	CSCORE_API const FECsBlackboardKeyType Enum = EMCsBlackboardKeyType::Get().Create(TEXT("Enum"));
	CSCORE_API const FECsBlackboardKeyType Int = EMCsBlackboardKeyType::Get().Create(TEXT("Int"));
	CSCORE_API const FECsBlackboardKeyType Float = EMCsBlackboardKeyType::Get().Create(TEXT("Float"));
	CSCORE_API const FECsBlackboardKeyType Name = EMCsBlackboardKeyType::Get().Create(TEXT("Name"));
	CSCORE_API const FECsBlackboardKeyType String = EMCsBlackboardKeyType::Get().Create(TEXT("String"));
	CSCORE_API const FECsBlackboardKeyType Vector = EMCsBlackboardKeyType::Get().Create(TEXT("Vector"));
	CSCORE_API const FECsBlackboardKeyType Rotator = EMCsBlackboardKeyType::Get().Create(TEXT("Rotator"));
	CSCORE_API const FECsBlackboardKeyType Object = EMCsBlackboardKeyType::Get().Create(TEXT("Object"));
	CSCORE_API const FECsBlackboardKeyType Class = EMCsBlackboardKeyType::Get().Create(TEXT("Class"));
}

/*static*/ const FECsBlackboardKeyType& FCsBlackboardKeyTypeHelper::GetType(struct FBlackboardKeySelector &Key)
{
	// Bool
	if (Key.SelectedKeyType == UBlackboardKeyType_Bool::StaticClass())
		return ECsBlackboardKeyType::Bool;
	// Enum
	if (Key.SelectedKeyType == UBlackboardKeyType_Enum::StaticClass())
		return ECsBlackboardKeyType::Enum;
	// Int
	if (Key.SelectedKeyType == UBlackboardKeyType_Int::StaticClass())
		return ECsBlackboardKeyType::Int;
	// Float
	if (Key.SelectedKeyType == UBlackboardKeyType_Float::StaticClass())
		return ECsBlackboardKeyType::Float;
	// Name
	if (Key.SelectedKeyType == UBlackboardKeyType_Name::StaticClass())
		return ECsBlackboardKeyType::Name;
	// String
	if (Key.SelectedKeyType == UBlackboardKeyType_String::StaticClass())
		return ECsBlackboardKeyType::String;
	// Vector
	if (Key.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		return ECsBlackboardKeyType::Vector;
	// Rotator
	if (Key.SelectedKeyType == UBlackboardKeyType_Rotator::StaticClass())
		return ECsBlackboardKeyType::Rotator;
	// Object
	if (Key.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
		return ECsBlackboardKeyType::Object;
	// Class
	if (Key.SelectedKeyType == UBlackboardKeyType_Class::StaticClass())
		return ECsBlackboardKeyType::Class;
	return EMCsBlackboardKeyType::Get().GetMAX();
}

// BTTaskLogicalOperator
EMCsBTTask_LogicalOperator* EMCsBTTask_LogicalOperator::Instance;

EMCsBTTask_LogicalOperator& EMCsBTTask_LogicalOperator::Get()
{
	if (!Instance)
		Instance = new EMCsBTTask_LogicalOperator();
	return *Instance;
}

namespace ECsBTTask_LogicalOperator
{
	namespace Ref
	{
		CSCORE_API const Type And = EMCsBTTask_LogicalOperator::Get().Add(Type::And, TEXT("And"));
		CSCORE_API const Type Or = EMCsBTTask_LogicalOperator::Get().Add(Type::Or, TEXT("Or"));
		CSCORE_API const Type ECsBTTask_LogicalOperator_MAX = EMCsBTTask_LogicalOperator::Get().Add(Type::ECsBTTask_LogicalOperator_MAX, TEXT("ECsBTTask_LogicalOperator_MAX"), TEXT("MAX"));
	}

	namespace Sym
	{
		CSCORE_API const FString And = TEXT("&");
		CSCORE_API const FString Or = TEXT("|");
	}
}

// BasicKeyOperation
namespace EBasicKeyOperation
{
	namespace Sym
	{
		CSCORE_API const FString Set = TEXT("true");
		CSCORE_API const FString NotSet = TEXT("false");
	}
}

// ArithmeticKeyOperation
namespace EArithmeticKeyOperation
{
	namespace Sym
	{
		CSCORE_API const FString Equal = TEXT("=");
		CSCORE_API const FString NotEqual = TEXT("!=");
		CSCORE_API const FString Less =TEXT("<");
		CSCORE_API const FString LessOrEqual = TEXT("<=");
		CSCORE_API const FString Greater = TEXT(">");
		CSCORE_API const FString GreaterOrEqual = TEXT(".=");
	}
}

// TextKeyOperation
namespace ETextKeyOperation
{
	namespace Sym
	{
		CSCORE_API const FString Equal = TEXT("=");
		CSCORE_API const FString NotEqual = TEXT("!=");
		CSCORE_API const FString Contain = TEXT("contains");
		CSCORE_API const FString NotContain = TEXT("not contains");
	}
}

// FCsBTTaskKeyValue
#pragma region

void FCsBTTask_KeyValue_Compare::Init(const FString& FunctionName)
{
	if (Type != EMCsBlackboardKeyType::Get().GetMAX())
		return;

	Type = FCsBlackboardKeyTypeHelper::GetType(Key);

	// Currently Enum, Object, and Class Types are NOT Supported
	if (Type == ECsBlackboardKeyType::Enum ||
		Type == ECsBlackboardKeyType::Object ||
		Type == ECsBlackboardKeyType::Class)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Blackboard Key of Types: Enum, Object, and Class are NOT supported."), *FunctionName);
	}
}

bool FCsBTTask_KeyValue_Compare::IsValid()
{
	return Type != ECsBlackboardKeyType::Enum && Type != ECsBlackboardKeyType::Object && Type != ECsBlackboardKeyType::Class;
}

bool FCsBTTask_KeyValue_Compare::Evaluate(const UBlackboardComponent* Blackboard)
{
	Last_Evaluation = Evaluate_Internal(Blackboard);
	return Last_Evaluation;
}


bool FCsBTTask_KeyValue_Compare::Evaluate_Internal(const UBlackboardComponent* Blackboard)
{
	// Bool
	if (Type == ECsBlackboardKeyType::Bool)
	{
		const bool Result = Blackboard->GetValue<UBlackboardKeyType_Bool>(Key.GetSelectedKeyID());

		if (BasicOperation == EBasicKeyOperation::Set)
			return Result;
		if (BasicOperation == EBasicKeyOperation::NotSet)
			return !Result;
		return false;
	}
	// Int
	if (Type == ECsBlackboardKeyType::Int)
	{
		const int32 Value = Blackboard->GetValue<UBlackboardKeyType_Int>(Key.GetSelectedKeyID());

		if (ArithmeticOperation == EArithmeticKeyOperation::Equal)
			return Value == Value_Int;
		if (ArithmeticOperation == EArithmeticKeyOperation::NotEqual)
			return Value != Value_Int;
		if (ArithmeticOperation == EArithmeticKeyOperation::Less)
			return Value < Value_Int;
		if (ArithmeticOperation == EArithmeticKeyOperation::LessOrEqual)
			return Value <= Value_Int;
		if (ArithmeticOperation == EArithmeticKeyOperation::Greater)
			return Value > Value_Int;
		if (ArithmeticOperation == EArithmeticKeyOperation::GreaterOrEqual)
			return Value >= Value_Int;
		return false;
	}
	// Float
	if (Type == ECsBlackboardKeyType::Float)
	{
		const float Value = Blackboard->GetValue<UBlackboardKeyType_Float>(Key.GetSelectedKeyID());

		if (ArithmeticOperation == EArithmeticKeyOperation::Equal)
			return Value == Value_Float;
		if (ArithmeticOperation == EArithmeticKeyOperation::NotEqual)
			return Value != Value_Float;
		if (ArithmeticOperation == EArithmeticKeyOperation::Less)
			return Value < Value_Float;
		if (ArithmeticOperation == EArithmeticKeyOperation::LessOrEqual)
			return Value <= Value_Float;
		if (ArithmeticOperation == EArithmeticKeyOperation::Greater)
			return Value > Value_Float;
		if (ArithmeticOperation == EArithmeticKeyOperation::GreaterOrEqual)
			return Value >= Value_Float;
		return false;
	}
	// Name
	if (Type == ECsBlackboardKeyType::Name)
	{
		const FName Value = Blackboard->GetValue<UBlackboardKeyType_Name>(Key.GetSelectedKeyID());

		if (TextOperation == ETextKeyOperation::Equal)
			return Value == Value_Name;
		if (TextOperation == ETextKeyOperation::NotEqual)
			return Value != Value_Name;
		if (TextOperation == ETextKeyOperation::Contain)
			return Value.ToString().Contains(Value_Name.ToString());
		if (TextOperation == ETextKeyOperation::NotContain)
			return !Value.ToString().Contains(Value_Name.ToString());
		return false;
	}
	// String
	if (Type == ECsBlackboardKeyType::String)
	{
		const FString Value = Blackboard->GetValue<UBlackboardKeyType_String>(Key.GetSelectedKeyID());

		if (TextOperation == ETextKeyOperation::Equal)
			return Value.Equals(Value_String, SearchCase);
		if (TextOperation == ETextKeyOperation::NotEqual)
			return !Value.Equals(Value_String, SearchCase);
		if (TextOperation == ETextKeyOperation::Contain)
			return Value.Contains(Value_String, SearchCase);
		if (TextOperation == ETextKeyOperation::NotContain)
			return !Value.Contains(Value_String, SearchCase);
		return false;
	}
	// Vector
	if (Type == ECsBlackboardKeyType::Vector)
	{
		const bool Result = Value_Vector == Blackboard->GetValue<UBlackboardKeyType_Vector>(Key.GetSelectedKeyID());

		if (BasicOperation == EBasicKeyOperation::Set)
			return Result;
		if (BasicOperation == EBasicKeyOperation::NotSet)
			return !Result;
		return false;
	}
	// Rotator
	if (Type == ECsBlackboardKeyType::Rotator)
	{
		const bool Result = Value_Rotator == Blackboard->GetValue<UBlackboardKeyType_Rotator>(Key.GetSelectedKeyID());

		if (BasicOperation == EBasicKeyOperation::Set)
			return Result;
		if (BasicOperation == EBasicKeyOperation::NotSet)
			return !Result;
		return false;
	}
	return false;
}

FString FCsBTTask_KeyValue_Compare::GetStaticDescription(const class UBlackboardComponent* Blackboard) const
{
	FString Description = ECsCached::Str::Empty;
	FString Result		= Last_Evaluation ? TEXT("True") : TEXT("False");

	// Bool
	if (Type == ECsBlackboardKeyType::Bool)
	{
		const FString& Symbol			= EBasicKeyOperation::ToSymbol(BasicOperation);
		bool Value						= Blackboard->GetValue<UBlackboardKeyType_Bool>(Key.GetSelectedKeyID());
		const FString ValueAsString		= Value ? TEXT("true") : TEXT("false");
		const FString DestValueAsTring	= EBasicKeyOperation::Set ? TEXT("true") : TEXT("false");
		Description = TEXT("Key: ") + Key.SelectedKeyName.ToString() + TEXT("Value: ") + ValueAsString + TEXT(" ") + Symbol + TEXT(" ") + DestValueAsTring + TEXT(" is ") + Result;
	}
	return Description;
}

#pragma endregion FCsBTTaskKeyValue