#ifndef DATA_GZIPT_H
#define DATA_GZIPT_H

/** @ingroup data
 *  @addtogroup gzip_t gzip_t
 */
/** @ingroup gzip_t
 *  @page gzip_t_overview Overview
 *  
 * This data can random read from gzipped file.
 */
/** @ingroup gzip_t
 *  @page gzip_t_define Configuration
 * 
 * Accepted configuration:
 * @code
 * some = (gzip_t){
 *              filename    = "somefilename.dat",     // simple file path
 * }
 *
 * some = (gzip_t)"FILENAME"                          // open file with default parameters
 * @endcode
 */

#define GZIPT_NAME  "gzip_t"
#define TYPE_GZIPT  datatype_t_getid_byname(GZIPT_NAME, NULL)

#endif
