#include <libfrozen.h>
#include <gzip_t.h>
#include <seekgzip/seekgzip.h>

#include <errors_list.c>

#include <core/hash/hash_t.h>
#include <enum/format/format_t.h>
#include <numeric/uint/uint_t.h>

typedef seekgzip_t gzip_t;

static void    gzip_destroy(gzip_t *fdata){ // {{{
	seekgzip_close(fdata);
} // }}}
static ssize_t gzip_new(gzip_t **pfdata, config_t *config){ // {{{
	ssize_t                ret;
	char                  *filepath;
	gzip_t                *fdata;
	
	hash_data_convert(ret, TYPE_STRINGT, filepath, config, HK(filename));
	if(ret != 0)
		return error("filename not supplied");
	
	fdata = seekgzip_open(filepath, 0);
	if( (ret = seekgzip_error(fdata)) != SEEKGZIP_SUCCESS)
		return error("seekgzip_open failed");
	
	*pfdata = fdata;
	return 0;
} // }}}

static ssize_t data_gzip_t_convert_from(data_t *data, fastcall_convert_from *fargs){ // {{{
	ssize_t                ret;
	
	if(fargs->src == NULL)
		return -EINVAL; 
		
	switch(fargs->format){
		case FORMAT(config):;
		case FORMAT(human):;
		case FORMAT(native):;
			request_t r_config[] = {
				{ HK(filename), *fargs->src },
				hash_end
			};
			return gzip_new((gzip_t **)&data->ptr, r_config);

		case FORMAT(hash):;
			hash_t            *config;
			
			data_get(ret, TYPE_HASHT, config, fargs->src);
			if(ret != 0)
				return -EINVAL;
			
			return gzip_new((gzip_t **)&data->ptr, config);
			
		default:
			break;
	};
	return -ENOSYS;
} // }}}
static ssize_t data_gzip_t_free(data_t *data, fastcall_free *fargs){ // {{{
	if(data->ptr != NULL)
		gzip_destroy(data->ptr);
	
	return 0;
} // }}}
static ssize_t data_gzip_t_read(data_t *data, fastcall_read *fargs){ // {{{
	ssize_t                ret;
	gzip_t                *fdata             = (gzip_t *)data->ptr;
	
	if(!fdata)
		return -EINVAL;
	
	seekgzip_seek(fdata, fargs->offset);
	ret = seekgzip_read(fdata, fargs->buffer, fargs->buffer_size);
	
	if(ret == 0 && fargs->buffer_size != 0){
		fargs->buffer_size = 0;
		return -1; // EOF
	}
	
	fargs->buffer_size = ret;
	return 0;
} // }}}
/*static ssize_t data_gzip_t_len(data_t *data, fastcall_length *fargs){ // {{{
	ssize_t                ret;
	gzip_t                *fdata             = (gzip_t *)data->ptr;
	
	if(fdata == NULL)
		return -EINVAL;
	
	//fargs->length = seekgzip_length(fdata);
	return 0;
} // }}}*/
static ssize_t data_gzip_t_nosys(data_t *data, fastcall_create *fargs){ // {{{
	return -ENOSYS;
} // }}}

data_proto_t gzip_t_proto = {
	.type_str               = "gzip_t",
	.api_type               = API_HANDLERS,
	.handlers               = {
		[ACTION_CONVERT_FROM] = (f_data_func)&data_gzip_t_convert_from,
		[ACTION_FREE]         = (f_data_func)&data_gzip_t_free,
		//[ACTION_LENGTH]       = (f_data_func)&data_gzip_t_len,
		[ACTION_READ]         = (f_data_func)&data_gzip_t_read,
		
		[ACTION_CREATE]       = (f_data_func)&data_gzip_t_nosys,
		[ACTION_WRITE]        = (f_data_func)&data_gzip_t_nosys,
		[ACTION_RESIZE]       = (f_data_func)&data_gzip_t_nosys,
	}
};


int main(void){
	errors_register((err_item *)&errs_list, &emodule);
	data_register(&gzip_t_proto);
	return 0;
}
