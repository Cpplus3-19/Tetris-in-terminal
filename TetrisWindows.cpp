#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

//Jeu Tetris dans le terminal pour Windows 

//contient pour l'instant que deux types de blocks

const int WIDTH = 10;  // restent
const int HEIGTH = 20;  //...inchangeables tout le temps 
int item_x, item_y;    //coordonées du block
int item_color = 1;
int choice;// variable qui donne le randum entre 0 et 1;
int score;
int rotation; //oriantation du block (à travailler)

bool items[2][4][4][4] =  // array de 2 blocks , qui a chacun 4 possibilités, qui est en soit une matrice 4x4

{
    //======================
    //L 0
    //======================
    {
        // Rotation 0
        {
            {false,false,true,false},
            {false,false,true,false},
            {false,false,true,false},
            {false,true,true,false}
        },

        // Rotation 1
        {
            {true,false,false,false},
            {true,true,true,false},
            {true,false,false,false},
            {false,false,false,false}
        },

        // Rotation 2
        {
            {true,true,false,false},
            {true,false,false,false},
            {true,false,false,false},
            {true,false,false,false}
        },

        // Rotation 3
        {
            {true,true,true,true},
            {false,false,false,true},
            {false,false,false,true},
            {false,false,false,true}
        }
    },

    //======================
    // une barre 1
    //======================
    {
        // Rotation 0
        {
            {false,false,false,false},
            {false,false,false,false},
            {true,true,true,true},
            {false,false,false,false}
        },

        // Rotation 1
        {
            {false,false,true,false},
            {false,false,true,false},
            {false,false,true,false},
            {false,false,true,false}
        },

        // Rotation 2
        {
            {false,false,false,false},
            {false,false,false,false},
            {true,true,true,true},
            {false,false,false,false}
        },

        // Rotation 3
        {
            {false,false,true,false},
            {false,false,true,false},
            {false,false,true,false},
            {false,false,true,false}
        }
    }
}; // ici on definit la structure et les rotations du block , pour changer ou ajouter des blocks utilisez multicursor alt+ souris

int item_size_x = 4, item_size_y = 4; // dimensions du block pour les cycles

int field[HEIGTH][WIDTH] = {0};  // field 

HANDLE h; // Donne acces au terminal et ses fonctionalités 

// fonction qui dessine le block
void insert_item_to_field(int x, int y, bool item[4][4], int color) {
    for (int i = 0; i < item_size_y; ++i) {
        for (int j = 0; j < item_size_x; ++j) {
            if (item[i][j]) {
                field[y+i][x+j] = color;
            }
        }
    }
}
//genere un nouveau block
void generate_new_item()
{
    item_x = WIDTH / 2;
    item_y = 0;

    choice = rand() % 2;

    insert_item_to_field(item_x, item_y, items[choice][rotation], 4);
}

//verifie si le block peut descendre 
bool can_move_down(int x, int y, bool item[4][4])
{
    for (int i = 0; i < item_size_y; ++i)
    {
        for (int j = 0; j < item_size_x; ++j)
        {
            if (item[i][j])
            {
                int new_y = y + i + 1;

                // Le bloc atteint le bas
                if (new_y >= HEIGTH)
                {
                    return false;
                
                }

                // Il y a déjà un bloc en dessous
                if (field[new_y][x + j] != 0)
                {
                    return false;
                }
            }
        }
    }

    return true;
}






void draw_point(int point) {
    switch (point) {
    case 0:
        cout << "."; break;
    case 1:
        
        SetConsoleTextAttribute(h, 0x1A);//couleurs
        cout << " ";
        SetConsoleTextAttribute(h, 0x0008);//couleurs
        break;
    }
    cout << " ";
}

// on vérifie si le joueur a constitué une ligne avec les blocks 
int points() 
{
    for (int i = 0; i < HEIGTH; i++)
    {
        bool complete = true;

        for (int j = 0; j < WIDTH; j++)
        {
            if (field[i][j] == 0)
            {
                complete = false;
                break;
            }
        }

        if (complete)
        {
            return i;   // numéro de la ligne complète
        }
    }

    return -1; // aucune ligne complète
}
// lorsque le block descends on le sumprime de sa position precedante 
void remove_item_from_field(int x, int y, bool item[4][4])
{
    if(y<HEIGTH){

        for (int i = 0; i < item_size_y; ++i)
        {
            for (int j = 0; j < item_size_x; ++j)
            {
            
                 if (item[i][j])
                {
                    field[y + i][x + j] = 0;
                }
              
            
            }
           
        }
    }
  
   
  
    
}
//on suprime la ligne du champs 
void remove_line(int ligne)
{
    for (int j = 0; j < WIDTH; j++)
    {
        field[ligne][j] = 0;
    }
    
}
//on dessine le champs de jeu 
void draw_field()
{
    cout << "+";

    for (int i = 0; i < HEIGTH; ++i)
    {
        cout << "-";
    }

    cout << "+\r\n";

    for (int i = 0; i < HEIGTH; ++i)
    {
        cout << "|";

        for (int j = 0; j < WIDTH; ++j)
        {
            draw_point(field[i][j]);
            
        }

        cout << "|";
        cout << "\r\n";   //ncures
    }

    cout << "+";

    for (int i = 0; i < HEIGTH; ++i)
    {
        cout << "-";
    }

    cout << "+\r\n";
    cout<<"score: "<<score<<endl;
    cout<<"'r' to rotate pieces"<<endl;
    cout<<"'a' to go right"<<endl;
    cout<<"'d' left"<<endl;
    cout<<" 2 type of pices with their rotations, realised as bool items[2][4][4][4] "<<endl;
    cout<<"it random and rotation between the two types as items[choice][rotation] "<<endl;
    cout<<"The speed is increasing with every line done and score"<<endl;
}

void rotation_hadle(){
    if(rotation==0){
        items[0];
    }
    if(rotation==1){
        items[1];
    }
    if(rotation==2){
        items[2];
    }
    if(rotation==3){
        items[3];
    }

}



void process_keyboard()
{
    if (kbhit())
    {
        char c = getch();

        if (c == 'r')
            rotation = (rotation + 1) % 4;

        if (c == 'a' && item_x > 0)
            item_x--;

        if (c == 'd' && item_x < WIDTH)
            item_x++;
    }
}
    

//on le descend
void process_fall(int *y, int x, bool item[4][4])
{
    if (can_move_down(x, *y, item))
    {
        (*y)++;
        if(score>1){
            (*y)++;

        } //pointeur 
        
    }
}

//peut servir pour rajouter une fin et des niveaux 
bool check_exit(int x, int y) {
    if (y >= HEIGTH)
        return true;
    else
        return false;
}

//boucle principale
int main(){
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    

        generate_new_item();
        bool exit = false;
        do
{
    system("CLS");
    draw_field();

    remove_item_from_field(item_x, item_y,items[choice][rotation]);

    if (can_move_down(item_x, item_y, items[choice][rotation]))
    {
        item_y++;
    }
    else
    {
        // Le bloc reste fixé
        insert_item_to_field(item_x, item_y, items[choice][rotation], 1);

        // Nouveau bloc
        generate_new_item();
    }
    int ligne = points();

if (ligne != -1)
{
   remove_line(ligne); // suprime la ligne 
   score++; 
   
}
    process_keyboard();

    Sleep(300);

    insert_item_to_field(item_x, item_y, items[choice][rotation], 1);

} while (!exit);
       
    
    return 0;
}
