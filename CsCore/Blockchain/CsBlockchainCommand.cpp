// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/CsBlockchainCommand.h"

EMCsBlockchainCommand* EMCsBlockchainCommand::Instance;

EMCsBlockchainCommand& EMCsBlockchainCommand::Get()
{
	if (!Instance)
		Instance = new EMCsBlockchainCommand();
	return *Instance;
}

// BlockchainCommandArgumentType
EMCsBlockchainCommandArgumentType* EMCsBlockchainCommandArgumentType::Instance;

EMCsBlockchainCommandArgumentType& EMCsBlockchainCommandArgumentType::Get()
{
	if (!Instance)
		Instance = new EMCsBlockchainCommandArgumentType();
	return *Instance;
}

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