namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class CgPlayerController : MonoBehaviour
    {
        #region "Data Members"

        public CgManager_Input Manager_Input;

        public List<ECgGameEvent> GameEventPriorityList;

        #endregion // Data Members

        // Use this for initialization
        void Start()
        {
            Init();
        }

        public virtual void Init()
        {
            GameEventPriorityList = new List<ECgGameEvent>();
        }

        protected virtual void PreProcessInput(float deltaTime)
        {
            Manager_Input.PreProcessInput(deltaTime);
        }

        protected virtual void PostProcessInput(float deltaTime)
        {
        }

        public virtual void GatherInput(float deltaTime)
        {
            PreProcessInput(deltaTime);
            PostProcessInput(deltaTime);
        }
    }
}
