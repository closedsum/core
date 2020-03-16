// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/BehaviorTree/CsTypes_BehaviorTree.h"
#include "CsCoreDEPRECATED.h"

#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

// BlackboardKeyType
#pragma region

namespace NCsBlackboardKeyType
{
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsBlackboardKeyType, Bool);
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsBlackboardKeyType, Enum);
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsBlackboardKeyType, Int);
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsBlackboardKeyType, Float);
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsBlackboardKeyType, Name);
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsBlackboardKeyType, String);
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsBlackboardKeyType, Vector);
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsBlackboardKeyType, Rotator);
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsBlackboardKeyType, Object);
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsBlackboardKeyType, Class);
}

/*static*/ const FECsBlackboardKeyType& FCsBlackboardKeyTypeHelper::GetType(const FBlackboardKeySelector &Key)
{
	// Bool
	if (Key.SelectedKeyType == UBlackboardKeyType_Bool::StaticClass())
		return NCsBlackboardKeyType::Bool;
	// Enum
	if (Key.SelectedKeyType == UBlackboardKeyType_Enum::StaticClass())
		return NCsBlackboardKeyType::Enum;
	// Int
	if (Key.SelectedKeyType == UBlackboardKeyType_Int::StaticClass())
		return NCsBlackboardKeyType::Int;
	// Float
	if (Key.SelectedKeyType == UBlackboardKeyType_Float::StaticClass())
		return NCsBlackboardKeyType::Float;
	// Name
	if (Key.SelectedKeyType == UBlackboardKeyType_Name::StaticClass())
		return NCsBlackboardKeyType::Name;
	// String
	if (Key.SelectedKeyType == UBlackboardKeyType_String::StaticClass())
		return NCsBlackboardKeyType::String;
	// Vector
	if (Key.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		return NCsBlackboardKeyType::Vector;
	// Rotator
	if (Key.SelectedKeyType == UBlackboardKeyType_Rotator::StaticClass())
		return NCsBlackboardKeyType::Rotator;
	// Object
	if (Key.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
		return NCsBlackboardKeyType::Object;
	// Class
	if (Key.SelectedKeyType == UBlackboardKeyType_Class::StaticClass())
		return NCsBlackboardKeyType::Class;
	return EMCsBlackboardKeyType::Get().GetMAX();
}

#pragma endregion BlackboardKeyType

// BTTask_LogicalOperator
#pragma region

namespace NCsBTTask_LogicalOperator
{
	namespace Ref
	{
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP(EMCsBTTask_LogicalOperator, And);
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP(EMCsBTTask_LogicalOperator, Or);
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsBTTask_LogicalOperator, ECsBTTask_LogicalOperator_MAX, "MAX");
	}

	namespace Sym
	{
		CSCOREDEPRECATED_API const FString And = TEXT("&");
		CSCOREDEPRECATED_API const FString Or = TEXT("|");
	}
}

#pragma endregion BTTask_LogicalOperator

// BTTask_BasicSetOperation
#pragma region

namespace NCsBTTask_BasicSetOperation
{
	namespace Ref
	{
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP(EMCsBTTask_BasicSetOperation, Set);
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP(EMCsBTTask_BasicSetOperation, Clear);
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsBTTask_BasicSetOperation, ECsBTTask_BasicSetOperation_MAX, "MAX");
	}
}

#pragma endregion BTTask_BasicSetOperation

// BasicKeyOperation
#pragma region

namespace EBasicKeyOperation
{
	namespace Sym
	{
		CSCOREDEPRECATED_API const FString Set = TEXT("true");
		CSCOREDEPRECATED_API const FString NotSet = TEXT("false");
	}
}

#pragma endregion BasicKeyOperation

// ArithmeticKeyOperation
#pragma region

namespace EArithmeticKeyOperation
{
	namespace Sym
	{
		CSCOREDEPRECATED_API const FString Equal = TEXT("=");
		CSCOREDEPRECATED_API const FString NotEqual = TEXT("!=");
		CSCOREDEPRECATED_API const FString Less =TEXT("<");
		CSCOREDEPRECATED_API const FString LessOrEqual = TEXT("<=");
		CSCOREDEPRECATED_API const FString Greater = TEXT(">");
		CSCOREDEPRECATED_API const FString GreaterOrEqual = TEXT(">=");
	}
}

#pragma endregion ArithmeticKeyOperation

// TextKeyOperation
#pragma region

namespace ETextKeyOperation
{
	namespace Sym
	{
		CSCOREDEPRECATED_API const FString Equal = TEXT("=");
		CSCOREDEPRECATED_API const FString NotEqual = TEXT("!=");
		CSCOREDEPRECATED_API const FString Contain = TEXT("contains");
		CSCOREDEPRECATED_API const FString NotContain = TEXT("not contains");
	}
}

#pragma endregion TextKeyOperation

// FCsBTTaskKeyValue
#pragma region

void FCsBTTask_KeyValue_Compare::Init(const FString& FunctionName)
{
	if (Type != EMCsBlackboardKeyType::Get().GetMAX())
		return;

	Type = FCsBlackboardKeyTypeHelper::GetType(Key);

	// Currently Enum, Object, and Class Types are NOT Supported
	if (Type == NCsBlackboardKeyType::Enum ||
		Type == NCsBlackboardKeyType::Object ||
		Type == NCsBlackboardKeyType::Class)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s: Blackboard Key of Types: Enum, Object, and Class are NOT supported."), *FunctionName);
	}
}

bool FCsBTTask_KeyValue_Compare::IsValid()
{
	return Type != NCsBlackboardKeyType::Enum && Type != NCsBlackboardKeyType::Object && Type != NCsBlackboardKeyType::Class;
}

bool FCsBTTask_KeyValue_Compare::Evaluate(const UBlackboardComponent* Blackboard)
{
	Last_Evaluation = Evaluate_Internal(Blackboard);
	return Last_Evaluation;
}

bool FCsBTTask_KeyValue_Compare::Evaluate_Internal(const UBlackboardComponent* Blackboard)
{
	// Bool
	if (Type == NCsBlackboardKeyType::Bool)
	{
		const bool Result = Blackboard->GetValue<UBlackboardKeyType_Bool>(Key.GetSelectedKeyID());

		if (BasicOperation == EBasicKeyOperation::Set)
			return Result;
		if (BasicOperation == EBasicKeyOperation::NotSet)
			return !Result;
		return false;
	}
	// Int
	if (Type == NCsBlackboardKeyType::Int)
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
	if (Type == NCsBlackboardKeyType::Float)
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
	if (Type == NCsBlackboardKeyType::Name)
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
	if (Type == NCsBlackboardKeyType::String)
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
	if (Type == NCsBlackboardKeyType::Vector)
	{
		const bool Result = Value_Vector == Blackboard->GetValue<UBlackboardKeyType_Vector>(Key.GetSelectedKeyID());

		if (BasicOperation == EBasicKeyOperation::Set)
			return Result;
		if (BasicOperation == EBasicKeyOperation::NotSet)
			return !Result;
		return false;
	}
	// Rotator
	if (Type == NCsBlackboardKeyType::Rotator)
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

FString FCsBTTask_KeyValue_Compare::GetRuntimeDescription(const class UBlackboardComponent* Blackboard) const
{
	FString Description = NCsCached::Str::Empty;
	FString Result		= Last_Evaluation ? TEXT("True") : TEXT("False");
	
	const FString& Symbol	  = EBasicKeyOperation::ToSymbol(BasicOperation);
	FString ValueAsString	  = NCsCached::Str::Empty;
	FString DestValueAsString = NCsCached::Str::Empty;

	// Bool
	if (Type == NCsBlackboardKeyType::Bool)
	{

		bool Value			= Blackboard->GetValue<UBlackboardKeyType_Bool>(Key.GetSelectedKeyID());
		ValueAsString		= Value ? TEXT("true") : TEXT("false");
		DestValueAsString	= EBasicKeyOperation::Set ? TEXT("true") : TEXT("false");
		Description = Key.SelectedKeyName.ToString() + TEXT(" (") + ValueAsString + TEXT(") = ") + DestValueAsString + TEXT(" is ") + Result;
		return Description;
	}
	// Enum
	if (Type == NCsBlackboardKeyType::Enum)
	{
	}
	// Int
	else
	if (Type == NCsBlackboardKeyType::Int)
	{
		int32 Value			= Blackboard->GetValue<UBlackboardKeyType_Int>(Key.GetSelectedKeyID());
		ValueAsString		= FString::FromInt(Value);
		DestValueAsString	= FString::FromInt(Value_Int);
	}
	// Float
	else
	if (Type == NCsBlackboardKeyType::Float)
	{
		float Value			= Blackboard->GetValue<UBlackboardKeyType_Float>(Key.GetSelectedKeyID());
		ValueAsString		= FString::SanitizeFloat(Value);
		DestValueAsString	= FString::SanitizeFloat(Value_Float);
	}
	// Name
	else
	if (Type == NCsBlackboardKeyType::Name)
	{
		FName Value			= Blackboard->GetValue<UBlackboardKeyType_Name>(Key.GetSelectedKeyID());
		ValueAsString		= Value.ToString();
		DestValueAsString	= Value_Name.ToString();
	}
	// String
	else
	if (Type == NCsBlackboardKeyType::String)
	{
		FString Value		= Blackboard->GetValue<UBlackboardKeyType_String>(Key.GetSelectedKeyID());
		ValueAsString		= Value;
		DestValueAsString	= Value_String;
	}
	// Vector
	else
	if (Type == NCsBlackboardKeyType::Vector)
	{
		FVector Value		= Blackboard->GetValue<UBlackboardKeyType_Vector>(Key.GetSelectedKeyID());
		ValueAsString		= Value.ToString();
		DestValueAsString	= Value_Vector.ToString();
	}
	// Rotator
	else
	if (Type == NCsBlackboardKeyType::Rotator)
	{
		FRotator Value		= Blackboard->GetValue<UBlackboardKeyType_Rotator>(Key.GetSelectedKeyID());
		ValueAsString		= Value.ToString();
		DestValueAsString	= Value_Vector.ToString();
	}
	/*
	// Object
	if (Key.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	return ECsBlackboardKeyType::Object;
	// Class
	if (Key.SelectedKeyType == UBlackboardKeyType_Class::StaticClass())
	return ECsBlackboardKeyType::Class;
	*/
	Description = Key.SelectedKeyName.ToString() + TEXT(" (") + ValueAsString + TEXT(" ") + Symbol + TEXT(" ") + DestValueAsString + TEXT(" is ") + Result;
	return Description;
}

FString FCsBTTask_KeyValue_Compare::GetStaticDescription() const
{
	FString Description = NCsCached::Str::Empty;

	const FECsBlackboardKeyType& KeyType = FCsBlackboardKeyTypeHelper::GetType(Key);
	FString DestValueAsString			 = NCsCached::Str::Empty;

	// Bool
	if (KeyType == NCsBlackboardKeyType::Bool)
		DestValueAsString = EBasicKeyOperation::Set ? TEXT("true") : TEXT("false");
	// Enum
	else
	if (KeyType == NCsBlackboardKeyType::Enum)
	{
	}
	// Int
	else
	if (KeyType == NCsBlackboardKeyType::Int)
		DestValueAsString = FString::FromInt(Value_Int);
	// Float
	else
	if (KeyType == NCsBlackboardKeyType::Float)
		DestValueAsString = FString::SanitizeFloat(Value_Float);
	// Name
	else
	if (KeyType == NCsBlackboardKeyType::Name)
		DestValueAsString = Value_Name.ToString();
	// String
	else
	if (KeyType == NCsBlackboardKeyType::String)
		DestValueAsString = Value_String;
	// Vector
	else
	if (KeyType == NCsBlackboardKeyType::Vector)
		DestValueAsString = Value_Vector.ToString();
	// Rotator
	else
	if (KeyType == NCsBlackboardKeyType::Rotator)
		DestValueAsString = Value_Rotator.ToString();
	Description = Key.SelectedKeyName.ToString() + TEXT(" is ") + DestValueAsString;
	return Description;
}

#pragma endregion FCsBTTaskKeyValue