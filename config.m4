PHP_ARG_ENABLE(decodep, whether to enable decodep support,
[  --enable-decodep           Enable decodep support])

if test "$PHP_DECODEP" != "no"; then
  PHP_NEW_EXTENSION(decodep, decodep.c, $ext_shared)
fi
