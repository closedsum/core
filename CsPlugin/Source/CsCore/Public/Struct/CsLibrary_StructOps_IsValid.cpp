// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Struct/CsLibrary_StructOps_IsValid.h"

// Struct
#include "Struct/CsStructOps_IsValid.h"

namespace NCsStruct
{
	namespace NOps
	{
		namespace NIsValid
		{
			bool FLibrary::IsValidChecked(const FString& Context, void* StructValue, const UStruct* Struct)
			{
				typedef NCsStruct::NOps::NIsValid::FTool ToolType;

				bool OutSuccess = false;
				bool Result = false;
				
				for (TFieldIterator<FProperty> It(Struct); It; ++It)
				{
					FProperty* Property = CastField<FProperty>(*It);

					// Struct
					if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
					{
						for (int32 I = 0; I < StructProperty->ArrayDim; ++I)
						{
							if (uint8* Value = StructProperty->ContainerPtrToValuePtr<uint8>(StructValue, I))
							{
								Result = ToolType::IsValidChecked(Context, Value, StructProperty->Struct, OutSuccess);

								if (!OutSuccess)
									Result = IsValidChecked(Context, Value, StructProperty->Struct);
								check(Result);
							}
						}
						continue;
					}
					// Array
					if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(*It))
					{
						// Struct
						if (FStructProperty* InnerStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
						{
							FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

							const int32 Count = Helper.Num();

							for (int32 I = 0; I < Count; ++I)
							{
								if (uint8* Value = Helper.GetRawPtr(I))
								{
									Result = ToolType::IsValidChecked(Context, Value, InnerStructProperty->Struct, OutSuccess);

									if (!OutSuccess)
										Result = IsValidChecked(Context, Value, InnerStructProperty->Struct);
									check(Result);
								}
							}
							continue;
						}
					}
					// Set
					if (FSetProperty* SetProperty = CastField<FSetProperty>(*It))
					{
						// Struct
						if (FStructProperty* ElementStructProperty = CastField<FStructProperty>(SetProperty->ElementProp))
						{
							FScriptSetHelper_InContainer Helper(SetProperty, StructValue);

							const int32 Count = Helper.Num();

							for (int32 I = 0; I < Count; ++I)
							{
								if (uint8* Value = Helper.GetElementPtr(I))
								{
									Result = ToolType::IsValidChecked(Context, Value, ElementStructProperty->Struct, OutSuccess);

									if (!OutSuccess)
										Result = IsValidChecked(Context, Value, ElementStructProperty->Struct);
									check(Result);
								}
							}
							continue;
						}
					}
					// Map
					if (FMapProperty* MapProperty = CastField<FMapProperty>(*It))
					{
						// Struct
						if (FStructProperty* ValueStructProperty = CastField<FStructProperty>(MapProperty->ValueProp))
						{
							FScriptMapHelper_InContainer Helper(MapProperty, StructValue);

							const int32 Count = Helper.Num();

							for (int32 I = 0; I < Count; ++I)
							{
								if (uint8* Value = Helper.GetValuePtr(I))
								{
									Result = ToolType::IsValidChecked(Context, Value, ValueStructProperty->Struct, OutSuccess);

									if (!OutSuccess)
										Result = IsValidChecked(Context, Value, ValueStructProperty->Struct);
									check(Result);
								}
							}
							continue;
						}
					}
				}
				return true;
			}

			bool FLibrary::IsValid(const FString& Context, void* StructValue, const UStruct* Struct, void(*Log)(const FString&))
			{
				typedef NCsStruct::NOps::NIsValid::FTool ToolType;

				bool OutSuccess = false;
				bool Result = false;
				
				for (TFieldIterator<FProperty> It(Struct); It; ++It)
				{
					FProperty* Property = CastField<FProperty>(*It);

					// Struct
					if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
					{
						for (int32 I = 0; I < StructProperty->ArrayDim; ++I)
						{
							if (uint8* Value = StructProperty->ContainerPtrToValuePtr<uint8>(StructValue, I))
							{
								Result = ToolType::IsValid(Context, Value, StructProperty->Struct, OutSuccess, Log);

								if (!OutSuccess)
									Result = IsValid(Context, Value, StructProperty->Struct, Log);
								if (!Result)
									return false;
							}
						}
						continue;
					}
					// Array
					if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(*It))
					{
						// Struct
						if (FStructProperty* InnerStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
						{
							FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

							const int32 Count = Helper.Num();

							for (int32 I = 0; I < Count; ++I)
							{
								if (uint8* Value = Helper.GetRawPtr(I))
								{
									Result = ToolType::IsValid(Context, Value, InnerStructProperty->Struct, OutSuccess, Log);

									if (!OutSuccess)
										Result = IsValid(Context, Value, InnerStructProperty->Struct, Log);
									if (!Result)
										return false;
								}
							}
							continue;
						}
					}
					// Set
					if (FSetProperty* SetProperty = CastField<FSetProperty>(*It))
					{
						// Struct
						if (FStructProperty* ElementStructProperty = CastField<FStructProperty>(SetProperty->ElementProp))
						{
							FScriptSetHelper_InContainer Helper(SetProperty, StructValue);

							const int32 Count = Helper.Num();

							for (int32 I = 0; I < Count; ++I)
							{
								if (uint8* Value = Helper.GetElementPtr(I))
								{
									Result = ToolType::IsValid(Context, Value, ElementStructProperty->Struct, OutSuccess, Log);

									if (!OutSuccess)
										Result = IsValid(Context, Value, ElementStructProperty->Struct, Log);
									if (!Result)
										return false;
								}
							}
							continue;
						}
					}
					// Map
					if (FMapProperty* MapProperty = CastField<FMapProperty>(*It))
					{
						// Struct
						if (FStructProperty* ValueStructProperty = CastField<FStructProperty>(MapProperty->ValueProp))
						{
							FScriptMapHelper_InContainer Helper(MapProperty, StructValue);

							const int32 Count = Helper.Num();

							for (int32 I = 0; I < Count; ++I)
							{
								if (uint8* Value = Helper.GetValuePtr(I))
								{
									Result = ToolType::IsValid(Context, Value, ValueStructProperty->Struct, OutSuccess, Log);

									if (!OutSuccess)
										Result = IsValid(Context, Value, ValueStructProperty->Struct, Log);
									if (!Result)
										return false;
								}
							}
							continue;
						}
					}
				}
				return true;
			}

			bool FLibrary::IsTopValidChecked(const FString& Context, void* StructValue, const UStruct* Struct)
			{
				typedef NCsStruct::NOps::NIsValid::FTool ToolType;

				bool OutSuccess = false;
				bool Result = false;
				
				for (TFieldIterator<FProperty> It(Struct); It; ++It)
				{
					FProperty* Property = CastField<FProperty>(*It);

					// Struct
					if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
					{
						for (int32 I = 0; I < StructProperty->ArrayDim; ++I)
						{
							if (uint8* Value = StructProperty->ContainerPtrToValuePtr<uint8>(StructValue, I))
							{
								Result = ToolType::IsTopValidChecked(Context, Value, StructProperty->Struct, OutSuccess);

								if (!OutSuccess)
									Result = IsTopValidChecked(Context, Value, StructProperty->Struct);
								check(Result);
							}
						}
						continue;
					}
					// Array
					if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(*It))
					{
						// Struct
						if (FStructProperty* InnerStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
						{
							FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

							const int32 Count = Helper.Num();

							for (int32 I = 0; I < Count; ++I)
							{
								if (uint8* Value = Helper.GetRawPtr(I))
								{
									Result = ToolType::IsTopValidChecked(Context, Value, InnerStructProperty->Struct, OutSuccess);

									if (!OutSuccess)
										Result = IsTopValidChecked(Context, Value, InnerStructProperty->Struct);
									check(Result);
								}
							}
							continue;
						}
					}
					// Set
					if (FSetProperty* SetProperty = CastField<FSetProperty>(*It))
					{
						// Struct
						if (FStructProperty* ElementStructProperty = CastField<FStructProperty>(SetProperty->ElementProp))
						{
							FScriptSetHelper_InContainer Helper(SetProperty, StructValue);

							const int32 Count = Helper.Num();

							for (int32 I = 0; I < Count; ++I)
							{
								if (uint8* Value = Helper.GetElementPtr(I))
								{
									Result = ToolType::IsTopValidChecked(Context, Value, ElementStructProperty->Struct, OutSuccess);

									if (!OutSuccess)
										Result = IsTopValidChecked(Context, Value, ElementStructProperty->Struct);
									check(Result);
								}
							}
							continue;
						}
					}
					// Map
					if (FMapProperty* MapProperty = CastField<FMapProperty>(*It))
					{
						// Struct
						if (FStructProperty* ValueStructProperty = CastField<FStructProperty>(MapProperty->ValueProp))
						{
							FScriptMapHelper_InContainer Helper(MapProperty, StructValue);

							const int32 Count = Helper.Num();

							for (int32 I = 0; I < Count; ++I)
							{
								if (uint8* Value = Helper.GetValuePtr(I))
								{
									Result = ToolType::IsTopValidChecked(Context, Value, ValueStructProperty->Struct, OutSuccess);

									if (!OutSuccess)
										Result = IsTopValidChecked(Context, Value, ValueStructProperty->Struct);
									check(Result);
								}
							}
							continue;
						}
					}
				}
				return true;
			}

			bool FLibrary::IsTopValid(const FString& Context, void* StructValue, const UStruct* Struct, void(*Log)(const FString&))
			{
				typedef NCsStruct::NOps::NIsValid::FTool ToolType;

				bool OutSuccess = false;
				bool Result = false;
				
				for (TFieldIterator<FProperty> It(Struct); It; ++It)
				{
					FProperty* Property = CastField<FProperty>(*It);

					// Struct
					if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
					{
						for (int32 I = 0; I < StructProperty->ArrayDim; ++I)
						{
							if (uint8* Value = StructProperty->ContainerPtrToValuePtr<uint8>(StructValue, I))
							{
								Result = ToolType::IsTopValid(Context, Value, StructProperty->Struct, OutSuccess, Log);

								if (!OutSuccess)
									Result = IsTopValid(Context, Value, StructProperty->Struct, Log);
								if (!Result)
									return false;
							}
						}
						continue;
					}
					// Array
					if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(*It))
					{
						// Struct
						if (FStructProperty* InnerStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
						{
							FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

							const int32 Count = Helper.Num();

							for (int32 I = 0; I < Count; ++I)
							{
								if (uint8* Value = Helper.GetRawPtr(I))
								{
									Result = ToolType::IsTopValid(Context, Value, InnerStructProperty->Struct, OutSuccess, Log);

									if (!OutSuccess)
										Result = IsTopValid(Context, Value, InnerStructProperty->Struct, Log);
									if (!Result)
										return false;
								}
							}
							continue;
						}
					}
					// Set
					if (FSetProperty* SetProperty = CastField<FSetProperty>(*It))
					{
						// Struct
						if (FStructProperty* ElementStructProperty = CastField<FStructProperty>(SetProperty->ElementProp))
						{
							FScriptSetHelper_InContainer Helper(SetProperty, StructValue);

							const int32 Count = Helper.Num();

							for (int32 I = 0; I < Count; ++I)
							{
								if (uint8* Value = Helper.GetElementPtr(I))
								{
									Result = ToolType::IsTopValid(Context, Value, ElementStructProperty->Struct, OutSuccess, Log);

									if (!OutSuccess)
										Result = IsTopValid(Context, Value, ElementStructProperty->Struct, Log);
									if (!Result)
										return false;
								}
							}
							continue;
						}
					}
					// Map
					if (FMapProperty* MapProperty = CastField<FMapProperty>(*It))
					{
						// Struct
						if (FStructProperty* ValueStructProperty = CastField<FStructProperty>(MapProperty->ValueProp))
						{
							FScriptMapHelper_InContainer Helper(MapProperty, StructValue);

							const int32 Count = Helper.Num();

							for (int32 I = 0; I < Count; ++I)
							{
								if (uint8* Value = Helper.GetValuePtr(I))
								{
									Result = ToolType::IsTopValid(Context, Value, ValueStructProperty->Struct, OutSuccess, Log);

									if (!OutSuccess)
										Result = IsTopValid(Context, Value, ValueStructProperty->Struct, Log);
									if (!Result)
										return false;
								}
							}
							continue;
						}
					}
				}
				return true;
			}
		}
	}
}