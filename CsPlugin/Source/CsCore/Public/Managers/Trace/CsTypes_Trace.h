// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"
#include "Types/Property/Multi/CsProperty_Multi_FString_Enum_ThreeParams.h"

#include "CsTypes_Trace.generated.h"
#pragma once

// TraceType
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsTraceType : uint8
{
	Line				UMETA(DisplayName = "Line"),
	Sweep				UMETA(DisplayName = "Sweep"),
	Overlap				UMETA(DisplayName = "Overlap"),
	OverlapBlocking		UMETA(DisplayName = "Overlap Blocking"),
	ECsTraceType_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsTraceType : public TCsEnumMap<ECsTraceType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceType, ECsTraceType)
};

namespace NCsTraceType
{
	typedef ECsTraceType Type;

	namespace Ref
	{
		extern CSCORE_API const Type Line;
		extern CSCORE_API const Type Sweep;
		extern CSCORE_API const Type Overlap;
		extern CSCORE_API const Type OverlapBlocking;
		extern CSCORE_API const Type ECsTraceType_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#define ECS_TRACE_TYPE_MAX NCsTraceType::MAX

#pragma endregion TraceType

// TraceMethod
#pragma region TraceMethod

/**
*/
UENUM(BlueprintType)
enum class ECsTraceMethod : uint8
{
	Test				UMETA(DisplayName = "Test"),
	Single				UMETA(DisplayName = "Single"),
	Multi				UMETA(DisplayName = "Multi"),
	ECsTraceMethod_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsTraceMethod : public TCsEnumMap<ECsTraceMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceMethod, ECsTraceMethod)
};

namespace NCsTraceMethod
{
	typedef ECsTraceMethod Type;

	namespace Ref
	{
		extern CSCORE_API const Type Test;
		extern CSCORE_API const Type Single;
		extern CSCORE_API const Type Multi;
		extern CSCORE_API const Type ECsTraceMethod_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#define ECS_TRACE_METHOD_MAX NCsTraceMethod::MAX

#pragma endregion TraceMethod

// TraceQuery
#pragma region

UENUM(BlueprintType)
enum class ECsTraceQuery : uint8
{
	Channel				UMETA(DisplayName = "Channel"),
	ObjectType			UMETA(DisplayName = "ObjectType"),
	Profile				UMETA(DisplayName = "Profile"),
	ECsTraceQuery_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsTraceQuery : public TCsEnumMap<ECsTraceQuery>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceQuery, ECsTraceQuery)
};

namespace NCsTraceQuery
{
	typedef ECsTraceQuery Type;

	namespace Ref
	{
		extern CSCORE_API const Type Channel;
		extern CSCORE_API const Type ObjectType;
		extern CSCORE_API const Type Profile;
		extern CSCORE_API const Type ECsTraceQuery_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#define ECS_TRACE_QUERY_MAX NCsTraceQuery::MAX

#pragma endregion TraceQuery

// TraceTransaction
#pragma region

UENUM(BlueprintType)
enum class ECsTraceTransaction : uint8
{
	Receive					UMETA(DisplayName = "Receive"),
	Discard					UMETA(DisplayName = "Discard"),
	Add						UMETA(DisplayName = "Add"),
	Process					UMETA(DisplayName = "Process"),
	Complete				UMETA(DisplayName = "Complete"),
	ECsTraceTransaction_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsTraceTransaction : public TCsEnumMap<ECsTraceTransaction>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceTransaction, ECsTraceTransaction)
};

namespace NCsTraceTransaction
{
	typedef ECsTraceTransaction Type;

	namespace Ref
	{
		extern CSCORE_API const Type Receive;
		extern CSCORE_API const Type Discard;
		extern CSCORE_API const Type Add;
		extern CSCORE_API const Type Process;
		extern CSCORE_API const Type Complete;
		extern CSCORE_API const Type ECsTraceTransaction_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		extern CSCORE_API const TCsString Receive;
		extern CSCORE_API const TCsString Discard;
		extern CSCORE_API const TCsString Add;
		extern CSCORE_API const TCsString Process;
		extern CSCORE_API const TCsString Complete;
	}

	FORCEINLINE const FString& ToActionString(const Type &EType)
	{
		if (EType == Type::Receive) { return Str::Receive.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Discard) { return Str::Discard.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Add) { return Str::Add.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Process) { return Str::Process.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Complete) { return Str::Complete.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		return CS_INVALID_ENUM_TO_STRING;
	}
}

#define ECS_TRACE_TRANSACTION_MAX NCsTraceTransaction::MAX

#pragma endregion TraceTransaction