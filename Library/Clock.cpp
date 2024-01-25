//
// Created  on 25/01/24.
//
#include "Headers/Clock.h"

Clock::Clock() : START(time(0)), SPEED(0), START_TIME{} {}
Clock::Clock(time_t start, int velocidade, time_t horaInicio) : START(start), SPEED(velocidade),
                                                                START_TIME(horaInicio) {}

void Clock::StartClock(int speed, const std::string& start_time) {
    START = time(nullptr);
    SPEED = speed;

    struct tm tmp;
    localtime_r(&START, &tmp);
    sscanf(start_time.c_str(), "%d:%d:%d", &tmp.tm_hour, &tmp.tm_min, &tmp.tm_sec);
    START_TIME = mktime(&tmp);

    char buffer[80];
    strftime(buffer, 80, "%c", localtime(&START_TIME));
    std::cout << "------------\n" << "\t[Hora de Arranque] = [" << buffer << "]" << "\n\n";
}

time_t Clock::getTime() const {
    time_t Dif = difftime(time(nullptr), START);
    time_t Simulada = START_TIME + Dif * SPEED;
    return Simulada;
}

std::string Clock::toString() const{
    std::string s = "\t[Time HW]->" + std::to_string(START);  s.append(";");
    s.append("\t\t[VELOCITY]->" + std::to_string(SPEED)); s.append(";");
    s.append("\t\t[Start_Hour SW]->" + std::to_string(START_TIME)); s.append(";");
    return s;
}
std::string Clock::toStringOut() const{
    std::string s = "\t[Time HW]->" + std::to_string(START);  s.append("\n");
    s.append("\t\t[VELOCITY]->" + std::to_string(SPEED)); s.append("\n");
    s.append("\t\t[Start_Hour SW]->" + std::to_string(START_TIME)); s.append("\n");
    return s;
}