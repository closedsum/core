// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/Data/CsData_ECsTestCustomization.h"
#include "CsEditor.h"

#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "DetailLayoutBuilder.h"
// AssetRegistry
#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
// Test
#include "Test/CsData_ECsTest.h"
#include "DetailCustomizations/EnumStruct/Input/ECsInputActionCustomization.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Data
#include "Data/CsGetDataRootSet.h"

#define LOCTEXT_NAMESPACE "CsData_ECsTestCustomization"

TSharedRef<IPropertyTypeCustomization> FCsData_ECsTestCustomization::MakeInstance()
{
	return MakeShareable(new FCsData_ECsTestCustomization);
}

void FCsData_ECsTestCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	ActionHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsData_ECsTest, Action));

	CustomTypeInterface  = FECsInputActionCustomization::MakeInstance();
	CustomPropertyWidget = MakeShareable(new FDetailWidgetRow);

	CustomTypeInterface->CustomizeHeader(ActionHandle.ToSharedRef(), CustomPropertyWidget.ToSharedRef().Get(), StructCustomizationUtils);

	HeaderRow.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
	.ValueContent()
		[
			CustomPropertyWidget->ValueContent().Widget
		];
}

void FCsData_ECsTestCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	FPropertyEditorModule& EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs(/*bUpdateFromSelection=*/ false, /*bLockable=*/ false, /*bAllowSearch=*/ false, /*InNameAreaSettings=*/ FDetailsViewArgs::HideNameArea, /*bHideSelectionTip=*/ true);
	PropertyView = EditModule.CreateDetailView(DetailsViewArgs);

	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	UClass* Class					  = Settings->DataRootSet.LoadSynchronous();
	UObject* O						  = Class ? Class->GetDefaultObject<UObject>() : nullptr;
	ICsGetDataRootSet* GetDataRootSet = O ? Cast<ICsGetDataRootSet>(O) : nullptr;
	
	if (GetDataRootSet)
	{
		const FCsDataRootSet& DataRootSet = GetDataRootSet->GetCsDataRootSet();

		if (UDataTable* Datas = DataRootSet.Datas)
		{
			const TMap<FName, uint8*>& RowMap = Datas->GetRowMap();

			for (const TPair<FName, uint8*>& Pair : RowMap)
			{
				const FName& RowName	  = Pair.Key;
				FCsDataEntry_Data* RowPtr = reinterpret_cast<FCsDataEntry_Data*>(Pair.Value);

				UClass* C	 = RowPtr->Data.LoadSynchronous();
				UObject* DOb = C ? C->GetDefaultObject() : nullptr;

				if (DOb)
				{
					PropertyView->SetObject(DOb);

					StructBuilder.AddCustomRow(LOCTEXT("MyStructRow", "MyStruct"))
						[
							PropertyView.ToSharedRef()
						];
					break;
				}
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
