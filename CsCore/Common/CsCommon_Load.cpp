// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Common/CsCommon_Load.h"
#include "CsCore.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Input.h"
#include "CsCVars.h"

#include "Common/CsCommon.h"

#include "Data/CsData.h"

UCsCommon_Load::UCsCommon_Load(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Enum to String Conversion
#pragma region

FString UCsCommon_Load::LoadFlagsToString(const int32 &LoadFlags)
{
	FString String = TEXT("");
	bool IsFirst = true;

	for (int32 I = 0; I < ECS_LOAD_FLAGS_EDITOR_MAX; I++)
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

	for (int32 I = 0; I < ECS_LOAD_FLAGS_EDITOR_MAX; I++)
	{
		const FString EnumAsString = ECsLoadFlags_Editor::ToString((TCsLoadFlags_Editor)I);

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

	for (int32 I = 0; I < Count; I++)
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

		if (AssetName != TEXT(""))
		{
			InJsonWriter->WriteValue(MemberName, AssetName);
		}
		else
		{
			InJsonWriter->WriteValue(MemberName, TEXT(""));
		}
	}
	else
	{
		InJsonWriter->WriteValue(MemberName, TEXT(""));
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

		if (AssetName != TEXT(""))
		{
			InJsonWriter->WriteValue(MemberName, AssetName);
		}
		else
		{
			InJsonWriter->WriteValue(MemberName, TEXT(""));
		}
	}
	else
	{
		InJsonWriter->WriteValue(MemberName, TEXT(""));
	}
}

void UCsCommon_Load::WriteAssetObjectPropertyToJson_Blueprint(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName)
{
	if (TAssetPtr<UBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>>(InObject))
		WriteTAssetPtrToJson_Blueprint(InJsonWriter, MemberName, *Member);
}

void UCsCommon_Load::WriteMemberStructPropertyToJson_Transform(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UStructProperty* &StructProperty, void* InObject, const FString &MemberName)
{
	if (FTransform* Member = StructProperty->ContainerPtrToValuePtr<FTransform>(InObject))
	{
		InJsonWriter->WriteObjectStart(MemberName);

		// Rotation
		InJsonWriter->WriteValue(TEXT("Rotation"), *(Member->GetRotation().Rotator().ToString()));
		// Translation
		InJsonWriter->WriteValue(TEXT("Translation"), *(Member->GetTranslation().ToString()));
		// Scale
		InJsonWriter->WriteValue(TEXT("Scale"), *(Member->GetScale3D().ToString()));

		InJsonWriter->WriteObjectEnd();
	}
}

void UCsCommon_Load::WriteMemberArrayStructPropertyToJson_Transform(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName)
{
	TArray<FTransform>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<FTransform>>(InObject);

	InJsonWriter->WriteArrayStart(MemberName);

	const int32 Count = Member->Num();

	for (int32 I = 0; I < Count; I++)
	{
		FTransform& Element = (*Member)[I];

		InJsonWriter->WriteObjectStart();

		// Rotation
		InJsonWriter->WriteValue(TEXT("Rotation"), *(Element.GetRotation().Rotator().ToString()));
		// Translation
		InJsonWriter->WriteValue(TEXT("Translation"), *(Element.GetTranslation().ToString()));
		// Scale
		InJsonWriter->WriteValue(TEXT("Scale"), *(Element.GetScale3D().ToString()));

		InJsonWriter->WriteObjectEnd();
	}
	InJsonWriter->WriteArrayEnd();
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
				if (AssetObjectProperty->ArrayDim == 1)
				{ WriteAssetObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
				if (AssetObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ WriteFixedArrayAssetObjectPropertyToJson_EnumSize<UMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(InJsonWriter, AssetObjectProperty, InStruct, MemberName, &ECsInteractiveState::ToString); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
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
			// UBlendSpace
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ WriteAssetObjectPropertyToJson<UBlendSpace>(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UAnimBlueprint
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ WriteAssetObjectPropertyToJson_AnimBlueprint(InJsonWriter, AssetObjectProperty, InStruct, MemberName); continue; }
			// UBlueprint
			if (AssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == 1)
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
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsStaticMesh>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
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
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsTArrayMaterialInstanceConstant>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
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
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsSoundElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsFpsSoundElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsFxElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsFpsFxElement>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsAnimSequence>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpsAnimSequence
			if (StructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsAnimSequence>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsAnimMontage>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsFpsAnimMontage
			if (StructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsFpsAnimMontage>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsTArrayAnimMontage>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsBlendSpace>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpsBlendSpace
			if (StructProperty->Struct == FCsFpsBlendSpace::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsBlendSpace>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsAnimBlueprint>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
			// FCsFpsAnimBlueprint
			if (StructProperty->Struct == FCsFpsAnimBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsAnimBlueprint>(InJsonWriter, StructProperty, InStruct, MemberName, true, Internal); continue; }
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
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsInputActionMappings>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }

				if (StructProperty->ArrayDim == ECS_INPUT_DEVICE_MAX)
				{ WriteMemberFixedArrayStructPropertyToJson_EnumSize<FCsInputActionMappings, ECsInputDevice::Type, ECS_INPUT_DEVICE_MAX>(InJsonWriter, StructProperty, InStruct, MemberName, &ECsInputDevice::ToString, nullptr); continue; }
			}
			// FCsInputActionMapping
			if (StructProperty->Struct == FCsInputActionMapping::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsInputActionMapping>(InJsonWriter, StructProperty, InStruct, MemberName, true, nullptr); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
					continue;
			}
			continue;
		}
		// Array
		else
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TAssetPtr
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerAssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UStaticMesh>(InJsonWriter, ArrayProperty, InStruct, MemberName, TEXT("Mesh")); continue; }
				// USkeletalMesh
				if (InnerAssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<USkeletalMesh>(InJsonWriter, ArrayProperty, InStruct, MemberName, TEXT("Mesh")); continue; }
				// UMaterialInstance
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UMaterialInstance>(InJsonWriter, ArrayProperty, InStruct, MemberName, TEXT("Mat")); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, ArrayProperty, InStruct, MemberName, TEXT("Mat")); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UAnimSequence>(InJsonWriter, ArrayProperty, InStruct, MemberName, TEXT("Anim")); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UAnimMontage>(InJsonWriter, ArrayProperty, InStruct, MemberName, TEXT("Anim")); continue; }
				// UBlueprint
				if (InnerAssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UBlueprint>(InJsonWriter, ArrayProperty, InStruct, MemberName, TEXT("Bp")); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InStruct, InScriptStruct))
						continue;
				}
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
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
				// FCsInputActionMapping
				if (InnerStructProperty->Struct == FCsInputActionMapping::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsInputActionMapping>(InJsonWriter, ArrayProperty, InStruct, MemberName); continue; }

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
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECollisionEnabled")))
				{ WriteMemberBytePropertyToJson<ECollisionEnabled::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECollisionEnabled::ToString); continue; }
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECollisionChannel")))
				{ WriteMemberBytePropertyToJson<ECollisionChannel>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsCollisionChannel::ToString); continue; }
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECollisionResponse")))
				{ WriteMemberBytePropertyToJson<ECollisionResponse>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsCollisionResponse::ToString); continue; }
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(TEXT("EHorizTextAligment")))
				{ WriteMemberBytePropertyToJson<EHorizTextAligment>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsHorizTextAligment::ToString); continue; }
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(TEXT("EVerticalTextAligment")))
				{ WriteMemberBytePropertyToJson<EVerticalTextAligment>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsVerticalTextAligment::ToString); continue; }
				// ECsLoadFlags_Editor
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECsLoadFlags_Editor")))
				{ WriteMemberBytePropertyToJson<ECsLoadFlags_Editor::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsLoadFlags_Editor::ToString); continue; }
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECsFxPriority")))
				{ WriteMemberBytePropertyToJson<ECsFxPriority::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsFxPriority::ToString); continue; }
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECsSoundPriority")))
				{ WriteMemberBytePropertyToJson<ECsSoundPriority::Type>(InJsonWriter, ByteProperty, InStruct, MemberName, &ECsSoundPriority::ToString); continue; }

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
				if (Property->HasMetaData(TEXT("BitmaskEnum")))
				{
					const FString BitmaskEnum = Property->GetMetaData(TEXT("BitmaskEnum"));

					if (BitmaskEnum == TEXT("ECsLoadFlags"))
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
			if (NameProperty->ArrayDim == 1)
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

void UCsCommon_Load::WriteObjectToJson(TSharedRef<TJsonWriter<TCHAR>> &InJsonWriter, void* InObject, UClass* const &InClass, const TArray<FCsCategoryMemberAssociation> &CategoryMemberAssociations, TCsWriteObjectToJson_Internal Internal)
{
	const FString NoCategory = TEXT("");
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
			if (LastCategory != TEXT(""))
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
		}
		// TAssetPtr
		else
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
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsStaticMesh>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
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
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsTArrayMaterialInstanceConstant>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
				if (StructProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ WriteMemberFixedArrayStructPropertyToJson_EnumSize<FCsTArrayMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(InJsonWriter, StructProperty, InObject, MemberName, &ECsInteractiveState::ToString, nullptr); continue; }
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
			// FCsCurveFloat
			if (StructProperty->Struct == FCsCurveFloat::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsCurveFloat>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsCurveVector>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsSoundElement>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			}
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsFpsSoundElement>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			}
			// FCsParticleSystem
			if (StructProperty->Struct == FCsParticleSystem::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsParticleSystem>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsFxElement>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			}
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsFpsFxElement>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsAnimSequence>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsFpsAnimSequence
			if (StructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsAnimSequence>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsAnimMontage>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			}
			// FCsFpsAnimMontage
			if (StructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsFpsAnimMontage>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			}
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsTArrayAnimMontage>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			}
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsBlendSpace>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsFpsBlendSpace
			if (StructProperty->Struct == FCsFpsBlendSpace::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsBlendSpace>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsAnimBlueprint>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
			// FCsFpsAnimBlueprint
			if (StructProperty->Struct == FCsFpsAnimBlueprint::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsFpsAnimBlueprint>(InJsonWriter, StructProperty, InObject, MemberName); continue; }
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
				if (StructProperty->ArrayDim == 1)
				{ WriteMemberStructPropertyToJson<FCsCollisionPreset>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			}
			// FCsPhysicsPreset
			if (StructProperty->Struct == FCsPhysicsPreset::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsPhysicsPreset>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }
			// FCsWidgetActorInfo
			if (StructProperty->Struct == FCsWidgetActorInfo::StaticStruct())
			{ WriteMemberStructPropertyToJson<FCsWidgetActorInfo>(InJsonWriter, StructProperty, InObject, MemberName, true, nullptr); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InObject, InClass))
					continue;
			}
			continue;
		}
		// Array
		else
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TAssetPtr
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// UMaterialInstance
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UMaterialInstance>(InJsonWriter, ArrayProperty, InObject, MemberName, TEXT("Mat")); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UMaterialInstanceConstant>(InJsonWriter, ArrayProperty, InObject, MemberName, TEXT("Mat")); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UAnimSequence>(InJsonWriter, ArrayProperty, InObject, MemberName, TEXT("Anim")); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UAnimMontage>(InJsonWriter, ArrayProperty, InObject, MemberName, TEXT("Anim")); continue; }
				// UBlueprint
				if (InnerAssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteArrayAssetObjectPropertyToJson<UBlueprint>(InJsonWriter, ArrayProperty, InObject, MemberName, TEXT("Bp")); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InObject, InClass))
						continue;
				}
				continue;
			}
			// Struct
			else
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
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
				// FCsDataMappingEntry
				if (InnerStructProperty->Struct == FCsDataMappingEntry::StaticStruct())
				{ WriteMemberArrayStructPropertyToJson<FCsDataMappingEntry>(InJsonWriter, ArrayProperty, InObject, MemberName); continue; }
	
				if (Internal)
				{
					if ((*Internal)(Property, InJsonWriter, InObject, InClass))
						continue;
				}
				continue;
			}
			// FName
			else
			if (UNameProperty* NameProperty = Cast<UNameProperty>(ArrayProperty->Inner))
				WriteMemberArrayStructPropertyToJson_Primitive<FName>(InJsonWriter, ArrayProperty, InObject, MemberName, &FName::ToString);

			if (Internal)
			{
				if ((*Internal)(Property, InJsonWriter, InObject, InClass))
					continue;
			}
			continue;
		}
		// bool
		else
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
		{
			if (bool* Member = BoolProperty->ContainerPtrToValuePtr<bool>(InObject))
				InJsonWriter->WriteValue(MemberName, *Member);
		}
		// Byte / Enum
		else
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			// enum
			if (ByteProperty->IsEnum())
			{
				// ECollisionEnabled
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECollisionEnabled")))
				{ WriteMemberBytePropertyToJson<ECollisionEnabled::Type>(InJsonWriter, ByteProperty, InObject, MemberName, &ECollisionEnabled::ToString); continue; }
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECollisionChannel")))
				{ WriteMemberBytePropertyToJson<ECollisionChannel>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsCollisionChannel::ToString); continue; }
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECollisionResponse")))
				{ WriteMemberBytePropertyToJson<ECollisionResponse>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsCollisionResponse::ToString); continue; }
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(TEXT("EHorizTextAligment")))
				{ WriteMemberBytePropertyToJson<EHorizTextAligment>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsHorizTextAligment::ToString); continue; }
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(TEXT("EVerticalTextAligment")))
				{ WriteMemberBytePropertyToJson<EVerticalTextAligment>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsVerticalTextAligment::ToString); continue; }
				// ECsLoadFlags_Editor
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECsLoadFlags_Editor")))
				{ WriteMemberBytePropertyToJson<ECsLoadFlags_Editor::Type>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsLoadFlags_Editor::ToString); continue; }
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECsFxPriority")))
				{ WriteMemberBytePropertyToJson<ECsFxPriority::Type>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsFxPriority::ToString); continue; }
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECsSoundPriority")))
				{ WriteMemberBytePropertyToJson<ECsSoundPriority::Type>(InJsonWriter, ByteProperty, InObject, MemberName, &ECsSoundPriority::ToString); continue; }
				// ECsInteractiveCollision
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECsInteractiveCollision")))
				{
					if (ByteProperty->ArrayDim == 1)
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
		}
		// int32
		else
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
		{
			if (int32* Member = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
			{
#if WITH_EDITOR
				if (Property->HasMetaData(TEXT("BitmaskEnum")))
				{
					const FString BitmaskEnum = Property->GetMetaData(TEXT("BitmaskEnum"));

					if (BitmaskEnum == TEXT("ECsLoadFlags"))
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
		}
		// float
		else
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
		{
			if (float* Member = FloatProperty->ContainerPtrToValuePtr<float>(InObject))
				InJsonWriter->WriteValue(MemberName, *Member);
		}
		// FString
		else
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
		{
			if (FString* Member = StrProperty->ContainerPtrToValuePtr<FString>(InObject))
				InJsonWriter->WriteValue(MemberName, *Member);
		}
		// FName
		else
		if (UNameProperty* NameProperty = Cast<UNameProperty>(*It))
		{
			if (FName* Member = NameProperty->ContainerPtrToValuePtr<FName>(InObject))
				InJsonWriter->WriteValue(MemberName, (*Member).ToString());
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

		if (AssetName.EndsWith(TEXT("_C")))
			AssetName.RemoveFromEnd(TEXT("_C"));

		*Member = TAssetPtr<UAnimBlueprint>(AssetName);
	}
}

void UCsCommon_Load::WriteToAssetObjectPropertyFromJson_Blueprint(TSharedPtr<FJsonObject> &JsonObject, UAssetObjectProperty* &AssetObjectProperty, void* InObject, const FString &MemberName)
{
	if (TAssetPtr<UBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>>(InObject))
	{
		FString AssetName = JsonObject->GetStringField(MemberName);

		if (AssetName.EndsWith(TEXT("_C")))
			AssetName.RemoveFromEnd(TEXT("_C"));

		*Member = TAssetPtr<UBlueprint>(AssetName);
	}
}

void UCsCommon_Load::WriteToMemberStructPropertyFromJson_Transform(TSharedPtr<FJsonObject> &JsonObject, UStructProperty* &StructProperty, void* InObject, const FString &MemberName)
{
	if (FTransform* Member = StructProperty->ContainerPtrToValuePtr<FTransform>(InObject))
	{
		// Rotation
		FRotator Rotation;
		Rotation.InitFromString(JsonObject->GetStringField(TEXT("Rotation")));
		FVector RotationAsVector = FVector(Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
		FQuat Quat = FQuat::MakeFromEuler(RotationAsVector);

		Member->SetRotation(Quat);
		// Translation
		FVector Translation;
		Translation.InitFromString(JsonObject->GetStringField(TEXT("Translation")));

		Member->SetTranslation(Translation);
		// Scale
		FVector Scale;
		Scale.InitFromString(JsonObject->GetStringField(TEXT("Scale")));

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

	for (int32 I = 0; I < Count; I++)
	{
		if (I >= ArrayCount)
			break;

		if (I >= MemberCount)
			Member->AddDefaulted();

		TSharedPtr<FJsonObject> Object = JsonArray[I]->AsObject();

		FTransform& Element = (*Member)[I];

		// Rotation
		FRotator Rotation;
		Rotation.InitFromString(Object->GetStringField(TEXT("Rotation")));
		FVector RotationAsVector = FVector(Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
		FQuat Quat = FQuat::MakeFromEuler(RotationAsVector);

		Element.SetRotation(Quat);
		// Translation
		FVector Translation;
		Translation.InitFromString(Object->GetStringField(TEXT("Translation")));

		Element.SetTranslation(Translation);
		// Scale
		FVector Scale;
		Scale.InitFromString(Object->GetStringField(TEXT("Scale")));

		Element.SetScale3D(Scale);
	}
}

void UCsCommon_Load::WriteToMemberArrayStructPropertyFromJson_Name(TSharedPtr<FJsonObject> &JsonObject, UArrayProperty* &ArrayProperty, void* InObject, const FString &MemberName)
{
	TArray<FName>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<FName>>(InObject);

	const TArray<TSharedPtr<FJsonValue>> JsonArray = JsonObject->GetArrayField(MemberName);

	const int32 ArrayCount  = JsonArray.Num();
	const int32 MemberCount = Member->Num();
	const int32 Count		= FMath::Max(ArrayCount, MemberCount);

	for (int32 I = 0; I < Count; I++)
	{
		if (I >= ArrayCount)
			break;

		if (I >= MemberCount)
			Member->AddDefaulted();

		TSharedPtr<FJsonObject> Object = JsonArray[I]->AsObject();

		(*Member)[I] = FName(*Object->GetStringField(MemberName));
	}
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
				if (AssetObjectProperty->ArrayDim == 1)
				{ WriteToAssetObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
				if (AssetObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ WriteToFixedArrayAssetObjectPropertyFromJson_EnumSize<UMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(JsonObject, AssetObjectProperty, InStruct, MemberName, &ECsInteractiveState::ToString); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
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
			// UBlendSpace
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ WriteToAssetObjectPropertyFromJson<UBlendSpace>(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UAnimBlueprint
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ WriteToAssetObjectPropertyFromJson_AnimBlueprint(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			// UBlueprint
			if (AssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{ WriteToAssetObjectPropertyFromJson_Blueprint(JsonObject, AssetObjectProperty, InStruct, MemberName); continue; }
			continue;
		}
		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FVector>(JsonObject, StructProperty, InStruct, MemberName, &FVector::InitFromString); continue; }
			// FRotator
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FRotator>(JsonObject, StructProperty, InStruct, MemberName, &FRotator::InitFromString); continue; }
			// FColor
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FColor>(JsonObject, StructProperty, InStruct, MemberName, &FColor::InitFromString); continue; }
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsStaticMesh>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
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
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsTArrayMaterialInstanceConstant>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
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
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsSoundElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsFpsSoundElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsFxElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsFpsFxElement>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsAnimSequence>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpsAnimSequence
			if (StructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsAnimSequence>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsAnimMontage>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsFpsAnimMontage
			if (StructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsFpsAnimMontage>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsTArrayAnimMontage>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsBlendSpace>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpsBlendSpace
			if (StructProperty->Struct == FCsFpsBlendSpace::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsBlendSpace>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsAnimBlueprint>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
			// FCsFpsAnimBlueprint
			if (StructProperty->Struct == FCsFpsAnimBlueprint::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsAnimBlueprint>(JsonObject, StructProperty, InStruct, MemberName, Internal); continue; }
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
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsInputActionMappings>(JsonObject, StructProperty, InStruct, MemberName); continue; }
				
				if (StructProperty->ArrayDim == ECS_INPUT_DEVICE_MAX)
				{ WriteToMemberFixedArrayStructPropertyFromJson_EnumSize<FCsInputActionMappings, ECsInputDevice::Type, ECS_INPUT_DEVICE_MAX>(JsonObject, StructProperty, InStruct, MemberName, &ECsInputDevice::ToString, nullptr); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InStruct, InScriptStruct))
						continue;
				}
				continue;
			}
			// FCsInputActionMapping
			if (StructProperty->Struct == FCsInputActionMapping::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsInputActionMapping>(JsonObject, StructProperty, InStruct, MemberName); continue; }

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
				{ WriteToArrayAssetObjectPropertyFromJson<UStaticMesh>(JsonObject, ArrayProperty, InStruct, MemberName, TEXT("Mesh")); continue; }
				// USkeletalMesh
				if (InnerAssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<USkeletalMesh>(JsonObject, ArrayProperty, InStruct, MemberName, TEXT("Mesh")); continue; }
				// UMaterialInstance
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UMaterialInstance>(JsonObject, ArrayProperty, InStruct, MemberName, TEXT("Mat")); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, ArrayProperty, InStruct, MemberName, TEXT("Mat")); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UAnimSequence>(JsonObject, ArrayProperty, InStruct, MemberName, TEXT("Anim")); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UAnimMontage>(JsonObject, ArrayProperty, InStruct, MemberName, TEXT("Anim")); continue; }
				// UBlueprint
				if (InnerAssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UBlueprint>(JsonObject, ArrayProperty, InStruct, MemberName, TEXT("Bp")); continue; }
				continue;
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FVector
				if (InnerStructProperty->Struct == TBaseStructure<FVector>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FVector>(JsonObject, ArrayProperty, InStruct, MemberName, &FVector::InitFromString); continue; }
				// FRotator
				if (InnerStructProperty->Struct == TBaseStructure<FRotator>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FRotator>(JsonObject, ArrayProperty, InStruct, MemberName, &FRotator::InitFromString); continue; }
				// FColor
				if (InnerStructProperty->Struct == TBaseStructure<FColor>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FColor>(JsonObject, ArrayProperty, InStruct, MemberName, &FColor::InitFromString); continue; }
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
				// FCsInputActionMapping
				if (InnerStructProperty->Struct == FCsInputActionMapping::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsInputActionMapping>(JsonObject, ArrayProperty, InStruct, MemberName, Internal); continue; }

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
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECollisionEnabled")))
				{
					if (ECollisionEnabled::Type* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionEnabled::Type>(InStruct))
					{ *Member = ECollisionEnabled::ToType(JsonObject->GetStringField(MemberName)); continue; }
					continue;
				}
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECollisionChannel")))
				{
					if (ECollisionChannel* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionChannel>(InStruct))
					{ *Member = ECsCollisionChannel::ToType(JsonObject->GetStringField(MemberName)); continue; }
					continue;
				}
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECollisionResponse")))
				{
					if (ECollisionResponse* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionResponse>(InStruct))
					{ *Member = ECsCollisionResponse::ToType(JsonObject->GetStringField(MemberName)); continue; }
					continue;
				}
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(TEXT("EHorizTextAligment")))
				{
					if (EHorizTextAligment* Member = ByteProperty->ContainerPtrToValuePtr<EHorizTextAligment>(InStruct))
					{ *Member = ECsHorizTextAligment::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(TEXT("EVerticalTextAligment")))
				{
					if (EVerticalTextAligment* Member = ByteProperty->ContainerPtrToValuePtr<EVerticalTextAligment>(InStruct))
					{ *Member = ECsVerticalTextAligment::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsLoadFlags_Editor
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECsLoadFlags_Editor")))
				{
					if (TCsLoadFlags_Editor* Member = ByteProperty->ContainerPtrToValuePtr<TCsLoadFlags_Editor>(InStruct))
					{ *Member = ECsLoadFlags_Editor::ToType(JsonObject->GetStringField(MemberName)); continue; }
					continue;
				}
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECsFxPriority")))
				{
					if (TCsFxPriority* Member = ByteProperty->ContainerPtrToValuePtr<TCsFxPriority>(InStruct))
					{ *Member = ECsFxPriority::ToType(JsonObject->GetStringField(MemberName)); continue; }
					continue;
				}
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECsSoundPriority")))
				{
					if (TCsSoundPriority* Member = ByteProperty->ContainerPtrToValuePtr<TCsSoundPriority>(InStruct))
					{ *Member = ECsSoundPriority::ToType(JsonObject->GetStringField(MemberName)); continue; }
					continue;
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

						for (int32 I = 0; I < 10; I++)
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
			if (NameProperty->ArrayDim == 1)
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

void UCsCommon_Load::ReadObjectFromJson(TSharedPtr<FJsonObject> &JsonParsed, void* InObject, UClass* const &InClass, const TArray<FCsCategoryMemberAssociation> &CategoryMemberAssociations, TCsReadObjectFromJson_Internal Internal /*=nullptr*/)
{
	const FString NoCategory = TEXT("");
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
				if (AssetObjectProperty->ArrayDim == 1)
				{ WriteToAssetObjectPropertyFromJson_Blueprint(JsonObject, AssetObjectProperty, InObject, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InObject, InClass))
						continue;
				}
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
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FVector>(JsonObject, StructProperty, InObject, MemberName, &FVector::InitFromString); continue; }
			// FRotator
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FRotator>(JsonObject, StructProperty, InObject, MemberName, &FRotator::InitFromString); continue; }
			// FColor
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
			{ WriteToMemberStructPropertyFromJson_Primitive<FColor>(JsonObject, StructProperty, InObject, MemberName, &FColor::InitFromString); continue; }
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsStaticMesh>(JsonObject, StructProperty, InObject, MemberName, nullptr); continue; }
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
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsTArrayMaterialInstanceConstant>(JsonObject, StructProperty, InObject, MemberName); continue; }
				if (StructProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ WriteToMemberFixedArrayStructPropertyFromJson_EnumSize<FCsTArrayMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(JsonObject, StructProperty, InObject, MemberName, &ECsInteractiveState::ToString, nullptr); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InObject, InClass))
						continue;
				}
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
			// FCsCurveFloat
			if (StructProperty->Struct == FCsCurveFloat::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsCurveFloat>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsCurveVector>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsSoundElement>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InObject, InClass))
						continue;
				}
				continue;
			}
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsFpsSoundElement>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InObject, InClass))
						continue;
				}
				continue;
			}
			// FCsParticleSystem
			if (StructProperty->Struct == FCsParticleSystem::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsParticleSystem>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsFxElement>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InObject, InClass))
						continue;
				}
				continue;
			}
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsFpsFxElement>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InObject, InClass))
						continue;
				}
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsAnimSequence>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsFpsAnimSequence
			if (StructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsAnimSequence>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsAnimMontage>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InObject, InClass))
						continue;
				}
				continue;
			}
			// FCsFpsAnimMontage
			if (StructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsFpsAnimMontage>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InObject, InClass))
						continue;
				}
				continue;
			}
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsTArrayAnimMontage>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InObject, InClass))
						continue;
				}
				continue;
			}
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsBlendSpace>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsFpsBlendSpace
			if (StructProperty->Struct == FCsFpsBlendSpace::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsBlendSpace>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsAnimBlueprint>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsFpsAnimBlueprint
			if (StructProperty->Struct == FCsFpsAnimBlueprint::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsFpsAnimBlueprint>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCollisionResponseContainer
			if (StructProperty->Struct == FCollisionResponseContainer::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCollisionResponseContainer>(JsonObject, StructProperty, InObject, MemberName); continue; }
			// FCsCollisionPreset
			if (StructProperty->Struct == FCsCollisionPreset::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ WriteToMemberStructPropertyFromJson<FCsCollisionPreset>(JsonObject, StructProperty, InObject, MemberName); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, JsonObject, InObject, InClass))
						continue;
				}
				continue;
			}
			// FCsWidgetActorInfo
			if (StructProperty->Struct == FCsWidgetActorInfo::StaticStruct())
			{ WriteToMemberStructPropertyFromJson<FCsWidgetActorInfo>(JsonObject, StructProperty, InObject, MemberName); continue; }

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
				{ WriteToArrayAssetObjectPropertyFromJson<UMaterialInstance>(JsonObject, ArrayProperty, InObject, MemberName, TEXT("Mat")); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UMaterialInstanceConstant>(JsonObject, ArrayProperty, InObject, MemberName, TEXT("Mat")); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UAnimSequence>(JsonObject, ArrayProperty, InObject, MemberName, TEXT("Anim")); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UAnimMontage>(JsonObject, ArrayProperty, InObject, MemberName, TEXT("Anim")); continue; }
				// UBlueprint
				if (InnerAssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ WriteToArrayAssetObjectPropertyFromJson<UBlueprint>(JsonObject, ArrayProperty, InObject, MemberName, TEXT("Bp")); continue; }
				
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
				// FVector
				if (InnerStructProperty->Struct == TBaseStructure<FVector>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FVector>(JsonObject, ArrayProperty, InObject, MemberName, &FVector::InitFromString); continue; }
				// FRotator
				if (InnerStructProperty->Struct == TBaseStructure<FRotator>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FRotator>(JsonObject, ArrayProperty, InObject, MemberName, &FRotator::InitFromString); continue; }
				// FColor
				if (InnerStructProperty->Struct == TBaseStructure<FColor>::Get())
				{ WriteToMemberArrayStructPropertyFromJson_Primitive<FColor>(JsonObject, ArrayProperty, InObject, MemberName, &FColor::InitFromString); continue; }
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
				// FCsDataMappingEntry
				if (InnerStructProperty->Struct == FCsDataMappingEntry::StaticStruct())
				{ WriteToMemberArrayStructPropertyFromJson<FCsDataMappingEntry>(JsonObject, ArrayProperty, InObject, MemberName, nullptr); continue; }

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
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECollisionEnabled")))
				{
					if (ECollisionEnabled::Type* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionEnabled::Type>(InObject))
					{ *Member = ECollisionEnabled::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECollisionChannel
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECollisionChannel")))
				{
					if (ECollisionChannel* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionChannel>(InObject))
					{ *Member = ECsCollisionChannel::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECollisionResponse
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECollisionResponse")))
				{
					if (ECollisionResponse* Member = ByteProperty->ContainerPtrToValuePtr<ECollisionResponse>(InObject))
					{ *Member = ECsCollisionResponse::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// EHorizTextAligment
				if (ByteProperty->Enum->CppType.Contains(TEXT("EHorizTextAligment")))
				{
					if (EHorizTextAligment* Member = ByteProperty->ContainerPtrToValuePtr<EHorizTextAligment>(InObject))
					{ *Member = ECsHorizTextAligment::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// EVerticalTextAligment
				if (ByteProperty->Enum->CppType.Contains(TEXT("EVerticalTextAligment")))
				{
					if (EVerticalTextAligment* Member = ByteProperty->ContainerPtrToValuePtr<EVerticalTextAligment>(InObject))
					{ *Member = ECsVerticalTextAligment::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsFxPriority
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECsFxPriority")))
				{
					if (TCsFxPriority* Member = ByteProperty->ContainerPtrToValuePtr<TCsFxPriority>(InObject))
					{ *Member = ECsFxPriority::ToType(JsonObject->GetStringField(MemberName)); continue; }
				}
				// ECsSoundPriority
				if (ByteProperty->Enum->CppType.Contains(TEXT("ECsSoundPriority")))
				{
					if (TCsSoundPriority* Member = ByteProperty->ContainerPtrToValuePtr<TCsSoundPriority>(InObject))
					{ *Member = ECsSoundPriority::ToType(JsonObject->GetStringField(MemberName)); continue; }
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

						for (int32 I = 0; I < 10; I++)
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

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_AnimMontage(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TAssetPtr<UAnimMontage>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UAnimMontage>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		if (AssetName == TEXT(""))
			return;

		const FString MemberName	 = AssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
		{
			if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
			{
				if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				{
					OutAssetReferences.AddDefaulted();

					const int32 Size = OutAssetReferences.Num();

					FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
					Reference.Reference = AssetName;
					Reference.Reference_Internal = AssetRef;
#if WITH_EDITOR
					if (CalculateResourceSizes)
					{
						UAnimMontage* Asset = Cast<UAnimMontage>(Member->LoadSynchronous());

						TArray<UAnimationAsset*> AnimationAssets;

						Asset->GetAllAnimationSequencesReferred(AnimationAssets);

						const int32 Count = AnimationAssets.Num();

						for (int32 I = 0; I < Count; I++)
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
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_AnimMontage(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TAssetPtr<UAnimMontage>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UAnimMontage>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		if (AssetName == TEXT(""))
			return;

		const FString MemberName	 = AssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
		{
			if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
			{
				if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				{
					OutAssetReferences.AddDefaulted();

					const int32 Size = OutAssetReferences.Num();

					FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
					Reference.Reference				   = AssetName;
					Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
					if (CalculateResourceSizes)
					{
						UAnimMontage* Asset = Cast<UAnimMontage>(Member->LoadSynchronous());

						TArray<UAnimationAsset*> AnimationAssets;

						Asset->GetAllAnimationSequencesReferred(AnimationAssets);

						const int32 Count = AnimationAssets.Num();

						for (int32 I = 0; I < Count; I++)
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
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_AnimSequence(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TAssetPtr<UAnimSequence>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UAnimSequence>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		if (AssetName == TEXT(""))
			return;

		const FString MemberName	 = AssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
		{
			if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
			{
				if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				{
					OutAssetReferences.AddDefaulted();

					const int32 Size = OutAssetReferences.Num();

					FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
					Reference.Reference				   = AssetName;
					Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
					if (CalculateResourceSizes)
					{
						UAnimSequence* Asset = Cast<UAnimSequence>(Member->LoadSynchronous());

						Reference.Size.Bytes	 = Asset->GetApproxCompressedSize();
						Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
						Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
					}
#endif // #if WITH_EDITOR
				}
			}
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_AnimSequence(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TAssetPtr<UAnimSequence>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UAnimSequence>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		if (AssetName == TEXT(""))
			return;

		const FString MemberName	 = AssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
		{
			if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
			{
				if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				{
					OutAssetReferences.AddDefaulted();

					const int32 Size = OutAssetReferences.Num();

					FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
					Reference.Reference				   = AssetName;
					Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
					if (CalculateResourceSizes)
					{
						UAnimSequence* Asset = Cast<UAnimSequence>(Member->LoadSynchronous());

						Reference.Size.Bytes	 = Asset->GetApproxCompressedSize();
						Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
						Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
					}
#endif // #if WITH_EDITOR
				}
			}
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_MaterialInstanceConstant(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TAssetPtr<UMaterialInstanceConstant>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UMaterialInstanceConstant>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		if (AssetName == TEXT(""))
			return;

		const FString MemberName	 = AssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
		{
			if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
			{
				if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				{
					OutAssetReferences.AddDefaulted();

					const int32 Size = OutAssetReferences.Num();

					FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
					Reference.Reference				   = AssetName;
					Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
					if (CalculateResourceSizes)
					{
						UMaterialInstanceConstant* Asset = Cast<UMaterialInstanceConstant>(Member->LoadSynchronous());

						const int32 Count = Asset->TextureParameterValues.Num();

						for (int32 I = 0; I < Count; I++)
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
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_MaterialInstanceConstant(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TAssetPtr<UMaterialInstanceConstant>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UMaterialInstanceConstant>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		if (AssetName == TEXT(""))
			return;

		const FString MemberName	 = AssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
		{
			if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
			{
				if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				{
					OutAssetReferences.AddDefaulted();

					const int32 Size = OutAssetReferences.Num();

					FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
					Reference.Reference				   = AssetName;
					Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
					if (CalculateResourceSizes)
					{
						UMaterialInstanceConstant* Asset = Cast<UMaterialInstanceConstant>(Member->LoadSynchronous());

						const int32 Count = Asset->TextureParameterValues.Num();

						for (int32 I = 0; I < Count; I++)
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
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_Blueprint(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TAssetPtr<UBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		if (AssetName == TEXT(""))
			return;

		const FString MemberName	 = AssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
		{
			if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
			{
				if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				{
					OutAssetReferences.AddDefaulted();

					const int32 Size = OutAssetReferences.Num();

					// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TAssetPtr for UAnimBlueprint / UWidgetBlueprint does NOT have _C
					FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
					Reference.Reference				   = AssetName.EndsWith(TEXT("_C")) ? AssetName : AssetName + TEXT("_C");
					Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
					if (CalculateResourceSizes)
					{
						UObject* Asset = Member->LoadSynchronous();

						Reference.Size.Bytes = Asset->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
						Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
						Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
					}
#endif // #if WITH_EDITOR
				}
			}
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromAssetObjectProperty_Blueprint(UAssetObjectProperty* &AssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TAssetPtr<UBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>>(InObject))
	{
		const FStringAssetReference AssetRef = Member->ToStringReference();
		const FString AssetName				 = AssetRef.ToString();

		if (AssetName == TEXT(""))
			return;

		const FString MemberName	 = AssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
		{
			if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
			{
				if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				{
					OutAssetReferences.AddDefaulted();

					const int32 Size = OutAssetReferences.Num();

					// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TAssetPtr for UAnimBlueprint / UWidgetBlueprint does NOT have _C
					FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
					Reference.Reference				   = AssetName.EndsWith(TEXT("_C")) ? AssetName : AssetName + TEXT("_C");
					Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
					if (CalculateResourceSizes)
					{
						UObject* Asset = Member->LoadSynchronous();

						Reference.Size.Bytes = Asset->GetResourceSizeBytes(EResourceSizeMode::Inclusive);
						Reference.Size.Kilobytes = UCsCommon::BytesToKilobytes(Reference.Size.Bytes);
						Reference.Size.Megabytes = UCsCommon::BytesToMegabytes(Reference.Size.Bytes);
					}
#endif // #if WITH_EDITOR
				}
			}
		}
	}
}

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_AnimMontage(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TArray<TAssetPtr<UAnimMontage>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UAnimMontage>>>(InObject))
	{
		const FString MemberName	 = ArrayAssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		int32* MemberLoadFlags = nullptr;

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject);

		if (!MemberLoadFlags)
			return;

		if (!CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
			return;

		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; I++)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			if (AssetName == TEXT(""))
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CalculateResourceSizes)
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

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_AnimMontage(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TArray<TAssetPtr<UAnimMontage>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UAnimMontage>>>(InObject))
	{
		const FString MemberName	 = ArrayAssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		int32* MemberLoadFlags = nullptr;

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject);

		if (!MemberLoadFlags)
			return;

		if (!CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
			return;

		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; I++)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			if (AssetName == TEXT(""))
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CalculateResourceSizes)
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

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_AnimSequence(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TArray<TAssetPtr<UAnimSequence>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UAnimSequence>>>(InObject))
	{
		const FString MemberName	 = ArrayAssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		int32* MemberLoadFlags = nullptr;

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject);

		if (!MemberLoadFlags)
			return;

		if (!CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
			return;

		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; I++)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			if (AssetName == TEXT(""))
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CalculateResourceSizes)
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

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_AnimSequence(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TArray<TAssetPtr<UAnimSequence>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UAnimSequence>>>(InObject))
	{
		const FString MemberName	 = ArrayAssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		int32* MemberLoadFlags = nullptr;

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject);

		if (!MemberLoadFlags)
			return;

		if (!CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
			return;

		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; I++)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			if (AssetName == TEXT(""))
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CalculateResourceSizes)
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

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_MaterialInstanceConstant(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TArray<TAssetPtr<UMaterialInstanceConstant>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UMaterialInstanceConstant>>>(InObject))
	{
		const FString MemberName	 = ArrayAssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		int32* MemberLoadFlags = nullptr;

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject);

		if (!MemberLoadFlags)
			return;

		const int32 Count = Member->Num();

		if (!CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
			return;

		for (int32 I = 0; I < Count; I++)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			if (AssetName == TEXT(""))
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CalculateResourceSizes)
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

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_MaterialInstanceConstant(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TArray<TAssetPtr<UMaterialInstanceConstant>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UMaterialInstanceConstant>>>(InObject))
	{
		const FString MemberName	 = ArrayAssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		int32* MemberLoadFlags = nullptr;

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject);

		if (!MemberLoadFlags)
			return;

		if (!CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
			return;

		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; I++)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			if (AssetName == TEXT(""))
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();

			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName;
			Reference.Reference_Internal	   = AssetRef;
#if WITH_EDITOR
			if (CalculateResourceSizes)
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

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_Blueprint(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UScriptStruct* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TArray<TAssetPtr<UBlueprint>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UBlueprint>>>(InObject))
	{
		const FString MemberName	 = ArrayAssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		int32* MemberLoadFlags = nullptr;

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject);

		if (!MemberLoadFlags)
			return;

		if (!CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
			return;

		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; I++)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			if (AssetName == TEXT(""))
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();
			// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TAssetPtr for UWidgetBlueprint does NOT have _C
			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName.EndsWith(TEXT("_C")) ? AssetName : AssetName + TEXT("_C");
			Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
			if (CalculateResourceSizes)
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

void UCsCommon_Load::GetAssetReferenceFromArrayAssetObjectProperty_Blueprint(UArrayProperty* &ArrayAssetObjectProperty, void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences)
{
	if (TArray<TAssetPtr<UBlueprint>>* Member = ArrayAssetObjectProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UBlueprint>>>(InObject))
	{
		const FString MemberName	 = ArrayAssetObjectProperty->GetName();
		const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

		int32* MemberLoadFlags = nullptr;

		if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
			MemberLoadFlags			  = IntProperty->ContainerPtrToValuePtr<int32>(InObject);

		if (!MemberLoadFlags)
			return;

		if (!CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
			return;

		const int32 Count = Member->Num();

		for (int32 I = 0; I < Count; I++)
		{
			const FStringAssetReference AssetRef = (*Member)[I].ToStringReference();
			const FString AssetName				 = AssetRef.ToString();

			if (AssetName == TEXT(""))
				continue;

			OutAssetReferences.AddDefaulted();

			const int32 Size = OutAssetReferences.Num();
			// TODO: Fix / Investigate. 4.16.1. Built Game (Okay in Editor). TAssetPtr for UWidgetBlueprint does NOT have _C
			FCsStringAssetReference& Reference = OutAssetReferences[Size - 1];
			Reference.Reference				   = AssetName.EndsWith(TEXT("_C")) ? AssetName : AssetName + TEXT("_C");
			Reference.Reference_Internal	   = FStringAssetReference(Reference.Reference);
#if WITH_EDITOR
			if (CalculateResourceSizes)
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

void UCsCommon_Load::GetAssetReferencesFromStruct(void* InStruct, UScriptStruct* const &InScriptStruct, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromStruct_Internal Internal /*=nullptr*/)
{
	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// TAssetSubclassOf
		if (UAssetClassProperty* AssetClassProperty = Cast<UAssetClassProperty>(*It))
		{
			if (Internal)
			{
				if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences))
					continue;
			}
			continue;
		}
		// TAssetPtr
		if (UAssetObjectProperty* AssetObjectProperty = Cast<UAssetObjectProperty>(*It))
		{
			// UStaticMesh
			if (AssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UStaticMesh>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, EResourceSizeMode::Exclusive, OutAssetReferences); continue; }
			// USkeletalMesh
			if (AssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<USkeletalMesh>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, EResourceSizeMode::Exclusive, OutAssetReferences); continue; }
			// UMaterialInstance
			if (AssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UMaterialInstance>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, EResourceSizeMode::Inclusive, OutAssetReferences); continue; }
			// UMaterialInstanceConstant
			if (AssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == 1)
				{ GetAssetReferenceFromAssetObjectProperty_MaterialInstanceConstant(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences); continue; }
				if (AssetObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ GetAssetReferenceFromFixedArrayAssetObjectProperty_EnumSize_MaterialInstanceConstant<ECS_INTERACTIVE_STATE_MAX>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences))
						continue;
				}
				continue;
			}
			// UPhysicalMaterial
			if (AssetObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UPhysicalMaterial>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, EResourceSizeMode::Inclusive, OutAssetReferences); continue; }
			// UPhysicsAsset
			if (AssetObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UPhysicsAsset>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, EResourceSizeMode::Exclusive, OutAssetReferences); continue; }
			// UAnimSequence
			if (AssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty_AnimSequence(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences); continue; }
			// UAnimMontage
			if (AssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty_AnimMontage(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences); continue; }
			// UBlendSpace
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UBlendSpace>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, EResourceSizeMode::Exclusive, OutAssetReferences); continue; }
			// UAnimBlueprint
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty_Blueprint(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences); continue; }
			// USoundCue
			if (AssetObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<USoundCue>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, EResourceSizeMode::Inclusive, OutAssetReferences); continue; }
			// UParticleSystem
			if (AssetObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UParticleSystem>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, EResourceSizeMode::Inclusive, OutAssetReferences); continue; }
			// UCurveFloat
			if (AssetObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UCurveFloat>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, EResourceSizeMode::Inclusive, OutAssetReferences); continue; }
			// UCurveVector
			if (AssetObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ GetAssetReferenceFromAssetObjectProperty<UCurveVector>(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, EResourceSizeMode::Inclusive, OutAssetReferences); continue; }
			// UBlueprint
			if (AssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == 1)
				{ GetAssetReferenceFromAssetObjectProperty_Blueprint(AssetObjectProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences); continue; }
			}
			
			if (Internal)
			{
				if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences))
					continue;
			}
			continue;
		}
		// Structs
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FCsStaticMesh
			if (StructProperty->Struct == FCsStaticMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsStaticMesh>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsSkeletalMesh>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsMaterialInstance>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			// FCsPhysicalMaterial
			if (StructProperty->Struct == FCsPhysicalMaterial::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsPhysicalMaterial>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsPhysicsAsset>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ GetAssetReferencesFromStructProperty<FCsSoundElement>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			}
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ GetAssetReferencesFromStructProperty<FCsFpsSoundElement>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ GetAssetReferencesFromStructProperty<FCsFxElement>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			}
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ GetAssetReferencesFromStructProperty<FCsFpsFxElement>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsAnimSequence>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			// FCsFpsAnimSequence
			if (StructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsAnimSequence>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsAnimMontage>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			// FCsFpsAnimMontage
			if (StructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsAnimMontage>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsTArrayAnimMontage>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsAnimBlueprint>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			// FCsFpsAnimBlueprint
			if (StructProperty->Struct == FCsFpsAnimBlueprint::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsAnimBlueprint>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsBlendSpace>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			// FCsFpsBlendSpace
			if (StructProperty->Struct == FCsFpsBlendSpace::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsBlendSpace>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			// FCsBlueprint
			if (StructProperty->Struct == FCsBlueprint::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsBlueprint>(StructProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
			
			if (Internal)
			{
				if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences))
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
					if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences))
						continue;
				}
				continue;
			}
			// TAssetPtr
			if (UAssetObjectProperty* InnerAssetObjectProperty = Cast<UAssetObjectProperty>(ArrayProperty->Inner))
			{
				// UStaticMesh
				if (InnerAssetObjectProperty->PropertyClass == UStaticMesh::StaticClass())
				{ GetAssetReferenceFromArrayAssetObjectProperty<UStaticMesh>(ArrayProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, EResourceSizeMode::Exclusive, OutAssetReferences); continue; }
				// USkeletalMesh
				if (InnerAssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
				{ GetAssetReferenceFromArrayAssetObjectProperty<USkeletalMesh>(ArrayProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, EResourceSizeMode::Exclusive, OutAssetReferences); continue; }
				// UMaterialInstance
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
				{ GetAssetReferenceFromArrayAssetObjectProperty<UMaterialInstance>(ArrayProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, EResourceSizeMode::Inclusive, OutAssetReferences); continue; }
				// UMaterialInstanceConstant
				if (InnerAssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
				{ GetAssetReferenceFromArrayAssetObjectProperty_MaterialInstanceConstant(ArrayProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences); continue; }
				// UAnimSequence
				if (InnerAssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
				{ GetAssetReferenceFromArrayAssetObjectProperty_AnimSequence(ArrayProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences); continue; }
				// UAnimMontage
				if (InnerAssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
				{ GetAssetReferenceFromArrayAssetObjectProperty_AnimMontage(ArrayProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences); continue; }
				// UBlueprint
				if (InnerAssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
				{ GetAssetReferenceFromArrayAssetObjectProperty_Blueprint(ArrayProperty, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences))
						continue;
				}
				continue;
			}
			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				// FCsAnimMontage
				if (InnerStructProperty->Struct == FCsAnimMontage::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsAnimMontage>(ArrayProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
				// FCsFxElement
				if (InnerStructProperty->Struct == FCsFxElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFxElement>(ArrayProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
				// FCsFpsFxElement
				if (InnerStructProperty->Struct == FCsFpsFxElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpsFxElement>(ArrayProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
				// FCsSoundElement
				if (InnerStructProperty->Struct == FCsSoundElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsSoundElement>(ArrayProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpsSoundElement>(ArrayProperty, InStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences, Internal); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, InStruct, InScriptStruct, LoadFlags, CalculateResourceSizes, OutAssetReferences))
						continue;
				}
				continue;
			}
			continue;
		}
	}
}

void UCsCommon_Load::GetAssetReferencesFromObject(void* InObject, UClass* const &InClass, const ECsLoadFlags &LoadFlags, const bool &CalculateResourceSizes, TArray<FCsStringAssetReference> &OutAssetReferences, TCsGetAssetReferencesFromObject_Internal Internal /*=nullptr*/)
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
			{ GetAssetReferencesFromStructProperty<FCsStaticMesh>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsFpsStaticMesh
			if (StructProperty->Struct == FCsFpsStaticMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsStaticMesh>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsTArrayStaticMesh
			if (StructProperty->Struct == FCsTArrayStaticMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsTArrayStaticMesh>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsSkeletalMesh
			if (StructProperty->Struct == FCsSkeletalMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsSkeletalMesh>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsFpsSkeletalMesh
			if (StructProperty->Struct == FCsFpsSkeletalMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsSkeletalMesh>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsTArraySkeletalMesh
			if (StructProperty->Struct == FCsTArraySkeletalMesh::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsTArraySkeletalMesh>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsMaterialInstance
			if (StructProperty->Struct == FCsMaterialInstance::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsMaterialInstance>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsMaterialInstanceConstant
			if (StructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsMaterialInstanceConstant>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsTArrayMaterialInstanceConstant::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ GetAssetReferencesFromStructProperty<FCsTArrayMaterialInstanceConstant>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
				if (StructProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ GetAssetReferencesFromFixedArrayStructProperty_EnumSize<FCsTArrayMaterialInstanceConstant, ECS_INTERACTIVE_STATE_MAX>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, InObject, InClass, LoadFlags, CalculateResourceSizes, OutAssetReferences))
						continue;
				}
				continue;
			}
			// FCsFpsTArrayMaterialInstanceConstant
			if (StructProperty->Struct == FCsFpsTArrayMaterialInstanceConstant::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsTArrayMaterialInstanceConstant>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsInteractiveMaterials
			if (StructProperty->Struct == FCsInteractiveMaterials::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsInteractiveMaterials>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsPhysicalMaterial
			if (StructProperty->Struct == FCsPhysicalMaterial::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsPhysicalMaterial>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsPhysicsAsset
			if (StructProperty->Struct == FCsPhysicsAsset::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsPhysicsAsset>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsCurveFloat
			if (StructProperty->Struct == FCsCurveFloat::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsCurveFloat>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsCurveVector>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == 1)
				{ GetAssetReferencesFromStructProperty<FCsSoundElement>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, InObject, InClass, LoadFlags, CalculateResourceSizes, OutAssetReferences))
						continue;
				}
				continue;
			}
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == 1)
				{ GetAssetReferencesFromStructProperty<FCsFpsSoundElement>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, InObject, InClass, LoadFlags, CalculateResourceSizes, OutAssetReferences))
						continue;
				}
				continue;
			}
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsCurveVector>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsParticleSystem
			if (StructProperty->Struct == FCsParticleSystem::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsParticleSystem>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == 1)
				{ GetAssetReferencesFromStructProperty<FCsFxElement>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, InObject, InClass, LoadFlags, CalculateResourceSizes, OutAssetReferences))
						continue;
				}
				continue;
			}
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{ 
				if (StructProperty->ArrayDim == 1)
				{ GetAssetReferencesFromStructProperty<FCsFpsFxElement>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, InObject, InClass, LoadFlags, CalculateResourceSizes, OutAssetReferences))
						continue;
				}
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsAnimSequence>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsFpsAnimSequence
			if (StructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsAnimSequence>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsAnimMontage>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsFpsAnimMontage
			if (StructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsAnimMontage>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsTArrayAnimMontage>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsAnimBlueprint>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsFpsAnimBlueprint
			if (StructProperty->Struct == FCsFpsAnimBlueprint::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsAnimBlueprint>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsBlendSpace>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsFpsBlendSpace
			if (StructProperty->Struct == FCsFpsBlendSpace::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsFpsBlendSpace>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsBlueprint
			if (StructProperty->Struct == FCsBlueprint::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsBlueprint>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsTArrayBlueprint
			if (StructProperty->Struct == FCsTArrayBlueprint::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsTArrayBlueprint>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
			// FCsWidgetActorInfo
			if (StructProperty->Struct == FCsWidgetActorInfo::StaticStruct())
			{ GetAssetReferencesFromStructProperty<FCsWidgetActorInfo>(StructProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }

			if (Internal)
			{
				if ((*Internal)(Property, InObject, InClass, LoadFlags, CalculateResourceSizes, OutAssetReferences))
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
				{ GetAssetReferencesFromArrayStructProperty<FCsMaterialInstance>(ArrayProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
				// FCsMaterialInstanceConstant
				if (InnerStructProperty->Struct == FCsMaterialInstanceConstant::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsMaterialInstanceConstant>(ArrayProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
				// FCsFxElement
				if (InnerStructProperty->Struct == FCsFxElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFxElement>(ArrayProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
				// FCsFpsFxElement
				if (InnerStructProperty->Struct == FCsFpsFxElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpsFxElement>(ArrayProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
				// FCsFpsSoundElement
				if (InnerStructProperty->Struct == FCsFpsSoundElement::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpsSoundElement>(ArrayProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
				// FCsFpsAnimSequence
				if (InnerStructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpsAnimSequence>(ArrayProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
				// FCsFpsAnimMontage
				if (InnerStructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
				{ GetAssetReferencesFromArrayStructProperty<FCsFpsAnimMontage>(ArrayProperty, InObject, LoadFlags, CalculateResourceSizes, OutAssetReferences, nullptr); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, InObject, InClass, LoadFlags, CalculateResourceSizes, OutAssetReferences))
						continue;
				}
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
	const FString AssetName = AssetPtr.ToString();

	if (AssetName == TEXT(""))
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
		const FString AssetDescription = TEXT("AnimBlueprint'") + AssetName + TEXT("_C'");
		Internal					    = (UAnimBlueprintGeneratedClass*)StaticLoadObject(UClass::StaticClass(), NULL, *AssetDescription, NULL, LOAD_None, NULL);

		if (!Internal)
		{
			UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetPtr_AnimBlueprint (%s): Failed to load Anim Blueprint at %s"), *MemberName, *AssetDescription);
		}
	}
}

void UCsCommon_Load::LoadTAssetPtr_AnimBlueprint(const FString &MemberName, TAssetPtr<UAnimBlueprint>* AssetPtr, UAnimBlueprintGeneratedClass* &Internal)
{
	const FString AssetName = AssetPtr->ToString();

	if (AssetName == TEXT(""))
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
		const FString AssetDescription = TEXT("AnimBlueprint'") + AssetName + TEXT("_C'");
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
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
			return;

		const FString InternalMemberName = MemberName + TEXT("_Internal");

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (UAnimBlueprintGeneratedClass** Internal = InternalProperty->ContainerPtrToValuePtr<UAnimBlueprintGeneratedClass*>(InObject))
				LoadTAssetPtr_AnimBlueprint(ObjectName + TEXT(".") + MemberName, Member, *Internal);
		}
	}
}

void UCsCommon_Load::LoadAssetObjectProperty_AnimBlueprint(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TAssetPtr<UAnimBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UAnimBlueprint>>(InObject))
	{
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
			return;

		const FString InternalMemberName = MemberName + TEXT("_Internal");

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (UAnimBlueprintGeneratedClass** Internal = InternalProperty->ContainerPtrToValuePtr<UAnimBlueprintGeneratedClass*>(InObject))
				LoadTAssetPtr_AnimBlueprint(ObjectName + TEXT(".") + MemberName, Member, *Internal);
		}
	}
}

void UCsCommon_Load::LoadTAssetPtr_Blueprint(const FString &MemberName, TAssetPtr<UBlueprint> AssetPtr, UBlueprintGeneratedClass* &Internal)
{
	const FString AssetName = AssetPtr.ToString();

	if (AssetName == TEXT(""))
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
		const FString AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("_C'");
		Internal					   = (UBlueprintGeneratedClass*)StaticLoadObject(UClass::StaticClass(), NULL, *AssetDescription, NULL, LOAD_None, NULL);

		if (!Internal)
		{
			UE_LOG(LogLoad, Warning, TEXT("UCsCommon::LoadTAssetPtr_Blueprint (%s): Failed to load Blueprint at %s"), *MemberName, *AssetDescription);
		}
	}
}

void UCsCommon_Load::LoadTAssetPtr_Blueprint(const FString &MemberName, TAssetPtr<UBlueprint>* AssetPtr, UBlueprintGeneratedClass* &Internal)
{
	const FString AssetName = AssetPtr->ToString();

	if (AssetName == TEXT(""))
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
		const FString AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("_C'");
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

	for (int32 I = 0; I < Count; I++)
	{
		TAssetPtr<UBlueprint>& AssetPtr = ArrayAssetPtr[I];

		if (AssetPtr.IsValid() && AssetPtr.Get())
		{
			UBlueprint* Bp				   = AssetPtr.Get();
			UBlueprintGeneratedClass* Data = Cast<UBlueprintGeneratedClass>(Cast<UBlueprintCore>(Bp)->GeneratedClass);

			ArrayInternal.Add(Data);
			continue;
		}
		
		const FString AssetName = AssetPtr.ToString();

		if (AssetName != TEXT(""))
		{
			const FString AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("_C'");
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

	for (int32 I = 0; I < Count; I++)
	{
		TAssetPtr<UBlueprint>& AssetPtr	= (*ArrayAssetPtr)[I];

		if (AssetPtr.IsValid() && AssetPtr.Get())
		{
			UBlueprint* Bp				   = AssetPtr.Get();
			UBlueprintGeneratedClass* Data = Cast<UBlueprintGeneratedClass>(Cast<UBlueprintCore>(Bp)->GeneratedClass);

			ArrayInternal.Add(Data);
			continue;
		}

		const FString AssetName = AssetPtr.ToString();

		if (AssetName != TEXT(""))
		{
			const FString AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("_C'");
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

void UCsCommon_Load::LoadFCsFpsAnimSequence(const FString &MemberName, FCsFpsAnimSequence* Anim, const ECsLoadFlags &LoadFlags)
{
	LoadFCsStruct<FCsFpsAnimSequence>(MemberName, Anim, LoadFlags);
}

void UCsCommon_Load::LoadFCsFpsAnimSequence(const FString &MemberName, FCsFpsAnimSequence* Anim, const TCsViewType &ViewType)
{
	ECsLoadFlags LoadFlags = ECsLoadFlags::All;

	if (ViewType == ECsViewType::FirstPerson)
		LoadFlags = ECsLoadFlags::Game1P;
	if (ViewType == ECsViewType::ThirdPerson)
		LoadFlags = ECsLoadFlags::Game3P;
	if (ViewType == ECsViewType::VR)
		LoadFlags = ECsLoadFlags::GameVR;

	LoadFCsFpsAnimSequence(MemberName, Anim, LoadFlags);
}

void UCsCommon_Load::LoadFCsAnimMontage(const FString &MemberName, FCsAnimMontage* Anim, const ECsLoadFlags &LoadFlags)
{
	LoadFCsStruct<FCsAnimMontage>(MemberName, Anim, LoadFlags);
}

void UCsCommon_Load::LoadFCsAnimMontage(const FString &MemberName, FCsAnimMontage* Anim)
{
	LoadFCsAnimMontage(MemberName, Anim, ECsLoadFlags::All);
}

void UCsCommon_Load::LoadFCsFpsAnimMontage(const FString &MemberName, FCsFpsAnimMontage* Anim, const ECsLoadFlags &LoadFlags)
{
	LoadFCsStruct<FCsFpsAnimMontage>(MemberName, Anim, LoadFlags);
}

void UCsCommon_Load::LoadFCsFpsAnimMontage(const FString &MemberName, FCsFpsAnimMontage* Anim, const TCsViewType &ViewType)
{
	ECsLoadFlags LoadFlags = ECsLoadFlags::All;

	if (ViewType == ECsViewType::FirstPerson)
		LoadFlags = ECsLoadFlags::Game1P;
	if (ViewType == ECsViewType::ThirdPerson)
		LoadFlags = ECsLoadFlags::Game3P;
	if (ViewType == ECsViewType::VR)
		LoadFlags = ECsLoadFlags::GameVR;

	LoadFCsFpsAnimMontage(MemberName, Anim, LoadFlags);
}

bool UCsCommon_Load::CanLoad(void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

	if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
	{
		if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
		{
			if (LoadFlags == ECsLoadFlags::All)
				return true;
			if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, ECsLoadFlags::All))
				return true;
			if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				return true;
		}
	}
	return false;
}

bool UCsCommon_Load::CanLoad(void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	const FString FlagMemberName = MemberName + TEXT("_LoadFlags");

	if (UIntProperty* IntProperty = FindField<UIntProperty>(InClass, *FlagMemberName))
	{
		if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(InObject))
		{
			if (LoadFlags == ECsLoadFlags::All)
				return true;
			if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, ECsLoadFlags::All))
				return true;
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
		const FString InternalMemberName = MemberName + TEXT("_Internal");

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (UBlueprintGeneratedClass** Internal = InternalProperty->ContainerPtrToValuePtr<UBlueprintGeneratedClass*>(InObject))
				LoadTAssetPtr_Blueprint(ObjectName + MemberName, Member, *Internal);
		}
	}
}

void UCsCommon_Load::LoadAssetObjectProperty_Blueprint(UAssetObjectProperty* &AssetObjectProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TAssetPtr<UBlueprint>* Member = AssetObjectProperty->ContainerPtrToValuePtr<TAssetPtr<UBlueprint>>(InObject))
	{
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
			return;

		const FString InternalMemberName = MemberName + TEXT("_Internal");

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (UBlueprintGeneratedClass** Internal = InternalProperty->ContainerPtrToValuePtr<UBlueprintGeneratedClass*>(InObject))
				LoadTAssetPtr_Blueprint(ObjectName + MemberName, Member, *Internal);
		}
	}
}

void UCsCommon_Load::LoadArrayAssetObjectProperty_Blueprint(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UClass* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TArray<TAssetPtr<UBlueprint>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UBlueprint>>>(InObject))
	{
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
			return;

		const FString InternalMemberName = MemberName + TEXT("_Internal");

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (TArray<UBlueprintGeneratedClass*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<UBlueprintGeneratedClass*>>(InObject))
				LoadTArrayTAssetPtr_Blueprint(ObjectName + MemberName, Member, *Internal);
		}
	}
}

void UCsCommon_Load::LoadArrayAssetObjectProperty_Blueprint(UArrayProperty* &ArrayProperty, const FString &ObjectName, void* InObject, UScriptStruct* const &InClass, const FString &MemberName, const ECsLoadFlags &LoadFlags)
{
	if (TArray<TAssetPtr<UBlueprint>>* Member = ArrayProperty->ContainerPtrToValuePtr<TArray<TAssetPtr<UBlueprint>>>(InObject))
	{
		if (!CanLoad(InObject, InClass, MemberName, LoadFlags))
			return;

		const FString InternalMemberName = MemberName + TEXT("_Internal");

		if (UProperty* InternalProperty = FindField<UProperty>(InClass, *InternalMemberName))
		{
			if (TArray<UBlueprintGeneratedClass*>* Internal = InternalProperty->ContainerPtrToValuePtr<TArray<UBlueprintGeneratedClass*>>(InObject))
				LoadTArrayTAssetPtr_Blueprint(ObjectName + MemberName, Member, *Internal);
		}
	}
}

void UCsCommon_Load::LoadStructWithTAssetPtrs(const FString &ObjectName, void* InStruct, UScriptStruct* const &InScriptStruct, const ECsLoadFlags &LoadFlags, TCsLoadStructWithTAssetPtrs_Internal Internal /*=nullptr*/)
{
	for (TFieldIterator<UProperty> It(InScriptStruct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName		 = Property->GetName();
		const FString InternalMemberName = Property->GetName() + TEXT("_Internal");

		// TAssetSubclassOf
		if (UAssetClassProperty* AssetClassProperty = Cast<UAssetClassProperty>(*It))
		{
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
			{ LoadAssetObjectProperty<UStaticMesh>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("StaticMesh"), TEXT("Static Mesh"), LoadFlags); continue; }
			// USkeletalMesh
			if (AssetObjectProperty->PropertyClass == USkeletalMesh::StaticClass())
			{ LoadAssetObjectProperty<USkeletalMesh>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("SkeletalMesh"), TEXT("Skeletal Mesh"), LoadFlags); continue; }
			// UMaterialInstance
			if (AssetObjectProperty->PropertyClass == UMaterialInstance::StaticClass())
			{ LoadAssetObjectProperty<UMaterialInstance>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("MaterialInstance"), TEXT("MaterialInstance"), LoadFlags); continue; }
			// UMaterialInstanceConstant
			if (AssetObjectProperty->PropertyClass == UMaterialInstanceConstant::StaticClass())
			{
				if (AssetObjectProperty->ArrayDim == 1)
				{ LoadAssetObjectProperty<UMaterialInstanceConstant>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("MaterialInstanceConstant"), TEXT("MaterialInstanceConstant"), LoadFlags); continue; }
				if (AssetObjectProperty->ArrayDim == ECS_INTERACTIVE_STATE_MAX)
				{ LoadFixedArrayAssetObjectProperty_EnumSize<UMaterialInstanceConstant, ECsInteractiveState::Type, ECS_INTERACTIVE_STATE_MAX>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("MaterialInstanceConstant"), TEXT("MaterialInstanceConstant"), LoadFlags, &ECsInteractiveState::ToString); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// UPhysicalMaterial
			if (AssetObjectProperty->PropertyClass == UPhysicalMaterial::StaticClass())
			{ LoadAssetObjectProperty<UPhysicalMaterial>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("PhysicalMaterial"), TEXT("Physical Material"), LoadFlags); continue; }
			// UPhysicsAsset
			if (AssetObjectProperty->PropertyClass == UPhysicsAsset::StaticClass())
			{ LoadAssetObjectProperty<UPhysicsAsset>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("PhysicsAsset"), TEXT("Physics Asset"), LoadFlags); continue; }
			// UAnimSequence
			if (AssetObjectProperty->PropertyClass == UAnimSequence::StaticClass())
			{ LoadAssetObjectProperty<UAnimSequence>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("AnimSequence"), TEXT("Anim Sequence"), LoadFlags); continue; }
			// UAnimMontage
			if (AssetObjectProperty->PropertyClass == UAnimMontage::StaticClass())
			{ LoadAssetObjectProperty<UAnimMontage>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("AnimMontage"), TEXT("Anim Montage"), LoadFlags); continue; }
			// UBlendSpace
			if (AssetObjectProperty->PropertyClass == UBlendSpace::StaticClass())
			{ LoadAssetObjectProperty<UBlendSpace>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("BlendSpace"), TEXT("Blend Space"), LoadFlags); continue; }
			// UAnimBlueprint
			if (AssetObjectProperty->PropertyClass == UAnimBlueprint::StaticClass())
			{ LoadAssetObjectProperty_AnimBlueprint(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, LoadFlags); continue; }
			// USoundCue
			if (AssetObjectProperty->PropertyClass == USoundCue::StaticClass())
			{ LoadAssetObjectProperty<USoundCue>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("SoundCue"), TEXT("Sound Cue"), LoadFlags); continue; }
			// UParticleSystem
			if (AssetObjectProperty->PropertyClass == UParticleSystem::StaticClass())
			{ LoadAssetObjectProperty<UParticleSystem>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("ParticleSystem"), TEXT("Particle System"), LoadFlags); continue; }
			// UCurveFloat
			if (AssetObjectProperty->PropertyClass == UCurveFloat::StaticClass())
			{ LoadAssetObjectProperty<UCurveFloat>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("CurveFloat"), TEXT("Curve Float"), LoadFlags); continue; }
			// UCurveVector
			if (AssetObjectProperty->PropertyClass == UCurveVector::StaticClass())
			{ LoadAssetObjectProperty<UCurveVector>(AssetObjectProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("CurveVector"), TEXT("Curve Vector"), LoadFlags); continue; }
			// UBlueprint
			if (AssetObjectProperty->PropertyClass == UBlueprint::StaticClass())
			{ 
				if (AssetObjectProperty->ArrayDim == 1)
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

			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ LoadMemberStructProperty<FCsAnimSequence>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsFpsAnimSequence
			if (StructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
			{ LoadMemberStructProperty<FCsFpsAnimSequence>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ LoadMemberStructProperty<FCsAnimMontage>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsFpsAnimMontage
			if (StructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ LoadMemberStructProperty<FCsFpsAnimMontage>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
				
				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
				continue;
			}
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ LoadMemberStructProperty<FCsBlendSpace>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsFpsBlendSpace
			if (StructProperty->Struct == FCsFpsBlendSpace::StaticStruct())
			{ LoadMemberStructProperty<FCsFpsBlendSpace>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{ LoadMemberStructProperty<FCsTArrayAnimMontage>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ LoadMemberStructProperty<FCsAnimBlueprint>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsFpsAnimBlueprint
			if (StructProperty->Struct == FCsFpsAnimBlueprint::StaticStruct())
			{ LoadMemberStructProperty<FCsFpsAnimBlueprint>(StructProperty, InStruct, StructName, LoadFlags, Internal); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
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
				if (StructProperty->ArrayDim == 1)
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
				if (StructProperty->ArrayDim == 1)
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
				if (StructProperty->ArrayDim == 1)
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
				// AMboData_Weapon
				//if (InnerAssetClassProperty->PropertyClass == AMboData_Weapon::StaticClass() || InnerAssetClassProperty->MetaClass == AMboData_Weapon::StaticClass())
				//{ LoadArrayAssetClassProperty<AMboData_Weapon>(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("MboData_Weapon")); continue; }
				// AMboData_Projectile
				//if (InnerAssetClassProperty->PropertyClass == AMboData_Projectile::StaticClass() || InnerAssetClassProperty->MetaClass == AMboData_Projectile::StaticClass())
				//{ LoadArrayAssetClassProperty<AMboData_Projectile>(ArrayProperty, ObjectName, InStruct, InScriptStruct, MemberName, TEXT("MboData_Projectile")); continue; }
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

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InStruct, InScriptStruct, LoadFlags))
						continue;
				}
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

		const FString MemberName		 = Property->GetName();
		const FString InternalMemberName = Property->GetName() + TEXT("_Internal");

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
				if (AssetObjectProperty->ArrayDim == 1)
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
			{ LoadMemberStructProperty<FCsStaticMesh>(StructProperty, InObject, StructName, LoadFlags); continue; }
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
				if (StructProperty->ArrayDim == 1)
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
			// FCsCurveFloat
			if (StructProperty->Struct == FCsCurveFloat::StaticStruct())
			{ LoadMemberStructProperty<FCsCurveFloat>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsCurveVector
			if (StructProperty->Struct == FCsCurveVector::StaticStruct())
			{ LoadMemberStructProperty<FCsCurveVector>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsSoundElement
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
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
				if (StructProperty->ArrayDim == 1)
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
				if (StructProperty->ArrayDim == 1)
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
				if (StructProperty->ArrayDim == 1)
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
			// FCsFpsAnimSequence
			if (StructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
			{ LoadMemberStructProperty<FCsFpsAnimSequence>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{ LoadMemberStructProperty<FCsAnimMontage>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsFpsAnimMontage
			if (StructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
			{ LoadMemberStructProperty<FCsFpsAnimMontage>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsTArrayAnimMontage
			if (StructProperty->Struct == FCsTArrayAnimMontage::StaticStruct())
			{ LoadMemberStructProperty<FCsTArrayAnimMontage>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ LoadMemberStructProperty<FCsAnimBlueprint>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsFpsAnimBlueprint
			if (StructProperty->Struct == FCsFpsAnimBlueprint::StaticStruct())
			{ LoadMemberStructProperty<FCsFpsAnimBlueprint>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ LoadMemberStructProperty<FCsBlendSpace>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsFpsBlendSpace
			if (StructProperty->Struct == FCsFpsBlendSpace::StaticStruct())
			{ LoadMemberStructProperty<FCsFpsBlendSpace>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsBlueprint
			if (StructProperty->Struct == FCsBlueprint::StaticStruct())
			{ LoadMemberStructProperty<FCsBlueprint>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsTArrayBlueprint
			if (StructProperty->Struct == FCsTArrayBlueprint::StaticStruct())
			{ LoadMemberStructProperty<FCsTArrayBlueprint>(StructProperty, InObject, StructName, LoadFlags); continue; }
			// FCsWidgetActorInfo
			if (StructProperty->Struct == FCsWidgetActorInfo::StaticStruct())
			{ LoadMemberStructProperty<FCsWidgetActorInfo>(StructProperty, InObject, StructName, LoadFlags); continue; }

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
				// AShooterWeaponData
				//if (InnerAssetClassProperty->PropertyClass == AShooterWeaponData::StaticClass() || InnerAssetClassProperty->MetaClass == AShooterWeaponData::StaticClass())
				//{ LoadArrayAssetClassProperty<AShooterWeaponData>(ArrayProperty, ObjectName, InObject, InClass, MemberName, TEXT("ShooterWeaponData")); continue; }
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
				// FCsFpsAnimSequence
				if (InnerStructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFpsAnimSequence>(ArrayProperty, InObject, StructName, LoadFlags); continue; }
				// FCsFpsAnimMontage
				if (InnerStructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
				{ LoadMemberArrayStructProperty<FCsFpsAnimMontage>(ArrayProperty, InObject, StructName, LoadFlags); continue; }

				if (Internal)
				{
					if ((*Internal)(Property, ObjectName, InObject, InClass, LoadFlags))
						continue;
				}
				continue;
			}
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
				if (StructProperty->ArrayDim == 1)
				{ UnLoadMemberStructProperty<FCsSoundElement>(StructProperty, InStruct); continue; }
				continue;
			}
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ UnLoadMemberStructProperty<FCsFpsSoundElement>(StructProperty, InStruct); continue; }
				continue;
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ UnLoadMemberStructProperty<FCsFxElement>(StructProperty, InStruct); continue; }
				continue;
			}
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ UnLoadMemberStructProperty<FCsFpsFxElement>(StructProperty, InStruct); continue; }
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ UnLoadMemberStructProperty<FCsAnimSequence>(StructProperty, InStruct); continue; }
			// FCsFpsAnimSequence
			if (StructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpsAnimSequence>(StructProperty, InStruct); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{ UnLoadMemberStructProperty<FCsAnimMontage>(StructProperty, InStruct); continue; }
			// FCsFpsAnimMontage
			if (StructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpsAnimMontage>(StructProperty, InStruct); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ UnLoadMemberStructProperty<FCsAnimBlueprint>(StructProperty, InStruct); continue; }
			// FCsFpsAnimBlueprint
			if (StructProperty->Struct == FCsFpsAnimBlueprint::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpsAnimBlueprint>(StructProperty, InStruct); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ UnLoadMemberStructProperty<FCsBlendSpace>(StructProperty, InStruct); continue; }
			// FCsFpsBlendSpace
			if (StructProperty->Struct == FCsFpsBlendSpace::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpsBlendSpace>(StructProperty, InStruct); continue; }
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
				// FCsFpsAnimMontage
				if (InnerStructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsFpsAnimMontage>(ArrayProperty, InStruct); continue; }
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
				if (StructProperty->ArrayDim == 1)
				{ UnLoadMemberStructProperty<FCsSoundElement>(StructProperty, InObject); continue; }
				continue;
			}
			// FCsFpsSoundElement
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ UnLoadMemberStructProperty<FCsFpsSoundElement>(StructProperty, InObject); continue; }
				continue;
			}
			// FCsFxElement
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ UnLoadMemberStructProperty<FCsFxElement>(StructProperty, InObject); continue; }
				continue;
			}
			// FCsFpsFxElement
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
				{ UnLoadMemberStructProperty<FCsFpsFxElement>(StructProperty, InObject); continue; }
				continue;
			}
			// FCsAnimSequence
			if (StructProperty->Struct == FCsAnimSequence::StaticStruct())
			{ UnLoadMemberStructProperty<FCsAnimSequence>(StructProperty, InObject); continue; }
			// FCsFpsAnimSequence
			if (StructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpsAnimSequence>(StructProperty, InObject); continue; }
			// FCsAnimMontage
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{ UnLoadMemberStructProperty<FCsAnimMontage>(StructProperty, InObject); continue; }
			// FCsFpsAnimMontage
			if (StructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpsAnimMontage>(StructProperty, InObject); continue; }
			// FCsAnimBlueprint
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
			{ UnLoadMemberStructProperty<FCsAnimBlueprint>(StructProperty, InObject); continue; }
			// FCsFpsAnimBlueprint
			if (StructProperty->Struct == FCsFpsAnimBlueprint::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpsAnimBlueprint>(StructProperty, InObject); continue; }
			// FCsBlendSpace
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
			{ UnLoadMemberStructProperty<FCsBlendSpace>(StructProperty, InObject); continue; }
			// FCsFpsBlendSpace
			if (StructProperty->Struct == FCsFpsBlendSpace::StaticStruct())
			{ UnLoadMemberStructProperty<FCsFpsBlendSpace>(StructProperty, InObject); continue; }
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
				// FCsFpsAnimMontage
				if (InnerStructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
				{ UnLoadMemberArrayStructProperty<FCsFpsAnimMontage>(ArrayProperty, InObject); continue; }
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
			// FCsFpsAnimSequence
			else
			if (StructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpsAnimSequence>(StructProperty, InStruct, StructName);
			// FCsAnimMontage
			else
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					Pass &= IsLoadedMemberStructProperty<FCsAnimMontage>(StructProperty, InStruct, StructName);
			}
			// FCsFpsAnimMontage
			else
			if (StructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpsAnimMontage>(StructProperty, InStruct, StructName);
			// FCsBlendSpace
			else
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsBlendSpace>(StructProperty, InStruct, StructName);
			// FCsFpsBlendSpace
			else
			if (StructProperty->Struct == FCsFpsBlendSpace::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpsBlendSpace>(StructProperty, InStruct, StructName);
			// FCsAnimBlueprint
			else
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsAnimBlueprint>(StructProperty, InStruct, StructName);
			// FCsFpsAnimBlueprint
			else
			if (StructProperty->Struct == FCsFpsAnimBlueprint::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpsAnimBlueprint>(StructProperty, InStruct, StructName);
			// FCsSoundElement
			else
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					Pass &= IsLoadedMemberStructProperty<FCsSoundElement>(StructProperty, InStruct, StructName);
			}
			// FCsFpsSoundElement
			else
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					Pass &= IsLoadedMemberStructProperty<FCsFpsSoundElement>(StructProperty, InStruct, StructName);
			}
			// FCsFxElement
			else
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					Pass &= IsLoadedMemberStructProperty<FCsFxElement>(StructProperty, InStruct, StructName);
			}
			// FCsFpsFxElement
			else
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
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
			// FCsFpsAnimSequence
			else
			if (StructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpsAnimSequence>(StructProperty, InObject, StructName);
			// FCsAnimMontage
			else
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					Pass &= IsLoadedMemberStructProperty<FCsAnimMontage>(StructProperty, InObject, StructName);
			}
			// FCsFpsAnimMontage
			else
			if (StructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpsAnimMontage>(StructProperty, InObject, StructName);
			// FCsBlendSpace
			else
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsBlendSpace>(StructProperty, InObject, StructName);
			// FCsFpsBlendSpace
			else
			if (StructProperty->Struct == FCsFpsBlendSpace::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpsBlendSpace>(StructProperty, InObject, StructName);
			// FCsAnimBlueprint
			else
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsAnimBlueprint>(StructProperty, InObject, StructName);
			// FCsFpsAnimBlueprint
			else
			if (StructProperty->Struct == FCsFpsAnimBlueprint::StaticStruct())
				Pass &= IsLoadedMemberStructProperty<FCsFpsAnimBlueprint>(StructProperty, InObject, StructName);
			// FCsSoundElement
			else
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					Pass &= IsLoadedMemberStructProperty<FCsSoundElement>(StructProperty, InObject, StructName);
			}
			// FCsFpsSoundElement
			else
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					Pass &= IsLoadedMemberStructProperty<FCsFpsSoundElement>(StructProperty, InObject, StructName);
			}
			// FCsFxElement
			else
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					Pass &= IsLoadedMemberStructProperty<FCsFxElement>(StructProperty, InObject, StructName);
			}
			// FCsFpsFxElement
			else
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
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

	for (int32 I = 0; I < Count; I++)
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

#pragma endregion Loading

// Members
#pragma region

#if WITH_EDITOR

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

			for (int32 I = 0; I < Max; I++)
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
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
				return SetMemberProperty<FVector>(InObject, Property, MemberValue);
			// FRotator
			else
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
				return SetMemberProperty<FRotator>(InObject, Property, MemberValue);
			// FColor
			else
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
				return SetMemberProperty<FColor>(InObject, Property, MemberValue);
		}
		// bool
		else
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
			return SetMemberProperty<bool>(InObject, Property, MemberValue);
		// Byte / Enum
		else
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			if (ByteProperty->IsEnum())
			{
				// ECharacterClass
				//if (ByteProperty->Enum->CppType.Contains(TEXT("ECharacterClass")))
				//	return SetMemberProperty<TEnumAsByte<ECharacterClass::Type>>(InObject, Property, MemberValue);
			}
		}
		// int32
		else
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			return SetMemberProperty<int32>(InObject, Property, MemberValue);
		// float
		else
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
			return SetMemberProperty<int32>(InObject, Property, MemberValue);
		// FString
		else
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
			return SetMemberProperty<FString>(InObject, Property, MemberValue);
		// FName
		else
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
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
				return SetMemberProperty<FVector>(InStruct, Property, MemberValue);
			// FRotator
			else
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
				return SetMemberProperty<FRotator>(InStruct, Property, MemberValue);
			// FColor
			else
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
				return SetMemberProperty<FColor>(InStruct, Property, MemberValue);
		}
		// bool
		else
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
		}
		// int32
		else
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			return SetMemberProperty<int32>(InStruct, Property, MemberValue);
		// float
		else
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
			return SetMemberProperty<int32>(InStruct, Property, MemberValue);
		// FString
		else
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
			return SetMemberProperty<FString>(InStruct, Property, MemberValue);
		// FName
		else
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
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
				return SetMemberProperty<FVector>(InObject, Property, MemberValue);
			// FRotator
			else
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
				return SetMemberProperty<FRotator>(InObject, Property, MemberValue);
			// FColor
			else
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
				return SetMemberProperty<FColor>(InObject, Property, MemberValue);
		}
		// bool
		else
		if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(*It))
			return SetMemberProperty<bool>(InObject, Property, MemberValue);
		// Byte / Enum
		else
		if (UByteProperty* ByteProperty = Cast<UByteProperty>(*It))
		{
			if (ByteProperty->IsEnum())
			{
				// ECharacterClass
				//if (ByteProperty->Enum->CppType.Contains(TEXT("ECharacterClass")))
				//	return SetMemberProperty<TEnumAsByte<ECharacterClass::Type>>(InObject, Property, MemberValue);
			}
		}
		// int32
		else
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			return SetMemberProperty<int32>(InObject, Property, MemberValue);
		// float
		else
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
			return SetMemberProperty<int32>(InObject, Property, MemberValue);
		// FString
		else
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
			return SetMemberProperty<FString>(InObject, Property, MemberValue);
		// FName
		else
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
			// FVector
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
				return SetMemberProperty<FVector>(InStruct, Property, MemberValue);
			// FRotator
			else
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
				return SetMemberProperty<FRotator>(InStruct, Property, MemberValue);
			// FColor
			else
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
				return SetMemberProperty<FColor>(InStruct, Property, MemberValue);
		}
		// bool
		else
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
		}
		// int32
		else
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			return SetMemberProperty<int32>(InStruct, Property, MemberValue);
		// float
		else
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
			return SetMemberProperty<int32>(InStruct, Property, MemberValue);
		// FString
		else
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
			return SetMemberProperty<FString>(InStruct, Property, MemberValue);
		// FName
		else
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
			// FCsFpsAnimSequence
			else
			if (StructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
				SetMemberProperty<FCsFpsAnimSequence>(ToObject, Property, MemberValues[Index]);
			// FCsAnimMontage
			else
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					SetMemberProperty<FCsAnimMontage>(ToObject, Property, MemberValues[Index]);
			}
			// FCsFpsAnimMontage
			else
			if (StructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
				SetMemberProperty<FCsFpsAnimMontage>(ToObject, Property, MemberValues[Index]);
			// FCsBlendSpace
			else
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
				SetMemberProperty<FCsBlendSpace>(ToObject, Property, MemberValues[Index]);
			// FCsFpsBlendSpace
			else
			if (StructProperty->Struct == FCsFpsBlendSpace::StaticStruct())
				SetMemberProperty<FCsFpsBlendSpace>(ToObject, Property, MemberValues[Index]);
			// FCsAnimBlueprint
			else
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
				SetMemberProperty<FCsAnimBlueprint>(ToObject, Property, MemberValues[Index]);
			// FCsFpsAnimBlueprint
			else
			if (StructProperty->Struct == FCsFpsAnimBlueprint::StaticStruct())
				SetMemberProperty<FCsFpsAnimBlueprint>(ToObject, Property, MemberValues[Index]);
			// FCsSoundElement
			else
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					SetMemberProperty<FCsSoundElement>(ToObject, Property, MemberValues[Index]);
			}
			// FCsFpsSoundElement
			else
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					SetMemberProperty<FCsFpsSoundElement>(ToObject, Property, MemberValues[Index]);
			}
			// FCsFxElement
			else
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					SetMemberProperty<FCsFxElement>(ToObject, Property, MemberValues[Index]);
			}
			// FCsFpsFxElement
			else
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
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
			else
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
				return EMemberType::FRotator;
			// FColor
			else
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
				return EMemberType::FColor;
		}
		// bool
		else
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
		}
		// int32
		else
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			return EMemberType::Int32;
		// float
		else
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
			return EMemberType::Float;
		// FString
		else
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
			return EMemberType::FString;
		// FName
		else
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
			else
			if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
				return EMemberType::FRotator;
			// FColor
			else
			if (StructProperty->Struct == TBaseStructure<FColor>::Get())
				return EMemberType::FColor;
		}
		// bool
		else
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
		}
		// int32
		else
		if (UIntProperty* IntProperty = Cast<UIntProperty>(*It))
			return EMemberType::Int32;
		// float
		else
		if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(*It))
			return EMemberType::Float;
		// FString
		else
		if (UStrProperty* StrProperty = Cast<UStrProperty>(*It))
			return EMemberType::FString;
		// FName
		else
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
			// FCsFpsAnimSequence
			if (StructProperty->Struct == FCsFpsAnimSequence::StaticStruct())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFpsAnimSequence>(InObject));
			// FCsAnimMontage
			else
			if (StructProperty->Struct == FCsAnimMontage::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsAnimMontage>(InObject));
			}
			// FCsFpsAnimMontage
			else
			if (StructProperty->Struct == FCsFpsAnimMontage::StaticStruct())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFpsAnimMontage>(InObject));
			// FCsBlendSpace
			else
			if (StructProperty->Struct == FCsBlendSpace::StaticStruct())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsBlendSpace>(InObject));
			// FCsFpsBlendSpace
			else
			if (StructProperty->Struct == FCsFpsBlendSpace::StaticStruct())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFpsBlendSpace>(InObject));
			// FCsAnimBlueprint
			else
			if (StructProperty->Struct == FCsAnimBlueprint::StaticStruct())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsAnimBlueprint>(InObject));
			// FCsFpsAnimBlueprint
			else
			if (StructProperty->Struct == FCsFpsAnimBlueprint::StaticStruct())
				OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFpsAnimBlueprint>(InObject));
			// FCsSoundElement
			else
			if (StructProperty->Struct == FCsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsSoundElement>(InObject));
			}
			// FCsFpsSoundElement
			else
			if (StructProperty->Struct == FCsFpsSoundElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFpsSoundElement>(InObject));
			}
			// FCsFxElement
			else
			if (StructProperty->Struct == FCsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
					OutMemberValues.Add((void*)Property->ContainerPtrToValuePtr<FCsFxElement>(InObject));
			}
			// FCsFpsFxElement
			else
			if (StructProperty->Struct == FCsFpsFxElement::StaticStruct())
			{
				if (StructProperty->ArrayDim == 1)
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
				// FVector
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