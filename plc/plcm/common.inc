#ifndef COMMON_INC_INCLUDED
#define COMMON_INC_INCLUDED
//----------------------------------------------------------------------------
// TITOLO      : common.inc
// AUTORE      : Mattia Grandi
// DESCRIZIONE : macro di utilizzo comune o di utilità generale
//----------------------------------------------------------------------------

#include "rtplc.h"

#define DI(var, node, word, bit)     (var) = TO_RTPLC_BIT(DI_##node##_##word[bit])
#define DO(var, node, word, bit)     (DO_##node##_##word[bit]) = TO_RTPLC_BIT(var)
#define AI(var, node, word)          (var) = (AI_##node[word])
#define AO(var, node, word)          (AO_##node[word]) = (var)
#define ENC(var, node, word)         (var) = (ENC_##node[word])

// Costanti 
#define QT_MIN          (-1.0e+10)  // Minimo valore gestibile
#define QT_MAX          (+1.0e+10)  // Massimo valore gestibile
#define QT_EPSILON      (+1.0e-5)   // Minimo valore che rappresenta una variazione apprezzabile
#define QT_CHECK        (0.05)      // Discriminante usata per conversioni, confronti e quote

// Macro d'utilità
#define ABS(a)                              (((a) >= 0) ? (a) : (-(a)))
#define SIGN(a)                             (((a) > 0) ? (1) : (((a) < 0) ? (-1) : (0)))
#define MAX(a, b)                           (((a) > (b)) ? (a) : (b))
#define MIN(a, b)                           (((a) < (b)) ? (a) : (b))
#define SQUARE(a)                           ((a)*(a))
#define TO_RTPLC_BIT(value)                 (((value) != 0) ? (RTPLC_TRUE) : (RTPLC_FALSE))
#define IS_POSITIVE(value)                  (((value) > 0) ? (RTPLC_TRUE) : (RTPLC_FALSE))
#define LIMIT(v, l, h)                      (((v) < (l)) ? (l) : (((h) < (v)) ? (h) : (v)))
#define IN_RANGE(v, l, h)                   ((((l) <= (v)) && ((v) <= (h))) ? (RTPLC_TRUE) : (RTPLC_FALSE))
#define FTEVAL(v, e)                        (IN_RANGE(v, (e)-0.1, (e)+0.1))
#define FTB(v)                              (!IN_RANGE((v), -(QT_CHECK), (QT_CHECK)))
#define BTF(v)                              ((v) ? (1.0) : (0.0))
#define FTCHK(v, e)                         (IN_RANGE((v), (e)-(QT_CHECK), (e)+(QT_CHECK)))
#define CHECK_FLAG(var, mask)               (((var) & (mask)) ? (RTPLC_TRUE) : (RTPLC_FALSE))
#define SET_FLAG(var, mask)                 ((var) |= (mask))
#define CLEAR_FLAG(var, mask)               ((var) &= ~(mask))
#define SET_FLAG_VALUE(var, mask, value)    ((value) ? SET_FLAG(var, mask) : CLEAR_FLAG(var, mask))
#define AL_TO_ERRNUM(val)                   ((USHORT)((val) & 0xFFFF))

// Macro per il log dei messaggi tramite rtplctrace
#define LOG_MSG(ch, lvl, msg, ...)      ((*(msg) != '\0') ? (rtplctrace##ch((lvl), _T(__FUNCTION__)_T(" %d - ")_T(msg), __LINE__, __VA_ARGS__)) : (0))
#define LOG_MSG1(lvl, msg, ...)         LOG_MSG(, lvl, msg, __VA_ARGS__)
#define LOG_MSG2(lvl, msg, ...)         LOG_MSG(2, lvl, msg, __VA_ARGS__)
#define LOG_MSG3(lvl, msg, ...)         LOG_MSG(3, lvl, msg, __VA_ARGS__)
#define LOG_MSG4(lvl, msg, ...)         LOG_MSG(4, lvl, msg, __VA_ARGS__)

// Stati d'uscita dalle function block
#define FB_EXIT_FAILURE     (RTPLC_STATUS_ERRORFLAG)
#define FB_EXIT_SUCCESS     (RTPLC_STATUS_OK)
#define FB_EXIT_WAIT        (!RTPLC_STATUS_ERRORFLAG)

// Macro per il log nelle function block
#define FB_ENTER()          LOG_MSG2(3, "Enter")
#define FB_EXIT(sts)        do { LOG_MSG2(3, "Exit %d", sts); return (sts); } while(FALSE)
#define FB_EXIT_VOID()      do { LOG_MSG2(3, "Exit"); return; } while(FALSE)
#define FB_NOEXEC()         LOG_MSG2(3, "Not Exec")
#define FB_RESET()          LOG_MSG2(3, "Reset")

// Macro per la verifica degli stati di ritorno dalle funtion block
#define FB_SUCCESS(value)   (((value) == (RTPLC_STATUS_OK)) ? (RTPLC_TRUE) : (RTPLC_FALSE))
#define FB_FAILURE(value)   (((value) & (RTPLC_STATUS_ERRORFLAG)) ? (RTPLC_TRUE) : (RTPLC_FALSE))
#define FB_WAIT(value)      (!FB_SUCCESS(value) && !FB_FAILURE(value))

// Macro per il controllo delle macchine a stati
#define RESET_STATUS(sts, msg, ...)     (((sts) = (0)), LOG_MSG2(1, msg, __VA_ARGS__))
#define NEXT_STATUS(sts, msg, ...)      (((sts)++), LOG_MSG2(1, msg, __VA_ARGS__))
#define PREV_STATUS(sts, msg, ...)      (((sts)--), LOG_MSG2(1, msg, __VA_ARGS__))
#define JUMP_STATUS(sts, n, msg, ...)   (((sts) = (n)), LOG_MSG2(1, msg, __VA_ARGS__))
#define SKIP_STATUS(sts, msg, ...)      (((sts) += 2), LOG_MSG2(1, msg, __VA_ARGS__))
#define ERROR_STATUS(sts, msg, ...)     (((sts) = (W322RTPLC_STATUS(sts))), LOG_MSG2(1, msg, __VA_ARGS__))
#define RETRY_STATUS(sts, msg, ...)     (((sts) = (RTPLC_STATUS2W32(sts))), LOG_MSG2(1, msg, __VA_ARGS__))

// Macro per la definizione e l'inizializzazione locale di variant stringa
#define BUF_RTPLC_STRING(id, sz)        RTPLC_CHARSTRING id##_str[sz+1]; RTPLC_STRING id = {sz, id##_str}
#define CST_RTPLC_STRING(id, val)       RTPLC_STRING id = {ARRAY_SIZE(val)-1, val}
#define SET_ARRAY(ary, value)           do { int i; for (i = 0; i < ARRAY_SIZE(ary); i++) (ary)[i] = (value); } while (FALSE)
#define SET_ARRAYF(ary, func)           do { int i; for (i = 0; i < ARRAY_SIZE(ary); i++) { (func); } } while (FALSE)
#define SET_STRING(str, val)            srcpyfromchar(&(str).value.string, (val))

// Ridefinizione funzioni allarm 
#ifndef ALLARM_USHORT_MACRO_DEFINED
#define ALLARM_USHORT_MACRO_DEFINED
#undef allarm
#define allarm(code)    allarm((USHORT)((code) & 0xFFFF))
#undef allarmr
#define allarmr(code)   allarmr((USHORT)((code) & 0xFFFF))
#undef attenz
#define attenz(code)    attenz((USHORT)((code) & 0xFFFF))
#undef attenzr
#define attenzr(code)   attenzr((USHORT)((code) & 0xFFFF))
#undef messagep
#define messagep(code)  messagep((USHORT)((code) & 0xFFFF))
#undef messagepr
#define messagepr(code) messagepr((USHORT)((code) & 0xFFFF))
#endif // ALLARM_USHORT_MACRO_DEFINED

#endif // COMMON_INC_INCLUDED
