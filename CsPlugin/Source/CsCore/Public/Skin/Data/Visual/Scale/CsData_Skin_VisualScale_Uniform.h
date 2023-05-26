// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_Skin_VisualScale_Uniform.generated.h"

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
					/**
					* Interface for determining the Uniform Scale of the visual Skin.
					* The default Uniform Scale is 1.0f.
					* This interface is usually used in testing.
					*/
					struct CSCORE_API IUniform : public ICsGetInterfaceMap
					{
					public:

						static const FName Name;

					public:

						virtual ~IUniform() {}

						/**
						*/
						virtual const float& GetUniformScale() const = 0;
					};
				}
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_Skin_VisualUniformScale : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for determining the Uniform Scale of the visual Skin.
* The default Scale is 1.0f.
* This interface is usually used in testing.
*/
class CSCORE_API ICsData_Skin_VisualUniformScale : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual const float& GetUniformScale() const = 0;
};

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_Skin_VisualScale_Uniform : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for determining the Uniform Scale of the visual Skin.
* The default Scale is 1.0f.
* This interface is usually used in testing.
*/
class CSCORE_API ICsData_Skin_VisualScale_Uniform : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual const float& GetUniformScale() const = 0;
};