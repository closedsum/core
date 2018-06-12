// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "CsEdEngine.h"
#include "CsEditor.h"

#include "Common/CsCommon.h"
#include "Common/CsCommon_Asset.h"

// Asset Registry
#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"

#include "Classes/Factories/BlueprintFactory.h"
// Data
#include "Data/CsData.h"

#include "Editor/PropertyEditor/Public/PropertyEditorModule.h"

// DetailCustomizations
	// Asset
#include "DetailCustomizations/EnumStruct/ECsAssetTypeCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsLoadAssetsTypeCustomization.h"
	// Input
#include "DetailCustomizations/EnumStruct/ECsInputActionCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsGameEventCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsSurfaceTypeCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsGestureTypeCustomization.h"
	// Character
#include "DetailCustomizations/EnumStruct/Character/ECsCharacterAnimCustomization.h"
#include "DetailCustomizations/EnumStruct/Character/ECsCharacterAnimBlueprintCustomization.h"
#include "DetailCustomizations/EnumStruct/Character/ECsCharacterBlendSpaceCustomization.h"
	// Weapon
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponStateCustomization.h"
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponSlotCustomization.h"
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponFireModeCustomization.h"
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponGripCustomization.h"
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponAnimCustomization.h"
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponBlendSpaceCustomization.h"
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponAnimBlueprintCustomization.h"
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponSoundCustomization.h"
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponOwnerCustomization.h"
	// Process
#include "DetailCustomizations/EnumStruct/ECsProcessCustomization.h"
	// Blockchain
#include "DetailCustomizations/EnumStruct/Blockchain/ECsBlockchainCommandCustomization.h"
#include "DetailCustomizations/EnumStruct/Blockchain/ECsBlockchainContractCustomization.h"
#include "DetailCustomizations/EnumStruct/Blockchain/ECsBlockchainContractFunctionCustomization.h"
#include "DetailCustomizations/EnumStruct/Blockchain/ECsEthereumJavascriptCustomization.h"
	// Item
#include "DetailCustomizations/EnumStruct/Item/ECsItemTypeCustomization.h"
#include "DetailCustomizations/EnumStruct/Item/ECsItemOwnerCustomization.h"
#include "DetailCustomizations/EnumStruct/Item/ECsItemInteractionCustomization.h"
	// Damage
#include "DetailCustomizations/EnumStruct/Damage/ECsDamageTypeCustomization.h"
#include "DetailCustomizations/EnumStruct/Damage/ECsHitTypeCustomization.h"
	// Interactive
#include "DetailCustomizations/EnumStruct/Interactive/ECsInteractiveTypeCustomization.h"

void UCsEdEngine::Init(IEngineLoop* InEngineLoop)
{
	Super::Init(InEngineLoop);

	// Custom properties
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

		// Asset
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsAssetType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsAssetTypeCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsLoadAssetsType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsLoadAssetsTypeCustomization::MakeInstance));
		// Input
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsInputAction", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsInputActionCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsGameEvent", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsGameEventCustomization::MakeInstance));
		// SurfaceType
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsSurfaceType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsSurfaceTypeCustomization::MakeInstance));
		// GestureType
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsGestureType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsGestureTypeCustomization::MakeInstance));
		// Character
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsCharacterAnim", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsCharacterAnimCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsCharacterAnimBlueprint", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsCharacterAnimBlueprintCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsCharacterBlendSpace", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsCharacterBlendSpaceCustomization::MakeInstance));
		// Weapon
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponState", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponStateCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponSlot", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponSlotCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponFireMode", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponFireModeCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponGrip", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponGripCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponAnim", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponAnimCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponBlendSpace", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponBlendSpaceCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponAnimBlueprint", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponAnimBlueprintCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponSound", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponSoundCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponOwner", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponOwnerCustomization::MakeInstance));
		// Process
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsProcess", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsProcessCustomization::MakeInstance));
		// Blockchain
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsBlockchainCommand", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsBlockchainCommandCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsBlockchainContract", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsBlockchainContractCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsBlockchainContractFunction", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsBlockchainContractFunctionCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsEthereumJavascript", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsEthereumJavascriptCustomization::MakeInstance));
		// Item
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsItemType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsItemTypeCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsItemOwner", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsItemOwnerCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsItemInteraction", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsItemInteractionCustomization::MakeInstance));
		// Damage
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsDamageType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsDamageTypeCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsHitType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsHitTypeCustomization::MakeInstance));
		// Interactive
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsInteractiveType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsInteractiveTypeCustomization::MakeInstance));
	}
}

bool UCsEdEngine::Exec(UWorld* InWorld, const TCHAR* Stream, FOutputDevice& Ar)
{
	if (Super::Exec(InWorld, Stream, Ar))
		return true;

	// Data
	{
		if (Check_MarkDatasDirty(Stream))
			return true;
	}
	return true;
}

// Stream
#pragma region

bool UCsEdEngine::Stream_GetString(const TCHAR*& Str, const FString &StringType, FString &OutString, const FString &Check, const FString &Format)
{
	OutString = UCsCommon::Stream_GetString(Str, false);

	if (OutString == TEXT(""))
	{
		UE_LOG(LogCsEditor, Warning, TEXT("Check_%s: No %s set."), *Check, *StringType);
		UE_LOG(LogCsEditor, Warning, TEXT("Check_%s: The correct format is %s"), *Check, *Format);
		return false;
	}
	return true;
}

#pragma endregion

// Data
#pragma region

bool UCsEdEngine::Check_MarkDatasDirty(const TCHAR* Stream)
{
	const FString Command	 = TEXT("MarkDatasDirty");
	const FString Parameters = TEXT("[assetType=optional]");
	const FString Format	 = Command + TEXT(" ") + Parameters;

	if (FParse::Command(&Stream, *Command))
	{
		// AssetType
		const FString AssetTypeAsString = UCsCommon::Stream_GetString(Stream, false);
		const FECsAssetType AssetType    = EMCsAssetType::Get().GetSafeEnum(AssetTypeAsString);

		MarkDatasDirty(AssetType);
		return true;
	}
	return false;
}

void UCsEdEngine::MarkDatasDirty(const FECsAssetType &AssetType)
{
	TArray<ACsData*> Datas;

	UClass* Class = (*GetAssetTypeStaticClass)(AssetType);

	UCsCommon_Asset::GetBlueprintDefaultObjects<ACsData>(TEXT("bp_"), ECsStringCompare::StartsWith, Datas, Class);

	const int32 Count = Datas.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		ACsData* Data = Datas[I];

		Data->MarkPackageDirty();

		const FString Name = TEXT(".") + Data->GetName();
		FString Path	   = Data->GetPathName();
		Path.RemoveFromEnd(Name);

		UE_LOG(LogCsEditor, Log, TEXT("MarkAllDatasDirty: %s is marked DIRTY."), *Path);
	}
}

#pragma endregion Data