#ifndef ITERADORNODEJUGADOR_H
#define ITERADORNODEJUGADOR_H
#include "NodeJugador.h"


class IteradorNodeJugador
{
    public:
        IteradorNodeJugador();
        IteradorNodeJugador(NodeJugador*);
        ~IteradorNodeJugador();
        void seguent(void);
        Jugador getJugador(void);
        bool esNul(void) const;
        NodeJugador *getNode(void) const;

    private:
        NodeJugador* m_posicio;
};

#endif // ITERADORNODEJUGADOR_H
