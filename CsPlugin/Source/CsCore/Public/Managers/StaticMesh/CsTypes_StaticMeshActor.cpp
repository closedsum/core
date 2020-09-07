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
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsStaticMeshActorDeallocateMethod, LifeTime);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsStaticMeshActorDeallocateMethod, Complete);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsStaticMeshActorDeallocateMethod, ECsStaticMeshActorDeallocateMethod_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsStaticMeshActorDeallocateMethod_MAX;
}

#pragma endregion StaticMeshActorDeallocateMethod