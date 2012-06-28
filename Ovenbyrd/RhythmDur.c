//
//  RhythmDur.cpp
//  Ovenbyrd
//
//  Created by chirgwin on 6/23/12.
//

#include "RhythmDur.h"

    /* ---------------------------------------------------------------- BeatStrength -- */
    
#define SUPERBEAT 9				/* Greatest possible metric strength */
#define WIMP -9					/* Least possible metric strength */
    
#define MAXBEATS 11
    
unsigned char beats[MAXBEATS-1][MAXBEATS-1] = {
    {0,0,0, 0,0,0,0, 0,0,0},	/* 2 beats per measure */
    {0,0,0, 0,0,0,0, 0,0,0},	/* 3 beats */
    {0,1,0, 0,0,0,0, 0,0,0},	/* 4 beats */
    {0,1,0, 0,0,0,0, 0,0,0},	/* 5 beats */
    {0,0,1, 0,0,0,0, 0,0,0},	/* 6 beats */
    {0,1,0, 1,0,0,0, 0,0,0},	/* 7 beats */
    {0,1,0, 2,0,1,0, 0,0,0},	/* 8 beats */
    {0,0,1, 0,0,1,0, 0,0,0},	/* 9 beats */
    {0,1,0, 0,2,0,1, 0,0,0},	/* 10 beats */
    {0,1,0, 0,2,0,0, 1,0,0},	/* 11 beats */
};

/* Deliver the metric strength (in the system of Byrd's dissertation, Sec. 4.4.1)
 of beat <beatNum> in a meter with <nBeats> beats. <beatNum>=0 is the downbeat.
 Consider <beatNum> modulo <nBeats>, i.e., in case the beat is past where the measure
 should end, act as if there are barlines at the intervals the meter indicates. */

static short BeatStrength(short beatNum, short nBeats)
{
    beatNum = beatNum % nBeats;
    if (beatNum==0) return SUPERBEAT;
    
    if (nBeats<=1 || nBeats>MAXBEATS) return 0;
    
    return beats[nBeats-2][beatNum-1];
}
/* ------------------------------------------------------------- MetricStrength -- */
/* Given an elapsed time within the measure and a description of the current time
 signature, deliver the metric strength of that elapsed time in the system described
 in Byrd's dissertation, Sec. 4.4.1. Essentially, the higher the value the stronger,
 and the weakest beat has a strength of 0. So positive values represent strong beats
 and negative values represent levels below the beat. */
short MetricStrength(
                     short		time,							/* Elapsed time in playDur units */
                     bool	tuplet,						/* Is it within a tuplet? */
                     short		timeSigNum,
                     short		timeSigDenom,
                     bool	compound,					/* TRUE=compound meter ==> 3 denom.units/beat, etc. */
                     short		errMax 						/* Must be >0 */
                     )
{
    short beatDur, remainder, fracBeatDur;
    short beatNum, level;
    
    if (tuplet) return WIMP;
    
    beatDur = CalcBeatDur(timeSigDenom, compound);
    
    beatNum = time/beatDur;
    remainder = time-beatNum*beatDur;
    if (remainder<errMax) 
        return BeatStrength(beatNum, (compound? timeSigNum/3 : timeSigNum));
    
    fracBeatDur = (compound? beatDur/3 : beatDur/2);
    for (level=-1; fracBeatDur>1; level--,fracBeatDur/=2) {
        if (remainder>=fracBeatDur) remainder -=fracBeatDur;
        if (compound && remainder>=fracBeatDur) remainder -=fracBeatDur;
        if (remainder<errMax) break;
    }
    
    return (compound? level-1 : level);				/* In compound meter, skip level -1 */
}

/* -------------------------------------------------------------- FindStrongPoint -- */
/* Try to find a point within the given range of times whose metric strength is at
 least <minStrength>; if there isn't any, look for a point whose metric strength is
 SUPERBEAT (this is the downbeat of the next measure), regardless of <minStrength>.
 If either type of point is found, set *pStrength to its actual strength and return
 its playDur elapsed time; if there is no point of either type, return -1. */


/* ----------------------------------------------------------------- CalcBeatDur -- */

long CalcBeatDur(long timeSigDenom, bool compound)
{
    long wholeDur, beatDur;
    
    wholeDur = Code2LDur(WHOLE_L_DUR, 0);
    beatDur = wholeDur/timeSigDenom;
    if (compound) beatDur *= 3;
    return beatDur;
}

long FindStrongPoint(
                     long startTime, long endTime,		/* PDUR times relative to beginning of measure */
                     short timeSigNum, short timeSigDenom,
                     bool compound,						/* TRUE=compound meter (6/8, 9/8, etc.) */
                     short minStrength,
                     short *pStrength
                     )
{
    short durIncr, beatDur, strength, s;
    long time, timeSigDur, startMeasTime;
    
    /* Look for a strong enough point within the measure */
    
    beatDur = CalcBeatDur(timeSigDenom, compound);
    durIncr = beatDur;
    if (minStrength<0) {
        s = minStrength;
        while (s++<0)
            durIncr /= 2;
    }
    
    time = TRUNC(startTime, durIncr);
    if (time<startTime) time += durIncr;
    for ( ; time<endTime; time += durIncr) {
        strength = MetricStrength(time, false, timeSigNum, timeSigDenom, compound,
                                  PDURUNIT-1);
        if (strength>=minStrength) {
            *pStrength = strength;
            return time;
        }
    }
    
    /* Nothing within the measure. See if the range extends into the next measure */
    
    timeSigDur = TimeSigDur(timeSigNum, timeSigDenom);
    startMeasTime = (startTime/timeSigDur)*timeSigDur;
    if (endTime>startMeasTime+timeSigDur) {
        *pStrength = SUPERBEAT;
        return startMeasTime+timeSigDur;
    }
    
    return -1L;
}


