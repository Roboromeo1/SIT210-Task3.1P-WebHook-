// This #include statement was automatically added by the Particle IDE.
#include <ThingSpeak.h>
// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>

#define DHTPIN D6     
// Here we define the type of sensor used
#define DHTTYPE DHT11        // DHT 11   

DHT dht(DHTPIN, DHTTYPE);

bool humid = false;

TCPClient client;


unsigned long ChannelNo = 1041599;
const char * APIKey = "G9U30NXFUQTE1GL6";


void setup() {
    
 ThingSpeak.begin(client);
 pinMode(D7, OUTPUT);
 Serial.begin(9600); 
 dht.begin();
 Particle.subscribe("temp", l, ALL_DEVICES);

}

void loop() {
    // Wait a few seconds between measurements.
    delay(2000);
    float t = dht.getTempCelcius();
    // Check if any reads failed and exit early (to try again).
    if (isnan(t))  {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    
   Particle.publish("temp", String (t), PUBLIC);
  Serial.print(dht.getTempFarenheit());
  Serial.println("t");
  ThingSpeak.writeFields(ChannelNo, APIKey);  

  delay(15000); 
}

    void l(const char *event, const char *data) {
        
            digitalWrite(D7, HIGH);
            delay(2000);
            digitalWrite(D7, LOW);
            delay(1000);
       
    }