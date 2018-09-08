namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgManager_Draw
    {
        #region "Constants"

        public static readonly byte REQUEST_SIZE = 255;

        #endregion // Constants

        #region "Data Members"

        private static FCgManager_Draw _Instance;
        public static FCgManager_Draw Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new FCgManager_Draw();
                }
                return _Instance;
            }
        }

        public FCgGizmoDrawRequest[] Requests;

        public byte RequestIndex;

        public List<FCgGizmoDrawRequest> ActiveRequests;

        #endregion // Data Members

        public FCgManager_Draw()
        {
            Requests = new FCgGizmoDrawRequest[REQUEST_SIZE];

            for (int i = 0; i < REQUEST_SIZE; ++i)
            {
                Requests[i] = new FCgGizmoDrawRequest();
            }

            ActiveRequests = new List<FCgGizmoDrawRequest>();
        }

        public static FCgManager_Draw Get()
        {
            return Instance;
        }

        public void Clear()
        {
            foreach (FCgGizmoDrawRequest r in Requests)
            {
                r.Reset();
            }
            ActiveRequests.Clear();
        }

        public void Shutdown()
        {
            Clear();
        }

        public void OnDrawGizmos()
        {
            int count = ActiveRequests.Count;

            for (int i = 0; i < count; ++i)
            {
                FCgGizmoDrawRequest request = ActiveRequests[i];

                if (request.HasCompleted())
                {
                    request.Reset();
                    continue;
                }
                else
                {
                    request.Draw();
                }

                // Frame
                request.UpdateFrame();
                // Time
                request.UpdateTime(Time.deltaTime);
            }
        }

        public FCgGizmoDrawRequest AllocateRequest()
        {
            for (byte i = 0; i < REQUEST_SIZE; ++i)
            {
                byte index                  = (byte)((RequestIndex + i) % REQUEST_SIZE);
                FCgGizmoDrawRequest request = Requests[index];

                if (!request.bAllocated)
                {
                    request.bAllocated = true;
                    return request;
                }
            }
            FCgDebug.LogError("FCsManager_Draw.AllocateRequest: Pool is exhausted");
            return null;
        }
       
        public void DrawLine(Vector3 from, Vector3 to, Color color, float time)
        {
            FCgGizmoDrawRequest request = AllocateRequest();

            request.Shape = ECgGizmoDrawShape.Line;
            request.DrawColor = color;
            request.LineParams.Set(from, to);
            request.bWaitForTime = true;
            request.WaitForTime = time;
        }

        public void DrawRay(Vector3 from, Vector3 direction, Color color, float time)
        {
            FCgGizmoDrawRequest request = AllocateRequest();

            request.Shape = ECgGizmoDrawShape.Ray;
            request.DrawColor = color;
            request.RayParams.Set(from, direction);
            request.bWaitForTime = true;
            request.WaitForTime = time;
        }

        public void DrawSphere(Vector3 center, float radius, Color color, float time)
        {
            FCgGizmoDrawRequest request = AllocateRequest();

            request.Shape = ECgGizmoDrawShape.Sphere;
            request.DrawColor = color;
            request.SphereParams.Set(center, radius);
            request.bWaitForTime = true;
            request.WaitForTime = time;
        }
    }
}