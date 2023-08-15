// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/Scale/CsData_Skin_VisualScale_UniformRangeImplSlice.h"

// Library
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
#include "Containers/CsDeconstructInterfaceSliceMap.h"
// Components
#include "Components/SceneComponent.h"

#define SliceType NCsSkin::NData::NVisual::NScale::NUniform::NRange::FImplSlice

void FCsData_Skin_VisualScale_UniformRangeImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetMinUniformScale(&Min);
	Slice->SetMaxUniformScale(&Max);
}

void FCsData_Skin_VisualScale_UniformRangeImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetMinUniformScale(Min);
	Slice->SetMaxUniformScale(Max);
}

SliceType* FCsData_Skin_VisualScale_UniformRangeImplSlice::AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

	typedef NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange InterfaceType;

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

bool FCsData_Skin_VisualScale_UniformRangeImplSlice::IsValidChecked(const FString& Context) const
{
	CS_IS_FLOAT_GREATER_THAN_CHECKED(Min, 0.0f)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(Max, 0.0f)
	return true;
}

bool FCsData_Skin_VisualScale_UniformRangeImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_FLOAT_GREATER_THAN(Min, 0.0f)
	CS_IS_FLOAT_GREATER_THAN(Max, 0.0f)
	return true;
}

void FCsData_Skin_VisualScale_UniformRangeImplSlice::SetChecked(const FString& Context, USceneComponent* Component) const
{
	check(IsValidChecked(Context));

	CS_IS_PTR_NULL_CHECKED(Component);

	if (Min == Max)
		Component->SetRelativeScale3D(Min * FVector3d::OneVector);
	else
		Component->SetRelativeScale3D(FMath::Lerp(Min, Max, FMath::RandRange(0.0f, 1.0f)) * FVector3d::OneVector);
}

bool FCsData_Skin_VisualScale_UniformRangeImplSlice::SetSafe(const FString& Context, USceneComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	CS_IS_PTR_NULL(Component)

	if (Min == Max)
	Component->SetRelativeScale3D(Min * FVector3d::OneVector);
	else
		Component->SetRelativeScale3D(FMath::Lerp(Min, Max, FMath::RandRange(0.0f, 1.0f)) * FVector3d::OneVector);
	return true;
}

const FName NCsSkin::NData::NVisual::NScale::NUniform::NRange::FImplSlice::Name = FName("NCsSkin::NData::NVisual::NScale::NUniform::NRange::FImplSlice");

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
					namespace NRange
					{
						namespace NImplSlice
						{
							namespace NCached
							{
								namespace Name
								{
									const FName VisualUniformRangeScaleSlice = FName("VisualUniformRangeScaleSlice");

									const FName MinUniformScale = FName("MinUniformScale");
									const FName MaxUniformScale = FName("MaxUniformScale");
								}
							}
						}

						/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
						{
							using namespace NCsSkin::NData::NVisual::NScale::NUniform::NRange::NImplSlice::NCached;

							CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

							typedef NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange InterfaceType;

							if (InterfaceMap->Implements(InterfaceType::Name))
							{
								CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InterfaceMap already contains a reference an interface of type: %s."), *Context, *(InterfaceType::Name.ToString())));
								return nullptr;
							}

							CS_IS_PTR_NULL_RET_NULL(DeconstructInterfaceSliceMap)

							CS_IS_PTR_NULL_RET_NULL(Object)

							// Check for properties matching interface: UniformRangeScaleVisualDataType (NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange)
							typedef NCsProperty::FLibrary PropertyLibrary;

							FImplSlice* Slice = nullptr;
							bool Success	  = false;

							// Try FCsData_Skin_VisualScale_UniformRangeImplSlice
							typedef FCsData_Skin_VisualScale_UniformRangeImplSlice StructSliceType;

							if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::VisualUniformRangeScaleSlice, nullptr))
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
								float* MinUniformScalePtr = PropertyLibrary::GetFloatPropertyValuePtr(Context, Object, Object->GetClass(), Name::MinUniformScale, nullptr);
								float* MaxUniformScalePtr = PropertyLibrary::GetFloatPropertyValuePtr(Context, Object, Object->GetClass(), Name::MaxUniformScale, nullptr);

								if (MinUniformScalePtr &&
									MaxUniformScalePtr)
								{
									Slice = new FImplSlice();

									// Add slice as type SkinType
									InterfaceMap->Add<InterfaceType>(InterfaceType::Name, static_cast<InterfaceType*>(Slice));
									// Set the InterfaceMap of Data to the "root" InterfaceMap
									Slice->SetInterfaceMap(InterfaceMap);

									DeconstructInterfaceSliceMap->AddSlice(FImplSlice::Name, Slice);
									DeconstructInterfaceSliceMap->AddDeconstructSliceImpl(FImplSlice::Name, &FImplSlice::Deconstruct);

									Slice->SetMinUniformScale(MinUniformScalePtr);
									Slice->SetMaxUniformScale(MaxUniformScalePtr);
									Success = true;
								}
							}

							if (!Success)
							{
								if (Log)
								{
									typedef NCsObject::FLibrary ObjectLibrary;

									Log(FString::Printf(TEXT("%s: Failed to find any properties from %s for interface: UniformRangeScaleVisualDataType (NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange)."), *Context, *(ObjectLibrary::PrintObjectAndClass(Object))));
									Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualScale_UniformRangeImplSlice with name: VisualUniformRangeScaleSlice."), *Context));
									Log(FString::Printf(TEXT("%s: - OR"), *Context));
									Log(FString::Printf(TEXT("%s: - Failed to get float property with name: MinUniformScale."), *Context));
									Log(FString::Printf(TEXT("%s: - Failed to get float property with name: MaxUniformScale."), *Context));
								}
							}
							return Slice;
						}

						bool FImplSlice::IsValidChecked(const FString& Context) const
						{
							CS_IS_FLOAT_GREATER_THAN_CHECKED(GetMinUniformScale(), 0.0f)
							CS_IS_FLOAT_GREATER_THAN_CHECKED(GetMaxUniformScale(), 0.0f)
							return true;
						}

						bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
						{
							CS_IS_FLOAT_GREATER_THAN(GetMinUniformScale(), 0.0f)
							CS_IS_FLOAT_GREATER_THAN(GetMaxUniformScale(), 0.0f)
							return true;
						}

						void FImplSlice::SetChecked(const FString& Context, USceneComponent* Component) const
						{
							check(IsValidChecked(Context));

							CS_IS_PTR_NULL_CHECKED(Component);

							const float& Min = GetMinUniformScale();
							const float& Max = GetMaxUniformScale();

							if (Min == Max)
								Component->SetRelativeScale3D(Min * FVector3d::OneVector);
							else
								Component->SetRelativeScale3D(FMath::Lerp(Min, Max, FMath::RandRange(0.0f, 1.0f)) * FVector3d::OneVector);
						}

						bool FImplSlice::SetSafe(const FString& Context, USceneComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
						{
							if (!IsValid(Context, Log))
								return false;

							CS_IS_PTR_NULL(Component)

							const float& Min = GetMinUniformScale();
							const float& Max = GetMaxUniformScale();

							if (Min == Max)
								Component->SetRelativeScale3D(Min * FVector3d::OneVector);
							else
								Component->SetRelativeScale3D(FMath::Lerp(Min, Max, FMath::RandRange(0.0f, 1.0f)) * FVector3d::OneVector);
							return true;
						}
					}
				}
			}
		}
	}
}
