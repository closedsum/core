// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "Types/CsTypes_Projectile.h"
#include "Types/CsTypes_Projectile_Tracking.h"
#include "Managers/Time/CsTypes_Time.h"
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Fixed_Int32.h"
// Containers
#include "Containers/CsUniformGrid.h"

class ICsProjectile;
class USceneComponent;
class USkeletalMeshComponent;

// NCCharacter::NVariables::NAllocate::FPayload
#pragma region

namespace NCsProjectile
{
	namespace NVariables
	{
		namespace NAllocate
		{
			struct CSPRJ_API FPayload
			{
			public:

				ICsProjectile* Projectile;

				FECsProjectile Type;

				FVector Location;

				FVector Direction;

				float CollisionRadius;

				float CollisionHalfHeight;

				FPayload() :
					Projectile(nullptr),
					Type(),
					Location(0.0f),
					Direction(0.0f),
					CollisionRadius(0.0f),
					CollisionHalfHeight(0.0f)
				{
				}

				bool IsValidChecked(const FString& Context) const;
			};
		}
	}
}

#pragma endregion NCsProjectile::NVariables::NAllocate::FPayload

// NCsProjectile::NVariables::FVariables
#pragma region

// NCsProjectile::NVariables::FManager
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NVariables, FManager)

namespace NCsProjectile
{
	namespace NVariables
	{
		struct CSPRJ_API FVariables
		{
		private:

			using StateType = NCsProjectile::EState;

		private:

			NCsProjectile::NVariables::FManager* Outer;

		public:

			int32 ID;

			struct CSPRJ_API FMovementInfo
			{
				friend struct NCsProjectile::NVariables::FVariables;

			private:

				NCsProjectile::NVariables::FVariables* Outer;

			public:

				FMovementInfo() :
					Outer(nullptr)
				{
				}

				FORCEINLINE void SetOuter(NCsProjectile::NVariables::FVariables* InOuter) { Outer = InOuter; }
				FORCEINLINE NCsProjectile::NVariables::FVariables* GetOuter() { return Outer; }

				FORCEINLINE const NCsProjectile::NVariables::FManager* GetOuterMost() const { return Outer->GetOuter(); }
				FORCEINLINE NCsProjectile::NVariables::FManager* GetOuterMost() { return Outer->GetOuter(); }

				FORCEINLINE const int32& GetID() const { return Outer->GetID(); }

				const float& GetInitialSpeed() const;
				float& GetInitialSpeed();
				const float& GetMaxSpeed() const;
				float& GetMaxSpeed();
				const FVector& GetDirection() const;
				FVector& GetDirection();
				const FVector3f& GetDirection3f() const;
				FVector3f& GetDirection3f();
				const FVector& GetVelocity() const;
				FVector& GetVelocity();
				const FVector3f& GetVelocity3f() const;
				FVector3f& GetVelocity3f();
				const float& GetSpeed() const;
				float& GetSpeed();
				const float& GetGravityScale() const;
				float& GetGravityScale();
			};

			FMovementInfo MovementInfo;
			 
			struct CSPRJ_API FTrackingInfo
			{
				friend struct NCsProjectile::NVariables::FVariables;

			private:

				using TrackingStateType = NCsProjectile::NTracking::EState;
				using DestinationType = NCsProjectile::NTracking::EDestination;

			private:

				NCsProjectile::NVariables::FVariables* Outer;

			public:

				FTrackingInfo() :
					Outer(nullptr)
				{
				}

				FORCEINLINE void SetOuter(NCsProjectile::NVariables::FVariables* InOuter) { Outer = InOuter; }
				FORCEINLINE NCsProjectile::NVariables::FVariables* GetOuter() { return Outer; }

				FORCEINLINE const NCsProjectile::NVariables::FManager* GetOuterMost() const { return Outer->GetOuter(); }
				FORCEINLINE NCsProjectile::NVariables::FManager* GetOuterMost() { return Outer->GetOuter(); }

				FORCEINLINE const int32& GetID() const { return Outer->GetID(); }

				const float& GetDelay() const;
				float& GetDelay();			
				const TrackingStateType& GetState() const;
				TrackingStateType& GetState();	
				const DestinationType& GetDestinationType() const;
				DestinationType& GetDestinationType();
				const uint32& GetDestinationMask() const;
				uint32& GetDestinationMask();
				const USceneComponent* GetComponent() const;
				USceneComponent*& GetComponent();
				const USkeletalMeshComponent* GetMeshComponent() const;
				USkeletalMeshComponent*& GetMeshComponent();
				const FName& GetBone() const;
				FName& GetBone();
				const int32& GetTargetID() const;
				int32& GetTargetID();
				const float& GetDuration() const;
				float& GetDuration();
				const float& GetElapsedTime() const;
				float& GetElapsedTime();
				const FVector& GetDestination() const;
				FVector& GetDestination();
				const FVector3f& GetDestination3f() const;
				FVector3f& GetDestination3f();
				const FVector& GetOffset() const;
				FVector& GetOffset();
				const FVector3f& GetOffset3f() const;
				FVector3f& GetOffset3f();
				const float& GetMinDotThreshold() const;
				float& GetMinDotThreshold();
				const float& GetMaxDotBeforeUsingPitch() const;
				float& GetMaxDotBeforeUsingPitch();
				const float& GetRotationRate() const;
				float& GetRotationRate();

				FORCEINLINE void DestinationMask_SetReacquire() { NCsProjectile::NTracking::NDestination::NFlag::SetReacquire(GetDestinationMask()); }
				FORCEINLINE void DestinationMask_MarkReacquire() { NCsProjectile::NTracking::NDestination::NFlag::MarkReacquire(GetDestinationMask()); }
				FORCEINLINE void DestinationMask_ClearReacquire() { NCsProjectile::NTracking::NDestination::NFlag::ClearReacquire(GetDestinationMask()); }
				FORCEINLINE bool DestinationMask_HasReacquire() const { return NCsProjectile::NTracking::NDestination::NFlag::HasReacquire(GetDestinationMask()); }

				void Reset()
				{
				}
			};

			FTrackingInfo TrackingInfo;

			struct CSPRJ_API FCollisionInfo
			{
				friend struct NCsProjectile::NVariables::FVariables;

			private:

				NCsProjectile::NVariables::FVariables* Outer;

			public:

				FCollisionInfo() :
					Outer(nullptr)
				{
				}

				FORCEINLINE void SetOuter(NCsProjectile::NVariables::FVariables* InOuter) { Outer = InOuter; }
				FORCEINLINE NCsProjectile::NVariables::FVariables* GetOuter() { return Outer; }

				FORCEINLINE const NCsProjectile::NVariables::FManager* GetOuterMost() const { return Outer->GetOuter(); }
				FORCEINLINE NCsProjectile::NVariables::FManager* GetOuterMost() { return Outer->GetOuter(); }

				FORCEINLINE const int32& GetID() const { return Outer->GetID(); }

				const uint8& GetChannel() const;
				uint8& GetChannel();
				const uint32& GetBlockMask() const;
				uint32& GetBlockMask();
				const float& GetRadius() const;
				float& GetRadius();
				const float& GetHalfHeight() const;
				float& GetHalfHeight();
				const int32& GetHitCount() const;
				int32& GetHitCount();
			};

			FCollisionInfo CollisionInfo;

			FVariables() :
				Outer(nullptr),
				ID(INDEX_NONE),
				MovementInfo(),
				TrackingInfo(),
				CollisionInfo()
			{
				MovementInfo.Outer = this;
				TrackingInfo.Outer = this;
				CollisionInfo.Outer = this;
			}

			FORCEINLINE void SetOuter(NCsProjectile::NVariables::FManager* InOuter) 
			{
				Outer = InOuter;
				MovementInfo.SetOuter(this);
				TrackingInfo.SetOuter(this);
				CollisionInfo.SetOuter(this);
			}
			FORCEINLINE NCsProjectile::NVariables::FManager* GetOuter() { return Outer; }

			FORCEINLINE const int32& GetID() const { return ID; }

			const FECsProjectile& GetType() const;
			FECsProjectile& GetType();	
			const StateType& GetState() const;
			StateType& GetState();
			const int32& GetGeneration() const;
			int32& GetGeneration();
			const FVector& GetLastLocation() const;
			FVector& GetLastLocation();
			const FVector3f& GetLastLocation3f() const;
			FVector3f& GetLastLocation3f();
			const FVector& GetLocation() const;
			FVector& GetLocation();
			const FVector3f& GetLocation3f() const;
			FVector3f& GetLocation3f();
			const FRotator& GetRotation() const;
			FRotator& GetRotation();
			const FRotator3f& GetRotation3f() const;
			FRotator3f& GetRotation3f();
			const FQuat& GetOrientation() const;
			FQuat& GetOrientation();
			const FQuat4f& GetOrientation4f() const;
			FQuat4f& GetOrientation4f();

			FORCEINLINE void ResolveOrientation() { GetOrientation() = GetRotation().Quaternion(); }

			FORCEINLINE bool IsValidChecked(const FString& Context) const 
			{ 
				checkf(ID != INDEX_NONE, TEXT("%s: ID == INDEX_NONE is NOT Valid."), *Context); 
				return true;
			}
			FORCEINLINE bool IsValid() const { return ID != INDEX_NONE; }

			void Reset()
			{
				ID = INDEX_NONE;
				TrackingInfo.Reset();
			}
		};
	}
}

#pragma endregion NCsProjectile::NVariables::FVariables

// NCsProjectile::NVariables::FManager
#pragma region

class UCsManager_Projectile;
class ICsProjectile;
class USceneComponent;

namespace NCsProjectile
{
	namespace NVariables
	{
		struct CSPRJ_API FManager final
		{
			friend class UCsManager_Projectile;

		private:

			using IDManagerType = NCsResource::NManager::NValue::NFixed::NInt32::FManager;
			using VariablesType = NCsProjectile::NVariables::FVariables;
			using VariablesPayloadType = NCsProjectile::NVariables::NAllocate::FPayload;
			using StateType = NCsProjectile::EState;
			using BoundsWorldType = NCsGrid::NUniform::FGrid;

		private:

			UCsManager_Projectile* Outer;

		public:

			TArray<ICsProjectile*> Projectiles;

		// IDs

			IDManagerType Manager_ID;

			int32 AllocatedCount;

			TArray<int32> AllocatedIDs;

			TArray<int32> Last_DeallocatedIDs;

			TArray<VariablesType> Variables;

			int32 AliveCount;

			TArray<int32> AliveIDs;

		// State

			TArray<FECsProjectile> Types;

			TArray<StateType> States;

			TArray<int32> Generations;

		// Movement

			TArray<FVector> Last_Locations;
			TArray<FVector3f> Last_Location3fs;
			TArray<FVector> Locations;
			TArray<FVector3f> Location3fs;

			TArray<FRotator> Last_Rotations;
			TArray<FRotator3f> Last_Rotation3fs;
			TArray<FRotator> Rotations;
			TArray<FRotator3f> Rotation3fs;
			TArray<FQuat> Orientations;
			TArray<FQuat4f> Orientation4fs;
			TArray<FVector> FacingDirections;
			TArray<FVector3f> FacingDirection3fs;

			struct FMovementInfos
			{
				friend struct NCsProjectile::NVariables::FManager;

			private:

				NCsProjectile::NVariables::FManager* Outer;

			public:

				TArray<float> InitialSpeeds;

				TArray<float> MaxSpeeds;

				TArray<float> GravityScales;

				TArray<FVector> Directions;
				TArray<FVector3f> Direction3fs;

				TArray<FVector> Velocities;
				TArray<FVector3f> Velocity3fs;

				TArray<float> Speeds;

				bool bOverride_Update;

				DECLARE_DELEGATE_OneParam(FUpdateImpl, const FCsDeltaTime& DeltaTime);

				FUpdateImpl UpdateImpl;

				FMovementInfos() :
					Outer(nullptr),
					InitialSpeeds(),
					MaxSpeeds(),
					GravityScales(),
					Directions(),
					Direction3fs(),
					Velocities(),
					Velocity3fs(),
					Speeds(),
					bOverride_Update(false),
					UpdateImpl()
				{
				}

				void SetSize(const int32& InSize)
				{
					InitialSpeeds.Reset(InSize);
					MaxSpeeds.Reset(InSize);
					GravityScales.Reset(InSize);
					Directions.Reset(InSize);
					Direction3fs.Reset(InSize);
					Velocities.Reset(InSize);
					Velocity3fs.Reset(InSize);
					Speeds.Reset(InSize);
					
					for (int32 I = 0; I < InSize; ++I)
					{
						InitialSpeeds.Add(0.0f);
						MaxSpeeds.Add(0.0f);
						GravityScales.Add(0.0f);
						Directions.Add(FVector::ZeroVector);
						Direction3fs.Add(FVector3f::ZeroVector);
						Velocities.Add(FVector::ZeroVector);
						Velocity3fs.Add(FVector3f::ZeroVector);
						Speeds.Add(0.0f);
					}
				}

				void Update(const FCsDeltaTime& DeltaTime);
			};

			FMovementInfos MovementInfos;

			struct FTrackingInfos
			{
				friend struct NCsProjectile::NVariables::FManager;

			private:

				using TrackingStateType = NCsProjectile::NTracking::EState;
				using DestinationType = NCsProjectile::NTracking::EDestination;

			private:

				NCsProjectile::NVariables::FManager* Outer;

			public:

				int32 DelayCount;

				TArray<int32> DelayIDs;

				TArray<float> Delays;

				int32 ActiveCount;

				TArray<int32> ActiveIDs;

				TArray<TrackingStateType> States;

				TArray<DestinationType> DestinationTypes;

				TArray<uint32> DestinationMasks;

				TArray<USceneComponent*> Components;

				TArray<USkeletalMeshComponent*> MeshComponents;

				TArray<FName> Bones;

				TArray<int32> TargetIDs;

				TArray<float> Durations;

				TArray<float> ElapsedTimes;

				TArray<FVector> Destinations;
				TArray<FVector3f> Destination3fs;

				TArray<FVector> Offsets;
				TArray<FVector3f> Offset3fs;

				TArray<float> MinDotThresholds;

				TArray<float> MaxDotBeforeUsingPitches;

				TArray<float> RotationRates;

				FTrackingInfos() :
					Outer(nullptr),
					DelayCount(0),
					DelayIDs(),
					Delays(),
					ActiveCount(0),
					ActiveIDs(),
					States(),
					DestinationTypes(),
					DestinationMasks(),
					Components(),
					MeshComponents(),
					Bones(),
					TargetIDs(),
					Durations(),
					ElapsedTimes(),
					Destinations(),
					Offsets(),
					MinDotThresholds(),
					MaxDotBeforeUsingPitches(),
					RotationRates()
				{
				}

				void SetSize(const int32& InSize)
				{
					DelayIDs.Reset(InSize);
					Delays.Reset(InSize);
					ActiveIDs.Reset(InSize);
					States.Reset(InSize);
					DestinationTypes.Reset(InSize);
					DestinationMasks.Reset(InSize);
					Components.Reset(InSize);
					MeshComponents.Reset(InSize);
					Bones.Reset(InSize);
					TargetIDs.Reset(InSize);
					Durations.Reset(InSize);
					ElapsedTimes.Reset(InSize);
					Destinations.Reset(InSize);
					Destination3fs.Reset(InSize);
					Offsets.Reset(InSize);
					Offset3fs.Reset(InSize);
					MinDotThresholds.Reset(InSize);
					MaxDotBeforeUsingPitches.Reset(InSize);
					RotationRates.Reset(InSize);

					for (int32 I = 0; I < InSize; ++I)
					{
						DelayIDs.Add(INDEX_NONE);
						Delays.Add(0.0f);
						ActiveIDs.Add(INDEX_NONE);
						States.Add(TrackingStateType::Inactive);
						DestinationTypes.Add(DestinationType::Custom);
						DestinationMasks.Add(0);
						Components.Add(nullptr);
						MeshComponents.Add(nullptr);
						Bones.Add(NAME_None);
						TargetIDs.Add(INDEX_NONE);
						Durations.Add(0.0f);
						ElapsedTimes.Add(0.0f);
						Destinations.Add(FVector::ZeroVector);
						Destination3fs.Add(FVector3f::ZeroVector);
						Offsets.Add(FVector::ZeroVector);
						Offset3fs.Add(FVector3f::ZeroVector);
						MinDotThresholds.Add(0.0f);
						MaxDotBeforeUsingPitches.Add(0.0f);
						RotationRates.Add(0.0f);
					}
				}

				void SetupIDs(const int32& ID);

				void Update(const FCsDeltaTime& DeltaTime);

				FORCEINLINE void Reset(const int32& Index)
				{
					States[Index] = TrackingStateType::Inactive;
					DelayIDs[Index]	   = INDEX_NONE;
					Delays[Index]	   = 0.0f;
					ActiveIDs[Index]   = INDEX_NONE;
					States[Index]	   = TrackingStateType::Inactive;
					DestinationTypes[Index] = DestinationType::Custom;
					DestinationMasks[Index] = 0;
					Components[Index] = nullptr;
					MeshComponents[Index] = nullptr;
					Bones[Index] = NAME_None;
					TargetIDs[Index] = INDEX_NONE;
					Durations[Index]   = 0.0f;
					ElapsedTimes[Index] = 0.0f;
					Destinations[Index] = FVector::ZeroVector;
					Destination3fs[Index] = FVector3f::ZeroVector;
					Offsets[Index]		= FVector::ZeroVector;
					Offset3fs[Index]		= FVector3f::ZeroVector;
					MinDotThresholds[Index] = 0.0f;
					MaxDotBeforeUsingPitches[Index] = 0.0f;
					RotationRates[Index] = 0.0f;
				}
			};

			FTrackingInfos TrackingInfos;

		// Collision

			struct FCollisionInfos
			{
				friend struct NCsProjectile::NVariables::FManager;

			private:

				NCsProjectile::NVariables::FManager* Outer;

			public:

				TArray<uint8> Channels;

				TArray<uint32> BlockMasks;

				TArray<float> Radii;

				TArray<float> HalfHeights;

				TArray<int32> HitCounts;

				DECLARE_DELEGATE_OneParam(FUpdateImpl, const FCsDeltaTime& DeltaTime);

				FUpdateImpl UpdateImpl;

				FCollisionInfos() :
					Outer(nullptr),
					Channels(),
					BlockMasks(),
					Radii(),
					HalfHeights(),
					HitCounts(),
					UpdateImpl()
				{
				}

				void SetSize(const int32& InSize)
				{
					Channels.Reset(InSize);
					BlockMasks.Reset(InSize);
					Radii.Reset(InSize);
					HalfHeights.Reset(InSize);
					HitCounts.Reset(InSize);

					for (int32 I = 0; I < InSize; ++I)
					{
						Channels.Add(0);
						BlockMasks.Add(0);
						Radii.Add(0.0f);
						HalfHeights.Add(0.0f);
						HitCounts.Add(0);
					}
				}

				void Update(const FCsDeltaTime& DeltaTime);

				FORCEINLINE void Reset(const int32& Index)
				{
					Channels[Index] = 0;
					BlockMasks[Index] = 0;
					HitCounts[Index] = 0;
				}
			};

			FCollisionInfos CollisionInfos;

			BoundsWorldType BoundsWorld;

			DECLARE_DELEGATE_OneParam(FPreUpdateImpl, const FCsDeltaTime& DeltaTime);

			FPreUpdateImpl PreUpdateImpl;

			DECLARE_DELEGATE_OneParam(FSetupIDsImpl, const int32& ID);

			FSetupIDsImpl SetupIDsImpl;

			FManager() :
				Outer(nullptr),
				Projectiles(),
				// IDs
				Manager_ID(),
				AllocatedCount(0),
				AllocatedIDs(),
				Last_DeallocatedIDs(),
				Variables(),
				AliveCount(0),
				AliveIDs(),
				// State
				Types(),
				States(),
				Generations(),
				// Movement
				Last_Locations(),
				Last_Location3fs(),
				Locations(),
				Location3fs(),
				Last_Rotations(),
				Last_Rotation3fs(),
				Rotations(),
				Rotation3fs(),
				Orientations(),
				Orientation4fs(),
				FacingDirections(),
				FacingDirection3fs(),
				MovementInfos(),
				TrackingInfos(),
				CollisionInfos(),
				BoundsWorld(),
				PreUpdateImpl(),
				SetupIDsImpl()
			{
				MovementInfos.Outer = this;
				TrackingInfos.Outer = this;
				CollisionInfos.Outer = this;
			}

			FORCEINLINE void SetOuter(UCsManager_Projectile* InOuter) { Outer = InOuter; }

			FORCEINLINE VariablesType* GetVariablesPtr(const int32& Index) { return &(Variables[Index]); }

			FORCEINLINE const TArray<ICsProjectile*>& GetProjectiles() const { return Projectiles; }

			// Movement
			FORCEINLINE FVector* GetLocationPtr(const int32& Index) { return &(Locations[Index]); }
			FORCEINLINE FVector3f* GetLocation3fPtr(const int32& Index) { return &(Location3fs[Index]); }
			FORCEINLINE FRotator* GetRotationPtr(const int32& Index) { return &(Rotations[Index]); }
			FORCEINLINE FRotator3f* GetRotation3fPtr(const int32& Index) { return &(Rotation3fs[Index]); }
			FORCEINLINE FQuat* GetOrientationPtr(const int32& Index) { return &(Orientations[Index]); }
			FORCEINLINE FQuat4f* GetOrientation4fPtr(const int32& Index) { return &(Orientation4fs[Index]); }

			FORCEINLINE void GetAliveLocations(TArray<int32>*& OutIDs, int32*& OutCount, TArray<FVector3f>*& OutLocations)
			{
				OutIDs		 = &AliveIDs;
				OutCount	 = &AliveCount;
				OutLocations = &Location3fs;
			}

			void SetSize(const int32& InSize)
			{
				Manager_ID.CreatePool(InSize);

				Projectiles.Reset(InSize);
				AllocatedIDs.Reset(InSize);
				Last_DeallocatedIDs.Reset(InSize);
				Variables.Reset(InSize);
				AliveIDs.Reset(InSize);
				Types.Reset(InSize);
				States.Reset(InSize);
				Generations.Reset(InSize);
				Last_Locations.Reset(InSize);
				Last_Location3fs.Reset(InSize);
				Locations.Reset(InSize);
				Location3fs.Reset(InSize);
				Last_Rotations.Reset(InSize);
				Last_Rotation3fs.Reset(InSize);
				Rotations.Reset(InSize);
				Rotation3fs.Reset(InSize);
				Orientations.Reset(InSize);
				Orientation4fs.Reset(InSize);

				typedef NCsResource::NManager::NValue::NFixed::NInt32::FResource ResourceType;

				const TArray<ResourceType*>& Resources = Manager_ID.GetPool();

				for (int32 I = 0; I < InSize; ++I)
				{
					// Manager_ID					
					ResourceType* C = Resources[I];
					int32& ID	= C->GetRef();
					ID			= I;

					Projectiles.Add(nullptr);
					AllocatedIDs.Add(INDEX_NONE);
					Variables.AddDefaulted();
					Variables[I].SetOuter(this);
					AliveIDs.Add(INDEX_NONE);
					Types.Add(EMCsProjectile::Get().GetMAX());
					States.Add(StateType::Inactive);
					Generations.Add(0);
					Last_Locations.Add(FVector::ZeroVector);
					Last_Location3fs.Add(FVector3f::ZeroVector);
					Locations.Add(FVector::ZeroVector);
					Location3fs.Add(FVector3f::ZeroVector);
					Last_Rotations.Add(FRotator::ZeroRotator);
					Last_Rotation3fs.Add(FRotator3f::ZeroRotator);
					Rotations.Add(FRotator::ZeroRotator);
					Rotation3fs.Add(FRotator3f::ZeroRotator);
					Orientations.Add(FQuat::Identity);
					Orientation4fs.Add(FQuat4f::Identity);
				}

				MovementInfos.SetSize(InSize);
				TrackingInfos.SetSize(InSize);
				CollisionInfos.SetSize(InSize);
			}

			void Update(const FCsDeltaTime& DeltaTime);

			FORCEINLINE bool IsValid(const int32& Index) const { return Variables[Index].IsValid(); }
			//FORCEINLINE bool IsAlive(const int32& Index) const { return States[Index] == StateType::Active || States[Index] == StateType::Transforming; }

			VariablesType* AllocateChecked(const FString& Context, const VariablesPayloadType& Payload);

			void DeallocateChecked(const FString& Context, VariablesType* Vars);

			FORCEINLINE void Reset(const int32& Index)
			{
				Variables[Index].Reset();
				Projectiles[Index]	= nullptr;
				States[Index]		= StateType::Inactive;
				Types[Index]		= EMCsProjectile::Get().GetMAX();
				Locations[Index]	= FVector::ZeroVector;
				Location3fs[Index]	= FVector3f::ZeroVector;
				Rotations[Index]	= FRotator::ZeroRotator;
				Rotation3fs[Index]	= FRotator3f::ZeroRotator;
				Orientations[Index] = FQuat::Identity;
				Orientation4fs[Index] = FQuat4f::Identity;
				TrackingInfos.Reset(Index);
				CollisionInfos.Reset(Index);
				Manager_ID.DeallocateAt(Index);
			}
		};
	}
}

#pragma endregion NCsProjectile::NVariables::FManager