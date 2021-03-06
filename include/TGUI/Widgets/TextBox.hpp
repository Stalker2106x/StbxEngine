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


#ifndef TGUI_TEXT_BOX_HPP
#define TGUI_TEXT_BOX_HPP


#include <TGUI/Widgets/Scrollbar.hpp>
#include <TGUI/Renderers/TextBoxRenderer.hpp>
#include <TGUI/Text.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Text box widget
    ///
    /// A text box is a multi-line input box which supports word-wrap and a vertical scrollbar.
    /// If you are looking for a single line input field (with options like setting a password character or displaying a
    /// default text when it is empty) then check out the EditBox class.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API TextBox : public Widget
    {
    public:

        typedef std::shared_ptr<TextBox> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const TextBox> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new text box widget
        ///
        /// @return The new text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static TextBox::Ptr create();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another text box
        ///
        /// @param textBox  The other text box
        ///
        /// @return The new text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static TextBox::Ptr copy(TextBox::ConstPtr textBox);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer that may be shared with other widgets using the same renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBoxRenderer* getSharedRenderer();
        const TextBoxRenderer* getSharedRenderer() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer
        /// @warning After calling this function, the widget has its own copy of the renderer and it will no longer be shared.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBoxRenderer* getRenderer();
        const TextBoxRenderer* getRenderer() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the text box
        ///
        /// This size does not include the borders.
        ///
        /// @param size  The new size of the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of the text box
        ///
        /// @param text  New text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setText(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Appends some text to the text that was already in the text box
        ///
        /// @param text  Text that will be added to the text that is already in the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addText(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text of the text box
        ///
        /// @return  The text that is currently inside the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::String& getText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text that you currently have selected
        ///
        /// @return The selected text of the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getSelectedText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the character size of the text
        ///
        /// @param size  The new text size.
        ///              The minimum text size is 8
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the character size of the text
        ///
        /// @return The current text size
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the maximum character limit
        ///
        /// @param maxChars  The new character limit.
        ///                  Set it to 0 to disable the limit
        ///
        /// This character limit is disabled by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumCharacters(std::size_t maxChars = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum character limit
        ///
        /// @return The character limit
        ///         The function will return 0 when there is no limit.
        ///
        /// There is no character limit by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getMaximumCharacters() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the blinking caret to after a specific character
        ///
        /// @param charactersBeforeCaret  The new position
        ///
        /// Note that the position is from before word-wrap is aplied.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCaretPosition(std::size_t charactersBeforeCaret);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns after which character the blinking cursor is currently located
        ///
        /// @return Characters before the caret
        ///
        /// Note that the position is from before word-wrap is aplied.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getCaretPosition() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes the text box read-only or make it writable again
        ///
        /// @param readOnly  Should the text box be read-only?
        ///
        /// When the text box is read-only, you can no longer delete characters and type text.
        /// Selecting text, copying text and even calling the setText function will still work.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setReadOnly(bool readOnly = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks if the text box read-only or writable
        ///
        /// @return Is the text box read-only?
        ///
        /// When the text box is read-only, you can no longer delete characters and type text.
        /// Selecting text, copying text and even calling the setText function will still work.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isReadOnly() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets whether the vertical scrollbar is present
        ///
        /// When present, the scrollbar will appear once the text takes more space than the text box.
        /// When not present, you will not be able to add text once the text box is full.
        /// The vertical scroll is present by default.
        ///
        /// @param present  Should the vertical scrollbar be present?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setVerticalScrollbarPresent(bool present);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the vertical scrollbar is present
        ///
        /// @return Is the vertical scrollbar present?
        ///
        /// @see setVerticalScrollbarPresent
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isVerticalScrollbarPresent() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the amount of lines that the text occupies in the TextBox
        ///
        /// @return Lines of text
        ///
        /// Note that this is the amount of lines after word-wrap is applied.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getLinesCount() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse position (which is relative to the parent widget) lies on top of the widget
        ///
        /// @return Is the mouse on top of the widget?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseOnWidget(Vector2f pos) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMousePressed(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseReleased(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseMoved(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void keyPressed(const sf::Event::KeyEvent& event) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void textEntered(std::uint32_t Key) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseWheelScrolled(float delta, Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseNoLongerOnWidget() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseNoLongerDown() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void widgetFocused() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void widgetUnfocused() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will search after which character the caret should be placed. It will not change the caret position.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2<std::size_t> findCaretPosition(Vector2f position) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Converts the two dimensional selection positions into one dimensional positions in the text.
        // The first element of the pair is the selection start and the second one is the selection end.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::pair<std::size_t, std::size_t> findTextSelectionPositions() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when you are selecting text.
        // It will find out which part of the text is selected.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void selectText(float posX, float posY);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Removes the selected characters. This function is called when pressing backspace, delete or a letter while there were
        // some characters selected.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deleteSelectedCharacters();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Rearrange the text inside the text box (by using word wrap).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rearrangeText(bool keepSelection);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will split the text into five pieces so that the text can be easily drawn.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateSelectionTexts();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the size without the borders
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2f getInnerSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called every frame with the time passed since the last frame.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void update(sf::Time elapsedTime) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculates the positions of the contents of the text box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculatePositions();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculates which lines are currently visible.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculateVisibleLines();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves a signal based on its name
        ///
        /// @param signalName  Name of the signal
        ///
        /// @return Signal that corresponds to the name
        ///
        /// @throw Exception when the name does not match any signal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Signal& getSignal(std::string signalName) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Lowercase name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const std::string& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the widget as a tree node in order to save it to a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::unique_ptr<DataIO::Node> save(SavingRenderersMap& renderers) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the widget from a tree of nodes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr clone() const override
        {
            return std::make_shared<TextBox>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        SignalString onTextChange = {"TextChanged"};    ///< The text was changed. Optional parameter: new text


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        sf::String   m_text;
        unsigned int m_textSize = 18;
        unsigned int m_lineHeight = 24;

        std::vector<sf::String> m_lines;

        // The maximum characters (0 by default, which means no limit)
        std::size_t m_maxChars = 0;

        // What is known about the visible lines?
        std::size_t m_topLine = 1;
        std::size_t m_visibleLines = 1;

        // Information about the selection
        sf::Vector2<std::size_t> m_selStart;
        sf::Vector2<std::size_t> m_selEnd;

        // Information about the caret
        Vector2f m_caretPosition;
        bool m_caretVisible = true;

        Text m_textBeforeSelection;
        Text m_textSelection1;
        Text m_textSelection2;
        Text m_textAfterSelection1;
        Text m_textAfterSelection2;

        std::vector<FloatRect> m_selectionRects;

        // The scrollbar
        ScrollbarChildWidget m_verticalScroll;

        // Is there a possibility that the user is going to double click?
        bool m_possibleDoubleClick = false;

        bool m_readOnly = false;

        Sprite m_spriteBackground;

        // Cached renderer properties
        Borders m_bordersCached;
        Padding m_paddingCached;
        Color   m_borderColorCached;
        Color   m_backgroundColorCached;
        Color   m_caretColorCached;
        Color   m_selectedTextBackgroundColorCached;
        float   m_caretWidthCached = 1;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TEXT_BOX_HPP
