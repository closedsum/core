// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/Visual/Fire/CsData_ProjectileWeapon_VisualFireImplSlice.h"

// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Weapon
#include "Managers/Weapon/Handler/CsManager_Weapon_DataHandler.h"

#define SliceType NCsWeapon::NProjectile::NData::NVisual::NFire::FImplSlice

SliceType* FCsData_ProjectileWeapon_VisualFireImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSlice(Slice);

	return nullptr;
}

SliceType* FCsData_ProjectileWeapon_VisualFireImplSlice::AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSliceAsValue(Slice);

	return nullptr;
}

SliceType* FCsData_ProjectileWeapon_VisualFireImplSlice::AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
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

	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::IFire FireVisualDataType;

	SliceType* Slice = DataHandler->AddSafeDataSlice<SliceType, FireVisualDataType>(Context, Name);

	return Slice;
}

void FCsData_ProjectileWeapon_VisualFireImplSlice::CopyToSlice(SliceType* Slice)
{
	Params.CopyToParams(Slice->GetFireVisualParamsPtr());
}

void FCsData_ProjectileWeapon_VisualFireImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Params.CopyToParamsAsValue(Slice->GetFireVisualParamsPtr());
}

#undef SliceType

bool FCsData_ProjectileWeapon_VisualFireImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_VALID(Params)
	return true;
}

const FName NCsWeapon::NProjectile::NData::NVisual::NFire::FImplSlice::Name = FName("NCsWeapon::NProjectile::NData::NVisual::NFire::FImplSlice");

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			namespace NVisual
			{
				namespace NFire
				{
					namespace NImplSlice
					{
						namespace NCached
						{
							namespace Name
							{
								const FName FireVisualSlice = FName("FireVisualSlice");

								const FName FireVisualParams = FName("FireVisualParams");
							}
						}
					}

					/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
					{
						using namespace NCsWeapon::NProjectile::NData::NVisual::NFire::NImplSlice::NCached;

						CS_IS_PTR_NULL_RET_NULL(Object)

						#define DataHandlerType NCsData::NManager::NHandler::TData
						typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
						typedef NCsWeapon::NData::IData DataType;
						typedef NCsWeapon::NData::FInterfaceMap DataInterfaceMapType;

						DataHandlerType<DataType, FCsData_WeaponPtr, DataInterfaceMapType>* DataHandler = WeaponManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
				
						#undef DataHandlerType

						if (!DataHandler)
							return nullptr;

						typedef NCsWeapon::NProjectile::NData::NVisual::NFire::IFire FireVisualDataType;

						FImplSlice* Slice = DataHandler->AddSafeDataSlice<FImplSlice, FireVisualDataType>(Context, DataName);

						if (!Slice)
							return nullptr;

						// Check for properties matching interface: FireVisualDataType (NCsWeapon::NProjectile::NData::NVisual::NFire::IFire)
						typedef NCsProperty::FLibrary PropertyLibrary;

						bool Success = false;

						// Try FCsData_ProjectileWeapon_VisualFireImplSlice
						typedef FCsData_ProjectileWeapon_VisualFireImplSlice StructSliceType;

						if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::FireVisualSlice, nullptr))
						{
							SliceAsStruct->CopyToSlice(Slice);
							Success = true;
						}
						// Try individual properties
						else
						{
							typedef FCsProjectileWeapon_Fire_VisualParams StructType;

							StructType* FireVisualParamsPtr = PropertyLibrary::GetStructPropertyValuePtr<StructType>(Context, Object, Object->GetClass(), Name::FireVisualParams, nullptr);

							if (FireVisualParamsPtr)
							{
								FireVisualParamsPtr->CopyToParams(Slice->GetFireVisualParamsPtr());
								Success = true;
							}
						}

						if (!Success)
						{
							if (Log)
							{
								Log(FString::Printf(TEXT("%s: Failed to find any properties from Object: %s with Class: %s for interface: NCsWeapon::NProjectile::NData::NVisual::NFire::IFire.")));
								Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_ProjectileWeapon_VisualFireImplSlice with name: FireVisualSlice.")));
								Log(FString::Printf(TEXT("%s: - OR")));
								Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsProjectileWeapon_Fire_VisualParams with name: FireVisualParams.")));
							}
						}
						return Slice;
					}

					bool FImplSlice::IsValidChecked(const FString& Context) const
					{
						CS_IS_VALID_CHECKED(Params);
						return true;
					}

					bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						CS_IS_VALID(Params)
						return true;
					}
				}
			}
		}
	}
}