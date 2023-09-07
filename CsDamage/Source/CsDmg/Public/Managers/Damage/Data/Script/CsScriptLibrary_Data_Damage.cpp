// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/Script/CsScriptLibrary_Data_Damage.h"
#include "CsDmg.h"

// Cached
#pragma region

namespace NCsScriptLibraryDataDamage
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Damage, Construct_Point);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data_Damage, ConstructFromObject_Point);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Data_Damage::UCsScriptLibrary_Data_Damage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_Data_Damage::Construct_Point(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_DamagePointImplSlice& Slice)
{
	using namespace NCsScriptLibraryDataDamage::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Construct_Point : Context;

	typedef NCsDamage::NData::NPoint::FImplSlice DataSliceType;

	if (!Slice.IsValid(Context))
		return false;

	DataSliceType* DataSlice = Slice.SafeConstructAsValue(Context, WorldContextObject, Name);

	return DataSlice && DataSlice->IsValid(Context);
}

bool UCsScriptLibrary_Data_Damage::ConstructFromObject_Point(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object)
{
	using namespace NCsScriptLibraryDataDamage::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ConstructFromObject_Point : Context;

	typedef NCsDamage::NData::NPoint::FImplSlice DataSliceType;

	DataSliceType* DataSlice = DataSliceType::SafeConstruct(Context, WorldContextObject, Name, Object);

	return DataSlice && DataSlice->IsValid(Context);
}