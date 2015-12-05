#include "SMSurface.h"

SMSurface* SMSurfaceFactory::CreateSurface(Awesomium::WebView *view, SMInt32 width, SMInt32 height) {
    return new SMSurface();
}

void SMSurfaceFactory::DestroySurface(SMSurface* surface) {
    
}
