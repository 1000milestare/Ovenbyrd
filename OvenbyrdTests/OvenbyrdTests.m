//
//  OvenbyrdTests.m
//  OvenbyrdTests
//
//  Created by chirgwin on 6/22/12.
//  Copyright (c) 2012 1000milestare. All rights reserved.
//

#import "OvenbyrdTests.h"

@implementation OvenbyrdTests

- (void)setUp
{
    [super setUp];
    InitTables();
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)testMetricStrength
{
    short expected = -8;
    short result = MetricStrength(10, false, 3, 4, false, 0);
    STAssertEquals(expected, result, @"Expected %d, but got %d",expected,result);
}

@end
