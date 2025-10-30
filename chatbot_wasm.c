#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ENTRADA 200

// ------------------ Definiciones ------------------
typedef enum { I_NONE=0, I_HORARIO, I_REQUISITOS, I_UNIFORMES, I_UBICACION,
            I_PASANTIAS, I_REDES, I_SERVICIOS, I_GRACIAS, I_AYUDA, 
            I_ESPECIALIDAD  } Intent;
typedef enum { S_NONE=0, S_INFORMATICA, S_SALUD, S_ELECTRO } Specialty;

// ------------------ Estado de memoria ------------------
static Intent ultimo_intent = I_NONE;

// ------------------ Keywords ------------------
const char *kw_horario[]    = {"horario","clase","clases","jornada", NULL};
const char *kw_requisitos[] = {"requisito","inscripcion","documentacion","admision", NULL};
const char *kw_uniformes[]  = {"uniforme","uniformes","vestimenta", NULL};
const char *kw_ubicacion[]  = {"ubicacion","donde","direccion","ubicado", NULL};
const char *kw_pasantias[]  = {"pasantia","pasantias", NULL};
const char *kw_redes[]      = {"redes","facebook","instagram","tiktok","twitter", NULL};
const char *kw_servicios[]  = {"instalacion","recurso","servicios", NULL};
const char *kw_gracias[]    = {"muchas","gracias","muchisimas", NULL};
const char *kw_ayuda[]      = {"ayuda","ayudar","responder","ofreces", NULL};
const char *kw_especialidades[]  = {"carreras","especialidades","especialidad", NULL};

// Especialidades
const char *kw_informatica[] = {"informatica","computacion","info", NULL};
const char *kw_salud[]       = {"salud","enfermeria", NULL};
const char *kw_electro[]     = {"electromecanica","mecanica","electro", NULL};

// ------------------ Respuestas ------------------
static const char *horarios[][4] = {
    /* S_NONE */ {
        "Para mostrarte el horario correcto, escribe: 'Horario' seguido de tu especialidad o curso. ", NULL, NULL, NULL 
    },//prueba para ver que pasa
    /* S_INFORMATICA */ {
        "Aquí tienes el horario de Informática de los 3 cursos: <a href='Horario de Informatica.pdf' download>Descargar PDF</a>",
        "Informática 1ro: Lunes y Miércoles 08:00-11:00",
        "Informática 2do: Martes y Jueves 09:00-12:00",
        "Informática 3ro: Viernes 10:00-13:00"
    },
    /* S_SALUD */ {
        "Aquí tienes el horario de Salud de los 3 cursos: <a href='Horario de Salud.pdf' download>Descargar PDF</a>",
        "Salud 1ro: Lunes 08:00-11:00",
        "Salud 2do: Martes 09:00-12:00",
        "Salud 3ro: Miércoles 10:00-13:00"
    },
    /* S_ELECTRO */ {
        "Aquí tienes el horario de Electromecánica de los 3 cursos: <a href='Horario de Electro.pdf' download>Descargar PDF</a>",
        "Electromecánica 1ro: Lunes 07:30-10:30",
        "Electromecánica 2do: Miércoles 09:00-12:00",
        "Electromecánica 3ro: Jueves 10:00-13:00"
    }
};

// ------------------ Utilidades ------------------
static void aMinusculas(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

static int match_any(const char *texto, const char *keywords[]) {
    for (int i=0; keywords[i] != NULL; i++) {
        if (strstr(texto, keywords[i]) != NULL) return 1;
    }
    return 0;
}

static int detectar_curso(const char *texto) {
    if (strstr(texto,"1ro") || strstr(texto,"1°") || strstr(texto,"primero") || strstr(texto,"1") || strstr(texto,"primer")) return 1;// le quite los espacios para ver si funciona con 1er
    if (strstr(texto,"2do") || strstr(texto,"2°") || strstr(texto,"segundo") || strstr(texto,"2") || strstr(texto,"segund")) return 2;
    if (strstr(texto,"3ro") || strstr(texto,"3°") || strstr(texto,"tercero") || strstr(texto,"3") || strstr(texto,"tercer")) return 3;
    return 0;
}

// ------------------ Núcleo ------------------
static const char* buscarRespuesta(const char *entrada) {
    static char copia[MAX_ENTRADA];
    strncpy(copia, entrada ? entrada : "", MAX_ENTRADA-1);
    copia[MAX_ENTRADA-1] = '\0';
    aMinusculas(copia);

    // Detectar intención
    Intent intent = I_NONE;
    if (match_any(copia, kw_horario)) intent = I_HORARIO;
    else if (match_any(copia, kw_requisitos)) intent = I_REQUISITOS;
    else if (match_any(copia, kw_uniformes))  intent = I_UNIFORMES;
    else if (match_any(copia, kw_ubicacion))  intent = I_UBICACION;
    else if (match_any(copia, kw_pasantias))  intent = I_PASANTIAS;
    else if (match_any(copia, kw_redes))      intent = I_REDES;
    else if (match_any(copia, kw_servicios))  intent = I_SERVICIOS;
    else if (match_any(copia, kw_gracias))    intent = I_GRACIAS;
    else if (match_any(copia, kw_ayuda))      intent = I_AYUDA;
    else if (match_any(copia, kw_especialidades)) intent = I_ESPECIALIDAD;

    // Detectar especialidad
    Specialty spec = S_NONE;
    if (match_any(copia, kw_informatica)) spec = S_INFORMATICA;
    else if (match_any(copia, kw_salud))  spec = S_SALUD;
    else if (match_any(copia, kw_electro)) spec = S_ELECTRO;

    // Detectar curso
    int curso = detectar_curso(copia);

    // ------------------ Respuestas con contexto ------------------

    // UNIFORMES (memoria)
    if (intent == I_UNIFORMES) {
        ultimo_intent = I_UNIFORMES;
        return "Hay tres uniformes: de gala, diario y educación física. ¿Sobre cuál quieres más información?";
    }
    if (ultimo_intent == I_UNIFORMES) {
        if (strstr(copia,"gala")) return "El uniforme de gala es camisa blanca, pantalón azul marino, pollera cuadrille p/ mujeres y corbata.";
        if (strstr(copia,"diario")) return "El uniforme diario es remera institucional y pantalón azul.";
        if (strstr(copia,"fisica")) return "El uniforme de educación física es la remera celeste institucional y el pantalón azul.";
    }

    // SERVICIOS (memoria)
    if (intent == I_SERVICIOS) {
        ultimo_intent = I_SERVICIOS;
        return "Servicios disponibles: Biblioteca, Cantina y Librería. ¿Cuál deseas conocer más?";
    }
    if (ultimo_intent == I_SERVICIOS) {
        if (strstr(copia,"biblioteca")) return "La biblioteca cuenta con más de 200 libros y está abierta de 08:00 a 14:00.";
        if (strstr(copia,"cantina")) return "La cantina ofrece variedad de refrigerios de 07:00 a 15:00.";
        if (strstr(copia,"libreria")) return "La librería vende útiles escolares, realiza fotocopias e impresiones.";
    }

    // HORARIOS
    if (intent == I_HORARIO) {
        ultimo_intent = I_HORARIO;
        if (spec != S_NONE) {
            if (curso >= 1 && curso <= 3) {
                return horarios[spec][curso];
            } else {
                return horarios[spec][0]; // general especialidad
            }
        } else {
            if (curso >= 1 && curso <= 3) {
                return "¿De qué especialidad? (especialidad + curso)";
            }
            return horarios[S_NONE][0];
        }
    }

    // HORARIOS (memoria)
if (ultimo_intent == I_HORARIO && intent == I_NONE) {
    int curso2 = detectar_curso(copia);
    Specialty spec2 = S_NONE;

    if (match_any(copia, kw_informatica)) spec2 = S_INFORMATICA;
    else if (match_any(copia, kw_salud))  spec2 = S_SALUD;
    else if (match_any(copia, kw_electro)) spec2 = S_ELECTRO;

    if (spec2 != S_NONE && curso2 >= 1 && curso2 <= 3) {
        return horarios[spec2][curso2];
    }
    if (spec2 != S_NONE) {
        return horarios[spec2][0]; // general especialidad
    }
    if (curso2 >= 1 && curso2 <= 3) {
        return "¿De qué especialidad? (especialidad + curso)";
    }
}

    // Otras intenciones simples
    if (intent == I_REQUISITOS) {
        ultimo_intent = I_REQUISITOS;
        return "Todo sobre el proceso de admisión, requisitos y fechas lo puedes encontrar en nuestra <a href='admisiones.html' innerHTML>página de Admisiones</a>.";
    }

    if (intent == I_UBICACION) {
        ultimo_intent = I_UBICACION;
        return "El colegio está ubicado sobre Pte. Hayes c/ Blvd. Bicentenario, Villarrica.<br><a href='https://maps.app.goo.gl/jKAiJticyFj9ZyUv8' target='_blank'>Ver ubicación</a>";
    }

    if (intent == I_PASANTIAS) {
        ultimo_intent = I_PASANTIAS;
        return "Las pasantías se realizan al termino del 2do año de cada especialidad. Para más detalles comunicarse con cada coordinación.";
    }

    if (intent == I_REDES) {
        ultimo_intent = I_REDES;
        return "Síguenos en nuestras redes:<br><a href='https://www.facebook.com/ctycevv/' target='_blank'>Facebook</a>, <br><a href='https://www.instagram.com/centro.de.estudiantesctycevv?utm_source=ig_web_button_share_sheet&igsh=ZDNlZDc0MzIxNw==' target='_blank'>Instagram</a>";
    }

    if (intent == I_GRACIAS) {
        ultimo_intent = I_GRACIAS;
        return "¡De nada! Ha sido un placer ayudarte. Si tienes más preguntas, no dudes en consultarme.";
    }

    if (intent == I_AYUDA) {
        ultimo_intent = I_AYUDA;
        return "Puedo ofrecerte información sobre:<br> -Horarios de clase.<br> -Requisitos de inscripción.<br> -Especialidades.<br> -Redes del colegio.<br> -Ubicación del colegio.<br> -Uniforme.<br> -Servicios que se ofrecen. ";
    }

    if (intent == I_ESPECIALIDAD) {
        ultimo_intent = I_ESPECIALIDAD;
        return "Ofrecemos 3 especialidades: Informática, Salud y Electromecánica. Puedes ver un resumen en nuestra <a href='index.html#especialidades' innerHTNL>página principal</a>.";
    }

    // Fallback
    ultimo_intent = I_NONE;
    return "No entendí exactamente. ¿Podrías repetirlo con más detalle?";
}


// ------------------ Exportar a JS ------------------
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
EMSCRIPTEN_KEEPALIVE
#endif
const char* responder(const char *entrada) {
    if (!entrada || strlen(entrada) == 0) {
        return "Por favor, escribe tu pregunta para poder ayudarte.";
    }
    return buscarRespuesta(entrada);
}
