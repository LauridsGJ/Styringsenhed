#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x1B, 0x82};   // MAC Address
byte ip[] = {169, 254, 43, 129};                          // Network Address
byte gateway[] = {10, 0, 0, 1};                      // Gateway Address
byte subnet[] = {255, 255, 255, 0};                  // Subnet Mask

EthernetServer server = EthernetServer(27015);

void setup()
{
    Serial.begin(9600);
         Serial.println("IP Address: ");
         Serial.println(ip[0]);
    Serial.println("Ethernet Begin");
      Ethernet.begin(mac,ip);
    server.begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP()); 

}

void loop() {
 int tal = 48;
 int tal1 = 48;
 
 EthernetClient client = server.available();
  
if(client)
  {
    Serial.println("client connected");

     if(client.read() == 'r')
     {
      if(client.read() == 'e')
      {
        if(client.read() == 'q')
        {
          char m = client.read();
          if(m == '1')
          {     
              Serial.println("req1");
              client.write(tal);
              client.write(tal1);
          }
          else if(m == '2')
          {
              Serial.println("req2");
              client.write(tal1);
              client.write(tal);
          }
            
        }
      }
    }
  }
} 
