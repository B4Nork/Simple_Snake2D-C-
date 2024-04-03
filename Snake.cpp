#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

void idzdoxy(int x, int y){
	
	HANDLE hCon;
	COORD dwPos;
	
	dwPos.X=x;
	dwPos.Y=y;
	
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon,dwPos);
	
}


int main(){
	srand(time(NULL));
	int width, high;
    char pole[35][35];
	int i , j , ile=0, szybkosc;
	int zledanewidth , zledanehigh;
	int pXw , pYw; //pozycja weza X i Y
	int pXj , pYj; //pozycja jedzenia X i Y
	int hXw[10000] , hYw[10000]; //historia pozycji X i Y weza
	int dlw=3;  //dlugosc weza
	int button;
	char way='r';//t-top, r-right, l-left, d-down
	char snake=219, hsnake=245, eat=207 , lt=201,ld=200,rt=187,rd=188,k=186,f=205; //narozniki i krawedzie	
	cout << "Witaj w grze snake!\n";
	cout << "Streowanie strzalki\n";
	cout << "Podaj szybkosc od 1 (im wiecej tym szybszy waz)\n";
	cin  >> szybkosc;
	width=0;
	high=0;
	
	while(width<5 || width>25){
		cout << "Podaj szerokosc planszy od 5 do 25.\n";
	    cin >> width;
	    if(width<5 || width>25){
	    	cout << "Podales zle dane sproboj jeszcze raz.\n";
	    	zledanewidth++;
		}
		if(zledanewidth==5){
			cout << "Nie rozumiesz co znaczy od 5 do 25!!! Masz ostania probe na dobre dane.\n";
		}
		if(zledanewidth==6){
			cout << "Nie chcesz sam podac to wymiar szerokosci bedzie wynosil 20.\n";
			width=20;
		}
	}
	while(high<5 || high>25){
		cout << "Podaj wysokosc planszy 5 do 25.\n";
	    cin >> high;
	    if(high<5 || high>25){
	    	cout << "Podales zle dane sproboj jeszcze raz.\n";
	    	zledanehigh++;
		}
		if(zledanehigh==5){
			cout << "Nie rozumiesz co znaczy od 5 do 25!!! Masz ostania probe na dobre dane.\n";
		}
		if(zledanehigh==6){
			cout << "Nie chcesz sam podac to wymiar szerokosci bedzie wynosil 20\n";
			high=20;
		}
	}
	
	for(i=0; i<high; i++){
		for(j=0; j<width; j++){
			pole[i][j]='p';//puste pola
		}
	}
	
	pXw=rand()%high;
	pYw=rand()%width;
	
	pole[pXw][pYw]='g';// glowa weza
	
	do{
		pXj=rand()%high;
	    pYj=rand()%width;
	}while(pole[pXj][pYj]!='p');
	
	pole[pXj][pYj]='j';//jedzenie
	
	getch();
	
	system("cls");
	
	
	for(;;){
	    
	    ile++;
	    hXw[ile]=pXw;
	    hYw[ile]=pYw;
	    
	    
		idzdoxy(0,0);
	
	    //granica gorna
	    cout << lt;
	    for(i=0; i<width; i++){
      	    cout << f << f;
	    }
	    cout << rt;
        //boki
        for(i=0; i<high; i++){
        	cout << endl << k;
    	    for(j=0; j<width; j++){
    		    if(pole[i][j]=='p') cout << "  ";
    		    if(pole[i][j]=='g') cout << hsnake << hsnake;
    		    if(pole[i][j]=='w') cout << snake << snake;
    		    if(pole[i][j]=='j') cout << eat << eat;
		        }
		    cout << k;
	    }

        //granica dol
	    cout << endl;
	    cout << ld;
    	for(i=0; i<width; i++){
	    	cout << f << f;
	    }
	    cout << rd;
	    
	    Sleep(1000/szybkosc);
	    
	    if(kbhit()){ // nacisne klawisz wykonaj instrukcje if
	    	button=getch();
	    	if(button==224) button+=getch();
	    	
	    	if(button==296 && way=='r' || button==296 && way=='l') way='t';
	    	if(button==304 && way=='r' || button==304 && way=='l') way='d';
	    	if(button==299 && way=='t' || button==299 && way=='d') way='l';
	    	if(button==301 && way=='t' || button==301 && way=='d') way='r';
		}
	    
	    if(way=='t') pXw--;
	    if(way=='d') pXw++;
	    if(way=='l') pYw--;
	    if(way=='r') pYw++;
	    
	    
	    if(pole[pXw][pYw]=='w'){
	    	cout << "\nKONIEC";
	    	getch();
	    	break;
		}
		
	    if(pole[pXw][pYw]=='j'){
	    	do{
	    		pole[hXw[ile-dlw]][hYw[ile-dlw]]='p';
		        pXj=rand()%high;
	            pYj=rand()%width;
	        }while(pole[pXj][pYj]!='p');
	    dlw++;
	    pole[pXj][pYj]='j';
	    }else{
	    	if(pole[hXw[ile-dlw]][hYw[ile-dlw]]!=pole[pXj][pYj]){
	    		pole[hXw[ile-dlw]][hYw[ile-dlw]]='p';
			}
		}
	    
	    //przenikanie scian
	    if(pXw==high) pXw=0;
	    if(pXw==-1) pXw=high;
	    if(pYw==width) pYw=0;
	    if(pYw==-1) pYw=width;
	    pole[pXw][pYw]='g';
	    pole[hXw[ile]][hYw[ile]]='w';
	    
	    
	}	
	
	cout << "\nTwoja dlugosc weza to:" << dlw+1;
	getchar();
	getchar();
}



