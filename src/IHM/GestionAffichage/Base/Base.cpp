#include "Base.h"


Base::Base()
{
    
}

bool Base::init(int SCREEN_WIDTH, int SCREEN_HEIGHT,sf::Uint8* matrix,sf::Uint16* id_matrix,std::map<int, std::map<std::string,std::function<void()>>>* map_event)
{
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    this->matrix = matrix;
    this->id_matrix = id_matrix;
    this->map_event = map_event;

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

int Base::rect(int post_x, int post_y, int width, int height, unsigned char RGBA[4])
{
    return rect(post_x, post_y, width, height, RGBA, -1);
}

// ~2 000 000 000 actualisation pixel par secondes
int Base::rect(int post_x, int post_y, int width, int height, unsigned char RGBA[4], int set_id) {

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

    if (set_id==-1){
        id++;
        set_id = id++;
    }

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

    return set_id;
}

int Base::text(int x, int y, std::string text, unsigned short int size, unsigned char text_color[4], unsigned char background_color[4])
{
    id++;
    int start_row = (y * SCREEN_WIDTH + x);
    
    for(int post=0; post<text.size(); post++)
    {
        std::string text_in_letter = convertText(text[post], size);
        int line = 0;
        int col = 0;
        int width = 0;
        
        for(int post_char = 0; post_char<text_in_letter.size(); post_char++)
        {
            if(line>=size)
            {
                break;
            }
            unsigned char character = text_in_letter[post_char];
            if(character==85)
            {
                line++;
                if(width==0)
                {
                    width=col/4;
                }
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
                    col+=4;
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
                    col+=4;
                }   
            }
            line++;
        }
        start_row+=width*4;
    }

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
