#ifdef HAVE_CONFIG_H
#include "config.h"
#berakhir jika

#include "php.h"
#include "php_ini.h"
#include "ext / standard / info.h"
#include "zend_compile.h"
#include "php_decodep.h"

zend_module_entry decodep_module_entry = {
#jika ZEND_MODULE_API_NO> = 20010901
	STANDARD_MODULE_HEADER,
#berakhir jika
	"decodep",
    BATAL,
	PHP_MINIT (decodep),
	PHP_MSHUTDOWN (decodep),
	BATAL,
	BATAL,
	PHP_MINFO (decodep),
#jika ZEND_MODULE_API_NO> = 20010901
	"0,1",
#berakhir jika
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_DECODEP
ZEND_GET_MODULE (decodep)
#berakhir jika

statis zend_op_array * (* orig_compile_string) (zval * source_string, char * nama file TSRMLS_DC);
statis zend_bool decodep_hooked = 0;

statis zend_op_array * decodep_compile_string (zval * source_string, char * nama file TSRMLS_DC)
{
	int c, len, ya;
	char * copy;
	
	/ * Abaikan eval non string () * /
	jika (Z_TYPE_P (source_string)! = IS_STRING) {
		return orig_compile_string (source_string, nama file TSRMLS_CC);
	}
	
	len = Z_STRLEN_P (string_sumber);
	salin = estrndup (Z_STRVAL_P (string_sumber), len);
	if (len> strlen (copy)) {
		untuk (c = 0; c <len; c ++) if (salin [c] == 0) salin [c] == '?';
	}
	
	printf ("Skrip mencoba mengevaluasi string berikut. \ n");
	printf ("---- \ n");
	printf ("% s \ n", salin);
	printf ("---- \ nApakah Anda ingin mengizinkan eksekusi? [y / N] \ n");
	
	ya = 0;
	sementara (1) {
		c = getchar ();
		jika (c == '\ n') putus;
		jika (c == 'y' || c == 'Y') {
			ya = 1;
		}
    }

	jika ya) {
		return orig_compile_string (source_string, nama file TSRMLS_CC);
	}
	
	zend_error (E_ERROR, "decodep: skrip dibatalkan karena eval ()") yang tidak diizinkan;
}


PHP_MINIT_FUNCTION (decodep)
{
	jika (decodep_hooked == 0) {
		decodep_hooked = 1;
		orig_compile_string = zend_compile_string;
		zend_compile_string = decodep_compile_string;
	}
	kembali SUKSES;
}

PHP_MSHUTDOWN_FUNCTION (decodep)
{
	jika (decodep_hooked == 1) {
		decodep_hooked = 0;
		zend_compile_string = orig_compile_string;
	}
	kembali SUKSES;
}

PHP_MINFO_FUNCTION (decodep)
{
	php_info_print_table_start ();
	php_info_print_table_header (2, "dukungan decodep", "diaktifkan");
	php_info_print_table_end ();
}
