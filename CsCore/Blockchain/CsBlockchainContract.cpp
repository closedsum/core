// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/CsBlockchainContract.h"

// BlockchainContract
CS_DEFINE_ENUM_MAP_BODY(EMCsBlockchainContract)

ICsBlockchainContract::ICsBlockchainContract(){}
ICsBlockchainContract::ICsBlockchainContract(const FString &InName){}
ICsBlockchainContract::~ICsBlockchainContract(){}

// Argument
#pragma region

	// BlockchainContractArgumentType
CS_DEFINE_ENUM_MAP_BODY(EMCsBlockchainContractArgumentType)

namespace NCsBlockchainContractArgumentType
{
	namespace Ref
	{
		CSCORE_API const Type Bool = EMCsBlockchainContractArgumentType::Get().Add(Type::Bool, TEXT("Bool"));
		CSCORE_API const Type Int32 = EMCsBlockchainContractArgumentType::Get().Add(Type::Int32, TEXT("Int32"));
		CSCORE_API const Type Float = EMCsBlockchainContractArgumentType::Get().Add(Type::Float, TEXT("Float"));
		CSCORE_API const Type String = EMCsBlockchainContractArgumentType::Get().Add(Type::String, TEXT("String"));
		CSCORE_API const Type StringString = EMCsBlockchainContractArgumentType::Get().Add(Type::StringString, TEXT("StringString"));
		CSCORE_API const Type ECsBlockchainContractArgumentType_MAX = EMCsBlockchainContractArgumentType::Get().Add(Type::ECsBlockchainContractArgumentType_MAX, TEXT("ECsBlockchainContractArgumentType_MAX"), TEXT("MAX"));
	}
}

#pragma endregion Argument

// Function
#pragma region

	// BlockchainContractFunction
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsBlockchainContractFunction)

	// BlockchainContractFunctionArgumentType
CS_DEFINE_ENUM_MAP_BODY(EMCsBlockchainContractFunctionArgumentType)

namespace NCsBlockchainContractFunctionArgumentType
{
	namespace Ref
	{
		CSCORE_API const Type Int32 = EMCsBlockchainContractFunctionArgumentType::Get().Add(Type::Int32, TEXT("Int32"));
		CSCORE_API const Type Float = EMCsBlockchainContractFunctionArgumentType::Get().Add(Type::Float, TEXT("Float"));
		CSCORE_API const Type String = EMCsBlockchainContractFunctionArgumentType::Get().Add(Type::String, TEXT("String"));
		CSCORE_API const Type ECsBlockchainContractFunctionArgumentType_MAX = EMCsBlockchainContractFunctionArgumentType::Get().Add(Type::ECsBlockchainContractFunctionArgumentType_MAX, TEXT("ECsBlockchainContractFunctionArgumentType_MAX"), TEXT("MAX"));
	}
}

	// BlockchainContractFunctionReturnType
CS_DEFINE_ENUM_MAP_BODY(EMCsBlockchainContractFunctionReturnType)

namespace NCsBlockchainContractFunctionReturnType
{
	namespace Ref
	{
		CSCORE_API const Type Int32 = EMCsBlockchainContractFunctionReturnType::Get().Add(Type::Int32, TEXT("Int32"));
		CSCORE_API const Type Float = EMCsBlockchainContractFunctionReturnType::Get().Add(Type::Float, TEXT("Float"));
		CSCORE_API const Type String = EMCsBlockchainContractFunctionReturnType::Get().Add(Type::String, TEXT("String"));
		CSCORE_API const Type ECsBlockchainContractFunctionReturnType_MAX = EMCsBlockchainContractFunctionReturnType::Get().Add(Type::ECsBlockchainContractFunctionReturnType_MAX, TEXT("ECsBlockchainContractFunctionReturnType_MAX"), TEXT("MAX"));
	}
}
#pragma endregion Function