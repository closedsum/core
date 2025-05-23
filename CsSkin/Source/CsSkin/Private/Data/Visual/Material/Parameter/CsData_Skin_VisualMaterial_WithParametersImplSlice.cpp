// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Visual/Material/Parameter/CsData_Skin_VisualMaterial_WithParametersImplSlice.h"

// Types
#include "CsMacro_Misc.h"
#include "CsMacro_Interface.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
#include "Containers/CsDeconstructInterfaceSliceMap.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsData_Skin_VisualMaterial_WithParametersImplSlice)

using SliceType = NCsSkin::NData::NVisual::NMaterial::NWithParameters::FImplSlice;

void FCsData_Skin_VisualMaterial_WithParametersImplSlice::CopyToSlice(SliceType* Slice)
{
	//Slice->SetMaterials(Materials.GetPtr());
}

void FCsData_Skin_VisualMaterial_WithParametersImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	//Slice->SetMaterials(Materials.Get());
}

SliceType* FCsData_Skin_VisualMaterial_WithParametersImplSlice::AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) /*=&NCsSkin::FLog::Warning*/) const
{
	CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

	using InterfaceType = NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters;

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

bool FCsData_Skin_VisualMaterial_WithParametersImplSlice::IsValidChecked(const FString& Context) const
{
	for (const FCsMaterialInterface_WithRangeParameters& Mat : Materials)
	{
		CS_IS_VALID_CHECKED(Mat);
	}
	return true;
}

bool FCsData_Skin_VisualMaterial_WithParametersImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsSkin::FLog::Warning*/) const
{
	for (const FCsMaterialInterface_WithRangeParameters& Mat : Materials)
	{
		CS_IS_VALID(Mat)
	}
	return true;
}

void FCsData_Skin_VisualMaterial_WithParametersImplSlice::SetChecked(const FString& Context, UPrimitiveComponent* Component) const
{
	check(IsValidChecked(Context));

	//CsMaterialLibrary::SetChecked(Context, Component, Materials.Get());
}

bool FCsData_Skin_VisualMaterial_WithParametersImplSlice::SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) /*=&NCsSkin::FLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	//return CsMaterialLibrary::SetSafe(Context, Component, Materials.Get(), Log);
	return true;
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsSkin::NData::NVisual::NMaterial::NWithParameters::FImplSlice);

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NMaterial
			{
				namespace NWithParameters
				{
					namespace NImplSlice
					{
						namespace NCached
						{
							namespace Name
							{
								const FName VisualMaterialWithParamsSlice = FName("VisualMaterialWithParamsSlice");

								const FName Materials = FName("Materials");
							}
						}
					}

					/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) /*=&NCsSkin::FLog::Warning*/)
					{
						using namespace NCsSkin::NData::NVisual::NMaterial::NWithParameters::NImplSlice::NCached;

						CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

						using InterfaceType = NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters;

						if (InterfaceMap->Implements(InterfaceType::Name))
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InterfaceMap already contains a reference an interface of type: %s."), *Context, *(InterfaceType::Name.ToString())));
							return nullptr;
						}

						CS_IS_PTR_NULL_RET_NULL(DeconstructInterfaceSliceMap)
						CS_IS_PTR_NULL_RET_NULL(Object)

						// Check for properties matching interface: CsMaterialWithParamsSkinDataType (NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters)

						FImplSlice* Slice = nullptr;
						bool Success	  = false;

						// Try FCsData_Skin_VisualMaterial_WithParametersImplSlice
						using StructSliceType = FCsData_Skin_VisualMaterial_WithParametersImplSlice;

						if (StructSliceType* SliceAsStruct = CsPropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::VisualMaterialWithParamsSlice, nullptr))
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
						// Try individual properties
						else
						{
							TArray<FCsMaterialInterface_WithRangeParameters>* MaterialsPtr = CsPropertyLibrary::GetArrayStructPropertyValuePtr<FCsMaterialInterface_WithRangeParameters>(Context, Object, Object->GetClass(), Name::Materials, nullptr);

							if (MaterialsPtr)
							{
								Slice = new FImplSlice();

								// Add slice as type SkinType
								InterfaceMap->Add<InterfaceType>(InterfaceType::Name, static_cast<InterfaceType*>(Slice));
								// Set the InterfaceMap of Data to the "root" InterfaceMap
								Slice->SetInterfaceMap(InterfaceMap);

								DeconstructInterfaceSliceMap->AddSlice(FImplSlice::Name, Slice);
								DeconstructInterfaceSliceMap->AddDeconstructSliceImpl(FImplSlice::Name, &FImplSlice::Deconstruct);

								//Slice->SetMaterials(MaterialsPtr->GetPtr());
								Success = true;
							}
						}

						if (!Success)
						{
							if (Log)
							{
								Log(FString::Printf(TEXT("%s: Failed to find any properties from %s for interface: CsMaterialWithParamsSkinDataType (NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters)."), *(CsObjectLibrary::PrintObjectAndClass(Object))));
								Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualMaterial_WithParametersImplSlice with name: VisualMaterialWithParamsSlice.")));
								Log(FString::Printf(TEXT("%s: - OR")));
								Log(FString::Printf(TEXT("%s: - Failed to get array struct property of type: TArray<FCsMaterialInterface_WithRangeParameters> with name: Materials.")));
							}
						}
						return Slice;
					}

					bool FImplSlice::IsValidChecked(const FString& Context) const
					{
						//CS_IS_TARRAY_EMPTY_CHECKED(GetMaterials(), UMaterialInterface*)

						//CS_IS_TARRAY_ANY_NULL_CHECKED(GetMaterials(), UMaterialInterface)
						return true;
					}

					bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsSkin::FLog::Warning*/) const
					{
						//CS_IS_TARRAY_EMPTY(GetMaterials(), UMaterialInterface*)

						//CS_IS_TARRAY_ANY_NULL(GetMaterials(), UMaterialInterface)
						return true;
					}

					void FImplSlice::SetChecked(const FString& Context, UPrimitiveComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs) const
					{
						//CsMaterialLibrary::SetChecked(Context, Component, GetMaterials());
					}

					bool FImplSlice::SetSafe(const FString& Context, UPrimitiveComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs, void(*Log)(const FString&) /*=&NCsSkin::FLog::Warning*/) const
					{
						//return CsMaterialLibrary::SetSafe(Context, Component, GetMaterials(), Log);
						return true;
					}
				}
			}
		}
	}
}
