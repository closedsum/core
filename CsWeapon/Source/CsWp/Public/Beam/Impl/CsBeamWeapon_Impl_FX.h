// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Engine/HitResult.h"
#include "Managers/FX/CsTypes_FX.h"

class ICsBeamWeapon;
class UObject;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsBeam::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NData, IData)
// NCsFX::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, IPayload)
// NCsWeapon::NBeam::NData::NVisual::NFire::IFire
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NBeam, NData, NVisual, NFire, IFire)

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NImpl
		{
			namespace NFX
			{
				/**
				* Basic implementation for any FX related Data used by an object
				* implementing the interface: ICsBeamWeapon
				*/
				struct CSWP_API FImpl
				{
					friend class ICsBeamWeapon;

				private:

					using DataType = NCsWeapon::NData::IData;
					using BeamDataType = NCsBeam::NData::IData;
					using FXPayloadType = NCsFX::NPayload::IPayload;
					using FireVisualDataType = NCsWeapon::NBeam::NData::NVisual::NFire::IFire;

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
					* Try to apply any Fire Visual Data.
					*
					* @param Data 
					*/
					void TryFire(DataType* Data);

					/**
					* Try to apply any Beam Impact Visual Data.
					*
					* @param Data
					* @param Hit	Hit information from trace.
					*/
					void TryImpact(BeamDataType* Data, const FHitResult& Hit);
				};
			}
		}
	}
}