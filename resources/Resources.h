#ifndef RESOURCES_RESOURCES_H_
#define RESOURCES_RESOURCES_H_

#include <filesystem>
#include <string_view>

namespace Resources {

inline std::filesystem::path resource(std::string_view path) {
    return std::filesystem::path("resources") / path;
}

namespace Chess {
    inline const auto board        = resource("chess/Chess-Board.png");
    inline const auto blackBishop  = resource("chess/Bishop_B.png");
    inline const auto blackKing    = resource("chess/King_B.png");
    inline const auto blackKnight  = resource("chess/Knight_B.png");
    inline const auto blackPawn    = resource("chess/Pawn_B.png");
    inline const auto blackQueen   = resource("chess/Queen_B.png");
    inline const auto blackRook    = resource("chess/Rook_B.png");
    inline const auto whiteBishop  = resource("chess/Bishop_W.png");
    inline const auto whiteKing    = resource("chess/King_W.png");
    inline const auto whiteKnight  = resource("chess/Knight_W.png");
    inline const auto whitePawn    = resource("chess/Pawn_W.png");
    inline const auto whiteQueen   = resource("chess/Queen_W.png");
    inline const auto whiteRook    = resource("chess/Rook_W.png");
    inline const auto startScreen2 = resource("chess/start_screen_2.png");
}

namespace Engine {
    inline const auto montserratFont = resource("engine/montserrat/Montserrat-Bold.ttf");
    inline const auto eye            = resource("engine/eye.png");
    inline const auto bg             = resource("engine/sunnyday.png");
    inline const auto human          = resource("engine/human.png");
    inline const auto balls          = resource("engine/balls.png");
    inline const auto windows        = resource("engine/windows.png");
    inline const auto sticky         = resource("engine/stickfigure.png");
    inline const auto arrow          = resource("engine/arrow.png");
}

namespace MapBuilder {
    inline const auto background = resource("mapbuilder/mbbg.jpg");
}

namespace TD {
    inline const auto background = resource("td/startbg.png");
    inline const auto grass      = resource("td/textures/grass.png");
}

namespace SkeletalRainOfBlood {
    inline const auto hero = resource("srb/hero.png");
}

namespace Breakout {
    inline const auto paddle = resource("breakout/paddle.png");
    inline const auto ball   = resource("breakout/ball.png");
}

}

#endif /* RESOURCES_RESOURCES_H_ */
