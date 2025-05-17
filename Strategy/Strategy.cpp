#include <iostream>
#include <cmath>
#include <memory>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// === Інтерфейси ===
class BrakeStrategy {
public:
    virtual double Brake(double velocity, double angle_deg) = 0;
    virtual ~BrakeStrategy() = default;
};

class DriveStrategy {
public:
    virtual double Accelerate(double velocity, double length) = 0;
    virtual ~DriveStrategy() = default;
};

// === Стратегії гальмування ===
class AggressiveBrake : public BrakeStrategy {
public:
    double Brake(double velocity, double angle_deg) override {
        double angle_rad = angle_deg * M_PI / 180.0;
        return velocity - 0.5 * angle_rad;
    }
};

class CarefulBrake : public BrakeStrategy {
public:
    double Brake(double velocity, double angle_deg) override {
        double angle_rad = angle_deg * M_PI / 180.0;
        return velocity - 0.3 * angle_rad;
    }
};

// === Стратегії прискорення ===
class AggressiveDrive : public DriveStrategy {
public:
    double Accelerate(double velocity, double length) override {
        double a = 0.2;
        double t = (-2 * velocity + sqrt(4 * velocity * velocity + 2 * a * length)) / (2 * a);
        return velocity + a * t;
    }
};

class CarefulDrive : public DriveStrategy {
public:
    double Accelerate(double velocity, double length) override {
        double a = 0.1;
        double t = (-2 * velocity + sqrt(4 * velocity * velocity + 2 * a * length)) / (2 * a);
        return velocity + a * t;
    }
};

// === Клас автомобіля ===
class Car {
private:
    double velocity;
    unique_ptr<BrakeStrategy> brake;
    unique_ptr<DriveStrategy> drive;

public:
    Car(BrakeStrategy* b, DriveStrategy* d)
        : velocity(0.0), brake(b), drive(d) {}

    double GetVelocity() const {
        return velocity;
    }

    void BrakeAtTurn(double angle_deg) {
        velocity = brake->Brake(velocity, angle_deg);
    }

    void AccelerateOnStraight(double length) {
        velocity = drive->Accelerate(velocity, length);
    }

    void SetBrakeStrategy(BrakeStrategy* b) {
        brake.reset(b);
    }

    void SetDriveStrategy(DriveStrategy* d) {
        drive.reset(d);
    }
};

// === Тестування ===
int main() {
    Car car1(new AggressiveBrake(), new CarefulDrive());
    Car car2(new CarefulBrake(), new AggressiveDrive());

    // Пряма ділянка 5 м
    car1.AccelerateOnStraight(5);
    car2.AccelerateOnStraight(5);

    // Поворот 90°
    car1.BrakeAtTurn(90);
    car2.BrakeAtTurn(90);

    // Пряма ділянка 10 м
    car1.AccelerateOnStraight(10);
    car2.AccelerateOnStraight(10);

    // Поворот 180°
    car1.BrakeAtTurn(180);
    car2.BrakeAtTurn(180);

    // Пряма ділянка 7 м
    car1.AccelerateOnStraight(7);
    car2.AccelerateOnStraight(7);

    cout << "Car 1 velocity: " << car1.GetVelocity() << " m/s\n";
    cout << "Car 2 velocity: " << car2.GetVelocity() << " m/s\n";

    return 0;
}