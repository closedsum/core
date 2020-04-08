// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"
#include "Widgets/Input/SComboBox.h"

class IDetailGroup;

/**
* Customizes a FCsData_ShortCode property to use a dropdown
*/
class CSEDITORDEPRECATED_API FCsDataShortCodeCustomization : public IPropertyTypeCustomization
{
private:
	typedef IPropertyTypeCustomization Super;

public:

	FCsDataShortCodeCustomization();

protected:

	void Init();

public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

protected:

	void SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle);

	TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<FString> InItem);

	void OnSelectionChanged(TSharedPtr<FString> DisplayNameItem, ESelectInfo::Type SelectInfo);
	void OnComboBoxOpening();

	TSharedPtr<FString> GetSelectedDisplayName() const;

	void SetShortCodeWithDisplayName(const FString& DisplayName);

	void GetDisplayNamePropertyValue(FName& OutShortCode) const;

	FText GetComboBoxContent() const;

protected:

	TSharedPtr<IPropertyHandle> AssetTypeHandle;
	TSharedPtr<IPropertyHandle> ShortCodeHandle;
	TArray<TSharedPtr<FString>> DisplayNameList;
	TSharedPtr<SComboBox<TSharedPtr<FString>>> DisplayNameComboBox;
};