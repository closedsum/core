// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
#include "Material/CsLibrary_Material.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Utility
#include "Utility/CsLog.h"
#include "Utility/CsPopulateEnumMapFromSettings.h"
// StaticMeshActor
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"

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

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		EMCsStaticMeshActor::Get().ClearUserDefinedEnums();

		FromEnumSettings(Context);
	}

	const FECsStaticMeshActor& GetDefault()
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("NCsStaticMeshActor::GetDefault: Failed to file settings of type: UCsDeveloperSettings."));

		return Settings->Default_ECsStaticMeshActor; 
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

#define PayloadType NCsStaticMeshActor::NPayload::FImpl
void FCsStaticMeshActorPooledInfo::SetPayloadChecked(const FString& Context, PayloadType* Payload) const
{
	check(IsValidChecked(Context));

	Payload->Mesh = Mesh.GetChecked(Context);
	Payload->SetMaterials(Materials.GetChecked(Context));
	Payload->DeallocateMethod = GetDeallocateMethod();
	Payload->LifeTime = LifeTime;
	Payload->AttachmentTransformRules = AttachmentTransformRules;
	Payload->Bone = Bone;
	Payload->TransformRules = TransformRules;

	Payload->Transform.SetTranslation(Payload->Transform.GetTranslation() + Transform.GetTranslation());
	const FRotator Rotation = Payload->Transform.GetRotation().Rotator() + Transform.GetRotation().Rotator();
	Payload->Transform.SetRotation(Rotation.Quaternion());
	Payload->Transform.SetScale3D(Payload->Transform.GetScale3D() * Transform.GetScale3D());

	Payload->bCastShadow = bCastShadow;
	Payload->bReceivesDecals = bReceivesDecals;
	Payload->bUseAsOccluder = bUseAsOccluder;
}

bool FCsStaticMeshActorPooledInfo::SetSafePayload(const FString& Context, PayloadType* Payload, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	if (!Mesh.GetSafe(Context, Log))
		return false;

	Payload->Mesh = Mesh.GetChecked(Context);

	if (!Materials.GetSafe(Context, Log))
		return false;

	Payload->SetMaterials(Materials.GetChecked(Context));
	Payload->DeallocateMethod = GetDeallocateMethod();
	Payload->LifeTime = LifeTime;
	Payload->AttachmentTransformRules = AttachmentTransformRules;
	Payload->Bone = Bone;
	Payload->TransformRules = TransformRules;

	Payload->Transform.SetTranslation(Payload->Transform.GetTranslation() + Transform.GetTranslation());
	const FRotator Rotation = Payload->Transform.GetRotation().Rotator() + Transform.GetRotation().Rotator();
	Payload->Transform.SetRotation(Rotation.Quaternion());
	Payload->Transform.SetScale3D(Payload->Transform.GetScale3D() * Transform.GetScale3D());

	Payload->bCastShadow = bCastShadow;
	Payload->bReceivesDecals = bReceivesDecals;
	Payload->bUseAsOccluder = bUseAsOccluder;
	return true;
}	

#undef PayloadType

bool FCsStaticMeshActorPooledInfo::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid.
	check(Mesh.GetChecked(Context));
	// Check Materials is Valid
	if (Materials.Materials.Num() > CS_EMPTY)
	{
		check(Materials.IsValidChecked(Context));

		typedef NCsMaterial::FLibrary MaterialLibrary;

		check(MaterialLibrary::IsValidChecked(Context, Mesh.Get(), Materials.Get()));
	}
	// Check Type is Valid
	check(EMCsStaticMeshActor::Get().IsValidEnumChecked(Context, Type));

	if (!Transform.Equals(FTransform::Identity))
	{
		checkf(TransformRules != 0, TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString()));
	}
	return true;
}

bool FCsStaticMeshActorPooledInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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
	CS_IS_ENUM_STRUCT_VALID(EMCsStaticMeshActor, FECsStaticMeshActor, Type)

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

#pragma endregion FCsStaticMeshActorPooledInfo

// NCsStaticMeshActor::NPayload::EChange
#pragma region

namespace NCsStaticMeshPayloadChange
{
	namespace Ref
	{
		typedef EMCsStaticMeshPayloadChange EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(StaticMesh);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Materials);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(KeepRelativeTransform, "Keep Relative Transform");
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(KeepWorldTransform, "Keep World Transform");
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(SnapToTargetNotIncludingScale, "Snap to Target not Including Scale");
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(SnapToTargetIncludingScale, "Snap to Target Including Scale");
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Transform);
	}

	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 255; // 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128
}

#pragma endregion NCsStaticMeshActor::NPayload::EChange