#pragma once

#include <vector>
#include <optional>

#ifdef NDEBUG
constexpr bool enable_validation_layers = false;
#define VALIDATION_LAYERS {};
#else
constexpr bool enable_validation_layers = false;
#define VALIDATION_LAYERS { \
    "VK_LAYER_KHRONOS_validation" \
    }
#endif
