// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/FX/CsTypes_FX.h"
#pragma once

class ICsTraceWeapon;
class UObject;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsTrace::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NData, IData)
// NCsFX::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, IPayload)
// NCsWeapon::NTrace::NData::NVisual::NFire::IFire
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NTrace, NData, NVisual, NFire, IFire)
// NCsTrace::NData::NVisual::NTracer::ITracer
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsTrace, NData, NVisual, NTracer, ITracer)

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NImpl
		{
			namespace NFX
			{
				/**
				* Basic implementation for any FX related Data used by an object
				* implementing the interface: ICsTraceWeapon
				*/
				struct CSWP_API FImpl
				{
					friend class ICsTraceWeapon;

				#define DataType NCsWeapon::NData::IData
				#define TraceDataType NCsTrace::NData::IData
				#define FXPayloadType NCsFX::NPayload::IPayload
				#define FireVisualDataType NCsWeapon::NTrace::NData::NVisual::NFire::IFire
				#define TracerVisualDataType NCsTrace::NData::NVisual::NTracer::ITracer

				protected:

					/** UObject reference to an object implementing the interface: ICsTraceWeapon. */
					UObject* Outer;

					/** Interface reference to Outer. */
					ICsTraceWeapon* Interface;

					/** Reference to the owner of Outer. */
					UObject* Owner;

					/** Reference used for anything using component specific logic. */
					USceneComponent* Component;

				public:

					FImpl() :
						Outer(nullptr),
						Interface(nullptr),
						Owner(nullptr),
						Component(nullptr)
					{
					}

					void SetOuter(UObject* InOuter);
					
					FORCEINLINE UObject* GetOuter() const { return Outer; }

					FORCEINLINE void SetOwner(UObject* InOwner) { Owner = InOwner; }
					FORCEINLINE UObject* GetOwner() const { return Owner; }

					FORCEINLINE void SetComponent(USceneComponent* InComponent) { Component = InComponent; }

				public:

					/**
					* Try to apply any Fire Visual Data.
					*
					* @param Data 
					*/
					void TryFire(DataType* Data);

					/**
					* Try to apply any Tracer Visual Data.
					* 
					* @param Data
					* @param End	The end location used by the tracer.
					*/
					void TryTracer(TraceDataType* Data, const FVector3f& End);

					/**
					* Try to apply any Trace Impact Visual Data.
					*
					* @param Data
					* @param Hit	Hit information from trace.
					*/
					void TryImpact(TraceDataType* Data, const FHitResult& Hit);

				#undef DataType
				#undef TraceDataType
				#undef FXPayloadType
				#undef FireVisualDataType
				#undef TracerVisualDataType
				};
			}
		}
	}
}