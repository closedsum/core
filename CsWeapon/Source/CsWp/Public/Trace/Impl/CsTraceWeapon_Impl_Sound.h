// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Sound/CsTypes_Sound.h"
#pragma once

class ICsTraceWeapon;
class UObject;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsTrace::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NData, IData)
// NCsSound::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSound, NPayload, IPayload)

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NImpl
		{
			namespace NSound
			{
				/**
				* Basic implementation for any Sound related Data used by an object
				* implementing the interface: ICsTraceWeapon
				*/
				struct CSWP_API FImpl
				{
					friend class ICsTraceWeapon;

				#define DataType NCsWeapon::NData::IData
				#define TraceDataType NCsTrace::NData::IData
				#define SoundPayloadType NCsSound::NPayload::IPayload

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
					* Try to apply any Fire Sound Data.
					*
					* @param Data 
					*/
					void TryFire(DataType* Data);

					/**
					* Try to apply any Trace Impact Sound Data.
					*
					* @param Data
					* @param Hit	Hit information from the trace.
					*/
					void TryImpact(TraceDataType* Data, const FHitResult& Hit);

					/**
					*
					*
					* @param Payload
					* @param Sound
					*/
					void SetPayload(SoundPayloadType* Payload, const FCsSound& Sound);

				#undef DataType
				#undef TraceDataType
				#undef SoundPayloadType
				};
			}
		}
	}
}