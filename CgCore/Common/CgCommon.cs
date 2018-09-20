// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public static class FCgCommon
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

        public static float BytesToKilobytes(int bytes)
        {
            return bytes * Mathf.Pow(10.0f, -3.0f);
        }

        public static float BytesToMegabytes(int bytes)
        {
            return bytes * Mathf.Pow(10.0f, -6.0f);
        }

        public static int KilobytesToBytes(float kilobytes)
        {
            return Mathf.FloorToInt(kilobytes * Mathf.Pow(10.0f, 3.0f));
        }

        #region "Coroutine"

        public static bool CoroutineStopCondition_CheckMonoObject(FCgRoutine r)
        {
            MonoBehaviour mb = r.Owner.Get<MonoBehaviour>();

            if (mb != null)
            {
                return true;
            }
            return false;
        }

        #endregion // Coroutine

        #region "List"

        public static void ShuffleList<T>(ref List<T> list)
        {
            int count = list.Count;

            for (int index = count; index > 1; --index)
            {
                int j = UnityEngine.Random.Range(0, index - 1);

                T temp          = list[j];
                list[j]         = list[index - 1];
                list[index - 1] = temp;
            }
        }

        #endregion // List

        #region "Local"

        public static MCgPlayerController GetLocalPlayerController(int index = 0)
        {
            MCgGameState gamestate = MCgGameInstance.Get().GameState;

            return gamestate.PlayerControllers.Count > index ? gamestate.PlayerControllers[index] : null;
        }

        public static T GetLocalPlayerController<T>(int index = 0)
            where T : MCgPlayerController
        {
            return (T)GetLocalPlayerController(index);
        }

        public static MCgPlayerState GetLocalPlayerState(int index = 0)
        {
            MCgPlayerController controller = GetLocalPlayerController(index);

            if (controller == null)
                return null;

            return controller.PlayerState;
        }

        public static T GetLocalPlayerState<T>(int index = 0)
            where T : MCgPlayerState
        {
            return (T)GetLocalPlayerState(index);
        }

        public static FCgManager_Input GetLocalManager_Input(int index = 0)
        {
            MCgPlayerController controller = GetLocalPlayerController(index);

            if (controller == null)
                return null;

            return controller.Manager_Input;
        }

        public static T GetLocalManager_Input<T>(int index = 0)
            where T : FCgManager_Input
        {
            return (T)GetLocalManager_Input(index);
        }

        public static FCgHud GetLocalHud(int index = 0)
        {
            MCgPlayerController controller = GetLocalPlayerController(index);

            if (controller == null)
                return null;

            return controller.Hud;
        }

        public static T GetLocalHud<T>(int index = 0)
            where T : FCgHud
        {
            return (T)GetLocalHud(index);
        }

        #endregion // Local 
    }
}