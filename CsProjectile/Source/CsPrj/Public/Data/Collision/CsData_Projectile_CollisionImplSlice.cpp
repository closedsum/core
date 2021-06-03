// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Collision/CsData_Projectile_CollisionImplSlice.h"

// Library
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Managers/Projectile/Handler/CsManager_Projectile_DataHandler.h"

#define SliceType NCsProjectile::NData::NCollision::FImplSlice

#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
#define CS_TEMP_ADD_SAFE_SLICE \
	typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary; \
	typedef NCsProjectile::NData::IData DataType; \
	typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType; \
	\
	DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = PrjManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log); \
	\
	if (!DataHandler) \
		return nullptr; \
	\
	typedef NCsProjectile::NData::NCollision::ICollision CollisionDataType; \
	\
	SliceType* Slice = DataHandler->AddSafeDataSlice<SliceType, CollisionDataType>(Context, Name); \
	\
	if (!Slice) \
		return nullptr;

SliceType* FCsData_Projectile_CollisionImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
{
	CS_TEMP_ADD_SAFE_SLICE

	CopyToSlice(Slice);

	return nullptr;
}

SliceType* FCsData_Projectile_CollisionImplSlice::AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_TEMP_ADD_SAFE_SLICE

	CopyToSliceAsValue(Slice);

	return nullptr;
}

#undef DataHandlerType
#undef CS_TEMP_GET_DATA_HANDLER

void FCsData_Projectile_CollisionImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetCollisionPreset(&Preset);
	Slice->SetCollisionRadius(&Radius);
}

void FCsData_Projectile_CollisionImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetCollisionPreset(Preset);
	Slice->SetCollisionRadius(Radius);
}

#undef SliceType

bool FCsData_Projectile_CollisionImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	// TODO: Add Check for Preset

	CS_IS_FLOAT_GREATER_THAN(Radius, 0.0f)
	return true;
}

const FName NCsProjectile::NData::NCollision::FImplSlice::Name = FName("NCsProjectile::NData::NCollision::FImplSlice");

namespace NCsProjectile
{
	namespace NData
	{
		namespace NCollision
		{
			namespace NImplSlice
			{
				namespace NCached
				{
					namespace Name
					{
						const FName VisualStaticMeshSlice = FName("CollisionSlice");

						const FName CollisionPreset = FName("CollisionPreset");
						const FName CollisionRadius = FName("CollisionRadius");
					}
				}
			}

			/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
			{
				using namespace NCsProjectile::NData::NCollision::NImplSlice::NCached;

				CS_IS_PTR_NULL_RET_NULL(Object)

				#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
				typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;
				typedef NCsProjectile::NData::IData DataType;
				typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType;

				DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = PrjManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
				
				#undef DataHandlerType

				if (!DataHandler)
					return nullptr;

				typedef NCsProjectile::NData::NCollision::ICollision CollisionDataType;

				FImplSlice* Slice = DataHandler->AddSafeDataSlice<FImplSlice, CollisionDataType>(Context, DataName);

				if (!Slice)
					return nullptr;

				// Check for properties matching interface: ProjectileDataType (NCsProjectile::NData::IData)
				typedef NCsProperty::FLibrary PropertyLibrary;

				bool Success = false;

				// Try FCsData_Projectile_CollisionImplSlice
				typedef FCsData_Projectile_CollisionImplSlice StructSliceType;

				if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::VisualStaticMeshSlice, nullptr))
				{
					SliceAsStruct->CopyToSlice(Slice);
					Success = true;
				}
				// Try individual properties
				else
				{
					FCsCollisionPreset* CollisionPresetPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsCollisionPreset>(Context, Object, Object->GetClass(), Name::CollisionPreset, nullptr);
					float* CollisionRadiusPtr			   = PropertyLibrary::GetFloatPropertyValuePtr(Context, Object, Object->GetClass(), Name::CollisionRadius, nullptr);

					if (CollisionPresetPtr &&
						CollisionRadiusPtr)
					{
						Slice->SetCollisionPreset(CollisionPresetPtr);
						Slice->SetCollisionRadius(CollisionRadiusPtr);
						Success = true;
					}
				}

				if (!Success)
				{
					if (Log)
					{
						typedef NCsObject::FLibrary ObjectLibrary;

						Log(FString::Printf(TEXT("%s: Failed to find any properties from %s for interface: NCsProjectile::NData::NCollision::ICollision."), *(ObjectLibrary::PrintObjectAndClass(Object))));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Projectile_CollisionImplSlice with name: CollisionSlice.")));
						Log(FString::Printf(TEXT("%s: - OR")));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsCollisionPreset with name: CollisionPreset.")));
						Log(FString::Printf(TEXT("%s: - Failed to get float property with name: CollisionRadius.")));
					}
				}
				return Slice;
			}

			bool FImplSlice::IsValidChecked(const FString& Context) const
			{
				// TODO: Add Check for Preset

				CS_IS_FLOAT_GREATER_THAN_CHECKED(CollisionRadius, 0.0f)
				return true;
			}

			bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&)/*=&NCsProjectile::FLog::Warning*/) const
			{
				// TODO: Add Check for Preset

				CS_IS_FLOAT_GREATER_THAN(CollisionRadius, 0.0f)
				return true;
			}
		}
	}
}