// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Cached.h"
// Property
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"

//CS_FWD_DECLARE_CACHED_FUNCTION_NAME(CsData_ECsWeaponCustomization)

/**
*/
class CSWPEDITOR_API FCsData_ECsWeaponCustomization : public IPropertyTypeCustomization
{
private:

	//CS_USING_CACHED_FUNCTION_NAME(CsData_ECsWeaponCustomization);

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