// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"
#include "Widgets/Input/SComboBox.h"
#include "Types/Enum/CsUserDefinedEnum.h"

class IDetailGroup;

/**
* Customizes a FECsEnum property to use a dropdown
*/
class CSEDITOR_API FECsEnumStructMaskCustomization : public IPropertyTypeCustomization
{
private:
	typedef IPropertyTypeCustomization Super;

public:

	FECsEnumStructMaskCustomization();

protected:

	void Log(const FString& Str);

	virtual void CustomPopulateEnumMap();

	virtual void PopulateEnumMapFromSettings();

	virtual void AddPropertyChange();

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
		
		for (const EnumStruct& Enum : EnumMap::Get())
		{
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
		// Mask
		MaskHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(EnumStruct, Mask));
		check(MaskHandle.IsValid());
		// Name_Internal
		NameInternalHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(EnumStruct, Name_Internal));
		check(NameInternalHandle.IsValid());
	}

	TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<FString> InItem);

	void OnSelectionChanged(TSharedPtr<FString> DisplayNameItem, ESelectInfo::Type SelectInfo);
	void OnComboBoxOpening();

	TSharedPtr<FString> GetSelectedDisplayName() const;

	virtual void SetEnumWithDisplayName(const FString& DisplayName);

	template<typename EnumMap, typename EnumStruct, typename ValueType>
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
			// Mask
			check(MaskHandle.IsValid());
			MaskHandle->SetValue(Enum.GetMask());
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
			// Mask
			check(MaskHandle.IsValid());
			ValueType OutMask;
			MaskHandle->GetValue(OutMask);
			if (OutMask != Enum.GetMask())
				MaskHandle->SetValue(Enum.GetMask());
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
		
		int32 Index = EnumMap::Get().Num();

		// uint8
		if (ValueHandle->GetPropertyClass()->IsChildOf(FByteProperty::StaticClass()))
		{
			uint8 Value;
			ValueHandle->GetValue(Value);
			Index = (int32)Value;
		}
		// uint16
		else
		if (ValueHandle->GetPropertyClass()->IsChildOf(FUInt16Property::StaticClass()))
		{
			uint16 Value;
			ValueHandle->GetValue(Value);
			Index = (int32)Value;
		}
		// uint32
		else
		if (ValueHandle->GetPropertyClass()->IsChildOf(FUInt32Property::StaticClass()))
		{
			uint32 Value;
			ValueHandle->GetValue(Value);
			Index = (int32)Value;
		}
		// int32
		else
		if (ValueHandle->GetPropertyClass()->IsChildOf(FIntProperty::StaticClass()))
		{
			ValueHandle->GetValue(Index);
		}

		// If Name is Valid, Get DisplayName
		if (EnumMap::Get().IsValidEnum(Name))
		{
			const EnumStruct& Enum = EnumMap::Get().GetEnum(Name);
			OutDisplayName		   = Enum.GetDisplayName();
		}
		// Else, try Value
		else
		if (Index < EnumMap::Get().Num())
		{
			const EnumStruct& Enum = EnumMap::Get().GetEnumAt(Index);
			OutDisplayName		   = Enum.GetDisplayName();
		}
		// Else, INVALID / NONE
		else
		{
			OutDisplayName = EnumMap::Get().GetNONE().GetDisplayName();
		}
	}

	FText GetComboBoxContent() const;

protected:

	TSharedPtr<IPropertyHandle> ValueHandle;
	TSharedPtr<IPropertyHandle> MaskHandle;
	TSharedPtr<IPropertyHandle> NameInternalHandle;
	TArray<TSharedPtr<FString>> DisplayNameList;
	TSharedPtr<SComboBox<TSharedPtr<FString>>> DisplayNameComboBox;
};
