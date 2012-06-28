//
//  SpaceTime.cp
//  Ovenbyrd
//
//  Created by chirgwin on 6/23/12.
//

#include "SpaceTime.h"

// FIXME
short l2p_durs[MAX_L_DUR+1];	/* Logical-to-physical dur. lookup table */
void InitTables()
{
    short i;
    l2p_durs[MAX_L_DUR] = PDURUNIT;						/* Set up lookup table to convert; assign 15 to 128th for tuplets */
	for (i = MAX_L_DUR-1; i>0; i--)						/*   logical to physical durations */
		l2p_durs[i] = 2*l2p_durs[i+1];	
}
/* ------------------------------------------------------------------ TimeSigDur -- */
/* Return the nominal duration of a measure with the given time signature. */

long TimeSigDur(short numerator, short denominator)
{
	return ((long)numerator*l2p_durs[WHOLE_L_DUR]/(long)denominator);
}

/* ------------------------------------------------------------------- Code2LDur -- */
/* Convert note l_dur code and number of augmentation dots to logical duration. */

long Code2LDur(char durCode, char nDots)
{
	register short	j;
	register long	noteDur;
    
	noteDur = (long)l2p_durs[durCode]; 				/* Get basic duration */
	for (j = 1; j<=nDots; j++)
		noteDur += (long)l2p_durs[durCode+j];		/* Add in aug. dots */
	return noteDur;
}
