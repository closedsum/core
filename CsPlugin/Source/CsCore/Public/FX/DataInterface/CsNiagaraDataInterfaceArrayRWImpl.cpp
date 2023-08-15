//// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
//#include "FX/DataInterface/CsNiagaraDataInterfaceArrayRWImpl.h"
//
//const FName FCsNiagaraDataInterfaceArrayRWImplHelper::Function_LengthName(TEXT("Length"));
//const FName FCsNiagaraDataInterfaceArrayRWImplHelper::Function_IsValidIndexName(TEXT("IsValidIndex"));
//const FName FCsNiagaraDataInterfaceArrayRWImplHelper::Function_LastIndexName(TEXT("LastIndex"));
//const FName FCsNiagaraDataInterfaceArrayRWImplHelper::Function_GetName(TEXT("Get"));
//
//const FName FCsNiagaraDataInterfaceArrayRWImplHelper::Function_ClearName(TEXT("Clear"));
//const FName FCsNiagaraDataInterfaceArrayRWImplHelper::Function_ResizeName(TEXT("Resize"));
//const FName FCsNiagaraDataInterfaceArrayRWImplHelper::Function_SetArrayElemName(TEXT("SetArrayElem"));
//const FName FCsNiagaraDataInterfaceArrayRWImplHelper::Function_AddName(TEXT("Add"));
//const FName FCsNiagaraDataInterfaceArrayRWImplHelper::Function_RemoveLastElemName(TEXT("RemoveLastElem"));
//
//FString FCsNiagaraDataInterfaceArrayRWImplHelper::GetBufferName(const FString& InterfaceName)
//{
//	return TEXT("ArrayBuffer_") + InterfaceName;
//}
//
//FString FCsNiagaraDataInterfaceArrayRWImplHelper::GetBufferSizeName(const FString& InterfaceName)
//{
//	return TEXT("ArrayBufferSize_") + InterfaceName;
//}
//
//#if WITH_EDITORONLY_DATA
//bool FCsNiagaraDataInterfaceArrayRWImplHelper::UpgradeFunctionCall(FNiagaraFunctionSignature& FunctionSignature)
//{
//	bool bModified = false;
//
//	static const TPair<FName, FName> NodeRenames[] =
//	{
//		MakeTuple(FName("GetNum"),			FCsNiagaraDataInterfaceArrayRWImplHelper::Function_LengthName),
//		MakeTuple(FName("GetValue"),		FCsNiagaraDataInterfaceArrayRWImplHelper::Function_GetName),
//		MakeTuple(FName("Reset"),			FCsNiagaraDataInterfaceArrayRWImplHelper::Function_ClearName),
//		MakeTuple(FName("SetNum"),			FCsNiagaraDataInterfaceArrayRWImplHelper::Function_ResizeName),
//		MakeTuple(FName("SetValue"),		FCsNiagaraDataInterfaceArrayRWImplHelper::Function_SetArrayElemName),
//		MakeTuple(FName("PushValue"),		FCsNiagaraDataInterfaceArrayRWImplHelper::Function_AddName),
//		MakeTuple(FName("PopValue"),		FCsNiagaraDataInterfaceArrayRWImplHelper::Function_RemoveLastElemName),
//	};
//
//	for (const auto& Pair : NodeRenames)
//	{
//		if (Pair.Key == FunctionSignature.Name)
//		{
//			FunctionSignature.Name = Pair.Value;
//			bModified = true;
//			break;
//		}
//	}
//
//	return bModified;
//}
//#endif
//
//IMPLEMENT_TYPE_LAYOUT(FCsNiagaraDataInterfaceParametersCS_ArrayRWImpl);
