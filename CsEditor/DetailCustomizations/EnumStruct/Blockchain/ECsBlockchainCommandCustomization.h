// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "DetailCustomizations/EnumStruct/ECsEnumCustomization.h"

/**
* Customizes a FECsBlockchainCommand property to use a dropdown
*/
class CSEDITOR_API FECsBlockchainCommandCustomization : public FECsEnumCustomization
{
private:
	typedef FECsEnumCustomization Super;

public:

	FECsBlockchainCommandCustomization();

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

	virtual void SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle) override;
	virtual void SetEnumWithDisplayName(const FString& DisplayName) override;
};