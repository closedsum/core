// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileImplSlice.h"

// Library
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Managers/Projectile/Handler/CsManager_Projectile_DataHandler.h"

#define SliceType NCsProjectile::NData::FImplSlice

SliceType* FCsData_ProjectileImplSlice::SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
{
	SliceType* Slice = SafeConstruct_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSlice(Slice);

	// TODO: Eventually store copy of slice on a UObject.

	return Slice;
}

SliceType* FCsData_ProjectileImplSlice::SafeConstructAsValue(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	SliceType* Slice = SafeConstruct_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSliceAsValue(Slice);

	// TODO: Eventually store copy of slice on a UObject.

	return Slice;
}

SliceType* FCsData_ProjectileImplSlice::SafeConstruct_Internal(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return nullptr;

	#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
	typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;
	typedef NCsProjectile::NData::IData DataType;
	typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType;
	
	DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = PrjManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
	
	#undef DataHandlerType

	if (!DataHandler)
		return nullptr;

	SliceType* Slice = DataHandler->SafeConstructData<SliceType, EMCsProjectile>(Context, Name);

	return Slice;
}

void FCsData_ProjectileImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetLifeTime(&LifeTime);
	Slice->SetInitialSpeed(&InitialSpeed);
	Slice->SetMaxSpeed(&MaxSpeed);
	Slice->SetGravityScale(&GravityScale);
}

void FCsData_ProjectileImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetLifeTime(LifeTime);
	Slice->SetInitialSpeed(InitialSpeed);
	Slice->SetMaxSpeed(MaxSpeed);
	Slice->SetGravityScale(GravityScale);
}

#undef SliceType

bool FCsData_ProjectileImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (MaxSpeed > 0.0f)
	{
		CS_IS_FLOAT_GREATER_THAN(LifeTime, 0.0f)

		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(InitialSpeed, 0.0f)
	}

	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GravityScale, 0.0f)
	return true;
}

const FName NCsProjectile::NData::FImplSlice::Name = FName("NCsProjectile::NData::FImplSlice");

namespace NCsProjectile
{
	namespace NData
	{
		namespace NImplSlice
		{
			namespace NCached
			{
				namespace Name
				{
					const FName ProjectileSlice = FName("ProjectileSlice");

					const FName LifeTime = FName("LifeTime");
					const FName InitialSpeed = FName("InitialSpeed");
					const FName MaxSpeed = FName("MaxSpeed");
					const FName GravityScale = FName("GravityScale");
				}
			}
		}

		#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
		#define CS_TEMP_GET_SAFE_DATA_HANDLER \
			typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary; \
			typedef NCsProjectile::NData::IData DataType; \
			typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType; \
			\
			DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = PrjManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log); \
			\
			if (!DataHandler) \
				return nullptr;

		/*static*/ FImplSlice* FImplSlice::SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			using namespace NCsProjectile::NData::NImplSlice::NCached;

			CS_IS_PTR_NULL_RET_NULL(Object)

			#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
			typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;
			typedef NCsProjectile::NData::IData DataType;
			typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType;
			
			DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = PrjManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
			
			#undef DataHandlerType

			if (!DataHandler)
				return nullptr;

			FImplSlice* Slice = DataHandler->SafeConstructData<FImplSlice, EMCsProjectile>(Context, DataName);

			if (!Slice)
				return nullptr;

			// Check for properties matching interface: ProjectileDataType (NCsProjectile::NData::IData)
			typedef NCsProperty::FLibrary PropertyLibrary;

			bool Success = false;

			// Try FCsData_ProjectileImplSlice
			if (FCsData_ProjectileImplSlice* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<FCsData_ProjectileImplSlice>(Context, Object, Object->GetClass(), Name::ProjectileSlice, nullptr))
			{
				SliceAsStruct->CopyToSlice(Slice);
				Success = true;
			}
			// Try individual properties
			else
			{
				#define CS_TEMP_GET_SAFE_FLOAT_PTR(__PropertyName) PropertyLibrary::GetFloatPropertyValuePtr(Context, Object, Object->GetClass(), Name::__PropertyName, nullptr)

				float* LifeTimePtr		= CS_TEMP_GET_SAFE_FLOAT_PTR(LifeTime);
				float* InitialSpeedPtr  = CS_TEMP_GET_SAFE_FLOAT_PTR(InitialSpeed);
				float* MaxSpeedPtr		= CS_TEMP_GET_SAFE_FLOAT_PTR(MaxSpeed);
				float* GravityScalePtr	= CS_TEMP_GET_SAFE_FLOAT_PTR(GravityScale);

				#undef CS_TEMP_GET_SAFE_FLOAT_PTR

				if (LifeTimePtr &&
					InitialSpeedPtr &&
					MaxSpeedPtr &&
					GravityScalePtr)
				{
					Slice->SetLifeTime(LifeTimePtr);
					Slice->SetInitialSpeed(InitialSpeedPtr);
					Slice->SetMaxSpeed(MaxSpeedPtr);
					Slice->SetGravityScale(GravityScalePtr);
					Success = true;
				}
			}

			if (!Success)
			{
				if (Log)
				{
					Log(FString::Printf(TEXT("%s: Failed to find any properties from Object: %s with Class: %s for interface: NCsProjectile::NData::IData.")));
					Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_ProjectileImplSlice with name: ProjectileSlice.")));
					Log(FString::Printf(TEXT("%s: - OR")));
					Log(FString::Printf(TEXT("%s: - Failed to get float property with name: LifeTime.")));
					Log(FString::Printf(TEXT("%s: - Failed to get float property with name: InitialSpeed.")));
					Log(FString::Printf(TEXT("%s: - Failed to get float property with name: MaxSpeed.")));
					Log(FString::Printf(TEXT("%s: - Failed to get float property with name: GravityScale.")));
				}
			}

			// TODO: Eventually store reference to UObject.

			return Slice;
		}

		bool FImplSlice::IsValidChecked(const FString& Context) const
		{
			if (GetMaxSpeed() > 0.0f)
			{
				CS_IS_FLOAT_GREATER_THAN_CHECKED(GetLifeTime(), 0.0f)

				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetInitialSpeed(), 0.0f)
			}

			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetGravityScale(), 0.0f)
			return true;
		}

		bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
		{
			if (GetMaxSpeed() > 0.0f)
			{
				CS_IS_FLOAT_GREATER_THAN(GetLifeTime(), 0.0f)

				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetInitialSpeed(), 0.0f)
			}

			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetGravityScale(), 0.0f)
			return true;
		}
	}
}