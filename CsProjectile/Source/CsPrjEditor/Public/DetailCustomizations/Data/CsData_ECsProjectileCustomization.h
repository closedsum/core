// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"

/**
*/
class CSPRJEDITOR_API FCsData_ECsProjectileCustomization : public IPropertyTypeCustomization
{

public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

protected:

	TSharedPtr<IPropertyHandle> ValueHandle;
	TSharedPtr<IPropertyTypeCustomization> ValueTypeInterface;
	TSharedPtr<FDetailWidgetRow> ValuePropertyWidget;

	TSharedPtr<STextBlock> DataTablePathText;
	
	FReply OnDataTableBrowseClicked();

	TSharedPtr<STextBlock> DataPathText;

	UObject* GetDataAssociatedWithValue();
	void OnValueChanged();
	FReply OnDataSaveClicked();
	FReply OnDataBrowseClicked();

	/** Property viewing widget */
	TSharedPtr<class IDetailsView> PropertyView;
};