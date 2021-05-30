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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, ConstructFromObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, AddSlice_Collision);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, AddSlice_VisualStaticMesh);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, AddSliceFromObject_VisualStaticMesh);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, AddSlice_VisualImpact);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Data_Projectile::UCsScriptLibrary_Data_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
#define CS_TEMP_GET_DATA_HANDLER \
	typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary; \
	\
	UCsManager_Projectile* Manager_Projectile = PrjManagerLibrary::GetSafe(Ctxt, WorldContextObject); \
	\
	if (!Manager_Projectile) \
		return false; \
	\
	typedef NCsProjectile::NData::IData DataType; \
	typedef NCsProjectile::NData::FInterfaceMap DataInterfaceMapType; \
	\
	DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler = Manager_Projectile->GetDataHandler();

bool UCsScriptLibrary_Data_Projectile::Construct(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_ProjectileImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Construct : Context;

	typedef NCsProjectile::NData::FImplSlice DataSliceType;

	if (!Slice.IsValid(Context))
		return false;

	DataSliceType* DataSlice = Slice.SafeConstructAsValue(Context, WorldContextObject, Name);

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::ConstructFromObject(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ConstructFromObject : Context;

	typedef NCsProjectile::NData::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::SafeConstruct(Context, WorldContextObject, Name, Object);

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSlice_Collision(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_CollisionImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_Collision : Context;

	CS_TEMP_GET_DATA_HANDLER

	typedef NCsProjectile::NData::NCollision::FImplSlice DataSliceType;
	typedef NCsProjectile::NData::NCollision::ICollision CollisionDataType;

	DataSliceType* DataSlice = DataHandler->AddSafeDataSlice<DataSliceType, CollisionDataType>(Ctxt, FName(*Name));

	if (!DataSlice)
		return false;

	Slice.CopyToSliceAsValue(DataSlice);

	// TODO: Eventually store copy of slice on a UObject.
	return true;
}

bool UCsScriptLibrary_Data_Projectile::AddSlice_VisualStaticMesh(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_VisualStaticMeshImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_VisualStaticMesh : Context;

	typedef NCsProjectile::NData::NVisual::NStaticMesh::FImplSlice DataSliceType;

	DataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSliceFromObject_VisualStaticMesh(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_VisualStaticMesh : Context;

	typedef NCsProjectile::NData::NVisual::NStaticMesh::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::AddSafeSlice(Context, WorldContextObject, FName(*Name), Object);
	
	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSlice_VisualImpact(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_VisualImpactImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_VisualStaticMesh : Context;

	CS_TEMP_GET_DATA_HANDLER

	typedef NCsProjectile::NData::NVisual::NImpact::FImplSlice DataSliceType;
	typedef NCsProjectile::NData::NVisual::NImpact::IImpact ImpactVisualDataType;

	DataSliceType* DataSlice = DataHandler->AddSafeDataSlice<DataSliceType, ImpactVisualDataType>(Ctxt, FName(*Name));

	if (!DataSlice)
		return false;

	Slice.CopyToSliceAsValue(DataSlice);

	// TODO: Eventually store copy of slice on a UObject.
	return true;
}

#undef DataHandlerType
#undef CS_TEMP_GET_DATA_HANDLER