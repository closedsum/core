// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections.Generic;
    using UnityEngine;

    public class CgInput_Axis : CgInput_Base
    {
        public class CgInputAxis_Event : TCgMulticastDelegate_TwoParams<MonoBehaviour, float> { }

        #region "Data Members"

        private Dictionary<ECgInputEvent, CgInputAxis_Event> Events;

        #endregion // Data Members

        public CgInput_Axis()
        {
            Info = new CgInputInfo(ECgInputType.Axis, ECgInputValue.Float);
            Info.Event = ECgInputEvent.Stationary;
            Info.Last_Event = Info.Event;

            Events = new Dictionary<ECgInputEvent, CgInputAxis_Event>(new ECgInputEventEqualityComparer());
            Events.Add(ECgInputEvent.FirstMoved, new CgInputAxis_Event());
            Events.Add(ECgInputEvent.Moved, new CgInputAxis_Event());
            Events.Add(ECgInputEvent.FirstStationary, new CgInputAxis_Event());
            Events.Add(ECgInputEvent.Stationary, new CgInputAxis_Event());
        }

        public void Raw(float val)
        {
            if ((Manager_Input.CurrentInputActionMap & (ActionMap)) == ECgInputActionMap.NONE)
                return;
            if (val != 0.0f && Info.Value == 0.0f)
                FirstMoved(val);
            else
            if (val != 0.0f && Info.Value != 0.0f)
                Moved(val);
            else
            if (val == 0.0f && Info.Value != 0.0f)
                FirstStationary(val);
            else
            if (val == 0.0f && Info.Value == 0.0f)
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

        public void AddEvent(ECgInputEvent e, CgInputAxis_Event.Event del)
        {
            CgInputAxis_Event handler;
            Events.TryGetValue(e, out handler);
            handler.Add(del);
        }

        private void Broadcast(ECgInputEvent e, MonoBehaviour mb, float val)
        {
            CgInputAxis_Event del;
            Events.TryGetValue(e, out del);
            del.Broadcast(mb, val);
        }
    }
}
