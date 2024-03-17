// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Macro/CsMacro_Namespace.h"
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

class ICsTraceWeapon;
class UObject;
class USceneComponent;
class USkeletalMeshComponent;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsTrace::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NData, IData)
// NCsWeapon::NTrace::NImpl::NFX::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NImpl, NFX, FImpl)
// NCsWeapon::NTrace::NImpl::NSound::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NTrace, NImpl, NSound, FImpl)

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NImpl
		{
			namespace NTrace
			{
				/**
				* Basic implementation for Trace used by an object
				* implementing the interface: ICsTraceWeapon
				*/
				struct CSWP_API FImpl
				{
					friend class ICsTraceWeapon;

				#define DataType NCsWeapon::NData::IData
				#define TraceDataType NCsTrace::NData::IData
				#define FXImplType NCsWeapon::NTrace::NImpl::NFX::FImpl
				#define SoundImplType NCsWeapon::NTrace::NImpl::NSound::FImpl

				protected:

					/** UObject reference to an object implementing the interface: ICsTraceWeapon. */
					UObject* Outer;

					/** Interface reference to Outer. */
					ICsTraceWeapon* Interface;

					/** Reference to the root component of Outer. */
					USceneComponent* RootComponent;

					/** Reference to the owner of Outer. */
					UObject* Owner;

					/** Reference used for anything using component specific logic. */
					USceneComponent* Component;

					USkeletalMeshComponent* SkeletalMeshComponent;

					TraceDataType* TraceData;

					/** Reference to FX implementation on Outer. */
					FXImplType* FXImpl;

					/** Reference to Sound implementation on Outer. */
					SoundImplType* SoundImpl;

					/**
					* Delegate type for custom implementation of GetStart().
					*
					* return Start Location
					*/
					DECLARE_DELEGATE_RetVal(FVector3f, FGetStart);

					/**  Delegate for custom implementation of GetStart(). */
					FGetStart GetStartImpl;

					/**
					* Delegate type for custom implementation of GetDirection().
					*
					* return Direction
					*/
					DECLARE_DELEGATE_RetVal(FVector3f, FGetDirection);

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

					void SetTraceData(const FString& Context, TraceDataType* Type);
					void SetTraceData(TraceDataType* Value);

					FORCEINLINE TraceDataType* GetTraceData() const { return TraceData; }

					void SetFXImpl(FXImplType* Value) { FXImpl = Value; }
					void SetSoundImpl(SoundImplType* Value) { SoundImpl = Value; }

					bool IsValidChecked(const FString& Context);

					FVector3f GetStart(DataType* Data);
					FVector3f GetDirection(DataType* Data, const FVector3f& Start);
					FVector3f GetEnd(DataType* Data, const FVector3f& Start);

					void OnHit(const FHitResult& Hit);

					void LineTrace(DataType* Data, const FVector3f& Start, const FVector3f& End, FHitResult& OutHit);

					FCsScopedTimerHandle TraceScopedHandle;

					void Trace(DataType* Data);

					FString PrintOuterNameAndClass();
					FString PrintOuterNameClassAndOwner();

				#undef DataType
				#undef TraceDataType
				#undef FXImplType
				#undef SoundImplType
				};
			}
		}
	}
}