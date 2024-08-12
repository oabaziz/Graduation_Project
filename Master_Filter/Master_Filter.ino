
const int flexPin = A0;  //Forward
const int flex2Pin = A1; //Backward

unsigned int Flex1_Val =0;
unsigned int Flex2_Val =0;

char data [2] ={0,0};

int filter1_index=0;
int filter2_index=0;
const int num_readings =5;
unsigned int flex1_filter [num_readings];
unsigned int flex2_filter [num_readings];
unsigned int total_1 =0;
unsigned int total_2 =0;
unsigned int filter1_avg =0;
unsigned int filter2_avg =0;
void setup() {
    // Initialize Serial for Bluetooth communication
    Serial.begin(38400);
    
    // Intialize the filters arrays by zero to avoid garbage data 
    for(int i=0;i<num_readings;i++){
      flex1_filter[i] =0;
      flex2_filter[i]=0;
    }
}

void loop() {
  if(Serial.available()){
    Flex1_Val=analogRead(flexPin); //Read data from 1st FLEX sensor
    Flex2_Val=analogRead(flex2Pin);  //Read data from 2nd FLEX sensor

    /*************Filter1******************************/
    flex1_filter[filter1_index] =Flex1_Val; // assign FLEX1 value to the filter array
    total_1+=flex1_filter[filter1_index];   // Adding FLEX1 values
    filter1_index++;                        //Increment filter 1 index
    
    if(filter1_index >= num_readings ){   
      filter1_avg =total_1 /num_readings;   //Calcualte the average of 10 flex values
      filter1_index =0;                     // if index is bigger than the filter size, assign it to zero
      total_1 =0;
    }
    
    /************ Flex 1 "44"****************************/
   if(filter1_avg >100 &&filter1_avg < 110){
    data[0] ='1';

    
   }else if((filter1_avg >=110 &&filter1_avg < 115)){
    data[0] ='2';
   }else if((filter1_avg >=115 &&filter1_avg < 120)){
    data[0] ='3';
   }
   else if((filter1_avg >= 120 &&filter1_avg < 135)){
    data[0] ='4';
   }
   else if(filter1_avg >=135 ){
    data[0] ='5';
   }else {
    data[0] ='0';
   }


    /*************Filter2******************************/
    flex2_filter[filter2_index] =Flex2_Val; // assign FLEX1 value to the filter array
    total_2+=flex2_filter[filter2_index];   // Adding FLEX1 values
    filter2_index++;                        //Increment filter 1 index
    
    if(filter2_index >= num_readings ){   
      filter2_avg =total_2 /num_readings;   //Calcualte the average of 10 flex values
      filter2_index =0;                 // if index is bigger than the filter size, assign it to zero
      total_2 =0;
    }
   /************ Flex 2 "46"****************************/
   if(filter2_avg>160 &&filter2_avg < 175){
    data[1] ='1';
   }else if((filter2_avg >=175 &&filter2_avg < 185)){
    data[1] ='2';
   
   }else if((filter2_avg >=185 &&filter2_avg < 195)){
    data[1] ='3';
   }
   else if((filter2_avg >=195 &&filter2_avg < 210)){
    data[1] ='4';
   }
   else if(filter2_avg >=210 ){
    data[1] ='5';
   }else {
    data[1] ='0';
   }

     // Adjust the delay based on your preference
  }else {
    Serial.println("Serial is not avilable");
  }
  if(filter1_index ==num_readings-1 && filter2_index ==num_readings-1){
    for(int cnt=0; cnt<2;cnt++){
    Serial.print(data[cnt]);
  }
  delay(500);
  }
  
}
