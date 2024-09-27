// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_Skin_VisualScale_UniformRange.generated.h"

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
						/**
						* Interface for determining the minimum and maximum Uniform Scale of the visual Skin.
						* The default Uniform Scale is [1.0f, 1.0f].
						*/
						struct CSSKIN_API IRange : public ICsGetInterfaceMap
						{
						public:

							static const FName Name;

						public:

							virtual ~IRange() {}

							/**
							* Get the minimum scale. 
							* The scale is applied:
							*  Scale: FMath::Lerp(Min, Max, FMath::RangeRange(0.0f, 1.0f)) * FVector3d::OneVector.
							* 
							* return
							*/
							virtual const float& GetMinUniformScale() const = 0;

							/**
							* Get the maximum scale.
							* The scale is applied:
							*  Scale: FMath::Lerp(Min, Max, FMath::RangeRange(0.0f, 1.0f)) * FVector3d::OneVector.
							*
							* return
							*/
							virtual const float& GetMaxUniformScale() const = 0;
						};
					}
				}
			}
		}
	}
}

using CsUniformRangeScaleSkinDataType = NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange;

UINTERFACE(BlueprintType)
class CSSKIN_API UCsData_Skin_VisualScale_UniformRange : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for determining the minimum and maximum Uniform Scale of the visual Skin.
* The default Uniform Scale is [1.0f, 1.0f].
*/
class CSSKIN_API ICsData_Skin_VisualScale_UniformRange : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	* Get the minimum scale.
	* The scale is applied:
	*  Scale: FMath::Lerp(Min, Max, FMath::RangeRange(0.0f, 1.0f)) * FVector3d::OneVector.
	*
	* return
	*/
	virtual const float& GetMinUniformScale() const = 0;

	/**
	* Get the maximum scale.
	* The scale is applied:
	*  Scale: FMath::Lerp(Min, Max, FMath::RangeRange(0.0f, 1.0f)) * FVector3d::OneVector.
	*
	* return
	*/
	virtual const float& GetMaxUniformScale() const = 0;
};