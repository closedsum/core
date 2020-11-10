// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/CsLibrary_Data_Skin_Visual.h"

// Library
#include "Library/CsLibrary_Material.h"
// Data
#include "Skin/Data/Visual/CsData_Skin_VisualStaticMesh.h"
#include "Skin/Data/Visual/CsData_Skin_VisualSkeletalMesh.h"
#include "Skin/Data/Visual/CsData_Skin_VisualMaterial.h"

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
		#define SkinType NCsSkin::NData::NVisual::IVisual

		// Static Mesh
		#pragma region

			void FLibrary::SetStaticMeshAndMaterials(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component)
			{
				SetStaticMesh(Context, Skin, Component);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MaterialLibrary::SetMaterialsChecked(Context, Component, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeStaticMeshAndMaterials(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMesh(Context, StaticMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::FLibrary MaterialLibrary;

					if (MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
					{
						MaterialLibrary::SetMaterialsChecked(Context, Component, MaterialSkin->GetMaterials());
					}
				}
			}

			void FLibrary::SetStaticMeshAndMIDs(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				SetStaticMesh(Context, Skin, Component);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MaterialLibrary::SetMIDsChecked(Context, Component, MIDs, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeStaticMeshAndMIDs(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMesh(Context, StaticMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::FLibrary MaterialLibrary;

					if (MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
					{
						MaterialLibrary::SetMIDsChecked(Context, Component, MIDs, MaterialSkin->GetMaterials());
					}
				}
			}

			void FLibrary::SetStaticMesh(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				StaticMeshSkinType* StaticMeshSkin = GetInterfaceChecked<StaticMeshSkinType>(Context, Skin);

				SetStaticMesh(Context, StaticMeshSkin, Component);
			}

			#define StaticMeshSkinType NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh
			void FLibrary::SetStaticMesh(const FString& Context, StaticMeshSkinType* StaticMeshSkin, UStaticMeshComponent* Component)
			{
				checkf(StaticMeshSkin, TEXT("%s: StaticMeshSkin is NULL."), *Context);

				UStaticMesh* Mesh = StaticMeshSkin->GetStaticMesh();

				checkf(Mesh, TEXT("%s: Failed to get StaticMesh from Skin of type: %s."), *Context, *(StaticMeshSkinType::Name.ToString()));

				checkf(Component, TEXT("%s: Component is NULL."), *Context);

				Component->SetStaticMesh(Mesh);
			}
			#undef StaticMeshSkinType

			void FLibrary::SetSafeStaticMesh(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMesh(Context, StaticMeshSkin, Component);
				}
			}

		#pragma endregion Static Mesh

		// Skeletal Mesh
		#pragma region

			void FLibrary::SetSkeletalMeshAndMaterials(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component)
			{	
				SetSkeletalMesh(Context, Skin, Component);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MaterialLibrary::SetMaterialsChecked(Context, Component, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeSkeletalMeshAndMaterials(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					SetSkeletalMesh(Context, SkeletalMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::FLibrary MaterialLibrary;

					if (MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
					{
						MaterialLibrary::SetMaterialsChecked(Context, Component, MaterialSkin->GetMaterials());
					}
				}
			}

			void FLibrary::SetSkeletalMesh(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				SkeletalMeshSkinType* SkeletalMeshSkin = GetInterfaceChecked<SkeletalMeshSkinType>(Context, Skin);

				SetSkeletalMesh(Context, SkeletalMeshSkin, Component);
			}

			#define SkeletalMeshSkinType NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh
			void FLibrary::SetSkeletalMesh(const FString& Context, SkeletalMeshSkinType* SkeletalMeshSkin, USkeletalMeshComponent* Component)
			{
				checkf(SkeletalMeshSkin, TEXT("%s: SkeletalMeshSkin is nULL."));

				USkeletalMesh* Mesh = SkeletalMeshSkin->GetSkeletalMesh();

				checkf(Mesh, TEXT("%s: Failed to get SkeletalMesh from Skin of type: %s."), *Context, *(SkeletalMeshSkinType::Name.ToString()));

				checkf(Component, TEXT("%s: Component is NULL."), *Context);

				Component->SetSkeletalMesh(Mesh);
			}
			#undef SkeletalMeshSkinType

			void FLibrary::SetSafeSkeletalMesh(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					SetSkeletalMesh(Context, SkeletalMeshSkin, Component);
				}
			}

		#pragma endregion Skeletal Mesh

		#undef SkinType
		}
	}
}