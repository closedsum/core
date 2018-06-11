// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Common/CsCommon_Load.h"
#include "CsCore.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Input.h"
#include "Types/CsTypes_UI.h"
#include "Types/CsTypes_FX.h"
#include "Types/CsTypes_Sound.h"
#include "Types/CsTypes_Anim.h"
#include "Types/CsTypes_Projectile.h"
#include "Types/CsTypes_Weapon.h"
#include "Types/CsTypes_Damage.h"
#include "Types/CsTypes_Character.h"
#include "Types/CsTypes_Interactive.h"
#include "Types/CsTypes_Item.h"
#include "Types/CsTypes_Recipe.h"
#include "Types/CsTypes_Math.h"
#include "CsCVars.h"

#include "Common/CsCommon.h"

#include "Data/CsData.h"
#include "Data/CsData_Projectile.h"
#include "Data/CsData_ProjectileImpact.h"

// Cache
#pragma region

namespace ECsCommonLoadCached
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
		const FString SoundCue = TEXT("SoundCue");
		const FString Sound_Cue = TEXT("Sound Cue");
		const FString ParticleSystem = TEXT("ParticleSystem");
		const FString Particle_System = TEXT("Particle System");
		const FString CurveFloat = TEXT("CurveFloat");
		const FString Curve_Float = TEXT("Curve Float");
		const FString CurveVector = TEXT("CurveVector");
		const FString Curve_Vector = TEXT("Curve Vector");

		const FString CsData_Projectile = TEXT("CsData_Projectile");
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

FString UCsCommon_Load::LoadFlagsToString(const int32 &LoadFlags)
{
	FString String = ECsCached::Str::Empty;
	bool IsFirst = true;

	for (int32 I = 0; I < ECS_LOAD_FLAGS_EDITOR_MAX; ++I)
	{
		if (CS_TEST_BLUEPRINT_BITFLAG(LoadFlags, (ECsLoadFlags)I))
		{
			if (!IsFirst)
			{
				String += TEXT(" | ");
			}
			String += ECsLoadFlags_Editor::ToString((TCsLoadFlags_Editor)I);
			IsFirst = false;
		}
	}
	return String;
}

#pragma endregion Enum to String Conversion

// Enum to Enum Conversion
#pragma region

int32 UCsCommon_Load::StringtoLoadFlags(const FString &LoadFlags)
{
	int32 Flag = 0;

	for (int32 I = 0; I < ECS_LOAD_FLAGS_EDITOR_MAX; ++I)
	{
		const FString& EnumAsString = ECsLoadFlags_Editor::ToString((TCsLoadFlags_Editor)I);

		if (LoadFlags.Contains(EnumAsString))
			CS_SET_BLUEPRINT_BITFLAG(Flag, ECsLoadFlags_Editor::ToFlag(EnumAsString));
	}
	return Flag;
}

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

void UCsCommon_Load::WriteTAssetPtrToJson_AnimBlueprint(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TAssetPtr<UAnimBlueprint> &Member)
{
	if (Member.IsValid() && Member.Get())
	{
		FString AssetName = Member.ToString();

		// (AssetName != TEXT(""))
		if (AssetName != ECsCached::Str::Empty)
		{
			InJsonWriter->WriteValue(MemberName, AssetName);
		}
		else
		{
											//   TEXT("")
			InJsonWriter->WriteValue(MemberName, ECsCached::Str::Empty);
		}
	}
	else
	{
										//   TEXT("")
		InJsonWriter->WriteValue(MemberName, ECsCached::Str::Empty);
	}
}

void UCsCommon_Load::WriteAssetObjectPropertyToJson_AnimBlueprint(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName)
{
	if (TAssetPtr<UAnimBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UAnimBlueprint>>(InObject))
		WriteTAssetPtrToJson_AnimBlueprint(InJsonWriter, MemberName, *Member);
}

void UCsCommon_Load::WriteTAssetPtrToJson_Blueprint(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, const FString &MemberName, TAssetPtr<UBlueprint> &Member)
{
	if (Member.IsValid() && Member.Get())
	{
		const FString AssetName = Member.ToString();

		// (AssetName != TEXT("")
		if (AssetName != ECsCached::Str::Empty)
		{
			InJsonWriter->WriteValue(MemberName, AssetName);
		}
		else
		{
											//   TEXT("")
			InJsonWriter->WriteValue(MemberName, ECsCached::Str::Empty);
		}
	}
	else
	{
										//   TEXT("")
		InJsonWriter->WriteValue(MemberName, ECsCached::Str::Empty);
	}
}

void UCsCommon_Load::WriteAssetObjectPropertyToJson_Blueprint(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName)
{
	if (TAssetPtr<UBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>>(InObject))
		WriteTAssetPtrToJson_Blueprint(InJsonWriter, MemberName, *Member);
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
		InJsonWriter->WriteValue(ECsCommonLoadCached::Str::Rotation, *(Member->GetRotation().Rotator().ToString()));
		// Translation
		InJsonWriter->WriteValue(ECsCommonLoadCached::Str::Translation, *(Member->GetTranslation().ToString()));
		// Scale
		InJsonWriter->WriteValue(ECsCommonLoadCached::Str::Scale, *(Member->GetScale3D().ToString()));

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
		InJsonWriter->WriteValue(ECsCommonLoadCached::Str::Rotation, *(Element.GetRotation().Rotator().ToString()));
		// Translation
		InJsonWriter->WriteValue(ECsCommonLoadCached::Str::Translation, *(Element.GetTranslation().ToString()));
		// Scale
		InJsonWriter->WriteValue(ECsCommonLoadCached::Str::Scale, *(Element.GetScale3D().ToString()));

		InJsonWriter->WriteObjectEnd();
	}
	InJsonWriter->WriteArrayEnd();
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

		// TAssetSubclassOf
		if (UAssetClassProperty* AssetClassProperty = Cast<UAssetClassProperty>(*It))
		{
			// ACsData_Projectile
			if (AssetClassProperty->MetaClass == ACsData_Projectile::StaticClass())
			{ WriteAssetClassPropertyToJson<ACsData_Projectile>(InJsonWriter, AssetClassProperty, InStruct, MemberName); continue; }
			// ACsData_ProjectileImpact
			if (AssetClassProperty->MetaClass == ACsData_ProjectileImpact::StaticClass())
			{ WriteAssetClassPropertyToJson<ACsData_ProjectileImpact>(InJsonWriter, AssetClassProperty, InStruct, MemberName); continue; }
			// ACsData
			if (AssetClassProperty->MetaClass == ACsData::StaticClass())
			{ WriteAssetClassPropertyToJson<ACsData>(InJsonWriter, AssetClassProperty, InStruct, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// TAssetPtr
		if (UAssetObjectProperty* AssetObjectProperty = Cast<UAssetObjectProperty>(*It))
		{
			// UStaticMesh
			if (AssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ WriteAssetObjectPropertyToJson<UStaticMesh>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// USkeletalMesh
			if (AssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ WriteAssetObjectPropertyToJson<USkeletalMesh>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstance
			if (AssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ WriteAssetObjectPropertyToJson<UMaterialInstance>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstanceConstant
			if (AssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == CS_SINGLETON)
				{ WriteAssetObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
				if (AssetObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ WriteFixedArrayAssetObjectPropertyToJson_EnumSize<UMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(InJsonWriter, AssetObjectProperty, InStruct, MemberName, &ECsInteractiveState::ToString); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// UPhysicalMaterial
			if (AssetObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ WriteAssetObjectPropertyToJson<UPhysicalMaterial>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UPhysicsAsset
			if (AssetObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ WriteAssetObjectPropertyToJson<UPhysicsAsset>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UCurveFloat
			if (AssetObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ WriteAssetObjectPropertyToJson<UCurveFloat>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UCurveVector
			if (AssetObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ WriteAssetObjectPropertyToJson<UCurveVector>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// USoundCue
			if (AssetObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ WriteAssetObjectPropertyToJson<USoundCue>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UParticleSystem
			if (AssetObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ WriteAssetObjectPropertyToJson<UParticleSystem>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UAnimSequence
			if (AssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ WriteAssetObjectPropertyToJson<UAnimSequence>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UAnimMontage
			if (AssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ WriteAssetObjectPropertyToJson<UAnimMontage>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace1D
			if (AssetObjectProperty->PropertyClass == UBlendSpace1D::StaticClass())
			{ WriteAssetObjectPropertyToJson<UBlendSpace1D>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ WriteAssetObjectPropertyToJson<UBlendSpace>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UAnimBlueprint
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ WriteAssetObjectPropertyToJson_AnimBlueprint(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UBlueprint
			if (AssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == CS_SINGLETON)
				{ WriteAssetObjectPropertyToJson_Blueprint(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
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
			// FCsFpsStaticMesh
			if (StructProperty->Struct == FCsFpsStaticMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsStaticMesh>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
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
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpsSoundElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

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
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpsFxElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

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
				{ WriteMemberFixedArrayStructPropertyToJson_EnumSize<FCsInputActionMappings, ECsInputDevice::Type, ECS_INPUT_DEVICE_MAX>(InJsonWriter, StructProperty, InStruct, MemberName, &ECsInputDevice::ToString, nullptr); continue; }
			}
			// FCsInputActionMapping
			if (StructProperty->Struct == FCsInputActionMapping::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsInputActionMapping>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsDrawDistance
			if (StructProperty->Struct == FCsDrawDistance::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsDrawDistance>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsFpsDrawDistance
			if (StructProperty->Struct == FCsFpsDrawDistance::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsDrawDistance>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
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
			// FCsData_ProjectilePtr
			if (StructProperty->Struct == FCsData_ProjectilePtr::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsData_ProjectilePtr>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
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

			// EnumStruct
			{
				// FECsAssetType
				if (StructProperty->Struct == FECsAssetType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsAssetType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
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
			// TAssetPtr
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerAssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UStaticMesh>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// USkeletalMesh
				if (InnerAssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<USkeletalMesh>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstance
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UMaterialInstance>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UAnimSequence>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UAnimMontage>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UBlueprint
				if (InnerAssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UBlueprint>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }

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
				// FCsFpsFxElement
				if (InnerStructProperty->Struct == FCsFpsFxElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpsFxElement>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsSoundElement>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpsSoundElement>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
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
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			// enum
			if (ByteProperty->IsEnum())
			{
				// ECollisionEnabled
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionEnabled))
				{ WriteMemberBytePropertyToJson<ECollisionEnabled::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECollisionEnabled::ToString); continue; }
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionChannel))
				{ WriteMemberBytePropertyToJson<ECollisionChannel>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsCollisionChannel::ToString); continue; }
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionResponse))
				{ WriteMemberBytePropertyToJson<ECollisionResponse>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsCollisionResponse::ToString); continue; }
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::HorizTextAligment))
				{ WriteMemberBytePropertyToJson<EHorizTextAligment>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsHorizTextAligment::ToString); continue; }
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::VerticalTextAligment))
				{ WriteMemberBytePropertyToJson<EVerticalTextAligment>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsVerticalTextAligment::ToString); continue; }
				// ECsLoadFlags_Editor
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsLoadFlags_Editor))
				{ WriteMemberBytePropertyToJson<ECsLoadFlags_Editor::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsLoadFlags_Editor::ToString); continue; }
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsFxPriority))
				{ WriteMemberBytePropertyToJson<ECsFxPriority::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsFxPriority::ToString); continue; }
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsSoundPriority))
				{ WriteMemberBytePropertyToJson<ECsSoundPriority::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsSoundPriority::ToString); continue; }
				// ECsProjectileMovementFunctionType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsProjectileMovementFunctionType))
				{ WriteMemberBytePropertyToJson<ECsProjectileMovementFunctionType::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsProjectileMovementFunctionType::ToString); continue; }
				// ECsParametricFunctionType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsParametricFunctionType))
				{ WriteMemberBytePropertyToJson<ECsParametricFunctionType::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsParametricFunctionType::ToString); continue; }
				// ECsItemMemberValueType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsItemMemberValueType))
				{ WriteMemberBytePropertyToJson<ECsItemMemberValueType::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsItemMemberValueType::ToString); continue; }
				// ECsItemOnConsumeContentAction
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsItemOnConsumeContentAction))
				{ WriteMemberBytePropertyToJson<ECsItemOnConsumeContentAction::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsItemOnConsumeContentAction::ToString); continue; }

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
				if (Property->HasMetaData(*(ECsCommonLoadCached::Str::BitmaskEnum)))
				{
																//    TEXT("BitmaskEnum")
					const FString BitmaskEnum = Property->GetMetaData(*(ECsCommonLoadCached::Str::BitmaskEnum));

					// (BitmaskEnum == TEXT("ECsLoadFlags"))
					if (BitmaskEnum == ECsCommonLoadCached::Str::CsLoadFlags)
					{
						InJsonWriter->WriteValue(MemberName, LoadFlagsToString(*Member));
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
	const FString NoCategory = ECsCached::Str::Empty;
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
			if (LastCategory != ECsCached::Str::Empty)
				InJsonWriter->WriteObjectEnd();
			InJsonWriter->WriteObjectStart(Category);

			LastCategory = Category;
		}

		// TAssetSubclassOf
		if (UAssetClassProperty* AssetClassProperty = Cast<UAssetClassProperty>(*It))
		{
			// ACsData_Projectile
			if (AssetClassProperty->MetaClass == ACsData_Projectile::StaticClass())
			{ WriteAssetClassPropertyToJson<ACsData_Projectile>(InJsonWriter, AssetClassProperty, InStruct, MemberName); continue; }
			// ACsData_ProjectileImpact
			if (AssetClassProperty->MetaClass == ACsData_ProjectileImpact::StaticClass())
			{ WriteAssetClassPropertyToJson<ACsData_ProjectileImpact>(InJsonWriter, AssetClassProperty, InStruct, MemberName); continue; }
			// ACsData
			if (AssetClassProperty->MetaClass == ACsData::StaticClass())
			{ WriteAssetClassPropertyToJson<ACsData>(InJsonWriter, AssetClassProperty, InStruct, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// TAssetPtr
		if (UAssetObjectProperty* AssetObjectProperty = Cast<UAssetObjectProperty>(*It))
		{
			// UStaticMesh
			if (AssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ WriteAssetObjectPropertyToJson<UStaticMesh>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// USkeletalMesh
			if (AssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ WriteAssetObjectPropertyToJson<USkeletalMesh>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstance
			if (AssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ WriteAssetObjectPropertyToJson<UMaterialInstance>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstanceConstant
			if (AssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == CS_SINGLETON)
				{ WriteAssetObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
				if (AssetObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ WriteFixedArrayAssetObjectPropertyToJson_EnumSize<UMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(InJsonWriter, AssetObjectProperty, InStruct, MemberName, &ECsInteractiveState::ToString); continue; }

				if (WriteStructToJson_Internal_Helper(Internal, Property, InJsonWriter, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// UPhysicalMaterial
			if (AssetObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ WriteAssetObjectPropertyToJson<UPhysicalMaterial>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UPhysicsAsset
			if (AssetObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ WriteAssetObjectPropertyToJson<UPhysicsAsset>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UCurveFloat
			if (AssetObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ WriteAssetObjectPropertyToJson<UCurveFloat>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UCurveVector
			if (AssetObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ WriteAssetObjectPropertyToJson<UCurveVector>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// USoundCue
			if (AssetObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ WriteAssetObjectPropertyToJson<USoundCue>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UParticleSystem
			if (AssetObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ WriteAssetObjectPropertyToJson<UParticleSystem>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UAnimSequence
			if (AssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ WriteAssetObjectPropertyToJson<UAnimSequence>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UAnimMontage
			if (AssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ WriteAssetObjectPropertyToJson<UAnimMontage>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace1D
			if (AssetObjectProperty->PropertyClass == UBlendSpace1D::StaticClass())
			{ WriteAssetObjectPropertyToJson<UBlendSpace1D>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ WriteAssetObjectPropertyToJson<UBlendSpace>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UAnimBlueprint
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ WriteAssetObjectPropertyToJson_AnimBlueprint(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UBlueprint
			if (AssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == CS_SINGLETON)
				{ WriteAssetObjectPropertyToJson_Blueprint(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
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
			// FCsFpsStaticMesh
			if (StructProperty->Struct == FCsFpsStaticMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsStaticMesh>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
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
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpsSoundElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

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
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpsFxElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

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
				{ WriteMemberFixedArrayStructPropertyToJson_EnumSize<FCsInputActionMappings, ECsInputDevice::Type, ECS_INPUT_DEVICE_MAX>(InJsonWriter, StructProperty, InStruct, MemberName, &ECsInputDevice::ToString, nullptr); continue; }
			}
			// FCsInputActionMapping
			if (StructProperty->Struct == FCsInputActionMapping::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsInputActionMapping>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsDrawDistance
			if (StructProperty->Struct == FCsDrawDistance::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsDrawDistance>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
			// FCsFpsDrawDistance
			if (StructProperty->Struct == FCsFpsDrawDistance::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsDrawDistance>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
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
			// FCsData_ProjectilePtr
			if (StructProperty->Struct == FCsData_ProjectilePtr::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsData_ProjectilePtr>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }
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

			// EnumStruct
			{
				// FECsAssetType
				if (StructProperty->Struct == FECsAssetType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsAssetType>(InJsonWriter, StructProperty, InStruct, MemberName); continue; }
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
			// TAssetPtr
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerAssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UStaticMesh>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// USkeletalMesh
				if (InnerAssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<USkeletalMesh>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstance
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UMaterialInstance>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UAnimSequence>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UAnimMontage>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// UBlueprint
				if (InnerAssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UBlueprint>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }

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
				// FCsFpsFxElement
				if (InnerStructProperty->Struct == FCsFpsFxElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpsFxElement>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsSoundElement>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpsSoundElement>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }
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
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			// enum
			if (ByteProperty->IsEnum())
			{
				// ECollisionEnabled
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionEnabled))
				{ WriteMemberBytePropertyToJson<ECollisionEnabled::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECollisionEnabled::ToString); continue; }
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionChannel))
				{ WriteMemberBytePropertyToJson<ECollisionChannel>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsCollisionChannel::ToString); continue; }
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionResponse))
				{ WriteMemberBytePropertyToJson<ECollisionResponse>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsCollisionResponse::ToString); continue; }
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::HorizTextAligment))
				{ WriteMemberBytePropertyToJson<EHorizTextAligment>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsHorizTextAligment::ToString); continue; }
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::VerticalTextAligment))
				{ WriteMemberBytePropertyToJson<EVerticalTextAligment>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsVerticalTextAligment::ToString); continue; }
				// ECsLoadFlags_Editor
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsLoadFlags_Editor))
				{ WriteMemberBytePropertyToJson<ECsLoadFlags_Editor::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsLoadFlags_Editor::ToString); continue; }
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsFxPriority))
				{ WriteMemberBytePropertyToJson<ECsFxPriority::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsFxPriority::ToString); continue; }
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsSoundPriority))
				{ WriteMemberBytePropertyToJson<ECsSoundPriority::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsSoundPriority::ToString); continue; }
				// ECsProjectileMovementFunctionType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsProjectileMovementFunctionType))
				{ WriteMemberBytePropertyToJson<ECsProjectileMovementFunctionType::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsProjectileMovementFunctionType::ToString); continue; }
				// ECsParametricFunctionType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsParametricFunctionType))
				{ WriteMemberBytePropertyToJson<ECsParametricFunctionType::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsParametricFunctionType::ToString); continue; }
				// ECsItemMemberValueType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsItemMemberValueType))
				{ WriteMemberBytePropertyToJson<ECsItemMemberValueType::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsItemMemberValueType::ToString); continue; }
				// ECsItemOnConsumeContentAction
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsItemOnConsumeContentAction))
				{ WriteMemberBytePropertyToJson<ECsItemOnConsumeContentAction::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsItemOnConsumeContentAction::ToString); continue; }

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
				if (Property->HasMetaData(*(ECsCommonLoadCached::Str::BitmaskEnum)))
				{
																//    TEXT("BitmaskEnum")
					const FString BitmaskEnum = Property->GetMetaData(*(ECsCommonLoadCached::Str::BitmaskEnum));

					// (BitmaskEnum == TEXT("ECsLoadFlags"))
					if (BitmaskEnum == ECsCommonLoadCached::Str::CsLoadFlags)
					{
						InJsonWriter->WriteValue(MemberName, LoadFlagsToString(*Member));
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
	const FString NoCategory = ECsCached::Str::Empty;
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
			if (LastCategory != ECsCached::Str::Empty)
				InJsonWriter->WriteObjectEnd();
			InJsonWriter->WriteObjectStart(Category);

			LastCategory = Category;
		}

		// TAssetSubclassOf
		if (UAssetClassProperty* AssetClassProperty = Cast<UAssetClassProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InObject, InClass))
					continue;
			}
			continue;
		}
		// TAssetPtr
		if (UAssetObjectProperty* AssetObjectProperty = Cast<UAssetObjectProperty>(*It))
		{
			// UStaticMesh
			if (AssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ WriteAssetObjectPropertyToJson<UStaticMesh>(InJsonWriter, AssetObjectProperty, InObject, MemberName); continue; }
			// USkeletalMesh
			if (AssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ WriteAssetObjectPropertyToJson<USkeletalMesh>(InJsonWriter, AssetObjectProperty, InObject, MemberName); continue; }
			// UMaterialInstance
			if (AssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ WriteAssetObjectPropertyToJson<UMaterialInstance>(InJsonWriter, AssetObjectProperty, InObject, MemberName); continue; }
			// UMaterialInstanceConstant
			if (AssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{ WriteAssetObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, AssetObjectProperty, InObject, MemberName); continue; }
			// UPhysicalMaterial
			if (AssetObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ WriteAssetObjectPropertyToJson<UPhysicalMaterial>(InJsonWriter, AssetObjectProperty, InObject, MemberName); continue; }
			// UPhysicsAsset
			if (AssetObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ WriteAssetObjectPropertyToJson<UPhysicsAsset>(InJsonWriter, AssetObjectProperty, InObject, MemberName); continue; }
			// UAnimSequence
			if (AssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ WriteAssetObjectPropertyToJson<UAnimSequence>(InJsonWriter, AssetObjectProperty, InObject, MemberName); continue; }
			// UAnimMontage
			if (AssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ WriteAssetObjectPropertyToJson<UAnimMontage>(InJsonWriter, AssetObjectProperty, InObject, MemberName); continue; }
			// UBlendSpace
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ WriteAssetObjectPropertyToJson<UBlendSpace>(InJsonWriter, AssetObjectProperty, InObject, MemberName); continue; }
			// UAnimBlueprint
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ WriteAssetObjectPropertyToJson_AnimBlueprint(InJsonWriter, AssetObjectProperty, InObject, MemberName); continue; }
			// USoundCue
			if (AssetObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ WriteAssetObjectPropertyToJson<USoundCue>(InJsonWriter, AssetObjectProperty, InObject, MemberName); continue; }
			// UParticleSystem
			if (AssetObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ WriteAssetObjectPropertyToJson<UParticleSystem>(InJsonWriter, AssetObjectProperty, InObject, MemberName); continue; }
			// UCurveVector
			if (AssetObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ WriteAssetObjectPropertyToJson<UCurveVector>(InJsonWriter, AssetObjectProperty, InObject, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InObject, InClass))
					continue;
			}
			continue;
		}
		// Structs
		else
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
			// FCsFpsStaticMesh
			if (StructProperty->Struct == FCsFpsStaticMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsStaticMesh>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
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
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpsSoundElement>(InJsonWriter, StructProperty, InObject, MemberName); continue; }

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
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteMemberStructPropertyToJson<FCsFpsFxElement>(InJsonWriter, StructProperty, InObject, MemberName); continue; }

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
			// FCsFpsDrawDistance
			if (StructProperty->Struct == FCsFpsDrawDistance::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsDrawDistance>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
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

			// EnumStruct
			{
				// FECsAssetType
				if (StructProperty->Struct == FECsAssetType::StaticStruct())
				{ WriteMemberEnumStructPropertyToJson<FECsAssetType>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
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
			// TAssetPtr
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// UMaterialInstance
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UMaterialInstance>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UAnimSequence>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UAnimMontage>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// UBlueprint
				if (InnerAssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UBlueprint>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }

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
				// FCsFpsFxElement
				if (InnerStructProperty->Struct == FCsFpsFxElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpsFxElement>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsSoundElement>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsFpsSoundElement>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
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
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			// enum
			if (ByteProperty->IsEnum())
			{
				// ECollisionEnabled
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionEnabled))
				{ WriteMemberBytePropertyToJson<ECollisionEnabled::Type>(InJsonWriter, ByteProperty, InObject, MemberName, &ECollisionEnabled::ToString); continue; }
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionChannel))
				{ WriteMemberBytePropertyToJson<ECollisionChannel>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsCollisionChannel::ToString); continue; }
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionResponse))
				{ WriteMemberBytePropertyToJson<ECollisionResponse>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsCollisionResponse::ToString); continue; }
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::HorizTextAligment))
				{ WriteMemberBytePropertyToJson<EHorizTextAligment>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsHorizTextAligment::ToString); continue; }
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::VerticalTextAligment))
				{ WriteMemberBytePropertyToJson<EVerticalTextAligment>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsVerticalTextAligment::ToString); continue; }
				// ECsLoadFlags_Editor
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsLoadFlags_Editor))
				{ WriteMemberBytePropertyToJson<ECsLoadFlags_Editor::Type>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsLoadFlags_Editor::ToString); continue; }
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsFxPriority))
				{ WriteMemberBytePropertyToJson<ECsFxPriority::Type>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsFxPriority::ToString); continue; }
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsSoundPriority))
				{ WriteMemberBytePropertyToJson<ECsSoundPriority::Type>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsSoundPriority::ToString); continue; }
				// ECsParametricFunctionType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsParametricFunctionType))
				{ WriteMemberBytePropertyToJson<ECsParametricFunctionType::Type>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsParametricFunctionType::ToString); continue; }
				// ECsItemMemberValueType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsItemMemberValueType))
				{ WriteMemberBytePropertyToJson<ECsItemMemberValueType::Type>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsItemMemberValueType::ToString); continue; }
				// ECsInteractiveCollision
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsInteractiveCollision))
				{
					if (ByteProperty->ArrayDim == CS_SINGLETON)
					{ WriteMemberBytePropertyToJson<ECsInteractiveCollision::Type>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsInteractiveCollision::ToString); continue; }
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
				if (Property->HasMetaData(*(ECsCommonLoadCached::Str::BitmaskEnum)))
				{
																//    TEXT("BitmaskEnum")
					const FString BitmaskEnum = Property->GetMetaData(*(ECsCommonLoadCached::Str::BitmaskEnum));

					// (BitmaskEnum == TEXT("ECsLoadFlags"))
					if (BitmaskEnum == ECsCommonLoadCached::Str::CsLoadFlags)
					{
						InJsonWriter->WriteValue(MemberName, LoadFlagsToString(*Member));
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

void UCsCommon_Load::WriteToAssetObjectPropertyFromJson_AnimBlueprint(TSharedPtr<FJsonObject> &JsonObject, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName)
{
	if (TAssetPtr<UAnimBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UAnimBlueprint>>(InObject))
	{
		FString AssetName = JsonObject->GetStringField(MemberName);

		// (AssetName.EndsWith(TEXT("_C")))
		if (AssetName.EndsWith(ECsLoadCached::Str::_C))
			AssetName.RemoveFromEnd(ECsLoadCached::Str::_C);

		*Member = TAssetPtr<UAnimBlueprint>(AssetName);
	}
}

void UCsCommon_Load::WriteToAssetObjectPropertyFromJson_Blueprint(TSharedPtr<FJsonObject> &JsonObject, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName)
{
	if (TAssetPtr<UBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>>(InObject))
	{
		FString AssetName = JsonObject->GetStringField(MemberName);

		// (AssetName.EndsWith(TEXT("_C")))
		if (AssetName.EndsWith(ECsLoadCached::Str::_C))
			AssetName.RemoveFromEnd(ECsLoadCached::Str::_C);

		*Member = TAssetPtr<UBlueprint>(AssetName);
	}
}

void UCsCommon_Load::WriteToMemberStructPropertyFromJson_Transform(TSharedPtr<FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString &MemberName)
{
	if (FTransform* Member = StructProperty->ContainerPtrToValuePtr<FTransform>(InObject))
	{
		TSharedPtr<FJsonObject> Object = JsonObject->Values.Find(ECsCommonLoadCached::Str::Transform)->Get()->AsObject();

		// Rotation
		FRotator Rotation;
														// TEXT("Rotation")
		Rotation.InitFromString(Object->GetStringField(ECsCommonLoadCached::Str::Rotation));
		FVector RotationAsVector = FVector(Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
		FQuat Quat = FQuat::MakeFromEuler(RotationAsVector);

		Member->SetRotation(Quat);
		// Translation
		FVector Translation;
															//TEXT("Translation")
		Translation.InitFromString(Object->GetStringField(ECsCommonLoadCached::Str::Translation));

		Member->SetTranslation(Translation);
		// Scale
		FVector Scale;
													//  TEXT("Scale")
		Scale.InitFromString(Object->GetStringField(ECsCommonLoadCached::Str::Scale));

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
		TSharedPtr<FJsonObject> Object		= ArrayObject->Values.Find(ECsCommonLoadCached::Str::Transform)->Get()->AsObject();

		FTransform& Element = (*Member)[I];

		// Rotation
		FRotator Rotation;
													// TEXT("Rotation")
		Rotation.InitFromString(Object->GetStringField(ECsCommonLoadCached::Str::Rotation));
		FVector RotationAsVector = FVector(Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
		FQuat Quat = FQuat::MakeFromEuler(RotationAsVector);

		Element.SetRotation(Quat);
		// Translation
		FVector Translation;
														//TEXT("Translation")
		Translation.InitFromString(Object->GetStringField(ECsCommonLoadCached::Str::Translation));

		Element.SetTranslation(Translation);
		// Scale
		FVector Scale;
												//  TEXT("Scale")
		Scale.InitFromString(Object->GetStringField(ECsCommonLoadCached::Str::Scale));

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

bool UCsCommon_Load::ReadStructFromJson_Internal_Helper(TCsReadStructFromJson_Internal Internal, UProperty* Property, TSharedPtr<class FJsonObject> &JsonObject, void* InStruct, UScriptStruct* const &InScriptStruct)
{
	if (Internal)
		return (*Internal)(Property, JsonObject, InStruct, InScriptStruct);
	return false;
}

bool UCsCommon_Load::ReadObjectFromJson_Internal_Helper(TCsReadObjectFromJson_Internal Internal, UProperty* Property, TSharedPtr<class FJsonObject> &JsonObject, void* InObject, UClass* const &InClass)
{
	return false;
}

void UCsCommon_Load::ReadStructFromJson(TSharedPtr<FJsonObject> &JsonObject, void* InStruct, UScriptStruct* const &InScriptStruct, TCsReadStructFromJson_Internal Internal /*=nullptr*/)
{
	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// TAssetSubclassOf
		if (UAssetClassProperty* AssetClassProperty = Cast<UAssetClassProperty>(*It))
		{
			// ACsData_Projectile
			if (AssetClassProperty->MetaClass == ACsData_Projectile::StaticClass())
			{ WriteToAssetClassPropertyFromJson<ACsData_Projectile>(JsonObject, AssetClassProperty, InStruct, MemberName); continue; }
			// ACsData_ProjectileImpact
			if (AssetClassProperty->MetaClass == ACsData_ProjectileImpact::StaticClass())
			{ WriteToAssetClassPropertyFromJson<ACsData_ProjectileImpact>(JsonObject, AssetClassProperty, InStruct, MemberName); continue; }
			// ACsData
			if (AssetClassProperty->MetaClass == ACsData::StaticClass())
			{ WriteToAssetClassPropertyFromJson<ACsData>(JsonObject, AssetClassProperty, InStruct, MemberName); continue; }
			
			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// TAssetPtr
		if (UAssetObjectProperty* AssetObjectProperty = Cast<UAssetObjectProperty>(*It))
		{
			// UStaticMesh
			if (AssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UStaticMesh>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// USkeletalMesh
			if (AssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<USkeletalMesh>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstance
			if (AssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UMaterialInstance>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstanceConstant
			if (AssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == CS_SINGLETON)
				{ WriteToAssetObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
				if (AssetObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ WriteToFixedArrayAssetObjectPropertyFromJson_EnumSize<UMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(JsonObject, AssetObjectProperty, InStruct, MemberName, &ECsInteractiveState::ToString); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// UPhysicalMaterial
			if (AssetObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UPhysicalMaterial>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UPhysicsAsset
			if (AssetObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UPhysicsAsset>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UCurveFloat
			if (AssetObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UCurveFloat>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UCurveVector
			if (AssetObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UCurveVector>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// USoundCue
			if (AssetObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<USoundCue>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UParticleSystem
			if (AssetObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UParticleSystem>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UAnimSequence
			if (AssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UAnimSequence>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UAnimMontage
			if (AssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UAnimMontage>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace1D
			if (AssetObjectProperty->PropertyClass == UBlendSpace1D::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UBlendSpace1D>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UBlendSpace>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UAnimBlueprint
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ WriteToAssetObjectPropertyFromJson_AnimBlueprint(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UBlueprint
			if (AssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{ WriteToAssetObjectPropertyFromJson_Blueprint(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }

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
			// FCsFpsStaticMesh
			if (StructProperty->Struct == FCsFpsStaticMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsStaticMesh>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
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
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpsSoundElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

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
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpsFxElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

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
				{ WriteToMemberFixedArrayStructPropertyFromJson_EnumSize<FCsInputActionMappings, ECsInputDevice::Type, ECS_INPUT_DEVICE_MAX>(JsonObject, StructProperty, InStruct, MemberName, &ECsInputDevice::ToString, nullptr); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsInputActionMapping
			if (StructProperty->Struct == FCsInputActionMapping::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsInputActionMapping>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsDrawDistance
			if (StructProperty->Struct == FCsDrawDistance::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsDrawDistance>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsFpsDrawDistance
			if (StructProperty->Struct == FCsFpsDrawDistance::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsDrawDistance>(JsonObject, StructProperty, InStruct, MemberName); continue; }
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
			// FCsData_ProjectilePtr
			if (StructProperty->Struct == FCsData_ProjectilePtr::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsData_ProjectilePtr>(JsonObject, StructProperty, InStruct, MemberName); continue; }
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

			// EnumStruct
			{
				// FECsAssetType
				if (StructProperty->Struct == FECsAssetType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsAssetType, EMCsAssetType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
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
			// TAssetPtr
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerAssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UStaticMesh>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// USkeletalMesh
				if (InnerAssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<USkeletalMesh>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstance
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UMaterialInstance>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UAnimSequence>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UAnimMontage>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UBlueprint
				if (InnerAssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UBlueprint>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				
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
				// FCsFpsFxElement
				if (InnerStructProperty->Struct == FCsFpsFxElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpsFxElement>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsSoundElement>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpsSoundElement>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
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
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			// enum
			if (ByteProperty->IsEnum())
			{
				// ECollisionEnabled
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionEnabled))
				{
					if (ECollisionEnabled::Type* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionEnabled::Type>(InStruct))
					{ *Member = ECollisionEnabled::ToType(JsonObject->GetStringField(MemberName)); continue; }
					continue;
				}
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionChannel))
				{
					if (ECollisionChannel* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionChannel>(InStruct))
					{ *Member = ECsCollisionChannel::ToType(JsonObject->GetStringField(MemberName)); continue; }
					continue;
				}
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionResponse))
				{
					if (ECollisionResponse* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionResponse>(InStruct))
					{ *Member = ECsCollisionResponse::ToType(JsonObject->GetStringField(MemberName)); continue; }
					continue;
				}
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::HorizTextAligment))
				{
					if (EHorizTextAligment* Member = ByteProperty->ContainerPtrToValuePtr<EHorizTextAligment>(InStruct))
					{ *Member = ECsHorizTextAligment::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::VerticalTextAligment))
				{
					if (EVerticalTextAligment* Member = ByteProperty->ContainerPtrToValuePtr<EVerticalTextAligment>(InStruct))
					{ *Member = ECsVerticalTextAligment::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsLoadFlags_Editor
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsLoadFlags_Editor))
				{
					if (TCsLoadFlags_Editor* Member = ByteProperty->ContainerPtrToValuePtr<TCsLoadFlags_Editor>(InStruct))
					{ *Member = ECsLoadFlags_Editor::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsFxPriority))
				{
					if (TCsFxPriority* Member = ByteProperty->ContainerPtrToValuePtr<TCsFxPriority>(InStruct))
					{ *Member = ECsFxPriority::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsSoundPriority))
				{
					if (TCsSoundPriority* Member = ByteProperty->ContainerPtrToValuePtr<TCsSoundPriority>(InStruct))
					{ *Member = ECsSoundPriority::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsProjectileMovementFunctionType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsProjectileMovementFunctionType))
				{
					if (TCsProjectileMovementFunctionType* Member = ByteProperty->ContainerPtrToValuePtr<TCsProjectileMovementFunctionType>(InStruct))
					{ *Member = ECsProjectileMovementFunctionType::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsParametricFunctionType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsParametricFunctionType))
				{
					if (TCsParametricFunctionType* Member = ByteProperty->ContainerPtrToValuePtr<TCsParametricFunctionType>(InStruct))
					{ *Member = ECsParametricFunctionType::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsItemMemberValueType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsProjectileMovementFunctionType))
				{
					if (TCsItemMemberValueType* Member = ByteProperty->ContainerPtrToValuePtr<TCsItemMemberValueType>(InStruct))
					{ *Member = ECsItemMemberValueType::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsItemOnConsumeContentAction
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsItemOnConsumeContentAction))
				{
					if (TCsItemOnConsumeContentAction* Member = ByteProperty->ContainerPtrToValuePtr<TCsItemOnConsumeContentAction>(InStruct))
					{ *Member = ECsItemOnConsumeContentAction::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}

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
							*Member = StringtoLoadFlags(JsonObject->GetStringField(MemberName)); continue;
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
	const FString NoCategory = ECsCached::Str::Empty;
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

		// TAssetSubclassOf
		if (UAssetClassProperty* AssetClassProperty = Cast<UAssetClassProperty>(*It))
		{
			// ACsData_Projectile
			if (AssetClassProperty->MetaClass == ACsData_Projectile::StaticClass())
			{ WriteToAssetClassPropertyFromJson<ACsData_Projectile>(JsonObject, AssetClassProperty, InStruct, MemberName); continue; }
			// ACsData_ProjectileImpact
			if (AssetClassProperty->MetaClass == ACsData_ProjectileImpact::StaticClass())
			{ WriteToAssetClassPropertyFromJson<ACsData_ProjectileImpact>(JsonObject, AssetClassProperty, InStruct, MemberName); continue; }
			// ACsData
			if (AssetClassProperty->MetaClass == ACsData::StaticClass())
			{ WriteToAssetClassPropertyFromJson<ACsData>(JsonObject, AssetClassProperty, InStruct, MemberName); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// TAssetPtr
		if (UAssetObjectProperty* AssetObjectProperty = Cast<UAssetObjectProperty>(*It))
		{
			// UStaticMesh
			if (AssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UStaticMesh>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// USkeletalMesh
			if (AssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<USkeletalMesh>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstance
			if (AssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UMaterialInstance>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UMaterialInstanceConstant
			if (AssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == CS_SINGLETON)
				{ WriteToAssetObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
				if (AssetObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ WriteToFixedArrayAssetObjectPropertyFromJson_EnumSize<UMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(JsonObject, AssetObjectProperty, InStruct, MemberName, &ECsInteractiveState::ToString); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// UPhysicalMaterial
			if (AssetObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UPhysicalMaterial>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UPhysicsAsset
			if (AssetObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UPhysicsAsset>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UCurveFloat
			if (AssetObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UCurveFloat>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UCurveVector
			if (AssetObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UCurveVector>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// USoundCue
			if (AssetObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<USoundCue>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UParticleSystem
			if (AssetObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UParticleSystem>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UAnimSequence
			if (AssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UAnimSequence>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UAnimMontage
			if (AssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UAnimMontage>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace1D
			if (AssetObjectProperty->PropertyClass == UBlendSpace1D::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UBlendSpace1D>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UBlendSpace
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UBlendSpace>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UAnimBlueprint
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ WriteToAssetObjectPropertyFromJson_AnimBlueprint(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UBlueprint
			if (AssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{ WriteToAssetObjectPropertyFromJson_Blueprint(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }

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
			// FCsFpsStaticMesh
			if (StructProperty->Struct == FCsFpsStaticMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsStaticMesh>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
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
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpsSoundElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

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
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpsFxElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

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
				{ WriteToMemberFixedArrayStructPropertyFromJson_EnumSize<FCsInputActionMappings, ECsInputDevice::Type, ECS_INPUT_DEVICE_MAX>(JsonObject, StructProperty, InStruct, MemberName, &ECsInputDevice::ToString, nullptr); continue; }

				if (ReadStructFromJson_Internal_Helper(Internal, Property, JsonObject, InStruct, InScriptStruct)) { continue; }
				continue;
			}
			// FCsInputActionMapping
			if (StructProperty->Struct == FCsInputActionMapping::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsInputActionMapping>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsDrawDistance
			if (StructProperty->Struct == FCsDrawDistance::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsDrawDistance>(JsonObject, StructProperty, InStruct, MemberName); continue; }
			// FCsFpsDrawDistance
			if (StructProperty->Struct == FCsFpsDrawDistance::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsDrawDistance>(JsonObject, StructProperty, InStruct, MemberName); continue; }
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
			// FCsData_ProjectilePtr
			if (StructProperty->Struct == FCsData_ProjectilePtr::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsData_ProjectilePtr>(JsonObject, StructProperty, InStruct, MemberName); continue; }
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
			
			// EnumStruct
			{
				// FECsAssetType
				if (StructProperty->Struct == FECsAssetType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsAssetType, EMCsAssetType>(JsonObject, StructProperty, InStruct, MemberName); continue; }
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
			// TAssetPtr
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerAssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UStaticMesh>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// USkeletalMesh
				if (InnerAssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<USkeletalMesh>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstance
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UMaterialInstance>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UAnimSequence>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UAnimMontage>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }
				// UBlueprint
				if (InnerAssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UBlueprint>(JsonObject, ArrayProperty, InStruct, MemberName); continue; }

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
				// FCsFpsFxElement
				if (InnerStructProperty->Struct == FCsFpsFxElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpsFxElement>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsSoundElement>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpsSoundElement>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }
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
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			// enum
			if (ByteProperty->IsEnum())
			{
				// ECollisionEnabled
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionEnabled))
				{
					if (ECollisionEnabled::Type* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionEnabled::Type>(InStruct))
					{ *Member = ECollisionEnabled::ToType(JsonObject->GetStringField(MemberName)); continue; }
					continue;
				}
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionChannel))
				{
					if (ECollisionChannel* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionChannel>(InStruct))
					{ *Member = ECsCollisionChannel::ToType(JsonObject->GetStringField(MemberName)); continue; }
					continue;
				}
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionResponse))
				{
					if (ECollisionResponse* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionResponse>(InStruct))
					{ *Member = ECsCollisionResponse::ToType(JsonObject->GetStringField(MemberName)); continue; }
					continue;
				}
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::HorizTextAligment))
				{
					if (EHorizTextAligment* Member = ByteProperty->ContainerPtrToValuePtr<EHorizTextAligment>(InStruct))
					{ *Member = ECsHorizTextAligment::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::VerticalTextAligment))
				{
					if (EVerticalTextAligment* Member = ByteProperty->ContainerPtrToValuePtr<EVerticalTextAligment>(InStruct))
					{ *Member = ECsVerticalTextAligment::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsLoadFlags_Editor
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsLoadFlags_Editor))
				{
					if (TCsLoadFlags_Editor* Member = ByteProperty->ContainerPtrToValuePtr<TCsLoadFlags_Editor>(InStruct))
					{ *Member = ECsLoadFlags_Editor::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsFxPriority))
				{
					if (TCsFxPriority* Member = ByteProperty->ContainerPtrToValuePtr<TCsFxPriority>(InStruct))
					{ *Member = ECsFxPriority::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsSoundPriority))
				{
					if (TCsSoundPriority* Member = ByteProperty->ContainerPtrToValuePtr<TCsSoundPriority>(InStruct))
					{ *Member = ECsSoundPriority::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsProjectileMovementFunctionType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsProjectileMovementFunctionType))
				{
					if (TCsProjectileMovementFunctionType* Member = ByteProperty->ContainerPtrToValuePtr<TCsProjectileMovementFunctionType>(InStruct))
					{ *Member = ECsProjectileMovementFunctionType::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsParametricFunctionType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsParametricFunctionType))
				{
					if (TCsParametricFunctionType* Member = ByteProperty->ContainerPtrToValuePtr<TCsParametricFunctionType>(InStruct))
					{ *Member = ECsParametricFunctionType::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsItemMemberValueType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsProjectileMovementFunctionType))
				{
					if (TCsItemMemberValueType* Member = ByteProperty->ContainerPtrToValuePtr<TCsItemMemberValueType>(InStruct))
					{ *Member = ECsItemMemberValueType::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsItemOnConsumeContentAction
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsItemOnConsumeContentAction))
				{
					if (TCsItemOnConsumeContentAction* Member = ByteProperty->ContainerPtrToValuePtr<TCsItemOnConsumeContentAction>(InStruct))
					{ *Member = ECsItemOnConsumeContentAction::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}

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
							*Member = StringtoLoadFlags(JsonObject->GetStringField(MemberName)); continue;
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
	const FString NoCategory = ECsCached::Str::Empty;
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
		
		// TAssetSubclassOf
		if (UAssetClassProperty* AssetClassProperty = Cast<UAssetClassProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, JsonObject, InObject, InClass))
					continue;
			}
			continue;
		}
		// TAssetPtr
		if (UAssetObjectProperty* AssetObjectProperty = Cast<UAssetObjectProperty>(*It))
		{
			// UStaticMesh
			if (AssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UStaticMesh>(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }
			// USkeletalMesh
			if (AssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<USkeletalMesh>(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }
			// UMaterialInstance
			if (AssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UMaterialInstance>(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }
			// UMaterialInstanceConstant
			if (AssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }
			// UPhysicalMaterial
			if (AssetObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UPhysicalMaterial>(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }
			// UPhysicsAsset
			if (AssetObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UPhysicsAsset>(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }
			// USoundCue
			if (AssetObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<USoundCue>(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }
			// UParticleSystem
			if (AssetObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UParticleSystem>(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }
			// UAnimSequence
			if (AssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UAnimSequence>(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }
			// UAnimMontage
			if (AssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UAnimMontage>(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }
			// UBlendSpace
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UBlendSpace>(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }
			// UAnimBlueprint
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ WriteToAssetObjectPropertyFromJson_AnimBlueprint(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }
			// UBlueprint
			if (AssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == CS_SINGLETON)
				{ WriteToAssetObjectPropertyFromJson_Blueprint(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }

				if (ReadObjectFromJson_Internal_Helper(Internal, Property, JsonObject, InObject, InClass)) { continue; }
				continue;
			}
			// UCurveVector
			if (AssetObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UCurveVector>(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }
			// UCurveFloat
			if (AssetObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UCurveFloat>(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }

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
			// FCsFpsStaticMesh
			if (StructProperty->Struct == FCsFpsStaticMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsStaticMesh>(JsonObject, StructProperty, InObject, MemberName); continue; }
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
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpsSoundElement>(JsonObject, StructProperty, InObject, MemberName); continue; }

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
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ WriteToMemberStructPropertyFromJson<FCsFpsFxElement>(JsonObject, StructProperty, InObject, MemberName); continue; }

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
			// FCsFpsDrawDistance
			if (StructProperty->Struct == FCsFpsDrawDistance::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsDrawDistance>(JsonObject, StructProperty, InObject, MemberName); continue; }
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

			// EnumStruct
			{
				// FECsAssetType
				if (StructProperty->Struct == FECsAssetType::StaticStruct())
				{ WriteToMemberEnumStructPropertyFromJson<FECsAssetType, EMCsAssetType>(JsonObject, StructProperty, InObject, MemberName); continue; }
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
			// TAssetPtr
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// UMaterialInstance
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UMaterialInstance>(JsonObject, ArrayProperty, InObject, MemberName); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, ArrayProperty, InObject, MemberName); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UAnimSequence>(JsonObject, ArrayProperty, InObject, MemberName); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UAnimMontage>(JsonObject, ArrayProperty, InObject, MemberName); continue; }
				// UBlueprint
				if (InnerAssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UBlueprint>(JsonObject, ArrayProperty, InObject, MemberName); continue; }
				
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
				// FCsFpsFxElement
				if (InnerStructProperty->Struct == FCsFpsFxElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpsFxElement>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsSoundElement>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsFpsSoundElement>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }
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
		// Byte / Enum
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			// enum
			if (ByteProperty->IsEnum())
			{
				// ECollisionEnabled
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionEnabled))
				{
					if (ECollisionEnabled::Type* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionEnabled::Type>(InObject))
					{ *Member = ECollisionEnabled::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionChannel))
				{
					if (ECollisionChannel* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionChannel>(InObject))
					{ *Member = ECsCollisionChannel::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionResponse))
				{
					if (ECollisionResponse* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionResponse>(InObject))
					{ *Member = ECsCollisionResponse::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::HorizTextAligment))
				{
					if (EHorizTextAligment* Member = ByteProperty->ContainerPtrToValuePtr<EHorizTextAligment>(InObject))
					{ *Member = ECsHorizTextAligment::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::VerticalTextAligment))
				{
					if (EVerticalTextAligment* Member = ByteProperty->ContainerPtrToValuePtr<EVerticalTextAligment>(InObject))
					{ *Member = ECsVerticalTextAligment::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsFxPriority))
				{
					if (TCsFxPriority* Member = ByteProperty->ContainerPtrToValuePtr<TCsFxPriority>(InObject))
					{ *Member = ECsFxPriority::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsSoundPriority))
				{
					if (TCsSoundPriority* Member = ByteProperty->ContainerPtrToValuePtr<TCsSoundPriority>(InObject))
					{ *Member = ECsSoundPriority::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsParametricFunctionType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsParametricFunctionType))
				{
					if (TCsParametricFunctionType* Member = ByteProperty->ContainerPtrToValuePtr<TCsParametricFunctionType>(InObject))
					{ *Member = ECsParametricFunctionType::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsItemMemberValueType
				if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsItemMemberValueType))
				{
					if (TCsItemMemberValueType* Member = ByteProperty->ContainerPtrToValuePtr<TCsItemMemberValueType>(InObject))
					{ *Member = ECsItemMemberValueType::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}

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
							*Member = StringtoLoadFlags(JsonObject->GetStringField(MemberName)); continue;
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

	// Asset References
#pragma region

		// FCsStringAssetReference
#pragma region

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_AnimMontage(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = AssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TAssetPtr<UAnimMontage>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UAnimMontage>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCached::Str::Empty)
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

			Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
			Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_AnimMontage(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = AssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TAssetPtr<UAnimMontage>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UAnimMontage>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCached::Str::Empty)
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

			Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Kilobytes);
			Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_AnimSequence(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = AssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TAssetPtr<UAnimSequence>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UAnimSequence>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCached::Str::Empty)
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
			Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
			Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_AnimSequence(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = AssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TAssetPtr<UAnimSequence>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UAnimSequence>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCached::Str::Empty)
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
			Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
			Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_MaterialInstanceConstant(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = AssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TAssetPtr<UMaterialInstanceConstant>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UMaterialInstanceConstant>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCached::Str::Empty)
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

				Reference.Size.Bytes += Texture->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
			}

			Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
			Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_MaterialInstanceConstant(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = AssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TAssetPtr<UMaterialInstanceConstant>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UMaterialInstanceConstant>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCached::Str::Empty)
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

				Reference.Size.Bytes += Texture->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
			}

			Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
			Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_Blueprint(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = AssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TAssetPtr<UBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCached::Str::Empty)
			return;

		OutAssetReferences.AddDefaulted();

		const int32 Size = OutAssetReferences.Num();

		// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TAssetPtr for UAnimBlueprint / UWidgetBlueprint does NOT have _C
		FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
										  // AssetName.EndsWith(TEXT("_C")) ? AssetName : AssetName + TEXT("_C");
		Reference.Reference				   = AssetName.EndsWith(ECsLoadCached::Str::_C) ? AssetName : AssetName + ECsLoadCached::Str::_C;
		Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
		if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
		{
			UObject* Asset = Member->LoadSynchronous();

			Reference.Size.Bytes = Asset->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
			Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
			Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_Blueprint(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = AssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TAssetPtr<UBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == ECsCached::Str::Empty)
			return;

		OutAssetReferences.AddDefaulted();

		const int32 Size = OutAssetReferences.Num();

		// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TAssetPtr for UAnimBlueprint / UWidgetBlueprint does NOT have _C
		FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
										  // AssetName.EndsWith(TEXT("_C")) ? AssetName : AssetName + TEXT("_C");
		Reference.Reference				   = AssetName.EndsWith(ECsLoadCached::Str::_C) ? AssetName : AssetName + ECsLoadCached::Str::_C;
		Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
		if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
		{
			UObject* Asset = Member->LoadSynchronous();

			Reference.Size.Bytes = Asset->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
			Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
			Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
		}
#endif // #if WITH_EDITOR
	}
}

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_AnimMontage(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArrayAssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TAssetPtr<UAnimMontage>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UAnimMontage>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == ECsCached::Str::Empty)
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

				Reference.Size.Kilobytes = UCsCommon::KilobytesToBytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_AnimMontage(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArrayAssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TAssetPtr<UAnimMontage>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UAnimMontage>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == ECsCached::Str::Empty)
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

				Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_AnimSequence(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArrayAssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TAssetPtr<UAnimSequence>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UAnimSequence>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == ECsCached::Str::Empty)
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
				Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_AnimSequence(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArrayAssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TAssetPtr<UAnimSequence>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UAnimSequence>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == ECsCached::Str::Empty)
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
				Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_MaterialInstanceConstant(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArrayAssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TAssetPtr<UMaterialInstanceConstant>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UMaterialInstanceConstant>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == ECsCached::Str::Empty)
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
					UE_LOG(LogCs, Warning, TEXT("UCsCommon::GetAssetReferenceFromArrayAssetObjectProperty_MaterialInstanceConstant: Failed to Load %s[%d]"), *MemberName, I);
					continue;
				}

				const int32 TextureCount = Asset->TextureParameterValues.Num();

				for (int32 J = 0; J < TextureCount; J++)
				{
					UTexture* Texture = Asset->TextureParameterValues[J].ParameterValue;

					if (!Texture)
						continue;

					Reference.Size.Bytes += Texture->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
				}

				Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_MaterialInstanceConstant(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArrayAssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TAssetPtr<UMaterialInstanceConstant>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UMaterialInstanceConstant>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == ECsCached::Str::Empty)
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

					Reference.Size.Bytes += Texture->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
				}

				Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_Blueprint(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArrayAssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TAssetPtr<UBlueprint>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UBlueprint>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == ECsCached::Str::Empty)
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();
			// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TAssetPtr for UWidgetBlueprint does NOT have _C
			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
											  // AssetName.EndsWith(TEXT("_C")) ? AssetName : AssetName + TEXT("_C");
			Reference.Reference				   = AssetName.EndsWith(ECsLoadCached::Str::_C) ? AssetName : AssetName + ECsLoadCached::Str::_C;
			Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
			if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
			{
				UBlueprint* Asset = (*Member)[I].LoadSynchronous();

				Reference.Size.Bytes = Asset->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
				Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
			}
#endif // #if WITH_EDITOR
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_Blueprint(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TArray<FCsStringAssetReference> &OutAssetReferences, const int32 &LoadCodes /*=ECS_LOAD_CODE_CALCULATE_RESOURCE_SIZES*/)
{
	const FString MemberName = ArrayAssetObjectProperty->GetName();

	if (!CanLoad(InObject, InClass, MemberName, LoadFlags, LoadCodes))
		return;

	if (TArray<TAssetPtr<UBlueprint>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UBlueprint>>>(InObject))
	{
		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			// (AssetName == TEXT(""))
			if (AssetName == ECsCached::Str::Empty)
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();
			// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TAssetPtr for UWidgetBlueprint does NOT have _C
			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
											  // AssetName.EndsWith(TEXT("_C")) ? AssetName : AssetName + TEXT("_C");
			Reference.Reference				   = AssetName.EndsWith(ECsLoadCached::Str::_C) ? AssetName : AssetName + ECsLoadCached::Str::_C;
			Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
			if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes))
			{
				UBlueprint* Asset = (*Member)[I].LoadSynchronous();

				Reference.Size.Bytes	 = Asset->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
				Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
				Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
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

		// TAssetSubclassOf
		if (UAssetClassProperty* AssetClassProperty = Cast<UAssetClassProperty>(*It))
		{
			// ACsData_Projectile
			if (AssetClassProperty->MetaClass == ACsData_Projectile::StaticClass())
			{ GetAssetReferenceFromAssetClassProperty<ACsData_Projectile>(AssetClassProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
			// ACsData_ProjectileImpact
			if (AssetClassProperty->MetaClass == ACsData_ProjectileImpact::StaticClass())
			{ GetAssetReferenceFromAssetClassProperty<ACsData_ProjectileImpact>(AssetClassProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes))
					continue;
			}
			continue;
		}
		// TAssetPtr
		if (UAssetObjectProperty* AssetObjectProperty = Cast<UAssetObjectProperty>(*It))
		{
			// UStaticMesh
			if (AssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UStaticMesh>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
			// USkeletalMesh
			if (AssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<USkeletalMesh>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
			// UMaterialInstance
			if (AssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UMaterialInstance>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Inclusive, OutAssetReferences, LoadCodes); continue; }
			// UMaterialInstanceConstant
			if (AssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferenceFromAssetObjectProperty_MaterialInstanceConstant(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
				if (AssetObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ GetAssetReferenceFromFixedArrayAssetObjectProperty_EnumSize_MaterialInstanceConstant<ECS_INTERACTIVE_STATE_MAX>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes))
						continue;
				}
				continue;
			}
			// UPhysicalMaterial
			if (AssetObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UPhysicalMaterial>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Inclusive, OutAssetReferences, LoadCodes); continue; }
			// UPhysicsAsset
			if (AssetObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UPhysicsAsset>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
			// UAnimSequence
			if (AssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty_AnimSequence(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
			// UAnimMontage
			if (AssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty_AnimMontage(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
			// UBlendSpace1D
			if (AssetObjectProperty->PropertyClass == UBlendSpace1D::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UBlendSpace1D>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
			// UBlendSpace
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UBlendSpace>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
			// UAnimBlueprint
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty_Blueprint(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
			// USoundCue
			if (AssetObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<USoundCue>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Inclusive, OutAssetReferences, LoadCodes); continue; }
			// UParticleSystem
			if (AssetObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UParticleSystem>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Inclusive, OutAssetReferences, LoadCodes); continue; }
			// UCurveFloat
			if (AssetObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UCurveFloat>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Inclusive, OutAssetReferences, LoadCodes); continue; }
			// UCurveVector
			if (AssetObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UCurveVector>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Inclusive, OutAssetReferences, LoadCodes); continue; }
			// UBlueprint
			if (AssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferenceFromAssetObjectProperty_Blueprint(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
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
			// FCsFpsStaticMesh
			if (StructProperty->Struct == FCsFpsStaticMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsStaticMesh>(StructProperty, InStruct, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
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
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsFpsSoundElement>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsFxElement>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
			}
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsFpsFxElement>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
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
			// FCsData_ProjectilePtr
			if (StructProperty->Struct == FCsData_ProjectilePtr::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsData_ProjectilePtr>(StructProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }

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
			// TAssetSubclassOf
			if (UAssetClassProperty* InnerAssetClassProperty = Cast<UAssetClassProperty>(ArrayProperty->Inner))
			{
				// AShooterWeaponData
				//if (InnerAssetClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerAssetClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//{ GetAssetReferenceFromArrayAssetObjectProperty<AShooterWeaponData>(ArrayProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences); continue; }
				if (Internal)
				{
					if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes))
						continue;
				}
				continue;
			}
			// TAssetPtr
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerAssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ GetAssetReferenceFromArrayAssetObjectProperty<UStaticMesh>(ArrayProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
				// USkeletalMesh
				if (InnerAssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ GetAssetReferenceFromArrayAssetObjectProperty<USkeletalMesh>(ArrayProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Exclusive, OutAssetReferences, LoadCodes); continue; }
				// UMaterialInstance
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ GetAssetReferenceFromArrayAssetObjectProperty<UMaterialInstance>(ArrayProperty, InStruct, InScriptStruct, LoadFlags, EResourceSizeMode::Inclusive, OutAssetReferences, LoadCodes); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ GetAssetReferenceFromArrayAssetObjectProperty_MaterialInstanceConstant(ArrayProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ GetAssetReferenceFromArrayAssetObjectProperty_AnimSequence(ArrayProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ GetAssetReferenceFromArrayAssetObjectProperty_AnimMontage(ArrayProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
				// UBlueprint
				if (InnerAssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ GetAssetReferenceFromArrayAssetObjectProperty_Blueprint(ArrayProperty, InStruct, InScriptStruct, LoadFlags, OutAssetReferences, LoadCodes); continue; }
				
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
				// FCsFpsFxElement
				if (InnerStructProperty->Struct == FCsFpsFxElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpsFxElement>(ArrayProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsSoundElement>(ArrayProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpsSoundElement>(ArrayProperty, InStruct, LoadFlags, OutAssetReferences, Internal, LoadCodes); continue; }
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
			// FCsFpsStaticMesh
			if (StructProperty->Struct == FCsFpsStaticMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsStaticMesh>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
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
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsFpsSoundElement>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				
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
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ GetAssetReferencesFromStructProperty<FCsFpsFxElement>(StructProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				
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
				// FCsFpsFxElement
				if (InnerStructProperty->Struct == FCsFpsFxElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpsFxElement>(ArrayProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpsSoundElement>(ArrayProperty, InObject, LoadFlags, OutAssetReferences, nullptr, LoadCodes); continue; }
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

void UCsCommon_Load::LoadTAssetPtr_AnimBlueprint(const FString &MemberName, TAssetPtr<UAnimBlueprint> AssetPtr, UAnimBlueprintGeneratedClass* &Internal)
{
	const FString& AssetName = AssetPtr.ToString();

	// (AssetName == TEXT(""))
	if (AssetName == ECsCached::Str::Empty)
	{
		Internal = nullptr;
		return;
	}

	if (Internal &&
		AssetPtr.IsValid() && AssetPtr.Get() &&
		Internal == Cast<UAnimBlueprintGeneratedClass>(Cast<UBlueprintCore>(AssetPtr.Get())->GeneratedClass))
	{
		UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetPtr_AnimBlueprint (%s): Possibly trying to load Anim Blueprint and it is already loaded"), *MemberName);
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
			UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetPtr_AnimBlueprint (%s): Failed to load Anim Blueprint at %s"), *MemberName, *AssetDescription);
		}
	}
}

void UCsCommon_Load::LoadTAssetPtr_AnimBlueprint(const FString &MemberName, TAssetPtr<UAnimBlueprint>* AssetPtr, UAnimBlueprintGeneratedClass* &Internal)
{
	const FString& AssetName = AssetPtr->ToString();

	// (AssetName == TEXT("")
	if (AssetName == ECsCached::Str::Empty)
	{
		Internal = nullptr;
		return;
	}

	if (Internal &&
		AssetPtr->IsValid() && AssetPtr->Get() &&
		Internal == Cast<UAnimBlueprintGeneratedClass>(Cast<UBlueprintCore>(AssetPtr->Get())->GeneratedClass))
	{
		UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetPtr_AnimBlueprint (%s): Possibly trying to load Anim Blueprint and it is already loaded"), *MemberName);
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
			UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetPtr_AnimBlueprint (%s): Failed to load Anim Blueprint at %s"), *MemberName, *AssetDescription);
		}
	}
}

void UCsCommon_Load::LoadAssetObjectProperty_AnimBlueprint(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TAssetPtr<UAnimBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UAnimBlueprint>>(InObject))
	{
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
			return;

										// MemberName = TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (UAnimBlueprintGeneratedClass** Internal = InternalProperty->ContainerPtrToValuePtr<UAnimBlueprintGeneratedClass*>(InObject))
				LoadTAssetPtr_AnimBlueprint(ObjectName + ECsCached::Str::Dot + MemberName, Member, *Internal);
										//  ObjectName = TEXT(".") + MemberName
		}
	}
}

void UCsCommon_Load::LoadAssetObjectProperty_AnimBlueprint(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TAssetPtr<UAnimBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UAnimBlueprint>>(InObject))
	{
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
			return;

										// MemberName = TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (UAnimBlueprintGeneratedClass** Internal = InternalProperty->ContainerPtrToValuePtr<UAnimBlueprintGeneratedClass*>(InObject))
				LoadTAssetPtr_AnimBlueprint(ObjectName + ECsCached::Str::Dot + MemberName, Member, *Internal);
										//  ObjectName + TEXT(".") + MemberName
		}
	}
}

void UCsCommon_Load::LoadTAssetPtr_Blueprint(const FString &MemberName, TAssetPtr<UBlueprint> AssetPtr, UBlueprintGeneratedClass* &Internal)
{
	const FString& AssetName = AssetPtr.ToString();

	// (AssetName == TEXT(""))
	if (AssetName == ECsCached::Str::Empty)
	{
		Internal = nullptr;
		return;
	}

	if (Internal &&
		AssetPtr.IsValid() && AssetPtr.Get() &&
		Internal == Cast<UBlueprintGeneratedClass>(Cast<UBlueprintCore>(AssetPtr.Get())->GeneratedClass))
	{
		//UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetPtr_Blueprint (%s): Possibly trying to load Blueprint and it is already loaded"), *MemberName);
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
			UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetPtr_Blueprint (%s): Failed to load Blueprint at %s"), *MemberName, *AssetDescription);
		}
	}
}

void UCsCommon_Load::LoadTAssetPtr_Blueprint(const FString &MemberName, TAssetPtr<UBlueprint>* AssetPtr, UBlueprintGeneratedClass* &Internal)
{
	const FString& AssetName = AssetPtr->ToString();

	// (AssetName == TEXT(""))
	if (AssetName == ECsCached::Str::Empty)
	{
		Internal = nullptr;
		return;
	}

	if (Internal &&
		AssetPtr->IsValid() && AssetPtr->Get() &&
		Internal == Cast<UBlueprintGeneratedClass>(Cast<UBlueprintCore>(AssetPtr->Get())->GeneratedClass))
	{
		//UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetPtr_Blueprint (%s): Possibly trying to load Blueprint and it is already loaded"), *MemberName);
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
			UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetPtr_Blueprint (%s): Failed to load Blueprint at %s"), *MemberName, *AssetDescription);
		}
	}
}

void UCsCommon_Load::LoadTArrayTAssetPtr_Blueprint(const FString &MemberName, TArray<TAssetPtr<UBlueprint>> &ArrayAssetPtr, TArray<UBlueprintGeneratedClass*> &ArrayInternal)
{
	if (ArrayInternal.Num() > 0 &&
		AreAllElementsInTArrayNotNull(ArrayInternal))
	{
		//UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTArrayTAssetPtr_Blueprint (%s): Possibly trying to load Blueprint and it is already loaded"), *MemberName);
	}

	UCsCommon_Load::NullAndEmptyTArray<UBlueprintGeneratedClass>(ArrayInternal);

	const int32 Count = ArrayAssetPtr.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		TAssetPtr<UBlueprint>& AssetPtr = ArrayAssetPtr[I];

		if (AssetPtr.IsValid() && AssetPtr.Get())
		{
			UBlueprint* Bp				   = AssetPtr.Get();
			UBlueprintGeneratedClass* Data = Cast<UBlueprintGeneratedClass>(Cast<UBlueprintCore>(Bp)->GeneratedClass);

			ArrayInternal.Add(Data);
			continue;
		}
		
		const FString& AssetName = AssetPtr.ToString();

		// (AssetName != TEXT(""))
		if (AssetName != ECsCached::Str::Empty)
		{
																			//TEXT("_C")
			const FString AssetDescription = TEXT("Blueprint'") + AssetName + ECsLoadCached::Str::_C + TEXT("'");
			UBlueprintGeneratedClass* Data = (UBlueprintGeneratedClass*)StaticLoadObject(UClass::StaticClass(), NULL, *AssetDescription, NULL, LOAD_None, NULL);

			if (!Data)
			{
				UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTArrayTAssetPtr_Blueprint (%s[%d]): Failed to load Blueprint at %s"), *MemberName, I, *AssetDescription);
			}
			ArrayInternal.Add(Data);
		}
		else
		{
			ArrayInternal.Add(nullptr);
		}
	}
}

void UCsCommon_Load::LoadTArrayTAssetPtr_Blueprint(const FString &MemberName, TArray<TAssetPtr<UBlueprint>>* &ArrayAssetPtr, TArray<UBlueprintGeneratedClass*> &ArrayInternal)
{
	if (ArrayInternal.Num() > 0 &&
		AreAllElementsInTArrayNotNull(ArrayInternal))
	{
		//UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTArrayTAssetPtr_Blueprint (%s): Possibly trying to load Blueprint and it is already loaded"), *MemberName);
	}

	UCsCommon_Load::NullAndEmptyTArray<UBlueprintGeneratedClass>(ArrayInternal);

	const int32 Count = ArrayAssetPtr->Num();

	for (int32 I = 0; I < Count; ++I)
	{
		TAssetPtr<UBlueprint>& AssetPtr	= (*ArrayAssetPtr)[I];

		if (AssetPtr.IsValid() && AssetPtr.Get())
		{
			UBlueprint* Bp				   = AssetPtr.Get();
			UBlueprintGeneratedClass* Data = Cast<UBlueprintGeneratedClass>(Cast<UBlueprintCore>(Bp)->GeneratedClass);

			ArrayInternal.Add(Data);
			continue;
		}

		const FString& AssetName = AssetPtr.ToString();

		// (AssetName != TEXT(""))
		if (AssetName != ECsCached::Str::Empty)
		{
																			//TEXT("_C")
			const FString AssetDescription = TEXT("Blueprint'") + AssetName + ECsLoadCached::Str::_C + TEXT("'");
			UBlueprintGeneratedClass* Data = (UBlueprintGeneratedClass*)StaticLoadObject(UClass::StaticClass(), NULL, *AssetDescription, NULL, LOAD_None, NULL);

			if (!Data)
			{
				UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTArrayTAssetPtr_Blueprint (%s[%d]): Failed to load Blueprint at %s"), *MemberName, I, *AssetDescription);
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

void UCsCommon_Load::LoadAssetObjectProperty_Blueprint(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TAssetPtr<UBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>>(InObject))
	{
										// MemberName = TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (UBlueprintGeneratedClass** Internal = InternalProperty->ContainerPtrToValuePtr<UBlueprintGeneratedClass*>(InObject))
				LoadTAssetPtr_Blueprint(ObjectName + ECsCached::Str::Dot + MemberName, Member, *Internal);
									//  ObjectName + TEXT(".") + MemberName
		}
	}
}

void UCsCommon_Load::LoadAssetObjectProperty_Blueprint(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TAssetPtr<UBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>>(InObject))
	{
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
			return;

										// MemberName + TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (UBlueprintGeneratedClass** Internal = InternalProperty->ContainerPtrToValuePtr<UBlueprintGeneratedClass*>(InObject))
				LoadTAssetPtr_Blueprint(ObjectName + ECsCached::Str::Dot + MemberName, Member, *Internal);
									//  ObjectName + TEXT(".") + MemberName
		}
	}
}

void UCsCommon_Load::LoadArrayAssetObjectProperty_Blueprint(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TArray<TAssetPtr<UBlueprint>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UBlueprint>>>(InObject))
	{
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
			return;

										// MemberName + TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (TArray<UBlueprintGeneratedClass*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<UBlueprintGeneratedClass*>>(InObject))
				LoadTArrayTAssetPtr_Blueprint(ObjectName + ECsCached::Str::Dot + MemberName, Member, *Internal);
											//ObjectName + TEXT(".") + MemberName
		}
	}
}

void UCsCommon_Load::LoadArrayAssetObjectProperty_Blueprint(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TArray<TAssetPtr<UBlueprint>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UBlueprint>>>(InObject))
	{
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags, 0))
			return;

										// MemberName + TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (TArray<UBlueprintGeneratedClass*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<UBlueprintGeneratedClass*>>(InObject))
				LoadTArrayTAssetPtr_Blueprint(ObjectName + ECsCached::Str::Dot + MemberName, Member, *Internal);
											//ObjectName + TEXT(".") + MemberName
		}
	}
}

void UCsCommon_Load::LoadStructWithTAssetPtrs(const FString &ObjectName, void* InStruct, UScriptStruct* const &InScriptStruct, const ECsLoadFlags &LoadFlags, TCsLoadStructWithTAssetPtrs_Internal Internal /*=nullptr*/)
{
	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// TAssetSubclassOf
		if (UAssetClassProperty* AssetClassProperty = Cast<UAssetClassProperty>(*It))
		{
			// ACsData_Projectile
			if (AssetClassProperty->MetaClass == ACsData_Projectile::StaticClass())
			{ LoadAssetClassProperty<ACsData_Projectile>(AssetClassProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::CsData_Projectile, LoadFlags); continue; }
			// ACsData_ProjectileImpact
			if (AssetClassProperty->MetaClass == ACsData_ProjectileImpact::StaticClass())
			{ LoadAssetClassProperty<ACsData_ProjectileImpact>(AssetClassProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::CsData_ProjectileImpact, LoadFlags); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
					continue;
			}
			continue;
		}
		// TAssetPtr
		if (UAssetObjectProperty* AssetObjectProperty = Cast<UAssetObjectProperty>(*It))
		{
			// UStaticMesh
			if (AssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ LoadAssetObjectProperty<UStaticMesh>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::StaticMesh, ECsCommonLoadCached::Str::Static_Mesh, LoadFlags); continue; }
			// USkeletalMesh
			if (AssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ LoadAssetObjectProperty<USkeletalMesh>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::SkeletalMesh, ECsCommonLoadCached::Str::Skeletal_Mesh, LoadFlags); continue; }
			// UMaterialInstance
			if (AssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ LoadAssetObjectProperty<UMaterialInstance>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::MaterialInstance, ECsCommonLoadCached::Str::MaterialInstance, LoadFlags); continue; }
			// UMaterialInstanceConstant
			if (AssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == CS_SINGLETON)
				{ LoadAssetObjectProperty<UMaterialInstanceConstant>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::MaterialInstanceConstant, ECsCommonLoadCached::Str::MaterialInstanceConstant, LoadFlags); continue; }
				if (AssetObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ LoadFixedArrayAssetObjectProperty_EnumSize<UMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::MaterialInstanceConstant, ECsCommonLoadCached::Str::MaterialInstanceConstant, LoadFlags, &ECsInteractiveState::ToString); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// UPhysicalMaterial
			if (AssetObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ LoadAssetObjectProperty<UPhysicalMaterial>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::PhysicalMaterial, ECsCommonLoadCached::Str::Physical_Material, LoadFlags); continue; }
			// UPhysicsAsset
			if (AssetObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ LoadAssetObjectProperty<UPhysicsAsset>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::PhysicsAsset, ECsCommonLoadCached::Str::Physics_Asset, LoadFlags); continue; }
			// UAnimSequence
			if (AssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ LoadAssetObjectProperty<UAnimSequence>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::AnimSequence, ECsCommonLoadCached::Str::Anim_Sequence, LoadFlags); continue; }
			// UAnimMontage
			if (AssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ LoadAssetObjectProperty<UAnimMontage>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::AnimMontage, ECsCommonLoadCached::Str::Anim_Montage, LoadFlags); continue; }
			// UBlendSpace1D
			if (AssetObjectProperty->PropertyClass == UBlendSpace1D::StaticClass())
			{ LoadAssetObjectProperty<UBlendSpace1D>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::BlendSpace1D, ECsCommonLoadCached::Str::Blend_Space_1D, LoadFlags); continue; }
			// UBlendSpace
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ LoadAssetObjectProperty<UBlendSpace>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::BlendSpace, ECsCommonLoadCached::Str::Blend_Space, LoadFlags); continue; }
			// UAnimBlueprint
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ LoadAssetObjectProperty_AnimBlueprint(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, LoadFlags); continue; }
			// USoundCue
			if (AssetObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ LoadAssetObjectProperty<USoundCue>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::SoundCue, ECsCommonLoadCached::Str::Sound_Cue, LoadFlags); continue; }
			// UParticleSystem
			if (AssetObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ LoadAssetObjectProperty<UParticleSystem>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::ParticleSystem, ECsCommonLoadCached::Str::Particle_System, LoadFlags); continue; }
			// UCurveFloat
			if (AssetObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ LoadAssetObjectProperty<UCurveFloat>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::CurveFloat, ECsCommonLoadCached::Str::Curve_Float, LoadFlags); continue; }
			// UCurveVector
			if (AssetObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ LoadAssetObjectProperty<UCurveVector>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, ECsCommonLoadCached::Str::CurveVector, ECsCommonLoadCached::Str::Curve_Vector, LoadFlags); continue; }
			// UBlueprint
			if (AssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{ 
				if (AssetObjectProperty->ArrayDim == CS_SINGLETON)
				{ LoadAssetObjectProperty_Blueprint(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, LoadFlags); continue; }
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
			// FCsFpsStaticMesh
			if (StructProperty->Struct == FCsFpsStaticMesh::StaticStruct())
			{ LoadMemberStructProperty<FCsFpsStaticMesh>(StructProperty, InStruct, StructName, LoadFlags); continue; }
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
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsFpsSoundElement>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				
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
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsFpsFxElement>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				
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
			// FCsData_ProjectilePtr
			if (StructProperty->Struct == FCsData_ProjectilePtr::StaticStruct())
			{ LoadMemberStructProperty<FCsData_ProjectilePtr>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }

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
			// TAssetSubclassOf
			if (UAssetClassProperty* InnerAssetClassProperty = Cast<UAssetClassProperty>(ArrayProperty->Inner))
			{
				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// TAssetPtr
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerAssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ LoadArrayAssetObjectProperty<UStaticMesh>(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("StaticMesh"), TEXT("Static Mesh"), LoadFlags); continue; }
				// USkeletalMesh
				if (InnerAssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ LoadArrayAssetObjectProperty<USkeletalMesh>(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("SkeletalMesh"), TEXT("Skeletal Mesh"), LoadFlags); continue; }
				// UMaterialInstance
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ LoadArrayAssetObjectProperty<UMaterialInstance>(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("MaterialInstance"), TEXT("Material Instance"), LoadFlags); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ LoadArrayAssetObjectProperty<UMaterialInstanceConstant>(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("MaterialInstanceConstant"), TEXT("Material Instance Constant"), LoadFlags); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ LoadArrayAssetObjectProperty<UAnimSequence>(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("AnimSequence"), TEXT("Anim Sequence"), LoadFlags); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ LoadArrayAssetObjectProperty<UAnimMontage>(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("AnimMontage"), TEXT("Anim Montage"), LoadFlags); continue; }
				// UBlueprint
				if (InnerAssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ LoadArrayAssetObjectProperty_Blueprint(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, LoadFlags); continue; }

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
				// FCsFpsFxElement
				if (InnerStructProperty->Struct == FCsFpsFxElement::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFpsFxElement>(ArrayProperty, InStruct, StructName, LoadFlags); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsSoundElement>(ArrayProperty, InStruct, StructName, LoadFlags); continue; }
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFpsSoundElement>(ArrayProperty, InStruct, StructName, LoadFlags); continue; }
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
void UCsCommon_Load::LoadObjectWithTAssetPtrs(const FString &ObjectName, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, TCsLoadObjectWithTAssetPtrs_Internal Internal /*=nullptr*/)
{
	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// TAssetSubclassOf
		if (UAssetClassProperty* AssetClassProperty = Cast<UAssetClassProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
					continue;
			}
			continue;
		}
		// TAssetPtr
		if (UAssetObjectProperty* AssetObjectProperty = Cast<UAssetObjectProperty>(*It))
		{
			// UStaticMesh
			if (AssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ LoadAssetObjectProperty<UStaticMesh>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("StaticMesh"), TEXT("Static Mesh"), LoadFlags); continue; }
			// USkeletalMesh
			if (AssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ LoadAssetObjectProperty<USkeletalMesh>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("SkeletalMesh"), TEXT("Skeletal Mesh"), LoadFlags); continue; }
			// UMaterialInstance
			if (AssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ LoadAssetObjectProperty<UMaterialInstance>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("MaterialInstance"), TEXT("Material Instance"), LoadFlags); continue; }
			// UMaterialInstanceConstant
			if (AssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{ LoadAssetObjectProperty<UMaterialInstanceConstant>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("MaterialInstanceConstant"), TEXT("Material Instance Constant"), LoadFlags); continue; }
			// UPhysicalMaterial
			if (AssetObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ LoadAssetObjectProperty<UPhysicalMaterial>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("PhysicalMaterial"), TEXT("Physical Material"), LoadFlags); continue; }
			// UPhysicsAsset
			if (AssetObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ LoadAssetObjectProperty<UPhysicsAsset>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("PhysicsAsset"), TEXT("Physics Asset"), LoadFlags); continue; }
			// UAnimSequence
			if (AssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ LoadAssetObjectProperty<UAnimSequence>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("AnimSequence"), TEXT("Anim Sequence"), LoadFlags); continue; }
			// UAnimMontage
			if (AssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ LoadAssetObjectProperty<UAnimMontage>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("AnimMontage"), TEXT("Anim Montage"), LoadFlags); continue; }
			// UBlendSpace
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ LoadAssetObjectProperty<UBlendSpace>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("BlendSpace"), TEXT("Blend Space"), LoadFlags); continue; }
			// UAnimBlueprint
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ LoadAssetObjectProperty_AnimBlueprint(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, LoadFlags); continue; }
			// USoundCue
			if (AssetObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ LoadAssetObjectProperty<USoundCue>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("SoundCue"), TEXT("Sound Cue"), LoadFlags); continue; }
			// UParticleSystem
			if (AssetObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ LoadAssetObjectProperty<UParticleSystem>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("ParticleSystem"), TEXT("Particle System"), LoadFlags); continue; }
			// UCurveFloat
			if (AssetObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ LoadAssetObjectProperty<UCurveFloat>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("CurveFloat"), TEXT("Curve Float"), LoadFlags); continue; }
			// UCurveVector
			if (AssetObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ LoadAssetObjectProperty<UCurveVector>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, TEXT("CurveVector"), TEXT("Curve Vector"), LoadFlags); continue; }
			// UBlueprint
			if (AssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == CS_SINGLETON)
				{ LoadAssetObjectProperty_Blueprint(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, LoadFlags); continue; }
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
			// FCsFpsStaticMesh
			if (StructProperty->Struct == FCsFpsStaticMesh::StaticStruct())
			{ LoadMemberStructProperty<FCsFpsStaticMesh>(StructProperty, InObject, StructName, LoadFlags); continue; }
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
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsFpsSoundElement>(StructProperty, InObject, StructName, LoadFlags); continue; }

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
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ LoadMemberStructProperty<FCsFpsFxElement>(StructProperty, InObject, StructName, LoadFlags); continue; }

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
			// TAssetSubclassOf
			if (UAssetClassProperty* InnerAssetClassProperty = Cast<UAssetClassProperty>(ArrayProperty->Inner))
			{
				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
						continue;
				}
				continue;
			}
			// TAssetPtr
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerAssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ LoadArrayAssetObjectProperty<UStaticMesh>(ArrayProperty, ObjectName, InObject, InClass, MemberName, TEXT("StaticMesh"), TEXT("Static Mesh"), LoadFlags); continue; }
				// USkeletalMesh
				if (InnerAssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ LoadArrayAssetObjectProperty<USkeletalMesh>(ArrayProperty, ObjectName, InObject, InClass, MemberName, TEXT("SkeletalMesh"), TEXT("Skeletal Mesh"), LoadFlags); continue; }
				// UMaterialInstance
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ LoadArrayAssetObjectProperty<UMaterialInstance>(ArrayProperty, ObjectName, InObject, InClass, MemberName, TEXT("MaterialInstance"), TEXT("Material Instance"), LoadFlags); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ LoadArrayAssetObjectProperty<UMaterialInstanceConstant>(ArrayProperty, ObjectName, InObject, InClass, MemberName, TEXT("MaterialInstanceConstant"), TEXT("Material Instance Constant"), LoadFlags); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ LoadArrayAssetObjectProperty<UAnimSequence>(ArrayProperty, ObjectName, InObject, InClass, MemberName, TEXT("AnimSequence"), TEXT("Anim Sequence"), LoadFlags); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ LoadArrayAssetObjectProperty<UAnimMontage>(ArrayProperty, ObjectName, InObject, InClass, MemberName, TEXT("AnimMontage"), TEXT("Anim Montage"), LoadFlags); continue; }
				// UBlueprint
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ LoadArrayAssetObjectProperty_Blueprint(ArrayProperty, ObjectName, InObject, InClass, MemberName, LoadFlags); continue; }

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
				// FCsFpsFxElement
				if (InnerStructProperty->Struct == FCsFpsFxElement::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFpsFxElement>(ArrayProperty, InObject, StructName, LoadFlags); continue; }
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFpsSoundElement>(ArrayProperty, InObject, StructName, LoadFlags); continue; }
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

void UCsCommon_Load::UnLoadStructWithTAssetPtrs(void* InStruct, UScriptStruct* const &InScriptStruct)
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
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ UnLoadMemberStructProperty<FCsFpsSoundElement>(StructProperty, InStruct); continue; }
				continue;
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ UnLoadMemberStructProperty<FCsFxElement>(StructProperty, InStruct); continue; }
				continue;
			}
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ UnLoadMemberStructProperty<FCsFpsFxElement>(StructProperty, InStruct); continue; }
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
			// TAssetSubclassOf
			if (UAssetClassProperty* InnerAssetClassProperty = Cast<UAssetClassProperty>(ArrayProperty->Inner))
			{
				if (!MemberName.Contains(TEXT("_Internal")))
					continue;

				// AShooterWeaponData
				//if (InnerAssetClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerAssetClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//{ UnLoadArrayObjectProperty<AShooterWeaponData>(ArrayProperty, InStruct); continue; }
				continue;
			}
			// TAssetPtr
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
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsFpsSoundElement>(ArrayProperty, InStruct); continue; }
				continue;
			}
			continue;
		}
	}
}

void UCsCommon_Load::UnLoadObjectWithTAssetPtrs(void* InObject, UClass* const &InClass)
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
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ UnLoadMemberStructProperty<FCsFpsSoundElement>(StructProperty, InObject); continue; }
				continue;
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ UnLoadMemberStructProperty<FCsFxElement>(StructProperty, InObject); continue; }
				continue;
			}
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ UnLoadMemberStructProperty<FCsFpsFxElement>(StructProperty, InObject); continue; }
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
			// TAssetSubclassOf
			if (UAssetClassProperty* InnerAssetClassProperty = Cast<UAssetClassProperty>(ArrayProperty->Inner))
			{
				if (!MemberName.Contains(TEXT("_Internal")))
					continue;

				// AShooterWeaponData
				//if (InnerAssetClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerAssetClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//{ UnLoadArrayObjectProperty<AShooterWeaponData>(ArrayProperty, InObject); continue; }
			}
			// TAssetPtr
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
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsFpsSoundElement>(ArrayProperty, InObject); continue; }
				continue;
			}
		}
	}
}

#pragma endregion UnLoad

	// IsLoaded
#pragma region

bool UCsCommon_Load::IsLoadedStructWithTAssetPtrs(const FString &ObjectName, void* InStruct, UScriptStruct* const &InScriptStruct)
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
			// FCsFpsSoundElement
			else
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsFpsSoundElement>(StructProperty, InStruct, StructName);
			}
			// FCsFxElement
			else
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsFxElement>(StructProperty, InStruct, StructName);
			}
			// FCsFpsFxElement
			else
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsFpsFxElement>(StructProperty, InStruct, StructName);
			}
		}
		// Array
		else
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TAssetSubclassOf
			if (UAssetClassProperty* InnerAssetClassProperty = Cast<UAssetClassProperty>(ArrayProperty->Inner))
			{
				if (!MemberName.Contains(TEXT("_Internal")))
					continue;

				// AShooterWeaponData
				//if (InnerAssetClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerAssetClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//	Pass &= IsLoadedArrayObjectProperty<AShooterWeaponData>(ArrayProperty, InStruct, MemberName);
			}
			// TAssetPtr
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
				// FCsFpsSoundElement
				else
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
					Pass &= IsLoadedMemberArrayStructProperty<FCsFpsSoundElement>(ArrayProperty, InStruct, StructName);
			}
		}
	}
	return Pass;
}

bool UCsCommon_Load::IsLoadedObjectWithTAssetPtrs(const FString &ObjectName, void* InObject, UClass* const &InClass)
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
			// FCsFpsSoundElement
			else
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsFpsSoundElement>(StructProperty, InObject, StructName);
			}
			// FCsFxElement
			else
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsFxElement>(StructProperty, InObject, StructName);
			}
			// FCsFpsFxElement
			else
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					Pass &= IsLoadedMemberStructProperty<FCsFpsFxElement>(StructProperty, InObject, StructName);
			}
		}
		// Array
		else
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TAssetSubclassOf
			if (UAssetClassProperty* InnerAssetClassProperty = Cast<UAssetClassProperty>(ArrayProperty->Inner))
			{
				if (!MemberName.Contains(TEXT("_Internal")))
					continue;

				// AShooterWeaponData
				//if (InnerAssetClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerAssetClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//	Pass &= IsLoadedArrayObjectProperty<AShooterWeaponData>(ArrayProperty, InObject, MemberName);
			}
			// TAssetPtr
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
				// FCsFpsSoundElement
				else
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
					Pass &= IsLoadedMemberArrayStructProperty<FCsFpsSoundElement>(ArrayProperty, InObject, StructName);
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

		const FString LoadFlagsAsString = LoadFlagsToString(*LoadFlags);

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

		// TAssetSubclassOf
		if (UAssetClassProperty* AssetClassProperty = Cast<UAssetClassProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, ObjectName, InObject, InClass))
					continue;
			}
			continue;
		}
		// TAssetPtr
		if (UAssetObjectProperty* AssetObjectProperty = Cast<UAssetObjectProperty>(*It))
		{
			// UStaticMesh
			if (AssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ CheckEnumAssetObjectProperty<UStaticMesh>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// USkeletalMesh
			if (AssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ CheckEnumAssetObjectProperty<USkeletalMesh>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UMaterialInstance
			if (AssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ CheckEnumAssetObjectProperty<UMaterialInstance>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UMaterialInstanceConstant
			if (AssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{ CheckEnumAssetObjectProperty<UMaterialInstanceConstant>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UPhysicalMaterial
			if (AssetObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ CheckEnumAssetObjectProperty<UPhysicalMaterial>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UPhysicsAsset
			if (AssetObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ CheckEnumAssetObjectProperty<UPhysicsAsset>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UAnimSequence
			if (AssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ CheckEnumAssetObjectProperty<UAnimSequence>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UAnimMontage
			if (AssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ CheckEnumAssetObjectProperty<UAnimMontage>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UBlendSpace
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ CheckEnumAssetObjectProperty<UBlendSpace>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UAnimBlueprint
			//if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			//{ CheckEnumAssetObjectProperty(AssetObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// USoundCue
			if (AssetObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ CheckEnumAssetObjectProperty<USoundCue>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UParticleSystem
			if (AssetObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ CheckEnumAssetObjectProperty<UParticleSystem>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UCurveFloat
			if (AssetObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ CheckEnumAssetObjectProperty<UCurveFloat>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UCurveVector
			if (AssetObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ CheckEnumAssetObjectProperty<UCurveVector>(AssetObjectProperty, ObjectName, InObject, InClass, MemberName); continue; }
			// UBlueprint
			if (AssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == CS_SINGLETON)
				{
					//LoadAssetObjectProperty_Blueprint(AssetObjectProperty, ObjectName, InObject, InClass, MemberName, LoadFlags); continue;
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
			// FCsFpsStaticMesh
			if (StructProperty->Struct == FCsFpsStaticMesh::StaticStruct())
			{ CheckEnumStructProperty<FCsFpsStaticMesh>(StructProperty, InObject, StructName, nullptr); continue; }
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
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ CheckEnumStructProperty<FCsFpsSoundElement>(StructProperty, InObject, StructName, nullptr); continue; }

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
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
				{ CheckEnumStructProperty<FCsFpsFxElement>(StructProperty, InObject, StructName, nullptr); continue; }

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
			// TAssetSubclassOf
			if (UAssetClassProperty* InnerAssetClassProperty = Cast<UAssetClassProperty>(ArrayProperty->Inner))
			{
				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass))
						continue;
				}
				continue;
			}
			// TAssetPtr
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerAssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ CheckEnumArrayAssetObjectProperty<UStaticMesh>(ArrayProperty, ObjectName, InObject, InClass, MemberName); continue; }
				// USkeletalMesh
				if (InnerAssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ CheckEnumArrayAssetObjectProperty<USkeletalMesh>(ArrayProperty, ObjectName, InObject, InClass, MemberName); continue; }
				// UMaterialInstance
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ CheckEnumArrayAssetObjectProperty<UMaterialInstance>(ArrayProperty, ObjectName, InObject, InClass, MemberName); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ CheckEnumArrayAssetObjectProperty<UMaterialInstanceConstant>(ArrayProperty, ObjectName, InObject, InClass, MemberName); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ CheckEnumArrayAssetObjectProperty<UAnimSequence>(ArrayProperty, ObjectName, InObject, InClass, MemberName); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ CheckEnumArrayAssetObjectProperty<UAnimMontage>(ArrayProperty, ObjectName, InObject, InClass, MemberName); continue; }
				// UBlueprint
				//if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				//{ CheckEnumArrayAssetObjectProperty(ArrayProperty, ObjectName, InObject, InClass, MemberName); continue; }

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
				// FCsFpsFxElement
				if (InnerStructProperty->Struct == FCsFpsFxElement::StaticStruct())
				{ CheckEnumArrayStructProperty<FCsFpsFxElement>(ArrayProperty, InObject, StructName); continue; }
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ CheckEnumArrayStructProperty<FCsFpsSoundElement>(ArrayProperty, InObject, StructName); continue; }
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
					if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CollisionChannel))
					{ CheckEnumByteProperty<ECollisionChannel>(ByteProperty, InObject, MemberName, ECollisionChannel::ECC_MAX); continue; }
					// ECsLoadFlags_Editor
					if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsLoadFlags_Editor))
					{ CheckEnumByteProperty<ECsLoadFlags_Editor::Type>(ByteProperty, InObject, MemberName, ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX); continue; }
					// ECsFxPriority
					if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsFxPriority))
					{ CheckEnumByteProperty<ECsFxPriority::Type>(ByteProperty, InObject, MemberName, ECsFxPriority::ECsFxPriority_MAX); continue; }
					// ECsSoundPriority
					if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsSoundPriority))
					{ CheckEnumByteProperty<ECsSoundPriority::Type>(ByteProperty, InObject, MemberName, ECsSoundPriority::ECsSoundPriority_MAX); continue; }
					// ECsInteractiveCollision
					if (ByteProperty->Enum->CppType.Contains(ECsCommonLoadCached::Str::CsInteractiveCollision))
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
					if (Property->HasMetaData(*(ECsCommonLoadCached::Str::BitmaskEnum)))
					{
																	//    TEXT("BitmaskEnum")
						const FString BitmaskEnum = Property->GetMetaData(*(ECsCommonLoadCached::Str::BitmaskEnum));

						// (BitmaskEnum == TEXT("ECsLoadFlags"))
						if (BitmaskEnum == ECsCommonLoadCached::Str::CsLoadFlags)
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

		// TAssetSubclassOf
		if (UAssetClassProperty* AssetClassProperty = Cast<UAssetClassProperty>(*It))
		{
			// AShooterWeaponData
			//if (AssetClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || AssetClassProperty->MetaClass == AShooterWeaponData::StaticClass())
			//	SetMemberProperty<TAssetSubclassOf<AShooterWeaponData>>(ToObject, Property, MemberValues[Index]);
		}
		// TAssetPtr
		else
		if (UAssetObjectProperty* AssetObjectProperty = Cast<UAssetObjectProperty>(*It))
		{
			// UStaticMesh
			if (AssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				SetMemberProperty<TAssetPtr<UStaticMesh>>(ToObject, Property, MemberValues[Index]);
			// UMaterialInstance
			else
			if (AssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				SetMemberProperty<TAssetPtr<UMaterialInstance>>(ToObject, Property, MemberValues[Index]);
			// UPhysicsAsset
			else
			if (AssetObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
				SetMemberProperty<TAssetPtr<UPhysicsAsset>>(ToObject, Property, MemberValues[Index]);
			// UAnimSequence
			else
			if (AssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				SetMemberProperty<TAssetPtr<UAnimSequence>>(ToObject, Property, MemberValues[Index]);
			// UAnimMontage
			else
			if (AssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				SetMemberProperty<TAssetPtr<UAnimMontage>>(ToObject, Property, MemberValues[Index]);
			// UBlendSpace
			else
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
				SetMemberProperty<TAssetPtr<UBlendSpace>>(ToObject, Property, MemberValues[Index]);
			// UAnimBlueprint
			else
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
				SetMemberProperty<TAssetPtr<UAnimBlueprint>>(ToObject, Property, MemberValues[Index]);
			// USoundCue
			else
			if (AssetObjectProperty->PropertyClass == USoundCue::StaticClass())
				SetMemberProperty<TAssetPtr<USoundCue>>(ToObject, Property, MemberValues[Index]);
			// UParticleSystem
			else
			if (AssetObjectProperty->PropertyClass == UParticleSystem::StaticClass())
				SetMemberProperty<TAssetPtr<UParticleSystem>>(ToObject, Property, MemberValues[Index]);
			// UCurveVector
			else
			if (AssetObjectProperty->PropertyClass == UCurveVector::StaticClass())
				SetMemberProperty<TAssetPtr<UCurveVector>>(ToObject, Property, MemberValues[Index]);
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
			// FCsFpsSoundElement
			else
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					SetMemberProperty<FCsFpsSoundElement>(ToObject, Property, MemberValues[Index]);
			}
			// FCsFxElement
			else
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					SetMemberProperty<FCsFxElement>(ToObject, Property, MemberValues[Index]);
			}
			// FCsFpsFxElement
			else
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					SetMemberProperty<FCsFpsFxElement>(ToObject, Property, MemberValues[Index]);
			}
		}
		// Array
		else
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TAssetSubclassOf
			if (UAssetClassProperty* InnerAssetClassProperty = Cast<UAssetClassProperty>(ArrayProperty->Inner))
			{
				// AShooterWeaponData
				//if (InnerAssetClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerAssetClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//{ SetMemberProperty<TArray<TAssetSubclassOf<AShooterWeaponData>>>(ToObject, Property, MemberValues[Index]); }
			}
			// TAssetPtr
			else
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// UAnimMontage
				//if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				//{ SetMemberProperty<TArray<TAssetPtr<UAnimMontage>>>(ToObject, Property, MemberValues[Index]); }
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
TEnumAsByte<EMemberType::Type> UCsCommon::GetObjectMemberType(UClass* const &InClass, const FString &MemberName)
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

TEnumAsByte<EMemberType::Type> UCsCommon::GetStructMemberType(UScriptStruct* const &InScriptStruct, const FString &MemberName)
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

		// TAssetSubclassOf
		if (UAssetClassProperty* AssetClassProperty = Cast<UAssetClassProperty>(*It))
		{
			// AShooterWeaponData
			//if (AssetClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || AssetClassProperty->MetaClass == AShooterWeaponData::StaticClass())
			//	OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TAssetSubclassOf<AShooterWeaponData>>(InObject));
		}
		// TAssetPtr
		else
		if (UAssetObjectProperty* AssetObjectProperty = Cast<UAssetObjectProperty>(*It))
		{
			// UStaticMesh
			if (AssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TAssetPtr<UStaticMesh>>(InObject));
			// UMaterialInstance
			else
			if (AssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TAssetPtr<UMaterialInstance>>(InObject));
			// UPhysicsAsset
			else
			if (AssetObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TAssetPtr<UPhysicsAsset>>(InObject));
			// UAnimSequence
			else
			if (AssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TAssetPtr<UAnimSequence>>(InObject));
			// UAnimMontage
			else
			if (AssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TAssetPtr<UAnimMontage>>(InObject));
			// UBlendSpace
			else
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TAssetPtr<UBlendSpace>>(InObject));
			// UAnimBlueprint
			else
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TAssetPtr<UAnimBlueprint>>(InObject));
			// USoundCue
			else
			if (AssetObjectProperty->PropertyClass == USoundCue::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TAssetPtr<USoundCue>>(InObject));
			// UParticleSystem
			else
			if (AssetObjectProperty->PropertyClass == UParticleSystem::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TAssetPtr<UParticleSystem>>(InObject));
			// UCurveVector
			else
			if (AssetObjectProperty->PropertyClass == UCurveVector::StaticClass())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TAssetPtr<UCurveVector>>(InObject));
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
			// FCsFpsSoundElement
			else
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFpsSoundElement>(InObject));
			}
			// FCsFxElement
			else
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFxElement>(InObject));
			}
			// FCsFpsFxElement
			else
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == CS_SINGLETON)
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFpsFxElement>(InObject));
			}
		}
		// Array
		else
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TAssetSubclassOf
			if (UAssetClassProperty* InnerAssetClassProperty = Cast<UAssetClassProperty>(ArrayProperty->Inner))
			{
				// AShooterWeaponData
				//if (InnerAssetClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerAssetClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//	OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TArray<TAssetSubclassOf<AShooterWeaponData>>>(InObject));
			}
			// TAssetPtr
			else
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// AnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<TArray<TAssetPtr<UAnimMontage>>>(InObject));
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