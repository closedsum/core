// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Material/CsLibrary_Material.h"
#include "CsCore.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Object/CsLibrary_Object.h"
#include "Material/CsLibrary_Material_Parameter.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Array.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Mesh
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Material
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

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

	// Load
	#pragma region

	UMaterialInterface* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UMaterialInterface>(Context, Path, Log);
	}

	UMaterialInterface* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UMaterialInterface>(Context, Path, Log);
	}

	bool FLibrary::SafeLoad(const FString& Context, const TArray<FString>& Paths, TArray<UMaterialInterface*>& OutMaterials, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

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

	bool FLibrary::IsValid(const FString& Context, const TArray<UMaterialInterface*>& Materials, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

		const int32 Count		 = Mesh->StaticMaterials.Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *(Mesh->GetName()), Count, MaterialCount);

		check(IsValidChecked(Context, Materials));

		return true;
	}

	bool FLibrary::IsValid(const FString& Context, UStaticMesh* Mesh, const TArray<UMaterialInterface*>& Materials, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check Mesh is Valid
		CS_IS_PTR_NULL(Mesh)

		const int32 Count		  = Mesh->StaticMaterials.Num();
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

		const int32 Count		  = Mesh->Materials.Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *(Mesh->GetName()), Count, MaterialCount);

		check(IsValidChecked(Context, Materials));

		return true;
	}

	bool FLibrary::IsValid(const FString& Context, USkeletalMesh* Mesh, const TArray<UMaterialInterface*>& Materials, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check Mesh is Valid
		CS_IS_PTR_NULL(Mesh)

		const int32 Count		  = Mesh->Materials.Num();
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

		checkf(Index < Mesh->Materials.Num(), TEXT("%s: Index: %d is GREATER THAN the number of Materials (%d) for Mesh: %s."), *Context, Index, *(Mesh->GetName()), Mesh->Materials.Num());

		return true;
	}

	bool FLibrary::IsValidChecked(const FString& Context, UStaticMesh* Mesh, const int32& Index)
	{
		CS_IS_PTR_NULL_CHECKED(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)

		checkf(Index < Mesh->StaticMaterials.Num(), TEXT("%s: Index: %d is GREATER THAN the number of Materials (%d) for Mesh: %s."), *Context, Index, *(Mesh->GetName()), Mesh->StaticMaterials.Num());
		return true;
	}

	bool FLibrary::IsValidChecked(const FString& Context, UPrimitiveComponent* Mesh, const int32& Index)
	{
		CS_IS_PTR_NULL_CHECKED(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)

		checkf(Index < Mesh->GetNumMaterials(), TEXT("%s: Index: %d is GREATER THAN the number of Materials (%d) for Mesh: %s."), *Context, Index, *(Mesh->GetName()), Mesh->GetNumMaterials());
		return true;
	}

	bool FLibrary::IsValid(const FString& Context, UPrimitiveComponent* Mesh, const int32& Index, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Index, 0)

		if (Index >= Mesh->GetNumMaterials())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Index: %d is GREATER THAN the number of Materials (%d) for Mesh: %s."), *Context, Index, *(Mesh->GetName()), Mesh->GetNumMaterials()));
			return false;
		}
		return true;
	}

	void FLibrary::SetChecked(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material)
	{
		// Check Component is Valid
		CS_IS_PTR_NULL_CHECKED(Component)
		// Check Material is Valid
		CS_IS_PTR_NULL_CHECKED(Material)

		const int32 Count = Component->GetNumMaterials();

		for (int32 I = 0; I < Count; ++I)
		{
			Component->SetMaterial(I, Material);
		}
	}

	bool FLibrary::SetSafe(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check Component is Valid
		CS_IS_PTR_NULL(Component)
		// Check Material is Valid
		CS_IS_PTR_NULL(Material)

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
		CS_IS_PTR_NULL_CHECKED(Component)
		// Check Material is Valid
		CS_IS_PTR_NULL_CHECKED(Material)
		// Check Index is Valid
		CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)

		checkf(Index < Component->GetNumMaterials(), TEXT("%s: Index: %d is NOT Valid for Component: %s with %d Material Slots."), *Context, Index, *(Component->GetName()), Component->GetNumMaterials());

		Component->SetMaterial(Index, Material);
	}

	bool FLibrary::SetSafe(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check Component is Valid
		CS_IS_PTR_NULL(Component)
		// Check Material is Valid
		CS_IS_PTR_NULL(Material)
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
		using namespace NCsMaterial::NLibrary::NCached;

		const FString& Context = Str::SetSafe;

		return SetSafe(Context, Component, Material, Index, nullptr);
	}

	void FLibrary::SetChecked(const FString& Context, UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials)
	{
		// Check Component is Valid
		CS_IS_PTR_NULL_CHECKED(Component)

		const int32 Count		  = Component->GetNumMaterials();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Component (%s) material count (%d) != input material count (%d)"), *Context, *(Component->GetName()), Count, MaterialCount);

		ClearOverrideChecked(Context, Component);

		for (int32 I = 0; I < Count; ++I)
		{
			checkf(Materials[I], TEXT("%s: Materials[%d] is NULL."), *Context, I);

			Component->SetMaterial(I, Materials[I]);
		}
	}

	bool FLibrary::SetSafe(const FString& Context, UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check Component is Valid
		CS_IS_PTR_NULL(Component)

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
			if (!Materials[I])
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Materials[%d] is NULL."), *Context, I));
				return false;
			}
			Component->SetMaterial(I, Materials[I]);
		}
		return true;
	}

	bool FLibrary::SetSafe(UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials)
	{
		using namespace NCsMaterial::NLibrary::NCached;

		const FString& Context = Str::SetSafe;

		return SetSafe(Context, Component, Materials, nullptr);
	}

	void FLibrary::SetChecked(const FString& Context, UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		// Check Mesh is Valid
		CS_IS_PTR_NULL_CHECKED(Mesh)

		const int32 Count		  = Mesh->GetStaticMesh()->StaticMaterials.Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);

		ClearOverrideChecked(Context, Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		// Check Mesh is Valid
		CS_IS_PTR_NULL_CHECKED(Mesh)

		const int32 Count		  = Mesh->SkeletalMesh->Materials.Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->SkeletalMesh->GetName(), Count, MaterialCount);

		ClearOverrideChecked(Context, Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::ClearOverrideChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index)
	{
		CS_IS_PTR_NULL_CHECKED(Component)
		
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

	bool FLibrary::SafeClearOverride(const FString& Context, UPrimitiveComponent* Component, const int32& Index, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL(Component)
		
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
		CS_IS_PTR_NULL_CHECKED(Component)

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

	bool FLibrary::SafeClearOverride(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL(Component)

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
		CS_IS_PTR_NULL_CHECKED(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		if (Index < Count)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(Index)))
			{
				if (!Material->IsPendingKill())
					Material->IsPendingKill();
			}
			Mesh->OverrideMaterials.RemoveAt(Index, 1, false);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
	}

	bool FLibrary::SafeClearOverride(const FString& Context, UStaticMeshComponent* Mesh, const int32& Index, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Index, 0)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		if (Index < Count)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(Index)))
			{
				if (!Material->IsPendingKill())
					Material->IsPendingKill();
			}
			Mesh->OverrideMaterials.RemoveAt(Index, 1, false);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
		return true;
	}

	void FLibrary::ClearOverrideChecked(const FString& Context, UStaticMeshComponent* Mesh)
	{
		CS_IS_PTR_NULL_CHECKED(Mesh)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(I)))
			{
				if (!Material->IsPendingKill())
					Material->IsPendingKill();
			}
			Mesh->OverrideMaterials.RemoveAt(I, 1, false);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
	}

	bool FLibrary::SafeClearOverride(const FString& Context, UStaticMeshComponent* Mesh, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL(Mesh)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(I)))
			{
				if (!Material->IsPendingKill())
					Material->IsPendingKill();
			}
			Mesh->OverrideMaterials.RemoveAt(I, 1, false);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
		return true;
	}

	void FLibrary::ClearOverrideChecked(const FString& Context, USkeletalMeshComponent* Mesh, const int32& Index)
	{
		CS_IS_PTR_NULL_CHECKED(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		if (Index < Count)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(Index)))
			{
				if (!Material->IsPendingKill())
					Material->IsPendingKill();
			}
			Mesh->OverrideMaterials.RemoveAt(Index, 1, false);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
	}

	bool FLibrary::SafeClearOverride(const FString& Context, USkeletalMeshComponent* Mesh, const int32& Index, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL(Mesh)
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Index, 0)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		if (Index < Count)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(Index)))
			{
				if (!Material->IsPendingKill())
					Material->IsPendingKill();
			}
			Mesh->OverrideMaterials.RemoveAt(Index, 1, false);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
		return true;
	}

	void FLibrary::ClearOverrideChecked(const FString& Context, USkeletalMeshComponent* Mesh)
	{
		CS_IS_PTR_NULL_CHECKED(Mesh)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(I)))
			{
				if (!Material->IsPendingKill())
					Material->IsPendingKill();
			}
			Mesh->OverrideMaterials.RemoveAt(I, 1, false);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
	}

	bool FLibrary::SafeClearOverride(const FString& Context, USkeletalMeshComponent* Mesh, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL(Mesh)

		const int32 Count = Mesh->GetNumOverrideMaterials();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(I)))
			{
				if (!Material->IsPendingKill())
					Material->IsPendingKill();
			}
			Mesh->OverrideMaterials.RemoveAt(I, 1, false);
		}

		if (Count > 0)
			Mesh->MarkRenderStateDirty();
		return true;
	}

	// Scalar
	#pragma region

	bool FLibrary::IsScalarParameterValidChecked(const FString& Context, UMaterialInterface* Material, const FName& ParamName)
	{
		// Check Material is Valid
		CS_IS_PTR_NULL_CHECKED(Material)
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

	bool FLibrary::IsScalarParameterValid(const FString& Context, UMaterialInterface* Material, const FName& ParamName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check Material is Valid
		CS_IS_PTR_NULL(Material)
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
		using namespace NCsMaterial::NLibrary::NCached;

		const FString& Context = Str::IsScalarParameterValid;

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
		CS_IS_PTR_NULL_CHECKED(Material)
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
		checkf(0, TEXT("%s: Failed to find ParamName: %s in Material: %s with Parent: %s."), *Context, *(ParamName.ToString()), *(Material->GetName()));
		return false;
	}

	bool FLibrary::IsVectorParameterValid(const FString& Context, UMaterialInterface* Material, const FName& ParamName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check Material is Valid
		CS_IS_PTR_NULL(Material)
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
		using namespace NCsMaterial::NLibrary::NCached;

		const FString& Context = Str::IsVectorParameterValid;

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
		CS_IS_PTR_NULL_CHECKED(Material)
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
		checkf(0, TEXT("%s: Failed to find ParamName: %s in Material: %s with Parent: %s."), *Context, *(ParamName.ToString()), *(Material->GetName()));
		return false;
	}

	bool FLibrary::IsTextureParameterValid(const FString& Context, UMaterialInterface* Material, const FName& ParamName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check Material is Valid
		CS_IS_PTR_NULL(Material)
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
		using namespace NCsMaterial::NLibrary::NCached;

		const FString& Context = Str::IsTextureParameterValid;

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

	#pragma endregion Scalar

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
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, IsVectorParameterValid);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, SetSafeVectorParameterValue);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, IsTextureParameterValid);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, SetSafeTextureParameterValue);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, PlayAnim_Internal);
				}

				namespace Name
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(NCsMaterial::NMID::FLibrary, PlayAnim_Internal);
				}
			}
		}

		FLibrary::FLibrary() :
			Manager_AnimParams()
		{
		}

		FLibrary::~FLibrary()
		{
			Manager_AnimParams.Shutdown();
		}

		bool FLibrary::IsValidChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs)
		{
			const int32 Count = MIDs.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				checkf(MIDs[I] && !MIDs[I]->IsPendingKill(), TEXT("%s: MIDs[%d] is NULL or IsPendingKill."), *Context, I);
			}
			return true;
		}

		void FLibrary::SetChecked(const FString& Context, UPrimitiveComponent* Mesh, UMaterialInterface* Material, const int32& Index, UMaterialInstanceDynamic*& OutMID)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverrideChecked(Context, Mesh, Index);
			MaterialLibrary::IsValidChecked(Context, Mesh, Index);

			if (OutMID &&
				!OutMID->IsPendingKill())
			{
				OutMID->MarkPendingKill();
			}

			CS_IS_PTR_NULL_CHECKED(Material)

			OutMID = Mesh->CreateDynamicMaterialInstance(Index, Material);
		}

		bool FLibrary::SetSafe(const FString& Context, UPrimitiveComponent* Mesh, UMaterialInterface* Material, const int32& Index, UMaterialInstanceDynamic*& OutMID, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			if (!MaterialLibrary::SafeClearOverride(Context, Mesh, Index, Log))
				return false;
			if (!MaterialLibrary::IsValid(Context, Mesh, Index, Log))
				return false;

			if (OutMID &&
				!OutMID->IsPendingKill())
			{
				OutMID->MarkPendingKill();
			}

			CS_IS_PTR_NULL(Material)

			OutMID = Mesh->CreateDynamicMaterialInstance(Index, Material);
			return true;
		}

		void FLibrary::SetChecked(const FString& Context, UPrimitiveComponent* Mesh, const TArray<UMaterialInterface*>& Materials, TArray<UMaterialInstanceDynamic*>& OutMIDs)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverrideChecked(Context, Mesh);
			Destroy(OutMIDs);

			const int32 Count = Materials.Num();

			CS_RESET_ARRAY_CHECKED(OutMIDs, UMaterialInstanceDynamic, Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

				OutMIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
			}
		}

		bool FLibrary::SetSafe(const FString& Context, UPrimitiveComponent* Mesh, const TArray<UMaterialInterface*>& Materials, TArray<UMaterialInstanceDynamic*>& OutMIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			if (!MaterialLibrary::SafeClearOverride(Context, Mesh, Log))
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
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverrideChecked(Context, Mesh);
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
			CS_IS_PTR_NULL_CHECKED(Mesh)

			check(IsValidChecked(Context, MIDs));

			const int32 Count = MIDs.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				Mesh->SetMaterial(I, MIDs[I]);
			}
		}

		void FLibrary::SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& OutMIDs, const TArray<UMaterialInterface*>& Materials)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverrideChecked(Context, Mesh);
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
			CS_IS_PTR_NULL_CHECKED(Mesh)

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

				if (MID &&
					!MID->IsPendingKill())
				{
					MID->MarkPendingKill();
				}
				OutMIDs.RemoveAt(I, 1, false);
			}
		}

		// Scalar
		#pragma region

		bool FLibrary::IsScalarParameterValidChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			// Check MID is Valid
			CS_IS_PTR_NULL_CHECKED(MID)
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

		bool FLibrary::IsScalarParameterValid(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check MID is Valid
			CS_IS_PTR_NULL(MID)
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

		bool FLibrary::SetSafeScalarParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

		bool FLibrary::SetSafeScalarParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY(MIDs, UMaterialInstanceDynamic*)

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetSafeScalarParameterValue(Context, MID, ParamName, Value, Log);
			}
			return true;
		}

		bool FLibrary::SetSafeScalarParameterValue(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeScalarParameterValue;

			return SetSafeScalarParameterValue(Context, MIDs, ParamName, Value, nullptr);
		}

		float FLibrary::GetScalarParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			check(IsScalarParameterValidChecked(Context, MID, ParamName));

			return MID->K2_GetScalarParameterValue(ParamName);
		}

		#pragma endregion Scalar

		// Vector
		#pragma region

		bool FLibrary::IsVectorParameterValidChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			// Check MID is Valid
			CS_IS_PTR_NULL_CHECKED(MID)
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

		bool FLibrary::IsVectorParameterValid(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check MID is Valid
			CS_IS_PTR_NULL(MID)
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

		void FLibrary::SetVectorParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector& Value)
		{
			check(IsVectorParameterValidChecked(Context, MID, ParamName));

			MID->SetVectorParameterValue(ParamName, Value);
		}

		void FLibrary::SetVectorParameterValueChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector& Value)
		{
			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY_CHECKED(MIDs, UMaterialInstanceDynamic*)

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetVectorParameterValueChecked(Context, MID, ParamName, Value);
			}
		}

		bool FLibrary::SetSafeVectorParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (IsVectorParameterValid(Context, MID, ParamName, Log))
			{
				MID->SetVectorParameterValue(ParamName, Value);
				return true;
			}
			return false;
		}

		bool FLibrary::SetSafeVectorParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeVectorParameterValue;

			return SetSafeVectorParameterValue(Context, MID, ParamName, Value, nullptr);
		}

		bool FLibrary::SetSafeVectorParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY(MIDs, UMaterialInstanceDynamic*)

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetSafeVectorParameterValue(Context, MID, ParamName, Value, Log);
			}
			return true;
		}

		bool FLibrary::SetSafeVectorParameterValue(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector& Value)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::SetSafeVectorParameterValue;

			return SetSafeVectorParameterValue(Context, MIDs, ParamName, Value, nullptr);
		}

		void FLibrary::SetVectorParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value)
		{
			check(IsVectorParameterValidChecked(Context, MID, ParamName));

			MID->SetVectorParameterValue(ParamName, Value);
		}

		bool FLibrary::SetSafeVectorParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

		void FLibrary::SetVectorParameterValueChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value)
		{
			// Check MIDs is Valid
			CS_IS_TARRAY_EMPTY_CHECKED(MIDs, UMaterialInstanceDynamic*)

				for (UMaterialInstanceDynamic* MID : MIDs)
				{
					SetVectorParameterValueChecked(Context, MID, ParamName, Value);
				}
		}

		bool FLibrary::SetSafeVectorParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

		FLinearColor FLibrary::GetVectorParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			check(IsVectorParameterValidChecked(Context, MID, ParamName));

			return MID->K2_GetVectorParameterValue(ParamName);
		}

		#pragma endregion Vector

		// Texture
		#pragma region

		bool FLibrary::IsTextureParameterValidChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			// Check MID is Valid
			CS_IS_PTR_NULL_CHECKED(MID)
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

		bool FLibrary::IsTextureParameterValid(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check MID is Valid
			CS_IS_PTR_NULL(MID)
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

		bool FLibrary::SetSafeTextureParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, UTexture* Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

		bool FLibrary::SetSafeTextureParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, UTexture* Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

		UTexture* FLibrary::GetTextureParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			check(IsTextureParameterValidChecked(Context, MID, ParamName));

			return MID->K2_GetTextureParameterValue(ParamName);
		}

		#pragma endregion Scalar

		// Anim
		#pragma region

		#define ParamsResourceType NCsMaterial::NAnim::NParams::FResource
		#define ParamsType NCsMaterial::NAnim::NParams::FParams

		FCsRoutineHandle FLibrary::PlayAnimChecked(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

			ParamsType* P = Params->Get();

			check(P->IsValidChecked(Context));

			// Get Coroutine Scheduler
			UObject* ContextRoot = CoroutineSchedulerLibrary::GetContextRootChecked(Context, WorldContext);

			UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(ContextRoot);
			const FECsUpdateGroup& UpdateGroup = Params->Get()->GetGroup();
			// Allocate Payload
			typedef NCsCoroutine::NPayload::FImpl PayloadType;

			PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);
			// Setup Payload
			#define COROUTINE PlayAnim_Internal

			Payload->CoroutineImpl.BindStatic(&FLibrary::COROUTINE);
			Payload->StartTime = UCsManager_Time::Get(ContextRoot)->GetTime(UpdateGroup);
			Payload->Owner.SetObject(P->GetOwner());
			Payload->SetName(Str::COROUTINE);
			Payload->SetFName(Name::COROUTINE);

#			undef COROUTINE

			// Set End callback (to free any allocated references)
			typedef NCsCoroutine::FOnEnd OnEndType;

			OnEndType& OnEnd = Payload->OnEnds.AddDefaulted_GetRef();
			OnEnd.BindStatic(&FLibrary::PlayAnim_Internal_OnEnd);

			static const int32 RESOURCE = 0;
			Payload->SetValue_Void(RESOURCE, Params);

			return Scheduler->Start(Payload);
		}

		FCsRoutineHandle FLibrary::SafePlayAnim(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check Params are Valid.
			CS_IS_PTR_NULL_RET_VALUE(Params, FCsRoutineHandle::Invalid)
			// Check Params's Resource is Valid.
			if (!Params->Get())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Params's Resource is NULL."), *Context));
				return FCsRoutineHandle::Invalid;
			}

			if (!Params->Get()->IsValid(Context))
				return FCsRoutineHandle::Invalid;

			if (!Get().Manager_AnimParams.Contains(Params))
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Params has NOT been allocated from pool. Use the method that passes by const reference."), *Context));
				return FCsRoutineHandle::Invalid;
			}

			// Check to get Context Root for CoroutineScheduler
			{
				typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

				UObject* ContextRoot = CoroutineSchedulerLibrary::GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
				if (!ContextRoot)
					return FCsRoutineHandle::Invalid;
		#endif // #if WITH_EDITOR
			}
			return PlayAnimChecked(Context, WorldContext, Params);
		}

		#define AnimType NCsMaterial::NAnim::FAnim

		FCsRoutineHandle FLibrary::PlayAnimChecked(const FString& Context, const UObject* WorldContext, const AnimType& Anim, const TArray<UMaterialInstanceDynamic*>& MIDs, UObject* Owner, const FECsUpdateGroup& Group)
		{
			ParamsResourceType* Resource = Get().AllocateAnimParams();
			ParamsType* Params			 = Resource->Get();

			Params->Anim = Anim;
			Params->SetMIDs(MIDs);
			Params->SetOwner(Owner);
			Params->SetGroup(Group);

			return PlayAnimChecked(Context, WorldContext, Resource);
		}

		#undef AnimType

		char FLibrary::PlayAnim_Internal(FCsRoutine* R)
		{
			using namespace NCsMaterial::NMID::NLibrary::NCached;

			const FString& Context = Str::PlayAnim_Internal;

			static const int32 RESOURCE = 0;
			ParamsResourceType* Resource = R->GetValue_Void<ParamsResourceType>(RESOURCE);
			ParamsType* Params			 = Resource->Get();

			const TArray<UMaterialInstanceDynamic*>& MIDs = Params->ResolveAndGetMIDsChecked(Context);

			// Anim
			typedef NCsMaterial::NAnim::FAnim AnimType;

			const AnimType& Anim = Params->Anim;

			typedef NCsAnim::EPlayback PlaybackType;

			const PlaybackType& Playback = Params->Anim.GetPlayback();
			const bool LoopingForever	 = Params->Anim.IsLoopingForever();
			const int32 FrameCount		 = Anim.FrameCount;
			const int32& TotalCount		 = Anim.GetTotalCount();

			static const int32 COUNT = 0;
			int32& Count = R->GetValue_Int(COUNT);

			static const int32 FRAME_INDEX = 1;
			int32& FrameIndex = R->GetValue_Int(FRAME_INDEX);

			// Frames
			typedef NCsMaterial::NAnim::FFrame FrameType;

			const FrameType& Frame = Anim.Frames[FrameIndex];

			FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);
			ElapsedTime += R->DeltaTime;

			const float& Duration = Frame.GetDuration();
			float Percent		   = FMath::Clamp(ElapsedTime.Time / Duration, 0.0f, 1.0f);

			static const int32 DIRECTION = 2;
			int32& Direction = R->GetValue_Int(DIRECTION);

			// Play Animation
			CS_COROUTINE_BEGIN(R);

			FrameIndex = Anim.ShouldStartReverse() ? FrameCount - 1 : 0;
			Direction  = Anim.ShouldStartReverse() ? -1 : 1;

			ElapsedTime.Reset();

			Percent = 0.0f;

			do
			{
				{
					typedef NCsMaterial::NAnim::NParameter::FVectorType VectorType;
					typedef NCsMaterial::NAnim::NParameter::FScalarType ScalarType;

					// Vector
					for (const VectorType& Param : Frame.VectorParameters)
					{
						// TODO: HSV
						//FLinearColor::LerpUsingHSV()

						const FLinearColor& Start = Param.GetFrom();
						const FLinearColor& End	  = Param.GetTo();

						// If SAME, set END ONCE
						if (Start == End)
						{
							if (Percent == 0.0f)
							{
								SetVectorParameterValueChecked(Context, MIDs, Param.GetName(), End);
							}
						}
						else
						{
							const FLinearColor StartToEnd = End - Start;

							typedef NCsMath::FLibrary MathLibrary;

							float DistanceSq;
							float Distance;
							const FLinearColor Normal = MathLibrary::GetSafeNormal(StartToEnd, DistanceSq, Distance);
						
							const ECsEasingType& Easing = Param.GetEasing();
							const float Alpha			= MathLibrary::Ease(Easing, Percent, 0.0f, 1.0f, 1.0f);

							FLinearColor Current = Start + Alpha * Distance * Normal;

							SetVectorParameterValueChecked(Context, MIDs, Param.GetName(), Current);
						};
					}
					// Scalar
					for (const ScalarType& Param : Frame.ScalarParameters)
					{
						const float& Start = Param.GetFrom();
						const float& End   = Param.GetTo();

						// If SAME, set END ONCE
						if (Start == End)
						{
							if (Percent == 0.0f)
							{
								SetScalarParameterValueChecked(Context, MIDs, Param.GetName(), End);
							}
						}
						else
						{
							typedef NCsMath::FLibrary MathLibrary;

							const ECsEasingType& Easing = Param.GetEasing();
							const float Alpha			= MathLibrary::Ease(Easing, Percent, 0.0f, 1.0f, 1.0f);

							const float Delta = End - Start;
							float Final		  = Start + Alpha * Delta;

							SetScalarParameterValueChecked(Context, MIDs, Param.GetName(), Final);
						};
					}

					if (ElapsedTime.Time < Duration)
					{
						CS_COROUTINE_YIELD(R);	
					}
					else
					{
						// Vector
						for (const VectorType& Param : Frame.VectorParameters)
						{
							SetVectorParameterValueChecked(Context, MIDs, Param.GetName(), Param.GetTo());
						}
						// Float
						for (const ScalarType& Param : Frame.ScalarParameters)
						{
							SetScalarParameterValueChecked(Context, MIDs, Param.GetName(), Param.GetTo());
						}

						ElapsedTime.Reset();

						// Forward
						if (Playback == PlaybackType::Forward)
							++FrameIndex;
						// Reverse
						else
						if (Playback == PlaybackType::Reverse)
							--FrameIndex;
						// PingPong
						else
						if (Playback == PlaybackType::PingPong)
						{
							if (FrameIndex == FrameCount - 1)
							{
								Direction = -1;
							}
	
							FrameIndex += Direction;
						}
						// Loop
						else
						if (Playback == PlaybackType::Loop)
						{
							FrameIndex = (FrameIndex + 1) % FrameCount;
						}
						// Loop Reverse
						else
						if (Playback == PlaybackType::LoopReverse)
						{
							FrameIndex = FrameIndex == 0 ? FrameCount - 1 : FrameIndex - 1;
						}
						// TODO: LoopPingPong
						++Count;
					}
					//CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= Duration);
				}
			} while (LoopingForever || Count < TotalCount);

			CS_COROUTINE_END(R);
		}

		void FLibrary::PlayAnim_Internal_OnEnd(FCsRoutine* R)
		{
			static const int32 RESOURCE  = 0;
			ParamsResourceType* Resource = R->GetValue_Void<ParamsResourceType>(RESOURCE);
			ParamsType* Params			 = Resource->Get();
			Params->Reset();

			Get().Manager_AnimParams.Deallocate(Resource);
		}

		#undef ParamsResourceType
		#undef ParamsType

		#pragma endregion Anim
	}
}