// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_Data.h"

// Managers
#include "Managers/Data/CsManager_Data.h"

namespace NCsData
{
	IData* FLibrary::GetDataChecked(const FString& Context, UObject* WorldContext, const FName& DataName)
	{
		ICsData* UData = UCsManager_Data::Get(WorldContext->GetWorld()->GetGameInstance())->GetDataChecked(Context, DataName);

		IData* Data = UData->_getIData();

		checkf(Data, TEXT("%s: Failed to get data of type: IData from Object: %s with Class: %s."), *Context, *(Data->_getUObject()->GetName()), *(Data->_getUObject()->GetClass()->GetName()));

		return Data;
	}
}