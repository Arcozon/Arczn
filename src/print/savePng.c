#include "arczn.h"

#define F_NAME_SIZE	512
const char	*_getFName(const t_art *art) {
	static const char	*genType[G_MAX] = {"Random", "Ivy", "Petri"};
	static const char	format[] = "png/%04d%02d%02d-%02d:%02d:%02d_%s_%lux%lu";
	static char	fName[F_NAME_SIZE] = {};

	if (art->fNameOut)
		return (art->fNameOut);

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	snprintf(fName, sizeof(fName), format,
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
		genType[art->gen], art->width, art->height);
	// printf("[%s]\n", fName);
	return (fName);
}

void	printSavePng(const t_art *art) {
	const char	*fName = _getFName(art);	
	int			err = 0;
	FILE		*pngFile	= fopen(fName, "w+");
	spng_ctx	*ctx		= spng_ctx_new(SPNG_CTX_ENCODER);
	uint8_t		*buff		= NULL;
	struct spng_ihdr ihdr	= {0};

	if (!pngFile || !ctx)	goto err;

	ihdr.width = art->widthClr;
	ihdr.height = art->heightClr;
	ihdr.bit_depth = 8;

	if (sizeof(t_clr) == 3)			ihdr.color_type = SPNG_COLOR_TYPE_TRUECOLOR;
	else if (sizeof(t_clr) == 4)	ihdr.color_type = SPNG_COLOR_TYPE_TRUECOLOR_ALPHA;

	if ((err = spng_set_ihdr(ctx, &ihdr))) goto err;
	if ((err = spng_set_png_file(ctx, pngFile))) goto err;

	const size_t	bSize = art->widthClr * art->heightClr * sizeof(t_clr);
	buff = malloc(bSize);
	if (!buff)	goto err;

	const size_t	buffLineWidth = art->widthClr * sizeof(t_clr);
	for (size_t i = 0; i < art->heightClr; ++i)
		memcpy(buff + i * buffLineWidth, art->arrClr[i], buffLineWidth);
	
	if ((err = spng_encode_image(ctx, buff, bSize, SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE))) goto err;
	goto done;
	
	err:	fprintf(stderr, "Err(%d): %s\n", err, spng_strerror(err));
	done:
	if (pngFile)
		fclose(pngFile);
	free(buff);
	if (ctx)
		spng_ctx_free(ctx);
}
