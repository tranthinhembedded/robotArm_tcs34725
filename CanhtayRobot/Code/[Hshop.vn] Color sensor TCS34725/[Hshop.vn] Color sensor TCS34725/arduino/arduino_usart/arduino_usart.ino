unsigned char Re_buf[11],counter=0;
unsigned char sign=0;
byte rgb[3]={0};
void setup() {
   Serial.begin(9600);  
  delay(1);    
  Serial.write(0XA5); 
  Serial.write(0X01);    
  Serial.write(0XA6);    
}

void loop() {
  unsigned char i=0,sum=0;
  
  if(sign)
  {   
     sign=0;
     for(i=0;i<7;i++)
      sum+=Re_buf[i]; 
     if(sum==Re_buf[i] )        
     {  	       
          rgb[0]=Re_buf[4];
          rgb[1]=Re_buf[5];
          rgb[2]=Re_buf[6];
           Serial.print("r:");
           Serial.print( rgb[0]);
           Serial.print(",g:");
           Serial.print( rgb[1]);
           Serial.print(",b:");
           Serial.println( rgb[2]);
           
   }
  } 
}
void serialEvent() {
  while (Serial.available()) {   
    Re_buf[counter]=(unsigned char)Serial.read();
    if(counter==0&&Re_buf[0]!=0x5A) return;            
    counter++;       
    if(counter==8)                
    {    
       counter=0;                  
       sign=1;
    }      
  }
}
