#define motor1 30
#define motor2 32
#define motor3 33

a = cos(240);   b = cos(120);   c = cos(0);
d = sin(240);   e = sin(120);   f = sin(0);
g = 1;          h = 1;          i = 1;

det = a * e * i + b * f * g + c * d * h - c * e * g - a * f * h - b * d * i;

a_inverse = (e * i - f * h) / det;      b_inverse = (h * c - i * b) / det;      c_inverse = (b * f - c * a) / det;
d_inverse = (g * f - d * i) / det;      e_inverse = (a* i - g * c) / det;       f_inverse = (d * c - a * f) / det;
g_inverse = (d * h - g * e) / det;      h_inverse = (g * b - a * h) / det;      i_inverse = (a * e - d * b) / det;

void setup(){
    pinMode(motor1, OUTPUT);
    pinMode(motor2, OUTPUT);
    pinMode(motor3, OUTPUT);

    set_robot_speeds(0, 70, 0);
    delay(3000);

    set_robot_speeds(0, -70, 0);
    delay(3000);

    set_robot_speeds(70, 0, 0);
    delay(3000);

    set_robot_speeds(-70, 0, 0);
    delay(3000);

    set_robot_speeds(0, 0, 70);
    delay(3000);

    set_robot_speeds(0, 0, -70);
    delay(3000);

    set_robot_speeds(0, 70, -70);
    delay(3000);

    set_robot_speeds(70, 0, -70);
    delay(3000);
}

void loop(){}

void set_robot_speeds(float x_speed, float y_speed, float w_speed){
    analogWrite(motor1, a_inverse * x_speed + b_inverse * y_speed + c_inverse * w_speed);
    analogWrite(motor2, d_inverse * x_speed + e_inverse * y_speed + f_inverse * w_speed);
    analogWrite(motor3, g_inverse * x_speed + h_inverse * y_speed + i_inverse * w_speed);
}