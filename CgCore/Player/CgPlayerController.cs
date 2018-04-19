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

        public CgPlayerState PlayerState;

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

        public virtual void OnUpdate(float deltaTime)
        {
            PlayerState.OnUpdate(deltaTime);
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

        public virtual void ProcessGameEvents()
        {
            PlayerState.ProcessGameEvents(GameEventPriorityList);
        }
    }
}
