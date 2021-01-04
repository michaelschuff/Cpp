#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Example : public olc::PixelGameEngine {
    public:
        Example() {
            sAppName = "Example";
        }

    public:
        bool OnUserCreate() override {
            // Called once at the start, so create things here
            return true;
        }

        bool OnUserUpdate(float fElapsedTime) override {
            Clear(olc::BLACK);
            // called once per frame
            for (int x = 0; x < ScreenWidth(); x++) {
                for (int y = 0; y < ScreenHeight(); y++) {
                    Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));
                }
            }
            Draw(GetMouseX(), GetMouseY(), olc::Pixel(255, 255, 255));
            return true;
        }
};


int main(int argc, char const *argv[]) {
    Example demo;
    if (demo.Construct(1200, 900, 1, 1))
        demo.Start();

    return 0;
}
