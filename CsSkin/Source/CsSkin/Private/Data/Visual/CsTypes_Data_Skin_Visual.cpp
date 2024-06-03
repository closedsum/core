// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Visual/CsTypes_Data_Skin_Visual.h"
#include "CsSkin.h"

// Library
#include "Data/CsLibrary_Data.h"
// Data
#include "Data/ICsData.h"
#include "Data/Visual/CsData_Skin_Visual.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Data_Skin_Visual)

// FCsData_Skin_Visual
#pragma region

#define SkinDataType NCsSkin::NData::NVisual::IVisual
SkinDataType* FCsData_Skin_VisualPtr::Load(const FString& Context, const int32& LoadFlags)
{
	TSoftClassPtr<UObject> DataSoftClass = Data;
	const FSoftObjectPath& Path			 = DataSoftClass.ToSoftObjectPath();
	
	if (!Path.IsValid())
	{
		UE_LOG(LogCsSkin, Warning, TEXT("%s: Data is NOT Valid."), *Context);
		return nullptr;
	}

	if (UClass* Class = DataSoftClass.LoadSynchronous())
	{
		UObject* DOb = Class->GetDefaultObject();

		if (ICsData* IData = Cast<ICsData>(DOb))
		{
			IData->Load(LoadFlags);

			typedef NCsData::IData DataType;
			typedef NCsData::FLibrary DataLibrary;

			if (DataType* Interface = IData->_getIData())
			{
				if (SkinDataType* SkinData = DataLibrary::GetSafeInterfaceChecked<SkinDataType>(Context, Interface))
				{
					return SkinData;
				}
				else
				{
					UE_LOG(LogCsSkin, Warning, TEXT("%s: Failed to get SkinDataType (NCsSkin::NData::NVisual::IVisual) from Data: %s."), *Context, *(DOb->GetName()));
				}
			}
			else
			{
				UE_LOG(LogCsSkin, Warning, TEXT("%s: Failed to get DataType (NCsData:IData) from Data: %s."), *Context, *(DOb->GetName()));
			}
		}
		else
		{
			UE_LOG(LogCsSkin, Warning, TEXT("%s: Object: %s with Class: %s @ %s does NOT implement interface: ICsData."), *Context, *(DOb->GetName()), *(Class->GetName()), *(Path.ToString()));
		}
	}
	else
	{
		UE_LOG(LogCsSkin, Warning, TEXT("%s: Failed to load Data @ %s."), *Context, *(Path.ToString()));
	}
	return nullptr;
}
#undef SkinDataType

#pragma endregion FCData_CharacterPtr