String inputString = ""; // a String to hold incoming data
boolean stringComplete = false; // whether the string is complete

void setup() {
// initialize serial:
Serial.begin(9600);
// reserve 200 bytes for the inputString:
inputString.reserve(200);
}

void loop() {
// print the string when a newline arrives:
if (stringComplete) {
Serial.println(inputString);
// clear the string:
inputString = "";
stringComplete = false;
}
}
