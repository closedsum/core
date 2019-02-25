// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"
#include "Widgets/Input/SComboBox.h"

class IDetailGroup;

/**
* Customizes a FECsEnum property to use a dropdown
*/
class CSEDITOR_API FECsEnumCustomization : public IPropertyTypeCustomization
{
private:
	typedef FECsEnumCustomization Super;

public:

	FECsEnumCustomization();

protected:

	virtual void CustomPopulateEnumMap();

	bool bPopulateEnumMapFromUserDefinedEnum;
	FName UserDefinedEnumObjectPath;

	void PopulateEnumMapFromUserDefinedEnum();

	virtual void AddEnumToMap(const FString& Name);
	virtual FString GetEnumStructName();
	
	template<typename EnumStruct, typename EnumMap>
	void Init()
	{
		EnumMap::Get().ClearUserDefinedEnums();

		CustomPopulateEnumMap();
		PopulateEnumMapFromUserDefinedEnum();
		
		PerformDropDownCheck = true;

		const int32& Count = EnumMap::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const EnumStruct& Enum = EnumMap::Get().GetEnumAt(I);

			DisplayNameList.Add(MakeShareable(new FString(Enum.DisplayName)));
		}
	}

public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	bool PerformDropDownCheck;

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

protected:

	virtual void SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle);

	template<typename EnumStruct>
	void SetPropertyHandles_Internal(TSharedRef<IPropertyHandle> StructPropertyHandle)
	{
		ValueHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(EnumStruct, Value));
		check(ValueHandle.IsValid());
		NameHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(EnumStruct, Name));
		check(NameHandle.IsValid());
		NameInternalHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(EnumStruct, Name_Internal));
		check(NameInternalHandle.IsValid());
		DisplayNameHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(EnumStruct, DisplayName));
		check(DisplayNameHandle.IsValid());
	}

	TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<FString> InItem);

	void OnSelectionChanged(TSharedPtr<FString> DisplayNameItem, ESelectInfo::Type SelectInfo);
	void OnComboBoxOpening();

	TSharedPtr<FString> GetSelectedDisplayName() const;

	virtual void SetEnumWithDisplayName(const FString& DisplayName);

	template<typename EnumStruct, typename EnumMap>
	void SetEnumWithDisplayName_Internal(const FString& DisplayName)
	{
		check(DisplayNameHandle.IsValid());

		FString OldDisplayName;
		DisplayNameHandle->GetValue(OldDisplayName);

		if (OldDisplayName != DisplayName)
		{
			DisplayNameHandle->SetValue(DisplayName);

			const EnumStruct& Enum = EnumMap::Get().GetEnumByDisplayName(DisplayName);

			check(ValueHandle.IsValid());
			ValueHandle->SetValue(Enum.Value);
			check(NameHandle.IsValid());
			NameHandle->SetValue(Enum.Name);
			check(NameInternalHandle.IsValid());
			NameInternalHandle->SetValue(Enum.Name_Internal);
		}
	}

	void GetDisplayNamePropertyValue(FString& OutDisplayName) const;

	FText GetComboBoxContent() const;

protected:

	TSharedPtr<IPropertyHandle> ValueHandle;
	TSharedPtr<IPropertyHandle> NameHandle;
	TSharedPtr<IPropertyHandle> NameInternalHandle;
	TSharedPtr<IPropertyHandle> DisplayNameHandle;
	TArray<TSharedPtr<FString>> DisplayNameList;
	TSharedPtr<SComboBox<TSharedPtr<FString>>> DisplayNameComboBox;
};
