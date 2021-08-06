#include <Stepper.h>

#define STEPS 2038 // số bước trong một vòng quay
// Số trên là hằng số với mỗi loại Stepper Motor.
 
Stepper stepper(STEPS, 8, 10, 9, 11);  
void setup() {
  // không cần làm gì cả, thư viện Stepper sẽ lo setup động cơ cho ta
}
 
void loop() {
  stepper.setSpeed(10); // 3 rpm
  stepper.step(STEPS); // quay một vòng cùng chiều đồng hồ
  delay(1000);
  stepper.setSpeed(20); // 6 rpm
  stepper.step(-STEPS); // quay một vòng ngược chiều đồng hồ
  delay(1000); 
}
