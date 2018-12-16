//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PingPong.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int paddleLStartLeft = 50, paddleRStartLeft = 850, paddlesStartTop = 150;
int ballStartLeft = 450, ballStartTop = 220;
int ballVerticalMovePerTime = 8, ballHorizontalMovePerTime = 8;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::moveUpLeftTimer(TObject *Sender)
{
    if(paddleL -> Top > 10) paddleL -> Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::moveDownLeftTimer(TObject *Sender)
{
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
{
    if(paddleR -> Top > 10) paddleR -> Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::moveDownRightTimer(TObject *Sender)
{
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
    if((ball -> Top + ball -> Height - 5 >= paddleL -> Top) &&
        (ball -> Top - 5 <= paddleL -> Top + paddleL -> Height) &&
        (ball -> Left <= paddleL -> Left + paddleL -> Width))
        ballHorizontalMovePerTime = -ballHorizontalMovePerTime;
    else if(ball -> Left <= paddleL -> Left + paddleL -> Width){
         moveBall -> Enabled = false;
         ball -> Visible = false;
    }

    //bounce from right paddle
    if((ball -> Top + ball -> Height - 5 >= paddleR -> Top) &&
        (ball -> Top - 5 <= paddleR -> Top + paddleR -> Height) &&
        (ball -> Left + ball -> Width >= paddleR -> Left))
        ballHorizontalMovePerTime = -ballHorizontalMovePerTime;
    else if(ball -> Left + ball -> Width >= paddleR -> Left){
         moveBall -> Enabled = false;
         ball -> Visible = false;
    }



}
//---------------------------------------------------------------------------





