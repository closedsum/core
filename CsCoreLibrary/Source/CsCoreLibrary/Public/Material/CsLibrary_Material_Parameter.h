// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Materials/Material.h"

namespace NCsMaterial
{
	namespace NParameter
	{
		/**
		* Library of functions related to Material Parameters
		*/
		struct CSCORELIBRARY_API FLibrary final
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