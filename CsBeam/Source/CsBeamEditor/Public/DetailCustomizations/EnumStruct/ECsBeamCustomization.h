// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "DetailCustomizations/EnumStruct/ECsEnumStructCustomization.h"

/**
* Customizes a FECsProjective property to use a dropdown
*/
class CSBEAMEDITOR_API FECsBeamCustomization : public FECsEnumStructCustomization
{
private:
	typedef FECsEnumStructCustomization Super;

public:

	FECsBeamCustomization();

protected:

	virtual void CustomPopulateEnumMap() override;

public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual void SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle) override;
	virtual void SetEnumWithDisplayName(const FString& DisplayName) override;
	virtual void GetDisplayNamePropertyValue(FString& OutDisplayName) const override;
};