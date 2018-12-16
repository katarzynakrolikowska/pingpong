//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PingPong.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int paddleLStartLeft = 50, paddleRStartLeft = 850, paddlesStartTop = 150;
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
    //newgame paddles position
    paddleL -> Left = paddleLStartLeft;
    paddleL -> Top = paddlesStartTop;
    paddleR -> Left = paddleRStartLeft;
    paddleR -> Top = paddlesStartTop;
}
//---------------------------------------------------------------------------

