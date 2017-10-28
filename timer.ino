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
unsigned long int start_time_ms, time_diff = 0;
volatile bool is_timer_enable = false;
int count = 0;
int val;
void setup() {
	Serial.begin(9600);
	pinMode(LED_A_port, OUTPUT);
	for(int i=0;i<7;++i){
		pinMode(LED_A_port+i, OUTPUT);
	}
	for(int i=0;i<4;++i){
		pinMode(LED_digit_port+i, OUTPUT);
	}
	pinMode(trig_port, OUTPUT);
	pinMode(echo_port, INPUT);
	start_time_ms = millis(); //開始時刻取得
}


void loop() {
	if (!is_timer_enable){
		digitalWrite(trig_port, LOW);
		delayMicroseconds(1);
		digitalWrite(trig_port, HIGH);
		delayMicroseconds(11);
		digitalWrite(trig_port, LOW);
		//Serial.println(time_diff);
		////////////////////////////////////////////////////////////////////////////////////////////////////val = pulseIn(echo_port, HIGH);
		float dist = val * 0.017;
		dist = 4.0; //DEBUG用
		if (dist > 4.0) {
			//is_timer_enable = true;
		}
		time_diff = millis() - start_time_ms;
	}
	unsigned long digit_selecter=1000;//TODO:いい変数名考えて
	for(int digit=0;digit<4;++digit){
		for(int segment=0;segment<4;++segment){
			digitalWrite(LED_digit_port+segment, LED_digit[digit][segment]);
		}
		seg((time_diff / digit_selecter) % 10);
		//Serial.println(time_diff);
		digit_selecter*=10;
	}
}

void seg(int num) {
	for(int seg_i=0;seg_i<7;++seg_i){
		digitalWrite(LED_A_port+seg_i,LED7segment[num][seg_i]);
	}
	delay(5);
}

