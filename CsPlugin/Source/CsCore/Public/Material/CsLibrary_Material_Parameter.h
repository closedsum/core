// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Materials/Material.h"

namespace NCsMaterial
{
	namespace NParameter
	{
		/**
		* Library of functions related to Material Parameters
		*/
		struct CSCORE_API FLibrary final
		{
		public:

			/**
			* Get all parameter infos of a given Type from Material.
			* 
			* @param Context			The calling context.
			* @param Material
			* @param Type
			* @param OutParameterInfos	(out)
			* @param OutParameterIds	(out)
			*/
			static void GetAllParameterInfoChecked(const FString& Context, UMaterial* Material, const EMaterialParameterType& Type, TArray<FMaterialParameterInfo>& OutParameterInfos, TArray<FGuid>& OutParameterIds);

			/**
			* Get all scalar parameter infos from Material.
			*
			* @param Context			The calling context.
			* @param Material
			* @param OutParameterInfos	(out)
			* @param OutParameterIds	(out)
			*/
			static void GetAllScalarParameterInfoChecked(const FString& Context, UMaterial* Material, TArray<FMaterialParameterInfo>& OutParameterInfos, TArray<FGuid>& OutParameterIds);

			/**
			* Get all vector parameter infos from Material.
			*
			* @param Context			The calling context.
			* @param Material
			* @param OutParameterInfos	(out)
			* @param OutParameterIds	(out)
			*/
			static void GetAllVectorParameterInfoChecked(const FString& Context, UMaterial* Material, TArray<FMaterialParameterInfo>& OutParameterInfos, TArray<FGuid>& OutParameterIds);

			/**
			* Get all texture parameter infos from Material.
			*
			* @param Context			The calling context.
			* @param Material
			* @param OutParameterInfos	(out)
			* @param OutParameterIds	(out)
			*/
			static void GetAllTextureParameterInfoChecked(const FString& Context, UMaterial* Material, TArray<FMaterialParameterInfo>& OutParameterInfos, TArray<FGuid>& OutParameterIds);
		};
	}
}