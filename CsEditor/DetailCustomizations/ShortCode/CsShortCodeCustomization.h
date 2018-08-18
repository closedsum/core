// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"
#include "Widgets/Input/SComboBox.h"

#include "Types/CsTypes_Load.h"

class IDetailGroup;

/**
* Customizes a FCsData_ShortCode property to use a dropdown
*/
class CSEDITOR_API FCsShortCodeCustomization : public IPropertyTypeCustomization
{
private:
	typedef IPropertyTypeCustomization Super;

public:

	FCsShortCodeCustomization();

protected:

	void Init(const FECsAssetType &AssetType);

public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

protected:

	virtual void SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle);

	template<typename ShortCodeStruct>
	void SetPropertyHandles_Internal(TSharedRef<IPropertyHandle> StructPropertyHandle)
	{
		ShortCodeHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(ShortCodeStruct, ShortCode));
		check(ShortCodeHandle.IsValid());
	}

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