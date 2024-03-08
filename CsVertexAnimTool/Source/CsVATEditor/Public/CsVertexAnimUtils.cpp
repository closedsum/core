// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "CsVertexAnimUtils.h"

#if WITH_EDITOR

// Library
#include "Library/CsLibrary_Math.h"
// Material
#include "Materials/MaterialInstanceDynamic.h"
// Module
#include "Modules/ModuleManager.h"
#include "AssetToolsModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
// Components
#include "Components/StaticMeshComponent.h"
// Mesh
#include "RawMesh.h"
#include "Rendering/SkeletalMeshRenderData.h"
#include "SkeletalRenderPublic.h"
#include "Engine/SkinnedAssetCommon.h"

namespace NCsAnimation
{
	namespace NVertex
	{
		namespace NTool
		{
			float FUtility::EncodeFloat(const float & T, const float& Bound)
			{
				// Divide to normalize, + 1 * 0.5 to account for negative Values
				return ((T / Bound) + 1.f) * 0.5f;
			}

			float FUtility::DeEncodeFloat(const float & T, const float & Bound)
			{
				return ((T * 2.f) - 1.f) * Bound;
			}

			FVector FUtility::DeEncodeVec(const FVector4& T, const float& Bound)
			{
				return (((FVector(T) * 2.f) - 1.f) * T.W) * Bound;
			}

			FVector4 FUtility::BitEncodeVecId(const FVector T, const float Bound, const int32 Id)
			{
				const FVector N = ((T / Bound) +1.0) * 0.5;

				uint32 RI = N.X * 1023;
				uint32 GI = N.Y * 1023;
				uint32 BI = N.Z * 1023;

				uint8 R8 = (uint8)(RI);
				uint8 G8 = (uint8)(GI);
				uint8 B8 = (uint8)(BI);

				// Should I be doing and & on these??
				uint8 RA = (uint8)((RI >> 8) & 0x3);
				uint8 GA = (uint8)((GI >> 6) & 0xc);
				uint8 BA = (uint8)((BI >> 4) & 0x30);
				uint8 IA = (uint8)(Id) << 6;

				uint8 A8 = ((RA | GA) | BA) | IA;

				return FVector4(R8 / 255.0, G8 / 255.0, B8 / 255.0, A8 / 255.0);
			}

			FVector4 FUtility::BitEncodeVecId_HD(const FVector T, const float Bound, const int32 Id)
			{
				const FVector N = ((T / Bound) + 1.0) * 0.5;

				uint32 RI = N.X * 0xFFFFF; 
				uint32 GI = N.Y * 0xFFFFF;
				uint32 BI = N.Z * 0xFFFFF;

				uint16 R8 = (uint16)(RI);
				uint16 G8 = (uint16)(GI);
				uint16 B8 = (uint16)(BI);

				// Should I be doing and & on these??
				uint16 RA = (uint16)((RI >> 16) & 0xF);
				uint16 GA = (uint16)((GI >> 12) & 0xF0);
				uint16 BA = (uint16)((BI >> 8) & 0xF00);
				uint16 IA = (uint16)(Id) << 12;

				//UE_LOG(LogUnrealMath, Warning, TEXT("RI %i, R8 %i || RA %i || IA %i"), RI, R8, RA, IA);

				uint16 A8 = ((RA | GA) | BA) | IA;

				return FVector4(
					-1.0 + ((R8 / 65535.0) * 2.0),
					-1.0 + ((G8 / 65535.0) * 2.0),
					-1.0 + ((B8 / 65535.0) * 2.0),
					-1.0 + ((A8 / 65535.0) * 2.0));
			}

			int32 FUtility::Grid2DIndex(const int32& X, const int32& Y, const int32& Width)
			{
				//(LocationX * GridSize.Height) + LocationY // CellIndex
				//return (X * Height) + Y;
				return (Y * Width) + X;
			}

			// This should be Y with Width
			int32 FUtility::Grid2D_X(const int32 & Index, const int32 & Width)
			{
				// Original // X  = CellIndex / GridSize.Height
				//return Index % Height;
				return Index % Width;
			}

			// This Should be X with Width
			int32 FUtility::Grid2D_Y(const int32 & Index, const int32 & Width)
			{
				// For Y = CellIndex % GridSize.Height
				//return  Index / Height;
				return  Index / Width;
			}

			// Helper function for ConvertMeshesToStaticMesh
			static void AddOrDuplicateMaterial(UMaterialInterface* InMaterialInterface, const FString& InPackageName, TArray<UMaterialInterface*>& OutMaterials)
			{
				if (InMaterialInterface && !InMaterialInterface->GetOuter()->IsA<UPackage>())
				{
					// Convert runtime material instances to new concrete material instances
					// Create new package
					FString OriginalMaterialName = InMaterialInterface->GetName();
					FString MaterialPath = FPackageName::GetLongPackagePath(InPackageName) / OriginalMaterialName;
					FString MaterialName;
					FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
					AssetToolsModule.Get().CreateUniqueAssetName(MaterialPath, TEXT(""), MaterialPath, MaterialName);
					UPackage* MaterialPackage = CreatePackage(*MaterialPath);

					// Duplicate the object into the new package
					UMaterialInterface* NewMaterialInterface = DuplicateObject<UMaterialInterface>(InMaterialInterface, MaterialPackage, *MaterialName);
					NewMaterialInterface->SetFlags(RF_Public | RF_Standalone);

					if (UMaterialInstanceDynamic* MaterialInstanceDynamic = Cast<UMaterialInstanceDynamic>(NewMaterialInterface))
					{
						UMaterialInstanceDynamic* OldMaterialInstanceDynamic = CastChecked<UMaterialInstanceDynamic>(InMaterialInterface);
						MaterialInstanceDynamic->K2_CopyMaterialInstanceParameters(OldMaterialInstanceDynamic);
					}

					NewMaterialInterface->MarkPackageDirty();

					FAssetRegistryModule::AssetCreated(NewMaterialInterface);

					InMaterialInterface = NewMaterialInterface;
				}

				OutMaterials.Add(InMaterialInterface);
			}

			// Helper function for ConvertMeshesToStaticMesh
			template <typename ComponentType>
			static void ProcessMaterials(ComponentType* InComponent, const FString& InPackageName, TArray<UMaterialInterface*>& OutMaterials)
			{
				const int32 NumMaterials = InComponent->GetNumMaterials();
				for (int32 MaterialIndex = 0; MaterialIndex < NumMaterials; MaterialIndex++)
				{
					UMaterialInterface* MaterialInterface = InComponent->GetMaterial(MaterialIndex);
					AddOrDuplicateMaterial(MaterialInterface, InPackageName, OutMaterials);
				}
			}

			// Helper function for ConvertMeshesToStaticMesh
			static bool IsValidSkinnedMeshComponent(USkinnedMeshComponent* InComponent)
			{
				return InComponent && InComponent->MeshObject && InComponent->IsVisible();
			}

			/** Helper struct for tracking validity of optional buffers */
			struct FRawMeshTracker
			{
				FRawMeshTracker()
					: bValidColors(false)
				{
					FMemory::Memset(bValidTexCoords, 0);
				}

				bool bValidTexCoords[MAX_MESH_TEXTURE_COORDS];
				bool bValidColors;
			};

			// Helper function for ConvertMeshesToStaticMesh
			static void SkinnedMeshToRawMeshes(USkinnedMeshComponent* InSkinnedMeshComponent, int32 InOverallMaxLODs, const FMatrix44d& InComponentToWorld, const FString& InPackageName, TArray<FRawMeshTracker>& OutRawMeshTrackers, TArray<FRawMesh>& OutRawMeshes, TArray<UMaterialInterface*>& OutMaterials)
			{
				typedef NCsMath::FLibrary MathLibrary;

				const int32 BaseMaterialIndex = OutMaterials.Num();

				// Export all LODs to raw meshes
				const int32 NumLODs = InSkinnedMeshComponent->GetNumLODs();

				for (int32 OverallLODIndex = 0; OverallLODIndex < InOverallMaxLODs; OverallLODIndex++)
				{
					int32 LODIndexRead = FMath::Min(OverallLODIndex, NumLODs - 1);

					FRawMesh& RawMesh = OutRawMeshes[OverallLODIndex];
					FRawMeshTracker& RawMeshTracker = OutRawMeshTrackers[OverallLODIndex];
					const int32 BaseVertexIndex = RawMesh.VertexPositions.Num();

					FSkeletalMeshLODInfo& SrcLODInfo = *(InSkinnedMeshComponent->GetSkinnedAsset()->GetLODInfo(LODIndexRead));

					// Get the CPU skinned verts for this LOD
					TArray<FFinalSkinVertex> FinalVertices;
					InSkinnedMeshComponent->GetCPUSkinnedVertices(FinalVertices, LODIndexRead);

					FSkeletalMeshRenderData& SkeletalMeshRenderData = InSkinnedMeshComponent->MeshObject->GetSkeletalMeshRenderData();
					FSkeletalMeshLODRenderData& LODData = SkeletalMeshRenderData.LODRenderData[LODIndexRead];

					// Copy skinned vertex positions
					for (int32 VertIndex = 0; VertIndex < FinalVertices.Num(); ++VertIndex)
					{
						RawMesh.VertexPositions.Add(MathLibrary::Convert(InComponentToWorld.TransformPosition(MathLibrary::Convert(FinalVertices[VertIndex].Position))));
					}

					const uint32 NumTexCoords = FMath::Min(LODData.StaticVertexBuffers.StaticMeshVertexBuffer.GetNumTexCoords(), (uint32)MAX_MESH_TEXTURE_COORDS);
					const int32 NumSections = LODData.RenderSections.Num();
					FRawStaticIndexBuffer16or32Interface& IndexBuffer = *LODData.MultiSizeIndexContainer.GetIndexBuffer();

					typedef NCsMath::FLibrary MathLibrary;

					for (int32 SectionIndex = 0; SectionIndex < NumSections; SectionIndex++)
					{
						const FSkelMeshRenderSection& SkelMeshSection = LODData.RenderSections[SectionIndex];
						if (InSkinnedMeshComponent->IsMaterialSectionShown(SkelMeshSection.MaterialIndex, LODIndexRead))
						{
							// Build 'wedge' info
							const int32 NumWedges = SkelMeshSection.NumTriangles * 3;
							for (int32 WedgeIndex = 0; WedgeIndex < NumWedges; WedgeIndex++)
							{
								const int32 VertexIndexForWedge = IndexBuffer.Get(SkelMeshSection.BaseIndex + WedgeIndex);

								RawMesh.WedgeIndices.Add(BaseVertexIndex + VertexIndexForWedge);

								const FFinalSkinVertex& SkinnedVertex = FinalVertices[VertexIndexForWedge];
								const FVector3d TangentX		= InComponentToWorld.TransformVector(SkinnedVertex.TangentX.ToFVector());
								const FVector3d TangentZ		= InComponentToWorld.TransformVector(SkinnedVertex.TangentZ.ToFVector());
								const FVector4d UnpackedTangentZ = SkinnedVertex.TangentZ.ToFVector4();
								const FVector3d TangentY		= (TangentZ ^ TangentX).GetSafeNormal() * UnpackedTangentZ.W;

								RawMesh.WedgeTangentX.Add(MathLibrary::Convert(TangentX));
								RawMesh.WedgeTangentY.Add(MathLibrary::Convert(TangentY));
								RawMesh.WedgeTangentZ.Add(MathLibrary::Convert(TangentZ));

								for (uint32 TexCoordIndex = 0; TexCoordIndex < MAX_MESH_TEXTURE_COORDS; TexCoordIndex++)
								{
									if (TexCoordIndex >= NumTexCoords)
									{
										RawMesh.WedgeTexCoords[TexCoordIndex].AddDefaulted();
									}
									else
									{
										RawMesh.WedgeTexCoords[TexCoordIndex].Add(LODData.StaticVertexBuffers.StaticMeshVertexBuffer.GetVertexUV(VertexIndexForWedge, TexCoordIndex));
										RawMeshTracker.bValidTexCoords[TexCoordIndex] = true;
									}
								}

								if (LODData.StaticVertexBuffers.ColorVertexBuffer.IsInitialized())
								{
									RawMesh.WedgeColors.Add(LODData.StaticVertexBuffers.ColorVertexBuffer.VertexColor(VertexIndexForWedge));
									RawMeshTracker.bValidColors = true;
								}
								else
								{
									RawMesh.WedgeColors.Add(FColor::White);
								}
							}

							int32 MaterialIndex = SkelMeshSection.MaterialIndex;
							// use the remapping of material indices if there is a valid value
							if (SrcLODInfo.LODMaterialMap.IsValidIndex(SectionIndex) && SrcLODInfo.LODMaterialMap[SectionIndex] != INDEX_NONE)
							{
								MaterialIndex = FMath::Clamp<int32>(SrcLODInfo.LODMaterialMap[SectionIndex], 0, InSkinnedMeshComponent->GetSkinnedAsset()->GetMaterials().Num());
							}

							// copy face info
							for (uint32 TriIndex = 0; TriIndex < SkelMeshSection.NumTriangles; TriIndex++)
							{
								RawMesh.FaceMaterialIndices.Add(BaseMaterialIndex + MaterialIndex);
								RawMesh.FaceSmoothingMasks.Add(0); // Assume this is ignored as bRecomputeNormals is false
							}
						}
					}
				}

				ProcessMaterials<USkinnedMeshComponent>(InSkinnedMeshComponent, InPackageName, OutMaterials);
			}

			UStaticMesh* FUtility::ConvertMeshesToStaticMesh(const TArray<UMeshComponent*>& InMeshComponents, const FTransform& InRootTransform, const FString& InPackageName)
			{
				UStaticMesh* StaticMesh = nullptr;

				// Build a package name to use
				FString MeshName;
				FString PackageName;

				if (InPackageName.IsEmpty())
				{
					FString NewNameSuggestion = FString(TEXT("StaticMesh"));
					FString PackageNameSuggestion = FString(TEXT("/Game/Meshes/")) + NewNameSuggestion;
					FString Name;
					FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
					AssetToolsModule.Get().CreateUniqueAssetName(PackageNameSuggestion, TEXT(""), PackageNameSuggestion, Name);

					/*
					TSharedPtr<SDlgPickAssetPath> PickAssetPathWidget =
						SNew(SDlgPickAssetPath)
						.Title(LOCTEXT("ConvertToStaticMeshPickName", "Choose New StaticMesh Location"))
						.DefaultAssetPath(FText::FromString(PackageNameSuggestion));

					if (PickAssetPathWidget->ShowModal() == EAppReturnType::Ok)
					{
						// Get the full name of where we want to create the mesh asset.
						PackageName = PickAssetPathWidget->GetFullAssetPath().ToString();
						MeshName = FPackageName::GetLongPackageAssetName(PackageName);

						// Check if the user inputed a valid asset name, if they did not, give it the generated default name
						if (MeshName.IsEmpty())
						{
							// Use the defaults that were already generated.
							PackageName = PackageNameSuggestion;
							MeshName = *Name;
						}
					}
					*/
					PackageName = PackageNameSuggestion;
					MeshName = *Name;
				}
				else
				{
					PackageName = InPackageName;
					MeshName = *FPackageName::GetLongPackageAssetName(PackageName);
				}

				if (!PackageName.IsEmpty() && !MeshName.IsEmpty())
				{
					TArray<FRawMesh> RawMeshes;
					TArray<UMaterialInterface*> Materials;

					TArray<FRawMeshTracker> RawMeshTrackers;

					FMatrix WorldToRoot = InRootTransform.ToMatrixWithScale().Inverse();

					// first do a pass to determine the max LOD level we will be combining meshes into
					int32 OverallMaxLODs = 0;
					for (UMeshComponent* MeshComponent : InMeshComponents)
					{
						USkinnedMeshComponent* SkinnedMeshComponent = Cast<USkinnedMeshComponent>(MeshComponent);
						UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(MeshComponent);

						if (IsValidSkinnedMeshComponent(SkinnedMeshComponent))
						{
							OverallMaxLODs = FMath::Max(SkinnedMeshComponent->MeshObject->GetSkeletalMeshRenderData().LODRenderData.Num(), OverallMaxLODs);
						}
						else if (false)//(IsValidStaticMeshComponent(StaticMeshComponent))
						{
							OverallMaxLODs = FMath::Max(StaticMeshComponent->GetStaticMesh()->GetRenderData()->LODResources.Num(), OverallMaxLODs);
						}
					}

					// Resize raw meshes to accommodate the number of LODs we will need
					RawMeshes.SetNum(OverallMaxLODs);
					RawMeshTrackers.SetNum(OverallMaxLODs);

					// Export all visible components
					for (UMeshComponent* MeshComponent : InMeshComponents)
					{
						FMatrix ComponentToWorld = MeshComponent->GetComponentTransform().ToMatrixWithScale() * WorldToRoot;

						USkinnedMeshComponent* SkinnedMeshComponent = Cast<USkinnedMeshComponent>(MeshComponent);
						UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(MeshComponent);

						if (IsValidSkinnedMeshComponent(SkinnedMeshComponent))
						{
							SkinnedMeshToRawMeshes(SkinnedMeshComponent, OverallMaxLODs, ComponentToWorld, PackageName, RawMeshTrackers, RawMeshes, Materials);
						}
						else if (false)//(IsValidStaticMeshComponent(StaticMeshComponent))
						{
							//StaticMeshToRawMeshes(StaticMeshComponent, OverallMaxLODs, ComponentToWorld, PackageName, RawMeshTrackers, RawMeshes, Materials);
						}
					}

					uint32 MaxInUseTextureCoordinate = 0;

					// scrub invalid vert color & tex coord data
					check(RawMeshes.Num() == RawMeshTrackers.Num());
					for (int32 RawMeshIndex = 0; RawMeshIndex < RawMeshes.Num(); RawMeshIndex++)
					{
						if (!RawMeshTrackers[RawMeshIndex].bValidColors)
						{
							RawMeshes[RawMeshIndex].WedgeColors.Empty();
						}

						for (uint32 TexCoordIndex = 0; TexCoordIndex < MAX_MESH_TEXTURE_COORDS; TexCoordIndex++)
						{
							if (!RawMeshTrackers[RawMeshIndex].bValidTexCoords[TexCoordIndex])
							{
								RawMeshes[RawMeshIndex].WedgeTexCoords[TexCoordIndex].Empty();
							}
							else
							{
								// Store first texture coordinate index not in use
								MaxInUseTextureCoordinate = FMath::Max(MaxInUseTextureCoordinate, TexCoordIndex);
							}
						}
					}

					// Check if we got some valid data.
					bool bValidData = false;
					for (FRawMesh& RawMesh : RawMeshes)
					{
						if (RawMesh.IsValidOrFixable())
						{
							bValidData = true;
							break;
						}
					}

					if (bValidData)
					{
						// Then find/create it.
						UPackage* Package = CreatePackage(*PackageName);
						check(Package);

						// Create StaticMesh object
						StaticMesh = NewObject<UStaticMesh>(Package, *MeshName, RF_Public | RF_Standalone);
						StaticMesh->InitResources();

						StaticMesh->SetLightingGuid(FGuid::NewGuid());

						// Determine which texture coordinate map should be used for storing/generating the lightmap UVs
						const uint32 LightMapIndex = FMath::Min(MaxInUseTextureCoordinate + 1, (uint32)MAX_MESH_TEXTURE_COORDS - 1);

						// Add source to new StaticMesh
						for (FRawMesh& RawMesh : RawMeshes)
						{
							if (RawMesh.IsValidOrFixable())
							{
								FStaticMeshSourceModel& SrcModel = StaticMesh->AddSourceModel();
								SrcModel.BuildSettings.bRecomputeNormals = false;
								SrcModel.BuildSettings.bRecomputeTangents = false;
								SrcModel.BuildSettings.bRemoveDegenerates = true;
								SrcModel.BuildSettings.bUseHighPrecisionTangentBasis = false;
								SrcModel.BuildSettings.bUseFullPrecisionUVs = false;
								SrcModel.BuildSettings.bGenerateLightmapUVs = true;
								SrcModel.BuildSettings.SrcLightmapIndex = 0;
								SrcModel.BuildSettings.DstLightmapIndex = LightMapIndex;
								SrcModel.SaveRawMesh(RawMesh);
							}
						}

						// Copy materials to new mesh 
						for (UMaterialInterface* Material : Materials)
						{
							StaticMesh->GetStaticMaterials().Add(FStaticMaterial(Material));
						}

						//Set the Imported version before calling the build
						StaticMesh->ImportVersion = EImportStaticMeshVersion::LastVersion;

						// Set light map coordinate index to match DstLightmapIndex
						StaticMesh->SetLightMapCoordinateIndex(LightMapIndex);

						// setup section info map
						for (int32 RawMeshLODIndex = 0; RawMeshLODIndex < RawMeshes.Num(); RawMeshLODIndex++)
						{
							const FRawMesh& RawMesh = RawMeshes[RawMeshLODIndex];
							TArray<int32> UniqueMaterialIndices;
							for (int32 MaterialIndex : RawMesh.FaceMaterialIndices)
							{
								UniqueMaterialIndices.AddUnique(MaterialIndex);
							}

							int32 SectionIndex = 0;
							for (int32 UniqueMaterialIndex : UniqueMaterialIndices)
							{
								StaticMesh->GetSectionInfoMap().Set(RawMeshLODIndex, SectionIndex, FMeshSectionInfo(UniqueMaterialIndex));
								SectionIndex++;
							}
						}
						StaticMesh->GetOriginalSectionInfoMap().CopyFrom(StaticMesh->GetSectionInfoMap());

						// Build mesh from source
						StaticMesh->Build(false);
						StaticMesh->PostEditChange();

						StaticMesh->MarkPackageDirty();

						// Notify asset registry of new asset
						FAssetRegistryModule::AssetCreated(StaticMesh);

						// Display notification so users can quickly access the mesh
						/*
						if (GIsEditor)
						{
							FNotificationInfo Info(FText::Format(LOCTEXT("SkeletalMeshConverted", "Successfully Converted Mesh"), FText::FromString(StaticMesh->GetName())));
							Info.ExpireDuration = 8.0f;
							Info.bUseLargeFont = false;
							Info.Hyperlink = FSimpleDelegate::CreateLambda([=]() { GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAssets(TArray<UObject*>({ StaticMesh })); });
							Info.HyperlinkText = FText::Format(LOCTEXT("OpenNewAnimationHyperlink", "Open {0}"), FText::FromString(StaticMesh->GetName()));
							TSharedPtr<SNotificationItem> Notification = FSlateNotificationManager::Get().AddNotification(Info);
							if (Notification.IsValid())
							{
								Notification->SetCompletionState(SNotificationItem::CS_Success);
							}
						}
						*/
					}
				}

				return StaticMesh;
			}

			void FUtility::VATUVsToStaticMeshLODs(UStaticMesh* StaticMesh, const int32 UVChannel, const TArray<TArray<FVector2f>>& UVs)
			{
				typedef NCsMath::FLibrary MathLibrary;

				for (int32 LOD = 0; LOD < StaticMesh->GetNumLODs(); LOD++)
				{
					const uint32 PaintingMeshLODIndex = LOD;

					if (StaticMesh->IsSourceModelValid(PaintingMeshLODIndex))
					{
						if (StaticMesh->GetSourceModel(PaintingMeshLODIndex).IsRawMeshEmpty() == false)
						{
							const uint32 NumUVChannels = StaticMesh->GetNumUVChannels(PaintingMeshLODIndex);
							// Extract the raw mesh.
							FRawMesh Mesh;
							StaticMesh->GetSourceModel(PaintingMeshLODIndex).LoadRawMesh(Mesh);

							// Build a mapping of vertex positions to vertex colors.
							for (int32 WedgeIndex = 0; WedgeIndex < Mesh.WedgeIndices.Num(); ++WedgeIndex)
							{
								int32 VertID	   = Mesh.WedgeIndices[WedgeIndex];
								FVector3d Position = MathLibrary::Convert(Mesh.VertexPositions[VertID]);

								for (uint32 TexCoordIndex = 0; TexCoordIndex < MAX_MESH_TEXTURE_COORDS; TexCoordIndex++)
								{
									if (TexCoordIndex <= NumUVChannels)//(!RawMeshTrackers[RawMeshIndex].bValidTexCoords[TexCoordIndex])
									{
										if ((TexCoordIndex == UVChannel))
										{
											// Mesh.WedgeTexCoords[TexCoordIndex].Empty();
											if (Mesh.WedgeTexCoords[TexCoordIndex].Num() != Mesh.WedgeIndices.Num())
												Mesh.WedgeTexCoords[TexCoordIndex].SetNum(Mesh.WedgeIndices.Num());

											Mesh.WedgeTexCoords[TexCoordIndex][WedgeIndex] = UVs[PaintingMeshLODIndex][VertID];
										}
										else if(TexCoordIndex >= NumUVChannels)
										{
											Mesh.WedgeTexCoords[TexCoordIndex].Empty();
										}
									}
									else
									{
										Mesh.WedgeTexCoords[TexCoordIndex].Empty();
									}
								}
							}

							// Determine which texture coordinate map should be used for storing/generating the lightmap UVs
							const uint32 LightMapIndex = FMath::Min(UVChannel == NumUVChannels ? NumUVChannels + 1 : NumUVChannels, (uint32)MAX_MESH_TEXTURE_COORDS - 1);
							StaticMesh->GetSourceModel(PaintingMeshLODIndex).BuildSettings.DstLightmapIndex = LightMapIndex;

							// Save the new raw mesh.
							StaticMesh->GetSourceModel(PaintingMeshLODIndex).SaveRawMesh(Mesh);


							StaticMesh->ImportVersion = EImportStaticMeshVersion::LastVersion;
							// Set light map coordinate index to match DstLightmapIndex
							StaticMesh->SetLightMapCoordinateIndex(LightMapIndex);
			

						}
					}
				}

				// Build mesh from source
				StaticMesh->Build(false);
				StaticMesh->PostEditChange();
				StaticMesh->MarkPackageDirty();
			}

			void FUtility::VATColorsToStaticMeshLODs(UStaticMesh* StaticMesh, const TArray<TArray<FColor>>& Colors)
			{
				for (int32 LOD = 0; LOD < StaticMesh->GetNumLODs(); LOD++)
				{
					const uint32 PaintingMeshLODIndex = LOD;

					if (StaticMesh->IsSourceModelValid(PaintingMeshLODIndex))
					{
						if (StaticMesh->GetSourceModel(PaintingMeshLODIndex).IsRawMeshEmpty() == false)
						{
							const uint32 NumUVChannels = StaticMesh->GetNumUVChannels(PaintingMeshLODIndex);
							// Extract the raw mesh.
							FRawMesh Mesh;
							StaticMesh->GetSourceModel(PaintingMeshLODIndex).LoadRawMesh(Mesh);

							// Reserve space for the new vertex colors.
							if (Mesh.WedgeColors.Num() == 0 || Mesh.WedgeColors.Num() != Mesh.WedgeIndices.Num())
							{
								Mesh.WedgeColors.Empty(Mesh.WedgeIndices.Num());
								Mesh.WedgeColors.AddUninitialized(Mesh.WedgeIndices.Num());
							}

							// Build a mapping of vertex positions to vertex colors.
							for (int32 WedgeIndex = 0; WedgeIndex < Mesh.WedgeIndices.Num(); ++WedgeIndex)
							{
								int32 VertID = Mesh.WedgeIndices[WedgeIndex];
								FVector3f Position = Mesh.VertexPositions[VertID];
								Mesh.WedgeColors[WedgeIndex] = Colors[PaintingMeshLODIndex][VertID];
							}

							// Save the new raw mesh.
							StaticMesh->GetSourceModel(PaintingMeshLODIndex).SaveRawMesh(Mesh);
							StaticMesh->ImportVersion = EImportStaticMeshVersion::LastVersion;
						}
					}
				}

				// Build mesh from source
				StaticMesh->Build(false);
				StaticMesh->PostEditChange();
				StaticMesh->MarkPackageDirty();
			}
		}
	}
}

#endif // #if WITH_EDITOR