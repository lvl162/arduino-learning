#include <Stepper.h>

#define STEPS 2038
// số bước trong một vòng quay
// Số trên là hằng số với mỗi loại Stepper Motor.
int degreeToSteps(int degree, int STEPS1 = 2038) {
  if (degree == 0) return 0;
  Serial.println(STEPS1 / (360 / degree));
  return STEPS1 / (360 / degree); // (tính âm dương bảo toàn)
}

Stepper stepper(STEPS, D5, D6, D7, D8);  
void setup() {
  Serial.begin(9600);
  // không cần làm gì cả, thư viện Stepper sẽ lo setup động cơ cho ta
}
 
void loop() {
  stepper.setSpeed(6); // 3 rpm
  int goc = degreeToSteps(90);
  stepper.step(goc); // quay một vòng cùng chiều đồng hồ
  delay(5000);
//  stepper.setSpeed(6); // 6 rpm
//  stepper.step(-degreeToSteps(180)); // quay một vòng ngược chiều đồng hồ
//  delay(1000); 
}
