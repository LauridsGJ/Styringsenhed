#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x1B, 0x82};   // MAC Address
byte ip[] = {169, 254, 43, 129};                          // Network Address

byte gateway[] = {10, 0, 0, 1};                      // Gateway Address
byte subnet[] = {255, 255, 0, 0};                  // Subnet Mask

EthernetServer server = EthernetServer(27015);

 int ReadArray[4];
  int MCStrom = 4, MCStrom1 = 200, MCSpanding = 5, MCSpanding1 = 20,MCpf = 250, MCpf1 = 50, MCTHD = 20,  MCTHD1 = 20;
  int M1Strom = 48, M1Strom1 = 90, M1Spanding = 50, M1Spanding1= 60, M1pf= 40, M1pf1= 30, M1THD = 50, M1THD1 = 60;

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

    Serial1.begin(9600);
    Serial2.begin(9600);
}

void loop()
{
 
  EthernetClient client = server.available();

//if(Serial.read()=='1')
//{
  Serial1.write('A');
  delay(4);
  MCStrom = Serial1.read();
  delay(4);
  MCStrom1 = Serial1.read();
  Serial.print("\n MCStrøm: ");
  Serial.write(MCStrom);
  Serial.write(MCStrom1);
  Serial1.write('B');
   delay(4);
  MCSpanding = Serial1.read();
   delay(4);
  MCSpanding1 = Serial1.read();
  Serial.print("\n MCSpanding: ");
  Serial.write(MCSpanding);
  Serial.write(MCSpanding1);
  Serial1.write('C');
   delay(4);
  MCpf = Serial1.read();
   delay(4);
  MCpf1 = Serial1.read();
  Serial.print("\n MCpf: ");
  Serial.write(MCpf);
  Serial.write(MCpf1);
  Serial1.write('D');
   delay(4);
  MCTHD= Serial1.read();
   delay(4);
  MCTHD1= Serial1.read();
  Serial.print("\n MCTHD: ");
  Serial.write(MCTHD);
  Serial.write(MCTHD1);
//  Serial2.write('A');
//  M1Strom = Serial2.read();
//  M1Strom1 = Serial2.read();  
//  Serial.print("\n M1Strøm: ");
//  Serial.write(M1Strom);
//  Serial.write(M1Strom1);
//  Serial2.write('B');
//  M1Spanding = Serial2.read();
//  M1Spanding1 = Serial2.read();  
//  Serial.print("\n M1Spanding: ");
//  Serial.write(M1Spanding);
//  Serial.write(M1Spanding1);
//  Serial2.write('C');
//  M1pf = Serial2.read();
//  M1pf1 = Serial2.read();
//  Serial.print("\n M1pf: ");
//  Serial.write(M1pf);
//  Serial.write(M1pf1);
//  Serial2.write('D');
//  M1THD = Serial2.read();
//  M1THD1 = Serial2.read();
//  Serial.print("\n M1THD: ");
//  Serial.write(M1THD);
//  Serial.write(M1THD1);
//}


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
              client.write(MCStrom);
              client.write(MCStrom1);
              client.write(MCSpanding);
              client.write(MCSpanding1);
              client.write(MCpf);
              client.write(MCpf1);
              client.write(MCTHD);
              client.write(MCTHD1);
            }
          
            if(m == '2')
            {
              Serial.println("req2");
              client.write(M1Strom);
              client.write(M1Strom1);
              client.write(M1Spanding);
              client.write(M1Spanding1);
              client.write(M1pf);
              client.write(M1pf1);
              client.write(M1THD);
              client.write(M1THD1);
            }

          }
            
        }
      }
//while(client.read()!= -1)



/*      while(client.connected())
      {
          client.write("hi");
          client.println("hi, i am ethernet shield connected on mega 2560.");
          // give the web browser time to receive the data
          delay(1000);
          Serial.println("data sent to client.");
      }
*/

      // close the connection:
     // client.stop();
     // Serial.println("client disconnected");
  }
}

