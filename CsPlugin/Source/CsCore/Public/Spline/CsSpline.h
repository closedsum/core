// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
#include "CsSpline.generated.h"

UINTERFACE(BlueprintType, MinimalApi, meta = (CannotImplementInterfaceInBlueprint))
class UCsSpline : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class USplineComponent;

class CSCORE_API ICsSpline
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual USplineComponent* GetSplineComponent() = 0;
};

// FCsSpline
#pragma region

struct CSCORE_API FCsSpline : public TCsInterfaceObject<ICsSpline>
{
private:

	typedef TCsInterfaceObject<ICsSpline> Super;

public:

	static const FCsSpline Empty;

// Script
#pragma region
public:

	/**
	* Delegate type for getting the primary spline component.
	*  The object implements a script interface of type: ICsSpline.
	*
	* @param Object		An object of type: ICsSpline.
	* return			Spline Component.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(USplineComponent*, FScript_GetSplineComponent, UObject* /*Object*/);

	/** Delegate for getting the primary spline component. 
		  The object implements a script interface of type: ICsSpline. */
	FScript_GetSplineComponent Script_GetSplineComponent_Impl;


#pragma endregion Script

public:

	FCsSpline() :
		Super(),
		Script_GetSplineComponent_Impl()
	{
	}

	virtual ~FCsSpline() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void Reset() override 
	{
		Super::Reset();

		Script_GetSplineComponent_Impl.Unbind();
	}

#pragma endregion TCsInterfaceObject

// ICsSpline
#pragma region
public:

	FORCEINLINE USplineComponent* GetSplineComponent()
	{
		if (bScript)
			return Script_GetSplineComponent_Impl.Execute(Object);
		return Interface->GetSplineComponent();
	}

#pragma endregion ICsSpline
};

#pragma endregion FCsSpline