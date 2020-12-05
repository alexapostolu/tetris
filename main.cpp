#include <SFML/Graphics.hpp>

#include <iostream>
#include <cstdint>
#include <ctime>
#include <array>
#include <vector>

typedef std::vector<std::vector<sf::RectangleShape> > Matrix;
typedef std::array<sf::Vector2i, 4> Cord;

constexpr uint8_t GRID_WIDTH = 10;
constexpr uint8_t GRID_HEIGHT = 20;

bool NO_LOOP = false;

bool can_hold_piece = true;

std::array<Cord, 7> tetrominos{
    std::array<sf::Vector2i, 4>{ sf::Vector2i(3, 0), sf::Vector2i(4, 0), sf::Vector2i(5, 0), sf::Vector2i(6, 0) },
    std::array<sf::Vector2i, 4>{ sf::Vector2i(3, 0), sf::Vector2i(3, 1), sf::Vector2i(4, 1), sf::Vector2i(5, 1) },
    std::array<sf::Vector2i, 4>{ sf::Vector2i(5, 0), sf::Vector2i(3, 1), sf::Vector2i(4, 1), sf::Vector2i(5, 1) },
    std::array<sf::Vector2i, 4>{ sf::Vector2i(4, 0), sf::Vector2i(4, 1), sf::Vector2i(5, 0), sf::Vector2i(5, 1) },
    std::array<sf::Vector2i, 4>{ sf::Vector2i(4, 0), sf::Vector2i(5, 0), sf::Vector2i(3, 1), sf::Vector2i(4, 1) },
    std::array<sf::Vector2i, 4>{ sf::Vector2i(4, 0), sf::Vector2i(3, 1), sf::Vector2i(4, 1), sf::Vector2i(5, 1) },
    std::array<sf::Vector2i, 4>{ sf::Vector2i(3, 0), sf::Vector2i(4, 0), sf::Vector2i(4, 1), sf::Vector2i(5, 1) },
};

sf::Vector2i tetrominos90[7][4] = {
    { sf::Vector2i(2, -1), sf::Vector2i(1, 0), sf::Vector2i(0, 1), sf::Vector2i(-1, 2) },
    { sf::Vector2i(1, 0), sf::Vector2i(2, -1), sf::Vector2i(0, 0), sf::Vector2i(-1, 1) },
    { sf::Vector2i(-1, 0), sf::Vector2i(1, 0), sf::Vector2i(0, 1), sf::Vector2i(0, 1) },
    { sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0) },
    { sf::Vector2i(0, 0), sf::Vector2i(-1, 1), sf::Vector2i(2, 0), sf::Vector2i(1, 1) },
    { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 0), sf::Vector2i(-1, 1) },
    { sf::Vector2i(2, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 0), sf::Vector2i(-1, 1) },
};

sf::Vector2i tetrominos180[7][4] = {
    { sf::Vector2i(-2, 2), sf::Vector2i(-1, 1), sf::Vector2i(0, 0), sf::Vector2i(1, -1) },
    { sf::Vector2i(-1, 1), sf::Vector2i(-1, 1), sf::Vector2i(1, 0), sf::Vector2i(1, 0) },
    { sf::Vector2i(-1, 1), sf::Vector2i(0, 0), sf::Vector2i(1, -1), sf::Vector2i(-2, 0) },
    { sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0) },
    { sf::Vector2i(0, 1), sf::Vector2i(1, 0), sf::Vector2i(-2, 1), sf::Vector2i(-1, 0) },
    { sf::Vector2i(-1, 1), sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0) },
    { sf::Vector2i(-2, 1), sf::Vector2i(0, 0), sf::Vector2i(-1, 1), sf::Vector2i(1, 0) },
};

sf::Vector2i tetrominos270[7][4] = {
    { sf::Vector2i(1, -2), sf::Vector2i(0, -1), sf::Vector2i(-1, 0), sf::Vector2i(-2, 1) },
    { sf::Vector2i(1, -1), sf::Vector2i(0, 0), sf::Vector2i(-2, 1), sf::Vector2i(-1, 0) },
    { sf::Vector2i(0, -1), sf::Vector2i(0, -1), sf::Vector2i(-1, 0), sf::Vector2i(1, 0) },
    { sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0) },
    { sf::Vector2i(-1, -1), sf::Vector2i(-2, 0), sf::Vector2i(1, -1), sf::Vector2i(0, 0) },
    { sf::Vector2i(1, -1), sf::Vector2i(-1, 0), sf::Vector2i(-1, 0), sf::Vector2i(0, 0) },
    { sf::Vector2i(1, -1), sf::Vector2i(-1, 0), sf::Vector2i(0, -1), sf::Vector2i(-2, 0) },
};

sf::Vector2i tetrominos0[7][4] = {
    { sf::Vector2i(-1, 1), sf::Vector2i(0, 0), sf::Vector2i(1, -1), sf::Vector2i(2, -2) },
    { sf::Vector2i(-1, 0), sf::Vector2i(-1, -0), sf::Vector2i(1, -1), sf::Vector2i(1, -1) },
    { sf::Vector2i(2, 0), sf::Vector2i(-1, 1), sf::Vector2i(0, 0), sf::Vector2i(1, -1) },
    { sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0) },
    { sf::Vector2i(1, 0), sf::Vector2i(2, -1), sf::Vector2i(-1, 0), sf::Vector2i(0, -1) },
    { sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(1, -1) },
    { sf::Vector2i(-1, 0), sf::Vector2i(1, -1), sf::Vector2i(0, 0), sf::Vector2i(2, -1) },
};

sf::Color tetromino_colours[7] = {
    sf::Color(0, 230, 255),
    sf::Color(0, 0, 255),
    sf::Color(255, 180, 0),
    sf::Color(255, 255, 0),
    sf::Color(0, 255, 0),
    sf::Color(190, 0, 255),
    sf::Color(255, 0, 0)
};

void line_clear(Matrix& grid)
{
    for (int a = 0; a < grid.size(); ++a)
    {
        bool lineFull = true;
        for (int b = 0; b < grid[a].size() && lineFull; ++b)
        {
            if (grid[a][b].getFillColor() == sf::Color(120, 120, 120))
                lineFull = false;
        }

        if (lineFull)
        {
            for (int b = a; b > 0; --b)
            {
                for (int c = 0; c < grid[b].size(); ++c)
                {
                    grid[b][c].setFillColor(grid[b - 1][c].getFillColor());
                    grid[b - 1][c].setFillColor(sf::Color(120, 120, 120));
                }
            }
        }
    }
}

void piece_new(Matrix& grid, Cord& current_piece, int& current_index, int& orientation, int piece_set = rand() % 7)
{
    can_hold_piece = true;

    line_clear(grid);

    current_index = piece_set;
    current_piece = tetrominos[current_index];

    orientation = 1;

    for (const sf::Vector2i& vec : current_piece)
    {
        if (grid[vec.y][vec.x].getFillColor() != sf::Color(120, 120, 120))
            NO_LOOP = true;

        grid[vec.y][vec.x].setFillColor(tetromino_colours[current_index]);
    }
}

bool piece_move_down(Matrix& grid, Cord& current_piece, int current_index)
{
    for (const sf::Vector2i& cord : current_piece)
    {
        if (cord.y == GRID_HEIGHT - 1)
            return true;

        if (grid[cord.y + 1][cord.x].getFillColor() != sf::Color(120, 120, 120))
        {
            bool canMove = false;
            for (const sf::Vector2i& other_cord : current_piece)
            {
                if (cord.y + 1 == other_cord.y && cord.x == other_cord.x)
                {
                    canMove = true;
                    break;
                }
            }

            if (!canMove)
                return true;
        }
    }

    for (int a = (int)current_piece.size() - 1; a >= 0; --a)
    {
        grid[current_piece[a].y][current_piece[a].x].setFillColor(sf::Color(120, 120, 120));

        current_piece[a].y++;
        grid[current_piece[a].y][current_piece[a].x].setFillColor(tetromino_colours[current_index]);
    }

    return false;
}

void piece_move_side(Matrix& grid, Cord& current_piece, int current_index, int direction)
{
    for (const sf::Vector2i& cord : current_piece)
    {
        if (cord.x + direction == -1 || cord.x + direction == GRID_WIDTH)
            return;

        if (grid[cord.y][cord.x + direction].getFillColor() != sf::Color(120, 120, 120))
        {
            bool canMove = false;
            for (const sf::Vector2i& other_cord : current_piece)
            {
                if (cord.x + direction == other_cord.x && cord.y == other_cord.y)
                {
                    canMove = true;
                    break;
                }
            }

            if (!canMove)
                return;
        }
    }

    for (sf::Vector2i& cord : current_piece)
    {
        grid[cord.y][cord.x].setFillColor(sf::Color(120, 120, 120));
        cord.x += direction;
    }

    for (const sf::Vector2i& cord : current_piece)
        grid[cord.y][cord.x].setFillColor(tetromino_colours[current_index]);
}

void piece_rotate(Matrix& grid, Cord& current_piece, int current_index, int& orientation)
{
    orientation = orientation == 4 ? 1 : orientation + 1;
    for (int a = 0; a < current_piece.size(); ++a)
    {
        grid[current_piece[a].y][current_piece[a].x].setFillColor(sf::Color(120, 120, 120));

        if (orientation == 1)
            current_piece[a] += tetrominos0[current_index][a];
        else if (orientation == 2)
            current_piece[a] += tetrominos90[current_index][a];
        else if (orientation == 3)
            current_piece[a] += tetrominos180[current_index][a];
        else
            current_piece[a] += tetrominos270[current_index][a];
    }


    for (const sf::Vector2i& vec : current_piece)
    {
        if (vec.x < 0 || vec.x >= GRID_WIDTH || vec.y < 0 || vec.y >= GRID_HEIGHT || grid[vec.y][vec.x].getFillColor() != sf::Color(120, 120, 120))
        {
            for (int b = 0; b < current_piece.size(); ++b)
            {
                if (orientation == 1)
                    current_piece[b] -= tetrominos0[current_index][b];
                else if (orientation == 2)
                    current_piece[b] -= tetrominos270[current_index][b];
                else if (orientation == 3)
                    current_piece[b] -= tetrominos180[current_index][b];
                else
                    current_piece[b] -= tetrominos90[current_index][b];

                grid[current_piece[b].y][current_piece[b].x].setFillColor(tetromino_colours[current_index]);
            }

            orientation--;
            return;
        }
    }

    for (const sf::Vector2i& cord : current_piece)
        grid[cord.y][cord.x].setFillColor(false ? sf::Color(0, 255, 0) : tetromino_colours[current_index]);
}

void piece_hard_drop(Matrix& grid, Cord& current_piece, int& current_index, int& orientation, sf::Clock& drop_clock)
{
    while (!piece_move_down(grid, current_piece, current_index));

    piece_new(grid, current_piece, current_index, orientation);
    drop_clock.restart();
}

void piece_hold(Matrix& grid, Cord& current_piece, int& current_index, int& orientation, int& hold_index)
{
    if (!can_hold_piece)
        return;

    for (const sf::Vector2i& vec : current_piece)
        grid[vec.y][vec.x].setFillColor(sf::Color(120, 120, 120));

    if (hold_index == -1)
    {
        hold_index = current_index;
        piece_new(grid, current_piece, current_index, orientation);

        can_hold_piece = false;
        return;
    }

    int current_index_temp = current_index;
    piece_new(grid, current_piece, current_index, orientation, hold_index);
    hold_index = current_index_temp;

    can_hold_piece = false;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(630, 860), "Tetris");

    srand((unsigned int)time(0));

    Matrix grid(GRID_HEIGHT, std::vector<sf::RectangleShape>(GRID_WIDTH));

    int current_index = rand() % 7;
    Cord current_piece = tetrominos[current_index];

    int hold_index = -1;

    int orientation = 1;

    sf::Clock drop_clock;
    float drop_speed = 0.5;

    for (std::size_t a = 0; a < grid.size(); ++a)
    {
        for (std::size_t b = 0; b < grid[a].size(); ++b)
        {
            grid[a][b] = sf::RectangleShape(sf::Vector2f(40, 40));
            grid[a][b].setPosition((b * 43) + 203.f, (a * 43) + 3.f);
            grid[a][b].setFillColor(sf::Color(120, 120, 120));
            grid[a][b].setOutlineColor(sf::Color(80, 80, 80));
            grid[a][b].setOutlineThickness(3);
        }
    }

    while (window.isOpen())
    {
        if (NO_LOOP)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    std::exit(0);
                }
            }

            /*
            sf::Font font;
            font.loadFromFile("font.ttf");

            sf::Text text;
            text.setFont(font);
            text.setString("Hello world");
            text.setCharacterSize(24); // in pixels, not points!
            text.setFillColor(sf::Color(255));
            
            window.draw(text);
            */

            continue;
        }

        drop_speed = 0.5f;

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    piece_move_side(grid, current_piece, current_index, -1);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    piece_move_side(grid, current_piece, current_index, 1);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    piece_rotate(grid, current_piece, current_index, orientation);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    drop_speed = 0.15f;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    piece_hard_drop(grid, current_piece, current_index, orientation, drop_clock);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                    piece_hold(grid, current_piece, current_index, orientation, hold_index);

                break;

            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        if (drop_clock.getElapsedTime().asSeconds() >= drop_speed)
        {
            if (piece_move_down(grid, current_piece, current_index))
                piece_new(grid, current_piece, current_index, orientation);

            drop_clock.restart();
        }

        window.clear(sf::Color(0, 0, 255));

        for (const std::vector<sf::RectangleShape>& row : grid)
        {
            for (const sf::RectangleShape& cell : row)
                window.draw(cell);
        }

        window.display();
    }
}