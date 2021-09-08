// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"
#include "Widgets/Input/SComboBox.h"
#include "Types/Enum/CsUserDefinedEnum.h"

class IDetailGroup;

/**
* Customizes a FECsEnum property to use a dropdown
*/
class CSEDITOR_API FECsEnumStructCustomization : public IPropertyTypeCustomization
{
private:
	typedef FECsEnumStructCustomization Super;

public:

	FECsEnumStructCustomization();

protected:

	void Log(const FString& Str);

	virtual void CustomPopulateEnumMap();

	virtual void PopulateEnumMapFromSettings();

	virtual void AddEnumToMap(const FString& Name);

	virtual const FString& GetEnumStructName();
	virtual const FName& GetEnumStructFName();
	
	virtual const FECsUserDefinedEnum& GetUserDefinedEnumType();

	template<typename EnumMap, typename EnumStruct>
	void Init()
	{
		EnumMap::Get().ClearUserDefinedEnums();

		CustomPopulateEnumMap();
		PopulateEnumMapFromSettings();
		
		const int32& Count = EnumMap::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const EnumStruct& Enum = EnumMap::Get().GetEnumAt(I);

			DisplayNameList.Add(MakeShareable(new FString(Enum.GetDisplayName())));
		}
	}

public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	bool bPerformDropDownCheck;

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

protected:

	virtual void SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle);

	template<typename EnumStruct>
	void SetPropertyHandles_Internal(TSharedRef<IPropertyHandle> StructPropertyHandle)
	{
		// Value
		ValueHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(EnumStruct, Value));
		check(ValueHandle.IsValid());
		// Name_Internal
		NameInternalHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(EnumStruct, Name_Internal));
		check(NameInternalHandle.IsValid());
	}

	TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<FString> InItem);

	void OnSelectionChanged(TSharedPtr<FString> DisplayNameItem, ESelectInfo::Type SelectInfo);
	void OnComboBoxOpening();

	TSharedPtr<FString> GetSelectedDisplayName() const;

	virtual void SetEnumWithDisplayName(const FString& DisplayName);

	template<typename EnumMap, typename EnumStruct>
	void SetEnumWithDisplayName_Internal(const FString& DisplayName)
	{
		check(NameInternalHandle.IsValid());

		FName OldName;
		NameInternalHandle->GetValue(OldName);

		const EnumStruct& Enum = EnumMap::Get().GetEnumByDisplayName(DisplayName);
		const FName& Name	   = Enum.GetFName();

		if (OldName != Name)
		{
			// Value
			check(ValueHandle.IsValid());
			ValueHandle->SetValue(Enum.GetValue());
			// Name_Internal
			check(NameInternalHandle.IsValid());
			NameInternalHandle->SetValue(Enum.GetFName());
		}
		else
		{
			// Value
			check(ValueHandle.IsValid());
			uint8 OutValue;
			ValueHandle->GetValue(OutValue);
			if (OutValue != Enum.GetValue())
				ValueHandle->SetValue(Enum.GetValue());
			// Name_Internal
			check(NameInternalHandle.IsValid());
			FName OutName;
			NameInternalHandle->GetValue(OutName);
			if (OutName != Enum.GetFName())
				NameInternalHandle->SetValue(Enum.GetFName());
		}
	}

	virtual void GetDisplayNamePropertyValue(FString& OutDisplayName) const;

	template<typename EnumMap, typename EnumStruct>
	void GetDisplayNamePropertyValue_Internal(FString& OutDisplayName) const
	{
		check(NameInternalHandle.IsValid());
		
		FName Name;
		NameInternalHandle->GetValue(Name);

		const EnumStruct& Enum = EnumMap::Get().GetSafeEnum(Name);

		OutDisplayName = Enum.GetDisplayName();
	}

	FText GetComboBoxContent() const;

protected:

	TSharedPtr<IPropertyHandle> ValueHandle;
	TSharedPtr<IPropertyHandle> NameInternalHandle;
	TArray<TSharedPtr<FString>> DisplayNameList;
	TSharedPtr<SComboBox<TSharedPtr<FString>>> DisplayNameComboBox;
};
