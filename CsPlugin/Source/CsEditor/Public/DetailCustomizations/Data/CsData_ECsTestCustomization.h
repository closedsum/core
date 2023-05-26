// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"

/**
*/
class CSEDITOR_API FCsData_ECsTestCustomization : public IPropertyTypeCustomization
{

public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

protected:

	TSharedPtr<IPropertyHandle> ActionHandle;
	TSharedPtr<IPropertyTypeCustomization> CustomTypeInterface;
	TSharedPtr<FDetailWidgetRow> CustomPropertyWidget;

	TSharedPtr<IPropertyHandle> DataHandle;
	TSharedPtr<STextBlock> DataPathText;

	void OnDataChanged();
	FReply OnSaveClicked();
	FReply OnBrowseClicked();

	/** Property viewing widget */
	TSharedPtr<class IDetailsView> PropertyView;
};