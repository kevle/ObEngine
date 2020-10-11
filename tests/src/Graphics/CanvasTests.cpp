#include <Graphics/Canvas.hpp>
#include <Graphics/Sprite.hpp>

#include <type_traits>

// Compare canvas layer type with Sprite layer type
static_assert(std::is_same_v<decltype(obe::Graphics::Canvas::CanvasElement::layer),
                  decltype(obe::Graphics::Sprite::m_layer)>,
    "Inconsistent layer type.");