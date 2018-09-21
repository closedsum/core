// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public static class FCgMath
    {
        #region "Constants"

        public static readonly float KINDA_SMALL_NUMBER = 0.0001f;

        public static readonly float INV_PI = 0.31830988618f;
        public static readonly float HALF_PI = 1.57079632679f;

        #endregion // Constants

        public static int Mod(int x, int m)
        {
            int r = x % m;
            return r < 0 ? r + m : r;
        }

        public static void SinCos(ref float scalarSin, ref float scalarCos, float value)
        {
            // Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
            float quotient = (INV_PI * 0.5f) * value;
            if (value >= 0.0f)
            {
                quotient = (float)((int)(quotient + 0.5f));
            }
            else
            {
                quotient = (float)((int)(quotient - 0.5f));
            }
            float y = value - (2.0f * Mathf.PI) * quotient;

            // Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
            float sign;
            if (y > HALF_PI)
            {
                y = Mathf.PI - y;
                sign = -1.0f;
            }
            else if (y < -HALF_PI)
            {
                y = -Mathf.PI - y;
                sign = -1.0f;
            }
            else
            {
                sign = +1.0f;
            }

            float y2 = y * y;

            // 11-degree minimax approximation
            scalarSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

            // 10-degree minimax approximation
            float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
            scalarCos = sign * p;
        }

        public static Vector3 RotateAngleAxis(Vector3 v, float deg, Vector3 axis)
        {
            float s = 0.0f, c = 0.0f;
            SinCos(ref s, ref c, Mathf.Deg2Rad * deg);

            float xx = axis.x * axis.x;
            float yy = axis.y * axis.y;
            float zz = axis.z * axis.z;

            float xy = axis.x * axis.y;
            float yz = axis.y * axis.z;
            float zx = axis.z * axis.x;

            float xs = axis.x * s;
            float ys = axis.y * s;
            float zs = axis.z * s;

            float omc = 1.0f - c;

            return new Vector3(
                (omc * xx + c) * v.x + (omc * xy - zs) * v.y + (omc * zx + ys) * v.z,
                (omc * xy + zs) * v.x + (omc * yy + c) * v.y + (omc * yz - xs) * v.z,
                (omc * zx - ys) * v.x + (omc * yz + xs) * v.y + (omc * zz + c) * v.z
                );
        }
    }

    public struct FCgTransform
    {
        public Vector3 Position;
        public Quaternion Rotation;
        public Vector3 Scale;

        public FCgTransform(Transform transform, bool local = false)
        {
            Position = local ? transform.localPosition : transform.position;
            Rotation = local ? transform.localRotation : transform.rotation;
            Scale = local ? transform.localScale : transform.lossyScale;
        }
    }
}
