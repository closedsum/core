// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/Handler/CsManager_Projectile_Datahandler.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsPrjLibrary_DataRootSet.h"
#include "Library/CsLibrary_Property.h"
// Projectile
#include "Data/CsData_ProjectileEmuSlice.h"

// Cached
#pragma region

namespace NCsManagerProjectileDataHandler
{
	namespace Name
	{
		const FName LifeTime = FName("LifeTime");
		const FName InitialSpeed = FName("InitialSpeed");
		const FName MaxSpeed = FName("MaxSpeed");
		const FName GravityScale = FName("GravityScale");
	}
}

#pragma endregion Cached

FCsManager_Projectile_DataHandler::FCsManager_Projectile_DataHandler()
{
}

// TCsManager_PooledObject_DataHandler Interface
#pragma region

void FCsManager_Projectile_DataHandler::GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects)
{
	UObject* DataRootSetImpl			 = FCsLibrary_DataRootSet::GetImplChecked(Context, MyRoot);
	const FCsPrjDataRootSet& DataRootSet = FCsPrjLibrary_DataRootSet::GetChecked(Context, MyRoot);

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

bool FCsManager_Projectile_DataHandler::HasEmulatedDataInterfaces(const FString& Context, const int32& Index) const
{
	UObject* DataRootSetImpl			 = FCsLibrary_DataRootSet::GetImplChecked(Context, MyRoot);
	const FCsPrjDataRootSet& DataRootSet = FCsPrjLibrary_DataRootSet::GetChecked(Context, MyRoot);

	checkf(Index < DataRootSet.Projectiles.Num(), TEXT("%s: Index < %s.GetCsPrjDataRootSet().Projectiles.Num() (%d >= %d)."), *Context, *(DataRootSetImpl->GetName()), DataRootSet.Projectiles.Num());

	return DataRootSet.Projectiles[Index].EmulatedDataInterfaces.Num() >  CS_EMPTY;
}

void FCsManager_Projectile_DataHandler::CreateEmulatedDataFromDataTable(const FString& Context, const int32& Index, UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject)
{
	using namespace NCsManagerProjectileDataHandler;

	const UScriptStruct* RowStruct = DataTable->GetRowStruct();

	const TSet<FECsProjectileData>& EmulatedDataInterfaces = GetEmulatedDataInterfaces(Context, Index);

	checkf(EmulatedDataInterfaces.Find(NCsProjectileData::Projectile), TEXT("%s: Emulated Data Interfaces must include ICsData_Projecitle."), *Context);

	// ICsData_Projectile
	bool Emulates_ICsDataProjectile = true;
		// LifeTime
	UFloatProperty* LifeTimeProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Context, RowStruct, Name::LifeTime, NCsProjectileData::Projectile.GetDisplayName());
		// InitialSpeed
	UFloatProperty* InitialSpeedProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Context, RowStruct, Name::InitialSpeed, NCsProjectileData::Projectile.GetDisplayName());
		// MaxSpeed
	UFloatProperty* MaxSpeedProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Context, RowStruct, Name::MaxSpeed, NCsProjectileData::Projectile.GetDisplayName());
		// GravityScale
	UFloatProperty* GravityScaleProperty = FCsLibrary_Property::FindPropertyByNameForInterfaceChecked<UFloatProperty>(Context, RowStruct, Name::GravityScale, NCsProjectileData::Projectile.GetDisplayName());

	// ICsData_ProjectileCollision
	bool Emulates_ICsData_ProjectileCollision = false;

	// ICsData_ProjectileStaticMeshVisual
	bool Emulates_ICsData_ProjectileStaticMeshVisual = false;
		// StaticMesh
	//FCsPrjStaticMesh* StaticMesh;

	if (EmulatedDataInterfaces.Find(NCsProjectileData::ProjectileStaticMeshVisual))
	{
	}

	if (EmulatedDataInterfaces.Find(NCsProjectileData::ProjectileTrailVisual))
	{
	}

		// CollisionPreset
	UStructProperty* CollisionPresetProperty = nullptr;

	if (EmulatedDataInterfaces.Find(NCsProjectileData::ProjectileCollision))
	{
		CollisionPresetProperty = FCsLibrary_Property::FindStructPropertyByNameForInterfaceChecked<FCsCollisionPreset>(Context, RowStruct, Name::GravityScale, NCsProjectileData::ProjectileCollision.GetDisplayName());
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
			FCsData_ProjectileEmuSlice* Data = new FCsData_ProjectileEmuSlice();

			checkf(EmulatedDataMap.Find(Name) == nullptr, TEXT("%s: Data has already been created for Row: %s."), *Context, *(Name.ToString()));

			EmulatedDataMap.Add(Name, Data);

			FCsData_ProjectileInterfaceMap* EmulatedInterfaceMap = new FCsData_ProjectileInterfaceMap();

			checkf(EmulatedDataInterfaceMap.Find(Name) == nullptr, TEXT("%s: Emulated Interface Map has already been created for Row: %s."), *Context, *(Name.ToString()));

			EmulatedDataInterfaceMap.Add(Name, EmulatedInterfaceMap);

			FCsInterfaceMap* InterfaceMap = EmulatedInterfaceMap->GetInterfaceMap();

			InterfaceMap->Add<ICsData_Projectile>(FCsData_ProjectileEmuSlice::Name, static_cast<ICsData_Projectile*>(Data));

			Data->SetInterfaceMap(InterfaceMap);

			TMap<FName, void*>& InterfaceImplMap = EmulatedDataInterfaceImplMap.FindOrAdd(Name);
			InterfaceImplMap.Add(FCsData_ProjectileEmuSlice::Name, Data);

			DataMap.Add(Name, Data);

			// LifeTime
			{
				float* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<float>(Context, LifeTimeProperty, RowPtr);

				Data->SetLifeTime(Value);
			}
			// InitialSpeed
			{
				float* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<float>(Context, InitialSpeedProperty, RowPtr);

				Data->SetInitialSpeed(Value);
			}
			// MaxSpeed
			{
				float* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<float>(Context, MaxSpeedProperty, RowPtr);

				Data->SetMaxSpeed(Value);
			}
			// GravityScale
			{
				float* Value = FCsLibrary_Property::ContainerPtrToValuePtrChecked<float>(Context, GravityScaleProperty, RowPtr);

				Data->SetGravityScale(Value);
			}
		}
		// ICsData_ProjectileCollision
		if (Emulates_ICsData_ProjectileCollision)
		{

		}
		// ICsData_ProjectileStaticMeshVisual
		if (Emulates_ICsData_ProjectileStaticMeshVisual)
		{

		}
	}
}

bool FCsManager_Projectile_DataHandler::DeconstructEmulatedData(const FName& InterfaceImplName, void* Data)
{
	// FCsData_ProjectileEmuSlice
	if (InterfaceImplName == FCsData_ProjectileEmuSlice::Name)
	{
		delete static_cast<FCsData_ProjectileEmuSlice*>(Data);
		return true;
	}
	// FCsData_ProjecitleVisualEmuSlice
	// FCsData_ProjectileCollisionEmuSlice
	return false;
}

#pragma endregion TCsManager_PooledObject_DataHandler Interface

const TSet<FECsProjectileData>& FCsManager_Projectile_DataHandler::GetEmulatedDataInterfaces(const FString& Context, const int32& Index)
{
	UObject* DataRootSetImpl			 = FCsLibrary_DataRootSet::GetImplChecked(Context, MyRoot);
	const FCsPrjDataRootSet& DataRootSet = FCsPrjLibrary_DataRootSet::GetChecked(Context, MyRoot);

	return DataRootSet.Projectiles[Index].EmulatedDataInterfaces;
}