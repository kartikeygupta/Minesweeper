/*Minesweeper v1.00
    Potential Upgrades:
        *Write code for self-generating mine-field.
        *Automatically open all those cells,  which are adjacent to surrounding cells and have mines values for them is zero.
*/
#include<iostream>
using namespace std;
//Begin class definition.
class cell
{
private:
    bool is_display, is_mine; // is_display - hide the contents of the cell or not, is_mine - whether the cell homes a mine or not
    int mines; //mines - number of mines in the  immediately adjacent cells.
public:
    cell()
    {
        is_display = false;
        is_mine = false;
        mines = 0;
    }
    bool check_disp()
    {
        return is_display;
    }
    bool check_mine() //Check for the presence of a mine in a cell
    {
        return is_mine;
    }
    void set_display() // sets cell visibility to true
    {
        is_display = true;
    }
    void set_mine() // sets a mine in the cell
    {
        is_mine = true;
    }
    void change_mine() // Increment the value of mines variable
    {
        mines++;
    }
    void display() //display the content of a grid
    {
        if(is_display)
            if(is_mine)
                cout << "*" <<"    ";
            else
                cout << mines <<"    ";
        else
            cout << " " << "    ";
    }
};
//End Class definition.
int mine_field[][2] = {{1, 3}, {3, 1}, {3, 6}, {7, 5}, {8, 4}, {7, 9}, {7, 6}, {8, 5}, {1, 9}, {4, 7}};
void disp_grid(cell grid[][10]) //Display the grid.
{
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            if (i==0&&j==0)
                cout << " " << "    ";
            else if (i==0&&j!=0)
                cout << j << "    ";
            else if (i!=0&&j==0)
                cout << i << "    ";
            else
                grid[i][j].display();
        }
        cout << endl << endl;
    }
}
void set_field(cell grid[][10]) //Generates mines and places them in the field
{
    for (int i=0; i<10; i++)
        grid[(mine_field[i][0])][(mine_field[i][1])].set_mine();
}
void show_mines(cell grid[][10]) //Displays all the mines in the field.
{
    for(int i=0; i<10; i++)
        grid[mine_field[i][0]][mine_field[i][1]].set_display();
}
void check(cell grid[][10], int i, int j) //The algorithm which calculates the number of mines surrounding the selected cell
{
    grid[i][j].set_display();
    for(int n=i-1; n<=i+1; n++)
        for(int m=j-1; m<=j+1; m++)
        {
            if(m==0||m==10||n==0||n==10||(n==i&&m==j))
                continue;
            else
                if(grid[n][m].check_mine())
                    grid[i][j].change_mine();
        }
}
/*void open_sesame(cell grid[][10]) //All cells are opened.
{
    for(int i=1; i<10; i++)
        for(int j=1; j<10; j++)
        {
            grid[i][j].set_display();
        }
}*/
/*void solved(cell grid[][10]) //Displays the solved field
{
    for(int i=1; i<10; i++)
        for(int j=1; j<10; j++)
        {
            grid[i][j].set_display();
            if(!grid[i][j].check_mine())
            {
                check(grid, i, j);
            }
        }
}*/
void time_delay(string S) //Gives certain strings that typing effect.
{
    for (int i=0; i<S.length(); i++)
    {
        cout << S[i];
        _sleep(75);
    }
}
void Welcome_screen()
{
    time_delay("Hello! Welcome to Minesweeper.");
    _sleep(600);
    time_delay(" I don't think we've met before.");
    _sleep(600);
    time_delay(" What is your name ?");
}
int main()
{
    cell grid[10][10];
    string name;
    int x, y, blocks_filled = 0;
    bool game = true;
    set_field(grid);
    Welcome_screen();
    cout << endl << "Hi! My name is ";
    cin >> name;
    time_delay("Hi " + name + ". Let's play Minesweeper.");
    system("CLS");
    while(game)
    {
        if(blocks_filled==71||game==false)
        {
            break;
        }
        else
        {
            system("CLS");
            disp_grid(grid);
            cout << endl << endl;
            time_delay("Enter your choice, " + name + ".");
            cout << endl;
            cout << "Number of cells opened : " << blocks_filled << endl;
            cout << "Number of cells remaining : " << 71 - blocks_filled << endl << endl;
            cout << "Enter the x coordinate : ";
            cin >> x;
            cout << "Enter the y coordinate : ";
            cin >> y;
            if(x<1||x>9)
            {
                cout << "You have entered an invalid x coordinate";
                if(y<1||y>9)
                {
                    cout << " and an invalid y coordinate";
                }
                cout << ".";
                system("PAUSE");
                continue;
            }
            if(y<1||y>9)
            {
                cout << "You have entered an invalid y coordinate.";
                system("PAUSE");
                continue;
            }
            if(grid[x][y].check_disp())
            {
                cout << "You have already entered this value before. Please enter a different value.";
                system("PAUSE");
                continue;
            }
            else
            {
                grid[x][y].set_display();
                if(grid[x][y].check_mine())
                {
                    game = false;
                    break;
                }
                else
                {
                    blocks_filled++;
                    check(grid, x, y);
                }
            }
        }
    }
    show_mines(grid);
    if(game)
    {
        system("CLS");
        disp_grid(grid);
        cout << endl << endl;
        cout <<  "Number of cells opened : " << blocks_filled << endl << endl;
        time_delay("Congratulations, " + name + "! You have survived the mine field!.");
    }
    else
    {
        system("CLS");
        disp_grid(grid);
        cout << endl << endl;
        time_delay("Sorry, " + name + ". You just stepped on a mine.");
    }
    return 0;
}
