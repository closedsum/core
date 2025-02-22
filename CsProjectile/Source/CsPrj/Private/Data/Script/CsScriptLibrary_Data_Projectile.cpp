// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Script/CsScriptLibrary_Data_Projectile.h"

// Data
#include "Data/CsData_ProjectileImplSlice.h"
// Projectile
#include "Managers/Projectile/Handler/CsManager_Projectile_DataHandler.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Data_Projectile)

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsScriptLibrary_Data_Projectile)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Data_Projectile, Construct)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Data_Projectile, ConstructFromObject)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Data_Projectile, AddSlice_Collision)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Data_Projectile, AddSliceFromObject_Collision)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Data_Projectile, AddSlice_VisualStaticMesh)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Data_Projectile, AddSliceFromObject_VisualStaticMesh)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Data_Projectile, AddSlice_VisualImpact)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Data_Projectile, AddSliceFromObject_VisualImpact)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Data_Projectile, AddSlice_DamagePoint)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Data_Projectile, AddSliceFromObject_DamagePoint)
CS_END_CACHED_FUNCTION_NAME

#pragma endregion Cached

UCsScriptLibrary_Data_Projectile::UCsScriptLibrary_Data_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

using DataSliceType = NCsProjectile::NData::FImplSlice;
using CollisionDataSliceType = NCsProjectile::NData::NCollision::NImplSlice::FImplSlice;
using StaticMeshDataSliceType = NCsProjectile::NData::NVisual::NStaticMesh::NImplSlice::FImplSlice;
using ImpactDataSliceType = NCsProjectile::NData::NVisual::NImpact::FImplSlice;
using DamageDataSliceType = NCsProjectile::NData::NDamage::NPoint::FImplSlice;

bool UCsScriptLibrary_Data_Projectile::Construct(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_ProjectileImplSlice& Slice)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Construct);

	if (!Slice.IsValid(Context))
		return false;

	DataSliceType* DataSlice = Slice.SafeConstructAsValue(Context, WorldContextObject, Name);

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::ConstructFromObject(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(ConstructFromObject);

	DataSliceType* DataSlice = DataSliceType::SafeConstruct(Context, WorldContextObject, Name, Object);

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSlice_Collision(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_CollisionImplSlice& Slice)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(AddSlice_Collision);

	CollisionDataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSliceFromObject_Collision(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(AddSliceFromObject_Collision);

	CollisionDataSliceType* DataSlice = CollisionDataSliceType::AddSafeSlice(Context, WorldContextObject, FName(*Name), Object);

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSlice_VisualStaticMesh(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_VisualStaticMeshImplSlice& Slice)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(AddSlice_VisualStaticMesh);

	StaticMeshDataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSliceFromObject_VisualStaticMesh(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(AddSliceFromObject_VisualStaticMesh);

	StaticMeshDataSliceType* DataSlice = StaticMeshDataSliceType::AddSafeSlice(Context, WorldContextObject, FName(*Name), Object);
	
	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSlice_VisualImpact(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_VisualImpactImplSlice& Slice)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(AddSlice_VisualImpact);

	ImpactDataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSliceFromObject_VisualImpact(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(AddSliceFromObject_VisualImpact);

	ImpactDataSliceType* DataSlice = ImpactDataSliceType::AddSafeSlice(Context, WorldContextObject, FName(*Name), Object);

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSlice_DamagePoint(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_DamagePointImplSlice& Slice)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(AddSlice_DamagePoint);

	DamageDataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSliceFromObject_DamagePoint(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(AddSliceFromObject_DamagePoint);

	DamageDataSliceType* DataSlice = DamageDataSliceType::AddSafeSlice(Context, WorldContextObject, FName(*Name), Object);

	return DataSlice && DataSlice->IsValid(Context);
}