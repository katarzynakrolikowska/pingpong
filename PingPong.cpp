//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PingPong.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"                                                                                                                      //---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PingPong.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int invisibleZoneStartLeft, invisibleZoneEndLeft;
int ballStartGameLeft = 490, ballStartGameTop = 250;
int ballVerticalMovePerTime, ballHorizontalMovePerTime;
char whoWonLastRound = {0};
int pointsPaddleL = 0, pointsPaddleR = 0;
int amountOfBallBouncing = 0;

void bounceBallFromPaddleCenter(){
    Form1 -> moveBall -> Interval = 15;
    if(ballHorizontalMovePerTime > 0)
        ballHorizontalMovePerTime += 1;
    else ballHorizontalMovePerTime -=1;
}

void makeBallFaster(){
    if(amountOfBallBouncing % 4 == 0){
        if(Form1 -> moveBall -> Interval > 15){
            Form1 -> moveBall -> Interval--;
        }
    }
}

void setBallAtGameStart(){
    if(whoWonLastRound == 'P'){
        ballVerticalMovePerTime = 8, ballHorizontalMovePerTime = -10;
    }else if(whoWonLastRound == 'L') {
        ballVerticalMovePerTime = -8, ballHorizontalMovePerTime = 10;
    }else{
        ballVerticalMovePerTime = 8, ballHorizontalMovePerTime = 10;
    }
}

void startGame(){
    amountOfBallBouncing = 0;
    invisibleZoneStartLeft = 480;
    invisibleZoneEndLeft = 520;
    setBallAtGameStart();
    Form1 -> moveBall -> Interval = 20;
    Form1 -> ball -> Left = ballStartGameLeft;
    Form1 -> ball -> Top = ballStartGameTop;
    Form1 -> ball -> Visible = true;
    Form1 -> ButtonNewGame -> Visible = false;
    Form1 -> BitBtnNextRound -> Visible = false;
    Form1 -> whosePoint -> Visible = false;
    Form1 -> result -> Visible = false;
    Form1 -> bouncingAmount -> Visible = false;
    Form1 -> moveBall -> Enabled = true;
}

void startNewGame(){
    pointsPaddleL = 0;
    pointsPaddleR = 0;
    whoWonLastRound = '0';
    startGame();
}

void displayResults(){
    Form1 -> moveBall -> Enabled = false;
    Form1 -> ball -> Visible = false;
    if(whoWonLastRound == 'P'){
        Form1 -> whosePoint -> Caption = "Punkt dla gracza prawego >";
        Form1 -> BitBtnNextRound -> Caption = "< NastÍpna runda";
    }else{
        Form1 -> whosePoint -> Caption = "< Punkt dla gracza lewego";
        Form1 -> BitBtnNextRound -> Caption = "NastÍpna runda >";
    }
    Form1 -> whosePoint -> Visible = true;
    Form1 -> result -> Caption = IntToStr(pointsPaddleL) + ":" + IntToStr(pointsPaddleR);
    Form1 -> result -> Visible = true;
    Form1 -> bouncingAmount -> Caption = "IloúÊ odbiÊ: " + IntToStr(amountOfBallBouncing);
    Form1 -> bouncingAmount -> Visible = true;
    Form1 -> BitBtnNextRound -> Visible = true;
    Form1 -> ButtonNewGame -> Visible = true;
}

void makeBallInvisible(){

        if((Form1 -> ball -> Left + Form1 -> ball -> Width / 2 > invisibleZoneStartLeft) &&
            (Form1 -> ball -> Left + Form1 -> ball -> Width / 2 < invisibleZoneEndLeft))
            Form1 -> ball -> Visible = false;
        else Form1 -> ball -> Visible = true;

}

void extendInvisibleZone(){
    if(amountOfBallBouncing < 50){
        invisibleZoneStartLeft--;
        invisibleZoneEndLeft++;
    }
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner){
}
//---------------------------------------------------------------------------
void __fastcall TForm1::moveUpLeftTimer(TObject *Sender){
    //move up left paddle
    if(paddleL -> Top > 10) paddleL -> Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::moveDownLeftTimer(TObject *Sender){
    //move down left paddle
     if(paddleL -> Top + paddleL -> Height < background -> Top + background -> Height - 10)
        paddleL -> Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift){
    if(Key == 'A') moveUpLeft -> Enabled = true;
    if(Key == 'Z') moveDownLeft -> Enabled = true;
    if(Key == VK_UP) moveUpRight -> Enabled = true;
    if(Key == VK_DOWN) moveDownRight -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift){
    if(Key == 'A') moveUpLeft -> Enabled = false;
    if(Key == 'Z') moveDownLeft -> Enabled = false;
    if(Key == VK_UP) moveUpRight -> Enabled = false;
    if(Key == VK_DOWN) moveDownRight -> Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::moveUpRightTimer(TObject *Sender){
    //move up right paddle
    if(paddleR -> Top > 10) paddleR -> Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::moveDownRightTimer(TObject *Sender){
    //move down right paddle
    if(paddleR -> Top + paddleR -> Height < background -> Top + background -> Height - 10)
        paddleR -> Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender){
    ShowMessage("Witaj w grze PingPong.\n\n"
    "Lewy gracz steruje wciskajπc klawisze A oraz Z.\n"
    "Prawy gracz steruje wciskajπc strza≥ki do gÛry i w dÛ≥.\n\n"
    "Dla urozmaicenia zabawy:\n"
    "Kiedy odbijesz pi≥kÍ na úrodku paletki, wÛwczas zmienisz jej kπt odbicia i pi≥ka przyúpieszy.\n"
    "Im d≥uøej odbijasz, tym pi≥ka szybciej przemieszcza siÍ.\n"
    "Moøesz dowolnie zmieniaÊ pole gry.\n\n"
    "Mi≥ej zabawy!");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::moveBallTimer(TObject *Sender){
    ball -> Left -= ballHorizontalMovePerTime;
    ball -> Top += ballVerticalMovePerTime;
    makeBallInvisible();
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
            //bounce from center of left paddle
            if((paddleL -> Top + paddleL -> Height / 2 >= ball -> Top) &&
                (paddleL -> Top + paddleL -> Height / 2 <= ball -> Top + ball -> Height))
                bounceBallFromPaddleCenter();
            else makeBallFaster();
        ballHorizontalMovePerTime = -ballHorizontalMovePerTime;
        amountOfBallBouncing ++;
        extendInvisibleZone();
     }
    // left paddle lose
    else if(ball -> Left <= paddleL -> Left + paddleL -> Width){
         whoWonLastRound = 'P';
         pointsPaddleR ++;
         displayResults();
    }

    //bounce from right paddle
    if((ball -> Top + ball -> Height - 5 >= paddleR -> Top) &&
    (ball -> Top - 5 <= paddleR -> Top + paddleR -> Height) &&
    (ball -> Left + ball -> Width >= paddleR -> Left)){
        //bounce from center of right paddle
        if((paddleR -> Top + paddleR -> Height / 2 >= ball -> Top) &&
            (paddleR -> Top + paddleR -> Height / 2 <= ball -> Top + ball -> Height))
            bounceBallFromPaddleCenter();
        else makeBallFaster();
    ballHorizontalMovePerTime = -ballHorizontalMovePerTime;
    amountOfBallBouncing ++;
    extendInvisibleZone();
    }
    //right paddle lose
    else if(ball -> Left + ball -> Width >= paddleR -> Left){
        whoWonLastRound = 'L';
        pointsPaddleL ++;
        displayResults();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonNewGaClick(TObject *Sender){
    if(whoWonLastRound == 'P' || whoWonLastRound == 'L'){
        if(Application -> MessageBox("Czy na pewno chcesz zaczπÊ od nowa?", "Potwierdü",
        MB_YESNO | MB_ICONQUESTION) == IDYES ){
            startNewGame();
        }
    }else{
        startNewGame();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtnNextRoundClick(TObject *Sender){
    startGame();
}
//---------------------------------------------------------------------------



