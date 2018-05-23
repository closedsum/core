// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_String.h"

namespace ECsStringEscapeType
{
	namespace Str
	{
		const TCsString Int = TCsString(TEXT("Int"), TEXT("int"));
		const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
		const TCsString String = TCsString(TEXT("String"), TEXT("string"));
	}

	namespace Ref
	{
		const Type Int = Type::Int;
		const Type Float = Type::Float;
		const Type String = Type::String;
		const Type ECsStringEscapeType_MAX = Type::ECsStringEscapeType_MAX;
	}
}

namespace ECsStringEscapeCharacter
{
	const FString Int = TEXT("%d");
	const FString Float = TEXT("%f");
	const FString String = TEXT("%s");
	const FString CR = TEXT("\r");
	const FString LF = TEXT("\n");
	const FString EOL = TEXT("\r\n");
}

namespace ECsStringWordRule
{
	namespace Str
	{
		const TCsString MatchCase = TCsString(TEXT("MatchCase"), TEXT("matchcase"));
		const TCsString Lower = TCsString(TEXT("Lower"), TEXT("lower"));
	}

	namespace Ref
	{
		const Type MatchCase = Type::MatchCase;
		const Type Lower = Type::Lower;
		const Type ECsStringWordRule_MAX = Type::ECsStringWordRule_MAX;
	}
}