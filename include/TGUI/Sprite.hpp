/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_SPRITE_HPP
#define TGUI_SPRITE_HPP

#include <TGUI/Texture.hpp>
#include <TGUI/Vector2f.hpp>
#include <TGUI/FloatRect.hpp>
#include <TGUI/Color.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Vertex.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API Sprite : public sf::Transformable
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief The way the image should be scaled
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum class ScalingType
        {
            Normal,     ///< The image is not split and scaled normally
            Horizontal, ///< Image is split in Left, Middle and Right parts. Left and Right keep ratio, Middle gets stretched
            Vertical,   ///< Image is split in Top, Middle and Bottom parts. Top and Bottom keep ratio, Middle gets stretched
            NineSlice   ///< Image is split in 9 parts. Corners keep size, sides are stretched in one direction, middle is stretched in both directions
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the texture
        ///
        /// @param texture  New texture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTexture(const Texture& texture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the texture used by this sprite
        ///
        /// @return Texture of the sprite
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const Texture& getTexture() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a reference to the texture used by this sprite
        ///
        /// @return Reference to the texture of the sprite
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Texture& getTexture();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether a texture was set
        ///
        /// @param Has a valid texture been assigned to this sprite?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isSet() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size that the image will have when drawing
        ///
        /// @param size  Size of the sprite
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Vector2f& size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the size that the image has when drawing
        ///
        /// @return Size of the sprite
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2f getSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the global color of the sprite
        ///
        /// This color is modulated (multiplied) with the sprite's texture. It can be used to colorize the sprite,
        /// or change its global opacity. Note that the alpha component is multiplied with the opacity set by setOpacity.
        ///
        /// By default, the sprite's color is opaque white.
        ///
        /// @param color  New color of the sprite
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setColor(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the global color of the sprite
        ///
        /// This color is modulated (multiplied) with the sprite's texture. It can be used to colorize the sprite,
        /// or change its global opacity.
        ///
        /// By default, the sprite's color is opaque white.
        ///
        /// @return Current color of the sprite
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const Color& getColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the opacity of the texture
        ///
        /// @param opacity  The opacity of the texture. 0 means completely transparent, while 1 (default) means fully opaque
        ///
        /// The alpha component of the color specified with setColor is multiplied with this factor.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setOpacity(float opacity);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the opacity of the texture
        ///
        /// @return The opacity of the texture. 0 means completely transparent, while 1 (default) means fully opaque
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float getOpacity() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the part of the sprite that should be drawn
        ///
        /// @param visibleRect Visible part of the sprite
        ///
        /// Set this to (0, 0, 0, 0) to show the entire sprite
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setVisibleRect(const FloatRect& visibleRect);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the part of the sprite that is drawn
        ///
        /// @return Visible part of the sprite
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        FloatRect getVisibleRect() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks if a certain pixel is transparent
        ///
        /// @param pos  Coordinate of the pixel
        ///
        /// @return True when the pixel is transparent, false when it is not
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isTransparentPixel(Vector2f pos) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the way in which the image is being scaled
        ///
        /// @return Scaling type
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ScalingType getScalingType() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draws the sprite
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update the location of the vertices
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateVertices();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        Vector2f     m_size;
        Texture     m_texture;
        std::vector<sf::Vertex> m_vertices;

        FloatRect   m_visibleRect;

        Color       m_vertexColor = Color::White;
        float       m_opacity = 1;

        ScalingType m_scalingType = ScalingType::Normal;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_SPRITE_HPP
