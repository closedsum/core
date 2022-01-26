// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "DetailCustomizations/EnumStruct/ECsEnumStructCustomization.h"

/**
* Customizes a FECsProjectiveClass property to use a dropdown
*/
class CSBEAMEDITOR_API FECsBeamClassCustomization : public FECsEnumStructCustomization
{
private:
	typedef FECsEnumStructCustomization Super;

public:

	FECsBeamClassCustomization();

protected:

	virtual void CustomPopulateEnumMap() override;

public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual void SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle) override;
	virtual void SetEnumWithDisplayName(const FString& DisplayName) override;
	virtual void GetDisplayNamePropertyValue(FString& OutDisplayName) const override;
};