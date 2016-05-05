
#include "Joc.h"
#include "../lib/libreria.h"
#include <cstdlib>


#include "Resultats.h"


int llegirEvent()
{
    int tecla;

    if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
        tecla = TECLA_ESQUERRA;
    else
        if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
            tecla = TECLA_DRETA;
        else
            if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
                tecla = TECLA_ABAIX;
            else
                if (Keyboard_GetKeyTrg(KEYBOARD_ESCAPE))
                    tecla = TECLA_ESC;
                    else
                        if (Keyboard_GetKeyTrg(KEYBOARD_UP))
                            tecla = TECLA_AMUNT;
                            else
                                if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
                                tecla = TECLA_ESPAI;
    return tecla;
}

int aleatori(int min, int max)
{
	int aleatori = rand() % (max - min + 1) + min;
	return aleatori;
}

void tractarEvent(int tecla, FigTetris& fig, Fons& fons)
{

	// Adaptar el mateix tractament de cada possible event (tecla) que vau fer a la sessi� 1, modificant el codi per
	// utilitzar els m�todes de les classes FigTetris i Fons

	switch(tecla)
	{
		case TECLA_ESQUERRA:
			if(fig.moureFig(-1, 0, fons));
			break;
		case TECLA_DRETA:
			if (fig.moureFig(1, 0, fons));
			break;
		case TECLA_ABAIX:
			if (fig.moureFig(0, 2, fons));
			break;
        case TECLA_AMUNT:
        case TECLA_ESPAI:
            if (fig.gir(fons));
            break;
            break;
		default:
		    break;
	}
}

void crearFigTetris(FigTetris* figTetrisActual)
{

    // Heu de crear totes les figures del tetris utilitzant el m�tode create de la classe FigTetris i guardar cadascuna de les figures
    // en una de les posicions de l'array de figures que es passa com a par�metre

    for (int i = 0; i < MAX_FIG; i++)
    {
        figTetrisActual[i].create(i, 0);
    }
}

int joc(int nivell)
{

    // Definicions i Inicialitzacions necess�ries per utilitzar la llibreria gr�fica
    // Ha de ser el mateix codi que teniu a la versi� de la primera sessi�

    Game joc;
    joc.Init();



    // Definicions dels objectes del fons i resultats

    Fons fons;
    Resultats resultats;

	// Declaracions de variables. No s'han de modificar
    int tecla = 0; // Valor de la tecla pressionada en cada iteraci� del joc
    bool metaAconseguida; // Indica si la figura ha arribat a la �ltima l�nia del taules
	int velocitatJoc = 400; // Indica velocitat del joc, quantes m�s linies es fan m�s r�pida �s
	int contVPeca; // Comptador per controlar la velocitat
	int vides = 3; // N� de vides
	int punts = 0; // Punts

	int fcompletades = 0; //nombre de files completades a la vegada

	srand((unsigned)time(NULL));




    // Inicialitzar els gr�fics del fons i resultat cridant als m�todes Inicialitzar de les classes fons i resultat
    // per al fons "data/GraficsTetris/fons.png");
    // per el resultat "data/GraficsTetris/Resultats.png"

    fons.inicialitzar("data/GraficsTetris/fons.png");
    resultats.inicialitzar("data/GraficsTetris/Resultats.png");



   	// Mostrem la finestra del joc com a la sesio 1

   	joc.Video_ShowWindow();



    // Declaraci� d'un array per guardar totes les figures del tetris.
    // Inicialitza els gr�fics de totes les figures de l'array amb la funci� CrearFigTetris

    FigTetris figura[MAX_FIG];
    crearFigTetris(figura);



	do
    {
        // Definici� i inicialitzaci� aleatoria de la figura del tetris
        int indexFig  = aleatori(INI_FIG, FI_FIG);
        int gir = aleatori(0, MAX_GIRS - 1);



        // Inicialitzacio de la posicio de la figura que s'ha generat aleat�riament utilitzant els m�todes setPosX i setPosY de la figura que
        // ocupa la posici� indexFig dins de l'array de figures
        // La posici� x vindria donada per ( (INICI_X) + ( ( rand() % ( ( (FI_X - INICI_X - (amplada en quadres figura actual * MIDA_Q)) / MIDA_Q ) + 1 ) ) * MIDA_Q ));
        // La posici� y per (INICI_Y);


        figura[indexFig].setPosX(( (INICI_X) + ( ( rand() % ( ( (FI_X - INICI_X - (figura[indexFig].amplada() * MIDA_Q)) / MIDA_Q ) + 1 ) ) * MIDA_Q )));
        figura[indexFig].setPosY(INICI_Y);

        // Inicialitzar variables que controlen si s'ha omplert la �ltima l�nia i la velocitat del joc
        metaAconseguida = false;
        contVPeca = velocitatJoc / nivell;



        // Dibuixar el fons, els resultats, la figura actual (cridant els m�todes corresponents de cada objecte) i refrescar pantalla (com a la primera sessi�)

        fons.pintaFons();
        resultats.pintaResultats(nivell, punts, vides);
        figura[indexFig].draw();

        joc.VideoUpdate();

        if(figura[indexFig].moureFig(0, 1, fons))
        {
                // Reinicialitzar el fons a negre (m�tode posarNegre de la classe Fons)

                fons.posarNegre();


                // Decrementem n� de vides
                vides--;

                metaAconseguida = true;
        }



        do
        {

           // Permetre que es processin els events com a la sesio 1, llegir event i tractar event, igual que es fa a la primera sessi�

            joc.ProcessEvents();
            tecla = llegirEvent();
            tractarEvent(tecla, figura[indexFig], fons);


            // Moviment de la figura segons la velocitat del joc
            contVPeca--;

            if(contVPeca == 0)
            {

                // Moure la figura una posicions cap avall i verificar si hem arribat a la �ltima l�nia del tauler actualitzant
                // metaAconseguida a true si �s aix� i les posicions corresponent de la �ltima l�nia del tauler ams els colors de la figura
                // Aix� s'ha de fer cridant al m�tode moureFig de la classe FigTetris.


                metaAconseguida = figura[indexFig].moureFig(0, 1, fons);



                contVPeca = velocitatJoc / nivell; // reinicialitzaci� comptador de velocitat
            }


            // Dibuixar el fons, els resultats, la figura actual (cridant els m�todes corresponents de cada objecte)

            fons.pintaFons();
            resultats.pintaResultats(nivell, punts, vides);
            figura[indexFig].draw();



			// Actualitza la pantalla com a sesio 1.

			joc.VideoUpdate();

            // Mira el temps que ha trigat





            // Mira si ha fet una linia
            if(fons.guanyar(fcompletades))
            {
                metaAconseguida = true;

                // Incrementem puntuaci� i nivell
                punts += fcompletades*(nivell += fcompletades);




            }

        }while((tecla != TECLA_ESC) && (!metaAconseguida) && (vides>0));

	}while((vides>0) && (tecla != TECLA_ESC));



	return punts;
}
