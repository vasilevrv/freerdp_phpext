PHP_ARG_ENABLE(freerdp, Whether to enable the FreeRDP extension, [  --enable-freerdp Enable FreeRDP])

if test "$PHP_HELLOWORLD" != "no"; then
    PHP_NEW_EXTENSION(freerdp, freerdp.c, $ext_shared)
fi

LDFLAGS="-L/usr/lib/x86_64-linux-gnu -l:libfreerdp-core.so $LDFLAGS"
