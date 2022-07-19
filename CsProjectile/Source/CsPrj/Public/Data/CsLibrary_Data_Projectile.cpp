// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_Data_Projectile.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Data
#include "Data/Launch/CsData_Projectile_Launch.h"
#include "Data/Tracking/CsData_Projectile_Tracking.h"
#include "Data/Collision/CsData_Projectile_Collision.h"
#include "Data/Visual/StaticMesh/CsData_Projectile_VisualStaticMesh.h"
#include "Data/Visual/CsData_Projectile_VisualTrail.h"
//#include "Data/Visual/Impact/CsData_Projectile_VisualImpact.h"
#include "Managers/Damage/Data/Types/CsData_GetDamageDataType.h"

namespace NCsProjectile
{
	namespace NData
	{
		#define DataType NCsProjectile::NData::IData

		FString FLibrary::PrintObjectAndClass(const DataType* Data)
		{
			if (UObject* O = Data->_getUObject())
				return FString::Printf(TEXT("Object: %s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
			return FString::Printf(TEXT("%s (Non-UObject)"), *(Data->GetInterfaceMap()->GetRootName().ToString()));
		}

		FString FLibrary::PrintDataAndClass(const DataType* Data)
		{
			if (UObject* O = Data->_getUObject())
				return FString::Printf(TEXT("Data: %s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
			return FString::Printf(TEXT("%s (Non-UObject)"), *(Data->GetInterfaceMap()->GetRootName().ToString()));
		}

		FString FLibrary::Print(const DataType* Data)
		{
			if (UObject* O = Data->_getUObject())
				return FString::Printf(TEXT("%s"), *(O->GetName()));
			return FString::Printf(TEXT("%s"), *(Data->GetInterfaceMap()->GetRootName().ToString()));
		}

		bool FLibrary::IsValidChecked(const FString& Context, const DataType* Data)
		{
			// Launch
			typedef NCsProjectile::NData::NLaunch::ILaunch LaunchDataType;

			if (const LaunchDataType* LaunchData = GetSafeInterfaceChecked<LaunchDataType>(Context, Data))
			{
				CS_IS_VALID_CHECKED(LaunchData->GetLaunchParams());
			}
			// Tracking
			typedef NCsProjectile::NData::NTracking::ITracking TrackingDataType;

			if (const TrackingDataType* TrackingData = GetSafeInterfaceChecked<TrackingDataType>(Context, Data))
			{
				if (TrackingData->ShouldUseTracking())
				{
					CS_IS_VALID_CHECKED(TrackingData->GetTrackingParams());
				}
			}
			// Collision
			typedef NCsProjectile::NData::NCollision::ICollision CollisionDataType;

			if (const CollisionDataType* CollisionData = GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
			{
				CS_IS_VALID_CHECKED(CollisionData->GetCollisionPreset());
				CS_IS_FLOAT_GREATER_THAN_CHECKED(CollisionData->GetCollisionRadius(), 0.0f)

				const TArray<TSubclassOf<UObject>>& Classes =  CollisionData->GetIgnoreHitObjectClasses();

				const int32 Count = Classes.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const TSubclassOf<UObject>& C = Classes[I];

					checkf(C.Get(), TEXT("%s: %s->GetIgnoreHitObjectClasses()[I] is NULL."), *Context, *Print(Data), I);
				}
			}
			// VisualStaticMesh
			typedef NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshVisualDataType;

			if (const StaticMeshVisualDataType* StaticMeshVisualData = GetSafeInterfaceChecked<StaticMeshVisualDataType>(Context, Data))
			{
				CS_IS_VALID_CHECKED(StaticMeshVisualData->GetStaticMesh());
			}
			// VisualTrail
			typedef NCsProjectile::NData::NVisual::NTrail::ITrail TrailVisualDataType;

			if (const TrailVisualDataType* TrailVisualData = GetSafeInterfaceChecked<TrailVisualDataType>(Context, Data))
			{
				CS_IS_VALID_CHECKED(TrailVisualData->GetTrailFX());
			}
			// Damage
			typedef NCsData::IGetDamageDataType GetDamageDataTypeDataType;

			if (const GetDamageDataTypeDataType* GetDamageDataType = GetSafeInterfaceChecked<GetDamageDataTypeDataType>(Context, Data))
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageData, GetDamageDataType->GetDamageDataType())
			}
			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			// Launch
			typedef NCsProjectile::NData::NLaunch::ILaunch LaunchDataType;

			if (const LaunchDataType* LaunchData = GetSafeInterfaceChecked<LaunchDataType>(Context, Data))
			{
				CS_IS_VALID(LaunchData->GetLaunchParams())
			}
			// Tracking
			typedef NCsProjectile::NData::NTracking::ITracking TrackingDataType;

			if (const TrackingDataType* TrackingData = GetSafeInterfaceChecked<TrackingDataType>(Context, Data))
			{
				if (TrackingData->ShouldUseTracking())
				{
					CS_IS_VALID(TrackingData->GetTrackingParams())
				}
			}
			// Collision
			typedef NCsProjectile::NData::NCollision::ICollision CollisionDataType;

			if (const CollisionDataType* CollisionData = GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
			{
				CS_IS_VALID(CollisionData->GetCollisionPreset())
				CS_IS_FLOAT_GREATER_THAN(CollisionData->GetCollisionRadius(), 0.0f)

				const TArray<TSubclassOf<UObject>>& Classes =  CollisionData->GetIgnoreHitObjectClasses();

				const int32 Count = Classes.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const TSubclassOf<UObject>& C = Classes[I];

					if (!C.Get())
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s->GetIgnoreHitObjectClasses()[I] is NULL."), *Context, *Print(Data), I));
						return false;
					}
				}
			}
			// VisualStaticMesh
			typedef NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshVisualDataType;

			if (const StaticMeshVisualDataType* StaticMeshVisualData = GetSafeInterfaceChecked<StaticMeshVisualDataType>(Context, Data))
			{
				CS_IS_VALID(StaticMeshVisualData->GetStaticMesh())
			}
			// VisualTrail
			typedef NCsProjectile::NData::NVisual::NTrail::ITrail TrailVisualDataType;

			if (const TrailVisualDataType* TrailVisualData = GetSafeInterfaceChecked<TrailVisualDataType>(Context, Data))
			{
				CS_IS_VALID(TrailVisualData->GetTrailFX())
			}
			// Damage
			typedef NCsData::IGetDamageDataType GetDamageDataTypeDataType;

			if (const GetDamageDataTypeDataType* GetDamageDataType = GetSafeInterfaceChecked<GetDamageDataTypeDataType>(Context, Data))
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsDamageData, FECsDamageData, GetDamageDataType->GetDamageDataType())
			}
			return true;
		}

		#undef DataType
	}
}