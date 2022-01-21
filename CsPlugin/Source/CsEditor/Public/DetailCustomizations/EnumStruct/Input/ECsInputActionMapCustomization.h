// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "DetailCustomizations/EnumStruct/ECsEnumStructMaskCustomization.h"

/**
* Customizes a FECsInputActionMap property to use a dropdown
*/
class CSEDITOR_API FECsInputActionMapCustomization : public FECsEnumStructMaskCustomization
{
private:
	typedef FECsEnumStructMaskCustomization Super;

public:

	FECsInputActionMapCustomization();

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual void CustomPopulateEnumMap() override;

	virtual void AddEnumToMap(const FString& Name) override;

	virtual const FString& GetEnumStructName() override;
	virtual const FName& GetEnumStructFName() override;

	virtual void SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle) override;
	virtual void SetEnumWithDisplayName(const FString& DisplayName) override;
	virtual void GetDisplayNamePropertyValue(FString& OutDisplayName) const override;
};
