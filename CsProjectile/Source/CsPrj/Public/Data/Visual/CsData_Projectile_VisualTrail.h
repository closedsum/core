// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/FX/CsTypes_FX.h"
#include "CsData_Projectile_VisualTrail.generated.h"

namespace NCsProjectile
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NTrail
			{
				/**
				*/
				struct CSPRJ_API ITrail : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					/**
					*/
					virtual const FCsFX& GetTrailFX() const = 0;
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_Projectile_VisualTrail : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSPRJ_API ICsData_Projectile_VisualTrail : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual const FCsFX& GetTrailFX() const = 0;
};