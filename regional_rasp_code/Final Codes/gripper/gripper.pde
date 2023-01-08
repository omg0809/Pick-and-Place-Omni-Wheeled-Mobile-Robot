import controlP5.*; 
import processing.serial.*;

Serial port;

ControlP5 cp5; 

void setup() { 

  size(700, 500);

  printArray(Serial.list());   
  port = new Serial(this, "/dev/ttyACM1", 9600); 

  cp5 = new ControlP5(this);
}

void draw() {

  background(150, 0, 150);
  fill(255);
  text("Motor Control GUI", 195, 30);
}

void lower() {
  port.write('1');
}

void middle() {
  port.write('2');
}

void top() {
  port.write('3');
}

void up(){
    port.write('z');
}

void down(){
    port.write('c');
}

void stop(){
    port.write('x');
}

void keyPressed(){
  switch(key){
    case'1':
    lower();
    break;
    
    case'2':
    middle();
    break;
    
    case'3':
    top();
    break;

    case'z':
    up();
    break;

    case'c':
    down();
    break;
    
  }
}

void keyReleased(){
  switch(key){
    case'1':
    stop();
    break;

    case'2':
    stop();
    break;

    case'3':
    stop();
    break; 

    case'z':
    stop();
    break;
    
    case'x':
    stop();
    break;
    
    case'c':
    stop();
    break;
    
  }
}
