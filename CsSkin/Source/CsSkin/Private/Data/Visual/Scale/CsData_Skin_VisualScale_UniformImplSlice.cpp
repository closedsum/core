// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Visual/Scale/CsData_Skin_VisualScale_UniformImplSlice.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
#include "Containers/CsDeconstructInterfaceSliceMap.h"
// Components
#include "Components/SceneComponent.h"

#define SliceType NCsSkin::NData::NVisual::NScale::NUniform::FImplSlice

void FCsData_Skin_VisualScale_UniformImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetUniformScale(&Scale);
}

void FCsData_Skin_VisualScale_UniformImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetUniformScale(Scale);
}

SliceType* FCsData_Skin_VisualScale_UniformImplSlice::AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

	typedef NCsSkin::NData::NVisual::NScale::NUniform::IUniform InterfaceType;

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

#undef SliceType

bool FCsData_Skin_VisualScale_UniformImplSlice::IsValidChecked(const FString& Context) const
{
	CS_IS_FLOAT_GREATER_THAN_CHECKED(Scale, 0.0f)
	return true;
}

bool FCsData_Skin_VisualScale_UniformImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_FLOAT_GREATER_THAN(Scale, 0.0f)
	return true;
}

void FCsData_Skin_VisualScale_UniformImplSlice::SetChecked(const FString& Context, USceneComponent* Component) const
{
	check(IsValidChecked(Context));

	CS_IS_PTR_NULL_CHECKED(Component);

	Component->SetRelativeScale3D(Scale * FVector3d::OneVector);
}

bool FCsData_Skin_VisualScale_UniformImplSlice::SetSafe(const FString& Context, USceneComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	CS_IS_PTR_NULL(Component)

	Component->SetRelativeScale3D(Scale * FVector3d::OneVector);
	return true;
}

const FName NCsSkin::NData::NVisual::NScale::NUniform::FImplSlice::Name = FName("NCsSkin::NData::NVisual::NScale::NUniform::FImplSlice");

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NScale
			{
				namespace NUniform
				{
					namespace NImplSlice
					{
						namespace NCached
						{
							namespace Name
							{
								const FName VisualUniformScaleSlice = FName("VisualUniformScaleSlice");

								const FName UniformScale = FName("UniformScale");
							}
						}
					}

					/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
					{
						using namespace NCsSkin::NData::NVisual::NScale::NUniform::NImplSlice::NCached;

						CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

						typedef NCsSkin::NData::NVisual::NScale::NUniform::IUniform InterfaceType;

						if (InterfaceMap->Implements(InterfaceType::Name))
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InterfaceMap already contains a reference an interface of type: %s."), *Context, *(InterfaceType::Name.ToString())));
							return nullptr;
						}

						CS_IS_PTR_NULL_RET_NULL(DeconstructInterfaceSliceMap)

						CS_IS_PTR_NULL_RET_NULL(Object)

						// Check for properties matching interface: StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
						typedef NCsProperty::FLibrary PropertyLibrary;

						FImplSlice* Slice = nullptr;
						bool Success	  = false;

						// Try FCsData_Skin_VisualScale_UniformImplSlice
						typedef FCsData_Skin_VisualScale_UniformImplSlice StructSliceType;

						if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::VisualUniformScaleSlice, nullptr))
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
							float* UniformScalePtr = PropertyLibrary::GetFloatPropertyValuePtr(Context, Object, Object->GetClass(), Name::UniformScale, nullptr);

							if (UniformScalePtr)
							{
								Slice = new FImplSlice();

								// Add slice as type SkinType
								InterfaceMap->Add<InterfaceType>(InterfaceType::Name, static_cast<InterfaceType*>(Slice));
								// Set the InterfaceMap of Data to the "root" InterfaceMap
								Slice->SetInterfaceMap(InterfaceMap);

								DeconstructInterfaceSliceMap->AddSlice(FImplSlice::Name, Slice);
								DeconstructInterfaceSliceMap->AddDeconstructSliceImpl(FImplSlice::Name, &FImplSlice::Deconstruct);

								Slice->SetUniformScale(UniformScalePtr);
								Success = true;
							}
						}

						if (!Success)
						{
							if (Log)
							{
								typedef NCsObject::FLibrary ObjectLibrary;

								Log(FString::Printf(TEXT("%s: Failed to find any properties from %s for interface: UniformScaleVisualDataType (NCsSkin::NData::NVisual::NScale::NUniform::IUniform)."), *Context, *(ObjectLibrary::PrintObjectAndClass(Object))));
								Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualScale_UniformImplSlice with name: VisualUniformScaleSlice."), *Context));
								Log(FString::Printf(TEXT("%s: - OR"), *Context));
								Log(FString::Printf(TEXT("%s: - Failed to get float property with name: UniformScale."), *Context));
							}
						}
						return Slice;
					}

					bool FImplSlice::IsValidChecked(const FString& Context) const
					{
						CS_IS_FLOAT_GREATER_THAN_CHECKED(GetUniformScale(), 0.0f)
						return true;
					}

					bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
					{
						CS_IS_FLOAT_GREATER_THAN(GetUniformScale(), 0.0f)
						return true;
					}

					void FImplSlice::SetChecked(const FString& Context, USceneComponent* Component) const
					{
						check(IsValidChecked(Context));

						CS_IS_PTR_NULL_CHECKED(Component);

						Component->SetRelativeScale3D(GetUniformScale() * FVector3d::OneVector);
					}

					bool FImplSlice::SetSafe(const FString& Context, USceneComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
					{
						if (!IsValid(Context, Log))
							return false;

						CS_IS_PTR_NULL(Component)

						Component->SetRelativeScale3D(GetUniformScale() * FVector3d::OneVector);
						return true;
					}
				}
			}
		}
	}
}
