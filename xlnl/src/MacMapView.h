//
//  MacMapView.h
//
//  Created by 吉村 智彦 on 11/05/07.
//  Copyright 2014 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface MacMapView : NSImageView {
	NSTrackingRectTag tag;
}

- (IBAction)performClick:(id)sender;
- (void)drawRect:(NSRect)dirtyRect;

@end
