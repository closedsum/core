// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Struct/CsRegisterStructOpsIsValid.h"

#include "CsStructOps_IsValid.h"
// Structs
#include "Material/CsTypes_Material.h"
#include "Types/CsTypes_StaticMesh.h"
#include "Types/CsTypes_SkeletalMesh.h"
#include "Types/CsTypes_Texture.h"
#include "Animation/CsTypes_Anim.h"
#include "Types/CsTypes_Curve.h"

namespace NCsStruct
{
	namespace NOps
	{
		namespace NIsValid
		{
			void FRegister::Execute()
			{
				typedef NCsStruct::NOps::NIsValid::FTool ToolType;

			#define REGISTER_IS_VALID_FNS(__Struct) ToolType::Get().RegisterIsValidCheckedFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_IsValidChecked); \
				ToolType::Get().RegisterIsValidFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_IsValid); \
				ToolType::Get().RegisterIsTopValidCheckedFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_IsTopValidChecked); \
				ToolType::Get().RegisterIsTopValidFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_IsTopValid);

				// Material
				{
					REGISTER_IS_VALID_FNS(FCsMaterialInterface)
					REGISTER_IS_VALID_FNS(FCsMaterialInstance);
					REGISTER_IS_VALID_FNS(FCsMaterialInstanceConstant);
					REGISTER_IS_VALID_FNS(FCsTArrayMaterialInterface);
					REGISTER_IS_VALID_FNS(FCsTArrayMaterialInstanceConstant);
					REGISTER_IS_VALID_FNS(FCsMaterialInterface_WithParameters);
					REGISTER_IS_VALID_FNS(FCsMaterialInterface_WithRangeParameters);
					REGISTER_IS_VALID_FNS(FCsMaterialParameterCollection);
				}
				// Static Mesh
				{
					REGISTER_IS_VALID_FNS(FCsStaticMesh);
				}
				// Skeletal Mesh
				{
					REGISTER_IS_VALID_FNS(FCsSkeletalMesh);
				}
				// Texture
				{
					REGISTER_IS_VALID_FNS(FCsTexture);
					REGISTER_IS_VALID_FNS(FCsTexture2D);
				}
				// Anim
				{
					REGISTER_IS_VALID_FNS(FCsAnimSequence);
					REGISTER_IS_VALID_FNS(FCsAnimSequenceInfo);
				//	REGISTER_UNLOAD_FN(FCsFpvAnimSequence);
					REGISTER_IS_VALID_FNS(FCsAnimMontage);
					REGISTER_IS_VALID_FNS(FCsAnimMontageInfo);
				//	REGISTER_UNLOAD_FN(FCsFpvAnimMontage);
					REGISTER_IS_VALID_FNS(FCsTArrayAnimMontage);
					REGISTER_IS_VALID_FNS(FCsAnimBlueprint);
				//	REGISTER_UNLOAD_FN(FCsFpvAnimBlueprint);
					REGISTER_IS_VALID_FNS(FCsBlendSpace1D);
				//	REGISTER_UNLOAD_FN(FCsFpvBlendSpace1D);
					REGISTER_IS_VALID_FNS(FCsBlendSpace);
				//	REGISTER_UNLOAD_FN(FCsFpvBlendSpace);
					REGISTER_IS_VALID_FNS(FCsAimOffset);
				//	REGISTER_UNLOAD_FN(FCsFpvAimOffset);
				}
				// Curve
				{
					REGISTER_IS_VALID_FNS(FCsCurveFloat)
				}

			#undef REGISTER_IS_VALID_FNS
			}
		}
	}
}