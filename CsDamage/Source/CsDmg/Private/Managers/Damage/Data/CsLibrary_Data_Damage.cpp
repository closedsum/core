// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "Managers/Damage/Data/Orientation/CsData_DamageOrientation.h"
#include "Managers/Damage/Data/Collision/CsData_DamageCollision.h"

namespace NCsDamage
{
	namespace NData
	{
		namespace NLibrary
		{
			using RangeType = NCsDamage::NRange::IRange;

			#define LogLevel void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/

			FString FLibrary::PrintDataAndClass(const DataType* Data)
			{
				if (UObject* O = Data->_getUObject())
					return FString::Printf(TEXT("Data: %s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("Data: %s (Non-UObject)"), *(Data->GetInterfaceMap()->GetRootName().ToString()));
			}

			bool FLibrary::IsValidChecked(const FString& Context, const DataType* Data)
			{
				CS_IS_PTR_NULL_CHECKED(Data)
				CS_IS_PTR_NULL_CHECKED(Data->GetValue())

				// CollisionDataType (NCsDamage::NData::NCollision::ICollision)
				{
					typedef NCsDamage::NData::NCollision::ICollision CollisionDataType;

					if (const CollisionDataType* CollisionData = GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
					{
						CS_IS_VALID_CHECKED(CollisionData->GetCollisionInfo());
					}
				}
				return true;
			}

			bool FLibrary::IsValid(const FString& Context, const DataType* Data, LogLevel)
			{
				CS_IS_PTR_NULL(Data)
				CS_IS_PTR_NULL(Data->GetValue())

				// CollisionDataType (NCsDamage::NData::NCollision::ICollision)
				{
					typedef NCsDamage::NData::NCollision::ICollision CollisionDataType;

					if (const CollisionDataType* CollisionData = GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
					{
						CS_IS_VALID(CollisionData->GetCollisionInfo())
					}
				}
				return true;
			}
		
			const RangeType* FLibrary::GetRangeChecked(const FString& Context, const DataType* Data)
			{
				CS_IS_PTR_NULL_CHECKED(Data)

				// ShapeDataType (NCsDamage::NData::NShape::IShape)
				{
					typedef NCsDamage::NData::NShape::IShape ShapeDataType;

					if (const ShapeDataType* Shape = GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
					{
						return Shape->GetRange();
					}
				}
				checkf(0, TEXT("%s: Failed to get RangeType (NCsDamage::NRange::IRange) from Data."), *Context);
				return nullptr;
			}

			const RangeType* FLibrary::GetSafeRange(const FString& Context, const DataType* Data, LogLevel)
			{
				CS_IS_PTR_NULL_RET_NULL(Data)

				// ShapeDataType (NCsDamage::NData::NShape::IShape)
				{
					typedef NCsDamage::NData::NShape::IShape ShapeDataType;

					if (const ShapeDataType* Shape = GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
					{
						return Shape->GetRange();
					}
				}
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get RangeType (NCsDamage::NRange::IRange) from Data."), *Context));
				return nullptr;
			}

			bool FLibrary::SafeApplyOrientation(const FString& Context, const DataType* Data, FVector3f& Origin, FVector3f& Direction, LogLevel)
			{
				CS_IS_PTR_NULL(Data)

				typedef NCsDamage::NData::NOrientation::IOrientation OrientationDataType;

				if (const OrientationDataType* OrientationData = GetSafeInterfaceChecked<OrientationDataType>(Context, Data))
				{
					const FVector3f& Location = OrientationData->GetLocation();

					if (Location != FVector3f::ZeroVector)
					{
						FVector3f Right = FVector3f::ZeroVector;
						FVector3f Up    = FVector3f::UpVector;
						CsMathLibrary::GetRightAndUpFromNormal(Direction, Right, Up);

						Origin += Location.X * Direction + Location.Y * Right + Location.Z + Up;
					}

					const FRotator3f& Rotation = OrientationData->GetRotation();

					if (Rotation.Yaw != 0.0f)
					{
						Direction = CsMathLibrary::RotateNormalWorldUp(Direction, Rotation.Yaw);
					}

					if (Rotation.Pitch != 0.0f)
					{
						Direction = CsMathLibrary::RotateNormalAngleRight(Direction, Rotation.Pitch);
					}
					return true;
				}
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s: does NOT implement the interface: %s."), *Context, *PrintDataAndClass(Data), *(OrientationDataType::Name.ToString())));
				return false;
			}

			#undef LogLevel
		}
	}
}