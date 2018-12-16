//---------------------------------------------------------------------------

#ifndef PingPongH
#define PingPongH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TShape *background;
    TShape *paddleL;
    TTimer *moveUpLeft;
    TTimer *moveDownLeft;
    TShape *paddleR;
    TTimer *moveUpRight;
    TTimer *moveDownRight;
    TImage *ball;
    TTimer *moveBall;
    TLabel *Label1;
    void __fastcall moveUpLeftTimer(TObject *Sender);
    void __fastcall moveDownLeftTimer(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall moveUpRightTimer(TObject *Sender);
    void __fastcall moveDownRightTimer(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall moveBallTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
