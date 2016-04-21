#include <Arduino.h>
#include <IMU.h>

IMU::IMU(ros::NodeHandle _nh):
mag_pub("imu/mag", &mag),
imu_pub("/imu", &imu),
temperature_pub("temperature", &temperature),
pressure_pub("pressure", &pressure)
{
  nh = _nh;
  mag_sensor = Adafruit_HMC5883_Unified(11);
  accel_sensor = Adafruit_ADXL345_Unified(22);
  bmp_sensor = Adafruit_BMP085_Unified(10085);
}

void IMU::setup(){
  nh.advertise(mag_pub);
  nh.advertise(imu_pub);
  nh.advertise(temperature_pub);
  nh.advertise(pressure_pub);

  mag.header.frame_id = "imu_sensor";
  imu.header.frame_id = "imu_sensor";
  temperature.header.frame_id = "imu_sensor";
  pressure.header.frame_id = "imu_sensor";

  if(!mag_sensor.begin()){
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
  }

  gyroscope.begin(L3G4200D_SCALE_2000DPS, L3G4200D_DATARATE_400HZ_50);
  

  if (!accel_sensor.begin()) {
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
  }
  accel_sensor.setRange(ADXL345_RANGE_2_G);

  if (!bmp_sensor.begin()) {
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
  }

  gyroscope.calibrate(100);

  imu.orientation.x = 0.0;
  imu.orientation.y = 0.0;
  imu.orientation.z = 0.0;
  imu.orientation.w = 1.0;
}

void IMU::loop(){
  sensors_event_t event;
  mag_sensor.getEvent(&event);

  mag.header.stamp = nh.now();
  mag.magnetic_field.x = -event.magnetic.x;
  mag.magnetic_field.y = -event.magnetic.y;
  mag.magnetic_field.z = event.magnetic.z;

  mag_pub.publish(&mag);

  sensors_event_t event2;
  accel_sensor.getEvent(&event2);

  Vector norm = gyroscope.readNormalize();

  imu.header.stamp = nh.now();
  imu.angular_velocity.x = norm.XAxis;
  imu.angular_velocity.y = norm.YAxis;
  imu.angular_velocity.z = norm.ZAxis;

  imu.linear_acceleration.x = event2.acceleration.x;//(event2.acceleration.x - azx);
  imu.linear_acceleration.y = event2.acceleration.y;//(event2.acceleration.y - azy);
  imu.linear_acceleration.z = event2.acceleration.z;//(event2.acceleration.z - azz);

  imu_pub.publish(&imu);

  temperature.header.stamp = nh.now();
  float temp;
  bmp_sensor.getTemperature(&temp);
  temperature.temperature = temp;
  temperature_pub.publish(&temperature);

  sensors_event_t event3;
  bmp_sensor.getEvent(&event3);
  if (event.pressure) {
    pressure.header.stamp = nh.now();
    pressure.fluid_pressure = event3.pressure;
    pressure_pub.publish(&pressure);
  }
}