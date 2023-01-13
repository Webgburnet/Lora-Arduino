#include <SoftwareSerial.h>   //Software Serial Port

#define RxD 2 // ou A10 sur Mega
#define TxD 3 // ou A11 sur Mega
#define vitesse_arduino 9600
#define vitesse_bluetooth 9600

SoftwareSerial loraSerial(RxD,TxD);

String recvChar;
String emitChar;
String commande_bluetooth;

/* Basic AT Commands :
AT+ID // Read all, DevAddr(ABP), DevEui(OTAA), AppEui(OTAA)
AT+ID=DevAddr // Read DevAddr
AT+ID=DevEui // Read DevEui
AT+ID=AppEui // Read AppEui
AT+ID=DevAddr,"devaddr" // Set new DevAddr
AT+ID=DevEui,"deveui" // Set new DevEui
AT+ID=AppEui,"appeui" // Set new AppEui
AT+KEY=APPKEY,"16 bytes length key" // Change application session key
AT+DR=band // Change the Band Plans
AT+DR=SCHEME // Check current band
AT+CH=NUM, 0-7 // Enable channel 0~7
AT+MODE="mode" // Select work mode: LWOTAA, LWABP or TEST
AT+JOIN // Send JOIN request
AT+MSG="Data to send" // Use to send string format frame which is no need to be confirmed by the server
AT+CMSG="Data to send" // Use to send string format frame which must be confirmed by the server
AT+MSGHEX="xx xx xx xx" // Use to send hex format frame which is no need to be confirmed by the server
AT+CMSGHEX="xx xx xx xx" // Use to send hex format frame which must be confirmed by the server
*/

void setup()
{
  Serial.begin(vitesse_arduino);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  
  Serial.println("Debut setup");
  loraSerial.begin(vitesse_bluetooth);
  loraSerial.flush();
  loraSerial.print("AT");
  Serial.println(loraSerial.readString());
  loraSerial.print("AT+ID");
  Serial.println(loraSerial.readString());
  
  delay(2000);
  loraSerial.flush();
}

void loop()
{
  
  if(loraSerial.available()>0)
  {
     recvChar = loraSerial.readString();
     int lenghtChar=recvChar.length();
//     Serial.print("longeur chaine : ");
//     Serial.println(lenghtChar);
//     Serial.print("Chaine de base : ");
//     Serial.println(recvChar);
     
     recvChar.remove(lenghtChar-2);
//     Serial.print("chaine sans saut : ");
//     Serial.println(recvChar);
     
    commande_bluetooth = recvChar;
//    Serial.print("commande ble : ");
//    Serial.println(commande_bluetooth);
//    Serial.print("longeur ble : ");
//    Serial.println(commande_bluetooth.length());

//    Serial.print(loraSerial.read());
//    Serial.write(loraSerial.read());
  }
  if(Serial.available()>0)
  {
    emitChar  = Serial.readString();
    Serial.println(emitChar);
    loraSerial.print(emitChar);
//    loraSerial.write(Serial.read());
//    loraSerial.print(Serial.read());
  }
  if(commande_bluetooth.equalsIgnoreCase("ButtonRecuCapteur"))
  {
    Serial.println("Emission vers le telephone");
    emitChar="&";
    emitChar=emitChar+"Valeur 1";
    emitChar=emitChar+"%";
    loraSerial.print(emitChar);
    commande_bluetooth="";
  }
}