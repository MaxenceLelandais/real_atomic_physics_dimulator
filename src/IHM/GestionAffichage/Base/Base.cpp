#include "Base.h"

Base::Base()
{
}

bool Base::init(int _SCREEN_WIDTH, int _SCREEN_HEIGHT, sf::Uint8 *_matrix, sf::Uint16 *_id_matrix, std::map<int, std::map<std::string, std::function<void()>>> *_map_event, bool *_screenModified)
{
    this->SCREEN_WIDTH = _SCREEN_WIDTH;
    this->SCREEN_HEIGHT = _SCREEN_HEIGHT;
    this->matrix = _matrix;
    this->id_matrix = _id_matrix;
    this->map_event = _map_event;
    this->screenModified = _screenModified;

    return true;
}

sf::Uint32 Base::convertColor(unsigned char RGBA[4])
{
    return static_cast<sf::Uint32>((RGBA[3] << 24) | (RGBA[2] << 16) | ((RGBA[1]) << 8) | RGBA[0]);
}

void Base::bind(int id, std::string event, std::function<void()> func)
{
    (*map_event)[id][event] = func;
}

int Base::rect(int post_x, int post_y, int width, int height, unsigned char RGBA[4])
{
    return rect(post_x, post_y, width, height, RGBA, 0);
}

int Base::rect(int post_x, int post_y, int width, int height, unsigned char RGBA[4], int set_id)
{

    if (post_x >= SCREEN_WIDTH || post_y >= SCREEN_HEIGHT)
        return set_id;

    if (post_x + width >= SCREEN_WIDTH)
    {
        width = SCREEN_WIDTH - post_x;
        if (width <= 0)
            return set_id;
    }

    if (post_y + height >= SCREEN_HEIGHT)
    {
        height = SCREEN_HEIGHT - post_y;
        if (height <= 0)
            return set_id;
    }

    sf::Uint32 pixelValue = convertColor(RGBA);

    unsigned int startRow = (post_y * SCREEN_WIDTH + post_x) * 4;
    unsigned int startRowId = (post_y * SCREEN_WIDTH + post_x);

    if (set_id == 0)
    {

        ++id;
        set_id = id;
    }

    std::vector<sf::Uint32> rowPixels(width, pixelValue);
    std::vector<sf::Uint16> rowIdPixels(width, set_id);

    for (unsigned short int y = 0; y < height; ++y)
    {
        std::memcpy(matrix + startRow + y * 4 * SCREEN_WIDTH, rowPixels.data(), width * 4);
        std::memcpy(id_matrix + startRowId + y * SCREEN_WIDTH, rowIdPixels.data(), width * 2);
    }
    *screenModified = true;

    return set_id;
}

int Base::rectBorder(int post_x, int post_y, int width, int height, int border, unsigned char fillRGBA[4], unsigned char borderRGBA[4])
{
    return rectBorder(post_x, post_y, width, height, border, fillRGBA, borderRGBA);
}

int Base::rectBorder(int post_x, int post_y, int width, int height, int border, unsigned char fillRGBA[4], unsigned char borderRGBA[4], int set_id)
{
    if (set_id == 0)
        set_id = rect(post_x, post_y, width, height, borderRGBA);
    else
        rect(post_x, post_y, width, height, borderRGBA, set_id);
    rect(post_x + border, post_y + border, width - 2 * border, height - 2 * border, fillRGBA, set_id);
    return set_id;
}

int Base::circle(int center_x, int center_y, int radius, unsigned char fillRGBA[4])
{
    return circle(center_x, center_y, radius, fillRGBA, 0);
}

int Base::circle(int center_x, int center_y, int radius, unsigned char fillRGBA[4], int set_id)
{
    if (center_x < 0 || center_x >= SCREEN_WIDTH || center_y < 0 || center_y >= SCREEN_HEIGHT)
        return 0;

    sf::Uint32 pixelValueFill = convertColor(fillRGBA);

    unsigned int radiusCarre = radius * radius;
    unsigned int yCarre;
    unsigned int postUp;
    unsigned int postDown;

    unsigned short int x = radius;
    unsigned short int y = 0;
    unsigned short int width = radius * 2;

    if (set_id == 0)
    {

        ++id;
        set_id = id;
    }

    for (unsigned short int line = 0; line < radius; line++)
    {
        std::vector<sf::Uint32> rowPixels(width, pixelValueFill);
        std::vector<sf::Uint16> rowIdPixels(width, set_id);

        if (center_y - y >= 0)
        {
            postUp = ((center_y - y) * SCREEN_WIDTH + center_x - x);
            std::memcpy(matrix + postUp * 4, rowPixels.data(), width * 4);
            std::memcpy(id_matrix + postUp, rowIdPixels.data(), width * 2);
        }
        if (center_y + y < SCREEN_HEIGHT)
        {
            postDown = ((center_y + y) * SCREEN_WIDTH + center_x - x);
            std::memcpy(matrix + postDown * 4, rowPixels.data(), width * 4);
            std::memcpy(id_matrix + postDown, rowIdPixels.data(), width * 2);
        }

        y++;
        yCarre = y * y;

        while (x * x + yCarre > radiusCarre)
        {
            x--;
            width -= 2;
        }
    }
    *screenModified = true;
    return set_id;
}

int Base::circleBorder(int center_x, int center_y, int radius, int border, unsigned char fillRGBA[4], unsigned char borderRGBA[4])
{
    return circleBorder(center_x, center_y, radius, border, fillRGBA, borderRGBA, 0);
}

int Base::circleBorder(int center_x, int center_y, int radius, int border, unsigned char fillRGBA[4], unsigned char borderRGBA[4], int set_id)
{
    if (set_id == 0)
        set_id = circle(center_x, center_y, radius, borderRGBA);
    else
        circle(center_x, center_y, radius, borderRGBA, set_id);
    circle(center_x, center_y, radius - border, fillRGBA, set_id);
    return set_id;
}

int Base::rectCircleAngle(int post_x, int post_y, int w, int h, int radius, unsigned char fillRGBA[4])
{
    return rectCircleAngle(post_x, post_y, w, h, radius, fillRGBA, 0);
}
int Base::rectCircleAngle(int post_x, int post_y, int w, int h, int radius, unsigned char fillRGBA[4], int set_id)
{
    sf::Uint32 pixelValueFill = convertColor(fillRGBA);

    unsigned short int center_x = post_x + radius;
    unsigned short int center_y = post_y + h / 2;
    unsigned short int x = radius;
    unsigned short int y = 0;
    unsigned short int width = radius * 2;

    unsigned int radiusCarre = radius * radius;
    unsigned int yCarre;
    unsigned int postUp;
    unsigned int postDown;

    if (set_id == 0)
    {
        ++id;
        set_id = id;
    }

    w -= 2 * radius;
    h -= 2 * radius;

    w = w < 0 ? 0 : w;
    h = h < 0 ? 0 : h;

    h /= 2;

    rect(post_x, post_y + radius, w + 2 * radius, h * 2, fillRGBA, set_id);

    for (int line = 0; line < radius; line++)
    {
        std::vector<sf::Uint32> rowPixels(width + w, pixelValueFill);
        std::vector<sf::Uint16> rowIdPixels(width + w, set_id);

        if (center_y - y >= 0)
        {
            postUp = ((center_y - y - h) * SCREEN_WIDTH + center_x - x);
            std::memcpy(matrix + postUp * 4, rowPixels.data(), (width + w) * 4);
            std::memcpy(id_matrix + postUp, rowIdPixels.data(), (width + w) * 2);
        }
        if (center_y + y < SCREEN_HEIGHT)
        {
            postDown = ((center_y + y + h) * SCREEN_WIDTH + center_x - x);
            std::memcpy(matrix + postDown * 4, rowPixels.data(), (width + w) * 4);
            std::memcpy(id_matrix + postDown, rowIdPixels.data(), (width + w) * 2);
        }
        y++;

        yCarre = y * y;

        while (x * x + yCarre > radiusCarre)
        {
            x--;
            width -= 2;
        }
    }
    *screenModified = true;
    return set_id;
}

int Base::rectCircleAngleBorder(int post_x, int post_y, int w, int h, int radius, int border, unsigned char fillRGBA[4], unsigned char borderRGBA[4])
{
    return rectCircleAngleBorder(post_x, post_y, w, h, radius, border, fillRGBA, borderRGBA, 0);
}

int Base::rectCircleAngleBorder(int post_x, int post_y, int w, int h, int radius, int border, unsigned char fillRGBA[4], unsigned char borderRGBA[4], int set_id)
{
    if (set_id == 0)
        set_id = rectCircleAngle(post_x, post_y, w, h, radius, borderRGBA);
    else
        int a = rectCircleAngle(post_x, post_y, w, h, radius, borderRGBA, set_id);
    int p = rectCircleAngle(post_x + border, post_y + border, w - 2 * border, h - 2 * border, radius, fillRGBA, set_id);
    return set_id;
}

void Base::text(int x, int y, std::string textDraw, int size, unsigned char text_color[4], unsigned char background_color[4])
{
    unsigned int text_size;
    unsigned int value;
    unsigned int value2;
    unsigned int start_row = (y * SCREEN_WIDTH + x) * 4;

    unsigned short int maxiVal = 0;
    unsigned short int miniVal = 0;
    unsigned short int *decalage_max = &maxiVal;
    unsigned short int *decalage_min = &miniVal;

    unsigned char line;
    unsigned char col;
    unsigned char offSetY;
    unsigned char decalage_min_save;
    unsigned char power;
    unsigned char offSetX;
    unsigned char character;

    bool activate_min;
    bool decalage_max_mesure;
    bool bit;
    bool width_mesure;

    size = size % 2 == 0 ? size : size + 1;
    size = size < 16 ? 16 : size > 200 ? 200
                                       : size;

    offSetX = size / 5;

    for (int post = 0; post < textDraw.size(); post++)
    {
        std::string text_in_letter = convertText(textDraw[post], size);

        text_size = text_in_letter.size();

        line = 0;
        col = 0;
        offSetY = 0;

        getWidthLetter(textDraw[post], size, decalage_min, decalage_max);
        decalage_min_save = (*decalage_min);
        value = start_row;

        for (int post_char = 0; post_char < text_size; post_char++)
        {
            if (line >= size)
                break;

            character = post_char < text_size ? text_in_letter[post_char] : 0x00;

            if (character == 85)
            {
                line++;
                value = start_row + line * SCREEN_WIDTH * 4;
                if (line < size)
                    offSetY = (size - line) * (col);

                col = 0;
                (*decalage_min) = decalage_min_save;
            }
            else
            {
                for (power = 128; power > 0; power /= 2)
                {
                    bit = (character & power) != 0;
                    if (col >= (*decalage_max))
                        break;

                    if ((*decalage_min) <= 0)
                    {
                        value2 = value + col * 4;
                        matrix[value2] = (bit) ? text_color[0] : background_color[0];
                        matrix[value2 + 1] = (bit) ? text_color[1] : background_color[1];
                        matrix[value2 + 2] = (bit) ? text_color[2] : background_color[2];
                        matrix[value2 + 3] = (bit) ? text_color[3] : background_color[3];
                        col += 1;
                    }
                    else
                        (*decalage_min)--;
                }
            }
        }
        
        if (post < textDraw.size() - 1)
        {
            start_row += (*decalage_max) * 4;
            for (line = 0; line < size; line++)
            {
                value = start_row + line * SCREEN_WIDTH * 4;
                for (col = 0; col < offSetX; col += 1)
                {
                    value2 = value + col * 4;
                    matrix[value2] = background_color[0];
                    matrix[value2 + 1] = background_color[1];
                    matrix[value2 + 2] = background_color[2];
                    matrix[value2 + 3] = background_color[3];
                }
            }
            start_row += offSetX * 4;
            *decalage_max = 0;
        *decalage_min = 0;
        }
    }
    *screenModified = true;
}

int Base::getWidthText(std::string textDraw, int size)
{
    unsigned short int maxiVal = 0;
    unsigned short int miniVal = 0;

    unsigned short int *maxi = &maxiVal;
    unsigned short int *mini = &miniVal;
    int width = 0;
    for (int post = 0; post < textDraw.size(); post++)
    {
        getWidthLetter(textDraw[post], size, mini, maxi);
        width += (*maxi)+size / 5;
        *maxi = 0;
        *mini = 0;
    }
    return width-size / 5;
}

void Base::getWidthLetter(unsigned char character, unsigned short int size, unsigned short int *decalage_min, unsigned short int *decalage_max)
{
    std::string text_in_letter = convertText(character, size);
    unsigned int text_size = text_in_letter.size();

    unsigned char line = 0;
    unsigned char col = 0;
    unsigned char offSetY = 0;
    unsigned char characterText;
    unsigned char power;

    bool activate_min = true;
    bool decalage_max_mesure = true;
    bool width_mesure = true;
    bool bit = false;

    if (character != ' ')
    {
        for (int post_char = 0; post_char < text_size; post_char++)
        {
            if (line >= size)
                break;

            characterText = text_in_letter[post_char];
            if (characterText == 85)
            {
                line++;
                col = 0;
                if (character != 'i' && character != '!')
                    activate_min = true;
                if ((character == 'i' or character == '!') && (*decalage_max) != 0)
                    decalage_max_mesure = false;
            }
            else
            {
                for (power = 128; power > 0; power /= 2)
                {
                    bit = (characterText & power) != 0;
                    if (bit && activate_min)
                    {
                        (*decalage_min) = (*decalage_min) == 0 ? col : (*decalage_min) > col ? col
                                                                                             : (*decalage_min);
                        activate_min = false;
                    }
                    if (bit && decalage_max_mesure)
                        (*decalage_max) = (*decalage_max) == 0 ? col : (*decalage_max) < col ? col
                                                                                             : (*decalage_max);
                    col += 1;
                }
            }
        }
    }
    (*decalage_max) -= (*decalage_min) - 1;
}

std::string Base::convertText(unsigned char letter, unsigned short int size)
{

    unsigned int position_list_char = 0;
    unsigned int col;

    unsigned char character;
    char symbol;

    if ((*font_dictionnary).count(size))
        return (*font_dictionnary)[size][letter];
    else
    {
        std::fstream file;
        file.open("ressources/font/roboto11/" + std::to_string(size) + "_px_roboto11.txt", std::ios::in);
        if (file.is_open())
        {
            std::string line;

            while (getline(file, line))
            {
                position_list_char = 0;

                for (col = 0; col < line.size(); col++)
                {
                    character = line[col];
                    symbol = (*character_list)[position_list_char * 2];

                    if (character == 85)
                    {
                        (*font_dictionnary)[size][symbol] += character;
                        position_list_char++;
                    }
                    else if (character == 170)
                    {
                        position_list_char = 0;
                    }
                    else
                    {
                        (*font_dictionnary)[size][symbol] += character;
                    }
                }
            }
            file.close(); // close the file object.
        }
    }
    return (*font_dictionnary)[size][letter];
}

Base::~Base()
{
}