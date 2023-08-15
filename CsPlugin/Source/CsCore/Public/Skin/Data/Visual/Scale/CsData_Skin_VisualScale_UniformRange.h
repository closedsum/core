// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
						struct CSCORE_API IRange : public ICsGetInterfaceMap
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

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_Skin_VisualScale_UniformRange : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for determining the minimum and maximum Uniform Scale of the visual Skin.
* The default Uniform Scale is [1.0f, 1.0f].
*/
class CSCORE_API ICsData_Skin_VisualScale_UniformRange : public ICsGetInterfaceMap
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