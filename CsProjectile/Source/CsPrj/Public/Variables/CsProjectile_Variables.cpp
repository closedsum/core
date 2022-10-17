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

		void FManager::FTrackingInfos::Update(const FCsDeltaTime& DeltaTime)
		{
			using namespace NCsProjectile::NVariables::NManager::NTrackingInfos::NCached;

			const FString& Context = Str::Update;

			typedef NCsMath::FLibrary MathLibrary;

			// FManager = Outer
		}

		void FManager::Update(const FCsDeltaTime& DeltaTime)
		{
			typedef NCsResource::NManager::NValue::NFixed::NInt32::FResource ResourceType;

			TCsDoubleLinkedList<ResourceType*>* Current = Manager_ID.GetAllocatedHead();
			TCsDoubleLinkedList<ResourceType*>* Next	= Current;

			// State
			int32 AllocatedCount = 0;
			AliveCount = 0;

			while (Next)
			{
				Current			= Next;
				ResourceType* C = **Current;
				Next			= Current->GetNextLink();

				int32& ID = C->GetRef();

				AllocatedIDs[AllocatedCount] = ID;

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
		}
	}
}

#pragma endregion NCsProjectile::NVariables::FManager