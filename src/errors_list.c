
static err_item errs_list[] = {
 { -27, "src/main_gzip.c: seekgzip_open failed" },
 { -23, "src/main_gzip.c: filename not supplied" },

	{ 0, NULL }
};
#define            errs_list_size      sizeof(errs_list[0])
#define            errs_list_nelements sizeof(errs_list) / errs_list_size
