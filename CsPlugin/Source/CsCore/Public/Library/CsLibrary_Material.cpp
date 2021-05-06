// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Material.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
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

	#pragma endregion Load

	bool FLibrary::IsValidChecked(const FString& Context, const TArray<UMaterialInterface*>& Materials)
	{
		// Check Materials is Valid
		CS_IS_ARRAY_EMPTY_CHECKED(Materials, UMaterialInterface*)

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
		CS_IS_ARRAY_EMPTY(Materials, UMaterialInterface*)

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

	void FLibrary::SetSafe(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check Component is Valid
		CS_IS_PTR_NULL_EXIT(Component)
		// Check Material is Valid
		CS_IS_PTR_NULL_EXIT(Material)
		// Check Index is Valid
		CS_IS_INT_GREATER_THAN_OR_EQUAL_EXIT(Index, 0)

		if (Index >= Component->GetNumMaterials())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Index: %d is NOT Valid for Component: %s with %d Material Slots."), *Context, Index, *(Component->GetName()), Component->GetNumMaterials()));
			return;
		}
		Component->SetMaterial(Index, Material);
	}

	void FLibrary::SetSafe(UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index)
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

	void FLibrary::SetSafe(const FString& Context, UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check Component is Valid
		CS_IS_PTR_NULL_EXIT(Component)

		const int32 Count		  = Component->GetNumMaterials();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mismatch between Component (%s) material count (%d) != input material count (%d)"), *Context, *(Component->GetName()), Count, MaterialCount));
			return;
		}

		ClearOverrideChecked(Context, Component);

		for (int32 I = 0; I < Count; ++I)
		{
			if (!Materials[I])
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Materials[%d] is NULL."), *Context, I));
				return;
			}
			Component->SetMaterial(I, Materials[I]);
		}
	}

	void FLibrary::SetSafe(UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials)
	{
		using namespace NCsMaterial::NLibrary::NCached;

		const FString& Context = Str::SetSafe;

		return SetSafe(Context, Component, Materials, nullptr);
	}

	void FLibrary::Set(UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		using namespace NCsMaterial::NLibrary::NCached;

		const FString& Context = Str::Set;

		// Check Mesh is Valid
		CS_IS_PTR_NULL_CHECKED(Mesh)

		const int32 Count		  = Mesh->GetStaticMesh()->StaticMaterials.Num();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);
			return;
		}

		ClearOverride(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			if (!Materials[Index])
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Materials[%d] is NULL."), *Context, Index);
			}

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::Set(UStaticMeshComponent* Mesh, const TArray<UMaterialInstanceConstant*>& Materials)
	{
		using namespace NCsMaterial::NLibrary::NCached;

		const FString& Context = Str::Set;

		// Check Mesh is Valid
		CS_IS_PTR_NULL_CHECKED(Mesh)

		const int32 Count		  = Mesh->GetStaticMesh()->StaticMaterials.Num();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);
			return;
		}

		ClearOverride(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			if (!Materials[Index])
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Materials[%d] is NULL."), *Context, Index);
			}

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::SetChecked(const FString& Context, UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		// Check Mesh is Valid
		CS_IS_PTR_NULL_CHECKED(Mesh)

		const int32 Count		  = Mesh->GetStaticMesh()->StaticMaterials.Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);

		ClearOverride(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::Set(USkeletalMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		using namespace NCsMaterial::NLibrary::NCached;

		const FString& Context = Str::Set;

		// Check Mesh is Valid
		CS_IS_PTR_NULL_CHECKED(Mesh)

		const int32 Count		  = Mesh->SkeletalMesh->Materials.Num();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->SkeletalMesh->GetName(), Count, MaterialCount);
			return;
		}

		ClearOverride(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			if (!Materials[Index])
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Materials[%d] is NULL."), *Context, Index);
			}
			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::Set(USkeletalMeshComponent* Mesh, const TArray<UMaterialInstanceConstant*>& Materials)
	{
		using namespace NCsMaterial::NLibrary::NCached;

		const FString& Context = Str::Set;

		// Check Mesh is Valid
		CS_IS_PTR_NULL_CHECKED(Mesh)

		const int32 Count		  = Mesh->SkeletalMesh->Materials.Num();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->SkeletalMesh->GetName(), Count, MaterialCount);
			return;
		}

		ClearOverride(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			if (!Materials[Index])
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Materials[%d] is NULL."), *Context, Index);
			}
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

		ClearOverride(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::ClearOverrideChecked(const FString& Context, UPrimitiveComponent* Component)
	{
		CS_IS_PTR_NULL_CHECKED(Component)

		if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Component))
		{
			ClearOverride(Mesh);
			return;
		}

		if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(Component))
		{
			ClearOverride(Mesh);
			return;
		}
		checkf(0, TEXT("%s: Component: %s with Class: %s is NOT of type: UStaticMeshComponent or USkeletalMeshComponent."), *Context, *(Component->GetName()), *(Component->GetClass()->GetName()));
	}

	void FLibrary::ClearOverride(UStaticMeshComponent* Mesh)
	{
		checkf(Mesh, TEXT("NCsMaterial::FLibrary::ClearOverride: Mesh is NULL."));

		int32 Count = Mesh->GetNumOverrideMaterials();

		for (int32 Index = 0; Index < Count; ++Index)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(Index)))
			{
				if (!Material->IsPendingKill())
					Material->IsPendingKill();
			}
		}
		Mesh->EmptyOverrideMaterials();
	}

	void FLibrary::ClearOverride(USkeletalMeshComponent* Mesh)
	{
		checkf(Mesh, TEXT("NCsMaterial::FLibrary::ClearOverride: Mesh is NULL."));

		int32 Count = Mesh->GetNumOverrideMaterials();

		for (int32 Index = 0; Index < Count; ++Index)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(Index)))
			{
				if (!Material->IsPendingKill())
					Material->IsPendingKill();
			}
		}
		Mesh->EmptyOverrideMaterials();
	}

	namespace NMID
	{
		namespace NCached 
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, IsScalarParameterValid);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, IsVectorParameterValid);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, SetSafeScalarParameterValue);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NMID::FLibrary, SetSafeVectorParameterValue);
			}
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

		void FLibrary::Set(UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverride(Mesh);
			Destroy(MIDs);

			const int32 Count = Materials.Num();

			MIDs.Reset(Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
			}
		}

		void FLibrary::Set(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<FSkeletalMaterial>& Materials)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverride(Mesh);
			Destroy(MIDs);

			const int32 Count = Materials.Num();

			MIDs.Reset(Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index].MaterialInterface));
			}
		}

		void FLibrary::Set(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInstanceConstant*>& Materials)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverride(Mesh);
			Destroy(MIDs);

			const int32 Count = Materials.Num();

			MIDs.Reset(Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
			}
		}

		void FLibrary::Set(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverride(Mesh);
			Destroy(MIDs);

			const int32 Count = Materials.Num();
	
			MIDs.Reset(Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
			}
		}

		void FLibrary::SetChecked(const FString& Context, UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverride(Mesh);
			Destroy(MIDs);

			const int32 Count = Materials.Num();

			MIDs.Reset(Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

				MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
			}
		}

		void FLibrary::SetChecked(const FString& Context, UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs)
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

		void FLibrary::SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverride(Mesh);
			Destroy(MIDs);

			const int32 Count = Materials.Num();

			MIDs.Reset(Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				UMaterialInterface* Material = Materials[Index];

				checkf(Material, TEXT("%s: Materials[%d] is NULL."), *Context, Index);

				MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Material));
			}
		}

		void FLibrary::SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs)
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

		void FLibrary::Destroy(TArray<UMaterialInstanceDynamic*>& MIDs)
		{
			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				if (MID &&
					!MID->IsPendingKill())
				{
					MID->MarkPendingKill();
				}
			}
			MIDs.SetNum(0, true);
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
			if (UMaterialInstance* MI = Cast<UMaterialInstance>(MID->Parent))
			{
				for (const FScalarParameterValue& Value : MI->ScalarParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}
			}
			// Material
			if (UMaterial* M = Cast<UMaterial>(MID->Parent))
			{
				TArray<FMaterialParameterInfo> Infos;
				TArray<FGuid> Ids;

				M->GetAllScalarParameterInfo(Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}

			}
			checkf(0, TEXT("%s: Failed to find ParamName: %s in MID: %s."), *Context, *(ParamName.ToString()), *(MID->GetName()));
			return false;
		}

		bool FLibrary::IsScalarParameterValid(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check MID is Valid
			CS_IS_PTR_NULL(MID)
			// Check ParamName is Valid
			CS_IS_NAME_NONE(ParamName)

			// MaterialInstance
			if (UMaterialInstance* MI = Cast<UMaterialInstance>(MID->Parent))
			{
				for (const FScalarParameterValue& Value : MI->ScalarParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}
			}
			// Material
			if (UMaterial* M = Cast<UMaterial>(MID->Parent))
			{
				TArray<FMaterialParameterInfo> Infos;
				TArray<FGuid> Ids;

				M->GetAllScalarParameterInfo(Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}
			}

			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find ParamName: %s in MID: %s."), *Context, *(ParamName.ToString()), *(MID->GetName())));
			return false;
		}

		bool FLibrary::IsScalarParameterValid(UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			using namespace NCached;

			const FString& Context = Str::IsScalarParameterValid;

			return IsScalarParameterValid(Context, MID, ParamName, nullptr);
		}

		void FLibrary::SetScalarParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value)
		{
			check(IsScalarParameterValidChecked(Context, MID, ParamName));

			MID->SetScalarParameterValue(ParamName, Value);
		}

		void FLibrary::SetScalarParameterValueChecked(const FString& Context, TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value)
		{
			// Check MIDs is Valid
			CS_IS_ARRAY_EMPTY_CHECKED(MIDs, UMaterialInstanceDynamic*)

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetScalarParameterValueChecked(Context, MID, ParamName, Value);
			}
		}

		void FLibrary::SetSafeScalarParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (IsScalarParameterValid(Context, MID, ParamName, Log))
			{
				MID->SetScalarParameterValue(ParamName, Value);
			}
		}

		void FLibrary::SetSafeScalarParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value)
		{
			using namespace NCached;

			const FString& Context = Str::SetSafeScalarParameterValue;

			SetSafeScalarParameterValue(Context, MID, ParamName, Value, nullptr);
		}

		void FLibrary::SetSafeScalarParameterValue(const FString& Context, TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check MIDs is Valid
			CS_IS_ARRAY_EMPTY_EXIT(MIDs, UMaterialInstanceDynamic*)

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetSafeScalarParameterValue(Context, MID, ParamName, Value, Log);
			}
		}

		void FLibrary::SetSafeScalarParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value)
		{
			using namespace NCached;

			const FString& Context = Str::SetSafeScalarParameterValue;

			SetSafeScalarParameterValue(Context, MIDs, ParamName, Value, nullptr);
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
			if (UMaterialInstance* MI = Cast<UMaterialInstance>(MID->Parent))
			{
				for (const FVectorParameterValue& Value : MI->VectorParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}
			}
			// Material
			if (UMaterial* M = Cast<UMaterial>(MID->Parent))
			{
				TArray<FMaterialParameterInfo> Infos;
				TArray<FGuid> Ids;

				M->GetAllVectorParameterInfo(Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}

			}
			checkf(0, TEXT("%s: Failed to find ParamName: %s in MID: %s."), *Context, *(ParamName.ToString()), *(MID->GetName()));
			return false;
		}

		bool FLibrary::IsVectorParameterValid(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check MID is Valid
			CS_IS_PTR_NULL(MID)
			// Check ParamName is Valid
			CS_IS_NAME_NONE(ParamName)

			// MaterialInstance
			if (UMaterialInstance* MI = Cast<UMaterialInstance>(MID->Parent))
			{
				for (const FVectorParameterValue& Value : MI->VectorParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}
			}
			// Material
			if (UMaterial* M = Cast<UMaterial>(MID->Parent))
			{
				TArray<FMaterialParameterInfo> Infos;
				TArray<FGuid> Ids;

				M->GetAllVectorParameterInfo(Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}

			}
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find ParamName: %s in MID: %s."), *Context, *(ParamName.ToString()), *(MID->GetName())));
			return false;
		}

		bool FLibrary::IsVectorParameterValid(UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			using namespace NCached;

			const FString& Context = Str::IsVectorParameterValid;

			return IsVectorParameterValid(Context, MID, ParamName, nullptr);
		}

		void FLibrary::SetVectorParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector& Value)
		{
			check(IsVectorParameterValidChecked(Context, MID, ParamName));

			MID->SetVectorParameterValue(ParamName, Value);
		}

		void FLibrary::SetVectorParameterValueChecked(const FString& Context, TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector& Value)
		{
			// Check MIDs is Valid
			CS_IS_ARRAY_EMPTY_CHECKED(MIDs, UMaterialInstanceDynamic*)

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetVectorParameterValueChecked(Context, MID, ParamName, Value);
			}
		}

		void FLibrary::SetSafeVectorParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (IsVectorParameterValid(Context, MID, ParamName, Log))
			{
				MID->SetVectorParameterValue(ParamName, Value);
			}
		}

		void FLibrary::SetSafeVectorParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector& Value)
		{
			using namespace NCached;

			const FString& Context = Str::SetSafeVectorParameterValue;

			SetSafeVectorParameterValue(Context, MID, ParamName, Value, nullptr);
		}

		void FLibrary::SetSafeVectorParameterValue(const FString& Context, TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check MIDs is Valid
			CS_IS_ARRAY_EMPTY_EXIT(MIDs, UMaterialInstanceDynamic*)

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetSafeVectorParameterValue(Context, MID, ParamName, Value, Log);
			}
		}

		void FLibrary::SetSafeVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector& Value)
		{
			using namespace NCached;

			const FString& Context = Str::SetSafeVectorParameterValue;

			SetSafeVectorParameterValue(Context, MIDs, ParamName, Value, nullptr);
		}

		void FLibrary::SetSafeVectorParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (IsVectorParameterValid(Context, MID, ParamName, Log))
			{
				MID->SetVectorParameterValue(ParamName, Value);
			}
		}

		void FLibrary::SetSafeVectorParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value)
		{
			using namespace NCached;

			const FString& Context = Str::SetSafeVectorParameterValue;

			SetSafeVectorParameterValue(Context, MID, ParamName, Value, nullptr);
		}

		void FLibrary::SetSafeVectorParameterValue(const FString& Context, TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check MIDs is Valid
			CS_IS_ARRAY_EMPTY_EXIT(MIDs, UMaterialInstanceDynamic*)

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetSafeVectorParameterValue(Context, MID, ParamName, Value, Log);
			}
		}

		void FLibrary::SetSafeVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value)
		{
			using namespace NCached;

			const FString& Context = Str::SetSafeVectorParameterValue;

			SetSafeVectorParameterValue(Context, MIDs, ParamName, Value, nullptr);
		}

	#pragma endregion Vector
	}
}