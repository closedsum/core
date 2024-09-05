// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Script/CsScriptLibrary_Data_Projectile.h"

// Data
#include "Data/CsData_ProjectileImplSlice.h"
// Projectile
#include "Managers/Projectile/Handler/CsManager_Projectile_DataHandler.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Data_Projectile)

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, AddSliceFromObject_Collision);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, AddSlice_VisualStaticMesh);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, AddSliceFromObject_VisualStaticMesh);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, AddSlice_VisualImpact);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, AddSliceFromObject_VisualImpact);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, AddSlice_DamagePoint);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Projectile, AddSliceFromObject_DamagePoint);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Data_Projectile::UCsScriptLibrary_Data_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

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

	typedef NCsProjectile::NData::NCollision::FImplSlice DataSliceType;

	DataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSliceFromObject_Collision(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSliceFromObject_Collision : Context;

	typedef NCsProjectile::NData::NCollision::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::AddSafeSlice(Context, WorldContextObject, FName(*Name), Object);

	return DataSlice && DataSlice->IsValid(Context);
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

	typedef NCsProjectile::NData::NVisual::NImpact::FImplSlice DataSliceType;

	DataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSliceFromObject_VisualImpact(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSliceFromObject_VisualImpact : Context;

	typedef NCsProjectile::NData::NVisual::NImpact::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::AddSafeSlice(Context, WorldContextObject, FName(*Name), Object);

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSlice_DamagePoint(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Projectile_DamagePointImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_DamagePoint : Context;

	typedef NCsProjectile::NData::NDamage::NPoint::FImplSlice DataSliceType;

	DataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Projectile::AddSliceFromObject_DamagePoint(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataProjectile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSliceFromObject_DamagePoint : Context;

	typedef NCsProjectile::NData::NDamage::NPoint::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::AddSafeSlice(Context, WorldContextObject, FName(*Name), Object);

	return DataSlice && DataSlice->IsValid(Context);
}