// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/Sound/CsData_ProjectileWeapon_SoundFireImplSlice.h"

// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Weapon
#include "Managers/Weapon/Handler/CsManager_Weapon_DataHandler.h"

#define SliceType NCsWeapon::NProjectile::NData::NSound::NFire::FImplSlice

SliceType* FCsData_ProjectileWeapon_SoundFireImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSlice(Slice);

	return nullptr;
}

SliceType* FCsData_ProjectileWeapon_SoundFireImplSlice::AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	SliceType* Slice = AddSafeSlice_Internal(Context, WorldContext, Name, Log);

	if (!Slice)
		return nullptr;

	CopyToSliceAsValue(Slice);

	return nullptr;
}

SliceType* FCsData_ProjectileWeapon_SoundFireImplSlice::AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	const_cast<FCsData_ProjectileWeapon_SoundFireImplSlice*>(this)->UpdateInternalPtrs();

	if (!IsValid(Context, Log))
		return nullptr;

	#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
	typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
	typedef NCsWeapon::NData::IData DataType;
	typedef NCsWeapon::NData::FInterfaceMap DataInterfaceMapType;
	
	DataHandlerType<DataType, FCsData_WeaponPtr, DataInterfaceMapType>* DataHandler = WeaponManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
	
	if (!DataHandler)
		return nullptr;
	
	typedef NCsWeapon::NProjectile::NData::NSound::NFire::IFire FireVisualDataType;
	
	SliceType* Slice = DataHandler->AddSafeDataSlice<SliceType, FireVisualDataType>(Context, Name);
	
	return Slice;
}

void FCsData_ProjectileWeapon_SoundFireImplSlice::CopyToSlice(SliceType* Slice)
{
	Params.CopyToParams(Slice->GetFireSoundParamsPtr());
}

void FCsData_ProjectileWeapon_SoundFireImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Params.CopyToParamsAsValue(Slice->GetFireSoundParamsPtr());
}

#undef SliceType

bool FCsData_ProjectileWeapon_SoundFireImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	if (!Params.IsValid(Context, Log))
		return false;
	return true;
}

const FName NCsWeapon::NProjectile::NData::NSound::NFire::FImplSlice::Name = FName("NCsWeapon::NProjectile::NData::NSound::NFire::FImplSlice");

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			namespace NSound
			{
				namespace NFire
				{
					namespace NImplSlice
					{
						namespace NCached
						{
							namespace Name
							{
								const FName SoundFireSlice = FName("SoundFireSlice");

								const FName SoundFireParams = FName("SoundFireParams");
							}
						}
					}

					/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
					{
						using namespace NCsWeapon::NProjectile::NData::NSound::NFire::NImplSlice::NCached;

						CS_IS_PTR_NULL_RET_NULL(Object)

						#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
						typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
						typedef NCsWeapon::NData::IData DataType;
						typedef NCsWeapon::NData::FInterfaceMap DataInterfaceMapType;

						DataHandlerType<DataType, FCsData_WeaponPtr, DataInterfaceMapType>* DataHandler = WeaponManagerLibrary::GetSafeDataHandler(Context, WorldContext, Log);
				
						#undef DataHandlerType

						if (!DataHandler)
							return nullptr;

						typedef NCsWeapon::NProjectile::NData::NSound::NFire::IFire FireSoundDataType;

						FImplSlice* Slice = DataHandler->AddSafeDataSlice<FImplSlice, FireSoundDataType>(Context, DataName);

						if (!Slice)
							return nullptr;

						// Check for properties matching interface: FireVisualDataType (NCsWeapon::NProjectile::NData::NSound::NFire::IFire)
						typedef NCsProperty::FLibrary PropertyLibrary;

						bool Success = false;

						// Try FCsData_ProjectileWeapon_SoundFireImplSlice
						typedef FCsData_ProjectileWeapon_SoundFireImplSlice StructSliceType;

						if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::SoundFireSlice, nullptr))
						{
							SliceAsStruct->UpdateInternalPtrs();
							SliceAsStruct->CopyToSlice(Slice);
							Success = true;
						}
						// Try individual properties
						else
						{
							typedef FCsProjectileWeapon_SoundFire_Params StructType;

							StructType* VisualSoundParamsPtr = PropertyLibrary::GetStructPropertyValuePtr<StructType>(Context, Object, Object->GetClass(), Name::SoundFireParams, nullptr);

							if (VisualSoundParamsPtr)
							{
								VisualSoundParamsPtr->UpdateInternalPtrs();
								VisualSoundParamsPtr->CopyToParams(Slice->GetFireSoundParamsPtr());
								Success = true;
							}
						}

						if (!Success)
						{
							if (Log)
							{
								Log(FString::Printf(TEXT("%s: Failed to find any properties from Object: %s with Class: %s for interface: NCsWeapon::NProjectile::NData::NSound::NFire::IFire.")));
								Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_ProjectileWeapon_SoundFireImplSlice with name: SoundFireSlice.")));
								Log(FString::Printf(TEXT("%s: - OR")));
								Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsProjectileWeapon_SoundFire_Params with name: SoundFireParams.")));
							}
						}
						return Slice;
					}

					bool FImplSlice::IsValidChecked(const FString& Context) const
					{
						check(Params.IsValidChecked(Context));
						return true;
					}

					bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						if (!Params.IsValid(Context, Log))
							return false;
						return true;
					}
				}
			}
		}
	}
}