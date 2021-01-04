//  License (OLC-3)
//  ~~~~~~~~~~~~~~~
//
//  Copyright 2018 - 2020 OneLoneCoder.com
//
//  Redistribution and use in source and binary forms, with or without modification,
//  are permitted provided that the following conditions are met:
//
//  1. Redistributions or derivations of source code must retain the above copyright
//  notice, this list of conditions and the following disclaimer.
//
//  2. Redistributions or derivative works in binary form must reproduce the above
//  copyright notice. This list of conditions and the following    disclaimer must be
//  reproduced in the documentation and/or other materials provided with the distribution.
//
//  3. Neither the name of the copyright holder nor the names of its contributors may
//  be used to endorse or promote products derived from this software without specific
//  prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT    HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL,    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  SUCH DAMAGE.
//
//  Thanks
//  ~~~~~~
//  I'd like to extend thanks to Bispoo, Eremiell, slavka, gurkanctn, Phantim, IProgramInCPP
//  JackOJC, KrossX, Huhlig, Dragoneye, Appa, JustinRichardsMusic, SliceNDice, dandistine
//  Ralakus, Gorbit99, raoul, joshinils, benedani, Moros1138, Alexio, SaladinAkara & MagetzUb
//  for advice, ideas and testing, and I'd like to extend my appreciation to the
//  200K YouTube followers, 80+ Patreons and 10K Discord server members who give me
//  the motivation to keep going with all this :D
//
//  Significant Contributors: @Moros1138, @SaladinAkara, @MaGetzUb, @slavka,
//                          @Dragoneye, @Gorbit99 & @Mumflr
//
//  Special thanks to those who bring gifts!
//  GnarGnarHead.......Domina
//  Gorbit99...........Bastion, Ori & The Blind Forest, Terraria
//  Marti Morta........Gris
//  Danicron...........Terraria
//  SaladinAkara.......Aseprite
//  AlterEgo...........Final Fantasy XII - The Zodiac Age
//  SlicEnDicE.........Noita
//
//  Special thanks to my Patreons too - I wont name you on here, but I've
//  certainly enjoyed my tea and flapjacks :D
//
//  Author
//  ~~~~~~
//  David Barr, aka javidx9, �OneLoneCoder 2018, 2019, 2020

#ifndef OLC_PGE_DEF
#define OLC_PGE_DEF

// MARK: Standard Includes
// +------------------------------------------------------------------------------+
// | STANDARD INCLUDES                                                            |
// +------------------------------------------------------------------------------+
#include <cmath>
#include <cstdint>
#include <string>
#include <iostream>
#include <streambuf>
#include <sstream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <fstream>
#include <map>
#include <functional>
#include <algorithm>
#include <array>
#include <cstring>

// MARK: Compiler Configuration
// +------------------------------------------------------------------------------+
// | COMPILER CONFIGURATION ODDITIES                                              |
// +------------------------------------------------------------------------------+
#define USE_EXPERIMENTAL_FS

#if defined(_WIN32)
#if _MSC_VER >= 1920 && _MSVC_LANG >= 201703L
#undef USE_EXPERIMENTAL_FS
#endif
#endif

#if defined(__linux__) || defined(__MINGW32__) || defined(__EMSCRIPTEN__) || defined(__FreeBSD__) || defined(__APPLE__)
#if __cplusplus >= 201703L
#undef USE_EXPERIMENTAL_FS
#endif
#endif

#if defined(__APPLE__)
#define PGE_USE_CUSTOM_START
#endif

#if defined(USE_EXPERIMENTAL_FS) || defined(FORCE_EXPERIMENTAL_FS)
// C++14
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
namespace _gfs = std::experimental::filesystem::v1;
#else
// C++17
#include <filesystem>
namespace _gfs = std::filesystem;
#endif

#if defined(UNICODE) || defined(_UNICODE)
#define olcT(s) L##s
#else
#define olcT(s) s
#endif

#define UNUSED(x) (void)(x)

#if !defined(OLC_GFX_OPENGL33) && !defined(OLC_GFX_DIRECTX10)
#define OLC_GFX_OPENGL10
#endif

#if defined(_WIN32)
#if defined(OLC_IMAGE_STB)
#define PGE_ILOADER_STB
#else
#define PGE_ILOADER_GDI
#endif
#endif

#if defined(__linux__) || defined(__APPLE__)
#if defined(OLC_IMAGE_STB)
#define PGE_ILOADER_STB
#else
#define PGE_ILOADER_LIBPNG
#endif
#endif

//MARK: olcPixelGameEngine
// +------------------------------------------------------------------------------+
// | olcPixelGameEngine INTERFACE DECLARATION                                     |
// +------------------------------------------------------------------------------+
namespace olc {
    class PixelGameEngine;
    class Sprite;
    
    // Pixel Game Engine Advanced Configuration
    constexpr uint8_t  nMouseButtons = 5;
    constexpr uint8_t  nDefaultAlpha = 0xFF;
    constexpr uint32_t nDefaultPixel = (nDefaultAlpha << 24);
    enum rcode { FAIL = 0, OK = 1, NO_FILE = -1 };
    
    //MARK: olc::Pixel
    // +------------------------------------------------------------------------------+
    // | olc::Pixel - Represents a 32-Bit RGBA colour                                 |
    // +------------------------------------------------------------------------------+
    struct Pixel {
        union {
            uint32_t n = nDefaultPixel;
            struct { uint8_t r; uint8_t g; uint8_t b; uint8_t a; };
        };
        
        enum Mode { NORMAL, MASK, ALPHA, CUSTOM };
        
        Pixel();
        Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = nDefaultAlpha);
        Pixel(uint32_t p);
        bool operator==(const Pixel& p) const;
        bool operator!=(const Pixel& p) const;
    };
    
    Pixel PixelF(float red, float green, float blue, float alpha = 1.0f);
    
    
    //MARK: Constants
    static const Pixel
    GREY(192, 192, 192), DARK_GREY(128, 128, 128), VERY_DARK_GREY(64, 64, 64),
    RED(255, 0, 0), DARK_RED(128, 0, 0), VERY_DARK_RED(64, 0, 0),
    YELLOW(255, 255, 0), DARK_YELLOW(128, 128, 0), VERY_DARK_YELLOW(64, 64, 0),
    GREEN(0, 255, 0), DARK_GREEN(0, 128, 0), VERY_DARK_GREEN(0, 64, 0),
    CYAN(0, 255, 255), DARK_CYAN(0, 128, 128), VERY_DARK_CYAN(0, 64, 64),
    BLUE(0, 0, 255), DARK_BLUE(0, 0, 128), VERY_DARK_BLUE(0, 0, 64),
    MAGENTA(255, 0, 255), DARK_MAGENTA(128, 0, 128), VERY_DARK_MAGENTA(64, 0, 64),
    WHITE(255, 255, 255), BLACK(0, 0, 0), BLANK(0, 0, 0, 0);
    
    enum Key {
        NONE,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        UP, DOWN, LEFT, RIGHT,
        SPACE, TAB, SHIFT, CTRL, INS, DEL, HOME, END, PGUP, PGDN,
        BACK, ESCAPE, RETURN, ENTER, PAUSE, SCROLL,
        NP0, NP1, NP2, NP3, NP4, NP5, NP6, NP7, NP8, NP9,
        NP_MUL, NP_DIV, NP_ADD, NP_SUB, NP_DECIMAL, PERIOD
    };
    
    
    // MARK: olc::vX2d
    // +------------------------------------------------------------------------------+
    // | olc::vX2d - A generic 2D vector type                                         |
    // +------------------------------------------------------------------------------+
#if !defined(OLC_IGNORE_VEC2D)
    template <class T>
    struct v2d_generic {
        T x = 0;
        T y = 0;
        v2d_generic() : x(0), y(0) {}
        v2d_generic(T _x, T _y) : x(_x), y(_y) {}
        v2d_generic(const v2d_generic& v) : x(v.x), y(v.y) {}
        v2d_generic& operator=(const v2d_generic& v) = default;
        T mag() { return T(std::sqrt(x * x + y * y)); }
        T mag2() { return x * x + y * y; }
        v2d_generic  norm() { T r = 1 / mag(); return v2d_generic(x * r, y * r); }
        v2d_generic  perp() { return v2d_generic(-y, x); }
        T dot(const v2d_generic& rhs) { return this->x * rhs.x + this->y * rhs.y; }
        T cross(const v2d_generic& rhs) { return this->x * rhs.y - this->y * rhs.x; }
        v2d_generic  operator +  (const v2d_generic& rhs) const { return v2d_generic(this->x + rhs.x, this->y + rhs.y); }
        v2d_generic  operator -  (const v2d_generic& rhs) const { return v2d_generic(this->x - rhs.x, this->y - rhs.y); }
        v2d_generic  operator *  (const T& rhs)           const { return v2d_generic(this->x * rhs, this->y * rhs); }
        v2d_generic  operator *  (const v2d_generic& rhs) const { return v2d_generic(this->x * rhs.x, this->y * rhs.y); }
        v2d_generic  operator /  (const T& rhs)           const { return v2d_generic(this->x / rhs, this->y / rhs); }
        v2d_generic  operator /  (const v2d_generic& rhs) const { return v2d_generic(this->x / rhs.x, this->y / rhs.y); }
        v2d_generic& operator += (const v2d_generic& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
        v2d_generic& operator -= (const v2d_generic& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
        v2d_generic& operator *= (const T& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
        v2d_generic& operator /= (const T& rhs) { this->x /= rhs; this->y /= rhs; return *this; }
        v2d_generic  operator +  () const { return { +x, +y }; }
        v2d_generic  operator -  () const { return { -x, -y }; }
        bool operator == (const v2d_generic& rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
        bool operator != (const v2d_generic& rhs) const { return (this->x != rhs.x || this->y != rhs.y); }
        const std::string str() const { return std::string("(") + std::to_string(this->x) + "," + std::to_string(this->y) + ")"; }
        friend std::ostream& operator << (std::ostream& os, const v2d_generic& rhs) { os << rhs.str(); return os; }
        operator v2d_generic<int32_t>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; }
        operator v2d_generic<float>() const { return { static_cast<float>(this->x), static_cast<float>(this->y) }; }
        operator v2d_generic<double>() const { return { static_cast<double>(this->x), static_cast<double>(this->y) }; }
    };
    
    template<class T> inline v2d_generic<T> operator * (const float& lhs, const v2d_generic<T>& rhs)
    { return v2d_generic<T>((T)(lhs * (float)rhs.x), (T)(lhs * (float)rhs.y)); }
    template<class T> inline v2d_generic<T> operator * (const double& lhs, const v2d_generic<T>& rhs)
    { return v2d_generic<T>((T)(lhs * (double)rhs.x), (T)(lhs * (double)rhs.y)); }
    template<class T> inline v2d_generic<T> operator * (const int& lhs, const v2d_generic<T>& rhs)
    { return v2d_generic<T>((T)(lhs * (int)rhs.x), (T)(lhs * (int)rhs.y)); }
    template<class T> inline v2d_generic<T> operator / (const float& lhs, const v2d_generic<T>& rhs)
    { return v2d_generic<T>((T)(lhs / (float)rhs.x), (T)(lhs / (float)rhs.y)); }
    template<class T> inline v2d_generic<T> operator / (const double& lhs, const v2d_generic<T>& rhs)
    { return v2d_generic<T>((T)(lhs / (double)rhs.x), (T)(lhs / (double)rhs.y)); }
    template<class T> inline v2d_generic<T> operator / (const int& lhs, const v2d_generic<T>& rhs)
    { return v2d_generic<T>((T)(lhs / (int)rhs.x), (T)(lhs / (int)rhs.y)); }
    
    typedef v2d_generic<int32_t> vi2d;
    typedef v2d_generic<uint32_t> vu2d;
    typedef v2d_generic<float> vf2d;
    typedef v2d_generic<double> vd2d;
#endif
    
    
    // MARK: olc::HWButton
    // +------------------------------------------------------------------------------+
    // | olc::HWButton - Represents the state of a hardware button (mouse/key/joy)    |
    // +------------------------------------------------------------------------------+
    struct HWButton{
        bool bPressed = false;  // Set once during the frame the event occurs
        bool bReleased = false; // Set once during the frame the event occurs
        bool bHeld = false;   // Set true for all frames between pressed and released events
    };
    
    
    // MARK: olc::Sprite
    // +------------------------------------------------------------------------------+
    // | olc::Sprite - An image represented by a 2D array of olc::Pixel               |
    // +------------------------------------------------------------------------------+
    class Sprite {
    public:
        Sprite(int32_t w, int32_t h);
        ~Sprite();
        
        
    public:
        int32_t width = 0;
        int32_t height = 0;
        enum Mode { NORMAL, PERIODIC };
        enum Flip { NONE = 0, HORIZ = 1, VERT = 2 };
        
    public:
        Pixel GetPixel(int32_t x, int32_t y) const;
        bool  SetPixel(int32_t x, int32_t y, Pixel p);
        Pixel GetPixel(const olc::vi2d& a) const;
        bool  SetPixel(const olc::vi2d& a, Pixel p);
        Pixel* GetData();
        Pixel* pColData = nullptr;
        Mode modeSample = Mode::NORMAL;
        
    };
    
    // MARK: olc::Renderer
    // +------------------------------------------------------------------------------+
    // | olc::Renderer - Renders                                                      |
    // +------------------------------------------------------------------------------+
    class Renderer {
    public:
        virtual ~Renderer() = default;
        virtual void       PrepareDevice() = 0;
        virtual olc::rcode CreateDevice(std::vector<void*> params, bool bFullScreen, bool bVSYNC) = 0;
        virtual olc::rcode DestroyDevice() = 0;
        virtual void       DisplayFrame() = 0;
        virtual void       PrepareDrawing() = 0;
        virtual void       DrawWindowQuad(const olc::vf2d& offset, const olc::vf2d& scale, const olc::Pixel tint) = 0;
        virtual uint32_t   CreateTexture(const uint32_t width, const uint32_t height) = 0;
        virtual void       UpdateTexture(uint32_t id, olc::Sprite* spr) = 0;
        virtual uint32_t   DeleteTexture(const uint32_t id) = 0;
        virtual void       ApplyTexture(uint32_t id) = 0;
        virtual void       UpdateViewport(const olc::vi2d& pos, const olc::vi2d& size) = 0;
        virtual void       ClearBuffer(olc::Pixel p, bool bDepth) = 0;
        static olc::PixelGameEngine* ptrPGE;
    };
    
    // MARK: olc::Platform
    // +------------------------------------------------------------------------------+
    // | olc::Platform - Various Platform related things                              |
    // +------------------------------------------------------------------------------+
    class Platform {
    public:
        virtual ~Platform() = default;
        virtual olc::rcode ApplicationStartUp() = 0;
        virtual olc::rcode ApplicationCleanUp() = 0;
        virtual olc::rcode ThreadStartUp() = 0;
        virtual olc::rcode ThreadCleanUp() = 0;
        virtual olc::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc::vi2d& vViewPos, const olc::vi2d& vViewSize) = 0;
        virtual olc::rcode CreateWindowPane(const olc::vi2d& vWindowPos, olc::vi2d& vWindowSize, bool bFullScreen) = 0;
        virtual olc::rcode SetWindowTitle(const std::string& s) = 0;
        virtual olc::rcode StartSystemEventLoop() = 0;
        virtual olc::rcode HandleSystemEvent() = 0;
        static olc::PixelGameEngine* ptrPGE;
    };
    
    
    
    static std::unique_ptr<Renderer> renderer;
    static std::unique_ptr<Platform> platform;
    static std::map<size_t, uint8_t> mapKeys;
    
    // MARK: olc::PixelGameEngine
    // +------------------------------------------------------------------------------+
    // | olc::PixelGameEngine - The main BASE class for your application              |
    // +------------------------------------------------------------------------------+
    class PixelGameEngine {
    public:
        PixelGameEngine();
        virtual ~PixelGameEngine();
    public:
        olc::rcode Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h,
                             bool full_screen = false, bool vsync = false, bool cohesion = false);
        olc::rcode Start();
        
    public: // User Override Interfaces
            // Called once on application startup, use to load your resources
        virtual bool OnUserCreate();
        // Called every frame, and provides you with a time per frame value
        virtual bool OnUserUpdate(float fElapsedTime);
        // Called once on application termination, so you can be one clean coder
        virtual bool OnUserDestroy();
        
    public: // Hardware Interfaces
            // Returns true if window is currently in focus
        bool IsFocused() const;
        // Get the state of a specific keyboard button
        HWButton GetKey(Key k) const;
        // Get the state of a specific mouse button
        HWButton GetMouse(uint32_t b) const;
        // Get Mouse X coordinate in "pixel" space
        int32_t GetMouseX() const;
        // Get Mouse Y coordinate in "pixel" space
        int32_t GetMouseY() const;
        // Get Mouse Wheel Delta
        int32_t GetMouseWheel() const;
        // Get the mouse in window space
        const olc::vi2d& GetWindowMouse() const;
        // Gets the mouse as a vector to keep Tarriest happy
        const olc::vi2d& GetMousePos() const;
        
    public: // Utility
            // Returns the width of the screen in "pixels"
        int32_t ScreenWidth() const;
        // Returns the height of the screen in "pixels"
        int32_t ScreenHeight() const;
        // Returns the width of the currently selected drawing target in "pixels"
        int32_t GetDrawTargetWidth() const;
        // Returns the height of the currently selected drawing target in "pixels"
        int32_t GetDrawTargetHeight() const;
        // Returns the currently active draw target
        olc::Sprite* GetDrawTarget() const;
        // Resize the primary screen sprite
        void SetScreenSize(int w, int h);
        // Gets the current Frames Per Second
        uint32_t GetFPS() const;
        // Gets last update of elapsed time
        float GetElapsedTime() const;
        // Gets Actual Window size
        const olc::vi2d& GetWindowSize() const;
        // Gets pixel scale
        const olc::vi2d& GetPixelSize() const;
        // Gets actual pixel scale
        const olc::vi2d& GetScreenPixelSize() const;
        
    public: // CONFIGURATION ROUTINES
            // window targeting functions
        void EnableWindow(bool b);
        void SetWindowOffset(const olc::vf2d& offset);
        void SetWindowOffset(float x, float y);
        void SetWindowScale(const olc::vf2d& scale);
        void SetWindowScale(float x, float y);
        void SetWindowTint(const olc::Pixel& tint);
        void SetWindowCustomRenderFunction(std::function<void()> f);
        
        
        // Change the pixel mode for different optimisations
        // olc::Pixel::NORMAL = No transparency
        // olc::Pixel::MASK   = Transparent if alpha is < 255
        // olc::Pixel::ALPHA  = Full transparency
        void SetPixelMode(Pixel::Mode m);
        Pixel::Mode GetPixelMode();
        // Use a custom blend function
        void SetPixelMode(std::function<olc::Pixel(const int x, const int y, const olc::Pixel& pSource, const olc::Pixel& pDest)> pixelMode);
        // Change the blend factor form between 0.0f to 1.0f;
        void SetPixelBlend(float fBlend);
        
        
        
    public: // DRAWING ROUTINES
            // Draws a single Pixel
        virtual bool Draw(int32_t x, int32_t y, Pixel p = olc::WHITE);
        bool Draw(const olc::vi2d& pos, Pixel p = olc::WHITE);
        
        void Clear(Pixel p);
        // Clears the rendering back buffer
        void ClearBuffer(Pixel p, bool bDepth = true);
        
        
    public: // Branding
        std::string sAppName;
        
    private: // Inner mysterious workings
        Pixel::Mode nPixelMode = Pixel::NORMAL;
        float       fBlendFactor = 1.0f;
        olc::vi2d   vScreenSize = { 256, 240 };
        olc::vf2d   vInvScreenSize = { 1.0f / 256.0f, 1.0f / 240.0f };
        olc::vi2d   vPixelSize = { 4, 4 };
        olc::vi2d   vScreenPixelSize = { 4, 4 };
        olc::vi2d   vMousePos = { 0, 0 };
        int32_t     nMouseWheelDelta = 0;
        olc::vi2d   vMousePosCache = { 0, 0 };
        olc::vi2d   vMouseWindowPos = { 0, 0 };
        int32_t     nMouseWheelDeltaCache = 0;
        olc::vi2d   vWindowSize = { 0, 0 };
        olc::vi2d   vViewPos = { 0, 0 };
        olc::vi2d   vViewSize = { 0,0 };
        bool        bFullScreen = false;
        olc::vf2d   vPixel = { 1.0f, 1.0f };
        bool        bHasInputFocus = false;
        bool        bHasMouseFocus = false;
        bool        bEnableVSYNC = false;
        float       fFrameTimer = 1.0f;
        float       fLastElapsed = 0.0f;
        int         nFrameCount = 0;
        uint32_t    nLastFPS = 0;
        bool        bPixelCohesion = false;
        std::function<olc::Pixel(const int x, const int y, const olc::Pixel&, const olc::Pixel&)> funcPixelMode;
        std::chrono::time_point<std::chrono::system_clock> m_tp1, m_tp2;
        
        // window vars
        olc::vf2d vOffset = { 0, 0 };
        olc::vf2d vScale = { 1, 1 };
        olc::Sprite* pDrawTarget = nullptr;
        uint32_t nResID = 0;
        olc::Pixel tint = olc::WHITE;
        std::function<void()> funcHook = nullptr;
        
        
        // State of keyboard
        bool        pKeyNewState[256] = { 0 };
        bool        pKeyOldState[256] = { 0 };
        HWButton    pKeyboardState[256] = { 0 };
        
        // State of mouse
        bool        pMouseNewState[nMouseButtons] = { 0 };
        bool        pMouseOldState[nMouseButtons] = { 0 };
        HWButton    pMouseState[nMouseButtons] = { 0 };
        
        // The main engine thread
        void        EngineThread();
        
        // At the very end of this file, chooses which
        // components to compile
        void        olc_ConfigureSystem();
        
        // If anything sets this flag to false, the engine
        // "should" shut down gracefully
        static std::atomic<bool>    bAtomActive;
        
    public:
        void olc_UpdateMouse(int32_t x, int32_t y);
        void olc_UpdateMouseWheel(int32_t delta);
        void olc_UpdateWindowSize(int32_t x, int32_t y);
        void olc_UpdateViewport();
        void olc_ConstructFontSheet();
        void olc_CoreUpdate();
        void olc_PrepareEngine();
        void olc_UpdateMouseState(int32_t button, bool state);
        void olc_UpdateKeyState(int32_t key, bool state);
        void olc_UpdateMouseFocus(bool state);
        void olc_UpdateKeyFocus(bool state);
        void olc_Terminate();
        
    };
}

#endif // OLC_PGE_DEF



// MARK: OLC_PGE_APPLICATION
// +------------------------------------------------------------------------------+
// | START OF OLC_PGE_APPLICATION                                                 |
// +------------------------------------------------------------------------------+
#ifdef OLC_PGE_APPLICATION
#undef OLC_PGE_APPLICATION


// +------------------------------------------------------------------------------+
// | olcPixelGameEngine INTERFACE IMPLEMENTATION (CORE)                           |
// | Note: The core implementation is platform independent                        |
// +------------------------------------------------------------------------------+
// MARK: olc::Pixel impl;
namespace olc {
    Pixel::Pixel() { r = 0; g = 0; b = 0; a = nDefaultAlpha; }
    
    Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
        n = red | (green << 8) | (blue << 16) | (alpha << 24);
    } // Thanks jarekpelczar
    
    Pixel::Pixel(uint32_t p) { n = p; }
    
    bool Pixel::operator==(const Pixel& p) const { return n == p.n; }
    
    bool Pixel::operator!=(const Pixel& p) const { return n != p.n; }
    
    Pixel PixelF(float red, float green, float blue, float alpha) {
        return Pixel(uint8_t(red * 255.0f), uint8_t(green * 255.0f), uint8_t(blue * 255.0f), uint8_t(alpha * 255.0f));
    }
}


// MARK: olc::Sprite impl;
namespace olc {
    Sprite::Sprite(int32_t w, int32_t h) {
        if (pColData) delete[] pColData;
        width = w;    height = h;
        pColData = new Pixel[width * height];
        for (int32_t i = 0; i < width * height; i++)
        pColData[i] = Pixel();
    }
    
    Sprite::~Sprite() {
        if (pColData) delete[] pColData;
    }
    Pixel Sprite::GetPixel(const olc::vi2d& a) const { return GetPixel(a.x, a.y); }
    
    bool Sprite::SetPixel(const olc::vi2d& a, Pixel p) { return SetPixel(a.x, a.y, p); }
    
    Pixel Sprite::GetPixel(int32_t x, int32_t y) const {
        if (modeSample == olc::Sprite::Mode::NORMAL) {
            if (x >= 0 && x < width && y >= 0 && y < height)
                return pColData[y * width + x];
            else
                return Pixel(0, 0, 0, 0);
        } else {
            return pColData[abs(y % height) * width + abs(x % width)];
        }
    }
    
    bool Sprite::SetPixel(int32_t x, int32_t y, Pixel p) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pColData[y * width + x] = p;
            return true;
        }
        else
            return false;
    }
    
    Pixel* Sprite::GetData() { return pColData; }
    
}


// MARK: olc::PixelGameEngine impl;
namespace olc {
    PixelGameEngine::PixelGameEngine() {
        sAppName = "Undefined";
        
        // Bring in relevant Platform & Rendering systems depending
        // on compiler parameters
        olc_ConfigureSystem();
    }
    
    PixelGameEngine::~PixelGameEngine() { }
    
    
    olc::rcode PixelGameEngine::Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h, bool full_screen, bool vsync, bool cohesion) {
        bPixelCohesion = cohesion;
        vScreenSize = { screen_w, screen_h };
        vInvScreenSize = { 1.0f / float(screen_w), 1.0f / float(screen_h) };
        vPixelSize = { pixel_w, pixel_h };
        vWindowSize = vScreenSize * vPixelSize;
        bFullScreen = full_screen;
        bEnableVSYNC = vsync;
        vPixel = 2.0f / vScreenSize;
        
        if (vPixelSize.x <= 0 || vPixelSize.y <= 0 || vScreenSize.x <= 0 || vScreenSize.y <= 0)
            return olc::FAIL;
        
        
        return olc::OK;
    }
    
    
    void PixelGameEngine::SetScreenSize(int w, int h) {
        vScreenSize = { w, h };
        vInvScreenSize = { 1.0f / float(w), 1.0f / float(h) };
        delete pDrawTarget; // Erase existing window sprites
        pDrawTarget = new Sprite(vScreenSize.x, vScreenSize.y);
        
        renderer->ClearBuffer(olc::BLACK, true);
        renderer->DisplayFrame();
        renderer->ClearBuffer(olc::BLACK, true);
        renderer->UpdateViewport(vViewPos, vViewSize);
    }
    
#if !defined(PGE_USE_CUSTOM_START)
    olc::rcode PixelGameEngine::Start() {
        if (platform->ApplicationStartUp() != olc::OK) return olc::FAIL;
        
        // Construct the window
        if (platform->CreateWindowPane({ 30,30 }, vWindowSize, bFullScreen) != olc::OK) return olc::FAIL;
        olc_UpdateWindowSize(vWindowSize.x, vWindowSize.y);
        
        // Start the thread
        bAtomActive = true;
        std::thread t = std::thread(&PixelGameEngine::EngineThread, this);
        
        // Some implementations may form an event loop here
        platform->StartSystemEventLoop();
        
        // Wait for thread to be exited
        t.join();
        
        if (platform->ApplicationCleanUp() != olc::OK) return olc::FAIL;
        
        return olc::OK;
    }
#endif
    
    
    void PixelGameEngine::SetWindowOffset(const olc::vf2d& offset) {
        SetWindowOffset(offset.x, offset.y);
    }
    
    void PixelGameEngine::SetWindowOffset(float x, float y) {
        vOffset = { x, y };
    }
    
    void PixelGameEngine::SetWindowScale(const olc::vf2d& scale) {
        SetWindowScale(scale.x, scale.y);
    }
    
    void PixelGameEngine::SetWindowScale(float x, float y) {
        vScale = { x, y };
    }
    
    void PixelGameEngine::SetWindowTint(const olc::Pixel& t_tint) {
        tint = t_tint;
    }
    
    void PixelGameEngine::SetWindowCustomRenderFunction(std::function<void()> f) {
        funcHook = f;
    }
    
    
    Sprite* PixelGameEngine::GetDrawTarget() const { return pDrawTarget; }
    
    int32_t PixelGameEngine::GetDrawTargetWidth() const {
        if (pDrawTarget)
            return pDrawTarget->width;
        else
            return 0;
    }
    
    int32_t PixelGameEngine::GetDrawTargetHeight() const {
        if (pDrawTarget)
            return pDrawTarget->height;
        else
            return 0;
    }
    
    uint32_t PixelGameEngine::GetFPS() const { return nLastFPS; }
    
    bool PixelGameEngine::IsFocused() const { return bHasInputFocus; }
    
    HWButton PixelGameEngine::GetKey(Key k) const { return pKeyboardState[k]; }
    
    HWButton PixelGameEngine::GetMouse(uint32_t b) const { return pMouseState[b]; }
    
    int32_t PixelGameEngine::GetMouseX() const { return vMousePos.x; }
    
    int32_t PixelGameEngine::GetMouseY() const { return vMousePos.y; }
    
    const olc::vi2d& PixelGameEngine::GetMousePos() const { return vMousePos; }
    
    int32_t PixelGameEngine::GetMouseWheel() const { return nMouseWheelDelta; }
    
    int32_t PixelGameEngine::ScreenWidth() const { return vScreenSize.x; }
    
    int32_t PixelGameEngine::ScreenHeight() const { return vScreenSize.y; }
    
    float PixelGameEngine::GetElapsedTime() const { return fLastElapsed; }
    
    const olc::vi2d& PixelGameEngine::GetWindowSize() const { return vWindowSize; }
    
    const olc::vi2d& PixelGameEngine::GetPixelSize() const { return vPixelSize; }
    
    const olc::vi2d& PixelGameEngine::GetScreenPixelSize() const { return vScreenPixelSize; }
    
    const olc::vi2d& PixelGameEngine::GetWindowMouse() const { return vMouseWindowPos; }
    
    
    bool PixelGameEngine::Draw(const olc::vi2d& pos, Pixel p) {
        return Draw(pos.x, pos.y, p);
    }
    
    // This is it, the critical function that plots a pixel
    bool PixelGameEngine::Draw(int32_t x, int32_t y, Pixel p) {
        if (!pDrawTarget) return false;
        
        if (nPixelMode == Pixel::NORMAL) {
            return pDrawTarget->SetPixel(x, y, p);
        }
        
        if (nPixelMode == Pixel::MASK) {
            if (p.a == 255)
                return pDrawTarget->SetPixel(x, y, p);
        }
        
        if (nPixelMode == Pixel::ALPHA) {
            Pixel d = pDrawTarget->GetPixel(x, y);
            float a = (float)(p.a / 255.0f) * fBlendFactor;
            float c = 1.0f - a;
            float r = a * (float)p.r + c * (float)d.r;
            float g = a * (float)p.g + c * (float)d.g;
            float b = a * (float)p.b + c * (float)d.b;
            return pDrawTarget->SetPixel(x, y, Pixel((uint8_t)r, (uint8_t)g, (uint8_t)b/*, (uint8_t)(p.a * fBlendFactor)*/));
        }
        
        if (nPixelMode == Pixel::CUSTOM) {
            return pDrawTarget->SetPixel(x, y, funcPixelMode(x, y, p, pDrawTarget->GetPixel(x, y)));
        }
        
        return false;
    }
    
    
    
    void PixelGameEngine::Clear(Pixel p) {
        int pixels = GetDrawTargetWidth() * GetDrawTargetHeight();
        Pixel* m = GetDrawTarget()->GetData();
        for (int i = 0; i < pixels; i++) m[i] = p;
    }
    
    void PixelGameEngine::ClearBuffer(Pixel p, bool bDepth) {
        renderer->ClearBuffer(p, bDepth);
    }
    
    
    void PixelGameEngine::SetPixelMode(Pixel::Mode m) { nPixelMode = m; }
    
    Pixel::Mode PixelGameEngine::GetPixelMode() { return nPixelMode; }
    
    void PixelGameEngine::SetPixelMode(std::function<olc::Pixel(const int x, const int y, const olc::Pixel&, const olc::Pixel&)> pixelMode) {
        funcPixelMode = pixelMode;
        nPixelMode = Pixel::Mode::CUSTOM;
    }
    
    void PixelGameEngine::SetPixelBlend(float fBlend) {
        fBlendFactor = fBlend;
        if (fBlendFactor < 0.0f) fBlendFactor = 0.0f;
        if (fBlendFactor > 1.0f) fBlendFactor = 1.0f;
    }
    
    // User must override these functions as required. I have not made
    // them abstract because I do need a default behaviour to occur if
    // they are not overwritten
    
    bool PixelGameEngine::OnUserCreate() { return false; }
    
    bool PixelGameEngine::OnUserUpdate(float fElapsedTime) { UNUSED(fElapsedTime);  return false; }
    
    bool PixelGameEngine::OnUserDestroy() { return true; }
    //////////////////////////////////////////////////////////////////
    
    void PixelGameEngine::olc_UpdateViewport() {
        int32_t ww = vScreenSize.x * vPixelSize.x;
        int32_t wh = vScreenSize.y * vPixelSize.y;
        float wasp = (float)ww / (float)wh;
        
        if (bPixelCohesion) {
            vScreenPixelSize = (vWindowSize / vScreenSize);
            vViewSize = (vWindowSize / vScreenSize) * vScreenSize;
        } else {
            vViewSize.x = (int32_t)vWindowSize.x;
            vViewSize.y = (int32_t)((float)vViewSize.x / wasp);
            
            if (vViewSize.y > vWindowSize.y) {
                vViewSize.y = vWindowSize.y;
                vViewSize.x = (int32_t)((float)vViewSize.y * wasp);
            }
        }
        
        vViewPos = (vWindowSize - vViewSize) / 2;
    }
    
    void PixelGameEngine::olc_UpdateWindowSize(int32_t x, int32_t y) {
        vWindowSize = { x, y };
        olc_UpdateViewport();
    }
    
    void PixelGameEngine::olc_UpdateMouseWheel(int32_t delta) {
        nMouseWheelDeltaCache += delta;
    }
    
    void PixelGameEngine::olc_UpdateMouse(int32_t x, int32_t y) {
        // Mouse coords come in screen space
        // But leave in pixel space
        bHasMouseFocus = true;
        vMouseWindowPos = { x, y };
        // Full Screen mode may have a weird viewport we must clamp to
        x -= vViewPos.x;
        y -= vViewPos.y;
        vMousePosCache.x = (int32_t)(((float)x / (float)(vWindowSize.x - (vViewPos.x * 2)) * (float)vScreenSize.x));
        vMousePosCache.y = (int32_t)(((float)y / (float)(vWindowSize.y - (vViewPos.y * 2)) * (float)vScreenSize.y));
        if (vMousePosCache.x >= (int32_t)vScreenSize.x) vMousePosCache.x = vScreenSize.x - 1;
        if (vMousePosCache.y >= (int32_t)vScreenSize.y) vMousePosCache.y = vScreenSize.y - 1;
        if (vMousePosCache.x < 0) vMousePosCache.x = 0;
        if (vMousePosCache.y < 0) vMousePosCache.y = 0;
    }
    
    void PixelGameEngine::olc_UpdateMouseState(int32_t button, bool state) { pMouseNewState[button] = state; }
    
    void PixelGameEngine::olc_UpdateKeyState(int32_t key, bool state) { pKeyNewState[key] = state; }
    
    void PixelGameEngine::olc_UpdateMouseFocus(bool state) { bHasMouseFocus = state; }
    
    void PixelGameEngine::olc_UpdateKeyFocus(bool state) { bHasInputFocus = state; }
    
    void PixelGameEngine::olc_Terminate() { bAtomActive = false; }
    
    void PixelGameEngine::EngineThread() {
        // Allow platform to do stuff here if needed, since its now in the
        // context of this thread
        if (platform->ThreadStartUp() == olc::FAIL) return;
        
        // Do engine context specific initialisation
        olc_PrepareEngine();
        
        // Create user resources as part of this thread
        if (!OnUserCreate()) bAtomActive = false;
        
        while (bAtomActive) {
            // Run as fast as possible
            while (bAtomActive) { olc_CoreUpdate(); }
            
            // Allow the user to free resources if they have overrided the destroy function
            if (!OnUserDestroy()) {
                // User denied destroy for some reason, so continue running
                bAtomActive = true;
            }
        }
        
        platform->ThreadCleanUp();
    }
    
    void PixelGameEngine::olc_PrepareEngine() {
        // Start OpenGL, the context is owned by the game thread
        if (platform->CreateGraphics(bFullScreen, bEnableVSYNC, vViewPos, vViewSize) == olc::FAIL) return;
        
        
        // Create Primary window "0"
        pDrawTarget = new olc::Sprite(vScreenSize.x, vScreenSize.y);
        nResID = renderer->CreateTexture(vScreenSize.x, vScreenSize.y);
        renderer->UpdateTexture(nResID, pDrawTarget);
        
        
        
        m_tp1 = std::chrono::system_clock::now();
        m_tp2 = std::chrono::system_clock::now();
    }
    
    
    void PixelGameEngine::olc_CoreUpdate() {
        // Handle Timing
        m_tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = m_tp2 - m_tp1;
        m_tp1 = m_tp2;
        
        // Our time per frame coefficient
        float fElapsedTime = elapsedTime.count();
        fLastElapsed = fElapsedTime;
        
        // Some platforms will need to check for events
        platform->HandleSystemEvent();
        
        // Compare hardware input states from previous frame
        auto ScanHardware = [&](HWButton* pKeys, bool* pStateOld, bool* pStateNew, uint32_t nKeyCount) {
            for (uint32_t i = 0; i < nKeyCount; i++) {
                pKeys[i].bPressed = false;
                pKeys[i].bReleased = false;
                if (pStateNew[i] != pStateOld[i]) {
                    if (pStateNew[i]) {
                        pKeys[i].bPressed = !pKeys[i].bHeld;
                        pKeys[i].bHeld = true;
                    } else {
                        pKeys[i].bReleased = true;
                        pKeys[i].bHeld = false;
                    }
                }
                pStateOld[i] = pStateNew[i];
            }
        };
        
        ScanHardware(pKeyboardState, pKeyOldState, pKeyNewState, 256);
        ScanHardware(pMouseState, pMouseOldState, pMouseNewState, nMouseButtons);
        
        // Cache mouse coordinates so they remain consistent during frame
        vMousePos = vMousePosCache;
        nMouseWheelDelta = nMouseWheelDeltaCache;
        nMouseWheelDeltaCache = 0;
        
        //  renderer->ClearBuffer(olc::BLACK, true);
        
        // Handle Frame Update
        if (!OnUserUpdate(fElapsedTime))
            bAtomActive = false;
        
        // Display Frame
        renderer->UpdateViewport(vViewPos, vViewSize);
        renderer->ClearBuffer(olc::BLACK, true);
        
        renderer->PrepareDrawing();
        
        if (funcHook == nullptr) {
            renderer->ApplyTexture(nResID);
            renderer->UpdateTexture(nResID, pDrawTarget);
            
            renderer->DrawWindowQuad(vOffset, vScale, tint);
            
        } else {
            // Mwa ha ha.... Have Fun!!!
            funcHook();
        }
        
        // Present Graphics to screen
        renderer->DisplayFrame();
        
        // Update Title Bar
        fFrameTimer += fElapsedTime;
        nFrameCount++;
        if (fFrameTimer >= 1.0f) {
            nLastFPS = nFrameCount;
            fFrameTimer -= 1.0f;
            std::string sTitle = "OneLoneCoder.com - Pixel Game Engine - " + sAppName + " - FPS: " + std::to_string(nFrameCount);
            platform->SetWindowTitle(sTitle);
            nFrameCount = 0;
        }
    }
    
    // Need a couple of statics as these are singleton instances
    // read from multiple locations
    std::atomic<bool> PixelGameEngine::bAtomActive{ false };
    olc::PixelGameEngine* olc::Platform::ptrPGE = nullptr;
    olc::PixelGameEngine* olc::Renderer::ptrPGE = nullptr;
};

















// MARK: KEEP
// +------------------------------------------------------------------------------+
// | olcPixelGameEngine PLATFORM SPECIFIC IMPLEMENTATIONS                         |
// +------------------------------------------------------------------------------+

// MARK: Renderer OpenGL 1.0
// +------------------------------------------------------------------------------+
// | START RENDERER: OpenGL 1.0 (the original, the best...)                       |
// +------------------------------------------------------------------------------+
#if defined(OLC_GFX_OPENGL10)
#if defined(_WIN32)
#include <windows.h>
#include <dwmapi.h>
#include <GL/gl.h>
#pragma comment(lib, "Dwmapi.lib")
typedef BOOL(WINAPI wglSwapInterval_t) (int interval);
static wglSwapInterval_t* wglSwapInterval = nullptr;
typedef HDC glDeviceContext_t;
typedef HGLRC glRenderContext_t;
#endif

#if defined(__linux__) || defined(__FreeBSD__)
#include <GL/gl.h>
namespace X11 {
    #include <GL/glx.h>
    #include <X11/X.h>
    #include <X11/Xlib.h>
}

typedef int(glSwapInterval_t)(X11::Display* dpy, X11::GLXDrawable drawable, int interval);
static glSwapInterval_t* glSwapIntervalEXT;
typedef X11::GLXContext glDeviceContext_t;
typedef X11::GLXContext glRenderContext_t;
#endif

#if defined(__APPLE__)
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

namespace olc {
    class Renderer_OGL10 : public olc::Renderer {
    private:
#if defined(__APPLE__)
        bool mFullScreen = false;
#else
        glDeviceContext_t glDeviceContext = 0;
        glRenderContext_t glRenderContext = 0;
#endif
        
        bool bSync = false;
        
#if defined(__linux__) || defined(__FreeBSD__)
        X11::Display* olc_Display = nullptr;
        X11::Window* olc_Window = nullptr;
        X11::XVisualInfo* olc_VisualInfo = nullptr;
#endif
        
    public:
        void PrepareDevice() override {
#if defined(__APPLE__)
            //glutInit has to be called with main() arguments, make fake ones
            int argc = 0;
            char* argv[1] = { (char*)"" };
            glutInit(&argc, argv);
            
            glutInitWindowPosition(0, 0);
            glutInitWindowSize(512, 512);
            
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
            
            // Creates the window and the OpenGL context for it
            glutCreateWindow("OneLoneCoder.com - Pixel Game Engine");
            
            glEnable(GL_TEXTURE_2D); // Turn on texturing
            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
#endif
        }
        
        olc::rcode CreateDevice(std::vector<void*> params, bool bFullScreen, bool bVSYNC) override {
#if defined(_WIN32)
            // Create Device Context
            glDeviceContext = GetDC((HWND)(params[0]));
            PIXELFORMATDESCRIPTOR pfd =
            {
                sizeof(PIXELFORMATDESCRIPTOR), 1,
                PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                PFD_MAIN_PLANE, 0, 0, 0, 0
            };
            
            int pf = 0;
            if (!(pf = ChoosePixelFormat(glDeviceContext, &pfd))) return olc::FAIL;
            SetPixelFormat(glDeviceContext, pf, &pfd);
            
            if (!(glRenderContext = wglCreateContext(glDeviceContext))) return olc::FAIL;
            wglMakeCurrent(glDeviceContext, glRenderContext);
            
            // Remove Frame cap
            wglSwapInterval = (wglSwapInterval_t*)wglGetProcAddress("wglSwapIntervalEXT");
            if (wglSwapInterval && !bVSYNC) wglSwapInterval(0);
            bSync = bVSYNC;
#endif
            
#if defined(__linux__) || defined(__FreeBSD__)
            using namespace X11;
            // Linux has tighter coupling between OpenGL and X11, so we store
            // various "platform" handles in the renderer
            olc_Display = (X11::Display*)(params[0]);
            olc_Window = (X11::Window*)(params[1]);
            olc_VisualInfo = (X11::XVisualInfo*)(params[2]);
            
            glDeviceContext = glXCreateContext(olc_Display, olc_VisualInfo, nullptr, GL_TRUE);
            glXMakeCurrent(olc_Display, *olc_Window, glDeviceContext);
            
            XWindowAttributes gwa;
            XGetWindowAttributes(olc_Display, *olc_Window, &gwa);
            glViewport(0, 0, gwa.width, gwa.height);
            
            glSwapIntervalEXT = nullptr;
            glSwapIntervalEXT = (glSwapInterval_t*)glXGetProcAddress((unsigned char*)"glXSwapIntervalEXT");
            
            if (glSwapIntervalEXT == nullptr && !bVSYNC)
            {
                printf("NOTE: Could not disable VSYNC, glXSwapIntervalEXT() was not found!\n");
                printf("      Don't worry though, things will still work, it's just the\n");
                printf("      frame rate will be capped to your monitors refresh rate - javidx9\n");
            }
            
            if (glSwapIntervalEXT != nullptr && !bVSYNC)
                glSwapIntervalEXT(olc_Display, *olc_Window, 0);
#endif
            
#if defined(__APPLE__)
            mFullScreen = bFullScreen;
            if (!bVSYNC)
            {
                GLint sync = 0;
                CGLContextObj ctx = CGLGetCurrentContext();
                if (ctx) CGLSetParameter(ctx, kCGLCPSwapInterval, &sync);
            }
#else
            glEnable(GL_TEXTURE_2D); // Turn on texturing
            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
#endif
            return olc::rcode::OK;
        }
        
        olc::rcode DestroyDevice() override {
#if defined(_WIN32)
            wglDeleteContext(glRenderContext);
#endif
            
#if defined(__linux__) || defined(__FreeBSD__)
            glXMakeCurrent(olc_Display, None, NULL);
            glXDestroyContext(olc_Display, glDeviceContext);
#endif
            
#if defined(__APPLE__)
            glutDestroyWindow(glutGetWindow());
#endif
            return olc::rcode::OK;
        }
        
        void DisplayFrame() override {
#if defined(_WIN32)
            SwapBuffers(glDeviceContext);
            if (bSync) DwmFlush(); // Woooohooooooo!!!! SMOOOOOOOTH!
#endif
            
#if defined(__linux__) || defined(__FreeBSD__)
            X11::glXSwapBuffers(olc_Display, *olc_Window);
#endif
            
#if defined(__APPLE__)
            glutSwapBuffers();
#endif
        }
        
        void PrepareDrawing() override {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        
        void DrawWindowQuad(const olc::vf2d& offset, const olc::vf2d& scale, const olc::Pixel tint) override {
            glBegin(GL_QUADS);
            glColor4ub(tint.r, tint.g, tint.b, tint.a);
            glTexCoord2f(0.0f * scale.x + offset.x, 1.0f * scale.y + offset.y);
            glVertex3f(-1.0f /*+ vSubPixelOffset.x*/, -1.0f /*+ vSubPixelOffset.y*/, 0.0f);
            glTexCoord2f(0.0f * scale.x + offset.x, 0.0f * scale.y + offset.y);
            glVertex3f(-1.0f /*+ vSubPixelOffset.x*/, 1.0f /*+ vSubPixelOffset.y*/, 0.0f);
            glTexCoord2f(1.0f * scale.x + offset.x, 0.0f * scale.y + offset.y);
            glVertex3f(1.0f /*+ vSubPixelOffset.x*/, 1.0f /*+ vSubPixelOffset.y*/, 0.0f);
            glTexCoord2f(1.0f * scale.x + offset.x, 1.0f * scale.y + offset.y);
            glVertex3f(1.0f /*+ vSubPixelOffset.x*/, -1.0f /*+ vSubPixelOffset.y*/, 0.0f);
            glEnd();
        }
        
//        void DrawDecalQuad(const olc::DecalInstance& decal) override {
//            if (decal.decal == nullptr) {
//                glBindTexture(GL_TEXTURE_2D, 0);
//                glBegin(GL_QUADS);
//                glColor4ub(decal.tint[0].r, decal.tint[0].g, decal.tint[0].b, decal.tint[0].a);
//                glTexCoord4f(decal.uv[0].x, decal.uv[0].y, 0.0f, decal.w[0]); glVertex2f(decal.pos[0].x, decal.pos[0].y);
//                glColor4ub(decal.tint[1].r, decal.tint[1].g, decal.tint[1].b, decal.tint[1].a);
//                glTexCoord4f(decal.uv[1].x, decal.uv[1].y, 0.0f, decal.w[1]); glVertex2f(decal.pos[1].x, decal.pos[1].y);
//                glColor4ub(decal.tint[2].r, decal.tint[2].g, decal.tint[2].b, decal.tint[2].a);
//                glTexCoord4f(decal.uv[2].x, decal.uv[2].y, 0.0f, decal.w[2]); glVertex2f(decal.pos[2].x, decal.pos[2].y);
//                glColor4ub(decal.tint[3].r, decal.tint[3].g, decal.tint[3].b, decal.tint[3].a);
//                glTexCoord4f(decal.uv[3].x, decal.uv[3].y, 0.0f, decal.w[3]); glVertex2f(decal.pos[3].x, decal.pos[3].y);
//                glEnd();
//            } else {
//                glBindTexture(GL_TEXTURE_2D, decal.decal->id);
//                glBegin(GL_QUADS);
//                glColor4ub(decal.tint[0].r, decal.tint[0].g, decal.tint[0].b, decal.tint[0].a);
//                glTexCoord4f(decal.uv[0].x, decal.uv[0].y, 0.0f, decal.w[0]); glVertex2f(decal.pos[0].x, decal.pos[0].y);
//                glTexCoord4f(decal.uv[1].x, decal.uv[1].y, 0.0f, decal.w[1]); glVertex2f(decal.pos[1].x, decal.pos[1].y);
//                glTexCoord4f(decal.uv[2].x, decal.uv[2].y, 0.0f, decal.w[2]); glVertex2f(decal.pos[2].x, decal.pos[2].y);
//                glTexCoord4f(decal.uv[3].x, decal.uv[3].y, 0.0f, decal.w[3]); glVertex2f(decal.pos[3].x, decal.pos[3].y);
//                glEnd();
//            }
//        }
        
        uint32_t CreateTexture(const uint32_t width, const uint32_t height) override {
            UNUSED(width);
            UNUSED(height);
            uint32_t id = 0;
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            return id;
        }
        
        uint32_t DeleteTexture(const uint32_t id) override {
            glDeleteTextures(1, &id);
            return id;
        }
        
        void UpdateTexture(uint32_t id, olc::Sprite* spr) override {
            UNUSED(id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spr->width, spr->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, spr->GetData());
        }
        
        void ApplyTexture(uint32_t id) override {
            glBindTexture(GL_TEXTURE_2D, id);
        }
        
        void ClearBuffer(olc::Pixel p, bool bDepth) override {
            glClearColor(float(p.r) / 255.0f, float(p.g) / 255.0f, float(p.b) / 255.0f, float(p.a) / 255.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            if (bDepth) glClear(GL_DEPTH_BUFFER_BIT);
        }
        
        void UpdateViewport(const olc::vi2d& pos, const olc::vi2d& size) override {
#if defined(__APPLE__)
            if (!mFullScreen) glutReshapeWindow(size.x, size.y);
#else
            glViewport(pos.x, pos.y, size.x, size.y);
#endif
        }
    };
}
#endif
// +------------------------------------------------------------------------------+
// | END RENDERER: OpenGL 1.0 (the original, the best...)                         |
// +------------------------------------------------------------------------------+

// MARK: WINDOWS
// +------------------------------------------------------------------------------+
// | START PLATFORM: MICROSOFT WINDOWS XP, VISTA, 7, 8, 10                        |
// +------------------------------------------------------------------------------+
#if defined(_WIN32)
#if !defined(__MINGW32__)
#pragma comment(lib, "user32.lib")    // Visual Studio Only
#pragma comment(lib, "gdi32.lib")   // For other Windows Compilers please add
#pragma comment(lib, "opengl32.lib")  // these libs to your linker input

#else
// In Code::Blocks
#if !defined(_WIN32_WINNT)
#ifdef HAVE_MSMF
#define _WIN32_WINNT 0x0600 // Windows Vista
#else
#define _WIN32_WINNT 0x0500 // Windows 2000
#endif
#endif
#endif

// Include WinAPI
#if !defined(__MINGW32__)
#define NOMINMAX
#endif
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace olc {
    class Platform_Windows : public olc::Platform {
    private:
        HWND olc_hWnd = nullptr;
        std::wstring wsAppName;
        
        std::wstring ConvertS2W(std::string s) {
#ifdef __MINGW32__
            wchar_t* buffer = new wchar_t[s.length() + 1];
            mbstowcs(buffer, s.c_str(), s.length());
            buffer[s.length()] = L'\0';
#else
            int count = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);
            wchar_t* buffer = new wchar_t[count];
            MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, buffer, count);
#endif
            std::wstring w(buffer);
            delete[] buffer;
            return w;
        }
        
    public:
        virtual olc::rcode ApplicationStartUp() override { return olc::rcode::OK; }
        virtual olc::rcode ApplicationCleanUp() override { return olc::rcode::OK; }
        virtual olc::rcode ThreadStartUp() override { return olc::rcode::OK; }
        
        virtual olc::rcode ThreadCleanUp() override {
            renderer->DestroyDevice();
            PostMessage(olc_hWnd, WM_DESTROY, 0, 0);
            return olc::OK;
        }
        
        virtual olc::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc::vi2d& vViewPos, const olc::vi2d& vViewSize) override {
            if (renderer->CreateDevice({ olc_hWnd }, bFullScreen, bEnableVSYNC) == olc::rcode::OK) {
                renderer->UpdateViewport(vViewPos, vViewSize);
                return olc::rcode::OK;
            } else {
                return olc::rcode::FAIL;
            }
        }
        
        virtual olc::rcode CreateWindowPane(const olc::vi2d& vWindowPos, olc::vi2d& vWindowSize, bool bFullScreen) override {
            WNDCLASS wc;
            wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
            wc.hInstance = GetModuleHandle(nullptr);
            wc.lpfnWndProc = olc_WindowEvent;
            wc.cbClsExtra = 0;
            wc.cbWndExtra = 0;
            wc.lpszMenuName = nullptr;
            wc.hbrBackground = nullptr;
            wc.lpszClassName = olcT("OLC_PIXEL_GAME_ENGINE");
            RegisterClass(&wc);
            
            // Define window furniture
            DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
            DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME;
            
            olc::vi2d vTopLeft = vWindowPos;
            
            // Handle Fullscreen
            if (bFullScreen) {
                dwExStyle = 0;
                dwStyle = WS_VISIBLE | WS_POPUP;
                HMONITOR hmon = MonitorFromWindow(olc_hWnd, MONITOR_DEFAULTTONEAREST);
                MONITORINFO mi = { sizeof(mi) };
                if (!GetMonitorInfo(hmon, &mi)) return olc::rcode::FAIL;
                vWindowSize = { mi.rcMonitor.right, mi.rcMonitor.bottom };
                vTopLeft.x = 0;
                vTopLeft.y = 0;
            }
            
            // Keep client size as requested
            RECT rWndRect = { 0, 0, vWindowSize.x, vWindowSize.y };
            AdjustWindowRectEx(&rWndRect, dwStyle, FALSE, dwExStyle);
            int width = rWndRect.right - rWndRect.left;
            int height = rWndRect.bottom - rWndRect.top;
            
            olc_hWnd = CreateWindowEx(dwExStyle, olcT("OLC_PIXEL_GAME_ENGINE"), olcT(""), dwStyle,
                                      vTopLeft.x, vTopLeft.y, width, height, NULL, NULL, GetModuleHandle(nullptr), this);
            
            // Create Keyboard Mapping
            mapKeys[0x00] = Key::NONE;
            mapKeys[0x41] = Key::A; mapKeys[0x42] = Key::B; mapKeys[0x43] = Key::C; mapKeys[0x44] = Key::D; mapKeys[0x45] = Key::E;
            mapKeys[0x46] = Key::F; mapKeys[0x47] = Key::G; mapKeys[0x48] = Key::H; mapKeys[0x49] = Key::I; mapKeys[0x4A] = Key::J;
            mapKeys[0x4B] = Key::K; mapKeys[0x4C] = Key::L; mapKeys[0x4D] = Key::M; mapKeys[0x4E] = Key::N; mapKeys[0x4F] = Key::O;
            mapKeys[0x50] = Key::P; mapKeys[0x51] = Key::Q; mapKeys[0x52] = Key::R; mapKeys[0x53] = Key::S; mapKeys[0x54] = Key::T;
            mapKeys[0x55] = Key::U; mapKeys[0x56] = Key::V; mapKeys[0x57] = Key::W; mapKeys[0x58] = Key::X; mapKeys[0x59] = Key::Y;
            mapKeys[0x5A] = Key::Z;
            
            mapKeys[VK_F1] = Key::F1; mapKeys[VK_F2] = Key::F2; mapKeys[VK_F3] = Key::F3; mapKeys[VK_F4] = Key::F4;
            mapKeys[VK_F5] = Key::F5; mapKeys[VK_F6] = Key::F6; mapKeys[VK_F7] = Key::F7; mapKeys[VK_F8] = Key::F8;
            mapKeys[VK_F9] = Key::F9; mapKeys[VK_F10] = Key::F10; mapKeys[VK_F11] = Key::F11; mapKeys[VK_F12] = Key::F12;
            
            mapKeys[VK_DOWN] = Key::DOWN; mapKeys[VK_LEFT] = Key::LEFT; mapKeys[VK_RIGHT] = Key::RIGHT; mapKeys[VK_UP] = Key::UP;
            mapKeys[VK_RETURN] = Key::ENTER; //mapKeys[VK_RETURN] = Key::RETURN;
            
            mapKeys[VK_BACK] = Key::BACK; mapKeys[VK_ESCAPE] = Key::ESCAPE; mapKeys[VK_RETURN] = Key::ENTER; mapKeys[VK_PAUSE] = Key::PAUSE;
            mapKeys[VK_SCROLL] = Key::SCROLL; mapKeys[VK_TAB] = Key::TAB; mapKeys[VK_DELETE] = Key::DEL; mapKeys[VK_HOME] = Key::HOME;
            mapKeys[VK_END] = Key::END; mapKeys[VK_PRIOR] = Key::PGUP; mapKeys[VK_NEXT] = Key::PGDN; mapKeys[VK_INSERT] = Key::INS;
            mapKeys[VK_SHIFT] = Key::SHIFT; mapKeys[VK_CONTROL] = Key::CTRL;
            mapKeys[VK_SPACE] = Key::SPACE;
            
            mapKeys[0x30] = Key::K0; mapKeys[0x31] = Key::K1; mapKeys[0x32] = Key::K2; mapKeys[0x33] = Key::K3; mapKeys[0x34] = Key::K4;
            mapKeys[0x35] = Key::K5; mapKeys[0x36] = Key::K6; mapKeys[0x37] = Key::K7; mapKeys[0x38] = Key::K8; mapKeys[0x39] = Key::K9;
            
            mapKeys[VK_NUMPAD0] = Key::NP0; mapKeys[VK_NUMPAD1] = Key::NP1; mapKeys[VK_NUMPAD2] = Key::NP2; mapKeys[VK_NUMPAD3] = Key::NP3; mapKeys[VK_NUMPAD4] = Key::NP4;
            mapKeys[VK_NUMPAD5] = Key::NP5; mapKeys[VK_NUMPAD6] = Key::NP6; mapKeys[VK_NUMPAD7] = Key::NP7; mapKeys[VK_NUMPAD8] = Key::NP8; mapKeys[VK_NUMPAD9] = Key::NP9;
            mapKeys[VK_MULTIPLY] = Key::NP_MUL; mapKeys[VK_ADD] = Key::NP_ADD; mapKeys[VK_DIVIDE] = Key::NP_DIV; mapKeys[VK_SUBTRACT] = Key::NP_SUB; mapKeys[VK_DECIMAL] = Key::NP_DECIMAL;
            return olc::OK;
        }
        
        virtual olc::rcode SetWindowTitle(const std::string& s) override {
#ifdef UNICODE
            SetWindowText(olc_hWnd, ConvertS2W(s).c_str());
#else
            SetWindowText(olc_hWnd, s.c_str());
#endif
            return olc::OK;
        }
        
        virtual olc::rcode StartSystemEventLoop() override {
            MSG msg;
            while (GetMessage(&msg, NULL, 0, 0) > 0) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            return olc::OK;
        }
        
        virtual olc::rcode HandleSystemEvent() override { return olc::rcode::FAIL; }
        
        // Windows Event Handler - this is statically connected to the windows event system
        static LRESULT CALLBACK olc_WindowEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
            switch (uMsg) {
                case WM_MOUSEMOVE: {
                    // Thanks @ForAbby (Discord)
                    uint16_t x = lParam & 0xFFFF; uint16_t y = (lParam >> 16) & 0xFFFF;
                    int16_t ix = *(int16_t*)&x;   int16_t iy = *(int16_t*)&y;
                    ptrPGE->olc_UpdateMouse(ix, iy);
                    return 0;
                }
                case WM_SIZE:       ptrPGE->olc_UpdateWindowSize(lParam & 0xFFFF, (lParam >> 16) & 0xFFFF); return 0;
                case WM_MOUSEWHEEL: ptrPGE->olc_UpdateMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));           return 0;
                case WM_MOUSELEAVE: ptrPGE->olc_UpdateMouseFocus(false);                                    return 0;
                case WM_SETFOCUS: ptrPGE->olc_UpdateKeyFocus(true);                                       return 0;
                case WM_KILLFOCUS:  ptrPGE->olc_UpdateKeyFocus(false);                                      return 0;
                case WM_KEYDOWN:  ptrPGE->olc_UpdateKeyState(mapKeys[wParam], true);                      return 0;
                case WM_KEYUP:    ptrPGE->olc_UpdateKeyState(mapKeys[wParam], false);                     return 0;
                case WM_LBUTTONDOWN:ptrPGE->olc_UpdateMouseState(0, true);                                  return 0;
                case WM_LBUTTONUP:  ptrPGE->olc_UpdateMouseState(0, false);                                 return 0;
                case WM_RBUTTONDOWN:ptrPGE->olc_UpdateMouseState(1, true);                                  return 0;
                case WM_RBUTTONUP:  ptrPGE->olc_UpdateMouseState(1, false);                                 return 0;
                case WM_MBUTTONDOWN:ptrPGE->olc_UpdateMouseState(2, true);                                  return 0;
                case WM_MBUTTONUP:  ptrPGE->olc_UpdateMouseState(2, false);                                 return 0;
                case WM_CLOSE:    ptrPGE->olc_Terminate();                                                return 0;
                case WM_DESTROY:  PostQuitMessage(0); DestroyWindow(hWnd);                return 0;
            }
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    };
}
#endif
// +------------------------------------------------------------------------------+
// | END PLATFORM: MICROSOFT WINDOWS XP, VISTA, 7, 8, 10                          |
// +------------------------------------------------------------------------------+




// MARK: LINUX
// +------------------------------------------------------------------------------+
// | START PLATFORM: LINUX                                                        |
// +------------------------------------------------------------------------------+
#if defined(__linux__) || defined(__FreeBSD__)
namespace olc {
    class Platform_Linux : public olc::Platform {
    private:
        X11::Display* olc_Display = nullptr;
        X11::Window          olc_WindowRoot;
        X11::Window          olc_Window;
        X11::XVisualInfo* olc_VisualInfo;
        X11::Colormap                olc_ColourMap;
        X11::XSetWindowAttributes    olc_SetWindowAttribs;
        
    public:
        virtual olc::rcode ApplicationStartUp() override { return olc::rcode::OK; }
        
        virtual olc::rcode ApplicationCleanUp() override { return olc::rcode::OK; }
        
        virtual olc::rcode ThreadStartUp() override { return olc::rcode::OK; }
        
        virtual olc::rcode ThreadCleanUp() override {
            renderer->DestroyDevice();
            return olc::OK;
        }
        
        virtual olc::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc::vi2d& vViewPos, const olc::vi2d& vViewSize) override {
            if (renderer->CreateDevice({ olc_Display, &olc_Window, olc_VisualInfo }, bFullScreen, bEnableVSYNC) == olc::rcode::OK) {
                renderer->UpdateViewport(vViewPos, vViewSize);
                return olc::rcode::OK;
            } else {
                return olc::rcode::FAIL;
            }
        }
        
        virtual olc::rcode CreateWindowPane(const olc::vi2d& vWindowPos, olc::vi2d& vWindowSize, bool bFullScreen) override {
            using namespace X11;
            XInitThreads();
            
            // Grab the deafult display and window
            olc_Display = XOpenDisplay(NULL);
            olc_WindowRoot = DefaultRootWindow(olc_Display);
            
            // Based on the display capabilities, configure the appearance of the window
            GLint olc_GLAttribs[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
            olc_VisualInfo = glXChooseVisual(olc_Display, 0, olc_GLAttribs);
            olc_ColourMap = XCreateColormap(olc_Display, olc_WindowRoot, olc_VisualInfo->visual, AllocNone);
            olc_SetWindowAttribs.colormap = olc_ColourMap;
            
            // Register which events we are interested in receiving
            olc_SetWindowAttribs.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
            ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask | StructureNotifyMask;
            
            // Create the window
            olc_Window = XCreateWindow(olc_Display, olc_WindowRoot, vWindowPos.x, vWindowPos.y,
                                       vWindowSize.x, vWindowSize.y,
                                       0, olc_VisualInfo->depth, InputOutput, olc_VisualInfo->visual,
                                       CWColormap | CWEventMask, &olc_SetWindowAttribs);
            
            Atom wmDelete = XInternAtom(olc_Display, "WM_DELETE_WINDOW", true);
            XSetWMProtocols(olc_Display, olc_Window, &wmDelete, 1);
            
            XMapWindow(olc_Display, olc_Window);
            XStoreName(olc_Display, olc_Window, "OneLoneCoder.com - Pixel Game Engine");
            
            if (bFullScreen) { // Thanks DragonEye, again :D
                Atom wm_state;
                Atom fullscreen;
                wm_state = XInternAtom(olc_Display, "_NET_WM_STATE", False);
                fullscreen = XInternAtom(olc_Display, "_NET_WM_STATE_FULLSCREEN", False);
                XEvent xev{ 0 };
                xev.type = ClientMessage;
                xev.xclient.window = olc_Window;
                xev.xclient.message_type = wm_state;
                xev.xclient.format = 32;
                xev.xclient.data.l[0] = (bFullScreen ? 1 : 0);   // the action (0: off, 1: on, 2: toggle)
                xev.xclient.data.l[1] = fullscreen;             // first property to alter
                xev.xclient.data.l[2] = 0;                      // second property to alter
                xev.xclient.data.l[3] = 0;                      // source indication
                XMapWindow(olc_Display, olc_Window);
                XSendEvent(olc_Display, DefaultRootWindow(olc_Display), False,
                           SubstructureRedirectMask | SubstructureNotifyMask, &xev);
                XFlush(olc_Display);
                XWindowAttributes gwa;
                XGetWindowAttributes(olc_Display, olc_Window, &gwa);
                vWindowSize.x = gwa.width;
                vWindowSize.y = gwa.height;
            }
            
            // Create Keyboard Mapping
            mapKeys[0x00] = Key::NONE;
            mapKeys[0x61] = Key::A; mapKeys[0x62] = Key::B; mapKeys[0x63] = Key::C; mapKeys[0x64] = Key::D; mapKeys[0x65] = Key::E;
            mapKeys[0x66] = Key::F; mapKeys[0x67] = Key::G; mapKeys[0x68] = Key::H; mapKeys[0x69] = Key::I; mapKeys[0x6A] = Key::J;
            mapKeys[0x6B] = Key::K; mapKeys[0x6C] = Key::L; mapKeys[0x6D] = Key::M; mapKeys[0x6E] = Key::N; mapKeys[0x6F] = Key::O;
            mapKeys[0x70] = Key::P; mapKeys[0x71] = Key::Q; mapKeys[0x72] = Key::R; mapKeys[0x73] = Key::S; mapKeys[0x74] = Key::T;
            mapKeys[0x75] = Key::U; mapKeys[0x76] = Key::V; mapKeys[0x77] = Key::W; mapKeys[0x78] = Key::X; mapKeys[0x79] = Key::Y;
            mapKeys[0x7A] = Key::Z;
            
            mapKeys[XK_F1] = Key::F1; mapKeys[XK_F2] = Key::F2; mapKeys[XK_F3] = Key::F3; mapKeys[XK_F4] = Key::F4;
            mapKeys[XK_F5] = Key::F5; mapKeys[XK_F6] = Key::F6; mapKeys[XK_F7] = Key::F7; mapKeys[XK_F8] = Key::F8;
            mapKeys[XK_F9] = Key::F9; mapKeys[XK_F10] = Key::F10; mapKeys[XK_F11] = Key::F11; mapKeys[XK_F12] = Key::F12;
            
            mapKeys[XK_Down] = Key::DOWN; mapKeys[XK_Left] = Key::LEFT; mapKeys[XK_Right] = Key::RIGHT; mapKeys[XK_Up] = Key::UP;
            mapKeys[XK_KP_Enter] = Key::ENTER; mapKeys[XK_Return] = Key::ENTER;
            
            mapKeys[XK_BackSpace] = Key::BACK; mapKeys[XK_Escape] = Key::ESCAPE; mapKeys[XK_Linefeed] = Key::ENTER; mapKeys[XK_Pause] = Key::PAUSE;
            mapKeys[XK_Scroll_Lock] = Key::SCROLL; mapKeys[XK_Tab] = Key::TAB; mapKeys[XK_Delete] = Key::DEL; mapKeys[XK_Home] = Key::HOME;
            mapKeys[XK_End] = Key::END; mapKeys[XK_Page_Up] = Key::PGUP; mapKeys[XK_Page_Down] = Key::PGDN; mapKeys[XK_Insert] = Key::INS;
            mapKeys[XK_Shift_L] = Key::SHIFT; mapKeys[XK_Shift_R] = Key::SHIFT; mapKeys[XK_Control_L] = Key::CTRL; mapKeys[XK_Control_R] = Key::CTRL;
            mapKeys[XK_space] = Key::SPACE; mapKeys[XK_period] = Key::PERIOD;
            
            mapKeys[XK_0] = Key::K0; mapKeys[XK_1] = Key::K1; mapKeys[XK_2] = Key::K2; mapKeys[XK_3] = Key::K3; mapKeys[XK_4] = Key::K4;
            mapKeys[XK_5] = Key::K5; mapKeys[XK_6] = Key::K6; mapKeys[XK_7] = Key::K7; mapKeys[XK_8] = Key::K8; mapKeys[XK_9] = Key::K9;
            
            mapKeys[XK_KP_0] = Key::NP0; mapKeys[XK_KP_1] = Key::NP1; mapKeys[XK_KP_2] = Key::NP2; mapKeys[XK_KP_3] = Key::NP3; mapKeys[XK_KP_4] = Key::NP4;
            mapKeys[XK_KP_5] = Key::NP5; mapKeys[XK_KP_6] = Key::NP6; mapKeys[XK_KP_7] = Key::NP7; mapKeys[XK_KP_8] = Key::NP8; mapKeys[XK_KP_9] = Key::NP9;
            mapKeys[XK_KP_Multiply] = Key::NP_MUL; mapKeys[XK_KP_Add] = Key::NP_ADD; mapKeys[XK_KP_Divide] = Key::NP_DIV; mapKeys[XK_KP_Subtract] = Key::NP_SUB; mapKeys[XK_KP_Decimal] = Key::NP_DECIMAL;
            
            return olc::OK;
        }
        
        virtual olc::rcode SetWindowTitle(const std::string& s) override {
            X11::XStoreName(olc_Display, olc_Window, s.c_str());
            return olc::OK;
        }
        
        virtual olc::rcode StartSystemEventLoop() override { return olc::OK; }
        
        virtual olc::rcode HandleSystemEvent() override {
            using namespace X11;
            // Handle Xlib Message Loop - we do this in the
            // same thread that OpenGL was created so we dont
            // need to worry too much about multithreading with X11
            XEvent xev;
            while (XPending(olc_Display)) {
                XNextEvent(olc_Display, &xev);
                if (xev.type == Expose) {
                    XWindowAttributes gwa;
                    XGetWindowAttributes(olc_Display, olc_Window, &gwa);
                    ptrPGE->olc_UpdateWindowSize(gwa.width, gwa.height);
                } else if (xev.type == ConfigureNotify) {
                    XConfigureEvent xce = xev.xconfigure;
                    ptrPGE->olc_UpdateWindowSize(xce.width, xce.height);
                } else if (xev.type == KeyPress) {
                    KeySym sym = XLookupKeysym(&xev.xkey, 0);
                    ptrPGE->olc_UpdateKeyState(mapKeys[sym], true);
                    XKeyEvent* e = (XKeyEvent*)&xev; // Because DragonEye loves numpads
                    XLookupString(e, NULL, 0, &sym, NULL);
                    ptrPGE->olc_UpdateKeyState(mapKeys[sym], true);
                } else if (xev.type == KeyRelease) {
                    KeySym sym = XLookupKeysym(&xev.xkey, 0);
                    ptrPGE->olc_UpdateKeyState(mapKeys[sym], false);
                    XKeyEvent* e = (XKeyEvent*)&xev;
                    XLookupString(e, NULL, 0, &sym, NULL);
                    ptrPGE->olc_UpdateKeyState(mapKeys[sym], false);
                } else if (xev.type == ButtonPress) {
                    switch (xev.xbutton.button) {
                        case 1: ptrPGE->olc_UpdateMouseState(0, true); break;
                        case 2: ptrPGE->olc_UpdateMouseState(2, true); break;
                        case 3: ptrPGE->olc_UpdateMouseState(1, true); break;
                        case 4: ptrPGE->olc_UpdateMouseWheel(120); break;
                        case 5: ptrPGE->olc_UpdateMouseWheel(-120); break;
                        default: break;
                    }
                } else if (xev.type == ButtonRelease) {
                    switch (xev.xbutton.button) {
                        case 1: ptrPGE->olc_UpdateMouseState(0, false); break;
                        case 2: ptrPGE->olc_UpdateMouseState(2, false); break;
                        case 3: ptrPGE->olc_UpdateMouseState(1, false); break;
                        default: break;
                    }
                } else if (xev.type == MotionNotify) {
                    ptrPGE->olc_UpdateMouse(xev.xmotion.x, xev.xmotion.y);
                } else if (xev.type == FocusIn) {
                    ptrPGE->olc_UpdateKeyFocus(true);
                } else if (xev.type == FocusOut) {
                    ptrPGE->olc_UpdateKeyFocus(false);
                } else if (xev.type == ClientMessage) {
                    ptrPGE->olc_Terminate();
                }
            }
            return olc::OK;
        }
    };
}
#endif
// +------------------------------------------------------------------------------+
// | END PLATFORM: LINUX                                                          |
// +------------------------------------------------------------------------------+




// MARK: MAC
// +------------------------------------------------------------------------------+
// | START PLATFORM: GLUT (used to make it simple for Apple)                      |
// +------------------------------------------------------------------------------+
//
#if defined(__APPLE__)
namespace olc {
    
    class Platform_GLUT : public olc::Platform {
    public:
        static std::atomic<bool>* bActiveRef;
        
        virtual olc::rcode ApplicationStartUp() override {
            return olc::rcode::OK;
        }
        
        virtual olc::rcode ApplicationCleanUp() override {
            return olc::rcode::OK;
        }
        
        virtual olc::rcode ThreadStartUp() override {
            return olc::rcode::OK;
        }
        
        virtual olc::rcode ThreadCleanUp() override {
            renderer->DestroyDevice();
            return olc::OK;
        }
        
        virtual olc::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc::vi2d& vViewPos, const olc::vi2d& vViewSize) override {
            if (renderer->CreateDevice({}, bFullScreen, bEnableVSYNC) == olc::rcode::OK) {
                renderer->UpdateViewport(vViewPos, vViewSize);
                return olc::rcode::OK;
            } else {
                return olc::rcode::FAIL;
            }
        }
        
        static void ExitMainLoop() {
            if (!ptrPGE->OnUserDestroy()) {
                *bActiveRef = true;
                return;
            }
            platform->ThreadCleanUp();
            platform->ApplicationCleanUp();
            exit(0);
        }
        
        static void ThreadFunct() {
            if (!*bActiveRef) {
                ExitMainLoop();
                return;
            }
            glutPostRedisplay();
        }
        
        static void DrawFunct() {
            ptrPGE->olc_CoreUpdate();
        }
        
        virtual olc::rcode CreateWindowPane(const olc::vi2d& vWindowPos, olc::vi2d& vWindowSize, bool bFullScreen) override {
            renderer->PrepareDevice();
            
            
            if (bFullScreen) {
                vWindowSize.x = glutGet(GLUT_SCREEN_WIDTH);
                vWindowSize.y = glutGet(GLUT_SCREEN_HEIGHT);
                glutFullScreen();
            }
            
            if (vWindowSize.x > glutGet(GLUT_SCREEN_WIDTH) || vWindowSize.y > glutGet(GLUT_SCREEN_HEIGHT)) {
                perror("ERROR: The specified window dimensions do not fit on your screen\n");
                return olc::FAIL;
            }
            
            // Create Keyboard Mapping
            mapKeys[0x00] = Key::NONE;
            mapKeys['A'] = Key::A; mapKeys['B'] = Key::B; mapKeys['C'] = Key::C; mapKeys['D'] = Key::D; mapKeys['E'] = Key::E;
            mapKeys['F'] = Key::F; mapKeys['G'] = Key::G; mapKeys['H'] = Key::H; mapKeys['I'] = Key::I; mapKeys['J'] = Key::J;
            mapKeys['K'] = Key::K; mapKeys['L'] = Key::L; mapKeys['M'] = Key::M; mapKeys['N'] = Key::N; mapKeys['O'] = Key::O;
            mapKeys['P'] = Key::P; mapKeys['Q'] = Key::Q; mapKeys['R'] = Key::R; mapKeys['S'] = Key::S; mapKeys['T'] = Key::T;
            mapKeys['U'] = Key::U; mapKeys['V'] = Key::V; mapKeys['W'] = Key::W; mapKeys['X'] = Key::X; mapKeys['Y'] = Key::Y;
            mapKeys['Z'] = Key::Z;
            
            mapKeys[GLUT_KEY_F1] = Key::F1; mapKeys[GLUT_KEY_F2] = Key::F2; mapKeys[GLUT_KEY_F3] = Key::F3; mapKeys[GLUT_KEY_F4] = Key::F4;
            mapKeys[GLUT_KEY_F5] = Key::F5; mapKeys[GLUT_KEY_F6] = Key::F6; mapKeys[GLUT_KEY_F7] = Key::F7; mapKeys[GLUT_KEY_F8] = Key::F8;
            mapKeys[GLUT_KEY_F9] = Key::F9; mapKeys[GLUT_KEY_F10] = Key::F10; mapKeys[GLUT_KEY_F11] = Key::F11; mapKeys[GLUT_KEY_F12] = Key::F12;
            
            mapKeys[GLUT_KEY_DOWN] = Key::DOWN; mapKeys[GLUT_KEY_LEFT] = Key::LEFT; mapKeys[GLUT_KEY_RIGHT] = Key::RIGHT; mapKeys[GLUT_KEY_UP] = Key::UP;
            mapKeys[13] = Key::ENTER;
            
            mapKeys[127] = Key::BACK; mapKeys[27] = Key::ESCAPE;
            mapKeys[9] = Key::TAB;  mapKeys[GLUT_KEY_HOME] = Key::HOME;
            mapKeys[GLUT_KEY_END] = Key::END; mapKeys[GLUT_KEY_PAGE_UP] = Key::PGUP; mapKeys[GLUT_KEY_PAGE_DOWN] = Key::PGDN;    mapKeys[GLUT_KEY_INSERT] = Key::INS;
            mapKeys[32] = Key::SPACE; mapKeys[46] = Key::PERIOD;
            
            mapKeys[48] = Key::K0; mapKeys[49] = Key::K1; mapKeys[50] = Key::K2; mapKeys[51] = Key::K3; mapKeys[52] = Key::K4;
            mapKeys[53] = Key::K5; mapKeys[54] = Key::K6; mapKeys[55] = Key::K7; mapKeys[56] = Key::K8; mapKeys[57] = Key::K9;
            
            glutKeyboardFunc([](unsigned char key, int x, int y) -> void {
                switch (glutGetModifiers()) {
                    case 0: //This is when there are no modifiers
                        if ('a' <= key && key <= 'z') key -= 32;
                        break;
                    case GLUT_ACTIVE_SHIFT:
                        ptrPGE->olc_UpdateKeyState(Key::SHIFT, true);
                        break;
                    case GLUT_ACTIVE_CTRL:
                        if ('a' <= key && key <= 'z') key -= 32;
                        ptrPGE->olc_UpdateKeyState(Key::CTRL, true);
                        break;
                    case GLUT_ACTIVE_ALT:
                        if ('a' <= key && key <= 'z') key -= 32;
                        break;
                }
                
                if (mapKeys[key])
                    ptrPGE->olc_UpdateKeyState(mapKeys[key], true);
            });
            
            glutKeyboardUpFunc([](unsigned char key, int x, int y) -> void {
                switch (glutGetModifiers()) {
                    case 0: //This is when there are no modifiers
                        if ('a' <= key && key <= 'z') key -= 32;
                        break;
                    case GLUT_ACTIVE_SHIFT:
                        ptrPGE->olc_UpdateKeyState(Key::SHIFT, false);
                        break;
                    case GLUT_ACTIVE_CTRL:
                        if ('a' <= key && key <= 'z') key -= 32;
                        ptrPGE->olc_UpdateKeyState(Key::CTRL, false);
                        break;
                    case GLUT_ACTIVE_ALT:
                        if ('a' <= key && key <= 'z') key -= 32;
                        //No ALT in PGE
                        break;
                }
                
                if (mapKeys[key])
                    ptrPGE->olc_UpdateKeyState(mapKeys[key], false);
            });
            
            //Special keys
            glutSpecialFunc([](int key, int x, int y) -> void {
                if (mapKeys[key])
                    ptrPGE->olc_UpdateKeyState(mapKeys[key], true);
            });
            
            glutSpecialUpFunc([](int key, int x, int y) -> void {
                if (mapKeys[key])
                    ptrPGE->olc_UpdateKeyState(mapKeys[key], false);
            });
            
            glutMouseFunc([](int button, int state, int x, int y) -> void {
                switch (button) {
                    case GLUT_LEFT_BUTTON:
                        if (state == GLUT_UP) ptrPGE->olc_UpdateMouseState(0, false);
                        else if (state == GLUT_DOWN) ptrPGE->olc_UpdateMouseState(0, true);
                        break;
                    case GLUT_MIDDLE_BUTTON:
                        if (state == GLUT_UP) ptrPGE->olc_UpdateMouseState(2, false);
                        else if (state == GLUT_DOWN) ptrPGE->olc_UpdateMouseState(2, true);
                        break;
                    case GLUT_RIGHT_BUTTON:
                        if (state == GLUT_UP) ptrPGE->olc_UpdateMouseState(1, false);
                        else if (state == GLUT_DOWN) ptrPGE->olc_UpdateMouseState(1, true);
                        break;
                }
            });
            
            auto mouseMoveCall = [](int x, int y) -> void {
                ptrPGE->olc_UpdateMouse(x, y);
            };
            
            glutMotionFunc(mouseMoveCall);
            glutPassiveMotionFunc(mouseMoveCall);
            
            glutEntryFunc([](int state) -> void {
                if (state == GLUT_ENTERED) ptrPGE->olc_UpdateKeyFocus(true);
                else if (state == GLUT_LEFT) ptrPGE->olc_UpdateKeyFocus(false);
            });
            
            glutDisplayFunc(DrawFunct);
            glutIdleFunc(ThreadFunct);
            
            return olc::OK;
        }
        
        virtual olc::rcode SetWindowTitle(const std::string& s) override {
            glutSetWindowTitle(s.c_str());
            return olc::OK;
        }
        
        virtual olc::rcode StartSystemEventLoop() override {
            glutMainLoop();
            return olc::OK;
        }
        
        virtual olc::rcode HandleSystemEvent() override {
            return olc::OK;
        }
    };
    
    std::atomic<bool>* Platform_GLUT::bActiveRef{ nullptr };
    
    //Custom Start
    olc::rcode PixelGameEngine::Start() {
        if (platform->ApplicationStartUp() != olc::OK) return olc::FAIL;
        
        // Construct the window
        if (platform->CreateWindowPane({ 30,30 }, vWindowSize, bFullScreen) != olc::OK) return olc::FAIL;
        olc_UpdateWindowSize(vWindowSize.x, vWindowSize.y);
        
        
        if (platform->ThreadStartUp() == olc::FAIL)  return olc::FAIL;
        
        olc_PrepareEngine();
        
        if (!OnUserCreate()) return olc::FAIL;
        
        Platform_GLUT::bActiveRef = &bAtomActive;
        
        glutWMCloseFunc(Platform_GLUT::ExitMainLoop);
        
        bAtomActive = true;
        
        platform->StartSystemEventLoop();
        
        //This code will not even be run but why not
        if (platform->ApplicationCleanUp() != olc::OK) return olc::FAIL;
        
        return olc::OK;
    }
}

#endif
// +------------------------------------------------------------------------------+
// | END PLATFORM: GLUT                                                           |
// +------------------------------------------------------------------------------+



namespace olc {
    void PixelGameEngine::olc_ConfigureSystem() {
#if defined(_WIN32)
        platform = std::make_unique<olc::Platform_Windows>();
#endif
        
#if defined(__linux__) || defined(__FreeBSD__)
        platform = std::make_unique<olc::Platform_Linux>();
#endif
        
#if defined(__APPLE__)
        platform = std::make_unique<olc::Platform_GLUT>();
#endif
        
        
        
#if defined(OLC_GFX_OPENGL10)
        renderer = std::make_unique<olc::Renderer_OGL10>();
#endif
        
#if defined(OLC_GFX_OPENGL33)
        renderer = std::make_unique<olc::Renderer_OGL33>();
#endif
        
#if defined(OLC_GFX_DIRECTX10)
        renderer = std::make_unique<olc::Renderer_DX10>();
#endif
        
        // Associate components with PGE instance
        platform->ptrPGE = this;
        renderer->ptrPGE = this;
    }
}

#endif // End olc namespace

// +------------------------------------------------------------------------------+
// | END OF OLC_PGE_APPLICATION                                                   |
// +------------------------------------------------------------------------------+
