#include "SMFramework.h"
#import <Cocoa/Cocoa.h>
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>

using namespace Awesomium;

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





class SMDataSource : public Awesomium::DataSource {
public:
    SMDataSource() {}
    virtual ~SMDataSource() {}
    
    virtual void OnRequest(int request_id,
                           const Awesomium::ResourceRequest& request,
                           const Awesomium::WebString& path);
    
};

const char* html_str = "fuck SDL";


void SMDataSource::OnRequest(int request_id,
                             const Awesomium::ResourceRequest& request,
                             const Awesomium::WebString& path) {
    if (path == WSLit("index.html"))
        SendResponse(request_id,
                     strlen(html_str),
                     (const unsigned char*)html_str,
                     WSLit("text/html"));
}


int main(int argc, const char **argv)
{
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  [NSApplication sharedApplication];
  NSWindow* window = [[[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 800, 600)
                                                  styleMask:NSTitledWindowMask | NSResizableWindowMask | NSClosableWindowMask
                                                    backing:NSBackingStoreBuffered defer:NO]
                      autorelease];
  [window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
  [window setTitle:@APP_NAME];
  
  // Create the WebCore
  Awesomium::WebConfig config;
  Awesomium::WebCore* core = Awesomium::WebCore::Initialize(config);
    
    Awesomium::WebSession* session = core->CreateWebSession(Awesomium::WSLit(""), Awesomium::WebPreferences());
    session->AddDataSource(Awesomium::WSLit("Supermesh"), new SMDataSource());
  
  // Create our WebView and start loading a certain URL
  Awesomium::WebView* view = core->CreateWebView(800, 600, session,
                                                 Awesomium::kWebViewType_Window);
  view->LoadURL(Awesomium::WebURL(Awesomium::WSLit("asset://Supermesh/index.html")));
  
  // Add our WebView to the Window's content view
  NSView* contentsContainer = [window contentView];
  NSView* contentsNativeView = view->window();
  NSRect contentsNativeViewFrame = [contentsContainer frame];
  contentsNativeViewFrame.origin = NSZeroPoint;
  [contentsNativeView setFrame:contentsNativeViewFrame];
  [contentsContainer addSubview:contentsNativeView];
  
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
