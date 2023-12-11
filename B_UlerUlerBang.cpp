#include <iostream>
#include <conio.h>
#include <windows.h>  
#include <ncurses/ncurses.h>

using namespace std;
int maxY, maxX;
int x, y;
char arah = 'd';
int score = 0;
int panjang = 1;
int ekor1[100], ekor2[100];
int fruitX, fruitY;
bool game = true;
int kolom = maxX/2; 
bool pilih;
char level;






void Welcome() {

	attron(COLOR_PAIR(1));

    
    mvprintw(LINES / 2 - 2, COLS / 2 - 20, "WW   WW  EEEEE  LL       CCCCC  OOO   MM   MM  EEEEE");
    mvprintw(LINES / 2 - 1, COLS / 2 - 20, "WW   WW  EE     LL      CC     OO  OO  MM   MM  EE");
    mvprintw(LINES / 2, COLS / 2 - 20, "WW W WW  EEEE   LL     CC      OO  OO  MM M MM  EEEE");
    mvprintw(LINES / 2 + 1, COLS / 2 - 20, "WW W WW  EE     LL      CC     OO  OO  MM   MM  EE");
    mvprintw(LINES / 2 + 2, COLS / 2 - 20, " W W W   EEEEE  LLLLL    CCCCC  OOO   MM   MM  EEEEE");
	mvprintw(19, 55, "TO OUR ULER ULER BANG <>");
    
    attroff(COLOR_PAIR(1));
}


void Tampilan(){
	attron(COLOR_PAIR(4));
	
	
	mvprintw(LINES/2,(COLS/2)-23, "Silahkan Pilih Level Yang anda mampu !");
	mvprintw((LINES/2)+1,(COLS/2)-8, "1. Mudah");
	mvprintw((LINES/2)+2, (COLS/2)-8, "2. Sedang");
	mvprintw((LINES/2)+3, (COLS/2)-8, "3. Susah");
	mvprintw((LINES/2)+4, (COLS/2)-23, "Silahkan Ketik angka 1 sampai 3 saja !");
	
	
	
	attroff(COLOR_PAIR(4));
	
}



void Console() {
    if (kbhit()) {
        switch (getch()) {
            case 'a': if(arah!='d')arah = 'a'; break;
            case 'w': if(arah!='s')arah = 'w'; break;
            case 's': if(arah!='w')arah = 's'; break;
            case 'd': if(arah!='a')arah = 'd'; break;
            case 'q': game = false; break;
        }
    }
}

void Draw() {
	attron(COLOR_PAIR(2));
    clear();
    WINDOW *win = newwin(maxY, maxX, 0, 0);
    
    refresh();
    box(win, 0, 0);
    wrefresh(win);

    mvprintw(y, x, "O");
    mvprintw(fruitY, fruitX, "#");

    for (int i = 0; i < panjang ; i++) {
        mvprintw(ekor2[i], ekor1[i], "-");
    }

    refresh();
//    Sleep(100);
	
	if(level=='1'){
		Sleep(80);
	}
    
    else if(level=='2'){
		Sleep(50);
	}
	else if(level=='3'){
		Sleep(10);
	}
	else{
		game=false;
		
	}
    
    attroff(COLOR_PAIR(2));
}




void Algorithm() {
    int prevX = ekor1[0];
    int prevY = ekor2[0];
    int prev2X, prev2Y;
    ekor1[0] = x;
    ekor2[0] = y;

    for (int i = 1; i < panjang ; i++) {
        prev2X = ekor1[i];
        prev2Y = ekor2[i];
        ekor1[i] = prevX;
        ekor2[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    if (arah == 'w') {
        y--;
    }
    if (arah == 's') {
        y++;
    }
    if (arah == 'a') {
        x--;
    }
    if (arah == 'd') {
        x++;
    }

    if (x == fruitX && y == fruitY) {
        fruitX = rand() % maxX;
        fruitY = rand() % maxY;
        score++;
        panjang++;
    }

    for (int i = 0; i < panjang; i++) {
        if (ekor1[i] == x && ekor2[i] == y) {
            game = false;
        }
    }

    
    if (x <= 0 || x >= maxX || y <= 0 || y >= maxY) {
        game = false;
    }
}

void setLevel() {
    Tampilan();
    level = getch(); 
    clear();
}

int main() {
   	
    
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    Welcome();
    refresh();
    getch();
    clear();
    
    
    start_color();
    init_pair(4, COLOR_RED, COLOR_BLACK);
    setLevel();
    noecho();
    curs_set(0);
    
    
	start_color();
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    noecho();  
    curs_set(0);  

    getmaxyx(stdscr, maxY, maxX);

    y = maxY / 2;
    x = maxX / 2;
    fruitX = rand() % maxX;
    fruitY = rand() % maxY;
	
	
	do {
        Draw();
		Console();
        Algorithm();
    } 
	while (game);
    clear();
	
	
    
    mvprintw((maxY/2)-1,(maxX/2)-15,"Score yang kamu dapatkan adalah : %d",score);
    refresh();
    Sleep(3000);
    mvprintw((maxY/2)-1,(maxX/2)-36,"Silahkan keluar, karna ini game limited edition, sekali seumur hidup");
    refresh();
    getch();
    endwin();

    return 0;
}
