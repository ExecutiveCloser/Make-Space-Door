/*
 STATE COLLEGE MAKESPACE WEB ACCESSIBLE DOOR
 WRITTEN BY: JOSEPH SANCHEZ 
 HTTP://MAKESPACE.IO 
 
 */

#include <SPI.h>
#include <Ethernet.h>
String buffer; 
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,177);


EthernetServer server(80);
  byte powersetting = HIGH;
   byte lowsetting = LOW;
void setup() {

  Serial.begin(9600);
  pinMode(6, OUTPUT); 
    pinMode(9, OUTPUT); 
      pinMode(10, OUTPUT); 
   while (!Serial) {
    ; 
  }



  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

 
}


void loop() {

//THIS RELOCKS THE DOOR 
  digitalWrite(6, HIGH); //ACTIVATE DOOR LOCK 
  digitalWrite(9, LOW);  //TURN GREEN LED OFF
  digitalWrite(10, HIGH); //TURN RED LED ON 
  EthernetClient client = server.available();
  
  if (client) {
				boolean currentLineIsBlank = true;
					buffer = ""; 
				while (client.connected()) { 
                    if (client.available()) {
					char c = client.read();
					Serial.print(c);
					buffer+=c;
					
							if (c == '\n' && currentLineIsBlank) {
                    //show our web page 
					client.print("<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'><html xmlns='http://www.w3.org/1999/xhtml'><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8' />");
					//client.print("<meta http-equiv='refresh' content='1; url=http://192.168.0.177>"); //REMOVE THIS LINE TO AUTO REFRESH THE BROWSER AT A SET RATE 
					client.print("<title>Make Space</title>");
          
						client.println("<html><body>");
			                   
						client.print("<a href='http://192.168.1.177/?status=unlock'>UNLOCK</a><br /><br />");
			       
			       //client.print("<a href='http://192.168.1.177/?status=lock'>LOCK</a>"); //UNCOMMENT THIS LINE IF YOU WISH TO ADD A LOCK BUTTON 
      
                     client.println("</body>");
                    
      
                     client.println("</html>");
          break;
        }
      
        if (c == '\n') {
          
          currentLineIsBlank = true;
          buffer="";
        
       } else if (c == '\r') {
          
             if(buffer.indexOf("GET /?status=unlock")>=0){
             digitalWrite(6, LOW);
             digitalWrite(9, LOW);
             digitalWrite(10, HIGH);
             delay(5000);
        
          
             
			                                              } 

			  if(buffer.indexOf("GET /?status=lock")>=0){
              digitalWrite(6, HIGH);
              digitalWrite(9, HIGH);
              digitalWrite(10, LOW); 
              delay(5000);
		  
		                                                 }
        }  
      
  
     
        
      }
	  }
	  

    // give the web browser time to receive the data
    delay(100);
    // close the connection:
    client.stop();
   
  }
} //end loop

