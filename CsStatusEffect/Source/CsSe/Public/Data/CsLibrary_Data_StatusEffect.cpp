// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_Data_StatusEffect.h"

namespace NCsStatusEffect
{
	namespace NData
	{
	#define DataType NCsStatusEffect::NData::IData

		FString FLibrary::PrintDataAndClass(DataType* Data)
		{
			if (UObject* O = Data->_getUObject())
				return FString::Printf(TEXT("Data: %s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
			return FString::Printf(TEXT("INVALID (Non-UObject)"));
		}

	#undef DataType
	}
}