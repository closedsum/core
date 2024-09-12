// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/CsData_ProjectileWeaponImplSlice.h"

// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Weapon
#include "Managers/Weapon/Handler/CsManager_Weapon_DataHandler.h"
// Params
#include "Projectile/Params/Launch/Trace/CsParams_ProjectileWeapon_LaunchTraceImpl.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsData_ProjectileWeaponImplSlice)

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

	#define DataHandlerType NCsData::NManager::NHandler::TData
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
	Slice->SetTimeBetweenShots(&TimeBetweenShots);
	Slice->SetTimeBetweenAutoShots(&TimeBetweenAutoShots);
	ProjectilesPerShotParams.CopyToParams(Slice->GetProjectilesPerShotParamsPtr());
	Slice->SetbSpreadParams(&bSpreadParams);
	SpreadParams.CopyToParams(Slice->GetSpreadParamsPtr());
}

void FCsData_ProjectileWeaponImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetDoFireOnRelease(bDoFireOnRelease);
	Slice->SetFullAuto(bFullAuto);
	Slice->SetInfiniteAmmo(bInfiniteAmmo);
	Slice->SetMaxAmmo(MaxAmmo);
	Slice->SetTimeBetweenShots(TimeBetweenShots);
	Slice->SetTimeBetweenAutoShots(TimeBetweenAutoShots);
	ProjectilesPerShotParams.CopyToParamsAsValue(Slice->GetProjectilesPerShotParamsPtr());
	Slice->SetbSpreadParams(bSpreadParams);
	SpreadParams.CopyToParamsAsValue(Slice->GetSpreadParamsPtr());
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
	// Check ProjectilesPerShot
	CS_IS_VALID_CHECKED(ProjectilesPerShotParams);
	// Check Spread
	if (bSpreadParams)
	{
		CS_IS_VALID_CHECKED(SpreadParams);
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
						const FName TimeBetweenShots = FName("TimeBetweenShots");
						const FName TimeBetweenAutoShots = FName("TimeBetweenAutoShots");
						const FName ProjectilesPerShotParams = FName("ProjectilesPerShotParams");
						const FName bSpreadParams = FName("bSpreadParams");
						const FName SpreadParams = FName("SpreadParams");
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

				#define DataHandlerType NCsData::NManager::NHandler::TData
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
					float* TimeBetweenShotsPtr				= CS_TEMP_GET_SAFE_FLOAT_PTR(TimeBetweenShots);
					float* TimeBetweenAutoShotsPtr			= CS_TEMP_GET_SAFE_FLOAT_PTR(TimeBetweenAutoShots);
					FCsProjectileWeapon_Shot_ProjectileParams* ProjectilesPerShotParamsPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsProjectileWeapon_Shot_ProjectileParams>(Context, Object, Object->GetClass(), Name::ProjectilesPerShotParams, nullptr);
					bool* bSpreadParamsPtr					= CS_TEMP_GET_SAFE_BOOL_PTR(bSpreadParams);

					FCsProjectileWeapon_SpreadParams* SpreadParamsPtr = PropertyLibrary::GetStructPropertyValuePtr<FCsProjectileWeapon_SpreadParams>(Context, Object, FCsProjectileWeapon_SpreadParams::StaticStruct(), Name::SpreadParams, nullptr);

					#undef CS_TEMP_GET_SAFE_BOOL_PTR
					#undef CS_TEMP_GET_SAFE_INT_PTR
					#undef CS_TEMP_GET_SAFE_FLOAT_PTR

					if (bDoFireOnReleasePtr &&
						bFullAutoPtr &&
						bInfiniteAmmoPtr &&
						MaxAmmoPtr &&
						TimeBetweenShotsPtr &&
						TimeBetweenAutoShotsPtr &&
						ProjectilesPerShotParamsPtr &&
						bSpreadParamsPtr &&
						SpreadParamsPtr)
					{
						Slice->SetDoFireOnRelease(bDoFireOnReleasePtr);
						Slice->SetFullAuto(bFullAutoPtr);
						Slice->SetInfiniteAmmo(bInfiniteAmmoPtr);
						Slice->SetMaxAmmo(MaxAmmoPtr);
						Slice->SetTimeBetweenShots(TimeBetweenShotsPtr);
						Slice->SetTimeBetweenAutoShots(TimeBetweenAutoShotsPtr);
						ProjectilesPerShotParamsPtr->CopyToParams(Slice->GetProjectilesPerShotParamsPtr());
						Slice->SetbSpreadParams(bSpreadParamsPtr);
						SpreadParamsPtr->CopyToParams(Slice->GetSpreadParamsPtr());
						Success = true;
					}
				}

				if (!Success)
				{
					if (Log)
					{
						Log(FString::Printf(TEXT("%s: Failed to find any properties from Object: %s with Class: %s for interface: NCsWeapon::NProjectile::NData::IData."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_ProjectileWeaponImplSlice with name: ProjectileWeaponSlice."), *Context));
						Log(FString::Printf(TEXT("%s: - OR"), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get bool property with name: bDoFireOnRelease."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get bool property with name: bFullAuto."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get bool property with name: bInfiniteAmmo."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get int property with name: MaxAmmo."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get float property with name: TimeBetweenShots."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get float property with name: TimeBetweenAutoShots."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsProjectileWeapon_Shot_ProjectileParams with name: ProjectilesPerShotParams."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get bool property with name: bSpreadParams."), *Context));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsProjectileWeapon_SpreadParams with name: SpreadParams."), *Context));
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
				// Check ProjectilesPerShot
				CS_IS_VALID_CHECKED(ProjectilesPerShotParams);
				// Check Spread
				if (GetbSpreadParams())
				{
					CS_IS_VALID_CHECKED(GetSpreadParams());
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
				// Check ProjectilesPerShot
				CS_IS_VALID(ProjectilesPerShotParams);
				// Check Spread
				if (GetbSpreadParams())
				{
					CS_IS_VALID(GetSpreadParams())
				}
				return true;
			}
		}
	}
}