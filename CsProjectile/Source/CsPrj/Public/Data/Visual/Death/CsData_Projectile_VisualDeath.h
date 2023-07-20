// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/Visual/CsTypes_Projectile_Visual_Death.h"

#include "CsData_Projectile_VisualDeath.generated.h"

namespace NCsProjectile
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NDeath
			{
				/**
				*/
				struct CSPRJ_API IDeath : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

				#define DeathVisualInfoType NCsProjectile::NVisual::NDeath::FInfo

					/**
					* Get whether to use any Visual information related to "dying".
					* 
					* return
					*/
					virtual const bool& UseDeathVisualInfo() const = 0;

					/**
					* Get the Visual information associated with "dying".
					* 
					* return	Visual Impact information related to the Projectile "dying"
					*/
					virtual const DeathVisualInfoType& GetDeathVisualInfo() const = 0;

				#undef DeathVisualInfoType
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_Projectile_VisualDeath : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSPRJ_API ICsData_Projectile_VisualDeath : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
	
#define DeathVisualInfoType NCsProjectile::NVisual::NDeath::FInfo

	/**
	* Get whether to use any Visual information related to "dying".
	*
	* return
	*/
	virtual const bool& UseDeathVisualInfo() const = 0;

	/**
	* Get the Visual Impact information associated with "dying".
	*
	* return	Visual information related to the Projectile "dying"
	*/
	virtual const DeathVisualInfoType& GetDeathVisualInfo() const = 0;

#undef DeathVisualInfoType
};