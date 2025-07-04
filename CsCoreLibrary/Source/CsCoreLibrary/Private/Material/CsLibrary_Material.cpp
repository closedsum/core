// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Material/CsLibrary_Material.h"

// Types
#include "CsMacro_Misc.h"
	// Common
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Material/CsLibrary_Material_Parameter.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Array.h"
#include "Library/CsLibrary_Valid.h"
// Mesh
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Material
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Runtime/Engine/Private/Materials/MaterialInstanceSupport.h" // TODO: NOTE: Test Batch Updating Material's Params

namespace NCsMaterial
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::FLibrary, SetSafe);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::FLibrary, Set);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::FLibrary, ClearOverride);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::FLibrary, IsScalarParameterValid);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::FLibrary, IsVectorParameterValid);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::FLibrary, IsTextureParameterValid);
			}
		}
	}

	#define USING_NS_CACHED using namespace NCsMaterial::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsMaterial::NLibrary::NCached; \
		const FString& Context = Str::__FunctionName
	#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/

	// Load
	#pragma region

	UMaterialInterface* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel)
	{
		return CsObjectLibrary::SafeLoad<UMaterialInterface>(Context, Path, Log);
	}

	UMaterialInterface* FLibrary::SafeLoad(const FString& Context, const FString& Path, LogLevel)
	{
		return CsObjectLibrary::SafeLoad<UMaterialInterface>(Context, Path, Log);
	}

	bool FLibrary::SafeLoad(const FString& Context, const TArray<FString>& Paths, TArray<UMaterialInterface*>& OutMaterials, LogLevel)
	{
		OutMaterials.Reset(Paths.Num());

		bool Success = true;

		for (const FString& Path : Paths)
		{
			UMaterialInterface* Material = OutMaterials.Add_GetRef(SafeLoad(Context, Path, Log));

			Success &= Material != nullptr;
		}
		return Success;
	}

	#pragma endregion Load

	// Get
	#pragma region
	
	UMaterialInterface* FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, LogLevel)
	{
		return CsPropertyLibrary::GetObjectPropertyValueByPath<UMaterialInterface>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
	}

	bool FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, FString& OutPath, bool& OutSuccess, LogLevel)
	{
		FSoftObjectPtr SoftObjectPtr = CsPropertyLibrary::GetSoftObjectPropertyValueByPath<UMaterialInterface>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
		OutPath					     = SoftObjectPtr.ToString();

		return OutSuccess;
	}

	bool FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, TArray<TSoftObjectPtr<UMaterialInterface>>& OutArray, bool& OutSuccess, LogLevel)
	{
		return CsPropertyLibrary::GetArraySoftObjectPropertyValueByPath<UMaterialInterface>(Context, Object, Object->GetClass(), Path, OutArray, OutSuccess, Log);
	}

	bool FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, TArray<FString>& OutArray, bool& OutSuccess, LogLevel)
	{
		return CsPropertyLibrary::GetArraySoftObjectPropertyValueAsStringByPath<UMaterialInterface>(Context, Object, Object->GetClass(), Path, OutArray, OutSuccess, Log);
	}

	bool FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, TArray<UMaterialInterface*>& OutArray, bool& OutSuccess, LogLevel)
	{
		return CsPropertyLibrary::GetArrayObjectPropertyValueByPath<UMaterialInterface>(Context, Object, Object->GetClass(), Path, OutArray, OutSuccess, Log);
	}

	#pragma endregion Get

	// Valid
	#pragma region

	bool FLibrary::IsValidChecked(const FString& Context, const TArray<UMaterialInterface*>& Materials)
	{
		// Check Materials is Valid
		CS_IS_TARRAY_EMPTY_CHECKED(Materials, UMaterialInterface*)

		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			checkf(Materials[I], TEXT("%s: Materials[%d] is NULL."), *Context, I);
		}
		return true;
	}

	bool FLibrary::IsValid(const FString& Context, const TArray<UMaterialInterface*>& Materials, LogLevel)
	{
		// Check Materials is Valid
		CS_IS_TARRAY_EMPTY(Materials, UMaterialInterface*)

		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (!Materials[I])
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Materials[%d] is NULL."), *Context, I));
				return false;
			}
		}
		return true;
	}

	bool FLibrary::IsValidChecked(const FString& Context, UStaticMesh* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		// Check Mesh is Valid
		CS_IS_PTR_NULL_CHECKED(Mesh)

		const int32 Count		 = Mesh->GetStaticMaterials().Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *(Mesh->GetName()), Count, MaterialCount);

		check(IsValidChecked(Context, Materials));

		return true;
	}

	bool FLibrary::IsValid(const FString& Context, UStaticMesh* Mesh, const TArray<UMaterialInterface*>& Materials, LogLevel)
	{
		// Check Mesh is Valid
		CS_IS_PTR_NULL(Mesh)

		const int32 Count		  = Mesh->GetStaticMaterials().Num();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *(Mesh->GetName()), Count, MaterialCount));
			return false;
		}

		if (!IsValid(Context, Materials, Log))
			return false;
		return true;
	}

	bool FLibrary::IsValidChecked(const FString& Context, USkeletalMesh* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		// Check Mesh is Valid
		CS_IS_PTR_NULL_CHECKED(Mesh)

		const int32 Count		  = Mesh->GetMaterials().Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *(Mesh->GetName()), Count, MaterialCount);

		check(IsValidChecked(Context, Materials));

		return true;
	}

	bool FLibrary::IsValid(const FString& Context, USkeletalMesh* Mesh, const TArray<UMaterialInterface*>& Materials, LogLevel)
	{
		// Check Mesh is Valid
		CS_IS_PTR_NULL(Mesh)

		const int32 Count		  = Mesh->GetMaterials().Num();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *(Mesh->GetName()), Count, MaterialCount));
			return false;
		}

		if (!IsValid(Context, Materials, Log))
			return false;
		return true;
	}

	bool FLibrary::IsValidChecked(const FString& Context, USkeletalMesh* Mesh, const int32& Index)
	{
		CS_IS_PTR_NULL_CHECKED(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)

		checkf(Index < Mesh->GetMaterials().Num(), TEXT("%s: Index: %d is GREATER THAN the number of Materials (%d) for Mesh: %s."), *Context, Index, Mesh->GetMaterials().Num(), *(Mesh->GetName()));

		return true;
	}

	bool FLibrary::IsValidChecked(const FString& Context, UStaticMesh* Mesh, const int32& Index)
	{
		CS_IS_PTR_NULL_CHECKED(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)

		checkf(Index < Mesh->GetStaticMaterials().Num(), TEXT("%s: Index: %d is GREATER THAN the number of Materials (%d) for Mesh: %s."), *Context, Index, Mesh->GetStaticMaterials().Num(), *(Mesh->GetName()));
		return true;
	}

	bool FLibrary::IsValidChecked(const FString& Context, UPrimitiveComponent* Mesh, const int32& Index)
	{
		CS_IS_PENDING_KILL_CHECKED(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)

		checkf(Index < Mesh->GetNumMaterials(), TEXT("%s: Index: %d is GREATER THAN the number of Materials (%d) for Mesh: %s."), *Context, Index, Mesh->GetNumMaterials(), *(Mesh->GetName()));
		return true;
	}

	bool FLibrary::IsValid(const FString& Context, UPrimitiveComponent* Mesh, const int32& Index, LogLevel)
	{
		CS_IS_PENDING_KILL(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Index, 0)

		if (Index >= Mesh->GetNumMaterials())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Index: %d is GREATER THAN the number of Materials (%d) for Mesh: %s."), *Context, Index, Mesh->GetNumMaterials(), *(Mesh->GetName())));
			return false;
		}
		return true;
	}

	bool FLibrary::IsValidChecked_ArrayIndex(const FString& Context, UMaterialInterface* Material, const int32& Index)
	{
		checkf(CsObjectLibrary::IsValidObject(Material), TEXT("%s: Materials[%d] is NULL or Pending Kill."), *Context, Index);
		return true;
	}

	bool FLibrary::IsValid_ArrayIndex(const FString& Context, UMaterialInterface* Material, const int32& Index, LogLevel)
	{
		if (!CsObjectLibrary::IsValidObject(Material))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Materials[%d] is NULL or Pending Kill."), *Context, Index));
			return false;
		}
		return true;
	}

	#pragma endregion __Valid

	// Set
	#pragma region

	void FLibrary::SetChecked(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material)
	{
		// Check Component is Valid
		CS_IS_PENDING_KILL_CHECKED(Component)
		// Check Material is Valid
		CS_IS_PENDING_KILL_CHECKED(Material)

		const int32 Count = Component->GetNumMaterials();

		for (int32 I = 0; I < Count; ++I)
		{
			Component->SetMaterial(I, Material);
		}
	}

	bool FLibrary::SetSafe(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, LogLevel)
	{
		// Check Component is Valid
		CS_IS_PENDING_KILL(Component)
		// Check Material is Valid
		CS_IS_PENDING_KILL(Material)

		const int32 Count = Component->GetNumMaterials();

		for (int32 I = 0; I < Count; ++I)
		{
			Component->SetMaterial(I, Material);
		}
		return true;
	}

	void FLibrary::SetChecked(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index)
	{
		// Check Component is Valid
		CS_IS_PENDING_KILL_CHECKED(Component)
		// Check Material is Valid
		CS_IS_PENDING_KILL_CHECKED(Material)
		// Check Index is Valid
		CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)

		checkf(Index < Component->GetNumMaterials(), TEXT("%s: Index: %d is NOT Valid for Component: %s with %d Material Slots."), *Context, Index, *(Component->GetName()), Component->GetNumMaterials());

		Component->SetMaterial(Index, Material);
	}

	bool FLibrary::SetSafe(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index, LogLevel)
	{
		// Check Component is Valid
		CS_IS_PENDING_KILL(Component)
		// Check Material is Valid
		CS_IS_PENDING_KILL(Material)
		// Check Index is Valid
		CS_IS_INT_GREATER_THAN_OR_EQUAL(Index, 0)

		if (Index >= Component->GetNumMaterials())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Index: %d is NOT Valid for Component: %s with %d Material Slots."), *Context, Index, *(Component->GetName()), Component->GetNumMaterials()));
			return false;
		}
		Component->SetMaterial(Index, Material);
		return true;
	}

	bool FLibrary::SetSafe(UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index)
	{
		SET_CONTEXT(SetSafe);

		return SetSafe(Context, Component, Material, Index, nullptr);
	}

	void FLibrary::SetChecked(const FString& Context, UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials)
	{
		// Check Component is Valid
		CS_IS_PENDING_KILL_CHECKED(Component)

		const int32 Count		  = Component->GetNumMaterials();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Component (%s) material count (%d) != input material count (%d)"), *Context, *(Component->GetName()), Count, MaterialCount);

		ClearOverrideChecked(Context, Component);

		for (int32 I = 0; I < Count; ++I)
		{
			check(IsValidChecked_ArrayIndex(Context, Materials[I], I));

			Component->SetMaterial(I, Materials[I]);
		}
	}

	bool FLibrary::SetSafe(const FString& Context, UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials, LogLevel)
	{
		// Check Component is Valid
		CS_IS_PENDING_KILL(Component)

		const int32 Count		  = Component->GetNumMaterials();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mismatch between Component (%s) material count (%d) != input material count (%d)"), *Context, *(Component->GetName()), Count, MaterialCount));
			return false;
		}

		ClearOverrideChecked(Context, Component);

		for (int32 I = 0; I < Count; ++I)
		{
			if (!IsValid_ArrayIndex(Context, Materials[I], I, Log))
				return false;
			Component->SetMaterial(I, Materials[I]);
		}
		return true;
	}

	bool FLibrary::SetSafe(UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials)
	{
		SET_CONTEXT(SetSafe);

		return SetSafe(Context, Component, Materials, nullptr);
	}

	void FLibrary::SetChecked(const FString& Context, UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		// Check Mesh is Valid
		CS_IS_PENDING_KILL_CHECKED(Mesh)

		const int32 Count		  = Mesh->GetStaticMesh()->GetStaticMaterials().Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);

		ClearOverrideChecked(Context, Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			check(IsValidChecked_ArrayIndex(Context, Materials[Index], Index));

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::SetChecked(const FString& Context, UStaticMeshComponent* Mesh, const TArray<TObjectPtr<UMaterialInterface>>& Materials)
	{
		// Check Mesh is Valid
		CS_IS_PENDING_KILL_CHECKED(Mesh)

		const int32 Count		  = Mesh->GetStaticMesh()->GetStaticMaterials().Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);

		ClearOverrideChecked(Context, Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			UMaterialInterface* Material = Materials[Index].Get();

			check(IsValidChecked_ArrayIndex(Context, Material, Index));

			Mesh->SetMaterial(Index, Material);
		}
	}

	void FLibrary::SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		// Check Mesh is Valid
		CS_IS_PENDING_KILL_CHECKED(Mesh)

		const int32 Count		  = Mesh->GetSkinnedAsset()->GetMaterials().Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->GetSkinnedAsset()->GetName(), Count, MaterialCount);

		ClearOverrideChecked(Context, Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			check(IsValidChecked_ArrayIndex(Context, Materials[Index], Index));

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, const TArray<TObjectPtr<UMaterialInterface>>& Materials)
	{
		// Check Mesh is Valid
		CS_IS_PENDING_KILL_CHECKED(Mesh)

		const int32 Count		  = Mesh->GetSkinnedAsset()->GetMaterials().Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->GetSkinnedAsset()->GetName(), Count, MaterialCount);

		ClearOverrideChecked(Context, Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			UMaterialInterface* Material = Materials[Index].Get();

			check(IsValidChecked_ArrayIndex(Context, Material, Index));

			Mesh->SetMaterial(Index, Material);
		}
	}

	#pragma endregion Set

	// Override
	#pragma region

	void FLibrary::ClearOverrideChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)
		
		if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Component))
		{
			ClearOverrideChecked(Context, Mesh, Index);
			return;
		}

		if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(Component))
		{
			ClearOverrideChecked(Context, Mesh, Index);
			return;
		}
		checkf(0, TEXT("%s: Component: %s with Class: %s is NOT of type: UStaticMeshComponent or USkeletalMeshComponent."), *Context, *(Component->GetName()), *(Component->GetClass()->GetName()));
	}

	bool FLibrary::SafeClearOverride(const FString& Context, UPrimitiveComponent* Component, const int32& Index, LogLevel)
	{
		CS_IS_PENDING_KILL(Component)
		
		if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Component))
		{
			return SafeClearOverride(Context, Mesh, Index, Log);
		}

		if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(Component))
		{
			return SafeClearOverride(Context, Mesh, Index, Log);
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Component: %s with Class: %s is NOT of type: UStaticMeshComponent or USkeletalMeshComponent."), *Context, *(Component->GetName()), *(Component->GetClass()->GetName())));
		return false;
	}

	void FLibrary::ClearOverrideChecked(const FString& Context, UPrimitiveComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Component))
		{
			ClearOverrideChecked(Context, Mesh);
			return;
		}

		if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(Component))
		{
			ClearOverrideChecked(Context, Mesh);
			return;
		}
		checkf(0, TEXT("%s: Component: %s with Class: %s is NOT of type: UStaticMeshComponent or USkeletalMeshComponent."), *Context, *(Component->GetName()), *(Component->GetClass()->GetName()));
	}

	bool FLibrary::SafeClearOverride(const FString& Context, UPrimitiveComponent* Component, LogLevel)
	{
		CS_IS_PENDING_KILL(Component)

		if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Component))
		{
			return SafeClearOverride(Context, Mesh, Log);
		}

		if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(Component))
		{
			return SafeClearOverride(Context, Mesh, Log);
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Component: %s with Class: %s is NOT of type: UStaticMeshComponent or USkeletalMeshComponent."), *Context, *(Component->GetName()), *(Component->GetClass()->GetName())));
		return false;
	}

	void FLibrary::ClearOverrideChecked(const FString& Context, UStaticMeshComponent* Mesh, const int32& Index)
	{
		CS_IS_PENDING_KILL_CHECKED(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		if (Index < Count)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(Index)))
			{
				CsObjectLibrary::SafeMarkAsGarbage(Context, Material, nullptr);
			}
			Mesh->OverrideMaterials.RemoveAt(Index, 1, EAllowShrinking::No);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
	}

	bool FLibrary::SafeClearOverride(const FString& Context, UStaticMeshComponent* Mesh, const int32& Index, LogLevel)
	{
		CS_IS_PENDING_KILL(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Index, 0)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		if (Index < Count)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(Index)))
			{
				CsObjectLibrary::SafeMarkAsGarbage(Context, Material, nullptr);
			}
			Mesh->OverrideMaterials.RemoveAt(Index, 1, EAllowShrinking::No);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
		return true;
	}

	void FLibrary::ClearOverrideChecked(const FString& Context, UStaticMeshComponent* Mesh)
	{
		CS_IS_PENDING_KILL_CHECKED(Mesh)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(I)))
			{
				CsObjectLibrary::SafeMarkAsGarbage(Context, Material, nullptr);
			}
			Mesh->OverrideMaterials.RemoveAt(I, 1, EAllowShrinking::No);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
	}

	bool FLibrary::SafeClearOverride(const FString& Context, UStaticMeshComponent* Mesh, LogLevel)
	{
		CS_IS_PENDING_KILL(Mesh)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(I)))
			{
				CsObjectLibrary::SafeMarkAsGarbage(Context, Material, nullptr);
			}
			Mesh->OverrideMaterials.RemoveAt(I, 1, EAllowShrinking::No);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
		return true;
	}

	void FLibrary::ClearOverrideChecked(const FString& Context, USkeletalMeshComponent* Mesh, const int32& Index)
	{
		CS_IS_PENDING_KILL_CHECKED(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		if (Index < Count)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(Index)))
			{
				CsObjectLibrary::SafeMarkAsGarbage(Context, Material, nullptr);
			}
			Mesh->OverrideMaterials.RemoveAt(Index, 1, EAllowShrinking::No);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
	}

	bool FLibrary::SafeClearOverride(const FString& Context, USkeletalMeshComponent* Mesh, const int32& Index, LogLevel)
	{
		CS_IS_PENDING_KILL(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Index, 0)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		if (Index < Count)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(Index)))
			{
				CsObjectLibrary::SafeMarkAsGarbage(Context, Material, nullptr);
			}
			Mesh->OverrideMaterials.RemoveAt(Index, 1, EAllowShrinking::No);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
		return true;
	}

	void FLibrary::ClearOverrideChecked(const FString& Context, USkeletalMeshComponent* Mesh)
	{
		CS_IS_PENDING_KILL_CHECKED(Mesh)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(I)))
			{
				CsObjectLibrary::SafeMarkAsGarbage(Context, Material, nullptr);
			}
			Mesh->OverrideMaterials.RemoveAt(I, 1, EAllowShrinking::No);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
	}

	bool FLibrary::SafeClearOverride(const FString& Context, USkeletalMeshComponent* Mesh, LogLevel)
	{
		CS_IS_PENDING_KILL(Mesh)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(I)))
			{
				CsObjectLibrary::SafeMarkAsGarbage(Context, Material, nullptr);
			}
			Mesh->OverrideMaterials.RemoveAt(I, 1, EAllowShrinking::No);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
		return true;
	}

	#pragma endregion Override

	// Scalar
	#pragma region

	bool FLibrary::IsScalarParameterValidChecked(const FString& Context, UMaterialInterface* Material, const FName& ParamName)
	{
		// Check Material is Valid
		CS_IS_PENDING_KILL_CHECKED(Material)
		// Check ParamName is Valid
		CS_IS_NAME_NONE_CHECKED(ParamName)

		typedef NCsMaterial::NParameter::FLibrary ParameterLibrary;

		// Material
		if (UMaterial* M = Cast<UMaterial>(Material))
		{
			static TArray<FMaterialParameterInfo> Infos;
			static TArray<FGuid> Ids;

			ParameterLibrary::GetAllScalarParameterInfoChecked(Context, M, Infos, Ids);

			for (const FMaterialParameterInfo& Info : Infos)
			{
				if (Info.Name == ParamName)
				{
					return true;
				}
			}
		}
		
		// MaterialInstance
		if (UMaterialInstance* MI = Cast<UMaterialInstance>(Material))
		{
			for (const FScalarParameterValue& Value : MI->ScalarParameterValues)
			{
				if (Value.ParameterInfo.Name == ParamName)
				{
					return true;
				}
			}

			// Check Parent

			// Material instance
			UMaterialInstance* MINST = Cast<UMaterialInstance>(MI->Parent);

			while (MINST)
			{
				for (const FScalarParameterValue& Value : MINST->ScalarParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}

				if (UMaterial* M = Cast<UMaterial>(MINST->Parent))
				{
					static TArray<FMaterialParameterInfo> Infos;
					static TArray<FGuid> Ids;

					ParameterLibrary::GetAllScalarParameterInfoChecked(Context, M, Infos, Ids);

					for (const FMaterialParameterInfo& Info : Infos)
					{
						if (Info.Name == ParamName)
						{
							return true;
						}
					}
					break;
				}
				MINST = Cast<UMaterialInstance>(MINST->Parent);
			}
			// Material
			if (UMaterial* M = Cast<UMaterial>(MI->Parent))
			{
				static TArray<FMaterialParameterInfo> Infos;
				static TArray<FGuid> Ids;

				ParameterLibrary::GetAllScalarParameterInfoChecked(Context, M, Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}
			}
		}
		checkf(0, TEXT("%s: Failed to find ParamName: %s in Material: %s."), *Context, *(ParamName.ToString()), *(Material->GetName()));
		return false;
	}

	bool FLibrary::IsScalarParameterValid(const FString& Context, UMaterialInterface* Material, const FName& ParamName, LogLevel)
	{
		// Check Material is Valid
		CS_IS_PENDING_KILL(Material)
		// Check ParamName is Valid
		CS_IS_NAME_NONE(ParamName)

		typedef NCsMaterial::NParameter::FLibrary ParameterLibrary;

		// Material
		if (UMaterial* M = Cast<UMaterial>(Material))
		{
			static TArray<FMaterialParameterInfo> Infos;
			static TArray<FGuid> Ids;

			ParameterLibrary::GetAllScalarParameterInfoChecked(Context, M, Infos, Ids);

			for (const FMaterialParameterInfo& Info : Infos)
			{
				if (Info.Name == ParamName)
				{
					return true;
				}
			}
		}

		// MaterialInstance
		if (UMaterialInstance* MI = Cast<UMaterialInstance>(Material))
		{
			for (const FScalarParameterValue& Value : MI->ScalarParameterValues)
			{
				if (Value.ParameterInfo.Name == ParamName)
				{
					return true;
				}
			}

			// Check Parent

			// Material instance
			UMaterialInstance* MINST = Cast<UMaterialInstance>(MI->Parent);

			while (MINST)
			{
				for (const FScalarParameterValue& Value : MINST->ScalarParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}

				if (UMaterial* M = Cast<UMaterial>(MINST->Parent))
				{
					static TArray<FMaterialParameterInfo> Infos;
					static TArray<FGuid> Ids;

					ParameterLibrary::GetAllScalarParameterInfoChecked(Context, M, Infos, Ids);

					for (const FMaterialParameterInfo& Info : Infos)
					{
						if (Info.Name == ParamName)
						{
							return true;
						}
					}
					break;
				}
				MINST = Cast<UMaterialInstance>(MINST->Parent);
			}
			// Material
			if (UMaterial* M = Cast<UMaterial>(MI->Parent))
			{
				static TArray<FMaterialParameterInfo> Infos;
				static TArray<FGuid> Ids;

				ParameterLibrary::GetAllScalarParameterInfoChecked(Context, M, Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find ParamName: %s in Material: %s."), *Context, *(ParamName.ToString()), *(Material->GetName())));
		return false;
	}

	bool FLibrary::IsScalarParameterValid(UMaterialInterface* Material, const FName& ParamName)
	{
		SET_CONTEXT(IsScalarParameterValid);

		return IsScalarParameterValid(Context, Material, ParamName, nullptr);
	}

	float FLibrary::GetScalarParameterValueChecked(const FString& Context, UMaterialInterface* Material, const FName& ParamName)
	{
		check(IsScalarParameterValidChecked(Context, Material, ParamName));

		FHashedMaterialParameterInfo ParameterInfo(ParamName, EMaterialParameterAssociation::GlobalParameter, INDEX_NONE);
	
		float Value;
		Material->GetScalarParameterValue(ParameterInfo, Value);
		return Value;
	}

	#pragma endregion Scalar

	// Vector
	#pragma region

	bool FLibrary::IsVectorParameterValidChecked(const FString& Context, UMaterialInterface* Material, const FName& ParamName)
	{
		// Check Material is Valid
		CS_IS_PENDING_KILL_CHECKED(Material)
		// Check ParamName is Valid
		CS_IS_NAME_NONE_CHECKED(ParamName)

		typedef NCsMaterial::NParameter::FLibrary ParameterLibrary;

		// Material
		if (UMaterial* M = Cast<UMaterial>(Material))
		{
			static TArray<FMaterialParameterInfo> Infos;
			static TArray<FGuid> Ids;

			ParameterLibrary::GetAllVectorParameterInfoChecked(Context, M, Infos, Ids);

			for (const FMaterialParameterInfo& Info : Infos)
			{
				if (Info.Name == ParamName)
				{
					return true;
				}
			}
		}

		// MaterialInstance
		if (UMaterialInstance* MI = Cast<UMaterialInstance>(Material))
		{
			for (const FVectorParameterValue& Value : MI->VectorParameterValues)
			{
				if (Value.ParameterInfo.Name == ParamName)
				{
					return true;
				}
			}

			// Check Parent

			// Material instance
			UMaterialInstance* MINST = Cast<UMaterialInstance>(MI->Parent);

			while (MINST)
			{
				for (const FVectorParameterValue& Value : MINST->VectorParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}

				if (UMaterial* M = Cast<UMaterial>(MINST->Parent))
				{
					static TArray<FMaterialParameterInfo> Infos;
					static TArray<FGuid> Ids;

					ParameterLibrary::GetAllVectorParameterInfoChecked(Context, M, Infos, Ids);

					for (const FMaterialParameterInfo& Info : Infos)
					{
						if (Info.Name == ParamName)
						{
							return true;
						}
					}
					break;
				}
				MINST = Cast<UMaterialInstance>(MINST->Parent);
			}
			// Material
			if (UMaterial* M = Cast<UMaterial>(MI->Parent))
			{
				static TArray<FMaterialParameterInfo> Infos;
				static TArray<FGuid> Ids;

				ParameterLibrary::GetAllVectorParameterInfoChecked(Context, M, Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}
			}
		}
		//checkf(0, TEXT("%s: Failed to find ParamName: %s in Material: %s with Parent: %s."), *Context, *(ParamName.ToString()), *(Material->GetName()));
		checkf(0, TEXT("%s: Failed to find ParamName: %s in Material: %s."), *Context, *(ParamName.ToString()), *(Material->GetName()));
		return false;
	}

	bool FLibrary::IsVectorParameterValid(const FString& Context, UMaterialInterface* Material, const FName& ParamName, LogLevel)
	{
		// Check Material is Valid
		CS_IS_PENDING_KILL(Material)
		// Check ParamName is Valid
		CS_IS_NAME_NONE(ParamName)

		typedef NCsMaterial::NParameter::FLibrary ParameterLibrary;

		// Material
		if (UMaterial* M = Cast<UMaterial>(Material))
		{
			static TArray<FMaterialParameterInfo> Infos;
			static TArray<FGuid> Ids;

			ParameterLibrary::GetAllVectorParameterInfoChecked(Context, M, Infos, Ids);

			for (const FMaterialParameterInfo& Info : Infos)
			{
				if (Info.Name == ParamName)
				{
					return true;
				}
			}
		}

		// MaterialInstance
		if (UMaterialInstance* MI = Cast<UMaterialInstance>(Material))
		{
			for (const FVectorParameterValue& Value : MI->VectorParameterValues)
			{
				if (Value.ParameterInfo.Name == ParamName)
				{
					return true;
				}
			}

			// Check Parent

			// Material instance
			UMaterialInstance* MINST = Cast<UMaterialInstance>(MI->Parent);

			while (MINST)
			{
				for (const FVectorParameterValue& Value : MINST->VectorParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}

				if (UMaterial* M = Cast<UMaterial>(MINST->Parent))
				{
					static TArray<FMaterialParameterInfo> Infos;
					static TArray<FGuid> Ids;

					ParameterLibrary::GetAllVectorParameterInfoChecked(Context, M, Infos, Ids);

					for (const FMaterialParameterInfo& Info : Infos)
					{
						if (Info.Name == ParamName)
						{
							return true;
						}
					}
					break;
				}
				MINST = Cast<UMaterialInstance>(MINST->Parent);
			}
			// Material
			if (UMaterial* M = Cast<UMaterial>(MI->Parent))
			{
				static TArray<FMaterialParameterInfo> Infos;
				static TArray<FGuid> Ids;

				ParameterLibrary::GetAllVectorParameterInfoChecked(Context, M, Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find ParamName: %s in Material: %s."), *Context, *(ParamName.ToString()), *(Material->GetName())));
		return false;
	}

	bool FLibrary::IsVectorParameterValid(UMaterialInterface* Material, const FName& ParamName)
	{
		SET_CONTEXT(IsVectorParameterValid);

		return IsVectorParameterValid(Context, Material, ParamName, nullptr);
	}

	FLinearColor FLibrary::GetVectorParameterValueChecked(const FString& Context, UMaterialInterface* Material, const FName& ParamName)
	{
		check(IsVectorParameterValidChecked(Context, Material, ParamName));

		FHashedMaterialParameterInfo ParameterInfo(ParamName, EMaterialParameterAssociation::GlobalParameter, INDEX_NONE);

		FLinearColor Value;
		Material->GetVectorParameterValue(ParameterInfo, Value);
		return Value;
	}

	#pragma endregion Vector

	// Texture
	#pragma region

	bool FLibrary::IsTextureParameterValidChecked(const FString& Context, UMaterialInterface* Material, const FName& ParamName)
	{
		// Check Material is Valid
		CS_IS_PENDING_KILL_CHECKED(Material)
		// Check ParamName is Valid
		CS_IS_NAME_NONE_CHECKED(ParamName)

		typedef NCsMaterial::NParameter::FLibrary ParameterLibrary;

		// Material
		if (UMaterial* M = Cast<UMaterial>(Material))
		{
			static TArray<FMaterialParameterInfo> Infos;
			static TArray<FGuid> Ids;

			ParameterLibrary::GetAllTextureParameterInfoChecked(Context, M, Infos, Ids);

			for (const FMaterialParameterInfo& Info : Infos)
			{
				if (Info.Name == ParamName)
				{
					return true;
				}
			}
		}

		// MaterialInstance
		if (UMaterialInstance* MI = Cast<UMaterialInstance>(Material))
		{
			for (const FTextureParameterValue& Value : MI->TextureParameterValues)
			{
				if (Value.ParameterInfo.Name == ParamName)
				{
					return true;
				}
			}

			// Check Parent

			// Material instance
			UMaterialInstance* MINST = Cast<UMaterialInstance>(MI->Parent);

			while (MINST)
			{
				for (const FTextureParameterValue& Value : MINST->TextureParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}

				if (UMaterial* M = Cast<UMaterial>(MINST->Parent))
				{
					static TArray<FMaterialParameterInfo> Infos;
					static TArray<FGuid> Ids;

					ParameterLibrary::GetAllTextureParameterInfoChecked(Context, M, Infos, Ids);

					for (const FMaterialParameterInfo& Info : Infos)
					{
						if (Info.Name == ParamName)
						{
							return true;
						}
					}
					break;
				}
				MINST = Cast<UMaterialInstance>(MINST->Parent);
			}
			// Material
			if (UMaterial* M = Cast<UMaterial>(MI->Parent))
			{
				static TArray<FMaterialParameterInfo> Infos;
				static TArray<FGuid> Ids;

				ParameterLibrary::GetAllTextureParameterInfoChecked(Context, M, Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}
			}
		}
		//checkf(0, TEXT("%s: Failed to find ParamName: %s in Material: %s with Parent: %s."), *Context, *(ParamName.ToString()), *(Material->GetName()));
		checkf(0, TEXT("%s: Failed to find ParamName: %s in Material: %s."), *Context, *(ParamName.ToString()), *(Material->GetName()));
		return false;
	}

	bool FLibrary::IsTextureParameterValid(const FString& Context, UMaterialInterface* Material, const FName& ParamName, LogLevel)
	{
		// Check Material is Valid
		CS_IS_PENDING_KILL(Material)
		// Check ParamName is Valid
		CS_IS_NAME_NONE(ParamName)

		typedef NCsMaterial::NParameter::FLibrary ParameterLibrary;

		// Material
		if (UMaterial* M = Cast<UMaterial>(Material))
		{
			static TArray<FMaterialParameterInfo> Infos;
			static TArray<FGuid> Ids;

			ParameterLibrary::GetAllTextureParameterInfoChecked(Context, M, Infos, Ids);

			for (const FMaterialParameterInfo& Info : Infos)
			{
				if (Info.Name == ParamName)
				{
					return true;
				}
			}
		}

		// MaterialInstance
		if (UMaterialInstance* MI = Cast<UMaterialInstance>(Material))
		{
			for (const FTextureParameterValue& Value : MI->TextureParameterValues)
			{
				if (Value.ParameterInfo.Name == ParamName)
				{
					return true;
				}
			}

			// Check Parent

			// Material instance
			UMaterialInstance* MINST = Cast<UMaterialInstance>(MI->Parent);

			while (MINST)
			{
				for (const FTextureParameterValue& Value : MINST->TextureParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}

				if (UMaterial* M = Cast<UMaterial>(MINST->Parent))
				{
					static TArray<FMaterialParameterInfo> Infos;
					static TArray<FGuid> Ids;

					ParameterLibrary::GetAllTextureParameterInfoChecked(Context, M, Infos, Ids);

					for (const FMaterialParameterInfo& Info : Infos)
					{
						if (Info.Name == ParamName)
						{
							return true;
						}
					}
					break;
				}
				MINST = Cast<UMaterialInstance>(MINST->Parent);
			}
			// Material
			if (UMaterial* M = Cast<UMaterial>(MI->Parent))
			{
				static TArray<FMaterialParameterInfo> Infos;
				static TArray<FGuid> Ids;

				ParameterLibrary::GetAllTextureParameterInfoChecked(Context, M, Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find ParamName: %s in Material: %s."), *Context, *(ParamName.ToString()), *(Material->GetName())));
		return false;
	}

	bool FLibrary::IsTextureParameterValid(UMaterialInterface* Material, const FName& ParamName)
	{
		SET_CONTEXT(IsTextureParameterValid);

		return IsTextureParameterValid(Context, Material, ParamName, nullptr);
	}

	UTexture* FLibrary::GetTextureParameterValueChecked(const FString& Context, UMaterialInterface* Material, const FName& ParamName)
	{
		check(IsTextureParameterValidChecked(Context, Material, ParamName));

		FHashedMaterialParameterInfo ParameterInfo(ParamName, EMaterialParameterAssociation::GlobalParameter, INDEX_NONE);

		UTexture* Value;
		Material->GetTextureParameterValue(ParameterInfo, Value);
		return Value;
	}

	#pragma endregion Texture

	#undef USING_NS_CACHED
	#undef SET_CONTEXT
	#undef LogLevel

	namespace NMID
	{
		namespace NLibrary
		{
			namespace NCached 
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, IsScalarParameterValid);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, SetSafeScalarParameterValue);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, SetSafeScalarParameterValue_MinChecks);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, IsVectorParameterValid);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, SetSafeVectorParameterValue);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, SetSafeVectorParameterValue_MinChecks);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, IsTextureParameterValid);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, SetSafeTextureParameterValue);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, SetSafeTextureParameterValue_MinChecks);
				}
			}
		}

		#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/

		bool FLibrary::IsValidChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs)
		{
			const int32 Count = MIDs.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				checkf(IsValid(MIDs[I]), TEXT("%s: MIDs[%d] is NULL or IsPendingKill."), *Context, I);
			}
			return true;
		}

		void FLibrary::SetChecked(const FString& Context, UPrimitiveComponent* Mesh, UMaterialInterface* Material, const int32& Index, UMaterialInstanceDynamic*& OutMID)
		{
			CsMaterialLibrary::ClearOverrideChecked(Context, Mesh, Index);
			CsMaterialLibrary::IsValidChecked(Context, Mesh, Index);

			CsObjectLibrary::SafeMarkAsGarbage(Context, OutMID, nullptr);

			CS_IS_PENDING_KILL_CHECKED(Material)

			OutMID = Mesh->CreateDynamicMaterialInstance(Index, Material);
		}

		bool FLibrary::SetSafe(const FString& Context, UPrimitiveComponent* Mesh, UMaterialInterface* Material, const int32& Index, UMaterialInstanceDynamic*& OutMID, LogLevel)
		{
			if (!CsMaterialLibrary::SafeClearOverride(Context, Mesh, Index, Log))
				return false;
			if (!CsMaterialLibrary::IsValid(Context, Mesh, Index, Log))
				return false;

			CsObjectLibrary::SafeMarkAsGarbage(Context, OutMID, nullptr);

			CS_IS_PENDING_KILL(Material)

			OutMID = Mesh->CreateDynamicMaterialInstance(Index, Material);
			return true;
		}

		void FLibrary::SetChecked(const FString& Context, UPrimitiveComponent* Mesh, const TArray<UMaterialInterface*>& Materials, TArray<UMaterialInstanceDynamic*>& OutMIDs)
		{
			CsMaterialLibrary::ClearOverrideChecked(Context, Mesh);
			Destroy(OutMIDs);

			const int32 Count = Materials.Num();

			CS_RESET_ARRAY_CHECKED(OutMIDs, UMaterialInstanceDynamic, Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

				OutMIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
			}
		}

		bool FLibrary::SetSafe(const FString& Context, UPrimitiveComponent* Mesh, const TArray<UMaterialInterface*>& Materials, TArray<UMaterialInstanceDynamic*>& OutMIDs, LogLevel)
		{
			if (!CsMaterialLibrary::SafeClearOverride(Context, Mesh, Log))
				return false;

			Destroy(OutMIDs);

			const int32 Count = Materials.Num();

			CS_RESET_ARRAY_CHECKED(OutMIDs, UMaterialInstanceDynamic, Count);

			for (int32 I = 0; I < Count; ++I)
			{
				if (!Materials[I])
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Materials[%d] is NULL."), *Context, I));
					return false;
				}
				OutMIDs.Add(Mesh->CreateDynamicMaterialInstance(I, Materials[I]));
			}
			return true;
		}

		void FLibrary::SetChecked(const FString& Context, UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& OutMIDs, const TArray<UMaterialInterface*>& Materials)
		{
			CsMaterialLibrary::ClearOverrideChecked(Context, Mesh);
			Destroy(OutMIDs);

			const int32 Count = Materials.Num();

			CS_RESET_ARRAY_CHECKED(OutMIDs, UMaterialInstanceDynamic, Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

				OutMIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
			}
		}

		void FLibrary::SetChecked(const FString& Context, UStaticMeshComponent* Mesh, const TArray<UMaterialInstanceDynamic*>& MIDs)
		{
			// Check Mesh is Valid
			CS_IS_PENDING_KILL_CHECKED(Mesh)

			check(IsValidChecked(Context, MIDs));

			const int32 Count = MIDs.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				Mesh->SetMaterial(I, MIDs[I]);
			}
		}

		void FLibrary::SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& OutMIDs, const TArray<UMaterialInterface*>& Materials)
		{
			CsMaterialLibrary::ClearOverrideChecked(Context, Mesh);
			Destroy(OutMIDs);

			const int32 Count = Materials.Num();

			CS_RESET_ARRAY_CHECKED(OutMIDs, UMaterialInstanceDynamic, Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				UMaterialInterface* Material = Materials[Index];

				checkf(Material, TEXT("%s: Materials[%d] is NULL."), *Context, Index);

				OutMIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Material));
			}
		}

		void FLibrary::SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, const TArray<UMaterialInstanceDynamic*>& MIDs)
		{
			// Check Mesh is Valid
			CS_IS_PENDING_KILL_CHECKED(Mesh)

			check(IsValidChecked(Context, MIDs));

			const int32 Count = MIDs.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				Mesh->SetMaterial(I, MIDs[I]);
			}
		}

		void FLibrary::Destroy(TArray<UMaterialInstanceDynamic*>& OutMIDs)
		{
			const int32 Count = OutMIDs.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				UMaterialInstanceDynamic* MID = OutMIDs[I];

				CsObjectLibrary::SafeMarkAsGarbage(MID);

				OutMIDs.RemoveAt(I, 1, EAllowShrinking::No);
			}
		}

		// Scalar
		#pragma region

		bool FLibrary::IsScalarParameterValidChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			// Check MID is Valid
			CS_IS_PENDING_KILL_CHECKED(MID)
			// Check ParamName is Valid
			CS_IS_NAME_NONE_CHECKED(ParamName)

			// MaterialInstance
			for (const FScalarParameterValue& Value : MID->ScalarParameterValues)
			{
				if (Value.ParameterInfo.Name == ParamName)
				{
					return true;
				}
			}

			// Check Parent
			typedef NCsMaterial::NParameter::FLibrary ParameterLibrary;

				// Material instance
			UMaterialInstance* MI = Cast<UMaterialInstance>(MID->Parent);

			while (MI)
			{
				for (const FScalarParameterValue& Value : MI->ScalarParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}

				if (UMaterial* M = Cast<UMaterial>(MI->Parent))
				{
					static TArray<FMaterialParameterInfo> Infos;
					static TArray<FGuid> Ids;

					ParameterLibrary::GetAllScalarParameterInfoChecked(Context, M, Infos, Ids);

					for (const FMaterialParameterInfo& Info : Infos)
					{
						if (Info.Name == ParamName)
						{
							return true;
						}
					}
					break;
				}
				MI = Cast<UMaterialInstance>(MI->Parent);
			}
				// Material
			if (UMaterial* M = Cast<UMaterial>(MID->Parent))
			{
				static TArray<FMaterialParameterInfo> Infos;
				static TArray<FGuid> Ids;

				ParameterLibrary::GetAllScalarParameterInfoChecked(Context, M, Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}
			}
			checkf(0, TEXT("%s: Failed to find ParamName: %s in MID: %s with Parent: %s."), *Context, *(ParamName.ToString()), *(MID->GetName()), *(MID->Parent->GetName()));
			return false;
		}

		bool FLibrary::IsScalarParameterValid(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, LogLevel)
		{
			// Check MID is Valid
			CS_IS_PENDING_KILL(MID)
			// Check ParamName is Valid
			CS_IS_NAME_NONE(ParamName)

			// MaterialInstance
			for (const FScalarParameterValue& Value : MID->ScalarParameterValues)
			{
				if (Value.ParameterInfo.Name == ParamName)
				{
					return true;
				}
			}

			// Check Parent
			typedef NCsMaterial::NParameter::FLibrary ParameterLibrary;

				// Material instance
			UMaterialInstance* MI = Cast<UMaterialInstance>(MID->Parent);

			while (MI)
			{
				for (const FScalarParameterValue& Value : MI->ScalarParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}

				if (UMaterial* M = Cast<UMaterial>(MI->Parent))
				{
					static TArray<FMaterialParameterInfo> Infos;
					static TArray<FGuid> Ids;

					ParameterLibrary::GetAllScalarParameterInfoChecked(Context, M, Infos, Ids);

					for (const FMaterialParameterInfo& Info : Infos)
					{
						if (Info.Name == ParamName)
						{
							return true;
						}
					}
					break;
				}
				MI = Cast<UMaterialInstance>(MI->Parent);
			}
				// Material
			if (UMaterial* M = Cast<UMaterial>(MID->Parent))
			{
				static TArray<FMaterialParameterInfo> Infos;
				static TArray<FGuid> Ids;

				ParameterLibrary::GetAllScalarParameterInfoChecked(Context, M, Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}
			}

			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find ParamName: %s in MID: %s with Parent: %s."), *Context, *(ParamName.ToString()), *(MID->GetName()), *(MID->Parent->GetName())));
			return false;
		}

		bool FLibrary::IsScalarParameterValid(UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::IsScalarParameterValid;

			return IsScalarParameterValid(Context, MID, ParamName, nullptr);
		}

		bool FLibrary::AreScalarParametersValidChecked(const FString& Context, UMaterialInstanceDynamic* MID, const TArray<FName>& ParamNames)
		{
			// Check MID is Valid
			CS_IS_PENDING_KILL_CHECKED(MID)
			// Are all Names in ParamNames Valid
			CS_IS_TARRAY_ANY_NONE_CHECKED(ParamNames)

			static TArray<FName> Names;

			CsArrayLibrary::Copy<FName>(Names, ParamNames);

			// MaterialInstance
			for (const FScalarParameterValue& Value : MID->ScalarParameterValues)
			{
				const int32 Count = Names.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					if (Value.ParameterInfo.Name == Names[I])
					{
						Names.RemoveAt(I, 1, EAllowShrinking::No);
					}
				}
			}

			// Check Parent
			typedef NCsMaterial::NParameter::FLibrary ParameterLibrary;

			// Material instance
			UMaterialInstance* MI = Cast<UMaterialInstance>(MID->Parent);

			while (MI)
			{
				for (const FScalarParameterValue& Value : MI->ScalarParameterValues)
				{
					const int32 Count = Names.Num();

					for (int32 I = Count - 1; I >= 0; --I)
					{
						if (Value.ParameterInfo.Name == Names[I])
						{
							Names.RemoveAt(I, 1, EAllowShrinking::No);
						}
					}
				}

				if (UMaterial* M = Cast<UMaterial>(MI->Parent))
				{
					static TArray<FMaterialParameterInfo> Infos;
					static TArray<FGuid> Ids;

					ParameterLibrary::GetAllScalarParameterInfoChecked(Context, M, Infos, Ids);

					for (const FMaterialParameterInfo& Info : Infos)
					{
						const int32 Count = Names.Num();

						for (int32 I = Count - 1; I >= 0; --I)
						{
							if (Info.Name == Names[I])
							{
								Names.RemoveAt(I, 1, EAllowShrinking::No);
							}
						}
					}
					break;
				}
				MI = Cast<UMaterialInstance>(MI->Parent);
			}
			// Material
			if (UMaterial* M = Cast<UMaterial>(MID->Parent))
			{
				static TArray<FMaterialParameterInfo> Infos;
				static TArray<FGuid> Ids;

				ParameterLibrary::GetAllScalarParameterInfoChecked(Context, M, Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					const int32 Count = Names.Num();

					for (int32 I = Count - 1; I >= 0; --I)
					{
						if (Info.Name == Names[I])
						{
							Names.RemoveAt(I, 1, EAllowShrinking::No);
						}
					}
				}
			}
			checkf(Names.Num() == CS_EMPTY, TEXT("%s: Failed to find ALL ParamNames in MID: %s with Parent: %s."), *Context, *(MID->GetName()), *(MID->Parent->GetName()));
			return true;
		}

		void FLibrary::SetScalarParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value)
		{
			check(IsScalarParameterValidChecked(Context, MID, ParamName));

			MID->SetScalarParameterValue(ParamName, Value);
		}

		void FLibrary::SetScalarParameterValueChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value)
		{
			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY_CHECKED(MIDs, UMaterialInstanceDynamic*)

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetScalarParameterValueChecked(Context, MID, ParamName, Value);
			}
		}

		bool FLibrary::SetSafeScalarParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value, LogLevel)
		{
			if (IsScalarParameterValid(Context, MID, ParamName, Log))
			{
				MID->SetScalarParameterValue(ParamName, Value);
				return true;
			}
			return false;
		}

		bool FLibrary::SetSafeScalarParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeScalarParameterValue;

			return SetSafeScalarParameterValue(Context, MID, ParamName, Value, nullptr);
		}

		bool FLibrary::SetSafeScalarParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value, LogLevel)
		{
			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY(MIDs, UMaterialInstanceDynamic*)

			bool Result = true;

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				Result &= SetSafeScalarParameterValue(Context, MID, ParamName, Value, Log);
			}
			return Result;
		}

		bool FLibrary::SetSafeScalarParameterValue(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeScalarParameterValue;

			return SetSafeScalarParameterValue(Context, MIDs, ParamName, Value, nullptr);
		}

		bool FLibrary::SetSafeScalarParameterValue_MinChecks(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value)
		{
			void(*Log)(const FString&) = nullptr;

			CS_IS_PENDING_KILL(MID)
			CS_IS_NAME_NONE(ParamName)

			MID->SetScalarParameterValue(ParamName, Value);
			return true;
		}

		bool FLibrary::SetSafeScalarParameterValue_MinChecks(UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeScalarParameterValue_MinChecks;

			return SetSafeScalarParameterValue_MinChecks(Context, MID, ParamName, Value);
		}

		bool FLibrary::SetSafeScalarParameterValue_MinChecks(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value)
		{
			void(*Log)(const FString&) = nullptr;

			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY(MIDs, UMaterialInstanceDynamic*)

			bool Result = true;

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				Result &= SetSafeScalarParameterValue_MinChecks(Context, MID, ParamName, Value);
			}
			return Result;
		}

		bool FLibrary::SetSafeScalarParameterValue_MinChecks(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeScalarParameterValue_MinChecks;

			return SetSafeScalarParameterValue_MinChecks(Context, MIDs, ParamName, Value);
		}

		float FLibrary::GetScalarParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			check(IsScalarParameterValidChecked(Context, MID, ParamName));

			return MID->K2_GetScalarParameterValue(ParamName);
		}

			// Batch
		#pragma region

		void FLibrary::PopulateScalarParameterValuesChecked(const FString& Context, UMaterialInstanceDynamic* MID, const TArray<FName>& Names, TArray<FScalarParameterValue*>& Values)
		{
			CS_IS_PENDING_KILL_CHECKED(MID)
			CS_IS_TARRAY_ANY_NONE_CHECKED(Names)

			checkf(Names.Num() == Values.Num(), TEXT("%s: The sizes Names: %d != Values: %d."), *Context, Names.Num(), Values.Num());

			// Find or Add
			static TArray<int32> Indices;

			// Determine what needs to be Added
			CsArrayLibrary::PopulateRange(Indices, 0, Names.Num() - 1);

			int32 Count = MID->ScalarParameterValues.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				FScalarParameterValue* Parameter = &(MID->ScalarParameterValues[I]);

				const int32 IndexCount = Indices.Num();

				for (int32 J = IndexCount - 1; J >= 0; --J)
				{
					const int32& Index = Indices[J];

					if (Parameter->ParameterInfo.Name == Names[Index])
					{
						Indices.RemoveAt(J, 1, EAllowShrinking::No);
					}
				}
			}

			const int32 IndexCount = Indices.Num();
			const int32 PrevCount  = MID->ScalarParameterValues.Num();

			MID->ScalarParameterValues.AddDefaulted(IndexCount);

			Count = MID->ScalarParameterValues.Num();

			for (int32 I = PrevCount; I < Count; ++I)
			{
				const int32 Index = Indices[I - PrevCount];

				FScalarParameterValue* ParameterValue = &(MID->ScalarParameterValues[I]);
				ParameterValue->ParameterInfo = FMaterialParameterInfo(Names[Index]);
				ParameterValue->ExpressionGUID.Invalidate();
			}

			// Cache references
			int32 ValueCount	  = 0;
			const int32 NameCount = Names.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				FScalarParameterValue* Parameter = &(MID->ScalarParameterValues[I]);

				for (int32 J = 0; J < NameCount; ++J)
				{
					if (Parameter->ParameterInfo.Name == Names[J])
					{
						Values[J] = Parameter;
						++ValueCount;
					}
				}
			}
			checkf(ValueCount == NameCount, TEXT("%s: Failed to set Values for ALL Names."), *Context);
		}

		#pragma endregion Batch

		#pragma endregion Scalar

		// Vector
		#pragma region

		bool FLibrary::IsVectorParameterValidChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			// Check MID is Valid
			CS_IS_PENDING_KILL_CHECKED(MID)
			// Check ParamName is Valid
			CS_IS_NAME_NONE_CHECKED(ParamName)

			// MaterialInstance
			for (const FVectorParameterValue& Value : MID->VectorParameterValues)
			{
				if (Value.ParameterInfo.Name == ParamName)
				{
					return true;
				}
			}

			// Check Parent
			typedef NCsMaterial::NParameter::FLibrary ParameterLibrary;

				// Material instance
			UMaterialInstance* MI = Cast<UMaterialInstance>(MID->Parent);

			while (MI)
			{
				for (const FVectorParameterValue& Value : MI->VectorParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}

				if (UMaterial* M = Cast<UMaterial>(MI->Parent))
				{
					static TArray<FMaterialParameterInfo> Infos;
					static TArray<FGuid> Ids;

					ParameterLibrary::GetAllVectorParameterInfoChecked(Context, M, Infos, Ids);

					for (const FMaterialParameterInfo& Info : Infos)
					{
						if (Info.Name == ParamName)
						{
							return true;
						}
					}
					break;
				}
				MI = Cast<UMaterialInstance>(MI->Parent);
			}
				// Material
			if (UMaterial* M = Cast<UMaterial>(MID->Parent))
			{
				static TArray<FMaterialParameterInfo> Infos;
				static TArray<FGuid> Ids;

				ParameterLibrary::GetAllVectorParameterInfoChecked(Context, M, Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}
			}
			checkf(0, TEXT("%s: Failed to find ParamName: %s in MID: %s with Parent: %s."), *Context, *(ParamName.ToString()), *(MID->GetName()), *(MID->Parent->GetName()));
			return false;
		}

		bool FLibrary::IsVectorParameterValid(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, LogLevel)
		{
			// Check MID is Valid
			CS_IS_PENDING_KILL(MID)
			// Check ParamName is Valid
			CS_IS_NAME_NONE(ParamName)

			// MaterialInstance
			for (const FVectorParameterValue& Value : MID->VectorParameterValues)
			{
				if (Value.ParameterInfo.Name == ParamName)
				{
					return true;
				}
			}

			// Check Parent
			typedef NCsMaterial::NParameter::FLibrary ParameterLibrary;

				// Material instance
			UMaterialInstance* MI = Cast<UMaterialInstance>(MID->Parent);

			while (MI)
			{
				for (const FVectorParameterValue& Value : MI->VectorParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}

				if (UMaterial* M = Cast<UMaterial>(MI->Parent))
				{
					static TArray<FMaterialParameterInfo> Infos;
					static TArray<FGuid> Ids;

					ParameterLibrary::GetAllVectorParameterInfoChecked(Context, M, Infos, Ids);

					for (const FMaterialParameterInfo& Info : Infos)
					{
						if (Info.Name == ParamName)
						{
							return true;
						}
					}
					break;
				}
				MI = Cast<UMaterialInstance>(MI->Parent);
			}
				// Material
			if (UMaterial* M = Cast<UMaterial>(MID->Parent))
			{
				static TArray<FMaterialParameterInfo> Infos;
				static TArray<FGuid> Ids;

				ParameterLibrary::GetAllVectorParameterInfoChecked(Context, M, Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}
			}
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find ParamName: %s in MID: %s with Parent: %s."), *Context, *(ParamName.ToString()), *(MID->GetName()), *(MID->Parent->GetName())));
			return false;
		}

		bool FLibrary::IsVectorParameterValid(UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::IsVectorParameterValid;

			return IsVectorParameterValid(Context, MID, ParamName, nullptr);
		}

		void FLibrary::SetVectorParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector3f& Value)
		{
			check(IsVectorParameterValidChecked(Context, MID, ParamName));

			MID->SetVectorParameterValue(ParamName, Value);
		}

		void FLibrary::SetVectorParameterValueChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector3f& Value)
		{
			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY_CHECKED(MIDs, UMaterialInstanceDynamic*)

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetVectorParameterValueChecked(Context, MID, ParamName, Value);
			}
		}

		bool FLibrary::SetSafeVectorParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector3f& Value, LogLevel)
		{
			if (IsVectorParameterValid(Context, MID, ParamName, Log))
			{
				MID->SetVectorParameterValue(ParamName, Value);
				return true;
			}
			return false;
		}

		bool FLibrary::SetSafeVectorParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector3f& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeVectorParameterValue;

			return SetSafeVectorParameterValue(Context, MID, ParamName, Value, nullptr);
		}

		bool FLibrary::SetSafeVectorParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector3f& Value, LogLevel)
		{
			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY(MIDs, UMaterialInstanceDynamic*)

			bool Result = true;

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				Result &= SetSafeVectorParameterValue(Context, MID, ParamName, Value, Log);
			}
			return Result;
		}

		bool FLibrary::SetSafeVectorParameterValue(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector3f& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeVectorParameterValue;

			return SetSafeVectorParameterValue(Context, MIDs, ParamName, Value, nullptr);
		}

		bool FLibrary::SetSafeVectorParameterValue_MinChecks(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector3f& Value)
		{
			void(*Log)(const FString&) = nullptr;

			CS_IS_PENDING_KILL(MID)
			CS_IS_NAME_NONE(ParamName)

			MID->SetVectorParameterValue(ParamName, Value);
			return true;
		}

		bool FLibrary::SetSafeVectorParameterValue_MinChecks(UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector3f& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeVectorParameterValue_MinChecks;

			return SetSafeVectorParameterValue_MinChecks(Context, MID, ParamName, Value);
		}

		bool FLibrary::SetSafeVectorParameterValue_MinChecks(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector3f& Value)
		{
			void(*Log)(const FString&) = nullptr;

			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY(MIDs, UMaterialInstanceDynamic*)

			bool Result = true;

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				Result &= SetSafeVectorParameterValue_MinChecks(Context, MID, ParamName, Value);
			}
			return Result;
		}

		bool FLibrary::SetSafeVectorParameterValue_MinChecks(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector3f& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeVectorParameterValue_MinChecks;

			return SetSafeVectorParameterValue_MinChecks(Context, MIDs, ParamName, Value);
		}

		void FLibrary::SetVectorParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value)
		{
			check(IsVectorParameterValidChecked(Context, MID, ParamName));

			MID->SetVectorParameterValue(ParamName, Value);
		}

		bool FLibrary::SetSafeVectorParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value, LogLevel)
		{
			if (IsVectorParameterValid(Context, MID, ParamName, Log))
			{
				MID->SetVectorParameterValue(ParamName, Value);
				return true;
			}
			return false;
		}

		bool FLibrary::SetSafeVectorParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeVectorParameterValue;

			return SetSafeVectorParameterValue(Context, MID, ParamName, Value, nullptr);
		}

		bool FLibrary::SetSafeVectorParameterValue_MinChecks(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value)
		{
			void(*Log)(const FString&) = nullptr;

			CS_IS_PTR_NULL(MID)
			CS_IS_NAME_NONE(ParamName)

			MID->SetVectorParameterValue(ParamName, Value);
			return true;
		}

		bool FLibrary::SetSafeVectorParameterValue_MinChecks(UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeVectorParameterValue_MinChecks;

			return SetSafeVectorParameterValue_MinChecks(Context, MID, ParamName, Value);
		}

		void FLibrary::SetVectorParameterValueChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value)
		{
			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY_CHECKED(MIDs, UMaterialInstanceDynamic*)

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetVectorParameterValueChecked(Context, MID, ParamName, Value);
			}
		}

		bool FLibrary::SetSafeVectorParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value, LogLevel)
		{
			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY(MIDs, UMaterialInstanceDynamic*)

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetSafeVectorParameterValue(Context, MID, ParamName, Value, Log);
			}
			return true;
		}

		bool FLibrary::SetSafeVectorParameterValue(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeVectorParameterValue;

			return SetSafeVectorParameterValue(Context, MIDs, ParamName, Value, nullptr);
		}

		bool FLibrary::SetSafeVectorParameterValue_MinChecks(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value)
		{
			void(*Log)(const FString&) = nullptr;

			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY(MIDs, UMaterialInstanceDynamic*)

			bool Result = true;

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				Result &= SetSafeVectorParameterValue_MinChecks(Context, MID, ParamName, Value);
			}
			return Result;
		}

		bool FLibrary::SetSafeVectorParameterValue_MinChecks(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeVectorParameterValue_MinChecks;

			return SetSafeVectorParameterValue_MinChecks(Context, MIDs, ParamName, Value);
		}

		FLinearColor FLibrary::GetVectorParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			check(IsVectorParameterValidChecked(Context, MID, ParamName));

			return MID->K2_GetVectorParameterValue(ParamName);
		}

			// Batch
		#pragma region

		void FLibrary::PopulateVectorParameterValuesChecked(const FString& Context, UMaterialInstanceDynamic* MID, const TArray<FName>& Names, TArray<FVectorParameterValue*>& Values)
		{
			CS_IS_PTR_NULL_CHECKED(MID)
			CS_IS_TARRAY_ANY_NONE_CHECKED(Names)

			checkf(Names.Num() == Values.Num(), TEXT("%s: The sizes Names: %d != Values: %d."), *Context, Names.Num(), Values.Num());

			// Find or Add
			static TArray<int32> Indices;

			// Determine what needs to be Added
			CsArrayLibrary::PopulateRange(Indices, 0, Names.Num() - 1);

			int32 Count = MID->VectorParameterValues.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				FVectorParameterValue* Parameter = &(MID->VectorParameterValues[I]);

				const int32 IndexCount = Indices.Num();

				for (int32 J = IndexCount - 1; J >= 0; --J)
				{
					const int32& Index = Indices[J];

					if (Parameter->ParameterInfo.Name == Names[Index])
					{
						Indices.RemoveAt(J, 1, EAllowShrinking::No);
					}
				}
			}

			const int32 IndexCount = Indices.Num();
			const int32 PrevCount  = MID->VectorParameterValues.Num();

			MID->VectorParameterValues.AddDefaulted(IndexCount);

			Count = MID->VectorParameterValues.Num();

			for (int32 I = PrevCount; I < Count; ++I)
			{
				const int32 Index = Indices[I - PrevCount];

				FVectorParameterValue* ParameterValue = &(MID->VectorParameterValues[I]);
				ParameterValue->ParameterInfo = FMaterialParameterInfo(Names[Index]);
				ParameterValue->ExpressionGUID.Invalidate();
			}

			// Cache references
			int32 ValueCount	  = 0;
			const int32 NameCount = Names.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				FVectorParameterValue* Parameter = &(MID->VectorParameterValues[I]);

				for (int32 J = 0; J < NameCount; ++J)
				{
					if (Parameter->ParameterInfo.Name == Names[J])
					{
						Values[J] = Parameter;
						++ValueCount;
					}
				}
			}
			checkf(ValueCount == NameCount, TEXT("%s: Failed to set Values for ALL Names."), *Context);
		}

		#pragma endregion Batch

		#pragma endregion Vector

		// Texture
		#pragma region

		bool FLibrary::IsTextureParameterValidChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			// Check MID is Valid
			CS_IS_PENDING_KILL_CHECKED(MID)
			// Check ParamName is Valid
			CS_IS_NAME_NONE_CHECKED(ParamName)

			// MaterialInstance
			for (const FTextureParameterValue& Value : MID->TextureParameterValues)
			{
				if (Value.ParameterInfo.Name == ParamName)
				{
					return true;
				}
			}

			// Check Parent
			typedef NCsMaterial::NParameter::FLibrary ParameterLibrary;

				// Material instance
			UMaterialInstance* MI = Cast<UMaterialInstance>(MID->Parent);

			while (MI)
			{
				for (const FTextureParameterValue& Value : MI->TextureParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}

				if (UMaterial* M = Cast<UMaterial>(MI->Parent))
				{
					static TArray<FMaterialParameterInfo> Infos;
					static TArray<FGuid> Ids;

					ParameterLibrary::GetAllTextureParameterInfoChecked(Context, M, Infos, Ids);

					for (const FMaterialParameterInfo& Info : Infos)
					{
						if (Info.Name == ParamName)
						{
							return true;
						}
					}
					break;
				}
				MI = Cast<UMaterialInstance>(MI->Parent);
			}
				// Material
			if (UMaterial* M = Cast<UMaterial>(MID->Parent))
			{
				static TArray<FMaterialParameterInfo> Infos;
				static TArray<FGuid> Ids;

				ParameterLibrary::GetAllTextureParameterInfoChecked(Context, M, Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}
			}
			checkf(0, TEXT("%s: Failed to find ParamName: %s in MID: %s with Parent: %s."), *Context, *(ParamName.ToString()), *(MID->GetName()), *(MID->Parent->GetName()));
			return false;
		}

		bool FLibrary::IsTextureParameterValid(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, LogLevel)
		{
			// Check MID is Valid
			CS_IS_PENDING_KILL(MID)
			// Check ParamName is Valid
			CS_IS_NAME_NONE(ParamName)

			// MaterialInstance
			for (const FTextureParameterValue& Value : MID->TextureParameterValues)
			{
				if (Value.ParameterInfo.Name == ParamName)
				{
					return true;
				}
			}

			// Check Parent
			typedef NCsMaterial::NParameter::FLibrary ParameterLibrary;

				// Material instance
			UMaterialInstance* MI = Cast<UMaterialInstance>(MID->Parent);

			while (MI)
			{
				for (const FTextureParameterValue& Value : MI->TextureParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}

				if (UMaterial* M = Cast<UMaterial>(MI->Parent))
				{
					static TArray<FMaterialParameterInfo> Infos;
					static TArray<FGuid> Ids;

					ParameterLibrary::GetAllTextureParameterInfoChecked(Context, M, Infos, Ids);

					for (const FMaterialParameterInfo& Info : Infos)
					{
						if (Info.Name == ParamName)
						{
							return true;
						}
					}
					break;
				}
				MI = Cast<UMaterialInstance>(MI->Parent);
			}
				// Material
			if (UMaterial* M = Cast<UMaterial>(MID->Parent))
			{
				static TArray<FMaterialParameterInfo> Infos;
				static TArray<FGuid> Ids;

				ParameterLibrary::GetAllTextureParameterInfoChecked(Context, M, Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}
			}
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find ParamName: %s in MID: %s with Parent: %s."), *Context, *(ParamName.ToString()), *(MID->GetName()), *(MID->Parent->GetName())));
			return false;
		}

		bool FLibrary::IsTextureParameterValid(UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::IsTextureParameterValid;

			return IsTextureParameterValid(Context, MID, ParamName, nullptr);
		}

		void FLibrary::SetTextureParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, UTexture* Value)
		{
			check(IsTextureParameterValidChecked(Context, MID, ParamName));

			MID->SetTextureParameterValue(ParamName, Value);
		}

		void FLibrary::SetTextureParameterValueChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, UTexture* Value)
		{
			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY_CHECKED(MIDs, UMaterialInstanceDynamic*)

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetTextureParameterValueChecked(Context, MID, ParamName, Value);
			}
		}

		bool FLibrary::SetSafeTextureParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, UTexture* Value, LogLevel)
		{
			if (IsTextureParameterValid(Context, MID, ParamName, Log))
			{
				MID->SetTextureParameterValue(ParamName, Value);
				return true;
			}
			return false;
		}

		bool FLibrary::SetSafeTextureParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, UTexture* Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeScalarParameterValue;

			return SetSafeTextureParameterValue(Context, MID, ParamName, Value, nullptr);
		}

		bool FLibrary::SetSafeTextureParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, UTexture* Value, LogLevel)
		{
			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY(MIDs, UMaterialInstanceDynamic*)

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetSafeTextureParameterValue(Context, MID, ParamName, Value, Log);
			}
			return true;
		}

		bool FLibrary::SetSafeTextureParameterValue(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, UTexture* Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeTextureParameterValue;

			return SetSafeTextureParameterValue(Context, MIDs, ParamName, Value, nullptr);
		}

		bool FLibrary::SetSafeTextureParameterValue_MinChecks(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, UTexture* Value)
		{
			void(*Log)(const FString&) = nullptr;

			CS_IS_PENDING_KILL(MID)
			CS_IS_NAME_NONE(ParamName)

			MID->SetTextureParameterValue(ParamName, Value);
			return true;
		}

		bool FLibrary::SetSafeTextureParameterValue_MinChecks(UMaterialInstanceDynamic* MID, const FName& ParamName, UTexture* Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeTextureParameterValue_MinChecks;

			return SetSafeTextureParameterValue_MinChecks(Context, MID, ParamName, Value);
		}

		bool FLibrary::SetSafeTextureParameterValue_MinChecks(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, UTexture* Value)
		{
			void(*Log)(const FString&) = nullptr;

			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY(MIDs, UMaterialInstanceDynamic*)

			bool Result = true;

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				Result &= SetSafeTextureParameterValue_MinChecks(Context, MID, ParamName, Value);
			}
			return Result;
		}

		bool FLibrary::SetSafeTextureParameterValue_MinChecks(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, UTexture* Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeTextureParameterValue_MinChecks;

			return SetSafeTextureParameterValue_MinChecks(Context, MIDs, ParamName, Value);
		}

		UTexture* FLibrary::GetTextureParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			check(IsTextureParameterValidChecked(Context, MID, ParamName));

			return MID->K2_GetTextureParameterValue(ParamName);
		}

		#pragma endregion Scalar

		#undef LogLevel
	}
}