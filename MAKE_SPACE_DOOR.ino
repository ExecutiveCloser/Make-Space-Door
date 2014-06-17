/*
  Web Server
 
 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 
 */

#include <SPI.h>
#include <Ethernet.h>
String buffer; 
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,177);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);
  byte powersetting = HIGH;
   byte lowsetting = LOW;
void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(6, OUTPUT); 
    pinMode(9, OUTPUT); 
      pinMode(10, OUTPUT); 
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  // listen for incoming clients
 
}


void loop() {

//THIS RELOCKS THE DOOR 
  digitalWrite(6, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  EthernetClient client = server.available();
  
  if (client) {
				boolean currentLineIsBlank = true;
					buffer = ""; 
				while (client.connected()) { 
         if (client.available()) {
					char c = client.read();
					Serial.print(c);
					buffer+=c;
					// if you've gotten to the end of the line (received a newline
					// character) and the line is blank, the http request has ended,
					// so you can send a reply
							if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
					client.print("<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'><html xmlns='http://www.w3.org/1999/xhtml'><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8' />");
					//client.print("<meta http-equiv='refresh' content='1; url=http://192.168.0.201/'>");
					client.print("<title>Make Space</title>");
          
						client.println("<html><body>");
			                      //////wake up////
									client.print("<a href='http://192.168.1.177/?status=unlock'>UNLOCK</a><br /><br />");
			       ////shut down////
			       client.print("<a href='http://192.168.1.177/?status=lock'>LOCK</a>");
      
                     client.println("</body>");
                      // output the value of each analog input pin
      
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
        }  // ends c == \r
      
  
     
        
      } //end c
	  }
	  

    // give the web browser time to receive the data
    delay(100);
    // close the connection:
    client.stop();
   
  }
} //end loop

