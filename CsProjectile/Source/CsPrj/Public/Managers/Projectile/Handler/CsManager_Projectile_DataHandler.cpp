// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/Handler/CsManager_Projectile_Datahandler.h"

// Types
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Collision.h"
// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsPrjLibrary_DataRootSet.h"
#include "Library/CsLibrary_Property.h"
// Projectile
#include "Data/CsData_ProjectileEmuSlice.h"

namespace NCsProjectile
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NCached
			{
				namespace Name
				{
					const FName LifeTime = FName("LifeTime");
					const FName InitialSpeed = FName("InitialSpeed");
					const FName MaxSpeed = FName("MaxSpeed");
					const FName GravityScale = FName("GravityScale");
				}
			}


			FData::FData()
			{
			}

			// DataHandlerType (NCsPooledObject::NManager::NHandler::TData)
			#pragma region

			void FData::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
			{
				UObject* DataRootSetImpl			 = NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsPrjDataRootSet& DataRootSet = NCsProjectile::NDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				for (const FCsProjectileSettings_DataTable_Projectiles& Projectiles : DataRootSet.Projectiles)
				{
					TSoftObjectPtr<UDataTable> DataTableSoftObject = Projectiles.Projectiles;

					checkf(DataTableSoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: %s.GetCsPrjDataRootSet().Projectiles is NOT Valid."), *Context, *(DataRootSetImpl->GetName()));

					UWorld* World				  = MyRoot->GetWorld();
					UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

					UDataTable* DataTable = Manager_Data->GetDataTable(DataTableSoftObject);

					checkf(DataTable, TEXT("%s: Failed to get DataTable @ %s."), *Context, *(DataTableSoftObject.ToSoftObjectPath().ToString()));

					OutDataTables.Add(DataTable);
					OutDataTableSoftObjects.Add(DataTableSoftObject);
				}
			}

			bool FData::HasEmulatedDataInterfaces(const FString& Context, const int32& Index) const
			{
				UObject* DataRootSetImpl			 = NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsPrjDataRootSet& DataRootSet = NCsProjectile::NDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				checkf(Index < DataRootSet.Projectiles.Num(), TEXT("%s: Index < %s.GetCsPrjDataRootSet().Projectiles.Num() (%d >= %d)."), *Context, *(DataRootSetImpl->GetName()), DataRootSet.Projectiles.Num());

				return DataRootSet.Projectiles[Index].EmulatedDataInterfaces.Num() >  CS_EMPTY;
			}

			void FData::CreateEmulatedDataFromDataTable(const FString& Context, const int32& Index, UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
			{
				using namespace NCached;

				const UScriptStruct* RowStruct = DataTable->GetRowStruct();

				const TSet<FECsProjectileData>& EmulatedDataInterfaces = GetEmulatedDataInterfaces(Context, Index);

				checkf(EmulatedDataInterfaces.Find(NCsProjectileData::Projectile), TEXT("%s: Emulated Data Interfaces must include ICsData_Projecitle."), *Context);

				typedef NCsProperty::FLibrary PropertyLibrary;

				// ICsData_Projectile
				bool Emulates_ICsDataProjectile = true;
					// LifeTime
				FFloatProperty* LifeTimeProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<FFloatProperty>(Context, RowStruct, Name::LifeTime, NCsProjectileData::Projectile.GetDisplayName());
					// InitialSpeed
				FFloatProperty* InitialSpeedProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<FFloatProperty>(Context, RowStruct, Name::InitialSpeed, NCsProjectileData::Projectile.GetDisplayName());
					// MaxSpeed
				FFloatProperty* MaxSpeedProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<FFloatProperty>(Context, RowStruct, Name::MaxSpeed, NCsProjectileData::Projectile.GetDisplayName());
					// GravityScale
				FFloatProperty* GravityScaleProperty = PropertyLibrary::FindPropertyByNameForInterfaceChecked<FFloatProperty>(Context, RowStruct, Name::GravityScale, NCsProjectileData::Projectile.GetDisplayName());

				// ICsData_ProjectileCollision
				bool Emulates_ICsData_ProjectileCollision = false;

				// ICsData_Projectile_VisualStaticMesh
				bool Emulates_ICsData_Projectile_VisualStaticMesh = false;
					// StaticMesh
				//FCsPrjStaticMesh* StaticMesh;

				if (EmulatedDataInterfaces.Find(NCsProjectileData::ProjectileStaticMeshVisual))
				{
				}

				if (EmulatedDataInterfaces.Find(NCsProjectileData::ProjectileTrailVisual))
				{
				}

					// CollisionPreset
				FStructProperty* CollisionPresetProperty = nullptr;

				if (EmulatedDataInterfaces.Find(NCsProjectileData::ProjectileCollision))
				{
					CollisionPresetProperty = PropertyLibrary::FindStructPropertyByNameForInterfaceChecked<FCsCollisionPreset>(Context, RowStruct, Name::GravityScale, NCsProjectileData::ProjectileCollision.GetDisplayName());
				}

				// Get Manager_Data
				UWorld* World				  = MyRoot->GetWorld();
				UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

				// Check which rows from the DataTable have been loaded
				const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

				for (const TPair<FName, uint8*>& Pair : RowMap)
				{
					const FName& Name = Pair.Key;
					uint8* RowPtr	  = Manager_Data->GetDataTableRow(DataTableSoftObject, Name);

					if (!RowPtr)
						continue;

					// ICsData_Projectile
					if (Emulates_ICsDataProjectile)
					{
						typedef NCsProjectile::NData::IData DataType;
						typedef NCsProjectile::NData::FEmuSlice DataEmuSliceType;

						DataEmuSliceType* Data = new DataEmuSliceType();

						checkf(EmulatedDataMap.Find(Name) == nullptr, TEXT("%s: Data has already been created for Row: %s."), *Context, *(Name.ToString()));

						EmulatedDataMap.Add(Name, Data);

						typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType;

						DataInterfaceMapType* EmulatedInterfaceMap = new DataInterfaceMapType();

						checkf(EmulatedDataInterfaceMap.Find(Name) == nullptr, TEXT("%s: Emulated Interface Map has already been created for Row: %s."), *Context, *(Name.ToString()));

						EmulatedDataInterfaceMap.Add(Name, EmulatedInterfaceMap);

						FCsInterfaceMap* InterfaceMap = EmulatedInterfaceMap->GetInterfaceMap();

						InterfaceMap->Add<DataType>(DataEmuSliceType::Name, static_cast<DataType*>(Data));

						Data->SetInterfaceMap(InterfaceMap);

						TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
						InterfaceImplMap.Add(DataEmuSliceType::Name, Data);

						DataMap.Add(Name, Data);

						// LifeTime
						{
							float* Value = PropertyLibrary::ContainerPtrToValuePtrChecked<float>(Context, LifeTimeProperty, RowPtr);

							Data->SetLifeTime(Value);
						}
						// InitialSpeed
						{
							float* Value = PropertyLibrary::ContainerPtrToValuePtrChecked<float>(Context, InitialSpeedProperty, RowPtr);

							Data->SetInitialSpeed(Value);
						}
						// MaxSpeed
						{
							float* Value = PropertyLibrary::ContainerPtrToValuePtrChecked<float>(Context, MaxSpeedProperty, RowPtr);

							Data->SetMaxSpeed(Value);
						}
						// GravityScale
						{
							float* Value = PropertyLibrary::ContainerPtrToValuePtrChecked<float>(Context, GravityScaleProperty, RowPtr);

							Data->SetGravityScale(Value);
						}
					}
					// ICsData_ProjectileCollision
					if (Emulates_ICsData_ProjectileCollision)
					{

					}
					// ICsData_Projectile_VisualStaticMesh
					if (Emulates_ICsData_Projectile_VisualStaticMesh)
					{

					}
				}
			}

			bool FData::DeconstructEmulatedData(const FName& InterfaceImplName, void* Data)
			{
				// NCsProjectile::NData::FEmuSlice
				if (InterfaceImplName == NCsProjectile::NData::FEmuSlice::Name)
				{
					delete static_cast<NCsProjectile::NData::FEmuSlice*>(Data);
					return true;
				}
				// FCsData_ProjecitleVisualEmuSlice
				// FCsData_ProjectileCollisionEmuSlice
				return false;
			}

			#pragma endregion DataHandlerType (NCsPooledObject::NManager::NHandler::TData)

			const TSet<FECsProjectileData>& FData::GetEmulatedDataInterfaces(const FString& Context, const int32& Index)
			{
				UObject* DataRootSetImpl			 = NCsDataRootSet::FLibrary::GetImplChecked(Context, MyRoot);
				const FCsPrjDataRootSet& DataRootSet = NCsProjectile::NDataRootSet::FLibrary::GetChecked(Context, MyRoot);

				return DataRootSet.Projectiles[Index].EmulatedDataInterfaces;
			}
		}
	}
}