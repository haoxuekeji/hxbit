#include "pxt.h"
#include <map>
#include <vector>
#include "ReceiverIR.h"
using namespace pxt;
typedef vector<Action> vA;

enum class Pins{
  P0=  3,
  P1=  2,
  P2=  1,
  P3=  4,
  P4=  5,
  P5=  17,
  P6=  12,
  P7=  11,
  P8=  18,
  P9=  10,
  P10= 6,
  P11= 26,
  P12= 20,
  P13= 23,
  P14= 22,
  P15= 21,
  P16= 16,
  P19= 0,
  P20= 30
};

enum class RemoteButton {
    //% blockId="Power" block="Power"
	  Power = 0x0,
    //% blockId="Up" block="Up"
	  Up = 0x1,
    //% blockId="Left" block="Left"
	  Left = 0x4,
    //% blockId="Right" block="Right"
	  Right = 0x6,
    //% blockId="Down" block="Down"
	  Down = 0x9,
    //% blockId="Light" block="Light"
	  Light = 0x2,
    //% blockId="BEEP" block="BEEP"
	  BEEP = 0x5,
    //% blockId="Plus" block="Plus"
	  Plus = 0xc,
    //% blockId="Minus" block="Minus"
	  Minus = 0xe,
    //% blockId="Tleft" block="Tleft"
	  TLeft = 0x8,
    //% blockId="Tright" block="TRight"
	  TRight = 0xA,
    //% blockId="NUM0" block="NUM0"
	  NUM0 = 0xD,
    //% blockId="NUM1" block="NUM1"
	  NUM1 = 0x10,
    //% blockId="NUM2" block="NUM2"
	  NUM2 = 0x11,
    //% blockId="NUM3" block="NUM3"
	  NUM3 = 0x12,
    //% blockId="NUM4" block="NUM4"
	  NUM4 = 0x14,
    //% blockId="NUM5" block="NUM5"
	  NUM5 = 0x15,
    //% blockId="NUM6" block="NUM6"
	  NUM6 = 0x16,
    //% blockId="NUM7" block="NUM7"
	  NUM7 = 0x18,
    //% blockId="NUM8" block="NUM8"
	  NUM8 = 0x19,
    //% blockId="NUM9" block="NUM9"
	  NUM9 = 0x1A,
};

//% color=50 weight=80
//% icon="\uf1eb"
namespace IR { 
  map<RemoteButton, vA> actions;
  map<RemoteButton, uint32_t> lastact;
  Timer tsb; 
  uint8_t buf[32];
  uint32_t now;
  ReceiverIR *rx;
  RemoteIR::Format fmt = RemoteIR::UNKNOWN;

  /**
  * button pushed.
  */
  //% blockId=ir_received_left_event
  //% block="on |%btn| button pressed"
  void onPressEvent(RemoteButton btn, Action body) {
    //if(actions.find(btn) == actions.end()) actions[btn] = new vector();
    actions[btn].push_back(body);
  }

  void cA(vA runner){for(int i=0;i<runner.size();i++){runAction0(runner[i]);} }

  void onReceivable(){
    int x = rx->getData(&fmt, buf, 32 * 8);
    if(actions.find((RemoteButton)buf[2]) == actions.end()) return;
    now = tsb.read_ms();
    if(now - lastact[(RemoteButton)buf[2]] < 100) return;
    lastact[(RemoteButton)buf[2]] = now;
    cA(actions[(RemoteButton)buf[2]]); 
  }

  void monitorIR(){
    while(1){
      while(rx->getState() != ReceiverIR::Received){ 
        uBit.sleep(50);
      }
      onReceivable();
    }
  }

  /**
  * initialises local variablesssss
  */
  //% blockId=ir_init
  //% block="connect ir receiver to %pin"
  void init(Pins pin){
    rx = new ReceiverIR((PinName)pin);
    tsb.start(); //interrupt timer for debounce
    create_fiber(monitorIR);
  }
}