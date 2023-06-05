// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
#include "Movement/CsProjectile_Movement.h"
#include "Tracking/CsProjectile_Tracking.h"

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
		// FVariables::FMovementInfo
		
		#define PROXY FVariables::FMovementInfo
		#define GET_BASE GetOuterMost()->MovementInfos

		const float& PROXY::GetInitialSpeed() const { return GET_BASE.InitialSpeeds[GetID()]; }
		float& PROXY::GetInitialSpeed() { return GET_BASE.InitialSpeeds[GetID()]; }
		const float& PROXY::GetMaxSpeed() const { return GET_BASE.MaxSpeeds[GetID()]; }
		float& PROXY::GetMaxSpeed() { return GET_BASE.MaxSpeeds[GetID()]; }
		const FVector& PROXY::GetDirection() const { return GET_BASE.Directions[GetID()]; }
		FVector& PROXY::GetDirection() { return GET_BASE.Directions[GetID()]; }
		const FVector& PROXY::GetVelocity() const { return GET_BASE.Velocities[GetID()]; }
		FVector& PROXY::GetVelocity() { return GET_BASE.Velocities[GetID()]; }
		const float& PROXY::GetSpeed() const { return GET_BASE.Speeds[GetID()]; }
		float& PROXY::GetSpeed() { return GET_BASE.Speeds[GetID()]; }
		const float& PROXY::GetGravityScale() const { return GET_BASE.GravityScales[GetID()]; }
		float& PROXY::GetGravityScale() { return GET_BASE.GravityScales[GetID()]; }

		#undef PROXY
		#undef GET_BASE

		// FVariables::FTrackingInfo

		#define PROXY FVariables::FTrackingInfo
		#define GET_BASE GetOuterMost()->TrackingInfos

		const float& PROXY::GetDelay() const { return GET_BASE.Delays[GetID()]; }
		float& PROXY::GetDelay() { return GET_BASE.Delays[GetID()]; }
		#define TrackingStateType NCsProjectile::NTracking::EState
		const TrackingStateType& PROXY::GetState() const { return GET_BASE.States[GetID()]; }
		TrackingStateType& PROXY::GetState() { return GET_BASE.States[GetID()]; }
		#undef TrackingStateType
		#define DestinationType NCsProjectile::NTracking::EDestination
		const DestinationType& PROXY::GetDestinationType() const { return GET_BASE.DestinationTypes[GetID()]; }
		DestinationType& PROXY::GetDestinationType() { return GET_BASE.DestinationTypes[GetID()]; }
		#undef DestinationType
		const uint32& PROXY::GetDestinationMask() const { return GET_BASE.DestinationMasks[GetID()]; }
		uint32& PROXY::GetDestinationMask() { return GET_BASE.DestinationMasks[GetID()]; }
		const USceneComponent* PROXY::GetComponent() const { return GET_BASE.Components[GetID()]; }
		USceneComponent*& PROXY::GetComponent() { return GET_BASE.Components[GetID()]; }
		const USkeletalMeshComponent* PROXY::GetMeshComponent() const { return GET_BASE.MeshComponents[GetID()]; }
		USkeletalMeshComponent*& PROXY::GetMeshComponent() { return GET_BASE.MeshComponents[GetID()]; }
		const FName& PROXY::GetBone() const { return GET_BASE.Bones[GetID()]; }
		FName& PROXY::GetBone() { return GET_BASE.Bones[GetID()]; }
		const int32& PROXY::GetTargetID() const { return GET_BASE.TargetIDs[GetID()]; }
		int32& PROXY::GetTargetID() { return GET_BASE.TargetIDs[GetID()]; }
		const float& PROXY::GetDuration() const { return GET_BASE.Durations[GetID()]; }
		float& PROXY::GetDuration() { return GET_BASE.Durations[GetID()]; }
		const float& PROXY::GetElapsedTime() const { return GET_BASE.ElapsedTimes[GetID()]; }
		float& PROXY::GetElapsedTime() { return GET_BASE.ElapsedTimes[GetID()]; }
		const FVector& PROXY::GetDestination() const { return GET_BASE.Destinations[GetID()]; }
		FVector& PROXY::GetDestination() { return GET_BASE.Destinations[GetID()]; }
		const FVector& PROXY::GetOffset() const { return GET_BASE.Offsets[GetID()]; }
		FVector& PROXY::GetOffset() { return GET_BASE.Offsets[GetID()]; }
		const float& PROXY::GetMinDotThreshold() const { return GET_BASE.MinDotThresholds[GetID()]; }
		float& PROXY::GetMinDotThreshold() { return GET_BASE.MinDotThresholds[GetID()]; }
		const float& PROXY::GetMaxDotBeforeUsingPitch() const { return GET_BASE.MaxDotBeforeUsingPitches[GetID()]; }
		float& PROXY::GetMaxDotBeforeUsingPitch() { return GET_BASE.MaxDotBeforeUsingPitches[GetID()]; }
		const float& PROXY::GetRotationRate() const { return GET_BASE.RotationRates[GetID()]; }
		float& PROXY::GetRotationRate() { return GET_BASE.RotationRates[GetID()]; }

		#undef PROXY
		#undef GET_BASE

		// FVariables::FCollisionInfo
		
		#define PROXY FVariables::FCollisionInfo
		#define GET_BASE GetOuterMost()->CollisionInfos

		const uint8& PROXY::GetChannel() const { return GET_BASE.Channels[GetID()]; }
		uint8& PROXY::GetChannel() { return GET_BASE.Channels[GetID()]; }
		const uint32& PROXY::GetBlockMask() const { return GET_BASE.BlockMasks[GetID()]; }
		uint32& PROXY::GetBlockMask() { return GET_BASE.BlockMasks[GetID()]; }
		const float& PROXY::GetRadius() const { return GET_BASE.Radii[GetID()]; }
		float& PROXY::GetRadius() { return GET_BASE.Radii[GetID()]; }
		const float& PROXY::GetHalfHeight() const { return GET_BASE.HalfHeights[GetID()]; }
		float& PROXY::GetHalfHeight() { return GET_BASE.HalfHeights[GetID()]; }
		const int32& PROXY::GetHitCount() const { return GET_BASE.HitCounts[GetID()]; }
		int32& PROXY::GetHitCount() { return GET_BASE.HitCounts[GetID()]; }

		#undef PROXY
		#undef GET_BASE

		// FVariables

		const FECsProjectile& FVariables::GetType() const { return Outer->Types[ID]; }
		FECsProjectile& FVariables::GetType() { return Outer->Types[ID]; }
		#define StateType NCsProjectile::EState
		const StateType& FVariables::GetState() const { return Outer->States[ID]; }
		StateType& FVariables::GetState() { return Outer->States[ID]; }
		#undef StateType
		const int32& FVariables::GetGeneration() const { return Outer->Generations[ID]; }
		int32& FVariables::GetGeneration() { return Outer->Generations[ID]; }
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

			if (!bOverride_Update)
			{
				void(*Log)(const FString&) = &NCsProjectile::FLog::Warning;

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

					ICsProjectile* Projectile = _Projectiles[ID];

					ICsProjectile_Movement* Movement = CS_INTERFACE_TO_INTERFACE_CAST(Projectile, ICsProjectile, ICsProjectile_Movement);

					if (Movement)
					{
						// NOTE: Currently Location is updated by Actor's Location
						Movement->Movement_SetLocation(FVector::ZeroVector);

						// LaunchDelay
						if (_States[ID] == StateType::LaunchDelay)
						{
							Movement->Movement_SetRotation(_Rotations[ID]);
						}
						else
						{
							Velocities[ID] = Speeds[ID] * Directions[ID];

							Movement->Movement_SetVelocity(Velocities[ID]);
						}
					}
				}
			}
			UpdateImpl.ExecuteIfBound(DeltaTime);
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

			// FManager = Outer
			TArray<ICsProjectile*>& _Projectiles = Outer->Projectiles;

			// Check IsValid
			{
				int32 ID = INDEX_NONE;

				// Delay
				for (int32 I = 0; I < DelayCount; ++I)
				{
					ID = DelayIDs[I];
					
					ICsProjectile* Projectile		 = _Projectiles[ID];
					ICsProjectile_Tracking* Tracking = CS_INTERFACE_TO_INTERFACE_CAST_CHECKED(Projectile, ICsProjectile, ICsProjectile_Tracking);

					if (!Tracking->Tracking_IsValid() &&
						!Tracking->Tracking_ReacquireDestination())
					{
						// Swap with Last Index and Mark as Inactive
						States[ID] = TrackingStateType::Inactive;

						DelayIDs[I]				 = DelayIDs[DelayCount - 1];
						DelayIDs[DelayCount - 1] = ID;
						--DelayCount;
					}
				}
				// Active
				for (int32 I = 0; I < ActiveCount; ++I)
				{
					ID = ActiveIDs[I];
					
					ICsProjectile* Projectile		 = _Projectiles[ID];
					ICsProjectile_Tracking* Tracking = CS_INTERFACE_TO_INTERFACE_CAST_CHECKED(Projectile, ICsProjectile, ICsProjectile_Tracking);

					if (!Tracking->Tracking_IsValid() &&
						!Tracking->Tracking_ReacquireDestination())
					{
						// Swap with Last Index and Mark as Inactive
						States[ID] = TrackingStateType::Inactive;

						ActiveIDs[I]			  = ActiveIDs[DelayCount - 1];
						ActiveIDs[DelayCount - 1] = ID;
						--ActiveCount;
					}
				}
			}

			// ElapsedTimes
			{
				// Delay
				for (int32 I = 0; I < DelayCount; ++I)
				{
					const int32& ID = DelayIDs[I];

					ElapsedTimes[ID] += DeltaTime.Time;
				}
				// Active
				for (int32 I = 0; I < ActiveCount; ++I)
				{
					const int32& ID = ActiveIDs[I];

					ElapsedTimes[ID] += DeltaTime.Time;
				}
			}

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

			// FManager::FMovementInfos = Outer->MovementInfos
			TArray<FVector>& _Directions = Outer->MovementInfos.Directions;

			// Get Destinations
			for (int32 I = 0; I < ActiveCount; ++I)
			{
				const int32& ID = ActiveIDs[I];

				ICsProjectile* Projectile		 = _Projectiles[ID];
				ICsProjectile_Tracking* Tracking = CS_INTERFACE_TO_INTERFACE_CAST_CHECKED(Projectile, ICsProjectile, ICsProjectile_Tracking);

				Destinations[ID] = Tracking->Tracking_GetDestination();
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
				AliveIDs[AliveCount] = ID;

				// Tracking
				TrackingInfos.SetupIDs(ID);

				++AliveCount;
				++AllocatedCount;
			}
			// Deallocate and prep Search
			{
				const int32 Count = Last_DeallocatedIDs.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					const int32& ID = Last_DeallocatedIDs[I];

					Last_Locations[ID] = FVector::ZeroVector;

					Last_DeallocatedIDs.RemoveAt(I, 1, false);
				}

				BoundsWorld.Reset();

				for (int32 I = 0; I < AllocatedCount; ++I)
				{
					const int32& ID = AllocatedIDs[I];

					BoundsWorld.Insert(ID, Locations[ID].X, Locations[ID].Y, CollisionInfos.HalfHeights[ID]);
				}
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

			Locations[ID]	   = Payload.Location;
			Last_Locations[ID] = Locations[ID];

			MovementInfos.Directions[ID] = Payload.Direction;

			Rotations[ID]	   = MovementInfos.Directions[ID].Rotation();
			Last_Rotations[ID] = Rotations[ID];
			Orientations[ID]   = Rotations[ID].Quaternion();

			CollisionInfos.Radii[ID]	   = Payload.CollisionRadius;
			CollisionInfos.HalfHeights[ID] = Payload.CollisionHalfHeight;

			BoundsWorld.Insert(ID, Locations[ID].X, Locations[ID].Y, CollisionInfos.HalfHeights[ID]);

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