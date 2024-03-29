// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsStaticMeshComponentInfo.h"

// Types
#include "Types/CsTypes_Math.h"
// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Component
#include "Components/StaticMeshComponent.h"

#define InfoType NCsStaticMesh::NComponent::FInfo

void FCsStaticMeshComponentInfo::CopyToInfo(InfoType* Info)
{
	CS_COPY_PTR_TO_PROXY(Info, Mesh);
	CS_COPY_PTR_TO_PROXY(Info, Materials);
	Info->SetAttachmentTransformRules(AttachmentTransformRules.ToRule());
	CS_COPY_TO_PROXY(Info, Bone);
	CS_COPY_TO_PROXY(Info, TransformRules);
	CS_COPY_TO_PROXY(Info, Transform);
	CS_COPY_TO_PROXY(Info, bCastShadow);
	CS_COPY_TO_PROXY(Info, bReceivesDecals);
	CS_COPY_TO_PROXY(Info, bUseAsOccluder);
	CS_COPY_TO_PROXY(Info, bRenderCustomDepth);
	CS_COPY_TO_PROXY(Info, CustomDepthStencilValue);
}

void FCsStaticMeshComponentInfo::CopyToInfoAsValue(InfoType* Info) const
{
	CS_COPY_PTR_TO_PROXY_AS_VALUE(Info, Mesh);
	CS_COPY_PTR_TO_PROXY_AS_VALUE(Info, Materials);
	Info->SetAttachmentTransformRules(AttachmentTransformRules.ToRule());
	CS_COPY_TO_PROXY_AS_VALUE(Info, Bone);
	CS_COPY_TO_PROXY_AS_VALUE(Info, TransformRules);
	CS_COPY_TO_PROXY_AS_VALUE(Info, Transform);
	CS_COPY_TO_PROXY_AS_VALUE(Info, bCastShadow);
	CS_COPY_TO_PROXY_AS_VALUE(Info, bReceivesDecals);
	CS_COPY_TO_PROXY_AS_VALUE(Info, bUseAsOccluder);
	CS_COPY_TO_PROXY_AS_VALUE(Info, bRenderCustomDepth);
	CS_COPY_TO_PROXY_AS_VALUE(Info, CustomDepthStencilValue);
}

#undef InfoType

bool FCsStaticMeshComponentInfo::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid.
	CS_IS_VALID_CHECKED(Mesh);
	// Check Materials is Valid
	CS_IS_VALID_CHECKED(Materials);

	if (Materials.Materials.Num() > CS_EMPTY)
	{
		typedef NCsMaterial::FLibrary MaterialLibrary;

		check(MaterialLibrary::IsValidChecked(Context, Mesh.Get(), Materials.Get()));
	}

	if (!Transform.Equals(FTransform3f::Identity))
	{
		checkf(TransformRules != 0, TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString()));
	}
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(CustomDepthStencilValue, 0)
	CS_IS_INT_LESS_THAN_OR_EQUAL_CHECKED(CustomDepthStencilValue, 255)
	return true;
}

bool FCsStaticMeshComponentInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Mesh is Valid.
	CS_IS_VALID(Mesh)
	// Check Materials is Valid
	CS_IS_VALID(Materials)

	if (Materials.Materials.Num() > CS_EMPTY)
	{
		typedef NCsMaterial::FLibrary MaterialLibrary;

		if (!MaterialLibrary::IsValid(Context, Mesh.Get(), Materials.Get(), Log))
			return false;
	}

	if (!Transform.Equals(FTransform3f::Identity))
	{
		if (TransformRules == 0)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString())));
			return true;
		}
	}
	CS_IS_INT_GREATER_THAN_OR_EQUAL(CustomDepthStencilValue, 0)
	CS_IS_INT_LESS_THAN_OR_EQUAL(CustomDepthStencilValue, 255)
	return true;
}

namespace NCsStaticMesh
{
	namespace NComponent
	{
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			// Check Mesh is Valid.
			CS_IS_PTR_NULL_CHECKED(GetMesh())
			// Check Materials is Valid
			CS_IS_TARRAY_EMPTY_CHECKED(GetMaterials(), UMaterialInterface*)
			CS_IS_TARRAY_ANY_NULL_CHECKED(GetMaterials(), UMaterialInterface)

			if (GetMaterials().Num() > CS_EMPTY)
			{
				typedef NCsMaterial::FLibrary MaterialLibrary;

				check(MaterialLibrary::IsValidChecked(Context, GetMesh(), GetMaterials()));
			}

			if (!GetTransform().Equals(FTransform3f::Identity))
			{
				checkf(GetTransformRules() != 0, TEXT("%s: No TransformRules set for GetTransform(): %s."), *Context, *(GetTransform().ToString()));
			}
			CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetCustomDepthStencilValue(), 0)
			CS_IS_INT_LESS_THAN_OR_EQUAL_CHECKED(GetCustomDepthStencilValue(), 255)
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			// Check Mesh is Valid.
			CS_IS_PTR_NULL(GetMesh())
			// Check Materials is Valid
			CS_IS_TARRAY_EMPTY(GetMaterials(), UMaterialInterface*)
			CS_IS_TARRAY_ANY_NULL(GetMaterials(), UMaterialInterface)

			if (GetMaterials().Num() > CS_EMPTY)
			{
				typedef NCsMaterial::FLibrary MaterialLibrary;

				if (!MaterialLibrary::IsValid(Context, GetMesh(), GetMaterials(), Log))
					return false;
			}

			if (!GetTransform().Equals(FTransform3f::Identity))
			{
				if (GetTransformRules() == 0)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No TransformRules set for GetTransform(): %s."), *Context, *(GetTransform().ToString())));
					return true;
				}
			}
			CS_IS_INT_GREATER_THAN_OR_EQUAL(GetCustomDepthStencilValue(), 0)
			CS_IS_INT_LESS_THAN_OR_EQUAL(GetCustomDepthStencilValue(), 255)
			return true;
		}

		void FInfo::SetChecked(const FString& Context, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs) const
		{
			CS_IS_PTR_NULL_CHECKED(Component)
			Component->SetStaticMesh(GetMesh()); 

			typedef NCsMaterial::NMID::FLibrary MIDLibrary;

			MIDLibrary::SetChecked(Context, Component, GetMaterials(), OutMIDs);
			NCsTransformRules::SetRelativeTransform(Component, GetTransform(), GetTransformRules());
		}
	}
}