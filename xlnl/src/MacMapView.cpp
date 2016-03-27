//
//  MacMapView.m
//
//  Created by 吉村 智彦 on 11/05/07.
//  Copyright (c) 1993-2014 __MyCompanyName__. All rights reserved.
//

#import "MacMapView.h"

#include	"GlobalVar.h"
#include	"call-prot.h"

@implementation MacMapView

- (BOOL)isFlipped
{
	return YES;
}

- (BOOL)acceptsFirstResponder
{
	return YES;
}

-(void)viewDidMoveToWindow
{
	tag = [self addTrackingRect:[self bounds] owner:self userData:NULL assumeInside:NO];
}

- (void)setFrame:(NSRect)frameRect
{
	[super setFrame:frameRect];
	[self removeTrackingRect:tag];
	tag = [self addTrackingRect:[self bounds] owner:self userData:NULL assumeInside:NO];
}

- (void)setBounds:(NSRect)aRect
{
	[super setBounds:aRect];
	[self removeTrackingRect:tag];
	tag = [self addTrackingRect:[self bounds] owner:self userData:NULL assumeInside:NO];
}

- (void)mouseEntered:(NSEvent *)theEvent
{
	[[self window] setAcceptsMouseMovedEvents:YES];
	[[self window] makeFirstResponder:self];
}

- (void)mouseExited:(NSEvent *)theEvent
{
	[[self window] setAcceptsMouseMovedEvents:NO];
}

- (void)mouseMoved:(NSEvent *)theEvent
{
	NSPoint location = [theEvent locationInWindow];
	NSPoint localPoint = [self convertPoint:location fromView:nil];
	gMouseMotion.move(localPoint.x, localPoint.y);
}

- (void)mouseDown:(NSEvent *)theEvent
{
	NSPoint location = [theEvent locationInWindow];
	NSPoint localPoint = [self convertPoint:location fromView:nil];
	gMouseMotion.begin(::MouseMotion::nMouseButton0, localPoint.x, localPoint.y);
}

- (void)mouseUp:(NSEvent *)theEvent
{
	NSPoint location = [theEvent locationInWindow];
	NSPoint localPoint = [self convertPoint:location fromView:nil];
	gMouseMotion.end(::MouseMotion::nMouseButton0, localPoint.x, localPoint.y);
}

- (BOOL)performKeyEquivalent:(NSEvent *)theEvent
{
	if ([theEvent type] == NSKeyDown){
		gKey.setString((const char *)[[theEvent characters] UTF8String]);
		return YES;
	}

	return NO;
}

- (void)keyDown:(NSEvent *)theEvent
{
	gKey.setString((const char *)[[theEvent characters] UTF8String]);
}

- (void)drawRect:(NSRect)dirtyRect
{
	if (gPcgDun.getWBuf() == NULL)
		return;
	CGContext *context = gPcgDun.getWBuf()->getPixMap();
	if (context == NULL)
		return;

#if 0
//@@@
	if (self.frame.size.width != [context size].width)
		if (self.frame.size.height != context.size.height)
			[self setFrameSize:context.size];
#endif

	CGRect rect;
#if 0
//@@@
	rect.origin.x = 0.0;
	rect.origin.y = 0.0;
	rect.size.width = [[self superview] bounds].size.width;
	rect.size.height = [[self superview] bounds].size.height;
#elif 0
	rect.origin.x = -gPcgDun.getScrollBarX();
	rect.origin.y = -gPcgDun.getScrollBarY();
	rect.size.width = gPcgDun.getScrollBarW();
	rect.size.height = gPcgDun.getScrollBarH();
#elif 1
	rect.origin.x = 0.0;
	rect.origin.y = 0.0;
	rect.size.width = [self bounds].size.width;
	rect.size.height = [self bounds].size.height;
#endif
	CGContextRef graphContext = (CGContextRef)[[[self window] graphicsContext] graphicsPort];

	gui_begin();
	CGImageRef img = CGBitmapContextCreateImage(context);
	gui_end();

	CGContextDrawImage(graphContext, rect, img);

	CGImageRelease(img);
}

@end
