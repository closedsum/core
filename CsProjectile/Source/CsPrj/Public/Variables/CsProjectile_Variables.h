// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Projectile.h"
#include "Managers/Time/CsTypes_Time.h"
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Fixed_Int32.h"
// Containers
#include "Containers/CsLooseCoarseGrid.h"

class ICsProjectile;
class USceneComponent;

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

				float CollisionRadius;

				FPayload() :
					Projectile(nullptr),
					Type(),
					Location(0.0f),
					CollisionRadius(0.0f)
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

			NCsProjectile::NVariables::FManager* Outer;

		public:

			int32 ID;

			struct FTrackingInfo
			{
				friend struct NCsProjectile::NVariables::FVariables;

			private:

				NCsProjectile::NVariables::FVariables* Outer;

			public:

				FTrackingInfo() :
					Outer(nullptr)
				{
				}

				FORCEINLINE void SetOuter(NCsProjectile::NVariables::FVariables* InOuter) { Outer = InOuter; }
				FORCEINLINE NCsProjectile::NVariables::FVariables* GetOuter() { return Outer; }
				FORCEINLINE NCsProjectile::NVariables::FManager* GetOuterMost() { return Outer->GetOuter(); }
				FORCEINLINE const NCsProjectile::NVariables::FManager* GetOuterMost() const { return Outer->GetOuter(); }

				FORCEINLINE const int32& GetID() const { return Outer->GetID(); }

				void Reset()
				{
				}
			};

			FTrackingInfo TrackingInfo;

			FVariables() :
				Outer(nullptr),
				ID(INDEX_NONE),
				TrackingInfo()
			{
				TrackingInfo.Outer = this;
			}

			FORCEINLINE void SetOuter(NCsProjectile::NVariables::FManager* InOuter) 
			{
				Outer = InOuter;
				TrackingInfo.SetOuter(this);
			}
			FORCEINLINE NCsProjectile::NVariables::FManager* GetOuter() { return Outer; }

			FORCEINLINE const int32& GetID() const { return ID; }

			const FVector& GetLastLocation() const;
			FVector& GetLastLocation();
			const FVector& GetLocation() const;
			FVector& GetLocation();
			const FRotator& GetRotation() const;
			FRotator& GetRotation();
			const FQuat& GetOrientation() const;
			FQuat& GetOrientation();

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

// NCCharacter::NVariables::FManager
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

		#define IDManagerType NCsResource::NManager::NValue::NFixed::NInt32::FManager
		#define VariablesType NCsProjectile::NVariables::FVariables

		private:

			UCsManager_Projectile* Outer;

		public:

			TArray<ICsProjectile*> Projectiles;

		// IDs

			IDManagerType Manager_ID;

			TArray<int32> AllocatedIDs;

			TArray<int32> Last_DeallocatedIDs;

			TArray<VariablesType> Variables;

			int32 AliveCount;

			TArray<int32> AliveIDs;

		// State

			TArray<FECsProjectile> Types;

			TArray<FVector> Last_Locations;
			TArray<FVector> Locations;

			TArray<FRotator> Rotations;
			TArray<FQuat> Orientations;

			struct FTrackingInfos
			{
				friend struct NCsProjectile::NVariables::FManager;

			private:

				NCsProjectile::NVariables::FManager* Outer;

			public:

				FTrackingInfos() :
					Outer(nullptr)
				{
				}

				void SetSize(const int32& InSize)
				{
					for (int32 I = 0; I < InSize; ++I)
					{
					}
				}

				void Update(const FCsDeltaTime& DeltaTime);

				FORCEINLINE void Reset(const int32& Index)
				{
				}
			};

			FTrackingInfos TrackingInfos;

			NCsLooseCoarseGrid::FGrid LooseCoarseGrid;

			FManager() :
				Outer(nullptr),
				Projectiles(),
				// IDs
				Manager_ID(),
				AllocatedIDs(),
				Last_DeallocatedIDs(),
				Variables(),
				AliveCount(0),
				AliveIDs(),
				// State
				Types(),
				// Movement
				Last_Locations(),
				Locations(),
				Rotations(),
				Orientations(),
				TrackingInfos()
			{
				TrackingInfos.Outer = this;
			}

			FORCEINLINE void SetOuter(UCsManager_Projectile* InOuter) { Outer = InOuter; }

			FORCEINLINE VariablesType* GetVariablesPtr(const int32& Index) { return &(Variables[Index]); }

			FORCEINLINE const TArray<ICsProjectile*>& GetProjectiles() const { return Projectiles; }

			// Movement
			FORCEINLINE FVector* GetLocationPtr(const int32& Index) { return &(Locations[Index]); }
			FORCEINLINE FRotator* GetRotationPtr(const int32& Index) { return &(Rotations[Index]); }
			FORCEINLINE FQuat* GetOrientationPtr(const int32& Index) { return &(Orientations[Index]); }

			FORCEINLINE void GetAliveLocations(TArray<int32>*& OutIDs, int32*& OutCount, TArray<FVector>*& OutLocations)
			{
				OutIDs		 = &AliveIDs;
				OutCount	 = &AliveCount;
				OutLocations = &Locations;
			}

			void SetSize(const int32& InSize)
			{
				Manager_ID.CreatePool(InSize);

				Projectiles.Reset(InSize);
				AllocatedIDs.Reset(InSize);
				Last_DeallocatedIDs.Reset(InSize);
				AliveIDs.Reset(InSize);
				Types.Reset(InSize);
				Last_Locations.Reset(InSize);
				Locations.Reset(InSize);
				Rotations.Reset(InSize);
				Orientations.Reset(InSize);

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
					AliveIDs.Add(INDEX_NONE);
					Types.Add(EMCsProjectile::Get().GetMAX());
					Last_Locations.Add(FVector::ZeroVector);
					Locations.Add(FVector::ZeroVector);
					Rotations.Add(FRotator::ZeroRotator);
					Orientations.Add(FQuat::Identity);
				}

				for (int32 I = 0; I < InSize; ++I)
				{
					Variables[I].SetOuter(this);
				}

				TrackingInfos.SetSize(InSize);
			}

			void Update(const FCsDeltaTime& DeltaTime);

			FORCEINLINE bool IsValid(const int32& Index) const { return Variables[Index].IsValid(); }
			//FORCEINLINE bool IsAlive(const int32& Index) const { return States[Index] == StateType::Active || States[Index] == StateType::Transforming; }

			FORCEINLINE void Reset(const int32& Index)
			{
				Variables[Index].Reset();
				Projectiles[Index]	= nullptr;
				Types[Index]		= EMCsProjectile::Get().GetMAX();
				Locations[Index]	= FVector::ZeroVector;
				Rotations[Index]	= FRotator::ZeroRotator;
				Orientations[Index] = FQuat::Identity;
				TrackingInfos.Reset(Index);
				Manager_ID.DeallocateAt(Index);
			}

		#undef IDManagerType
		#undef VariablesType
		};
	}
}

#pragma endregion NCsProjectile::NVariables::FManager