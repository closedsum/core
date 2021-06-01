// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/CsData_ProjectileWeaponImplSlice.h"

// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Weapon
#include "Managers/Weapon/Handler/CsManager_Weapon_DataHandler.h"
// Params
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_LaunchTraceImpl.h"

#define SliceType NCsWeapon::NProjectile::NData::FImplSlice

SliceType* FCsData_ProjectileWeaponImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSlice(Slice);

	return nullptr;
}

SliceType* FCsData_ProjectileWeaponImplSlice::AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSliceAsValue(Slice);

	return nullptr;
}

SliceType* FCsData_ProjectileWeaponImplSlice::AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return nullptr;

	#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
	typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
	typedef NCsWeapon::NData::IData DataType;
	typedef NCsWeapon::NData::FInterfaceMap DataInterfaceMapType;
	
	DataHandlerType<DataType, FCsData_WeaponPtr, DataInterfaceMapType>* DataHandler = WeaponManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
	
	if (!DataHandler)
		return nullptr;
	
	typedef NCsWeapon::NProjectile::NData::IData PrjWeaponDataType;
	
	SliceType* Slice = DataHandler->AddSafeDataSlice<SliceType, PrjWeaponDataType>(Context, Name);
	
	return Slice;
}

void FCsData_ProjectileWeaponImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetDoFireOnRelease(&bDoFireOnRelease);
	Slice->SetFullAuto(&bFullAuto);
	Slice->SetInfiniteAmmo(&bInfiniteAmmo);
	Slice->SetMaxAmmo(&MaxAmmo);
	Slice->SetProjectilesPerShot(&ProjectilesPerShot);
	Slice->SetTimeBetweenShots(&TimeBetweenShots);
	Slice->SetTimeBetweenAutoShots(&TimeBetweenAutoShots);
	Slice->SetTimeBetweenProjectilesPerShot(&TimeBetweenProjectilesPerShot);
}

void FCsData_ProjectileWeaponImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetDoFireOnRelease(bDoFireOnRelease);
	Slice->SetFullAuto(bFullAuto);
	Slice->SetInfiniteAmmo(bInfiniteAmmo);
	Slice->SetMaxAmmo(MaxAmmo);
	Slice->SetProjectilesPerShot(ProjectilesPerShot);
	Slice->SetTimeBetweenShots(TimeBetweenShots);
	Slice->SetTimeBetweenAutoShots(TimeBetweenAutoShots);
	Slice->SetTimeBetweenProjectilesPerShot(TimeBetweenProjectilesPerShot);
}

#undef SliceType

bool FCsData_ProjectileWeaponImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	// Check MaxAmmo is a valid value
	if (!bInfiniteAmmo)
	{
		CS_IS_INT_GREATER_THAN(MaxAmmo, 0)
	}
	// Check TimeBetweenShots > 0.0f
	CS_IS_FLOAT_GREATER_THAN(TimeBetweenShots, 0.0f)
	// Check ProjectilesPerShot >= 1
	CS_IS_INT_GREATER_THAN_OR_EQUAL(ProjectilesPerShot, 1)
	// Check TimeBetweenProjectilesPerShot is valid when ProjectilesPerShot > 1
	if (ProjectilesPerShot > 1)
	{
		if (TimeBetweenProjectilesPerShot <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TimeBetweenProjectilesPerShot must be > 0.0f when ProjectilesPerShot > 1."), *Context));
			return false;
		}
	}
	return true;
}

const FName NCsWeapon::NProjectile::NData::FImplSlice::Name = FName("NCsWeapon::NProjectile::NData::FImplSlice");

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			namespace NImplSlice
			{
				namespace NCached
				{
					namespace Name
					{
						const FName ProjectileWeaponSlice = FName("ProjectileWeaponSlice");

						const FName bDoFireOnRelease = FName("bDoFireOnRelease");
						const FName bFullAuto = FName("bFullAuto");
						const FName bInfiniteAmmo = FName("bInfiniteAmmo");
						const FName MaxAmmo = FName("MaxAmmo");
						const FName ProjectilesPerShot = FName("ProjectilesPerShot");
						const FName TimeBetweenShots = FName("TimeBetweenShots");
						const FName TimeBetweenAutoShots = FName("TimeBetweenAutoShots");
						const FName TimeBetweenProjectilesPerShot = FName("TimeBetweenProjectilesPerShot");
					}
				}
			}

			FImplSlice::~FImplSlice()
			{
				if (LaunchParams)
				{
					// NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl
					{
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl ParamsType;

						if (LaunchParamsName == ParamsType::Name)
						{
							delete static_cast<ParamsType*>(LaunchParams);
							LaunchParams = nullptr;
						}
					}
				}
			}

			/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
			{
				using namespace NCsWeapon::NProjectile::NData::NImplSlice::NCached;

				CS_IS_PTR_NULL_RET_NULL(Object)

				#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
				typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
				typedef NCsWeapon::NData::IData DataType;
				typedef NCsWeapon::NData::FInterfaceMap DataInterfaceMapType;

				DataHandlerType<DataType, FCsData_WeaponPtr, DataInterfaceMapType>* DataHandler = WeaponManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
				
				#undef DataHandlerType

				if (!DataHandler)
					return nullptr;

				typedef NCsWeapon::NProjectile::NData::IData PrjWeaponDataType;

				FImplSlice* Slice = DataHandler->AddSafeDataSlice<FImplSlice, PrjWeaponDataType>(Context, DataName);

				if (!Slice)
					return nullptr;

				// Check for properties matching interface: PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData)
				typedef NCsProperty::FLibrary PropertyLibrary;

				bool Success = false;

				// Try FCsData_ProjectileWeaponImplSlice
				typedef FCsData_ProjectileWeaponImplSlice StructSliceType;

				if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::ProjectileWeaponSlice, nullptr))
				{
					SliceAsStruct->CopyToSlice(Slice);
					Success = true;
				}
				// Try individual properties
				else
				{
					#define CS_TEMP_GET_SAFE_BOOL_PTR(__PropertyName) PropertyLibrary::GetBoolPropertyValuePtr(Context, Object, Object->GetClass(), Name::__PropertyName, nullptr)
					#define CS_TEMP_GET_SAFE_INT_PTR(__PropertyName) PropertyLibrary::GetIntPropertyValuePtr(Context, Object, Object->GetClass(), Name::__PropertyName, nullptr)
					#define CS_TEMP_GET_SAFE_FLOAT_PTR(__PropertyName) PropertyLibrary::GetFloatPropertyValuePtr(Context, Object, Object->GetClass(), Name::__PropertyName, nullptr)

					bool* bDoFireOnReleasePtr				= CS_TEMP_GET_SAFE_BOOL_PTR(bDoFireOnRelease);
					bool* bFullAutoPtr						= CS_TEMP_GET_SAFE_BOOL_PTR(bFullAuto);
					bool* bInfiniteAmmoPtr					= CS_TEMP_GET_SAFE_BOOL_PTR(bInfiniteAmmo);
					int32* MaxAmmoPtr						= CS_TEMP_GET_SAFE_INT_PTR(MaxAmmo);
					int32* ProjectilesPerShotPtr			= CS_TEMP_GET_SAFE_INT_PTR(ProjectilesPerShot);
					float* TimeBetweenShotsPtr				= CS_TEMP_GET_SAFE_FLOAT_PTR(TimeBetweenShots);
					float* TimeBetweenAutoShotsPtr			= CS_TEMP_GET_SAFE_FLOAT_PTR(TimeBetweenAutoShots);
					float* TimeBetweenProjectilesPerShotPtr = CS_TEMP_GET_SAFE_FLOAT_PTR(TimeBetweenProjectilesPerShot);

					#undef CS_TEMP_GET_SAFE_BOOL_PTR
					#undef CS_TEMP_GET_SAFE_INT_PTR
					#undef CS_TEMP_GET_SAFE_FLOAT_PTR

					if (bDoFireOnReleasePtr &&
						bFullAutoPtr &&
						bInfiniteAmmoPtr &&
						MaxAmmoPtr &&
						ProjectilesPerShotPtr &&
						TimeBetweenShotsPtr &&
						TimeBetweenAutoShotsPtr &&
						TimeBetweenProjectilesPerShotPtr)
					{
						Slice->SetDoFireOnRelease(bDoFireOnReleasePtr);
						Slice->SetFullAuto(bFullAutoPtr);
						Slice->SetInfiniteAmmo(bInfiniteAmmoPtr);
						Slice->SetMaxAmmo(MaxAmmoPtr);
						Slice->SetProjectilesPerShot(ProjectilesPerShotPtr);
						Slice->SetTimeBetweenShots(TimeBetweenShotsPtr);
						Slice->SetTimeBetweenAutoShots(TimeBetweenAutoShotsPtr);
						Slice->SetTimeBetweenProjectilesPerShot(TimeBetweenProjectilesPerShotPtr);
						Success = true;
					}
				}

				if (!Success)
				{
					if (Log)
					{
						Log(FString::Printf(TEXT("%s: Failed to find any properties from Object: %s with Class: %s for interface: NCsWeapon::NProjectile::NData::IData.")));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_ProjectileWeaponImplSlice with name: ProjectileWeaponSlice.")));
						Log(FString::Printf(TEXT("%s: - OR")));
						Log(FString::Printf(TEXT("%s: - Failed to get bool property with name: bDoFireOnRelease.")));
						Log(FString::Printf(TEXT("%s: - Failed to get bool property with name: bFullAuto.")));
						Log(FString::Printf(TEXT("%s: - Failed to get bool property with name: bInfiniteAmmo.")));
						Log(FString::Printf(TEXT("%s: - Failed to get int property with name: MaxAmmo.")));
						Log(FString::Printf(TEXT("%s: - Failed to get int property with name: ProjectilesPerShot.")));
						Log(FString::Printf(TEXT("%s: - Failed to get float property with name: TimeBetweenShots.")));
						Log(FString::Printf(TEXT("%s: - Failed to get float property with name: TimeBetweenAutoShots.")));
						Log(FString::Printf(TEXT("%s: - Failed to get float property with name: TimeBetweenProjectilesPerShot.")));
					}
				}
				return Slice;
			}

			bool FImplSlice::IsValidChecked(const FString& Context) const
			{
				// Check MaxAmmo is a valid value
				if (!HasInfiniteAmmo())
				{
					CS_IS_INT_GREATER_THAN_CHECKED(GetMaxAmmo(), 0)
				} 
				// Check TimeBetweenShots > 0.0f
				CS_IS_FLOAT_GREATER_THAN_CHECKED(GetTimeBetweenShots(), 0.0f)
				// Check ProjectilesPerShot >= 1
				CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetProjectilesPerShot(), 1)
				// Check TimeBetweenProjectilesPerShot is valid when ProjectilesPerShot > 1
				if (GetProjectilesPerShot() > 1)
				{
					checkf(GetTimeBetweenProjectilesPerShot() > 0.0f, TEXT("%s: TimeBetweenProjectilesPerShot must be > 0.0f when ProjectilesPerShot > 1."), *Context);
				}
				return true;
			}

			bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&)/*=&NCsProjectile::FLog::Warning*/) const
			{
				// Check MaxAmmo is a valid value
				if (!HasInfiniteAmmo())
				{
					CS_IS_INT_GREATER_THAN(GetMaxAmmo(), 0)
				}
				// Check TimeBetweenShots > 0.0f
				CS_IS_FLOAT_GREATER_THAN(GetTimeBetweenShots(), 0.0f)
				// Check ProjectilesPerShot >= 1
				CS_IS_INT_GREATER_THAN_OR_EQUAL(GetProjectilesPerShot(), 1)
				// Check TimeBetweenProjectilesPerShot is valid when ProjectilesPerShot > 1
				if (GetProjectilesPerShot() > 1)
				{
					if (GetTimeBetweenProjectilesPerShot() <= 0.0f)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TimeBetweenProjectilesPerShot must be > 0.0f when ProjectilesPerShot > 1."), *Context));
						return false;
					}
				}
				return true;
			}
		}
	}
}