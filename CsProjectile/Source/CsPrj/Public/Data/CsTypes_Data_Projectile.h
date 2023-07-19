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


// NCsProjectile::NVisual::NStaticMesh::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NVisual, NStaticMesh, FInfo)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_Visual_StaticMeshInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Mesh")
	FCsStaticMesh Mesh;

	/** The size of the Mesh in World Space. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Mesh")
	FVector Scale;

	/** Whether to scale the mesh by the Collision Radius. 
		NOTE: If TRUE, Scale is ignored. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Mesh")
	bool bScaleByCollisionRadius;

	/** Multiplier to apply to Collision Radius.
		NOTE: Only used if bScaleByCollisionRadius is TRUE. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Mesh", meta = (EditCondition = "bScaleByCollisionRadius", UIMin = "0.0", ClampMin = "0.0"))
	float ScaleByCollisionRadiusMultiplier;

public:

	FCsProjectile_Visual_StaticMeshInfo() :
		Mesh(),
		Scale(1.0f),
		bScaleByCollisionRadius(false),
		ScaleByCollisionRadiusMultiplier(1.0f)
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
				/** The size of the Mesh in World Space. */
				CS_DECLARE_MEMBER_WITH_PROXY(Scale, FVector)
				/** Whether to scale the mesh by the Collision Radius. 
					NOTE: If TRUE, Scale is ignored. */
				CS_DECLARE_MEMBER_WITH_PROXY(bScaleByCollisionRadius, bool)
				/** Multiplier to apply to Collision Radius.
					NOTE: Only used if bScaleByCollisionRadius is TRUE. */
				CS_DECLARE_MEMBER_WITH_PROXY(ScaleByCollisionRadiusMultiplier, float)

			public:

				FInfo() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Mesh, nullptr),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Scale, 1.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bScaleByCollisionRadius, false),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(ScaleByCollisionRadiusMultiplier, 1.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(Mesh);
					CS_CTOR_SET_MEMBER_PROXY(Scale);
					CS_CTOR_SET_MEMBER_PROXY(bScaleByCollisionRadius);
					CS_CTOR_SET_MEMBER_PROXY(ScaleByCollisionRadiusMultiplier);
				}
	
				CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Mesh, UStaticMesh)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Scale, FVector)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bScaleByCollisionRadius, bool)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ScaleByCollisionRadiusMultiplier, float)

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
			};
		}
	}
}

#pragma endregion FCsProjectile_Visual_StaticMeshInfo