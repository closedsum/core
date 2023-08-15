// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UCsVertexAnimProfile;
class UDebugSkelMeshComponent;
class USkeletalMesh;

namespace NCsAnimation
{
    namespace NVertex
    {
        namespace NTool
        {
            namespace NEditor
            {
            #if WITH_EDITOR

                struct CSVATEDITOR_API FUtility
                {
                public:

                    static float PackBits(const uint32& bit);
                    static int UnPackBits(const float bit);
                    
                    static void DoBakeProcess(UCsVertexAnimProfile* Profile);
                    static void DoBakeProcess(UCsVertexAnimProfile* Profile, UDebugSkelMeshComponent* PreviewComponent);
    
                    static void SkelPivotPos(USkeletalMesh* Skel, TArray <FVector>& VectorData);
                    static void SkelOrigin(USkeletalMesh* Skel, TArray <FVector>& VectorData);
                    static void SkelExtents(USkeletalMesh* Skel, TArray <FVector>& VectorData);

                    static void VectorDataToTextureColor(const TArray<FVector>& InVectorData, TArray <FFloat16Color>& Data);
                    // used for HDR Pivot Pos, Origin Pos, Origin Extents | ldr Pivot Directions (X, Y or Z)
                    static void VectorDataToUV(const TArray<FVector>& InVectorData, const int32 StartIdx, TArray<FVector2D[MAX_STATIC_TEXCOORDS]>& UVs);
                    // used for ldr Pivot Directions (X, Y or Z)
                    static void VectorDataToVertColor(const TArray<FVector>& InVectorData, TArray<FColor>& Colors);

                    static void UVChannelsToSkeletalMesh(USkeletalMesh* Skel, const int32 LODIndex, const int32 UVChannelStart, TArray<TArray<FVector2f>>& UVChannels);
                    static void UVChannelToStaticMesh(UStaticMesh* Mesh, const int32 TargetUVChannel, TArray <FVector2D>& UVs);

                    static void IntoIslands(const TArray <int32>& IndexBuffer, const TArray <FVector2D>& UVs, TArray <int32>& OutIslandIDs, int32& OutNumIslands);
                    static void ClosestUVPivotAssign(const TArray <int32>& IndexBuffer, const TArray <FVector2D>& UVs, const TArray <FVector2D>& PivotUVPos, TArray <int32>& VertPivotIDs);
                };

            #endif // #if WITH_EDITOR
            }
        }
    }
}


