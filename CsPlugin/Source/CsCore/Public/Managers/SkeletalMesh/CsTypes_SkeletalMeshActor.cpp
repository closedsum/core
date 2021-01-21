// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"
#include "CsCore.h"

// Settings
#include "Settings/CsDeveloperSettings.h"
// Utility
#include "Utility/CsLog.h"
#include "Utility/CsPopulateEnumMapFromSettings.h"

// SkeletalMeshActor
#pragma region

namespace NCsSkeletalMeshActor
{
	namespace Str
	{
		const FString SkeletalMeshActor = TEXT("SkeletalMeshActor");
	}

	void FromEnumSettings(const FString& Context)
	{
		FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsDeveloperSettings, EMCsSkeletalMeshActor, FECsSkeletalMeshActor>(Context, Str::SkeletalMeshActor, &FCsLog::Warning);
	}

	/*
	const FCsDataRootSet* GetDataRootSet(const FString& Context, UObject* ContextRoot)
	{
		return FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsDataRootSet, ICsGetDataRootSet, &ICsGetDataRootSet::GetCsDataRootSet>(Context, ContextRoot);
	}
	*/
	/*
	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsDataRootSet* DataRootSet = FCsPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsSkeletalMeshActor>(Context, ContextRoot, DataRootSet->WidgetActorClasses, Str::SkeletalMeshActor, &FCsLog::Warning);
	}
	*/
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		EMCsSkeletalMeshActor::Get().ClearUserDefinedEnums();

		FromEnumSettings(Context);

		//FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion SkeletalMeshActor

// SkeletalMeshActorClass
#pragma region

namespace NCsSkeletalMeshActorClass
{
	namespace Str
	{
		const FString SkeletalMeshActorClass = TEXT("SkeletalMeshActorClass");
	}
	/*
	const FCsDataRootSet* GetDataRootSet(const FString& Context, UObject* ContextRoot)
	{
		return FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsDataRootSet, ICsGetDataRootSet, &ICsGetDataRootSet::GetCsDataRootSet>(Context, ContextRoot);
	}
	*/
	/*
	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsDataRootSet* DataRootSet = FCsPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsSkeletalMeshActorClass>(Context, ContextRoot, DataRootSet->WidgetActorClasses, Str::SkeletalMeshActorClass, &FCsLog::Warning);
	}
	*/
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		EMCsSkeletalMeshActorClass::Get().ClearUserDefinedEnums();

		//FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion SkeletalMeshActorClass

// SkeletalMeshActorDeallocateMethod
#pragma region

namespace NCsSkeletalMeshActorDeallocateMethod
{
	namespace Ref
	{
		typedef EMCsSkeletalMeshActorDeallocateMethod EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(LifeTime);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Complete);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSkeletalMeshActorDeallocateMethod_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSkeletalMeshActorDeallocateMethod_MAX;
}

#pragma endregion SkeletalMeshActorDeallocateMethod

// FCsSkeletalMeshActorPooledInfo
#pragma region

bool FCsSkeletalMeshActorPooledInfo::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid.
	check(Mesh.IsValidChecked(Context));
	// Check Materials is Valid
	check(Materials.IsValidChecked(Context));
	// Check Type is Valid
	check(EMCsSkeletalMeshActor::Get().IsValidEnumChecked(Context, Type));

	if (!Transform.Equals(FTransform::Identity))
	{
		checkf(TransformRules != 0, TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString()));
	}
	return true;
}

#pragma endregion FCsSkeletalMeshActorPooledInfo