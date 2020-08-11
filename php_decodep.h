#ifndef PHP_DECODEP_H
#define PHP_DECODEP_H

extern zend_module_entry decodep_module_entry;
#define phpext_decodep_ptr &evalhook_module_entry

#ifdef PHP_WIN32
#	define PHP_DECODEP_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_DECODEP_API __attribute__ ((visibility("default")))
#else
#	define PHP_DECODEP_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(decodep);
PHP_MSHUTDOWN_FUNCTION(decodep);
PHP_MINFO_FUNCTION(decodep);

#ifdef ZTS
#define DECODEP_G(v) TSRMG(decodep_globals_id, zend_decodep_globals *, v)
#else
#define DECODEP_G(v) (decodep_globals.v)
#endif

#endif	/* PHP_DECODEP_H */



