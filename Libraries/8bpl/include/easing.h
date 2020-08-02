/*
    8bpl - Copyright (c) daltomi <daltomi@disroot.org>
    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from
    the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not claim
      that you wrote the original software. If you use this software in a product,
      an acknowledgment in the product documentation would be appreciated but is
      not required.

    2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original software.

    3. This notice may not be removed or altered from any source distribution.
*/

/*
  Based in: https://github.com/RoStrap/Interpolation/blob/master/EasingFunctions.lua

  Ignore func. impl: easing_in_out_elastic,
*/

/*
  Disclaimer for Robert Penner's Easing Equations license:
  TERMS OF USE - EASING EQUATIONS
  Open source under the BSD License.
  Copyright © 2001 Robert Penner
  All rights reserved.
  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
  * Neither the name of the author nor the names of contributors may be used to }orse or promote products derived from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

//~ -- For all easing functions:
//~ -- t = elapsed time
//~ -- b = { value
//~ -- c = change in value same as: }ing - {
//~ -- d = duration (total time)

//~ -- Where applicable
//~ -- a = amplitude
//~ -- p = period

#ifndef LIB_8BPL_EASING_H_INCLUDED
#define LIB_8BPL_EASING_H_INCLUDED

#include "8bpl.h"

REAL Easing__Linear(REAL t, REAL b, REAL c, REAL d);

REAL Easing__Smooth(REAL t, REAL b, REAL c, REAL d);

REAL Easing__Smoother(REAL t, REAL b, REAL c, REAL d);

REAL Easing_IinQuad(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutQuad(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InOutQuad(REAL t, REAL b, REAL c, REAL d);

REAL Easing_RevBack(REAL t, REAL b, REAL c, REAL d);

REAL Easing_RidiculousWigglek(REAL t, REAL b, REAL c, REAL d);

REAL Easing_Spring(REAL t, REAL b, REAL c, REAL d);

REAL Easing_SoftSpring(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutInQuad(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InCubic(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutCubic(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InOutCubic(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutInCubic(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InQuart(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutQuart(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InOutQuart(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutInQuart(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InQuint(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutQuint(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InOutQuint(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InSine(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutSine(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InOutSine(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutInSine(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InExpo(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutExpo(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InOutExpo(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutInExpo(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InCirc(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutCirc(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InOutCirc(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutInCirc(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InElastic(REAL t, REAL b, REAL c, REAL d, REAL a, REAL p);

REAL Easing_OutElastic(REAL t, REAL b, REAL c, REAL d, REAL a, REAL p);

REAL Easing_OutInElastic(REAL t, REAL b, REAL c, REAL d, REAL a, REAL p);

REAL Easing_InBack(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutBack(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InOutBack(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutInBack(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutBounce(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InBounce(REAL t, REAL b, REAL c, REAL d);

REAL Easing_InOutBounce(REAL t, REAL b, REAL c, REAL d);

REAL Easing_OutInBounce(REAL t, REAL b, REAL c, REAL d);

#endif


