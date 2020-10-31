//サーボライブラリ
#include <Servo.h>
//累乗計算のためのmath.h
#include <math.h>
//抵抗は７セグが1kΩ,圧電スピーカーが200Ω
//ボタンピン const←後で値変更できない
const int BTN_SELECT_PIN = 12;
const int BTN_DONE_PIN = 13;
const int SPEAKER_PIN = 3;
//7セグ用,a~dpまでは7セグの特定位置に該当
const int a = 7;
const int b = 6;
const int c = 5;
const int d = 11;
const int e = 10;
const int f = 8;
const int g = 9;
const int dp = 4;
//
// サーボのピン番号
//茶色　GND
//赤は　5V
//オレンジが下記ピン
const int SERVO_PIN = 2;
//サーボのインスタンス
Servo servo;




//スタート音再生用
void startsound(void) {
  tone(SPEAKER_PIN, 392, 300);//ソ
  delay(300);
  tone(SPEAKER_PIN, 349, 300);//ファ
  delay(300);
}

//選択音再生用
void selectsound(void) {
  tone(SPEAKER_PIN, 330, 300);//ミ
  delay(300);
}
//終了音再生用
void endsound() {
  //人形の夢と目覚め
  tone(SPEAKER_PIN, 392, 300);//ソ
  delay(300);
  tone(SPEAKER_PIN, 349, 300);//ファ
  delay(300);
  tone(SPEAKER_PIN, 330, 600);//ミ-
  delay(600);
  tone(SPEAKER_PIN, 392, 300);//ソ
  delay(300);
  tone(SPEAKER_PIN, 523, 300);//ド
  delay(300);
  tone(SPEAKER_PIN, 494, 600);//シ-
  delay(600);
  tone(SPEAKER_PIN, 392, 300);//ソ
  delay(300);
  tone(SPEAKER_PIN, 587, 300);//レ
  delay(300);
  tone(SPEAKER_PIN, 523, 800);//ドー
  delay(600);
  tone(SPEAKER_PIN, 659, 900);//ミー
  delay(1200);
  tone(SPEAKER_PIN, 523, 300);//ド
  delay(300);
  tone(SPEAKER_PIN, 494, 300);//シ
  delay(300);
  tone(SPEAKER_PIN, 440, 600);//ラー
  delay(600);
  tone(SPEAKER_PIN, 698, 300);//ファ
  delay(300);
  tone(SPEAKER_PIN, 587, 300);//レ
  delay(300);
  tone(SPEAKER_PIN, 523, 600);//ドー
  delay(600);
  tone(SPEAKER_PIN, 494, 600);//シー
  delay(600);
  tone(SPEAKER_PIN, 523, 1000);//ドー
  delay(300);
}


//1桁セグメントLED表示用関数---------------------------------
//display number1
void display1(void)
{
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
}
//display E
void displayE(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(d, HIGH);
}

//display F
void displayF(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(e, HIGH);
}

//display S
void displayS(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
}
//display A
void displayA(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(e, HIGH);
}
//display C
void displayC(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(e, HIGH);
}
//display dp
void displaydp(void)
{
  digitalWrite(dp, HIGH);
}
//display number2
void display2(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(d, HIGH);
}
// display number3
void display3(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
}
// display number4
void display4(void)
{
  digitalWrite(f, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);

}
// display number5
void display5(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
}
// display number6
void display6(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
}
// display number7
void display7(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
}
// display number8
void display8(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
}
void clearDisplay(void)
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(g, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
}
void display9(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(f, HIGH);
}
void display0(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
}
void displayClear(void) {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, LOW);
}
//1桁セグメントLEDGER表示用ここまで----------------------------------------




//ボタン読み取り→代入関数
int btn_record(void) {
  Serial.println("start btn_record");
  displayS;//セレクトしてのS
  int value;
  int time_count;
  int  time_decide = 60000;
  //ボタン入力の値代入用変数
  int time_select = 0;

  //10秒ループ
  for (time_count = 0; time_count < 100 ; time_count++) {
    //ボタン読み取り
    value = digitalRead( BTN_SELECT_PIN );
    //出力(シリアルモニタ)
    Serial.println( value );
    //変数代入 スイッチ押されると0になるので
    if (value == 0) {
      time_select += 1;
      selectsound();

      Serial.println("add");
      Serial.println( time_select );
      //ボタン押した回数でモード変更
      displayClear();
      switch (time_select) {
        //case0は押さなかった場合
        case 0:
          //60分
          display6();
          //          time_decide = 3600000;
          time_decide = 360;
          break;
        case 1:
          //30分
          display3();
          //          time_decide = 1800000;
          time_decide = 180;
          break;
        case 2:
          //10分 ↓はミリ秒で送る
          display1();
          //          time_decide = 600000;
          time_decide = 60;
          break;
        case 3:
          //90分
          display9();
          //          time_decide = 5400000;
          time_decide = 540;
          break;
        default:
          //１分
          displayA();
          //          time_decide = 60000;
          time_decide = 6;
          break;
      }
    }
    delay(100);
  }
  displayClear();

  //  displayC;
  return time_decide;
}


//サーボ動作用
void run_servo(int time_decided) {
  Serial.println("start run_servo");

  double waru;
  Serial.println("selected_time");
  Serial.println(time_decided * pow(10, 4));
  waru = time_decided * pow(10, 4) / 180;
  Serial.println("strat_timer");
  Serial.println(waru);
  for (int time_diff = 180; time_diff > 0; time_diff -= 2) {
    servo.write(time_diff);
    delay(waru * 2);

  }

}



//初期化関数
void setup() {
  //起動表示
  displayF();
  startsound();

  //サーボモーターを動かす
  servo.attach(SERVO_PIN);
  servo.write(0);
  delay(1000);

  //ボタン関係の準備
  pinMode( BTN_SELECT_PIN, INPUT_PULLUP );
  pinMode( BTN_DONE_PIN, INPUT_PULLUP );
  //↑INPUT_PULLUP引数に入れるだけで、抵抗不要で安定化できる！

  //シリアルモニタ準備
  Serial.begin( 9600 );
  Serial.println( "serial start" );

  //起動音＋起動確認数字表示
  int test;
  test = btn_record();
  delay(2000);
  Serial.println( "runned btn_record" );
  Serial.println(test);
  displayClear;
  delay(1000);
  displaydp;
  run_servo(test);
  Serial.println( "runned run_servo" );
  displayClear();
  displayE();
  endsound();
  displayClear();
}

void loop() {
}
