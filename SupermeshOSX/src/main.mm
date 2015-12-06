#include "SMFramework.h"
#include "SMApplication.h"
#import <Cocoa/Cocoa.h>

extern "C" {
	#include "libavformat/avformat.h"
	#include "libavcodec/avcodec.h"
	#include "libavutil/avutil.h"
	#include "libavdevice/avdevice.h"
}

@interface AppDelegate : NSObject<NSApplicationDelegate> {
    NSTimer *timer;
}
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification;
- (void)applicationWillTerminate:(NSNotification *)aNotification;
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication;
- (void)updateTimer:(NSTimer *)timer;
@end

@interface WinDelegate : NSObject<NSWindowDelegate> {
    Awesomium::WebView* webView;
}
@property (assign) Awesomium::WebView* webView;
- (void)windowDidResize:(NSNotification *)notification;
@end

int readsave_frames(int videoStreamIdx
					, AVFormatContext *pFormatCtx
					, AVCodecContext  *pCodecCtx
					, AVCodec         *pCodec
					)
{
	int             y, i;
	FILE           *pFile;
	AVPacket        packet;
	int             frameFinished;
	AVFrame        *pFrame;
	
	
	// Open file
	pFile=fopen("out.raw", "wb");
	if(pFile==NULL)
	{
		printf("Unable to open output file\n");
		return -1;
	}
	
	/// Allocate video frame
	pFrame = avcodec_alloc_frame();
	
	printf("\n");
	for(i=0; av_read_frame(pFormatCtx, &packet) >= 0;) {
		
		// Is this a packet from the video stream?
		if(packet.stream_index==videoStreamIdx) {
			i++;
			
			/// Decode video frame
			avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
			
			// Did we get a video frame?
			if(frameFinished) {
				printf("\rFrame [%d]: pts=%lld, pkt_pts=%lld, pkt_dts=%lld", i, pFrame->pts, pFrame->pkt_pts, pFrame->pkt_dts);
			}
		}
		
		// Free the packet that was allocated by av_read_frame
		av_free_packet(&packet);
	}
	printf("\n");
	
	/// Free the Y frame
	av_free(pFrame);
	
	// Close file
	fclose(pFile);
	
	return 0;
}

/*
int main(int argc, char *argv[]) {
	AVFormatContext *pFormatCtx;
	int             videoStreamIdx;
	AVCodecContext  *pCodecCtx;
	AVCodec         *pCodec;
	
	if(argc < 2) {
		printf("Please provide a movie file\n");
		return -1;
	}
	// Register all formats and codecs
	av_register_all();
	
	pFormatCtx = avformat_alloc_context();
	
	/// Open video file
	if(avformat_open_input(&pFormatCtx, argv[1], 0, NULL) != 0)
	{
		printf("avformat_open_input failed: Couldn't open file\n");
		return -1; // Couldn't open file
	}
	
	/// Retrieve stream information
	if(avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		printf("avformat_find_stream_info failed: Couldn't find stream information\n");
		return -1; // Couldn't find stream information
	}
	
	/// Dump information about file onto standard error
	av_dump_format(pFormatCtx, 0, argv[1], 0);
	
	
	/// Find the first video stream
	{
		int i = 0;
		videoStreamIdx=-1;
		for(i=0; 10; i++)
		{
			if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) { //CODEC_TYPE_VIDEO
				videoStreamIdx=i;
				break;
			}
		}
	}
	/// Check if video stream is found
	if(videoStreamIdx==-1)
		return -1; // Didn't find a video stream
	
	
	/// Get a pointer to the codec context for the video stream
	pCodecCtx = pFormatCtx->streams[videoStreamIdx]->codec;
	
	
	/// Find the decoder for the video stream
	pCodec = avcodec_find_decoder( pCodecCtx->codec_id);
	if(pCodec==NULL) {
		fprintf(stderr, "Unsupported codec!\n");
		return -1; // Codec not found
	}
	
	/// Open codec
	if( avcodec_open2(pCodecCtx, pCodec, NULL) < 0 )
		return -1; // Could not open codec
	
	// Read frames and save them to disk
	if ( readsave_frames(videoStreamIdx, pFormatCtx, pCodecCtx, pCodec) < 0)
	{
		return -1;
	}
	
	/// Close the codec
	avcodec_close(pCodecCtx);
	
	/// Close the video file
	avformat_close_input(&pFormatCtx);
	
	return 0;
}*/

int main(int argc, const char **argv)
{
	// create my pool
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    [NSApplication sharedApplication];
    NSWindow* window = [[[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, APP_WIDTH, APP_HEIGHT)
                                                styleMask:NSTitledWindowMask | NSResizableWindowMask | NSClosableWindowMask
                                                      backing:NSBackingStoreBuffered defer:NO]
                        autorelease];
    [window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
    [window setTitle:@APP_NAME];
    
	// setup application
	g_App = new SMApplication();
	Awesomium::WebView* view = g_App->Initialize();
        
    // Add our WebView to the Window's content view
    NSView* contentsContainer = [window contentView];
    NSView* contentsNativeView = view->window();
    NSRect contentsNativeViewFrame = [contentsContainer frame];
    contentsNativeViewFrame.origin = NSZeroPoint;
    [contentsNativeView setFrame:contentsNativeViewFrame];
    [contentsContainer addSubview:contentsNativeView];
 
	
    // create delegate
    WinDelegate* winDelegate = [[WinDelegate alloc] init];
    [window setDelegate:winDelegate];
    winDelegate.webView = view;
    
    // Activate the window
    [window makeKeyAndOrderFront:nil];
    
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    NSObject<NSApplicationDelegate>* appDelegate = [[AppDelegate alloc] init];
    [NSApp setDelegate:appDelegate];
    [NSApp activateIgnoringOtherApps:YES];
    [NSApp run];
    
    [NSApp setDelegate:nil];
    [appDelegate release];
    
    [window setDelegate:nil];
    [winDelegate release];
    
    [pool release];
    return 0;
}

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    timer = [NSTimer timerWithTimeInterval:(1.0f/60.0f)
                                    target:self
                                  selector:@selector(updateTimer:)
                                  userInfo:nil
                                   repeats:YES];
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    if (Awesomium::WebCore::instance())
        Awesomium::WebCore::instance()->Shutdown();
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication {
    return YES;
}

- (void)updateTimer:(NSTimer *)timer {
    if (Awesomium::WebCore::instance())
        Awesomium::WebCore::instance()->Update();
}

@end

@implementation WinDelegate

@synthesize webView;

- (void)windowDidResize:(NSNotification *)notification {
    NSWindow* window = [notification object];
    NSSize windowSize = [[window contentView] frame].size;
    webView->Resize((int)windowSize.width, (int)windowSize.height);
}

@end
