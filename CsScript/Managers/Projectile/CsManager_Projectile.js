/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var JsCsManager = require('CsScript/Managers/CsManager.js');
var JsCsProjectile = require('CsScript/Managers/Projectile/CsProjectile.js');

var me;

module.exports = class JsCsManager_Projectile extends JsCsManager
{
    constructor()
    {
        super();

        me = this;
    }

    Init(inPtr, inRoot)
    {
        super.Init(inPtr, inRoot);

        this.ptr = CsManager_Projectile.C(inPtr);

        const len = this.ptr.Pool.length;
        
        for (let i = 0; i < len; i++)
        {
            let projectile = new JsCsProjectile();
            projectile.Init(this.ptr.Pool[i], inRoot);

            this.Pool.push(projectile);
        }
    }

    CleanUp()
    {
        super.CleanUp();

        const len = this.Pool.length;

        for (let i = 0; i < len; i++)
        {
            this.Pool[i].CleanUp();
        }
    }
};