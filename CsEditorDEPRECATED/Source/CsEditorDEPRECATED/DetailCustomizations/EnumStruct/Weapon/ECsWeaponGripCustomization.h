// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "DetailCustomizations/EnumStruct/ECsEnumStructCustomization.h"

/**
* Customizes a FECsWeaponGrip property to use a dropdown
*/
class CSEDITORDEPRECATED_API FECsWeaponGripCustomization : public FECsEnumStructCustomization
{
private:
	typedef FECsEnumStructCustomization Super;

public:

	FECsWeaponGripCustomization();

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual void SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle) override;
	virtual void SetEnumWithDisplayName(const FString& DisplayName) override;
};