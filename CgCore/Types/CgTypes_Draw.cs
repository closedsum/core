namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public enum ECgGizmoDrawShape : byte
    {
        Line,
        Ray,
        Cube,
        Sphere,
        Frustrum,
        MAX
    }

    public sealed class ECgGizmoDrawShapeEqualityComparer : IEqualityComparer<ECgGizmoDrawShape>
    {
        public bool Equals(ECgGizmoDrawShape lhs, ECgGizmoDrawShape rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgGizmoDrawShape x)
        {
            return x.GetHashCode();
        }
    }

    public class FCgGizmoDrawLineParams
    {
        public Vector3 From;
        public Vector3 To;

        public FCgGizmoDrawLineParams()
        {
            Reset();
        }

        public void Reset()
        {
            From = Vector3.zero;
            To = Vector3.zero;
        }

        public void Set(Vector3 from, Vector3 to)
        {
            From = from;
            To = to;
        }
    }

    public class FCgGizmoDrawRayParams
    {
        public Vector3 From;
        public Vector3 Direction;

        public FCgGizmoDrawRayParams()
        {
            Reset();
        }

        public void Reset()
        {
            From = Vector3.zero;
            Direction = Vector3.zero;
        }

        public void Set(Vector3 from, Vector3 direction)
        {
            From = from;
            Direction = direction;
        }
    }

    public class FCgGizmoDrawCubeParams
    {
        public Vector3 Center;
        public Vector3 Size;

        public FCgGizmoDrawCubeParams()
        {
            Reset();
        }

        public void Reset()
        {
            Center = Vector3.zero;
            Size = Vector3.one;
        }

        public void Set(Vector3 center, Vector3 size)
        {
            Center = center;
            Size = size;
        }
    }

    public class FCgGizmoDrawSphereParams
    {
        public Vector3 Center;
        public float Radius;

        public FCgGizmoDrawSphereParams()
        {
            Reset();
        }

        public void Reset()
        {
            Center = Vector3.zero;
            Radius = 1.0f;
        }

        public void Set(Vector3 center, float radius)
        {
            Center = center;
            Radius = radius;
        }
    }

    public class FCgGizmoDrawFrustrumParams
    {
        public Vector3 Center;
        public float Fov;
        public float MaxRange;
        public float MinRange;
        public float Aspect;

        public FCgGizmoDrawFrustrumParams()
        {
            Reset();
        }

        public void Reset()
        {
            Center = Vector3.zero;
            Fov = 45.0f;
            MaxRange = 1.0f;
            MinRange = 0.0f;
            Aspect = 1.0f;
        }

        public void Set(Vector3 center, float fov, float maxRange, float minRange, float aspect)
        {
            Center = center;
            Fov = fov;
            MaxRange = maxRange;
            MinRange = minRange;
            Aspect = aspect;
        }
    }

    public class FCgGizmoDrawRequest
    {
        public sealed class FFrameType : TCgProperty<int> { }
        public sealed class FTimeType : TCgProperty<float> { }
        public sealed class FBoolType : TCgProperty<bool> { }

        #region "Data Members"

        public bool bAllocated;

        public ECgGizmoDrawShape Shape;

        public bool bWire;

        public FCgGizmoDrawLineParams LineParams;
        public FCgGizmoDrawRayParams RayParams;
        public FCgGizmoDrawCubeParams CubeParams;
        public FCgGizmoDrawSphereParams SphereParams;
        public FCgGizmoDrawFrustrumParams FrustrumParams;

        public Color DrawColor;

        // Frame
        public bool bWaitForFrame;
        public int WaitForFrameCounter;
        public int WaitForFrame;
        public FFrameType WaitForFrameType;
        // Time
        public bool bWaitForTime;
        public float WaitForTimeTimer;
        public float WaitForTime;
        public FTimeType WaitForTimeType;
        // Flag
        public bool bWaitForFlag;
        public FBoolType WaitForBoolType;
        public ICgFlag WaitForFlagType;

        #endregion // Data Members

        public FCgGizmoDrawRequest()
        {
            LineParams = new FCgGizmoDrawLineParams();
            RayParams = new FCgGizmoDrawRayParams();
            CubeParams = new FCgGizmoDrawCubeParams();
            SphereParams = new FCgGizmoDrawSphereParams();
            FrustrumParams = new FCgGizmoDrawFrustrumParams();

            Reset();
        }

        public void Reset()
        {
            bAllocated = false;
            Shape = ECgGizmoDrawShape.MAX;
            bWire = false;

            LineParams.Reset();
            RayParams.Reset();
            CubeParams.Reset();
            SphereParams.Reset();
            FrustrumParams.Reset();

            DrawColor = Color.black;
            // Frame
            bWaitForFrame = false;
            WaitForFrameCounter = 0;
            WaitForFrame = 0;
            WaitForFrameType = null;
            // Time
            bWaitForTime = false;
            WaitForTimeTimer = 0.0f;
            WaitForTime = 0.0f;
            WaitForTimeType = null;
            // Flag
            bWaitForFlag = false;
            WaitForBoolType = null;
            WaitForFlagType = null;
        }

        public bool HasCompleted()
        {
            // Frame
            // Time
            if (bWaitForTime)
            {
                if (WaitForTimeType != null)
                {
                    WaitForTime = WaitForTimeType.Get();

                    if (WaitForTime < 0.0f)
                    {
                        WaitForTime = 0.0f;
                        WaitForTimeType = null;

                        FCgDebug.LogWarning("FCgGizmoDrawRequest.HasCompleted: WaitForTimeType of type 'FCgGizmoDrawRequest.FTimeType' is used for WaitForTime. WaitForTimeType value must be >= 0.0f.");
                    }
                }
                return WaitForTimeTimer >= WaitForTime;
            }
            // Flag
            return true;
        }

        public void Draw()
        {
            Gizmos.color = DrawColor;
            FCgDebug.Log("drawing" + LineParams.From.ToString() + " " + LineParams.To.ToString());
            // Line
            if (Shape == ECgGizmoDrawShape.Line)
                Gizmos.DrawLine(LineParams.From, LineParams.To);
            // Ray
            else
            if (Shape == ECgGizmoDrawShape.Ray)
                Gizmos.DrawRay(RayParams.From, RayParams.Direction);
            // Cube
            else
            if (Shape == ECgGizmoDrawShape.Cube)
            {
                if (bWire)
                    Gizmos.DrawWireCube(CubeParams.Center, CubeParams.Size);
                else
                    Gizmos.DrawCube(CubeParams.Center, CubeParams.Size);
            }
            // Sphere
            else
            if (Shape == ECgGizmoDrawShape.Sphere)
            {
                if (bWire)
                    Gizmos.DrawWireSphere(SphereParams.Center, SphereParams.Radius);
                else
                    Gizmos.DrawSphere(SphereParams.Center, SphereParams.Radius);
            }
            // Frustrum
            else
            if (Shape == ECgGizmoDrawShape.Frustrum)
                Gizmos.DrawFrustum(FrustrumParams.Center, FrustrumParams.Fov, FrustrumParams.MaxRange, FrustrumParams.MinRange, FrustrumParams.Aspect);
        }

        public void UpdateTime(float deltaTime)
        {
            if (bWaitForTime)
                WaitForTimeTimer += deltaTime;
        }

        public void UpdateFrame()
        {
            if (bWaitForFrame)
                ++WaitForFrameCounter;
        }
    }
}
