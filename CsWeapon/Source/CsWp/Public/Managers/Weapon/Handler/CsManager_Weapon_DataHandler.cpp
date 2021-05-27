// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Weapon/Handler/CsManager_Weapon_Datahandler.h"


// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsWpLibrary_DataRootSet.h"
// Data
#include "Data/CsData_WeaponImplSlice.h"
#include "Projectile/Data/CsData_ProjectileWeaponImplSlice.h"
#include "Projectile/Data/Sound/CsData_ProjectileWeapon_SoundFireImpl.h"

namespace NCsWeapon
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NCached
			{
				namespace Name
				{
					// ICsData_ProjectileWeapon
					const FName bDoFireOnRelease = FName("bDoFireOnRelease");
					const FName bFullAuto = FName("bFullAuto");
					const FName bInfiniteAmmo = FName("bInfiniteAmmo");
					const FName MaxAmmo = FName("MaxAmmo");
					const FName ProjectilesPerShot = FName("ProjectilesPerShot");
					const FName TimeBetweenShots = FName("TimeBetweenShots");
					const FName TimeBetweenAutoShots = FName("TimeBetweenAutoShots");
					const FName TimeBetweenProjectilesPerShot = FName("TimeBetweenProjectilesPerShot");
					// ICsData_ProjectileWeapon_SoundFire
					const FName FireSound = FName("FireSound");
				}
			}


			FData::FData()
			{
			}
			 
			// DataHandlerType (NCsPooledObject::NManager::NHandler::TData)
			#pragma region

			void FData::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				UObject* DataRootSetImpl			= NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsWpDataRootSet& DataRootSet = NCsWeapon::NDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				for (const FCsWeaponSettings_DataTable_Weapons& Weapons : DataRootSet.Weapons)
				{
					TSoftObjectPtr<UDataTable> DataTableSoftObject = Weapons.Weapons;

					checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsWpDataRootSet().Weapons is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

					typedef NCsData::NManager::FLibrary DataManagerLibrary;

					UDataTable* DataTable = DataManagerLibrary::GetDataTableChecked(Context, MyRoot, DataTableSoftObject);

					OutDataTables.Add(DataTable);
					OutDataTableSoftObjects.Add(DataTableSoftObject);
				}
			}

			bool FData::HasEmulatedDataInterfaces(const FString& Context, const int32& Index) const
			{
				UObject* DataRootSetImpl			= NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsWpDataRootSet& DataRootSet = NCsWeapon::NDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				checkf(Index < DataRootSet.Weapons.Num(), TEXT("%s: Index < %s.GetCsWpDataRootSet().Weapons.Num() (%d >= %d)."), *Context, *(DataRootSetImpl->GetName()), DataRootSet.Weapons.Num());

				return DataRootSet.Weapons[Index].EmulatedDataInterfaces.Num() >  CS_EMPTY;
			}

			void FData::CreateEmulatedDataFromDataTable(const FString& Context, const int32& Index, UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
			{
				using namespace NCached;

				const UScriptStruct* RowStruct = DataTable->GetRowStruct();

				const TSet<FECsWeaponData>& EmulatedDataInterfaces = GetEmulatedDataInterfaces(Context, Index);

				checkf(EmulatedDataInterfaces.Find(NCsWeaponData::Weapon), TEXT("%s: Emulated Data Interfaces must include ICsData_Weapon."), *Context);

				// ICsData_Weapon
				bool Emulates_ICsDataWeapon = true;

				// ICsData_ProjectileWeapon
				bool Emulates_ICsData_ProjectileWeapon = false;

					// bDoFireOnRelease
				FBoolProperty* bDoFireOnReleaseProperty = nullptr;
					// bFullAuto
				FBoolProperty* bFullAutoProperty = nullptr;
					// bInfiniteAmmo
				FBoolProperty* bInfiniteAmmoProperty = nullptr;
					// MaxAmmo
				FIntProperty* MaxAmmoProperty = nullptr;
					// ProjectilesPerShot
				FIntProperty* ProjectilesPerShotProperty = nullptr;
					// TimeBetweenShots
				FFloatProperty* TimeBetweenShotsProperty = nullptr;
					// TimeBetweenAutoShots
				FFloatProperty* TimeBetweenAutoShotsProperty = nullptr;
					// TimeBetweenProjectilesPerShot
				FFloatProperty* TimeBetweenProjectilesPerShotProperty = nullptr;

				typedef NCsProperty::FLibrary PropertyLibrary;

				if (EmulatedDataInterfaces.Find(NCsWeaponData::ProjectileWeapon))
				{
					// bDoFireOnRelease
					bDoFireOnReleaseProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<FBoolProperty>(Context, RowStruct, Name::bDoFireOnRelease, NCsWeaponData::ProjectileWeapon.GetDisplayName());
					// bFullAuto
					bFullAutoProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<FBoolProperty>(Context, RowStruct, Name::bFullAuto, NCsWeaponData::ProjectileWeapon.GetDisplayName());
					// bInfiniteAmmo
					bInfiniteAmmoProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<FBoolProperty>(Context, RowStruct, Name::bInfiniteAmmo, NCsWeaponData::ProjectileWeapon.GetDisplayName());
					// MaxAmmo
					MaxAmmoProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<FIntProperty>(Context, RowStruct, Name::MaxAmmo, NCsWeaponData::ProjectileWeapon.GetDisplayName());
					// ProjectilesPerShot
					ProjectilesPerShotProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<FIntProperty>(Context, RowStruct, Name::ProjectilesPerShot, NCsWeaponData::ProjectileWeapon.GetDisplayName());
					// TimeBetweenShots
					TimeBetweenShotsProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<FFloatProperty>(Context, RowStruct, Name::TimeBetweenShots, NCsWeaponData::ProjectileWeapon.GetDisplayName());
					// TimeBetweenAutoShots
					TimeBetweenAutoShotsProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<FFloatProperty>(Context, RowStruct, Name::TimeBetweenAutoShots, NCsWeaponData::ProjectileWeapon.GetDisplayName());
					// TimeBetweenProjectilesPerShot
					TimeBetweenProjectilesPerShotProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<FFloatProperty>(Context, RowStruct, Name::TimeBetweenProjectilesPerShot, NCsWeaponData::ProjectileWeapon.GetDisplayName());

					Emulates_ICsData_ProjectileWeapon = true;
				}

				// ICsData_ProjectileWeapon_SoundFire
				bool Emulates_ICsData_ProjectileWeapon_SoundFire = false;

					// FireSound
				FStructProperty* FireSoundProperty = nullptr;

				if (EmulatedDataInterfaces.Find(NCsWeaponData::ProjectileWeaponSound))
				{
					// FireSound
					FireSoundProperty = PropertyLibrary::FindStructPropertyByNameForInterfaceChecked<FCsSound>(Context, RowStruct, Name::FireSound, NCsWeaponData::ProjectileWeaponSound.GetDisplayName());

					Emulates_ICsData_ProjectileWeapon_SoundFire = true;
				}

				// Get Manager_Data
				typedef NCsData::NManager::FLibrary DataManagerLibrary;

				UCsManager_Data* Manager_Data = DataManagerLibrary::GetChecked(Context, MyRoot);

				// Check which rows from the DataTable have been loaded
				const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

				for (const TPair<FName, uint8*>& Pair : RowMap)
				{
					const FName& Name = Pair.Key;
					uint8* RowPtr	  = Manager_Data->GetDataTableRow(DataTableSoftObject, Name);

					if (!RowPtr)
						continue;

					TMap<FName, uint8*>& Map = DataTableRowByPathMap.FindOrAdd(DataTableSoftObject.ToSoftObjectPath());
					Map.Add(Name, RowPtr);

					typedef NCsWeapon::NData::FInterfaceMap DataInterfaceMapType;

					// ICsData_Weapon
					if (Emulates_ICsDataWeapon)
					{
						// Setup and Add Emulated Interface
						typedef NCsWeapon::NData::IData DataType;
						typedef NCsWeapon::NData::FImplSlice DataSliceType;

						DataSliceType* Data = new DataSliceType();

						checkf(EmulatedDataMap.Find(Name) == nullptr, TEXT("%s: Data has already been created for Row: %s."), *Context, *(Name.ToString()));

						EmulatedDataMap.Add(Name, Data);

						DataInterfaceMapType* EmulatedInterfaceMap = new DataInterfaceMapType();

						checkf(EmulatedDataInterfaceMap.Find(Name) == nullptr, TEXT("%s: Emulated Interface Map has already been created for Row: %s."), *Context, *(Name.ToString()));

						EmulatedDataInterfaceMap.Add(Name, EmulatedInterfaceMap);

						FCsInterfaceMap* InterfaceMap = EmulatedInterfaceMap->GetInterfaceMap();

						InterfaceMap->Add<DataType>(DataSliceType::Name, static_cast<DataType*>(Data));

						Data->SetInterfaceMap(InterfaceMap);

						TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
						InterfaceImplMap.Add(DataSliceType::Name, Data);

						DataMap.Add(Name, Data);
					}
					// ICsData_ProjectileWeapon
					if (Emulates_ICsData_ProjectileWeapon)
					{
						// Setup and Add Emulated Interface
						typedef NCsWeapon::NProjectile::NData::IData DataType;
						typedef NCsWeapon::NProjectile::NData::FImplSlice DataSliceType;

						DataSliceType* Data = new DataSliceType();

						DataInterfaceMapType* EmulatedInterfaceMap = EmulatedDataInterfaceMap[Name];
						FCsInterfaceMap* InterfaceMap			   = EmulatedInterfaceMap->GetInterfaceMap();

						InterfaceMap->Add<DataType>(DataSliceType::Name, static_cast<DataType*>(Data));

						Data->SetInterfaceMap(InterfaceMap);

						TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
						InterfaceImplMap.Add(DataSliceType::Name, Data);

						// bDoFireOnRelease
						{
							bool* Value = PropertyLibrary::ContainerPtrToValuePtrChecked<bool>(Context, bDoFireOnReleaseProperty, RowPtr);

							Data->SetDoFireOnRelease(Value);
						}
						// bFullAuto
						{
							bool* Value = PropertyLibrary::ContainerPtrToValuePtrChecked<bool>(Context, bFullAutoProperty, RowPtr);

							Data->SetFullAuto(Value);
						}
						// bInfiniteAmmo
						{
							bool* Value = PropertyLibrary::ContainerPtrToValuePtrChecked<bool>(Context, bInfiniteAmmoProperty, RowPtr);

							Data->SetInfiniteAmmo(Value);
						}
						// MaxAmmo
						{
							int32* Value = PropertyLibrary::ContainerPtrToValuePtrChecked<int32>(Context, MaxAmmoProperty, RowPtr);

							Data->SetMaxAmmo(Value);
						}
						// ProjectilesPerShot
						{
							int32* Value = PropertyLibrary::ContainerPtrToValuePtrChecked<int32>(Context, ProjectilesPerShotProperty, RowPtr);

							Data->SetProjectilesPerShot(Value);
						}
						// TimeBetweenShots
						{
							float* Value = PropertyLibrary::ContainerPtrToValuePtrChecked<float>(Context, TimeBetweenShotsProperty, RowPtr);

							Data->SetTimeBetweenShots(Value);
						}
						// TimeBetweenAutoShots
						{
							float* Value = PropertyLibrary::ContainerPtrToValuePtrChecked<float>(Context, TimeBetweenAutoShotsProperty, RowPtr);

							Data->SetTimeBetweenAutoShots(Value);
						}
						// TimeBetweenProjectilesPerShot
						{
							float* Value = PropertyLibrary::ContainerPtrToValuePtrChecked<float>(Context, TimeBetweenProjectilesPerShotProperty, RowPtr);

							Data->SetTimeBetweenProjectilesPerShot(Value);
						}
					}
					// ICsData_ProjectileWeapon_SoundFire
					if (Emulates_ICsData_ProjectileWeapon_SoundFire)
					{
						// Setup and Add Emulated Interface

						// TODO: Change FImpl to FEmu functionality
						/*
						typedef ICsData_ProjectileWeapon_SoundFire SoundDataType;
						typedef NCsWeapon::NProjectile::NData::NSound::NFire::FImpl SoundDataImplType;

						SoundDataImplType* Data = new SoundDataImplType();

						DataInterfaceMapType* EmulatedInterfaceMap = EmulatedDataInterfaceMap[Name];
						FCsInterfaceMap* InterfaceMap			   = EmulatedInterfaceMap->GetInterfaceMap();

						InterfaceMap->Add<SoundDataType>(SoundDataImplType::Name, static_cast<SoundDataType*>(Data));

						Data->SetInterfaceMap(InterfaceMap);

						TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
						InterfaceImplMap.Add(SoundDataImplType::Name, Data);

						// FireSound
						{
							FCsSound* Value = PropertyLibrary::ContainerPtrToValuePtrChecked<FCsSound>(Context, FireSoundProperty, RowPtr);

							Data->SetFireSound(Value);
						}
						*/
					}
				}
			}

			bool FData::DeconstructEmulatedData(const FName& InterfaceImplName, void* Data)
			{
				// NCsWeapon::NData::FImplSlice
				if (InterfaceImplName == NCsWeapon::NData::FImplSlice::Name)
				{
					delete static_cast<NCsWeapon::NData::FImplSlice*>(Data);
					return true;
				}
				// NCsWeapon::NProjectile::NData::FImplSlice
				if (InterfaceImplName == NCsWeapon::NProjectile::NData::FImplSlice::Name)
				{
					delete static_cast<NCsWeapon::NProjectile::NData::FImplSlice*>(Data);
					return true;
				}
				// NCsWeapon::NProjectile::NData::NSound::NFire::FImpl
				if (InterfaceImplName == NCsWeapon::NProjectile::NData::NSound::NFire::FImpl::Name)
				{
					delete static_cast<NCsWeapon::NProjectile::NData::NSound::NFire::FImpl*>(Data);
					return true;
				}
				return false;
			}

			#pragma endregion DataHandlerType (NCsPooledObject::NManager::NHandler::TData)

			const TSet<FECsWeaponData>& FData::GetEmulatedDataInterfaces(const FString& Context, const int32& Index)
			{
				UObject* DataRootSetImpl			= NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsWpDataRootSet& DataRootSet = NCsWeapon::NDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				return DataRootSet.Weapons[Index].EmulatedDataInterfaces;
			}
		}
	}
}