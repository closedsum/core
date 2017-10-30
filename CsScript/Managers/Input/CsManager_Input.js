/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var JsCsManager = require('CsScript/Managers/CsManager.js');

var me;

module.exports = class JsCsManager_Input extends JsCsManager
{
    constructor()
    {
        super();

        me = this;
    }

    Init(inPtr, inRoot)
    {
        super.Init(inPtr, inRoot);

        this.ptr = CsManager_Input.C(inPtr);

        /*
        // Pressed
        this.Manager.Default_Event.Add(this.Default_Event);
        this.Manager.Default_ScriptEvent.Add(this.Default_ScriptEvent);

        this.Manager.FirstPressed_Event.Add(this.FirstPressed_Event);
        this.Manager.FirstPressed_ScriptEvent.Add(this.FirstPressed_ScriptEvent);
        this.Manager.Pressed_Event.Add(this.Pressed_Event);
        this.Manager.Pressed_ScriptEvent.Add(this.Pressed_ScriptEvent);
        this.Manager.FirstReleased_Event.Add(this.FirstReleased_Event);
        this.Manager.FirstReleased_ScriptEvent.Add(this.FirstReleased_ScriptEvent);
        // Axis
        this.Manager.Axis_Event.Add(this.Axis_Event);
        this.Manager.Axis_ScriptEvent.Add(this.Axis_ScriptEvent);

        this.Manager.Axis_FirstMoved_Event.Add(this.Axis_FirstMoved_Event);
        this.Manager.Axis_FirstMoved_ScriptEvent.Add(this.Axis_FirstMoved_ScriptEvent);
        this.Manager.Axis_Moved_Event.Add(this.Axis_Moved_Event);
        this.Manager.Axis_Moved_ScriptEvent.Add(this.Axis_Moved_ScriptEvent);
        this.Manager.Axis_FirstStationary_Event.Add(this.Axis_FirstStationary_Event);
        this.Manager.Axis_FirstStationary_ScriptEvent.Add(this.Axis_FirstStationary_ScriptEvent);
        this.Manager.Axis_Stationary_Event.Add(this.Axis_Stationary_Event);
        this.Manager.Axis_Stationary_ScriptEvent.Add(this.Axis_Stationary_ScriptEvent);
        // Location
        this.Manager.Location_Event.Add(this.Location_Event);
        this.Manager.Location_ScriptEvent.Add(this.Location_ScriptEvent);

        this.Manager.Location_FirstMoved_Event.Add(this.Location_FirstMoved_Event);
        this.Manager.Location_FirstMoved_ScriptEvent.Add(this.Location_FirstMoved_ScriptEvent);
        this.Manager.Location_Moved_Event.Add(this.Location_Moved_Event);
        this.Manager.Location_Moved_ScriptEvent.Add(this.Location_Moved_ScriptEvent);
        this.Manager.Location_FirstStationary_Event.Add(this.Location_FirstStationary_Event);
        this.Manager.Location_FirstStationary_ScriptEvent.Add(this.Location_FirstStationary_ScriptEvent);
        this.Manager.Location_Stationary_Event.Add(this.Location_Stationary_Event);
        this.Manager.Location_Stationary_ScriptEvent.Add(this.Location_Stationary_ScriptEvent);
        // Rotation
        this.Manager.Rotation_Event.Add(this.Rotation_Event);
        this.Manager.Rotation_ScriptEvent.Add(this.Rotation_ScriptEvent);

        this.Manager.Rotation_FirstMoved_Event.Add(this.Rotation_FirstMoved_Event);
        this.Manager.Rotation_FirstMoved_ScriptEvent.Add(this.Rotation_FirstMoved_ScriptEvent);
        this.Manager.Rotation_Moved_Event.Add(this.Rotation_Moved_Event);
        this.Manager.Rotation_Moved_ScriptEvent.Add(this.Rotation_Moved_ScriptEvent);
        this.Manager.Rotation_FirstStationary_Event.Add(this.Rotation_FirstStationary_Event);
        this.Manager.Rotation_FirstStationary_ScriptEvent.Add(this.Rotation_FirstStationary_ScriptEvent);
        this.Manager.Rotation_Stationary_Event.Add(this.Rotation_Stationary_Event);
        this.Manager.Rotation_Stationary_ScriptEvent.Add(this.Rotation_Stationary_ScriptEvent);
        */
    }

    CleanUp(){}

    // Pressed
    Default_Event(actor, action, event){}
    Default_ScriptEvent(action, event){}

    FirstPressed_Event(actor, action){}
    FirstPressed_ScriptEvent(action){}
    Pressed_Event(actor, action){}
    Pressed_ScriptEvent(action){}
    FirstReleased_Event(actor, action){}
    FirstReleased_ScriptEvent(action){}
    // Axis
    Axis_Event(actor, action, event, val){}
    Axis_ScriptEvent(action, event, val){}

    Axis_FirstMoved_Event(actor, action, val){}
    Axis_FirstMoved_ScriptEvent(action, val){}
    Axis_Moved_Event(actor, action, val){}
    Axis_Moved_ScriptEvent(action, val){}
    Axis_FirstStationary_Event(actor, action, val){}
    Axis_FirstStationary_ScriptEvent(action, val){}
    Axis_Stationary_Event(actor, action, val){}
    Axis_Stationary_ScriptEvent(action, val){}
    // Location
    Location_Event(actor, action, event, location){}
    Location_ScriptEvent(action, event, location){}

    Location_FirstMoved_Event(actor, action, location){}
    Location_FirstMoved_ScriptEvent(action, location){}
    Location_Moved_Event(actor, action, location){}
    Location_Moved_ScriptEvent(action, location){}
    Location_FirstStationary_Event(actor, action, location){}
    Location_FirstStationary_ScriptEvent(action, location){}
    Location_Stationary_Event(actor, action, location){}
    Location_Stationary_ScriptEvent(action, location){}
     // Rotation
    Rotation_Event(actor, action, event, Rotation){}
    Rotation_ScriptEvent(action, event, Rotation){}

    Rotation_FirstMoved_Event(actor, action, rotation){}
    Rotation_FirstMoved_ScriptEvent(action, rotation){}
    Rotation_Moved_Event(actor, action, rotation){}
    Rotation_Moved_ScriptEvent(action, rotation){}
    Rotation_FirstStationary_Event(actor, action, rotation){}
    Rotation_FirstStationary_ScriptEvent(action, rotation){}
    Rotation_Stationary_Event(actor, action, rotation){}
    Rotation_Stationary_ScriptEvent(action, rotation){}
};