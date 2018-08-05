// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgInput_Trigger : FCgInput_Base
    {
        public class FCgInputTrigger_Event : TCgMulticastDelegate_TwoParams<MonoBehaviour, float> { }

        #region "Data Members"

        private Dictionary<ECgInputEvent, FCgInputTrigger_Event> Events;

        #endregion // Data Members

        public FCgInput_Trigger()
        {
            Info = new FCgInputInfo(ECgInputType.Trigger, ECgInputValue.Float);
            Info.Event = ECgInputEvent.Stationary;
            Info.Last_Event = Info.Event;

            Events = new Dictionary<ECgInputEvent, FCgInputTrigger_Event>(new ECgInputEventEqualityComparer());
            Events.Add(ECgInputEvent.FirstMoved, new FCgInputTrigger_Event());
            Events.Add(ECgInputEvent.Moved, new FCgInputTrigger_Event());
            Events.Add(ECgInputEvent.FirstStationary, new FCgInputTrigger_Event());
            Events.Add(ECgInputEvent.Stationary, new FCgInputTrigger_Event());
        }

        public void Raw(float val)
        {
            if ((Manager_Input.CurrentInputActionMap & (ActionMap)) == NONE)
                return;

            FCgInput input = Manager_Input.GetPreviousPreviousInputAction(Action);

            if (input == null && Info.Value != val)
                FirstMoved(val);
            else
            if (Info.Value != val)
                Moved(val);
            else
            if ((input == null && Info.Value == val) || (input != null && input.Value != Info.Value && Info.Value == val))
                FirstStationary(val);
            else
            if (Info.Value == val)
                Stationary(val);
        }

        public void FirstMoved(float val)
        {
            ECgInputEvent e = ECgInputEvent.FirstMoved;
            Info.Set(e, val);
            Manager_Input.AddInput(Action, e, val);

            Broadcast(e, Manager_Input.InputOwner, val);
        }

        public void Moved(float val)
        {
            ECgInputEvent e = ECgInputEvent.Moved;
            Info.Set(e, val);
            Manager_Input.AddInput(Action, e, val);

            Broadcast(e, Manager_Input.InputOwner, val);
        }

        public void FirstStationary(float val)
        {
            ECgInputEvent e = ECgInputEvent.FirstStationary;
            Info.Set(e, val);
            Manager_Input.AddInput(Action, e, val);

            Broadcast(e, Manager_Input.InputOwner, val);
        }

        public void Stationary(float val)
        {
            ECgInputEvent e = ECgInputEvent.Stationary;
            Info.Set(e, val);
            Manager_Input.AddInput(Action, e, val);

            Broadcast(e, Manager_Input.InputOwner, val);
        }

        public void AddEvent(ECgInputEvent e, FCgInputTrigger_Event.Event del)
        {
            FCgInputTrigger_Event handler;
            Events.TryGetValue(e, out handler);
            handler.Add(del);
        }

        private void Broadcast(ECgInputEvent e, MonoBehaviour mb, float val)
        {
            FCgInputTrigger_Event del;
            Events.TryGetValue(e, out del);
            del.Broadcast(mb, val);
        }
    }
}
