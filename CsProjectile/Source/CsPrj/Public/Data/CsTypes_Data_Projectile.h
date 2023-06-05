// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_StaticMesh.h"
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsTypes_Data_Projectile.generated.h"

// FCsPrjStaticMesh
#pragma region

// NCsProjectile::NVisual::NStaticMesh::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NVisual, NStaticMesh, FInfo)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsPrjStaticMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Mesh")
	FCsStaticMesh Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Mesh")
	FVector Scale;

	/** Whether to scale the mesh by the Collision Radius. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Mesh")
	bool bScaleByCollisionRadius;

public:

	FCsPrjStaticMesh() :
		Mesh(),
		Scale(1.0f),
		bScaleByCollisionRadius(false)
	{
	}

#define InfoType NCsProjectile::NVisual::NStaticMesh::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

class UStaticMesh;

namespace NCsProjectile
{
	namespace NVisual
	{
		namespace NStaticMesh
		{
			struct CSPRJ_API FInfo
			{
			private:
			
				CS_DECLARE_MEMBER_WITH_PROXY(Mesh, UStaticMesh*)
				CS_DECLARE_MEMBER_WITH_PROXY(Scale, FVector)
				CS_DECLARE_MEMBER_WITH_PROXY(bScaleByCollisionRadius, bool)

			public:

				FInfo() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Mesh, nullptr),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Scale, 1.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bScaleByCollisionRadius, false)
				{
					CS_CTOR_SET_MEMBER_PROXY(Mesh);
					CS_CTOR_SET_MEMBER_PROXY(Scale);
					CS_CTOR_SET_MEMBER_PROXY(bScaleByCollisionRadius);
				}
	
				CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Mesh, UStaticMesh)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Scale, FVector)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bScaleByCollisionRadius, bool)

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
			};
		}
	}
}

#pragma endregion FCsPrjStaticMesh