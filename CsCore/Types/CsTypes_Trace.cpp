// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Trace.h"

// TraceType
CS_DEFINE_ENUM_MAP_BODY(EMCsTraceType)

namespace NCsTraceType
{
	namespace Ref
	{
		CSCORE_API const Type Line = EMCsTraceType::Get().Add(Type::Line, TEXT("Line"));
		CSCORE_API const Type Sweep = EMCsTraceType::Get().Add(Type::Sweep, TEXT("Sweep"));
		CSCORE_API const Type Overlap = EMCsTraceType::Get().Add(Type::Overlap, TEXT("Overlap"));
		CSCORE_API const Type ECsTraceType_MAX = EMCsTraceType::Get().Add(Type::ECsTraceType_MAX, TEXT("ECsTraceType_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsTraceType_MAX;
}

// TraceMethod
CS_DEFINE_ENUM_MAP_BODY(EMCsTraceMethod)

namespace NCsTraceMethod
{
	namespace Ref
	{
		CSCORE_API const Type Test = EMCsTraceMethod::Get().Add(Type::Test, TEXT("Test"));
		CSCORE_API const Type Single = EMCsTraceMethod::Get().Add(Type::Single, TEXT("Single"));
		CSCORE_API const Type Multi = EMCsTraceMethod::Get().Add(Type::Multi, TEXT("Multi"));
		CSCORE_API const Type ECsTraceMethod_MAX = EMCsTraceMethod::Get().Add(Type::ECsTraceMethod_MAX, TEXT("ECsTraceMethod_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsTraceMethod_MAX;
}

// TraceQuery
CS_DEFINE_ENUM_MAP_BODY(EMCsTraceQuery)

namespace NCsTraceQuery
{
	namespace Ref
	{
		CSCORE_API const Type Channel = EMCsTraceQuery::Get().Add(Type::Channel, TEXT("Channel"));
		CSCORE_API const Type ObjectType = EMCsTraceQuery::Get().Add(Type::ObjectType, TEXT("ObjectType"));
		CSCORE_API const Type Profile = EMCsTraceQuery::Get().Add(Type::Profile, TEXT("Profile"));
		CSCORE_API const Type ECsTraceQuery_MAX = EMCsTraceQuery::Get().Add(Type::ECsTraceQuery_MAX, TEXT("ECsTraceQuery_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsTraceQuery_MAX;
}