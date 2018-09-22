// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public static class FCgMath
    {
        #region "Constants"

        public static readonly float KINDA_SMALL_NUMBER = 0.0001f;

        public static readonly float INV_PI = 0.31830988618f;
        public static readonly float HALF_PI = 1.57079632679f;
        public static readonly float TWO_PI = 6.283185307179586476925286766559f;
        public static readonly float PI_BY_2 = 1.5707963267948966192313216916398f;
        public static readonly float PI_BY_4 = 0.78539816339744830961566084581988f;
        public static readonly float THREE_PI_BY_4 = 2.3561944901923449288469825374596f;

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

        public static Vector3 VectorToAngles(Vector3 v)
        {
            Vector3 r;

            // Pitch
            r.x = Mathf.Atan2(v.z, Mathf.Sqrt(v.x * v.x + v.y * v.y)) * (180.0f / Mathf.PI);
            // Yaw
            r.y = Mathf.Atan2(v.y, v.x) * (180.0f / Mathf.PI);
            // Roll
            r.z = 0.0f;

            return r;
        }

        public static float VectorToYaw(Vector3 v)
        {
            float yaw;

            if (v.x == 0 && v.z == 0)
            {
                yaw = 0;
            }
            else
            {
                yaw = Mathf.Atan2(v.x, v.z) * Mathf.Rad2Deg;
                yaw += yaw >= 0 ? 0 : 360;
            }
            return yaw;
        }

        public static float FastVectorToYaw(Vector3 v)
        {
            float yaw;

            if (v.x == 0 && v.z == 0)
            {
                yaw = 0;
            }
            else
            {
                yaw = FastAtan2(v.x, v.z) * Mathf.Rad2Deg;
                yaw += yaw >= 0 ? 0 : 360;
            }
            return yaw;
        }

        public static void AnglesToVector(Vector3 angles, out Vector3 forward, out Vector3 right, out Vector3 up)
        {
            float sinPitch = Mathf.Sin(Mathf.Deg2Rad * angles.x);
            float cosPitch = Mathf.Cos(Mathf.Deg2Rad * angles.x);

            float sinYaw = Mathf.Sin(Mathf.Deg2Rad * angles.y);
            float cosYaw = Mathf.Cos(Mathf.Deg2Rad * angles.y);

            float sinRoll = Mathf.Sin(Mathf.Deg2Rad * angles.z);
            float cosRoll = Mathf.Cos(Mathf.Deg2Rad * angles.z);

            // Forward

            forward.z = cosPitch * cosYaw;
            forward.x = cosPitch * sinYaw;
            forward.y = -1 * sinPitch;

            // Right

            right.z = -1 * sinRoll * sinPitch * cosYaw + -1 * cosRoll * -1 * sinYaw;
            right.x = -1 * sinRoll * sinPitch * sinYaw + -1 * cosRoll * cosYaw;
            right.y = -1 * sinRoll * cosPitch;

            right *= -1;

            // Up

            up.z = cosRoll * sinPitch * cosYaw + -1 * sinRoll * -1 * sinYaw;
            up.x = cosRoll * sinPitch * sinYaw + -1 * sinRoll * cosYaw;
            up.y = cosRoll * cosPitch;
        }

        public static Vector3 AngleToForward(Vector3 angles)
        {
            float sinPitch = Mathf.Sin(Mathf.Deg2Rad * angles.x);
            float cosPitch = Mathf.Cos(Mathf.Deg2Rad * angles.x);

            float sinYaw = Mathf.Sin(Mathf.Deg2Rad * angles.y);
            float cosYaw = Mathf.Cos(Mathf.Deg2Rad * angles.y);

            return new Vector3(cosPitch * sinYaw, -1 * sinPitch, cosPitch * cosYaw);
        }

        public static void FastAnglesToVector(Vector3 angles, out Vector3 forward, out Vector3 right, out Vector3 up)
        {
            float sinPitch, cosPitch, sinYaw, cosYaw, sinRoll, cosRoll;

            FastSinCos(Mathf.Deg2Rad * angles.x, out sinPitch, out cosPitch);
            FastSinCos(Mathf.Deg2Rad * angles.y, out sinYaw, out cosYaw);
            FastSinCos(Mathf.Deg2Rad * angles.z, out sinRoll, out cosRoll);

            // Forward

            forward.z = cosPitch * cosYaw;
            forward.x = cosPitch * sinYaw;
            forward.y = -1 * sinPitch;

            // Right

            right.z = -1 * sinRoll * sinPitch * cosYaw + -1 * cosRoll * -1 * sinYaw;
            right.x = -1 * sinRoll * sinPitch * sinYaw + -1 * cosRoll * cosYaw;
            right.y = -1 * sinRoll * cosPitch;

            right *= -1;

            // Up

            up.z = cosRoll * sinPitch * cosYaw + -1 * sinRoll * -1 * sinYaw;
            up.x = cosRoll * sinPitch * sinYaw + -1 * sinRoll * cosYaw;
            up.y = cosRoll * cosPitch;
        }

        public static void FastSinCos(float x, out float fSin, out float fCos)
        {
            // always wrap input angle to -PI..PI

            if (x < -Mathf.PI)
                x += TWO_PI;
            else
            if (x > Mathf.PI)
                x -= TWO_PI;

            // compute sine

            if (x < 0)
                fSin = 1.27323954f * x + 0.405284735f * x * x;
            else
                fSin = 1.27323954f * x - 0.405284735f * x * x;

            // compute cosine: sin(x + PI/2) = cos(x)

            x += PI_BY_2;

            if (x > Mathf.PI)
                x -= TWO_PI;

            if (x < 0)
                fCos = 1.27323954f * x + 0.405284735f * x * x;
            else
                fCos = 1.27323954f * x - 0.405284735f * x * x;
        }

        public static float FastAtan2(float y, float x)
        {
            float r, angle;
            float absY = Mathf.Abs(y) + 1e-10f; // kludge to prevent 0/0 condition

            if (x < 0.0f)
            {
                r = (x + absY) / (absY - x);
                angle = THREE_PI_BY_4;
            }
            else
            {
                r = (x - absY) / (x + absY);
                angle = PI_BY_4;
            }

            angle += (0.1963f * r * r - 0.9817f) * r;

            // negate if in quad III or IV

            return (y < 0.0f) ? -angle : angle;
        }

        public static float GetAngleDelta(float angle1, float angle2)
        {
            int mag = (angle2 - angle1 > 0) ? 1 : -1;
            float deltaAngle = angle2 - angle1;

            return (Mathf.Abs(deltaAngle) > 180) ? -1 * mag * (360 - Mathf.Abs(deltaAngle)) : mag * Mathf.Abs(deltaAngle);
        }

        public static float ClampAngle360(float angle)
        {
            if (angle > 0)
            {
                while (angle > 360)
                {
                    angle -= 360;
                }
            }
            else
            if (angle < 0)
            {
                while (angle < 360)
                {
                    angle += 360;
                }
            }
            return angle;
        }

        public static float ClampAngle180(float angle)
        {
            while (angle > 180)
            {
                angle -= 360;
            }

            while (angle < -180)
            {
                angle += 360;
            }
            return angle;
        }

        public static bool IsSignSame(int x, int y)
        {
            if (x < 0 && y < 0) { return true; }
            if (x > 0 && y > 0) { return true; }
            if (x == 0 && y == 0) { return true; }
            return false;
        }
    }

    public enum ECgAxis
    {
        X, 
        Y,
        Z,
        MAX
    }

    [Serializable]
    public struct FCgTransform
    {
        #region "Constants"

        public static readonly FCgTransform Identity = new FCgTransform(Vector3.zero, Quaternion.identity, Vector3.zero);
        
        #endregion // Constants

        #region "Data Members"

        [SerializeField]
        public Vector3 Position;
        [NonSerialized]
        public Quaternion Rotation;
        [SerializeField]
        public Vector3 Euler;
        [SerializeField]
        public Vector3 Scale;

        #endregion // Data Members

        public FCgTransform(Vector3 position, Quaternion rotation, Vector3 scale)
        {
            Position = position;
            Rotation = rotation;
            Euler = Rotation.eulerAngles;
            Scale = scale;
        }

        public FCgTransform(Transform transform, bool local = false)
        {
            Position = local ? transform.localPosition : transform.position;
            Rotation = local ? transform.localRotation : transform.rotation;
            Euler = Rotation.eulerAngles;
            Scale = local ? transform.localScale : transform.lossyScale;
        }

        public void SetRotation(Vector3 euler)
        {
            Euler = euler;
            Rotation = Quaternion.Euler(euler);
        }

        public void SetRotation(Quaternion rotation)
        {
            Rotation = rotation;
            Euler = Rotation.eulerAngles;
        }
    }
}