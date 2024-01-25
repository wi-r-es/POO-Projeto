//
// Created  on 25/01/24.
//
#include "Headers/Clock.h"

Clock::Clock() : START(time(0)), VELOCIDADE(25), Hora_Inicio((time_t) "10:00:00") {}
Clock::Clock(time_t start, int velocidade, time_t horaInicio) : START(start), VELOCIDADE(velocidade),
                                                                Hora_Inicio(horaInicio) {}

void Clock::StartClock(int Vel, const std::string& H_Inicio) {
    START = time(nullptr);
    VELOCIDADE = Vel;

    struct tm tmp;
    localtime_r(&START, &tmp);
    sscanf(H_Inicio.c_str(), "%d:%d:%d", &tmp.tm_hour, &tmp.tm_min, &tmp.tm_sec);
    Hora_Inicio = mktime(&tmp);

    char buffer[80];
    strftime(buffer, 80, "%c", localtime(&Hora_Inicio));
    std::cout << "Hora de Arranque = [" << buffer << "]" << std::endl;
}

time_t Clock::getTime() const {
    time_t Dif = difftime(time(nullptr), START);
    time_t Simulada = Hora_Inicio + Dif * VELOCIDADE;
    return Simulada;
}

std::string Clock::toString() const{

}