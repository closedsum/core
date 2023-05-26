// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Sound/CsTypes_Sound.h"
#pragma once

class ICsBeamWeapon;
class UObject;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsBeam::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NData, IData)
// NCsSound::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSound, NPayload, IPayload)

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NImpl
		{
			namespace NSound
			{
				/**
				* Basic implementation for any Sound related Data used by an object
				* implementing the interface: ICsBeamWeapon
				*/
				struct CSWP_API FImpl
				{
					friend class ICsBeamWeapon;

				#define DataType NCsWeapon::NData::IData
				#define BeamDataType NCsBeam::NData::IData
				#define SoundPayloadType NCsSound::NPayload::IPayload

				protected:

					/** UObject reference to an object implementing the interface: ICsBeamWeapon. */
					UObject* Outer;

					/** Interface reference to Outer. */
					ICsBeamWeapon* Interface;

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
					* Try to apply any Beam Impact Sound Data.
					*
					* @param Data
					* @param Hit	Hit information from the trace.
					*/
					void TryImpact(BeamDataType* Data, const FHitResult& Hit);

				#undef DataType
				#undef BeamDataType
				#undef SoundPayloadType
				};
			}
		}
	}
}