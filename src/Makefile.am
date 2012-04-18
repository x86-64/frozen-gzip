modules_LTLIBRARIES = module_c_gzip.la
module_c_gzip_la_CFLAGS = -I@includedir@/frozen/ -I../ -DFROZEN_MODULE
module_c_gzip_la_LDFLAGS = -module -avoid-version -shared -lseekgzip
module_c_gzip_la_SOURCES = main_gzip.c
EXTRA_DIST = errors_list.c
