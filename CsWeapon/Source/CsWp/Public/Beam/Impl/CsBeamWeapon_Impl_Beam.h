// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

class ICsGetUpdateGroup;
class ICsWeapon;
class ICsBeamWeapon;
class ICsGetBeamType;
class UObject;
class USceneComponent;
class USkeletalMeshComponent;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsWeapon::NBeam::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NBeam, NData, IData)
// NCsWeapon::NBeam::NParams::NBeam::IBeam
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NBeam, NParams, NBeam, IBeam)
// NCsWeapon::NBeam::NImpl::NFX::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NBeam, NImpl, NFX, FImpl)
// NCsWeapon::NBeam::NImpl::NSound::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NBeam, NImpl, NSound, FImpl)

class ICsBeam;

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NImpl
		{
			namespace NBeam
			{
				/**
				* Basic implementation for Beam used by an object
				* implementing the interface: ICsBeamWeapon
				*/
				struct CSWP_API FImpl
				{
					friend class ICsBeamWeapon;

				#define DataType NCsWeapon::NData::IData
				#define BeamDataType NCsWeapon::NBeam::NData::IData
				#define BeamParamsType NCsWeapon::NBeam::NParams::NBeam::IBeam
				#define FXImplType NCsWeapon::NBeam::NImpl::NFX::FImpl
				#define SoundImplType NCsWeapon::NBeam::NImpl::NSound::FImpl

				protected:

					/** UObject reference to an object implementing the interface: ICsBeamWeapon. */
					UObject* Outer;

					/** Interface to get the Update Group (FECsUpdateGroup) from Outer. */
					ICsGetUpdateGroup* GetUpdateGroup;

					/** Weapon Interface reference to Outer. */
					ICsWeapon* WeaponInterface;

					/** Beam Weapon Interface reference to Outer. */
					ICsBeamWeapon* BeamWeaponInterface;

					/** Interface to get Beam's type (FECsBeam) from Outer. */
					ICsGetBeamType* GetBeamType;

					/** Reference to the root component of Outer. */
					USceneComponent* RootComponent;

					/** Reference to the owner of Outer. */
					UObject* Owner;

					/** Reference used for anything using component specific logic. */
					USceneComponent* Component;

					USkeletalMeshComponent* SkeletalMeshComponent;

					DataType* Data;

					BeamDataType* BeamData;

					BeamParamsType* BeamParams;

					/** Reference to FX implementation on Outer. */
					FXImplType* FXImpl;

					/** Reference to Sound implementation on Outer. */
					SoundImplType* SoundImpl;

					/**
					* Delegate type for custom implementation of GetStart().
					*
					* return Start Location
					*/
					DECLARE_DELEGATE_RetVal(FVector, FGetStart);

					/**  Delegate for custom implementation of GetStart(). */
					FGetStart GetStartImpl;

					/**
					* Delegate type for custom implementation of GetDirection().
					*
					* return Direction
					*/
					DECLARE_DELEGATE_RetVal(FVector, FGetDirection);

					/** Delegate for custom implementation of GetDirection(). */
					FGetDirection GetDirectionImpl;

					TArray<ICsBeam*> Beams;

					FCsScopedTimerHandle BeamScopedHandle;

				public:

					FImpl();
					~FImpl();

					void SetOuter(UObject* InOuter);
					FORCEINLINE UObject* GetOuter() const { return Outer; }

					void SetRootComponent(USceneComponent* InComponent);
					FORCEINLINE USceneComponent* GetRootComponent() { return RootComponent; }

					FORCEINLINE void SetOwner(UObject* InOwner) { Owner = InOwner; }
					FORCEINLINE UObject* GetOwner() const { return Owner; }

					FORCEINLINE void SetComponent(USceneComponent* InComponent) { Component = InComponent; }
					FORCEINLINE USceneComponent* GetComponent() const { return Component; }

					void SetData(DataType* Value) { Data = Value; }
					void SetBeamData(BeamDataType* Value);

					void SetFXImpl(FXImplType* Value) { FXImpl = Value; }
					void SetSoundImpl(SoundImplType* Value) { SoundImpl = Value; }

					FVector GetLocation();
					FVector GetDirection(const FVector& Start);

					void LineTrace(const FVector& Start, const FVector& End, FHitResult& OutHit);

					void Emit();

					void AfterShot();
					void AfterBeamsPerShot();
					void AfterStopFire();

					FString PrintOuterNameAndClass();
					FString PrintOuterNameClassAndOwner();

				#undef DataType
				#undef BeamDataType
				#undef BeamParamsType
				#undef FXImplType
				#undef SoundImplType
				};
			}
		}
	}
}