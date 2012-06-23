//
//  SpaceTime.h
//  Nightingale
//
//  Created by chirgwin on 6/23/12.
//  Copyright (c) 2012 AMNS. All rights reserved.
//

#ifndef __Nightingale__SpaceTime__
#define __Nightingale__SpaceTime__

#ifdef __cplusplus
extern "C" {
#endif
    //FIXME
    void InitTables();
    long Code2LDur(char durCode, char nDots);
    long TimeSigDur(short numerator, short denominator);    
#ifdef __cplusplus
}
#endif


#endif /* defined(__Nightingale__SpaceTime__) */
