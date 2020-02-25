// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/CsBlockchainCommand.h"
#include "CsBlockchain.h"

// BlockchainCommandArgumentType
namespace NCsBlockchainCommandArgumentType
{
	namespace Ref
	{
		CSBLOCKCHAIN_API const Type Int32 = EMCsBlockchainCommandArgumentType::Get().Add(Type::Int32, TEXT("Int32"));
		CSBLOCKCHAIN_API const Type Float = EMCsBlockchainCommandArgumentType::Get().Add(Type::Float, TEXT("Float"));
		CSBLOCKCHAIN_API const Type String = EMCsBlockchainCommandArgumentType::Get().Add(Type::String, TEXT("String"));
		CSBLOCKCHAIN_API const Type StringString = EMCsBlockchainCommandArgumentType::Get().Add(Type::StringString, TEXT("StringString"));
		CSBLOCKCHAIN_API const Type ECsBlockchainCommandArgumentType_MAX = EMCsBlockchainCommandArgumentType::Get().Add(Type::ECsBlockchainCommandArgumentType_MAX, TEXT("ECsBlockchainCommandArgumentType_MAX"), TEXT("MAX"));
	}
}