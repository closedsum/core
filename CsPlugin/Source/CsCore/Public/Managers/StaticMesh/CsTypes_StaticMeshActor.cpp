// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"
#include "CsCore.h"

// Settings
#include "Settings/CsDeveloperSettings.h"
// Utility
#include "Utility/CsLog.h"
#include "Utility/CsPopulateEnumMapFromSettings.h"

// StaticMeshActor
#pragma region

namespace NCsStaticMeshActor
{
	namespace Str
	{
		const FString StaticMeshActor = TEXT("StaticMeshActor");
	}

	void FromEnumSettings(const FString& Context)
	{
		FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsDeveloperSettings, EMCsStaticMeshActor, FECsStaticMeshActor>(Context, Str::StaticMeshActor, &FCsLog::Warning);
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

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsStaticMeshActor>(Context, ContextRoot, DataRootSet->WidgetActorClasses, Str::StaticMeshActor, &FCsLog::Warning);
	}
	*/
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		EMCsStaticMeshActor::Get().ClearUserDefinedEnums();

		FromEnumSettings(Context);

		//FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion StaticMeshActor

// StaticMeshActorClass
#pragma region

namespace NCsStaticMeshActorClass
{
	namespace Str
	{
		const FString StaticMeshActorClass = TEXT("StaticMeshActorClass");
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

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsStaticMeshActorClass>(Context, ContextRoot, DataRootSet->WidgetActorClasses, Str::StaticMeshActorClass, &FCsLog::Warning);
	}
	*/
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		EMCsStaticMeshActorClass::Get().ClearUserDefinedEnums();

		//FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion StaticMeshActorClass

// StaticMeshActorDeallocateMethod
#pragma region

namespace NCsStaticMeshActorDeallocateMethod
{
	namespace Ref
	{
		typedef EMCsStaticMeshActorDeallocateMethod EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(LifeTime);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Complete);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsStaticMeshActorDeallocateMethod_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsStaticMeshActorDeallocateMethod_MAX;
}

#pragma endregion StaticMeshActorDeallocateMethod

// FCsStaticMeshActorPooledInfo
#pragma region

bool FCsStaticMeshActorPooledInfo::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid.
	check(GetChecked(Context));
	// Check Type is Valid
	check(EMCsStaticMeshActor::Get().IsValidEnumChecked(Context, Type));

	if (!Transform.Equals(FTransform::Identity))
	{
		checkf(TransformRules != 0, TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString()));
	}
	return true;
}

#pragma endregion FCsStaticMeshActorPooledInfo