// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Script/CsScriptLibrary_Data_Projectile.h"
#include "CsCore.h"

// Library
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
// Managers
#include "Managers/Projectile/CsManager_Projectile.h"
// Data
#include "Data/CsData_ProjectileImplSlice.h"
// Projectile
#include "Managers/Projectile/Handler/CsManager_Projectile_DataHandler.h"

// Cached
#pragma region

namespace NCsScriptLibraryDataProjectile
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, Construct);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, AddSlice_Collision);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, AddSlice_VisualStaticMesh);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Data_Projectile::UCsScriptLibrary_Data_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsScriptLibrary_Data_Projectile::Construct(const FString& Context, const UObject* WorldContextObject, const FString& Name)
{
	using namespace NCsScriptLibraryDataProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Construct : Context;

	typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;

	UCsManager_Projectile* Manager_Projectile = PrjManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_Projectile)
		return;

	#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
	typedef NCsProjectile::NData::IData DataType;
	typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType;

	DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = Manager_Projectile->GetDataHandler();

	#undef DataHandlerType

	typedef NCsProjectile::NData::FImplSlice DataSliceType;

	DataHandler->SafeConstructData<DataSliceType>(Ctxt, FName(*Name));

	// TODO: Eventually store copy of slice on a UObject.
}

void UCsScriptLibrary_Data_Projectile::AddSlice_Collision(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_CollisionImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_Collision : Context;

	typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;

	UCsManager_Projectile* Manager_Projectile = PrjManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_Projectile)
		return;

	#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
	typedef NCsProjectile::NData::IData DataType;
	typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType;

	DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = Manager_Projectile->GetDataHandler();

	#undef DataHandlerType

	typedef NCsProjectile::NData::NCollision::FImplSlice DataSliceType;
	typedef NCsProjectile::NData::NCollision::ICollision CollisionDataType;

	DataSliceType* DataSlice = DataHandler->AddSafeDataSlice<DataSliceType, CollisionDataType>(Ctxt, FName(*Name));

	Slice.CopyToSliceAsValue(DataSlice);

	// TODO: Eventually store copy of slice on a UObject.
}

void UCsScriptLibrary_Data_Projectile::AddSlice_VisualStaticMesh(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_VisualStaticMeshImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_VisualStaticMesh : Context;

	typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;

	UCsManager_Projectile* Manager_Projectile = PrjManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_Projectile)
		return;

	#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
	typedef NCsProjectile::NData::IData DataType;
	typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType;

	DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = Manager_Projectile->GetDataHandler();

	#undef DataHandlerType

	typedef NCsProjectile::NData::NVisual::NStaticMesh::FImplSlice DataSliceType;
	typedef NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshVisualDataType;

	DataSliceType* DataSlice = DataHandler->AddSafeDataSlice<DataSliceType, StaticMeshVisualDataType>(Ctxt, FName(*Name));

	Slice.CopyToSliceAsValue(DataSlice);

	// TODO: Eventually store copy of slice on a UObject.
}