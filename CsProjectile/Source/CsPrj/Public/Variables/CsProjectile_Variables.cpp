// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Variables/CsProjectile_Variables.h"

// CVars
#include "Managers/Projectile/CsCVars_Manager_Projectile.h"
// Types
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"
// Library
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Projectile/CsManager_Projectile.h"
// Projectile
#include "CsProjectilePooledImpl.h"
// Components
#include "CsProjectileMovementComponent.h" // TEMP

// NCsProjectile::NVariables::NAllocate::FPayload
#pragma region

namespace NCsProjectile
{
	namespace NVariables
	{
		namespace NAllocate
		{
			bool FPayload::IsValidChecked(const FString& Context) const
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectile, Type)
				return true;
			}
		}
	}
}

#pragma endregion NCsProjectile::NVariables::NAllocate::FPayload

// NCsProjectile::NVariables::FVariables
#pragma region

namespace NCsProjectile
{
	namespace NVariables
	{
		// FVariables::FTrackingInfo

		const float& FVariables::FTrackingInfo::GetDelay() const { return GetOuterMost()->TrackingInfos.Delays[GetID()]; }
		float& FVariables::FTrackingInfo::GetDelay() { return GetOuterMost()->TrackingInfos.Delays[GetID()]; }
		#define TrackingStateType NCsProjectile::NTracking::EState
		const TrackingStateType& FVariables::FTrackingInfo::GetState() const { return GetOuterMost()->TrackingInfos.States[GetID()]; }
		TrackingStateType& FVariables::FTrackingInfo::GetState() { return GetOuterMost()->TrackingInfos.States[GetID()]; }
		#undef TrackingStateType
		#define DestinationType NCsProjectile::NTracking::EDestination
		const DestinationType& FVariables::FTrackingInfo::GetDestinationType() const { return GetOuterMost()->TrackingInfos.DestinationTypes[GetID()]; }
		DestinationType& FVariables::FTrackingInfo::GetDestinationType() { return GetOuterMost()->TrackingInfos.DestinationTypes[GetID()]; }
		#undef DestinationType
		const USceneComponent* FVariables::FTrackingInfo::GetComponent() const { return GetOuterMost()->TrackingInfos.Components[GetID()]; }
		USceneComponent*& FVariables::FTrackingInfo::GetComponent() { return GetOuterMost()->TrackingInfos.Components[GetID()]; }
		const USkeletalMeshComponent* FVariables::FTrackingInfo::GetMeshComponent() const { return GetOuterMost()->TrackingInfos.MeshComponents[GetID()]; }
		USkeletalMeshComponent*& FVariables::FTrackingInfo::GetMeshComponent() { return GetOuterMost()->TrackingInfos.MeshComponents[GetID()]; }
		const FName& FVariables::FTrackingInfo::GetBone() const { return GetOuterMost()->TrackingInfos.Bones[GetID()]; }
		FName& FVariables::FTrackingInfo::GetBone() { return GetOuterMost()->TrackingInfos.Bones[GetID()]; }
		const int32& FVariables::FTrackingInfo::GetTargetID() const { return GetOuterMost()->TrackingInfos.TargetIDs[GetID()]; }
		int32& FVariables::FTrackingInfo::GetTargetID() { return GetOuterMost()->TrackingInfos.TargetIDs[GetID()]; }
		const float& FVariables::FTrackingInfo::GetDuration() const { return GetOuterMost()->TrackingInfos.Durations[GetID()]; }
		float& FVariables::FTrackingInfo::GetDuration() { return GetOuterMost()->TrackingInfos.Durations[GetID()]; }
		const float& FVariables::FTrackingInfo::GetElapsedTime() const { return GetOuterMost()->TrackingInfos.ElapsedTimes[GetID()]; }
		float& FVariables::FTrackingInfo::GetElapsedTime() { return GetOuterMost()->TrackingInfos.ElapsedTimes[GetID()]; }
		const FVector& FVariables::FTrackingInfo::GetDestination() const { return GetOuterMost()->TrackingInfos.Destinations[GetID()]; }
		FVector& FVariables::FTrackingInfo::GetDestination() { return GetOuterMost()->TrackingInfos.Destinations[GetID()]; }
		const FVector& FVariables::FTrackingInfo::GetOffset() const { return GetOuterMost()->TrackingInfos.Offsets[GetID()]; }
		FVector& FVariables::FTrackingInfo::GetOffset() { return GetOuterMost()->TrackingInfos.Offsets[GetID()]; }
		const float& FVariables::FTrackingInfo::GetMinDotThreshold() const { return GetOuterMost()->TrackingInfos.MinDotThresholds[GetID()]; }
		float& FVariables::FTrackingInfo::GetMinDotThreshold() { return GetOuterMost()->TrackingInfos.MinDotThresholds[GetID()]; }
		const float& FVariables::FTrackingInfo::GetMaxDotBeforeUsingPitch() const { return GetOuterMost()->TrackingInfos.MaxDotBeforeUsingPitches[GetID()]; }
		float& FVariables::FTrackingInfo::GetMaxDotBeforeUsingPitch() { return GetOuterMost()->TrackingInfos.MaxDotBeforeUsingPitches[GetID()]; }
		const float& FVariables::FTrackingInfo::GetRotationRate() const { return GetOuterMost()->TrackingInfos.RotationRates[GetID()]; }
		float& FVariables::FTrackingInfo::GetRotationRate() { return GetOuterMost()->TrackingInfos.RotationRates[GetID()]; }

		// FVariables::FCollisionInfo
		
		const float& FVariables::FCollisionInfo::GetRadius() const { return GetOuterMost()->CollisionInfos.Radii[GetID()]; }
		float& FVariables::FCollisionInfo::GetRadius() { return GetOuterMost()->CollisionInfos.Radii[GetID()]; }

		// FVariables

		const FVector& FVariables::GetLastLocation() const { return Outer->Last_Locations[ID]; }
		FVector& FVariables::GetLastLocation() { return Outer->Last_Locations[ID]; }
		const FVector& FVariables::GetLocation() const { return Outer->Locations[ID]; }
		FVector& FVariables::GetLocation() { return Outer->Locations[ID]; }
		const FRotator& FVariables::GetRotation() const { return Outer->Rotations[ID]; }
		FRotator& FVariables::GetRotation() { return Outer->Rotations[ID]; }
		const FQuat& FVariables::GetOrientation() const { return Outer->Orientations[ID]; }
		FQuat& FVariables::GetOrientation() { return Outer->Orientations[ID]; }
	}
}

#pragma endregion NCsProjectile::NVariables::FVariables

// NCsProjectile::NVariables::FManager
#pragma region

namespace NCsProjectile
{
	namespace NVariables
	{
		namespace NManager
		{
			namespace NCached
			{
				namespace Str
				{

				}

				namespace ScopedTimer
				{
					//CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCCharacter::NVariables::FManager, Update_Steering);
					//CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCCharacter::NVariables::FManager, Resolve_Movement);
				}
			}

			namespace NMovementInfos
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NVariables::FManager::FMovementInfos, Update);
					}
				}
			}

			namespace NTrackingInfos
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NVariables::FManager::FTrackingInfos, Update);
					}
				}
			}
		}

		void FManager::FMovementInfos::Update(const FCsDeltaTime& DeltaTime)
		{
			using namespace NCsProjectile::NVariables::NManager::NMovementInfos::NCached;

			const FString& Context = Str::Update;

			typedef NCsProjectile::EState StateType;

			// FManager = Outer
			TArray<ICsProjectile*>& _Projectiles = Outer->Projectiles;
			const int32& _AliveCount	     = Outer->AliveCount;
			const TArray<int32>& _AliveIDs   = Outer->AliveIDs;
			TArray<FRotator>& _Rotations	 = Outer->Rotations;
			TArray<FQuat>& _Orientations	 = Outer->Orientations;

			// Resolve Rotation and Orientation
			for (int32 I = 0; I < _AliveCount; ++I)
			{
				const int32& ID = _AliveIDs[I];

				_Rotations[ID]	  = Directions[ID].Rotation();
				_Orientations[ID] = _Rotations[ID].Quaternion();
			}

			const TArray<StateType>& _States = Outer->States;

			// TEMP
			for (int32 I = 0; I < _AliveCount; ++I)
			{
				const int32& ID = _AliveIDs[I];

				ICsProjectile* Projectile				= _Projectiles[ID];
				ACsProjectilePooledImpl* ProjectileImpl = CS_INTERFACE_TO_UOBJECT_CAST_CHECKED(Projectile, ICsProjectile, ACsProjectilePooledImpl);

				// LaunchDelay
				if (_States[ID] == StateType::LaunchDelay)
				{
					ProjectileImpl->SetActorRotation(_Rotations[ID]);
				}
				else
				{
					Velocities[ID] = Speeds[ID] * Directions[ID];
					ProjectileImpl->MovementComponent->Velocity = Speeds[ID] * Directions[ID];
				}
			}
		}

		void FManager::FTrackingInfos::SetupIDs(const int32& ID)
		{
			typedef NCsProjectile::NTracking::EState StateType;

			// Delay
			if (States[ID] == StateType::Delay)
			{
				DelayIDs[DelayCount] = ID;
				++DelayCount;
			}
			// Active
			else
			if (States[ID] == StateType::Active)
			{
				ActiveIDs[ActiveCount] = ID;
				++ActiveCount;
			}
		}

		void FManager::FTrackingInfos::Update(const FCsDeltaTime& DeltaTime)
		{
			using namespace NCsProjectile::NVariables::NManager::NTrackingInfos::NCached;

			const FString& Context = Str::Update;

			typedef NCsProjectile::NTracking::EState TrackingStateType;

			// Delay -> Active
			for (int32 I = 0; I < DelayCount; ++I)
			{
				const int32& ID = DelayIDs[I];

				if (ElapsedTimes[ID] >= Delays[ID])
				{
					States[ID]			   = TrackingStateType::Active;
					ActiveIDs[ActiveCount] = ID;
					++ActiveCount;
				}
			}
			
			typedef NCsMath::FLibrary MathLibrary;

			// FManager = Outer
			TArray<ICsProjectile*>& _Projectiles = Outer->Projectiles;
			TArray<FVector>& _Directions		 = Outer->MovementInfos.Directions;

			// Get Destinations
			for (int32 I = 0; I < ActiveCount; ++I)
			{
				const int32& ID = ActiveIDs[I];

				ICsProjectile* Projectile				= _Projectiles[ID];
				ACsProjectilePooledImpl* ProjectileImpl = CS_INTERFACE_TO_UOBJECT_CAST_CHECKED(Projectile, ICsProjectile, ACsProjectilePooledImpl);

				Destinations[ID] = ProjectileImpl->TrackingImpl.GetDestination();
			}

			// FManager = Outer
			typedef NCsProjectile::EState StateType;

			const TArray<StateType>& _States  = Outer->States;
			const TArray<FVector>& _Locations = Outer->Locations;

			// Get Directions
			{
				FVector NewDirection;
				float Dot;

				for (int32 I = 0; I < ActiveCount; ++I)
				{
					const int32& ID = ActiveIDs[I];

					NewDirection = (Destinations[ID] - _Locations[ID]).GetSafeNormal();

					const float& MinDotThreshold = MinDotThresholds[ID];
			
					Dot = FVector::DotProduct(_Directions[ID], NewDirection);

					if (Dot >= MinDotThreshold)
					{
						const float& MaxDotBeforeUsingPitch = MaxDotBeforeUsingPitches[ID];

						// Ignore Pitch / Z
						if (Dot <= MaxDotBeforeUsingPitch)
						{
							Destinations[ID].Z = _Locations[ID].Z;
						}

						Destinations[ID] += Offsets[ID];
						NewDirection      = (Destinations[ID] - _Locations[ID]).GetSafeNormal();

						_Directions[ID] = FMath::VInterpNormalRotationTo(_Directions[ID], NewDirection, DeltaTime.Time, RotationRates[ID]);
					}
				}
			}

			// Active -> Inactive
			for (int32 I = 0; I < ActiveCount; ++I)
			{
				const int32& ID = ActiveIDs[I];

				// Result is either:
				//  True: StateType::Active (2)
				//	False: StateType::Inactive (0)
				States[ID] = (TrackingStateType)(((Durations[ID] == 0.0f) | (ElapsedTimes[ID] < Durations[ID])) * 2);
			}
		}

		void FManager::FCollisionInfos::Update(const FCsDeltaTime& DeltaTime)
		{
			UpdateImpl.ExecuteIfBound(DeltaTime);
		}

		void FManager::Update(const FCsDeltaTime& DeltaTime)
		{
			typedef NCsResource::NManager::NValue::NFixed::NInt32::FResource ResourceType;

			TCsDoubleLinkedList<ResourceType*>* Current = Manager_ID.GetAllocatedHead();
			TCsDoubleLinkedList<ResourceType*>* Next	= Current;

			// State
			AllocatedCount = 0;
			AliveCount = 0;

			TrackingInfos.ActiveCount = 0;
			TrackingInfos.DelayCount = 0;

			while (Next)
			{
				Current			= Next;
				ResourceType* C = **Current;
				Next			= Current->GetNextLink();

				int32& ID = C->GetRef();

				AllocatedIDs[AllocatedCount] = ID;

				// Tracking
				TrackingInfos.SetupIDs(ID);

				++AllocatedCount;
			}
			// Deallocate and prep Search
			{
				const int32 Count = Last_DeallocatedIDs.Num();

				const float GridWidthBy2  = LooseCoarseGrid.GetWidthBy2();
				const float GridHeightBy2 = LooseCoarseGrid.GetHeightBy2();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					const int32& ID = Last_DeallocatedIDs[I];

					LooseCoarseGrid.Remove(ID, Last_Locations[ID].X + GridWidthBy2, Last_Locations[ID].Y + GridHeightBy2);

					Last_Locations[ID] = FVector::ZeroVector;

					Last_DeallocatedIDs.RemoveAt(I, 1, false);
				}
				LooseCoarseGrid.Optimize();
			}

			TrackingInfos.Update(DeltaTime);
			MovementInfos.Update(DeltaTime);
			CollisionInfos.Update(DeltaTime);
		}

		#define VariablesType NCsProjectile::NVariables::FVariables

		#define VariablesPayloadType NCsProjectile::NVariables::NAllocate::FPayload
		VariablesType* FManager::AllocateChecked(const FString& Context, const VariablesPayloadType& Payload)
		{
			const int32& ID = Manager_ID.AllocateResourceRef();

			Variables[ID].ID = ID;

			Projectiles[ID] = Payload.Projectile;
			Types[ID]		= Payload.Type;

			/*
			typedef NCCharacter::NAnim::EMethod AnimMethodType;

			if (Payload.IsVertexAnimMethod())
			{
				const int32 SkinID			  = Niagara_SkinID_AllocateChecked(Context, Payload.Type, Payload.SkinType);
				Manager_Variables.SkinIDs[ID] = SkinID;
			}
			else
			{
				Manager_Variables.SkinIDs[ID] = INDEX_NONE;
			}
			*/

			const FVector& Location = Payload.Location;
			const float& Radius		= Payload.CollisionRadius;

			const float GridWidthBy2  = LooseCoarseGrid.GetWidthBy2();
			const float GridHeightBy2 = LooseCoarseGrid.GetHeightBy2();

			LooseCoarseGrid.Insert(ID, Location.X + GridWidthBy2, Location.Y + GridHeightBy2, Radius, Radius);

			return GetVariablesPtr(ID);
		}

		void FManager::DeallocateChecked(const FString& Context, VariablesType* Vars)
		{
			CS_IS_PTR_NULL_CHECKED(Vars);

			check(Vars->IsValidChecked(Context));

			const int32 ID = Vars->GetID();

			check(Manager_ID.IsAllocatedChecked(Context, ID));
			checkf(Vars == GetVariablesPtr(ID), TEXT("%s: ID: %s is NOT correct for Vars."), *Context, ID);
			/*
			if (Manager_Variables.SkinIDs[ID] != INDEX_NONE)
			{
				Niagara_SkinID_DeallocateChecked(Context, Manager_Variables.Types[ID], Manager_Variables.SkinTypes[ID], Manager_Variables.SkinIDs[ID]);
			}
			*/
			Last_DeallocatedIDs.Add(ID);
			Reset(ID);
		}

		#undef VariablesPayloadType
	}
}

#pragma endregion NCsProjectile::NVariables::FManager