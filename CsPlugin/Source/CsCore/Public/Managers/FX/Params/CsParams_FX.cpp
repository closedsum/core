// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Params/CsParams_FX.h"

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

				CSCORE_API CS_ADD_TO_ENUM_MAP(Int);
				CSCORE_API CS_ADD_TO_ENUM_MAP(Float);
				CSCORE_API CS_ADD_TO_ENUM_MAP(Vector);
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EValue_MAX, "MAX");
			}

			CSCORE_API const uint8 MAX = (uint8)Type::EValue_MAX;
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

						CSCORE_API CS_ADD_TO_ENUM_MAP(Explicit);
						CSCORE_API CS_ADD_TO_ENUM_MAP(Owner_RootComponent);
						CSCORE_API CS_ADD_TO_ENUM_MAP(Parent_RootComponent);
						CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMethod_MAX, "MAX");
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
				bool FSkeletalMeshType::IsValidChecked(const FString& Context) const
				{
					CS_IS_NAME_NONE_CHECKED(GetName())

					const FString NameAsString = GetName().ToString();

					checkf(NameAsString.StartsWith(TEXT("User.")), TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Data Interface Parameter of type: Skeletal Mesh."), *Context, *NameAsString);

					typedef NCsFX::NParameter::NDataInterface::NSkeletalMesh::EMMethod MethodMapType;
					typedef NCsFX::NParameter::NDataInterface::NSkeletalMesh::EMethod MethodType;

					CS_IS_ENUM_VALID_CHECKED(MethodMapType, GetMethod())
					CS_IS_PENDING_KILL_CHECKED(GetComponent())
					return true;
				}

				bool FSkeletalMeshType::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					CS_IS_NAME_NONE(GetName())

					const FString NameAsString = GetName().ToString();

					if (!NameAsString.StartsWith(TEXT("User.")))
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Int Parameter Name."), *Context, *NameAsString));
						return false;
					}

					typedef NCsFX::NParameter::NDataInterface::NSkeletalMesh::EMMethod MethodMapType;
					typedef NCsFX::NParameter::NDataInterface::NSkeletalMesh::EMethod MethodType;

					CS_IS_ENUM_VALID(MethodMapType, MethodType, GetMethod())
					CS_IS_PENDING_KILL(GetComponent())
					return true;
				}
			}
		}
	}
}