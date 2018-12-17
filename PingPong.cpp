//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PingPong.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int paddleLStartLeft = 50, paddleRStartLeft = 980, paddlesStartTop = 150;
int ballStartLeft = 470, ballStartTop = 320;
int ballVerticalMovePerTime, ballHorizontalMovePerTime;
char whoWon = {0};
int pointsPaddleL = 0, pointsPaddleR = 0;
int amountOfBallBouncing = 0;

void bounceBallFromPaddleCenter(){
    Form1 -> moveBall -> Interval = 15;
    ballHorizontalMovePerTime += 1;
}

void whoStartGame(){
    if(whoWon == 'P'){
        ballVerticalMovePerTime = 8, ballHorizontalMovePerTime = -8;
    }else if(whoWon == 'L') {
        ballVerticalMovePerTime = -8, ballHorizontalMovePerTime = 8;
    }else{
        ballVerticalMovePerTime = 8, ballHorizontalMovePerTime = 8;
    }
}

void startGame(){
    amountOfBallBouncing = 0;
    whoStartGame();
    Form1 -> moveBall -> Interval = 20;
    Form1 -> ball -> Left = 470;
    Form1 -> ball -> Top = 250;
    Form1 -> ball -> Visible = true;
    Form1 -> ButtonNewGame -> Visible = false;
    Form1 -> BitBtnNextRound -> Visible = false;
    Form1 -> whosePoint -> Visible = false;
    Form1 -> result -> Visible = false;
    Form1 -> bouncingAmount -> Visible = false;
    Form1 -> moveBall -> Enabled = true;
}

void displayResults(){
    Form1 -> moveBall -> Enabled = false;
    Form1 -> ball -> Visible = false;
    if(whoWon == 'P'){
        Form1 -> whosePoint -> Caption = "Punkt dla gracza prawego >";
        Form1 -> BitBtnNextRound -> Caption = "< Nastepna runda";
    }else{
        Form1 -> whosePoint -> Caption = "< Punkt dla gracza lewego";
        Form1 -> BitBtnNextRound -> Caption = "Nastepna runda >";
    }
    Form1 -> whosePoint -> Visible = true;
    Form1 -> result -> Caption = IntToStr(pointsPaddleL) + ":" + IntToStr(pointsPaddleR);
    Form1 -> result -> Visible = true;
    Form1 -> bouncingAmount -> Caption = "Ilosc odbic: " + IntToStr(amountOfBallBouncing);
    Form1 -> bouncingAmount -> Visible = true;
    Form1 -> BitBtnNextRound -> Visible = true;
    
    Form1 -> ButtonNewGame -> Visible = true;
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::moveUpLeftTimer(TObject *Sender)
{   //move up left paddle
    if(paddleL -> Top > 10) paddleL -> Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::moveDownLeftTimer(TObject *Sender)
{    //move down left paddle
     if(paddleL -> Top + paddleL -> Height < background -> Top + background -> Height - 10)
        paddleL -> Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 'A') moveUpLeft -> Enabled = true;
    if(Key == 'Z') moveDownLeft -> Enabled = true;
    if(Key == VK_UP) moveUpRight -> Enabled = true;
    if(Key == VK_DOWN) moveDownRight -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 'A') moveUpLeft -> Enabled = false;
    if(Key == 'Z') moveDownLeft -> Enabled = false;
    if(Key == VK_UP) moveUpRight -> Enabled = false;
    if(Key == VK_DOWN) moveDownRight -> Enabled = false;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::moveUpRightTimer(TObject *Sender)
{   //move up right paddle
    if(paddleR -> Top > 10) paddleR -> Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::moveDownRightTimer(TObject *Sender)
{
    //move down right paddle
    if(paddleR -> Top + paddleR -> Height < background -> Top + background -> Height - 10)
        paddleR -> Top += 10;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{

    //newgame ball position
    ball -> Left = ballStartLeft;
    ball -> Top = ballStartTop;
    //newgame paddles position
    paddleL -> Left = paddleLStartLeft;
    paddleL -> Top = paddlesStartTop;
    paddleR -> Left = paddleRStartLeft;
    paddleR -> Top = paddlesStartTop;

    ball -> Visible = true;
    moveBall -> Enabled = false;
    moveDownLeft -> Enabled = false;
    moveUpLeft -> Enabled = false;
    moveDownRight -> Enabled = false;
    moveUpRight -> Enabled = false;

    ButtonNewGame -> Caption = "Nowa gra";
    ButtonNewGame -> Visible = true;

    whosePoint -> Caption = "Zagrajmy w PingPonga!";
    whosePoint -> Visible = true;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::moveBallTimer(TObject *Sender)
{
    ball -> Left -= ballHorizontalMovePerTime;
    ball -> Top += ballVerticalMovePerTime;

    //bounce from bottom wall
    if(ball -> Top + ball -> Height >= background -> Height )
        ballVerticalMovePerTime = -ballVerticalMovePerTime;

    //bounce from top wall
    if(ball -> Top <= background -> Top )
        ballVerticalMovePerTime = -ballVerticalMovePerTime;

    //bounce from left paddle
    if((ball -> Top + ball -> Height / 2 >= paddleL -> Top) &&
        (ball -> Top + ball -> Height / 2 <= paddleL -> Top + paddleL -> Height) &&
        (ball -> Left <= paddleL -> Left + paddleL -> Width)){
            if((paddleL -> Top + paddleL -> Height / 2 >= ball -> Top) &&
                (paddleL -> Top + paddleL -> Height / 2 <= ball -> Top + ball -> Height))
                bounceBallFromPaddleCenter();
            ballHorizontalMovePerTime = -ballHorizontalMovePerTime;
            amountOfBallBouncing ++;
     }
    // left paddle lose
    else if(ball -> Left <= paddleL -> Left + paddleL -> Width){
         whoWon = 'P';
         pointsPaddleR ++;
         displayResults();
    }

    //bounce from right paddle
    if((ball -> Top + ball -> Height - 5 >= paddleR -> Top) &&
    (ball -> Top - 5 <= paddleR -> Top + paddleR -> Height) &&
    (ball -> Left + ball -> Width >= paddleR -> Left)){
        if((paddleR -> Top + paddleR -> Height / 2 >= ball -> Top) &&
            (paddleR -> Top + paddleR -> Height / 2 <= ball -> Top + ball -> Height))
            bounceBallFromPaddleCenter();
        ballHorizontalMovePerTime = -ballHorizontalMovePerTime;
        amountOfBallBouncing ++;
    }
    //right paddle lose
    else if(ball -> Left + ball -> Width >= paddleR -> Left){
        whoWon = 'L';
        pointsPaddleL ++;
        displayResults();
    }

}
//---------------------------------------------------------------------------



void __fastcall TForm1::ButtonNewGaClick(TObject *Sender)
{
    pointsPaddleL = 0; pointsPaddleR = 0;
    whoWon = '0';
    startGame();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::BitBtnNextRoundClick(TObject *Sender)
{
    startGame();
}
//---------------------------------------------------------------------------

