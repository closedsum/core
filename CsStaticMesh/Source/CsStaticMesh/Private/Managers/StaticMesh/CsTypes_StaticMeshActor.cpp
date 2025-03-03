// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"

// Types
#include "CsMacro_Misc.h"
// Library
	// Settings
#include "Settings/CsLibrary_StaticMeshSettings.h"
	// Common
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Utility
#include "Utility/CsLibrary_EnumStruct.h"
#include "Utility/CsStaticMeshLog.h"
// StaticMeshActor
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_StaticMeshActor)

// StaticMeshActor
#pragma region

namespace NCsStaticMeshActor
{
	namespace NCached
	{
		namespace Str
		{
			const FString StaticMeshActor = TEXT("StaticMeshActor");
		}
	}

	void FromEnumSettings(const FString& Context)
	{
		using namespace NCsStaticMeshActor::NCached;

		typedef NCsStaticMesh::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_StaticMeshActor();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_StaticMeshActor();
		Payload.EnumName				 = Str::StaticMeshActor;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsStaticMesh::FLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsStaticMeshActor::Get().ClearUserDefinedEnums();

		FromEnumSettings(Context);
	}

	const FECsStaticMeshActor& GetDefault()
	{
		typedef NCsStaticMesh::NSettings::FLibrary SettingsLibrary;

		return *(SettingsLibrary::GetDefault_ECsStaticMeshActor());
	}
}

#pragma endregion StaticMeshActor

// StaticMeshActorClass
#pragma region

namespace NCsStaticMeshActorClass
{
	namespace NCached
	{
		namespace Str
		{
			const FString StaticMeshActorClass = TEXT("StaticMeshActorClass");
		}
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

		CSSTATICMESH_API CS_ADD_TO_ENUM_MAP(LifeTime);
		CSSTATICMESH_API CS_ADD_TO_ENUM_MAP(Complete);
		CSSTATICMESH_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsStaticMeshActorDeallocateMethod_MAX, "MAX");
	}

	CSSTATICMESH_API const uint8 MAX = (uint8)Type::ECsStaticMeshActorDeallocateMethod_MAX;
}

#pragma endregion StaticMeshActorDeallocateMethod

using PayloadImplType = NCsStaticMeshActor::NPayload::NImpl::FImpl;

// FCsStaticMeshActorPooledInfo
#pragma region

void FCsStaticMeshActorPooledInfo::SetPayloadChecked(const FString& Context, PayloadImplType* Payload) const
{
	check(IsValidChecked(Context));

	Payload->Mesh = Mesh.GetChecked(Context);
	Payload->SetMaterials(Materials.GetChecked(Context));
	Payload->DeallocateMethod = GetDeallocateMethod();
	Payload->LifeTime					= LifeTime;
	Payload->AttachmentTransformRules	= AttachmentTransformRules;
	Payload->Bone						= Bone;
	Payload->TransformRules				= TransformRules;

	Payload->Transform.SetTranslation(Payload->Transform.GetTranslation() + Transform.GetTranslation());
	const FRotator3f Rotation = Payload->Transform.GetRotation().Rotator() + Transform.GetRotation().Rotator();
	Payload->Transform.SetRotation(Rotation.Quaternion());
	Payload->Transform.SetScale3D(Payload->Transform.GetScale3D() * Transform.GetScale3D());

	Payload->bCastShadow			= bCastShadow;
	Payload->bReceivesDecals		= bReceivesDecals;
	Payload->bUseAsOccluder			= bUseAsOccluder;
	Payload->bRenderCustomDepth		= bRenderCustomDepth;
	Payload->CustomDepthStencilValue = CustomDepthStencilValue;
}

bool FCsStaticMeshActorPooledInfo::SetSafePayload(const FString& Context, PayloadImplType* Payload, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	if (!Mesh.GetSafe(Context, Log))
		return false;

	Payload->Mesh = Mesh.GetChecked(Context);

	if (!Materials.GetSafe(Context, Log))
		return false;

	Payload->SetMaterials(Materials.GetChecked(Context));
	Payload->DeallocateMethod		= GetDeallocateMethod();
	Payload->LifeTime				= LifeTime;
	Payload->AttachmentTransformRules = AttachmentTransformRules;
	Payload->Bone					= Bone;
	Payload->TransformRules			= TransformRules;

	Payload->Transform.SetTranslation(Payload->Transform.GetTranslation() + Transform.GetTranslation());
	const FRotator3f Rotation = Payload->Transform.GetRotation().Rotator() + Transform.GetRotation().Rotator();
	Payload->Transform.SetRotation(Rotation.Quaternion());
	Payload->Transform.SetScale3D(Payload->Transform.GetScale3D() * Transform.GetScale3D());

	Payload->bCastShadow			= bCastShadow;
	Payload->bReceivesDecals		= bReceivesDecals;
	Payload->bUseAsOccluder			= bUseAsOccluder;
	Payload->bRenderCustomDepth		= bRenderCustomDepth;
	Payload->CustomDepthStencilValue = CustomDepthStencilValue;
	return true;
}	

bool FCsStaticMeshActorPooledInfo::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid.
	check(Mesh.GetChecked(Context));
	// Check Materials is Valid
	if (!Materials.Materials.IsEmpty())
	{
		check(Materials.IsValidChecked(Context));
		check(CsMaterialLibrary::IsValidChecked(Context, Mesh.Get(), Materials.Get()));
	}
	// Check Type is Valid
	check(EMCsStaticMeshActor::Get().IsValidEnumChecked(Context, Type));

	if (!Transform.Equals(FTransform3f::Identity))
	{
		checkf(TransformRules != 0, TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString()));
	}
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(CustomDepthStencilValue, 0)
	CS_IS_INT_LESS_THAN_OR_EQUAL_CHECKED(CustomDepthStencilValue, 255)
	return true;
}

bool FCsStaticMeshActorPooledInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Mesh is Valid.
	if (!Mesh.IsValid(Context, Log))
		return false;
	// Check Materials is Valid
	if (!Materials.Materials.IsEmpty())
	{
		if (!Materials.IsValid(Context, Log))
			return false;

		if (!CsMaterialLibrary::IsValid(Context, Mesh.Get(), Materials.Get(), Log))
			return false;
	}
	// Check Type is Valid
	CS_IS_ENUM_STRUCT_VALID(EMCsStaticMeshActor, FECsStaticMeshActor, Type)

	if (!Transform.Equals(FTransform3f::Identity))
	{
		if (TransformRules == 0)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString())));
			return true;
		}
	}
	CS_IS_INT_GREATER_THAN_OR_EQUAL(CustomDepthStencilValue, 0)
	CS_IS_INT_LESS_THAN_OR_EQUAL(CustomDepthStencilValue, 255)
	return true;
}

#pragma endregion FCsStaticMeshActorPooledInfo

// NCsStaticMeshActor::NPayload::EChange
#pragma region

namespace NCsStaticMeshPayloadChange
{
	namespace Ref
	{
		typedef EMCsStaticMeshPayloadChange EnumMapType;

		CSSTATICMESH_API CS_ADD_TO_ENUM_FLAG_MAP(StaticMesh);
		CSSTATICMESH_API CS_ADD_TO_ENUM_FLAG_MAP(Materials);
		CSSTATICMESH_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(KeepRelativeTransform, "Keep Relative Transform");
		CSSTATICMESH_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(KeepWorldTransform, "Keep World Transform");
		CSSTATICMESH_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(SnapToTargetNotIncludingScale, "Snap to Target not Including Scale");
		CSSTATICMESH_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(SnapToTargetIncludingScale, "Snap to Target Including Scale");
		CSSTATICMESH_API CS_ADD_TO_ENUM_FLAG_MAP(Transform);
	}

	CSSTATICMESH_API const int32 None = 0;
	CSSTATICMESH_API const int32 All = 255; // 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128
}

#pragma endregion NCsStaticMeshActor::NPayload::EChange