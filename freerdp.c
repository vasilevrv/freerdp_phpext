#include <php.h>
#include <freerdp/freerdp.h>
#include "freerdp.h"

struct tf_context
{
        rdpContext _p;
};

typedef struct tf_context tfContext;

static BOOL tf_context_new(freerdp* instance, rdpContext* context)
{
        return TRUE;
}

static void tf_context_free(freerdp* instance, rdpContext* context)
{
}

static BOOL tf_pre_connect(freerdp* instance)
{
    return TRUE;
}

static BOOL tf_post_connect(freerdp* instance)
{
    return TRUE;
}

zend_function_entry freerdp_functions[] = {
    PHP_FE(freerdp_test, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry freerdp_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_FREERDP_EXTNAME,
    freerdp_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_FREERDP_VERSION,
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(freerdp)

PHP_FUNCTION(freerdp_test) {

    char *rdp_hostname;
    char *rdp_username;
    char *rdp_password;

    int rdp_hostname_len;
    int rdp_username_len;
    int rdp_password_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                          "sss", &rdp_hostname, &rdp_hostname_len, &rdp_username, &rdp_username_len, &rdp_password, &rdp_password_len) == FAILURE) {
        return;
    }

    freerdp* instance;
    BOOL res;
    instance = freerdp_new();
    if (!instance) {
        exit(1);
    }


    instance->PreConnect = tf_pre_connect;
    instance->PostConnect = tf_post_connect;
    instance->ContextSize = sizeof(tfContext);
    instance->ContextNew = tf_context_new;
    instance->ContextFree = tf_context_free;

    freerdp_context_new(instance);

    rdpSettings* settings;
    settings = instance->settings;
    settings->ServerHostname = rdp_hostname;
    settings->Password = rdp_password;
    settings->Username = rdp_username;
    settings->AuthenticationOnly = TRUE;
    settings->IgnoreCertificate = TRUE;

    res = freerdp_connect(instance);
    RETVAL_BOOL(res);
}
