PHP_ARG_ENABLE (decodep, apakah akan mengaktifkan dukungan decodep,
[   --enable-decodep Aktifkan dukungan decodep ] )

jika uji "$ PHP_DECODEP"! = "tidak"; kemudian
  PHP_NEW_EXTENSION (decodep, decodep.c, $ ext_shared)
fi
