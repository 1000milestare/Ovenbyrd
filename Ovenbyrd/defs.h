//
//  defs.h
//  Ovenbyrd
//
//  Created by chirgwin on 6/23/12.
//

#ifndef Ovenbyrd_defs_h
#define Ovenbyrd_defs_h

#define PDURUNIT 15						/* p_dur code for shortest note,i.e., w/dur.code=MAX_L_DUR */

enum {
    WHOLEMR_L_DUR=-1,						/* l_dur code (subType) for whole measure rest */
    UNKNOWN_L_DUR=0,						/*								unknown CMN value */
    BREVE_L_DUR=1,							/*								breve */
    WHOLE_L_DUR,							/* 							whole note/rest */
    HALF_L_DUR,								/* 							half note/rest */
    QTR_L_DUR,								/* 							quarter note/rest */
    EIGHTH_L_DUR,							/*								eighth note/rest */
    SIXTEENTH_L_DUR,						/*								16th note/rest */
    THIRTY2ND_L_DUR,						/*								32nd note/rest */
    SIXTY4TH_L_DUR,						/*								64th note/rest */
    ONE28TH_L_DUR,							/*								128th note/rest */
    NO_L_DUR	
};

#endif
