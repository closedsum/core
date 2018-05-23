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