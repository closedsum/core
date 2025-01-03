// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"

// Types
#include "CsMacro_Misc.h"
// Library
	// Settings
#include "Settings/CsLibrary_SkeletalMeshSettings.h"
	// Common
#include "Library/CsLibrary_Valid.h"
#include "Material/CsLibrary_Material.h"
// Utility
#include "Utility/CsLibrary_EnumStruct.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_SkeletalMeshActor)


// SkeletalMeshActor
#pragma region

namespace NCsSkeletalMeshActor
{
	namespace NCached
	{
		namespace Str
		{
			const FString SkeletalMeshActor = TEXT("SkeletalMeshActor");
		}
	}

	void FromEnumSettings(const FString& Context)
	{
		using namespace NCsSkeletalMeshActor::NCached;

		typedef NCsSkeletalMesh::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_SkeletalMeshActor();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_SkeletalMeshActor();
		Payload.EnumName				 = Str::SkeletalMeshActor;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsSkeletalMesh::FLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
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

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsSkeletalMeshActor>(Context, ContextRoot, DataRootSet->WidgetActorClasses, Str::SkeletalMeshActor, &NCsSkeletalMesh::FLog::Warning);
	}
	*/
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsSkeletalMeshActor::Get().ClearUserDefinedEnums();

		FromEnumSettings(Context);

		//FromDataTable(Context, ContextRoot);
	}

	const FECsSkeletalMeshActor& GetDefault()
	{
		typedef NCsSkeletalMesh::NSettings::FLibrary SettingsLibrary;

		return *(SettingsLibrary::GetDefault_ECsSkeletalMeshActor());
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

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsSkeletalMeshActorClass>(Context, ContextRoot, DataRootSet->WidgetActorClasses, Str::SkeletalMeshActorClass, &NCsSkeletalMesh::FLog::Warning);
	}
	*/
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
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

		CSSKELETALMESH_API CS_ADD_TO_ENUM_MAP(LifeTime);
		CSSKELETALMESH_API CS_ADD_TO_ENUM_MAP(Complete);
		CSSKELETALMESH_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSkeletalMeshActorDeallocateMethod_MAX, "MAX");
	}

	CSSKELETALMESH_API const uint8 MAX = (uint8)Type::ECsSkeletalMeshActorDeallocateMethod_MAX;
}

#pragma endregion SkeletalMeshActorDeallocateMethod

// FCsSkeletalMeshActorPooledInfo
#pragma region

bool FCsSkeletalMeshActorPooledInfo::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid.
	check(Mesh.IsValidChecked(Context));
	// Check Materials is Valid
	if (!Materials.Materials.IsEmpty())
	{
		check(Materials.IsValidChecked(Context));

		typedef NCsMaterial::FLibrary MaterialLibrary;

		check(MaterialLibrary::IsValidChecked(Context, Mesh.Get(), Materials.Get()));
	}
	// Check Type is Valid
	check(EMCsSkeletalMeshActor::Get().IsValidEnumChecked(Context, Type));

	if (!Transform.Equals(FTransform3f::Identity))
	{
		checkf(TransformRules != 0, TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString()));
	}
	return true;
}

bool FCsSkeletalMeshActorPooledInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsSkeletalMesh::FLog::Warning*/) const
{
	// Check Mesh is Valid.
	if (!Mesh.IsValid(Context, Log))
		return false;
	// Check Materials is Valid
	if (!Materials.Materials.IsEmpty())
	{
		if (!Materials.IsValid(Context, Log))
			return false;

		typedef NCsMaterial::FLibrary MaterialLibrary;

		if (!MaterialLibrary::IsValid(Context, Mesh.Get(), Materials.Get(), Log))
			return false;
	}
	// Check Type is Valid
	CS_IS_ENUM_STRUCT_VALID(EMCsSkeletalMeshActor, FECsSkeletalMeshActor, Type)

	if (!Transform.Equals(FTransform3f::Identity))
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

		CSSKELETALMESH_API CS_ADD_TO_ENUM_FLAG_MAP(SkeletalMesh);
		CSSKELETALMESH_API CS_ADD_TO_ENUM_FLAG_MAP(Materials);
		CSSKELETALMESH_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(KeepRelativeTransform, "Keep Relative Transform");
		CSSKELETALMESH_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(KeepWorldTransform, "Keep World Transform");
		CSSKELETALMESH_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(SnapToTargetNotIncludingScale, "Snap to Target not Including Scale");
		CSSKELETALMESH_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(SnapToTargetIncludingScale, "Snap to Target Including Scale");
		CSSKELETALMESH_API CS_ADD_TO_ENUM_FLAG_MAP(Transform);
		CSSKELETALMESH_API CS_ADD_TO_ENUM_FLAG_MAP(AnimInstance);
	}

	CSSKELETALMESH_API const int32 None = 0;
	CSSKELETALMESH_API const int32 All = 255; // 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128
}

#pragma endregion NCsSkeletalMeshActor::NPayload::EChange