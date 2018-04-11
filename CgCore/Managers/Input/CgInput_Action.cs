namespace CgCore
{
    using UnityEngine;

    public class CgInput_Action : CgInput_Base
    {
        #region "Constants"

        private static readonly byte ACTION_COUNT = 3;

        #endregion

        #region "Delegates"

        public delegate void Event(MonoBehaviour mb);

        private Event[] Events;

        #endregion

        #region "Data Members"

        public CgInput_Action()
        {
            Events = new Event[ACTION_COUNT];
        }

        #endregion

        public void FirstPressed()
        {
            if ((Manager_Input.CurrentInputActionMap & ActionMap) == 0)
                return;

            ECgInputEvent e = ECgInputEvent.FirstPressed;
            Info.Event = e;
            Manager_Input.AddInput(Action, e);

            if (Events[(byte)e] != null)
                Events[(byte)e](Manager_Input.InputOwner);
        }

        public void Pressed()
        {
            ECgInputEvent e = ECgInputEvent.Pressed;

            if (Info.Last_Event == ECgInputEvent.FirstPressed)
                Info.Event = e;
            Manager_Input.AddInput(Action, e);

            if (Events[(byte)e] != null)
                Events[(byte)e](Manager_Input.InputOwner);
        }

        public void FirstReleased()
        {
            if ((Manager_Input.CurrentInputActionMap & ActionMap) == 0)
                return;

            ECgInputEvent e = ECgInputEvent.FirstReleased;
            Info.Event = e;
            Manager_Input.AddInput(Action, e);

            if (Events[(byte)e] != null)
                Events[(byte)e](Manager_Input.InputOwner);
        }

        public void SetEvent(ECgInputEvent e, Event del)
        {
            if (e == ECgInputEvent.FirstPressed)
                Events[(byte)e] += del;
        }
    }
}
