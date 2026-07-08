#include "arczn.h"
#include "parg.h"

__always_inline
void	_cpy_TRUECOLOR(const void *img, const size_t imgWidth, t_clr *clr[], const size_t heightClr, const size_t widthClr) {
	for (size_t i = 0; i < heightClr; ++i) {
		memcpy(clr[i], img + (i * imgWidth), widthClr * sizeof(t_clr));
	}
}

__always_inline
void	_cpy_TRUECOLOR_ALPHA(const void *img, const size_t imgWidth,
		t_clr *clr[], const size_t heightClr, const size_t widthClr) {
	for (size_t i = 0; i < heightClr; ++i) {
		for (size_t j = 0; j < widthClr; ++j) {
			memcpy(&clr[i][j], img + (i * imgWidth) + j * 4, sizeof(t_clr));
		}
	}
}

const char *color_type_str(enum spng_color_type color_type)
{
    switch(color_type)
    {
        case SPNG_COLOR_TYPE_GRAYSCALE: return "grayscale";
        case SPNG_COLOR_TYPE_TRUECOLOR: return "truecolor";
        case SPNG_COLOR_TYPE_INDEXED: return "indexed color";
        case SPNG_COLOR_TYPE_GRAYSCALE_ALPHA: return "grayscale with alpha";
        case SPNG_COLOR_TYPE_TRUECOLOR_ALPHA: return "truecolor with alpha";
        default: return "(invalid)";
    }
}

int	parsBaseImage(const char *baseFName, t_nonConstArt *art) {
	int			err = 0;
	FILE		*f = fopen(baseFName, "r");
	spng_ctx	*ctx	= spng_ctx_new(0);
	uint8_t		*img	= NULL;
	size_t		imgSize		= 0;
	size_t		imgWidth	= 0;
	struct spng_ihdr ihdr	= {0};

	if (!f || !ctx) {
		err = 1;
		goto err;
	}
	spng_set_crc_action(ctx, SPNG_CRC_USE, SPNG_CRC_USE);
	const size_t limit = 1024 * 1024 * 64;
	spng_set_chunk_limits(ctx, limit, limit);
	if ((err = spng_set_png_file(ctx, f))) {
		fprintf(stderr, "Err spng_set_png_file\n");
		goto err;
	}
	if ((err = spng_get_ihdr(ctx, &ihdr))) {
		fprintf(stderr, "Err spng_get_ihdr\n");
		goto err;
	}
	if (ihdr.bit_depth != 8
		|| (ihdr.color_type != SPNG_COLOR_TYPE_TRUECOLOR
		&& ihdr.color_type != SPNG_COLOR_TYPE_TRUECOLOR_ALPHA)) {
		err = 1;
		goto err;
	}
	
	if ((err = spng_decoded_image_size(ctx, SPNG_FMT_PNG, &imgSize))) {
		fprintf(stderr, "Err spng_decoded_image_size\n");
		goto err;
	}
	imgWidth = imgSize / ihdr.height;
	img = malloc(imgSize);
	if (!img) {
		printf("Malloc err");
		return (err);
	}
	if ((err = spng_decode_image(ctx, img, imgSize, SPNG_FMT_PNG, 0))) {
		fprintf(stderr, "Err spng_decode_image\n");
		goto err;
	}
	art->width = (ihdr.width + 1) / 2;
	art->height = (ihdr.height + 1) / 2;
	if (_allocClr(art)) {
		err = 1;
		goto err;
	}
	switch (ihdr.color_type) {
		case SPNG_COLOR_TYPE_TRUECOLOR:
			_cpy_TRUECOLOR(img, imgWidth, art->arrClr, art->heightClr, art->widthClr);
			break;
			case SPNG_COLOR_TYPE_TRUECOLOR_ALPHA:	
			_cpy_TRUECOLOR_ALPHA(img, imgWidth, art->arrClr, art->heightClr, art->widthClr);
			break;
		default:
			fprintf(stderr, "Wrong color_type\n");
			err = 12;
			goto err;
			break;
	}

	goto done;
	err:
		fprintf(stderr, "BaseImg: Err(%d): %s\n", err, spng_strerror(err));
	done:
	if (f)			fclose(f);
	if (ctx)		spng_ctx_free(ctx);
	free(img);
	return (0);
	(void)art;
}
