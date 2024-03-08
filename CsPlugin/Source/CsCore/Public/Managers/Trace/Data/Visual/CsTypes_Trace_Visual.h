// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnumMap.h"
#include "Managers/FX/CsTypes_FX.h"

#include "CsTypes_Trace_Visual.generated.h"

// TraceVisualAttach
#pragma region

/**
* Describes how the tracer visual will attach to the object performing the trace.
* NOTE: ECsTraceVisualAttach takes precedence over ECsTraceVisualTransform.
*/
UENUM(BlueprintType)
enum class ECsTraceVisualAttach : uint8
{
	None						UMETA(DisplayName = "None"),
	Owner						UMETA(DisplayName = "Owner"),
	Component					UMETA(DisplayName = "Component"),
	Custom						UMETA(DisplayName = "Custom"),
	ECsTraceVisualAttach_MAX	UMETA(Hidden),
};


struct CSCORE_API EMCsTraceVisualAttach : public TCsEnumMap<ECsTraceVisualAttach>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceVisualAttach, ECsTraceVisualAttach)
};

namespace NCsTraceVisualAttach
{
	typedef ECsTraceVisualAttach Type;

	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type Owner;
		extern CSCORE_API const Type Component;
		extern CSCORE_API const Type ECsTraceVisualAttach_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion TraceVisualAttach

// TraceVisualTransform
#pragma region

/**
* Describes how the transform of the tracer visual will be set by the object performing the trace.
* NOTE: EAttach takes precedence over ETransform
*/
UENUM(BlueprintType)
enum class ECsTraceVisualTransform : uint8
{
	None						UMETA(DisplayName = "None"),
	Owner						UMETA(DisplayName = "Owner"),
	Component					UMETA(DisplayName = "Component"),
	Custom						UMETA(DisplayName = "Custom"),
	ECsTraceVisualTransform_MAX	UMETA(Hidden),
};


struct CSCORE_API EMCsTraceVisualTransform : public TCsEnumMap<ECsTraceVisualTransform>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceVisualTransform, ECsTraceVisualTransform)
};

namespace NCsTraceVisualTransform
{
	typedef ECsTraceVisualTransform Type;

	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type Owner;
		extern CSCORE_API const Type Component;
		extern CSCORE_API const Type ECsTraceVisualTransform_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion TraceVisualTransform

// FCsTracerFX
#pragma region

// NCsTrace::NData::NVisual::NTracer::EAttach
CS_FWD_DECLARE_ENUM_CLASS_UINT8_NAMESPACE_4(NCsTrace, NData, NVisual, NTracer, EAttach)
// NCsTrace::NData::NVisual::NTracer::ETransform
CS_FWD_DECLARE_ENUM_CLASS_UINT8_NAMESPACE_4(NCsTrace, NData, NVisual, NTracer, ETransform)

/**
* Container holding general information for a Tracer FX.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsTracerFX
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Trace")
	FCsFX FX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Trace")
	ECsTraceVisualAttach Attach;

private:

#define AttachType NCsTrace::NData::NVisual::NTracer::EAttach

	AttachType* Attach_Internal;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Trace")
	ECsTraceVisualTransform Transform;

private:

#define TransformType NCsTrace::NData::NVisual::NTracer::ETransform

	TransformType* Transform_Internal;

public:

	/** the Niagara Parameter name for the end point of the fx. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Trace")
	FName EndParameter;

	FCsTracerFX() :
		FX(),
		Attach(ECsTraceVisualAttach::None),
		Attach_Internal(nullptr),
		Transform(ECsTraceVisualTransform::None),
		Transform_Internal(nullptr),
		EndParameter(NAME_None)
	{
		Attach_Internal = (AttachType*)(&Attach);
		Transform_Internal = (TransformType*)(&Transform);
	}

	FORCEINLINE void UpdateInternalPtrs()
	{
		UpdateAttachTypePtr();
		UpdateTransformTypePtr();
	}

	FORCEINLINE void UpdateAttachTypePtr() { Attach_Internal = (AttachType*)(&Attach); }
	FORCEINLINE void UpdateTransformTypePtr() { Transform_Internal = (TransformType*)(&Transform); }

	FORCEINLINE AttachType* GetAttachTypePtr() const { return Attach_Internal; }
	FORCEINLINE TransformType* GetTransformTypePtr() const { return Transform_Internal; }

#undef AttachType
#undef TransformType

private:

	FORCEINLINE void __Nothing() const {}
};

#pragma endregion FCsTracerFX