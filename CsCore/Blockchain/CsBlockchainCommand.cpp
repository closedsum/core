// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/CsBlockchainCommand.h"

// BlockchainCommand
CS_DEFINE_ENUM_MAP_BODY(EMCsBlockchainCommand)

// BlockchainCommandArgumentType
CS_DEFINE_ENUM_MAP_BODY(EMCsBlockchainCommandArgumentType)

namespace NCsBlockchainCommandArgumentType
{
	namespace Ref
	{
		CSCORE_API const Type Int32 = EMCsBlockchainCommandArgumentType::Get().Add(Type::Int32, TEXT("Int32"));
		CSCORE_API const Type Float = EMCsBlockchainCommandArgumentType::Get().Add(Type::Float, TEXT("Float"));
		CSCORE_API const Type String = EMCsBlockchainCommandArgumentType::Get().Add(Type::String, TEXT("String"));
		CSCORE_API const Type StringString = EMCsBlockchainCommandArgumentType::Get().Add(Type::StringString, TEXT("StringString"));
		CSCORE_API const Type ECsBlockchainCommandArgumentType_MAX = EMCsBlockchainCommandArgumentType::Get().Add(Type::ECsBlockchainCommandArgumentType_MAX, TEXT("ECsBlockchainCommandArgumentType_MAX"), TEXT("MAX"));
	}
}