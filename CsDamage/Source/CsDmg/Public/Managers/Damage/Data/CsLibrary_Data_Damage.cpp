// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"

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
		#define DataType NCsDamage::NData::IData

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

		bool FLibrary::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

		#define RangeType NCsDamage::NRange::IRange
		
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

		const RangeType* FLibrary::GetSafeRange(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

		#undef RangeType

		bool FLibrary::SafeApplyOrientation(const FString& Context, const DataType* Data, FVector& Origin, FVector& Direction, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL(Data)

			typedef NCsMath::FLibrary MathLibrary;
			typedef NCsDamage::NData::NOrientation::IOrientation OrientationDataType;

			if (const OrientationDataType* OrientationData = GetSafeInterfaceChecked<OrientationDataType>(Context, Data))
			{
				const FVector& Location = OrientationData->GetLocation();

				if (Location != FVector::ZeroVector)
				{
					FVector Right = FVector::ZeroVector;
					FVector Up    = FVector::UpVector;
					MathLibrary::GetRightAndUpFromNormal(Direction, Right, Up);

					Origin += Location.X * Direction + Location.Y * Right + Location.Z + Up;
				}

				const FRotator& Rotation = OrientationData->GetRotation();

				if (Rotation.Yaw != 0.0f)
				{
					Direction = MathLibrary::RotateNormalWorldUp(Direction, Rotation.Yaw);
				}

				if (Rotation.Pitch != 0.0f)
				{
					Direction = MathLibrary::RotateNormalAngleRight(Direction, Rotation.Pitch);
				}
				return true;
			}
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s: does NOT implement the interface: %s."), *Context, *PrintDataAndClass(Data), *(OrientationDataType::Name.ToString())));
			return false;
		}

		#undef DataType
	}
}