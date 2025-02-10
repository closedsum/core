// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Script/CsScriptLibrary_Data_Beam.h"

// Data
#include "Data/CsData_BeamImplSlice.h"
// Beam
#include "Managers/Beam/Handler/CsManager_Beam_DataHandler.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Data_Beam)

// Cached
#pragma region

namespace NCsScriptLibraryDataBeam
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Beam, Construct);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Beam, ConstructFromObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Beam, AddSlice_Collision);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Beam, AddSliceFromObject_Collision);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Beam, AddSlice_VisualStaticMesh);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Beam, AddSliceFromObject_VisualStaticMesh);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Beam, AddSlice_VisualImpact);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Beam, AddSliceFromObject_VisualImpact);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Beam, AddSlice_DamagePoint);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Beam, AddSliceFromObject_DamagePoint);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Data_Beam::UCsScriptLibrary_Data_Beam(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_Data_Beam::Construct(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_BeamImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataBeam::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Construct : Context;

	typedef NCsBeam::NData::FImplSlice DataSliceType;

	if (!Slice.IsValid(Context))
		return false;

	DataSliceType* DataSlice = Slice.SafeConstructAsValue(Context, WorldContextObject, Name);

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Beam::ConstructFromObject(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataBeam::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ConstructFromObject : Context;

	typedef NCsBeam::NData::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::SafeConstruct(Context, WorldContextObject, Name, Object);

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Beam::AddSlice_Collision(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Beam_CollisionImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataBeam::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_Collision : Context;

	typedef NCsBeam::NData::NCollision::NImplSlice::FImplSlice DataSliceType;

	DataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Beam::AddSliceFromObject_Collision(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataBeam::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSliceFromObject_Collision : Context;

	typedef NCsBeam::NData::NCollision::NImplSlice::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::AddSafeSlice(Context, WorldContextObject, FName(*Name), Object);

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Beam::AddSlice_VisualStaticMesh(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Beam_VisualStaticMeshImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataBeam::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_VisualStaticMesh : Context;

	typedef NCsBeam::NData::NVisual::NStaticMesh::FImplSlice DataSliceType;

	DataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Beam::AddSliceFromObject_VisualStaticMesh(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataBeam::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_VisualStaticMesh : Context;

	typedef NCsBeam::NData::NVisual::NStaticMesh::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::AddSafeSlice(Context, WorldContextObject, FName(*Name), Object);
	
	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Beam::AddSlice_VisualImpact(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Beam_VisualImpactImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataBeam::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_VisualStaticMesh : Context;

	typedef NCsBeam::NData::NVisual::NImpact::FImplSlice DataSliceType;

	DataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Beam::AddSliceFromObject_VisualImpact(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataBeam::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSliceFromObject_VisualImpact : Context;

	typedef NCsBeam::NData::NVisual::NImpact::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::AddSafeSlice(Context, WorldContextObject, FName(*Name), Object);

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Beam::AddSlice_DamagePoint(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_Beam_DamagePointImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataBeam::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSlice_DamagePoint : Context;

	typedef NCsBeam::NData::NDamage::NPoint::FImplSlice DataSliceType;

	DataSliceType* DataSlice = Slice.AddSafeSliceAsValue(Ctxt, WorldContextObject, FName(*Name));

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Beam::AddSliceFromObject_DamagePoint(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataBeam::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddSliceFromObject_DamagePoint : Context;

	typedef NCsBeam::NData::NDamage::NPoint::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::AddSafeSlice(Context, WorldContextObject, FName(*Name), Object);

	return DataSlice && DataSlice->IsValid(Context);
}