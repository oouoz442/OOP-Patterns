#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// === ���������� ===
class BrakeStrategy {
public:
    virtual double Brake(double velocity, double angle_deg) = 0;
    virtual ~BrakeStrategy() = default;
};

class DriveStrategy {
public:
    virtual pair<double, double> Accelerate(double velocity, double length) = 0;
    virtual ~DriveStrategy() = default;
};

// === ������㳿 ����������� ===
class AggressiveBrake : public BrakeStrategy {
public:
    double Brake(double velocity, double angle_deg) override {
        double angle_rad = angle_deg * M_PI / 180.0;
        return max(0.0, velocity - 0.5 * angle_rad);
    }
};

class CarefulBrake : public BrakeStrategy {
public:
    double Brake(double velocity, double angle_deg) override {
        double angle_rad = angle_deg * M_PI / 180.0;
        return max(0.0, velocity - 0.3 * angle_rad);
    }
};

// === ������㳿 ����������� ===
class AggressiveDrive : public DriveStrategy {
public:
    pair<double, double> Accelerate(double velocity, double length) override {
        double a = 0.2;
        double t = (-2 * velocity + sqrt(4 * velocity * velocity + 2 * a * length)) / (2 * a);
        double newVelocity = velocity + a * t;
        return { newVelocity, t };
    }
};

class CarefulDrive : public DriveStrategy {
public:
    pair<double, double> Accelerate(double velocity, double length) override {
        double a = 0.1;
        double t = (-2 * velocity + sqrt(4 * velocity * velocity + 2 * a * length)) / (2 * a);
        double newVelocity = velocity + a * t;
        return { newVelocity, t };
    }
};

// === ���� ��������� ===
class Car {
private:
    double velocity;
    double totalTime;
    unique_ptr<BrakeStrategy> brake;
    unique_ptr<DriveStrategy> drive;

public:
    Car(BrakeStrategy* b, DriveStrategy* d)
        : velocity(0.0), totalTime(0.0), brake(b), drive(d) {}

    double GetVelocity() const {
        return velocity;
    }

    double GetTotalTime() const {
        return totalTime;
    }

    void BrakeAtTurn(double angle_deg) {
        velocity = brake->Brake(velocity, angle_deg);
        totalTime += 1.0; // ���������: ����������� ����� 1 ���
    }

    void AccelerateOnStraight(double length) {
        auto [newVel, timeSpent] = drive->Accelerate(velocity, length);
        velocity = newVel;
        totalTime += timeSpent;
    }

    void SetBrakeStrategy(BrakeStrategy* b) {
        brake.reset(b);
    }

    void SetDriveStrategy(DriveStrategy* d) {
        drive.reset(d);
    }
};

// === ���������� ===
int main() {
    Car car1(new AggressiveBrake(), new CarefulDrive());
    Car car2(new CarefulBrake(), new AggressiveDrive());

    // �����: ����� � ������� � ����� � ������� � �����
    car1.AccelerateOnStraight(5);
    car1.BrakeAtTurn(90);
    car1.AccelerateOnStraight(10);
    car1.BrakeAtTurn(180);
    car1.AccelerateOnStraight(7);

    car2.AccelerateOnStraight(5);
    car2.BrakeAtTurn(90);
    car2.AccelerateOnStraight(10);
    car2.BrakeAtTurn(180);
    car2.AccelerateOnStraight(7);

    cout << "Car 1 final velocity: " << car1.GetVelocity() << " m/s\n";
    cout << "Car 1 total time: " << car1.GetTotalTime() << " s\n\n";

    cout << "Car 2 final velocity: " << car2.GetVelocity() << " m/s\n";
    cout << "Car 2 total time: " << car2.GetTotalTime() << " s\n";

    return 0;
}