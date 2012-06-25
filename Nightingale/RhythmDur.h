//
//  RhythmDur.h
//  Nightingale
//
//  Created by chirgwin on 6/23/12.
//  Copyright (c) 2012 AMNS. All rights reserved.
//

#ifndef __Nightingale__RhythmDur__
#define __Nightingale__RhythmDur__
#include "SpaceTime.h"
#define TRUNC(value, mod)	(((value)/(mod))*(mod))

static short BeatStrength(short beatNum, short nBeats);
long CalcBeatDur(long timeSigDenom, bool compound);
long FindStrongPoint(
                     long startTime, long endTime,		/* PDUR times relative to beginning of measure */
                     short timeSigNum, short timeSigDenom,
                     bool compound,						/* TRUE=compound meter (6/8, 9/8, etc.) */
                     short minStrength,
                     short *pStrength
                     );

short MetricStrength(
                     short		time,							/* Elapsed time in playDur units */
                     bool	tuplet,						/* Is it within a tuplet? */
                     short		timeSigNum,
                     short		timeSigDenom,
                     bool	compound,					/* TRUE=compound meter ==> 3 denom.units/beat, etc. */
                     short		errMax 						/* Must be >0 */
                     );

#endif /* defined(__Nightingale__RhythmDur__) */
