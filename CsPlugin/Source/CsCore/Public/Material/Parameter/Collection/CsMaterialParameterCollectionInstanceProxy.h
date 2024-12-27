// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/CsTypes_Math.h"

class FMaterialParameterCollectionInstanceResource;
class FRHIUniformBuffer;
struct FRHIUniformBufferLayout;

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
					struct CSCORE_API FProxy final
					{
					public:

						FMaterialParameterCollectionInstanceResource* Resource;

						/** Unique identifier for the UMaterialParameterCollection that material shaders were compiled with. */
						FGuid* Id;

						FName* OwnerName;

						/** Uniform buffer containing the UMaterialParameterCollection default parameter values and UMaterialParameterCollectionInstance instance overrides. */
						/*FUniformBufferRHIRef*/TRefCountPtr<FRHIUniformBuffer>* UniformBuffer;

						/*FUniformBufferLayoutRHIRef*/TRefCountPtr<const FRHIUniformBufferLayout>* UniformBufferLayout;

						bool bComplete;

						FProxy() :
							Resource(nullptr),
							Id(nullptr),
							OwnerName(nullptr),
							UniformBuffer(nullptr),
							UniformBufferLayout(nullptr),
							bComplete(false)
						{
						}

						~FProxy(){}

						FORCEINLINE FGuid& GetId() { return *Id; }

						FORCEINLINE FName& GetOwnerName() { return *OwnerName; }

						FORCEINLINE /*FUniformBufferRHIRef*/TRefCountPtr<FRHIUniformBuffer>& GetUniformBuffer() { return *UniformBuffer; }

						FORCEINLINE /*FUniformBufferLayoutRHIRef*/TRefCountPtr<const FRHIUniformBufferLayout>& GetUniformBufferLayout() { return *UniformBufferLayout; }

						FORCEINLINE /*FUniformBufferLayoutRHIRef*/TRefCountPtr<const FRHIUniformBufferLayout>* GetUniformBufferLayoutPtr() { return UniformBufferLayout; }

						void Init(FMaterialParameterCollectionInstanceResource* InResource);

						void GameThread_UpdateContents(const FGuid& InId, const TArray<FVector4f>& Data, const FName& InOwnerName, bool bRecreateUniformBuffer);

						void RenderThread_UpdateContents(const FGuid& InId, const TArray<FVector4f>& Data, const FName& InOwnerName, bool bRecreateUniformBuffer);

						FORCEINLINE void StartUpdateContents() { bComplete = false; }
						FORCEINLINE bool IsComplete() const { return bComplete; }

						FORCEINLINE void Reset()
						{
							Resource = nullptr;
							Id = nullptr;
							OwnerName = nullptr;
							UniformBuffer = nullptr;
							UniformBufferLayout = nullptr;
							bComplete = false;
						}
					};
				}
			}
		}
	}
}

class UMaterialParameterCollection;

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NCollection
		{
			struct CSCORE_API FProxy final
			{
			private:

				using ResourceProxyType = NCsMaterial::NParameter::NCollection::NInstance::NResource::FProxy;

			public:

				UMaterialParameterCollection* Collection;

				/** The number ScalarParamterValues if it was packed in FVector4s. */
				int32 ScalarParameterValuesOffset;

				/** Values to be set on the uniform buffer */
				TArray<FVector4f> ParameterData;

				ResourceProxyType ResourceProxy;

				bool bComplete;

				FProxy() : 
					Collection(nullptr),
					ScalarParameterValuesOffset(0),
					ParameterData(),
					ResourceProxy(),
					bComplete(false)
				{
				}

				~FProxy(){}

				void Init(UMaterialParameterCollection* InCollection);

				void UpdateParamterData();

				FORCEINLINE void StartUpdateState() { bComplete = false; }
				FORCEINLINE bool IsComplete() const { return bComplete; }

				void GameThread_UpdateState(bool bRecreateUniformBuffer);
				void RenderThread_UpdateState();

				FORCEINLINE void Reset()
				{
					Collection = nullptr;
					ScalarParameterValuesOffset = 0;
					ParameterData.Reset(ParameterData.Max());
					ResourceProxy.Reset();
					bComplete = false;
				}
			};
		}
	}
}


class UMaterialParameterCollectionInstance;

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NCollection
		{
			namespace NInstance
			{
				struct CSCORE_API FProxy final
				{
				private:
				
					using ResourceProxyType = NCsMaterial::NParameter::NCollection::NInstance::NResource::FProxy;
					using MemberType = NCsVector4::EMember;

				public:

					UMaterialParameterCollectionInstance* Instance;

					/** Overrides for scalar parameter values. 
						Pointer to Instance->ScalarParamterValues. */
					TMap<FName, float>* ScalarParameterValues;

					TArray<float*> ScalarParameterValuesByIndex;

					/** The number ScalarParamterValues if it was packed in FVector4s. */
					int32 ScalarParameterValuesOffset;

					/** Overrides for vector parameter values. 
						Pointer to Instance->VectorParamterValues. */
					TMap<FName, FLinearColor>* VectorParameterValues;

					TArray<FLinearColor*> VectorParameterValuesByIndex;

					/** Values to be set on the uniform buffer */
					TArray<FVector4f> ParameterData;

					ResourceProxyType ResourceProxy;

					bool bDirty;

					bool bComplete;

					FProxy() : 
						Instance(nullptr),
						ScalarParameterValues(nullptr),
						ScalarParameterValuesByIndex(),
						ScalarParameterValuesOffset(0),
						VectorParameterValues(nullptr),
						VectorParameterValuesByIndex(),
						ParameterData(),
						ResourceProxy(),
						bDirty(false),
						bComplete(false)
					{
					}

					~FProxy(){}

					void Init(UMaterialParameterCollectionInstance* InInstance);

					FORCEINLINE const TMap<FName, float>& GetScalarParameterValues() const { return *ScalarParameterValues; }
					FORCEINLINE TMap<FName, float>& GetScalarParameterValues() { return *ScalarParameterValues; }

					FORCEINLINE void SetScalarParamterValue(const int32& Index, const float& Value)
					{
						*(ScalarParameterValuesByIndex[Index]) = Value;
						bDirty = true;
					}

					FORCEINLINE const TMap<FName, FLinearColor>& GetVectorParameterValues() const { return *VectorParameterValues; }
					FORCEINLINE TMap<FName, FLinearColor>& GetVectorParameterValues() { return *VectorParameterValues; }

					FORCEINLINE void SetVectorParameterValue(const int32& Index, const FLinearColor& Value)
					{
						*(VectorParameterValuesByIndex[Index]) = Value;
						bDirty = true;
					}
	
					FORCEINLINE void SetVectorParameterValue(const int32& Index, const MemberType& Member, const float& Value)
					{
						FLinearColor& C  = *(VectorParameterValuesByIndex[Index]);
						FVector4f V		 = C;
						V[(uint8)Member] = Value;
						C				 = FLinearColor(V);
						bDirty = true;
					}

					FORCEINLINE void SetVectorParameterValues(const int32& StartIndex, const TArray<FLinearColor>& Values)
					{
						const int32 Count = Values.Num();
						const int32 End   = StartIndex + Count;

						for (int32 I = StartIndex; I < End; ++I)
						{
							*(VectorParameterValuesByIndex[I]) = Values[I - StartIndex];
						}
						bDirty = true;
					}

					template<uint32 SIZE>
					FORCEINLINE void SetVectorParameterValues(const int32& StartIndex, const TArray<FLinearColor, TFixedAllocator<SIZE>>& Values)
					{
						const int32 Count = Values.Num();
						const int32 End = StartIndex + Count;

						for (int32 I = StartIndex; I < End; ++I)
						{
							*(VectorParameterValuesByIndex[I]) = Values[I - StartIndex];
						}
						bDirty = true;
					}

					FORCEINLINE void SetVectorParameterValuesAndEmpty(const int32& StartIndex, TArray<FLinearColor>& Values)
					{
						const int32 Count = Values.Num();
						const int32 End   = StartIndex + Count;
						int32 Index;

						for (int32 I = End - 1; I >= StartIndex; --I)
						{
							Index = I - StartIndex;

							*(VectorParameterValuesByIndex[I]) = Values[Index];
							Values.RemoveAt(Index, 1, false);
						}
						bDirty = true;
					}

					void UpdateParamterData();

					FORCEINLINE bool IsDirty() const { return bDirty; }
					FORCEINLINE void ClearDirty() { bDirty = false; }

					FORCEINLINE void StartUpdateState() { bComplete = false; }
					FORCEINLINE bool IsComplete() const { return bComplete; }

					void GameThread_UpdateState(bool bRecreateUniformBuffer);
					void RenderThread_UpdateState();

					FORCEINLINE void Reset()
					{
						Instance = nullptr;
						ScalarParameterValues = nullptr;
						ScalarParameterValuesByIndex.Reset(ScalarParameterValuesByIndex.Max());
						ScalarParameterValuesOffset = 0;
						VectorParameterValues = nullptr;
						VectorParameterValuesByIndex.Reset(VectorParameterValuesByIndex.Max());
						ParameterData.Reset(ParameterData.Max());
						ResourceProxy.Reset();
						bDirty = false;
						bComplete = false;
					}
				};
			}
		}
	}
}