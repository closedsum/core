namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class MCgPlayerController : MonoBehaviour
    {
        #region "Data Members"

        public FCgManager_Input Manager_Input;

        public List<FECgGameEvent> GameEventPriorityList;

        public MCgPlayerState PlayerState;

        #endregion // Data Members

        // Use this for initialization
        void Start()
        {
        }

        public virtual void Init()
        {
            GameEventPriorityList = new List<FECgGameEvent>();
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
