// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgInput_Action : FCgInput_Base
    {
        public class CgInputAction_Event : TCgMulticastDelegate_OneParam<MonoBehaviour> { }

        #region "Data Members"

        private Dictionary<ECgInputEvent, CgInputAction_Event> Events;

        #endregion // Data Members

        public FCgInput_Action()
        {
            Info = new FCgInputInfo(ECgInputType.Action, ECgInputValue.Void);
            Info.Event = ECgInputEvent.Released;
            Info.Last_Event = Info.Event;

            Events = new Dictionary<ECgInputEvent, CgInputAction_Event>(new ECgInputEventEqualityComparer());
            Events.Add(ECgInputEvent.FirstPressed, new CgInputAction_Event());
            Events.Add(ECgInputEvent.Pressed, new CgInputAction_Event());
            Events.Add(ECgInputEvent.FirstReleased, new CgInputAction_Event());
        }

        public void FirstPressed()
        {
            if ((Manager_Input.CurrentInputActionMap & ActionMap) == NONE)
                return;
            
            ECgInputEvent e = ECgInputEvent.FirstPressed;
            Info.Event = e;
            Manager_Input.AddInput(Action, e);

            Broadcast(e, Manager_Input.InputOwner);
        }

        public void Pressed()
        {
            ECgInputEvent e = ECgInputEvent.Pressed;

            if (Info.Last_Event == ECgInputEvent.FirstPressed)
                Info.Event = e;
            Manager_Input.AddInput(Action, e);

            Broadcast(e, Manager_Input.InputOwner);
        }

        public void FirstReleased()
        {
            if ((Manager_Input.CurrentInputActionMap & ActionMap) == NONE)
                return;

            ECgInputEvent e = ECgInputEvent.FirstReleased;
            Info.Event = e;
            Manager_Input.AddInput(Action, e);

            Broadcast(e, Manager_Input.InputOwner);
        }

        public void AddEvent(ECgInputEvent e, CgInputAction_Event.Event del)
        {
            CgInputAction_Event handler;
            Events.TryGetValue(e, out handler);
            handler.Add(del);
        }

        private void Broadcast(ECgInputEvent e, MonoBehaviour mb)
        {
            CgInputAction_Event del;
            Events.TryGetValue(e, out del);
            del.Broadcast(mb);
        }
    }
}
