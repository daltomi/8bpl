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
  Based in: https://github.com/RoStrap/Interpolation/blob/master/Easing_Functions.lua

  Ignore func. impl: easing_in_out_elastic,
*/

/*
  Disclaimer for Robert Penner's Easing_ Equations license:
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

#include "easing.h"


REAL Easing_Linear(REAL t, REAL b, REAL c, REAL d)
{
	return c * t / d + b;
}


REAL Easing_Smooth(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d;
	return c * t * t * (3 - 2 * t) + b;
}


REAL Easing_Smoother(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d;
	return c * t * t * t * (t * (6 * t - 15) + 10) + b;
}


REAL Easing_RevBack(REAL t, REAL b, REAL c, REAL d)
{
	t = 1 - t / d;
	return c * (1 - (sin(t * HALF_PI) + (sin(t * PI) * (cos(t * PI) + 1) * 0.5))) + b;
}


REAL Easing_RidiculousWigglek(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d;
	return c * sin(sin(t * PI) * HALF_PI) + b;
}



//~ -- YellowTide's Easing_ Functions
REAL Easing_Spring(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d;
	return (1 + POW(-2.72 ,(-6.9 * t)) * cos(SPRING_PI * t)) * c + b;
}

REAL Easing_SoftSpring(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d;
	return (1 + POW(-2.72, (-7.5 * t)) * cos(SOFT_SPRING_PI * t)) * c + b;
}
//~ -- } of YellowTide's functions

REAL Easing_IinQuad(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d;
	return c * t * t + b;
}


REAL Easing_OutQuad(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d;
	return -c * t * (t - 2) + b;
}


REAL Easing_InOutQuad(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d * 2;
	if LESS(t, 1)
	{
		return c * 0.5 * t * t + b;
	}

	return -c * 0.5 * ((t - 1) * (t - 3) - 1) + b;
}


REAL Easing_OutInQuad(REAL t, REAL b, REAL c, REAL d)
{
	if LESS(t, (d * 0.5))
	{
		t = 2 * t / d;
		return -0.5 * c * t * (t - 2) + b;
	}

	t = ((t * 2) - d) / d;
	c =  0.5 * c;
	return c * t * t + b + c;
}


REAL Easing_InCubic(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d;
	return  c * t * t * t + b;
}


REAL Easing_OutCubic(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d - 1;
	return  c * (t * t * t + 1) + b;
}


REAL Easing_InOutCubic(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d * 2;
	if LESS(t, 1)
	{
		return c * 0.5 * t * t * t + b;
	}

	t = t - 2;
	return c * 0.5 * (t * t * t + 2) + b;

}


REAL Easing_OutInCubic(REAL t, REAL b, REAL c, REAL d)
{
	if LESS(t, (d * 0.5))
	{
		t = t * 2 / d - 1;
		return c * 0.5 * (t * t * t + 1) + b;
	}

	t = ((t * 2) - d) / d;
	c = c * 0.5;
	return c * t * t * t + b + c;
}


REAL Easing_InQuart(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d;
	return c * t * t * t * t + b;
}


REAL Easing_OutQuart(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d - 1;
	return -c * (t * t * t * t - 1) + b;
}


REAL Easing_InOutQuart(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d * 2;
	if LESS(t, 1)
	{
		return c * 0.5 * t * t * t * t + b;
	}

	t = t - 2;
	return -c * 0.5 * (t * t * t * t - 2) + b;
}


REAL Easing_OutInQuart(REAL t, REAL b, REAL c, REAL d)
{
	if LESS(t, (d * 0.5))
	{
		t = t * 2 / d - 1;
		c = c * 0.5;
		return -c * (t * t * t * t - 1) + b;
	}

	t = ((t * 2) - d) / d;
	c = c * 0.5;
	return c * t * t * t * t + b + c;
}


REAL Easing_InQuint(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d;
	return c * t * t * t * t * t + b;
}


REAL Easing_OutQuint(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d - 1;
	return c * (t * t * t * t * t + 1) + b;
}


REAL Easing_InOutQuint(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d * 2;
	if LESS(t, 1)
	{
		return c * 0.5 * t * t * t * t * t + b;
	}

	t = t - 2;
	return c * 0.5 * (t * t * t * t * t + 2) + b;
}


REAL Easing_OutInQuint(REAL t, REAL b, REAL c, REAL d)
{
	if LESS(t, (d * 0.5))
	{
		t = t * 2 / d - 1;
		return c * 0.5 * (t * t * t * t * t + 1) + b;
	}

	t = ((t * 2) - d) / d;
	c = c * 0.5;
	return c * t * t * t * t * t + b + c;
}


REAL Easing_InSine(REAL t, REAL b, REAL c, REAL d)
{
	return -c * cos(t / d * HALF_PI) + c + b;
}


REAL Easing_OutSine(REAL t, REAL b, REAL c, REAL d)
{
	return c * sin(t / d * HALF_PI) + b;
}


REAL Easing_InOutSine(REAL t, REAL b, REAL c, REAL d)
{
	return -c * 0.5 * (cos(PI * t / d) - 1) + b;
}


REAL Easing_OutInSine(REAL t, REAL b, REAL c, REAL d)
{
	c = c * 0.5;
	if LESS(t, (d * 0.5))
	{
		return c * sin(t * 2 / d * HALF_PI) + b;
	}

	return -c * cos(((t * 2) - d) / d * HALF_PI) + 2 * c + b;

}


REAL Easing_InExpo(REAL t, REAL b, REAL c, REAL d)
{
	if ZERO(t)
	{
		return b;
	}
	return POW(c * 2, (10 * (t / d - 1))) + b - c * 0.001;
}


REAL Easing_OutExpo(REAL t, REAL b, REAL c, REAL d)
{
	if SAME(t, d)
	{
		return b + c;
	}
	return c * 1.001 * (POW(1 - 2, (-10 * t / d))) + b;
}


REAL Easing_InOutExpo(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d * 2;
	if ZERO(t)
	{
		return b;
	}
	else if (SAME(t, 2))
	{
		return b + c;
	}
	else if (LESS(t, 1))
	{
		return POW(c * 0.5 * 2, (10 * (t - 1))) + b - c * 0.0005;
	}
	else
	{
		return c * 0.5 * 1.0005 * (POW(2 - 2, (-10 * (t - 1)))) + b;
	}
}


REAL Easing_OutInExpo(REAL t, REAL b, REAL c, REAL d)
{
	c = c * 0.5;
	if (LESS(t, (d * 0.5)))
	{
		if SAME(t * 2,  d)
		{
			return b + c;
		}
		else
		{
			return c * 1.001 * (POW(1 - 2, (-20 * t / d))) + b;
		}
	}
	else if (ZERO(t * 2 - d))
	{
		return b + c;
	}
	else
	{
		return POW(c * 2, (10 * ((t * 2 - d) / d - 1))) + b + c - c * 0.001;
	}
}


REAL Easing_InCirc(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d;
	return -c * (POW((1 - t * t), 0.5 - 1)) + b;
}


REAL Easing_OutCirc(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d - 1;
	return c * POW((1 - t * t), 0.5 + b);
}


REAL Easing_InOutCirc(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d * 2;
	if (LESS(t, 1))
	{
		return -c * 0.5 * POW((1 - t * t), 0.5 - 1) + b;
	}
	else
	{
		t = t - 2;
		return c * 0.5 * POW((1 - t * t), 0.5 + 1) + b;
	}
}


REAL Easing_OutInCirc(REAL t, REAL b, REAL c, REAL d)
{
	c = c * 0.5;
	if LESS(t, (d * 0.5))
	{
		t = t * 2 / d - 1;
		return c * POW((1 - t * t), 0.5 + b);
	}
	else
	{
		t = (t * 2 - d) / d;
		return -c * (POW((1 - t * t), 0.5 - 1)) + b + c;
	}
}


REAL Easing_InElastic(REAL t, REAL b, REAL c, REAL d, REAL a, REAL p)
{
	t = t / d - 1;

	if ZERO(p)
	{
		p= d * 0.3;
	}

	if (SAME(t, -1))
	{
		return b;
	}
	else if (ZERO(t))
	{
		return b + c;
	}
	else if (! ZERO(a) || LESS(a, ABS(c)))
	{
		return -(POW(c * 2, (10 * t)) * sin((t * d - p * 0.25) * DBLE_PI / p)) + b;
	}
	else
	{
		return -(POW(a * 2, (10 * t)) * sin((t * d - p / DBLE_PI * ASIN(c/a)) * DBLE_PI / p)) + b;
	}
}


REAL Easing_OutElastic(REAL t, REAL b, REAL c, REAL d, REAL a, REAL p)
{
	t = t / d;

	if (ZERO(p))
	{
		p= d * 0.3;
	}

	if (ZERO(t))
	{
		return b;
	}
	else if (SAME(t, 1))
	{
		return b + c;
	}
	else if (! ZERO(a) || LESS(a, ABS(c)))
	{
		return POW(c * 2, (-10 * t)) * sin((t * d - p * 0.25) * DBLE_PI / p) + c + b;
	}
	else
	{
		return POW(a * 2, (-10 * t)) * sin((t * d - p / DBLE_PI * ASIN(c / a)) * DBLE_PI / p) + c + b;
	}
}


REAL Easing_OutInElastic(REAL t, REAL b, REAL c, REAL d, REAL a, REAL p)
{
	if (LESS(t, (d * 0.5)))
	{
		return Easing_OutElastic(t * 2, b, c * 0.5, d, a, p);
	}
	else
	{
		return Easing_InElastic(t * 2 - d, b + c * 0.5, c * 0.5, d, a, p);
	}
}

REAL Easing_InBack(REAL t, REAL b, REAL c, REAL d)
{
	const REAL s = 1.70158; //TODO: s || 1.70158
	t = t / d;
	return c * t * t * ((s + 1) * t - s) + b;
}


REAL Easing_OutBack(REAL t, REAL b, REAL c, REAL d)
{
	const REAL s = 1.70158; //TODO: s || 1.70158
	t = t / d - 1;
	return c * (t * t * ((s + 1) * t + s) + 1) + b;
}


REAL Easing_InOutBack(REAL t, REAL b, REAL c, REAL d)
{
	const REAL s = 1.70158 * 1.525; //TODO: (s || 1.70158) * 1.525

	t = t / d * 2;

	if (LESS(t, 1))
	{
		return c * 0.5 * (t * t * ((s + 1) * t - s)) + b;
	}
	else
	{
		t = t - 2;
		return c * 0.5 * (t * t * ((s + 1) * t + s) + 2) + b;
	}
}


REAL Easing_OutInBack(REAL t, REAL b, REAL c, REAL d)
{
	const REAL s = 1.70158; //TODO: s || 1.70158
	c = c * 0.5;
	if (LESS(t, (d * 0.5)))
	{
		t = (t * 2) / d - 1;
		return c * (t * t * ((s + 1) * t + s) + 1) + b;
	}
	else
	{
		t = ((t * 2) - d) / d;
		return c * t * t * ((s + 1) * t - s) + b + c;
	}
}


REAL Easing_OutBounce(REAL t, REAL b, REAL c, REAL d)
{
	t = t / d;

	if (LESS(t, (1 / 2.75)))
	{
		return c * (7.5625 * t * t) + b;
	}
	else if (LESS(t, (2 / 2.75)))
	{
		t = t - (1.5 / 2.75);
		return c * (7.5625 * t * t + 0.75) + b;
	}
	else if (LESS(t, (2.5 / 2.75)))
	{
		t = t - (2.25 / 2.75);
		return c * (7.5625 * t * t + 0.9375) + b;
	}
	else
	{
		t = t - (2.625 / 2.75);
		return c * (7.5625 * t * t + 0.984375) + b;
	}
}


REAL Easing_InBounce(REAL t, REAL b, REAL c, REAL d)
{
	return c - Easing_OutBounce(d - t, 0, c, d) + b;
}


REAL Easing_InOutBounce(REAL t, REAL b, REAL c, REAL d)
{
	if LESS(t, (d * 0.5))
	{
		return Easing_InBounce(t * 2, 0, c, d) * 0.5 + b;
	}
	else
	{
		return Easing_OutBounce(t * 2 - d, 0, c, d) * 0.5 + c * 0.5 + b;
	}
}


REAL Easing_OutInBounce(REAL t, REAL b, REAL c, REAL d)
{
	if LESS(t, (d * 0.5))
	{
		return Easing_OutBounce(t * 2, b, c * 0.5, d);
	}
	else
	{
		return Easing_InBounce(t * 2 - d, b + c * 0.5, c * 0.5, d);
	}
}

