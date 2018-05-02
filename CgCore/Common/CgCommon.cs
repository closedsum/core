// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public static class CgCommon
    {
        public static bool IsNumericType(object o)
        {
            switch (Type.GetTypeCode(o.GetType()))
            {
                case TypeCode.Byte:
                case TypeCode.SByte:
                case TypeCode.UInt16:
                case TypeCode.UInt32:
                case TypeCode.UInt64:
                case TypeCode.Int16:
                case TypeCode.Int32:
                case TypeCode.Int64:
                case TypeCode.Decimal:
                case TypeCode.Double:
                case TypeCode.Single:
                    return true;
                default:
                    return false;
            }
        }

        public static string NumericTypeToString(object o)
        {
            switch (Type.GetTypeCode(o.GetType()))
            {
                case TypeCode.Byte: return "" + (byte)o;
                case TypeCode.SByte: return "" + (sbyte)o;
                case TypeCode.UInt16: return "" + (ushort)o;
                case TypeCode.UInt32: return "" + (uint)o;
                case TypeCode.UInt64: return "" + (ulong)o;
                case TypeCode.Int16: return "" + (short)o;
                case TypeCode.Int32: return "" + (int)o;
                case TypeCode.Int64: return "" + (long)o;
                case TypeCode.Decimal: return "" + (decimal)o;
                case TypeCode.Double: return "" + (double)o;
                case TypeCode.Single: return "" + (float)o;
                default:
                    return "";
            }
        }
    }
}