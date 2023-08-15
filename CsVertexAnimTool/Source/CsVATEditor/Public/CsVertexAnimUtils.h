// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#if WITH_EDITOR

class UMeshComponent;
class UStaticMesh;

/**
* Abstract class holding helper functions to be used in the baking process
*/
namespace NCsAnimation
{
	namespace NVertex
	{
		namespace NTool
		{
			struct CSVATEDITOR_API FUtility
			{
			public:

				static float EncodeFloat(const float& T, const float& Bound);
				static float DeEncodeFloat(const float& T, const float& Bound);
	
				static FVector DeEncodeVec(const FVector4& T, const float& Bound);

				static FVector4 BitEncodeVecId(const FVector T, const float Bound, const int32 Id);
				static FVector4 BitEncodeVecId_HD(const FVector T, const float Bound, const int32 Id);

				static int32 Grid2DIndex(const int32& X, const int32& Y, const int32& Width);
				static int32 Grid2D_X(const int32& Index, const int32& Height);
				static int32 Grid2D_Y(const int32& Index, const int32& Height);

				/**
				 * Convert a set of mesh components in their current pose to a static mesh.
				 * 
				 * @param	InMeshComponents		The mesh components we want to convert
				 * @param	InRootTransform			The transform of the root of the mesh we want to output
				 * @param	InPackageName			The package name to create the static mesh in. If this is empty then a dialog will be displayed to pick the mesh.
				 * @return a new static mesh (specified by the user)
				 */
				static UStaticMesh* ConvertMeshesToStaticMesh(const TArray<UMeshComponent*>& InMeshComponents, const FTransform& InRootTransform = FTransform::Identity, const FString& InPackageName = FString());

				static void VATUVsToStaticMeshLODs(UStaticMesh* StaticMesh, const int32 UVChannel, const TArray <TArray <FVector2f>>& UVs);
				static void VATColorsToStaticMeshLODs(UStaticMesh* StaticMesh, const TArray <TArray <FColor>>& Colors);
			};
		}
	}
}

#endif // #if WITH_EDITOR