#define encoder1PinA  18    //motor 1
#define encoder1PinB  19
long unsigned int encoder1Pos = 1000;
#define encoder2PinA  2    //motor 2
#define encoder2PinB  3
long unsigned int encoder2Pos = 1000;
#define encoder3PinA  20    //motor 3
#define encoder3PinB  21
long unsigned int encoder3Pos = 1000;

volatile int cps1 = 0;
volatile int cps2 = 0;
volatile int cps3 = 0;

//motor intializations
const int inAPin1 = 30;
const int PWMPin1 = 9;

const int inAPin2 = 32;
const int PWMPin2 = 8;

const int inAPin3 = 34;
const int PWMPin3 = 7;

int i = 0;                            //used by timing ISR

int pwm1 = 0;
int cps1_des = 0;
double output1 = 0;

int pwm2 = 0;
int cps2_des = 0;
double output2 = 0;

int pwm3 = 0;
int cps3_des = 0;
double output3 = 0;

int temp1 = 1000;
int temp3 = 1000;
int temp2 = 1000;

//**************************************
//*********SETUP FUNCTION***************
//**************************************
void setup() {
  // motor setup
  pinMode(inAPin1, OUTPUT);
  pinMode(PWMPin1, OUTPUT);

  pinMode(inAPin2, OUTPUT);
  pinMode(PWMPin2, OUTPUT);

  pinMode(inAPin3, OUTPUT);
  pinMode(PWMPin3, OUTPUT);


  //encoder setup
  pinMode(encoder1PinA, INPUT);
  digitalWrite(encoder1PinA, HIGH);
  pinMode(encoder1PinB, INPUT);
  digitalWrite(encoder1PinB, HIGH);
  attachInterrupt(digitalPinToInterrupt(2), doEncoder1, CHANGE);  // encoder pin on interrupt 2

  pinMode(encoder2PinA, INPUT);
  digitalWrite(encoder2PinA, HIGH);
  pinMode(encoder2PinB, INPUT);
  digitalWrite(encoder2PinB, HIGH);
  attachInterrupt(digitalPinToInterrupt(18), doEncoder2, CHANGE);  // encoder pin on interrupt 18

  pinMode(encoder3PinA, INPUT);
  digitalWrite(encoder3PinA, HIGH);
  pinMode(encoder3PinB, INPUT);
  digitalWrite(encoder3PinB, HIGH);
  attachInterrupt(digitalPinToInterrupt(20), doEncoder3, CHANGE);  // encoder pin on interrupt 18


  //Serial setup
  Serial.begin (9600);
}
//**************END OF SETUP FUNCTION****************************

int err_new1 = 0;
int err_old1 = 0;
int err_d11 = 0;
int err_d21 = 0;

int err_new2 = 0;
int err_old2 = 0;
int err_d12 = 0;
int err_d22 = 0;

int err_new3 = 0;
int err_old3 = 0;
int err_d13 = 0;
int err_d23 = 0;

// for PID
float adj = 1;
float Kp = 0.3;

int d1;                           // for direction of rotation of motors
int d2;
int d3;


void loop(){
}

//============== Motor Functions ================================
void M1( int cps1_des, int dir1)
{
  if (dir1 == 1)
  {
    digitalWrite(inAPin1, HIGH);
  }
  else if (dir1 == -1)
  {
    digitalWrite(inAPin1, LOW);
  }
  else if (dir1 == 0)
  {
    digitalWrite(inAPin1, LOW);
  }

  err_new1 = (cps1_des - cps1);                 // calc error in counts
  err_d21 = err_new1 - err_d11;
  err_new1 = (Kp * err_new1) + (0 * err_old1) + (0 * err_d21) ;

  output1 = adj * (1.4919 * (err_new1));      //converting counts to PWM

  if (output1 > 250)
    output1 = 250;
  else if (output1 < 10)
    output1 = 0;

  analogWrite(PWMPin1, output1);
  err_old1 = err_new1;
  err_d11 = err_old1;
}

void M2( int cps2_des, int dir2)
{
  if (dir2 == 1)
  {
    digitalWrite(inAPin2, LOW);
  }
  else if (dir2 == -1)
  {
    digitalWrite(inAPin2, HIGH);
  }
  else if (dir2 == 0)
  {
    digitalWrite(inAPin2, LOW);
  }

  err_new2 = (cps2_des - cps2);               // calc error in counts
  err_d22 = err_new2 - err_d12;
  err_new2 = (Kp * err_new2) + (0 * err_old2) + (0 * err_d22);

  output2 = adj * (1.4919 * (err_new2));    //converting counts to PWM

  if (output2 > 250)
    output2 = 250;
  else if (output2 < 10)
    output2 = 0;

  analogWrite(PWMPin2, output2);
  err_old2 = err_new2;
  err_d12 = err_old2;
}

void M3( int cps3_des, int dir3)
{
  if (dir3 == 1)
  {
    digitalWrite(inAPin3, LOW);
  }
  else if (dir3 == -1)
  {
    digitalWrite(inAPin3, HIGH);
  }
  else if (dir3 == 0)
  {
    digitalWrite(inAPin3, LOW);
  }

  err_new3 = (cps3_des - cps3);            // calc error in counts
  err_d23 = err_new3 - err_d13;
  err_new3 = (Kp * err_new3) + (0 * err_old3) + (0 * err_d23) ;

  output3 = adj * (1.4919 * (err_new3)); //converting counts to PWM

  if (output3 > 250)
    output3 = 250;
  else if (output3 < 10)
    output3 = 0;

  analogWrite(PWMPin3, output3);
  err_old3 = err_new3;
  err_d13 = err_old3;
}


//=============== Timer ISR ======================================
ISR(TIMER1_COMPA_vect)                    // Speed calcullation
{
  if ((encoder3Pos != temp3) && (i == 0))
  {
    i++;
    temp1 = encoder1Pos;
    temp2 = encoder2Pos;
    temp3 = encoder3Pos;
  }
  if (i != 0)
  {
    cps1 = encoder1Pos - temp1;
    temp1 = encoder1Pos;
    cps2 = encoder2Pos - temp2;
    temp2 = encoder2Pos;
    cps3 = encoder3Pos - temp3;
    temp3 = encoder3Pos;
  }
}

//=============================== Encoder ISR ====================
void doEncoder1()
{
  encoder1Pos++;
}
void doEncoder2()
{
  encoder2Pos++;
}
void doEncoder3()
{
  encoder3Pos++;
}