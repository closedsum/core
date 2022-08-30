// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
#include "Material/CsLibrary_Material.h"
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

	const FECsSkeletalMeshActor& GetDefault()
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("NCsSkeletalMeshActor::GetDefault: Failed to file settings of type: UCsDeveloperSettings."));

		return Settings->Default_ECsSkeletalMeshActor;
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
	if (Materials.Materials.Num() > CS_EMPTY)
	{
		check(Materials.IsValidChecked(Context));

		typedef NCsMaterial::FLibrary MaterialLibrary;

		check(MaterialLibrary::IsValidChecked(Context, Mesh.Get(), Materials.Get()));
	}
	// Check Type is Valid
	check(EMCsSkeletalMeshActor::Get().IsValidEnumChecked(Context, Type));

	if (!Transform.Equals(FTransform::Identity))
	{
		checkf(TransformRules != 0, TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString()));
	}
	return true;
}

bool FCsSkeletalMeshActorPooledInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Mesh is Valid.
	if (!Mesh.IsValid(Context, Log))
		return false;
	// Check Materials is Valid
	if (Materials.Materials.Num() > CS_EMPTY)
	{
		if (!Materials.IsValid(Context, Log))
			return false;

		typedef NCsMaterial::FLibrary MaterialLibrary;

		if (!MaterialLibrary::IsValid(Context, Mesh.Get(), Materials.Get(), Log))
			return false;
	}
	// Check Type is Valid
	CS_IS_ENUM_STRUCT_VALID(EMCsSkeletalMeshActor, FECsSkeletalMeshActor, Type)

	if (!Transform.Equals(FTransform::Identity))
	{
		if (TransformRules == 0)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString())));
			return true;
		}
	}
	return true;
}

#pragma endregion FCsSkeletalMeshActorPooledInfo

// NCsSkeletalMeshActor::NPayload::EChange
#pragma region

namespace NCsSkeletalMeshPayloadChange
{
	namespace Ref
	{
		typedef EMCsSkeletalMeshPayloadChange EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(SkeletalMesh);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Materials);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(KeepRelativeTransform, "Keep Relative Transform");
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(KeepWorldTransform, "Keep World Transform");
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(SnapToTargetNotIncludingScale, "Snap to Target not Including Scale");
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(SnapToTargetIncludingScale, "Snap to Target Including Scale");
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Transform);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(AnimInstance);
	}

	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 255; // 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128
}

#pragma endregion NCsSkeletalMeshActor::NPayload::EChange