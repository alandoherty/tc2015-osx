#include "SMDataSource.h"
#include <Awesomium/STLHelpers.h>
#include <Awesomium/WebCore.h>
#include <sys/stat.h>

using namespace Awesomium;

const char* rootDir = "../../../OSXWeb/";

off_t fsize(const char *filename) {
    struct stat st;
    
    if (stat(filename, &st) == 0)
        return st.st_size;
    
    fprintf(stderr, "Cannot determine size of %s: %s\n",
            filename, strerror(errno));
    
    return -1;
}

void SMDataSource::OnRequest(int request_id,
                             const Awesomium::ResourceRequest& request,
                             const Awesomium::WebString& path) {
    // convert to UTF8 first
    SMUInt32 utf8PathLen = path.ToUTF8(NULL, 0);
    char* utf8Path = (char*)malloc(utf8PathLen);
    path.ToUTF8(utf8Path, utf8PathLen);
    
    // calculate lengths
    SMInt32 rootLen = strlen(rootDir);
    
    // allocate path
    SMInt32 actualPathLen = rootLen + path.length() +1;
    char* actualPath = (char*)malloc(actualPathLen);
    actualPath[actualPathLen - 1] = '\0';
    
    // copy base
    memcpy(actualPath, rootDir, rootLen);
    
    // copy path
    memcpy(&actualPath[rootLen], utf8Path, path.length());
    
    // open file
    FILE* file = fopen(actualPath, "r");
    
    if (file == NULL) {
        static const char* notFound = "404 not found";
        SendResponse(request_id, strlen(notFound), (unsigned char*)notFound, WSLit("text/html"));
    } else {
        // read data
        SMInt32 fileSize = static_cast<SMInt32>(fsize(actualPath));
        
        if (fileSize == -1) {
            static const char* notFound = "File size failed";
            SendResponse(request_id, strlen(notFound), (unsigned char*)notFound, WSLit("text/html"));
        } else {
            char* buff = (char*)malloc(fileSize + 1);
            buff[fileSize - 1] = '\0';
            fread((void*)buff, fileSize, 1, file);
            
            // send
            SendResponse(request_id, fileSize, (unsigned char*)buff, WSLit("text/html"));
            
            // free buffer
            free(buff);
        }
        
        // close file
        fclose(file);
    }
    
    // free path
    free(actualPath);
    free(utf8Path);
}
