// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/CsBlockchainContract.h"

EMCsBlockchainContract* EMCsBlockchainContract::Instance;

EMCsBlockchainContract& EMCsBlockchainContract::Get()
{
	if (!Instance)
		Instance = new EMCsBlockchainContract();
	return *Instance;
}

EMCsBlockchainContractFunction* EMCsBlockchainContractFunction::Instance;

EMCsBlockchainContractFunction& EMCsBlockchainContractFunction::Get()
{
	if (!Instance)
		Instance = new EMCsBlockchainContractFunction();
	return *Instance;
}

ICsBlockchainContract::ICsBlockchainContract(){}
ICsBlockchainContract::ICsBlockchainContract(const FString &InName){}
ICsBlockchainContract::~ICsBlockchainContract(){}

// Argument
#pragma region

namespace ECsBlockchainContractArgumentType
{
	namespace Str
	{
		CSCORE_API const TCsString Bool = TCsString(TEXT("Bool"), TEXT("bool"));
		CSCORE_API const TCsString Int32 = TCsString(TEXT("Int32"), TEXT("int32"));
		CSCORE_API const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
		CSCORE_API const TCsString String = TCsString(TEXT("String"), TEXT("string"));
		CSCORE_API const TCsString StringString = TCsString(TEXT("StringString"), TEXT("stringstring"));
	}

	namespace Ref
	{
		CSCORE_API const Type Bool = Type::Bool;
		CSCORE_API const Type Int32 = Type::Int32;
		CSCORE_API const Type Float = Type::Float;
		CSCORE_API const Type String = Type::String;
		CSCORE_API const Type StringString = Type::StringString;
		CSCORE_API const Type ECsBlockchainContractArgumentType_MAX = Type::ECsBlockchainContractArgumentType_MAX;
	}
}

#pragma endregion Argument

// Function
#pragma region

namespace ECsBlockchainContractFunctionArgumentType
{
	namespace Str
	{
		CSCORE_API const TCsString Int32 = TCsString(TEXT("Int32"), TEXT("int32"));
		CSCORE_API const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
		CSCORE_API const TCsString String = TCsString(TEXT("String"), TEXT("string"));
	}

	namespace Ref
	{
		CSCORE_API const Type Int32 = Type::Int32;
		CSCORE_API const Type Float = Type::Float;
		CSCORE_API const Type String = Type::String;
		CSCORE_API const Type ECsBlockchainContractFunctionArgumentType_MAX = Type::ECsBlockchainContractFunctionArgumentType_MAX;
	}
}

namespace ECsBlockchainContractFunctionReturnType
{
	namespace Str
	{
		CSCORE_API const TCsString Int32 = TCsString(TEXT("Int32"), TEXT("int32"));
		CSCORE_API const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
		CSCORE_API const TCsString String = TCsString(TEXT("String"), TEXT("string"));
	}

	namespace Ref
	{
		CSCORE_API const Type Int32 = Type::Int32;
		CSCORE_API const Type Float = Type::Float;
		CSCORE_API const Type String = Type::String;
		CSCORE_API const Type ECsBlockchainContractFunctionReturnType_MAX = Type::ECsBlockchainContractFunctionReturnType_MAX;
	}
}
#pragma endregion Function