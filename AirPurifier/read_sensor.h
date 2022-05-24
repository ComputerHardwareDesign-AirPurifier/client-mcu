int measurePin = A5;
int ledPower = 11;


unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;


float voMeasured = 0;
float calcVoltage = 0;

float Voc = 0.6;  //Voc is 0.6 Volts for dust free acordind sensor spec
float K = 0.5;
int samples[16];


void dust_sensor_init(){

pinMode(ledPower,OUTPUT);
}
float standard_deviation(int mean){
  float sum_square_error=0.0;
  for(int i=0;i<16;i++){
    sum_square_error+=pow(samples[i]-mean,2);
  }
  return sqrt(sum_square_error/15);
}
int average_16(int x) {

  static int i = 0;
  static int total = 0;

  total += x - samples[i];
  samples[i] = x;

  i = (i == 15 ? 0 : i + 1);
 
  
  return total >> 4;
}

void cal_dust_density(){
   float Vo = voMeasured * (5.0/ 1024);
  if(Vo>3.5){
    Vo=3.5;
  }
 
//  float dV = Vo - Voc;
//  if (dV < 0) {
//    dV = 0;
//    Voc = Vo;
//  }
//  dustValue = ((dV) / K) * 100;

dustValue = 170*Vo-100;
  if (dustValue >= 1000) {
    dustValue = 999;
  }else if(dustValue<0){
    dustValue=0;
  }

//  Serial.println("Raw Signal Value (0-1023):");
//  Serial.println(voMeasured);
//
//  Serial.println("Voltage:");
//  Serial.println(Vo);
//
//  Serial.println("Dust Density:");
//  Serial.println(dustValue);

}
void read_dust_sensor() {

  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);
  int analog_input=average_16(analogRead(measurePin));
  float std_value=standard_deviation(analog_input);
//    Serial.println("analog_input:");
//  Serial.println(analog_input);
//  
//  Serial.println("Standard Deviation:");
//  Serial.println(std_value);
//  
  if(analog_input>=voMeasured+(std_value)||analog_input<=voMeasured-(std_value)){
  voMeasured = analog_input;
  }
  cal_dust_density();
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);

}

void dust_sensor_controller(){
read_dust_sensor();
}
