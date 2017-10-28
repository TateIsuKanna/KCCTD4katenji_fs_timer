int LED7segment[][7]=
{
	{HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW},
	{LOW,HIGH,HIGH,LOW,LOW,LOW,LOW},
	{HIGH,HIGH,LOW,HIGH,HIGH,LOW,HIGH},
	{HIGH,HIGH,HIGH,HIGH,LOW,LOW,HIGH},
	{LOW,HIGH,HIGH,LOW,LOW,HIGH,HIGH},
	{HIGH,LOW,HIGH,HIGH,LOW,HIGH,HIGH},
	{HIGH,LOW,HIGH,HIGH,HIGH,HIGH,HIGH},
	{HIGH,HIGH,HIGH,LOW,LOW,HIGH,LOW},
	{HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH},
	{HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH}
};
int LED_digit[][4]=
{
	{HIGH,HIGH,HIGH,LOW},
	{HIGH,HIGH,LOW,HIGH},
	{HIGH,LOW,HIGH,HIGH},
	{LOW,HIGH,HIGH,HIGH}
};

const int trig_port = 13;
const int echo_port = 14;
const int LED_A_port = 2;
const int LED_digit_port = 9;
unsigned long int start_time_ms;
bool is_timer_enable = false;

void setup() {
	Serial.begin(9600);
	for(int i=0;i<7;++i){
		pinMode(LED_A_port+i, OUTPUT);
	}
	for(int i=0;i<4;++i){
		pinMode(LED_digit_port+i, OUTPUT);
	}
	pinMode(trig_port, OUTPUT);
	pinMode(echo_port, INPUT);
	start_time_ms = millis();
}


void loop() {
	if (!is_timer_enable){
		digitalWrite(trig_port, LOW);
		delayMicroseconds(1);
		digitalWrite(trig_port, HIGH);
		delayMicroseconds(11);
		digitalWrite(trig_port, LOW);
		int sensor_value;
		sensor_value = pulseIn(echo_port, HIGH);
		Serial.println(sensor_value);
		float dist = sensor_value * 0.017;
		//dist = 1000.0; //DEBUG用
		if (dist > 4.0) {
			is_timer_enable = true;
		}
		show_value_to_7seg(millis() - start_time_ms);
	}
}

void show_value_to_7seg(unsigned long value){
	unsigned long digit_selecter=1000;//TODO:いい変数名考えて
	for(int digit=0;digit<4;++digit){
		for(int segment=0;segment<4;++segment){
			digitalWrite(LED_digit_port+segment, LED_digit[digit][segment]);
		}
		seg((value / digit_selecter) % 10);
		digit_selecter*=10;
	}
}

void seg(int num) {
	for(int seg_i=0;seg_i<7;++seg_i){
		digitalWrite(LED_A_port+seg_i,LED7segment[num][seg_i]);
	}
	delay(3);
}

