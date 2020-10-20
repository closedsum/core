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
		// Static Mesh
		#pragma region

			void FLibrary::SetStaticMeshAndMaterials(const FString& Context, IVisual* Skin, UStaticMeshComponent* Component)
			{
				checkf(Skin, TEXT("%s: Skin is NULL."), *Context);

				checkf(Component, TEXT("%s: Component is NULL."), *Context);

				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				StaticMeshSkinType* StaticMeshSkin = GetInterfaceChecked<StaticMeshSkinType>(Context, Skin);

				UStaticMesh* Mesh = StaticMeshSkin->GetStaticMesh();

				checkf(Mesh, TEXT("%s: Failed to get StaticMesh from Skin of type: %s."), *Context, *(StaticMeshSkinType::Name.ToString()));

				Component->SetStaticMesh(Mesh);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;

				MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				FCsLibrary_Material::SetMaterialsChecked(Context, Component, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeStaticMeshAndMaterials(const FString& Context, IVisual* Skin, UStaticMeshComponent* Component)
			{
				checkf(Skin, TEXT("%s: Skin is NULL."), *Context);

				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					UStaticMesh* Mesh = StaticMeshSkin->GetStaticMesh();

					checkf(Mesh, TEXT("%s: Failed to get StaticMesh from Skin of type: %s."), *Context, *(StaticMeshSkinType::Name.ToString()));

					checkf(Component, TEXT("%s: Component is NULL."), *Context);

					Component->SetStaticMesh(Mesh);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;

					if (MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
					{
						FCsLibrary_Material::SetMaterialsChecked(Context, Component, MaterialSkin->GetMaterials());
					}
				}
			}

			void FLibrary::SetStaticMesh(const FString& Context, IVisual* Skin, UStaticMeshComponent* Component)
			{
				checkf(Skin, TEXT("%s: Skin is NULL."), *Context);

				checkf(Component, TEXT("%s: Component is NULL."), *Context);

				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				StaticMeshSkinType* StaticMeshSkin = GetInterfaceChecked<StaticMeshSkinType>(Context, Skin);

				UStaticMesh* Mesh = StaticMeshSkin->GetStaticMesh();

				checkf(Mesh, TEXT("%s: Failed to get StaticMesh from Skin of type: %s."), *Context, *(StaticMeshSkinType::Name.ToString()));

				Component->SetStaticMesh(Mesh);
			}

			void FLibrary::SetSafeStaticMesh(const FString& Context, IVisual* Skin, UStaticMeshComponent* Component)
			{
				checkf(Skin, TEXT("%s: Skin is NULL"));

				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					UStaticMesh* Mesh = StaticMeshSkin->GetStaticMesh();

					checkf(Mesh, TEXT("%s: Failed to get StaticMesh from Skin of type: %s."), *Context, *(StaticMeshSkinType::Name.ToString()));

					checkf(Component, TEXT("%s: Component is NULL."), *Context);

					Component->SetStaticMesh(Mesh);
				}
			}

		#pragma endregion Static Mesh

		// Skeletal Mesh
		#pragma region

			void FLibrary::SetSkeletalMeshAndMaterials(const FString& Context, IVisual* Skin, USkeletalMeshComponent* Component)
			{
				checkf(Skin, TEXT("%s: Skin is NULL."), *Context);

				checkf(Component, TEXT("%s: Component is NULL."), *Context);

				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				SkeletalMeshSkinType* SkeletalMeshSkin = GetInterfaceChecked<SkeletalMeshSkinType>(Context, Skin);

				USkeletalMesh* Mesh = SkeletalMeshSkin->GetSkeletalMesh();

				checkf(Mesh, TEXT("%s: Failed to get StaticMesh from Skin of type: %s."), *Context, *(SkeletalMeshSkinType::Name.ToString()));

				Component->SetSkeletalMesh(Mesh);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;

				MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				FCsLibrary_Material::SetMaterialsChecked(Context, Component, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeSkeletalMeshAndMaterials(const FString& Context, IVisual* Skin, USkeletalMeshComponent* Component)
			{
				checkf(Skin, TEXT("%s: Skin is NULL."), *Context);

				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					USkeletalMesh* Mesh = SkeletalMeshSkin->GetSkeletalMesh();

					checkf(Mesh, TEXT("%s: Failed to get SkeletalMesh from Skin of type: %s."), *Context, *(SkeletalMeshSkinType::Name.ToString()));

					checkf(Component, TEXT("%s: Component is NULL."), *Context);

					Component->SetSkeletalMesh(Mesh);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;

					if (MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
					{
						FCsLibrary_Material::SetMaterialsChecked(Context, Component, MaterialSkin->GetMaterials());
					}
				}
			}

			void FLibrary::SetSkeletalMesh(const FString& Context, IVisual* Skin, USkeletalMeshComponent* Component)
			{
				checkf(Skin, TEXT("%s: Skin is NULL."), *Context);

				checkf(Component, TEXT("%s: Component is NULL."), *Context);

				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				SkeletalMeshSkinType* SkeletalMeshSkin = GetInterfaceChecked<SkeletalMeshSkinType>(Context, Skin);

				USkeletalMesh* Mesh = SkeletalMeshSkin->GetSkeletalMesh();

				checkf(Mesh, TEXT("%s: Failed to get SkeletalMesh from Skin of type: %s."), *Context, *(SkeletalMeshSkinType::Name.ToString()));

				Component->SetSkeletalMesh(Mesh);
			}

			void FLibrary::SetSafeSkeletalMesh(const FString& Context, IVisual* Skin, USkeletalMeshComponent* Component)
			{
				checkf(Skin, TEXT("%s: Skin is NULL"));

				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					USkeletalMesh* Mesh = SkeletalMeshSkin->GetSkeletalMesh();

					checkf(Mesh, TEXT("%s: Failed to get SkeletalMesh from Skin of type: %s."), *Context, *(SkeletalMeshSkinType::Name.ToString()));

					checkf(Component, TEXT("%s: Component is NULL."), *Context);

					Component->SetSkeletalMesh(Mesh);
				}
			}

		#pragma endregion Skeletal Mesh
		}
	}
}