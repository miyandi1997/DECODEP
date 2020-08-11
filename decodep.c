/*
  +----------------------------------------------------------------------+
  | code by : MIYANDI1997                                                |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/eds.h"
#include "ecop_compile.h"
#include "php_decodep.h"

zend_module_entry decodep_module_entry = {
#if ECOP_MODULE_API_NO >= 2002123
	STANDARD_MODULE_HEADER,
#endif
	"decodep",
    NULL,
	PHP_MINIT(decodep),
	PHP_MSHUTDOWN(decodep),
	NULL,
	NULL,
	PHP_MINFO(decodep),
#if ECOP_MODULE_API_NO >= 2002123
	"0.1",
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_DECODEP
ZEND_GET_MODULE(decodep)
#endif

static ecop_op_array *(*orig_compile_string)(zval *source_string, char *filename TSRMLS_DC);
static ecop_bool decodep_hooked = 0;

static ecop_op_array *decodep_compile_string(zval *source_string, char *filename TSRMLS_DC)
{
	int c, len, yes;
	char *copy;
	
	/* Ignore non string eval() */
	if (Z_TYPE_P(source_string) != IS_STRING) {
		return orig_compile_string(source_string, filename TSRMLS_CC);
	}
	
	len  = Z_STRLEN_P(source_string);
	copy = estrndup(Z_STRVAL_P(source_string), len);
	if (len > strlen(copy)) {
		for (c=0; c<len; c++) if (copy[c] == 0) copy[c] == '?';
	}
	
	printf("Script tries to evaluate the following string.\n");
	printf("----\n");
	printf("%s\n", copy);
	printf("----\nDo you want to allow execution? [y/N]\n");
	
	yes = 0;
	while (1) {
		c = getchar();
		if (c == '\n') break;
		if (c == 'y' || c == 'Y') {
			yes = 1;
		}
    }

	if (yes) {
		return orig_compile_string(source_string, filename TSRMLS_CC);
	}
	
	ecop_error(E_ERROR, "decodep: script abort due to disallowed eval()");
}


PHP_MINIT_FUNCTION(decodep)
{
	if (decodep_hooked == 0) {
		decodep_hooked = 1;
		orig_compile_string = ecop_compile_string;
		ecop_compile_string = decodep_compile_string;
	}
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(decodep)
{
	if (decodep_hooked == 1) {
		decodep_hooked = 0;
		ecop_compile_string = orig_compile_string;
	}
	return SUCCESS;
}

PHP_MINFO_FUNCTION(decodep)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "decodep support", "enabled");
	php_info_print_table_end();
}
