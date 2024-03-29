//
//  OBDocumentView.m
//  Ovenbyrd
//
//  Created by chirgwin on 6/22/12.
//  Copyright (c) 2012 1000milestare. All rights reserved.
//

#import "OBDocumentView.h"

@implementation OBDocumentView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

/* simple custom cursor example:
   this cursor bitmap and it's hotspot point were harvested directly from
   the old Nightingale.rsrc resource file
 */
-(void)mouseDown:(NSEvent *)event
{
    NSCursor *cursor = [[NSCursor alloc] initWithImage: [NSImage imageNamed:@"cursor_treble_clef.png"]
                                         hotSpot: NSMakePoint (7, 12)];
    [cursor set];
    
    /* call a C++ function and log the result */    
    NSLog(@"this is the result of a call to MetricStrength: %hd", MetricStrength(10, false, 3, 4, false, 0));
    
}

/* simple Quartz 2D drawing example:
   draw a staff 
 */
- (void)drawRect:(NSRect)dirtyRect
{
    NSGraphicsContext *nsGraphicsContext = [NSGraphicsContext currentContext];
    CGContextRef c = (CGContextRef) [nsGraphicsContext graphicsPort];
    
    CGContextSetRGBStrokeColor(c, 0.0, 0.0, 0.0, 1.0);

    CGFloat width = [self bounds].size.width;
    CGFloat spacing = 10.0;

    CGContextBeginPath(c);
    CGContextSetLineWidth(c, 1.0);
    NSInteger i, numStaffLines;
    numStaffLines = 5;
    for (i = 1; i <= numStaffLines; i++)
    {
        CGContextMoveToPoint(c, spacing, i * spacing);
        CGContextAddLineToPoint(c, width - spacing, i * spacing);
        CGContextDrawPath(c, kCGPathStroke);
    }
    CGContextStrokePath(c);
}

@end
