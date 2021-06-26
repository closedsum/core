/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsFunction = require('Cs/Library/Library_Function.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var FunctionLibrary = NJsFunction.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;
var checkf = CommonLibrary.checkf;
var IsValidObjectChecked = CommonLibrary.IsValidObjectChecked;

module.exports = class NJsDelegate
{
    static FDelegateBase = class DelegateBase
    {
        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, TerminationCount: int} 
         */
        constructor(params /*object*/)
        {
            this.Fn = params.Fn;
            this.Caller = params.Caller;
            this.bStatic = params.bStatic;
            this.TerminationCount = params.TerminationCount;
            this.ExecutionCount = 0;
        }

        /**
         * @returns {boolean}
         */
        /*bool*/ ShouldRemove(){ return this.TerminationCount > 0 && this.ExecutionCount >= this.TerminationCount; }
    }
    
    static FDelegate = class Delegate extends NJsDelegate.FDelegateBase
    {
        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, TerminationCount: int} 
         */
        constructor(params /*object*/)
        {
            super(params);
        }

        Execute()
        {
            ++this.ExecutionCount;

            if (this.bStatic)
                return this.Fn();
            return this.Fn.call(this.Caller);
        }
    }

    static FDelegate_OneParam = class Delegate_OnParams extends NJsDelegate.FDelegateBase
    {
        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, TerminationCount: int} 
         */
        constructor(params /*object*/)
        {
            super(params);
        }

        /**
         * @param {any} param1
         * @returns {any}
         */
        /*any*/ Execute(param1 /*any*/)
        {
            ++this.ExecutionCount;

            if (this.bStatics)
                return this.Fn(param1);
            return this.Fn.call(this.Caller, param1);
        }
    }

    static FMulticastBase = class MulticastBase
    {
        constructor(argCount /*int*/)
        {
            this.InvocationMap = new Map(); // [Guid as string][Delegate]

            checkf(CommonLibrary.IsIntChecked("NJsDelegate.FMulticastBase.ctor:", argCount));
            checkf(argCount >= 0, "NJsDelegate.FMulticastBase.ctor: argCount: " + argCount + " is NOT >= 0.");

            this.ArgCount = argCount;
        }

        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, TerminationCount: int} 
         * @returns {NJsDelegate.FDelegate}
         */
        // NJsDelegate.FDelegate CreateDelegate(object: params)

        /**
         * @param {function}    fn 
         * @param {object}      caller
         * @returns {string}    Guid as string 
         */
        /*string*/ Add(fn /*function*/, caller /*object*/)
        {
            let context = this.Add.name;

            check(FunctionLibrary.IsArgCountChecked(context, fn, this.ArgCount));
            check(IsValidObjectChecked(context, caller));

            for (const [key, value] of this.InvocationMap.entries())
            {
                checkf(value.Fn !== fn && value.Caller !== caller, context + ": fn and caller have ALREADY been added.");
            }

            let id = Guid.NewGuid().Conv_GuidToString();
            let params = {Fn: fn, Caller: caller, bStatic: false, TerminationCount: -1}
            let d = this.CreateDelegate(params);

            this.InvocationMap.set(id, d);

            return id;
        }

        /**
         * @param {function} fn
         * @returns {string} Guid as string
         */
        /*string*/ AddStatic(fn /*function*/)
        {
            let context = this.AddStatic.name;

            check(FunctionLibrary.IsArgCountChecked(context, fn, this.ArgCount));

            for (const [key, value] of this.InvocationMap.entries())
            {
                checkf(value.Fn !== fn, context + ": fn and caller have ALREADY been added.");
            }

            let id = Guid.NewGuid().Conv_GuidToString();
            let params = {Fn: fn, Caller: null, bStatic: false, TerminationCount: -1}
            let d = this.CreateDelegate(params);

            this.InvocationMap.set(id, d);

            return id;
        }
  
        /*string*/ AddOneShot(fn /*function*/, caller /*object*/)
        {
            let context = this.AddOneShot.name;

            check(FunctionLibrary.IsArgCountChecked(context, fn, this.ArgCount));

            for (const [key, value] of this.InvocationMap.entries())
            {
                checkf(value.Fn !== fn && value.Caller !== caller, context + ": fn and caller have ALREADY been added.");
            }

            let id = Guid.NewGuid().Conv_GuidToString();
            let params = {Fn: fn, Caller: caller, bStatic: false, TerminationCount: 1}
            let d = this.CreateDelegate(params);

            this.InvocationMap.set(id, d);

            return id;
        }

        /*bool*/ Remove(id /*string*/)
        {
            if (this.InvocationMap.has(id))
            {
                this.InvocationMap.delete(id);
                return true;
            }
            return false;
        }

        /*bool*/ RemoveByCaller(caller /*object*/)
        {
            let ids = [];

            for (const [key, value] of this.InvocationMap.entries())
            {
                if (value.caller === caller)
                    ids.push(key);
            }

            for (const id of ids)
            {
                this.InvocationMap.delete(id);
            }
            return ids.length > 0;
        }
    }

    static FMulticast = class Multicast extends NJsDelegate.FMulticastBase
    {
        constructor()
        {
            super(0);
        }

        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, TerminationCount: int} 
         */
        /*NJsDelegate.FDelegate*/ CreateDelegate(params /*object*/)
        {
            return new NJsDelegate.FDelegate(params);
        }

        Broadcast()
        {
            let ids = [];

            for (let [key, value] of this.InvocationMap.entries())
            {
                value.Execute();

                // Check if the delegate should be removed after execution.
                if (value.ShouldRemove())
                    ids.push(key);
            }

            // Remove any delegates that have "expired"
            for (const id of ids)
            {
                this.InvocationMap.delete(id);
            }
        }
    }
};