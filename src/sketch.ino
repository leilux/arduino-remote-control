#include <SPI.h>
#include <Ethernet.h>
#include "parseurl.h"
#include "webpage.h"

#define led 13

byte mac[] = {0xde, 0xad, 0xbe, 0xef, 0xfe, 0xed};
IPAddress ip(192,168,8,129);
char request_header[1024];
char url[1024];
char path[100], cgi_args[100];
int count=0;

EthernetServer server(80);

void setup() {
//    SPI.begin();
//    SPI.setBitOrder(MSBFIRST);
//    SPI.setDataMode(SPI_MODE0);

//    pinMode(3, OUTPUT);
//    digitalWrite(3, HIGH);
    pinMode(led, OUTPUT);

    Ethernet.begin(mac, ip);

    server.begin();
}

void loop() {
    count = 0;
    EthernetClient client = server.available();
    if (client) {
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                if (c=='\n' && currentLineIsBlank) {    
                    break;
                }
                request_header[count++] = c;
                if (c=='\n') {
                    currentLineIsBlank = true;
                }
                else if (c!='\r') {
                    currentLineIsBlank = false;
                }
            }
        }
        request_header[count] = '\0';
        get_url_from_request(request_header, url);
        parse_url(url, path, cgi_args);

        if (strcmp(path, "")==0) {
            client.println("HTTP/1.1 200 ok");
            client.println("Server: arduino mege 2560");
            client.println("Content-Type: text/html");
            client.println();
            client.print(led_control);
        }
        else if (strcmp(path,"on")==0) {
            led_on();
            client.println("HTTP/1.1 200 ok");
            client.println("Content-Type: text/html");
            client.println();
        }
        else if (strcmp(path, "off")==0) {
            led_off();
            client.println("HTTP/1.1 200 ok");
            client.println("Content-Type: text/html");
            client.println();
        }
        else if (strcmp(path, "status")==0) {
            client.println("HTTP/1.1 200 ok");
            client.println("Content-Type: application/json");
            client.println();
            client.print(digitalRead(led)==LOW ? "{\"status\":\"off\"}" : "{\"status\":\"on\"}");
        }
        else {}
                
        delay(1);
        client.stop();
    } // /.if 
}

void led_on() {
  digitalWrite(led, HIGH);
}

void led_off() {
  digitalWrite(led, LOW);
}
