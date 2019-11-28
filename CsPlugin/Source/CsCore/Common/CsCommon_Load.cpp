// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Common/CsCommon_Load.h"
#include "CsCore.h"
#include "CsCVars.h"

// Type
#include "Types/CsTypes.h"
#include "Managers/Input/CsTypes_Input.h"
#include "UI/CsTypes_UI.h"
#include "Types/CsTypes_FX.h"
#include "Types/CsTypes_Sound.h"
#include "Types/CsTypes_Anim.h"
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "Types/CsTypes_Weapon.h"
#include "Types/CsTypes_Damage.h"
#include "Types/CsTypes_Character.h"
#include "Types/CsTypes_Interactive.h"
#include "Types/CsTypes_Item.h"
#include "Types/CsTypes_Recipe.h"
#include "Types/CsTypes_Math.h"
#include "Types/CsTypes_Sense.h"
// Data
#include "Data/CsData.h"
#include "Data/CsData_ProjectileBase.h"
#include "Data/CsData_ProjectileImpact.h"

// Cache
#pragma region

namespace NCsCommonLoadCached
{
	namespace Str
	{
		const FString Transform = TEXT("Transform");
		const FString Rotation = TEXT("Rotation");
		const FString Translation = TEXT("Translation");
		const FString Scale = TEXT("Scale");

		const FString Mesh = TEXT("Mesh");
		const FString Mat = TEXT("Mat");
		const FString Anim = TEXT("Anim");
		const FString Bp = TEXT("Bp");

		const FString CollisionEnabled = TEXT("ECollisionEnabled");
		const FString CollisionChannel = TEXT("ECollisionChannel");
		const FString CollisionResponse = TEXT("ECollisionResponse");
		const FString HorizTextAligment = TEXT("EHorizTextAligment");
		const FString VerticalTextAligment = TEXT("EVerticalTextAligment");
		const FString CsLoadFlags_Editor = TEXT("ECsLoadFlags_Editor");
		const FString CsFxPriority = TEXT("ECsFxPriority");
		const FString CsSoundPriority = TEXT("ECsSoundPriority");
		const FString CsInteractiveCollision = TEXT("ECsInteractiveCollision");
		const FString CsProjectileMovementFunctionType = TEXT("ECsProjectileMovementFunctionType");
		const FString CsParametricFunctionType = TEXT("ECsParametricFunctionType");
		const FString CsLoadFlags = TEXT("ECsLoadFlags");
		const FString CsItemMemberValueType = TEXT("ECsItemMemberValueType");
		const FString CsItemOnConsumeContentAction = TEXT("ECsItemOnConsumeContentAction");
		const FString CsEasingType = TEXT("ECsEasingType");

		const FString BitmaskEnum = TEXT("BitmaskEnum");

		const FString StaticMesh = TEXT("StaticMesh");
		const FString Static_Mesh = TEXT("Static Mesh");
		const FString SkeletalMesh = TEXT("SkeletalMesh");
		const FString Skeletal_Mesh = TEXT("Skeletal Mesh");
		const FString MaterialInstance = TEXT("MaterialInstance");
		const FString MaterialInstanceConstant = TEXT("MaterialInstanceConstant");
		const FString PhysicalMaterial = TEXT("PhysicalMaterial");
		const FString Physical_Material = TEXT("Physical Material");
		const FString PhysicsAsset = TEXT("PhysicsAsset");
		const FString Physics_Asset = TEXT("Physics Asset");
		const FString AnimSequence = TEXT("AnimSequence");
		const FString Anim_Sequence = TEXT("Anim Sequence");
		const FString AnimMontage = TEXT("AnimMontage");
		const FString Anim_Montage = TEXT("Anim Montage");
		const FString BlendSpace1D = TEXT("BlendSpace1D");
		const FString Blend_Space_1D = TEXT("Blend Space 1D");
		const FString BlendSpace = TEXT("BlendSpace");
		const FString Blend_Space = TEXT("Blend Space");
		const FString AimOffsetBlendSpace = TEXT("AimOffsetBlendSpace");
		const FString Aim_Offset_Blend_Space = TEXT("Aim Offset Blend Space");
		const FString SoundCue = TEXT("SoundCue");
		const FString Sound_Cue = TEXT("Sound Cue");
		const FString ParticleSystem = TEXT("ParticleSystem");
		const FString Particle_System = TEXT("Particle System");
		const FString CurveFloat = TEXT("CurveFloat");
		const FString Curve_Float = TEXT("Curve Float");
		const FString CurveVector = TEXT("CurveVector");
		const FString Curve_Vector = TEXT("Curve Vector");

		const FString CsData_ProjectileBase = TEXT("CsData_ProjectileBase");
		const FString CsData_ProjectileImpact = TEXT("CsData_ProjectileImpact");
	}
}

#pragma endregion Cache

UCsCommon_Load::UCsCommon_Load(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Enum to String Conversion
#pragma region

#pragma endregion Enum to String Conversion

// Enum to Enum Conversion
#pragma region

ECsLoadFlags UCsCommon_Load::ViewTypeToLoadFlags(const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	if (ViewType == ECsViewType::FirstPerson)
		return ECsLoadFlags::Game1P;
	if (ViewType == ECsViewType::ThirdPerson)
		return IsLow ? ECsLoadFlags::Game3PLow : ECsLoadFlags::Game3P;
	if (ViewType == ECsViewType::VR)
		return ECsLoadFlags::GameVR;
	return ECsLoadFlags::All;
}

#pragma endregion Enum to Enum Conversion

// Base Structure
#pragma region

FString UCsCommon_Load::ToString_FInt32Interval(const FInt32Interval &Interval)
{
	return FString::Printf(TEXT("Min=%d Max=%d"), Interval.Min, Interval.Max);
}

bool UCsCommon_Load::InitFromString_FInt32Interval(const FString& InSourceString, FInt32Interval &OutInterval)
{
	OutInterval.Min = OutInterval.Max = 0;

	// The initialization is only successful if the Min and Max values can all be parsed from the string
	const bool bSuccessful = FParse::Value(*InSourceString, TEXT("Min="), OutInterval.Min) && FParse::Value(*InSourceString, TEXT("Max="), OutInterval.Max);

	return bSuccessful;
}

FString UCsCommon_Load::ToString_FFloatInterval(const FFloatInterval &Interval)
{
	return FString::Printf(TEXT("Min=%f Max=%f"), Interval.Min, Interval.Max);
}

bool UCsCommon_Load::InitFromString_FFloatInterval(const FString& InSourceString, FFloatInterval &OutInterval)
{
	OutInterval.Min = OutInterval.Max = 0.0f;

	// The initialization is only successful if the Min and Max values can all be parsed from the string
	const bool bSuccessful = FParse::Value(*InSourceString, TEXT("Min="), OutInterval.Min) && FParse::Value(*InSourceString, TEXT("Max="), OutInterval.Max);

	return bSuccessful;
}

#pragma endregion Base Structure

// Json
#pragma region

	// Write
#pragma region

void UCsCommon_Load::JsonWriter(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, const FName &Member)
{
	InJsonWriter->WriteValue(MemberName, Member.ToString());
}

void UCsCommon_Load::JsonWriter(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TArray<FName> &Member, const FString &ElementName)
{
	InJsonWriter->WriteArrayStart(MemberName);

	const int32 Count = Member.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		JsonWriter_ArrayElement(InJsonWriter, ElementName, Member[I]);
	}
	InJsonWriter->WriteArrayEnd();
}

void UCsCommon_Load::JsonWriter_ArrayElement(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, const FName &Member)
{
	InJsonWriter->WriteObjectStart();
		JsonWriter(InJsonWriter, MemberName, Member);
	InJsonWriter->WriteObjectEnd();
}

void UCsCommon_Load::WriteTSoftObjectPtrToJson_AnimBlueprint(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TSoftObjectPtr<UAnimBlueprint> &Member)
{
	if (Member.IsValid() && Member.Get())
	{
		FString AssetName = Member.ToString();

		// (AssetName != TEXT(""))
		if (AssetName != NCsCached::Str::Empty)
		{
			InJsonWriter->WriteValue(MemberName, AssetName);
		}
		else
		{
											//   TEXT("")
			InJsonWriter->WriteValue(MemberName, NCsCached::Str::Empty);
		}
	}
	else
	{
										//   TEXT("")
		InJsonWriter->WriteValue(MemberName, NCsCached::Str::Empty);
	}
}

void UCsCommon_Load::WriteSoftObjectPropertyToJson_AnimBlueprint(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, USoftObjectProperty* &SoftObjectProperty, void* InObject, const FString &MemberName)
{
	if (TSoftObjectPtr<UAnimBlueprint>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UAnimBlueprint>>(InObject))
		WriteTSoftObjectPtrToJson_AnimBlueprint(InJsonWriter, MemberName, *Member);
}

void UCsCommon_Load::WriteTSoftObjectPtrToJson_Blueprint(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TSoftObjectPtr<UBlueprint> &Member)
{
	if (Member.IsValid() && Member.Get())
	{
		const FString AssetName = Member.ToString();

		// (AssetName != TEXT("")
		if (AssetName != NCsCached::Str::Empty)
		{
			InJsonWriter->WriteValue(MemberName, AssetName);
		}
		else
		{
											//   TEXT("")
			InJsonWriter->WriteValue(MemberName, NCsCached::Str::Empty);
		}
	}
	else
	{
										//   TEXT("")
		InJsonWriter->WriteValue(MemberName, NCsCached::Str::Empty);
	}
}

void UCsCommon_Load::WriteSoftObjectPropertyToJson_Blueprint(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, USoftObjectProperty* &SoftObjectProperty, void* InObject, const FString &MemberName)
{
	if (TSoftObjectPtr<UBlueprint>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UBlueprint>>(InObject))
		WriteTSoftObjectPtrToJson_Blueprint(InJsonWriter, MemberName, *Member);
}

void UCsCommon_Load::WriteMemberIntegralArrayPropertyToJson_uint64(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName)
{
	TArray<uint64>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<uint64>>(InObject);

	InJsonWriter->WriteObjectStart(MemberName);

	const int32 Count = Member->Num();

	for (int32 I = 0; I < Count; ++I)
	{
		InJsonWriter->WriteValue(FString::FromInt(I), FString::Printf(TEXT("%llu"), (*Member)[I]));
	}
	InJsonWriter->WriteObjectEnd();
}

void UCsCommon_Load::WriteMemberStructPropertyToJson_Transform(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString &MemberName)
{
	if (FTransform* Member = StructProperty->ContainerPtrToValuePtr<FTransform>(InObject))
	{
		InJsonWriter->WriteObjectStart(MemberName);

		// Rotation
		InJsonWriter->WriteValue(NCsCommonLoadCached::Str::Rotation, *(Member->GetRotation().Rotator().ToString()));
		// Translation
		InJsonWriter->WriteValue(NCsCommonLoadCached::Str::Translation, *(Member->GetTranslation().ToString()));
		// Scale
		InJsonWriter->WriteValue(NCsCommonLoadCached::Str::Scale, *(Member->GetScale3D().ToString()));

		InJsonWriter->WriteObjectEnd();
	}
}

void UCsCommon_Load::WriteMemberArrayStructPropertyToJson_Transform(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName)
{
	TArray<FTransform>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<FTransform>>(InObject);

	InJsonWriter->WriteArrayStart(MemberName);

	const int32 Count = Member->Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FTransform& Element = (*Member)[I];

		InJsonWriter->WriteObjectStart();

		// Rotation
		InJsonWriter->WriteValue(NCsCommonLoadCached::Str::Rotation, *(Element.GetRotation().Rotator().ToString()));
		// Translation
		InJsonWriter->WriteValue(NCsCommonLoadCached::Str::Translation, *(Element.GetTranslation().ToString()));
		// Scale
		InJsonWriter->WriteValue(NCsCommonLoadCached::Str::Scale, *(Element.GetScale3D().ToString()));

		InJsonWriter->WriteObjectEnd();
	}
	InJsonWriter->WriteArrayEnd();
}

void UCsCommon_Load::WriteMemberStructPropertyToJson_FCsData_ShortCode(TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString &MemberName)
{
	InJsonWriter->WriteObjectStart(MemberName);

		FCsData_ShortCode* Member = StructProperty->ContainerPtrToValuePtr<FCsData_ShortCode>(InObject);

		// Type
		InJsonWriter->WriteValue(TEXT("Type"), EMCsAssetType::Get()[Member->Type].Name);
		// ShortCode
		InJsonWriter->WriteValue(TEXT("ShortCode"), Member->ShortCode.ToString());

	InJsonWriter->WriteObjectEnd();
}

bool UCsCommon_Load::WriteStructToJson_Internal_Helper(TCsWriteStructToJson_Internal Internal, UProperty* Property, TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, void* InStruct, UScriptStruct* const &InScriptStruct)
{
	if (Internal)
		return (*Internal)(Property, InJsonWriter, InStruct, InScriptStruct);
	return false;
}

bool UCsCommon_Load::WriteObjectToJson_Internal_Helper(TCsWriteObjectToJson_Internal Internal, UProperty* Property, TSharedRef<class TJsonWriter<TCHAR>> &InJsonWriter, void* InObject, UClass* const &InClass)
{
	if (Internal)
		return (*Internal)(Property, InJsonWriter, InObject, InClass);
	return false;
}

void UCsCommon_Load::WriteStructToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, void* InStruct, UScriptStruct* const &InScriptStruct, TCsWriteStructToJson_Internal Internal /*=nullptr*/)
{
	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);
		
		const FString MemberName = Property->GetName();

		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(*It))
		{
			// ACsData_ProjectileBase
			if (SoftClassProperty->MetaClass == ACsData_ProjectileBase::StaticClass())
			{ WriteSoftClassPropertyToJson<ACsData_ProjectileBase>(InJsonWriter, SoftClassProperty, InStruct, MemberName); continue; }
			// ACsData_ProjectileImpact
			if (SoftClassProperty->MetaClass == ACsData_ProjectileImpact::StaticClass())
			{ WriteSoftClassPropertyToJson<ACsData_ProjectileImpact>(InJsonWriter, SoftClassProperty, InStruct, MemberName); continue; }
			// ACsData
			if (SoftClassProperty->MetaClass == ACsData::StaticClass())
			{ WriteSoftClassPropertyToJson<ACsData>(InJsonWriter, SoftClassProperty, InStruct, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// TSoftObjectPtr
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(*It))
		{
			// UStaticMesh
			if (SoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ WriteSoftObjectPropertyToJson<UStaticMesh>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// USkeletalMesh
			if (SoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ WriteSoftObjectPropertyToJson<USkeletalMesh>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstance
			if (SoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ WriteSoftObjectPropertyToJson<UMaterialInstance>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstanceConstant
			if (SoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{
				if (SoftObjectProperty->ArrayDim == CS_SINGLETON)
				{ WriteSoftObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
				if (SoftObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ WriteFixedArraySoftObjectPropertyToJson_EnumSize<UMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(InJsonWriter, SoftObjectProperty, InStruct, MemberName, &ECsInteractiveState::ToString); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// UPhysicalMaterial
			if (SoftObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ WriteSoftObjectPropertyToJson<UPhysicalMaterial>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UPhysicsAsset
			if (SoftObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ WriteSoftObjectPropertyToJson<UPhysicsAsset>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UCurveFloat
			if (SoftObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ WriteSoftObjectPropertyToJson<UCurveFloat>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UCurveVector
			if (SoftObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ WriteSoftObjectPropertyToJson<UCurveVector>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// USoundCue
			if (SoftObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ WriteSoftObjectPropertyToJson<USoundCue>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UParticleSystem
			if (SoftObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ WriteSoftObjectPropertyToJson<UParticleSystem>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UAnimSequence
			if (SoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ WriteSoftObjectPropertyToJson<UAnimSequence>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UAnimMontage
			if (SoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ WriteSoftObjectPropertyToJson<UAnimMontage>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace1D
			if (SoftObjectProperty->PropertyClass == UBlendSpace1D::StaticClass())
			{ WriteSoftObjectPropertyToJson<UBlendSpace1D>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace
			if (SoftObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ WriteSoftObjectPropertyToJson<UBlendSpace>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UAnimBlueprint
			if (SoftObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ WriteSoftObjectPropertyToJson_AnimBlueprint(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UBlueprint
			if (SoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{
				if (SoftObjectProperty->ArrayDim == CS_SINGLETON)
				{ WriteSoftObjectPropertyToJson_Blueprint(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FGuid
			if (StructProperty->Struct == TBaseStructure<FGuid>::Get())
			{ WriteMemberStructPropertyToJson_Primitive<FGuid>(InJsonWriter, StructProperty, InStruct, MemberName, &FGuid::ToString); continue; }
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
			{ WriteMemberStructPropertyToJson_Primitive<FVector>(InJsonWriter, StructProperty, InStruct, MemberName, &FVector::ToString); continue; }
			// FRotator
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
			{ WriteMemberStructPropertyToJson_Primitive<FRotator>(InJsonWriter, StructProperty, InStruct, MemberName, &FRotator::ToString); continue; }
			// FColor
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
			{ WriteMemberStructPropertyToJson_Primitive<FColor>(InJsonWriter, StructProperty, InStruct, MemberName, &FColor::ToString); continue; }
			// FTransform
			if (StructProperty->Struct == TBaseStructure<FTransform>::Get())
			{ WriteMemberStructPropertyToJson_Transform(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
			// FInt32Interval
			if (StructProperty->Struct == TBaseStructure<FInt32Interval>::Get())
			{ WriteMemberStructPropertyToJson_BaseStructure<FInt32Interval>(InJsonWriter, StructProperty, InStruct, MemberName, &UCsCommon_Load::ToString_FInt32Interval); continue; }
			// FFloatInterval
			if (StructProperty->Struct == TBaseStructure<FFloatInterval>::Get())
			{ WriteMemberStructPropertyToJson_BaseStructure<FFloatInterval>(InJsonWriter, StructProperty, InStruct, MemberName, &UCsCommon_Load::ToString_FFloatInterval); continue; }
			// FCsUint8Point
			if (StructProperty->Struct == FCsUint8Point::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsUint8Point>(InJsonWriter, StructProperty, InStruct, MemberName, &FCsUint8Point::ToString); continue; }
			// FCsUint8MatrixDimension
			if (StructProperty->Struct == FCsUint8MatrixDimension::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsUint8MatrixDimension>(InJsonWriter, StructProperty, InStruct, MemberName, &FCsUint8MatrixDimension::ToString); continue; }
			// FCsUint8MatrixCoordinate
			if (StructProperty->Struct == FCsUint8MatrixCoordinate::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsUint8MatrixCoordinate>(InJsonWriter, StructProperty, InStruct, MemberName, &FCsUint8MatrixCoordinate::ToString); continue; }
			// FCsVectorFlag
			if (StructProperty->Struct == FCsVectorFlag::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsVectorFlag>(InJsonWriter, StructProperty, InStruct, MemberName, &FCsVectorFlag::ToString); continue; }
			// FCsRotatorFlag
			if (StructProperty->Struct == FCsRotatorFlag::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsRotatorFlag>(InJsonWriter, StructProperty, InStruct, MemberName, &FCsRotatorFlag::ToString); continue; }
			// FCsOptionalVectorInterval
			if (StructProperty->Struct == FCsOptionalVectorInterval::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsOptionalVectorInterval>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsOptionalRotatorInterval
			if (StructProperty->Struct == FCsOptionalRotatorInterval::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsOptionalRotatorInterval>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsStaticMesh>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvStaticMesh
			if (StructProperty->Struct == FCsFpvStaticMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvStaticMesh>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsSkeletalMesh>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpsSkeletalMesh
			if (StructProperty->Struct == FCsFpsSkeletalMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsSkeletalMesh>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsMaterialInstance>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsMaterialInstanceConstant
			if (StructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsMaterialInstanceConstant>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsTArrayMaterialInstanceConstant::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsTArrayMaterialInstanceConstant>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsFpsTArrayMaterialInstanceConstant::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsTArrayMaterialInstanceConstant>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsPhysicalMaterial
			if (StructProperty->Struct == FCsPhysicalMaterial::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPhysicalMaterial>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPhysicsAsset>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsCurveFloat
			if (StructProperty->Struct == FCsCurveFloat::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsCurveFloat>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsCurveVector>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsSoundElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvSoundElement
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpvSoundElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFxElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvFxElement
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpvFxElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsAnimSequence>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpvAnimSequence
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvAnimSequence>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsAnimMontage>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvAnimMontage
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpvAnimMontage>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsTArrayAnimMontage>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsBlendSpace1D
			if (StructProperty->Struct == FCsBlendSpace1D::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsBlendSpace1D>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpvBlendSpace1D
			if (StructProperty->Struct == FCsFpvBlendSpace1D::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvBlendSpace1D>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsBlendSpace>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpvBlendSpace
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvBlendSpace>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsAimOffset
			if (StructProperty->Struct == FCsAimOffset::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsAimOffset>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpvAimOffset
			if (StructProperty->Struct == FCsFpvAimOffset::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvAimOffset>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsAnimBlueprint>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpvAnimBlueprint
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvAnimBlueprint>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsBlueprint
			if (StructProperty->Struct == FCsBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsBlueprint>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsTArrayBlueprint
			if (StructProperty->Struct == FCsTArrayBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsTArrayBlueprint>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCollisionResponseContainer
			if (StructProperty->Struct == FCollisionResponseContainer::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCollisionResponseContainer>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsDataMappingEntry
			if (StructProperty->Struct == FCsDataMappingEntry::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsDataMappingEntry>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsInputProfile
			if (StructProperty->Struct == FCsInputProfile::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsInputProfile>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsInputActionMappings
			if (StructProperty->Struct == FCsInputActionMappings::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsInputActionMappings>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }

				if (StructProperty->ArrayDim == ECS_INPUT_DEVICE_MAX)
				{ WriteMemberFixedArrayStructPropertyToJson_EnumSize<FCsInputActionMappings, ECsInputDevice, EMCsInputDevice, ECS_INPUT_DEVICE_MAX>(InJsonWriter, StructProperty, InStruct, MemberName, nullptr); continue; }
			}
			// FCsInputActionMapping
			if (StructProperty->Struct == FCsInputActionMapping::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsInputActionMapping>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsDrawDistance
			if (StructProperty->Struct == FCsDrawDistance::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsDrawDistance>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsFpvDrawDistance
			if (StructProperty->Struct == FCsFpvDrawDistance::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvDrawDistance>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// Weapon_FireMode
			{
				// FCsData_Weapon_FireMode_Firing
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Firing::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_Weapon_FireMode_Firing>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_Weapon_FireMode_Animation
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Animation::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_Weapon_FireMode_Animation>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_FpsWeapon_FireMode_Animation
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Animation::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_FpsWeapon_FireMode_Animation>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_Weapon_FireMode_Movement
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Movement::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_Weapon_FireMode_Movement>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_Weapon_FireMode_Aiming
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Aiming::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_Weapon_FireMode_Aiming>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_FpsWeapon_FireMode_Aiming
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Aiming::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_FpsWeapon_FireMode_Aiming>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_Weapon_FireMode_Scope
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Scope::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_Weapon_FireMode_Scope>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_Weapon_FireMode_FXs
				if (StructProperty->Struct == FCsData_Weapon_FireMode_FXs::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_Weapon_FireMode_FXs>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_FpsWeapon_FireMode_FXs
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_FXs::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_FpsWeapon_FireMode_FXs>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_Weapon_FireMode_Sounds
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Sounds::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_Weapon_FireMode_Sounds>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_FpsWeapon_FireMode_Sounds
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Sounds::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_FpsWeapon_FireMode_Sounds>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			}
			// FCsData_ProjectileBasePtr
			if (StructProperty->Struct == FCsData_ProjectileBasePtr::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsData_ProjectileBasePtr>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsData_ProjectileImpactPtr
			if (StructProperty->Struct == FCsData_ProjectileImpactPtr::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsData_ProjectileImpactPtr>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsRadius
			if (StructProperty->Struct == FCsRadius::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsRadius>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsProjectileMovementFunctionAxis
			if (StructProperty->Struct == FCsProjectileMovementFunctionAxis::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsProjectileMovementFunctionAxis>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsParametricFunction
			if (StructProperty->Struct == FCsParametricFunction::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsParametricFunction>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsParametricFunctionAxis
			if (StructProperty->Struct == FCsParametricFunctionAxis::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsParametricFunctionAxis>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsItemMemberDescription
			if (StructProperty->Struct == FCsItemMemberDescription::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsItemMemberDescription>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsInventoryLoadoutRecipe
			if (StructProperty->Struct == FCsInventoryLoadoutRecipe::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsInventoryLoadoutRecipe>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsInventoryLoadoutItem
			if (StructProperty->Struct == FCsInventoryLoadoutItem::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsInventoryLoadoutItem>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsRecipeIngredient
			if (StructProperty->Struct == FCsRecipeIngredient::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsRecipeIngredient>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsPlayerData_Inventory_Bag
			if (StructProperty->Struct == FCsPlayerData_Inventory_Bag::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPlayerData_Inventory_Bag>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsPlayerData_Inventory_Slot
			if (StructProperty->Struct == FCsPlayerData_Inventory_Slot::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPlayerData_Inventory_Slot>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsItemOnConsumeContentRule
			if (StructProperty->Struct == FCsItemOnConsumeContentRule::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsItemOnConsumeContentRule>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsTArrayPayload
			if (StructProperty->Struct == FCsTArrayPayload::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsTArrayPayload>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsPayload
			if (StructProperty->Struct == FCsPayload::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPayload>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsData_ShortCode
			if (StructProperty->Struct == FCsData_ShortCode::StaticStruct())
			{ WriteMemberStructPropertyToJson_FCsData_ShortCode(InJsonWriter, StructProperty, InStruct, MemberName); continue; }

			// EnumStruct
			{
				// FECsAssetType
				if (StructProperty->Struct == FECsAssetType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsAssetType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsLoadAssetsType
				if (StructProperty->Struct == FECsLoadAssetsType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsLoadAssetsType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsInputAction
				if (StructProperty->Struct == FECsInputAction::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsInputAction>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsGameEvent
				if (StructProperty->Struct == FECsGameEvent::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsGameEvent>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsSurfaceType
				if (StructProperty->Struct == FECsSurfaceType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsSurfaceType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsWeaponGrip
				if (StructProperty->Struct == FECsWeaponGrip::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsWeaponGrip>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsDamageType
				if (StructProperty->Struct == FECsDamageType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsDamageType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsInteractiveType
				if (StructProperty->Struct == FECsInteractiveType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsInteractiveType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsProjectile
				if (StructProperty->Struct == FECsProjectile::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsProjectile>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsSoundType
				if (StructProperty->Struct == FECsSoundType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsSoundType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsItemType
				if (StructProperty->Struct == FECsItemType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsItemType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsRecipeType
				if (StructProperty->Struct == FECsRecipeType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsRecipeType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftObjectPtr
			if (USoftObjectProperty* InnerSoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerSoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UStaticMesh>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// USkeletalMesh
				if (InnerSoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<USkeletalMesh>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstance
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UMaterialInstance>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstanceConstant
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimSequence
				if (InnerSoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UAnimSequence>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimMontage
				if (InnerSoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UAnimMontage>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UBlueprint
				if (InnerSoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UBlueprint>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FGuid
				if (InnerStructProperty->Struct == TBaseStructure<FGuid>::Get())
				{ WriteMemberArrayStructPropertyToJson_Primitive<FGuid>(InJsonWriter, ArrayProperty, InStruct, MemberName, &FGuid::ToString); continue; }
				// FVector
				if (InnerStructProperty->Struct == TBaseStructure<FVector>::Get())
				{ WriteMemberArrayStructPropertyToJson_Primitive<FVector>(InJsonWriter, ArrayProperty, InStruct, MemberName, &FVector::ToString); continue; }
				// FRotator
				if (InnerStructProperty->Struct == TBaseStructure<FRotator>::Get())
				{ WriteMemberArrayStructPropertyToJson_Primitive<FRotator>(InJsonWriter, ArrayProperty, InStruct, MemberName, &FRotator::ToString); continue; }
				// FColor
				if (InnerStructProperty->Struct == TBaseStructure<FColor>::Get())
				{ WriteMemberArrayStructPropertyToJson_Primitive<FColor>(InJsonWriter, ArrayProperty, InStruct, MemberName, &FColor::ToString); continue; }
				// FTransform
				if (InnerStructProperty->Struct == TBaseStructure<FTransform>::Get())
				{ WriteMemberArrayStructPropertyToJson_Transform(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsAnimMontage>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsFxElement
				if (InnerStructProperty->Struct == FCsFxElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFxElement>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsFpvFxElement
				if (InnerStructProperty->Struct == FCsFpvFxElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpvFxElement>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsSoundElement>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsFpvSoundElement
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpvSoundElement>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsAnimSequence
				if (InnerStructProperty->Struct == FCsAnimSequence::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsAnimSequence>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsFpvAnimSequence
				if (InnerStructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpvAnimSequence>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsAnimMontage>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsFpvAnimMontage
				if (InnerStructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpvAnimMontage>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsInputActionMapping
				if (InnerStructProperty->Struct == FCsInputActionMapping::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsInputActionMapping>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsInventoryLoadoutRecipe
				if (InnerStructProperty->Struct == FCsInventoryLoadoutRecipe::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsInventoryLoadoutRecipe>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsInventoryLoadoutItem
				if (InnerStructProperty->Struct == FCsInventoryLoadoutItem::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsInventoryLoadoutItem>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsRecipeIngredient
				if (InnerStructProperty->Struct == FCsRecipeIngredient::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsRecipeIngredient>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsPlayerData_Inventory_Bag
				if (InnerStructProperty->Struct == FCsPlayerData_Inventory_Bag::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsPlayerData_Inventory_Bag>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsPlayerData_Inventory_Slot
				if (InnerStructProperty->Struct == FCsPlayerData_Inventory_Slot::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsPlayerData_Inventory_Slot>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsPayload
				if (InnerStructProperty->Struct == FCsPayload::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsPayload>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FName
			if (UNameProperty* NameProperty = Cast<UNameProperty>(ArrayProperty->Inner))
			{ WriteMemberArrayStructPropertyToJson_Primitive<FName>(InJsonWriter, ArrayProperty, InStruct, MemberName, &FName::ToString); continue; }
			// uint64
			if (UUInt64Property* IntProperty = Cast<UUInt64Property>(ArrayProperty->Inner))
			{ WriteMemberIntegralArrayPropertyToJson_uint64(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// Map
		if (UMapProperty* MapProperty = Cast<UMapProperty>(*It))
		{
			UStructProperty* KeyStructProp = Cast<UStructProperty>(MapProperty->KeyProp);
			UFloatProperty* ValueFloatProp = Cast<UFloatProperty>(MapProperty->ValueProp);

			if (KeyStructProp && ValueFloatProp)
			{
				// FECsSenseActorType, float
				if (KeyStructProp->Struct == FECsSenseActorType::StaticStruct())
				{ WriteMemberMapStructPropertyToJson_EnumStructKey_NumericValue<FECsSenseActorType, float>(InJsonWriter, MapProperty, InStruct, MemberName, Internal); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// bool
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
		{
			if (bool* Member = BoolProperty->ContainerPtrToValuePtr<bool>(InStruct))
				InJsonWriter->WriteValue(MemberName, *Member);
			continue;
		}
		// Enum Class
		if (UEnumProperty* EnumProperty = Cast<UEnumProperty>(*It))
		{
			// ECsEasingType
			if (EnumProperty->GetEnum()->CppType.Contains(NCsCommonLoadCached::Str::CsEasingType))
			{ WriteMemberEnumPropertyToJson<ECsEasingType, EMCsEasingType>(InJsonWriter, EnumProperty, InStruct, MemberName); continue; }
			// ECsProjectileMovementFunctionType
			if (EnumProperty->GetEnum()->CppType.Contains(NCsCommonLoadCached::Str::CsProjectileMovementFunctionType))
			{ WriteMemberEnumPropertyToJson<ECsProjectileMovementFunctionType, EMCsProjectileMovementFunctionType>(InJsonWriter, EnumProperty, InStruct, MemberName); continue; }
			continue;
		}
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			// enum
			if (ByteProperty->IsEnum())
			{
				// ECollisionEnabled
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionEnabled))
				{ WriteMemberEnumAsBytePropertyToJson<ECollisionEnabled::Type, EMCollisionEnabled>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionChannel))
				{ WriteMemberEnumAsBytePropertyToJson<ECollisionChannel, EMCsCollisionChannel>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionResponse))
				{ WriteMemberEnumAsBytePropertyToJson<ECollisionResponse, EMCollisionResponse>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::HorizTextAligment))
				{ WriteMemberEnumAsBytePropertyToJson<EHorizTextAligment, EMHorizTextAligment>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::VerticalTextAligment))
				{ WriteMemberEnumAsBytePropertyToJson<EVerticalTextAligment, EMVerticalTextAligment>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECsLoadFlags_Editor
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsLoadFlags_Editor))
				{ WriteMemberEnumAsBytePropertyToJson<ECsLoadFlags_Editor::Type, EMCsLoadFlags_Editor>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsFxPriority))
				{ WriteMemberEnumAsBytePropertyToJson<ECsFxPriority::Type, EMCsFxPriority>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsSoundPriority))
				{ WriteMemberEnumAsBytePropertyToJson<ECsSoundPriority::Type, EMCsSoundPriority>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECsParametricFunctionType
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsParametricFunctionType))
				{ WriteMemberEnumAsBytePropertyToJson<ECsParametricFunctionType::Type, EMCsParametricFunctionType>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECsItemMemberValueType
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsItemMemberValueType))
				{ WriteMemberEnumAsBytePropertyToJson<ECsItemMemberValueType::Type, EMCsItemMemberValueType>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECsItemOnConsumeContentAction
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsItemOnConsumeContentAction))
				{ WriteMemberEnumAsBytePropertyToJson<ECsItemOnConsumeContentAction::Type, EMCsItemOnConsumeContentAction>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// uint8
			else
			{
				if (uint8* Member = ByteProperty->ContainerPtrToValuePtr<uint8>(InStruct))
					InJsonWriter->WriteValue(MemberName, *Member);
			}
			continue;
		}
		// uint16
		if (UUInt16Property* Int16Property = Cast<UUInt16Property>(*It))
		{
			if (uint16* Member = Int16Property->ContainerPtrToValuePtr<uint16>(InStruct))
			{ InJsonWriter->WriteValue(MemberName, *Member); continue; }
			continue;
		}
		// int32
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
		{
			
			if (int32* Member = IntProperty->ContainerPtrToValuePtr<int32>(InStruct))
			{
#if WITH_EDITOR
									//    TEXT("BitmaskEnum")
				if (Property->HasMetaData(*(NCsCommonLoadCached::Str::BitmaskEnum)))
				{
																//    TEXT("BitmaskEnum")
					const FString BitmaskEnum = Property->GetMetaData(*(NCsCommonLoadCached::Str::BitmaskEnum));

					// (BitmaskEnum == TEXT("ECsLoadFlags"))
					if (BitmaskEnum == NCsCommonLoadCached::Str::CsLoadFlags)
					{
						InJsonWriter->WriteValue(MemberName, EMCsLoadFlags::Get().MaskToString(*Member));
					}
				}
				else
#endif // #if WITH_EDITOR
				{
					InJsonWriter->WriteValue(MemberName, *Member);
				}
			}
			continue;
		}
		// uint64
		if (UUInt64Property* IntProperty = Cast<UUInt64Property>(*It))
		{
			if (uint64* Member = IntProperty->ContainerPtrToValuePtr<uint64>(InStruct))
				InJsonWriter->WriteValue(MemberName, FString::Printf(TEXT("%llu"), *Member));
			continue;
		}
		// float
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
		{
			if (float* Member = FloatProperty->ContainerPtrToValuePtr<float>(InStruct))
				InJsonWriter->WriteValue(MemberName, *Member);
			continue;
		}
		// FString
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
		{
			if (FString* Member = StrProperty->ContainerPtrToValuePtr<FString>(InStruct))
				InJsonWriter->WriteValue(MemberName, *Member);
			continue;
		}
		// FName
		if (UNameProperty* NameProperty = Cast<UNameProperty>(*It))
		{
			if (NameProperty->ArrayDim == CS_SINGLETON)
			{
				if (FName* Member = NameProperty->ContainerPtrToValuePtr<FName>(InStruct))
				{ InJsonWriter->WriteValue(MemberName, (*Member).ToString()); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
	}
}

void UCsCommon_Load::WriteStructToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, void* InStruct, UScriptStruct* const &InScriptStruct, const TArray<FCsCategoryMemberAssociation> &CategoryMemberAssociations, TCsWriteStructToJson_Internal Internal /*=nullptr*/)
{
	const FString NoCategory = NCsCached::Str::Empty;
	FString Category		 = NoCategory;
	FString LastCategory	 = NoCategory;
	int32 CategoryIndex		 = 0;

	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		if (CategoryIndex >= CategoryMemberAssociations.Num())
			break;

		const int32 Count = CategoryMemberAssociations[CategoryIndex].Members.Num();
		const int32 Index = CategoryMemberAssociations[CategoryIndex].Members.Find(MemberName);

		if (Index == INDEX_NONE)
			continue;

		Category = CategoryMemberAssociations[CategoryIndex].Category;

		if (Index == Count - 1)
			CategoryIndex++;

		// Check if Category changed
		if (Category != LastCategory)
		{
			// (LastCategory != TEXT(""))
			if (LastCategory != NCsCached::Str::Empty)
				InJsonWriter->WriteObjectEnd();
			InJsonWriter->WriteObjectStart(Category);

			LastCategory = Category;
		}

		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(*It))
		{
			// ACsData_ProjectileBase
			if (SoftClassProperty->MetaClass == ACsData_ProjectileBase::StaticClass())
			{ WriteSoftClassPropertyToJson<ACsData_ProjectileBase>(InJsonWriter, SoftClassProperty, InStruct, MemberName); continue; }
			// ACsData_ProjectileImpact
			if (SoftClassProperty->MetaClass == ACsData_ProjectileImpact::StaticClass())
			{ WriteSoftClassPropertyToJson<ACsData_ProjectileImpact>(InJsonWriter, SoftClassProperty, InStruct, MemberName); continue; }
			// ACsData
			if (SoftClassProperty->MetaClass == ACsData::StaticClass())
			{ WriteSoftClassPropertyToJson<ACsData>(InJsonWriter, SoftClassProperty, InStruct, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// TSoftObjectPtr
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(*It))
		{
			// UStaticMesh
			if (SoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ WriteSoftObjectPropertyToJson<UStaticMesh>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// USkeletalMesh
			if (SoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ WriteSoftObjectPropertyToJson<USkeletalMesh>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstance
			if (SoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ WriteSoftObjectPropertyToJson<UMaterialInstance>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstanceConstant
			if (SoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{
				if (SoftObjectProperty->ArrayDim == CS_SINGLETON)
				{ WriteSoftObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
				if (SoftObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ WriteFixedArraySoftObjectPropertyToJson_EnumSize<UMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(InJsonWriter, SoftObjectProperty, InStruct, MemberName, &ECsInteractiveState::ToString); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// UPhysicalMaterial
			if (SoftObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ WriteSoftObjectPropertyToJson<UPhysicalMaterial>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UPhysicsAsset
			if (SoftObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ WriteSoftObjectPropertyToJson<UPhysicsAsset>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UCurveFloat
			if (SoftObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ WriteSoftObjectPropertyToJson<UCurveFloat>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UCurveVector
			if (SoftObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ WriteSoftObjectPropertyToJson<UCurveVector>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// USoundCue
			if (SoftObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ WriteSoftObjectPropertyToJson<USoundCue>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UParticleSystem
			if (SoftObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ WriteSoftObjectPropertyToJson<UParticleSystem>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UAnimSequence
			if (SoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ WriteSoftObjectPropertyToJson<UAnimSequence>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UAnimMontage
			if (SoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ WriteSoftObjectPropertyToJson<UAnimMontage>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace1D
			if (SoftObjectProperty->PropertyClass == UBlendSpace1D::StaticClass())
			{ WriteSoftObjectPropertyToJson<UBlendSpace1D>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace
			if (SoftObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ WriteSoftObjectPropertyToJson<UBlendSpace>(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UAnimBlueprint
			if (SoftObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ WriteSoftObjectPropertyToJson_AnimBlueprint(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			// UBlueprint
			if (SoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{
				if (SoftObjectProperty->ArrayDim == CS_SINGLETON)
				{ WriteSoftObjectPropertyToJson_Blueprint(InJsonWriter, SoftObjectProperty, InStruct, MemberName); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FGuid
			if (StructProperty->Struct == TBaseStructure<FGuid>::Get())
			{ WriteMemberStructPropertyToJson_Primitive<FGuid>(InJsonWriter, StructProperty, InStruct, MemberName, &FGuid::ToString); continue; }
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
			{ WriteMemberStructPropertyToJson_Primitive<FVector>(InJsonWriter, StructProperty, InStruct, MemberName, &FVector::ToString); continue; }
			// FRotator
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
			{ WriteMemberStructPropertyToJson_Primitive<FRotator>(InJsonWriter, StructProperty, InStruct, MemberName, &FRotator::ToString); continue; }
			// FColor
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
			{ WriteMemberStructPropertyToJson_Primitive<FColor>(InJsonWriter, StructProperty, InStruct, MemberName, &FColor::ToString); continue; }
			// FTransform
			if (StructProperty->Struct == TBaseStructure<FTransform>::Get())
			{ WriteMemberStructPropertyToJson_Transform(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
			// FInt32Interval
			if (StructProperty->Struct == TBaseStructure<FInt32Interval>::Get())
			{ WriteMemberStructPropertyToJson_BaseStructure<FInt32Interval>(InJsonWriter, StructProperty, InStruct, MemberName, &UCsCommon_Load::ToString_FInt32Interval); continue; }
			// FFloatInterval
			if (StructProperty->Struct == TBaseStructure<FFloatInterval>::Get())
			{ WriteMemberStructPropertyToJson_BaseStructure<FFloatInterval>(InJsonWriter, StructProperty, InStruct, MemberName, &UCsCommon_Load::ToString_FFloatInterval); continue; }
			// FCsUint8Point
			if (StructProperty->Struct == FCsUint8Point::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsUint8Point>(InJsonWriter, StructProperty, InStruct, MemberName, &FCsUint8Point::ToString); continue; }
			// FCsUint8MatrixDimension
			if (StructProperty->Struct == FCsUint8MatrixDimension::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsUint8MatrixDimension>(InJsonWriter, StructProperty, InStruct, MemberName, &FCsUint8MatrixDimension::ToString); continue; }
			// FCsUint8MatrixCoordinate
			if (StructProperty->Struct == FCsUint8MatrixCoordinate::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsUint8MatrixCoordinate>(InJsonWriter, StructProperty, InStruct, MemberName, &FCsUint8MatrixCoordinate::ToString); continue; }
			// FCsVectorFlag
			if (StructProperty->Struct == FCsVectorFlag::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsVectorFlag>(InJsonWriter, StructProperty, InStruct, MemberName, &FCsVectorFlag::ToString); continue; }
			// FCsRotatorFlag
			if (StructProperty->Struct == FCsRotatorFlag::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsRotatorFlag>(InJsonWriter, StructProperty, InStruct, MemberName, &FCsRotatorFlag::ToString); continue; }
			// FCsOptionalVectorInterval
			if (StructProperty->Struct == FCsOptionalVectorInterval::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsOptionalVectorInterval>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsOptionalRotatorInterval
			if (StructProperty->Struct == FCsOptionalRotatorInterval::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsOptionalRotatorInterval>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsStaticMesh>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvStaticMesh
			if (StructProperty->Struct == FCsFpvStaticMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvStaticMesh>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsSkeletalMesh>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpsSkeletalMesh
			if (StructProperty->Struct == FCsFpsSkeletalMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsSkeletalMesh>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsMaterialInstance>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsMaterialInstanceConstant
			if (StructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsMaterialInstanceConstant>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsTArrayMaterialInstanceConstant::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsTArrayMaterialInstanceConstant>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsFpsTArrayMaterialInstanceConstant::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsTArrayMaterialInstanceConstant>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsPhysicalMaterial
			if (StructProperty->Struct == FCsPhysicalMaterial::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPhysicalMaterial>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPhysicsAsset>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsCurveFloat
			if (StructProperty->Struct == FCsCurveFloat::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsCurveFloat>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsCurveVector>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsSoundElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvSoundElement
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpvSoundElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFxElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvFxElement
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpvFxElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsAnimSequence>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpvAnimSequence
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvAnimSequence>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsAnimMontage>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvAnimMontage
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpvAnimMontage>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsTArrayAnimMontage>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsBlendSpace1D
			if (StructProperty->Struct == FCsBlendSpace1D::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsBlendSpace1D>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpvBlendSpace1D
			if (StructProperty->Struct == FCsFpvBlendSpace1D::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvBlendSpace1D>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsBlendSpace>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpvBlendSpace
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvBlendSpace>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsAimOffset
			if (StructProperty->Struct == FCsAimOffset::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsAimOffset>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpvAimOffset
			if (StructProperty->Struct == FCsFpvAimOffset::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvAimOffset>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsAnimBlueprint>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpvAnimBlueprint
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvAnimBlueprint>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsBlueprint
			if (StructProperty->Struct == FCsBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsBlueprint>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsTArrayBlueprint
			if (StructProperty->Struct == FCsTArrayBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsTArrayBlueprint>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsCollisionPreset
			if (StructProperty->Struct == FCsCollisionPreset::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsCollisionPreset>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCollisionResponseContainer
			if (StructProperty->Struct == FCollisionResponseContainer::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCollisionResponseContainer>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsDataMappingEntry
			if (StructProperty->Struct == FCsDataMappingEntry::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsDataMappingEntry>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsInputProfile
			if (StructProperty->Struct == FCsInputProfile::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsInputProfile>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsInputActionMappings
			if (StructProperty->Struct == FCsInputActionMappings::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsInputActionMappings>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }

				if (StructProperty->ArrayDim == ECS_INPUT_DEVICE_MAX)
				{ WriteMemberFixedArrayStructPropertyToJson_EnumSize<FCsInputActionMappings, ECsInputDevice, EMCsInputDevice, ECS_INPUT_DEVICE_MAX>(InJsonWriter, StructProperty, InStruct, MemberName, nullptr); continue; }
			}
			// FCsInputActionMapping
			if (StructProperty->Struct == FCsInputActionMapping::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsInputActionMapping>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsDrawDistance
			if (StructProperty->Struct == FCsDrawDistance::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsDrawDistance>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsFpvDrawDistance
			if (StructProperty->Struct == FCsFpvDrawDistance::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvDrawDistance>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// Weapon_FireMode
			{
				// FCsData_Weapon_FireMode_Firing
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Firing::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_Weapon_FireMode_Firing>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_Weapon_FireMode_Animation
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Animation::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_Weapon_FireMode_Animation>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_FpsWeapon_FireMode_Animation
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Animation::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_FpsWeapon_FireMode_Animation>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_Weapon_FireMode_Movement
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Movement::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_Weapon_FireMode_Movement>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_Weapon_FireMode_Aiming
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Aiming::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_Weapon_FireMode_Aiming>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_FpsWeapon_FireMode_Aiming
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Aiming::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_FpsWeapon_FireMode_Aiming>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_Weapon_FireMode_Scope
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Scope::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_Weapon_FireMode_Scope>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_Weapon_FireMode_FXs
				if (StructProperty->Struct == FCsData_Weapon_FireMode_FXs::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_Weapon_FireMode_FXs>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_FpsWeapon_FireMode_FXs
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_FXs::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_FpsWeapon_FireMode_FXs>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_Weapon_FireMode_Sounds
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Sounds::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_Weapon_FireMode_Sounds>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
				// FCsData_FpsWeapon_FireMode_Sounds
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Sounds::StaticStruct())
				{ WriteMemberStructPropertyToJson<FCsData_FpsWeapon_FireMode_Sounds>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			}
			// FCsData_ProjectileBasePtr
			if (StructProperty->Struct == FCsData_ProjectileBasePtr::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsData_ProjectileBasePtr>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsData_ProjectileImpactPtr
			if (StructProperty->Struct == FCsData_ProjectileImpactPtr::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsData_ProjectileImpactPtr>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsRadius
			if (StructProperty->Struct == FCsRadius::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsRadius>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsProjectileMovementFunctionAxis
			if (StructProperty->Struct == FCsProjectileMovementFunctionAxis::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsProjectileMovementFunctionAxis>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsParametricFunction
			if (StructProperty->Struct == FCsParametricFunction::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsParametricFunction>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsParametricFunctionAxis
			if (StructProperty->Struct == FCsParametricFunctionAxis::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsParametricFunctionAxis>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsItemMemberDescription
			if (StructProperty->Struct == FCsItemMemberDescription::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsItemMemberDescription>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsInventoryLoadoutRecipe
			if (StructProperty->Struct == FCsInventoryLoadoutRecipe::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsInventoryLoadoutRecipe>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsInventoryLoadoutItem
			if (StructProperty->Struct == FCsInventoryLoadoutItem::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsInventoryLoadoutItem>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsRecipeIngredient
			if (StructProperty->Struct == FCsRecipeIngredient::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsRecipeIngredient>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsPlayerData_Inventory_Bag
			if (StructProperty->Struct == FCsPlayerData_Inventory_Bag::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPlayerData_Inventory_Bag>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsPlayerData_Inventory_Slot
			if (StructProperty->Struct == FCsPlayerData_Inventory_Slot::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPlayerData_Inventory_Slot>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsItemOnConsumeContentRule
			if (StructProperty->Struct == FCsItemOnConsumeContentRule::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsItemOnConsumeContentRule>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsTArrayPayload
			if (StructProperty->Struct == FCsTArrayPayload::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsTArrayPayload>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsPayload
			if (StructProperty->Struct == FCsPayload::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPayload>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsData_ShortCode
			if (StructProperty->Struct == FCsData_ShortCode::StaticStruct())
			{ WriteMemberStructPropertyToJson_FCsData_ShortCode(InJsonWriter, StructProperty, InStruct, MemberName); continue; }

			// EnumStruct
			{
				// FECsAssetType
				if (StructProperty->Struct == FECsAssetType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsAssetType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsLoadAssetsType
				if (StructProperty->Struct == FECsLoadAssetsType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsLoadAssetsType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsInputAction
				if (StructProperty->Struct == FECsInputAction::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsInputAction>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsGameEvent
				if (StructProperty->Struct == FECsGameEvent::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsGameEvent>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsSurfaceType
				if (StructProperty->Struct == FECsSurfaceType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsSurfaceType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsWeaponGrip
				if (StructProperty->Struct == FECsWeaponGrip::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsWeaponGrip>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsDamageType
				if (StructProperty->Struct == FECsDamageType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsDamageType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsInteractiveType
				if (StructProperty->Struct == FECsInteractiveType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsInteractiveType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsProjectile
				if (StructProperty->Struct == FECsProjectile::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsProjectile>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsSoundType
				if (StructProperty->Struct == FECsSoundType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsSoundType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsItemType
				if (StructProperty->Struct == FECsItemType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsItemType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
				// FECsRecipeType
				if (StructProperty->Struct == FECsRecipeType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsRecipeType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftObjectPtr
			if (USoftObjectProperty* InnerSoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerSoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UStaticMesh>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// USkeletalMesh
				if (InnerSoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<USkeletalMesh>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstance
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UMaterialInstance>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstanceConstant
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimSequence
				if (InnerSoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UAnimSequence>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimMontage
				if (InnerSoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UAnimMontage>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UBlueprint
				if (InnerSoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UBlueprint>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FGuid
				if (InnerStructProperty->Struct == TBaseStructure<FGuid>::Get())
				{ WriteMemberArrayStructPropertyToJson_Primitive<FGuid>(InJsonWriter, ArrayProperty, InStruct, MemberName, &FGuid::ToString); continue; }
				// FVector
				if (InnerStructProperty->Struct == TBaseStructure<FVector>::Get())
				{ WriteMemberArrayStructPropertyToJson_Primitive<FVector>(InJsonWriter, ArrayProperty, InStruct, MemberName, &FVector::ToString); continue; }
				// FRotator
				if (InnerStructProperty->Struct == TBaseStructure<FRotator>::Get())
				{ WriteMemberArrayStructPropertyToJson_Primitive<FRotator>(InJsonWriter, ArrayProperty, InStruct, MemberName, &FRotator::ToString); continue; }
				// FColor
				if (InnerStructProperty->Struct == TBaseStructure<FColor>::Get())
				{ WriteMemberArrayStructPropertyToJson_Primitive<FColor>(InJsonWriter, ArrayProperty, InStruct, MemberName, &FColor::ToString); continue; }
				// FTransform
				if (InnerStructProperty->Struct == TBaseStructure<FTransform>::Get())
				{ WriteMemberArrayStructPropertyToJson_Transform(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsAnimMontage>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsFxElement
				if (InnerStructProperty->Struct == FCsFxElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFxElement>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsFpvFxElement
				if (InnerStructProperty->Struct == FCsFpvFxElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpvFxElement>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsSoundElement>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsFpvSoundElement
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpvSoundElement>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsAnimSequence
				if (InnerStructProperty->Struct == FCsAnimSequence::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsAnimSequence>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsFpvAnimSequence
				if (InnerStructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpvAnimSequence>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsAnimMontage>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsFpvAnimMontage
				if (InnerStructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpvAnimMontage>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsInputActionMapping
				if (InnerStructProperty->Struct == FCsInputActionMapping::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsInputActionMapping>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsInventoryLoadoutRecipe
				if (InnerStructProperty->Struct == FCsInventoryLoadoutRecipe::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsInventoryLoadoutRecipe>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsInventoryLoadoutItem
				if (InnerStructProperty->Struct == FCsInventoryLoadoutItem::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsInventoryLoadoutItem>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsRecipeIngredient
				if (InnerStructProperty->Struct == FCsRecipeIngredient::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsRecipeIngredient>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsPlayerData_Inventory_Bag
				if (InnerStructProperty->Struct == FCsPlayerData_Inventory_Bag::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsPlayerData_Inventory_Bag>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsPlayerData_Inventory_Slot
				if (InnerStructProperty->Struct == FCsPlayerData_Inventory_Slot::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsPlayerData_Inventory_Slot>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsPayload
				if (InnerStructProperty->Struct == FCsPayload::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsPayload>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FName
			if (UNameProperty* NameProperty = Cast<UNameProperty>(ArrayProperty->Inner))
			{ WriteMemberArrayStructPropertyToJson_Primitive<FName>(InJsonWriter, ArrayProperty, InStruct, MemberName, &FName::ToString); continue; }
			// uint64
			if (UUInt64Property* IntProperty = Cast<UUInt64Property>(ArrayProperty->Inner))
			{ WriteMemberIntegralArrayPropertyToJson_uint64(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// Map
		if (UMapProperty* MapProperty = Cast<UMapProperty>(*It))
		{
			UStructProperty* KeyStructProp = Cast<UStructProperty>(MapProperty->KeyProp);
			UFloatProperty* ValueFloatProp = Cast<UFloatProperty>(MapProperty->ValueProp);

			if (KeyStructProp && ValueFloatProp)
			{
				// FECsSenseActorType, float
				if (KeyStructProp->Struct == FECsSenseActorType::StaticStruct())
				{ WriteMemberMapStructPropertyToJson_EnumStructKey_NumericValue<FECsSenseActorType, float>(InJsonWriter, MapProperty, InStruct, MemberName, Internal); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// bool
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
		{
			if (bool* Member = BoolProperty->ContainerPtrToValuePtr<bool>(InStruct))
				InJsonWriter->WriteValue(MemberName, *Member);
			continue;
		}
		// Enum Class
		if (UEnumProperty* EnumProperty = Cast<UEnumProperty>(*It))
		{
			// ECsEasingType
			if (EnumProperty->GetEnum()->CppType.Contains(NCsCommonLoadCached::Str::CsEasingType))
			{ WriteMemberEnumPropertyToJson<ECsEasingType, EMCsEasingType>(InJsonWriter, EnumProperty, InStruct, MemberName); continue; }
			// ECsProjectileMovementFunctionType
			if (EnumProperty->GetEnum()->CppType.Contains(NCsCommonLoadCached::Str::CsProjectileMovementFunctionType))
			{ WriteMemberEnumPropertyToJson<ECsProjectileMovementFunctionType, EMCsProjectileMovementFunctionType>(InJsonWriter, EnumProperty, InStruct, MemberName); continue; }
			continue;
		}
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			// enum
			if (ByteProperty->IsEnum())
			{
				// ECollisionEnabled
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionEnabled))
				{ WriteMemberEnumAsBytePropertyToJson<ECollisionEnabled::Type, EMCollisionEnabled>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionChannel))
				{ WriteMemberEnumAsBytePropertyToJson<ECollisionChannel, EMCsCollisionChannel>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionResponse))
				{ WriteMemberEnumAsBytePropertyToJson<ECollisionResponse, EMCollisionResponse>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::HorizTextAligment))
				{ WriteMemberEnumAsBytePropertyToJson<EHorizTextAligment, EMHorizTextAligment>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::VerticalTextAligment))
				{ WriteMemberEnumAsBytePropertyToJson<EVerticalTextAligment, EMVerticalTextAligment>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECsLoadFlags_Editor
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsLoadFlags_Editor))
				{ WriteMemberEnumAsBytePropertyToJson<ECsLoadFlags_Editor::Type, EMCsLoadFlags_Editor>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsFxPriority))
				{ WriteMemberEnumAsBytePropertyToJson<ECsFxPriority::Type, EMCsFxPriority>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsSoundPriority))
				{ WriteMemberEnumAsBytePropertyToJson<ECsSoundPriority::Type, EMCsSoundPriority>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECsParametricFunctionType
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsParametricFunctionType))
				{ WriteMemberEnumAsBytePropertyToJson<ECsParametricFunctionType::Type, EMCsParametricFunctionType>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECsItemMemberValueType
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsItemMemberValueType))
				{ WriteMemberEnumAsBytePropertyToJson<ECsItemMemberValueType::Type, EMCsItemMemberValueType>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }
				// ECsItemOnConsumeContentAction
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsItemOnConsumeContentAction))
				{ WriteMemberEnumAsBytePropertyToJson<ECsItemOnConsumeContentAction::Type, EMCsItemOnConsumeContentAction>(InJsonWriter, ByteProperty, InStruct, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// uint8
			else
			{
				if (uint8* Member = ByteProperty->ContainerPtrToValuePtr<uint8>(InStruct))
					InJsonWriter->WriteValue(MemberName, *Member);
			}
			continue;
		}
		// uint16
		if (UUInt16Property* Int16Property = Cast<UUInt16Property>(*It))
		{
			if (uint16* Member = Int16Property->ContainerPtrToValuePtr<uint16>(InStruct))
			{ InJsonWriter->WriteValue(MemberName, *Member); continue; }
			continue;
		}
		// int32
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
		{

			if (int32* Member = IntProperty->ContainerPtrToValuePtr<int32>(InStruct))
			{
#if WITH_EDITOR
									//    TEXT("BitmaskEnum")
				if (Property->HasMetaData(*(NCsCommonLoadCached::Str::BitmaskEnum)))
				{
																//    TEXT("BitmaskEnum")
					const FString BitmaskEnum = Property->GetMetaData(*(NCsCommonLoadCached::Str::BitmaskEnum));

					// (BitmaskEnum == TEXT("ECsLoadFlags"))
					if (BitmaskEnum == NCsCommonLoadCached::Str::CsLoadFlags)
					{
						InJsonWriter->WriteValue(MemberName, EMCsLoadFlags::Get().MaskToString(*Member));
					}
				}
				else
#endif // #if WITH_EDITOR
				{
					InJsonWriter->WriteValue(MemberName, *Member);
				}
			}
			continue;
		}
		// uint64
		if (UUInt64Property* IntProperty = Cast<UUInt64Property>(*It))
		{
			if (uint64* Member = IntProperty->ContainerPtrToValuePtr<uint64>(InStruct))
				InJsonWriter->WriteValue(MemberName, FString::Printf(TEXT("%llu"), *Member));
			continue;
		}
		// float
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
		{
			if (float* Member = FloatProperty->ContainerPtrToValuePtr<float>(InStruct))
				InJsonWriter->WriteValue(MemberName, *Member);
			continue;
		}
		// FString
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
		{
			if (FString* Member = StrProperty->ContainerPtrToValuePtr<FString>(InStruct))
				InJsonWriter->WriteValue(MemberName, *Member);
			continue;
		}
		// FName
		if (UNameProperty* NameProperty = Cast<UNameProperty>(*It))
		{
			if (NameProperty->ArrayDim == CS_SINGLETON)
			{
				if (FName* Member = NameProperty->ContainerPtrToValuePtr<FName>(InStruct))
				{
					InJsonWriter->WriteValue(MemberName, (*Member).ToString()); continue;
				}
			}

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
	}
	InJsonWriter->WriteObjectEnd();
}

void UCsCommon_Load::WriteObjectToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, void* InObject, UClass* const &InClass, const TArray<FCsCategoryMemberAssociation> &CategoryMemberAssociations, TCsWriteObjectToJson_Internal Internal)
{
	const FString NoCategory = NCsCached::Str::Empty;
	FString Category		 = NoCategory;
	FString LastCategory	 = NoCategory;
	int32 CategoryIndex		 = 0;
	
	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);
		
		const FString MemberName = Property->GetName();

		if (CategoryIndex >= CategoryMemberAssociations.Num())
			break;

		const int32 Count = CategoryMemberAssociations[CategoryIndex].Members.Num();
		const int32 Index = CategoryMemberAssociations[CategoryIndex].Members.Find(MemberName);

		if (Index == INDEX_NONE)
			continue;

		Category = CategoryMemberAssociations[CategoryIndex].Category;

		if (Index == Count - 1)
			CategoryIndex++;

		// Check if Category changed
		if (Category != LastCategory)
		{
			// (LastCategory != TEXT(""))
			if (LastCategory != NCsCached::Str::Empty)
				InJsonWriter->WriteObjectEnd();
			InJsonWriter->WriteObjectStart(Category);

			LastCategory = Category;
		}

		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InObject, InClass))
					continue;
			}
			continue;
		}
		// TSoftObjectPtr
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(*It))
		{
			// UStaticMesh
			if (SoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ WriteSoftObjectPropertyToJson<UStaticMesh>(InJsonWriter, SoftObjectProperty, InObject, MemberName); continue; }
			// USkeletalMesh
			if (SoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ WriteSoftObjectPropertyToJson<USkeletalMesh>(InJsonWriter, SoftObjectProperty, InObject, MemberName); continue; }
			// UMaterialInstance
			if (SoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ WriteSoftObjectPropertyToJson<UMaterialInstance>(InJsonWriter, SoftObjectProperty, InObject, MemberName); continue; }
			// UMaterialInstanceConstant
			if (SoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{ WriteSoftObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, SoftObjectProperty, InObject, MemberName); continue; }
			// UPhysicalMaterial
			if (SoftObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ WriteSoftObjectPropertyToJson<UPhysicalMaterial>(InJsonWriter, SoftObjectProperty, InObject, MemberName); continue; }
			// UPhysicsAsset
			if (SoftObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ WriteSoftObjectPropertyToJson<UPhysicsAsset>(InJsonWriter, SoftObjectProperty, InObject, MemberName); continue; }
			// UAnimSequence
			if (SoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ WriteSoftObjectPropertyToJson<UAnimSequence>(InJsonWriter, SoftObjectProperty, InObject, MemberName); continue; }
			// UAnimMontage
			if (SoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ WriteSoftObjectPropertyToJson<UAnimMontage>(InJsonWriter, SoftObjectProperty, InObject, MemberName); continue; }
			// UBlendSpace
			if (SoftObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ WriteSoftObjectPropertyToJson<UBlendSpace>(InJsonWriter, SoftObjectProperty, InObject, MemberName); continue; }
			// UAnimBlueprint
			if (SoftObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ WriteSoftObjectPropertyToJson_AnimBlueprint(InJsonWriter, SoftObjectProperty, InObject, MemberName); continue; }
			// USoundCue
			if (SoftObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ WriteSoftObjectPropertyToJson<USoundCue>(InJsonWriter, SoftObjectProperty, InObject, MemberName); continue; }
			// UParticleSystem
			if (SoftObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ WriteSoftObjectPropertyToJson<UParticleSystem>(InJsonWriter, SoftObjectProperty, InObject, MemberName); continue; }
			// UCurveVector
			if (SoftObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ WriteSoftObjectPropertyToJson<UCurveVector>(InJsonWriter, SoftObjectProperty, InObject, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InObject, InClass))
					continue;
			}
			continue;
		}
		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FGuid
			if (StructProperty->Struct == TBaseStructure<FGuid>::Get())
			{ WriteMemberStructPropertyToJson_Primitive<FGuid>(InJsonWriter, StructProperty, InObject, MemberName, &FGuid::ToString); continue; }
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
			{ WriteMemberStructPropertyToJson_Primitive<FVector>(InJsonWriter, StructProperty, InObject, MemberName, &FVector::ToString); continue; }
			// FRotator
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
			{ WriteMemberStructPropertyToJson_Primitive<FRotator>(InJsonWriter, StructProperty, InObject, MemberName, &FRotator::ToString); continue; }
			// FColor
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
			{ WriteMemberStructPropertyToJson_Primitive<FColor>(InJsonWriter, StructProperty, InObject, MemberName, &FColor::ToString); continue; }
			// FTransform
			if (StructProperty->Struct == TBaseStructure<FTransform>::Get())
			{ WriteMemberStructPropertyToJson_Transform(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FInt32Interval
			if (StructProperty->Struct == TBaseStructure<FInt32Interval>::Get())
			{ WriteMemberStructPropertyToJson_BaseStructure<FInt32Interval>(InJsonWriter, StructProperty, InObject, MemberName, &UCsCommon_Load::ToString_FInt32Interval); continue; }
			// FFloatInterval
			if (StructProperty->Struct == TBaseStructure<FFloatInterval>::Get())
			{ WriteMemberStructPropertyToJson_BaseStructure<FFloatInterval>(InJsonWriter, StructProperty, InObject, MemberName, &UCsCommon_Load::ToString_FFloatInterval); continue; }
			// FCsUint8Point
			if (StructProperty->Struct == FCsUint8Point::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsUint8Point>(InJsonWriter, StructProperty, InObject, MemberName, &FCsUint8Point::ToString); continue; }
			// FCsUint8MatrixDimension
			if (StructProperty->Struct == FCsUint8MatrixDimension::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsUint8MatrixDimension>(InJsonWriter, StructProperty, InObject, MemberName, &FCsUint8MatrixDimension::ToString); continue; }
			// FCsUint8MatrixCoordinate
			if (StructProperty->Struct == FCsUint8MatrixCoordinate::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsUint8MatrixCoordinate>(InJsonWriter, StructProperty, InObject, MemberName, &FCsUint8MatrixCoordinate::ToString); continue; }
			// FCsVectorFlag
			if (StructProperty->Struct == FCsVectorFlag::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsVectorFlag>(InJsonWriter, StructProperty, InObject, MemberName, &FCsVectorFlag::ToString); continue; }
			// FCsRotatorFlag
			if (StructProperty->Struct == FCsRotatorFlag::StaticStruct())
			{ WriteMemberStructPropertyToJson_Primitive<FCsRotatorFlag>(InJsonWriter, StructProperty, InObject, MemberName, &FCsRotatorFlag::ToString); continue; }
			// FCsOptionalVectorInterval
			if (StructProperty->Struct == FCsOptionalVectorInterval::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsOptionalVectorInterval>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsOptionalRotatorInterval
			if (StructProperty->Struct == FCsOptionalRotatorInterval::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsOptionalRotatorInterval>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsStaticMesh>(InJsonWriter, StructProperty, InObject, MemberName); continue; }

				if (WriteObjectToJson_Internal_Helper(Internal, Property, InJsonWriter, InObject, InClass)) { continue; }
				continue;
			}
			// FCsFpvStaticMesh
			if (StructProperty->Struct == FCsFpvStaticMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvStaticMesh>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsTArrayStaticMesh
			if (StructProperty->Struct == FCsTArrayStaticMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsTArrayStaticMesh>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsSkeletalMesh>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsFpsSkeletalMesh
			if (StructProperty->Struct == FCsFpsSkeletalMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsSkeletalMesh>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsTArraySkeletalMesh
			if (StructProperty->Struct == FCsTArraySkeletalMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsTArraySkeletalMesh>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsMaterialInstance>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsMaterialInstanceConstant
			if (StructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsMaterialInstanceConstant>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsTArrayMaterialInstanceConstant::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsTArrayMaterialInstanceConstant>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
				if (StructProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ WriteMemberFixedArrayStructPropertyToJson_EnumSize<FCsTArrayMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(InJsonWriter, StructProperty, InObject, MemberName, &ECsInteractiveState::ToString, nullptr); continue; }
				
				if (WriteObjectToJson_Internal_Helper(Internal, Property, InJsonWriter, InObject, InClass)) { continue; }
				continue;
			}
			// FCsFpsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsFpsTArrayMaterialInstanceConstant::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsTArrayMaterialInstanceConstant>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsInteractiveMaterials
			if (StructProperty->Struct == FCsInteractiveMaterials::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsInteractiveMaterials>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsPhysicalMaterial
			if (StructProperty->Struct == FCsPhysicalMaterial::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPhysicalMaterial>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPhysicsAsset>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsPhysicsPreset
			if (StructProperty->Struct == FCsPhysicsPreset::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPhysicsPreset>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsPhysicsImpulse
			if (StructProperty->Struct == FCsPhysicsImpulse::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPhysicsImpulse>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsCurveFloat
			if (StructProperty->Struct == FCsCurveFloat::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsCurveFloat>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsCurveVector>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsSoundElement>(InJsonWriter, StructProperty, InObject, MemberName); continue; }

				if (WriteObjectToJson_Internal_Helper(Internal, Property, InJsonWriter, InObject, InClass)) { continue; }
				continue;
			}
			// FCsFpvSoundElement
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpvSoundElement>(InJsonWriter, StructProperty, InObject, MemberName); continue; }

				if (WriteObjectToJson_Internal_Helper(Internal, Property, InJsonWriter, InObject, InClass)) { continue; }
				continue;
			}
			// FCsParticleSystem
			if (StructProperty->Struct == FCsParticleSystem::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsParticleSystem>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFxElement>(InJsonWriter, StructProperty, InObject, MemberName); continue; }

				if (WriteObjectToJson_Internal_Helper(Internal, Property, InJsonWriter, InObject, InClass)) { continue; }
				continue;
			}
			// FCsFpvFxElement
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpvFxElement>(InJsonWriter, StructProperty, InObject, MemberName); continue; }

				if (WriteObjectToJson_Internal_Helper(Internal, Property, InJsonWriter, InObject, InClass)) { continue; }
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsAnimSequence>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsFpvAnimSequence
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvAnimSequence>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsAnimMontage>(InJsonWriter, StructProperty, InObject, MemberName); continue; }

				if (WriteObjectToJson_Internal_Helper(Internal, Property, InJsonWriter, InObject, InClass)) { continue; }
				continue;
			}
			// FCsFpvAnimMontage
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpvAnimMontage>(InJsonWriter, StructProperty, InObject, MemberName); continue; }

				if (WriteObjectToJson_Internal_Helper(Internal, Property, InJsonWriter, InObject, InClass)) { continue; }
				continue;
			}
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsTArrayAnimMontage>(InJsonWriter, StructProperty, InObject, MemberName); continue; }

				if (WriteObjectToJson_Internal_Helper(Internal, Property, InJsonWriter, InObject, InClass)) { continue; }
				continue;
			}
			// FCsBlendSpace1D
			if (StructProperty->Struct == FCsBlendSpace1D::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsBlendSpace1D>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsFpvBlendSpace1D
			if (StructProperty->Struct == FCsFpvBlendSpace1D::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvBlendSpace1D>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsBlendSpace>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsFpvBlendSpace
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvBlendSpace>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsAimOffset
			if (StructProperty->Struct == FCsAimOffset::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsAimOffset>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsFpvAimOffset
			if (StructProperty->Struct == FCsFpvAimOffset::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvAimOffset>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsAnimBlueprint>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsFpvAnimBlueprint
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvAnimBlueprint>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsBlueprint
			if (StructProperty->Struct == FCsBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsBlueprint>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsTArrayBlueprint
			if (StructProperty->Struct == FCsTArrayBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsTArrayBlueprint>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCollisionResponseContainer
			if (StructProperty->Struct == FCollisionResponseContainer::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCollisionResponseContainer>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsCollisionPreset
			if (StructProperty->Struct == FCsCollisionPreset::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsCollisionPreset>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }

				if (WriteObjectToJson_Internal_Helper(Internal, Property, InJsonWriter, InObject, InClass)) { continue; }
				continue;
			}
			// FCsHeadCollision
			if (StructProperty->Struct == FCsHeadCollision::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsHeadCollision>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsDrawDistance
			if (StructProperty->Struct == FCsDrawDistance::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsDrawDistance>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsFpvDrawDistance
			if (StructProperty->Struct == FCsFpvDrawDistance::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpvDrawDistance>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsWidgetComponentInfo
			if (StructProperty->Struct == FCsWidgetComponentInfo::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsWidgetComponentInfo>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsWidgetActorInfo
			if (StructProperty->Struct == FCsWidgetActorInfo::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsWidgetActorInfo>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsData_ProjectileImpactPtr
			if (StructProperty->Struct == FCsData_ProjectileImpactPtr::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsData_ProjectileImpactPtr>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsRadius
			if (StructProperty->Struct == FCsRadius::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsRadius>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsProjectileMovementFunction
			if (StructProperty->Struct == FCsProjectileMovementFunction::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsProjectileMovementFunction>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsParametricFunction
			if (StructProperty->Struct == FCsParametricFunction::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsParametricFunction>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsParametricFunctionAxis
			if (StructProperty->Struct == FCsParametricFunctionAxis::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsParametricFunctionAxis>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsDamageFalloff
			if (StructProperty->Struct == FCsDamageFalloff::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsDamageFalloff>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsDamageRadial
			if (StructProperty->Struct == FCsDamageRadial::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsDamageRadial>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsInventoryLoadout
			if (StructProperty->Struct == FCsInventoryLoadout::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsInventoryLoadout>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsTArrayPayload
			if (StructProperty->Struct == FCsTArrayPayload::StaticStruct())
			{
				if (WriteObjectToJson_Internal_Helper(Internal, Property, InJsonWriter, InObject, InClass)) { continue; }
				continue;
			}
			// FCsSenseData
			if (StructProperty->Struct == FCsSenseData::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsSenseData>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsData_ShortCode
			if (StructProperty->Struct == FCsData_ShortCode::StaticStruct())
			{ WriteMemberStructPropertyToJson_FCsData_ShortCode(InJsonWriter, StructProperty, InObject, MemberName); continue; }

			// EnumStruct
			{
				// FECsAssetType
				if (StructProperty->Struct == FECsAssetType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsAssetType>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
				// FECsLoadAssetsType
				if (StructProperty->Struct == FECsLoadAssetsType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsLoadAssetsType>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
				// FECsInputAction
				if (StructProperty->Struct == FECsInputAction::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsInputAction>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
				// FECsGameEvent
				if (StructProperty->Struct == FECsGameEvent::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsGameEvent>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
				// FECsSurfaceType
				if (StructProperty->Struct == FECsSurfaceType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsSurfaceType>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
				// FECsWeaponGrip
				if (StructProperty->Struct == FECsWeaponGrip::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsWeaponGrip>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
				// FECsDamageType
				if (StructProperty->Struct == FECsDamageType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsDamageType>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
				// FECsInteractiveType
				if (StructProperty->Struct == FECsInteractiveType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsInteractiveType>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
				// FECsProjectile
				if (StructProperty->Struct == FECsProjectile::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsProjectile>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
				// FECsSoundType
				if (StructProperty->Struct == FECsSoundType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsSoundType>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
				// FECsItemType
				if (StructProperty->Struct == FECsItemType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsItemType>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
				// FECsRecipeType
				if (StructProperty->Struct == FECsRecipeType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsRecipeType>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InObject, InClass))
					continue;
			}
			continue;
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftObjectPtr
			if (USoftObjectProperty* InnerSoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
			{
				// UMaterialInstance
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UMaterialInstance>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// UMaterialInstanceConstant
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// UAnimSequence
				if (InnerSoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UAnimSequence>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// UAnimMontage
				if (InnerSoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UAnimMontage>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// UBlueprint
				if (InnerSoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteArraySoftObjectPropertyToJson<UBlueprint>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InObject, InClass))
						continue;
				}
				continue;
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FGuid
				if (InnerStructProperty->Struct == TBaseStructure<FGuid>::Get())
				{ WriteMemberArrayStructPropertyToJson_Primitive<FGuid>(InJsonWriter, ArrayProperty, InObject, MemberName, &FGuid::ToString); continue; }
				// FVector
				if (InnerStructProperty->Struct == TBaseStructure<FVector>::Get())
				{ WriteMemberArrayStructPropertyToJson_Primitive<FVector>(InJsonWriter, ArrayProperty, InObject, MemberName, &FVector::ToString); continue; }
				// FRotator
				if (InnerStructProperty->Struct == TBaseStructure<FRotator>::Get())
				{ WriteMemberArrayStructPropertyToJson_Primitive<FRotator>(InJsonWriter, ArrayProperty, InObject, MemberName, &FRotator::ToString); continue; }
				// FColor
				if (InnerStructProperty->Struct == TBaseStructure<FColor>::Get())
				{ WriteMemberArrayStructPropertyToJson_Primitive<FColor>(InJsonWriter, ArrayProperty, InObject, MemberName, &FColor::ToString); continue; }
				// FTransform
				if (InnerStructProperty->Struct == TBaseStructure<FTransform>::Get())
				{ WriteMemberArrayStructPropertyToJson_Transform(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsAnimMontage>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsFxElement
				if (InnerStructProperty->Struct == FCsFxElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFxElement>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsFpvFxElement
				if (InnerStructProperty->Struct == FCsFpvFxElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpvFxElement>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsSoundElement>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsFpvSoundElement
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpvSoundElement>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsAnimSequence
				if (InnerStructProperty->Struct == FCsAnimSequence::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsAnimSequence>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsFpvAnimSequence
				if (InnerStructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpvAnimSequence>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsAnimMontage>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsFpvAnimMontage
				if (InnerStructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpvAnimMontage>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsDataMappingEntry
				if (InnerStructProperty->Struct == FCsDataMappingEntry::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsDataMappingEntry>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsItemMemberDescription
				if (InnerStructProperty->Struct == FCsItemMemberDescription::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsItemMemberDescription>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsRecipeIngredient
				if (InnerStructProperty->Struct == FCsRecipeIngredient::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsRecipeIngredient>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsItemOnConsumeContentRule
				if (InnerStructProperty->Struct == FCsItemOnConsumeContentRule::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsItemOnConsumeContentRule>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InObject, InClass))
						continue;
				}
				continue;
			}
			// FName
			if (UNameProperty* NameProperty = Cast<UNameProperty>(ArrayProperty->Inner))
			{ WriteMemberArrayStructPropertyToJson_Primitive<FName>(InJsonWriter, ArrayProperty, InObject, MemberName, &FName::ToString); continue; }
			// uint64
			if (UUInt64Property* IntProperty = Cast<UUInt64Property>(ArrayProperty->Inner))
			{ WriteMemberIntegralArrayPropertyToJson_uint64(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InObject, InClass))
					continue;
			}
			continue;
		}
		// Map
		if (UMapProperty* MapProperty = Cast<UMapProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InObject, InClass))
					continue;
			}
			continue;
		}
		// bool
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
		{
			if (bool* Member = BoolProperty->ContainerPtrToValuePtr<bool>(InObject))
				InJsonWriter->WriteValue(MemberName, *Member);
			continue;
		}
		// Enum Class
		if (UEnumProperty* EnumProperty = Cast<UEnumProperty>(*It))
		{
			// ECsEasingType
			if (EnumProperty->GetEnum()->CppType.Contains(NCsCommonLoadCached::Str::CsEasingType))
			{ WriteMemberEnumPropertyToJson<ECsEasingType, EMCsEasingType>(InJsonWriter, EnumProperty, InObject, MemberName); continue; }
			continue;
		}
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			// enum
			if (ByteProperty->IsEnum())
			{
				// ECollisionEnabled
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionEnabled))
				{ WriteMemberEnumAsBytePropertyToJson<ECollisionEnabled::Type, EMCollisionEnabled>(InJsonWriter, ByteProperty, InObject, MemberName); continue; }
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionChannel))
				{ WriteMemberEnumAsBytePropertyToJson<ECollisionChannel, EMCsCollisionChannel>(InJsonWriter, ByteProperty, InObject, MemberName); continue; }
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionResponse))
				{ WriteMemberEnumAsBytePropertyToJson<ECollisionResponse, EMCollisionResponse>(InJsonWriter, ByteProperty, InObject, MemberName); continue; }
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::HorizTextAligment))
				{ WriteMemberEnumAsBytePropertyToJson<EHorizTextAligment, EMHorizTextAligment>(InJsonWriter, ByteProperty, InObject, MemberName); continue; }
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::VerticalTextAligment))
				{ WriteMemberEnumAsBytePropertyToJson<EVerticalTextAligment, EMVerticalTextAligment>(InJsonWriter, ByteProperty, InObject, MemberName); continue; }
				// ECsLoadFlags_Editor
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsLoadFlags_Editor))
				{ WriteMemberEnumAsBytePropertyToJson<ECsLoadFlags_Editor::Type, EMCsLoadFlags_Editor>(InJsonWriter, ByteProperty, InObject, MemberName); continue; }
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsFxPriority))
				{ WriteMemberEnumAsBytePropertyToJson<ECsFxPriority::Type, EMCsFxPriority>(InJsonWriter, ByteProperty, InObject, MemberName); continue; }
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsSoundPriority))
				{ WriteMemberEnumAsBytePropertyToJson<ECsSoundPriority::Type, EMCsSoundPriority>(InJsonWriter, ByteProperty, InObject, MemberName); continue; }
				// ECsParametricFunctionType
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsParametricFunctionType))
				{ WriteMemberEnumAsBytePropertyToJson<ECsParametricFunctionType::Type, EMCsParametricFunctionType>(InJsonWriter, ByteProperty, InObject, MemberName); continue; }
				// ECsItemMemberValueType
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsItemMemberValueType))
				{ WriteMemberEnumAsBytePropertyToJson<ECsItemMemberValueType::Type, EMCsItemMemberValueType>(InJsonWriter, ByteProperty, InObject, MemberName); continue; }
				// ECsInteractiveCollision
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsInteractiveCollision))
				{
					if (ByteProperty->ArrayDim == CS_SINGLETON)
					{ WriteMemberEnumAsBytePropertyToJson<ECsInteractiveCollision::Type, EMCsInteractiveCollision>(InJsonWriter, ByteProperty, InObject, MemberName); continue; }
				}

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InObject, InClass))
						continue;
				}
				continue;
			}
			// uint8
			else
			{
				if (uint8* Member = ByteProperty->ContainerPtrToValuePtr<uint8>(InObject))
					InJsonWriter->WriteValue(MemberName, *Member);
			}
			continue;
		}
		// int32
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
		{
			if (int32* Member = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
			{
#if WITH_EDITOR
									//    TEXT("BitmaskEnum")
				if (Property->HasMetaData(*(NCsCommonLoadCached::Str::BitmaskEnum)))
				{
																//    TEXT("BitmaskEnum")
					const FString BitmaskEnum = Property->GetMetaData(*(NCsCommonLoadCached::Str::BitmaskEnum));

					// (BitmaskEnum == TEXT("ECsLoadFlags"))
					if (BitmaskEnum == NCsCommonLoadCached::Str::CsLoadFlags)
					{
						InJsonWriter->WriteValue(MemberName, EMCsLoadFlags::Get().MaskToString(*Member));
					}
				}
				else
#endif // #if WITH_EDITOR
				{
					InJsonWriter->WriteValue(MemberName, *Member);
				}
			}
			continue;
		}
		// uint64
		if (UUInt64Property* IntProperty = Cast<UUInt64Property>(*It))
		{
			if (uint64* Member = IntProperty->ContainerPtrToValuePtr<uint64>(InObject))
				InJsonWriter->WriteValue(MemberName, FString::Printf(TEXT("%llu"), *Member));
			continue;
		}
		// float
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
		{
			if (float* Member = FloatProperty->ContainerPtrToValuePtr<float>(InObject))
				InJsonWriter->WriteValue(MemberName, *Member);
			continue;
		}
		// FString
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
		{
			if (FString* Member = StrProperty->ContainerPtrToValuePtr<FString>(InObject))
				InJsonWriter->WriteValue(MemberName, *Member);
			continue;
		}
		// FName
		if (UNameProperty* NameProperty = Cast<UNameProperty>(*It))
		{
			if (FName* Member = NameProperty->ContainerPtrToValuePtr<FName>(InObject))
				InJsonWriter->WriteValue(MemberName, (*Member).ToString());
			continue;
		}
	}
	InJsonWriter->WriteObjectEnd();
}

#pragma endregion Write

	// Read
#pragma region

void UCsCommon_Load::WriteToSoftObjectPropertyFromJson_AnimBlueprint(TSharedPtr<FJsonObject> &JsonObject, USoftObjectProperty* &SoftObjectProperty, void* InObject, const FString &MemberName)
{
	if (TSoftObjectPtr<UAnimBlueprint>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UAnimBlueprint>>(InObject))
	{
		FString AssetName = JsonObject->GetStringField(MemberName);

		// (AssetName.EndsWith(TEXT("_C")))
		if (AssetName.EndsWith(ECsLoadCached::Str::_C))
			AssetName.RemoveFromEnd(ECsLoadCached::Str::_C);

		*Member = TSoftObjectPtr<UAnimBlueprint>(AssetName);
	}
}

void UCsCommon_Load::WriteToSoftObjectPropertyFromJson_Blueprint(TSharedPtr<FJsonObject> &JsonObject, USoftObjectProperty* &SoftObjectProperty, void* InObject, const FString &MemberName)
{
	if (TSoftObjectPtr<UBlueprint>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UBlueprint>>(InObject))
	{
		FString AssetName = JsonObject->GetStringField(MemberName);

		// (AssetName.EndsWith(TEXT("_C")))
		if (AssetName.EndsWith(ECsLoadCached::Str::_C))
			AssetName.RemoveFromEnd(ECsLoadCached::Str::_C);

		*Member = TSoftObjectPtr<UBlueprint>(AssetName);
	}
}

void UCsCommon_Load::WriteToMemberStructPropertyFromJson_Transform(TSharedPtr<FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString &MemberName)
{
	if (FTransform* Member = StructProperty->ContainerPtrToValuePtr<FTransform>(InObject))
	{
		TSharedPtr<FJsonObject> Object = JsonObject->Values.Find(NCsCommonLoadCached::Str::Transform)->Get()->AsObject();

		// Rotation
		FRotator Rotation;
														// TEXT("Rotation")
		Rotation.InitFromString(Object->GetStringField(NCsCommonLoadCached::Str::Rotation));
		FVector RotationAsVector = FVector(Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
		FQuat Quat = FQuat::MakeFromEuler(RotationAsVector);

		Member->SetRotation(Quat);
		// Translation
		FVector Translation;
															//TEXT("Translation")
		Translation.InitFromString(Object->GetStringField(NCsCommonLoadCached::Str::Translation));

		Member->SetTranslation(Translation);
		// Scale
		FVector Scale;
													//  TEXT("Scale")
		Scale.InitFromString(Object->GetStringField(NCsCommonLoadCached::Str::Scale));

		Member->SetScale3D(Scale);
	}
}

void UCsCommon_Load::WriteToMemberArrayStructPropertyFromJson_Transform(TSharedPtr<FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName)
{
	TArray<FTransform>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<FTransform>>(InObject);

	const TArray<TSharedPtr<FJsonValue>> JsonArray = JsonObject->GetArrayField(MemberName);

	const int32 ArrayCount = JsonArray.Num();
	const int32 MemberCount = Member->Num();
	const int32 Count		= FMath::Max(ArrayCount, MemberCount);

	for (int32 I = 0; I < Count; ++I)
	{
		if (I >= ArrayCount)
			break;

		if (I >= MemberCount)
			Member->AddDefaulted();

		TSharedPtr<FJsonObject> ArrayObject = JsonArray[I]->AsObject();
		TSharedPtr<FJsonObject> Object		= ArrayObject->Values.Find(NCsCommonLoadCached::Str::Transform)->Get()->AsObject();

		FTransform& Element = (*Member)[I];

		// Rotation
		FRotator Rotation;
													// TEXT("Rotation")
		Rotation.InitFromString(Object->GetStringField(NCsCommonLoadCached::Str::Rotation));
		FVector RotationAsVector = FVector(Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
		FQuat Quat = FQuat::MakeFromEuler(RotationAsVector);

		Element.SetRotation(Quat);
		// Translation
		FVector Translation;
														//TEXT("Translation")
		Translation.InitFromString(Object->GetStringField(NCsCommonLoadCached::Str::Translation));

		Element.SetTranslation(Translation);
		// Scale
		FVector Scale;
												//  TEXT("Scale")
		Scale.InitFromString(Object->GetStringField(NCsCommonLoadCached::Str::Scale));

		Element.SetScale3D(Scale);
	}
}

void UCsCommon_Load::WriteToMemberArrayStructPropertyFromJson_Name(TSharedPtr<FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName)
{
	TArray<FName>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<FName>>(InObject);

	const TSharedPtr<FJsonObject>& Object = JsonObject->GetObjectField(MemberName);

	TArray<FString> Keys;

	Object->Values.GetKeys(Keys);

	const int32 ArrayCount  = Keys.Num();
	const int32 MemberCount = Member->Num();
	const int32 Count		= FMath::Max(ArrayCount, MemberCount);

	for (int32 I = 0; I < Count; ++I)
	{
		if (I >= ArrayCount)
			break;

		if (I >= MemberCount)
			Member->AddDefaulted();

		const FString& Key				 = Keys[I];
		TSharedPtr<FJsonValue> JsonValue = *(Object->Values.Find(Key));
		FString Value					 = JsonValue->AsString();

		(*Member)[I] = FName(*Value);
	}
}

void UCsCommon_Load::WriteToMemberArrayStructPropertyFromJson_uint64(TSharedPtr<FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName)
{
	TArray<uint64>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<uint64>>(InObject);

	const TSharedPtr<FJsonObject>& Object = JsonObject->GetObjectField(MemberName);

	TArray<FString> Keys;

	Object->Values.GetKeys(Keys);

	const int32 ArrayCount  = Keys.Num();
	const int32 MemberCount = Member->Num();
	const int32 Count		= FMath::Max(ArrayCount, MemberCount);

	for (int32 I = 0; I < Count; ++I)
	{
		if (I >= ArrayCount)
			break;

		if (I >= MemberCount)
			Member->Add(0);

		const FString& Key				 = Keys[I];
		TSharedPtr<FJsonValue> JsonValue = *(Object->Values.Find(Key));
		FString Value					 = JsonValue->AsString();

		(*Member)[I] = FCString::Strtoui64(*Value, NULL, 10);
	}
}

void UCsCommon_Load::WriteToMemberStructPropertyFromJson_FCsData_ShortCode(TSharedPtr<class FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString &MemberName)
{
	FCsData_ShortCode* Member = StructProperty->ContainerPtrToValuePtr<FCsData_ShortCode>(InObject);

	TSharedPtr<FJsonObject> Object = JsonObject->GetObjectField(MemberName);
	const FString& AssetTypeName = Object->GetStringField(TEXT("Type"));
	// Type
	Member->Type = EMCsAssetType::Get().GetEnum(AssetTypeName).Value;
	// ShortCode
	Member->ShortCode = FName(*(Object->GetStringField(TEXT("ShortCode"))));
}

bool UCsCommon_Load::ReadStructFromJson_Internal_Helper(TCsReadStructFromJson_Internal Internal, UProperty* Property, TSharedPtr<class FJsonObject> &JsonObject, void* InStruct, UScriptStruct* const &InScriptStruct)
{
	if (Internal)
		return (*Internal)(Property, JsonObject, InStruct, InScriptStruct);
	return false;
}

bool UCsCommon_Load::ReadObjectFromJson_Internal_Helper(TCsReadObjectFromJson_Internal Internal, UProperty* Property, TSharedPtr<class FJsonObject> &JsonObject, void* InObject, UClass* const &InClass)
{
	if (Internal)
		return (*Internal)(Property, JsonObject, InObject, InClass);
	return false;
}

void UCsCommon_Load::ReadStructFromJson(TSharedPtr<FJsonObject> &JsonObject, void* InStruct, UScriptStruct* const &InScriptStruct, TCsReadStructFromJson_Internal Internal /*=nullptr*/)
{
	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(*It))
		{
			// ACsData_ProjectileBase
			if (SoftClassProperty->MetaClass == ACsData_ProjectileBase::StaticClass())
			{ WriteToSoftClassPropertyFromJson<ACsData_ProjectileBase>(JsonObject, SoftClassProperty, InStruct, MemberName); continue; }
			// ACsData_ProjectileImpact
			if (SoftClassProperty->MetaClass == ACsData_ProjectileImpact::StaticClass())
			{ WriteToSoftClassPropertyFromJson<ACsData_ProjectileImpact>(JsonObject, SoftClassProperty, InStruct, MemberName); continue; }
			// ACsData
			if (SoftClassProperty->MetaClass == ACsData::StaticClass())
			{ WriteToSoftClassPropertyFromJson<ACsData>(JsonObject, SoftClassProperty, InStruct, MemberName); continue; }
			
			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// TSoftObjectPtr
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(*It))
		{
			// UStaticMesh
			if (SoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UStaticMesh>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// USkeletalMesh
			if (SoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<USkeletalMesh>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstance
			if (SoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UMaterialInstance>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstanceConstant
			if (SoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{
				if (SoftObjectProperty->ArrayDim == CS_SINGLETON)
				{ WriteToSoftObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
				if (SoftObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ WriteToFixedArraySoftObjectPropertyFromJson_EnumSize<UMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(JsonObject, SoftObjectProperty, InStruct, MemberName, &ECsInteractiveState::ToString); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// UPhysicalMaterial
			if (SoftObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UPhysicalMaterial>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UPhysicsAsset
			if (SoftObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UPhysicsAsset>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UCurveFloat
			if (SoftObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UCurveFloat>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UCurveVector
			if (SoftObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UCurveVector>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// USoundCue
			if (SoftObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<USoundCue>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UParticleSystem
			if (SoftObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UParticleSystem>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UAnimSequence
			if (SoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UAnimSequence>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UAnimMontage
			if (SoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UAnimMontage>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace1D
			if (SoftObjectProperty->PropertyClass == UBlendSpace1D::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UBlendSpace1D>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace
			if (SoftObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UBlendSpace>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UAnimBlueprint
			if (SoftObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ WriteToSoftObjectPropertyFromJson_AnimBlueprint(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UBlueprint
			if (SoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{ WriteToSoftObjectPropertyFromJson_Blueprint(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FGuid
			if (StructProperty->Struct == TBaseStructure<FGuid>::Get())
			{ WriteToMemberStructPropertyFromJson_BaseStructure<FGuid>(JsonObject, StructProperty, InStruct, MemberName, &FGuid::Parse); continue; }
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FVector>(JsonObject, StructProperty, InStruct, MemberName, &FVector::InitFromString); continue; }
			// FRotator
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FRotator>(JsonObject, StructProperty, InStruct, MemberName, &FRotator::InitFromString); continue; }
			// FColor
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FColor>(JsonObject, StructProperty, InStruct, MemberName, &FColor::InitFromString); continue; }
			// FTransform
			if (StructProperty->Struct == TBaseStructure<FTransform>::Get())
			{ WriteToMemberStructPropertyFromJson_Transform(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FInt32Interval
			if (StructProperty->Struct == TBaseStructure<FInt32Interval>::Get())
			{ WriteToMemberStructPropertyFromJson_BaseStructure<FInt32Interval>(JsonObject, StructProperty, InStruct, MemberName, &UCsCommon_Load::InitFromString_FInt32Interval); continue; }
			// FFloatInterval
			if (StructProperty->Struct == TBaseStructure<FFloatInterval>::Get())
			{ WriteToMemberStructPropertyFromJson_BaseStructure<FFloatInterval>(JsonObject, StructProperty, InStruct, MemberName, &UCsCommon_Load::InitFromString_FFloatInterval); continue; }
			// FCsUint8Point
			if (StructProperty->Struct == FCsUint8Point::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsUint8Point>(JsonObject, StructProperty, InStruct, MemberName, &FCsUint8Point::InitFromString); continue; }
			// FCsUint8MatrixDimension
			if (StructProperty->Struct == FCsUint8MatrixDimension::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsUint8MatrixDimension>(JsonObject, StructProperty, InStruct, MemberName, &FCsUint8MatrixDimension::InitFromString); continue; }
			// FCsUint8MatrixCoordinate
			if (StructProperty->Struct == FCsUint8MatrixCoordinate::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsUint8MatrixCoordinate>(JsonObject, StructProperty, InStruct, MemberName, &FCsUint8MatrixCoordinate::InitFromString); continue; }
			// FCsVectorFlag
			if (StructProperty->Struct == FCsVectorFlag::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsVectorFlag>(JsonObject, StructProperty, InStruct, MemberName, &FCsVectorFlag::InitFromString); continue; }
			// FCsRotatorFlag
			if (StructProperty->Struct == FCsRotatorFlag::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsRotatorFlag>(JsonObject, StructProperty, InStruct, MemberName, &FCsRotatorFlag::InitFromString); continue; }
			// FCsOptionalVectorInterval
			if (StructProperty->Struct == FCsOptionalVectorInterval::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsOptionalVectorInterval>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsOptionalRotatorInterval
			if (StructProperty->Struct == FCsOptionalRotatorInterval::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsOptionalRotatorInterval>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsStaticMesh>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvStaticMesh
			if (StructProperty->Struct == FCsFpvStaticMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvStaticMesh>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsSkeletalMesh>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpsSkeletalMesh
			if (StructProperty->Struct == FCsFpsSkeletalMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsSkeletalMesh>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsMaterialInstance>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsMaterialInstanceConstant
			if (StructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsMaterialInstanceConstant>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsTArrayMaterialInstanceConstant::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsTArrayMaterialInstanceConstant>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsFpsTArrayMaterialInstanceConstant::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsTArrayMaterialInstanceConstant>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsPhysicalMaterial
			if (StructProperty->Struct == FCsPhysicalMaterial::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsPhysicalMaterial>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsPhysicsAsset>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsCurveFloat
			if (StructProperty->Struct == FCsCurveFloat::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsCurveFloat>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsCurveVector>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsSoundElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvSoundElement
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpvSoundElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFxElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvFxElement
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpvFxElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsAnimSequence>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpvAnimSequence
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvAnimSequence>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsAnimMontage>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvAnimMontage
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpvAnimMontage>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsTArrayAnimMontage>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsBlendSpace1D
			if (StructProperty->Struct == FCsBlendSpace1D::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsBlendSpace1D>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpvBlendSpace1D
			if (StructProperty->Struct == FCsFpvBlendSpace1D::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvBlendSpace1D>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsBlendSpace>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpvBlendSpace
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvBlendSpace>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsAimOffset
			if (StructProperty->Struct == FCsAimOffset::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsAimOffset>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpvAimOffset
			if (StructProperty->Struct == FCsFpvAimOffset::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvAimOffset>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsAnimBlueprint>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpvAnimBlueprint
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvAnimBlueprint>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsBlueprint
			if (StructProperty->Struct == FCsBlueprint::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsBlueprint>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsTArrayBlueprint
			if (StructProperty->Struct == FCsTArrayBlueprint::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsTArrayBlueprint>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCollisionResponseContainer
			if (StructProperty->Struct == FCollisionResponseContainer::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCollisionResponseContainer>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsDataMappingEntry
			if (StructProperty->Struct == FCsDataMappingEntry::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsDataMappingEntry>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsInputProfile
			if (StructProperty->Struct == FCsInputProfile::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsInputProfile>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsInputActionMappings
			if (StructProperty->Struct == FCsInputActionMappings::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsInputActionMappings>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				if (StructProperty->ArrayDim == ECS_INPUT_DEVICE_MAX)
				{ WriteToMemberFixedArrayStructPropertyFromJson_EnumSize<FCsInputActionMappings, ECsInputDevice, EMCsInputDevice, ECS_INPUT_DEVICE_MAX>(JsonObject, StructProperty, InStruct, MemberName, nullptr); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsInputActionMapping
			if (StructProperty->Struct == FCsInputActionMapping::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsInputActionMapping>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsDrawDistance
			if (StructProperty->Struct == FCsDrawDistance::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsDrawDistance>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsFpvDrawDistance
			if (StructProperty->Struct == FCsFpvDrawDistance::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvDrawDistance>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// Weapon_FireMode
			{
				// FCsData_Weapon_FireMode_Firing
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Firing::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_Weapon_FireMode_Firing>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_Weapon_FireMode_Animation
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Animation::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_Weapon_FireMode_Animation>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_FpsWeapon_FireMode_Animation
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Animation::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_FpsWeapon_FireMode_Animation>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_Weapon_FireMode_Movement
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Movement::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_Weapon_FireMode_Movement>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_Weapon_FireMode_Aiming
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Aiming::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_Weapon_FireMode_Aiming>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_FpsWeapon_FireMode_Aiming
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Aiming::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_FpsWeapon_FireMode_Aiming>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_Weapon_FireMode_Scope
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Scope::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_Weapon_FireMode_Scope>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_Weapon_FireMode_FXs
				if (StructProperty->Struct == FCsData_Weapon_FireMode_FXs::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_Weapon_FireMode_FXs>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_FpsWeapon_FireMode_FXs
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_FXs::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_FpsWeapon_FireMode_FXs>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_Weapon_FireMode_Sounds
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Sounds::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_Weapon_FireMode_Sounds>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_FpsWeapon_FireMode_Sounds
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Sounds::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_FpsWeapon_FireMode_Sounds>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			}
			// FCsData_ProjectileBasePtr
			if (StructProperty->Struct == FCsData_ProjectileBasePtr::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsData_ProjectileBasePtr>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsData_ProjectileImpactPtr
			if (StructProperty->Struct == FCsData_ProjectileImpactPtr::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsData_ProjectileImpactPtr>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsRadius
			if (StructProperty->Struct == FCsRadius::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsRadius>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsProjectileMovementFunctionAxis
			if (StructProperty->Struct == FCsProjectileMovementFunctionAxis::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsProjectileMovementFunctionAxis>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsParametricFunction
			if (StructProperty->Struct == FCsParametricFunction::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsParametricFunction>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsParametricFunctionAxis
			if (StructProperty->Struct == FCsParametricFunctionAxis::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsParametricFunctionAxis>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsItemMemberDescription
			if (StructProperty->Struct == FCsItemMemberDescription::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsItemMemberDescription>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsInventoryLoadoutRecipe
			if (StructProperty->Struct == FCsInventoryLoadoutRecipe::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsInventoryLoadoutRecipe>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsInventoryLoadoutItem
			if (StructProperty->Struct == FCsInventoryLoadoutItem::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsInventoryLoadoutItem>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsRecipeIngredient
			if (StructProperty->Struct == FCsRecipeIngredient::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsRecipeIngredient>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsPlayerData_Inventory_Bag
			if (StructProperty->Struct == FCsPlayerData_Inventory_Bag::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsPlayerData_Inventory_Bag>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsPlayerData_Inventory_Slot
			if (StructProperty->Struct == FCsPlayerData_Inventory_Slot::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsPlayerData_Inventory_Slot>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsItemOnConsumeContentRule
			if (StructProperty->Struct == FCsItemOnConsumeContentRule::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsItemOnConsumeContentRule>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsTArrayPayload
			if (StructProperty->Struct == FCsTArrayPayload::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsTArrayPayload>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsPayload
			if (StructProperty->Struct == FCsPayload::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsPayload>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsData_ShortCode
			if (StructProperty->Struct == FCsData_ShortCode::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_FCsData_ShortCode(JsonObject, StructProperty, InStruct, MemberName); continue; }

			// EnumStruct
			{
				// FECsAssetType
				if (StructProperty->Struct == FECsAssetType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsAssetType, EMCsAssetType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsLoadAssetsType
				if (StructProperty->Struct == FECsLoadAssetsType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsLoadAssetsType, EMCsLoadAssetsType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsInputAction
				if (StructProperty->Struct == FECsInputAction::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsInputAction, EMCsInputAction>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsGameEvent
				if (StructProperty->Struct == FECsGameEvent::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsGameEvent, EMCsGameEvent>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsSurfaceType
				if (StructProperty->Struct == FECsSurfaceType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsSurfaceType, EMCsSurfaceType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsWeaponGrip
				if (StructProperty->Struct == FECsWeaponGrip::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsWeaponGrip, EMCsWeaponGrip>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsDamageType
				if (StructProperty->Struct == FECsDamageType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsDamageType, EMCsDamageType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsInteractiveType
				if (StructProperty->Struct == FECsInteractiveType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsInteractiveType, EMCsInteractiveType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsProjectile
				if (StructProperty->Struct == FECsProjectile::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsProjectile, EMCsProjectile>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsSoundType
				if (StructProperty->Struct == FECsSoundType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsSoundType, EMCsSoundType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsItemType
				if (StructProperty->Struct == FECsItemType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsItemType, EMCsItemType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsRecipeType
				if (StructProperty->Struct == FECsRecipeType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsRecipeType, EMCsRecipeType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftObjectPtr
			if (USoftObjectProperty* InnerSoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerSoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UStaticMesh>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// USkeletalMesh
				if (InnerSoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<USkeletalMesh>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstance
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UMaterialInstance>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstanceConstant
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimSequence
				if (InnerSoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UAnimSequence>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimMontage
				if (InnerSoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UAnimMontage>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UBlueprint
				if (InnerSoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UBlueprint>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FGuid
				if (InnerStructProperty->Struct == TBaseStructure<FGuid>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_BaseStructure<FGuid>(JsonObject, ArrayProperty, InStruct, MemberName, &FGuid::Parse); continue; }
				// FVector
				if (InnerStructProperty->Struct == TBaseStructure<FVector>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FVector>(JsonObject, ArrayProperty, InStruct, MemberName, &FVector::InitFromString); continue; }
				// FRotator
				if (InnerStructProperty->Struct == TBaseStructure<FRotator>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FRotator>(JsonObject, ArrayProperty, InStruct, MemberName, &FRotator::InitFromString); continue; }
				// FColor
				if (InnerStructProperty->Struct == TBaseStructure<FColor>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FColor>(JsonObject, ArrayProperty, InStruct, MemberName, &FColor::InitFromString); continue; }
				// FTransform
				if (InnerStructProperty->Struct == TBaseStructure<FTransform>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Transform(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsAnimMontage>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsFxElement
				if (InnerStructProperty->Struct == FCsFxElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFxElement>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsFpvFxElement
				if (InnerStructProperty->Struct == FCsFpvFxElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpvFxElement>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsSoundElement>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsFpvSoundElement
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpvSoundElement>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsAnimSequence
				if (InnerStructProperty->Struct == FCsAnimSequence::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsAnimSequence>(JsonObject, ArrayProperty, InStruct, MemberName, nullptr); continue; }
				// FCsFpvAnimSequence
				if (InnerStructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpvAnimSequence>(JsonObject, ArrayProperty, InStruct, MemberName, nullptr); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsAnimMontage>(JsonObject, ArrayProperty, InStruct, MemberName, nullptr); continue; }
				// FCsFpvAnimMontage
				if (InnerStructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpvAnimMontage>(JsonObject, ArrayProperty, InStruct, MemberName, nullptr); continue; }
				// FCsInputActionMapping
				if (InnerStructProperty->Struct == FCsInputActionMapping::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsInputActionMapping>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsInventoryLoadoutRecipe
				if (InnerStructProperty->Struct == FCsInventoryLoadoutRecipe::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsInventoryLoadoutRecipe>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsInventoryLoadoutItem
				if (InnerStructProperty->Struct == FCsInventoryLoadoutItem::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsInventoryLoadoutItem>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsPlayerData_Inventory_Bag
				if (InnerStructProperty->Struct == FCsPlayerData_Inventory_Bag::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsPlayerData_Inventory_Bag>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsPlayerData_Inventory_Slot
				if (InnerStructProperty->Struct == FCsPlayerData_Inventory_Slot::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsPlayerData_Inventory_Slot>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsPayload
				if (InnerStructProperty->Struct == FCsPayload::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsPayload>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FName
			if (UNameProperty* NameProperty = Cast<UNameProperty>(ArrayProperty->Inner))
			{ WriteToMemberArrayStructPropertyFromJson_Name(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
			// uint64
			if (UUInt64Property* IntProperty = Cast<UUInt64Property>(ArrayProperty->Inner))
			{ WriteToMemberArrayStructPropertyFromJson_uint64(JsonObject, ArrayProperty, InStruct, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// Map
		if (UMapProperty* MapProperty = Cast<UMapProperty>(*It))
		{
			UStructProperty* KeyStructProp = Cast<UStructProperty>(MapProperty->KeyProp);
			UFloatProperty* ValueFloatProp = Cast<UFloatProperty>(MapProperty->ValueProp);

			if (KeyStructProp && ValueFloatProp)
			{
				// FECsSenseActorType, float
				if (KeyStructProp->Struct == FECsSenseActorType::StaticStruct())
				{ WriteToMemberMapStructPropertyFromJson_EnumStructKey_NumericValue<FECsSenseActorType, float>(JsonObject, MapProperty, InStruct, MemberName, Internal); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// bool
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
		{
			if (bool* Member = BoolProperty->ContainerPtrToValuePtr<bool>(InStruct))
			{ *Member = JsonObject->GetBoolField(MemberName); continue; }
			continue;
		}
		// Enum Class
		if (UEnumProperty* EnumProperty = Cast<UEnumProperty>(*It))
		{
			// ECsEasingType
			if (EnumProperty->GetEnum()->CppType.Contains(NCsCommonLoadCached::Str::CsEasingType))
			{ WriteToMemberEnumPropertyFromJson<ECsEasingType, EMCsEasingType>(JsonObject, EnumProperty, InStruct, MemberName); continue; }
			// ECsProjectileMovementFunctionType
			if (EnumProperty->GetEnum()->CppType.Contains(NCsCommonLoadCached::Str::CsProjectileMovementFunctionType))
			{ WriteToMemberEnumPropertyFromJson<ECsProjectileMovementFunctionType, EMCsProjectileMovementFunctionType>(JsonObject, EnumProperty, InStruct, MemberName); continue; }
			continue;
		}
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			// enum
			if (ByteProperty->IsEnum())
			{
				// ECollisionEnabled
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionEnabled))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECollisionEnabled::Type, EMCollisionEnabled>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionChannel))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECollisionChannel, EMCsCollisionChannel>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionResponse))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECollisionResponse, EMCollisionResponse>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::HorizTextAligment))
				{ WriteToMemberEnumAsBytePropertyFromJson<EHorizTextAligment, EMHorizTextAligment>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::VerticalTextAligment))
				{ WriteToMemberEnumAsBytePropertyFromJson<EHorizTextAligment, EMHorizTextAligment>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECsLoadFlags_Editor
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsLoadFlags_Editor))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsLoadFlags_Editor::Type, EMCsLoadFlags_Editor>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsFxPriority))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsFxPriority::Type, EMCsFxPriority>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsSoundPriority))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsSoundPriority::Type, EMCsSoundPriority>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECsParametricFunctionType
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsParametricFunctionType))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsParametricFunctionType::Type, EMCsParametricFunctionType>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECsItemMemberValueType
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsProjectileMovementFunctionType))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsItemMemberValueType::Type, EMCsItemMemberValueType>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECsItemOnConsumeContentAction
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsItemOnConsumeContentAction))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsItemOnConsumeContentAction::Type, EMCsItemOnConsumeContentAction>(JsonObject, ByteProperty, InStruct, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// uint8
			else
			{
				if (uint8* Member = ByteProperty->ContainerPtrToValuePtr<uint8>(InStruct))
				{ *Member = (uint8)JsonObject->GetIntegerField(MemberName); continue; }
				continue;
			}
			continue;
		}
		if (UUInt16Property* IntProperty = Cast<UUInt16Property>(*It))
		{
			if (uint16* Member = IntProperty->ContainerPtrToValuePtr<uint16>(InStruct))
			{ *Member = (uint16)JsonObject->GetIntegerField(MemberName); continue; }
			continue;
		}
		// int32
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
		{
			if (int32* Member = IntProperty->ContainerPtrToValuePtr<int32>(InStruct))
			{
				FString String;

				// BitmaskEnum
				if (JsonObject->TryGetStringField(MemberName, String))
				{
					if (String.Len() > 0)
					{
						bool IsInt = false;

						for (int32 I = 0; I < 10; ++I)
						{
							if (String[0] == FString::FromInt(I)[0])
								IsInt |= true;
							if (IsInt)
								break;
						}

						if (IsInt)
						{
							*Member = JsonObject->GetIntegerField(MemberName); continue;
						}
						else
						{
							*Member = EMCsLoadFlags::Get().StringToMask(JsonObject->GetStringField(MemberName)); continue;
						}
					}
					else
					{
						*Member = JsonObject->GetIntegerField(MemberName); continue;
					}
				}
				else
				{
					*Member = JsonObject->GetIntegerField(MemberName); continue;
				}
			}
			continue;
		}
		// uint64
		if (UUInt64Property* IntProperty = Cast<UUInt64Property>(*It))
		{
			if (uint64* Member = IntProperty->ContainerPtrToValuePtr<uint64>(InStruct))
			{ *Member = FCString::Strtoui64(*(JsonObject->GetStringField(MemberName)), NULL, 10); continue; }
		}
		// float
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
		{
			if (float* Member = FloatProperty->ContainerPtrToValuePtr<float>(InStruct))
			{ *Member = (float)JsonObject->GetNumberField(MemberName); continue; }
			continue;
		}
		// FString
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
		{
			if (FString* Member = StrProperty->ContainerPtrToValuePtr<FString>(InStruct))
			{ *Member = JsonObject->GetStringField(MemberName); continue; }
			continue;
		}
		// FName
		if (UNameProperty* NameProperty = Cast<UNameProperty>(*It))
		{
			if (NameProperty->ArrayDim == CS_SINGLETON)
			{
				if (FName* Member = NameProperty->ContainerPtrToValuePtr<FName>(InStruct))
				{ *Member = FName(*JsonObject->GetStringField(MemberName)); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
					continue;
			}
		}
	}
}

void UCsCommon_Load::ReadStructFromJson(TSharedPtr<FJsonObject> &JsonParsed, void* InStruct, UScriptStruct* const &InScriptStruct, const TArray<FCsCategoryMemberAssociation> &CategoryMemberAssociations, TCsReadStructFromJson_Internal Internal /*=nullptr*/)
{
	const FString NoCategory = NCsCached::Str::Empty;
	FString Category		 = NoCategory;
	int32 CategoryIndex		 = 0;

	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		if (CategoryIndex >= CategoryMemberAssociations.Num())
			break;

		const int32 Count = CategoryMemberAssociations[CategoryIndex].Members.Num();
		const int32 Index = CategoryMemberAssociations[CategoryIndex].Members.Find(MemberName);

		if (Index == INDEX_NONE)
			continue;

		Category = CategoryMemberAssociations[CategoryIndex].Category;

		if (Index == Count - 1)
			CategoryIndex++;

		TSharedPtr<FJsonObject> JsonObject = JsonParsed->Values.Find(Category)->Get()->AsObject();

		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(*It))
		{
			// ACsData_ProjectileBase
			if (SoftClassProperty->MetaClass == ACsData_ProjectileBase::StaticClass())
			{ WriteToSoftClassPropertyFromJson<ACsData_ProjectileBase>(JsonObject, SoftClassProperty, InStruct, MemberName); continue; }
			// ACsData_ProjectileImpact
			if (SoftClassProperty->MetaClass == ACsData_ProjectileImpact::StaticClass())
			{ WriteToSoftClassPropertyFromJson<ACsData_ProjectileImpact>(JsonObject, SoftClassProperty, InStruct, MemberName); continue; }
			// ACsData
			if (SoftClassProperty->MetaClass == ACsData::StaticClass())
			{ WriteToSoftClassPropertyFromJson<ACsData>(JsonObject, SoftClassProperty, InStruct, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// TSoftObjectPtr
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(*It))
		{
			// UStaticMesh
			if (SoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UStaticMesh>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// USkeletalMesh
			if (SoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<USkeletalMesh>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstance
			if (SoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UMaterialInstance>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstanceConstant
			if (SoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{
				if (SoftObjectProperty->ArrayDim == CS_SINGLETON)
				{ WriteToSoftObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
				if (SoftObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ WriteToFixedArraySoftObjectPropertyFromJson_EnumSize<UMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(JsonObject, SoftObjectProperty, InStruct, MemberName, &ECsInteractiveState::ToString); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// UPhysicalMaterial
			if (SoftObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UPhysicalMaterial>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UPhysicsAsset
			if (SoftObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UPhysicsAsset>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UCurveFloat
			if (SoftObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UCurveFloat>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UCurveVector
			if (SoftObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UCurveVector>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// USoundCue
			if (SoftObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<USoundCue>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UParticleSystem
			if (SoftObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UParticleSystem>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UAnimSequence
			if (SoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UAnimSequence>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UAnimMontage
			if (SoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UAnimMontage>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace1D
			if (SoftObjectProperty->PropertyClass == UBlendSpace1D::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UBlendSpace1D>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace
			if (SoftObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UBlendSpace>(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UAnimBlueprint
			if (SoftObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ WriteToSoftObjectPropertyFromJson_AnimBlueprint(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }
			// UBlueprint
			if (SoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{ WriteToSoftObjectPropertyFromJson_Blueprint(JsonObject, SoftObjectProperty, InStruct, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FGuid
			if (StructProperty->Struct == TBaseStructure<FGuid>::Get())
			{ WriteToMemberStructPropertyFromJson_BaseStructure<FGuid>(JsonObject, StructProperty, InStruct, MemberName, &FGuid::Parse); continue; }
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FVector>(JsonObject, StructProperty, InStruct, MemberName, &FVector::InitFromString); continue; }
			// FRotator
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FRotator>(JsonObject, StructProperty, InStruct, MemberName, &FRotator::InitFromString); continue; }
			// FColor
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FColor>(JsonObject, StructProperty, InStruct, MemberName, &FColor::InitFromString); continue; }
			// FTransform
			if (StructProperty->Struct == TBaseStructure<FTransform>::Get())
			{ WriteToMemberStructPropertyFromJson_Transform(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FInt32Interval
			if (StructProperty->Struct == TBaseStructure<FInt32Interval>::Get())
			{ WriteToMemberStructPropertyFromJson_BaseStructure<FInt32Interval>(JsonObject, StructProperty, InStruct, MemberName, &UCsCommon_Load::InitFromString_FInt32Interval); continue; }
			// FFloatInterval
			if (StructProperty->Struct == TBaseStructure<FFloatInterval>::Get())
			{ WriteToMemberStructPropertyFromJson_BaseStructure<FFloatInterval>(JsonObject, StructProperty, InStruct, MemberName, &UCsCommon_Load::InitFromString_FFloatInterval); continue; }
			// FCsUint8Point
			if (StructProperty->Struct == FCsUint8Point::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsUint8Point>(JsonObject, StructProperty, InStruct, MemberName, &FCsUint8Point::InitFromString); continue; }
			// FCsUint8MatrixDimension
			if (StructProperty->Struct == FCsUint8MatrixDimension::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsUint8MatrixDimension>(JsonObject, StructProperty, InStruct, MemberName, &FCsUint8MatrixDimension::InitFromString); continue; }
			// FCsUint8MatrixCoordinate
			if (StructProperty->Struct == FCsUint8MatrixCoordinate::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsUint8MatrixCoordinate>(JsonObject, StructProperty, InStruct, MemberName, &FCsUint8MatrixCoordinate::InitFromString); continue; }
			// FCsVectorFlag
			if (StructProperty->Struct == FCsVectorFlag::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsVectorFlag>(JsonObject, StructProperty, InStruct, MemberName, &FCsVectorFlag::InitFromString); continue; }
			// FCsRotatorFlag
			if (StructProperty->Struct == FCsRotatorFlag::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsRotatorFlag>(JsonObject, StructProperty, InStruct, MemberName, &FCsRotatorFlag::InitFromString); continue; }
			// FCsOptionalVectorInterval
			if (StructProperty->Struct == FCsOptionalVectorInterval::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsOptionalVectorInterval>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsOptionalRotatorInterval
			if (StructProperty->Struct == FCsOptionalRotatorInterval::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsOptionalRotatorInterval>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsStaticMesh>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvStaticMesh
			if (StructProperty->Struct == FCsFpvStaticMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvStaticMesh>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsSkeletalMesh>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpsSkeletalMesh
			if (StructProperty->Struct == FCsFpsSkeletalMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsSkeletalMesh>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsMaterialInstance>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsMaterialInstanceConstant
			if (StructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsMaterialInstanceConstant>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsTArrayMaterialInstanceConstant::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsTArrayMaterialInstanceConstant>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsFpsTArrayMaterialInstanceConstant::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsTArrayMaterialInstanceConstant>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsPhysicalMaterial
			if (StructProperty->Struct == FCsPhysicalMaterial::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsPhysicalMaterial>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsPhysicsAsset>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsCurveFloat
			if (StructProperty->Struct == FCsCurveFloat::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsCurveFloat>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsCurveVector>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsSoundElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvSoundElement
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpvSoundElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFxElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvFxElement
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpvFxElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsAnimSequence>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpvAnimSequence
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvAnimSequence>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsAnimMontage>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsFpvAnimMontage
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpvAnimMontage>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsTArrayAnimMontage>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsBlendSpace1D
			if (StructProperty->Struct == FCsBlendSpace1D::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsBlendSpace1D>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpvBlendSpace1D
			if (StructProperty->Struct == FCsFpvBlendSpace1D::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvBlendSpace1D>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsBlendSpace>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpvBlendSpace
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvBlendSpace>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsAimOffset
			if (StructProperty->Struct == FCsAimOffset::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsAimOffset>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpvAimOffset
			if (StructProperty->Struct == FCsFpvAimOffset::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvAimOffset>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsAnimBlueprint>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpvAnimBlueprint
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvAnimBlueprint>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsBlueprint
			if (StructProperty->Struct == FCsBlueprint::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsBlueprint>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsTArrayBlueprint
			if (StructProperty->Struct == FCsTArrayBlueprint::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsTArrayBlueprint>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsCollisionPreset
			if (StructProperty->Struct == FCsCollisionPreset::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsCollisionPreset>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCollisionResponseContainer
			if (StructProperty->Struct == FCollisionResponseContainer::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCollisionResponseContainer>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsDataMappingEntry
			if (StructProperty->Struct == FCsDataMappingEntry::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsDataMappingEntry>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsInputProfile
			if (StructProperty->Struct == FCsInputProfile::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsInputProfile>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsInputActionMappings
			if (StructProperty->Struct == FCsInputActionMappings::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsInputActionMappings>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				if (StructProperty->ArrayDim == ECS_INPUT_DEVICE_MAX)
				{ WriteToMemberFixedArrayStructPropertyFromJson_EnumSize<FCsInputActionMappings, ECsInputDevice, EMCsInputDevice, ECS_INPUT_DEVICE_MAX>(JsonObject, StructProperty, InStruct, MemberName, nullptr); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsInputActionMapping
			if (StructProperty->Struct == FCsInputActionMapping::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsInputActionMapping>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsDrawDistance
			if (StructProperty->Struct == FCsDrawDistance::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsDrawDistance>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsFpvDrawDistance
			if (StructProperty->Struct == FCsFpvDrawDistance::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvDrawDistance>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// Weapon_FireMode
			{
				// FCsData_Weapon_FireMode_Firing
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Firing::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_Weapon_FireMode_Firing>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_Weapon_FireMode_Animation
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Animation::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_Weapon_FireMode_Animation>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_FpsWeapon_FireMode_Animation
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Animation::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_FpsWeapon_FireMode_Animation>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_Weapon_FireMode_Movement
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Movement::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_Weapon_FireMode_Movement>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_Weapon_FireMode_Aiming
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Aiming::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_Weapon_FireMode_Aiming>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_FpsWeapon_FireMode_Aiming
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Aiming::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_FpsWeapon_FireMode_Aiming>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_Weapon_FireMode_Scope
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Scope::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_Weapon_FireMode_Scope>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_Weapon_FireMode_FXs
				if (StructProperty->Struct == FCsData_Weapon_FireMode_FXs::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_Weapon_FireMode_FXs>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_FpsWeapon_FireMode_FXs
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_FXs::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_FpsWeapon_FireMode_FXs>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_Weapon_FireMode_Sounds
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Sounds::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_Weapon_FireMode_Sounds>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FCsData_FpsWeapon_FireMode_Sounds
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Sounds::StaticStruct())
				{ WriteToMemberStructPropertyFromJson<FCsData_FpsWeapon_FireMode_Sounds>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			}
			// FCsData_ProjectileBasePtr
			if (StructProperty->Struct == FCsData_ProjectileBasePtr::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsData_ProjectileBasePtr>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsData_ProjectileImpactPtr
			if (StructProperty->Struct == FCsData_ProjectileImpactPtr::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsData_ProjectileImpactPtr>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsRadius
			if (StructProperty->Struct == FCsRadius::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsRadius>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsProjectileMovementFunctionAxis
			if (StructProperty->Struct == FCsProjectileMovementFunctionAxis::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsProjectileMovementFunctionAxis>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsParametricFunction
			if (StructProperty->Struct == FCsParametricFunction::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsParametricFunction>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsParametricFunctionAxis
			if (StructProperty->Struct == FCsParametricFunctionAxis::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsParametricFunctionAxis>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsItemMemberDescription
			if (StructProperty->Struct == FCsItemMemberDescription::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsItemMemberDescription>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsInventoryLoadoutRecipe
			if (StructProperty->Struct == FCsInventoryLoadoutRecipe::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsInventoryLoadoutRecipe>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsInventoryLoadoutItem
			if (StructProperty->Struct == FCsInventoryLoadoutItem::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsInventoryLoadoutItem>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsRecipeIngredient
			if (StructProperty->Struct == FCsRecipeIngredient::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsRecipeIngredient>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsPlayerData_Inventory_Bag
			if (StructProperty->Struct == FCsPlayerData_Inventory_Bag::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsPlayerData_Inventory_Bag>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsPlayerData_Inventory_Slot
			if (StructProperty->Struct == FCsPlayerData_Inventory_Slot::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsPlayerData_Inventory_Slot>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsItemOnConsumeContentRule
			if (StructProperty->Struct == FCsItemOnConsumeContentRule::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsItemOnConsumeContentRule>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsTArrayPayload
			if (StructProperty->Struct == FCsTArrayPayload::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsTArrayPayload>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsPayload
			if (StructProperty->Struct == FCsPayload::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsPayload>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsData_ShortCode
			if (StructProperty->Struct == FCsData_ShortCode::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_FCsData_ShortCode(JsonObject, StructProperty, InStruct, MemberName); continue; }

			// EnumStruct
			{
				// FECsAssetType
				if (StructProperty->Struct == FECsAssetType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsAssetType, EMCsAssetType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsLoadAssetsType
				if (StructProperty->Struct == FECsLoadAssetsType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsLoadAssetsType, EMCsLoadAssetsType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsInputAction
				if (StructProperty->Struct == FECsInputAction::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsInputAction, EMCsInputAction>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsGameEvent
				if (StructProperty->Struct == FECsGameEvent::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsGameEvent, EMCsGameEvent>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsSurfaceType
				if (StructProperty->Struct == FECsSurfaceType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsSurfaceType, EMCsSurfaceType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsWeaponGrip
				if (StructProperty->Struct == FECsWeaponGrip::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsWeaponGrip, EMCsWeaponGrip>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsDamageType
				if (StructProperty->Struct == FECsDamageType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsDamageType, EMCsDamageType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsInteractiveType
				if (StructProperty->Struct == FECsInteractiveType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsInteractiveType, EMCsInteractiveType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsProjectile
				if (StructProperty->Struct == FECsProjectile::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsProjectile, EMCsProjectile>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsSoundType
				if (StructProperty->Struct == FECsSoundType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsSoundType, EMCsSoundType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				// FECsItemType
				if (StructProperty->Struct == FECsItemType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsItemType, EMCsItemType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftObjectPtr
			if (USoftObjectProperty* InnerSoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerSoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UStaticMesh>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// USkeletalMesh
				if (InnerSoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<USkeletalMesh>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstance
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UMaterialInstance>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstanceConstant
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimSequence
				if (InnerSoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UAnimSequence>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimMontage
				if (InnerSoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UAnimMontage>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UBlueprint
				if (InnerSoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UBlueprint>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FGuid
				if (InnerStructProperty->Struct == TBaseStructure<FGuid>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_BaseStructure<FGuid>(JsonObject, ArrayProperty, InStruct, MemberName, &FGuid::Parse); continue; }
				// FVector
				if (InnerStructProperty->Struct == TBaseStructure<FVector>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FVector>(JsonObject, ArrayProperty, InStruct, MemberName, &FVector::InitFromString); continue; }
				// FRotator
				if (InnerStructProperty->Struct == TBaseStructure<FRotator>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FRotator>(JsonObject, ArrayProperty, InStruct, MemberName, &FRotator::InitFromString); continue; }
				// FColor
				if (InnerStructProperty->Struct == TBaseStructure<FColor>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FColor>(JsonObject, ArrayProperty, InStruct, MemberName, &FColor::InitFromString); continue; }
				// FTransform
				if (InnerStructProperty->Struct == TBaseStructure<FTransform>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Transform(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsAnimMontage>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsFxElement
				if (InnerStructProperty->Struct == FCsFxElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFxElement>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsFpvFxElement
				if (InnerStructProperty->Struct == FCsFpvFxElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpvFxElement>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsSoundElement>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsFpvSoundElement
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpvSoundElement>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsAnimSequence
				if (InnerStructProperty->Struct == FCsAnimSequence::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsAnimSequence>(JsonObject, ArrayProperty, InStruct, MemberName, nullptr); continue; }
				// FCsFpvAnimSequence
				if (InnerStructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpvAnimSequence>(JsonObject, ArrayProperty, InStruct, MemberName, nullptr); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsAnimMontage>(JsonObject, ArrayProperty, InStruct, MemberName, nullptr); continue; }
				// FCsFpvAnimMontage
				if (InnerStructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpvAnimMontage>(JsonObject, ArrayProperty, InStruct, MemberName, nullptr); continue; }
				// FCsInputActionMapping
				if (InnerStructProperty->Struct == FCsInputActionMapping::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsInputActionMapping>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsInventoryLoadoutRecipe
				if (InnerStructProperty->Struct == FCsInventoryLoadoutRecipe::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsInventoryLoadoutRecipe>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsInventoryLoadoutItem
				if (InnerStructProperty->Struct == FCsInventoryLoadoutItem::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsInventoryLoadoutItem>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsRecipeIngredient
				if (InnerStructProperty->Struct == FCsRecipeIngredient::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsRecipeIngredient>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsPlayerData_Inventory_Bag
				if (InnerStructProperty->Struct == FCsPlayerData_Inventory_Bag::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsPlayerData_Inventory_Bag>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsPlayerData_Inventory_Slot
				if (InnerStructProperty->Struct == FCsPlayerData_Inventory_Slot::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsPlayerData_Inventory_Slot>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsPayload
				if (InnerStructProperty->Struct == FCsPayload::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsPayload>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FName
			if (UNameProperty* NameProperty = Cast<UNameProperty>(ArrayProperty->Inner))
			{ WriteToMemberArrayStructPropertyFromJson_Name(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
			// uint64
			if (UUInt64Property* IntProperty = Cast<UUInt64Property>(ArrayProperty->Inner))
			{ WriteToMemberArrayStructPropertyFromJson_uint64(JsonObject, ArrayProperty, InStruct, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// Map
		if (UMapProperty* MapProperty = Cast<UMapProperty>(*It))
		{
			UStructProperty* KeyStructProp = Cast<UStructProperty>(MapProperty->KeyProp);
			UFloatProperty* ValueFloatProp = Cast<UFloatProperty>(MapProperty->ValueProp);

			if (KeyStructProp && ValueFloatProp)
			{
				// FECsSenseActorType, float
				if (KeyStructProp->Struct == FECsSenseActorType::StaticStruct())
				{ WriteToMemberMapStructPropertyFromJson_EnumStructKey_NumericValue<FECsSenseActorType, float>(JsonObject, MapProperty, InStruct, MemberName, Internal); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// bool
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
		{
			if (bool* Member = BoolProperty->ContainerPtrToValuePtr<bool>(InStruct))
			{ *Member = JsonObject->GetBoolField(MemberName); continue; }
			continue;
		}
		// Enum Class
		if (UEnumProperty* EnumProperty = Cast<UEnumProperty>(*It))
		{
			// ECsEasingType
			if (EnumProperty->GetEnum()->CppType.Contains(NCsCommonLoadCached::Str::CsEasingType))
			{ WriteToMemberEnumPropertyFromJson<ECsEasingType, EMCsEasingType>(JsonObject, EnumProperty, InStruct, MemberName); continue; }
			// ECsProjectileMovementFunctionType
			if (EnumProperty->GetEnum()->CppType.Contains(NCsCommonLoadCached::Str::CsProjectileMovementFunctionType))
			{ WriteToMemberEnumPropertyFromJson<ECsProjectileMovementFunctionType, EMCsProjectileMovementFunctionType>(JsonObject, EnumProperty, InStruct, MemberName); continue; }
			continue;
		}
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			// enum
			if (ByteProperty->IsEnum())
			{
				// ECollisionEnabled
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionEnabled))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECollisionEnabled::Type, EMCollisionEnabled>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionChannel))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECollisionChannel, EMCsCollisionChannel>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionResponse))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECollisionResponse, EMCollisionResponse>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::HorizTextAligment))
				{ WriteToMemberEnumAsBytePropertyFromJson<EHorizTextAligment, EMHorizTextAligment>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::VerticalTextAligment))
				{ WriteToMemberEnumAsBytePropertyFromJson<EHorizTextAligment, EMHorizTextAligment>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECsLoadFlags_Editor
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsLoadFlags_Editor))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsLoadFlags_Editor::Type, EMCsLoadFlags_Editor>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsFxPriority))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsFxPriority::Type, EMCsFxPriority>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsSoundPriority))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsSoundPriority::Type, EMCsSoundPriority>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECsParametricFunctionType
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsParametricFunctionType))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsParametricFunctionType::Type, EMCsParametricFunctionType>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECsItemMemberValueType
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsProjectileMovementFunctionType))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsItemMemberValueType::Type, EMCsItemMemberValueType>(JsonObject, ByteProperty, InStruct, MemberName); continue; }
				// ECsItemOnConsumeContentAction
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsItemOnConsumeContentAction))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsItemOnConsumeContentAction::Type, EMCsItemOnConsumeContentAction>(JsonObject, ByteProperty, InStruct, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// uint8
			else
			{
				if (uint8* Member = ByteProperty->ContainerPtrToValuePtr<uint8>(InStruct))
				{ *Member = (uint8)JsonObject->GetIntegerField(MemberName); continue; }
				continue;
			}
			continue;
		}
		if (UUInt16Property* IntProperty = Cast<UUInt16Property>(*It))
		{
			if (uint16* Member = IntProperty->ContainerPtrToValuePtr<uint16>(InStruct))
			{ *Member = (uint16)JsonObject->GetIntegerField(MemberName); continue; }
			continue;
		}
		// int32
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
		{
			if (int32* Member = IntProperty->ContainerPtrToValuePtr<int32>(InStruct))
			{
				FString String;

				// BitmaskEnum
				if (JsonObject->TryGetStringField(MemberName, String))
				{
					if (String.Len() > 0)
					{
						bool IsInt = false;

						for (int32 I = 0; I < 10; ++I)
						{
							if (String[0] == FString::FromInt(I)[0])
								IsInt |= true;
							if (IsInt)
								break;
						}

						if (IsInt)
						{
							*Member = JsonObject->GetIntegerField(MemberName); continue;
						}
						else
						{
							*Member = EMCsLoadFlags::Get().StringToMask(JsonObject->GetStringField(MemberName)); continue;
						}
					}
					else
					{
						*Member = JsonObject->GetIntegerField(MemberName); continue;
					}
				}
				else
				{
					*Member = JsonObject->GetIntegerField(MemberName); continue;
				}
			}
			continue;
		}
		// uint64
		if (UUInt64Property* IntProperty = Cast<UUInt64Property>(*It))
		{
			if (uint64* Member = IntProperty->ContainerPtrToValuePtr<uint64>(InStruct))
			{ *Member = FCString::Strtoui64(*(JsonObject->GetStringField(MemberName)), NULL, 10); continue; }
		}
		// float
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
		{
			if (float* Member = FloatProperty->ContainerPtrToValuePtr<float>(InStruct))
			{ *Member = (float)JsonObject->GetNumberField(MemberName); continue; }
			continue;
		}
		// FString
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
		{
			if (FString* Member = StrProperty->ContainerPtrToValuePtr<FString>(InStruct))
			{ *Member = JsonObject->GetStringField(MemberName); continue; }
			continue;
		}
		// FName
		if (UNameProperty* NameProperty = Cast<UNameProperty>(*It))
		{
			if (NameProperty->ArrayDim == CS_SINGLETON)
			{
				if (FName* Member = NameProperty->ContainerPtrToValuePtr<FName>(InStruct))
				{ *Member = FName(*JsonObject->GetStringField(MemberName)); continue; }
				continue;
			}

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
					continue;
			}
		}
	}
}

void UCsCommon_Load::ReadObjectFromJson(TSharedPtr<FJsonObject> &JsonParsed, void* InObject, UClass* const &InClass, const TArray<FCsCategoryMemberAssociation> &CategoryMemberAssociations, TCsReadObjectFromJson_Internal Internal /*=nullptr*/)
{
	const FString NoCategory = NCsCached::Str::Empty;
	FString Category		 = NoCategory;
	int32 CategoryIndex		 = 0;

	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		if (CategoryIndex >= CategoryMemberAssociations.Num())
			break;

		const int32 Count = CategoryMemberAssociations[CategoryIndex].Members.Num();
		const int32 Index = CategoryMemberAssociations[CategoryIndex].Members.Find(MemberName);

		if (Index == INDEX_NONE)
			continue;

		Category = CategoryMemberAssociations[CategoryIndex].Category;

		if (Index == Count - 1)
			CategoryIndex++;

		TSharedPtr<FJsonObject> JsonObject = JsonParsed->Values.Find(Category)->Get()->AsObject();
		
		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InObject, InClass))
					continue;
			}
			continue;
		}
		// TSoftObjectPtr
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(*It))
		{
			// UStaticMesh
			if (SoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UStaticMesh>(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }
			// USkeletalMesh
			if (SoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<USkeletalMesh>(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }
			// UMaterialInstance
			if (SoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UMaterialInstance>(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }
			// UMaterialInstanceConstant
			if (SoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }
			// UPhysicalMaterial
			if (SoftObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UPhysicalMaterial>(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }
			// UPhysicsAsset
			if (SoftObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UPhysicsAsset>(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }
			// USoundCue
			if (SoftObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<USoundCue>(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }
			// UParticleSystem
			if (SoftObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UParticleSystem>(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }
			// UAnimSequence
			if (SoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UAnimSequence>(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }
			// UAnimMontage
			if (SoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UAnimMontage>(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }
			// UBlendSpace
			if (SoftObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UBlendSpace>(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }
			// UAnimBlueprint
			if (SoftObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ WriteToSoftObjectPropertyFromJson_AnimBlueprint(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }
			// UBlueprint
			if (SoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{
				if (SoftObjectProperty->ArrayDim == CS_SINGLETON)
				{ WriteToSoftObjectPropertyFromJson_Blueprint(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }

				if (ReadObjectFromJson_Internal_Helper(Internal, Property, JsonObject, InObject, InClass)) { continue; }
				continue;
			}
			// UCurveVector
			if (SoftObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UCurveVector>(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }
			// UCurveFloat
			if (SoftObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ WriteToSoftObjectPropertyFromJson<UCurveFloat>(JsonObject, SoftObjectProperty, InObject, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InObject, InClass))
					continue;
			}
			continue;
		}
		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FGuid
			if (StructProperty->Struct == TBaseStructure<FGuid>::Get())
			{ WriteToMemberStructPropertyFromJson_BaseStructure<FGuid>(JsonObject, StructProperty, InObject, MemberName, &FGuid::Parse); continue; }
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FVector>(JsonObject, StructProperty, InObject, MemberName, &FVector::InitFromString); continue; }
			// FRotator
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FRotator>(JsonObject, StructProperty, InObject, MemberName, &FRotator::InitFromString); continue; }
			// FColor
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FColor>(JsonObject, StructProperty, InObject, MemberName, &FColor::InitFromString); continue; }
			// FTransform
			if (StructProperty->Struct == TBaseStructure<FTransform>::Get())
			{ WriteToMemberStructPropertyFromJson_Transform(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FInt32Interval
			if (StructProperty->Struct == TBaseStructure<FInt32Interval>::Get())
			{ WriteToMemberStructPropertyFromJson_BaseStructure<FInt32Interval>(JsonObject, StructProperty, InObject, MemberName, &UCsCommon_Load::InitFromString_FInt32Interval); continue; }
			// FFloatInterval
			if (StructProperty->Struct == TBaseStructure<FFloatInterval>::Get())
			{ WriteToMemberStructPropertyFromJson_BaseStructure<FFloatInterval>(JsonObject, StructProperty, InObject, MemberName, &UCsCommon_Load::InitFromString_FFloatInterval); continue; }
			// FCsUint8Point
			if (StructProperty->Struct == FCsUint8Point::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsUint8Point>(JsonObject, StructProperty, InObject, MemberName, &FCsUint8Point::InitFromString); continue; }
			// FCsUint8MatrixDimension
			if (StructProperty->Struct == FCsUint8MatrixDimension::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsUint8MatrixDimension>(JsonObject, StructProperty, InObject, MemberName, &FCsUint8MatrixDimension::InitFromString); continue; }
			// FCsUint8MatrixCoordinate
			if (StructProperty->Struct == FCsUint8MatrixCoordinate::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsUint8MatrixCoordinate>(JsonObject, StructProperty, InObject, MemberName, &FCsUint8MatrixCoordinate::InitFromString); continue; }
			// FCsVectorFlag
			if (StructProperty->Struct == FCsVectorFlag::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsVectorFlag>(JsonObject, StructProperty, InObject, MemberName, &FCsVectorFlag::InitFromString); continue; }
			// FCsRotatorFlag
			if (StructProperty->Struct == FCsRotatorFlag::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_Primitive<FCsRotatorFlag>(JsonObject, StructProperty, InObject, MemberName, &FCsRotatorFlag::InitFromString); continue; }
			// FCsOptionalVectorInterval
			if (StructProperty->Struct == FCsOptionalVectorInterval::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsOptionalVectorInterval>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsOptionalRotatorInterval
			if (StructProperty->Struct == FCsOptionalRotatorInterval::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsOptionalRotatorInterval>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsStaticMesh>(JsonObject, StructProperty, InObject, MemberName, nullptr); continue; }

				if (ReadObjectFromJson_Internal_Helper(Internal, Property, JsonObject, InObject, InClass)) { continue; }
				continue;
			}
			// FCsFpvStaticMesh
			if (StructProperty->Struct == FCsFpvStaticMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvStaticMesh>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsTArrayStaticMesh
			if (StructProperty->Struct == FCsTArrayStaticMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsTArrayStaticMesh>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsSkeletalMesh>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsFpsSkeletalMesh
			if (StructProperty->Struct == FCsFpsSkeletalMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsSkeletalMesh>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsTArraySkeletalMesh
			if (StructProperty->Struct == FCsTArraySkeletalMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsTArraySkeletalMesh>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsMaterialInstance>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsMaterialInstanceConstant
			if (StructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsMaterialInstanceConstant>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsTArrayMaterialInstanceConstant::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsTArrayMaterialInstanceConstant>(JsonObject, StructProperty, InObject, MemberName); continue; }
				if (StructProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ WriteToMemberFixedArrayStructPropertyFromJson_EnumSize<FCsTArrayMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(JsonObject, StructProperty, InObject, MemberName, &ECsInteractiveState::ToString, nullptr); continue; }

				if (ReadObjectFromJson_Internal_Helper(Internal, Property, JsonObject, InObject, InClass)) { continue; }
				continue;
			}
			// FCsFpsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsFpsTArrayMaterialInstanceConstant::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsTArrayMaterialInstanceConstant>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsInteractiveMaterials
			if (StructProperty->Struct == FCsInteractiveMaterials::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsInteractiveMaterials>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsPhysicalMaterial
			if (StructProperty->Struct == FCsPhysicalMaterial::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsPhysicalMaterial>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsPhysicsAsset>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsPhysicsPreset
			if (StructProperty->Struct == FCsPhysicsPreset::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsPhysicsPreset>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsPhysicsImpulse
			if (StructProperty->Struct == FCsPhysicsImpulse::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsPhysicsImpulse>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsCurveFloat
			if (StructProperty->Struct == FCsCurveFloat::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsCurveFloat>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsCurveVector>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsSoundElement>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (ReadObjectFromJson_Internal_Helper(Internal, Property, JsonObject, InObject, InClass)) { continue; }
				continue;
			}
			// FCsFpvSoundElement
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpvSoundElement>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (ReadObjectFromJson_Internal_Helper(Internal, Property, JsonObject, InObject, InClass)) { continue; }
				continue;
			}
			// FCsParticleSystem
			if (StructProperty->Struct == FCsParticleSystem::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsParticleSystem>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFxElement>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (ReadObjectFromJson_Internal_Helper(Internal, Property, JsonObject, InObject, InClass)) { continue; }
				continue;
			}
			// FCsFpvFxElement
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpvFxElement>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (ReadObjectFromJson_Internal_Helper(Internal, Property, JsonObject, InObject, InClass)) { continue; }
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsAnimSequence>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsFpvAnimSequence
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvAnimSequence>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsAnimMontage>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (ReadObjectFromJson_Internal_Helper(Internal, Property, JsonObject, InObject, InClass)) { continue; }
				continue;
			}
			// FCsFpvAnimMontage
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpvAnimMontage>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (ReadObjectFromJson_Internal_Helper(Internal, Property, JsonObject, InObject, InClass)) { continue; }
				continue;
			}
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsTArrayAnimMontage>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (ReadObjectFromJson_Internal_Helper(Internal, Property, JsonObject, InObject, InClass)) { continue; }
				continue;
			}
			// FCsBlendSpace1D
			if (StructProperty->Struct == FCsBlendSpace1D::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsBlendSpace1D>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsFpvBlendSpace1D
			if (StructProperty->Struct == FCsFpvBlendSpace1D::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvBlendSpace1D>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsBlendSpace>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsFpvBlendSpace
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvBlendSpace>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsAimOffset
			if (StructProperty->Struct == FCsAimOffset::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsAimOffset>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsFpvAimOffset
			if (StructProperty->Struct == FCsFpvAimOffset::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvAimOffset>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsAnimBlueprint>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsFpvAnimBlueprint
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvAnimBlueprint>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCollisionResponseContainer
			if (StructProperty->Struct == FCollisionResponseContainer::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCollisionResponseContainer>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsCollisionPreset
			if (StructProperty->Struct == FCsCollisionPreset::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsCollisionPreset>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (ReadObjectFromJson_Internal_Helper(Internal, Property, JsonObject, InObject, InClass)) { continue; }
				continue;
			}
			// FCsHeadCollision
			if (StructProperty->Struct == FCsHeadCollision::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsHeadCollision>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsDrawDistance
			if (StructProperty->Struct == FCsDrawDistance::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsDrawDistance>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsFpvDrawDistance
			if (StructProperty->Struct == FCsFpvDrawDistance::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpvDrawDistance>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsWidgetComponentInfo
			if (StructProperty->Struct == FCsWidgetComponentInfo::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsWidgetComponentInfo>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsWidgetActorInfo
			if (StructProperty->Struct == FCsWidgetActorInfo::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsWidgetActorInfo>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsData_ProjectileImpactPtr
			if (StructProperty->Struct == FCsData_ProjectileImpactPtr::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsData_ProjectileImpactPtr>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsRadius
			if (StructProperty->Struct == FCsRadius::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsRadius>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsProjectileMovementFunction
			if (StructProperty->Struct == FCsProjectileMovementFunction::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsProjectileMovementFunction>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsParametricFunction
			if (StructProperty->Struct == FCsParametricFunction::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsParametricFunction>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsParametricFunctionAxis
			if (StructProperty->Struct == FCsParametricFunctionAxis::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsParametricFunctionAxis>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsDamageFalloff
			if (StructProperty->Struct == FCsDamageFalloff::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsDamageFalloff>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsDamageRadial
			if (StructProperty->Struct == FCsDamageRadial::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsDamageRadial>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsInventoryLoadout
			if (StructProperty->Struct == FCsInventoryLoadout::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsInventoryLoadout>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsTArrayPayload
			if (StructProperty->Struct == FCsTArrayPayload::StaticStruct())
			{ 
				if (ReadObjectFromJson_Internal_Helper(Internal, Property, JsonObject, InObject, InClass)) { continue; }
				continue;
			}
			// FCsSenseData
			if (StructProperty->Struct == FCsSenseData::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsSenseData>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsData_ShortCode
			if (StructProperty->Struct == FCsData_ShortCode::StaticStruct())
			{ WriteToMemberStructPropertyFromJson_FCsData_ShortCode(JsonObject, StructProperty, InObject, MemberName); continue; }

			// EnumStruct
			{
				// FECsAssetType
				if (StructProperty->Struct == FECsAssetType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsAssetType, EMCsAssetType>(JsonObject, StructProperty, InObject, MemberName); continue; }
				// FECsLoadAssetsType
				if (StructProperty->Struct == FECsLoadAssetsType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsLoadAssetsType, EMCsLoadAssetsType>(JsonObject, StructProperty, InObject, MemberName); continue; }
				// FECsInputAction
				if (StructProperty->Struct == FECsInputAction::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsInputAction, EMCsInputAction>(JsonObject, StructProperty, InObject, MemberName); continue; }
				// FECsGameEvent
				if (StructProperty->Struct == FECsGameEvent::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsGameEvent, EMCsGameEvent>(JsonObject, StructProperty, InObject, MemberName); continue; }
				// FECsSurfaceType
				if (StructProperty->Struct == FECsSurfaceType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsSurfaceType, EMCsSurfaceType>(JsonObject, StructProperty, InObject, MemberName); continue; }
				// FECsWeaponGrip
				if (StructProperty->Struct == FECsWeaponGrip::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsWeaponGrip, EMCsWeaponGrip>(JsonObject, StructProperty, InObject, MemberName); continue; }
				// FECsDamageType
				if (StructProperty->Struct == FECsDamageType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsDamageType, EMCsDamageType>(JsonObject, StructProperty, InObject, MemberName); continue; }
				// FECsInteractiveType
				if (StructProperty->Struct == FECsInteractiveType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsInteractiveType, EMCsInteractiveType>(JsonObject, StructProperty, InObject, MemberName); continue; }
				// FECsProjectile
				if (StructProperty->Struct == FECsProjectile::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsProjectile, EMCsProjectile>(JsonObject, StructProperty, InObject, MemberName); continue; }
				// FECsSoundType
				if (StructProperty->Struct == FECsSoundType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsSoundType, EMCsSoundType>(JsonObject, StructProperty, InObject, MemberName); continue; }
				// FECsItemType
				if (StructProperty->Struct == FECsItemType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsItemType, EMCsItemType>(JsonObject, StructProperty, InObject, MemberName); continue; }
				// FECsRecipeType
				if (StructProperty->Struct == FECsRecipeType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsRecipeType, EMCsRecipeType>(JsonObject, StructProperty, InObject, MemberName); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InObject, InClass))
					continue;
			}
			continue;
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftObjectPtr
			if (USoftObjectProperty* InnerSoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
			{
				// UMaterialInstance
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UMaterialInstance>(JsonObject, ArrayProperty, InObject, MemberName); continue; }
				// UMaterialInstanceConstant
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, ArrayProperty, InObject, MemberName); continue; }
				// UAnimSequence
				if (InnerSoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UAnimSequence>(JsonObject, ArrayProperty, InObject, MemberName); continue; }
				// UAnimMontage
				if (InnerSoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UAnimMontage>(JsonObject, ArrayProperty, InObject, MemberName); continue; }
				// UBlueprint
				if (InnerSoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteToArraySoftObjectPropertyFromJson<UBlueprint>(JsonObject, ArrayProperty, InObject, MemberName); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InObject, InClass))
						continue;
				}
				continue;
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FGuid
				if (InnerStructProperty->Struct == TBaseStructure<FGuid>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_BaseStructure<FGuid>(JsonObject, ArrayProperty, InObject, MemberName, &FGuid::Parse); continue; }
				// FVector
				if (InnerStructProperty->Struct == TBaseStructure<FVector>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FVector>(JsonObject, ArrayProperty, InObject, MemberName, &FVector::InitFromString); continue; }
				// FRotator
				if (InnerStructProperty->Struct == TBaseStructure<FRotator>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FRotator>(JsonObject, ArrayProperty, InObject, MemberName, &FRotator::InitFromString); continue; }
				// FColor
				if (InnerStructProperty->Struct == TBaseStructure<FColor>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FColor>(JsonObject, ArrayProperty, InObject, MemberName, &FColor::InitFromString); continue; }
				// FTransform
				if (InnerStructProperty->Struct == TBaseStructure<FTransform>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Transform(JsonObject, ArrayProperty, InObject, MemberName); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsAnimMontage>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
				// FCsFxElement
				if (InnerStructProperty->Struct == FCsFxElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFxElement>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
				// FCsFpvFxElement
				if (InnerStructProperty->Struct == FCsFpvFxElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpvFxElement>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsSoundElement>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
				// FCsFpvSoundElement
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpvSoundElement>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
				// FCsAnimSequence
				if (InnerStructProperty->Struct == FCsAnimSequence::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsAnimSequence>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
				// FCsFpvAnimSequence
				if (InnerStructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpvAnimSequence>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsAnimMontage>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
				// FCsFpvAnimMontage
				if (InnerStructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpvAnimMontage>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
				// FCsDataMappingEntry
				if (InnerStructProperty->Struct == FCsDataMappingEntry::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsDataMappingEntry>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
				// FCsItemMemberDescription
				if (InnerStructProperty->Struct == FCsItemMemberDescription::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsItemMemberDescription>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
				// FCsRecipeIngredient
				if (InnerStructProperty->Struct == FCsRecipeIngredient::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsRecipeIngredient>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
				// FCsItemOnConsumeContentRule
				if (InnerStructProperty->Struct == FCsItemOnConsumeContentRule::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsItemOnConsumeContentRule>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InObject, InClass))
						continue;
				}
				continue;
			}
			// FName
			if (UNameProperty* NameProperty = Cast<UNameProperty>(ArrayProperty->Inner))
			{ WriteToMemberArrayStructPropertyFromJson_Name(JsonObject, ArrayProperty, InObject, MemberName); continue; }
			// uint64
			if (UUInt64Property* IntProperty = Cast<UUInt64Property>(ArrayProperty->Inner))
			{ WriteToMemberArrayStructPropertyFromJson_uint64(JsonObject, ArrayProperty, InObject, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InObject, InClass))
					continue;
			}
			continue;
		}
		// Map
		if (UMapProperty* MapProperty = Cast<UMapProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InObject, InClass))
					continue;
			}
			continue;
		}
		// bool
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
		{
			if (bool* Member = BoolProperty->ContainerPtrToValuePtr<bool>(InObject))
			{ *Member = JsonObject->GetBoolField(MemberName); continue; }
			continue;
		}
		// Enum Class
		if (UEnumProperty* EnumProperty = Cast<UEnumProperty>(*It))
		{
			// ECsEasingType
			if (EnumProperty->GetEnum()->CppType.Contains(NCsCommonLoadCached::Str::CsEasingType))
			{ WriteToMemberEnumPropertyFromJson<ECsEasingType, EMCsEasingType>(JsonObject, EnumProperty, InObject, MemberName); continue; }
			continue;
		}
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			// enum
			if (ByteProperty->IsEnum())
			{
				// ECollisionEnabled
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionEnabled))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECollisionEnabled::Type, EMCollisionEnabled>(JsonObject, ByteProperty, InObject, MemberName); continue; }
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionChannel))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECollisionChannel, EMCsCollisionChannel>(JsonObject, ByteProperty, InObject, MemberName); continue; }
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionResponse))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECollisionResponse, EMCollisionResponse>(JsonObject, ByteProperty, InObject, MemberName); continue; }
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::HorizTextAligment))
				{ WriteToMemberEnumAsBytePropertyFromJson<EHorizTextAligment, EMHorizTextAligment>(JsonObject, ByteProperty, InObject, MemberName); continue; }
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::VerticalTextAligment))
				{ WriteToMemberEnumAsBytePropertyFromJson<EVerticalTextAligment, EMVerticalTextAligment>(JsonObject, ByteProperty, InObject, MemberName); continue; }
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsFxPriority))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsFxPriority::Type, EMCsFxPriority>(JsonObject, ByteProperty, InObject, MemberName); continue; }
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsSoundPriority))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsSoundPriority::Type, EMCsSoundPriority>(JsonObject, ByteProperty, InObject, MemberName); continue; }
				// ECsParametricFunctionType
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsParametricFunctionType))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsParametricFunctionType::Type, EMCsParametricFunctionType>(JsonObject, ByteProperty, InObject, MemberName); continue; }
				// ECsItemMemberValueType
				if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsItemMemberValueType))
				{ WriteToMemberEnumAsBytePropertyFromJson<ECsItemMemberValueType::Type, EMCsItemMemberValueType>(JsonObject, ByteProperty, InObject, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InObject, InClass))
						continue;
				}
				continue;
			}
			// uint8
			{
				if (uint8* Member = ByteProperty->ContainerPtrToValuePtr<uint8>(InObject))
				{ *Member = (uint8)JsonObject->GetIntegerField(MemberName); continue; }
			}
		}
		// int32
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
		{
			if (int32* Member = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
			{
				FString String;

				// BitmaskEnum
				if (JsonObject->TryGetStringField(MemberName, String))
				{
					if (String.Len() > 0)
					{
						bool IsInt = false;

						for (int32 I = 0; I < 10; ++I)
						{
							if (String[0] == FString::FromInt(I)[0])
								IsInt |= true;
							if (IsInt)
								break;
						}

						if (IsInt)
						{
							*Member = JsonObject->GetIntegerField(MemberName); continue;
						}
						else
						{
							*Member = EMCsLoadFlags::Get().StringToMask(JsonObject->GetStringField(MemberName)); continue;
						}
					}
					else
					{
						*Member = JsonObject->GetIntegerField(MemberName); continue;
					}
				}
				else
				{
					*Member = JsonObject->GetIntegerField(MemberName); continue;
				}
			}
			continue;
		}
		// uint64
		if (UUInt64Property* IntProperty = Cast<UUInt64Property>(*It))
		{
			if (uint64* Member = IntProperty->ContainerPtrToValuePtr<uint64>(InObject))
			{ *Member = FCString::Strtoui64(*(JsonObject->GetStringField(MemberName)), NULL, 10); continue; }
		}
		// float
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
		{
			if (float* Member = FloatProperty->ContainerPtrToValuePtr<float>(InObject))
			{ *Member = (float)JsonObject->GetNumberField(MemberName); continue; }
		}
		// FString
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
		{
			if (FString* Member = StrProperty->ContainerPtrToValuePtr<FString>(InObject))
			{ *Member = JsonObject->GetStringField(MemberName); continue; }
		}
		// FName
		if (UNameProperty* NameProperty = Cast<UNameProperty>(*It))
		{
			if (FName* Member = NameProperty->ContainerPtrToValuePtr<FName>(InObject))
			{ *Member = FName(*JsonObject->GetStringField(MemberName)); continue; }
		}
	}
}

#pragma endregion Read

#pragma endregion Json

// Loading
#pragma region

float UCsCommon_Load::BytesToKilobytes(const int32 &Bytes)
{
	return Bytes * FMath::Pow(10, -3);
}

float UCsCommon_Load::BytesToMegabytes(const int32 &Bytes)
{
	return Bytes * FMath::Pow(10, -6);
}

int32 UCsCommon_Load::KilobytesToBytes(const float &Kilobytes)
{
	return Kilobytes * FMath::Pow(10, 3);
}

	// Asset References
#pragma region

		// FCsStringAssetReference
#pragma region

void UCsCommon_Load::GetAssetReferenceFromSoftObjectProperty_AnimMontage(USoftObjectProperty* &SoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = SoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TSoftObjectPtr<UAnimMontage>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UAnimMontage>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToSoftObjectPath();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
			return;

		OutAssetReferences.AddDefaulted();

		const int32 Size = OutAssetReferences.Num();

		FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
		Reference.Reference = AssetName;
		Reference.Reference_Internal = AssetRef;
#if WITH_EDITOR
		if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
		{
			UAnimMontage* Asset = Cast<UAnimMontage>(Member->LoadSynchronous());

			TArray<UAnimationAsset*> AnimationAssets;

			Asset->GetAllAnimationSequencesReferred(AnimationAssets);

			const int32 Count = AnimationAssets.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				if (UAnimSequence* Anim = Cast<UAnimSequence>(AnimationAssets[I]))
				{
					Reference.Size.Bytes += Anim->GetApproxCompressedSize();
				}
			}

			Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
			Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromSoftObjectProperty_AnimMontage(USoftObjectProperty* &SoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = SoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TSoftObjectPtr<UAnimMontage>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UAnimMontage>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToSoftObjectPath();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
			return;

		OutAssetReferences.AddDefaulted();

		const int32 Size = OutAssetReferences.Num();

		FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
		Reference.Reference				   = AssetName;
		Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
		if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
		{
			UAnimMontage* Asset = Cast<UAnimMontage>(Member->LoadSynchronous());

			TArray<UAnimationAsset*> AnimationAssets;

			Asset->GetAllAnimationSequencesReferred(AnimationAssets);

			const int32 Count = AnimationAssets.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				if (UAnimSequence* Anim = Cast<UAnimSequence>(AnimationAssets[I]))
				{
					Reference.Size.Bytes += Anim->GetApproxCompressedSize();
				}
			}

			Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Kilobytes);
			Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromSoftObjectProperty_AnimSequence(USoftObjectProperty* &SoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = SoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TSoftObjectPtr<UAnimSequence>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UAnimSequence>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToSoftObjectPath();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
			return;

		OutAssetReferences.AddDefaulted();

		const int32 Size = OutAssetReferences.Num();

		FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
		Reference.Reference = AssetName;
		Reference.Reference_Internal = AssetRef;
#if WITH_EDITOR
		if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
		{
			UAnimSequence* Asset = Cast<UAnimSequence>(Member->LoadSynchronous());

			Reference.Size.Bytes	 = Asset->GetApproxCompressedSize();
			Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
			Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromSoftObjectProperty_AnimSequence(USoftObjectProperty* &SoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = SoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TSoftObjectPtr<UAnimSequence>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UAnimSequence>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToSoftObjectPath();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
			return;

		OutAssetReferences.AddDefaulted();

		const int32 Size = OutAssetReferences.Num();

		FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
		Reference.Reference				   = AssetName;
		Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
		if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
		{
			UAnimSequence* Asset = Cast<UAnimSequence>(Member->LoadSynchronous());

			Reference.Size.Bytes	 = Asset->GetApproxCompressedSize();
			Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
			Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromSoftObjectProperty_MaterialInstanceConstant(USoftObjectProperty* &SoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = SoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TSoftObjectPtr<UMaterialInstanceConstant>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UMaterialInstanceConstant>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToSoftObjectPath();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
			return;

		OutAssetReferences.AddDefaulted();

		const int32 Size = OutAssetReferences.Num();

		FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
		Reference.Reference				   = AssetName;
		Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
		if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
		{
			UMaterialInstanceConstant* Asset = Cast<UMaterialInstanceConstant>(Member->LoadSynchronous());

			const int32 Count = Asset->TextureParameterValues.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				UTexture* Texture = Asset->TextureParameterValues[I].ParameterValue;

				if (!Texture)
					continue;

				Reference.Size.Bytes += Texture->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
			}

			Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
			Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromSoftObjectProperty_MaterialInstanceConstant(USoftObjectProperty* &SoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = SoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TSoftObjectPtr<UMaterialInstanceConstant>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UMaterialInstanceConstant>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToSoftObjectPath();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
			return;

		OutAssetReferences.AddDefaulted();

		const int32 Size = OutAssetReferences.Num();

		FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
		Reference.Reference				   = AssetName;
		Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
		if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
		{
			UMaterialInstanceConstant* Asset = Cast<UMaterialInstanceConstant>(Member->LoadSynchronous());

			const int32 Count = Asset->TextureParameterValues.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				UTexture* Texture = Asset->TextureParameterValues[I].ParameterValue;

				if (!Texture)
					continue;

				Reference.Size.Bytes += Texture->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
			}

			Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
			Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromSoftObjectProperty_Blueprint(USoftObjectProperty* &SoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = SoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TSoftObjectPtr<UBlueprint>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UBlueprint>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToSoftObjectPath();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
			return;

		OutAssetReferences.AddDefaulted();

		const int32 Size = OutAssetReferences.Num();

		// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TSoftObjectPtr for UAnimBlueprint / UWidgetBlueprint does NOT have _C
		FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
										  // AssetName.EndsWith(TEXT("_C")) ? AssetName : AssetName + TEXT("_C");
		Reference.Reference				   = AssetName.EndsWith(ECsLoadCached::Str::_C) ? AssetName : AssetName + ECsLoadCached::Str::_C;
		Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
		if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
		{
			UObject* Asset = Member->LoadSynchronous();

			Reference.Size.Bytes = Asset->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
			Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
			Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromSoftObjectProperty_Blueprint(USoftObjectProperty* &SoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = SoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TSoftObjectPtr<UBlueprint>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UBlueprint>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToSoftObjectPath();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
			return;

		OutAssetReferences.AddDefaulted();

		const int32 Size = OutAssetReferences.Num();

		// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TSoftObjectPtr for UAnimBlueprint / UWidgetBlueprint does NOT have _C
		FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
										  // AssetName.EndsWith(TEXT("_C")) ? AssetName : AssetName + TEXT("_C");
		Reference.Reference				   = AssetName.EndsWith(ECsLoadCached::Str::_C) ? AssetName : AssetName + ECsLoadCached::Str::_C;
		Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
		if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
		{
			UObject* Asset = Member->LoadSynchronous();

			Reference.Size.Bytes = Asset->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
			Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
			Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromArraySoftObjectProperty_AnimMontage(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArraySoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TSoftObjectPtr<UAnimMontage>>* Member = ArraySoftObjectProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<UAnimMontage>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == NCsCached::Str::Empty)
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
			{
				UAnimMontage* Asset = Cast<UAnimMontage>((*Member)[I].LoadSynchronous());

				TArray<UAnimationAsset*> AnimationAssets;

				Asset->GetAllAnimationSequencesReferred(AnimationAssets);

				const int32 AssetCount = AnimationAssets.Num();

				for (int32 J = 0; J < AssetCount; J++)
				{
					if (UAnimSequence* Anim = Cast<UAnimSequence>(AnimationAssets[J]))
					{
						Reference.Size.Bytes += Anim->GetApproxCompressedSize();
					}
				}

				Reference.Size.Kilobytes = KilobytesToBytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = BytesToKilobytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArraySoftObjectProperty_AnimMontage(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArraySoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TSoftObjectPtr<UAnimMontage>>* Member = ArraySoftObjectProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<UAnimMontage>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == NCsCached::Str::Empty)
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
			{
				UAnimMontage* Asset = Cast<UAnimMontage>((*Member)[I].LoadSynchronous());

				TArray<UAnimationAsset*> AnimationAssets;

				Asset->GetAllAnimationSequencesReferred(AnimationAssets);

				const int32 AssetCount = AnimationAssets.Num();

				for (int32 J = 0; J < AssetCount; J++)
				{
					if (UAnimSequence* Anim = Cast<UAnimSequence>(AnimationAssets[J]))
					{
						Reference.Size.Bytes += Anim->GetApproxCompressedSize();
					}
				}

				Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArraySoftObjectProperty_AnimSequence(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArraySoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TSoftObjectPtr<UAnimSequence>>* Member = ArraySoftObjectProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<UAnimSequence>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == NCsCached::Str::Empty)
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
			{
				UAnimSequence* Asset = Cast<UAnimSequence>((*Member)[I].LoadSynchronous());

				Reference.Size.Bytes = Asset->GetApproxCompressedSize();
				Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArraySoftObjectProperty_AnimSequence(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArraySoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TSoftObjectPtr<UAnimSequence>>* Member = ArraySoftObjectProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<UAnimSequence>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == NCsCached::Str::Empty)
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
			{
				UAnimSequence* Asset = Cast<UAnimSequence>((*Member)[I].LoadSynchronous());

				Reference.Size.Bytes = Asset->GetApproxCompressedSize();
				Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArraySoftObjectProperty_MaterialInstanceConstant(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArraySoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TSoftObjectPtr<UMaterialInstanceConstant>>* Member = ArraySoftObjectProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<UMaterialInstanceConstant>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == NCsCached::Str::Empty)
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
			{
				UMaterialInstanceConstant* Asset = Cast<UMaterialInstanceConstant>((*Member)[I].LoadSynchronous());

				if (!Asset)
				{
					UE_LOG(LogCs, Warning, TEXT("UCsCommon_Load::GetAssetReferenceFromArraySoftObjectProperty_MaterialInstanceConstant: Failed to Load %s[%d]"), *MemberName, I);
					continue;
				}

				const int32 TextureCount = Asset->TextureParameterValues.Num();

				for (int32 J = 0; J < TextureCount; J++)
				{
					UTexture* Texture = Asset->TextureParameterValues[J].ParameterValue;

					if (!Texture)
						continue;

					Reference.Size.Bytes += Texture->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
				}

				Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArraySoftObjectProperty_MaterialInstanceConstant(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArraySoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TSoftObjectPtr<UMaterialInstanceConstant>>* Member = ArraySoftObjectProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<UMaterialInstanceConstant>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == NCsCached::Str::Empty)
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
			{
				UMaterialInstanceConstant* Asset = Cast<UMaterialInstanceConstant>((*Member)[I].LoadSynchronous());

				const int32 TextureCount = Asset->TextureParameterValues.Num();

				for (int32 J = 0; J < TextureCount; J++)
				{
					UTexture* Texture = Asset->TextureParameterValues[J].ParameterValue;

					if (!Texture)
						continue;

					Reference.Size.Bytes += Texture->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
				}

				Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArraySoftObjectProperty_Blueprint(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArraySoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TSoftObjectPtr<UBlueprint>>* Member = ArraySoftObjectProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<UBlueprint>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == NCsCached::Str::Empty)
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();
			// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TSoftObjectPtr for UWidgetBlueprint does NOT have _C
			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
											  // AssetName.EndsWith(TEXT("_C")) ? AssetName : AssetName + TEXT("_C");
			Reference.Reference				   = AssetName.EndsWith(ECsLoadCached::Str::_C) ? AssetName : AssetName + ECsLoadCached::Str::_C;
			Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
			if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
			{
				UBlueprint* Asset = (*Member)[I].LoadSynchronous();

				Reference.Size.Bytes = Asset->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
				Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArraySoftObjectProperty_Blueprint(UArrayProperty* &ArraySoftObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArraySoftObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TSoftObjectPtr<UBlueprint>>* Member = ArraySoftObjectProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<UBlueprint>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToSoftObjectPath();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == NCsCached::Str::Empty)
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();
			// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TSoftObjectPtr for UWidgetBlueprint does NOT have _C
			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
											  // AssetName.EndsWith(TEXT("_C")) ? AssetName : AssetName + TEXT("_C");
			Reference.Reference				   = AssetName.EndsWith(ECsLoadCached::Str::_C) ? AssetName : AssetName + ECsLoadCached::Str::_C;
			Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
			if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
			{
				UBlueprint* Asset = (*Member)[I].LoadSynchronous();

				Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
				Reference.Size.Kilobytes = BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

#pragma endregion FCsStringAssetReference

void UCsCommon_Load::GetAssetReferencesFromStruct(void* InStruct, UScriptStruct* const &InScriptStruct, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal /*=nullptr*/, const int32 &LoadCodes /*=ECsLoadCodes::CalculateResourceSizes*/)
{
	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(*It))
		{
			// ACsData_ProjectileBase
			if (SoftClassProperty->MetaClass == ACsData_ProjectileBase::StaticClass())
			{ GetAssetReferenceFromSoftClassProperty<ACsData_ProjectileBase>(SoftClassProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
			// ACsData_ProjectileImpact
			if (SoftClassProperty->MetaClass == ACsData_ProjectileImpact::StaticClass())
			{ GetAssetReferenceFromSoftClassProperty<ACsData_ProjectileImpact>(SoftClassProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes))
					continue;
			}
			continue;
		}
		// TSoftObjectPtr
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(*It))
		{
			// UStaticMesh
			if (SoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty<UStaticMesh>(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
			// USkeletalMesh
			if (SoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty<USkeletalMesh>(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
			// UMaterialInstance
			if (SoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty<UMaterialInstance>(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::EstimatedTotal, OutAssetReferences, LoadCodes); continue; }
			// UMaterialInstanceConstant
			if (SoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{
				if (SoftObjectProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferenceFromSoftObjectProperty_MaterialInstanceConstant(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
				if (SoftObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ GetAssetReferenceFromFixedArraySoftObjectProperty_EnumSize_MaterialInstanceConstant<ECS_INTERACTIVE_STATE_MAX>(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes))
						continue;
				}
				continue;
			}
			// UPhysicalMaterial
			if (SoftObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty<UPhysicalMaterial>(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::EstimatedTotal, OutAssetReferences, LoadCodes); continue; }
			// UPhysicsAsset
			if (SoftObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty<UPhysicsAsset>(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
			// UAnimSequence
			if (SoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty_AnimSequence(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
			// UAnimMontage
			if (SoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty_AnimMontage(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
			// UBlendSpace1D
			if (SoftObjectProperty->PropertyClass == UBlendSpace1D::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty<UBlendSpace1D>(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
			// UBlendSpace
			if (SoftObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty<UBlendSpace>(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
			// UAnimOffsetBlendSpace
			if (SoftObjectProperty->PropertyClass == UAimOffsetBlendSpace::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty<UAimOffsetBlendSpace>(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
			// UAnimBlueprint
			if (SoftObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty_Blueprint(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
			// USoundCue
			if (SoftObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty<USoundCue>(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::EstimatedTotal, OutAssetReferences, LoadCodes); continue; }
			// UParticleSystem
			if (SoftObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty<UParticleSystem>(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::EstimatedTotal, OutAssetReferences, LoadCodes); continue; }
			// UCurveFloat
			if (SoftObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty<UCurveFloat>(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::EstimatedTotal, OutAssetReferences, LoadCodes); continue; }
			// UCurveVector
			if (SoftObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ GetAssetReferenceFromSoftObjectProperty<UCurveVector>(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::EstimatedTotal, OutAssetReferences, LoadCodes); continue; }
			// UBlueprint
			if (SoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{
				if (SoftObjectProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferenceFromSoftObjectProperty_Blueprint(SoftObjectProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
			}
			
			if (Internal)
			{
				if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes))
					continue;
			}
			continue;
		}
		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsStaticMesh>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes))
						continue;
				}
				continue;
			}
			// FCsFpvStaticMesh
			if (StructProperty->Struct == FCsFpvStaticMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpvStaticMesh>(StructProperty, InStruct, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsTArrayStaticMesh
			if (StructProperty->Struct == FCsTArrayStaticMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsTArrayStaticMesh>(StructProperty, InStruct, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsSkeletalMesh>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsFpsSkeletalMesh
			if (StructProperty->Struct == FCsFpsSkeletalMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsSkeletalMesh>(StructProperty, InStruct, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsTArraySkeletalMesh
			if (StructProperty->Struct == FCsTArraySkeletalMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsTArraySkeletalMesh>(StructProperty, InStruct, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsMaterialInstance>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsPhysicalMaterial
			if (StructProperty->Struct == FCsPhysicalMaterial::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsPhysicalMaterial>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsPhysicsAsset>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsSoundElement>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			}
			// FCsFpvSoundElement
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsFpvSoundElement>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsFxElement>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			}
			// FCsFpvFxElement
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsFpvFxElement>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsAnimSequence>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsFpvAnimSequence
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpvAnimSequence>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsAnimMontage>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsFpvAnimMontage
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpvAnimMontage>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsTArrayAnimMontage>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsAnimBlueprint>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsFpvAnimBlueprint
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpvAnimBlueprint>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsBlendSpace1D
			if (StructProperty->Struct == FCsBlendSpace1D::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsBlendSpace1D>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsFpvBlendSpace1D
			if (StructProperty->Struct == FCsFpvBlendSpace1D::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpvBlendSpace1D>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsBlendSpace>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsFpvBlendSpace
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpvBlendSpace>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsAimOffset
			if (StructProperty->Struct == FCsAimOffset::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsAimOffset>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsFpvAimOffset
			if (StructProperty->Struct == FCsFpvAimOffset::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpvAimOffset>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsBlueprint
			if (StructProperty->Struct == FCsBlueprint::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsBlueprint>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// FCsCollisionPreset
			if (StructProperty->Struct == FCsCollisionPreset::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsCollisionPreset>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			// Weapon_FireMode
			{
				// FCsData_Weapon_FireMode_Firing
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Firing::StaticStruct())
				{ GetAssetReferencesFromStructProperty<FCsData_Weapon_FireMode_Firing>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsData_Weapon_FireMode_Animation
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Animation::StaticStruct())
				{ GetAssetReferencesFromStructProperty<FCsData_Weapon_FireMode_Animation>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsData_FpsWeapon_FireMode_Animation
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Animation::StaticStruct())
				{ GetAssetReferencesFromStructProperty<FCsData_FpsWeapon_FireMode_Animation>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsData_Weapon_FireMode_Scope
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Scope::StaticStruct())
				{ GetAssetReferencesFromStructProperty<FCsData_Weapon_FireMode_Scope>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsData_Weapon_FireMode_FXs
				if (StructProperty->Struct == FCsData_Weapon_FireMode_FXs::StaticStruct())
				{ GetAssetReferencesFromStructProperty<FCsData_Weapon_FireMode_FXs>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsData_FpsWeapon_FireMode_FXs
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_FXs::StaticStruct())
				{ GetAssetReferencesFromStructProperty<FCsData_FpsWeapon_FireMode_FXs>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsData_Weapon_FireMode_Sounds
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Sounds::StaticStruct())
				{ GetAssetReferencesFromStructProperty<FCsData_Weapon_FireMode_Sounds>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsData_FpsWeapon_FireMode_Sounds
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Sounds::StaticStruct())
				{ GetAssetReferencesFromStructProperty<FCsData_FpsWeapon_FireMode_Sounds>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			}
			// FCsData_ProjectileBasePtr
			if (StructProperty->Struct == FCsData_ProjectileBasePtr::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsData_ProjectileBasePtr>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes))
					continue;
			}
			continue;
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftClassPtr
			if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				// AShooterWeaponData
				//if (InnerSoftClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerSoftClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//{ GetAssetReferenceFromArraySoftObjectProperty<AShooterWeaponData>(ArrayProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences); continue; }
				if (Internal)
				{
					if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes))
						continue;
				}
				continue;
			}
			// TSoftObjectPtr
			if (USoftObjectProperty* InnerSoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerSoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ GetAssetReferenceFromArraySoftObjectProperty<UStaticMesh>(ArrayProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
				// USkeletalMesh
				if (InnerSoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ GetAssetReferenceFromArraySoftObjectProperty<USkeletalMesh>(ArrayProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
				// UMaterialInstance
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ GetAssetReferenceFromArraySoftObjectProperty<UMaterialInstance>(ArrayProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::EstimatedTotal, OutAssetReferences, LoadCodes); continue; }
				// UMaterialInstanceConstant
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ GetAssetReferenceFromArraySoftObjectProperty_MaterialInstanceConstant(ArrayProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
				// UAnimSequence
				if (InnerSoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ GetAssetReferenceFromArraySoftObjectProperty_AnimSequence(ArrayProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
				// UAnimMontage
				if (InnerSoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ GetAssetReferenceFromArraySoftObjectProperty_AnimMontage(ArrayProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
				// UBlueprint
				if (InnerSoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ GetAssetReferenceFromArraySoftObjectProperty_Blueprint(ArrayProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes))
						continue;
				}
				continue;
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsAnimMontage>(ArrayProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsFxElement
				if (InnerStructProperty->Struct == FCsFxElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFxElement>(ArrayProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsFpvFxElement
				if (InnerStructProperty->Struct == FCsFpvFxElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpvFxElement>(ArrayProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsSoundElement>(ArrayProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsFpvSoundElement
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpvSoundElement>(ArrayProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsAnimSequence
				if (InnerStructProperty->Struct == FCsAnimSequence::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsAnimSequence>(ArrayProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsFpvAnimSequence
				if (InnerStructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpvAnimSequence>(ArrayProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsAnimMontage>(ArrayProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsFpvAnimMontage
				if (InnerStructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpvAnimMontage>(ArrayProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes))
						continue;
				}
				continue;
			}
			continue;
		}
		// Map
		if (UMapProperty* MapProperty = Cast<UMapProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes))
					continue;
			}
			continue;
		}
	}
}

void UCsCommon_Load::GetAssetReferencesFromObject(void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromObject_Internal Internal /*=nullptr*/, const int32 &LoadCodes /*=ECsLoadCodes::CalculateResourceSizes*/)
{
	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsStaticMesh>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InObject, InClass, LoadFlags, OutAssetReferences, LoadCodes))
						continue;
				}
				continue;
			}
			// FCsFpvStaticMesh
			if (StructProperty->Struct == FCsFpvStaticMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpvStaticMesh>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsTArrayStaticMesh
			if (StructProperty->Struct == FCsTArrayStaticMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsTArrayStaticMesh>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsSkeletalMesh>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsFpsSkeletalMesh
			if (StructProperty->Struct == FCsFpsSkeletalMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsSkeletalMesh>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsTArraySkeletalMesh
			if (StructProperty->Struct == FCsTArraySkeletalMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsTArraySkeletalMesh>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsMaterialInstance>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsMaterialInstanceConstant
			if (StructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsMaterialInstanceConstant>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsTArrayMaterialInstanceConstant::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsTArrayMaterialInstanceConstant>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				if (StructProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ GetAssetReferencesFromFixedArrayStructProperty_EnumSize<FCsTArrayMaterialInstanceConstant, ECS_INTERACTIVE_STATE_MAX>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InObject, InClass, LoadFlags, OutAssetReferences, LoadCodes))
						continue;
				}
				continue;
			}
			// FCsFpsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsFpsTArrayMaterialInstanceConstant::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsTArrayMaterialInstanceConstant>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsInteractiveMaterials
			if (StructProperty->Struct == FCsInteractiveMaterials::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsInteractiveMaterials>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsPhysicalMaterial
			if (StructProperty->Struct == FCsPhysicalMaterial::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsPhysicalMaterial>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsPhysicsAsset>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsCurveFloat
			if (StructProperty->Struct == FCsCurveFloat::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsCurveFloat>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsCurveVector>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsSoundElement>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, InObject, InClass, LoadFlags, OutAssetReferences, LoadCodes))
						continue;
				}
				continue;
			}
			// FCsFpvSoundElement
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsFpvSoundElement>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, InObject, InClass, LoadFlags, OutAssetReferences, LoadCodes))
						continue;
				}
				continue;
			}
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsCurveVector>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsParticleSystem
			if (StructProperty->Struct == FCsParticleSystem::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsParticleSystem>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsFxElement>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, InObject, InClass, LoadFlags, OutAssetReferences, LoadCodes))
						continue;
				}
				continue;
			}
			// FCsFpvFxElement
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsFpvFxElement>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, InObject, InClass, LoadFlags, OutAssetReferences, LoadCodes))
						continue;
				}
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsAnimSequence>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsFpvAnimSequence
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpvAnimSequence>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsAnimMontage>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsFpvAnimMontage
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpvAnimMontage>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsTArrayAnimMontage>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsAnimBlueprint>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsFpvAnimBlueprint
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpvAnimBlueprint>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsBlendSpace1D
			if (StructProperty->Struct == FCsBlendSpace1D::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsBlendSpace1D>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsFpvBlendSpace1D
			if (StructProperty->Struct == FCsFpvBlendSpace1D::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpvBlendSpace1D>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsBlendSpace>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsFpvBlendSpace
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpvBlendSpace>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsAimOffset
			if (StructProperty->Struct == FCsAimOffset::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsAimOffset>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsFpvAimOffset
			if (StructProperty->Struct == FCsFpvAimOffset::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpvAimOffset>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsBlueprint
			if (StructProperty->Struct == FCsBlueprint::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsBlueprint>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsTArrayBlueprint
			if (StructProperty->Struct == FCsTArrayBlueprint::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsTArrayBlueprint>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsWidgetComponentInfo
			if (StructProperty->Struct == FCsWidgetComponentInfo::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsWidgetComponentInfo>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsWidgetActorInfo
			if (StructProperty->Struct == FCsWidgetActorInfo::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsWidgetActorInfo>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsData_ProjectileImpactPtr
			if (StructProperty->Struct == FCsData_ProjectileImpactPtr::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsData_ProjectileImpactPtr>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsDamageFalloff
			if (StructProperty->Struct == FCsDamageFalloff::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsDamageFalloff>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
			// FCsDamageRadial
			if (StructProperty->Struct == FCsDamageRadial::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsDamageRadial>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InObject, InClass, LoadFlags, OutAssetReferences, LoadCodes))
					continue;
			}
			continue;
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FCsMaterialInstance
				if (InnerStructProperty->Struct == FCsMaterialInstance::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsMaterialInstance>(ArrayProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				// FCsMaterialInstanceConstant
				if (InnerStructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsMaterialInstanceConstant>(ArrayProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				// FCsFxElement
				if (InnerStructProperty->Struct == FCsFxElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFxElement>(ArrayProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				// FCsFpvFxElement
				if (InnerStructProperty->Struct == FCsFpvFxElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpvFxElement>(ArrayProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				// FCsFpvSoundElement
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpvSoundElement>(ArrayProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				// FCsAnimSequence
				if (InnerStructProperty->Struct == FCsAnimSequence::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsAnimSequence>(ArrayProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				// FCsFpvAnimSequence
				if (InnerStructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpvAnimSequence>(ArrayProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsAnimMontage>(ArrayProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				// FCsFpvAnimMontage
				if (InnerStructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpvAnimMontage>(ArrayProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, InObject, InClass, LoadFlags, OutAssetReferences, LoadCodes))
						continue;
				}
				continue;
			}
			continue;
		}
		// Map
		if (UMapProperty* MapProperty = Cast<UMapProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, InObject, InClass, LoadFlags, OutAssetReferences, LoadCodes))
					continue;
			}
			continue;
		}
	}
}

#pragma endregion Asset References

	// Load
#pragma region

void UCsCommon_Load::LoadTSoftObjectPtr_AnimBlueprint(const FString &MemberName, TSoftObjectPtr<UAnimBlueprint> AssetPtr, UAnimBlueprintGeneratedClass* &Internal)
{
	const FString& AssetName = AssetPtr.ToString();

	// (AssetName == TEXT(""))
	if (AssetName == NCsCached::Str::Empty)
	{
		Internal = nullptr;
		return;
	}

	if (Internal &&
		AssetPtr.IsValid() && AssetPtr.Get() &&
		Internal == Cast<UAnimBlueprintGeneratedClass>(Cast<UBlueprintCore>(AssetPtr.Get())->GeneratedClass))
	{
		UE_LOG(LogLoad, Warning, TEXT("UCsCUCsCommon_Loadommon::LoadTSoftObjectPtr_AnimBlueprint (%s): Possibly trying to load Anim Blueprint and it is already loaded"), *MemberName);
		return;
	}

	if (AssetPtr.IsValid() && AssetPtr.Get())
	{
		Internal = Cast<UAnimBlueprintGeneratedClass>(Cast<UBlueprintCore>(AssetPtr.Get())->GeneratedClass);
	}
	else
	{
																			//TEXT("_C")
		const FString AssetDescription = TEXT("AnimBlueprint'") + AssetName + ECsLoadCached::Str::_C + TEXT("'");
		Internal					    = (UAnimBlueprintGeneratedClass*)StaticLoadObject(UClass::StaticClass(), NULL, *AssetDescription, NULL, LOAD_None, NULL);

		if (!Internal)
		{
			UE_LOG(LogLoad, Warning, TEXT("UCsCommon_Load::LoadTSoftObjectPtr_AnimBlueprint (%s): Failed to load Anim Blueprint at %s"), *MemberName, *AssetDescription);
		}
	}
}

void UCsCommon_Load::LoadTSoftObjectPtr_AnimBlueprint(const FString &MemberName, TSoftObjectPtr<UAnimBlueprint>* AssetPtr, UAnimBlueprintGeneratedClass* &Internal)
{
	const FString& AssetName = AssetPtr->ToString();

	// (AssetName == TEXT("")
	if (AssetName == NCsCached::Str::Empty)
	{
		Internal = nullptr;
		return;
	}

	if (Internal &&
		AssetPtr->IsValid() && AssetPtr->Get() &&
		Internal == Cast<UAnimBlueprintGeneratedClass>(Cast<UBlueprintCore>(AssetPtr->Get())->GeneratedClass))
	{
		UE_LOG(LogLoad, Warning, TEXT("UCsCUCsCommon_Loadommon::LoadTSoftObjectPtr_AnimBlueprint (%s): Possibly trying to load Anim Blueprint and it is already loaded"), *MemberName);
		return;
	}

	if (AssetPtr->IsValid() && AssetPtr->Get())
	{
		Internal = Cast<UAnimBlueprintGeneratedClass>(Cast<UBlueprintCore>(AssetPtr->Get())->GeneratedClass);
	}
	else
	{
																			//TEXT("_C")
		const FString AssetDescription = TEXT("AnimBlueprint'") + AssetName + ECsLoadCached::Str::_C + TEXT("'");
		Internal					   = (UAnimBlueprintGeneratedClass*)StaticLoadObject(UClass::StaticClass(), NULL, *AssetDescription, NULL, LOAD_None, NULL);

		if (!Internal)
		{
			UE_LOG(LogLoad, Warning, TEXT("UCsCommon_Load::LoadTSoftObjectPtr_AnimBlueprint (%s): Failed to load Anim Blueprint at %s"), *MemberName, *AssetDescription);
		}
	}
}

void UCsCommon_Load::LoadSoftObjectProperty_AnimBlueprint(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TSoftObjectPtr<UAnimBlueprint>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UAnimBlueprint>>(InObject))
	{
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
			return;

										// MemberName = TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (UAnimBlueprintGeneratedClass** Internal = InternalProperty->ContainerPtrToValuePtr<UAnimBlueprintGeneratedClass*>(InObject))
				LoadTSoftObjectPtr_AnimBlueprint(ObjectName + NCsCached::Str::Dot + MemberName, Member, *Internal);
										//  ObjectName = TEXT(".") + MemberName
		}
	}
}

void UCsCommon_Load::LoadSoftObjectProperty_AnimBlueprint(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TSoftObjectPtr<UAnimBlueprint>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UAnimBlueprint>>(InObject))
	{
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
			return;

										// MemberName = TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (UAnimBlueprintGeneratedClass** Internal = InternalProperty->ContainerPtrToValuePtr<UAnimBlueprintGeneratedClass*>(InObject))
				LoadTSoftObjectPtr_AnimBlueprint(ObjectName + NCsCached::Str::Dot + MemberName, Member, *Internal);
										//  ObjectName + TEXT(".") + MemberName
		}
	}
}

void UCsCommon_Load::LoadTSoftObjectPtr_Blueprint(const FString &MemberName, TSoftObjectPtr<UBlueprint> AssetPtr, UBlueprintGeneratedClass* &Internal)
{
	const FString& AssetName = AssetPtr.ToString();

	// (AssetName == TEXT(""))
	if (AssetName == NCsCached::Str::Empty)
	{
		Internal = nullptr;
		return;
	}

	if (Internal &&
		AssetPtr.IsValid() && AssetPtr.Get() &&
		Internal == Cast<UBlueprintGeneratedClass>(Cast<UBlueprintCore>(AssetPtr.Get())->GeneratedClass))
	{
		//UE_LOG(LogLoad, Warning, TEXT("UCsCommon_Load::LoadTSoftObjectPtr_Blueprint (%s): Possibly trying to load Blueprint and it is already loaded"), *MemberName);
		return;
	}

	if (AssetPtr.IsValid() && AssetPtr.Get())
	{
		Internal = Cast<UBlueprintGeneratedClass>(Cast<UBlueprintCore>(AssetPtr.Get())->GeneratedClass);
	}
	else
	{
																		//TEXT("_C")
		const FString AssetDescription = TEXT("Blueprint'") + AssetName + ECsLoadCached::Str::_C + TEXT("'");
		Internal					   = (UBlueprintGeneratedClass*)StaticLoadObject(UClass::StaticClass(), NULL, *AssetDescription, NULL, LOAD_None, NULL);

		if (!Internal)
		{
			UE_LOG(LogLoad, Warning, TEXT("UCsCommon_Load::LoadTSoftObjectPtr_Blueprint (%s): Failed to load Blueprint at %s"), *MemberName, *AssetDescription);
		}
	}
}

void UCsCommon_Load::LoadTSoftObjectPtr_Blueprint(const FString &MemberName, TSoftObjectPtr<UBlueprint>* AssetPtr, UBlueprintGeneratedClass* &Internal)
{
	const FString& AssetName = AssetPtr->ToString();

	// (AssetName == TEXT(""))
	if (AssetName == NCsCached::Str::Empty)
	{
		Internal = nullptr;
		return;
	}

	if (Internal &&
		AssetPtr->IsValid() && AssetPtr->Get() &&
		Internal == Cast<UBlueprintGeneratedClass>(Cast<UBlueprintCore>(AssetPtr->Get())->GeneratedClass))
	{
		//UE_LOG(LogLoad, Warning, TEXT("UCsCommon_Load::LoadTSoftObjectPtr_Blueprint (%s): Possibly trying to load Blueprint and it is already loaded"), *MemberName);
		return;
	}

	if (AssetPtr->IsValid() && AssetPtr->Get())
	{
		Internal = Cast<UBlueprintGeneratedClass>(Cast<UBlueprintCore>(AssetPtr->Get())->GeneratedClass);
	}
	else
	{
																		//TEXT("_C")
		const FString AssetDescription = TEXT("Blueprint'") + AssetName + ECsLoadCached::Str::_C + TEXT("'");
		Internal					   = (UBlueprintGeneratedClass*)StaticLoadObject(UClass::StaticClass(), NULL, *AssetDescription, NULL, LOAD_None, NULL);

		if (!Internal)
		{
			UE_LOG(LogLoad, Warning, TEXT("UCsCommon_Load::LoadTSoftObjectPtr_Blueprint (%s): Failed to load Blueprint at %s"), *MemberName, *AssetDescription);
		}
	}
}

void UCsCommon_Load::LoadTArrayTSoftObjectPtr_Blueprint(const FString &MemberName, TArray<TSoftObjectPtr<UBlueprint>> &ArrayAssetPtr, TArray<UBlueprintGeneratedClass*> &ArrayInternal)
{
	if (ArrayInternal.Num() > 0 &&
		AreAllElementsInTArrayNotNull(ArrayInternal))
	{
		//UE_LOG(LogLoad, Warning, TEXT("UCsCommon_Load::LoadTArrayTSoftObjectPtr_Blueprint (%s): Possibly trying to load Blueprint and it is already loaded"), *MemberName);
	}

	UCsCommon_Load::NullAndEmptyTArray<UBlueprintGeneratedClass>(ArrayInternal);

	const int32 Count = ArrayAssetPtr.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		TSoftObjectPtr<UBlueprint>& AssetPtr = ArrayAssetPtr[I];

		if (AssetPtr.IsValid() && AssetPtr.Get())
		{
			UBlueprint* Bp				   = AssetPtr.Get();
			UBlueprintGeneratedClass* Data = Cast<UBlueprintGeneratedClass>(Cast<UBlueprintCore>(Bp)->GeneratedClass);

			ArrayInternal.Add(Data);
			continue;
		}
		
		const FString& AssetName = AssetPtr.ToString();

		// (AssetName != TEXT(""))
		if (AssetName != NCsCached::Str::Empty)
		{
																			//TEXT("_C")
			const FString AssetDescription = TEXT("Blueprint'") + AssetName + ECsLoadCached::Str::_C + TEXT("'");
			UBlueprintGeneratedClass* Data = (UBlueprintGeneratedClass*)StaticLoadObject(UClass::StaticClass(), NULL, *AssetDescription, NULL, LOAD_None, NULL);

			if (!Data)
			{
				UE_LOG(LogLoad, Warning, TEXT("UCsCommon_Load::LoadTArrayTSoftObjectPtr_Blueprint (%s[%d]): Failed to load Blueprint at %s"), *MemberName, I, *AssetDescription);
			}
			ArrayInternal.Add(Data);
		}
		else
		{
			ArrayInternal.Add(nullptr);
		}
	}
}

void UCsCommon_Load::LoadTArrayTSoftObjectPtr_Blueprint(const FString &MemberName, TArray<TSoftObjectPtr<UBlueprint>>* &ArrayAssetPtr, TArray<UBlueprintGeneratedClass*> &ArrayInternal)
{
	if (ArrayInternal.Num() > 0 &&
		AreAllElementsInTArrayNotNull(ArrayInternal))
	{
		//UE_LOG(LogLoad, Warning, TEXT("UCsCommon_Load::LoadTArrayTSoftObjectPtr_Blueprint (%s): Possibly trying to load Blueprint and it is already loaded"), *MemberName);
	}

	UCsCommon_Load::NullAndEmptyTArray<UBlueprintGeneratedClass>(ArrayInternal);

	const int32 Count = ArrayAssetPtr->Num();

	for (int32 I = 0; I < Count; ++I)
	{
		TSoftObjectPtr<UBlueprint>& AssetPtr	= (*ArrayAssetPtr)[I];

		if (AssetPtr.IsValid() && AssetPtr.Get())
		{
			UBlueprint* Bp				   = AssetPtr.Get();
			UBlueprintGeneratedClass* Data = Cast<UBlueprintGeneratedClass>(Cast<UBlueprintCore>(Bp)->GeneratedClass);

			ArrayInternal.Add(Data);
			continue;
		}

		const FString& AssetName = AssetPtr.ToString();

		// (AssetName != TEXT(""))
		if (AssetName != NCsCached::Str::Empty)
		{
																			//TEXT("_C")
			const FString AssetDescription = TEXT("Blueprint'") + AssetName + ECsLoadCached::Str::_C + TEXT("'");
			UBlueprintGeneratedClass* Data = (UBlueprintGeneratedClass*)StaticLoadObject(UClass::StaticClass(), NULL, *AssetDescription, NULL, LOAD_None, NULL);

			if (!Data)
			{
				UE_LOG(LogLoad, Warning, TEXT("UCsCommon_Load::LoadTArrayTSoftObjectPtr_Blueprint (%s[%d]): Failed to load Blueprint at %s"), *MemberName, I, *AssetDescription);
			}
			ArrayInternal.Add(Data);
		}
		else
		{
			ArrayInternal.Add(nullptr);
		}
	}
}

void UCsCommon_Load::LoadFCsAnimSequence(const FString &MemberName, FCsAnimSequence* Anim, const ECsLoadFlags &LoadFlags)
{
	LoadFCsStruct<FCsAnimSequence>(MemberName, Anim, LoadFlags);
}

void UCsCommon_Load::LoadFCsAnimSequence(const FString &MemberName, FCsAnimSequence* Anim)
{
	LoadFCsAnimSequence(MemberName, Anim, ECsLoadFlags::All);
}

void UCsCommon_Load::LoadFCsFpvAnimSequence(const FString &MemberName, FCsFpvAnimSequence* Anim, const ECsLoadFlags &LoadFlags)
{
	LoadFCsStruct<FCsFpvAnimSequence>(MemberName, Anim, LoadFlags);
}

void UCsCommon_Load::LoadFCsFpvAnimSequence(const FString &MemberName, FCsFpvAnimSequence* Anim, const TCsViewType &ViewType)
{
	ECsLoadFlags LoadFlags = ECsLoadFlags::All;

	if (ViewType == ECsViewType::FirstPerson)
		LoadFlags = ECsLoadFlags::Game1P;
	if (ViewType == ECsViewType::ThirdPerson)
		LoadFlags = ECsLoadFlags::Game3P;
	if (ViewType == ECsViewType::VR)
		LoadFlags = ECsLoadFlags::GameVR;

	LoadFCsFpvAnimSequence(MemberName, Anim, LoadFlags);
}

void UCsCommon_Load::LoadFCsAnimMontage(const FString &MemberName, FCsAnimMontage* Anim, const ECsLoadFlags &LoadFlags)
{
	LoadFCsStruct<FCsAnimMontage>(MemberName, Anim, LoadFlags);
}

void UCsCommon_Load::LoadFCsAnimMontage(const FString &MemberName, FCsAnimMontage* Anim)
{
	LoadFCsAnimMontage(MemberName, Anim, ECsLoadFlags::All);
}

void UCsCommon_Load::LoadFCsFpvAnimMontage(const FString &MemberName, FCsFpvAnimMontage* Anim, const ECsLoadFlags &LoadFlags)
{
	LoadFCsStruct<FCsFpvAnimMontage>(MemberName, Anim, LoadFlags);
}

void UCsCommon_Load::LoadFCsFpvAnimMontage(const FString &MemberName, FCsFpvAnimMontage* Anim, const TCsViewType &ViewType)
{
	ECsLoadFlags LoadFlags = ECsLoadFlags::All;

	if (ViewType == ECsViewType::FirstPerson)
		LoadFlags = ECsLoadFlags::Game1P;
	if (ViewType == ECsViewType::ThirdPerson)
		LoadFlags = ECsLoadFlags::Game3P;
	if (ViewType == ECsViewType::VR)
		LoadFlags = ECsLoadFlags::GameVR;

	LoadFCsFpvAnimMontage(MemberName, Anim, LoadFlags);
}

void UCsCommon_Load::LoadFCsBlendSpace1D(const FString &MemberName, FCsBlendSpace1D* Blend, const ECsLoadFlags &LoadFlags)
{
	LoadFCsStruct<FCsBlendSpace1D>(MemberName, Blend, LoadFlags);
}

void UCsCommon_Load::LoadFCsBlendSpace1D(const FString &MemberName, FCsBlendSpace1D* Blend)
{
	LoadFCsBlendSpace1D(MemberName, Blend, ECsLoadFlags::All);
}

void UCsCommon_Load::LoadFCsFpvBlendSpace1D(const FString &MemberName, FCsFpvBlendSpace1D* Blend , const ECsLoadFlags &LoadFlags)
{
	LoadFCsStruct<FCsFpvBlendSpace1D>(MemberName, Blend, LoadFlags);
}

void UCsCommon_Load::LoadFCsFpvBlendSpace1D(const FString &MemberName, FCsFpvBlendSpace1D* Blend, const TCsViewType &ViewType)
{
	ECsLoadFlags LoadFlags = ECsLoadFlags::All;

	if (ViewType == ECsViewType::FirstPerson)
		LoadFlags = ECsLoadFlags::Game1P;
	if (ViewType == ECsViewType::ThirdPerson)
		LoadFlags = ECsLoadFlags::Game3P;
	if (ViewType == ECsViewType::VR)
		LoadFlags = ECsLoadFlags::GameVR;

	LoadFCsFpvBlendSpace1D(MemberName, Blend, LoadFlags);
}

void UCsCommon_Load::LoadFCsBlendSpace(const FString &MemberName, FCsBlendSpace* Blend, const ECsLoadFlags &LoadFlags)
{
	LoadFCsStruct<FCsBlendSpace>(MemberName, Blend, LoadFlags);
}

void UCsCommon_Load::LoadFCsBlendSpace(const FString &MemberName, FCsBlendSpace* Blend)
{
	LoadFCsBlendSpace(MemberName, Blend, ECsLoadFlags::All);
}

void UCsCommon_Load::LoadFCsFpvBlendSpace(const FString &MemberName, FCsFpvBlendSpace* Blend, const ECsLoadFlags &LoadFlags)
{
	LoadFCsStruct<FCsFpvBlendSpace>(MemberName, Blend, LoadFlags);
}

void UCsCommon_Load::LoadFCsFpvBlendSpace(const FString &MemberName, FCsFpvBlendSpace* Blend, const TCsViewType &ViewType)
{
	ECsLoadFlags LoadFlags = ECsLoadFlags::All;

	if (ViewType == ECsViewType::FirstPerson)
		LoadFlags = ECsLoadFlags::Game1P;
	if (ViewType == ECsViewType::ThirdPerson)
		LoadFlags = ECsLoadFlags::Game3P;
	if (ViewType == ECsViewType::VR)
		LoadFlags = ECsLoadFlags::GameVR;

	LoadFCsFpvBlendSpace(MemberName, Blend, LoadFlags);
}

void UCsCommon_Load::LoadFCsAimOffset(const FString &MemberName, FCsAimOffset* Blend, const ECsLoadFlags &LoadFlags)
{
	LoadFCsStruct<FCsAimOffset>(MemberName, Blend, LoadFlags);
}

void UCsCommon_Load::LoadFCsAimOffset(const FString &MemberName, FCsAimOffset* Blend)
{
	LoadFCsAimOffset(MemberName, Blend, ECsLoadFlags::All);
}

void UCsCommon_Load::LoadFCsFpvAimOffset(const FString &MemberName, FCsFpvAimOffset* Blend, const ECsLoadFlags &LoadFlags)
{
	LoadFCsStruct<FCsFpvAimOffset>(MemberName, Blend, LoadFlags);
}

void UCsCommon_Load::LoadFCsFpvAimOffset(const FString &MemberName, FCsFpvAimOffset* Blend, const TCsViewType &ViewType)
{
	ECsLoadFlags LoadFlags = ECsLoadFlags::All;

	if (ViewType == ECsViewType::FirstPerson)
		LoadFlags = ECsLoadFlags::Game1P;
	if (ViewType == ECsViewType::ThirdPerson)
		LoadFlags = ECsLoadFlags::Game3P;
	if (ViewType == ECsViewType::VR)
		LoadFlags = ECsLoadFlags::GameVR;

	LoadFCsFpvAimOffset(MemberName, Blend, LoadFlags);
}

bool UCsCommon_Load::CanLoad(void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags, const int32 &LoadCodes)
{
								// MemberName + TEXT("_LoadFlags")
	const FString FlagMemberName = MemberName + ECsLoadCached::Str::_LoadFlags;

	if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
	{
		if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
		{
			if (LoadFlags == ECsLoadFlags::All)
			{
				if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::SuppressLoadFlagsAllWarning))
					return true;

				UE_LOG(LogCs, Warning, TEXT("UCsCommon_Load::CanLoad (%s @ %s): Using LoadFlags = ECsLoadFlags::All. This should be reserved for debugging. Be explicit with LoadFlags."), *(InClass->GetName()), *MemberName);
				return true;
			}
			if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, ECsLoadFlags::All))
			{
				if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::SuppressLoadFlagsAllWarning))
					return true;

				UE_LOG(LogCs, Warning, TEXT("UCsCommon_Load::CanLoad (%s @ %s): Using LoadFlags = ECsLoadFlags::All. This should be reserved for debugging. Be explicit with LoadFlags."), *(InClass->GetName()), *MemberName);
				return true;
			}
			if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				return true;
		}
	}
	return false;
}

bool UCsCommon_Load::CanLoad(void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags, const int32 &LoadCodes)
{
								// MemberName + TEXT("_LoadFlags")
	const FString FlagMemberName = MemberName + ECsLoadCached::Str::_LoadFlags;

	if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
	{
		if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
		{
			if (LoadFlags == ECsLoadFlags::All)
			{
				if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::SuppressLoadFlagsAllWarning))
					return true;

				UE_LOG(LogCs, Warning, TEXT("UCsCommon_Load::CanLoad (%s @ %s): Using LoadFlags = ECsLoadFlags::All. This should be reserved for debugging. Be explicit with LoadFlags."), *(InClass->GetName()), *MemberName);
				return true;
			}
			if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, ECsLoadFlags::All))
			{
				if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::SuppressLoadFlagsAllWarning))
					return true;

				UE_LOG(LogCs, Warning, TEXT("UCsCommon_Load::CanLoad (%s @ %s): Using LoadFlags = ECsLoadFlags::All. This should be reserved for debugging. Be explicit with LoadFlags."), *(InClass->GetName()), *MemberName);
				return true;
			}
			if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				return true;
		}
	}
	return false;
}

void UCsCommon_Load::LoadSoftObjectProperty_Blueprint(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TSoftObjectPtr<UBlueprint>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UBlueprint>>(InObject))
	{
										// MemberName = TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (UBlueprintGeneratedClass** Internal = InternalProperty->ContainerPtrToValuePtr<UBlueprintGeneratedClass*>(InObject))
				LoadTSoftObjectPtr_Blueprint(ObjectName + NCsCached::Str::Dot + MemberName, Member, *Internal);
									//  ObjectName + TEXT(".") + MemberName
		}
	}
}

void UCsCommon_Load::LoadSoftObjectProperty_Blueprint(USoftObjectProperty* &SoftObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TSoftObjectPtr<UBlueprint>* Member = SoftObjectProperty->ContainerPtrToValuePtr<TSoftObjectPtr<UBlueprint>>(InObject))
	{
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
			return;

										// MemberName + TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (UBlueprintGeneratedClass** Internal = InternalProperty->ContainerPtrToValuePtr<UBlueprintGeneratedClass*>(InObject))
				LoadTSoftObjectPtr_Blueprint(ObjectName + NCsCached::Str::Dot + MemberName, Member, *Internal);
									//  ObjectName + TEXT(".") + MemberName
		}
	}
}

void UCsCommon_Load::LoadArraySoftObjectProperty_Blueprint(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TArray<TSoftObjectPtr<UBlueprint>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<UBlueprint>>>(InObject))
	{
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
			return;

										// MemberName + TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (TArray<UBlueprintGeneratedClass*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<UBlueprintGeneratedClass*>>(InObject))
				LoadTArrayTSoftObjectPtr_Blueprint(ObjectName + NCsCached::Str::Dot + MemberName, Member, *Internal);
											//ObjectName + TEXT(".") + MemberName
		}
	}
}

void UCsCommon_Load::LoadArraySoftObjectProperty_Blueprint(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TArray<TSoftObjectPtr<UBlueprint>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<UBlueprint>>>(InObject))
	{
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
			return;

										// MemberName + TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (TArray<UBlueprintGeneratedClass*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<UBlueprintGeneratedClass*>>(InObject))
				LoadTArrayTSoftObjectPtr_Blueprint(ObjectName + NCsCached::Str::Dot + MemberName, Member, *Internal);
											//ObjectName + TEXT(".") + MemberName
		}
	}
}

void UCsCommon_Load::LoadStructWithTSoftObjectPtrs(const FString &ObjectName, void* InStruct, UScriptStruct* const &InScriptStruct, const ECsLoadFlags &LoadFlags, TCsLoadStructWithTSoftObjectPtrs_Internal Internal /*=nullptr*/)
{
	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(*It))
		{
			// ACsData_ProjectileBase
			if (SoftClassProperty->MetaClass == ACsData_ProjectileBase::StaticClass())
			{ LoadSoftClassProperty<ACsData_ProjectileBase>(SoftClassProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::CsData_ProjectileBase, LoadFlags); continue; }
			// ACsData_ProjectileImpact
			if (SoftClassProperty->MetaClass == ACsData_ProjectileImpact::StaticClass())
			{ LoadSoftClassProperty<ACsData_ProjectileImpact>(SoftClassProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::CsData_ProjectileImpact, LoadFlags); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
					continue;
			}
			continue;
		}
		// TSoftObjectPtr
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(*It))
		{
			// UStaticMesh
			if (SoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ LoadSoftObjectProperty<UStaticMesh>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::StaticMesh, NCsCommonLoadCached::Str::Static_Mesh, LoadFlags); continue; }
			// USkeletalMesh
			if (SoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ LoadSoftObjectProperty<USkeletalMesh>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::SkeletalMesh, NCsCommonLoadCached::Str::Skeletal_Mesh, LoadFlags); continue; }
			// UMaterialInstance
			if (SoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ LoadSoftObjectProperty<UMaterialInstance>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::MaterialInstance, NCsCommonLoadCached::Str::MaterialInstance, LoadFlags); continue; }
			// UMaterialInstanceConstant
			if (SoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{
				if (SoftObjectProperty->ArrayDim == CS_SINGLETON)
				{ LoadSoftObjectProperty<UMaterialInstanceConstant>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::MaterialInstanceConstant, NCsCommonLoadCached::Str::MaterialInstanceConstant, LoadFlags); continue; }
				if (SoftObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ LoadFixedArraySoftObjectProperty_EnumSize<UMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::MaterialInstanceConstant, NCsCommonLoadCached::Str::MaterialInstanceConstant, LoadFlags, &ECsInteractiveState::ToString); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// UPhysicalMaterial
			if (SoftObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ LoadSoftObjectProperty<UPhysicalMaterial>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::PhysicalMaterial, NCsCommonLoadCached::Str::Physical_Material, LoadFlags); continue; }
			// UPhysicsAsset
			if (SoftObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ LoadSoftObjectProperty<UPhysicsAsset>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::PhysicsAsset, NCsCommonLoadCached::Str::Physics_Asset, LoadFlags); continue; }
			// UAnimSequence
			if (SoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ LoadSoftObjectProperty<UAnimSequence>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::AnimSequence, NCsCommonLoadCached::Str::Anim_Sequence, LoadFlags); continue; }
			// UAnimMontage
			if (SoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ LoadSoftObjectProperty<UAnimMontage>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::AnimMontage, NCsCommonLoadCached::Str::Anim_Montage, LoadFlags); continue; }
			// UBlendSpace1D
			if (SoftObjectProperty->PropertyClass == UBlendSpace1D::StaticClass())
			{ LoadSoftObjectProperty<UBlendSpace1D>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::BlendSpace1D, NCsCommonLoadCached::Str::Blend_Space_1D, LoadFlags); continue; }
			// UBlendSpace
			if (SoftObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ LoadSoftObjectProperty<UBlendSpace>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::BlendSpace, NCsCommonLoadCached::Str::Blend_Space, LoadFlags); continue; }
			// UAimOffsetBlendSpace
			if (SoftObjectProperty->PropertyClass == UAimOffsetBlendSpace::StaticClass())
			{ LoadSoftObjectProperty<UAimOffsetBlendSpace>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::AimOffsetBlendSpace, NCsCommonLoadCached::Str::Aim_Offset_Blend_Space, LoadFlags); continue; }
			// UAnimBlueprint
			if (SoftObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ LoadSoftObjectProperty_AnimBlueprint(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, LoadFlags); continue; }
			// USoundCue
			if (SoftObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ LoadSoftObjectProperty<USoundCue>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::SoundCue, NCsCommonLoadCached::Str::Sound_Cue, LoadFlags); continue; }
			// UParticleSystem
			if (SoftObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ LoadSoftObjectProperty<UParticleSystem>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::ParticleSystem, NCsCommonLoadCached::Str::Particle_System, LoadFlags); continue; }
			// UCurveFloat
			if (SoftObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ LoadSoftObjectProperty<UCurveFloat>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::CurveFloat, NCsCommonLoadCached::Str::Curve_Float, LoadFlags); continue; }
			// UCurveVector
			if (SoftObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ LoadSoftObjectProperty<UCurveVector>(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, NCsCommonLoadCached::Str::CurveVector, NCsCommonLoadCached::Str::Curve_Vector, LoadFlags); continue; }
			// UBlueprint
			if (SoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{ 
				if (SoftObjectProperty->ArrayDim == CS_SINGLETON)
				{ LoadSoftObjectProperty_Blueprint(SoftObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, LoadFlags); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
					continue;
			}
			continue;
		}
		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			const FString StructName = FString::Printf(TEXT("%s.%s"), *ObjectName, *MemberName);

			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsStaticMesh>(StructProperty, InStruct, StructName, LoadFlags); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsFpvStaticMesh
			if (StructProperty->Struct == FCsFpvStaticMesh::StaticStruct())
			{ LoadMemberStructProperty<FCsFpvStaticMesh>(StructProperty, InStruct, StructName, LoadFlags); continue; }
			// FCsTArrayStaticMesh
			if (StructProperty->Struct == FCsTArrayStaticMesh::StaticStruct())
			{ LoadMemberStructProperty<FCsTArrayStaticMesh>(StructProperty, InStruct, StructName, LoadFlags); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ LoadMemberStructProperty<FCsSkeletalMesh>(StructProperty, InStruct, StructName, LoadFlags); continue; }
			// FCsFpsSkeletalMesh
			if (StructProperty->Struct == FCsFpsSkeletalMesh::StaticStruct())
			{ LoadMemberStructProperty<FCsFpsSkeletalMesh>(StructProperty, InStruct, StructName, LoadFlags); continue; }
			// FCsTArraySkeletalMesh
			if (StructProperty->Struct == FCsTArraySkeletalMesh::StaticStruct())
			{ LoadMemberStructProperty<FCsTArraySkeletalMesh>(StructProperty, InStruct, StructName, LoadFlags); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ LoadMemberStructProperty<FCsMaterialInstance>(StructProperty, InStruct, StructName, LoadFlags); continue; }
			// FCsMaterialInstanceConstant
			if (StructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
			{ LoadMemberStructProperty<FCsMaterialInstanceConstant>(StructProperty, InStruct, StructName, LoadFlags); continue; }
			// FCsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsTArrayMaterialInstanceConstant::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsTArrayMaterialInstanceConstant>(StructProperty, InStruct, StructName, LoadFlags); continue; }
				if (StructProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ LoadMemberFixedArrayStructProperty_EnumSize<FCsTArrayMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(StructProperty, InStruct, StructName, LoadFlags, &ECsInteractiveState::ToString, nullptr); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsFpsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsFpsTArrayMaterialInstanceConstant::StaticStruct())
			{ LoadMemberStructProperty<FCsFpsTArrayMaterialInstanceConstant>(StructProperty, InStruct, StructName, LoadFlags); continue; }
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ LoadMemberStructProperty<FCsAnimSequence>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsFpvAnimSequence
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
			{ LoadMemberStructProperty<FCsFpvAnimSequence>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsAnimMontage>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsFpvAnimMontage
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsFpvAnimMontage>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{ LoadMemberStructProperty<FCsTArrayAnimMontage>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsBlendSpace1D
			if (StructProperty->Struct == FCsBlendSpace1D::StaticStruct())
			{ LoadMemberStructProperty<FCsBlendSpace1D>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsFpvBlendSpace1D
			if (StructProperty->Struct == FCsFpvBlendSpace1D::StaticStruct())
			{ LoadMemberStructProperty<FCsFpvBlendSpace1D>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ LoadMemberStructProperty<FCsBlendSpace>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsFpvBlendSpace
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
			{ LoadMemberStructProperty<FCsFpvBlendSpace>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsAimOffset
			if (StructProperty->Struct == FCsAimOffset::StaticStruct())
			{ LoadMemberStructProperty<FCsAimOffset>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsFpvAimOffset
			if (StructProperty->Struct == FCsFpvAimOffset::StaticStruct())
			{ LoadMemberStructProperty<FCsFpvAimOffset>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ LoadMemberStructProperty<FCsAnimBlueprint>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsFpvAnimBlueprint
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
			{ LoadMemberStructProperty<FCsFpvAnimBlueprint>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsPhysicalMaterial
			if (StructProperty->Struct == FCsPhysicalMaterial::StaticStruct())
			{ LoadMemberStructProperty<FCsPhysicalMaterial>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ LoadMemberStructProperty<FCsPhysicsAsset>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsSoundElement>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsFpvSoundElement
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsFpvSoundElement>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsFxElement>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsFpvFxElement
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsFpvFxElement>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsBlueprint
			if (StructProperty->Struct == FCsBlueprint::StaticStruct())
			{ LoadMemberStructProperty<FCsBlueprint>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsTArrayBlueprint
			if (StructProperty->Struct == FCsTArrayBlueprint::StaticStruct())
			{ LoadMemberStructProperty<FCsTArrayBlueprint>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsCollisionPreset
			if (StructProperty->Struct == FCsCollisionPreset::StaticStruct())
			{ LoadMemberStructProperty<FCsCollisionPreset>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// Weapon_FireMode
			{
				// FCsData_Weapon_FireMode_Firing
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Firing::StaticStruct())
				{ LoadMemberStructProperty<FCsData_Weapon_FireMode_Firing>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				// FCsData_Weapon_FireMode_Animation
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Animation::StaticStruct())
				{ LoadMemberStructProperty<FCsData_Weapon_FireMode_Animation>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				// FCsData_FpsWeapon_FireMode_Animation
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Animation::StaticStruct())
				{ LoadMemberStructProperty<FCsData_FpsWeapon_FireMode_Animation>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				// FCsData_Weapon_FireMode_Scope
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Scope::StaticStruct())
				{ LoadMemberStructProperty<FCsData_Weapon_FireMode_Scope>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				// FCsData_Weapon_FireMode_FXs
				if (StructProperty->Struct == FCsData_Weapon_FireMode_FXs::StaticStruct())
				{ LoadMemberStructProperty<FCsData_Weapon_FireMode_FXs>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				// FCsData_FpsWeapon_FireMode_FXs
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_FXs::StaticStruct())
				{ LoadMemberStructProperty<FCsData_FpsWeapon_FireMode_FXs>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				// FCsData_Weapon_FireMode_Sounds
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Sounds::StaticStruct())
				{ LoadMemberStructProperty<FCsData_Weapon_FireMode_Sounds>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				// FCsData_FpsWeapon_FireMode_Sounds
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Sounds::StaticStruct())
				{ LoadMemberStructProperty<FCsData_FpsWeapon_FireMode_Sounds>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			}
			// FCsData_ProjectileBasePtr
			if (StructProperty->Struct == FCsData_ProjectileBasePtr::StaticStruct())
			{ LoadMemberStructProperty<FCsData_ProjectileBasePtr>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
					continue;
			}
			continue;
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftClassPtr
			if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// TSoftObjectPtr
			if (USoftObjectProperty* InnerSoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerSoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ LoadArraySoftObjectProperty<UStaticMesh>(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("StaticMesh"), TEXT("Static Mesh"), LoadFlags); continue; }
				// USkeletalMesh
				if (InnerSoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ LoadArraySoftObjectProperty<USkeletalMesh>(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("SkeletalMesh"), TEXT("Skeletal Mesh"), LoadFlags); continue; }
				// UMaterialInstance
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ LoadArraySoftObjectProperty<UMaterialInstance>(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("MaterialInstance"), TEXT("Material Instance"), LoadFlags); continue; }
				// UMaterialInstanceConstant
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ LoadArraySoftObjectProperty<UMaterialInstanceConstant>(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("MaterialInstanceConstant"), TEXT("Material Instance Constant"), LoadFlags); continue; }
				// UAnimSequence
				if (InnerSoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ LoadArraySoftObjectProperty<UAnimSequence>(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("AnimSequence"), TEXT("Anim Sequence"), LoadFlags); continue; }
				// UAnimMontage
				if (InnerSoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ LoadArraySoftObjectProperty<UAnimMontage>(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("AnimMontage"), TEXT("Anim Montage"), LoadFlags); continue; }
				// UBlueprint
				if (InnerSoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ LoadArraySoftObjectProperty_Blueprint(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, LoadFlags); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				const FString StructName = FString::Printf(TEXT("%s.%s"), *ObjectName, *MemberName);

				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsAnimMontage>(ArrayProperty, InStruct, StructName, LoadFlags); continue; }
				// FCsFxElement
				if (InnerStructProperty->Struct == FCsFxElement::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFxElement>(ArrayProperty, InStruct, StructName, LoadFlags); continue; }
				// FCsFpvFxElement
				if (InnerStructProperty->Struct == FCsFpvFxElement::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFpvFxElement>(ArrayProperty, InStruct, StructName, LoadFlags); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsSoundElement>(ArrayProperty, InStruct, StructName, LoadFlags); continue; }
				// FCsFpvSoundElement
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFpvSoundElement>(ArrayProperty, InStruct, StructName, LoadFlags); continue; }
				// FCsAnimSequence
				if (InnerStructProperty->Struct == FCsAnimSequence::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsAnimSequence>(ArrayProperty, InStruct, StructName, LoadFlags); continue; }
				// FCsFpvAnimSequence
				if (InnerStructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFpvAnimSequence>(ArrayProperty, InStruct, StructName, LoadFlags); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsAnimMontage>(ArrayProperty, InStruct, StructName, LoadFlags); continue; }
				// FCsFpvAnimMontage
				if (InnerStructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFpvAnimMontage>(ArrayProperty, InStruct, StructName, LoadFlags); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			continue;
		}
		// Map
		if (UMapProperty* MapProperty = Cast<UMapProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
					continue;
			}
			continue;
		}
	}
}

//#if PLATFORM_WINDOWS
//#pragma optimize("", off)
//#endif // #if PLATFORM_WINDOWS
void UCsCommon_Load::LoadObjectWithTSoftObjectPtrs(const FString &ObjectName, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TCsLoadObjectWithTSoftObjectPtrs_Internal Internal /*=nullptr*/)
{
	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
					continue;
			}
			continue;
		}
		// TSoftObjectPtr
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(*It))
		{
			// UStaticMesh
			if (SoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ LoadSoftObjectProperty<UStaticMesh>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("StaticMesh"), TEXT("Static Mesh"), LoadFlags); continue; }
			// USkeletalMesh
			if (SoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ LoadSoftObjectProperty<USkeletalMesh>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("SkeletalMesh"), TEXT("Skeletal Mesh"), LoadFlags); continue; }
			// UMaterialInstance
			if (SoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ LoadSoftObjectProperty<UMaterialInstance>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("MaterialInstance"), TEXT("Material Instance"), LoadFlags); continue; }
			// UMaterialInstanceConstant
			if (SoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{ LoadSoftObjectProperty<UMaterialInstanceConstant>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("MaterialInstanceConstant"), TEXT("Material Instance Constant"), LoadFlags); continue; }
			// UPhysicalMaterial
			if (SoftObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ LoadSoftObjectProperty<UPhysicalMaterial>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("PhysicalMaterial"), TEXT("Physical Material"), LoadFlags); continue; }
			// UPhysicsAsset
			if (SoftObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ LoadSoftObjectProperty<UPhysicsAsset>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("PhysicsAsset"), TEXT("Physics Asset"), LoadFlags); continue; }
			// UAnimSequence
			if (SoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ LoadSoftObjectProperty<UAnimSequence>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("AnimSequence"), TEXT("Anim Sequence"), LoadFlags); continue; }
			// UAnimMontage
			if (SoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ LoadSoftObjectProperty<UAnimMontage>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("AnimMontage"), TEXT("Anim Montage"), LoadFlags); continue; }
			// UBlendSpace
			if (SoftObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ LoadSoftObjectProperty<UBlendSpace>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("BlendSpace"), TEXT("Blend Space"), LoadFlags); continue; }
			// UAnimBlueprint
			if (SoftObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ LoadSoftObjectProperty_AnimBlueprint(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, LoadFlags); continue; }
			// USoundCue
			if (SoftObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ LoadSoftObjectProperty<USoundCue>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("SoundCue"), TEXT("Sound Cue"), LoadFlags); continue; }
			// UParticleSystem
			if (SoftObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ LoadSoftObjectProperty<UParticleSystem>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("ParticleSystem"), TEXT("Particle System"), LoadFlags); continue; }
			// UCurveFloat
			if (SoftObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ LoadSoftObjectProperty<UCurveFloat>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("CurveFloat"), TEXT("Curve Float"), LoadFlags); continue; }
			// UCurveVector
			if (SoftObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ LoadSoftObjectProperty<UCurveVector>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("CurveVector"), TEXT("Curve Vector"), LoadFlags); continue; }
			// UBlueprint
			if (SoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{
				if (SoftObjectProperty->ArrayDim == CS_SINGLETON)
				{ LoadSoftObjectProperty_Blueprint(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, LoadFlags); continue; }
			}

			if (Internal)
			{
				if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
					continue;
			}
			continue;
		}
		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			const FString StructName = FString::Printf(TEXT("%s.%s"), *ObjectName, *MemberName);

			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsStaticMesh>(StructProperty, InObject, StructName, LoadFlags); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsFpvStaticMesh
			if (StructProperty->Struct == FCsFpvStaticMesh::StaticStruct())
			{ LoadMemberStructProperty<FCsFpvStaticMesh>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsTArrayStaticMesh
			if (StructProperty->Struct == FCsTArrayStaticMesh::StaticStruct())
			{ LoadMemberStructProperty<FCsTArrayStaticMesh>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ LoadMemberStructProperty<FCsSkeletalMesh>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsFpsSkeletalMesh
			if (StructProperty->Struct == FCsFpsSkeletalMesh::StaticStruct())
			{ LoadMemberStructProperty<FCsFpsSkeletalMesh>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsTArraySkeletalMesh
			if (StructProperty->Struct == FCsTArraySkeletalMesh::StaticStruct())
			{ LoadMemberStructProperty<FCsTArraySkeletalMesh>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ LoadMemberStructProperty<FCsMaterialInstance>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsMaterialInstanceConstant
			if (StructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
			{ LoadMemberStructProperty<FCsMaterialInstanceConstant>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsTArrayMaterialInstanceConstant::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsTArrayMaterialInstanceConstant>(StructProperty, InObject, StructName, LoadFlags); continue; }
				if (StructProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ LoadMemberFixedArrayStructProperty_EnumSize<FCsTArrayMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(StructProperty, InObject, StructName, LoadFlags, &ECsInteractiveState::ToString, nullptr); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsFpsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsFpsTArrayMaterialInstanceConstant::StaticStruct())
			{ LoadMemberStructProperty<FCsFpsTArrayMaterialInstanceConstant>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsInteractiveMaterials
			if (StructProperty->Struct == FCsInteractiveMaterials::StaticStruct())
			{ LoadMemberStructProperty<FCsInteractiveMaterials>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsPhysicalMaterial
			if (StructProperty->Struct == FCsPhysicalMaterial::StaticStruct())
			{ LoadMemberStructProperty<FCsPhysicalMaterial>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ LoadMemberStructProperty<FCsPhysicsAsset>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsCollisionPreset
			if (StructProperty->Struct == FCsCollisionPreset::StaticStruct())
			{ LoadMemberStructProperty<FCsCollisionPreset>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsCurveFloat
			if (StructProperty->Struct == FCsCurveFloat::StaticStruct())
			{ LoadMemberStructProperty<FCsCurveFloat>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ LoadMemberStructProperty<FCsCurveVector>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsSoundElement>(StructProperty, InObject, StructName, LoadFlags); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsFpvSoundElement
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsFpvSoundElement>(StructProperty, InObject, StructName, LoadFlags); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsParticleSystem
			if (StructProperty->Struct == FCsParticleSystem::StaticStruct())
			{ LoadMemberStructProperty<FCsParticleSystem>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsFxElement>(StructProperty, InObject, StructName, LoadFlags); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsFpvFxElement
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsFpvFxElement>(StructProperty, InObject, StructName, LoadFlags); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ LoadMemberStructProperty<FCsAnimSequence>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsFpvAnimSequence
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
			{ LoadMemberStructProperty<FCsFpvAnimSequence>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{ LoadMemberStructProperty<FCsAnimMontage>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsFpvAnimMontage
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
			{ LoadMemberStructProperty<FCsFpvAnimMontage>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{ LoadMemberStructProperty<FCsTArrayAnimMontage>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ LoadMemberStructProperty<FCsAnimBlueprint>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsFpvAnimBlueprint
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
			{ LoadMemberStructProperty<FCsFpvAnimBlueprint>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsBlendSpace1D
			if (StructProperty->Struct == FCsBlendSpace1D::StaticStruct())
			{ LoadMemberStructProperty<FCsBlendSpace1D>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsFpvBlendSpace1D
			if (StructProperty->Struct == FCsFpvBlendSpace1D::StaticStruct())
			{ LoadMemberStructProperty<FCsFpvBlendSpace1D>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ LoadMemberStructProperty<FCsBlendSpace>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsFpvBlendSpace
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
			{ LoadMemberStructProperty<FCsFpvBlendSpace>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsAimOffset
			if (StructProperty->Struct == FCsAimOffset::StaticStruct())
			{ LoadMemberStructProperty<FCsAimOffset>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsFpvAimOffset
			if (StructProperty->Struct == FCsFpvAimOffset::StaticStruct())
			{ LoadMemberStructProperty<FCsFpvAimOffset>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsBlueprint
			if (StructProperty->Struct == FCsBlueprint::StaticStruct())
			{ LoadMemberStructProperty<FCsBlueprint>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsTArrayBlueprint
			if (StructProperty->Struct == FCsTArrayBlueprint::StaticStruct())
			{ LoadMemberStructProperty<FCsTArrayBlueprint>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsWidgetComponentInfo
			if (StructProperty->Struct == FCsWidgetComponentInfo::StaticStruct())
			{ LoadMemberStructProperty<FCsWidgetComponentInfo>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsWidgetActorInfo
			if (StructProperty->Struct == FCsWidgetActorInfo::StaticStruct())
			{ LoadMemberStructProperty<FCsWidgetActorInfo>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsData_ProjectileImpactPtr
			if (StructProperty->Struct == FCsData_ProjectileImpactPtr::StaticStruct())
			{ LoadMemberStructProperty<FCsData_ProjectileImpactPtr>(StructProperty, InObject, StructName, LoadFlags, nullptr); continue; }
			// FCsDamageFalloff
			if (StructProperty->Struct == FCsDamageFalloff::StaticStruct())
			{ LoadMemberStructProperty<FCsDamageFalloff>(StructProperty, InObject, StructName, LoadFlags, nullptr); continue; }
			// FCsDamageRadial
			if (StructProperty->Struct == FCsDamageRadial::StaticStruct())
			{ LoadMemberStructProperty<FCsDamageRadial>(StructProperty, InObject, StructName, LoadFlags, nullptr); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
					continue;
			}
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftClassPtr
			if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
						continue;
				}
				continue;
			}
			// TSoftObjectPtr
			if (USoftObjectProperty* InnerSoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerSoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ LoadArraySoftObjectProperty<UStaticMesh>(ArrayProperty, ObjectName, InObject, InClass, MemberName, TEXT("StaticMesh"), TEXT("Static Mesh"), LoadFlags); continue; }
				// USkeletalMesh
				if (InnerSoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ LoadArraySoftObjectProperty<USkeletalMesh>(ArrayProperty, ObjectName, InObject, InClass, MemberName, TEXT("SkeletalMesh"), TEXT("Skeletal Mesh"), LoadFlags); continue; }
				// UMaterialInstance
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ LoadArraySoftObjectProperty<UMaterialInstance>(ArrayProperty, ObjectName, InObject, InClass, MemberName, TEXT("MaterialInstance"), TEXT("Material Instance"), LoadFlags); continue; }
				// UMaterialInstanceConstant
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ LoadArraySoftObjectProperty<UMaterialInstanceConstant>(ArrayProperty, ObjectName, InObject, InClass, MemberName, TEXT("MaterialInstanceConstant"), TEXT("Material Instance Constant"), LoadFlags); continue; }
				// UAnimSequence
				if (InnerSoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ LoadArraySoftObjectProperty<UAnimSequence>(ArrayProperty, ObjectName, InObject, InClass, MemberName, TEXT("AnimSequence"), TEXT("Anim Sequence"), LoadFlags); continue; }
				// UAnimMontage
				if (InnerSoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ LoadArraySoftObjectProperty<UAnimMontage>(ArrayProperty, ObjectName, InObject, InClass, MemberName, TEXT("AnimMontage"), TEXT("Anim Montage"), LoadFlags); continue; }
				// UBlueprint
				if (InnerSoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ LoadArraySoftObjectProperty_Blueprint(ArrayProperty, ObjectName, InObject, InClass, MemberName, LoadFlags); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
						continue;
				}
				continue;
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				const FString StructName = FString::Printf(TEXT("%s.%s"), *ObjectName, *MemberName);

				// FCsMaterialInstance
				if (InnerStructProperty->Struct == FCsMaterialInstance::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsMaterialInstance>(ArrayProperty, InObject, StructName, LoadFlags); continue; }
				// FCsMaterialInstanceConstant
				if (InnerStructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsMaterialInstanceConstant>(ArrayProperty, InObject, StructName, LoadFlags); continue; }
				// FCsFpvFxElement
				if (InnerStructProperty->Struct == FCsFpvFxElement::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFpvFxElement>(ArrayProperty, InObject, StructName, LoadFlags); continue; }
				// FCsFpvSoundElement
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFpvSoundElement>(ArrayProperty, InObject, StructName, LoadFlags); continue; }
				// FCsAnimSequence
				if (InnerStructProperty->Struct == FCsAnimSequence::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsAnimSequence>(ArrayProperty, InObject, StructName, LoadFlags); continue; }
				// FCsFpvAnimSequence
				if (InnerStructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFpvAnimSequence>(ArrayProperty, InObject, StructName, LoadFlags); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsAnimMontage>(ArrayProperty, InObject, StructName, LoadFlags); continue; }
				// FCsFpvAnimMontage
				if (InnerStructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFpvAnimMontage>(ArrayProperty, InObject, StructName, LoadFlags); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
						continue;
				}
				continue;
			}
		}
		// Map
		if (UMapProperty* MapProperty = Cast<UMapProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
					continue;
			}
			continue;
		}
	}
}
//#if PLATFORM_WINDOWS
//#pragma optimize("", on)
//#endif // #if PLATFORM_WINDOWS

#pragma endregion Load

	// UnLoad
#pragma region

void UCsCommon_Load::UnLoadStructWithTSoftObjectPtrs(void* InStruct, UScriptStruct* const &InScriptStruct)
{
	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// UClass
		if (UClassProperty* ClassProperty = Cast<UClassProperty>(*It))
		{
			if (!MemberName.Contains(TEXT("_Internal")))
				continue;

			// AShooterWeaponData
			//if (ClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || ClassProperty->MetaClass == AShooterWeaponData::StaticClass())
			//{ UnLoadClassProperty<AShooterWeaponData>(ClassProperty, InStruct); continue; }
			continue;
		}
		// UObject
		if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(*It))
		{
			if (!MemberName.Contains(TEXT("_Internal")))
				continue;

			// UStaticMesh
			if (ObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ UnLoadObjectProperty<UStaticMesh>(ObjectProperty, InStruct); continue; }
			// USkeletalMesh
			if (ObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ UnLoadObjectProperty<USkeletalMesh>(ObjectProperty, InStruct); continue; }
			// UMaterialInstance
			if (ObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ UnLoadObjectProperty<UMaterialInstance>(ObjectProperty, InStruct); continue; }
			// UMaterialInstanceConstant
			if (ObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{ UnLoadObjectProperty<UMaterialInstanceConstant>(ObjectProperty, InStruct); continue; }
			// UPhysicsAsset
			if (ObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ UnLoadObjectProperty<UPhysicsAsset>(ObjectProperty, InStruct); continue; }
			// UAnimSequence
			if (ObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ UnLoadObjectProperty<UAnimSequence>(ObjectProperty, InStruct); continue; }
			// UAnimMontage
			if (ObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ UnLoadObjectProperty<UAnimMontage>(ObjectProperty, InStruct); continue; }
			// UBlendSpace
			if (ObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ UnLoadObjectProperty<UBlendSpace>(ObjectProperty, InStruct); continue; }
			// UAnimBlueprintGeneratedClass
			if (ObjectProperty->PropertyClass == UAnimBlueprintGeneratedClass::StaticClass())
			{ UnLoadObjectProperty<UAnimBlueprintGeneratedClass>(ObjectProperty, InStruct); continue; }
			// USoundCue
			if (ObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ UnLoadObjectProperty<USoundCue>(ObjectProperty, InStruct); continue; }
			// UParticleSystem
			if (ObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ UnLoadObjectProperty<UParticleSystem>(ObjectProperty, InStruct); continue; }
			continue;
		}
		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{ UnLoadMemberStructProperty<FCsStaticMesh>(StructProperty, InStruct); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ UnLoadMemberStructProperty<FCsSkeletalMesh>(StructProperty, InStruct); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ UnLoadMemberStructProperty<FCsMaterialInstance>(StructProperty, InStruct); continue; }
			// FCsMaterialInstanceConstant
			if (StructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
			{ UnLoadMemberStructProperty<FCsMaterialInstanceConstant>(StructProperty, InStruct); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ UnLoadMemberStructProperty<FCsPhysicsAsset>(StructProperty, InStruct); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ UnLoadMemberStructProperty<FCsSoundElement>(StructProperty, InStruct); continue; }
				continue;
			}
			// FCsFpvSoundElement
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ UnLoadMemberStructProperty<FCsFpvSoundElement>(StructProperty, InStruct); continue; }
				continue;
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ UnLoadMemberStructProperty<FCsFxElement>(StructProperty, InStruct); continue; }
				continue;
			}
			// FCsFpvFxElement
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ UnLoadMemberStructProperty<FCsFpvFxElement>(StructProperty, InStruct); continue; }
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ UnLoadMemberStructProperty<FCsAnimSequence>(StructProperty, InStruct); continue; }
			// FCsFpvAnimSequence
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpvAnimSequence>(StructProperty, InStruct); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{ UnLoadMemberStructProperty<FCsAnimMontage>(StructProperty, InStruct); continue; }
			// FCsFpvAnimMontage
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpvAnimMontage>(StructProperty, InStruct); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ UnLoadMemberStructProperty<FCsAnimBlueprint>(StructProperty, InStruct); continue; }
			// FCsFpvAnimBlueprint
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpvAnimBlueprint>(StructProperty, InStruct); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ UnLoadMemberStructProperty<FCsBlendSpace>(StructProperty, InStruct); continue; }
			// FCsFpvBlendSpace
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpvBlendSpace>(StructProperty, InStruct); continue; }
			continue;
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftClassPtr
			if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				if (!MemberName.Contains(TEXT("_Internal")))
					continue;

				// AShooterWeaponData
				//if (InnerSoftClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerSoftClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//{ UnLoadArrayObjectProperty<AShooterWeaponData>(ArrayProperty, InStruct); continue; }
				continue;
			}
			// TSoftObjectPtr
			if (UObjectProperty* InnerObjectProperty = Cast<UObjectProperty>(ArrayProperty->Inner))
			{
				if (!MemberName.Contains(TEXT("_Internal")))
					continue;

				// UMaterialInstance
				if (InnerObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ UnLoadArrayObjectProperty<UMaterialInstance>(ArrayProperty, InStruct); continue; }
				// UMaterialInstanceConstant
				if (InnerObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ UnLoadArrayObjectProperty<UMaterialInstanceConstant>(ArrayProperty, InStruct); continue; }
				// UAnimSequence
				if (InnerObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ UnLoadArrayObjectProperty<UAnimSequence>(ArrayProperty, InStruct); continue; }
				// UAnimMontage
				if (InnerObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ UnLoadArrayObjectProperty<UAnimMontage>(ArrayProperty, InStruct); continue; }
				continue;
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FCsMaterialInstance
				if (InnerStructProperty->Struct == FCsMaterialInstance::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsMaterialInstance>(ArrayProperty, InStruct); continue; }
				// FCsMaterialInstanceConstant
				if (InnerStructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsMaterialInstanceConstant>(ArrayProperty, InStruct); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsAnimMontage>(ArrayProperty, InStruct); continue; }
				// FCsFpvAnimMontage
				if (InnerStructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsFpvAnimMontage>(ArrayProperty, InStruct); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsSoundElement>(ArrayProperty, InStruct); continue; }
				// FCsFpvSoundElement
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsFpvSoundElement>(ArrayProperty, InStruct); continue; }
				continue;
			}
			continue;
		}
	}
}

void UCsCommon_Load::UnLoadObjectWithTSoftObjectPtrs(void* InObject, UClass* const &InClass)
{
	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// UClass
		if (UClassProperty* ClassProperty = Cast<UClassProperty>(*It))
		{
			if (!MemberName.Contains(TEXT("_Internal")))
				continue;

			// AShooterWeaponData
			//if (ClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || ClassProperty->MetaClass == AShooterWeaponData::StaticClass())
			//{ UnLoadClassProperty<AShooterWeaponData>(ClassProperty, InObject); continue; }
			continue;
		}
		// UObject
		if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(*It))
		{
			if (!MemberName.Contains(TEXT("_Internal")))
				continue;

			// UStaticMesh
			if (ObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ UnLoadObjectProperty<UStaticMesh>(ObjectProperty, InObject); continue; }
			// USkeletalMesh
			if (ObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ UnLoadObjectProperty<USkeletalMesh>(ObjectProperty, InObject); continue; }
			// UMaterialInstance
			if (ObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ UnLoadObjectProperty<UMaterialInstance>(ObjectProperty, InObject); continue; }
			// UPhysicsAsset
			if (ObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ UnLoadObjectProperty<UPhysicsAsset>(ObjectProperty, InObject); continue; }
			// UAnimSequence
			if (ObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ UnLoadObjectProperty<UAnimSequence>(ObjectProperty, InObject); continue; }
			// UAnimMontage
			if (ObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ UnLoadObjectProperty<UAnimMontage>(ObjectProperty, InObject); continue; }
			// UBlendSpace
			if (ObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ UnLoadObjectProperty<UBlendSpace>(ObjectProperty, InObject); continue; }
			// UAnimBlueprintGeneratedClass
			if (ObjectProperty->PropertyClass == UAnimBlueprintGeneratedClass::StaticClass())
			{ UnLoadObjectProperty<UAnimBlueprintGeneratedClass>(ObjectProperty, InObject); continue; }
			// USoundCue
			if (ObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ UnLoadObjectProperty<USoundCue>(ObjectProperty, InObject); continue; }
			// UParticleSystem
			if (ObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ UnLoadObjectProperty<UParticleSystem>(ObjectProperty, InObject); continue; }
			continue;
		}
		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{ UnLoadMemberStructProperty<FCsStaticMesh>(StructProperty, InObject); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ UnLoadMemberStructProperty<FCsSkeletalMesh>(StructProperty, InObject); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ UnLoadMemberStructProperty<FCsMaterialInstance>(StructProperty, InObject); continue; }
			// FCsMaterialInstanceConstant
			if (StructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
			{ UnLoadMemberStructProperty<FCsMaterialInstanceConstant>(StructProperty, InObject); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ UnLoadMemberStructProperty<FCsPhysicsAsset>(StructProperty, InObject); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ UnLoadMemberStructProperty<FCsSoundElement>(StructProperty, InObject); continue; }
				continue;
			}
			// FCsFpvSoundElement
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ UnLoadMemberStructProperty<FCsFpvSoundElement>(StructProperty, InObject); continue; }
				continue;
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ UnLoadMemberStructProperty<FCsFxElement>(StructProperty, InObject); continue; }
				continue;
			}
			// FCsFpvFxElement
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ UnLoadMemberStructProperty<FCsFpvFxElement>(StructProperty, InObject); continue; }
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ UnLoadMemberStructProperty<FCsAnimSequence>(StructProperty, InObject); continue; }
			// FCsFpvAnimSequence
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpvAnimSequence>(StructProperty, InObject); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{ UnLoadMemberStructProperty<FCsAnimMontage>(StructProperty, InObject); continue; }
			// FCsFpvAnimMontage
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpvAnimMontage>(StructProperty, InObject); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ UnLoadMemberStructProperty<FCsAnimBlueprint>(StructProperty, InObject); continue; }
			// FCsFpvAnimBlueprint
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpvAnimBlueprint>(StructProperty, InObject); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ UnLoadMemberStructProperty<FCsBlendSpace>(StructProperty, InObject); continue; }
			// FCsFpvBlendSpace
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpvBlendSpace>(StructProperty, InObject); continue; }
			continue;
		}
		// Array
		else
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftClassPtr
			if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				if (!MemberName.Contains(TEXT("_Internal")))
					continue;

				// AShooterWeaponData
				//if (InnerSoftClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerSoftClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//{ UnLoadArrayObjectProperty<AShooterWeaponData>(ArrayProperty, InObject); continue; }
			}
			// TSoftObjectPtr
			if (UObjectProperty* InnerObjectProperty = Cast<UObjectProperty>(ArrayProperty->Inner))
			{
				if (!MemberName.Contains(TEXT("_Internal")))
					continue;

				// UMaterialInstance
				if (InnerObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ UnLoadArrayObjectProperty<UMaterialInstance>(ArrayProperty, InObject); continue; }
				// UMaterialInstanceConstant
				if (InnerObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ UnLoadArrayObjectProperty<UMaterialInstanceConstant>(ArrayProperty, InObject); continue; }
				// UAnimSequence
				if (InnerObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ UnLoadArrayObjectProperty<UAnimSequence>(ArrayProperty, InObject); continue; }
				// UAnimMontage
				if (InnerObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ UnLoadArrayObjectProperty<UAnimMontage>(ArrayProperty, InObject); continue; }
				continue;
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FCsMaterialInstance
				if (InnerStructProperty->Struct == FCsMaterialInstance::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsMaterialInstance>(ArrayProperty, InObject); continue; }
				// FCsMaterialInstanceConstant
				if (InnerStructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsMaterialInstanceConstant>(ArrayProperty, InObject); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsAnimMontage>(ArrayProperty, InObject); continue; }
				// FCsFpvAnimMontage
				if (InnerStructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsFpvAnimMontage>(ArrayProperty, InObject); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsSoundElement>(ArrayProperty, InObject); continue; }
				// FCsFpvSoundElement
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsFpvSoundElement>(ArrayProperty, InObject); continue; }
				continue;
			}
		}
	}
}

#pragma endregion UnLoad

	// IsLoaded
#pragma region

bool UCsCommon_Load::IsLoadedStructWithTSoftObjectPtrs(const FString &ObjectName, void* InStruct, UScriptStruct* const &InScriptStruct)
{
	bool Pass = true;

	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// UClass
		if (UClassProperty* ClassProperty = Cast<UClassProperty>(*It))
		{
			if (!MemberName.Contains(TEXT("_Internal")))
				continue;

			// AShooterWeaponData
			//if (ClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || ClassProperty->MetaClass == AShooterWeaponData::StaticClass())
			//	Pass &= IsLoadedClassProperty<AShooterWeaponData>(ClassProperty, InStruct, MemberName);
		}
		// UObject
		else
		if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(*It))
		{
			if (!MemberName.Contains(TEXT("_Internal")))
				continue;

			// UStaticMesh
			if (ObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				Pass &= IsLoadedObjectProperty<UStaticMesh>(ObjectProperty, InStruct, MemberName);
			// USkeletalMesh
			if (ObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				Pass &= IsLoadedObjectProperty<USkeletalMesh>(ObjectProperty, InStruct, MemberName);
			// UMaterialInstance
			else
			if (ObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				Pass &= IsLoadedObjectProperty<UMaterialInstance>(ObjectProperty, InStruct, MemberName);
			// UPhysicsAsset
			else
			if (ObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
				Pass &= IsLoadedObjectProperty<UPhysicsAsset>(ObjectProperty, InStruct, MemberName);
			// UAnimSequence
			else
			if (ObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				Pass &= IsLoadedObjectProperty<UAnimSequence>(ObjectProperty, InStruct, MemberName);
			// UAnimMontage
			else
			if (ObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				Pass &= IsLoadedObjectProperty<UAnimMontage>(ObjectProperty, InStruct, MemberName);
			// UBlendSpace
			else
			if (ObjectProperty->PropertyClass == UBlendSpace::StaticClass())
				Pass &= IsLoadedObjectProperty<UBlendSpace>(ObjectProperty, InStruct, MemberName);
			// UAnimBlueprintGeneratedClass
			else
			if (ObjectProperty->PropertyClass == UAnimBlueprintGeneratedClass::StaticClass())
				Pass &= IsLoadedObjectProperty<UAnimBlueprintGeneratedClass>(ObjectProperty, InStruct, MemberName);
			// USoundCue
			else
			if (ObjectProperty->PropertyClass == USoundCue::StaticClass())
				Pass &= IsLoadedObjectProperty<USoundCue>(ObjectProperty, InStruct, MemberName);
			// UParticleSystem
			else
			if (ObjectProperty->PropertyClass == UParticleSystem::StaticClass())
				Pass &= IsLoadedObjectProperty<UParticleSystem>(ObjectProperty, InStruct, MemberName);
		}
		// Structs
		else
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			const FString StructName = FString::Printf(TEXT("%s%s."), *ObjectName, *MemberName);

			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsAnimSequence>(StructProperty, InStruct, StructName);
			// FCsFpvAnimSequence
			else
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpvAnimSequence>(StructProperty, InStruct, StructName);
			// FCsAnimMontage
			else
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsAnimMontage>(StructProperty, InStruct, StructName);
			}
			// FCsFpvAnimMontage
			else
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpvAnimMontage>(StructProperty, InStruct, StructName);
			// FCsBlendSpace
			else
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsBlendSpace>(StructProperty, InStruct, StructName);
			// FCsFpvBlendSpace
			else
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpvBlendSpace>(StructProperty, InStruct, StructName);
			// FCsAnimBlueprint
			else
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsAnimBlueprint>(StructProperty, InStruct, StructName);
			// FCsFpvAnimBlueprint
			else
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpvAnimBlueprint>(StructProperty, InStruct, StructName);
			// FCsSoundElement
			else
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsSoundElement>(StructProperty, InStruct, StructName);
			}
			// FCsFpvSoundElement
			else
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsFpvSoundElement>(StructProperty, InStruct, StructName);
			}
			// FCsFxElement
			else
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsFxElement>(StructProperty, InStruct, StructName);
			}
			// FCsFpvFxElement
			else
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsFpvFxElement>(StructProperty, InStruct, StructName);
			}
		}
		// Array
		else
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftClassPtr
			if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				if (!MemberName.Contains(TEXT("_Internal")))
					continue;

				// AShooterWeaponData
				//if (InnerSoftClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerSoftClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//	Pass &= IsLoadedArrayObjectProperty<AShooterWeaponData>(ArrayProperty, InStruct, MemberName);
			}
			// TSoftObjectPtr
			else
			if (UObjectProperty* InnerObjectProperty = Cast<UObjectProperty>(ArrayProperty->Inner))
			{
				if (!MemberName.Contains(TEXT("_Internal")))
					continue;

				// UAnimSequence
				if (InnerObjectProperty->PropertyClass == UAnimSequence::StaticClass())
					Pass &= IsLoadedArrayObjectProperty<UAnimSequence>(ArrayProperty, InStruct, MemberName);
				// UAnimMontage
				else
				if (InnerObjectProperty->PropertyClass == UAnimMontage::StaticClass())
					Pass &= IsLoadedArrayObjectProperty<UAnimMontage>(ArrayProperty, InStruct, MemberName);
			}
			// Struct
			else
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				const FString StructName = FString::Printf(TEXT("%s%s."), *ObjectName, *MemberName);

				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
					Pass &= IsLoadedMemberArrayStructProperty<FCsAnimMontage>(ArrayProperty, InStruct, StructName);
				// FCsSoundElement
				else
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
					Pass &= IsLoadedMemberArrayStructProperty<FCsSoundElement>(ArrayProperty, InStruct, StructName);
				// FCsFpvSoundElement
				else
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
					Pass &= IsLoadedMemberArrayStructProperty<FCsFpvSoundElement>(ArrayProperty, InStruct, StructName);
			}
		}
	}
	return Pass;
}

bool UCsCommon_Load::IsLoadedObjectWithTSoftObjectPtrs(const FString &ObjectName, void* InObject, UClass* const &InClass)
{
	bool Pass = true;

	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// UClass
		if (UClassProperty* ClassProperty = Cast<UClassProperty>(*It))
		{
			if (!MemberName.Contains(TEXT("_Internal")))
				continue;

			// AShooterWeaponData
			//if (ClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || ClassProperty->MetaClass == AShooterWeaponData::StaticClass())
			//	Pass &= IsLoadedClassProperty<AShooterWeaponData>(ClassProperty, InObject, MemberName);
		}
		// UObject
		else
		if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(*It))
		{
			if (!MemberName.Contains(TEXT("_Internal")))
				continue;

			// UStaticMesh
			if (ObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				Pass &= IsLoadedObjectProperty<UStaticMesh>(ObjectProperty, InObject, MemberName);
			// USkeletalMesh
			if (ObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				Pass &= IsLoadedObjectProperty<USkeletalMesh>(ObjectProperty, InObject, MemberName);
			// UMaterialInstance
			else
			if (ObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				Pass &= IsLoadedObjectProperty<UMaterialInstance>(ObjectProperty, InObject, MemberName);
			// UPhysicsAsset
			else
			if (ObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
				Pass &= IsLoadedObjectProperty<UPhysicsAsset>(ObjectProperty, InObject, MemberName);
			// UAnimSequence
			else
			if (ObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				Pass &= IsLoadedObjectProperty<UAnimSequence>(ObjectProperty, InObject, MemberName);
			// UAnimMontage
			else
			if (ObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				Pass &= IsLoadedObjectProperty<UAnimMontage>(ObjectProperty, InObject, MemberName);
			// UBlendSpace
			else
			if (ObjectProperty->PropertyClass == UBlendSpace::StaticClass())
				Pass &= IsLoadedObjectProperty<UBlendSpace>(ObjectProperty, InObject, MemberName);
			// UAnimBlueprintGeneratedClass
			else
			if (ObjectProperty->PropertyClass == UAnimBlueprintGeneratedClass::StaticClass())
				Pass &= IsLoadedObjectProperty<UAnimBlueprintGeneratedClass>(ObjectProperty, InObject, MemberName);
			// USoundCue
			else
			if (ObjectProperty->PropertyClass == USoundCue::StaticClass())
				Pass &= IsLoadedObjectProperty<USoundCue>(ObjectProperty, InObject, MemberName);
			// UParticleSystem
			else
			if (ObjectProperty->PropertyClass == UParticleSystem::StaticClass())
				Pass &= IsLoadedObjectProperty<UParticleSystem>(ObjectProperty, InObject, MemberName);
		}
		// Structs
		else
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			const FString StructName = FString::Printf(TEXT("%s%s."), *ObjectName, *MemberName);

			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsAnimSequence>(StructProperty, InObject, StructName);
			// FCsFpvAnimSequence
			else
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpvAnimSequence>(StructProperty, InObject, StructName);
			// FCsAnimMontage
			else
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsAnimMontage>(StructProperty, InObject, StructName);
			}
			// FCsFpvAnimMontage
			else
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpvAnimMontage>(StructProperty, InObject, StructName);
			// FCsBlendSpace
			else
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsBlendSpace>(StructProperty, InObject, StructName);
			// FCsFpvBlendSpace
			else
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpvBlendSpace>(StructProperty, InObject, StructName);
			// FCsAnimBlueprint
			else
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsAnimBlueprint>(StructProperty, InObject, StructName);
			// FCsFpvAnimBlueprint
			else
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpvAnimBlueprint>(StructProperty, InObject, StructName);
			// FCsSoundElement
			else
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsSoundElement>(StructProperty, InObject, StructName);
			}
			// FCsFpvSoundElement
			else
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsFpvSoundElement>(StructProperty, InObject, StructName);
			}
			// FCsFxElement
			else
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsFxElement>(StructProperty, InObject, StructName);
			}
			// FCsFpvFxElement
			else
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsFpvFxElement>(StructProperty, InObject, StructName);
			}
		}
		// Array
		else
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftClassPtr
			if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				if (!MemberName.Contains(TEXT("_Internal")))
					continue;

				// AShooterWeaponData
				//if (InnerSoftClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerSoftClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//	Pass &= IsLoadedArrayObjectProperty<AShooterWeaponData>(ArrayProperty, InObject, MemberName);
			}
			// TSoftObjectPtr
			else
			if (UObjectProperty* InnerObjectProperty = Cast<UObjectProperty>(ArrayProperty->Inner))
			{
				if (!MemberName.Contains(TEXT("_Internal")))
					continue;

				// UAnimSequence
				if (InnerObjectProperty->PropertyClass == UAnimSequence::StaticClass())
					Pass &= IsLoadedArrayObjectProperty<UAnimSequence>(ArrayProperty, InObject, MemberName);
				// UAnimMontage
				else
				if (InnerObjectProperty->PropertyClass == UAnimMontage::StaticClass())
					Pass &= IsLoadedArrayObjectProperty<UAnimMontage>(ArrayProperty, InObject, MemberName);
			}
			// Struct
			else
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				const FString StructName = FString::Printf(TEXT("%s%s."), *ObjectName, *MemberName);

				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
					Pass &= IsLoadedMemberArrayStructProperty<FCsAnimMontage>(ArrayProperty, InObject, StructName);
				// FCsSoundElement
				else
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
					Pass &= IsLoadedMemberArrayStructProperty<FCsSoundElement>(ArrayProperty, InObject, StructName);
				// FCsFpvSoundElement
				else
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
					Pass &= IsLoadedMemberArrayStructProperty<FCsFpvSoundElement>(ArrayProperty, InObject, StructName);
			}
		}
	}
	return Pass;
}

void UCsCommon_Load::IsLoaded_LogMessages(const FString &DataName, TArray<FString>& OutMessages)
{
	const int32 Count = OutMessages.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		UE_LOG(LogLoad, Warning, TEXT("IsLoaded (%s): %s"), *DataName, *OutMessages[I]);
	}
	OutMessages.Reset();
}

#pragma endregion IsLoaded

TCsLoadAsyncOrder UCsCommon_Load::GetLoadAsyncOrder()
{
	if (CsCVarManagerLoadingAsyncOrder->GetInt() > CS_CVAR_LOAD_UNSET)
		return (TCsLoadAsyncOrder)CsCVarManagerLoadingAsyncOrder->GetInt();
	return ECsLoadAsyncOrder::Bulk;
}

// Enum
#pragma region

#if WITH_EDITOR

void UCsCommon_Load::CheckEnumLoadFlags(int32* LoadFlags, const FString &ObjectName, const FString &MemberName)
{
	if (*LoadFlags == CS_LOAD_FLAGS_NONE)
	{
		// 1P_LoadFlags
		if (MemberName.EndsWith(ECsLoadCached::Str::_1P_LoadFlags))
		{
			CS_SET_BLUEPRINT_BITFLAG(*LoadFlags, ECsLoadFlags::Game);
			CS_SET_BLUEPRINT_BITFLAG(*LoadFlags, ECsLoadFlags::Game1P);
		}
		// 3P_LoadFlags
		else
		if (MemberName.EndsWith(ECsLoadCached::Str::_3P_LoadFlags))
		{
			CS_SET_BLUEPRINT_BITFLAG(*LoadFlags, ECsLoadFlags::Game);
			CS_SET_BLUEPRINT_BITFLAG(*LoadFlags, ECsLoadFlags::Game3P);
		}
		// 3P_Low_LoadFlags
		else
		if (MemberName.EndsWith(ECsLoadCached::Str::_3P_Low_LoadFlags))
		{
			CS_SET_BLUEPRINT_BITFLAG(*LoadFlags, ECsLoadFlags::Game);
			CS_SET_BLUEPRINT_BITFLAG(*LoadFlags, ECsLoadFlags::Game3PLow);
		}
		// VR_LoadFlags
		else
		if (MemberName.EndsWith(ECsLoadCached::Str::VR_LoadFlags))
		{
			CS_SET_BLUEPRINT_BITFLAG(*LoadFlags, ECsLoadFlags::Game);
			CS_SET_BLUEPRINT_BITFLAG(*LoadFlags, ECsLoadFlags::GameVR);
		}
		// _LoadFlags
		else
		{
			CS_SET_BLUEPRINT_BITFLAG(*LoadFlags, ECsLoadFlags::Game);
		}

		const FString LoadFlagsAsString = EMCsLoadFlags::Get().MaskToString(*LoadFlags);

		UE_LOG(LogCs, Warning, TEXT("UCsCommon_Load::CheckEnumLoadFlags: %s was 0. Setting %s to %s."), *ObjectName, *MemberName, *LoadFlagsAsString);
	}
}

void UCsCommon_Load::CheckStructWithEnum(const FString &ObjectName, void* InStruct, UScriptStruct* const &InScriptStruct, TCsCheckStructWithEnum_Internal Internal /*=nullptr*/)
{
}

void UCsCommon_Load::CheckObjectWithEnum(const FString &ObjectName, void* InObject, UClass* const &InClass, TCsCheckObjectWithEnum_Internal Internal /*=nullptr*/)
{
	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, ObjectName, InObject, InClass))
					continue;
			}
			continue;
		}
		// TSoftObjectPtr
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(*It))
		{
			// UStaticMesh
			if (SoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ CheckEnumSoftObjectProperty<UStaticMesh>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// USkeletalMesh
			if (SoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ CheckEnumSoftObjectProperty<USkeletalMesh>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UMaterialInstance
			if (SoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ CheckEnumSoftObjectProperty<UMaterialInstance>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UMaterialInstanceConstant
			if (SoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{ CheckEnumSoftObjectProperty<UMaterialInstanceConstant>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UPhysicalMaterial
			if (SoftObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ CheckEnumSoftObjectProperty<UPhysicalMaterial>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UPhysicsAsset
			if (SoftObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ CheckEnumSoftObjectProperty<UPhysicsAsset>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UAnimSequence
			if (SoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ CheckEnumSoftObjectProperty<UAnimSequence>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UAnimMontage
			if (SoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ CheckEnumSoftObjectProperty<UAnimMontage>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UBlendSpace
			if (SoftObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ CheckEnumSoftObjectProperty<UBlendSpace>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UAnimBlueprint
			//if (SoftObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			//{ CheckEnumSoftObjectProperty(SoftObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// USoundCue
			if (SoftObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ CheckEnumSoftObjectProperty<USoundCue>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UParticleSystem
			if (SoftObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ CheckEnumSoftObjectProperty<UParticleSystem>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UCurveFloat
			if (SoftObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ CheckEnumSoftObjectProperty<UCurveFloat>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UCurveVector
			if (SoftObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ CheckEnumSoftObjectProperty<UCurveVector>(SoftObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UBlueprint
			if (SoftObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{
				if (SoftObjectProperty->ArrayDim == CS_SINGLETON)
				{
					//LoadSoftObjectProperty_Blueprint(SoftObjectProperty, ObjectName, InObject, InClass, MemberName, LoadFlags); continue;
				}
			}

			if (Internal)
			{
				if ((*Internal)(Property, ObjectName, InObject, InClass))
					continue;
			}
			continue;
		}
		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			const FString StructName = FString::Printf(TEXT("%s.%s"), *ObjectName, *MemberName);

			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ CheckEnumStructProperty<FCsStaticMesh>(StructProperty, InObject, StructName, nullptr); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass))
						continue;
				}
				continue;
			}
			// FCsFpvStaticMesh
			if (StructProperty->Struct == FCsFpvStaticMesh::StaticStruct())
			{ CheckEnumStructProperty<FCsFpvStaticMesh>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsTArrayStaticMesh
			if (StructProperty->Struct == FCsTArrayStaticMesh::StaticStruct())
			{ CheckEnumStructProperty<FCsTArrayStaticMesh>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ CheckEnumStructProperty<FCsSkeletalMesh>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsFpsSkeletalMesh
			if (StructProperty->Struct == FCsFpsSkeletalMesh::StaticStruct())
			{ CheckEnumStructProperty<FCsFpsSkeletalMesh>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsTArraySkeletalMesh
			if (StructProperty->Struct == FCsTArraySkeletalMesh::StaticStruct())
			{ CheckEnumStructProperty<FCsTArraySkeletalMesh>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ CheckEnumStructProperty<FCsMaterialInstance>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsMaterialInstanceConstant
			if (StructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
			{ CheckEnumStructProperty<FCsMaterialInstanceConstant>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsTArrayMaterialInstanceConstant::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ CheckEnumStructProperty<FCsTArrayMaterialInstanceConstant>(StructProperty, InObject, StructName, nullptr); continue; }
				if (StructProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{
					//LoadMemberFixedArrayStructProperty_EnumSize<FCsTArrayMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(StructProperty, InObject, StructName, LoadFlags, &ECsInteractiveState::ToString, nullptr); continue;
				}

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass))
						continue;
				}
				continue;
			}
			// FCsFpsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsFpsTArrayMaterialInstanceConstant::StaticStruct())
			{ CheckEnumStructProperty<FCsFpsTArrayMaterialInstanceConstant>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsInteractiveMaterials
			if (StructProperty->Struct == FCsInteractiveMaterials::StaticStruct())
			{ CheckEnumStructProperty<FCsInteractiveMaterials>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsPhysicalMaterial
			if (StructProperty->Struct == FCsPhysicalMaterial::StaticStruct())
			{ CheckEnumStructProperty<FCsPhysicalMaterial>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ CheckEnumStructProperty<FCsPhysicsAsset>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsCurveFloat
			if (StructProperty->Struct == FCsCurveFloat::StaticStruct())
			{ CheckEnumStructProperty<FCsCurveFloat>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ CheckEnumStructProperty<FCsCurveVector>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ CheckEnumStructProperty<FCsSoundElement>(StructProperty, InObject, StructName, nullptr); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass))
						continue;
				}
				continue;
			}
			// FCsFpvSoundElement
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ CheckEnumStructProperty<FCsFpvSoundElement>(StructProperty, InObject, StructName, nullptr); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass))
						continue;
				}
				continue;
			}
			// FCsParticleSystem
			if (StructProperty->Struct == FCsParticleSystem::StaticStruct())
			{ CheckEnumStructProperty<FCsParticleSystem>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ CheckEnumStructProperty<FCsFxElement>(StructProperty, InObject, StructName, nullptr); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass))
						continue;
				}
				continue;
			}
			// FCsFpvFxElement
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ CheckEnumStructProperty<FCsFpvFxElement>(StructProperty, InObject, StructName, nullptr); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass))
						continue;
				}
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ CheckEnumStructProperty<FCsAnimSequence>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsFpvAnimSequence
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
			{ CheckEnumStructProperty<FCsFpvAnimSequence>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{ CheckEnumStructProperty<FCsAnimMontage>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsFpvAnimMontage
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
			{ CheckEnumStructProperty<FCsFpvAnimMontage>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{ CheckEnumStructProperty<FCsTArrayAnimMontage>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ CheckEnumStructProperty<FCsAnimBlueprint>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsFpvAnimBlueprint
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
			{ CheckEnumStructProperty<FCsFpvAnimBlueprint>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsBlendSpace1D
			if (StructProperty->Struct == FCsBlendSpace1D::StaticStruct())
			{ CheckEnumStructProperty<FCsBlendSpace1D>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsFpvBlendSpace1D
			if (StructProperty->Struct == FCsFpvBlendSpace1D::StaticStruct())
			{ CheckEnumStructProperty<FCsFpvBlendSpace1D>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ CheckEnumStructProperty<FCsBlendSpace>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsFpvBlendSpace
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
			{ CheckEnumStructProperty<FCsFpvBlendSpace>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsBlueprint
			if (StructProperty->Struct == FCsBlueprint::StaticStruct())
			{ CheckEnumStructProperty<FCsBlueprint>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsTArrayBlueprint
			if (StructProperty->Struct == FCsTArrayBlueprint::StaticStruct())
			{ CheckEnumStructProperty<FCsTArrayBlueprint>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsWidgetComponentInfo
			if (StructProperty->Struct == FCsWidgetComponentInfo::StaticStruct())
			{ CheckEnumStructProperty<FCsWidgetComponentInfo>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsWidgetActorInfo
			if (StructProperty->Struct == FCsWidgetActorInfo::StaticStruct())
			{ CheckEnumStructProperty<FCsWidgetActorInfo>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsData_ProjectileImpactPtr
			if (StructProperty->Struct == FCsData_ProjectileImpactPtr::StaticStruct())
			{ CheckEnumStructProperty<FCsData_ProjectileImpactPtr>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsDamageFalloff
			if (StructProperty->Struct == FCsDamageFalloff::StaticStruct())
			{ CheckEnumStructProperty<FCsDamageFalloff>(StructProperty, InObject, StructName, nullptr); continue; }
			// FCsDamageRadial
			if (StructProperty->Struct == FCsDamageRadial::StaticStruct())
			{ CheckEnumStructProperty<FCsDamageRadial>(StructProperty, InObject, StructName, nullptr); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, ObjectName, InObject, InClass))
					continue;
			}
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftClassPtr
			if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass))
						continue;
				}
				continue;
			}
			// TSoftObjectPtr
			if (USoftObjectProperty* InnerSoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerSoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ CheckEnumArraySoftObjectProperty<UStaticMesh>(ArrayProperty, ObjectName, InObject, InClass, MemberName); continue; }
				// USkeletalMesh
				if (InnerSoftObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ CheckEnumArraySoftObjectProperty<USkeletalMesh>(ArrayProperty, ObjectName, InObject, InClass, MemberName); continue; }
				// UMaterialInstance
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ CheckEnumArraySoftObjectProperty<UMaterialInstance>(ArrayProperty, ObjectName, InObject, InClass, MemberName); continue; }
				// UMaterialInstanceConstant
				if (InnerSoftObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ CheckEnumArraySoftObjectProperty<UMaterialInstanceConstant>(ArrayProperty, ObjectName, InObject, InClass, MemberName); continue; }
				// UAnimSequence
				if (InnerSoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ CheckEnumArraySoftObjectProperty<UAnimSequence>(ArrayProperty, ObjectName, InObject, InClass, MemberName); continue; }
				// UAnimMontage
				if (InnerSoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ CheckEnumArraySoftObjectProperty<UAnimMontage>(ArrayProperty, ObjectName, InObject, InClass, MemberName); continue; }
				// UBlueprint
				//if (InnerSoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				//{ CheckEnumArraySoftObjectProperty(ArrayProperty, ObjectName, InObject, InClass, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass))
						continue;
				}
				continue;
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				const FString StructName = FString::Printf(TEXT("%s.%s"), *ObjectName, *MemberName);

				// FCsMaterialInstance
				if (InnerStructProperty->Struct == FCsMaterialInstance::StaticStruct())
				{ CheckEnumArrayStructProperty<FCsMaterialInstance>(ArrayProperty, InObject, StructName); continue; }
				// FCsMaterialInstanceConstant
				if (InnerStructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
				{ CheckEnumArrayStructProperty<FCsMaterialInstanceConstant>(ArrayProperty, InObject, StructName); continue; }
				// FCsFpvFxElement
				if (InnerStructProperty->Struct == FCsFpvFxElement::StaticStruct())
				{ CheckEnumArrayStructProperty<FCsFpvFxElement>(ArrayProperty, InObject, StructName); continue; }
				// FCsFpvSoundElement
				if (InnerStructProperty->Struct == FCsFpvSoundElement::StaticStruct())
				{ CheckEnumArrayStructProperty<FCsFpvSoundElement>(ArrayProperty, InObject, StructName); continue; }
				// FCsAnimSequence
				if (InnerStructProperty->Struct == FCsAnimSequence::StaticStruct())
				{ CheckEnumArrayStructProperty<FCsAnimSequence>(ArrayProperty, InObject, StructName); continue; }
				// FCsFpvAnimSequence
				if (InnerStructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				{ CheckEnumArrayStructProperty<FCsFpvAnimSequence>(ArrayProperty, InObject, StructName); continue; }
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ CheckEnumArrayStructProperty<FCsAnimMontage>(ArrayProperty, InObject, StructName); continue; }
				// FCsFpvAnimMontage
				if (InnerStructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				{ CheckEnumArrayStructProperty<FCsFpvAnimMontage>(ArrayProperty, InObject, StructName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass))
						continue;
				}
				continue;
			}
			// Byte / Enum
			if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
			{
				// enum
				if (ByteProperty->IsEnum())
				{
					// ECollisionChannel
					if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CollisionChannel))
					{ CheckEnumByteProperty<ECollisionChannel>(ByteProperty, InObject, MemberName, ECollisionChannel::ECC_MAX); continue; }
					// ECsLoadFlags_Editor
					if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsLoadFlags_Editor))
					{ CheckEnumByteProperty<ECsLoadFlags_Editor::Type>(ByteProperty, InObject, MemberName, ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX); continue; }
					// ECsFxPriority
					if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsFxPriority))
					{ CheckEnumByteProperty<ECsFxPriority::Type>(ByteProperty, InObject, MemberName, ECsFxPriority::ECsFxPriority_MAX); continue; }
					// ECsSoundPriority
					if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsSoundPriority))
					{ CheckEnumByteProperty<ECsSoundPriority::Type>(ByteProperty, InObject, MemberName, ECsSoundPriority::ECsSoundPriority_MAX); continue; }
					// ECsInteractiveCollision
					if (ByteProperty->Enum->CppType.Contains(NCsCommonLoadCached::Str::CsInteractiveCollision))
					{
						if (ByteProperty->ArrayDim == CS_SINGLETON)
						{ CheckEnumByteProperty<ECsInteractiveCollision::Type>(ByteProperty, InObject, MemberName, ECsInteractiveCollision::ECsInteractiveCollision_MAX); continue; }
					}

					if (Internal)
					{
						if ((*Internal)(Property, ObjectName, InObject, InClass))
							continue;
					}
					continue;
				}
				continue;
			}
			// int32
			if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			{
				if (int32* Member = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
				{
										//    TEXT("BitmaskEnum")
					if (Property->HasMetaData(*(NCsCommonLoadCached::Str::BitmaskEnum)))
					{
																	//    TEXT("BitmaskEnum")
						const FString BitmaskEnum = Property->GetMetaData(*(NCsCommonLoadCached::Str::BitmaskEnum));

						// (BitmaskEnum == TEXT("ECsLoadFlags"))
						if (BitmaskEnum == NCsCommonLoadCached::Str::CsLoadFlags)
						{
							const FString FullLoadFlagsMemberName = FString::Printf(TEXT("%s.%s"), *ObjectName, *MemberName);

							CheckEnumLoadFlags(Member, FullLoadFlagsMemberName, MemberName);
						}
					}
				}
				continue;
			}
		}
	}
}

#endif // #if WITH_EDITOR

#pragma endregion Enum

#pragma endregion Loading

// Members
#pragma region

#if WITH_EDITOR

void UCsCommon_Load::GetCategoryMemberAssociations(void* InStruct, UScriptStruct* const &InScriptStruct, TArray<FCsCategoryMemberAssociation> &OutCategoryMemberAssociations)
{
	OutCategoryMemberAssociations.Reset();

	const FString NoCategory = TEXT("");
	FString LastCategory	 = NoCategory;

	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		if (!Property->HasMetaData(TEXT("Category")))
			continue;

		const FString Category = Property->GetMetaData(TEXT("Category"));

		if (Category.Len() <= 3)
			continue;

		// Check if Category Changed
		if (Category != LastCategory)
		{
			// Check if VALID Category
			bool IsNumberTens = false;
			bool IsNumberOnes = false;

			const int32 Max = 10;

			for (int32 I = 0; I < Max; ++I)
			{
				if (Category[0] == FString::FromInt(I)[0])
					IsNumberTens |= true;
				if (Category[1] == FString::FromInt(I)[0])
					IsNumberOnes |= true;
			}

			if (!IsNumberTens || !IsNumberOnes)
				continue;

			OutCategoryMemberAssociations.AddDefaulted();

			const int32 ListIndex = OutCategoryMemberAssociations.Num() - 1;
			OutCategoryMemberAssociations[ListIndex].Category = Category;

			LastCategory = Category;
		}

		const int32 ListIndex = OutCategoryMemberAssociations.Num() - 1;

		OutCategoryMemberAssociations[ListIndex].Members.Add(MemberName);
	}
}

void UCsCommon_Load::GetCategoryMemberAssociations(void* InObject, UClass* const &InClass, TArray<FCsCategoryMemberAssociation> &OutCategoryMemberAssociations)
{
	OutCategoryMemberAssociations.Reset();

	const FString NoCategory = TEXT("");
	FString LastCategory	 = NoCategory;

	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		if (!Property->HasMetaData(TEXT("Category")))
			continue;

		const FString Category = Property->GetMetaData(TEXT("Category"));

		if (Category.Len() <= 3)
			continue;

		// Check if Category Changed
		if (Category != LastCategory)
		{
			// Check if VALID Category
			bool IsNumberTens = false;
			bool IsNumberOnes = false;

			const int32 Max = 10;

			for (int32 I = 0; I < Max; ++I)
			{
				if (Category[0] == FString::FromInt(I)[0])
					IsNumberTens |= true;
				if (Category[1] == FString::FromInt(I)[0])
					IsNumberOnes |= true;
			}

			if (!IsNumberTens || !IsNumberOnes)
				continue;

			OutCategoryMemberAssociations.AddDefaulted();

			const int32 ListIndex = OutCategoryMemberAssociations.Num() - 1;
			OutCategoryMemberAssociations[ListIndex].Category = Category;

			LastCategory = Category;
		}

		const int32 ListIndex = OutCategoryMemberAssociations.Num() - 1;

		OutCategoryMemberAssociations[ListIndex].Members.Add(MemberName);
	}
}

#endif // #if WITH_EDITOR

// Set
#pragma region

bool UCsCommon_Load::SetObjectMember(void* InObject, UClass* const &InClass, const FString &MemberName, void* MemberValue)
{
	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString PropertyName = Property->GetName();

		if (PropertyName != MemberName)
			continue;

		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FGuid
			if (StructProperty->Struct == TBaseStructure<FGuid>::Get())
				return SetMemberProperty<FGuid>(InObject, Property, MemberValue);
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
				return SetMemberProperty<FVector>(InObject, Property, MemberValue);
			// FRotator
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
				return SetMemberProperty<FRotator>(InObject, Property, MemberValue);
			// FColor
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
				return SetMemberProperty<FColor>(InObject, Property, MemberValue);
			continue;
		}
		// bool
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
			return SetMemberProperty<bool>(InObject, Property, MemberValue);
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			if (ByteProperty->IsEnum())
			{
				// ECharacterClass
				//if (ByteProperty->Enum->CppType.Contains(TEXT("ECharacterClass")))
				//	return SetMemberProperty<TEnumAsByte<ECharacterClass::Type>>(InObject, Property, MemberValue);
			}
			continue;
		}
		// int32
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			return SetMemberProperty<int32>(InObject, Property, MemberValue);
		// float
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
			return SetMemberProperty<int32>(InObject, Property, MemberValue);
		// FString
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
			return SetMemberProperty<FString>(InObject, Property, MemberValue);
		// FName
		if (UNameProperty* NameProperty = Cast<UNameProperty>(*It))
			return SetMemberProperty<FName>(InObject, Property, MemberValue);
	}
	return false;
}

bool UCsCommon_Load::SetStructMember(void* InStruct, UScriptStruct* const &InScriptStruct, const FString &MemberName, void* MemberValue)
{
	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString PropertyName = Property->GetName();

		if (PropertyName != MemberName)
			continue;

		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FGuid
			if (StructProperty->Struct == TBaseStructure<FGuid>::Get())
				return SetMemberProperty<FGuid>(InStruct, Property, MemberValue);
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
				return SetMemberProperty<FVector>(InStruct, Property, MemberValue);
			// FRotator
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
				return SetMemberProperty<FRotator>(InStruct, Property, MemberValue);
			// FColor
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
				return SetMemberProperty<FColor>(InStruct, Property, MemberValue);
			continue;
		}
		// bool
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
			return SetMemberProperty<bool>(InStruct, Property, MemberValue);
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			if (ByteProperty->IsEnum())
			{
				// ECharacterClass
				//if (ByteProperty->Enum->CppType.Contains(TEXT("ECharacterClass")))
				//	return SetMemberProperty<TEnumAsByte<ECharacterClass::Type>>(InStruct, Property, MemberValue);
			}
			continue;
		}
		// int32
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			return SetMemberProperty<int32>(InStruct, Property, MemberValue);
		// float
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
			return SetMemberProperty<int32>(InStruct, Property, MemberValue);
		// FString
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
			return SetMemberProperty<FString>(InStruct, Property, MemberValue);
		// FName
		if (UNameProperty* NameProperty = Cast<UNameProperty>(*It))
			return SetMemberProperty<FName>(InStruct, Property, MemberValue);
	}
	return false;
}

bool UCsCommon_Load::SetObjectMember(void* InObject, UClass* const &InClass, const uint16 &MemberIndex, void* MemberValue)
{
	uint16 Index = 0;

	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		if (Index < MemberIndex)
		{
			Index++;
			continue;
		}
		if (Index > MemberIndex)
			return false;

		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FGuid
			if (StructProperty->Struct == TBaseStructure<FGuid>::Get())
				return SetMemberProperty<FGuid>(InObject, Property, MemberValue);
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
				return SetMemberProperty<FVector>(InObject, Property, MemberValue);
			// FRotator
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
				return SetMemberProperty<FRotator>(InObject, Property, MemberValue);
			// FColor
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
				return SetMemberProperty<FColor>(InObject, Property, MemberValue);
			continue;
		}
		// bool
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
			return SetMemberProperty<bool>(InObject, Property, MemberValue);
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			if (ByteProperty->IsEnum())
			{
				// ECharacterClass
				//if (ByteProperty->Enum->CppType.Contains(TEXT("ECharacterClass")))
				//	return SetMemberProperty<TEnumAsByte<ECharacterClass::Type>>(InObject, Property, MemberValue);
			}
			continue;
		}
		// int32
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			return SetMemberProperty<int32>(InObject, Property, MemberValue);
		// float
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
			return SetMemberProperty<int32>(InObject, Property, MemberValue);
		// FString
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
			return SetMemberProperty<FString>(InObject, Property, MemberValue);
		// FName
		if (UNameProperty* NameProperty = Cast<UNameProperty>(*It))
			return SetMemberProperty<FName>(InObject, Property, MemberValue);
	}
	return false;
}

bool UCsCommon_Load::SetStructMember(void* InStruct, UScriptStruct* const &InScriptStruct, const uint16 &MemberIndex, void* MemberValue)
{
	uint16 Index = 0;

	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		if (Index < MemberIndex)
		{
			Index++;
			continue;
		}
		if (Index > MemberIndex)
			return false;

		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FGuid
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
				return SetMemberProperty<FVector>(InStruct, Property, MemberValue);
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
				return SetMemberProperty<FVector>(InStruct, Property, MemberValue);
			// FRotator
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
				return SetMemberProperty<FRotator>(InStruct, Property, MemberValue);
			// FColor
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
				return SetMemberProperty<FColor>(InStruct, Property, MemberValue);
			continue;
		}
		// bool
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
			return SetMemberProperty<bool>(InStruct, Property, MemberValue);
		// Byte / Enum
		else
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			if (ByteProperty->IsEnum())
			{
				// ECharacterClass
				//if (ByteProperty->Enum->CppType.Contains(TEXT("ECharacterClass")))
				//	return SetMemberProperty<TEnumAsByte<ECharacterClass::Type>>(InStruct, Property, MemberValue);
			}
			continue;
		}
		// int32
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			return SetMemberProperty<int32>(InStruct, Property, MemberValue);
		// float
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
			return SetMemberProperty<int32>(InStruct, Property, MemberValue);
		// FString
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
			return SetMemberProperty<FString>(InStruct, Property, MemberValue);
		// FName
		if (UNameProperty* NameProperty = Cast<UNameProperty>(*It))
			return SetMemberProperty<FName>(InStruct, Property, MemberValue);
	}
	return false;
}

void UCsCommon_Load::SetObjectMembers(void* FromObject, void* ToObject, UClass* const &InClass, const TArray<FString>* MemberNames)
{
	if (!MemberNames)
		return;
	
	const int32 Count = MemberNames->Num();

	TArray<void*> MemberValues;

	GetObjectMembers(FromObject, InClass, MemberNames, MemberValues);

	int32 Index = 0;

	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		if (Index < Count)
		{
			if ((*MemberNames)[Index] == MemberName)
				Index++;
			else
				continue;
		}
		else
		{
			return;
		}

		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(*It))
		{
			// AShooterWeaponData
			//if (SoftClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || SoftClassProperty->MetaClass == AShooterWeaponData::StaticClass())
			//	SetMemberProperty<TSoftClassPtr<AShooterWeaponData>>(ToObject, Property, MemberValues[Index]);
		}
		// TSoftObjectPtr
		else
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(*It))
		{
			// UStaticMesh
			if (SoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				SetMemberProperty<TSoftObjectPtr<UStaticMesh>>(ToObject, Property, MemberValues[Index]);
			// UMaterialInstance
			else
			if (SoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				SetMemberProperty<TSoftObjectPtr<UMaterialInstance>>(ToObject, Property, MemberValues[Index]);
			// UPhysicsAsset
			else
			if (SoftObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
				SetMemberProperty<TSoftObjectPtr<UPhysicsAsset>>(ToObject, Property, MemberValues[Index]);
			// UAnimSequence
			else
			if (SoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				SetMemberProperty<TSoftObjectPtr<UAnimSequence>>(ToObject, Property, MemberValues[Index]);
			// UAnimMontage
			else
			if (SoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				SetMemberProperty<TSoftObjectPtr<UAnimMontage>>(ToObject, Property, MemberValues[Index]);
			// UBlendSpace
			else
			if (SoftObjectProperty->PropertyClass == UBlendSpace::StaticClass())
				SetMemberProperty<TSoftObjectPtr<UBlendSpace>>(ToObject, Property, MemberValues[Index]);
			// UAnimBlueprint
			else
			if (SoftObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
				SetMemberProperty<TSoftObjectPtr<UAnimBlueprint>>(ToObject, Property, MemberValues[Index]);
			// USoundCue
			else
			if (SoftObjectProperty->PropertyClass == USoundCue::StaticClass())
				SetMemberProperty<TSoftObjectPtr<USoundCue>>(ToObject, Property, MemberValues[Index]);
			// UParticleSystem
			else
			if (SoftObjectProperty->PropertyClass == UParticleSystem::StaticClass())
				SetMemberProperty<TSoftObjectPtr<UParticleSystem>>(ToObject, Property, MemberValues[Index]);
			// UCurveVector
			else
			if (SoftObjectProperty->PropertyClass == UCurveVector::StaticClass())
				SetMemberProperty<TSoftObjectPtr<UCurveVector>>(ToObject, Property, MemberValues[Index]);
		}
		// Structs
		else
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
				SetMemberProperty<FCsAnimSequence>(ToObject, Property, MemberValues[Index]);
			// FCsFpvAnimSequence
			else
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				SetMemberProperty<FCsFpvAnimSequence>(ToObject, Property, MemberValues[Index]);
			// FCsAnimMontage
			else
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					SetMemberProperty<FCsAnimMontage>(ToObject, Property, MemberValues[Index]);
			}
			// FCsFpvAnimMontage
			else
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				SetMemberProperty<FCsFpvAnimMontage>(ToObject, Property, MemberValues[Index]);
			// FCsBlendSpace
			else
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
				SetMemberProperty<FCsBlendSpace>(ToObject, Property, MemberValues[Index]);
			// FCsFpvBlendSpace
			else
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
				SetMemberProperty<FCsFpvBlendSpace>(ToObject, Property, MemberValues[Index]);
			// FCsAnimBlueprint
			else
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
				SetMemberProperty<FCsAnimBlueprint>(ToObject, Property, MemberValues[Index]);
			// FCsFpvAnimBlueprint
			else
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
				SetMemberProperty<FCsFpvAnimBlueprint>(ToObject, Property, MemberValues[Index]);
			// FCsSoundElement
			else
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					SetMemberProperty<FCsSoundElement>(ToObject, Property, MemberValues[Index]);
			}
			// FCsFpvSoundElement
			else
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					SetMemberProperty<FCsFpvSoundElement>(ToObject, Property, MemberValues[Index]);
			}
			// FCsFxElement
			else
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					SetMemberProperty<FCsFxElement>(ToObject, Property, MemberValues[Index]);
			}
			// FCsFpvFxElement
			else
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					SetMemberProperty<FCsFpvFxElement>(ToObject, Property, MemberValues[Index]);
			}
		}
		// Array
		else
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftClassPtr
			if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				// AShooterWeaponData
				//if (InnerSoftClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerSoftClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//{ SetMemberProperty<TArray<TSoftClassPtr<AShooterWeaponData>>>(ToObject, Property, MemberValues[Index]); }
			}
			// TSoftObjectPtr
			else
			if (USoftObjectProperty* InnerSoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
			{
				// UAnimMontage
				//if (InnerSoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				//{ SetMemberProperty<TArray<TSoftObjectPtr<UAnimMontage>>>(ToObject, Property, MemberValues[Index]); }
			}
			// Struct
			else
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FCsAnimMontage
				//if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				//{ SetMemberProperty<FCsAnimMontage>(ToObject, Property, MemberValues[Index]); }
				// FCsSoundElement
				//else
				//if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				//{ SetMemberProperty<FCsSoundElement>(ToObject, Property, MemberValues[Index]); }
			}
		}
	}
}

#pragma endregion Set

// Get
#pragma region

void* UCsCommon_Load::GetStructMemberEX(UProperty* Property, void* InStruct, UScriptStruct* const &InScriptStruct, const FString &MemberName)
{
	const FString PropertyName = Property->GetName();

	if (PropertyName != MemberName)
		return nullptr;

	// Struct
	if (UStructProperty* StructProperty = Cast<UStructProperty>(Property))
	{
		// Weapon_FireMode
		{
			// FCsData_Weapon_FireMode_Firing
			if (StructProperty->Struct == FCsData_Weapon_FireMode_Firing::StaticStruct())
				return (void*)Property->ContainerPtrToValuePtr<FCsData_Weapon_FireMode_Firing>(InStruct);
			// FCsData_Weapon_FireMode_Animation
			if (StructProperty->Struct == FCsData_Weapon_FireMode_Animation::StaticStruct())
				return (void*)Property->ContainerPtrToValuePtr<FCsData_Weapon_FireMode_Animation>(InStruct);
			// FCsData_FpsWeapon_FireMode_Animation
			if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Animation::StaticStruct())
				return (void*)Property->ContainerPtrToValuePtr<FCsData_FpsWeapon_FireMode_Animation>(InStruct);
			// FCsData_Weapon_FireMode_Movement
			if (StructProperty->Struct == FCsData_Weapon_FireMode_Movement::StaticStruct())
				return (void*)Property->ContainerPtrToValuePtr<FCsData_Weapon_FireMode_Movement>(InStruct);
			// FCsData_Weapon_FireMode_Aiming
			if (StructProperty->Struct == FCsData_Weapon_FireMode_Aiming::StaticStruct())
				return (void*)Property->ContainerPtrToValuePtr<FCsData_Weapon_FireMode_Aiming>(InStruct);
			// FCsData_FpsWeapon_FireMode_Aiming
			if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Aiming::StaticStruct())
				return (void*)Property->ContainerPtrToValuePtr<FCsData_FpsWeapon_FireMode_Aiming>(InStruct);
			// FCsData_Weapon_FireMode_Scope
			if (StructProperty->Struct == FCsData_Weapon_FireMode_Scope::StaticStruct())
				return (void*)Property->ContainerPtrToValuePtr<FCsData_Weapon_FireMode_Scope>(InStruct);
			// FCsData_Weapon_FireMode_FXs
			if (StructProperty->Struct == FCsData_Weapon_FireMode_FXs::StaticStruct())
				return (void*)Property->ContainerPtrToValuePtr<FCsData_Weapon_FireMode_FXs>(InStruct);
			// FCsData_FpsWeapon_FireMode_FXs
			if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_FXs::StaticStruct())
				return (void*)Property->ContainerPtrToValuePtr<FCsData_FpsWeapon_FireMode_FXs>(InStruct);
			// FCsData_Weapon_FireMode_Sounds
			if (StructProperty->Struct == FCsData_Weapon_FireMode_Sounds::StaticStruct())
				return (void*)Property->ContainerPtrToValuePtr<FCsData_Weapon_FireMode_Sounds>(InStruct);
			// FCsData_FpsWeapon_FireMode_Sounds
			if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Sounds::StaticStruct())
				return (void*)Property->ContainerPtrToValuePtr<FCsData_FpsWeapon_FireMode_Sounds>(InStruct);
		}
	}
	return nullptr;
}

UScriptStruct* UCsCommon_Load::GetScriptStructMember(void* InStruct, UScriptStruct* const &InScriptStruct, const FString &MemberName, TCsGetScriptStructMember_Internal Internal /*=nullptr*/)
{
	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString PropertyName = Property->GetName();

		if (PropertyName != MemberName)
			continue;

		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// Weapon_FireMode
			{
				// FCsData_Weapon_FireMode_Firing
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Firing::StaticStruct())
					return FCsData_Weapon_FireMode_Firing::StaticStruct();
				// FCsData_Weapon_FireMode_Animation
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Animation::StaticStruct())
					return FCsData_Weapon_FireMode_Animation::StaticStruct();
				// FCsData_FpsWeapon_FireMode_Animation
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Animation::StaticStruct())
					return FCsData_FpsWeapon_FireMode_Animation::StaticStruct();
				// FCsData_Weapon_FireMode_Movement
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Movement::StaticStruct())
					return FCsData_Weapon_FireMode_Movement::StaticStruct();
				// FCsData_Weapon_FireMode_Aiming
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Aiming::StaticStruct())
					return FCsData_Weapon_FireMode_Aiming::StaticStruct();
				// FCsData_FpsWeapon_FireMode_Aiming
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Aiming::StaticStruct())
					return FCsData_FpsWeapon_FireMode_Aiming::StaticStruct();
				// FCsData_Weapon_FireMode_Scope
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Scope::StaticStruct())
					return FCsData_Weapon_FireMode_Scope::StaticStruct();
				// FCsData_Weapon_FireMode_FXs
				if (StructProperty->Struct == FCsData_Weapon_FireMode_FXs::StaticStruct())
					return FCsData_Weapon_FireMode_FXs::StaticStruct();
				// FCsData_FpsWeapon_FireMode_FXs
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_FXs::StaticStruct())
					return FCsData_FpsWeapon_FireMode_FXs::StaticStruct();
				// FCsData_Weapon_FireMode_Sounds
				if (StructProperty->Struct == FCsData_Weapon_FireMode_Sounds::StaticStruct())
					return FCsData_Weapon_FireMode_Sounds::StaticStruct();
				// FCsData_FpsWeapon_FireMode_Sounds
				if (StructProperty->Struct == FCsData_FpsWeapon_FireMode_Sounds::StaticStruct())
					return FCsData_FpsWeapon_FireMode_Sounds::StaticStruct();
			}

			if (Internal)
			{
				if (UScriptStruct* Ptr = (*Internal)(Property, InStruct, InScriptStruct, MemberName))
					return Ptr;
			}
			return nullptr;
		}
	}
	return nullptr;
}

/*
TEnumAsByte<EMemberType::Type> UCsCommon_Load::GetObjectMemberType(UClass* const &InClass, const FString &MemberName)
{
	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString PropertyName = Property->GetName();

		if (PropertyName != MemberName)
			continue;

		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
				return EMemberType::FVector;
			// FRotator
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
				return EMemberType::FRotator;
			// FColor
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
				return EMemberType::FColor;
			continue;
		}
		// bool
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
			return EMemberType::Bool;
		// Byte / Enum
		else
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			if (ByteProperty->IsEnum())
			{
				// ECharacterClass
				//if (ByteProperty->Enum->CppType.Contains(TEXT("ECharacterClass")))
				//	return EMemberType::ECharacterClass;
			}
			continue;
		}
		// int32
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			return EMemberType::Int32;
		// float
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
			return EMemberType::Float;
		// FString
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
			return EMemberType::FString;
		// FName
		if (UNameProperty* NameProperty = Cast<UNameProperty>(*It))
			return EMemberType::FName;
	}
	return EMemberType::EMemberType_MAX;
}

TEnumAsByte<EMemberType::Type> UCsCommon_Load::GetStructMemberType(UScriptStruct* const &InScriptStruct, const FString &MemberName)
{
	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString PropertyName = Property->GetName();

		if (PropertyName != MemberName)
			continue;

		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
				return EMemberType::FVector;
			// FRotator
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
				return EMemberType::FRotator;
			// FColor
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
				return EMemberType::FColor;
			continue;
		}
		// bool
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
			return EMemberType::Bool;
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			if (ByteProperty->IsEnum())
			{
				// ECharacterClass
				//if (ByteProperty->Enum->CppType.Contains(TEXT("ECharacterClass")))
				//	return EMemberType::ECharacterClass;
			}
			continue;
		}
		// int32
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			return EMemberType::Int32;
		// float
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
			return EMemberType::Float;
		// FString
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
			return EMemberType::FString;
		// FName
		if (UNameProperty* NameProperty = Cast<UNameProperty>(*It))
			return EMemberType::FName;
	}
	return EMemberType::EMemberType_MAX;
}
*/
uint16 UCsCommon_Load::GetObjectMemberIndex(UClass* const &InClass, const FString &MemberName)
{
	uint16 Index = 0;

	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString PropertyName = Property->GetName();

		if (PropertyName == MemberName)
			return Index;
		Index++;
	}
	return Index;
}

void UCsCommon_Load::GetObjectMembers(void* InObject, UClass* const &InClass, const TArray<FString>* MemberNames, TArray<void*> &OutMemberValues)
{
	if (!MemberNames)
		return;

	const int32 Count = MemberNames->Num();

	int32 Index = 0;

	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		if (Index < Count)
		{
			if ((*MemberNames)[Index] == MemberName)
				Index++;
			else
				continue;
		}
		else
		{
			return;
		}

		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(*It))
		{
			// AShooterWeaponData
			//if (SoftClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || SoftClassProperty->MetaClass == AShooterWeaponData::StaticClass())
			//	OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TSoftClassPtr<AShooterWeaponData>>(InObject));
		}
		// TSoftObjectPtr
		else
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(*It))
		{
			// UStaticMesh
			if (SoftObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TSoftObjectPtr<UStaticMesh>>(InObject));
			// UMaterialInstance
			else
			if (SoftObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TSoftObjectPtr<UMaterialInstance>>(InObject));
			// UPhysicsAsset
			else
			if (SoftObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TSoftObjectPtr<UPhysicsAsset>>(InObject));
			// UAnimSequence
			else
			if (SoftObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TSoftObjectPtr<UAnimSequence>>(InObject));
			// UAnimMontage
			else
			if (SoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TSoftObjectPtr<UAnimMontage>>(InObject));
			// UBlendSpace
			else
			if (SoftObjectProperty->PropertyClass == UBlendSpace::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TSoftObjectPtr<UBlendSpace>>(InObject));
			// UAnimBlueprint
			else
			if (SoftObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TSoftObjectPtr<UAnimBlueprint>>(InObject));
			// USoundCue
			else
			if (SoftObjectProperty->PropertyClass == USoundCue::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TSoftObjectPtr<USoundCue>>(InObject));
			// UParticleSystem
			else
			if (SoftObjectProperty->PropertyClass == UParticleSystem::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TSoftObjectPtr<UParticleSystem>>(InObject));
			// UCurveVector
			else
			if (SoftObjectProperty->PropertyClass == UCurveVector::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TSoftObjectPtr<UCurveVector>>(InObject));
		}
		// Structs
		else
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsAnimSequence>(InObject));
			// FCsFpvAnimSequence
			if (StructProperty->Struct == FCsFpvAnimSequence::StaticStruct())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFpvAnimSequence>(InObject));
			// FCsAnimMontage
			else
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsAnimMontage>(InObject));
			}
			// FCsFpvAnimMontage
			else
			if (StructProperty->Struct == FCsFpvAnimMontage::StaticStruct())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFpvAnimMontage>(InObject));
			// FCsBlendSpace
			else
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsBlendSpace>(InObject));
			// FCsFpvBlendSpace
			else
			if (StructProperty->Struct == FCsFpvBlendSpace::StaticStruct())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFpvBlendSpace>(InObject));
			// FCsAnimBlueprint
			else
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsAnimBlueprint>(InObject));
			// FCsFpvAnimBlueprint
			else
			if (StructProperty->Struct == FCsFpvAnimBlueprint::StaticStruct())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFpvAnimBlueprint>(InObject));
			// FCsSoundElement
			else
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsSoundElement>(InObject));
			}
			// FCsFpvSoundElement
			else
			if (StructProperty->Struct == FCsFpvSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFpvSoundElement>(InObject));
			}
			// FCsFxElement
			else
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFxElement>(InObject));
			}
			// FCsFpvFxElement
			else
			if (StructProperty->Struct == FCsFpvFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFpvFxElement>(InObject));
			}
		}
		// Array
		else
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftClassPtr
			if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				// AShooterWeaponData
				//if (InnerSoftClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerSoftClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//	OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TArray<TSoftClassPtr<AShooterWeaponData>>>(InObject));
			}
			// TSoftObjectPtr
			else
			if (USoftObjectProperty* InnerSoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
			{
				// AnimMontage
				if (InnerSoftObjectProperty->PropertyClass == UAnimMontage::StaticClass())
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TArray<TSoftObjectPtr<UAnimMontage>>>(InObject));
			}
			// Struct
			else
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FGuid
				if (InnerStructProperty->Struct == TBaseStructure<FGuid>::Get())
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TArray<FGuid>>(InObject));
				// FVector
				else
				if (InnerStructProperty->Struct == TBaseStructure<FVector>::Get())
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TArray<FVector>>(InObject));
				// FRotator
				else
				if (InnerStructProperty->Struct == TBaseStructure<FRotator>::Get())
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TArray<FRotator>>(InObject));
				// FColor
				else
				if (InnerStructProperty->Struct == TBaseStructure<FColor>::Get())
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TArray<FColor>>(InObject));
				// FCsAnimMontage
				else
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TArray<FCsAnimMontage>>(InObject));
				// FCsSoundElement
				else
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TArray<FCsSoundElement>>(InObject));
			}
		}
		// bool
		else
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
			OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<bool>(InObject));
		// Byte / Enum
		else
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			// enum
			if (ByteProperty->IsEnum())
			{
				// ECharacterClass
				//if (ByteProperty->Enum->CppType.Contains(TEXT("ECharacterClass")))
				//	OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TEnumAsByte<ECharacterClass::Type>>(InObject));
			}
			// uint8
			else
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<uint8>(InObject));
		}
		// int32
		else
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<int32>(InObject));
		// float
		else
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
			OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<float>(InObject));
		// FString
		else
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
			OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FString>(InObject));
		// FName
		else
		if (UNameProperty* NameProperty = Cast<UNameProperty>(*It))
			OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FName>(InObject));
	}
}

#pragma endregion Get

#pragma endregion Members