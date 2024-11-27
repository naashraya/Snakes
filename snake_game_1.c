#include<stdio.h>
#include<conio.h>     //getch(), kbhit()
#include<stdlib.h>    //system(cls), system(pause)
#include<windows.h>   //Beep()

void instruction();    //to show instructions to play game
void game_enter();     //views first screen for game
void level_choose();   //to choose level
void main_loop();      //looping of functions of game are done here
void setup();          //provides initial position for fruit, snake head, etc
void input_part();     //takes input from user i.e. a, s, w, d, x
void logic_part();     //decides result for input provided, game rules creation i.e. gameover conditions
void draw();           //display part of the game i.e snake's position, score, walls etc are shown
void sound();          //sound for gameover 
void game_over();      //views gameover page and also play again function
void file_input();     //put data of highscore into the file 
void file_output();    //take data of highscore out of the file

int width = 40, height= 30, level = 0, option_1= 0;
int x, y, m, n, i, j, k, fruitX, fruitY, score, game_state, flag, highscore, option_2;
int tailX[100], tailY[100];
int CountTail=0;

int main(){
    game_enter();
    return 0;
}

void instruction(){
    printf("Game Controls: \na = move left \ns = move down \nd = move right \nw = move up \nh = home \np = pause game \nx = quit game \n");
    printf("Alert! Backward movement is not allowed. \nNow press any key to return to home");
    getch();
    game_enter();
}

void game_enter(){
    char a, b, c;
    system("cls");
    for (i= 0; i<height; i++){
        for (j= 0; j<width; j++){
            if (i== 0 || i== height-1 || j== 0 || j == width-1){
                printf("*");
            }
            else if (i==height/4 && j==width/3){
                printf("Snake Game");
                j+=9; 
            }      
            else if(i==height/3+1 && j==width/4){
                if (option_1 == 0){
                    printf("-> Level");
                    j+=7;
                }
                else{
                    printf("Level");
                    j+=4;
                }
            }
            else if(i==height/2 && j==width/4){
                if (option_1 == 1){
                    printf("-> Instructions");
                    j+=14;
                }
                else{
                    printf("Instructions");
                    j+=11;
                }
            }
            else if(i==height/2+4 && j==width/4){
                if (option_1 == 2){
                    printf("-> Exit");
                    j+=6;
                }
                else{
                    printf("Exit");
                    j+=3;
                }
            }
            else
                printf(" ");
        }
        printf("\n");
    }
    if (option_1 == 0){
        a = getch();
        if (a == 's'){
            option_1  = 1;
            game_enter();
        } 
        else if (a == 'w'){
            option_1  = 2;
            game_enter();
        } 
        else{
            level_choose();
        }
    }  
    else if (option_1 == 1){
        b = getch();
        if (b == 'w'){
            option_1  = 0;
            game_enter();
        } 
        else if (b == 's'){
            option_1  = 2;
            game_enter();
        } 
        else{
            instruction();
        }
    }
    else{
        c = getch();
        if (c == 'w'){
            option_1  = 1;
            game_enter();
        } 
        else if (c == 's'){
            option_1  = 0;
            game_enter();
        } 
        else{
            game_state = 1;
        }
    }
}

void level_choose(){
    system("cls");
    for (i= 0; i<height; i++){
        for (j= 0; j<width; j++){
            if (i== 0 || i== height-1 || j== 0 || j == width-1){
                printf("*");
            }
            else if (i==height/4 && j==width/3){
                printf("Snake Game");
                j+=9; 
            }      
 
            else if(i==height/2 && j==width/4){
                printf("Choose Level:");
                j+=12;
            }
            else if(i==height/2+2 && j==width/4){
                if (level == 0){
                    printf("-> Easy");
                    j+=6;
                }
                else{
                    printf("Easy");
                    j+=3;
                }
            }
            else if(i==height/2+4 && j==width/4){
                if (level == 0){
                    printf("Hard");
                    j+=3;
                }
                else{
                    printf("-> Hard");
                    j+=6;
                }
            }
            else
                printf(" ");
        }
        printf("\n");
    }
    if (level == 0){
        if (getch() == 's'){
            level = 1;
            level_choose();
        } 
        else{
            main_loop();
        }
    }  
    else{
        if (getch() == 'w'){
            level = 0;
            level_choose();
        } 
        else{
            main_loop();
        }
    }
}

void main_loop(){
    setup();
    while(!game_state){ // loop until game_state is not equal to 1
        draw();
        input_part();
        logic_part();
        if (level == 0){
            for (m= 0; m<10000; m++){        // to make code run slower to decrease the speed of snake
                for (n= 0; n<10000; n++){

                }
            }
        }
        else{
            for (m= 0; m<1000; m++){        // to make code run slower to decrease the speed of snake
                for (n= 0; n<1000; n++){

                }
            }            
        }
    }
    sound();
    game_over();
}

void setup(){
    game_state = 0;
    x = height/2;
    y = width/2;
    option_2 = 0;
    label1:
    fruitX = rand()%(height-1);
    if (fruitX==0){
        goto label1;
    }
    label2:
    fruitY = rand()%(width-1);
    if (fruitY==0){
        goto label2;
    }
    file_output(); //to get highscore
    score =0;
    CountTail =0;
}

void input_part(){
    if (kbhit()){
        switch(getch()){
            case 'a':  //aswd
                flag = 1;
                break;
            case 's':
                flag = 2;
                break;
            case 'd':
                flag = 3;
                break;
            case 'w':
                flag = 4;
                break;
            case 'x':
                game_state= 1;
                break;
            case 'p':
                system("pause");
                break;
            case 'h':
                game_enter();
                break;
        }
    }
}

void logic_part(){
    int prevX= tailX[0];
    int prevY= tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (i= 1; i<CountTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;

    }
    switch(flag){
        case 1:
            y--;
            break;
        case 2:
            x++;
            break;
        case 3:
            y++;
            break;
        case 4:
            x--;
            break;
        default:
            break;
    }
    if (x<=0 || x>=height-1 || y<=0 || y>=width-1){
        game_state =1;
    }
    for (i=0; i<CountTail; i++){
        if (x==tailX[i] && y== tailY[i]){
            game_state = 1;
        }
    }
    if (x == fruitX && y==fruitY){
        label3:
        fruitX = rand()%(height-1);
        if (fruitX==0){
            goto label3;
        }
        label4:
        fruitY = rand()%(width-1);
        if (fruitY==0){
            goto label4;
        }
        score+=1;
        CountTail++;
        if (score>highscore){
            highscore++;
            file_input();
        }
    }
}

void draw(){
    system("cls");  //resets screen
    for (i = 0; i<height; i++){
        for (j= 0; j<width; j++){
            if (i== 0 || i== height-1  || j== 0 || j == width-1){
                printf("*");
            }
            else{
                if(i==x && j==y){
                    printf("O");
                }
                else if(i==fruitX && j==fruitY){
                    printf("%c", 219);
                }
                else{
                    int ch=0;
                    for (k = 0; k < CountTail; k++){
                        if (i == tailX[k] && j== tailY[k]){
                            printf("o");
                            ch = 1;
                        }
                    }
                    if (ch== 0){
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }
    printf("Level: ");
    if (level == 0){
        printf("Easy\n");
    }
    else{
        printf("Hard\n");
    }
    printf("SCORE = %03d", score);
    printf("\nHIGHSCORE = %03d\n", highscore);

}

void sound(){
    Beep(5000, 100);
    Sleep(50);
    Beep(1200, 100);
    getch();
}

void game_over(){
    system("cls");
    for (i= 0; i<height;i++){
        for (j= 0; j<width; j++){
            if (i== 0 || i== height-1 || j== 0 || j == width-1){
                printf("*");
            }
            else if (i==height/6 && j==width/3){
                printf("Game Over");
                j+=8;
            }
            else if(i==height/4 && j== width/4){
                printf("Your score: %03d", score);
                j+=14;
            }
            else if(i==height/4+1 && j==width/4){
                    printf("Highscore: %03d", highscore);
                    j+=13;
            }
            else if(i==height/2+2 && j==width/4){
                if (option_2 == 0){
                    printf("-> Play again");
                    j+=12;
                }
                else{
                    printf("Play again");
                    j+=9;
                }
            }
            else if(i==height/2+5 && j==width/4){
                if (option_2 == 0){
                    printf("Home");
                    j+=3;
                }
                else{
                    printf("-> Home");
                    j+=6;
                }
            }
            else
                printf(" ");
        }
        printf("\n");
    }
    if (option_2 == 0){
        if (getch() == 's'){
            option_2 = 1;
            game_over();
        }
        else{
            main_loop();
        }
    }
    else{
        if (getch() == 'w'){
            option_2 = 0;
            game_over();
        }  
        else{
            game_enter();
        }     
    }

}

void file_input(){
    FILE *fp;
    fp = fopen("highscore.txt", "w");
    fprintf(fp, "%d", highscore);
    fclose(fp);
}

void file_output(){
    FILE *fp;
    fp = fopen ("highscore.txt", "r");
    fscanf(fp, "%d", &highscore);
    fclose(fp);
}



