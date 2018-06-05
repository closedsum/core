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
#include "DetailCustomizations/EnumStruct/ECsInputActionCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsGameEventCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsSurfaceTypeCustomization.h"
	// Weapon
#include "DetailCustomizations/EnumStruct/ECsWeaponStateCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponSlotCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponFireModeCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponGripCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponAnimCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponBlendSpaceCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponAnimBlueprintCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponSoundCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponOwnerCustomization.h"
	// Process
#include "DetailCustomizations/EnumStruct/ECsProcessCustomization.h"
	// Blockchain
#include "DetailCustomizations/EnumStruct/ECsBlockchainCommandCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsBlockchainContractCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsBlockchainContractFunctionCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsEthereumJavascriptCustomization.h"

DECLARE_LOG_CATEGORY_CLASS(LogCsEditor, Log, All);

void UCsEdEngine::Init(IEngineLoop* InEngineLoop)
{
	Super::Init(InEngineLoop);

	// Custom properties
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

		// Input
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsInputAction", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsInputActionCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsGameEvent", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsGameEventCustomization::MakeInstance));
		// SurfaceType
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsSurfaceType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsSurfaceTypeCustomization::MakeInstance));
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
		const TCsAssetType AssetType    = (*StringToAssetType)(AssetTypeAsString);

		MarkDatasDirty(AssetType);
		return true;
	}
	return false;
}

void UCsEdEngine::MarkDatasDirty(const TCsAssetType &AssetType)
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