#ifndef TITLESCREEN_HPP
#define TITLESCREEN_HPP

#include <raylib.h>

#include "../screens/BattlersChooserScreen.hpp"
#include "screenManager.hpp"

class TitleScreen : public Screen {
   private:
    Texture2D background;

   public:
    void Load() override;
    void Unload() override;
    void Update() override;
    void Draw() override;
};

#endif  // TITLESCREEN_HPP