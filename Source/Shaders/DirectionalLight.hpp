#if defined( __cplusplus)
#   pragma once
#endif

#include "SharedTypes.hpp"

// Defines a directional light
struct DirectionalLight
{
    FLOAT4 DiffuseColor;
    FLOAT3 Direction;
};
