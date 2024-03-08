// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"

/**
*/
class CSDMGEDITOR_API FCsData_DamagePtrCustomization : public IPropertyTypeCustomization
{

public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

protected:

	TSharedPtr<IPropertyHandle> DataHandle;
	TSharedPtr<STextBlock> DataPathText;

	void OnDataChanged();
	FReply OnSaveClicked();
	FReply OnBrowseClicked();

	/** Property viewing widget */
	TSharedPtr<class IDetailsView> PropertyView;
};