// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_Data_Beam.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Data
#include "Data/Collision/CsData_Beam_Collision.h"
// Beam
#include "Collision/CsBeam_CollisionShape.h"

namespace NCsBeam
{
	namespace NData
	{
		#define DataType NCsBeam::NData::IData

		bool FLibrary::IsValidChecked(const FString& Context, const DataType* Data)
		{
			// CollisionDataType
			typedef NCsBeam::NData::NCollision::ICollision CollisionDataType;

			if (const CollisionDataType* CollisionData = GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
			{
				CS_IS_VALID_CHECKED(CollisionData->GetCollisionPreset());

				check(CollisionData->GetCollisionShape()->IsValidChecked(Context));

				CS_IS_VALID_CHECKED(CollisionData->GetCollisionFrequencyParams());

				CS_IS_INT_GREATER_THAN_CHECKED(CollisionData->GetCollisionCount(), 0)
			}
			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
		{
			// CollisionDataType
			typedef NCsBeam::NData::NCollision::ICollision CollisionDataType;

			if (const CollisionDataType* CollisionData = GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
			{
				CS_IS_VALID(CollisionData->GetCollisionPreset());

				if (!CollisionData->GetCollisionShape()->IsValid(Context, Log))
					return false;

				CS_IS_VALID(CollisionData->GetCollisionFrequencyParams());

				CS_IS_INT_GREATER_THAN(CollisionData->GetCollisionCount(), 0)
			}
			return true;
		}

		#undef DataType
	}
}