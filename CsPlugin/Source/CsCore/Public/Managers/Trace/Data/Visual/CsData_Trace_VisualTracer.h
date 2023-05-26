// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/FX/CsTypes_FX.h"

#include "CsData_Trace_VisualTracer.generated.h"

namespace NCsTrace
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NTracer
			{
				// Attach
				#pragma region

				/**
				* Describes how the tracer visual will attach to the object performing the trace.
				* NOTE: EAttach takes precedence over ETransform. 
				*/
				enum class EAttach : uint8
				{
					None,
					Owner,
					Component,
					Custom,
					EAttach_MAX
				};

				#pragma endregion Attach

				// Transform
				#pragma region

				/**
				* Describes how the transform of the tracer visual will be set by the object performing the trace.
				* NOTE: EAttach takes precedence over ETransform 
				*/
				enum class ETransform : uint8
				{
					None,
					Owner,
					Component,
					Custom,
					ETransform_MAX
				};

				#pragma endregion Transform

				/**
				* Interface that describes anything visual related to a Tracer for a Trace. 				 
				*/
				struct CSCORE_API ITracer : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~ITracer() {}

					/**
					* Get the FX related information for the tracer.
					*
					* return FX
					*/
					virtual const FCsFX& GetTracerFX() const = 0;

					/**
					* Get how the tracer will attach to the object performing the trace.
					* NOTE: Attach Type (NCsTrace::NData::NVisual::NTracer::EAttach) takes 
					*	    precedence over Transform Type (NCsTrace::NData::NVisual::NTracer::ETransform).
					* 
					* return Attach Type
					*/
					virtual const EAttach& GetTracerAttachType() const = 0;

					/**
					* Get how the transform of the tracer will be set by the object perform the trace.
					* NOTE: Attach Type (NCsTrace::NData::NVisual::NTracer::EAttach) takes
					*	    precedence over Transform Type (NCsTrace::NData::NVisual::NTracer::ETransform).
					*
					* return Transform Type
					*/
					virtual const ETransform& GetTracerTransformType() const = 0;

					/**
					* Get the Niagara Parameter name for the end point of the fx.
					*
					* return Name 
					*/
					virtual const FName& GetTracerEndParameterName() const = 0;
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_Trace_VisualTracer: public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface that describes anything visual related to a Tracer for a Trace.
*/
class CSCORE_API ICsData_Trace_VisualTracer : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define AttachType NCsTrace::NData::NVisual::NTracer::EAttach
#define TransformType NCsTrace::NData::NVisual::NTracer::ETransform

public:

	/**
	* Get the FX related information for the tracer.
	*
	* return FX
	*/
	virtual const FCsFX& GetTracerFX() const = 0;

	/**
	* Get how the tracer will attach to the object performing the trace.
	* NOTE: Attach Type (NCsTrace::NData::NVisual::NTracer::EAttach) takes
	*	    precedence over Transform Type (NCsTrace::NData::NVisual::NTracer::ETransform).
	*
	* return Attach Type
	*/
	virtual const AttachType& GetTracerAttachType() const = 0;
	
	/**
	* Get how the transform of the tracer will be set by the object perform the trace.
	* NOTE: Attach Type (NCsTrace::NData::NVisual::NTracer::EAttach) takes
	*	    precedence over Transform Type (NCsTrace::NData::NVisual::NTracer::ETransform).
	*
	* return Transform Type
	*/
	virtual const TransformType& GetTracerTransformType() const = 0;

	/**
	* Get the Niagara Parameter name for the end point of the fx.
	*
	* return Name 
	*/
	virtual const FName& GetTracerEndParameterName() const = 0;

#undef AttachType
#undef TransformType
};