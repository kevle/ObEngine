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


#ifndef TGUI_GRID_HPP
#define TGUI_GRID_HPP


#include <TGUI/Container.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API Grid : public Container
    {
    public:

        typedef std::shared_ptr<Grid> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const Grid> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief The alignment of the widget in its cell
        ///
        /// Where in the cell is the widget located?
        /// The widget is centered by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum class Alignment
        {
            Center,      ///< Center the widget in the cell
            UpperLeft,   ///< Draw the widget in the upper left corner of the cell
            Up,          ///< Draw the widget at the upper side of the cell (horizontally centered)
            UpperRight,  ///< Draw the widget in the upper right corner of the cell
            Right,       ///< Draw the widget at the right side of the cell (vertically centered)
            BottomRight, ///< Draw the widget in the bottom right corner of the cell
            Bottom,      ///< Draw the widget at the bottom of the cell (horizontally centered)
            BottomLeft,  ///< Draw the widget in the bottom left corner of the cell
            Left         ///< Draw the widget at the left side of the cell (vertically centered)
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Grid();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new grid widget
        ///
        /// @return The new grid
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Grid::Ptr create();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Grid(const Grid& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Move constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Grid(Grid&& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Overload of assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Grid& operator= (const Grid& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Overload of move assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Grid& operator= (Grid&& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another grid
        ///
        /// @param grid  The other grid
        ///
        /// @return The new grid
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Grid::Ptr copy(Grid::ConstPtr grid);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the grid
        ///
        /// @param size   New size of the grid
        ///
        /// When this function is called, the grid will no longer be auto-sizing and widgets in the grid will be repositioned
        /// to fill the available space.
        ///
        /// @see setAutoSize
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the grid is auto-sized or not
        ///
        /// @param autoSize  Should the size of the grid depend on the widgets inside it?
        ///
        /// When the grid is in auto-size mode, size is defined by the widgets that were added to the grid.
        /// Otherwise, the size is given and the widgets are positioned to fill the provided size.
        ///
        /// The grid is auto-sized by default.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setAutoSize(bool autoSize);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the grid is auto-sized or not
        ///
        /// @return Does the size of the grid depend on the widgets inside it?
        ///
        /// @see setAutoSize
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getAutoSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a single widget that was added to the container
        ///
        /// @param widget  Pointer to the widget to remove
        ///
        /// @see remove(sf::String)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool remove(const Widget::Ptr& widget) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all widgets that were added to the container
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllWidgets() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a widget to the grid
        ///
        /// @param widget    Pointer to a fully created widget that will be added to the grid
        /// @param row       The row in which the widget should be placed
        /// @param column    The column in which the widget should be placed
        /// @param borders   Distance from the grid cell to the widget (left, top, right, bottom)
        /// @param alignment Where the widget is located in the cell
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addWidget(const Widget::Ptr& widget,
                       std::size_t        row,
                       std::size_t        column,
                       const Borders&     borders   = Borders{0},
                       Alignment          alignment = Alignment::Center);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the widget in a specific cell of the grid
        ///
        /// @param row     The row that the widget is in
        /// @param column  The column that the widget is in
        ///
        /// @return The widget inside the given cell, or nullptr when the cell doesn't contain a widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr getWidget(std::size_t row, std::size_t column) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a list of widgets and the cell they are in
        ///
        /// @return A mapping of each widget to its row and cell. The first element of the pair is the row while the second
        ///         element in the pair is the column.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::map<Widget::Ptr, std::pair<std::size_t, std::size_t>> getWidgetLocations() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes borders of a given widget
        ///
        /// @param widget  The widget to which borders should be added
        /// @param borders The new borders around the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setWidgetBorders(const Widget::Ptr& widget, const Borders& borders = Borders(0, 0, 0, 0));


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes borders of a widget in a certain cell
        ///
        /// @param row     The row that the widget is in
        /// @param column  The column that the widget is in
        /// @param borders The new borders around the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setWidgetBorders(std::size_t row, std::size_t column, const Borders& borders = Borders(0, 0, 0, 0));


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the borders around a widget
        ///
        /// @param widget  The widget to get the borders from
        ///
        /// @return The borders inside the around the widget, or Borders{0} when the widget wasn't part of the grid
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Borders getWidgetBorders(const Widget::Ptr& widget) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the borders around a widget in a specific cell of the grid
        ///
        /// @param row     The row that the widget is in
        /// @param column  The column that the widget is in
        ///
        /// @return The borders inside the given cell, or Borders{0} when the cell doesn't contain a widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Borders getWidgetBorders(std::size_t row, std::size_t column) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the alignment of a given widget in its cell
        ///
        /// @param widget    The widget for which the alignment should be changed
        /// @param alignment The new alignment
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setWidgetAlignment(const Widget::Ptr& widget, Alignment alignment = Alignment::Center);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the alignment of a given widget in its cell
        ///
        /// @param row       The row that the widget is in
        /// @param column    The column that the widget is in
        /// @param alignment The new alignment
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setWidgetAlignment(std::size_t row, std::size_t column, Alignment alignment = Alignment::Center);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the alignment of a given widget
        ///
        /// @param widget  The widget to get the alignment from
        ///
        /// @return The alignment inside the cell, or Grid::Alignment::Center when the widget wasn't part of the grid
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Alignment getWidgetAlignment(const Widget::Ptr& widget) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the alignment of a given widget in its cell
        ///
        /// @param row     The row that the widget is in
        /// @param column  The column that the widget is in
        ///
        /// @return The alignment inside the given cell, or Grid::Alignment::Center when the cell doesn't contain a widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Alignment getWidgetAlignment(std::size_t row, std::size_t column) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the widgets and their positions in the grid
        ///
        /// @return grid of widgets
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::vector<std::vector<Widget::Ptr>>& getGridWidgets() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse position (which is relative to the parent widget) lies on top of the widget
        ///
        /// @return Is the mouse on top of the widget?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseOnWidget(sf::Vector2f pos) const override;


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
        // Returns the minimum size required by the grid to display correctly all widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getMinimumSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Reposition all the widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updatePositionsOfAllWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the position and size of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr clone() const override
        {
            return std::make_shared<Grid>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        bool m_autoSize = true;

        std::vector<std::vector<Widget::Ptr>> m_gridWidgets;
        std::vector<std::vector<Borders>>     m_objBorders;
        std::vector<std::vector<Alignment>>   m_objAlignment;

        std::vector<float> m_rowHeight;
        std::vector<float> m_columnWidth;

        std::map<Widget::Ptr, unsigned int> m_connectedCallbacks;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_GRID_HPP
