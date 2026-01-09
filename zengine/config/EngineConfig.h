#ifndef CONFIG_CONFIG_H_
#define CONFIG_CONFIG_H_

#include <string>
#include <cstdint>

#include "renderer/primitives/Point.h"
#include "renderer/primitives/Dimensions.h"

namespace EngineConfig {
const int32_t FRAME_RATE = 60;
const Dimensions MB_DIM = {950, 640};
const Dimensions TILE_DIM = {80, 80};
}

#endif /* CONFIG_CONFIG_H_ */
