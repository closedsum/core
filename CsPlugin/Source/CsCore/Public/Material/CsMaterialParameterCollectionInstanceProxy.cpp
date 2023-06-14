// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Material/CsMaterialParameterCollectionInstanceProxy.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Material/CsLibrary_Material_Parameter_Collection.h"
#include "Library/CsLibrary_Valid.h"
// Material
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "UniformBuffer.h"
#include "ParameterCollection.h"

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NCollection
		{
			namespace NInstance
			{
				namespace NResource
				{
					namespace NProxy
					{
						namespace NCached
						{
							namespace Str
							{
								CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NParameter::NCollection::NInstance::NResource::FProxy, Init);
							}
						}
					}

					void FProxy::Init(FMaterialParameterCollectionInstanceResource* InResource)
					{
						using namespace NCsMaterial::NParameter::NCollection::NInstance::NResource::NProxy::NCached;

						const FString& Context = Str::Init;

						CS_IS_PTR_NULL_CHECKED(InResource);

						Resource = InResource;
						
						typedef NCsMaterial::NParameter::NCollection::FLibrary CollectionLibrary;

						Id					= CollectionLibrary::GetIdPtrChecked(Context, Resource);
						OwnerName			= CollectionLibrary::GetOwnerNamePtrChecked(Context, Resource);
						UniformBuffer		= CollectionLibrary::GetUniformBufferPtrChecked(Context, Resource);
						UniformBufferLayout = CollectionLibrary::GetUniformBufferLayoutPtrChecked(Context, Resource);
					}

					void FProxy::GameThread_UpdateContents(const FGuid& InGuid, const TArray<FVector4>& Data, const FName& InOwnerName, bool bRecreateUniformBuffer)
					{
						FProxy* Proxy = this;
						ENQUEUE_RENDER_COMMAND(UpdateCollectionCommand)(
							[InGuid, Data, InOwnerName, Proxy, bRecreateUniformBuffer](FRHICommandListImmediate& RHICmdList)
						{
							Proxy->RenderThread_UpdateContents(InGuid, Data, InOwnerName, bRecreateUniformBuffer);
						}
						);
					}

					void FProxy::RenderThread_UpdateContents(const FGuid& InId, const TArray<FVector4>& Data, const FName& InOwnerName, bool bRecreateUniformBuffer)
					{
						GetId()		   = InId;
						GetOwnerName() = InOwnerName;

						if (InId != FGuid() && Data.Num() > 0)
						{
							const uint32 NewSize = Data.GetTypeSize() * Data.Num();
							check(GetUniformBufferLayout().Resources.Num() == 0);

							if (!bRecreateUniformBuffer && IsValidRef(GetUniformBuffer()))
							{
								check(NewSize == GetUniformBufferLayout().ConstantBufferSize);
								check(GetUniformBuffer()->GetLayout() == GetUniformBufferLayout());
								RHIUpdateUniformBuffer(GetUniformBuffer(), Data.GetData());
							}
							else
							{
								GetUniformBufferLayout().ConstantBufferSize = NewSize;
								GetUniformBufferLayout().ComputeHash();
								GetUniformBuffer() = RHICreateUniformBuffer(Data.GetData(), GetUniformBufferLayout(), UniformBuffer_MultiFrame);
							}
						}
					}
				}
			}
		}
	}
}
namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NCollection
		{
			namespace NInstance
			{
				namespace NProxy
				{
					namespace NCached
					{
						namespace Str
						{
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NParameter::NCollection::NInstance::FProxy, Init);
						}
					}
				}

				void FProxy::Init(UMaterialParameterCollectionInstance* InInstance)
				{
					using namespace NCsMaterial::NParameter::NCollection::NInstance::NProxy::NCached;

					const FString& Context = Str::Init;

					CS_IS_PENDING_KILL_CHECKED(InInstance);

					Instance = InInstance;

					typedef NCsMaterial::NParameter::NCollection::FLibrary CollectionLibrary;

					ScalarParameterValuesPtr = CollectionLibrary::GetScalarParameterValuesPtrChecked(Context, Instance);

					// Populate ScalarParamterValues with ScalarParamters from Instance
					{
						const int32 Count = Instance->GetCollection()->ScalarParameters.Num();

						ScalarParameterValuesByIndex.Reset(Count);

						for (int32 I = 0; I < Count; ++I)
						{
							const FCollectionScalarParameter& Parameter = Instance->GetCollection()->ScalarParameters[I];
							
							float& Value = ScalarParameterValuesPtr->FindOrAdd(Parameter.ParameterName);
							Value		 = Parameter.DefaultValue;
						}

						for (int32 I = 0; I < Count; ++I)
						{
							const FCollectionScalarParameter& Parameter = Instance->GetCollection()->ScalarParameters[I];

							float& Value = GetScalarParameterValues()[Parameter.ParameterName];

							ScalarParameterValuesByIndex.Add(&Value);
						}
					}

					ScalarParameterValuesOffset = FMath::DivideAndRoundUp(GetScalarParameterValues().Num(), 4);

					VectorParameterValuesPtr = CollectionLibrary::GetVectorParameterValuesPtrChecked(Context, Instance);

					// Populate VectorParamterValues with VectorParamters from Instance
					{
						const int32 Count = Instance->GetCollection()->VectorParameters.Num();

						VectorParameterValuesByIndex.Reset(Count);

						for (int32 I = 0; I < Count; ++I)
						{
							const FCollectionVectorParameter& Parameter = Instance->GetCollection()->VectorParameters[I];
							
							FLinearColor& Value = VectorParameterValuesPtr->FindOrAdd(Parameter.ParameterName);
							Value				= Parameter.DefaultValue;
						}

						for (int32 I = 0; I < Count; ++I)
						{
							const FCollectionVectorParameter& Parameter = Instance->GetCollection()->VectorParameters[I];

							FLinearColor& Value = GetVectorParameterValues()[Parameter.ParameterName];

							VectorParameterValuesByIndex.Add(&Value);
						}
					}

					// Populate Parameter Data
					{
						const int32 Count = ScalarParameterValuesOffset + GetVectorParameterValues().Num();

						ParameterData.Reset(Count);

						for (int32 I = 0; I < Count; ++I)
						{
							ParameterData.Add(FVector4(0.0f, 0.0f, 0.0f, 0.0f));
						}
						UpdateParamterData();
					}
					
					ResourceProxy.Init(Instance->GetResource());
					
					GameThread_UpdateRenderState(true);
				}

				void FProxy::UpdateParamterData()
				{
					// Scalar
					{
						const int32 Count = ScalarParameterValuesByIndex.Num();

						int32 VectorIndex;
						int32 VectorMemberIndex;

						for (int32 I = 0; I < Count; ++I)
						{
							float* ValuePtr  = ScalarParameterValuesByIndex[I];

							VectorIndex					   = I / 4;
							VectorMemberIndex			   = I % 4;
							FVector4& VectorValue		   = ParameterData[VectorIndex];
							VectorValue[VectorMemberIndex] = *ValuePtr;
						}
					}
					// Vector
					{
						const int32 Count = VectorParameterValuesByIndex.Num();

						for (int32 I = 0; I < Count; ++I)
						{
							FLinearColor* ValuePtr = VectorParameterValuesByIndex[I];

							ParameterData[ScalarParameterValuesOffset + I] = *ValuePtr;
						}
					}
				}

				void FProxy::GameThread_UpdateRenderState(bool bRecreateUniformBuffer)
				{
					const UMaterialParameterCollection* Collection = Instance->GetCollection();
					const FName OwnerName						   = Instance->GetFName();

					ResourceProxy.GameThread_UpdateContents(Collection ? Collection->StateId : FGuid(), ParameterData, OwnerName, bRecreateUniformBuffer);

					/*
					const UMaterialParameterCollection* Collection = Instance->GetCollection();
					const FGuid InId							   = Collection ? Collection->StateId : FGuid();
					const TArray<FVector4>& Data				   = ParameterData;
					const FName InOwnerName						   = Instance->GetFName();

					FMaterialParameterCollectionInstanceResource* Resource = const_cast<FMaterialParameterCollectionInstanceResource*>(Instance->GetResource());

					Resource->GameThread_UpdateContents(InId, Data, InOwnerName, bRecreateUniformBuffer);
					*/
				}

				void FProxy::UpdateRenderState()
				{
					const UMaterialParameterCollection* Collection = Instance->GetCollection();
					const FName OwnerName						   = Instance->GetFName();

					ResourceProxy.RenderThread_UpdateContents(Collection ? Collection->StateId : FGuid(), ParameterData, OwnerName, false);
				}
			}
		}
	}
}