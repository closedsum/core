// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/CsBlockchainCommand.h"

EMCsBlockchainCommand* EMCsBlockchainCommand::Instance;

EMCsBlockchainCommand& EMCsBlockchainCommand::Get()
{
	if (!Instance)
		Instance = new EMCsBlockchainCommand();
	return *Instance;
}

namespace ECsBlockchainCommandArgumentType
{
	namespace Str
	{
		CSCORE_API const TCsString Int32 = TCsString(TEXT("Int32"), TEXT("int32"));
		CSCORE_API const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
		CSCORE_API const TCsString String = TCsString(TEXT("String"), TEXT("string"));
		CSCORE_API const TCsString StringString = TCsString(TEXT("StringString"), TEXT("stringstring"));
	}

	namespace Ref
	{
		CSCORE_API const Type Int32 = Type::Int32;
		CSCORE_API const Type Float = Type::Float;
		CSCORE_API const Type String = Type::String;
		CSCORE_API const Type StringString = Type::StringString;
		CSCORE_API const Type ECsBlockchainCommandArgumentType_MAX = Type::ECsBlockchainCommandArgumentType_MAX;
	}
}