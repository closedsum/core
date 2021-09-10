// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.

// Types
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"
#pragma once

class ICsBeamWeapon;
class UObject;
class USceneComponent;
class USkeletalMeshComponent;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsBeam::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NData, IData)
// NCsWeapon::NBeam::NImpl::NFX::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NBeam, NImpl, NFX, FImpl)
// NCsWeapon::NBeam::NImpl::NSound::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NBeam, NImpl, NSound, FImpl)

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
				#define BeamDataType NCsBeam::NData::IData
				#define FXImplType NCsWeapon::NBeam::NImpl::NFX::FImpl
				#define SoundImplType NCsWeapon::NBeam::NImpl::NSound::FImpl

				protected:

					/** UObject reference to an object implementing the interface: ICsBeamWeapon. */
					UObject* Outer;

					/** Interface reference to Outer. */
					ICsBeamWeapon* Interface;

					/** Reference to the root component of Outer. */
					USceneComponent* RootComponent;

					/** Reference to the owner of Outer. */
					UObject* Owner;

					/** Reference used for anything using component specific logic. */
					USceneComponent* Component;

					USkeletalMeshComponent* SkeletalMeshComponent;

					BeamDataType* BeamData;

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

					void SetBeamData(const FString& Context, BeamDataType* Type);
					void SetBeamData(BeamDataType* Value);

					FORCEINLINE BeamDataType* GetBeamData() const { return BeamData; }

					void SetFXImpl(FXImplType* Value) { FXImpl = Value; }
					void SetSoundImpl(SoundImplType* Value) { SoundImpl = Value; }

					bool IsValidChecked(const FString& Context);

					FVector GetStart(DataType* Data);
					FVector GetDirection(DataType* Data, const FVector& Start);

					void OnHit(const FHitResult& Hit);

					void LineTrace(DataType* Data, const FVector& Start, const FVector& End, FHitResult& OutHit);

					FCsScopedTimerHandle BeamScopedHandle;

					void Emit(DataType* Data);

					FString PrintOuterNameAndClass();
					FString PrintOuterNameClassAndOwner();

				#undef DataType
				#undef BeamDataType
				#undef FXImplType
				#undef SoundImplType
				};
			}
		}
	}
}