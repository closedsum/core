// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interface
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Data/CsTypes_Data_Projectile.h"

#include "CsData_Projectile_VisualStaticMesh.generated.h"

class UStaticMesh;

namespace NCsProjectile
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NStaticMesh
			{
				/**
				*/
				struct CSPRJ_API IStaticMesh : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IStaticMesh(){}

				private:

					// Allow clearer names without name collisions
					struct _
					{
						using StaticMeshInfoType = NCsProjectile::NVisual::NStaticMesh::FInfo;
					};

				public:

					virtual const _::StaticMeshInfoType& GetStaticMeshInfo() const = 0;
				};
			}
		}
	}
}


UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_Projectile_VisualStaticMesh : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class UStaticMesh;

/**
*/
class CSPRJ_API ICsData_Projectile_VisualStaticMesh : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

private:

	// Allow clearer names without name collisions
	struct _
	{
		using StaticMeshInfoType = NCsProjectile::NVisual::NStaticMesh::FInfo;
	};

public:

	virtual const _::StaticMeshInfoType& GetStaticMeshInfo() const = 0;
};