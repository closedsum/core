// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Struct/CsRegisterStructOpsData.h"

#include "CsStructOps_Data.h"
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
		namespace NData
		{
			void FRegister::Execute()
			{
				typedef NCsStruct::NOps::NData::FTool ToolType;

			#define REGISTER_UNLOAD_FN(__Struct) ToolType::Get().RegisterUnloadFn(__Struct::StaticStruct()->GetFName(), &__Struct::StructOps_Data_Unload)

				// Material
				{
					REGISTER_UNLOAD_FN(FCsMaterialInterface);
					REGISTER_UNLOAD_FN(FCsMaterialInstance);
					REGISTER_UNLOAD_FN(FCsMaterialInstanceConstant);
					REGISTER_UNLOAD_FN(FCsTArrayMaterialInterface);
					REGISTER_UNLOAD_FN(FCsTArrayMaterialInstanceConstant);
					REGISTER_UNLOAD_FN(FCsMaterialInterface_WithParameters);
					REGISTER_UNLOAD_FN(FCsMaterialInterface_WithRangeParameters);
					REGISTER_UNLOAD_FN(FCsMaterialParameterCollection);
				}
				// Static Mesh
				{
					REGISTER_UNLOAD_FN(FCsStaticMesh);
				}
				// Skeletal Mesh
				{
					REGISTER_UNLOAD_FN(FCsSkeletalMesh);
				}
				// Texture
				{
					REGISTER_UNLOAD_FN(FCsTexture);
					REGISTER_UNLOAD_FN(FCsTexture2D);
				}
				// Anim
				{
					REGISTER_UNLOAD_FN(FCsAnimSequence);
					REGISTER_UNLOAD_FN(FCsAnimSequenceInfo);
					REGISTER_UNLOAD_FN(FCsFpvAnimSequence);
					REGISTER_UNLOAD_FN(FCsAnimMontage);
					REGISTER_UNLOAD_FN(FCsAnimMontageInfo);
					REGISTER_UNLOAD_FN(FCsFpvAnimMontage);
					REGISTER_UNLOAD_FN(FCsTArrayAnimMontage);
					REGISTER_UNLOAD_FN(FCsAnimBlueprint);
					REGISTER_UNLOAD_FN(FCsFpvAnimBlueprint);
					REGISTER_UNLOAD_FN(FCsBlendSpace1D);
					REGISTER_UNLOAD_FN(FCsFpvBlendSpace1D);
					REGISTER_UNLOAD_FN(FCsBlendSpace);
					REGISTER_UNLOAD_FN(FCsFpvBlendSpace);
					REGISTER_UNLOAD_FN(FCsAimOffset);
					REGISTER_UNLOAD_FN(FCsFpvAimOffset);
				}
				// Curve
				{
					REGISTER_UNLOAD_FN(FCsCurveFloat);
				}

			#undef REGISTER_UNLOAD_FN
			}
		}
	}
}