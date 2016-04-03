#include <Thread.h>
#include <ThreadController.h>
#include <DueTimer.h>

// ThreadController that will controll all threads
ThreadController controll = ThreadController();

//RPM Feedback Thread
Thread fbThread = Thread();

//IMU Thread
Thread imuThread = Thread();

//base Movement Thread
Thread baseThread = Thread();


// callback for feedback Thread
void fbThreadCallback(){
	Serial.println("fbThread\t\t\tcallback");
}

// callback for IMU Thread
void imuThreadCallback(){
  pulseIn(2,HIGH);
  pulseIn(2,HIGH);
  pulseIn(2,HIGH);
  Serial.println("\timuThread\t\tcallback");
}

// callback for base Thread
void baseThreadCallback(){
  Serial.println("\t\tbaseThread\tcallback");
 // delay(50);
}
	
// This is the callback for the Timer
void timerCallback(){
	controll.run();
}

void setup(){
	Serial.begin(9600);

	// Configure fbThread
	fbThread.onRun(fbThreadCallback);
	fbThread.setInterval(1000);

	// Configure imuThread
  imuThread.onRun(imuThreadCallback);
  imuThread.setInterval(2000);

  // Configure baseThread
  baseThread.onRun(baseThreadCallback);
  baseThread.setInterval(100);



	// Adds both threads to the controller
	controll.add(&fbThread); // & to pass the pointer to it
  controll.add(&imuThread);
  controll.add(&baseThread);

	 Timer.getAvailable().attachInterrupt(timerCallback).start(20000);
}

void waitSerial(){
	while (!Serial.available());
	delay(10);
    while (Serial.available() && Serial.read());	
}

void loop(){
	while(1){
		noInterrupts();	// Call to disable interrupts
		Serial.println("Type anyting to stop fbThread!");
		interrupts();	// Call to enable interrupts
		waitSerial();
		fbThread.enabled = false;

		noInterrupts();
		Serial.println("Type anyting to stop imuThread!");
		interrupts();
		waitSerial();
		imuThread.enabled = false;

		noInterrupts();
		Serial.println("Type anyting to enable fbThread!");
		interrupts();
		waitSerial();
		fbThread.enabled = true;

		noInterrupts();
		Serial.println("Type anyting to enable imuThread!");
		interrupts();
		waitSerial();
		imuThread.enabled = true;

	}
}
