//
//  SyphonServer.m
//  syphon
//
//  Created by Michael Schuff on 10/19/20.
//

#include "SyphonBuildMacros.h"

#include <Syphon/Syphon.h>
#include "SyphonServerInterface.h"

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#import <OpenGL/gl3.h>
#include <OpenGL/glu.h>


Server::Server(std::string name)
{
    _context = CGLGetCurrentContext();
    _name = name;

    NSString* n_ = toNSString(name);
    SyphonServer* srv = [[SyphonServer alloc] initWithName:n_ context:_context options:@{}];

    _obj = new _serverOpaquePtr(srv);
    [srv release]; // retained by _serverOpaquePtr()
    if (!srv)
        _error = true;
}

Server::Server(const Server& src)
{
    _obj = new _serverOpaquePtr(src._obj->obj);
    _error = src._error;
    _context = src._context;
    _name = src._name;
}

void Server::publishFrameTexture(GLuint texID, Rect _region, Size _size, bool flipped)
{
    auto target = GL_TEXTURE_2D;
    SyphonServer* _s = _obj->obj;

    NSRect region = NSMakeRect(_region.origin.x, _region.origin.y, _region.size.width, _region.size.height);
    NSSize size = NSMakeSize(_size.width, _size.height);

    [_s publishFrameTexture:texID textureTarget:target imageRegion:region textureDimensions:size flipped:flipped];
}

ServerDescription Server::serverDescription()
{
    if (_error)
        return ServerDescription();
    NSDictionary* _dict = [_obj->obj serverDescription];
    auto _opaque = new _serverDescriptionOpaquePtr(_dict);
    ServerDescription ret(_opaque);

    return ret;
};

bool Server::hasClients()
{
    return [_obj->obj hasClients];
}

void Server::stop()
{
    [_obj->obj stop];
}

Server::~Server()
{
    [_obj->obj stop];
    delete _obj;
}
