// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Visual/CsData_Skin_VisualImplSlice.h"

// Types
#include "CsMacro_Misc.h"
#include "CsMacro_Interface.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
#include "Containers/CsDeconstructInterfaceSliceMap.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsData_Skin_VisualImplSlice)

using SliceType = NCsSkin::NData::NVisual::FImplSlice;

void FCsData_Skin_VisualImplSlice::CopyToSlice(SliceType* Slice)
{
}

void FCsData_Skin_VisualImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
}

SliceType* FCsData_Skin_VisualImplSlice::AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

	using InterfaceType = NCsSkin::NData::NVisual::IVisual;

	if (InterfaceMap->Implements(InterfaceType::Name))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InterfaceMap already contains a reference an interface of type: %s."), *Context, *(InterfaceType::Name.ToString())));
		return nullptr;
	}

	CS_IS_PTR_NULL_RET_NULL(DeconstructInterfaceSliceMap)

	SliceType* Slice = new SliceType();

	// Add slice as type SkinType
	InterfaceMap->Add<InterfaceType>(InterfaceType::Name, static_cast<InterfaceType*>(Slice));
	// Set the InterfaceMap of Data to the "root" InterfaceMap
	Slice->SetInterfaceMap(InterfaceMap);

	DeconstructInterfaceSliceMap->AddSlice(SliceType::Name, Slice);
	DeconstructInterfaceSliceMap->AddDeconstructSliceImpl(SliceType::Name, &SliceType::Deconstruct);

	CopyToSliceAsValue(Slice);
	return Slice;
}

bool FCsData_Skin_VisualImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	return true;
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsSkin::NData::NVisual::FImplSlice);

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NImplSlice
			{
				namespace NCached
				{
					namespace Name
					{
						const FName VisualSkinSlice = FName("VisualSkinSlice");
					}
				}
			}

			/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				using namespace NCsSkin::NData::NVisual::NImplSlice::NCached;

				CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

				using InterfaceType = NCsSkin::NData::NVisual::IVisual;

				if (InterfaceMap->Implements(InterfaceType::Name))
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InterfaceMap already contains a reference an interface of type: %s."), *Context, *(InterfaceType::Name.ToString())));
					return nullptr;
				}

				CS_IS_PTR_NULL_RET_NULL(DeconstructInterfaceSliceMap)

				CS_IS_PTR_NULL_RET_NULL(Object)

				// Check for properties matching interface: SkinDataType (NCsSkin::NData::NVisual::IVisual)

				FImplSlice* Slice = nullptr;
				bool Success	  = false;

				// Try FCsData_Skin_VisualImplSlice
				using StructSliceType = FCsData_Skin_VisualImplSlice;

				if (StructSliceType* SliceAsStruct = CsPropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::VisualSkinSlice, nullptr))
				{
					Slice = new FImplSlice();

					// Add slice as type SkinType
					InterfaceMap->Add<InterfaceType>(InterfaceType::Name, static_cast<InterfaceType*>(Slice));
					// Set the InterfaceMap of Data to the "root" InterfaceMap
					Slice->SetInterfaceMap(InterfaceMap);

					DeconstructInterfaceSliceMap->AddSlice(FImplSlice::Name, Slice);
					DeconstructInterfaceSliceMap->AddDeconstructSliceImpl(FImplSlice::Name, &FImplSlice::Deconstruct);

					SliceAsStruct->CopyToSlice(Slice);
					Success = true;
				}

				if (!Success)
				{
					if (Log)
					{
						Log(FString::Printf(TEXT("%s: Failed to find any properties from %s for interface: SkinDataType (NCsSkin::NData::NVisual::IVisual)."), *Context, *(CsObjectLibrary::PrintObjectAndClass(Object))));
						Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualImplSlice with name: VisualSkinSlice."), *Context));
					}
				}
				return Slice;
			}

			bool FImplSlice::IsValidChecked(const FString& Context) const
			{
				return true;
			}

			bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCLog::Warning*/) const
			{
				return true;
			}
		}
	}
}