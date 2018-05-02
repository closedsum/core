namespace CgCore
{
    using System;
    using System.Diagnostics;
    using System.Collections.Generic;
    using UnityEngine;

    public class CgProcessPayload : CgPooledObjectPayload
    {
        #region "Data Members"

        public bool CreateNoWindow;
        public bool UseShellExecute;
        public string FileName;
        public string Arguments;
        public bool ErrorDialog;
        public bool RedirectStandardInput;
        public bool RedirectStandardOutput;
        public bool RedirectStandardError;
        public bool EnableRaisingEvents;

        public CgProcess.OutputDataRecieved OutputDataRecieved_Event;
        public CgProcess.ErrorDataRecieved ErrorDataRecieved_Event;
        public CgProcess.Exited Exited_Event;

        #endregion // Data Members

        public CgProcessPayload() : base()
        {
            OutputDataRecieved_Event = new CgProcess.OutputDataRecieved();
            ErrorDataRecieved_Event = new CgProcess.ErrorDataRecieved();
            Exited_Event = new CgProcess.Exited();

            Reset();
        }

        public override void Reset()
        {
            base.Reset();

            CreateNoWindow = true;
            UseShellExecute = false;
            FileName = "";
            Arguments = "";
            ErrorDialog = false;
            RedirectStandardInput = false;
            RedirectStandardOutput = false;
            RedirectStandardError = false;
            EnableRaisingEvents = false;
                
            OutputDataRecieved_Event.Clear();
            ErrorDataRecieved_Event.Clear();
            Exited_Event.Clear();
        }
    }

    public class CgManager_Process : TCgManager<ECgProcess, CgProcess>
    {
        private static readonly int PAYLOAD_COUNT = 8;

        public CgManager_Process() : base()
        {
            for (int i = 0; i < PAYLOAD_COUNT; ++i)
            {
                Payloads.Add(new CgProcessPayload());
            }
        }
    }

    public class ICgManager_Process : MonoBehaviour
    {
        private static ICgManager_Process _Instance;

        #region "Data Members"

        protected TCgManager<ECgProcess, CgProcess> Internal;

        protected List<Process> Processes = new List<Process>();

        #endregion // Data Members

        public static ICgManager_Process Get()
        {
            return _Instance;
        }

        public static void Init(Type type)
        {
            if (_Instance != null)
                return;

            if (!type.IsSubclassOf(typeof(TCgManager<ECgProcess, CgProcess>)))
            {
                CgDebug.Log("ICgManager_Process.Init: Passed in Type of " + type.GetType().Name + " is NOT a SubclassOf TCgManager<ECgProcess, CgProcess>");
                return;
            }

            GameObject go = new GameObject("Manager_Process");
            _Instance     = go.AddComponent<ICgManager_Process>();

            _Instance.Internal = (TCgManager<ECgProcess,CgProcess>)type.GetConstructor(Type.EmptyTypes).Invoke(Type.EmptyTypes);
            _Instance.Internal.OnAddToPool_Event.Add(_Instance.OnAddToPool);
        }

        #region "Internal"

        public virtual void Clear()
        {
            Internal.Clear();
        }

        public static void Shutdown()
        {
            if (_Instance != null)
                _Instance.Internal.Shutdown();
        }

        public virtual void CreatePool(ECgProcess e, int size)
        {
            Internal.CreatePool(e, size);
        }

        public virtual void AddToPool(ECgProcess e, CgProcess o)
        {
            Internal.AddToPool(e, o);
        }

        public virtual void AddToActivePool(ECgProcess e, CgProcess o)
        {
            Internal.AddToActivePool(e, o);
        }

        public void OnUpdate(float deltaTime)
        {
            Internal.OnUpdate(deltaTime);
        }

        public int GetActivePoolSize(ECgProcess e)
        {
            return Internal.GetActivePoolSize(e);
        }

        public bool IsExhausted(ECgProcess e)
        {
            return Internal.IsExhausted(e);
        }

            #region "Allocate / DeAllocate"

        public bool DeAllocate(ECgProcess e, int index)
        {
            return Internal.DeAllocate(e, index);
        }

        public void DeAllocateAll()
        {
            Internal.DeAllocateAll();
        }

            #endregion // Allocate / DeAllocate

        public CgProcess Spawn(ECgProcess e, ICgPooledObjectPayload payload)
        {
            return Internal.Spawn(e, payload);
        }

        public CgProcessPayload AllocatePayload()
        {
            return (CgProcessPayload)Internal.AllocatePayload();
        }

        #endregion "Internal"

        public void OnAddToPool(ECgProcess e, CgProcess o)
        {
            Process p = new Process();
            Processes.Add(p);
            o.P = p;
            o.P.OutputDataReceived += o.OnOutputDataRecieved;
            o.P.ErrorDataReceived += o.OnErrorDataRecieved;
            o.P.Exited += o.OnExited;
        }
    }
}