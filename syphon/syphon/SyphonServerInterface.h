//
//  SyphonServerInterface.h
//  syphon
//
//  Created by Michael Schuff on 10/19/20.
//

#ifndef SyphonServerInterface_h
#define SyphonServerInterface_h



#include <OpenGL/OpenGL.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>

class Server {
    _serverOpaquePtr* _obj = 0;

    bool _error = false;

    CGLContextObj _context;
    std::string _name;

public:
    Server(std::string name);
    Server(const Server& src);
    ~Server();

    void publishFrameTexture(GLuint texID, Rect region, Size size, bool flipped);

    inline bool errorState() { return _error; }

    CGLContextObj& context() { return _context; };
    std::string name() { return _name; };
    ServerDescription serverDescription();

    bool hasClients();

    void stop();
};



#endif /* SyphonServerInterface_h */
