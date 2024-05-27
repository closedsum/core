// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnumMap.h"
#include "Multi/CsProperty_Multi_FString_Enum_ThreeParams.h"

#include "CsTypes_Trace.generated.h"

// TraceType
#pragma region

/**
* Describes what type of Trace to perform.
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

struct CSPHYSICS_API EMCsTraceType : public TCsEnumMap<ECsTraceType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceType, ECsTraceType)
};

namespace NCsTraceType
{
	typedef ECsTraceType Type;

	namespace Ref
	{
		extern CSPHYSICS_API const Type Line;
		extern CSPHYSICS_API const Type Sweep;
		extern CSPHYSICS_API const Type Overlap;
		extern CSPHYSICS_API const Type OverlapBlocking;
		extern CSPHYSICS_API const Type ECsTraceType_MAX;
	}

	extern CSPHYSICS_API const uint8 MAX;
}

#define ECS_TRACE_TYPE_MAX NCsTraceType::MAX

#pragma endregion TraceType

// TraceMethod
#pragma region TraceMethod

/**
* Describes how (number) the Trace is performed.
*/
UENUM(BlueprintType)
enum class ECsTraceMethod : uint8
{
	Test				UMETA(DisplayName = "Test"),
	Single				UMETA(DisplayName = "Single"),
	Multi				UMETA(DisplayName = "Multi"),
	ECsTraceMethod_MAX	UMETA(Hidden),
};

struct CSPHYSICS_API EMCsTraceMethod : public TCsEnumMap<ECsTraceMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceMethod, ECsTraceMethod)
};

namespace NCsTraceMethod
{
	typedef ECsTraceMethod Type;

	namespace Ref
	{
		extern CSPHYSICS_API const Type Test;
		extern CSPHYSICS_API const Type Single;
		extern CSPHYSICS_API const Type Multi;
		extern CSPHYSICS_API const Type ECsTraceMethod_MAX;
	}

	extern CSPHYSICS_API const uint8 MAX;
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

struct CSPHYSICS_API EMCsTraceQuery : public TCsEnumMap<ECsTraceQuery>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceQuery, ECsTraceQuery)
};

namespace NCsTraceQuery
{
	typedef ECsTraceQuery Type;

	namespace Ref
	{
		extern CSPHYSICS_API const Type Channel;
		extern CSPHYSICS_API const Type ObjectType;
		extern CSPHYSICS_API const Type Profile;
		extern CSPHYSICS_API const Type ECsTraceQuery_MAX;
	}

	extern CSPHYSICS_API const uint8 MAX;
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

struct CSPHYSICS_API EMCsTraceTransaction : public TCsEnumMap<ECsTraceTransaction>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceTransaction, ECsTraceTransaction)
};

namespace NCsTraceTransaction
{
	typedef ECsTraceTransaction Type;

	namespace Ref
	{
		extern CSPHYSICS_API const Type Receive;
		extern CSPHYSICS_API const Type Discard;
		extern CSPHYSICS_API const Type Add;
		extern CSPHYSICS_API const Type Process;
		extern CSPHYSICS_API const Type Complete;
		extern CSPHYSICS_API const Type ECsTraceTransaction_MAX;
	}

	extern CSPHYSICS_API const uint8 MAX;

	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		extern CSPHYSICS_API const TCsString Receive;
		extern CSPHYSICS_API const TCsString Discard;
		extern CSPHYSICS_API const TCsString Add;
		extern CSPHYSICS_API const TCsString Process;
		extern CSPHYSICS_API const TCsString Complete;
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

// FCsTraceCollisionBox
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSPHYSICS_API FCsTraceCollisionBox
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float HalfExtentX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float HalfExtentY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float HalfExtentZ;

	FCsTraceCollisionBox() :
		HalfExtentX(0.0f),
		HalfExtentY(0.0f),
		HalfExtentZ(0.0f)
	{
	}
};

#pragma endregion FCsTraceCollisionBox

// FCsTraceCollisionSphere
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSPHYSICS_API FCsTraceCollisionSphere
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Radius;

	FCsTraceCollisionSphere() :
		Radius(0.0f)
	{
	}
};

#pragma endregion FCsTraceCollisionSphere

// FCsTraceCollisionCapsule
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSPHYSICS_API FCsTraceCollisionCapsule
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Trace", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float HalfHeight;

	FCsTraceCollisionCapsule() :
		Radius(0.0f),
		HalfHeight(0.0f)
	{
	}
};

#pragma endregion FCsTraceCollisionCapsule

// TraceBoneSpace
#pragma region

/**
* Describes what "Space" to use for tracing from a Bone (Location)
*/
UENUM(BlueprintType)
enum class ECsTraceBoneSpace : uint8
{
	Bone					UMETA(DisplayName = "Bone"),
	Component				UMETA(DisplayName = "Component"),
	ECsTraceBoneSpace_MAX	UMETA(Hidden),
};

struct CSPHYSICS_API EMCsTraceBoneSpace : public TCsEnumMap<ECsTraceBoneSpace>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceBoneSpace, ECsTraceBoneSpace)
};

namespace NCsTraceBoneSpace
{
	typedef ECsTraceBoneSpace Type;

	namespace Ref
	{
		extern CSPHYSICS_API const Type Bone;
		extern CSPHYSICS_API const Type Component;
		extern CSPHYSICS_API const Type ECsTraceBoneSpace_MAX;
	}
}

namespace NCsTrace
{
	namespace NBone
	{
		enum class ESpace : uint8
		{
			Bone,
			Component,
			ESpace_MAX
		};

		struct CSPHYSICS_API EMSpace : public TCsEnumMap<ESpace>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMSpace, ESpace)
		};

		namespace NSpace
		{
			typedef ESpace Type;

			namespace Ref
			{
				extern CSPHYSICS_API const Type Bone;
				extern CSPHYSICS_API const Type Component;
				extern CSPHYSICS_API const Type ESpace_MAX;
			}
		}
	}
}

#pragma endregion TraceBoneSpace