// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "DetailCustomizations/EnumStruct/ECsEnumStructMaskCustomization.h"

/**
* Customizes a FECsTeam property to use a dropdown
*/
class CSEDITOR_API FECsTeamCustomization : public FECsEnumStructMaskCustomization
{
private:
	typedef FECsEnumStructMaskCustomization Super;

public:

	FECsTeamCustomization();

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual void SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle) override;
	virtual void SetEnumWithDisplayName(const FString& DisplayName) override;
	virtual void GetDisplayNamePropertyValue(FString& OutDisplayName) const override;
};