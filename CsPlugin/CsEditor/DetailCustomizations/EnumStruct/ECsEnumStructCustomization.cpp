// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsEnumStructCustomization.h"
#include "CsEditor.h"

#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "DetailLayoutBuilder.h"
// Type
#include "Types/CsTypes_Primitive.h"
// AssetRegistry
#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
// Blueprint
#include "Classes/Factories/BlueprintFactory.h"

#include "Classes/Engine/UserDefinedEnum.h"

#include "Types/Enum/CsEnumStructUserDefinedEnumMap.h"

#define LOCTEXT_NAMESPACE "ECsEnumStructCustomization"


FECsEnumStructCustomization::FECsEnumStructCustomization()
{
}

void FECsEnumStructCustomization::CustomPopulateEnumMap(){}

void FECsEnumStructCustomization::PopulateEnumMapFromUserDefinedEnum()
{
	if (!bPopulateEnumMapFromUserDefinedEnum)
		return;

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
	IAssetRegistry& AssetRegistry			  = AssetRegistryModule.Get();

	const FName ClassName = UCsEnumStructUserDefinedEnumMap::StaticClass()->GetFName();

	TArray<FAssetData> OutAssetData;

	if (AssetRegistry.GetAssetsByClass(ClassName, OutAssetData))
	{
		if (OutAssetData.Num() > CS_SINGLETON)
		{
			UE_LOG(LogCsEditor, Warning, TEXT("FER6EnumStructCustomization::PopulateEnumMapFromUserDefinedEnum (%s): More than ONE class found of type: UCsEnumStructUserDefinedEnumMap. Choosing the FIRST one. There should only be ONE."), *GetEnumStructName());
		}

		FAssetData& Asset = OutAssetData[CS_FIRST];

		UCsEnumStructUserDefinedEnumMap* Map = Cast<UCsEnumStructUserDefinedEnumMap>(Asset.GetAsset());

		if (UUserDefinedEnum* Enum = Map->GetUserDefinedEnum(GetUserDefinedEnumType()))
		{
			const int32 Count = Enum->NumEnums() - 1;

			for (int32 I = 0; I < Count; ++I)
			{
				const FString Name = Enum->GetDisplayNameTextByIndex(I).ToString();

				AddEnumToMap(Name);
			}
		}
		else
		{
			UE_LOG(LogCsEditor, Warning, TEXT("FER6EnumStructCustomization::PopulateEnumMapFromUserDefinedEnum (%s): Failed to find a UserDefinedEnum associated with EnumStruct: %s."), *GetEnumStructName(), *(GetUserDefinedEnumType().Name));
		}
	}
	else
	{
		UE_LOG(LogCsEditor, Warning, TEXT("FER6EnumStructCustomization::PopulateEnumMapFromUserDefinedEnum (%s): No class found of type: UCsEnumStructUserDefinedEnumMap."), *GetEnumStructName());
	}
}

void FECsEnumStructCustomization::AddEnumToMap(const FString& Name)
{

}

const FString& FECsEnumStructCustomization::GetEnumStructName()
{
	return NCsCached::Str::Empty;
}

const FName& FECsEnumStructCustomization::GetEnumStructFName()
{
	return NCsCached::Name::None;
}

const FECsUserDefinedEnum& FECsEnumStructCustomization::GetUserDefinedEnumType()
{
	return EMCsUserDefinedEnum::Get().GetMAX();
}

void FECsEnumStructCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	SetPropertyHandles(StructPropertyHandle);
	
	// Alter DisplayNameList for Properties that are visible and should NOT be edited
	if (PerformDropDownCheck)
	{
		UProperty* Property	= StructPropertyHandle->GetProperty();

		if (Property->HasAnyPropertyFlags(CPF_DisableEditOnTemplate | CPF_DisableEditOnInstance | CPF_EditConst))
		{
			const int32 Count = DisplayNameList.Num();

			FString DisplayName;
			GetDisplayNamePropertyValue(DisplayName);

			for (int32 I = Count - 1; I >= 0; --I)
			{
				if (DisplayName == *DisplayNameList[I].Get())
					continue;
				DisplayNameList.RemoveAt(I);
			}
		}
	}

	TSharedPtr<FString> InitialSelectedDisplayName = GetSelectedDisplayName();

	if (InitialSelectedDisplayName.IsValid())
	{
		SetEnumWithDisplayName(*InitialSelectedDisplayName.Get());
	}

	HeaderRow.NameContent()
	[
		SNew(STextBlock)
		.Text(StructPropertyHandle->GetPropertyDisplayName())
		.Font(IDetailLayoutBuilder::GetDetailFont())
	]
	.ValueContent()
	[
		SAssignNew(DisplayNameComboBox, SComboBox<TSharedPtr<FString>>)
		.OptionsSource(&DisplayNameList)
		.OnGenerateWidget(this, &FECsEnumStructCustomization::OnGenerateWidget)
		.OnSelectionChanged(this, &FECsEnumStructCustomization::OnSelectionChanged)
		.OnComboBoxOpening(this, &FECsEnumStructCustomization::OnComboBoxOpening)
		.InitiallySelectedItem(InitialSelectedDisplayName)
		.IsEnabled(FSlateApplication::Get().GetNormalExecutionAttribute())
		.ContentPadding(FMargin(2.0f, 2.0f))
		.Content()
		[
			SNew(STextBlock)
			.Text(this, &FECsEnumStructCustomization::GetComboBoxContent)
			.Font(IDetailLayoutBuilder::GetDetailFont())
		]
	];
}

void FECsEnumStructCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle){}

void FECsEnumStructCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

TSharedRef<SWidget> FECsEnumStructCustomization::OnGenerateWidget(TSharedPtr<FString> InItem)
{
	return
		SNew(STextBlock)
		.Text(FText::FromString(*InItem))
		.Font(IDetailLayoutBuilder::GetDetailFont());
}

void FECsEnumStructCustomization::OnSelectionChanged(TSharedPtr<FString> DisplayNameItem, ESelectInfo::Type SelectInfo)
{
	if (DisplayNameItem.IsValid())
	{
		SetEnumWithDisplayName(*DisplayNameItem);
	}
}

void FECsEnumStructCustomization::OnComboBoxOpening()
{
	TSharedPtr<FString> SelectedDisplayName = GetSelectedDisplayName();

	if (SelectedDisplayName.IsValid())
	{
		check(DisplayNameComboBox.IsValid());
		DisplayNameComboBox->SetSelectedItem(SelectedDisplayName);
	}
}

TSharedPtr<FString> FECsEnumStructCustomization::GetSelectedDisplayName() const
{
	const int32 Count = DisplayNameList.Num();

	if (Count <= 0)
	{
		return NULL;
	}

	FString DisplayName;
	GetDisplayNamePropertyValue(DisplayName);

	for (int32 I = 0; I < Count; ++I)
	{
		if (DisplayName == *DisplayNameList[I].Get())
		{
			return DisplayNameList[I];
		}
	}
	return DisplayNameList[0];
}

void FECsEnumStructCustomization::SetEnumWithDisplayName(const FString& DisplayName){}

void FECsEnumStructCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	check(DisplayNameHandle.IsValid());
	DisplayNameHandle->GetValue(OutDisplayName);
}

FText FECsEnumStructCustomization::GetComboBoxContent() const
{
	TSharedPtr<FString> SelectedDisplayName = GetSelectedDisplayName();

	if (SelectedDisplayName.IsValid())
	{
		return FText::FromString(*SelectedDisplayName);
	}
	return LOCTEXT("Invalid", "Invalid");
}

#undef LOCTEXT_NAMESPACE
