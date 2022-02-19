// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Material/CsLibrary_Material_Parameter.h"

// Library
#include "Library/CsLibrary_Array.h"
#include "Library/CsLibrary_Valid.h"

namespace NCsMaterial
{
	namespace NParameter
	{
		void FLibrary::GetAllParameterInfoChecked(const FString& Context, UMaterial* Material, const EMaterialParameterType& Type, TArray<FMaterialParameterInfo>& OutParameterInfos, TArray<FGuid>& OutParameterIds)
		{
			CS_IS_PTR_NULL_CHECKED(Material)

		#if WITH_EDITOR
			if (Type == EMaterialParameterType::Scalar)
				Material->GetAllScalarParameterInfo(OutParameterInfos, OutParameterIds);
			else
			if (Type == EMaterialParameterType::Vector)
				Material->GetAllVectorParameterInfo(OutParameterInfos, OutParameterIds);
			else
			if (Type == EMaterialParameterType::Texture)
				Material->GetAllTextureParameterInfo(OutParameterInfos, OutParameterIds);
		#else
			const FMaterialCachedExpressionData& CachedData = Material->GetCachedExpressionData();
			const FMaterialCachedParameterEntry& Entry		= CachedData.Parameters.GetParameterTypeEntry(Type);
			const int32 NumParameters						= Entry.NameHashes.Num();

			typedef NCsArray::FLibrary ArrayLibrary;

			ArrayLibrary::ResetChecked<FMaterialParameterInfo>(OutParameterInfos, NumParameters);
			ArrayLibrary::ResetChecked<FGuid>(OutParameterIds, NumParameters);

			CachedData.Parameters.GetAllParameterInfoOfType(Type, false, OutParameterInfos, OutParameterIds);
		#endif // #if WITH_EDITOR
		}

		void FLibrary::GetAllScalarParameterInfoChecked(const FString& Context, UMaterial* Material, TArray<FMaterialParameterInfo>& OutParameterInfos, TArray<FGuid>& OutParameterIds)
		{
			GetAllParameterInfoChecked(Context, Material, EMaterialParameterType::Scalar, OutParameterInfos, OutParameterIds);
		}

		void FLibrary::GetAllVectorParameterInfoChecked(const FString& Context, UMaterial* Material, TArray<FMaterialParameterInfo>& OutParameterInfos, TArray<FGuid>& OutParameterIds)
		{
			GetAllParameterInfoChecked(Context, Material, EMaterialParameterType::Vector, OutParameterInfos, OutParameterIds);
		}

		void FLibrary::GetAllTextureParameterInfoChecked(const FString& Context, UMaterial* Material, TArray<FMaterialParameterInfo>& OutParameterInfos, TArray<FGuid>& OutParameterIds)
		{
			GetAllParameterInfoChecked(Context, Material, EMaterialParameterType::Texture, OutParameterInfos, OutParameterIds);
		}
	}
}