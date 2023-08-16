#include "Base.h"


Base::Base()
{
    
}

bool Base::init(int SCREEN_WIDTH, int SCREEN_HEIGHT,sf::Uint8* matrix,sf::Uint16* id_matrix,std::map<int, std::map<std::string,std::function<void()>>>* map_event, bool* screenModified)
{
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    this->matrix = matrix;
    this->id_matrix = id_matrix;
    this->map_event = map_event;
    this->screenModified = screenModified;

    return true;
}

sf::Uint32 Base::convertColor(unsigned char RGBA[4])
{
    return static_cast<sf::Uint32>((RGBA[0] << 24) | (RGBA[1] << 16) | ((RGBA[2]) << 8) |  RGBA[3]);
}

void Base::bind(int id, std::string event, std::function<void()> func)
{
    (*map_event)[id][event] = func;
}

int Base::rect(int post_x, int post_y, int width, int height, unsigned char RGBA[4], int set_id=0) {

    if(post_x>=SCREEN_WIDTH || post_y>=SCREEN_HEIGHT)
        return set_id;

    if(post_x+width>=SCREEN_WIDTH)
    {
        width = SCREEN_WIDTH - post_x;
        if(width<=0)
            return set_id;
    }

    if(post_y+height>=SCREEN_HEIGHT)
    {
        height = SCREEN_HEIGHT - post_y;
        if(height<=0)
            return set_id;
    }

    set_id = set_id==0 ? ++id : set_id;

    sf::Uint32 pixelValue = convertColor(RGBA);

    std::vector<sf::Uint32> rowPixels(width, pixelValue);  
    std::vector<sf::Uint16> rowIdPixels(width, set_id);  

    int startRow = (post_y * SCREEN_WIDTH + post_x)*4;  
    int startRowId = (post_y * SCREEN_WIDTH + post_x);  
    int y = 0;
    for (y = 0; y < height; ++y) {
        std::memcpy(matrix + startRow + y *4* SCREEN_WIDTH, rowPixels.data(), width * 4);
        std::memcpy(id_matrix + startRowId + y * SCREEN_WIDTH, rowIdPixels.data(), width*2);
    }
    *screenModified = true;

    return set_id;
}
int Base::rectBorder(int post_x, int post_y, int width, int height, int border, unsigned char fillRGBA[4], unsigned char borderRGBA[4]) {
    
    int idRectBorder = rect(post_x, post_y, width, height, borderRGBA);    
    rect(post_x+border, post_y+border, width-2*border, height-2*border, fillRGBA, idRectBorder);
    return idRectBorder;
}

int Base::circle(int center_x, int center_y, int radius, unsigned char fillRGBA[4], int set_id=0) {
    if (center_x < 0 || center_x >= SCREEN_WIDTH || center_y < 0 || center_y >= SCREEN_HEIGHT)
        return 0;

    set_id = set_id==0 ? ++id : set_id;

    int x = radius;
    int y = 0;
    sf::Uint32 pixelValueFill = convertColor(fillRGBA);

    int width = radius*2;
    int radiusCarre = radius*radius;

    for(int line=0; line<radius;line++)
    {
        std::vector<sf::Uint32> rowPixels(width, pixelValueFill);  
        std::vector<sf::Uint16> rowIdPixels(width, set_id);            

        if(center_y-y>=0)
        {
            int postUp = ((center_y-y)*SCREEN_WIDTH+center_x-x);
            std::memcpy(matrix + postUp*4, rowPixels.data(), width * 4);
            std::memcpy(id_matrix + postUp, rowIdPixels.data(), width*2);
        }
        if(center_y+y<SCREEN_HEIGHT)
        {
            int postDown = ((center_y+y)*SCREEN_WIDTH+center_x-x);
            std::memcpy(matrix + postDown*4, rowPixels.data(), width * 4);
            std::memcpy(id_matrix + postDown, rowIdPixels.data(), width*2);
        }
        
        y++;
        int yCarre = y*y;

        while(x*x+yCarre>radiusCarre)
        {
            x--;
            width-=2;
        }
    }
    *screenModified = true;
    return set_id;
}

int Base::circleBorder(int center_x, int center_y, int radius, int border, unsigned char fillRGBA[4], unsigned char borderRGBA[4]) {

    int idCircle = circle(center_x, center_y, radius, borderRGBA);
    circle(center_x, center_y, radius-border, fillRGBA, idCircle);
    return idCircle;
}

int Base::rectCircleAngle(int post_x, int post_y, int w, int h, int radius, unsigned char fillRGBA[4], int set_id=0) {

    set_id = set_id==0 ? ++id : set_id;

    id++;

    int center_x = post_x+radius;
    int center_y = post_y+(int)h/2;

    w -= 2*radius;
    h -= 2*radius;

    if(w<0)
    {
        w=0;
    }
    if(h<0)
    {
        h=0;
    }

    h/=2;

    int x = radius;
    int y = 0;
    sf::Uint32 pixelValueFill = convertColor(fillRGBA);

    int width = radius*2;
    int radiusCarre = radius*radius;
    rect(post_x,post_y+radius,w+2*radius,h*2, fillRGBA);

    for(int line=0; line<radius;line++)
    {
        std::vector<sf::Uint32> rowPixels(width+w, pixelValueFill);  
        std::vector<sf::Uint16> rowIdPixels(width+w, set_id);   

        if(center_y-y>=0)
        {
            int postUp = ((center_y-y-h)*SCREEN_WIDTH+center_x-x);
            std::memcpy(matrix + postUp*4, rowPixels.data(), (width+w) * 4);
            std::memcpy(id_matrix + postUp, rowIdPixels.data(), (width+w)*2);
        }
        if(center_y+y<SCREEN_HEIGHT)
        {
            int postDown = ((center_y+y+h)*SCREEN_WIDTH+center_x-x);
            std::memcpy(matrix + postDown*4, rowPixels.data(), (width+w) * 4);
            std::memcpy(id_matrix + postDown, rowIdPixels.data(), (width+w)*2);
        }
        y++;

        int yCarre = y*y;

        while(x*x+yCarre>radiusCarre)
        {
            x--;
            width-=2;
        }
    }
    *screenModified = true;
    return set_id;
}

int Base::rectCircleAngleBorder(int post_x, int post_y, int w, int h, int radius, int border, unsigned char fillRGBA[4], unsigned char borderRGBA[4]) {

    int idRectCircleAngle = rectCircleAngle(post_x, post_y, w, h, radius, borderRGBA);
    rectCircleAngle(post_x+border, post_y+border, w-2*border, h-2*border, radius, fillRGBA, idRectCircleAngle);
    return idRectCircleAngle;
}

int Base::text(int x, int y, std::string text, unsigned short int size, unsigned char text_color[4], unsigned char background_color[4], int set_id = 0)
{
    set_id = set_id==0 ? ++id : set_id;
    int start_row = (y * SCREEN_WIDTH + x);
    
    for(int post=0; post<text.size(); post++)
    {
        std::string text_in_letter = convertText(text[post], size);
        int line = 0;
        int col = 0;
        int width = 0;
        
        int text_size = text_in_letter.size();
        
        for(int post_char = 0; post_char<text_size; post_char++)
        {
            if(line>=size)
            {
                break;
            }
            unsigned char character = text_in_letter[post_char];
            if(character==85)
            {
                line++;
                col = 0;
            }
            else
            {
                for(int power = 128; power>0; power/=2)
                {
                    bool bit = (character & power) != 0;
                    
                    matrix[start_row + col + line * SCREEN_WIDTH*4] = (bit) ? text_color[0] : background_color[0];
                    matrix[start_row + col + line * SCREEN_WIDTH*4+1] = (bit) ? text_color[1] : background_color[1];
                    matrix[start_row + col + line * SCREEN_WIDTH*4+2] = (bit) ? text_color[2] : background_color[2];
                    matrix[start_row + col + line * SCREEN_WIDTH*4+3] = (bit) ? text_color[3] : background_color[3];
                    id_matrix[start_row + (int)col/2 + line * SCREEN_WIDTH] = set_id;
                    col+=4;
                    if(bit)
                    {
                        width = col/4>width ? col/4 : width;
                    }
                }
            }
        }
        
        col = 0;

        while(line<size)
        {
            for(int post=0; post<width/8;post++)
            {
                for(int power = 0; power<8; power++)
                {
                    matrix[start_row + col + line * SCREEN_WIDTH*4] = background_color[0];
                    matrix[start_row + col + line * SCREEN_WIDTH*4+1] = background_color[1];
                    matrix[start_row + col + line * SCREEN_WIDTH*4+2] = background_color[2];
                    matrix[start_row + col + line * SCREEN_WIDTH*4+3] = background_color[3];
                    id_matrix[start_row + (int)col/2 + line * SCREEN_WIDTH] = set_id;
                    col+=4;
                }   
            }
            line++;
        }
        start_row+=width*4;
    }
    *screenModified = true;
    return id;
}

std::string Base::convertText(unsigned char letter, unsigned short int size)
{
    size = size%2==0 ? size : size+1;
    if(size<16)
    {
        size = 16;
    }
    else if(size>200)
    {
        size = 200;
    }
    if((*font_dictionnary).count(size))
    {
        return (*font_dictionnary)[size][letter];
    }
    else
    {
                std::fstream file;
        file.open("ressources/font/roboto11/"+std::to_string(size)+"_px_roboto11.txt",std::ios::in);
        if (file.is_open()){   //checking whether the file is open
            std::string line;
            
            while(getline(file, line)){  //read data from file object and put it into string.
                int position_list_char = 0;
                unsigned char character;
                char symbol;
                for(int col=0; col<line.size(); col++)
                {
                    character = line[col];
                    symbol = (*character_list)[position_list_char*2];
                    
                    if (character==85)
                    {
                        (*font_dictionnary)[size][symbol] += character;
                        position_list_char ++;
                        if (position_list_char>91)
                            position_list_char = 0;
                    }
                    else if (character==170)
                    {
                        position_list_char = 0;
                    }
                    else
                    {
                        if(symbol==' ')
                        {
                            character=0x00;
                        }
                        (*font_dictionnary)[size][symbol] += character;
                    }
                }
            }
            file.close();   //close the file object.
        }
    }
    return (*font_dictionnary)[size][letter];
}



Base::~Base()
{
	
}
