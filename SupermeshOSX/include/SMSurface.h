#ifndef SupermeshOSX_SMSurfaceFactory_h
#define SupermeshOSX_SMSurfaceFactory_h

#include "SMFramework.h"
#include <Awesomium/Surface.h>

class SMSurface : public Awesomium::Surface {
public:
    void Paint(unsigned char * src_buffer, int src_row_span, const Awesomium::Rect & src_rect, const Awesomium::Rect & dest_rect);
    void Scroll	(int dx, int dy, const Awesomium::Rect & clip_rect);
    
    SMSurface();
    ~SMSurface();
};

class SMSurfaceFactory : public Awesomium::SurfaceFactory {
public:
    SMSurface* CreateSurface (Awesomium::WebView *view, SMInt32 width, SMInt32 height);
    void DestroySurface (SMSurface *surface);
    
    SMSurfaceFactory();
    ~SMSurfaceFactory();
};

#endif
