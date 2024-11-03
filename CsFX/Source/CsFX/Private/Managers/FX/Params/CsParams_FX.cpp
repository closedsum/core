// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Params/CsParams_FX.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Components
#include "Components/SkeletalMeshComponent.h"

namespace NCsFX
{
	namespace NParameter
	{
		namespace NValue
		{
			namespace Ref
			{
				typedef EMValue EnumMapType;

				CSFX_API CS_ADD_TO_ENUM_MAP(Int);
				CSFX_API CS_ADD_TO_ENUM_MAP(Float);
				CSFX_API CS_ADD_TO_ENUM_MAP(Vector);
				CSFX_API CS_ADD_TO_ENUM_MAP_CUSTOM(EValue_MAX, "MAX");
			}

			CSFX_API const uint8 MAX = (uint8)Type::EValue_MAX;
		}
	}
}

namespace NCsFX
{
	namespace NParameter
	{
		namespace NDataInterface
		{
			namespace NSkeletalMesh
			{
				namespace NMethod
				{
					namespace Ref
					{
						typedef EMMethod EnumMapType;

						CSFX_API CS_ADD_TO_ENUM_MAP(Explicit);
						CSFX_API CS_ADD_TO_ENUM_MAP(Owner_RootComponent);
						CSFX_API CS_ADD_TO_ENUM_MAP(Parent_RootComponent);
						CSFX_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMethod_MAX, "MAX");
					}
				}
			}
		}
	}
}

namespace NCsFX
{
	namespace NParameter
	{
		namespace NDataInterface
		{
			namespace NSkeletalMesh
			{
				CS_DEFINE_STATIC_LOG_WARNING(FSkeletalMeshType, NCsFX::FLog::Warning);

				using MethodMapType = NCsFX::NParameter::NDataInterface::NSkeletalMesh::EMMethod;
				using MethodType = NCsFX::NParameter::NDataInterface::NSkeletalMesh::EMethod;

				bool FSkeletalMeshType::IsValidChecked(const FString& Context) const
				{
					CS_IS_NAME_NONE_CHECKED(GetName())

					const FString NameAsString = GetName().ToString();

					checkf(NameAsString.StartsWith(TEXT("User.")), TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Data Interface Parameter of type: Skeletal Mesh."), *Context, *NameAsString);

					CS_IS_ENUM_VALID_CHECKED(MethodMapType, GetMethod())
					CS_IS_PENDING_KILL_CHECKED(GetComponent())
					return true;
				}

				bool FSkeletalMeshType::IsValid(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_WARNING_COMMENT) const
				{
					CS_IS_NAME_NONE(GetName())

					const FString NameAsString = GetName().ToString();

					if (!NameAsString.StartsWith(TEXT("User.")))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Int Parameter Name."), *Context, *NameAsString));
						return false;
					}

					CS_IS_ENUM_VALID(MethodMapType, MethodType, GetMethod())
					CS_IS_PENDING_KILL(GetComponent())
					return true;
				}
			}
		}
	}
}